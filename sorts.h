#ifndef SORTS_H_
#define SORTS_H_
#include <vector>
using namespace std;

//Helpers
void Swap (int &num1, int &num2) {
	int temp = num1;
	num1 = num2;
	num2 = temp;
}
void Merge(vector<int>& items, int start, int mid, int end) {
	int size = (end - start) + 1;
	int* tmp_arr;
	tmp_arr = new int[size];
	int first1 = start;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = end;
	int index = 0;

	while ((first1 <= last1) && (first2 <= last2)) {
		if (items[first1] < items[first2]) {
			tmp_arr[index] = items[first1];
			first1++;
		}
		else {
			tmp_arr[index] = items[first2];
			first2++;
		}
		index++;
	}
	while (first1 <= last1) {
		tmp_arr[index] = items[first1];
		first1++;
		index++;
	}
	while (first2 <= last2) {
		tmp_arr[index] = items[first2];
		first2++;
		index++;
	}
	for (index = 0; index < size; index++) {
		items[start] = tmp_arr[index];
		start++;
	}
	delete[] tmp_arr;
}
bool checkBounds(vector<int>& items, int index1, int index2) {
	if (index2 > items.size() - 1) {
		cerr << "UNABLE TO SORT \n\n";
		return false;
	}
	else if (index1 < 0) {
		cerr << "UNABLE TO SORT \n\n";
		return false;
	}
	else if (index2 < index1) {
		cerr << "UNABLE TO SORT \n\n";
		return false;
	}
	return true;
}
//End of Helpers

void InsertionSort(vector<int>& items, int start, int end) {
	if (!checkBounds(items, start, end))
		return;

	for (int place = (start + 1); place < (end + 1); place++) {
		int temp = items[place];
		int i = place;
		while ((i > start) && (items[i - 1] > temp)) {
			items[i] = items[i - 1];
			i--;
		}
		items[i] = temp;
	}
}
void BubbleSort(vector<int> &items, int start, int end) {
	if (!checkBounds(items, start, end))
		return;
	
	for (int i = start; i < end; i++) {
		for (int j = start; j < (end -(i - start)); j++) {
			if (items[j]> items[j+1]) {
				Swap(items[j], items[j + 1]);
			}
		}
	}
}
void MergeSort(vector<int> &items, int start, int end) {
	if (!checkBounds(items, start, end))
		return;

	if (start < end) {
		int mid = (start + end) / 2;
		MergeSort(items, start, mid);
		MergeSort(items, mid + 1, end);
		Merge(items,start,mid,end);
	}
}
void IterativeMergeSort(vector<int> &items, int start, int end) {
	if (!checkBounds(items, start, end))
		return;
	int size = end - start;
	//faster access time than a vector (about 2 times faster)
	int *additional; 
	additional = new int[size]; 
	
	int curr_size;  // current size of the 2 subarrays being merged	  
	int left_start; // For picking starting index of left subarray
					// to be merged
	for (curr_size = 1; curr_size <= size; curr_size *= 2){
		int index = 0;
		for (left_start = start; left_start <= end; left_start += (2 * curr_size)){
			int mid = min(left_start + curr_size - 1, end);
			int right_end = min(left_start + 2 * curr_size - 1, end);
			
			int first1 = left_start;
			int last1 = mid;
			int first2 = mid + 1;
			int last2 = right_end;
			while ((first1 <= last1) && (first2 <= last2)) {
				if (items[first1] < items[first2]) {
					additional[index] = items[first1];
					first1++;
					index++;
				}
				else {
					additional[index] = items[first2];
					first2++;
					index++;
				}
			}
			while (first1 <= last1) {
				additional[index] = items[first1];
				first1++;
				index++;
			}
			while (first2 <= last2) {
				additional[index] = items[first2];
				first2++;
				index++;
			}
		}
		if ((curr_size * 2) <= size) { //merge back up
			int index = 0;
			curr_size *= 2;
			for (left_start = 0; left_start < end; left_start += (2 * curr_size))
			{
				int mid = min(left_start + curr_size - 1, size);
				int right_end = min(left_start + 2 * curr_size - 1, size);

				int first1 = left_start;
				int last1 = mid;
				int first2 = mid + 1;
				int last2 = right_end;
				
				while ((first1 <= last1) && (first2 <= last2)) {
					if (additional[first1] < additional[first2]) {
						items[index+start] = additional[first1];
						first1++;
						index++;
					}
					else {
						items[index+start] = additional[first2];
						first2++;
						index++;
					}
				}
				while (first1 <= last1) {
					items[index+start] = additional[first1];
					first1++;
					index++;
				}
				while (first2 <= last2) {
					items[index+start] = additional[first2];
					first2++;
					index++;
				}
			}
		}
		
		else {// if it can't merge back up, just copy back to original vector
			for (int i = 0; i < size+1; i++) {
				items[i + start] = additional[i];
			}
		}
	}
}
void QuickSortRecursive(vector<int>& items, int start, int end) {
	//base case
	if (end - start < 5) {
		InsertionSort(items, start, end);
		return;
	}
	//find the pivot by sorting first mid last
	int mid = (start + end) / 2;
	if (items[start] > items[end]) {
		Swap(items[start], items[end]);
	}
	if (items[start] > items[mid]) {
		Swap(items[start], items[mid]);
	}
	if (items[mid] > items[end]) {
		Swap(items[mid], items[end]);
	}

	//put the pivot 1 before the last
	int pivot = items[mid];
	Swap(items[mid], items[end - 1]);

	//Partition our vector around pivot value
	int left = start + 1;
	int right = end - 2;
	bool done = false;
	while (!done) {
		while (items[left] < pivot) {
			left++;
		}
		while (items[right] > pivot) {
			right--;
		}
		if (right > left) {
			Swap(items[left], items[right]);
			left++;
			right--;
		}
		else {
			done = true;
		}
	}
	//place pivot in correct location
	Swap(items[left], items[end - 1]);

	QuickSortRecursive(items, start, left - 1);
	QuickSortRecursive(items, left + 1, end);
}
void QuickSort(vector<int>& items, int start, int end) {
		if (!checkBounds(items, start, end))
		return;
	QuickSortRecursive(items, start, end);
}
void ShellSort(vector<int> &items, int start, int end) {
	if (!checkBounds(items, start, end))
		return;

	int size = (end - start) + 1;
	int gap;
	for (gap = size / 2; gap > 0; gap = (gap == 2) ? 1 : int(gap / 2.2)) {
		for (int i = gap; i < size; i++) {
			int tmp = items[i + start];
			int j = i;
			for (; j >= gap && (tmp < items[(j-gap)+start]); j -= gap) {
				items[j + start] = items[(j - gap )+start];
		    }
			items[j + start] = tmp;
		}
	}
}

#endif


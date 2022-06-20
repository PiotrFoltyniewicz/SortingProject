#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <iostream>

namespace sort
{
	void BubbleSort(std::vector<int>& tab);
	void InsertionSort(std::vector<int>& tab);
	void CountingSort(std::vector<int>& tab);
	void BucketSort(std::vector<int>& tab);
	void MergeSort(std::vector<int>& tab);
	void SelectionSort(std::vector<int>& tab);
	void ShellSort(std::vector<int>& tab);
	void CombSort(std::vector<int>& tab);
	void QuickSort(std::vector<int>& tab);
}
#endif
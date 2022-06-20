#include "sorting.h"
#include <math.h>
#include <iomanip>

//prywatne funkcje
namespace
{
	void SwapElements(int& a, int& b)
	{
		int p = a;
		a = b;
		b = p;
	}

	std::vector<int> Merge(std::vector<int> tab)
	{
		if (tab.size() <= 1) return tab;

		//dzielenie tablicy
		int midIndex = tab.size() / 2;
		std::vector<int> leftTab(tab.begin(), tab.begin() + midIndex);
		std::vector<int> rightTab(tab.begin() + midIndex, tab.begin() + tab.size());

		leftTab = Merge(leftTab);
		rightTab = Merge(rightTab);
	
		//odpowiednie umieszczanie elementów w tablicy rodzica
		int i = 0;
		int j = 0;
		int k = 0;

		while (i < leftTab.size() && j < rightTab.size()) {
			//porównuje po elemencie z lewej i prawej tablicy i mniejszy zostaje przeniesiony 
			if (leftTab[i] < rightTab[j]) {
				tab[k] = leftTab[i];
				i++;
			}
			else {
				tab[k] = rightTab[j];
				j++;
			}
			k++;
		}
		//w przypadku gdy jedna z tablic jest d³u¿sza to zostaj¹ nie przeniesione wartoœci i teraz w³aœnie bêd¹ przeniesione
		while (i < leftTab.size()) {
			tab[k] = leftTab[i];
			i++;
			k++;
		}

		while (j < rightTab.size()) {
			tab[k] = rightTab[j];
			j++;
			k++;
		}
		return tab;
	}

	int Partition(std::vector<int>& tab, int leftIndex, int rightIndex) {
		int pivotIndex = leftIndex + (rightIndex - leftIndex) / 2;
		int pivotValue = tab[pivotIndex];
		int i = leftIndex;
		int	j = rightIndex;
		int temp;
		while (i <= j) {
			while (tab[i] < pivotValue) {
				i++;
			}
			while (tab[j] > pivotValue) {
				j--;
			}
			if (i <= j) {
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
				i++;
				j--;
			}
		}
		return i;
	}

	void Quick(std::vector<int> & tab, int leftIndex, int rightIndex) 
	{
		if (leftIndex < rightIndex) {
			int pivotIndex = Partition(tab, leftIndex, rightIndex);
			Quick(tab, leftIndex, pivotIndex - 1);
			Quick(tab, pivotIndex, rightIndex);
		}
	}
}

//sortowanie babelkowe
void sort::BubbleSort(std::vector<int>& tab)
{
	int n = tab.size();

	while (n > 1)
	{
		for (int i = 0; i < n - 1; i++)
		{
			if (tab[i] > tab[i + 1])
				SwapElements(tab[i], tab[i + 1]);
		}
		n--;
	}
}

//sortowanie przez wstawianie
void sort::InsertionSort(std::vector<int>& tab)
{
	int n = tab.size();
	int key;

	for (int i = 1; i < n; i++)
	{
		key = tab[i];

		for (int j = 0; j < i; j++)
		{
			if (key < tab[j])
			{
				tab.insert(tab.begin() + j, key);
				tab.erase(tab.begin() + i + 1);
				break;
			}
		}
	}
}

//sortowanie przez zliczanie
void sort::CountingSort(std::vector<int>& tab)
{
	int n = tab.size();
	int max = tab[0];
	for (int i = 0; i < n; i++)
	{
		if (tab[i] > max)
			max = tab[i];
	}


	std::vector<int> count(max + 1);
	std::vector<int> output(n);

	for (int i = 0; i < n; i++)
	{
		int j = tab[i];
		count[j]++;
	}

	for (int i = 1; i <= max; i++)
	{
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		int j = tab[i];
		count[j]--;
		output[count[j]] = tab[i];
	}
	tab.clear();

	for (int i = 0; i < n; i++)
	{
		tab.push_back(output[i]);
	}
}

//sortowanie kube?kowe
void sort::BucketSort(std::vector<int>& tab)
{
	int n = tab.size();
	int max = tab[0];
	for (int i = 0; i < n; i++)
	{
		if (tab[i] > max)
			max = tab[i];
	}

	std::vector<std::vector<int>> buckets(ceil(sqrt(n)) + 1);
	int b = buckets.size();
	double proportion = ceil((double)max / (double)tab.size());

	int index;
	for (int i = 0; i < n; i++)
	{
		index = floor((tab[i] / b) / proportion);
		buckets[index].push_back(tab[i]);
	}

	for (int i = 0; i < b; i++)
	{
		sort::InsertionSort(buckets[i]);
	}

	int k = 0;

	for (int i = 0; i < b; i++)
	{
		for (int j = 0; j < buckets[i].size(); j++)
		{
			tab[k] = buckets[i][j];
			k++;
		}
	}
}

//sortowanie przez scalanie
void sort::MergeSort(std::vector<int>& tab)
{
	tab = Merge(tab);
}

//sortowanie Shella
void sort::ShellSort(std::vector<int>& tab)
{
	int n = tab.size();

	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i++)
		{
			int temp = tab[i];

			int j;
			for (j = i; j >= gap && tab[j - gap] > temp; j -= gap)
			{
				tab[j] = tab[j - gap];
			}

			tab[j] = temp;
		}
	}
}

//sortowanie grzebieniowe
void sort::CombSort(std::vector<int>& tab)
{
	auto GetGap = [](int gap)
	{

		gap = gap * 10 / 13;
		if (gap < 1) return 1;

		return gap;
	};

	int n = tab.size();

	int gap = n;

	bool isSorted = false;

	while (gap != 1 || isSorted == false)
	{
		gap = GetGap(gap);

		isSorted = true;

		for (int i = 0; i < n - gap; i++)
		{
			if (tab[i] > tab[i + gap])
			{
				SwapElements(tab[i], tab[i + gap]);
				isSorted = false;
			}
		}
	}
}

//sortowanie przez wybor
void sort::SelectionSort(std::vector<int>& tab)
{
	int minIndex;
	int n = tab.size();

	for (int i = 0; i < n - 1; i++)
	{
		minIndex = i;

		for (int j = i + 1; j < n; j++)
		{
			if (tab[j] < tab[minIndex])
			{
				minIndex = j;
			}
		}
		SwapElements(tab[minIndex], tab[i]);
	}
}

//sortowanie szybkie
void sort::QuickSort(std::vector<int>& tab) {

	int left = 0;
	int right = tab.size() - 1;

	return Quick(tab, left, right);
}
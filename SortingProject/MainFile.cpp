#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "sorting.h"
#include <fstream>
#include <string>

using namespace std;
using namespace sort;

typedef void (*sortingFunction)(vector<int>&);

vector<int> GenerateRandomList(int maxValue, int amount)
{
	srand(time(NULL));
	vector<int> tempList;
	for (int i = 1; i <= amount; i++)
	{
		tempList.push_back(rand() % maxValue + 1);
	}
	return tempList;
}

double MeasureTime(sortingFunction sort, vector<int> tab, bool print = false)
{
	double timeDiff;
	clock_t start, end;

	start = clock();

	sort(tab);

	end = clock();
	timeDiff = (end - start) / (long double)CLOCKS_PER_SEC;

	if (print)
		cout << "Execution time: " << timeDiff << '\n';
	return timeDiff;
}

// dla wektora intow / wektora z wartosciami
void SaveList(vector<int> tab, string fileName)
{
	ofstream file;

	file.open(fileName, ios::out);

	if (!file.good())
	{
		cout << "Error when opening file." << '\n';
		return;
	}

	for (int i = 0; i < tab.size(); i++)
	{
		file << tab[i] << '\n';
	}
	cout << "Saved list to the file " << fileName << '\n';
}

// dla wektora double / wektor z pomiarami czasu
void SaveMeasurements(vector<double long> tab, string fileName, int amount, int maxValue, int size)
{
	ofstream file;

	file.open(fileName, ios::out);

	if (!file.good())
	{
		cout << "Error when opening the file." << '\n';
		return;
	}

	file << "Result of " << amount << " measurements for list of length " << size << " and maximum value " << maxValue << '\n';
	file << "Average sorting time: " << tab.back() << '\n';
	tab.pop_back();

	for (int i = 0; i < tab.size(); i++)
	{
		file << tab[i] << '\n';
	}
	cout << "Measurements saved to the file " << fileName << '\n';
}

vector<int> GetList(string fileName)
{
	vector<int> tab;
	ifstream file;

	file.open(fileName, ios::in);

	if (!file.good())
	{
		cout << "Error when opening the file." << '\n';

		return tab;
	}

	int value;
	while (file >> value)
	{
		tab.push_back(value);
	}

	cout << "File loaded" << '\n';

	return tab;
}

void PrintList(vector<int> tab)
{
	for (int i = 0; i < tab.size(); i++)
	{
		cout << tab[i] << " ";
	}
	cout << '\n';
}

vector<int> CopyList(vector<int> tab)
{
	return tab;
}

void MeasureAndSave(sortingFunction sort, string fileName, int amount, int length)
{
	vector<int> list;
	vector<double long> measurements(amount);

	double long average = 0;
	for (int i = 0; i < amount; i++)
	{
		measurements[i] = MeasureTime(sort, GenerateRandomList(20000, length));
		average += measurements[i];
		cout << "Repetition " << i + 1 << '\n';
	}
	average /= amount;
	measurements.push_back(average);
	SaveMeasurements(measurements, fileName, amount, 20000, length);
}

void MeasureAndSaveIncreasingLength(sortingFunction sort, string fileName, int amount, int length)
{
	vector<int> list;
	vector<double long> measurements(amount);

	ofstream file;

	file.open(fileName, ios::out);

	for (int i = 0; i < amount; i++)
	{
		file << MeasureTime(sort, GenerateRandomList(20000, length)) << '\n';
		length += 10000;
		cout << "Repetition " << i + 1 << '\n';
	}

	cout << "Measurements saved to the file " << fileName << '\n';
}

int main()
{
	//             algorytm,  nazwa pliku, ilosc testow, dlugosc tablicy
	MeasureAndSave(BubbleSort, "BubbleSort.txt", 5, 20000);
	MeasureAndSave(InsertionSort, "InsertionSort.txt", 5, 20000);
	MeasureAndSave(SelectionSort, "SelectionSort.txt", 5, 20000);
	MeasureAndSave(CountingSort, "CountingSort.txt", 5, 20000);
	MeasureAndSave(MergeSort, "MergeSort.txt", 5, 20000);
	MeasureAndSave(ShellSort, "ShellSort.txt", 5, 20000);
	MeasureAndSave(CombSort, "CombSort.txt", 5, 20000);
	MeasureAndSave(BucketSort, "BucketSort.txt", 5, 20000);
	MeasureAndSave(QuickSort, "QuickSort.txt", 5, 20000);
	MeasureAndSaveIncreasingLength(BubbleSort, "BubbleSortIncreasing.txt", 5, 10000);
	MeasureAndSaveIncreasingLength(InsertionSort, "InsertionSortIncreasing.txt", 5, 10000);
	MeasureAndSaveIncreasingLength(SelectionSort, "SelectionSortIncreasing.txt", 5, 10000);
	MeasureAndSaveIncreasingLength(CountingSort, "CountingSortIncreasing.txt", 5, 10000);
	MeasureAndSaveIncreasingLength(MergeSort, "MergeSortIncreasing.txt", 5, 10000);
	MeasureAndSaveIncreasingLength(ShellSort, "ShellSortIncreasing.txt", 5, 10000);
	MeasureAndSaveIncreasingLength(CombSort, "CombSortIncreasing.txt", 5, 10000);
	MeasureAndSaveIncreasingLength(BucketSort, "BucketSortIncreasing.txt", 5, 10000);
	MeasureAndSaveIncreasingLength(QuickSort, "QuickSortIncreasing.txt", 5, 10000);
}

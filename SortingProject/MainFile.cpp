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
		cout << "Czas wykonania: " << timeDiff << '\n';
	return timeDiff;
}

// dla wektora intow / wektora z wartosciami
void SaveList(vector<int> tab, string fileName)
{
	ofstream file;

	file.open(fileName, ios::out);

	if (!file.good())
	{
		cout << "Blad przy otwieraniu pliku." << '\n';
		return;
	}

	for (int i = 0; i < tab.size(); i++)
	{
		file << tab[i] << '\n';
	}
	cout << "Zapisano liste w pliku " << fileName << '\n';
}

// dla wektora double / wektor z pomiarami czasu
void SaveMeasurements(vector<double long> tab, string fileName, int amount, int maxValue, int size)
{
	ofstream file;

	file.open(fileName, ios::out);

	if (!file.good())
	{
		cout << "Blad przy otwieraniu pliku." << '\n';
		return;
	}

	file << "Wynik " << amount << " pomiarow dla tablicy o dlugosci " << size << " i maksymalnej wartosci " << maxValue << '\n';
	file << "Sredni czas sortowania: " << tab.back() << '\n';
	tab.pop_back();

	for (int i = 0; i < tab.size(); i++)
	{
		file << tab[i] << '\n';
	}
	cout << "Zapisano pomiary w pliku " << fileName << '\n';
}

vector<int> GetList(string fileName)
{
	vector<int> tab;
	ifstream file;

	file.open(fileName, ios::in);

	if (!file.good())
	{
		cout << "Blad przy otwieraniu pliku." << '\n';

		return tab;
	}

	int value;
	while (file >> value)
	{
		tab.push_back(value);
	}

	cout << "Wczytano plik" << '\n';

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
		cout << "Powtorzenie " << i + 1 << '\n';
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
		cout << "Powtorzenie " << i + 1 << '\n';
	}

	cout << "Zapisano pomiary w pliku " << fileName << '\n';
}

int main()
{
	//             algorytm,  nazwa pliku, ilosc testow, dlugosc tablicy
	MeasureAndSave(BubbleSort, "BubbleSort.txt", 10, 10000);
	MeasureAndSave(InsertionSort, "InsertionSort.txt", 10, 10000);
	MeasureAndSave(SelectionSort, "SelectionSort.txt", 10, 10000);
	MeasureAndSave(CountingSort, "CountingSort.txt", 10, 10000);
	MeasureAndSave(MergeSort, "MergeSort.txt", 10, 10000);
	MeasureAndSave(ShellSort, "ShellSort.txt", 10, 10000);
	MeasureAndSave(CombSort, "CombSort.txt", 10, 10000);
	MeasureAndSave(BucketSort, "BucketSort.txt", 10, 10000);
	MeasureAndSave(QuickSort, "QuickSort.txt", 10, 10000);
}

// Name: Andrew Pinkerton
// Assignment: Insertion and Merge Sort Comparison
// Date: 9/13/2024

#include<iostream>
#include<cstdlib>
#include<ctime>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

//Function to generate random array...
void generateRandomArray(int arr[], int size, int lower_bound, int upper_bound)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = lower_bound + (rand() % (upper_bound - lower_bound + 1));
	}
}

//Function for insertion sort
void insertionSort(int arr[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int j = i;
		while (j > 0 && arr[j - 1] > arr[j])
		{
			int temp = arr[j - 1];

			arr[j - 1] = arr[j];
			arr[j] = temp;

			j--;
		}
	}
}

//Function for merge 
void merge(int arr[], int left, int mid, int right)
{
	const int arrLeftLength = mid - left + 1;
	const int arrRightLength = right - mid;

	vector<int> arrayLeft(arrLeftLength), arrayRight(arrRightLength);

	for (int i = 0; i < arrLeftLength; i++)
	{
		arrayLeft[i] = arr[left + i];
	}
	for (int j = 0; j < arrRightLength; j++)
	{
		arrayRight[j] = arr[mid + j + 1];
	}
	int i = 0;
	int j = 0;
	int k = left;

	while (i < arrLeftLength && j < arrRightLength)
	{
		if (arrayLeft[i] <= arrayRight[j])
		{
			arr[k] = arrayLeft[i];
			i++;
		}
		else
		{
			arr[k] = arrayRight[j];
			j++;
		}
		k++;
	}

	while (i < arrLeftLength)
	{
		arr[k] = arrayLeft[i];
		i++;
		k++;
	}
	while (j < arrRightLength)
	{
		arr[k] = arrayRight[j];
		j++;
		k++;
	}
}

//Function for mergeSort
void mergeSort(int arr[], int left, int right)
{
	if (left >= right)
		return;
	int mid = left + (right - left) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);

	merge(arr, left, mid, right);
}

//Print array
void printArray(const int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << (i < size - 1 ? "," : "");
	}
	cout << endl;
}

// Driver code
int main()
{
	const int size = 100; // Change random array size
	int arr[size], arrCopy[size]; // Copy for Merge Sort

	// Seeding the RNG
	srand(time(0));
	// Generate the array
	generateRandomArray(arr, size, 1, 1000);

	copy(arr, arr + size, arrCopy); //Copy array for Merge Sort

	// Measure time taken by Insertion Sort
	auto startInsertion = high_resolution_clock::now();
	insertionSort(arr, size);
	auto stopInsertion = high_resolution_clock::now();
	auto durationInsSort = duration_cast<microseconds> (stopInsertion - startInsertion);

	// Measure time taken by Merge Sort
	auto startMerge = high_resolution_clock::now();
	mergeSort(arrCopy, 0, size-1);
	auto stopMerge = high_resolution_clock::now();
	auto durationMergeSort = duration_cast<microseconds> (stopMerge - startMerge);

	cout << "Insertion Sorted Array: " << endl;
	printArray(arr, size);
	cout << endl << endl;

	cout << "Merge Sorted Array: " << endl;
	printArray(arrCopy, size);

	//Insertion Sort Time Display
	cout << endl << "Insertion sort time: " << durationInsSort.count() << " milliseconds";

	//Merge Sort Time Display
	cout << endl << "Merge sort time: " << durationMergeSort.count() << " milliseconds" << endl << endl;

	return 0;
}
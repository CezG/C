

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <chrono> 
using namespace std::chrono;
using namespace std;

const int n = 5000;    //size of table

void copyArray(int [], int [], int );
void checkTimeAndPrintSorting(int [], int , void(*)(int [], int ), string );
void checkTimeAndPrintSorting(int [], int , int , int , void(*)(int [], int , int ), string );
void insertValuesToTable(int , int []);
void insertDecreasingValuesIntoTable(int []);
void insertIncreasingValuesIntoTable(int []);
void bubbleSort(int [], int);
void printTable(int [], string );
void maxHeapify(int [], int , int );
int parent(int );
void heapSort(int [], int );
void quickSort(int [], int , int );
int partition(int [], int , int );


int main()
{
	int A[n], B[n];

	insertValuesToTable(n, A);
	int arraySize = sizeof(A) / sizeof(A[0]);
	cout << "array size = " << arraySize << endl << endl;
	
	int p = 0;				// first index of array - to quicksort
	int r = arraySize - 1;	// last index of array	- to quicksort
	
	copyArray(A, B, arraySize);
	checkTimeAndPrintSorting(A, arraySize, bubbleSort, "bubble sort - random values");
	copyArray(B, A, arraySize);
	checkTimeAndPrintSorting(A, arraySize, heapSort, "heap sort - random values");
	copyArray(B, A, arraySize);
	checkTimeAndPrintSorting(A, arraySize, p, r, quickSort, "quick sort - random values");
	
	insertDecreasingValuesIntoTable(A);
	copyArray(A, B, arraySize);
	checkTimeAndPrintSorting(A,arraySize, bubbleSort, "bubble sort - decreasing values");
	copyArray(B, A, arraySize);
	checkTimeAndPrintSorting(A, arraySize, heapSort, "heap sort - decreasing values");
	copyArray(B, A, arraySize);
	checkTimeAndPrintSorting(A, arraySize, p, r, quickSort, "quick sort - decreasing values");
	
	insertIncreasingValuesIntoTable(A);
	copyArray(A, B, arraySize);
	checkTimeAndPrintSorting(A, arraySize, bubbleSort, "bubble sort - increasing values");
	copyArray(B, A, arraySize);
	checkTimeAndPrintSorting(A, arraySize, heapSort, "heap sort - increasing values");
	copyArray(B, A, arraySize);
	checkTimeAndPrintSorting(A, arraySize, p, r, quickSort, "quick sort - increasing values");
	
    return 0;
}

void copyArray(int first[], int second[], int arraySize) {
	for (int i = 0; i <= arraySize; i++) {
		second[i] = first[i];
	}
}

void checkTimeAndPrintSorting( int A[], int arraySize, void(*function)(int A[], int arraySize), string arrayName ) {

	//cout << endl << "Before ";
	//printTable(A, arrayName);
	auto start = high_resolution_clock::now();
	//cout << "After " ;
	function(A, arraySize);
	auto stop = high_resolution_clock::now();
	//printTable(A, arrayName);
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by function "<< arrayName << " :" << duration.count() << " microseconds\n" << endl;
}

void checkTimeAndPrintSorting(int A[], int arraySize, int p, int r, void(*function)(int A[], int p, int r), string arrayName) {

	//cout << endl << "Before ";
	//printTable(A, arrayName);
	auto start = high_resolution_clock::now();
	//cout << "After " ;
	function(A, p, r);
	auto stop = high_resolution_clock::now();
	//printTable(A, arrayName);
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by function " << arrayName << " :" << duration.count() << " microseconds\n" << endl;
}


void insertValuesToTable(int maxRange, int A[]) {

	for (int i = 0; i < n; i++) {
		A[i] = rand() % maxRange;
	}
}

void insertDecreasingValuesIntoTable( int A[]) {
	int j = n;
	for (int i = 0; i < n; i++) {
		A[i] = --j;
	}
}
void insertIncreasingValuesIntoTable(int A[]) {
	for (int i = 0; i < n; i++) {
		A[i] = i;
	}
}

void bubbleSort(int A[], int nottUsed) {		//like it was on first semester on C++ 

	int i, j, tmp;
	for (i = 1; i <= n; i++) {
		for (j=n-1; j>= i; j--)
			if (A[j] < A[j - 1]) {
				tmp = A[j - 1];
				A[j - 1] = A[j];
				A[j] = tmp;
			}
	}
}

void printTable(int array[], string arrayName) {

	cout << arrayName <<"[] = ";
	for (int i = 0; i < n; i++) {
		cout << array[i] << ", ";
	}
	cout << endl << endl ;
}

void maxHeapify(int A[], int i, int heapSize) {
	
	int largest = i;
	int l = 2 * i + 1;  // l = left
	int r = 2 * i + 2;	// r = right
		
	if (l < heapSize && A[l] > A[i])
		largest = l;
	else largest = i;  
	if (r < heapSize && A[r] > A[largest])
		largest = r;

	if (largest != i) {
		swap(A[i], A[largest]);
		return maxHeapify(A, largest, heapSize);
	}
}

int parent(int i) {
	return i / 2 -1;
}

void heapSort(int A[], int arraySize){

	for (int i = parent(arraySize); i >= 0; i--)
		maxHeapify(A, i, arraySize);

	for (int i = arraySize - 1; i >= 0; i--) {
		swap(A[0], A[i]);
		maxHeapify(A,0, i );
	}
}

void quickSort(int A[], int p, int r) {

	if (p < r) {
		int q = partition(A, p, r);
		quickSort(A, p, q - 1);
		quickSort(A, q + 1, r);
	}
}

int partition(int A[], int p, int r) {
	int x = A[r];
	int i = (p - 1);
	for (int j = p; j <= r - 1; j++) {
		if (A[j] <= x) {
			i++;
			swap(A[i], A[j]);
		}		
	}
	swap(A[i + 1], A[r]);
	return (i + 1);
}




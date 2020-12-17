#include <iostream>
#include <time.h>
#include <iomanip>
#include <random>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class Sorter{
public:
  Sorter();
  ~Sorter();
  void BubbleSort(double numbers[], int numSize);
  void SelectionSort(double numbers[], int numSize);
  void InsertionSort(double numbers[], int numbersSize);
  void Merge(double numbers[], int i, int j, int k);
  void MergeSort(double numbers[], int i, int k);
  void swap(double* a, double* b);
  int Partition(double *numbers, int left, int right, int index);
  void QuickSort(double *numbers, int left, int right, int pivot);
  void generateNumbers(int size, double min, double max, string fileName);
  bool readNums(string fileName);
  void sortAll(string fileName);

  double *bubbleSortArray;
  double *selectionSortArray;
  double *insertionSortArray;
  double *mergeSortArray;
  double *quickSortArray;
  int size;

};

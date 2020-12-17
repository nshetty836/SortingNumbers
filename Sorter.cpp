#include "Sorter.h"

//default constructor
Sorter::Sorter(){}

//destructor
Sorter::~Sorter(){
  delete [] bubbleSortArray;
  delete [] selectionSortArray;
  delete [] insertionSortArray;
  delete [] mergeSortArray;
  delete [] quickSortArray;
}

//uses bubble method to sort an array
void Sorter::BubbleSort(double numbers[], int numSize){
  for(int i = 0; i < numSize; ++i){
    double temp = 0;
    for(int j = i+1; j < numSize; ++j){
      if(numbers[j] < numbers[i]){
        swap(&numbers[i], &numbers[j]);
      }
    }
  }
}

//uses selection method to sort an array
void Sorter::SelectionSort(double numbers[], int numSize) {
   int i = 0;
   int j = 0;
   int indexSmallest = 0;
   double temp = 0;  // Temporary variable for swap

   for (i = 0; i < numSize - 1; ++i) {

      // Find index of smallest remaining element
      indexSmallest = i;
      for (j = i + 1; j < numSize; ++j) {

         if ( numbers[j] < numbers[indexSmallest] ) {
            indexSmallest = j;
         }
      }

      // Swap numbers[i] and numbers[indexSmallest]
      temp = numbers[i];
      numbers[i] = numbers[indexSmallest];
      numbers[indexSmallest] = temp;
   }
}

//uses insertion method to sort an array
void Sorter::InsertionSort(double numbers[], int numbersSize) {
   int j = 0;
   double temp = 0;  // Temporary variable for swap

   for (int i = 1; i < numbersSize; ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && numbers[j] < numbers[j - 1]) {

         // Swap numbers[j] and numbers[j - 1]
         temp = numbers[j];
         numbers[j] = numbers[j - 1];
         numbers[j - 1] = temp;
         --j;
      }
   }
}

//sorts parted array and merges arrays back together
void Sorter::Merge(double numbers[], int i, int j, int k) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   double *mergedNumbers = new double[mergedSize];   // Dynamically allocates temporary array
                                                   // for merged numbers

   leftPos = i;                         // Initialize left partition position
   rightPos = j + 1;                      // Initialize right partition position

   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (numbers[leftPos] <= numbers[rightPos]) {
         mergedNumbers[mergePos] = numbers[leftPos];
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = numbers[rightPos];
         ++rightPos;

      }
      ++mergePos;
   }

   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }

   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }

   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
}

//uses merge method to sort an array
void Sorter::MergeSort(double numbers[], int i, int k) {
   int j = 0;

   if (i < k) {
      j = (i + k) / 2 ; // Find the midpoint in the partition

      // Recursively sort left and right partitions
      MergeSort(numbers, i, j);
      MergeSort(numbers, j + 1, k);

      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k);
   }
}

// A utility function to swap two elements
void Sorter::swap(double* a, double* b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

void Sorter::QuickSort(double *numbers, int left, int right, int pivot) {
  // If the partition size is not 1 or zero
  // elements, then the partition is not yet sorted
  if (left < right) {
    pivot = Partition(numbers, left, right, pivot);

    //recursively sort left and right partitions
    QuickSort(numbers, left, pivot - 1, left);
    QuickSort(numbers, pivot + 1, right, pivot + 1);

  }
}

//chooses a pivot to divide the data into left and right
int Sorter::Partition(double *numbers, int left, int right, int index) {
  double pivotValue = numbers[index];
  int storedIndex = left;
  double tmp;

  tmp = numbers[index];
  numbers[index] = numbers[right];
  numbers[right] = tmp;

  for (int i = left; i < right; i++) {
    if (numbers[i] <= pivotValue) {
      tmp = numbers[i];
      numbers[i] = numbers[storedIndex];
      numbers[storedIndex] = tmp;

      storedIndex++;
    }
  }

  tmp = numbers[storedIndex];
  numbers[storedIndex] = numbers[right];
  numbers[right] = tmp;

  return storedIndex;
}

//generates random numbers given the amount, minimum and maximum nums, and file name to output to
void Sorter::generateNumbers(int size, double min, double max, string fileName){
  srand(time(nullptr));
  ofstream fout;
  fout.open(fileName);
  fout << size << endl;
  for(int i = 0; i < size; ++i){
    fout << fixed << setprecision(2)
             << min + (double)(rand()) / ((double)(RAND_MAX/(max - min)))
             << endl;
  }
  fout.close();
}

//reads numbers from a file and adds them to 5 arrays for the 5
//returns true if the file was successfully loaded, false otherwise
bool Sorter::readNums(string fileName){
  ifstream fileIn;
  try{
    fileIn.open(fileName);
    if (fileIn.is_open() == true)
    {
      string line;
      getline(fileIn, line);
      size = stoi(line);
      double num;

      //Dynamically allocating arrays
      bubbleSortArray = new double[size];
      selectionSortArray = new double[size];
      insertionSortArray = new double[size];
      mergeSortArray = new double[size];
      quickSortArray = new double[size];

      //for each number in the file, add to each array
      for(int i = 0; i < size; ++i){
        getline(fileIn >> ws, line);
        num = stod(line);
        bubbleSortArray[i] = num;
        selectionSortArray[i] = num;
        insertionSortArray[i] = num;
        mergeSortArray[i] = num;
        quickSortArray[i] = num;
      }
      fileIn.close();
      return true;

    }
    else{
      cout << "File could not be opened.\n" << endl;
    }
  }
  catch(exception e){
    cout << "Error in file." << endl;

  }
  return false;
}

//sorts all the arrays using 5 different methods and outputs amount of time it took
void Sorter::sortAll(string fileName){
  bool opened = readNums(fileName);
  if(opened == true){
    clock_t tStart = clock();
    BubbleSort(bubbleSortArray, size);
    cout << "\nBubble Sort " << endl;
    cout << "-----------------------" << endl;
    cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;

    tStart = clock();
    SelectionSort(selectionSortArray, size);
    cout << "\nSelection Sort " << endl;
    cout << "-----------------------" << endl;
    cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;

    tStart = clock();
    InsertionSort(insertionSortArray, size);

    cout << "\nInsertion Sort " << endl;
    cout << "-----------------------" << endl;
    cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;

    tStart = clock();
    MergeSort(mergeSortArray, 0, size-1);

    cout << "\nMerge Sort " << endl;
    cout << "-----------------------" << endl;
    cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;

    tStart = clock();

    QuickSort(quickSortArray, 0, size - 1, 0);

    cout << "\nQuick Sort " << endl;
    cout << "-----------------------" << endl;
    cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;
    cout << endl;
  }
}

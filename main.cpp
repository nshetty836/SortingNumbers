#include <iostream>
#include "Sorter.h"

using namespace std;

int main(int argc, char **argv){
  Sorter s;

  int choice = 0;
  int size, min, max;
  string input, fileName = "";

  //if there is a command line argument, load that file to sort
  if(argc >=2){
    fileName = argv[1];
    cout << "Loaded file '" << fileName << "' from command line." << endl;
    cout << endl;
  }

  //keep asking user for their choice until they exit
  while(choice != 4){
    cout << "Sorting Test Menu: " << endl;
    cout << "1) Generate Numbers \n2) Sort Numbers and Output Times \n3) Sort My File and Output Times \n4) Exit" << endl;
    cout << "Choice: ";
    try{
      getline(cin, input);
      choice = stoi(input);
    }
    catch(exception e){
      cout << "\nError: invalid input." << endl;
    }

    //Allows the user to enter amount of numbers, min and max, and file name to output
    if(choice == 1){
      try{
        cout << "\nEnter the amount of numbers you would like to generate: " << endl;
        getline(cin, input);
        size = stoi(input);
        cout << "Enter the minimum number of the random generation: " << endl;
        getline(cin, input);
        min = stoi(input);
        cout << "Enter the maximum number of the random generation: " << endl;
        getline(cin, input);
        max = stoi(input);
        cout << "Enter the file name: " << endl;
        getline(cin, fileName);
        cout << "\nGenerating numbers...\n" << endl;
        s.generateNumbers(size, min, max, fileName);
        cout << "Numbers generated.\n" << endl;
      }
      catch (exception e){
        cout << "Error: Invalid input." << endl;
      }
    }
    //sorts generated numbers
    else if(choice == 2){
      if(fileName == ""){
        cout << "Error: Empty file. Generate numbers before sorting.\n" << endl;
      }
      else{
        s.sortAll(fileName);
      }
    }
    //sorts numbers from a given file
    else if(choice == 3){
      cout << "Enter the file name: " << endl;
      getline(cin, fileName);
      bool opened = s.readNums(fileName);
      if(opened == true){
        s.sortAll(fileName);
        cout << endl;
      }
    }
    //exits the program
    else if(choice == 4){
      cout << "All done.\n" << endl;
    }
    else{
      cout << "\nPlease enter a number from 1 to 4.\n" << endl;
    }
  }

  return 0;
};

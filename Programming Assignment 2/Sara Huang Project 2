// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
	   << (*ipD)->val2 << " " 
	   << (*ipD)->val3 << " " 
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

void insertionSort(list<Data *> &l) { //insertion sort function for first column
  int SIZE = l.size();
  Data** array1 = new Data*[SIZE];
  copy(l.begin(),l.end(),array1); //making copy of array
  Data* tmp = new Data();
  for (int p = 1; p < SIZE; p++) {
    tmp->val1 = array1[p]->val1; //making sure each value aligns in the array
    tmp->val2 = array1[p]->val2;
    tmp->val3 = array1[p]->val3;
    tmp->val4 = array1[p]->val4;
    int j;
    for(j = p; j > 0 && tmp->val1 < array1[j-1]->val1; j--) {
      array1[j]->val1 = array1[j-1]->val1;
      array1[j]->val2 = array1[j-1]->val2;
      array1[j]->val3 = array1[j-1]->val3;
      array1[j]->val4 = array1[j-1]->val4;
    }
    array1[j]->val1 = tmp->val1; //updating the array
    array1[j]->val2 = tmp->val2;
    array1[j]->val3 = tmp->val3;
    array1[j]->val4 = tmp->val4;
  }
  list<Data *> outputList;
  for (int i = 0; i < SIZE; i++) {
    outputList.push_back(array1[i]);
  }
  l = outputList;
}

list<Data *>::iterator i_0, i_1, i_2, i_3; //global
list<Data *>::iterator tmp_0, tmp_1;
list<Data *> bucket_2[65536]; //buckets as lists for column 2 of 2^16; split into 2 halves - 16 upper bits, 16 bottom bits
void intSort(list<Data *> &l) { //bucket sort function for second column
    unsigned int i, j, k;
    for(i_1 = l.begin(); i_1 != l.end(); i_1++) {
        j = (*i_1)->val2;
        i = 0xFFFF0000&j; //bitwise AND (2^32-2^16)
        i = i >> 16; //shift 16 bits down
        bucket_2[i].push_back(*i_1); //put values back in
    }
    for(k = 1; k < 65536; k++) {
        i_2 = bucket_2[0].end();
        bucket_2[0].splice(i_2,bucket_2[k]); //organize buckets according to the end of the previous one and add each successive one
    }
    l.swap(bucket_2[0]);
    i_0 = l.begin();
    i_3 = l.end();
    for(i_1 = i_0; i_1 != i_3; i_1++) { //insertion sort on remaining buckets
        tmp_0 = i_1;
        tmp_1 = i_1;
        tmp_1--;
        unsigned int j = (*tmp_0)->val2;
        while(tmp_0 != i_0 && (*tmp_1)->val2 > j) {
            std::iter_swap(tmp_1,tmp_0); //forward iterator to objects to be swapped
            tmp_1--;
            tmp_0--;
        }
    }
}

char c;
list<Data* > bucket[94]; //buckets as lists for column 3 of 94 
void charSort(list<Data *> &l) { //bucket sort for third column
  i_1 = l.begin();
  i_2 = l.end();
  for (i_0 = i_1; i_0 != i_2; i_0++) { 
    c = ((*i_0)->val3)-33; //arrange buckets according to ASCII character value in column 3 shifted by 33
    bucket[c].push_back(*i_0); //put values back in
  }
  for (int i = 1; i < 94; i++) {
    i_1= bucket[0].end();
    bucket[0].splice(i_1,bucket[i]); //organize buckets according to the end of the previous one and add each successive one
  }
  l.swap(bucket[0]); //replace with ordered buckets
}

string y;
void stringSort(list<Data *> &l) { //bucket sort for fourth column
    char c;
    for(int i = 2; i >= 0; i--) { //arrange by first 3 positions of string
        for(i_1 = l.begin(); i_1 != l.end(); i_1++) {
            c = (*i_1)->val4[i];
            bucket[c-33].push_back(*i_1); //shift by ASCII character value range [33,126], put values back in
        }
        for(int j = 1; j < 94; j++) { //for ASCII character range within position
            i_2 = bucket[0].end();
            bucket[0].splice(i_2,bucket[j]); //position buckets
            bucket[j].clear();
        }
        l.swap(bucket[0]); //replace with ordered buckets
        bucket[0].clear(); //remove 
    }
    i_0 = l.begin();
    i_3 = l.end();
    for(i_1 = i_0; i_1 != i_3; i_1++) { //insertion sort on remaining buckets, organize buckets according to the end of the previous one and add each successive one
        tmp_0 = i_1;
        tmp_1 = i_1;
        tmp_1--;
        y = (*tmp_0)->val4;
        while(tmp_0 != i_0 && (*tmp_1)->val4 > y) {
            std::iter_swap(tmp_1,tmp_0); //forward iterator to objects to be swapped
            tmp_1--;
            tmp_0--;
        }
    }
}

void sortDataList(list<Data *> &l, int field) {
  // Fill in this function
switch (field) {
  case 1: insertionSort(l);
  break;
  case 2: intSort(l);
  break;
  case 3: charSort(l);
  break;
  case 4: stringSort(l);
  break;
}
}

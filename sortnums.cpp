/*
 *  Comp 15
 *  Sorting Assignment
 *
 *  sortnums.cpp
 *  Author:  Conor Jenkinson, Tufts University, Spring 2016
 *
 */  

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <tgmath.h>
#include "IntVector.h"

using namespace std;

string algorithmFromCommandLine(int argc, char *argv[]);
void   usageAbort (string progname, string message);
void   readNumbers(istream &input, IntVector &data);
void   sortNumbers(string algorithm, IntVector &data);
void   printNumbers(IntVector &data);

void swap(IntVector &vector, int i, int j);
void bubbleSort(IntVector &data);
void mergeSort(IntVector &data);
IntVector leftHalf(IntVector &data);
IntVector rightHalf(IntVector &data);
void merge(IntVector &result, IntVector &left, IntVector &right);
void insertionSort(IntVector &data);
int findMax(IntVector &data, int a);
void quickSort(IntVector &data, int left, int right);
void radixSort(IntVector &data);
int number_of_digits(int num);
int findMin(IntVector &data, int a);
void initialize_array(int ar[], int size);
void shellSort(IntVector &data);
void bucketSort(IntVector &data);

int main(int argc, char *argv[])
{      
    IntVector data;
    string    sortAlgorithm;
      
    sortAlgorithm = algorithmFromCommandLine(argc, argv);
    readNumbers(cin, data);
    sortNumbers(sortAlgorithm, data);
    printNumbers(data);

    return 0;
}

/*
 * Abort the program with a message on standard error
 * explaining how to run the program correctly from the 
 * command line.
 */
void usageAbort(string progname, string message)
{
    cerr << message << endl
         << "Usage:  " << progname << " algorithm" << endl
         << "     where algorithm is one of "
         << "bubble, sort2, or sort3"
         << endl;
    exit(1);
}
//reads the command line input
//and returns the selected algorithm 
string algorithmFromCommandLine(int argc, char *argv[]){
    (void) argc; 
    if ((strcmp(argv[1],"bubble") == 0) or (
        strcmp(argv[1],"sort2") == 0) or (
        strcmp(argv[1], "sort3") == 0)){
        string algorithm = argv[1];
        return algorithm;
    } 
     
    string message = "No valid algorithm selected";
    usageAbort(argv[0], message);
    return "q";
}  
 
void readNumbers(istream &input, IntVector &data){
    (void) input; 
    int num = 0 ;
    while(cin>>num){
        data.add(num);
    }
}
/*
 * Read in a collection of integers from the given input stream
 * and add them to the end of the data vector.  Input numbers are
 * separated by whitespace (they don't have to be one per line).
 *
 * Does not distinguish between failure due to end
 * of file or any other failure of the input device.  
 *
 */
void sortNumbers(string algorithm, IntVector &data){
//Updates contents of data so items are sorted using the chosen
//algorithm.
    if (algorithm == "bubble"){
        bubbleSort(data);
    }   
    if (algorithm == "sort2"){
        insertionSort(data);
    }
    if (algorithm == "sort3"){
        radixSort(data);
    }
}
void printNumbers( IntVector &data){
// Print contents of data one item per line.
    int size = data.size();
    for (int i = 0 ; i < size ; i++){
        cout << data.get(i) << endl;
    }
}   
//In-place sort of contents of data using the bubble sort algorithm. 
void bubbleSort(IntVector &data){
    int size = data.size();   
    for (int i = 0 ; i < size-1  ; i++){
        for (int j = 0; j < size -1 - i ; j++){
            if (data.get(j) > data.get(j+1)){
                swap(data,j,j+1);
            }   
        }
    }
}       
 
 
void swap(IntVector &vector, int i, int j){
    // Updates the given vector so that the items at position i and j
    //are swapped.
    int c = vector.get(i);
    vector.set(i,(vector.get(j)));
    vector.set(j,c);

}
void mergeSort(IntVector &data){
    if (data.size() > 1){
        IntVector left;     //split array into halves
        IntVector right;
        left = leftHalf(data);
        right = rightHalf(data);
        mergeSort(left);    //recursively sort halves
        mergeSort(right);

        merge(data,left,right); //merge the sorted halves
    }
}
//returns the left half of the given array
IntVector leftHalf(IntVector &data){
    int size1 = data.size() / 2;
    IntVector left(size1);
    for (int i = 0; i < size1; i++){
        left.add(data.get(i));
    } 
    return left;
}
//returns the right half of the given array
IntVector rightHalf(IntVector &data){
    int size1 = data.size() / 2;
    int size2 = data.size() - size1;
    IntVector right(size2);
    for (int i = 0; i < size2; i++){
        right.add(data.get(i+size1));
    } 
    return right;
}
//merges the given left and right arrays into resulting array
void merge(IntVector &result, IntVector &left, IntVector &right){
    int i1 = 0;
    int i2 = 0;
    for (int i = 0; i < result.size(); i++){
        if(i2>=right.size()  or (i1 < left.size()
        and left.get(i1) <= right.get(i2))){
            result.set(i,left.get(i1));
            i1++;
        }
        else {
            result.set(i,right.get(i2));
            i2++;    
        }
    }
}
//sort of data using insertion sort algorithm
void insertionSort(IntVector &data){
    for (int i = 0; i < data.size(); i++){
        swap(data,i,findMin(data,i));
    }
}
//returns the maximum number of the IntVector
int findMax(IntVector &data, int a){
    int max = a;
    for (int i = a; i < data.size(); i++){
        if(data.get(i)>data.get(max)){
            max = i;
        }
    }
    return max; 
}
//returns the minimum number of the IntVector
int findMin(IntVector &data, int a){
    int min = a;
    for (int i = a; i < data.size(); i++){
        if(data.get(i)<data.get(min)){
            min = i;
        }
    }
    return min; 
}
//sorts data using an inplace quick sort
void quickSort(IntVector &data, int left, int right){
    if (left == right){
        return;
    }
    int pivot_loc = left;  //pivot is always leftmost number
    int pivot = data.get(pivot_loc);
    int a = left;
    int b = right;
    while (left != right){
        if (data.get(right) >= pivot){
            right--; 
        }
        if (left == right){
            break; 
        }
        if (data.get(left) <= pivot){
            left++;
        }
        if ((data.get(right) < pivot) and
        (data.get(left) > pivot)){
            swap(data,left,right);
        }
    }

    swap(data,pivot_loc,right); //pivot is in place
    quickSort(data, a, right);  //recursively sorts each side of pivot    
    quickSort(data, pivot_loc+1, b);
}
//sorts data using radix sort
void radixSort(IntVector &data){
    int pass = 0;
    int count[10];
    int new_ar[data.size()]; 
    initialize_array(count, 10);
    initialize_array(new_ar, data.size());
    int num_digits = number_of_digits(data.get(findMax(data,0)));
    int location;
    int base = 10;
    int last_index = data.size()-1; 
    while (pass < num_digits){  
        for (int i = 0; i < data.size(); i++){
            location = (int)((data.get(i)) / pow(base, pass)) % base; 
            count[location]++; //fills up count array 
        }
        for (int i = 1; i < base; i++){
           count[i] += count[i-1]; //adjusts count positions
        }
        for (int i = last_index; i >= 0 ; i-- ){
            location = ((int)((data.get(i)) / pow(base, pass)) % base);
            new_ar[count[location]-1] = data.get(i);
            count[location]--;
        }
        for (int i = 0; i < data.size(); i++){
            data.set(i,new_ar[i]); //refills data vector
        }
        pass++;
        initialize_array(new_ar, data.size());//empties arrays
        initialize_array(count, base);
    }     
}
//computes the number of digits in a given num
int number_of_digits(int num){
    int num_digits = 1;
    while (num/10 > 0){
        num /= 10; 
        num_digits++;
    }
    return num_digits;
}
//sets all positions in ar to 0 
void initialize_array(int ar[], int size){
    for (int i = 0; i < size; i++){
        ar[i] = 0;
    }
}
//sorts data using 5-3-1 shell sort algorithm 
void shellSort(IntVector &data){
    int sort = 5;
    int start; 
    int next;
    while (sort >= 1){
        for (int i = sort; i < data.size(); i++){
            start = data.get(i);
            next = i;
            while((next >= sort) and (data.get(next-sort) > start)){
                data.set(next, data.get(next-sort));
                next -= sort; 
            }
            data[next] = start;
        }
        sort-=2;
    }
}
//sorts data using bucket sort algorithm
void bucketSort(IntVector &data){
    int max = data.get(findMax(data,0));
    int *ar = new int[max+1]; //creates array as big as the biggest int
    initialize_array(ar, max+1);
    for (int i = 0; i < data.size(); i++){
        ar[data.get(i)]++;
    }
    IntVector newData;    
    for (int i = 0; i < max+1; i++){
        if (ar[i] > 0){
            newData.add(i);
        }
    }    
    data = newData;
    delete [] ar; 
}







 

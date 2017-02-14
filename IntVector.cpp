
// IntVector.cpp - Implmentation of IntVector Class
// Comp 15 - HW 5
// Conor Jenkinson
// 				   Implementation of dynamic integer arrays 	
#include <stdio.h>      
#include <stdlib.h>  
#include <iostream>
#include "IntVector.h"
using namespace std;

IntVector::IntVector(){
	array_cap = 20;
	array_size = 0;
	dynamic_array = new int[array_cap];

} 
IntVector::IntVector(int initialSize){
	array_cap = initialSize;
	array_size = 0;
	dynamic_array = new int[array_cap];
}
IntVector::IntVector(const IntVector &source){
	array_size = source.size();
	array_cap = source.capacity();
	dynamic_array = new int[array_cap];
	for (int i = 0 ; i < array_size; i++){
		dynamic_array[i] = source.dynamic_array[i];
	}

}
IntVector& IntVector::operator=(const IntVector &rhs){
	if (this != &rhs){
		delete [] dynamic_array;
		array_cap = rhs.array_cap;
		array_size = rhs.array_size;
		dynamic_array = new int[array_cap];
		for (int i = 0 ; i < array_size; i++){
			dynamic_array[i] = rhs.dynamic_array[i];
		}
	}
	return *this; 
}
IntVector::~IntVector(){
	destroy(); 
}

void IntVector::destroy(){
	array_size = 0;
	array_cap = 0;
	delete[] dynamic_array;
}
int IntVector::get(int index) const {
	if ((index > array_size-1) or (index < 0)){
		cout << "Error: Index out of range" << index << array_size<< endl ;
		abort();
	}
	return dynamic_array[index];
}
void IntVector::set(int index, int newVal){
	if ((index > array_cap-1) or (index < 0)){
		cout << index << "set Error: Index out of range" << endl ;
		abort();
	}
	dynamic_array[index] = newVal;
}
int& IntVector::operator[](int index){
	if ((index > array_size-1) or (index < 0)){
		cout << "Error: Index out of range" << endl ;
		abort();
	}
	return dynamic_array[index];
}
void  IntVector::add(int newVal){
	if (array_size == array_cap){
		expand();
	}
	dynamic_array[array_size] = newVal;
	array_size++;
}
int IntVector::size() const{
	return array_size;
}
int IntVector::capacity() const{
	return array_cap;
}
void IntVector::expand(){
	int new_cap = array_cap *2 + 1;
	int *new_array = new int[new_cap];
	for (int i=0; i < array_cap; i++)
		new_array[i] = dynamic_array[i];
	delete[] dynamic_array;
	dynamic_array = new_array;
	array_cap *=2;
}















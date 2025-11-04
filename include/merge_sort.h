#pragma once
#include <vector>
#include "movie.h"
using namespace std;

void mergeSort(vector<Movie>& movies,int start, int end, int fieldChoice);
void mergeSortRecursive(vector<Movie>& movies, int start, int end, int fieldChoice);
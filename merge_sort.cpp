#include "movie.h"
#include <vector>
using namespace std;

void mergeSort(vector<Movie>& movies, int start, int middle, int end, int fieldChoice) {
    // counts each side
    int leftCount = middle - start + 1;
    int rightCount = end - middle;

    // vector for each half of the movies
    vector<Movie> leftMovies(leftCount);
    vector<Movie> rightMovies(rightCount);

    // copies each half to respective vector
    for (int i = 0; i < leftCount; i++) {
        leftMovies[i] = movies[start + i];
    }
    for (int i = 0; i < rightCount; i++) {
        rightMovies[i] = movies[middle + 1 + i];
    }

    // i is the index for the left half,
    // j is the index for the right half,
    // and k is the index for the movies vector
    int i = 0;
    int j = 0;
    int k = start;

    // this is where the real merging begins
    // also does different comparisons based on user option input
    while (i < leftCount && j < rightCount) {
        bool condition = false;

        if (fieldChoice == 1) {
            condition = leftMovies[i].rating > rightMovies[j].rating;
        } else if (fieldChoice == 2) {
            condition = leftMovies[i].length > rightMovies[j].length;
        } else if (fieldChoice == 3) {
            condition = leftMovies[i].year > rightMovies[j].year;
        }

        if (condition) {
            movies[k] = leftMovies[i];
            i++;
        } else {
            movies[k] = rightMovies[j];
            j++;
        }
        k++;
    }

    // copies the rest of the movies
    while (i < leftCount) {
        movies[k] = leftMovies[i];
        i++;
        k++;
    }
    while (j < rightCount) {
        movies[k] = rightMovies[j];
        j++;
        k++;
    }
}

// splits the movies until they are each one element, sorts them, merges them, again and again, you get the point.
void mergeSortRecursive(vector<Movie>& movies, int start, int end, int fieldChoice) {
    if (start < end) {
        int middle = start + (end - start) / 2;
        mergeSortRecursive(movies, start, middle, fieldChoice);
        mergeSortRecursive(movies, middle + 1, end, fieldChoice);
        mergeSort(movies, start, middle, end, fieldChoice);
    }
}
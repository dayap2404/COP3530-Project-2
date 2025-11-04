#include "movie.h"
#include <algorithm>
using namespace std;

//comparison function used in heap sort
bool compareMovies(const Movie& a, const Movie& b, int fieldChoice) {
    if (fieldChoice == 1)
        return a.rating < b.rating;
    else if (fieldChoice == 2)
        return a.length < b.length;
    else if (fieldChoice == 3)
        return a.year < b.year;
    return false;
}

//the heapify of all time
void heapify(vector<Movie>& movies, int n, int i, int fieldChoice) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //check the left child of the node
    if (left < n && compareMovies(movies[largest], movies[left], fieldChoice))
        largest = left;

    //check the right child of the node
    if (right < n && compareMovies(movies[largest], movies[right], fieldChoice))
        largest = right;

    //swap and heapify recursively
    if (largest != i) {
        swap(movies[i], movies[largest]);
        heapify(movies, n, largest, fieldChoice);
    }
}

//it's heap sortin' time
void heapSort(vector<Movie>& movies, int fieldChoice) {
    int n = movies.size();

    //building a max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(movies, n, i, fieldChoice);

    //extraction of elements from heap
    for (int i = n - 1; i >= 0; i--) {
        swap(movies[0], movies[i]);
        heapify(movies, i, 0, fieldChoice);
    }

    //reverse is descending order due to max heap
    reverse(movies.begin(), movies.end());
}
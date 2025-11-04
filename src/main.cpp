#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>   // for placeholder sort
#include "movie.h"
#include "merge_sort.h"
#include "heap_sort.h"
using namespace std;


int main() {
    cout << "=============================" << endl;
    cout << "   🎬 MOVIE RANKS   " << endl;
    cout << "=============================" << endl;

    // load dataset
    string filename = "data/imdb-dataset.csv";
    vector<Movie> movies = loadMovies(filename);

    if (movies.empty()) {
        cerr << "Error: No movies loaded." << endl;
        return 1;
    }

    // display menu
    int fieldChoice, algoChoice;
    displayMenu();
    cout << "\nEnter field to sort by: ";
    cin >> fieldChoice;
    cout << "Enter sorting algorithm (1 = Merge, 2 = Heap): ";
    cin >> algoChoice;

    cout << "\nSorting in progress...\n";

    // timer start
    auto start = chrono::high_resolution_clock::now();

    // replace later with mergeSort() or heapSort() - just for testing rn
    if (algoChoice == 1) { // Merge Sort
        cout << "\nUsing Merge Sort...\n";
        mergeSortRecursive(movies, 0, movies.size() - 1, fieldChoice);
    }
    else if (algoChoice == 2) { // Heap Sort
        cout << "\nUsing Heap Sort...\n";
        heapSort(movies, fieldChoice);
    }
    else {
        cerr << "Invalid algorithm choice." << endl;
        return 1;
    }

    // end timer
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end - start).count();

    cout << "\nSorting complete!" << endl;
    cout << "Runtime: " << duration << " seconds\n" << endl;

    // display the result
    displayTopMovies(movies);

    cout << "\nProgram complete. Goodbye!\n";
    return 0;
}

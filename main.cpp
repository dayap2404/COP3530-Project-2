#include "movie.h"
#include <iostream>
#include <chrono>
using namespace std;

// Forward declarations for sorting functions
void mergeSortRecursive(vector<Movie>& movies, int start, int end, int fieldChoice);
void heapSort(vector<Movie>& movies, int fieldChoice);

int main() {
    cout << "=============================" << endl;
    cout << "   🎬 MOVIE RANKS   " << endl;
    cout << "=============================" << endl;

    // Load dataset
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

    // Timer start
    auto start = chrono::high_resolution_clock::now();

    if (algoChoice == 1) { // sort with merge
        mergeSortRecursive(movies, 0, movies.size() - 1, fieldChoice);
    }
    else if (algoChoice == 2) { // sort with heap
        heapSort(movies, fieldChoice);
    }
    else {
        cerr << "Invalid field choice." << endl;
        return 1;
    }

    // end timer
    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end - start).count();

    cout << "\n✅ Sorting complete!" << endl;
    cout << "⏱️  Runtime: " << duration << " seconds\n" << endl;

    // display the result
    displayTopMovies(movies, 10);

    cout << "\nProgram complete. Goodbye!\n";
    return 0;
}

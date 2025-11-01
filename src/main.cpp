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

    // replace later with mergeSort() or heapSort() - just for testing rn
    if (fieldChoice == 1) { // sort by rating
        sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
            return a.rating > b.rating;
        });
    }
    else if (fieldChoice == 2) { // sort by length
        sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
            return a.length > b.length;
        });
    }
    else if (fieldChoice == 3) { // sort by release year
        sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
            return a.year > b.year;
        });
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
    displayTopMovies(movies);

    cout << "\nProgram complete. Goodbye!\n";
    return 0;
}

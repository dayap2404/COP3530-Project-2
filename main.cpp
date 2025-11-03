#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
using namespace std;

struct Movie {
        string title;
        float rating;
        int year;
        int length;
};

//load the movies from the file
vector<Movie> loadMovies(const string& filename) {
    vector<Movie> movies;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return movies;
    }

    string line;
    getline(file, line); // skip the header row

    while (getline(file, line)) {
        stringstream ss(line);
        string title, ratingStr, reviewStr, genreStr;
        string yearStr, lengthStr;

        getline(ss, title, ',');
        getline(ss, ratingStr, ',');
        getline(ss, yearStr, ',');
        getline(ss, lengthStr, ',');

        // handle spaces and quotation marks
        title.erase(remove(title.begin(), title.end(), '\"'), title.end());

        // for numebrs
        if (ratingStr.empty() || yearStr.empty() || lengthStr.empty())
            continue;

        try {
            Movie m;
            m.title = title;
            m.rating = stof(ratingStr);
            m.year = stoi(yearStr);
            m.length = stoi(lengthStr);
            movies.push_back(m);
        }
        catch (...) {
            continue;
        }
    }

    file.close();
    cout << "Loaded " << movies.size() << " movies successfully.\n";
    return movies;
}

// print the meny
void displayMenu() {
    cout << "\nSort movies by:\n";
    cout << "1. Rating\n";
    cout << "2. Length\n";
    cout << "3. Release Year\n";
}

// show top movies
void displayTopMovies(const vector<Movie>& movies, int n) {
    cout << "\nTop " << n << " Movies:\n";
    cout << "--------------------------------------------\n";

    for (int i = 0; i < n && i < (int)movies.size(); ++i) {
        cout << i + 1 << ". " << movies[i].title
             << " (" << movies[i].year << ")  ⭐ "
             << movies[i].rating << " | " << movies[i].length << " mins\n";
    }
}

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
    if (algoChoice == 1) { // sort with merge
        mergeSortRecursive(movies, 0, movies.size() - 1, fieldChoice);
    }
    else if (algoChoice == 2) { // sort with heap
        cout << "INSERT HEAP SORT HERE" << endl;
        // PUT YOUR MERGE SORT FUNCTION HERE
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
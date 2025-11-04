#include "movie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

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

// print the menu
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

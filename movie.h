#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
using namespace std;

struct Movie {
    string title;
    float rating;
    int year;
    int length;
};

// all the functions we will need for menu n such
vector<Movie> loadMovies(const string& filename);
void displayMenu();
void displayTopMovies(const vector<Movie>& movies, int n);

#endif
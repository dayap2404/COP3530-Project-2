#pragma once
#include <string>
#include <vector>
using namespace std;

struct Movie {
    string title;
    float rating;
    int year;
    int length;
};

//class function to load the movies from the data file
vector<Movie> loadMovies(const string& fileName);

//this is for main but so it displays the menu
void displayMenu();

//display the top 10
void displayTopMovies(const vector<Movie>& movies, int n =10);

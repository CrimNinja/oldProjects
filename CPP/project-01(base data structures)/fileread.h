// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#ifndef FILEREAD_H
#define FILEREAD_H

#include <vector>
#include <string>
#include <map>

using namespace std;

/*---------------------------------------------------------------------------*/
struct product {
    string name;
    double price;
};

/*---------------------------------------------------------------------------*/
map <string, map <string, vector <product>>> read(const string& filename);
    // read the file and store the parsed data in a suitable datastructure

#endif // FILEREAD_H

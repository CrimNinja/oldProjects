// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#ifndef SPLITTER_H
#define SPLITTER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Splitter {
public:
    /*--------------------------------------------------------------------------------*/
    Splitter();             // initialize with the default values
    int counter() const;    // get the number of fields in the string to split
    bool has_empty() const; // check for empty fields. has to be split first
    void reset();           // reset the split string vector

    void split();           // split the string set as set to split with the seperator
                            // and store it as a vector of strings. ignores empty
                            // fields but keeps track of occurances of empty fields

    /*--------------------------------------------------------------------------------*/
    void set_seperator(const char& seperator);       // set the seperator
    void set_string_to_split(const string& line);    // set the string to split

    vector <string> fields() const;                  // get the split string.
                                                     // string has to be split first
private:
    string _string_to_split;
    vector<string> _split_string;
    char _seperator;
    int _word_counter;
    bool _empty;
};

#endif // SPLITTER_H

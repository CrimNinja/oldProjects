// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#include "splitter.h"
#include <string>
#include <vector>

using namespace std;

/*--------------------------------------------------------------------------*/
Splitter::Splitter () {
    // initialize with the default values
    _string_to_split = "";
    _seperator = ';';
    _word_counter = 0;
    _empty = false;
}

/*--------------------------------------------------------------------------*/
void Splitter::reset() {
    // reset the split string vector
    _split_string.clear();
}

/*--------------------------------------------------------------------------*/
bool Splitter::has_empty() const {
    // check for empty fields. has to be split first
    return _empty;
}

/*--------------------------------------------------------------------------*/
void Splitter::set_seperator(const char& seperator) {
    // set the seperator
    _seperator = seperator;
}

/*--------------------------------------------------------------------------*/
void Splitter::set_string_to_split(const string& line) {
    // set the string to split
    _string_to_split = line;
}

/*--------------------------------------------------------------------------*/
void Splitter::split() {
    // split the string set as set to split with the seperator
    // and store it as a vector of strings. ignores empty fields
    // but keeps track of occurances of empty fields
    /*----------------------------------------------------------------------*/
    size_t pos = 0;
    _word_counter = 0;
    size_t found = _string_to_split.find(_seperator, pos);
    string temp;

    /*----------------------------------------------------------------------*/
    temp = _string_to_split.substr(pos, (found - pos));
    while (found != string::npos){
        if (!temp.empty()) {
            _split_string.push_back(temp);
            _word_counter += 1;
        } else
            _empty = true;
        pos = (found + 1);
        found = _string_to_split.find(_seperator, pos);
        temp = _string_to_split.substr(pos, (found - pos));
    }
    if (!temp.empty()) {
        _split_string.push_back(temp);
        _word_counter += 1;
    }
}

/*--------------------------------------------------------------------------*/
vector <string> Splitter::fields() const {
    // get the split string. string has to be split first
    return _split_string;
}

/*--------------------------------------------------------------------------*/
int Splitter::counter() const {
    // get the number of fields in the string to split
    return _word_counter;
}

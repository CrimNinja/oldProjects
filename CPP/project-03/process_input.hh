// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#ifndef PROCESS_INPUT_HH
#define PROCESS_INPUT_HH

#include <string>

using namespace std;

    // Function to process the user input and return strings in such a way
    // that it is easier to process it.
    int process_input(const string& input,
                      string& command, int& number,
                      string& chore_description, bool& number_check);

#endif // PROCESS_INPUT_HH

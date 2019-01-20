// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#include <string>
#include <iostream>
#include <regex>

#include "process_input.hh"

using namespace std;

//  Function to process the input and return the commands in a neat fashion.

int process_input(const string& input, string& command, int& number,
                  string& chore_description, bool &number_check) {

//    Initialize the parameters to check for various error conditions.
    bool number_missing = false;
    number_check = false;
    bool extra_text_check = false;
    int command_type = -1;
    string temp;

//    Regex for checking the type of command input.
    const string ONE_ARG_COMMAND_REGEX = "(init)|(erase)";
    regex one_arg_command_reg(ONE_ARG_COMMAND_REGEX);

    const string COMMAND_REGEX = "(quit)|(print)|(next)";
    regex command_reg(COMMAND_REGEX);

//    Initialize parameters for splitting UserInput.
    size_t pos = 0;
    size_t found = input.find(' ', pos);

    temp = input.substr(pos, (found - pos));

//    Split the user input into usable strings. First string is the command, which is
//    always present, the second and third are not always present, so check if they are
//    present, if they are, split them and put them in separate strings.
    if (!temp.empty()) {
        command = temp;
        temp.clear();
    }

    if (found != string::npos) {
        pos = (found + 1);
        found = input.find(' ', pos);
        temp = input.substr(pos, (found - pos));
    } else {
        temp.clear();
    }

    if (regex_match(command, command_reg)) {
        if (!temp.empty()) {
            extra_text_check = true;
        }
    } else if (regex_match(command, one_arg_command_reg)) {
        if (temp.empty()) {
            number_missing = true;
//            check if the input number is actually a number.
        } else if (!regex_match(temp, regex("[0-9]+"))) {
            number_check = true;
        } else {
            number = stoi(temp);
        }
    } else if (command == "add") {

//        Check conditions for add function and print errors in respective cases.
        if (temp.empty()) {
            number_missing = true;
        }
        if (found != string::npos) {
            pos = (found + 1);
            chore_description = input.substr(pos);
        }

        if (chore_description.empty() and temp.empty()) {
            cout << "Error: priority level and chore description are missing." << endl;
            return -1;
        }

        if (!regex_match(temp, regex("[0-9]+"))) {
            number_check = true;
        } else {
            number = stoi(temp);
        }

        if (chore_description.empty()) {
            cout << "Error: Chore description missing." << endl;
            return -1;
        }
    } else {
//        Error condition when command not found.
        cout << "Error: Command not found." << endl;
    }

//    Print the error conditions for the respective commands. and set switch
//    variable to recognize the command in the main function.
    if (command == "quit") {
        command_type = 0;
    } else if (command == "next") {
        if (extra_text_check) {
            cout << "Error: extra text after next command." << endl;
            return -1;
        } else {
            command_type = 1;
        }
    } else if (command == "print") {
        if (extra_text_check) {
            cout << "Error: extra text after print command." << endl;
            return -1;
        } else {
            command_type = 2;
        }
    } else if (command == "init") {
        if (number_missing) {
            cout << "Error: the number of priority levels is missing."
                 << endl;
            return -1;
        } else if (number_check or number <= 0) {
            cout << "Error: the number of priority levels must"
                    " be an integer larger than 0."
                 << endl;
            return -1;
        }
        command_type = 3;
    } else if (command == "erase") {
        if (number_missing) {
            cout << "Error: the running number is missing."
                 << endl;
            return -1;
        } else if (number_check) {
            cout << "Error: it is not possible to create a priority"
                    " list with 0 or less levels."
                 << endl;
            return -1;
        } else if (number <= 0) {
            cout << "Error: the running number must"
                    " be larger than 0."
                 << endl;
            return -1;
        }
        command_type = 4;
    } else if (command == "add") {
        command_type = 5;
    }
    return command_type;
}

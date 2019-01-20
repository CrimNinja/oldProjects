// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#include <iostream>
#include <string>
#include <regex>

#include "process_input.hh"
#include "stack.hh"

using namespace std;

int main() {

    // Initialize the necessary variables for keeping tabs on the function.
    string input;
    bool initialized = false;
    int total_chores = 0;
    Stack* master_list = nullptr;   // Pointer to the start of the datastrucure.
    int counter[100000] = {0};      // Keep track of tasks in each priority level.
    int list_level = 0;

    while (true) {
        string command;
        int number = -99;
        string chore_description;
        bool number_check = false;
        cout << "chores> ";
        getline(cin, input);

        // Process the input and get the command type.
        int command_type = process_input(input, command, number,
                                         chore_description, number_check);

        switch (command_type) {
        case 0: {

            // If already initialized, deallocate all dynamic memory allocations.
            if (initialized) {
                delete [] master_list;
            }
            return 0;
        }
        case 1: {
            if (initialized) {
                // next();
                // Prints the chore that is next in turn.
                string removed_value;
                bool removed = false;
                for (int i = 0; i <= list_level; ++i) {
                    if (counter[list_level - i] > 0) {
                        if (master_list[list_level - i].pop_front(removed_value)) {
                            cout << removed_value << endl;
                            total_chores = total_chores - 1;
                            removed = true;
                            break;
                        }
                    }
                }
                if (!removed) {
                    cout << "--- no chores left ---" << endl;
                }
            } else {
                cout << "Error: List not initialized." << endl;
            }
            break;
        }
        case 2: {
            if (initialized) {
                // print();
                // prints all the chores in the right order.
                int running_number = 1;
                for (int i = 1; i <= list_level; ++i) {
                    if (!master_list[list_level - i].empty()) {
                        cout << "Priority level " << list_level - i + 1
                             << ":" << endl;
                        master_list[list_level - i].print(running_number);
                    }
                }
            } else {
                cout << "Error: List not initialized." << endl;
            }

            break;
        }
        case 3: {

            // Initialize the data structure if not already initialized, else
            // remove the existing data structure and initialize according to the
            // most recent command.
            if (!initialized) {
                list_level = number;
                master_list = new Stack[number];
                cout << "New priority list with levels 1-"
                     << number << " initialized." << endl;
                initialized = true;

            } else {
                delete [] master_list;
                list_level = number;
                total_chores = 0;
                Stack* test_list = new Stack[number];
                master_list = test_list;
                cout << "New priority list with levels 1-"
                     << number << " initialized." << endl;
                initialized = true;
            }

            break;
        }
        case 4: {
            // erase();
            // Removes the chore corresponding to the running number given.
            if (initialized) {
                if (number > total_chores) {
                    cout << "Error: there is no such chore." << endl;
                    break;
                }

                for (int i = 1; i <= list_level; ++i) {
                    if (number <= master_list[list_level - i].size()
                            and number > 0) {
                        master_list[list_level - i].erase(number, total_chores);
                        break;
                    } else {
                        number = number - master_list[list_level - i].size();
                    }
                }
            } else {
                cout << "Error: List not initialized." << endl;
            }

            break;
        }
        case 5: {
            // add();
            // Add a new chore in the respective priority list according to
            // FIFO model.
            if (initialized) {
                if (number_check) {
                    cout << "Error: priority level must be an integer between 1-"
                         << number << "." << endl;
                } else if (number > list_level) {
                    cout << "Error: priority level must be an integer between 1-"
                         << list_level << "." << endl;
                } else if (number == 0) {
                    cout << "Error: priority level must be an integer between 1-"
                         << list_level << "." << endl;
                } else {
                    master_list[number - 1].push_back(chore_description);
                    cout << "New chore added to priority level "
                         << number << "." << endl;
                    total_chores = total_chores + 1;
                    counter[number - 1] = counter[number - 1] + 1;
                }
            } else {
                cout << "Error: List not initialized." << endl;
            }

            break;
        }
        default:
            break;
        }

    }
    return 0;
}

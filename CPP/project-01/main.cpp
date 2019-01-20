// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>

#include "splitter.h"
#include "fileread.h"
#include "usercommands.h"
//#include "global.h"

using namespace std;

// define function pointers
/*--------------------------------------------------------------------------*/
typedef void (*no_arg_pfunctions)(const map <string, map <string, vector
                                  <product>>>& read_map);
typedef void (*one_arg_pfunctions)(const map <string, map <string, vector
                                   <product>>>& read_map, const string&);
typedef void (*two_arg_pfunctions)(const map <string, map <string,
                                   vector <product>>>& read_map,
                                   const string&, const string&);

/*--------------------------------------------------------------------------*/
//void command_hint(int& error_counter) {
//    // presents the user with a hint on how to use the console if the user
//    // fails a third time in a row.
//    if (error_counter > 2) {
//        cout << "\ntype 'help <command>' to know more about the <command>."
//             << endl;
//        cout << "\ntype 'list' for the list of available commands.\n";
//        error_counter = 0;
//    }
//}

/*--------------------------------------------------------------------------*/
// read the data in the file and store it in a suitable data structure
// map <string, map <string, vector <product>>> read_map = read("products.txt");

/*--------------------------------------------------------------------------*/
int main() {
    // initialize the necessary variables
    /*----------------------------------------------------------------------*/
    string input;
    vector <string> input_vector;
    Splitter ui;

//    int error_counter = 0;

    map <string, no_arg_pfunctions> no_arg_map;
    map <string, one_arg_pfunctions> one_arg_map;
    map <string, two_arg_pfunctions> two_arg_map;

    no_arg_pfunctions no_arg_pfunct;
    one_arg_pfunctions one_arg_pfunct;
    two_arg_pfunctions two_arg_pfunct;

    // add function entries in the respective dispatchers
    /*----------------------------------------------------------------------*/
    no_arg_map["quit"] = quit;
    no_arg_map["chains"] = chains;
//    no_arg_map["all"] = all;
//    no_arg_map["list"] = list;

    one_arg_map["stores"] = stores;
    one_arg_map["cheapest"] = cheapest;
//    one_arg_map["syntax"] = syntax;
//    one_arg_map["help"] = help;

    two_arg_map["selection"] = selection;

    // read the data in the file and store it in a suitable data structure
    map <string, map <string, vector <product>>> read_map = read("products.txt");

    /*----------------------------------------------------------------------*/
    while (true) {
//        cout << endl << setfill('-') << setw(60) << "-" << endl;
        cout << "product search> ";
//        cout << setfill(' ');
        getline(cin, input);

        // use splitter class to work the user input
        ui.reset();
        ui.set_string_to_split(input);
        ui.set_seperator(' ');
        ui.split();
        input_vector = ui.fields();

        /*------------------------------------------------------------------*/
        // use switch case to pass control to the respective fields
        switch (ui.counter()) {
        // if command exists and format is right, run it
        // if command exists but wrong syntax, display the syntax
        /*------------------------------------------------------------------*/
        case 0:
            cout << "Error: Not enough commands!" << endl;
//            command_hint(++error_counter);
            break;
        case 1: {
            auto i = no_arg_map.find(input_vector[0]);
            if (i != no_arg_map.end()) {
                no_arg_pfunct = no_arg_map[input_vector[0]];
                (*no_arg_pfunct)(read_map);
            } else if (check_command(input_vector[0])) {
                cout << "Error: command format wrong.\n";
//                one_arg_pfunct = one_arg_map["syntax"];
//                (*one_arg_pfunct)(input_vector[0]);
            } else {
                cout << "Error: command not found! \n";
//                command_hint(++error_counter);
            }
        }
            break;
        /*------------------------------------------------------------------*/
        case 2: {
            auto i = one_arg_map.find(input_vector[0]);
            if (i != one_arg_map.end()) {
                one_arg_pfunct = one_arg_map[input_vector[0]];
                (*one_arg_pfunct)(read_map, input_vector[1]);
            } else if (check_command(input_vector[0])) {
                cout << "Error: command format wrong.\n";
//                one_arg_pfunct = one_arg_map["syntax"];
//                (*one_arg_pfunct)(input_vector[0]);
            } else {
                cout << "Error: command not found! \n";
//                command_hint(++error_counter);
            }
        }
            break;
        /*------------------------------------------------------------------*/
        case 3: {
            auto i = two_arg_map.find(input_vector[0]);
            if (i != two_arg_map.end()) {
                two_arg_pfunct = two_arg_map[input_vector[0]];
                (*two_arg_pfunct)(read_map, input_vector[1], input_vector[2]);
            } else if (check_command(input_vector[0])) {
                cout << "Error: command format wrong.\n";
//                one_arg_pfunct = one_arg_map["syntax"];
//                (*one_arg_pfunct)(input_vector[0]);
            } else {
//                command_hint(++error_counter);
                cout << "Error: command not found! n";
            }
        }
            break;
        /*------------------------------------------------------------------*/
        default: {
            if (check_command(input_vector[0])) {
                cout << "Error: command format wrong.\n";
//                one_arg_pfunct = one_arg_map["syntax"];
//                (*one_arg_pfunct)(input_vector[0]);
            } else {
                cout << "Error: command not found! \n";
//                command_hint(++error_counter);
            }
        }
            break;
        }
    }
    return 0;
}

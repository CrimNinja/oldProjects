// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#ifndef USERCOMMANDS_H
#define USERCOMMANDS_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "fileread.h"

using namespace std;

// Functions with no arguments.
/*----------------------------------------------------------------------------------------*/
void quit(const map <string, map <string,
          vector <product>>>& read_map);    // exits the program.
void chains(const map <string, map <string,
            vector <product>>>& read_map);  // print chain store names in alphabetical order.

//void all();       // print the whole database in a presentable manner
//void list();      // prints the list of available commands.

// Functions with one argument.
/*----------------------------------------------------------------------------------------*/
void stores(const map <string, map <string, vector <product>>>& read_map,
            const string& chain);          // prints out the stores of that market chain
//void syntax(const string& command);        // prints the syntax for the command.
bool check_command(const string& command); // checks if the command exists.

void cheapest(const map <string, map <string, vector <product>>>& read_map,
              const string& product_name); // print out the cheapest product price
                                           // and the places it is available at that price

//void help(const string& command);          // shows an example of the command along with
                                           // the command syntax.
// Function with double arguments.
/*----------------------------------------------------------------------------------------*/
void selection(const map <string, map <string, vector <product>>>& read_map,
               const string& chain, const string& store); // display the products available
                                                          // in the selected store in
                                                          // alphabetical order

#endif // UI_H

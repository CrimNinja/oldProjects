// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi


#include "fileread.h"
#include "splitter.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

/*--------------------------------------------------------------------------------------*/
map <string, map<string, vector<product>>> read(const string& file_name) {

    // read the file and store the parsed data in a suitable datastructure

    // initialize necessary variables
    size_t char_check = 0;
    bool product_updated;

    string temp_string;
    product temp_struct;
    vector <product> temp_vector;
    map <string, vector <product>> temp_map;

    map <string, map<string, vector <product>>> read_map;

    ifstream file;

    vector <string> readvector;
    Splitter temp;
    string line;

    // try to open the file using try and catch not working

//    file.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit );
//        try {

//            file.open(file_name);
//        } catch (exception const& e) {
//            cout << "\nError: The input file cannot be read.";
//            exit(0);
//        }

    // open the file
    file.open(file_name);

    /*----------------------------------------------------------------------------------*/
    if (file.is_open()) {
        while (getline(file, line)) {
            readvector.push_back(line);

            // make sure the temp variables are all reset
            temp.reset();
            temp_map.clear();
            temp_struct = {};
            product_updated = false;

            temp.set_string_to_split(line);
            temp.split();
            readvector = temp.fields();

            // check the read vector to make sure that it meets the format prescribed.
            /*---------------------------------------------------------------------------*/
            size_t s = count(line.begin(), line.end(), ';');
            size_t w = line.find(' ');

            // check if the read line has exactly 3 semicolons
            if (s != 3) {
                cout << "Error: the input file can not be read";
                exit(0);
            }

            // check if the read line has any empty field
            if (temp.has_empty()) {
                cout << "Error: the input file can not be read";
                exit(0);
            }

            // check if the read line has any white space character
            if (w != string::npos) {
                cout << "Error: the input file can not be read";
                exit(0);
            }

            // check if we have an entry already and then enter the details.
            /*---------------------------------------------------------------------------*/

            // check chains and add chain entries, if there are no
            // entries then make a new entry with an empty value
            auto chain_check = read_map.find(readvector[0]);
            if (chain_check == read_map.end()) {
                read_map[readvector[0]] = temp_map;
            }

            /*---------------------------------------------------------------------------*/
            // check store in chain, if the store entry does not exist,
            // add the store entry with an empty vector as value
            auto store_check = read_map.at(readvector[0]).find(readvector[1]);
            if (store_check == read_map.at(readvector[0]).end()) {
                read_map.at(readvector[0])[readvector[1]] = temp_vector;
            }

            temp_struct.name = readvector[2];
            // check if the last field is a double
            /*---------------------------------------------------------------------------*/
            try {
                temp_struct.price = stod(readvector[3], &char_check);
                temp_string = readvector[3].substr(char_check);
                // check if the field has only floating point characters
                if (!temp_string.empty()) {
                    cout << "Error: the input file can not be read";
                    exit(0);
                }
            } catch (const invalid_argument& e) {
                // exception is thrown when the last field does not start with
                // a floating point character
                cout << "Error: the input file can not be read";
                exit(0);
            }

            /*---------------------------------------------------------------------------*/
            // add product if new, else update price
            for (auto& prod : read_map.at(readvector[0]).at(readvector[1])) {
                if (prod.name == temp_struct.name) {
                    prod.price = temp_struct.price;
                    product_updated = true;
                }
            }
            // if the product does not exist, make a new entry with the given price
            if (!product_updated)
                read_map.at(readvector[0]).at(readvector[1]).push_back(temp_struct);
        }
        file.close();
    } else {
        cout << "\nError: the input file can not be read";
        exit(0);
    }
    return read_map;
}

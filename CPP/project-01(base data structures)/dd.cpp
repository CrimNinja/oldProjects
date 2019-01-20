#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "splitter.h"
#include "fileread.h"
#include "usercommands.h"
#include "global.h"

using namespace std;

typedef void (*no_arg_pfunctions)();
typedef void (*one_arg_pfunctions)(string);
typedef void (*two_arg_pfunctions)(string, string);

map<string, map<string, vector<product>>> read_map = read("products.txt");

int main()
{
    string input;
    vector <string> input_vector;
    Splitter ui;

    map <string, no_arg_pfunctions> no_arg_map;
    map <string, one_arg_pfunctions> one_arg_map;
    map <string, two_arg_pfunctions> two_arg_map;

    no_arg_pfunctions no_arg_pfunct;
    one_arg_pfunctions one_arg_pfunct;
    two_arg_pfunctions two_arg_pfunct;

    no_arg_map["quit"] = quit;
    no_arg_map["chains"] = chains;
    no_arg_map["all"] = all;

    one_arg_map["stores"] = stores;
    one_arg_map["cheapest"] = cheapest;

    two_arg_map["selection"] = selection;

    while (true) {
        cout << "product_search> ";
        getline(cin, input);

        ui.reset();
        ui.set_string_to_split(input);
        ui.set_seperator(' ');
        ui.split();
        input_vector = ui.fields();

        switch (ui.counter()) {
        case 0:
            cout << "\n\n" << "Not enough commands!" << endl;
            break;
        case 1: {
            auto i = no_arg_map.find(input_vector[0]);
            if (i != no_arg_map.end()) {
                no_arg_pfunct = no_arg_map[input_vector[0]];
                (*no_arg_pfunct)();
            }
        }
            break;
        case 2: {
            auto i = one_arg_map.find(input_vector[0]);
            if (i != one_arg_map.end()) {
                one_arg_pfunct = one_arg_map[input_vector[0]];
                (*one_arg_pfunct)(input_vector[1]);
            }
        }
            break;
        case 3: {
            auto i = two_arg_map.find(input_vector[0]);
            if (i != two_arg_map.end()) {
                two_arg_pfunct = two_arg_map[input_vector[0]];
                (*two_arg_pfunct)(input_vector[1], input_vector[2]);
            }
        }
            break;
        default:
            cout << "\n\n" << "Command not recognized!" << endl;
            cout << "Kindly make sure there is no whitespaces between names." << endl;
            break;
        }
    }

    return 0;
}

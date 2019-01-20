// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#include "usercommands.h"

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <limits>

using namespace std;

// list of commands
/*--------------------------------------------------------------------------*/
const map <string, int> commands = { {"all", 0}, {"help", 1},
                               {"selection", 2}, {"chains", 3},
                               {"stores", 4}, {"cheapest", 5},
                               {"quit", 6}, {"list", 7} };

// Functions with no arguments.
/*--------------------------------------------------------------------------*/
//void list() {
//    // prints the list of available commands.
//    for (auto command = commands.begin();
//        command != commands.end(); ++command)
//        cout << "\t\t\t" << command->first << endl;
//    cout << "\nType help followed by the command to know how to use it."
//         << "\nExample help quit.\n";
//}

/*--------------------------------------------------------------------------*/
void quit(const map <string, map <string, vector <product>>>& read_map) {
    // exits the program.
    auto copy_map = read_map;
    exit(0);
}

/*--------------------------------------------------------------------------*/
void chains(const map <string, map <string, vector <product>>>& read_map) {
    // print chain store names in alphabetical order.
    for (auto chain = read_map.begin();
         chain != read_map.end(); ++chain)
        cout << chain->first << endl;
}

/*--------------------------------------------------------------------------*/
//void all() {
//    // print the whole database in a presentable manner
//    for (auto chain = read_map.begin();
//         chain != read_map.end(); ++chain) {
////        cout << endl << setw(60) << setfill('-')
////             << '-' << setfill(' ') << endl;
//        cout << chain->first << " ";
////        cout << setw(60) << setfill('-') << '-'
////             << setfill(' ') << endl;
//        for (auto store = chain->second.begin();
//             store != chain->second.end(); ++store) {

//            // format the header
//            /*--------------------------------------------------------------*/
////            cout << "    " << store->first << endl;
////            cout << "   " << setw(25) << setfill('-') << '-';
////            cout << '-' << setfill(' ') << endl;

//            sort(store->second.begin(), store->second.end(),
//                 [](const product& a, const product& b) -> bool {
//                    return a.name < b.name;});
//            for (auto prod : store->second) {
//                // format and print the products
//                /*----------------------------------------------------------*/
////                cout << setw(10) << ' ';
////                cout << setw(10) << left << prod.name << "\t";
////                cout << left << fixed << setprecision(2)
//                  cout << prod.price << endl;
//            }
//            cout << endl;
//        }
//    }
//}

// Functions with one argument.
/*--------------------------------------------------------------------------*/
bool check_command(const string& command) {
    // checks if the command exists.
    auto command_check = commands.find(command);
    if (command_check != commands.end())
        return true;
    else
        return false;
}

/*--------------------------------------------------------------------------*/
//void syntax(const string& command){
//    // prints the syntax for the command.
//    auto command_check = commands.find(command);
//    if (command_check != commands.end()) {
//        switch (command_check->second) {
//        case 0: cout << "\n\nSyntax: all\n\n";
//            break;
//        case 1: cout << "\n\nSyntax: help command_name, "
//                        "Example: help quit\n";
//            break;
//        case 2: cout << "\n\nSyntax: selection <chain_name> <store_name>,"
//                        " Example: selection Prisma Kaleva\n";
//            break;
//        case 3: cout << "\n\nSyntax: chains\n";
//            break;
//        case 4: cout << "\n\nSyntax: stores <chain_name>, "
//                        "Example: stores Prisma\n";
//            break;
//        case 5: cout << "\n\nSyntax: cheapest <product_name>, "
//                        "Example: stores Prisma\n";
//            break;
//        case 6: cout << "\n\nSyntax: quit\n";
//            break;
//        case 7: cout << "\n\nSyntax: list\n";
//            break;
//        }
//    }
//}

/*--------------------------------------------------------------------------*/
//void help(const string& command) {
//    // shows an example of the command along with the command syntax.
//    auto command_check = commands.find(command);
//    if (command_check != commands.end()) {
//        switch (command_check->second) {
//        case 0: cout << "\nLists every product available in each store "
//                        "of each chain." << endl
//                     << "\nSyntax: all\n\n";
//            break;
//        case 1: cout << "\nDisplay help on the selected command."
//                     << endl << "\nSyntax: help command_name, Example: help"
//                                " quit\n\n";
//            break;
//        case 2: cout << "\nLists the products available in the selected "
//                        "store in \nalphabetical order.\n\n"

//                        "Syntax: selection <chain_name> <store_name>,\n"
//                        "Example: selection Prisma Kaleva\n\n";
//            break;
//        case 3: cout << "\nLists all the known chains in alphabetical order."
//                     << endl << "\nSyntax: chains\n\n";
//            break;
//        case 4: cout << "\nLists all the stores of the particular chain in "
//                        "alphabetical\norder.\n\n"

//                        "Syntax: stores <chain_name>,\n"
//                        "Example: stores Prisma\n\n";
//            break;
//        case 5: cout << "\nDisplays the cheapest price of the selected "
//                        "product and the\nplaces where we get it at that "
//                        "print in alphabetical order.\n\n"

//                        "Syntax: cheapest <product_name>, "
//                        "Example: cheapest milk\n\n";
//            break;
//        case 6: cout << "\nQuits the program.\n\nSyntax: quit\n\n";
//            break;
//        case 7: cout << "\nLists all recognized functions in alphabetical "
//                        "order.\n\n"

//                        "Syntax: list\n\n";
//            break;
//        }
//    } else
//        cout << "The command " << command << " does not exist.\n"
//             << "\nType list to list all the commands.\n\n";

//}

/*--------------------------------------------------------------------------*/
void stores(const map <string, map <string, vector <product>>>& read_map,
            const string& chain) {
    // prints out the stores of that market chain
    auto chain_check = read_map.find(chain);
    if (chain_check != read_map.end()) {
        for (auto store = read_map.at(chain).begin();
             store != read_map.at(chain).end(); ++store) {
            cout << store->first << endl;
        }
    } else {
        cout << "Error: Market chain unavailable. \n";
    }
}

/*--------------------------------------------------------------------------*/
void cheapest(const map <string, map <string, vector <product>>>& read_map,
              const string& product_name) {
    // print out the cheapest product price
    // and the places it is available at that price
    double cheapest_price = numeric_limits <double>::infinity();
    multimap <string, string> store_list;

    /*----------------------------------------------------------------------*/
    for (auto chain = read_map.begin();
         chain != read_map.end(); ++chain) {
        for (auto store = chain->second.begin();
             store != chain->second.end(); ++store) {
            for (auto prod : store->second) {
                if (product_name == prod.name
                        && prod.price < cheapest_price) {
                    cheapest_price = prod.price;
                    store_list.clear();
                    store_list.insert(make_pair(chain->first, store->first));
                } else if (product_name == prod.name
                           && prod.price == cheapest_price)
                    store_list.insert(make_pair(chain->first, store->first));
            }
        }
    }

    // check if the product is available in any store
    if (store_list.empty()) {
        cout << "This product is not available anywhere.\n";
        return;
    }

    // format and print the cheapest price
    /*----------------------------------------------------------------------*/
//    cout << "\nThe cheapest price for " << product_name << " is ";
    cout << fixed << setprecision(2)
         << cheapest_price << endl;
//         << "\nIt is available in the following stores.\n";

//    cout << setw(60) << setfill('-') << '-' <<setfill(' ');
//    cout << endl << setw(10) << ' ';
//    cout << setw(10) << left << "chain";
//    cout << left << " " << "\t store" << endl;
//    cout << setw(60) << setfill('-') << '-' <<setfill(' ') << endl;

    /*----------------------------------------------------------------------*/
    for (auto store = store_list.begin();
         store != store_list.end(); ++store) {

        // format and print the stores
        /*------------------------------------------------------------------*/
//        cout << setw(10) << ' ';
        cout << store->first << " ";
        cout << store->second << endl;
    }
}

// Function with double arguments.
/*--------------------------------------------------------------------------*/
void selection(const map <string, map <string, vector <product>>>& read_map,
               const string& chain, const string& store) {

    // display the products available in the selected store in
    // alphabetical order
    auto chain_check = read_map.find(chain);
    if (chain_check != read_map.end()) {
        auto store_check = read_map.at(chain).find(store);
        if (store_check != read_map.at(chain).end()) {
            vector <product> products = read_map.at(chain).at(store);

            // format the header
            /*--------------------------------------------------------------*/
//            cout << "\nThe products available in " << chain
//                 << " " << store << " are." << endl;

//            cout << endl << setw(60) << setfill('-')
//                 << '-' << setfill(' ');
//            cout << endl << setw(10) << ' ';
//            cout << setw(10) << left << "product";
//            cout << left << " " << "\t price";
//            cout << endl << setw(60) << setfill('-')
//                 << '-' << setfill(' ') << endl;

            /*--------------------------------------------------------------*/
            sort(products.begin(), products.end(),
                 [](const product& a, const product& b) -> bool {
                    return a.name < b.name;});
            for (auto prod : products) {

                // format and print the products
                /*----------------------------------------------------------*/
//                cout << setw(10) << ' ';
                cout << prod.name << " ";
                cout << fixed << setprecision(2) <<  prod.price << endl;
            }
        } else cout << "Error: store not found.\n";
    } else cout << "Error: chain not found.\n";
}
/*--------------------------------------------------------------------------*/








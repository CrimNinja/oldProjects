// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#include <iostream>
#include <string>

#include "stack.hh"

using namespace std;

// Constructor
Stack::Stack() {

    //    Initialize the first and last pointers along with the stack size.
    first_ptr = nullptr;
    last_ptr = nullptr;
    list_size = 0;
}

// Destructor
Stack::~Stack() {

    //    Traverse the whole list and remove the elements one by one.
    while (first_ptr != nullptr) {
        Cell *temp = first_ptr;
        first_ptr = temp->next_ptr;
        list_size = 0;
        delete temp;
    }
}

//    Returns true if the list is empty.
bool Stack::empty() const {

    return first_ptr == nullptr;
}

//    Returns the size of the stack.
int Stack::size() const {

    return list_size;
}

//    Erases the element at the desired position and updates the total chores.
void Stack::erase(const int& remove_number, int& total_chores) {

    Cell *temp = first_ptr;

    //    Condition to remove the first element.
    if (remove_number == 1) {
        first_ptr = first_ptr->next_ptr;
        list_size = list_size - 1;
        total_chores = total_chores - 1;
        delete temp;
        return;
    }

    Cell* temp2 = first_ptr->next_ptr;
    int i = 2;
    while (temp2 != nullptr) {
        //    Condition to remove the last element.
        if (temp2 == last_ptr) {
            last_ptr = temp;
            temp->next_ptr = nullptr;
            list_size = list_size - 1;
            total_chores = total_chores - 1;
            delete temp2;
            return;
        }
        //    Condition to remove any element in between.
        if (i == remove_number) {
            temp->next_ptr = temp2->next_ptr;
            list_size = list_size - 1;
            total_chores = total_chores - 1;
            delete temp2;
            return;
        }
        temp = temp->next_ptr;
        temp2 = temp2->next_ptr;
        ++i;
    }
}

//    Removes the first element on the stack.
bool Stack::pop_front(string &removed_value) {

    Cell *temp = first_ptr;
    if (temp != nullptr) {
        removed_value = temp->chore_description;
        //        Update first and last values according to the number of elements in the stack.
        if (first_ptr == last_ptr) {
            first_ptr = nullptr;
            last_ptr = nullptr;
        } else {
            first_ptr = temp->next_ptr;
        }
        list_size = list_size - 1;
        delete temp;
    } else {
        return false;
    }

    return true;
}

//  Add an element to the end of the stack.
void Stack::push_back(const string& new_value) {

    Cell *element = new Cell;
    element->chore_description = new_value;
    element->next_ptr = nullptr;
    list_size = list_size + 1;
    //        Update first and last values according to the number of elements in the stack.
    if (last_ptr == nullptr) {
        last_ptr = element;
        first_ptr = element;
    } else {
        last_ptr->next_ptr = element;
        last_ptr = element;
    }
}

//    Print the elements in the list in FIFO order.
void Stack::print(int &running_number) const {

    Cell *temp = first_ptr;
    for ( ; temp; temp = temp->next_ptr) {
        cout << "  " << running_number << ". "
             << temp->chore_description << endl;
        running_number = running_number + 1;
    }
}

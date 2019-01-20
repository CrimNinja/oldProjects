// Siva Sankar Kannan - 267605 - siva.kannan@student.tut.fi

#ifndef STACK_HH
#define STACK_HH

#include <string>

using namespace std;

class Stack {
      public:
        Stack();
        ~Stack();

        // empty will only return true, if there are no elements
        // in the stack i.e. the linked  list is empty.
        bool empty() const;

        // push_back will insert the new_value on bottom of the stack
        // i.e. in tail end of the linked list.
        void push_back(const string &new_value);


        // pop_front will remove the topmost value from the stack
        // i.e. the first element of the linked list.  The removed
        // value will be stored into removed_value and the return
        // value will be true if the removal of an element is successfull.
        // If not (i.e. the stack is empty), return value is false.
        bool pop_front(string& removed_value);

        // Print the elements stored in the stack on top to bottom
        // order.  This method is mainly for testing purposes.
        void print(int& running_number) const;

        // Removes the element from the stack that has to be removed.
        // Also updates the total chores for the main function.
        void erase(const int& remove_number, int &total_chores);

        // Returns the size of the linked list.
        int size() const;

      private:
        struct Cell {
            string chore_description;
            Cell* next_ptr;
        };

        Cell* first_ptr;
        Cell* last_ptr;
        int list_size;
    };

#endif // STACK_HH

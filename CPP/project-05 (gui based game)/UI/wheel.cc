#include "wheel.hh"

#include <cstdlib>
#include <ctime>


wheel::wheel() {
    currentValue = 1;
    srand(time(NULL));
}

void wheel::spin() {
    currentValue = rand() % 4 + 1;
}

int wheel::getCurrentValue() {
    return currentValue;
}

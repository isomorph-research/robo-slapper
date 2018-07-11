#include "robotarm.h"

void setup() {
    int failure = 1;
    while(failure) {
        failure = init_arm();
    }
}

void loop() {
    //put robot commands here
}
#include <math.h>
#include "Effect.h"

int main() {
    
    /*
    WavFileReader source("melody");
    BitReductor destination(source, "melody2", 4);
    destination.applyEffect();
    destination.~BitReductor();
    */

    WavFileReader source1("melody");
    Amplifyer destination2(source1, "amplified", 3);
    destination2.applyEffect();

     
}

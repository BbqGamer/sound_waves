#include <math.h>
#include "Effect.h"

int main() {
    

    WavFileReader source("melody");
    BitReductor destination(source, "melody2", 4);
    destination.applyEffect();
    
}

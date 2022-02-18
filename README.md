# HX711 Amplier Library for MBED

Read HX711 load cell amplifier data.

The original repository was made for Arduino and can be found at: https://github.com/bogde/HX711.  
It was forked and adjusted for MBED in https://github.com/atoy40/mbed-hx711.

The library is compatible with MBED v6.

## Usage

Add the library to your project using mbed CLI (or directly through online IDE):

```# mbed add https://github.com/RobertoRoos/mbed-hx711 HX711```

## Example

```cpp
#include "mbed.h"
#include "HX711.h"

HX711 loadcell(D7, D6);

int main(void) {
    while(1) {
        loadcell.powerUp();
        printf("Weight = %.1f\n", loadcell.getUnits(10));
        loadcell.powerDown();

        wait(3);
    }
}
```

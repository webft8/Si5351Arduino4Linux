// (c) Rafal Rozestwinski (callsign: SO2A), https://github.com/webft8/Si5351Arduino4Linux
// Example usage, documentation: https://github.com/webft8/Si5351Arduino4Linux
// Dependencies: sudo apt-get install libi2c-dev
// Link with -li2c
// Basic build command: g++ -li2c example.cpp si5351.cpp -o ./si5351_cli

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include "si5351.h"

int main(int argc, char** argv) {
    if(argc != 4) {
        printf("Usage: %s I2C_DEVICE_NUMBER FREQUENCY_CLK0_FLOAT CALIBRATION_FACTOR_INT\n", argv[0]);
        printf("example:  $ ./si5351_cli 1 3600000.0 -100\n");
        printf("                         ^    ^        ^\n");
        printf("                        i2c   3.6MHz   calibrarion\n");
        printf("                /dev/i2c-1\n");
        printf("                         ^\n");
        exit(1);
    }
    int i2c_device_number = std::stof(argv[1]);
    float frequency = std::stof(argv[2]);
    int calibrarion = std::stoi(argv[3]);
    printf("Using i2c device number: %i\n", i2c_device_number); fflush(stdout);
    printf("Setting SI5351 calibration to %i\n", calibrarion); fflush(stdout);
    printf("Setting SI5351 CLK0 to f=%f\n", frequency); fflush(stdout);
    Si5351 si5351(i2c_device_number);
    bool i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
    if(!i2c_found) {
        printf("Device not found on I2C bus!\n");
        exit(1);
    }
    si5351.output_enable(SI5351_CLK0, 1);
    //si5351.output_enable(SI5351_CLK1, 1);
    //si5351.output_enable(SI5351_CLK2, 1);
    si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA);
    //si5351.drive_strength(SI5351_CLK1, SI5351_DRIVE_8MA);
    //si5351.drive_strength(SI5351_CLK2, SI5351_DRIVE_8MA);
    si5351.set_correction(calibrarion, SI5351_PLL_INPUT_XO);
    si5351.set_freq(frequency * SI5351_FREQ_MULT, SI5351_CLK0);
    si5351.update_status();
    printf("Done.\n"); fflush(stdout);
    return 0;
}

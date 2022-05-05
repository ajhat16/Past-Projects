#include "thermo.h"
#include <stdlib.h>
#include <stdio.h>

int set_temp_from_ports(temp_t *temp) {
    if (THERMO_SENSOR_PORT > 28800 || THERMO_SENSOR_PORT < 0 || (THERMO_STATUS_PORT & (1 << 2))) {
        temp->tenths_degrees = 0;
        temp->temp_mode = 3;
        return 1;
    }
    
    temp->tenths_degrees = THERMO_SENSOR_PORT >> 5;
    int remainder = THERMO_SENSOR_PORT & 0b11111;
    
    if (remainder > 15) {
        temp->tenths_degrees++;
    }

    temp->tenths_degrees += -450;

    if (THERMO_STATUS_PORT & (1 << 5)) {
        temp->temp_mode = 2;
    } else {
        temp->temp_mode = 1;
    }

    if (temp->temp_mode == 2) {
        temp->tenths_degrees = (temp->tenths_degrees * 90) / 50 + 320;
    }

    return 0;
}

int set_display_from_temp(temp_t temp, int *display) {
    if (temp.temp_mode == 1) {
        if (temp.tenths_degrees < -450 || temp.tenths_degrees > 450) {
            *display = 0b00000110111101111110111110000000;
            return 1;
        }
    } else if (temp.temp_mode == 2) {
        if (temp.tenths_degrees < -490 || temp.tenths_degrees > 1130) {
            *display = 0b00000110111101111110111110000000;
            return 1;
        }
    } else {
        *display = 0b00000110111101111110111110000000;
        return 1;
    }
    
    *display = 0;

    int binary_digits[] = {0b1111011, 0b1001000, 0b0111101, 0b1101101, 0b1001110, 0b1100111, 0b1110111, 0b1001001, 0b1111111, 0b1101111};
    int binary_negative = 0b0000100;
    int temp_thousands = 0;
    int temp_hundreds = 0;
    int temp_tens = 0;
    int temp_ones = 0;
    int temp_degrees = abs(temp.tenths_degrees);
    int mask = 0;

    while (temp_degrees > 10) {
        if (temp_degrees > 999) {
            temp_thousands = temp_degrees / 1000;
            temp_degrees -= (temp_thousands * 1000);
        } else if (temp_degrees > 99) {
            temp_hundreds = temp_degrees / 100;
            temp_degrees -= (temp_hundreds * 100);
        } else {
            temp_tens = temp_degrees / 10;
            temp_degrees -= (temp_tens * 10);
        }
    }
    temp_ones = temp_degrees % 10;
    
    if (temp_thousands != 0) {
        mask = binary_digits[temp_ones] | (binary_digits[temp_tens] << 7) | (binary_digits[temp_hundreds] << 14) | (binary_digits[temp_thousands] << 21);
    } else if (temp_hundreds != 0) {
        mask = binary_digits[temp_ones] | (binary_digits[temp_tens] << 7) | (binary_digits[temp_hundreds] << 14);
        if (temp.tenths_degrees < 0) {
            mask = mask | (binary_negative << 21);
        }
    } else {
        mask = binary_digits[temp_ones] | (binary_digits[temp_tens] << 7);
        if (temp.tenths_degrees < 0) {
            mask = mask | (binary_negative << 14);
        }
    }

    if (temp.temp_mode == 1) {
        mask = mask | (0b0001 << 28);
    } else {
        mask = mask | (0b0010 << 28);
    }

    *display = mask;

    return 0;
}

int thermo_update() {
    temp_t temp;
    
    int retval1 = set_temp_from_ports(&temp);
    int retval2 = set_display_from_temp(temp, &THERMO_DISPLAY_PORT);

    if (retval1 == 0 && retval2 == 0) {
        return 0;
    } else {
        return 1;
    }
}
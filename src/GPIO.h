#ifndef GPIO_H
#define GPIO_H
#include <Arduino.h>

/*Output Pins Connected to Relay Module*/
const uint8_t output[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};
// const uint8_t output[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 49, 47};

/*Input Pins Connected to PIR sensor*/
const uint8_t input[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
                         42, 43, 44, 45, 46, 47, 48, 49, 2, 3, 5, 6, 7, 8, 9, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21};

/*const uint8_t input[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, 45, 43, 41, 39, 37, 35, 33, 31, 29, 27,
                             25, 23, 12, 11, 9, 8, 7, 6, 5, 3, 2, 14, 15, 16, 17, 18, 19, 20, 21, A11,
                             A13, A12, A10, A14, A15};*/

/*Status of Input Pins*/
uint8_t input_status[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif
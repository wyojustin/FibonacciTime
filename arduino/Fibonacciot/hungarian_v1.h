#ifndef HUNGARIAN_V1_H
#define HUNGARIAN_V1_H
/*
 * ClockTHREEjr faceplate file.
 * Autogenerated from Hungarian_v1.wtf
 * 
 *      Author: 
 *     Licence: 
 * Description:
 *    
 * 
 */
static uint8_t hungarian_v1_words[] = {
     32, // # words
      0,  0,  3,       0,  0,  7,       9,  0,  3,       7,  0,  5,     // words
     12,  0,  4,       0,  1, 11,       5,  1,  6,      11,  1,  5,     // words
      0,  2,  3,       3,  2,  5,       8,  2,  5,      13,  2,  3,     // words
      0,  3,  4,       4,  3,  2,       6,  3,  3,       9,  3,  5,     // words
      0,  4,  6,       7,  4,  3,      11,  4,  3,       0,  5,  4,     // words
      5,  5,  3,       9,  5,  4,      14,  5,  2,       0,  6,  3,     // words
      4,  6,  4,       4,  6,  7,      11,  6,  5,       0,  6,  7,     // words
      7,  7,  5,       0,  0,  0,       0,  0,  0,       0,  0,  0,     // words
};

static uint8_t hungarian_v1_displays[] = {
   4, // number of bytes per state
//          tizen
//         negyed
//     HÁROMNEGYED
//           este
//           efel
//            fel
//           utan
//            del
//               
//               
//               
//               
//          nyolc
//            het
//             ot
//          neggy
//            hat
//          harum
//          KETTO
//            EGY
//               
//               
//               
//               
//            tiz
//             ot
//          lesz 
//           van 
//           mult
//           ORA 
//           tiz 
//         kikenc
//               
//               
//               
//               
//               
//               
//               
//          belul
//         percen
//          mulva
//         percel
//           perc
//               
//               
//               
//               
    0b00001000, 0b00000000, 0b00010000, 0b00000000, 
    0b00001000, 0b00000000, 0b01001000, 0b00000010, 
    0b01000000, 0b00000001, 0b01100000, 0b00000101, 
    0b01000000, 0b00000001, 0b00010000, 0b00000000, 
    0b01000000, 0b00000001, 0b01001000, 0b00000010, 
    0b00000100, 0b00000001, 0b01100000, 0b00000101, 
    0b00000100, 0b00000001, 0b00010000, 0b00000000, 
    0b00000100, 0b00000001, 0b01001000, 0b00000010, 
    0b00100000, 0b00000001, 0b01100000, 0b00000101, 
    0b00100000, 0b00000001, 0b00010000, 0b00000000, 
    0b00100000, 0b00000001, 0b01001000, 0b00000010, 
    0b00000000, 0b00000001, 0b01100100, 0b00000101, 
    0b00000000, 0b00000001, 0b00010100, 0b00000000, 
    0b00000000, 0b00000001, 0b01001100, 0b00000010, 
    0b01000000, 0b00000010, 0b01100000, 0b00000101, 
    0b01000000, 0b00000010, 0b00010000, 0b00000000, 
    0b01000000, 0b00000010, 0b01001000, 0b00000010, 
    0b00000100, 0b00000010, 0b01100000, 0b00000101, 
    0b00000100, 0b00000010, 0b00010000, 0b00000000, 
    0b00000100, 0b00000010, 0b01001000, 0b00000010, 
    0b00100000, 0b00000010, 0b01100000, 0b00000101, 
    0b00100000, 0b00000010, 0b00010000, 0b00000000, 
    0b00100000, 0b00000010, 0b01001000, 0b00000010, 
    0b00000000, 0b00000010, 0b01100100, 0b00000101, 
    0b00000000, 0b00000010, 0b00010100, 0b00000000, 
    0b00000000, 0b00000010, 0b01001100, 0b00000010, 
    0b01000000, 0b00000100, 0b01100000, 0b00000101, 
    0b01000000, 0b00000100, 0b00010000, 0b00000000, 
    0b01000000, 0b00000100, 0b01001000, 0b00000010, 
    0b00000100, 0b00000100, 0b01100000, 0b00000101, 
    0b00000100, 0b00000100, 0b00010000, 0b00000000, 
    0b00000100, 0b00000100, 0b01001000, 0b00000010, 
    0b00100000, 0b00000100, 0b01100000, 0b00000101, 
    0b00100000, 0b00000100, 0b00010000, 0b00000000, 
    0b00100000, 0b00000100, 0b01001000, 0b00000010, 
    0b00000000, 0b00000100, 0b01100100, 0b00000101, 
    0b00000000, 0b00000100, 0b00010100, 0b00000000, 
    0b00000000, 0b00000100, 0b01001100, 0b00000010, 
    0b01000000, 0b00010000, 0b01100000, 0b00000101, 
    0b01000000, 0b00010000, 0b00010000, 0b00000000, 
    0b01000000, 0b00010000, 0b01001000, 0b00000010, 
    0b00000100, 0b00010000, 0b01100000, 0b00000101, 
    0b00000100, 0b00010000, 0b00010000, 0b00000000, 
    0b00000100, 0b00010000, 0b01001000, 0b00000010, 
    0b00100000, 0b00010000, 0b01100000, 0b00000101, 
    0b00100000, 0b00010000, 0b00010000, 0b00000000, 
    0b00100000, 0b00010000, 0b01001000, 0b00000010, 
    0b00000000, 0b00010000, 0b01100100, 0b00000101, 
    0b00000000, 0b00010000, 0b00010100, 0b00000000, 
    0b00000000, 0b00010000, 0b01001100, 0b00000010, 
    0b01000000, 0b00100000, 0b01100000, 0b00000101, 
    0b01000000, 0b00100000, 0b00010000, 0b00000000, 
    0b01000000, 0b00100000, 0b01001000, 0b00000010, 
    0b00000100, 0b00100000, 0b01100000, 0b00000101, 
    0b00000100, 0b00100000, 0b00010000, 0b00000000, 
    0b00000100, 0b00100000, 0b01001000, 0b00000010, 
    0b00100000, 0b00100000, 0b01100000, 0b00000101, 
    0b00100000, 0b00100000, 0b00010000, 0b00000000, 
    0b00100000, 0b00100000, 0b01001000, 0b00000010, 
    0b00000000, 0b00100000, 0b01100100, 0b00000101, 
    0b00000000, 0b00100000, 0b00010100, 0b00000000, 
    0b00000000, 0b00100000, 0b01001100, 0b00000010, 
    0b01000000, 0b00001000, 0b01100000, 0b00000101, 
    0b01000000, 0b00001000, 0b00010000, 0b00000000, 
    0b01000000, 0b00001000, 0b01001000, 0b00000010, 
    0b00000100, 0b00001000, 0b01100000, 0b00000101, 
    0b00000100, 0b00001000, 0b00010000, 0b00000000, 
    0b00000100, 0b00001000, 0b01001000, 0b00000010, 
    0b00100000, 0b00001000, 0b01100000, 0b00000101, 
    0b00100000, 0b00001000, 0b00010000, 0b00000000, 
    0b00100000, 0b00001000, 0b01001000, 0b00000010, 
    0b00000000, 0b00001000, 0b01100100, 0b00000101, 
    0b00000000, 0b00001000, 0b00010100, 0b00000000, 
    0b00000000, 0b00001000, 0b01001100, 0b00000010, 
    0b01000000, 0b01000000, 0b01100000, 0b00000101, 
    0b01000000, 0b01000000, 0b00010000, 0b00000000, 
    0b01000000, 0b01000000, 0b01001000, 0b00000010, 
    0b00000100, 0b01000000, 0b01100000, 0b00000101, 
    0b00000100, 0b01000000, 0b00010000, 0b00000000, 
    0b00000100, 0b01000000, 0b01001000, 0b00000010, 
    0b00100000, 0b01000000, 0b01100000, 0b00000101, 
    0b00100000, 0b01000000, 0b00010000, 0b00000000, 
    0b00100000, 0b01000000, 0b01001000, 0b00000010, 
    0b00000000, 0b01000000, 0b01100100, 0b00000101, 
    0b00000000, 0b01000000, 0b00010100, 0b00000000, 
    0b00000000, 0b01000000, 0b01001100, 0b00000010, 
    0b01000000, 0b10000000, 0b01100000, 0b00000101, 
    0b01000000, 0b10000000, 0b00010000, 0b00000000, 
    0b01000000, 0b10000000, 0b01001000, 0b00000010, 
    0b00000100, 0b10000000, 0b01100000, 0b00000101, 
    0b00000100, 0b10000000, 0b00010000, 0b00000000, 
    0b00000100, 0b10000000, 0b01001000, 0b00000010, 
    0b00100000, 0b10000000, 0b01100000, 0b00000101, 
    0b00100000, 0b10000000, 0b00010000, 0b00000000, 
    0b00100000, 0b10000000, 0b01001000, 0b00000010, 
    0b00000000, 0b10000000, 0b01100100, 0b00000101, 
    0b00000000, 0b10000000, 0b00010100, 0b00000000, 
    0b00000000, 0b10000000, 0b01001100, 0b00000010, 
    0b01000000, 0b00000000, 0b01100001, 0b00000101, 
    0b01000000, 0b00000000, 0b00010001, 0b00000000, 
    0b01000000, 0b00000000, 0b01001001, 0b00000010, 
    0b00000100, 0b00000000, 0b01100001, 0b00000101, 
    0b00000100, 0b00000000, 0b00010001, 0b00000000, 
    0b00000100, 0b00000000, 0b01001001, 0b00000010, 
    0b00100000, 0b00000000, 0b01100001, 0b00000101, 
    0b00100000, 0b00000000, 0b00010001, 0b00000000, 
    0b00100000, 0b00000000, 0b01001001, 0b00000010, 
    0b00000000, 0b00000000, 0b01100101, 0b00000101, 
    0b00000000, 0b00000000, 0b00010101, 0b00000000, 
    0b00000000, 0b00000000, 0b01001101, 0b00000010, 
    0b01000000, 0b00000000, 0b01100010, 0b00000101, 
    0b01000000, 0b00000000, 0b00010010, 0b00000000, 
    0b01000000, 0b00000000, 0b01001010, 0b00000010, 
    0b00000100, 0b00000000, 0b01100010, 0b00000101, 
    0b00000100, 0b00000000, 0b00010010, 0b00000000, 
    0b00000100, 0b00000000, 0b01001010, 0b00000010, 
    0b00100000, 0b00000000, 0b01100010, 0b00000101, 
    0b00100000, 0b00000000, 0b00010010, 0b00000000, 
    0b00100000, 0b00000000, 0b01001010, 0b00000010, 
    0b00000000, 0b00000000, 0b01100110, 0b00000101, 
    0b00000000, 0b00000000, 0b00010110, 0b00000000, 
    0b00000000, 0b00000000, 0b01001110, 0b00000010, 
    0b11000000, 0b00000001, 0b01100000, 0b00000101, 
    0b11000000, 0b00000001, 0b00010000, 0b00000000, 
    0b11000000, 0b00000001, 0b01001000, 0b00000010, 
    0b10000100, 0b00000001, 0b01100000, 0b00000101, 
    0b10000100, 0b00000001, 0b00010000, 0b00000000, 
    0b10000100, 0b00000001, 0b01001000, 0b00000010, 
    0b10100000, 0b00000001, 0b01100000, 0b00000101, 
    0b10100000, 0b00000001, 0b00010000, 0b00000000, 
    0b10100000, 0b00000001, 0b01001000, 0b00000010, 
    0b10000000, 0b00000001, 0b01100100, 0b00000101, 
    0b10000000, 0b00000001, 0b00010100, 0b00000000, 
    0b10000000, 0b00000001, 0b01001100, 0b00000010, 
    0b11000000, 0b00000010, 0b01100000, 0b00000101, 
    0b11000000, 0b00000010, 0b00010000, 0b00000000, 
    0b11000000, 0b00000010, 0b01001000, 0b00000010, 
    0b10000100, 0b00000010, 0b01100000, 0b00000101, 
    0b10000100, 0b00000010, 0b00010000, 0b00000000, 
    0b10000100, 0b00000010, 0b01001000, 0b00000010, 
    0b10100000, 0b00000010, 0b01100000, 0b00000101, 
    0b10100000, 0b00000010, 0b00010000, 0b00000000, 
    0b10100000, 0b00000010, 0b01001000, 0b00000010, 
    0b00000001, 0b00000000, 0b01100000, 0b00000101, 
    0b00000001, 0b00000000, 0b00010000, 0b00000000, 
    0b00000001, 0b00000000, 0b01001000, 0b00000010, 
    0b01000010, 0b00000001, 0b01100000, 0b00000101, 
    0b01000010, 0b00000001, 0b00010000, 0b00000000, 
    0b01000010, 0b00000001, 0b01001000, 0b00000010, 
    0b00000110, 0b00000001, 0b01100000, 0b00000101, 
    0b00000110, 0b00000001, 0b00010000, 0b00000000, 
    0b00000110, 0b00000001, 0b01001000, 0b00000010, 
    0b00100010, 0b00000001, 0b01100000, 0b00000101, 
    0b00100010, 0b00000001, 0b00010000, 0b00000000, 
    0b00100010, 0b00000001, 0b01001000, 0b00000010, 
    0b00000010, 0b00000001, 0b01100100, 0b00000101, 
    0b00000010, 0b00000001, 0b00010100, 0b00000000, 
    0b00000010, 0b00000001, 0b01001100, 0b00000010, 
    0b01000010, 0b00000010, 0b01100000, 0b00000101, 
    0b01000010, 0b00000010, 0b00010000, 0b00000000, 
    0b01000010, 0b00000010, 0b01001000, 0b00000010, 
    0b00000110, 0b00000010, 0b01100000, 0b00000101, 
    0b00000110, 0b00000010, 0b00010000, 0b00000000, 
    0b00000110, 0b00000010, 0b01001000, 0b00000010, 
    0b00100010, 0b00000010, 0b01100000, 0b00000101, 
    0b00100010, 0b00000010, 0b00010000, 0b00000000, 
    0b00100010, 0b00000010, 0b01001000, 0b00000010, 
    0b00000010, 0b00000010, 0b01100100, 0b00000101, 
    0b00000010, 0b00000010, 0b00010100, 0b00000000, 
    0b00000010, 0b00000010, 0b01001100, 0b00000010, 
    0b01000010, 0b00000100, 0b01100000, 0b00000101, 
    0b01000010, 0b00000100, 0b00010000, 0b00000000, 
    0b01000010, 0b00000100, 0b01001000, 0b00000010, 
    0b00000110, 0b00000100, 0b01100000, 0b00000101, 
    0b00000110, 0b00000100, 0b00010000, 0b00000000, 
    0b00000110, 0b00000100, 0b01001000, 0b00000010, 
    0b00100010, 0b00000100, 0b01100000, 0b00000101, 
    0b00100010, 0b00000100, 0b00010000, 0b00000000, 
    0b00100010, 0b00000100, 0b01001000, 0b00000010, 
    0b00000010, 0b00000100, 0b01100100, 0b00000101, 
    0b00000010, 0b00000100, 0b00010100, 0b00000000, 
    0b00000010, 0b00000100, 0b01001100, 0b00000010, 
    0b01000010, 0b00010000, 0b01100000, 0b00000101, 
    0b01000010, 0b00010000, 0b00010000, 0b00000000, 
    0b01000010, 0b00010000, 0b01001000, 0b00000010, 
    0b00000110, 0b00010000, 0b01100000, 0b00000101, 
    0b00000110, 0b00010000, 0b00010000, 0b00000000, 
    0b00000110, 0b00010000, 0b01001000, 0b00000010, 
    0b00100010, 0b00010000, 0b01100000, 0b00000101, 
    0b00100010, 0b00010000, 0b00010000, 0b00000000, 
    0b00100010, 0b00010000, 0b01001000, 0b00000010, 
    0b00000010, 0b00010000, 0b01100100, 0b00000101, 
    0b00000010, 0b00010000, 0b00010100, 0b00000000, 
    0b00000010, 0b00010000, 0b01001100, 0b00000010, 
    0b01000010, 0b00100000, 0b01100000, 0b00000101, 
    0b01000010, 0b00100000, 0b00010000, 0b00000000, 
    0b01000010, 0b00100000, 0b01001000, 0b00000010, 
    0b00000110, 0b00100000, 0b01100000, 0b00000101, 
    0b00000110, 0b00100000, 0b00010000, 0b00000000, 
    0b00000110, 0b00100000, 0b01001000, 0b00000010, 
    0b00100010, 0b00100000, 0b01100000, 0b00000101, 
    0b00100010, 0b00100000, 0b00010000, 0b00000000, 
    0b00100010, 0b00100000, 0b01001000, 0b00000010, 
    0b00000010, 0b00100000, 0b01100100, 0b00000101, 
    0b00000010, 0b00100000, 0b00010100, 0b00000000, 
    0b00000010, 0b00100000, 0b01001100, 0b00000010, 
    0b01010000, 0b00001000, 0b01100000, 0b00000101, 
    0b01010000, 0b00001000, 0b00010000, 0b00000000, 
    0b01010000, 0b00001000, 0b01001000, 0b00000010, 
    0b00010100, 0b00001000, 0b01100000, 0b00000101, 
    0b00010100, 0b00001000, 0b00010000, 0b00000000, 
    0b00010100, 0b00001000, 0b01001000, 0b00000010, 
    0b00110000, 0b00001000, 0b01100000, 0b00000101, 
    0b00110000, 0b00001000, 0b00010000, 0b00000000, 
    0b00110000, 0b00001000, 0b01001000, 0b00000010, 
    0b00010000, 0b00001000, 0b01100100, 0b00000101, 
    0b00010000, 0b00001000, 0b00010100, 0b00000000, 
    0b00010000, 0b00001000, 0b01001100, 0b00000010, 
    0b01010000, 0b01000000, 0b01100000, 0b00000101, 
    0b01010000, 0b01000000, 0b00010000, 0b00000000, 
    0b01010000, 0b01000000, 0b01001000, 0b00000010, 
    0b00010100, 0b01000000, 0b01100000, 0b00000101, 
    0b00010100, 0b01000000, 0b00010000, 0b00000000, 
    0b00010100, 0b01000000, 0b01001000, 0b00000010, 
    0b00110000, 0b01000000, 0b01100000, 0b00000101, 
    0b00110000, 0b01000000, 0b00010000, 0b00000000, 
    0b00110000, 0b01000000, 0b01001000, 0b00000010, 
    0b00010000, 0b01000000, 0b01100100, 0b00000101, 
    0b00010000, 0b01000000, 0b00010100, 0b00000000, 
    0b00010000, 0b01000000, 0b01001100, 0b00000010, 
    0b01010000, 0b10000000, 0b01100000, 0b00000101, 
    0b01010000, 0b10000000, 0b00010000, 0b00000000, 
    0b01010000, 0b10000000, 0b01001000, 0b00000010, 
    0b00010100, 0b10000000, 0b01100000, 0b00000101, 
    0b00010100, 0b10000000, 0b00010000, 0b00000000, 
    0b00010100, 0b10000000, 0b01001000, 0b00000010, 
    0b00110000, 0b10000000, 0b01100000, 0b00000101, 
    0b00110000, 0b10000000, 0b00010000, 0b00000000, 
    0b00110000, 0b10000000, 0b01001000, 0b00000010, 
    0b00010000, 0b10000000, 0b01100100, 0b00000101, 
    0b00010000, 0b10000000, 0b00010100, 0b00000000, 
    0b00010000, 0b10000000, 0b01001100, 0b00000010, 
    0b01010000, 0b00000000, 0b01100001, 0b00000101, 
    0b01010000, 0b00000000, 0b00010001, 0b00000000, 
    0b01010000, 0b00000000, 0b01001001, 0b00000010, 
    0b00010100, 0b00000000, 0b01100001, 0b00000101, 
    0b00010100, 0b00000000, 0b00010001, 0b00000000, 
    0b00010100, 0b00000000, 0b01001001, 0b00000010, 
    0b00110000, 0b00000000, 0b01100001, 0b00000101, 
    0b00110000, 0b00000000, 0b00010001, 0b00000000, 
    0b00110000, 0b00000000, 0b01001001, 0b00000010, 
    0b00010000, 0b00000000, 0b01100101, 0b00000101, 
    0b00010000, 0b00000000, 0b00010101, 0b00000000, 
    0b00010000, 0b00000000, 0b01001101, 0b00000010, 
    0b01010000, 0b00000000, 0b01100010, 0b00000101, 
    0b01010000, 0b00000000, 0b00010010, 0b00000000, 
    0b01010000, 0b00000000, 0b01001010, 0b00000010, 
    0b00010100, 0b00000000, 0b01100010, 0b00000101, 
    0b00010100, 0b00000000, 0b00010010, 0b00000000, 
    0b00010100, 0b00000000, 0b01001010, 0b00000010, 
    0b00110000, 0b00000000, 0b01100010, 0b00000101, 
    0b00110000, 0b00000000, 0b00010010, 0b00000000, 
    0b00110000, 0b00000000, 0b01001010, 0b00000010, 
    0b00010000, 0b00000000, 0b01100110, 0b00000101, 
    0b00010000, 0b00000000, 0b00010110, 0b00000000, 
    0b00010000, 0b00000000, 0b01001110, 0b00000010, 
    0b11010000, 0b00000001, 0b01100000, 0b00000101, 
    0b11010000, 0b00000001, 0b00010000, 0b00000000, 
    0b11010000, 0b00000001, 0b01001000, 0b00000010, 
    0b10010100, 0b00000001, 0b01100000, 0b00000101, 
    0b10010100, 0b00000001, 0b00010000, 0b00000000, 
    0b10010100, 0b00000001, 0b01001000, 0b00000010, 
    0b10110000, 0b00000001, 0b01100000, 0b00000101, 
    0b10110000, 0b00000001, 0b00010000, 0b00000000, 
    0b10110000, 0b00000001, 0b01001000, 0b00000010, 
    0b10010000, 0b00000001, 0b01100100, 0b00000101, 
    0b10010000, 0b00000001, 0b00010100, 0b00000000, 
    0b10010000, 0b00000001, 0b01001100, 0b00000010, 
    0b11010000, 0b00000010, 0b01100000, 0b00000101, 
    0b11010000, 0b00000010, 0b00010000, 0b00000000, 
    0b11010000, 0b00000010, 0b01001000, 0b00000010, 
    0b10010100, 0b00000010, 0b01100000, 0b00000101, 
    0b10010100, 0b00000010, 0b00010000, 0b00000000, 
    0b10010100, 0b00000010, 0b01001000, 0b00000010, 
    0b10110000, 0b00000010, 0b01100000, 0b00000101, 
    0b10110000, 0b00000010, 0b00010000, 0b00000000, 
    0b10110000, 0b00000010, 0b01001000, 0b00000010, 
    0b00001000, 0b00000000, 0b01100000, 0b00000101, 
    };
// Minutes hack constants
static uint32_t hungarian_v1_minute_leds[] = {
  // n_minute_state, n_minute_led,        led0, led2,           led3,           led4...
                  0,            0, 
};
static uint32_t hungarian_v1_minutes_hack[] = {
};
static Faceplate hungarian_v1(hungarian_v1_words, hungarian_v1_displays, hungarian_v1_minute_leds, hungarian_v1_minutes_hack, "Hungarian_V1");
#endif

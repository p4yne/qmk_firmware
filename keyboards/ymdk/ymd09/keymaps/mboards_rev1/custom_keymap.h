/*
Copyright 2022 stoffl

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

#include "print.h"
#include <string.h>

// Custom HSV values
#define C_HSV_WINERED        0, 255,  85
#define C_HSV_DARKGOLD      36, 255,  85
#define C_HSV_DARKBLUE     170, 255,  85

// #define HSV_AZURE       132, 102, 255
// #define HSV_BLACK         0,   0,   0
// #define HSV_BLUE        170, 255, 255
// #define HSV_CHARTREUSE   64, 255, 255
// #define HSV_CORAL        11, 176, 255
// #define HSV_CYAN        128, 255, 255
// #define HSV_GOLD         36, 255, 255
// #define HSV_GOLDENROD    30, 218, 218
// #define HSV_GREEN        85, 255, 255
// #define HSV_MAGENTA     213, 255, 255
// #define HSV_ORANGE       28, 255, 255
// #define HSV_PINK        234, 128, 255
// #define HSV_PURPLE      191, 255, 255
// #define HSV_RED           0, 255, 255
// #define HSV_SPRINGGREEN 106, 255, 255
// #define HSV_TEAL        128, 255, 128
// #define HSV_TURQUOISE   123,  90, 112
// #define HSV_WHITE         0,   0, 255
// #define HSV_YELLOW       43, 255, 255
// #define HSV_OFF         HSV_BLACK


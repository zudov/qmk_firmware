/*
Copyright 2015 Jack Humbert <jack.humb@gmail.com>

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

#include "keymap_common.h"
#include <math.h>

#define UNICODE_OSX /* Mac with Unicode Hex Input */

uint16_t hextokeycode(int hex) {
    if (hex == 0x0) {
        return KC_0;
    } else if (hex < 0xA) {
        return KC_1 + (hex - 0x1);
    } else {
        return KC_A + (hex - 0xA);
    }
}

void action_custom(keyrecord_t *record, uint32_t code)
{
    // For more info on how this works per OS, see here: https://en.wikipedia.org/wiki/Unicode_input#Hexadecimal_code_input

    if (record->event.pressed) {
        #ifdef UNICODE_OSX
            register_code(KC_LALT);
        #endif

        uint32_t unicode = code;
        bool leading_zero = false;
        for(int i = 6; i >= 0; i--) {
            uint8_t digit = ((unicode >> (int)(i*4)) & 0xF);
            if (digit > 0 || leading_zero || (i < 4)) {
                leading_zero = true;
                register_code(hextokeycode(digit));
                unregister_code(hextokeycode(digit));
                if (i == 4) {
                    register_code(KC_LSFT);
                    register_code(KC_EQL);
                    unregister_code(KC_EQL);
                    unregister_code(KC_LSFT);
                }
            }
        }

        #ifdef UNICODE_OSX
            unregister_code(KC_LALT);
        #endif
    }
    return;
}
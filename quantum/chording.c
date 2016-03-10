/*
Copyright 2016 Jack Humbert <jack.humb@gmail.com>

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

#include "chording.h"

bool chording = false;
uint8_t chord_keys_count = 0;
uint8_t chord_keys[8];

const uint16_t PROGMEM chords[] = {

};

void action_custom(keyrecord_t *record, uint32_t code)
{
    if (record->event.pressed) {

    } else {
    	if (chording) {
    		// FIRE
    		chording = false;
    	} else {
    		register_code(code);
    		unregister_code(code);
    	}
    }
}

bool chord_keys(uint8_t kc0, uint8_t kc1) {
	if ()
}
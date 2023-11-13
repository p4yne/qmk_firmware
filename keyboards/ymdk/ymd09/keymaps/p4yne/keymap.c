/*
Copyright 2022 p4yne

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
#include "custom_keymap.h"
#include "sendstring_german.h"

// Defines names for use in layer keycodes and the keymap
enum  layers {
  _LVL0_,
  _LVL1_,
  _LVL2_,
  _LVL3_,
  _LVL4_,
  _LVL5_,
  _LVL6_,
  _LVL7_
};

const uint8_t PROGMEM ledmap[][3] = {
  [_LVL0_] = {C_HSV_WINERED},
  [_LVL1_] = {HSV_RED},
  [_LVL2_] = {C_HSV_DARKGOLD},
  [_LVL3_] = {HSV_GOLD},
  [_LVL4_] = {C_HSV_DARKBLUE},
  [_LVL5_] = {HSV_BLUE},
  [_LVL6_] = {HSV_MAGENTA},
  [_LVL7_] = {HSV_PURPLE}
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_LVL0_] = LAYOUT(KC_7, KC_8, LT(_LVL1_, KC_9),
                    KC_4, KC_5, KC_6,
                    KC_1, KC_2, KC_3),
                    
  [_LVL1_] = LAYOUT(TO(_LVL6_), TO(_LVL7_), KC_TRNS,
                    TO(_LVL4_), TO(_LVL5_), KC_VOLU,
                    TO(_LVL2_), TO(_LVL3_), KC_VOLD),

  [_LVL2_] = LAYOUT(LCAG(KC_B), LCAG(KC_L), MO(_LVL3_),
                    LCAG(KC_Z), LCAG(KC_C), KC_MUTE,
                    LCAG(KC_S), LCAG(KC_V), LCAG(KC_M)),
                    
//  [_LVL2_] = LAYOUT(LCAG(KC_B), LCAG(KC_L), MO(_LVL3_),
//                    LCAG(KC_Z), LCAG(KC_C), KC_MUTE,
//                    LCAG(KC_S), LCAG(KC_V), S(KC_MUTE)),

  [_LVL3_] = LAYOUT(MEH(KC_B), MEH(KC_L), KC_TRNS,
                    MEH(KC_Z), MEH(KC_C), KC_MEH,
                    MEH(KC_S), MEH(KC_V), TO(_LVL0_)),

  [_LVL4_] = LAYOUT(KC_TRNS, KC_TRNS, TO(_LVL0_),
                    KC_TRNS, KC_TRNS, KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_TRNS),
                   
  [_LVL5_] = LAYOUT(KC_TRNS, KC_TRNS, TO(_LVL0_),
                    KC_TRNS, KC_TRNS, KC_TRNS,
                    KC_TRNS, KC_TRNS, KC_TRNS),

  [_LVL6_] = LAYOUT(KC_ACL0, KC_ACL1, TO(_LVL0_),
                    KC_BTN1, KC_MS_U, KC_BTN2,
                    KC_MS_L, KC_MS_D, KC_MS_R),

  [_LVL7_] = LAYOUT(RESET, RGB_TOG, TO(_LVL0_),
                    RGB_HUI, RGB_SAI, RGB_MOD,
                    RGB_HUD, RGB_SAD, RGB_RMOD),

};


void keyboard_post_init_user(void) {
  // Call the post init code.
#ifdef CONSOLE_ENABLE
  debug_enable=true;
  debug_matrix=true;
#endif
  rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
  rgb_matrix_enable();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  // useful for getting matrix right
  uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    switch (keycode) {
        case HYPR(KC_O): {
            if (record->event.pressed) {
                SEND_STRING("Qmk is awesome!\n");
            }
            return false;
        }
        case RGB_TOG: {
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        rgb_matrix_set_color_all(RGB_BLACK);
                    }
                    break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(RGB_BLACK);
                    }
                    break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                    }
                    break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    }
                    break;
                }
            }
            return false;        
        }       
        default: 
            return true;
    }
};


void set_led_color_by_hsv(int ledkey, uint8_t h_in, uint8_t s_in, uint8_t v_in){
    HSV hsv = { .h = h_in, .s = s_in, .v = v_in};
    RGB rgb = hsv_to_rgb(hsv);
    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    rgb_matrix_set_color(ledkey, f * rgb.r, f * rgb.g, f * rgb.b);
}

void set_led_color_by_layer(int layer, int ledkey){
    set_led_color_by_hsv(ledkey, pgm_read_byte(&ledmap[layer][0]),
                              pgm_read_byte(&ledmap[layer][1]),
                              pgm_read_byte(&ledmap[layer][2]));    
}

void set_layer_color(int layer) {
  int ledkey=0;
  for (int i=0; i<MATRIX_COLS*MATRIX_ROWS;i++) {
    uint8_t row = i/MATRIX_COLS;
    uint8_t col = (2-(i-(MATRIX_COLS*row)));
    uint16_t key=pgm_read_word(&keymaps[layer][row][col]);   
    // continue if this is not a valid key
    if (key==KC_NO) { continue; }
    // clear key if it is only a transition
    if (key == KC_TRNS) {
      if (rgb_matrix_get_flags() != LED_FLAG_ALL){
        // for layers that are "above" others like the function layer _LVL1_
        // or layer _LVL5_ let the lower layer light shine through on the 
        // transparent keys, else blank them.
        if ((layer == _LVL1_) || (layer == _LVL3_) || (layer == _LVL5_)) {
          set_led_color_by_hsv(ledkey, pgm_read_byte(&ledmap[layer-1][0]),
                            pgm_read_byte(&ledmap[layer-1][1]),
                            pgm_read_byte(&ledmap[layer-1][2]));
        } else {
          set_led_color_by_hsv(ledkey, HSV_BLACK);
        }
      }
    } else {
      // this key does something - light it up in layer specific color
      //if ((layer != _LVL0_) || (rgb_matrix_get_flags() != LED_FLAG_ALL)){
      if (rgb_matrix_get_flags() != LED_FLAG_ALL) {
        set_led_color_by_hsv(ledkey, pgm_read_byte(&ledmap[layer][0]),
                          pgm_read_byte(&ledmap[layer][1]),
                          pgm_read_byte(&ledmap[layer][2]));
      }
    }

    if (layer == _LVL2_) {
        if (key==KC_MUTE) {
            set_led_color_by_hsv(ledkey, C_HSV_WINERED);
        }
        if (key==LCAG(KC_M)) {
            set_led_color_by_hsv(ledkey, HSV_RED);
        }
        if (key==LCAG(KC_B)) {
            set_led_color_by_hsv(ledkey, HSV_BLACK);
        }
        if (key==LCAG(KC_L)) {
            set_led_color_by_hsv(ledkey, HSV_BLUE);
        }
//        if (key==LCAG(KC_Z)) {
//            set_led_color_by_hsv(ledkey, HSV_RED);
//        }
        if (key==LCAG(KC_C)) {
            set_led_color_by_hsv(ledkey, HSV_MAGENTA);
        }
//        if (key==LCAG(KC_S)) {
//            set_led_color_by_hsv(ledkey, HSV_RED);
//        }
        if (key==LCAG(KC_V)) {
            set_led_color_by_hsv(ledkey, HSV_AZURE);
        }
        if (key==LCAG(KC_B)) {
            set_led_color_by_hsv(ledkey, HSV_RED);
        }                                                        
    }
    if (layer == _LVL3_) {
        if((key==TO(_LVL0_))) {
            set_led_color_by_hsv(ledkey, HSV_GREEN);
        }
    }
    // color testing layer
    /* 
    if (layer == _LVL4_) {
        switch (i) {
          case 0: {
                set_led_color_by_hsv(ledkey, HSV_AZURE);
              }
              break;
          case 1: {
                set_led_color_by_hsv(ledkey, HSV_BLUE);
              }
              break;
          case 2: {
                set_led_color_by_hsv(ledkey, HSV_CHARTREUSE);
              }
              break;
          case 3: {
                set_led_color_by_hsv(ledkey, HSV_CORAL);
              }
              break;
          case 4: {
                set_led_color_by_hsv(ledkey, HSV_CYAN);
              }
              break;
          case 5: {
                set_led_color_by_hsv(ledkey, HSV_GOLD);
              }
              break;
          case 6: {
                set_led_color_by_hsv(ledkey, HSV_GOLDENROD);
              }
              break;
          case 7: {
                set_led_color_by_hsv(ledkey, HSV_MAGENTA);
              }
              break;
          case 8: {
                set_led_color_by_hsv(ledkey, HSV_ORANGE);
              }
              break;
          default: {
              }
              break;
        }
    } 
    */
    if (layer == _LVL7_) {
        if((key==RESET)) {
            set_led_color_by_hsv(ledkey, HSV_RED);
        }
        if((key==TO(_LVL0_))) {
            set_led_color_by_hsv(ledkey, HSV_GREEN);
        }
    }
    
    ledkey++;
  }
/*
    if (layer == _LVL0_) {  
        for (uint8_t i = 0; i < DRIVER_LED_TOTAL; ++i) {
            if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
                set_led_color_by_layer(layer, i);
            }
        }
    }
    if (layer == _LVL1_) {
        for (uint8_t i = 0; i < DRIVER_LED_TOTAL; ++i) {
            switch (i) {
              case 0: {
                    set_led_color_by_hsv(i, HSV_AZURE);
                  }
                  break;
              case 1: {
                    set_led_color_by_hsv(i, HSV_BLUE);
                  }
                  break;
              case 2: {
                    set_led_color_by_hsv(i, HSV_CHARTREUSE);
                  }
                  break;
              case 3: {
                    set_led_color_by_hsv(i, HSV_CORAL);
                  }
                  break;
              case 4: {
                    set_led_color_by_hsv(i, HSV_CYAN);
                  }
                  break;
              case 5: {
                    set_led_color_by_hsv(i, HSV_GOLD);
                  }
                  break;
              case 6: {
                    set_led_color_by_hsv(i, HSV_GOLDENROD);
                  }
                  break;
              case 7: {
                    set_led_color_by_hsv(i, HSV_MAGENTA);
                  }
                  break;
              case 8: {
                    set_led_color_by_hsv(i, HSV_ORANGE);
                  }
                  break;
              default: {
                  }
                  break;
            }
        }    
    } 
*/   
  return;
}

void rgb_matrix_indicators_user(void) {
  set_layer_color(get_highest_layer(layer_state));

}

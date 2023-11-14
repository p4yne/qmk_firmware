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
  _LVL7_,
  _LVL8_,
  _LVL9_
};

const uint8_t PROGMEM ledmap[][3] = {
  [_LVL0_] = {C_HSV_WINERED},
  [_LVL1_] = {HSV_AZURE},
  [_LVL2_] = {HSV_BLUE},
  [_LVL3_] = {HSV_CHARTREUSE},
  [_LVL4_] = {HSV_CORAL},
  [_LVL5_] = {HSV_CYAN},
  [_LVL6_] = {HSV_GOLD},
  [_LVL7_] = {HSV_GOLDENROD},
  [_LVL8_] = {HSV_MAGENTA},
  [_LVL9_] = {HSV_ORANGE}
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_LVL0_] = LAYOUT(TO(_LVL3_), TO(_LVL2_), TO(_LVL1_),
                    TO(_LVL6_), TO(_LVL5_), TO(_LVL4_),
                    TO(_LVL9_), TO(_LVL8_), TO(_LVL7_)),
                    
  [_LVL1_] = LAYOUT(TO(_LVL3_), TO(_LVL2_), TO(_LVL0_),
                    TO(_LVL6_), TO(_LVL5_), TO(_LVL4_),
                    TO(_LVL9_), TO(_LVL8_), TO(_LVL7_)),
                    
  [_LVL2_] = LAYOUT(TO(_LVL3_), TO(_LVL0_), TO(_LVL1_),
                    TO(_LVL6_), TO(_LVL5_), TO(_LVL4_),
                    TO(_LVL9_), TO(_LVL8_), TO(_LVL7_)),

  [_LVL3_] = LAYOUT(TO(_LVL0_), TO(_LVL2_), TO(_LVL1_),
                    TO(_LVL6_), TO(_LVL5_), TO(_LVL4_),
                    TO(_LVL9_), TO(_LVL8_), TO(_LVL7_)),

  [_LVL4_] = LAYOUT(TO(_LVL3_), TO(_LVL2_), TO(_LVL1_),
                    TO(_LVL6_), TO(_LVL5_), TO(_LVL0_),
                    TO(_LVL9_), TO(_LVL8_), TO(_LVL7_)),

  [_LVL5_] = LAYOUT(TO(_LVL3_), TO(_LVL2_), TO(_LVL1_),
                    TO(_LVL6_), TO(_LVL0_), TO(_LVL4_),
                    TO(_LVL9_), TO(_LVL8_), TO(_LVL7_)),
                   
  [_LVL6_] = LAYOUT(TO(_LVL3_), TO(_LVL2_), TO(_LVL1_),
                    TO(_LVL0_), TO(_LVL5_), TO(_LVL4_),
                    TO(_LVL9_), TO(_LVL8_), TO(_LVL7_)),

  [_LVL7_] = LAYOUT(TO(_LVL3_), TO(_LVL2_), TO(_LVL1_),
                    TO(_LVL6_), TO(_LVL5_), TO(_LVL4_),
                    TO(_LVL9_), TO(_LVL8_), TO(_LVL0_)),

  [_LVL8_] = LAYOUT(TO(_LVL3_), TO(_LVL2_), TO(_LVL1_),
                    TO(_LVL6_), TO(_LVL5_), TO(_LVL4_),
                    TO(_LVL9_), TO(_LVL0_), TO(_LVL7_)),

  [_LVL9_] = LAYOUT(TO(_LVL3_), TO(_LVL2_), TO(_LVL1_),
                    TO(_LVL6_), TO(_LVL5_), TO(_LVL4_),
                    TO(_LVL0_), TO(_LVL8_), TO(_LVL7_))
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




void set_layer_color(int layer) {
  for (int i=0; i<MATRIX_COLS*MATRIX_ROWS;i++) {
    uint8_t row = i/MATRIX_COLS;
    uint8_t col = (2-(i-(MATRIX_COLS*row)));
    uint16_t key=pgm_read_word(&keymaps[layer][row][col]);   
    // continue if this is not a valid key
    if (key==KC_NO) { continue; }
    // clear key if it is only a transition
    if (key == KC_TRNS) {
      /*if (rgb_matrix_get_flags() != LED_FLAG_ALL){
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
      }*/
    } else {
      // this key does something - light it up in layer specific color
      //if ((layer != _LVL0_) || (rgb_matrix_get_flags() != LED_FLAG_ALL)){
      if (rgb_matrix_get_flags() != LED_FLAG_ALL) {
        set_led_color_by_hsv(i, pgm_read_byte(&ledmap[layer][0]),
                          pgm_read_byte(&ledmap[layer][1]),
                          pgm_read_byte(&ledmap[layer][2]));
      }
    }
  }    
/*
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
    */
    // color testing layer
     
   /* if (layer == _LVL0_) {
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
    } */
 /*   
    if (layer == _LVL7_) {
        if((key==RESET)) {
            set_led_color_by_hsv(ledkey, HSV_RED);
        }
        if((key==TO(_LVL0_))) {
            set_led_color_by_hsv(ledkey, HSV_GREEN);
        }
    }
 */   

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

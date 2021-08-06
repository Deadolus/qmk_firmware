/* Copyright 2019 ashlar 2021 peepeetee, deadolus
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap.h"

// // Defines names for use in layer keycodes and the keymap
enum  layers {
  _BL,
  _RED_,
  _GREEN_,
  _BLUE_,
  _CYAN_,
  _MAGENTA_,
  _YELLOW_
};

void dance_blue_finished(qk_tap_dance_state_t *state, void *user_data) {
  if(get_mods()) return;
  if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
        register_code16(KC_CAPS);
        unregister_code16(KC_CAPS);
        return;
        }
        layer_on(_BLUE_);
    } else {
      if(state->count == 2) {
        //if (state->interrupted) {
        layer_on(_BLUE_);
      //} else if (state->pressed) return TD_DOUBLE_HOLD;
      }
    }
}

void dance_green_finished(qk_tap_dance_state_t *state, void *user_data) {
  if(get_mods()) return; //return if some modifier pressed
  if (state->count == 1) {
    if (!state->interrupted && !state->pressed) {
      tap_code(KC_ESC);
      return;
    }
    layer_on(_GREEN_);
  } else {
      layer_on(_GREEN_);
  }
}

void dance_cln_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1 ) {
    layer_off(_GREEN_);
    layer_off(_BLUE_);
    layer_off(_RED_);
  }
}

//send ] when short pressed AND no other key pressed, else turn on red layer
void dance_red_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
        if (!state->interrupted && !state->pressed) {
        register_code16(KC_RALT);
        tap_code(KC_RBRC);
        unregister_code16(KC_RALT);
        return;
        }
        layer_on(_RED_);
    }
}

void dance_shift_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
        if (!state->interrupted && !state->pressed) {
          //send (
        register_code16(KC_LSFT);
        tap_code(KC_8);
        unregister_code16(KC_LSFT);
        return;
        }
        if(state->pressed) {
        register_code16(KC_LSFT);
        return;
        }
        return;
    }
  for(int i=0;i<state->count; i++) {
        register_code16(KC_LSFT);
        unregister_code16(KC_LSFT);
  }
}

void dance_shift_reset(qk_tap_dance_state_t *state, void *user_data) {
  unregister_code16(KC_LSFT);
}


#ifdef TAP_DANCE_ENABLE
enum {
  TD_HOME_END,
  TD_WHEEL_UP,
  TD_WHEEL_DOWN,
  TD_ESC_GREEN,
  TD_CAPS_BLUE,
  TD_BRK_RED,
  TD_LEFT_SHIFT
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //tap once for home, twice for end
  [TD_HOME_END] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
  [TD_WHEEL_UP] = ACTION_TAP_DANCE_DOUBLE(KC_MS_WH_UP,KC_PGUP),
  [TD_WHEEL_DOWN] = ACTION_TAP_DANCE_DOUBLE(KC_MS_WH_DOWN,KC_PGDOWN),
  [TD_ESC_GREEN] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, dance_green_finished, dance_cln_reset, 140),
  [TD_CAPS_BLUE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_blue_finished, dance_cln_reset),
  [TD_BRK_RED] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_red_finished, dance_cln_reset),
  [TD_LEFT_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_shift_finished, dance_shift_reset)
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
   * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │   │
   * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
   * │    │   │   │   │   │   │   │   │   │   │   │   │      │   │   │
   * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │    │    │    │                        │   │   │   │   │   │   │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */
#ifdef TAP_DANCE_ENABLE
  /* 0: ISO qwerty */
  [_BL] = LAYOUT_65_iso_blocker(
      TD(TD_CAPS_BLUE), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,              KC_DEL,
      KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                       TD(TD_HOME_END),
      TD(TD_ESC_GREEN), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, LT(_YELLOW_, KC_ENT), TD(TD_WHEEL_UP),
      TD(TD_LEFT_SHIFT),KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP,                TD(TD_WHEEL_DOWN),
      KC_LCPO, KC_LGUI, KC_LAPO,                            KC_SPC,                             KC_RAPC, TD(TD_BRK_RED),   KC_LEFT, KC_DOWN,              KC_RGHT

      ),
#else
  [_BL] = LAYOUT_65_iso_blocker(
      KC_CAPS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC, KC_RBRC,          KC_HOME,
      KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP,
      KC_LSPO, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH, KC_RSPC, KC_UP,   KC_PGDN,
      KC_LCTL, KC_LGUI, KC_LAPO,                   KC_SPC,                             KC_RAPC, MO(_RED_),          KC_LEFT, KC_DOWN, KC_RGHT

      ),
#endif

  [_RED_] = LAYOUT_65_iso_blocker(
      KC_GRV,  KC_F1,       KC_F2,      KC_F3,      KC_F4,         KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  TG(_YELLOW_), LGUI(KC_PAUSE),
      _______, _______,     _______,    _______,    _______,       _______,      _______, _______, _______, _______, _______, _______, _______,          LGUI(KC_DEL),
      _______, TO(_GREEN_), TO(_BLUE_), TO(_CYAN_), TO(_MAGENTA_), TO(_YELLOW_), _______, _______, _______, _______, _______, _______, _______, TO(0),   LGUI(KC_END),
      _______, _______,     _______,    _______,    _______,       _______,      _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
      RESET,   _______,     _______,                               KC_LEAD,                                 _______, _______,          KC_MPLY, KC_VOLD, KC_MUTE
      ),
  [_GREEN_] = LAYOUT_65_iso_blocker(
      KC_ASTG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,_______ , _______, _______, _______, TD(TD_WHEEL_DOWN), TD(TD_WHEEL_UP),  KC_PSCR, _______, _______, _______,  _______,
      _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, KC_MS_L, KC_MS_D, KC_MS_U,  KC_MS_R, KC_BTN1, KC_BTN2, _______, TO(0), LCTL(KC_PGUP),
      _______, _______, _______, _______, _______, _______, _______, _______,           KC_BTN3, KC_HOME, KC_END,  _______, _______, _______, LCTL(KC_PGDOWN),
      _______, _______, KC_BTN3,                   _______,                            _______, _______,          _______, _______, _______
      ),
  [_BLUE_] = LAYOUT_65_iso_blocker(
      _______, DM_PLY1, DM_PLY2, _______, _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______, _______, _______, _______, _______,
      _______, DM_REC1, DM_REC2, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______, _______,          _______,
      _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______, _______,  TO(0),  _______,
      _______, _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______, _______, _______,
      _______, _______, _______,                   KC_0,                               KC_PCMM, _______,          _______, _______, _______
      ),
  [_CYAN_] = LAYOUT_65_iso_blocker(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(0),   _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
      ),
  [_MAGENTA_] = LAYOUT_65_iso_blocker(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(0),   _______,
      _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
      ),
  [_YELLOW_] = LAYOUT_65_iso_blocker( //F-Keys layer, use red-minus to toggle on/off, used to have sticky Fkeys
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
      ),

  /*template
    [_UL] = LAYOUT_65_iso_blocker(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(0),   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______
    )
    */
};

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

const uint8_t PROGMEM ledmap[][3] = {
  [_BL] = _______,
  [_RED_] = RED,
  [_GREEN_] = GREEN,
  [_BLUE_] = BLUE,
  [_CYAN_] = CYAN,
  [_MAGENTA_] = MAGENTA,
  [_YELLOW_] = YELLOW
};

#undef _______
#define _______ KC_TRNS
#endif



void keyboard_post_init_user(void) {
  // Call the post init code.
#ifdef CONSOLE_ENABLE
  debug_enable=true;
  debug_matrix=true;
#endif
  rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
  autoshift_disable();
}

layer_state_t layer_state_set_user(layer_state_t state) {
//make sure we can enter numbers when entering blue layer -> numlock on
  if(IS_LAYER_ON_STATE(state, _BLUE_)) {
    led_t ledState = host_keyboard_led_state();
    if (!ledState.num_lock) {
      tap_code(KC_NUMLOCK);
    }
  }
  return state;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  //useful for getting matrix right
  uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

  switch (keycode) {
    case RGB_TOG:
      if (record->event.pressed) {
        switch (rgb_matrix_get_flags()) {
          case LED_FLAG_ALL: {
                               rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                               rgb_matrix_set_color_all(0, 0, 0);
                             }
                             break;
          case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                                                                               rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                                                                               rgb_matrix_set_color_all(0, 0, 0);
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
    default:
      return true; // Process all other keycodes normally
  }
}

void setEscKey(void) {
  if (get_autoshift_state()) {
    rgb_matrix_set_color(0, 0x00, 0xFF, 0x00);

  } else {
    if((rgb_matrix_get_flags() != LED_FLAG_ALL)) {
      rgb_matrix_set_color(0, 0x0, 0x0, 0x0);
    }
  }
}


void setCapsLock(void) {
  led_t host_leds = host_keyboard_led_state();
  if (host_leds.caps_lock) {
    rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);

  } else {
    //if capslock is not pressed don't clear it, it might be used for displaying led pattern
    if((rgb_matrix_get_flags() != LED_FLAG_ALL)) {
      rgb_matrix_set_color(30, 0x0, 0x0, 0x0);
    }
  }
}

void lightUpKey(int key, int layer) {
  //this key does something - light it up
  HSV hsv = {
    .h = pgm_read_byte(&ledmap[layer][0]),
    .s = pgm_read_byte(&ledmap[layer][1]),
    .v = pgm_read_byte(&ledmap[layer][2]),
  };

  RGB rgb = hsv_to_rgb(hsv);
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  if( (layer != 0) || (rgb_matrix_get_flags() != LED_FLAG_ALL))
    rgb_matrix_set_color(key, f * rgb.r, f * rgb.g, f * rgb.b);
}

void set_layer_color(int layer) {
  int ledkey=0;
  for(int i=0; i<MATRIX_COLS*MATRIX_ROWS;i++) {
    uint8_t row = i/MATRIX_COLS;
    uint8_t col=(i-(i/MATRIX_COLS)*MATRIX_COLS);
    uint16_t key=pgm_read_word(&keymaps[layer][row][col]);
    //continue if this is not a valid key
    if(key==KC_NO) { continue; }
    //clear key if it is only a transition
    int keyLayer=layer;
    while((key == KC_TRNS) && (keyLayer > 0)) {
      --keyLayer;
      if(!IS_LAYER_ON_STATE(layer_state, keyLayer)) continue;
      key=pgm_read_word(&keymaps[keyLayer][row][col]);
    }
    if ((key == KC_TRNS)) {
      /* if(layer>0) { */
      /*   set_layer_color(layer-1); */
      /* } else { */
      if(rgb_matrix_get_flags() != LED_FLAG_ALL){
        rgb_matrix_set_color(ledkey, 0, 0, 0);
        /* } */
    }
    } else {
      //this key does something - light it up
      lightUpKey(ledkey, keyLayer);
    }
    //if we are on layer 0 set capslock to correct status
    if(keyLayer==0 && i==30) { setCapsLock(); }
    if(keyLayer==0 && i==0) { setEscKey(); }
    ledkey++;
  }
  return;
}

void rgb_matrix_indicators_user(void) {
  if(IS_LAYER_ON_STATE(layer_state, 1)) {
    set_layer_color(1);
  }
  set_layer_color(get_highest_layer(layer_state));

}

#ifdef LEADER_ENABLE
LEADER_EXTERNS();

//SEND_STRING seems to be local dependent.
//For swiss-german layout I have to send "ctrl+." to get ":"
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_F) {
      // Anything you can do in a macro.
      SEND_STRING("QMK is awesome.");
    }
    SEQ_ONE_KEY(KC_V) {
      register_code(KC_LCTL);
      register_code(KC_LALT);
      SEND_STRING("x");
      unregister_code(KC_LCTL);
      unregister_code(KC_LALT);
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_S) {
      SEND_STRING("https");
      register_code(KC_LSFT);
      SEND_STRING(".77");
      unregister_code(KC_LSFT);
      SEND_STRING("start.duckduckgo.com\n");
    }
  }
}
#endif

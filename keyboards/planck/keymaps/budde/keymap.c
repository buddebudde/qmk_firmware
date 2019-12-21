/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  EXT_PLV
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define KC_SWLBRC LALT(KC_LBRC)
#define KC_SWQUOT LALT(KC_QUOT)
#define KC_SWSCLN LALT(KC_SCLN)
#define KC_MYCAPS MT(MOD_LCTL, KC_ESC)
#define KC_MYLOWER LT(LOWER, KC_DEL)
#define KC_MYRAISE LT(RAISE, KC_ENT)
#define KC_MYSFT MT(MOD_LSFT, KC_BSPC)
#define KC_MYZERO MT(MOD_RCTL, KC_0)
#define SE_SLASH S(KC_7)
#define SE_AT RALT(KC_2)
#define SE_AMPR S(KC_6)
#define SE_LPRN S(KC_8)
#define SE_RPRN S(KC_9)
#define SE_DQUO S(KC_2)
#define SE_DLR RALT(KC_4)
#define SE_LCBR RALT(KC_7)
#define SE_RCBR RALT(KC_0)
#define SE_LBRC RALT(KC_8)
#define SE_RBRC RALT(KC_9)
#define SE_EQAL S(KC_0)
#define SE_GBP RALT(KC_3)
#define SE_TILD RALT(KC_RBRC)
#define SE_EURO RALT(KC_E)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.   ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+-------   |------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   |   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |   |   N  |   M  |   ,  |   .  |   -  | Enter|
 * |------+------+------+------+------+------+   |------+------+------+------+------+------|
 * | Shift| Shift| Shift| LAlt | Raise| Shift|   | Space|Ent/lw| GUI | Shift| Shift| Shift|
 * `-----------------------------------------'   `-----------------------------------------'
 *  alt acts as enter when tapped
 *  middle shift acts as backspace when tapped
 *  , . / becomes < > ? when shift is pressed, as usual
 */

[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,        KC_Y,      KC_U,    KC_I,    KC_O,     KC_P, KC_LBRC, \
      KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,      KC_G,        KC_H,      KC_J,    KC_K,    KC_L,  KC_SCLN,  KC_QUOT, \
     KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,        KC_N,      KC_M, KC_COMM,  KC_DOT,  KC_SLSH,  KC_ENT, \
      KC_RSFT, KC_RSFT, KC_RSFT, KC_LALT,   KC_MYLOWER,  KC_MYSFT,      KC_SPC,  KC_MYRAISE, KC_LGUI, KC_RSFT,   KC_DOWN,   KC_UP \
),



/* Lower
 * ,-----------------------------------------.   ,-----------------------------------------.
 * |      |      |      |      |      |      |   | home | pgdn | pgup | end  |      |      |
 * |------+------+------+------+------+-------   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |   | left | down |  up  | down |      |      |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |PlayP | Vol- | Vol+ | Mute |      |      |
 * |------+------+------+------+------+------+   |------+------+------+------+------+------|
 * |      |      |      |      |      |      |   |      |      |      |      |      |      |
 * `-----------------------------------------'   `-----------------------------------------'
 */

[_RAISE] = LAYOUT_planck_grid( 
    _______, _______, _______, _______, _______, _______,    	     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_WH_U, _______, \
    BL_TOGG, BL_BRTG, _______, _______, _______, _______,    		 KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_WH_D, KC_VOLU, \
    BL_INC, BL_DEC, BL_STEP, _______, _______, _______, 			 KC_MPRV, KC_MUTE, KC_MPLY, KC_MNXT, _______, KC_VOLD, \
    _______, _______, _______, _______, _______, _______, 			 _______,  _______, _______, _______, _______, _______ \
),

/* Raise
 * ,-----------------------------------------.   ,-----------------------------------------.
 * |   €  |   !  |   @  |   {  |   }  |   ´  |   |   %  |   7  |   8  |   9  |   +  |   ?  |
 * |------+------+------+------+------+-------   |------+------+------+------+------+------|
 * |   $  |   '  |   "  |   (  |   )  |   `  |   |   >  |   4  |   5  |   6  |   *  |   =  |
 * |------+------+------+------+------+------|   |------+------+------+------+------+------|
 * |   £  |   #  |   ^  |   [  |   ]  |   &  |   |   <  |   1  |   2  |   3  |   /  |   \  |
 * |------+------+------+------+------+------+   |------+------+------+------+------+------|
 * | RESET| Game |      |   §  |      | Del  |   |   ½  |   ~  |   0  |      |      |      |
 * `-----------------------------------------'   `-----------------------------------------'
 */

[_LOWER] = LAYOUT_planck_grid( \
    SE_EURO,  KC_EXLM, SE_AT,  SE_LCBR, SE_RCBR, KC_EQL,  KC_PERC,    KC_7,    KC_8,     KC_9, KC_MINS,  S(KC_MINS), \
    SE_DLR,   KC_BSLS, SE_DQUO, SE_LPRN, SE_RPRN, KC_PLUS, S(KC_NUBS), KC_4,    KC_5,     KC_6, KC_PIPE,  SE_EQAL, \
    SE_GBP,  KC_HASH, KC_RCBR, SE_LBRC, SE_RBRC, SE_AMPR, KC_NUBS,    KC_1,    KC_2,     KC_3, SE_SLASH, RALT(KC_MINS), \
    RESET,  _______, _______,KC_GRAVE, _______, RALT(KC_NUBS),  KC_TILD,   SE_TILD, KC_0, _______, _______, _______  \
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______,  _______,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;

    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;



void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

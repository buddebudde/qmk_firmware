#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif 

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _GAME 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  GAME,
  SMILEY,
  SADSMILEY
};

enum macro_keycodes {
  KC_SAMPLEMACRO,// I believe this is the macro that allows me to just but "Q" in the keymap instead of KC_Q, but I'm not 100% sure :)
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

#define KC_CTRL LM(3, MOD_LCTL) // shifts to layer 3 (adjust) so that the LEDs can fire up on that layer
#define KC_MYLOWER LT(_LOWER, KC_DEL)
#define KC_MYRAISE LT(_RAISE, KC_ENT)
#define KC_MYSFT MT(MOD_LSFT, KC_BSPC)
#define KC_SE_SLSH S(KC_7)
#define KC_SE_AT RALT(KC_2)
#define KC_SE_AMPR S(KC_6)
#define KC_SE_LPRN S(KC_8)
#define KC_SE_RPRN S(KC_9)
#define KC_SE_QUO KC_BSLS
#define KC_SE_DQUO S(KC_2)
#define KC_SE_DLR RALT(KC_4)
#define KC_SE_LCBR RALT(KC_7)
#define KC_SE_RCBR RALT(KC_0)
#define KC_SE_LBRC RALT(KC_8)
#define KC_SE_RBRC RALT(KC_9)
#define KC_SE_EQAL S(KC_0)
#define KC_SE_GBP RALT(KC_3)
#define KC_SE_TILD RALT(KC_RBRC)
#define KC_SE_EURO RALT(KC_E)
#define KC_SE_AA KC_LBRC
#define KC_SE_OE KC_SCLN
#define KC_SE_AE KC_QUOT
#define KC_SE_PLAYP KC_MEDIA_PLAY_PAUSE
#define KC_SE_MUTE KC_AUDIO_MUTE
#define KC_SE_CIRC KC_RCBR
#define KC_SE_PARA KC_GRAVE
#define KC_SE_HALF KC_TILD
#define KC_SE_ACUT KC_EQL
#define KC_SE_GRAV KC_PLUS
#define KC_SE_MORE S(KC_NUBS)
#define KC_SE_LESS KC_NUBS
#define KC_SE_PLUS KC_MINS
#define KC_SE_ASTR KC_PIPE
#define KC_SE_QUES S(KC_MINS)
#define KC_SE_BSLH RALT(KC_MINS)
#define KC_SE_PIPE RALT(KC_NUBS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  Back|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   :(  |    |   :)  |------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LAlt | Del/  |/ Back/ /       \space \  |enter/ |RShift| RGUI |
 *                   |      |      | lower | shift /         \      \ | raise |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,      KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,      KC_U,    KC_I,    KC_O,    KC_P,     KC_SE_AA, \
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,      KC_J,    KC_K,    KC_L,    KC_SE_OE, KC_SE_AE, \
  KC_LCTRL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   SADSMILEY,          SMILEY,  KC_N,      KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                     KC_LALT,  KC_LALT,  KC_MYLOWER,   KC_MYSFT,           KC_SPC,    KC_MYRAISE,  KC_RSFT,  KC_RGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   €  |   !  |  @   |   {  |   }  |   ´  |                    |  %   |  7   |   8  |   9  |   *  |   ?  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   $  |   '  |   "  |   (  |   )  |   `  |-------.    ,-------|   >  |   4  |   5  |   6  |   +  |   =  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |   £  |   #  |   ^  |   [  |   ]  |   &  |-------|    |-------|   <  |   1  |   2  |   3  |   /  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |   ½  |  §   |LOWER | /  |    /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
         _______, _______,    _______,      _______,    _______,    _______,                               _______, _______, _______, _______,    _______,    _______, \
      KC_SE_EURO, KC_EXLM,   KC_SE_AT,   KC_SE_LCBR, KC_SE_RCBR, KC_SE_ACUT,                               KC_PERC,    KC_7,    KC_8,    KC_9, KC_SE_ASTR, KC_SE_QUES,\
      KC_SE_DLR,  KC_SE_QUO, KC_SE_DQUO, KC_SE_LPRN, KC_SE_RPRN, KC_SE_GRAV,                            KC_SE_MORE,    KC_4,    KC_5,    KC_6, KC_SE_PLUS, KC_SE_EQAL,\
      KC_SE_GBP,  KC_HASH,   KC_SE_CIRC, KC_SE_LBRC, KC_SE_RBRC, KC_SE_AMPR, KC_LBRC,          KC_RBRC, KC_SE_LESS,    KC_1,    KC_2,    KC_3, KC_SE_SLSH, KC_SE_BSLH,\
                                         KC_SE_HALF, KC_SE_PARA, KC_TRNS, KC_SE_PIPE,          KC_TRNS, KC_SE_TILD,    KC_0,    KC_0\
                                  //`-------------------------------------------'  `-----------------------'
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | RESET|      |      |      |      |      |                    |      |      |      |      |      | RESET|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  Home| PgDn | PgUp | End  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  |  F12 |-------.    ,-------| Left | Down |  Up  |Right |ScrlUp| VolUp|       
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------| Prev | Mute | Play | Next |ScrlDn| VolDn|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      | GAME |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  KC_RST,  _______, _______, _______, _______, _______,                           _______,    _______,      _______, _______, _______,  KC_RST, \
  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                            KC_HOME,    KC_PGDN,      KC_PGUP, KC_END,  _______, _______, \
  KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,                           KC_LEFT,    KC_DOWN,        KC_UP, KC_RGHT, KC_WH_U, KC_VOLU, \
  _______, _______, _______,  _______, _______, _______, _______,        _______, KC_MPRV, KC_SE_MUTE,  KC_SE_PLAYP, KC_MNXT, KC_WH_D, KC_VOLD, \
                              _______, _______, _______, _______,        _______, _______,    _______,    TO(_GAME)\
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,\
                             _______, _______, _______, _______, _______,  _______, _______, _______  \
  ),

 [_GAME] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SE_AA, \
  KC_CAPS,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SE_OE, KC_SE_AE, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_F5,  KC_SE_RPRN,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                      KC_CTRL, KC_LALT, KC_RALT,  KC_SPC,  KC_SPC,  KC_MYRAISE,   KC_RSFT,   TO(_QWERTY) \
),
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case GAME:
        if (record->event.pressed) {
          layer_on(_GAME);
        } else {
          layer_off(_GAME);
        }
        return false;
        break;
	case SMILEY:
        if (record->event.pressed) {
          SEND_STRING(SS_LSFT(".")SS_LSFT("9"));
       }  
	   return false;
       break;
   case SADSMILEY:
        if (record->event.pressed) {
          SEND_STRING(SS_LSFT(".")SS_LSFT("8"));
       }  
	   return false;
       break;
    }
  return true;
}

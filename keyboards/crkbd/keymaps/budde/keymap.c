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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  KC_JANZON // tribute to /u/johananasen aka Janzon
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
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  SE_AA,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SE_OE, SE_AE,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       CTRL,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LALT, MYLOWER, MYSFT,   SPC, MYRAISE, LALT \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------------.                  ,-----------------------------------------------.
    SE_EURO,    EXLM,  SE_AT,SE_LCBR,SE_RCBR,SE_ACUT,                      PERC,   7   ,   8   ,   9   ,SE_ASTR,SE_QUES,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
    SE_DLR,  SE_QUO,SE_DQUO,SE_LPRN,SE_RPRN,SE_GRAV,                   SE_MORE,   4   ,   5   ,   6   ,SE_PLUS,SE_EQAL,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
    SE_GBP,    HASH,SE_CIRC,SE_LBRC,SE_RBRC,SE_AMPR,                   SE_LESS,   1   ,   2   ,   3   ,SE_SLSH,SE_BSLH,\
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
                                    SE_PARA,  TRNS, SE_PIPE,   SE_HALF,SE_TILD,   0   \
                                  //`-----------------------'  `-----------------------'
  ),
	
  [_RAISE] = LAYOUT_kc( \
 //,-----------------------------------------.                ,-----------------------------------------.
      RST  , LRST , _____, _____, _____,JANZON,                   HOME,  PGDN,  PGUP,  END,   INS,  PSCR,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LTOG , LHUI , LSAI , LVAI , LMOD , _____,                   LEFT,  DOWN,   UP , RIGHT, WH_U , VOLU,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     _____ , LHUD , LSAD , LVAD , _____, _____,                   MPRV,  MUTE,  MPLY,  MNXT, WH_D, VOLD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                LALT, TRNS,    MYSFT,     SPC,   TRNS, LALT \
                              //`--------------------'  `--------------------'
  ),
 [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        _____,  _____, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  _____,  _____,  _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  _____,  _____,  _____, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____,   _____,      _____, _____, _____ \
                              //`--------------------'  `--------------------'
  )
};


uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _LOWER:
        if(isLeftHand) {

          rgblight_setrgb_at(148, 0, 211, 13); // sets LED number 13 (lower) to purple on left hand

        } else {

          for(int i=10; i < 21; i ++) {
            if(i != 13){
              rgblight_setrgb_at(0, 255, 150, i); // sets LED 10-21 but not 13 to cyan on right hand
            }
          }
        }
        break;
    case _RAISE:

        if(!isLeftHand) {
          rgblight_setrgb_at(148, 0, 211, 13); // same thing here, sets LED 13 (raise) to purple and HJKL to cyan
          rgblight_setrgb_at(0, 255, 150, 8);
          rgblight_setrgb_at(0, 255, 150, 11);
          rgblight_setrgb_at(0, 255, 150, 16);
          rgblight_setrgb_at(0, 255, 150, 19);
        }

        break;
    case _ADJUST:
      if(isLeftHand){
        rgblight_setrgb_at(148,0,211, 26); // control purple, ZXCV cyan.
        rgblight_setrgb_at(0,255,150,21);
        rgblight_setrgb_at(0,255,150,20);
        rgblight_setrgb_at(0,255,150,15);
        rgblight_setrgb_at(0,255,150,12);
      }
      break;
    default:
        rgblight_enable();
        if(isLeftHand) {                        // this sets the underside LEDs (1-6) to cyan on both sides and does nothing with the rest.
          for(int i=0; i < 6; i ++) {           // this also means that if I manually change LED color to red, the bottom 6 LEDS will ALWAYS be cyan.
            rgblight_setrgb_at(0, 0, 255, i); // it's the only way I found to make it switch back to underglow LEDs after I've used another layer.
          }
        } else {
          for(int j=0; j < 6; j ++) {
            rgblight_setrgb_at(0, 0, 255, j);
          }
        }
        break;
    }
  return state;
}


int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

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
    case KC_JANZON:   // original LED underglow testing with Janzon. not used at the moment, but kept the code for nostalgia
      if (record->event.pressed) {
        if(isLeftHand) {
          for(int i=0; i < 6; i ++) {
            rgblight_sethsv_springgreen_at(i);
          }
        } else {
          for(int j=0; j < 6; j ++) {
            rgblight_sethsv_springgreen_at(j);
          }
        }
      }
      return true;
      break;

    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;

    case KC_MYLOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);

      } else {
        layer_off(_LOWER);


      }
      return true;
      break;

    case KC_MYRAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return true;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

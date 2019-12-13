#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
//SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _NAVIG,
    _MOUSE,
    _NUMBR,
    _SYMBL,
    _FUNKEY,
    _MEDIA
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
      XXXXXXX,  XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,            XXXXXXX,                                                    XXXXXXX,  XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,            XXXXXXX, \
      KC_GRV,   KC_Q,         KC_W,         KC_E,         KC_R,               KC_T,                                                       KC_Y,                KC_U,                KC_I,         KC_O,         KC_P,            KC_EQL, \
      KC_BSLS,  LALT_T(KC_A), LGUI_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F),       KC_G,                                                       KC_H,                RSFT_T(KC_J),        RCTL_T(KC_K), RGUI_T(KC_L), RALT_T(KC_SCLN), KC_QUOT, \
      KC_TAB,   KC_Z,         KC_X,         KC_C,         KC_V,               KC_B,               KC_LBRC,            KC_RBRC,            KC_N,                KC_M,                KC_COMM,      KC_DOT,       KC_SLSH,         KC_MINS, \
      XXXXXXX,  XXXXXXX,      XXXXXXX,      XXXXXXX,      LT(_MEDIA, KC_ESC), LT(_NAVIG, KC_TAB), LT(_MOUSE, KC_ENT), LT(_SYMBL, KC_SPC), LT(_NUMBR, KC_BSPC), LT(_FUNKEY, KC_DEL), XXXXXXX,      XXXXXXX,      XXXXXXX,         XXXXXXX \
      ),

   // Colemak DHm
  [_COLEMAK] = LAYOUT( \
      XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,            XXXXXXX,                                                    XXXXXXX,             XXXXXXX,             XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX, \
      KC_GRV,  KC_Q,         KC_W,         KC_F,         KC_P,               KC_B,                                                       KC_J,                KC_L,                KC_U,         KC_Y,         KC_SCLN,      KC_EQL, \
      KC_BSLS, LALT_T(KC_A), LGUI_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T),       KC_G,                                                       KC_M,                RSFT_T(KC_N),        RCTL_T(KC_E), RGUI_T(KC_I), RALT_T(KC_O), KC_QUOT, \
      KC_TAB,  KC_Z,         KC_X,         KC_C,         KC_D,               KC_V,               KC_LBRC,            KC_RBRC,            KC_K,                KC_H,                KC_COMM,      KC_DOT,       KC_SLSH,      KC_UNDS, \
      XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,      LT(_MEDIA, KC_ESC), LT(_NAVIG, KC_TAB), LT(_MOUSE, KC_ENT), LT(_SYMBL, KC_SPC), LT(_NUMBR, KC_BSPC), LT(_FUNKEY, KC_DEL), XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX \
      ),

  [_NAVIG] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, LCTL(KC_UNDS), LCTL(KC_W), LALT(KC_W), LCTL(KC_Y), XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_LEFT,       KC_DOWN,    KC_UP,      KC_RIGHT,   XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME,       KC_PGDN,    KC_PGUP,    KC_END,     XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX \
      ),

  [_MOUSE] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, LCTL(KC_UNDS), LCTL(KC_W), LALT(KC_W), LCTL(KC_Y), XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_MS_L,       KC_MS_D,    KC_MS_U,    KC_MS_R,    XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, KC_BTN1, KC_BTN2, KC_BTN3,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX \
      ),

  [_NUMBR] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                    XXXXXXX, KC_RSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_0,    KC_MINS, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      ),

  [_SYMBL] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RPRN, KC_UNDS, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      ),

  [_FUNKEY] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, LCA(F3), KC_F7,   KC_F8,   KC_F9,   KC_F12,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, LCA(F2), KC_F4,   KC_F5,   KC_F6,   KC_F11,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, LCA(F1), KC_F1,   KC_F2,   KC_F3,   KC_F10,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      ),

  [_MEDIA] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, RESET,   RGBRST,  XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MUTE, KC_VOLU, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, QWERTY,  COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      )
};

// define variables for reactive RGB
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
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

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  RGB_current_mode = rgblight_config.mode;
#endif
#ifdef SSD1306OLED
  iota_gfx_init(!has_usb());   // turns on the display
#endif
}

#ifdef SSD1306OLED

void matrix_scan_user(void) {
  iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                   const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_NAVIG (1<<_NAVIG)
#define L_MOUSE (1<<_MOUSE)
#define L_FUNKEY (1<<_FUNKEY)
#define L_SYMBL (1<<_SYMBL)
#define L_MEDIA (1<<_MEDIA)
#define L_NUMBR (1<<_NUMBR)


static void render_blank(struct CharacterMatrix *matrix) {
  matrix_write_P(matrix, PSTR("\n"));
}

static void render_numb(struct CharacterMatrix *matrix) {
  static char numb[][12] = {{0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x11,0x1e,0x1f,0},
                            {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x11,0x1c,0x1d,0},
                            {0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0x11,0x1a,0x1b,0},
                            {0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0x11,0x18,0x19,0}};
  matrix_write(matrix, numb[0]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, numb[1]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, numb[2]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, numb[3]);
}

static void render_symb(struct CharacterMatrix *matrix) {
  static char symb[][12] = {{0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x11,0x3e,0x3f,0},
                            {0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x11,0x3c,0x3d,0},
                            {0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0x11,0x1a,0x1b,0},
                            {0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0x11,0x18,0x19,0}};
  matrix_write(matrix, symb[0]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, symb[1]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, symb[2]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, symb[3]);
}

static void render_func(struct CharacterMatrix *matrix) {
  static char func[][12] = {{0x60,0x61,0x14,0x15,0x16,0x17,0x34,0x35,0x11,0x5e,0x5f,0},
                            {0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x11,0x1c,0x1d,0},
                            {0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0x11,0x1e,0x1f,0},
                            {0xc0,0xc1,0x12,0x13,0x02,0x03,0x04,0x05,0x11,0x5c,0x5d,0}};
  matrix_write(matrix, func[0]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, func[1]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, func[2]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, func[3]);
}

static void render_navi(struct CharacterMatrix *matrix) {
  static char navi[][12] = {{0x58,0x59,0x11,0x73,0x74,0x75,0x76,0x77,0x78,0x68,0x69,0},
                            {0x5a,0x5b,0x11,0x93,0x94,0x95,0x96,0x97,0x98,0x68,0x69,0},
                            {0x3a,0x3b,0x11,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0x68,0x69,0},
                            {0x38,0x39,0x11,0xd3,0xd4,0xd5,0xd6,0xd7,0xd9,0x68,0x69,0}};
  matrix_write(matrix, navi[0]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, navi[1]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, navi[2]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, navi[3]);
}

static void render_mous(struct CharacterMatrix *matrix) {
  static char mous[][12] = {{0x58,0x59,0x11,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0},
                            {0x5a,0x5b,0x11,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0},
                            {0x3a,0x3b,0x11,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0},
                            {0x38,0x39,0x11,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0}};
  matrix_write(matrix, mous[0]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, mous[1]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, mous[2]);
  matrix_write_P(matrix, PSTR("\n"));
  matrix_write(matrix, mous[3]);
}

void render_left(struct CharacterMatrix *matrix) {
  switch (layer_state) {
        case L_FUNKEY:
           render_func(matrix);
           break;
        case L_NUMBR:
           render_numb(matrix);
           break;
        case L_SYMBL:
           render_symb(matrix);
           break;
        default:
           render_blank(matrix);
    }
}
void render_right(struct CharacterMatrix *matrix) {
  switch (layer_state) {
        case L_NAVIG:
          render_navi(matrix);
           break;
        case L_MOUSE:
          render_mous(matrix);
          break;
        case L_MEDIA:
          render_navi(matrix);
           break;
        default:
          render_blank(matrix);
    }
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_left(&matrix);
  }else{
    render_right(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

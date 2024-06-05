/* Copyright (C) 2007-2008 The Android Open Source Project
** Copyright (c) KylinSoft Co., Ltd. 2016-2024.All rights reserved.
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

#include "kmre_keycode.h"
#include "keycodes_common.h"

#include <stdlib.h>
#include <unistd.h>

//linux键码是否是按字母顺序排列的
bool linux_keycode_is_alphabetical(int32_t linux_key)
{
    return (linux_key >= LINUX_KEY_Q && linux_key <= LINUX_KEY_P) ||
           (linux_key >= LINUX_KEY_A && linux_key <= LINUX_KEY_L) ||
           (linux_key >= LINUX_KEY_Z && linux_key <= LINUX_KEY_M);
}

bool linux_keycode_is_modifier(int32_t linux_key)
{
    switch (linux_key) {
        case LINUX_KEY_LEFTCTRL:
        case LINUX_KEY_RIGHTCTRL:
        case LINUX_KEY_LEFTSHIFT:
        case LINUX_KEY_RIGHTSHIFT:
        case LINUX_KEY_LEFTALT:
        case LINUX_KEY_RIGHTALT:
        case LINUX_KEY_CAPSLOCK:
        case LINUX_KEY_NUMLOCK:
            return true;
        default:
            return false;
    }
}

#define KMRE_LINUX_KEYMAP_LIST \
    const KmreLinuxKeyCodeMap linux_kmre_keycode_map[] =
#if defined(__linux__)
#define KMRE_LINUX_KEYMAP(xkb, win, mac, code) \
    { xkb, code }
#endif

KMRE_LINUX_KEYMAP_LIST {
  KMRE_LINUX_KEYMAP(0x0026, 0x001e, 0x0000, LINUX_KEY_A), // aA
  KMRE_LINUX_KEYMAP(0x0038, 0x0030, 0x000b, LINUX_KEY_B), // bB
  KMRE_LINUX_KEYMAP(0x0036, 0x002e, 0x0008, LINUX_KEY_C), // cC
  KMRE_LINUX_KEYMAP(0x0028, 0x0020, 0x0002, LINUX_KEY_D), // dD
  KMRE_LINUX_KEYMAP(0x001a, 0x0012, 0x000e, LINUX_KEY_E), // eE
  KMRE_LINUX_KEYMAP(0x0029, 0x0021, 0x0003, LINUX_KEY_F), // fF
  KMRE_LINUX_KEYMAP(0x002a, 0x0022, 0x0005, LINUX_KEY_G), // gG
  KMRE_LINUX_KEYMAP(0x002b, 0x0023, 0x0004, LINUX_KEY_H), // hH
  KMRE_LINUX_KEYMAP(0x001f, 0x0017, 0x0022, LINUX_KEY_I), // iI
  KMRE_LINUX_KEYMAP(0x002c, 0x0024, 0x0026, LINUX_KEY_J), // jJ
  KMRE_LINUX_KEYMAP(0x002d, 0x0025, 0x0028, LINUX_KEY_K), // kK
  KMRE_LINUX_KEYMAP(0x002e, 0x0026, 0x0025, LINUX_KEY_L), // lL
  KMRE_LINUX_KEYMAP(0x003a, 0x0032, 0x002e, LINUX_KEY_M), // mM
  KMRE_LINUX_KEYMAP(0x0039, 0x0031, 0x002d, LINUX_KEY_N), // nN
  KMRE_LINUX_KEYMAP(0x0020, 0x0018, 0x001f, LINUX_KEY_O), // oO
  KMRE_LINUX_KEYMAP(0x0021, 0x0019, 0x0023, LINUX_KEY_P), // pP
  KMRE_LINUX_KEYMAP(0x0018, 0x0010, 0x000c, LINUX_KEY_Q), // qQ
  KMRE_LINUX_KEYMAP(0x001b, 0x0013, 0x000f, LINUX_KEY_R), // rR
  KMRE_LINUX_KEYMAP(0x0027, 0x001f, 0x0001, LINUX_KEY_S), // sS
  KMRE_LINUX_KEYMAP(0x001c, 0x0014, 0x0011, LINUX_KEY_T), // tT
  KMRE_LINUX_KEYMAP(0x001e, 0x0016, 0x0020, LINUX_KEY_U), // uU
  KMRE_LINUX_KEYMAP(0x0037, 0x002f, 0x0009, LINUX_KEY_V), // vV
  KMRE_LINUX_KEYMAP(0x0019, 0x0011, 0x000d, LINUX_KEY_W), // wW
  KMRE_LINUX_KEYMAP(0x0035, 0x002d, 0x0007, LINUX_KEY_X), // xX
  KMRE_LINUX_KEYMAP(0x001d, 0x0015, 0x0010, LINUX_KEY_Y), // yY
  KMRE_LINUX_KEYMAP(0x0034, 0x002c, 0x0006, LINUX_KEY_Z), // zZ
  KMRE_LINUX_KEYMAP(0x000a, 0x0002, 0x0012, LINUX_KEY_1), // 1!
  KMRE_LINUX_KEYMAP(0x000b, 0x0003, 0x0013, LINUX_KEY_2), // 2@
  KMRE_LINUX_KEYMAP(0x000c, 0x0004, 0x0014, LINUX_KEY_3), // 3#
  KMRE_LINUX_KEYMAP(0x000d, 0x0005, 0x0015, LINUX_KEY_4), // 4$
  KMRE_LINUX_KEYMAP(0x000e, 0x0006, 0x0017, LINUX_KEY_5), // 5%
  KMRE_LINUX_KEYMAP(0x000f, 0x0007, 0x0016, LINUX_KEY_6), // 6^
  KMRE_LINUX_KEYMAP(0x0010, 0x0008, 0x001a, LINUX_KEY_7), // 7&
  KMRE_LINUX_KEYMAP(0x0011, 0x0009, 0x001c, LINUX_KEY_8), // 8*
  KMRE_LINUX_KEYMAP(0x0012, 0x000a, 0x0019, LINUX_KEY_9), // 9(
  KMRE_LINUX_KEYMAP(0x0013, 0x000b, 0x001d, LINUX_KEY_0), // 0)
  KMRE_LINUX_KEYMAP(0x0024, 0x001c, 0x0024, LINUX_KEY_ENTER),
  KMRE_LINUX_KEYMAP(0x0009, 0x0001, 0x0035, LINUX_KEY_ESC),
  KMRE_LINUX_KEYMAP(0x0016, 0x000e, 0x0033, LINUX_KEY_BACKSPACE),
  KMRE_LINUX_KEYMAP(0x0017, 0x000f, 0x0030, LINUX_KEY_TAB),
  KMRE_LINUX_KEYMAP(0x0041, 0x0039, 0x0031, LINUX_KEY_SPACE), // Spacebar
  KMRE_LINUX_KEYMAP(0x0014, 0x000c, 0x001b, LINUX_KEY_MINUS), // -_
  KMRE_LINUX_KEYMAP(0x0015, 0x000d, 0x0018, LINUX_KEY_EQUAL), // =+
  KMRE_LINUX_KEYMAP(0x0022, 0x001a, 0x0021, LINUX_KEY_LEFTBRACE),
  KMRE_LINUX_KEYMAP(0x0023, 0x001b, 0x001e, LINUX_KEY_RIGHTBRACE),
  KMRE_LINUX_KEYMAP(0x0033, 0x002b, 0x002a, LINUX_KEY_BACKSLASH), // \|
  KMRE_LINUX_KEYMAP(0x002f, 0x0027, 0x0029, LINUX_KEY_SEMICOLON), // ;:
  KMRE_LINUX_KEYMAP(0x0030, 0x0028, 0x0027, LINUX_KEY_APOSTROPHE), // '"
  KMRE_LINUX_KEYMAP(0x0031, 0x0029, 0x0032, LINUX_KEY_GREEN), // `~
  KMRE_LINUX_KEYMAP(0x003b, 0x0033, 0x002b, LINUX_KEY_COMMA), // ,<
  KMRE_LINUX_KEYMAP(0x003c, 0x0034, 0x002f, LINUX_KEY_DOT), // .>
  KMRE_LINUX_KEYMAP(0x003d, 0x0035, 0x002c, LINUX_KEY_SLASH), // /?
  KMRE_LINUX_KEYMAP(0x0042, 0x003a, 0x0039, LINUX_KEY_CAPSLOCK),
  KMRE_LINUX_KEYMAP(0x007f, 0x0045, 0xffff, LINUX_KEY_PAUSE),
  KMRE_LINUX_KEYMAP(0x0076, 0xe052, 0x0072, LINUX_KEY_INSERT),
  KMRE_LINUX_KEYMAP(0x006e, 0xe047, 0x0073, LINUX_KEY_HOME),
  KMRE_LINUX_KEYMAP(0x0070, 0xe049, 0x0074, LINUX_KEY_PAGEUP),
  KMRE_LINUX_KEYMAP(0x0077, 0xe053, 0x0075, LINUX_KEY_DELETE),
  KMRE_LINUX_KEYMAP(0x0073, 0xe04f, 0x0077, LINUX_KEY_END),
  KMRE_LINUX_KEYMAP(0x0075, 0xe051, 0x0079, LINUX_KEY_PAGEDOWN),
  KMRE_LINUX_KEYMAP(0x0072, 0xe04d, 0x007c, LINUX_KEY_RIGHT),
  KMRE_LINUX_KEYMAP(0x0071, 0xe04b, 0x007b, LINUX_KEY_LEFT),
  KMRE_LINUX_KEYMAP(0x0074, 0xe050, 0x007d, LINUX_KEY_DOWN),
  KMRE_LINUX_KEYMAP(0x006f, 0xe048, 0x007e, LINUX_KEY_UP),
  KMRE_LINUX_KEYMAP(0x004d, 0xe045, 0x0047, LINUX_KEY_NUMLOCK),
  KMRE_LINUX_KEYMAP(0x006a, 0xe035, 0x004b, LINUX_KEY_KPSLASH),
  KMRE_LINUX_KEYMAP(0x0056, 0x004e, 0x0045, LINUX_KEY_KPPLUS),
  KMRE_LINUX_KEYMAP(0x0068, 0xe01c, 0x004c, LINUX_KEY_ENTER),
  KMRE_LINUX_KEYMAP(0x0057, 0x004f, 0x0053, LINUX_KEY_KP1),
  KMRE_LINUX_KEYMAP(0x0058, 0x0050, 0x0054, LINUX_KEY_KP2),
  KMRE_LINUX_KEYMAP(0x0059, 0x0051, 0x0055, LINUX_KEY_KP3),
  KMRE_LINUX_KEYMAP(0x0053, 0x004b, 0x0056, LINUX_KEY_KP4),
  KMRE_LINUX_KEYMAP(0x0054, 0x004c, 0x0057, LINUX_KEY_KP5),
  KMRE_LINUX_KEYMAP(0x0055, 0x004d, 0x0058, LINUX_KEY_KP6),
  KMRE_LINUX_KEYMAP(0x004f, 0x0047, 0x0059, LINUX_KEY_KP7),
  KMRE_LINUX_KEYMAP(0x0050, 0x0048, 0x005b, LINUX_KEY_KP8),
  KMRE_LINUX_KEYMAP(0x0051, 0x0049, 0x005c, LINUX_KEY_KP9),
  KMRE_LINUX_KEYMAP(0x005a, 0x0052, 0x0052, LINUX_KEY_KP0),
  KMRE_LINUX_KEYMAP(0x005b, 0x0052, 0x0052, LINUX_KEY_KPDOT), // .  (numlock, scancode: 91, linuxKeycode: 83)
  KMRE_LINUX_KEYMAP(0x003f, 0x0052, 0x0052, LINUX_KEY_KPASTERISK), // *  (numlock, scancode: 63, linuxKeycode: 55)
  KMRE_LINUX_KEYMAP(0x0052, 0x0052, 0x0052, LINUX_KEY_KPMINUS), // -  (numlock, scancode: 82, linuxKeycode: 74)
  KMRE_LINUX_KEYMAP(0x007c, 0xe05e, 0xffff, LINUX_KEY_POWER),
  KMRE_LINUX_KEYMAP(0x0081, 0x007e, 0x005f, LINUX_KEY_KPCOMMA),
  KMRE_LINUX_KEYMAP(0x0025, 0x001d, 0x003b, LINUX_KEY_LEFTCTRL),
  KMRE_LINUX_KEYMAP(0x0032, 0x002a, 0x0038, LINUX_KEY_LEFTSHIFT),
  KMRE_LINUX_KEYMAP(0x0040, 0x0038, 0x003a, LINUX_KEY_LEFTALT),
  KMRE_LINUX_KEYMAP(0x0085, 0xe05b, 0x0037, LINUX_KEY_LEFTMETA),
  KMRE_LINUX_KEYMAP(0x0069, 0xe01d, 0x003e, LINUX_KEY_RIGHTCTRL),
  KMRE_LINUX_KEYMAP(0x003e, 0x0036, 0x003c, LINUX_KEY_RIGHTSHIFT),
  KMRE_LINUX_KEYMAP(0x006c, 0xe038, 0x003d, LINUX_KEY_RIGHTALT),
  KMRE_LINUX_KEYMAP(0x0086, 0xe05c, 0x0036, LINUX_KEY_RIGHTMETA),
};

#undef KMRE_LINUX_KEYMAP
#undef KMRE_LINUX_KEYMAP_LIST


int convert_key_scancode_to_linux_keycode(int32_t scancode)
{
#if defined(__linux__)
    size_t i;
    for (i = 0; i < (sizeof(linux_kmre_keycode_map) / sizeof(linux_kmre_keycode_map[0])); i++) {
        if (linux_kmre_keycode_map[i].scancode == scancode) {
            return linux_kmre_keycode_map[i].linux_keycode;
        }
    }
    return LINUX_KEY_RESERVED;  // 0
#else
    return LINUX_KEY_RESERVED;  // 0
#endif
}

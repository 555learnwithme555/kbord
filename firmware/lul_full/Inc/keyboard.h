#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "stm32f0xx_hal.h"

#define KEY_LEFT_CTRL   0x80
#define KEY_LEFT_SHIFT    0x81
#define KEY_LEFT_ALT    0x82
#define KEY_LEFT_GUI    0x83
#define KEY_RIGHT_CTRL    0x84
#define KEY_RIGHT_SHIFT   0x85
#define KEY_RIGHT_ALT   0x86
#define KEY_RIGHT_GUI   0x87

#define KEY_RETURN (0X28+0x88)
#define KEY_ESC (0X29+0x88)
#define KEY_BACKSPACE (0X2A+0x88)
#define KEY_TAB (0X2B+0x88)
#define KEY_CAPS_LOCK (0X39+0x88)
#define KEY_F1 (0X3A+0x88)
#define KEY_F2 (0X3B+0x88)
#define KEY_F3 (0X3C+0x88)
#define KEY_F4 (0X3D+0x88)
#define KEY_F5 (0X3E+0x88)
#define KEY_F6 (0X3F+0x88)
#define KEY_F7 (0X40+0x88)
#define KEY_F8 (0X41+0x88)
#define KEY_F9 (0X42+0x88)
#define KEY_F10 (0X43+0x88)
#define KEY_F11 (0X44+0x88)
#define KEY_F12 (0X45+0x88)
#define KEY_INSERT (0X49+0x88)
#define KEY_HOME (0X4A+0x88)
#define KEY_PAGE_UP (0X4B+0x88)
#define KEY_DELETE (0X4C+0x88)
#define KEY_END (0X4D+0x88)
#define KEY_PAGE_DOWN (0X4E+0x88)
#define KEY_RIGHT_ARROW (0X4F+0x88)
#define KEY_LEFT_ARROW (0X50+0x88)
#define KEY_DOWN_ARROW (0X51+0x88)
#define KEY_UP_ARROW (0X52+0x88)

#define KB_BUF_SIZE 5

void kb_test(void);

#ifdef __cplusplus
}
#endif

#endif



#ifndef BLUETOOTH_KEYMAP
#define BLUETOOTH_KEYMAP

// Bits in usbHidKeyboardInput.modifiers
#define M_NONE          ((0))
#define M_CONTROL_L  ((1<<0))
#define M_SHIFT_L    ((1<<1))
#define M_ALT_L      ((1<<2))
#define M_GUI_L      ((1<<3))
#define M_CONTROL_R ((1<<4))
#define M_SHIFT_R   ((1<<5))
#define M_ALT_R     ((1<<6))
#define M_GUI_R     ((1<<7))
 
// Values for usbHidKeyboardInput.keyCodes
// Only the key codes for common keys are defined here. See Hut1_12.pdf for a full list.
#define K_NONE               (0x00)
#define K_A                  (0x04)
#define K_B                  (0x05)
#define K_C                  (0x06)
#define K_D                  (0x07)
#define K_E                  (0x08)
#define K_F                  (0x09)
#define K_G                  (0x0A)
#define K_H                  (0x0B)
#define K_I                  (0x0C)
#define K_J                  (0x0D)
#define K_K                  (0x0E)
#define K_L                  (0x0F)
#define K_M                  (0x10)
#define K_N                  (0x11)
#define K_O                  (0x12)
#define K_P                  (0x13)
#define K_Q                  (0x14)
#define K_R                  (0x15)
#define K_S                  (0x16)
#define K_T                  (0x17)
#define K_U                  (0x18)
#define K_V                  (0x19)
#define K_W                  (0x1A)
#define K_X                  (0x1B)
#define K_Y                  (0x1C)
#define K_Z                  (0x1D)
#define K_1                  (0x1E)
#define K_2                  (0x1F)
#define K_3                  (0x20)
#define K_4                  (0x21)
#define K_5                  (0x22)
#define K_6                  (0x23)
#define K_7                  (0x24)
#define K_8                  (0x25)
#define K_9                  (0x26)
#define K_0                  (0x27)
#define K_RETURN             (0x28)
#define K_ESCAPE             (0x29)
#define K_BACKSPACE          (0x2A)
#define K_TAB                (0x2B)
#define K_SPACE              (0x2C)
#define K_MINUS              (0x2D)
#define K_EQUAL              (0x2E)
#define K_BRACKET_L       (0x2F)
#define K_BRACKET_R      (0x30)
#define K_BACKSLASH          (0x31)
#define K_EUROPE_1           (0x32)
#define K_SEMICOLON          (0x33)
#define K_APOSTROPHE         (0x34)
#define K_GRAVE              (0x35)
#define K_COMMA              (0x36)
#define K_PERIOD             (0x37)
#define K_SLASH              (0x38)
#define K_CAPS_LOCK          (0x39)
#define K_F1                 (0x3A)
#define K_F2                 (0x3B)
#define K_F3                 (0x3C)
#define K_F4                 (0x3D)
#define K_F5                 (0x3E)
#define K_F6                 (0x3F)
#define K_F7                 (0x40)
#define K_F8                 (0x41)
#define K_F9                 (0x42)
#define K_F10                (0x43)
#define K_F11                (0x44)
#define K_F12                (0x45)
#define K_PRINT_SCREEN       (0x46)
#define K_SCROLL_LOCK        (0x47)
#define K_PAUSE              (0x48)
#define K_INSERT             (0x49)
#define K_HOME               (0x4A)
#define K_PAGE_U            (0x4B)
#define K_DELETE             (0x4C)
#define K_END                (0x4D)
#define K_PAGE_D          (0x4E)
#define K_ARROW_R        (0x4F)
#define K_ARROW_L         (0x50)
#define K_ARROW_D         (0x51)
#define K_ARROW_U           (0x52)
#define K_NUM_LOCK           (0x53)
#define K_KPAD_DIVIDE      (0x54)
#define K_KPAD_MULTIPLY    (0x55)
#define K_KPAD_SUBTRACT    (0x56)
#define K_KPAD_ADD         (0x57)
#define K_KPAD_ENTER       (0x58)
#define K_KPAD_1           (0x59)
#define K_KPAD_2           (0x5A)
#define K_KPAD_3           (0x5B)
#define K_KPAD_4           (0x5C)
#define K_KPAD_5           (0x5D)
#define K_KPAD_6           (0x5E)
#define K_KPAD_7           (0x5F)
#define K_KPAD_8           (0x60)
#define K_KPAD_9           (0x61)
#define K_KPAD_0           (0x62)
#define K_KPAD_DECIMAL     (0x63)
#define K_EUROPE_2           (0x64)
#define K_APPLICATION        (0x65)
#define K_POWER              (0x66)
#define K_KPAD_EQUAL       (0x67)
#define K_F13                (0x68)
#define K_F14                (0x69)
#define K_F15                (0x6A)
#define K_CONTROL_L       (0xE0)
#define K_SHIFT_L         (0xE1)
#define K_ALT_L           (0xE2)
#define K_GUI_L           (0xE3)
#define K_CONTROL_R      (0xE4)
#define K_SHIFT_R        (0xE5)
#define K_ALT_R          (0xE6)
#define K_GUI_R          (0xE7)

#endif

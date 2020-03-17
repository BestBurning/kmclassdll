#ifndef _KEYMOUSE_H
#define _KEYMOUSE_H


#ifndef METHOD_BUFFERED
#define METHOD_BUFFERED                 0
#endif

#ifndef CTL_CODE
#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)
#endif

#ifndef FILE_ANY_ACCESS
#define FILE_ANY_ACCESS                 0
#endif

#ifndef KEYBOARD_DEVICE
#define KEYBOARD_DEVICE      0
#endif

#ifndef MOUSE_DEVICE
#define MOUSE_DEVICE         1
#endif
//
// Define the various device type values.  Note that values used by Microsoft
// Corporation are in the range 0-0x7FFF(32767), and 0x8000(32768)-0xFFFF(65535)
// are reserved for use by customers.
//
#define FILE_DEVICE_KEYMOUSE	0x8000

//
// Macro definition for defining IOCTL and FSCTL function control codes. Note
// that function codes 0-0x7FF(2047) are reserved for Microsoft Corporation,
// and 0x800(2048)-0xFFF(4095) are reserved for customers.
//
#define KEYMOUSE_IOCTL_BASE 0x800

//
// The device driver IOCTLs

//
#define CTL_CODE_KEYMOUSE(i)	(ULONG)(CTL_CODE(FILE_DEVICE_KEYMOUSE, KEYMOUSE_IOCTL_BASE + i, METHOD_BUFFERED, FILE_ANY_ACCESS))
#define IOCTL_KEYBOARD       	CTL_CODE_KEYMOUSE(0)
#define IOCTL_MOUSE	            CTL_CODE_KEYMOUSE(1)

//
// Name that Win32 front end will use to open the KeyMouse device
//


#define KEYMOUSE_DEVICE_NAME		    L"\\Device\\kmclass"
#define KEYMOUSE_DOS_DEVICE_NAME	    L"\\DosDevices\\kmclass"

#ifdef  UNICODE
#define KEYMOUSE_WIN32_DEVICE_NAME	    L"\\\\.\\kmclass"
#define KEYMOUSE_DRIVER_NAME            L"kmclass"
#else
#define KEYMOUSE_WIN32_DEVICE_NAME	    "\\\\.\\kmclass"
#define KEYMOUSE_DRIVER_NAME            "kmclass"
#endif


typedef struct _KEYBOARD_INPUT_DATA {

    USHORT UnitId;

    USHORT MakeCode;

    USHORT Flags;

    USHORT Reserved;

    ULONG ExtraInformation;

} KEYBOARD_INPUT_DATA, * PKEYBOARD_INPUT_DATA;

//
// Define the keyboard input data Flags.
//

#define KEY_MAKE  0
#define KEY_BREAK 1
#define KEY_E0    2
#define KEY_E1    4
#define KEY_TERMSRV_SET_LED 8
#define KEY_TERMSRV_SHADOW  0x10
#define KEY_TERMSRV_VKPACKET 0x20

#define KEY_DOWN                KEY_MAKE
#define KEY_UP                  KEY_BREAK
#define KEY_BLANK                -1


typedef struct _MOUSE_INPUT_DATA {

    USHORT UnitId;

    USHORT Flags;

    union {
        ULONG Buttons;
        struct {
            USHORT  ButtonFlags;
            USHORT  ButtonData;
        };
    };

    ULONG RawButtons;

    LONG LastX;

    LONG LastY;

    ULONG ExtraInformation;

} MOUSE_INPUT_DATA, * PMOUSE_INPUT_DATA;

//
// Define the mouse button state indicators.
//

#define MOUSE_LEFT_BUTTON        0x0001
#define MOUSE_RIGHT_BUTTON       0x0002
#define MOUSE_LEFT_BUTTON_DOWN   0x0001  // Left Button changed to down.
#define MOUSE_LEFT_BUTTON_UP     0x0002  // Left Button changed to up.
#define MOUSE_RIGHT_BUTTON_DOWN  0x0004  // Right Button changed to down.
#define MOUSE_RIGHT_BUTTON_UP    0x0008  // Right Button changed to up.
#define MOUSE_MIDDLE_BUTTON_DOWN 0x0010  // Middle Button changed to down.
#define MOUSE_MIDDLE_BUTTON_UP   0x0020  // Middle Button changed to up.

#define MOUSE_BUTTON_1_DOWN     MOUSE_LEFT_BUTTON_DOWN
#define MOUSE_BUTTON_1_UP       MOUSE_LEFT_BUTTON_UP
#define MOUSE_BUTTON_2_DOWN     MOUSE_RIGHT_BUTTON_DOWN
#define MOUSE_BUTTON_2_UP       MOUSE_RIGHT_BUTTON_UP
#define MOUSE_BUTTON_3_DOWN     MOUSE_MIDDLE_BUTTON_DOWN
#define MOUSE_BUTTON_3_UP       MOUSE_MIDDLE_BUTTON_UP

#define MOUSE_BUTTON_4_DOWN     0x0040
#define MOUSE_BUTTON_4_UP       0x0080
#define MOUSE_BUTTON_5_DOWN     0x0100
#define MOUSE_BUTTON_5_UP       0x0200

#define MOUSE_WHEEL             0x0400

//
// Define the mouse indicator flags.
//

#define MOUSE_MOVE_RELATIVE         0
#define MOUSE_MOVE_ABSOLUTE         1
#define MOUSE_VIRTUAL_DESKTOP    0x02  // the coordinates are mapped to the virtual desktop
#define MOUSE_ATTRIBUTES_CHANGED 0x04  // requery for mouse attributes



#endif
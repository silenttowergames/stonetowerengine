#include "KeyboardStateFunctions.h"

void KeyboardState_Create(KeyboardState* keyboardState)
{
	memset(keyboardState, 0, sizeof(KeyboardState));
	
	SDL_KeyCode codes[240] = {
        SDLK_UNKNOWN,
        SDLK_RETURN,
        SDLK_ESCAPE,
        SDLK_BACKSPACE,
        SDLK_TAB,
        SDLK_SPACE,
        SDLK_EXCLAIM,
        SDLK_QUOTEDBL,
        SDLK_HASH,
        SDLK_PERCENT,
        SDLK_DOLLAR,
        SDLK_AMPERSAND,
        SDLK_QUOTE,
        SDLK_LEFTPAREN,
        SDLK_RIGHTPAREN,
        SDLK_ASTERISK,
        SDLK_PLUS,
        SDLK_COMMA,
        SDLK_MINUS,
        SDLK_PERIOD,
        SDLK_SLASH,
        SDLK_0,
        SDLK_1,
        SDLK_2,
        SDLK_3,
        SDLK_4,
        SDLK_5,
        SDLK_6,
        SDLK_7,
        SDLK_8,
        SDLK_9,
        SDLK_COLON,
        SDLK_SEMICOLON,
        SDLK_LESS,
        SDLK_EQUALS,
        SDLK_GREATER,
        SDLK_QUESTION,
        SDLK_AT,
        SDLK_LEFTBRACKET,
        SDLK_BACKSLASH,
        SDLK_RIGHTBRACKET,
        SDLK_CARET,
        SDLK_UNDERSCORE,
        SDLK_BACKQUOTE,
        SDLK_a,
        SDLK_b,
        SDLK_c,
        SDLK_d,
        SDLK_e,
        SDLK_f,
        SDLK_g,
        SDLK_h,
        SDLK_i,
        SDLK_j,
        SDLK_k,
        SDLK_l,
        SDLK_m,
        SDLK_n,
        SDLK_o,
        SDLK_p,
        SDLK_q,
        SDLK_r,
        SDLK_s,
        SDLK_t,
        SDLK_u,
        SDLK_v,
        SDLK_w,
        SDLK_x,
        SDLK_y,
        SDLK_z,
        SDLK_CAPSLOCK,
        SDLK_F1,
        SDLK_F2,
        SDLK_F3,
        SDLK_F4,
        SDLK_F5,
        SDLK_F6,
        SDLK_F7,
        SDLK_F8,
        SDLK_F9,
        SDLK_F10,
        SDLK_F11,
        SDLK_F12,
        SDLK_PRINTSCREEN,
        SDLK_SCROLLLOCK,
        SDLK_PAUSE,
        SDLK_INSERT,
        SDLK_HOME,
        SDLK_PAGEUP,
        SDLK_DELETE,
        SDLK_END,
        SDLK_PAGEDOWN,
        SDLK_RIGHT,
        SDLK_LEFT,
        SDLK_DOWN,
        SDLK_UP,
        SDLK_NUMLOCKCLEAR,
        SDLK_KP_DIVIDE,
        SDLK_KP_MULTIPLY,
        SDLK_KP_MINUS,
        SDLK_KP_PLUS,
        SDLK_KP_ENTER,
        SDLK_KP_1,
        SDLK_KP_2,
        SDLK_KP_3,
        SDLK_KP_4,
        SDLK_KP_5,
        SDLK_KP_6,
        SDLK_KP_7,
        SDLK_KP_8,
        SDLK_KP_9,
        SDLK_KP_0,
        SDLK_KP_PERIOD,
        SDLK_APPLICATION,
        SDLK_POWER,
        SDLK_KP_EQUALS,
        SDLK_F13,
        SDLK_F14,
        SDLK_F15,
        SDLK_F16,
        SDLK_F17,
        SDLK_F18,
        SDLK_F19,
        SDLK_F20,
        SDLK_F21,
        SDLK_F22,
        SDLK_F23,
        SDLK_F24,
        SDLK_EXECUTE,
        SDLK_HELP,
        SDLK_MENU,
        SDLK_SELECT,
        SDLK_STOP,
        SDLK_AGAIN,
        SDLK_UNDO,
        SDLK_CUT,
        SDLK_COPY,
        SDLK_PASTE,
        SDLK_FIND,
        SDLK_MUTE,
        SDLK_VOLUMEUP,
        SDLK_VOLUMEDOWN,
        SDLK_KP_COMMA,
        SDLK_KP_EQUALSAS400,
        SDLK_ALTERASE,
        SDLK_SYSREQ,
        SDLK_CANCEL,
        SDLK_CLEAR,
        SDLK_PRIOR,
        SDLK_RETURN2,
        SDLK_SEPARATOR,
        SDLK_OUT,
        SDLK_OPER,
        SDLK_CLEARAGAIN,
        SDLK_CRSEL,
        SDLK_EXSEL,
        SDLK_KP_00,
        SDLK_KP_000,
        SDLK_THOUSANDSSEPARATOR,
        SDLK_DECIMALSEPARATOR,
        SDLK_CURRENCYUNIT,
        SDLK_CURRENCYSUBUNIT,
        SDLK_KP_LEFTPAREN,
        SDLK_KP_RIGHTPAREN,
        SDLK_KP_LEFTBRACE,
        SDLK_KP_RIGHTBRACE,
        SDLK_KP_TAB,
        SDLK_KP_BACKSPACE,
        SDLK_KP_A,
        SDLK_KP_B,
        SDLK_KP_C,
        SDLK_KP_D,
        SDLK_KP_E,
        SDLK_KP_F,
        SDLK_KP_XOR,
        SDLK_KP_POWER,
        SDLK_KP_PERCENT,
        SDLK_KP_LESS,
        SDLK_KP_GREATER,
        SDLK_KP_AMPERSAND,
        SDLK_KP_DBLAMPERSAND,
        SDLK_KP_VERTICALBAR,
        SDLK_KP_DBLVERTICALBAR,
        SDLK_KP_COLON,
        SDLK_KP_HASH,
        SDLK_KP_SPACE,
        SDLK_KP_AT,
        SDLK_KP_EXCLAM,
        SDLK_KP_MEMSTORE,
        SDLK_KP_MEMRECALL,
        SDLK_KP_MEMCLEAR,
        SDLK_KP_MEMADD,
        SDLK_KP_MEMSUBTRACT,
        SDLK_KP_MEMMULTIPLY,
        SDLK_KP_MEMDIVIDE,
        SDLK_KP_PLUSMINUS,
        SDLK_KP_CLEAR,
        SDLK_KP_CLEARENTRY,
        SDLK_KP_BINARY,
        SDLK_KP_OCTAL,
        SDLK_KP_DECIMAL,
        SDLK_KP_HEXADECIMAL,
        SDLK_LCTRL,
        SDLK_LSHIFT,
        SDLK_LALT,
        SDLK_LGUI,
        SDLK_RCTRL,
        SDLK_RSHIFT,
        SDLK_RALT,
        SDLK_RGUI,
        SDLK_MODE,
        SDLK_AUDIONEXT,
        SDLK_AUDIOPREV,
        SDLK_AUDIOSTOP,
        SDLK_AUDIOPLAY,
        SDLK_AUDIOMUTE,
        SDLK_MEDIASELECT,
        SDLK_WWW,
        SDLK_MAIL,
        SDLK_CALCULATOR,
        SDLK_COMPUTER,
        SDLK_AC_SEARCH,
        SDLK_AC_HOME,
        SDLK_AC_BACK,
        SDLK_AC_FORWARD,
        SDLK_AC_STOP,
        SDLK_AC_REFRESH,
        SDLK_AC_BOOKMARKS,
        SDLK_BRIGHTNESSDOWN,
        SDLK_BRIGHTNESSUP,
        SDLK_DISPLAYSWITCH,
        SDLK_KBDILLUMTOGGLE,
        SDLK_KBDILLUMDOWN,
        SDLK_KBDILLUMUP,
        SDLK_EJECT,
        SDLK_SLEEP,
        SDLK_APP1,
        SDLK_APP2,
        SDLK_AUDIOREWIND,
        SDLK_AUDIOFASTFORWARD,
    };
    memcpy(keyboardState->codes, codes, sizeof(codes));
}

int KeyboardState_GetKey(KeyboardState* keyboardState, SDL_Keycode key)
{
    int i = KeyboardState_GetIndex(keyboardState, key);
    
    if (i < 0)
    {
        return 0;
    }
    
    return keyboardState->held[i];
}

int KeyboardState_GetIndex(KeyboardState* keyboardState, SDL_Keycode key)
{
    int
        count = sizeof(keyboardState->codes) / sizeof(SDL_Keycode),
        i
    ;
    
    for(i = 0; i < count; i++)
    {
        if(keyboardState->codes[i] == key)
        {
            break;
        }
    }
    
    if(i >= count)
    {
        return -1;
    }
    
    return i;
}

void KeyboardState_Event(KeyboardState* keyboardState, SDL_KeyboardEvent key)
{
    int i = KeyboardState_GetIndex(keyboardState, key.keysym.sym);
    
    if (i < 0)
    {
        return;
    }
    
    switch (key.type)
    {
        case SDL_KEYDOWN:
        {
            keyboardState->down[i] = fmin(5000, fmax(1, keyboardState->down[i] + 1));
        } break;
        
        case SDL_KEYUP:
        {
            keyboardState->down[i] = -1;
        } break;
        
        default:
            break;
    }
}

void KeyboardState_Update(KeyboardState* keyboardState)
{
    for(int i = 0; i < sizeof(keyboardState->down) / sizeof(int); i++)
    {
        if(keyboardState->down[i] > 0)
        {
            keyboardState->held[i] = fmin(5000, fmax(1, keyboardState->held[i] + 1));
        }
        else
        {
            keyboardState->held[i] = fmax(-5000, fmin(-1, keyboardState->held[i] - 1));
        }
    }
}

void KeyboardState_EndUpdate(KeyboardState* keyboardState)
{
    memset(keyboardState->letterQueue, 0, sizeof(keyboardState->letterQueue));
}

// TODO: All of these state functions need to be abstracted for use with gamepads
bool KeyboardState_Down(KeyboardState* keyboardState, SDL_Keycode key)
{
    int state = KeyboardState_GetKey(keyboardState, key);
    
    return state > 0;
}

bool KeyboardState_Up(KeyboardState* keyboardState, SDL_Keycode key)
{
    return !KeyboardState_Down(keyboardState, key);
}

bool KeyboardState_Pressed(KeyboardState* keyboardState, SDL_Keycode key)
{
    int state = KeyboardState_GetKey(keyboardState, key);
    
    return state == 1;
}

bool KeyboardState_Released(KeyboardState* keyboardState, SDL_Keycode key)
{
    int state = KeyboardState_GetKey(keyboardState, key);
    
    return state == -1;
}

bool KeyboardState_Held(KeyboardState* keyboardState, SDL_Keycode key)
{
    int i = KeyboardState_GetIndex(keyboardState, key);
    
    if (i < 0)
    {
        return false;
    }
    
    return keyboardState->held[i] > 0 && ((keyboardState->held[i] == 1 && keyboardState->down[i] == 1) || (keyboardState->down[i] > 1 && (keyboardState->held[i] - keyboardState->down[i]) % 2 == 0));
}

void KeyboardState_Type(KeyboardState* keyboardState, char character)
{
    for(int i = 0; i < sizeof(keyboardState->letterQueue) / sizeof(char); i++)
    {
        if(keyboardState->letterQueue[i] == '\0')
        {
            keyboardState->letterQueue[i] = character;
            
            break;
        }
    }
}

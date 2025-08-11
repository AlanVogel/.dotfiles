#pragma once

// Ensure TRRS is used for split communication (default for Corne TRRS cable, no I2C)
#define SPLIT_TRANSPORT_MIRROR

// Tapping term for tap/hold keys (e.g., MO(_FIRST), MO(_SECOND))
#define TAPPING_TERM 175

// Optional: Prevent accidental repeat taps for tap/hold keys
#define QUICK_TAP_TERM 0

// Optional: Permissive hold for easier layer switching
#define PERMISSIVE_HOLD

// Optional: Ignore modifier tap interrupt for smoother behavior
//#define IGNORE_MOD_TAP_INTERRUPT

// Enable OLED support
#ifndef OLED_ENABLE
#define OLED_ENABLE
#endif

// Ensure LED state (like Caps Lock) is shared between halves
#define SPLIT_LED_STATE_ENABLE

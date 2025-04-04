#pragma once

#define OLED_BRIGHTNESS 16
#define DEBOUNCE 5
#define FORCE_NKRO
#define TAPPING_TERM 200
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP0
#define I2C1_SCL_PIN GP1

/*
SPACE SAVERS WHEN NOT DEBUGGING
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG


#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT 
*/
#include <stdio.h>

#define null NULL
#define DEBUG_EN true
#define DEBUG if (DEBUG_EN) printf("%s %d", __FILE__, __LINE__);
#define MAX_STR 1000
#define DECIMAL_CHAR_VAL_0 48
#define DECIMAL_CHAR_VAL_9 57
typedef enum {false, true} bool;

char getChar();
bool isInt(char c);

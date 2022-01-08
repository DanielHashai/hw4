#include <stdio.h>

#define null NULL
#define DEBUG_EN true
#define EXTRA_DEBUG_EN true
#define DEBUG if (DEBUG_EN) printf("%s %d", __FILE__, __LINE__);
#define MAX_STR 1000
#define DECIMAL_CHAR_VAL_0 48
#define DECIMAL_CHAR_VAL_9 57
#define CHAR_SUCCESS ((char)255)
typedef enum {false, true} bool;

char getChar();
char getCharOnly();
int getInt();
bool isInt(char c);
bool isTerminate(char c);

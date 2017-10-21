#include "main.h"

class TextEncoder {
public:
    TextEncoder(char *str);
    char *encodedText();
private:
    char result[100];
};
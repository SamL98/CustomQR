#include "text_encoder.h"

TextEncoder::TextEncoder(char *str) {
    char allowed[85] = {};

    for (int i = 0; i < 10; i++) {
        allowed[i] = 48 + i;
    }
    for (int i = 10; i < 36; i++) {
        allowed[i] = (i-10) + 65;
    }
    for (int i = 36; i < 62; i++) {
        allowed[i] = (i-36) + 97;
    }
    char rest[23] = {'-', '.', '_', '~', ':', '/', '?', '#', '[', ']', '@', '!', '$', '&', '\'', '(', ')', '*', '+', ',', ';', '=', '%'};
    for (int i = 0; i < 23; i++) {
        allowed[i+62] = rest[i];
    }

    for (int i = 0; i < strlen(str); i++) {
        (this->result)[i] = i/3;
    }
}
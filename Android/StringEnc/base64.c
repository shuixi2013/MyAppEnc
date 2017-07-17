//
// Created by qwedd on 2017/7/11.
//

#include "base64.h"


int base64_decode(char *in,  char *out)
{
    unsigned long t, x, y, z;
    unsigned char c;
    int g = 3;

    for (x = y = z = t = 0; in[x]!=0;) {
        c = map[in[x++]];
        if (c == 255) return -1;
        if (c == 253) continue;
        if (c == 254) { c = 0; g--; }
        t = (t<<6)|c;
        if (++y == 4) {
//          if (z + g > *outlen) { return CRYPT_BUFFER_OVERFLOW; }
            out[z++] = (unsigned char)((t>>16)&255);
            if (g > 1) out[z++] = (unsigned char)((t>>8)&255);
            if (g > 2) out[z++] = (unsigned char)(t&255);
            y = t = 0;
        }
    }


    return z;
}
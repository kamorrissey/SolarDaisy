// Jenkins small-fast 8-bit pseudo-random number generator
// Uses no multiplication

#include "jsf8.h"

#define rot8(x, k) ((uint8_t)(((x) << (k)) | ((x) >> (8 - (k)))))

static uint8_t jsf_a, jsf_b, jsf_c, jsf_d;

uint8_t jsf8(void)
{
    uint8_t e = jsf_a - rot8(jsf_b, 1);
    jsf_a = jsf_b ^ rot8(jsf_c, 4);
    jsf_b = jsf_c + jsf_d;
    jsf_c = jsf_d + e;
    jsf_d = e + jsf_a;
    return jsf_d;
}

void jsf8_seed(uint8_t seed)
{
    jsf_a = 0xF1;
    jsf_b = jsf_c = jsf_d = seed;
    for (uint8_t i = 0; i < 20; ++i)
    {
        (void)jsf8();  // mix in the seed
    }
}

// Sun Jul  2 01:36:01 UTC 2017
// 0103-a0a-05-
// 4735-a0s-01-

// #define HAS_NEO_PIXEL_PIN_8 - yaffa.h

#ifndef NEO_PIXEL
#define NEO_PIXEL

extern const char rgb_str[]; // = "rgb"; // local idiom yainsu
extern const char pixel_str[]; // = "pixel"; // local idiom ainsuForth
extern const char npxBright_str[]; // = "bright"; // local idiom ainsuForth

extern void _rgb(void);
extern void setup_neoPixel(void);
extern void _pixel(void);
extern void _npxBright(void);

extern void _cyan(void);
extern void _darkNPX(void); // darken neo pixel
extern void _dullMagenta(void);

extern void _rot(void);
extern void _swap(void);

extern cell_t dStack_pop(void);
extern void dStack_push(cell_t value);

// extern void _rgbp(void);
// extern void _orange(void);
// extern void _blue(void);

// extern void neoPixel(void); // ainsuForth: invoke using the 'pixel' word

#endif



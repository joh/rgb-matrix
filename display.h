#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

struct Color {
    uint16_t r;
    uint16_t g;
    uint16_t b;
};

typedef struct Color DisplayBuf[8][8];

void display_init(void);
DisplayBuf *display_get_backbuffer(void);
void display_swapbuffers(void);
void display_clear(DisplayBuf *buf, uint16_t r, uint16_t g, uint16_t b);
void display_set(DisplayBuf *buf, unsigned int x, unsigned int y,
        uint16_t r, uint16_t g, uint16_t b);

#endif

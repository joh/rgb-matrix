#include <string.h>
#include <stdlib.h>

#include "display.h"
#include "utils.h"
#include "tests.h"

void test_columns(void)
{
    unsigned int i, k;

    const struct Color colors[] = {
        {0xffff, 0, 0},
        {0, 0xffff, 0},
        {0, 0, 0xffff},
        /*{0xffff, 0xffff, 0},*/
        /*{0, 0xffff, 0xffff},*/
        /*{0xffff, 0, 0xffff},*/
        /*{0xffff, 0xffff, 0xffff},*/
    };

    for (k = 0; k < sizeof(colors) / sizeof(*colors); k++) {
        const struct Color c = colors[k];
        for (i = 0; i < 8; i++) {
            DisplayBuf *buf = display_get_backbuffer();

            display_clear(buf, 0, 0, 0);
            display_set(buf, i, 0, c.r, c.g, c.b);
            display_swapbuffers();
            usleep(100000);
        }
    }
}

void test_rows(void)
{
    unsigned int i, k;

    const struct Color colors[] = {
        {0xffff, 0, 0},
        {0, 0xffff, 0},
        {0, 0, 0xffff},
        /*{0xffff, 0xffff, 0},*/
        /*{0, 0xffff, 0xffff},*/
        /*{0xffff, 0, 0xffff},*/
        /*{0xffff, 0xffff, 0xffff},*/
    };

    for (k = 0; k < sizeof(colors) / sizeof(*colors); k++) {
        const struct Color c = colors[k];
        for (i = 0; i < 8; i++) {
            DisplayBuf *buf = display_get_backbuffer();

            display_clear(buf, 0, 0, 0);
            display_set(buf, 0, i, c.r, c.g, c.b);
            display_swapbuffers();
            usleep(100000);
        }
    }
}

void test_swapbuffers(void)
{
    unsigned int i, j, k;
    for (k = 0; k < 200; k++) {
        DisplayBuf *buf = display_get_backbuffer();
        memset(buf, 0, sizeof(*buf));
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                /*(*buf)[i][j].r = rand() % 0xfff;*/
                /*(*buf)[i][j].g = rand() % 0xffff;*/
                /*(*buf)[i][j].b = rand() % 0x2fff;*/
                if (k % 2 == 0)
                    (*buf)[i][j].r = 0xffff;
                else
                    (*buf)[i][j].g = 0xffff;
            }
        }

        display_swapbuffers();

        /*while (k==1) {*/
        /*display_swapbuffers();*/
        /*}*/

        usleep(10000);
    }
}

void test_brightness(void)
{
    unsigned int i, j, k;

    const struct Color colors[] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0},
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
    };

    for (k = 0; k < sizeof(colors) / sizeof(*colors); k++) {
        const struct Color c = colors[k];
        DisplayBuf *buf = display_get_backbuffer();
        uint16_t brightness = 0;

        display_clear(buf, 0, 0, 0);

        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                (*buf)[i][j].r = c.r * brightness;
                (*buf)[i][j].g = c.g * brightness;
                (*buf)[i][j].b = c.b * brightness;
                brightness += 0xffff/64;
                /*brightness += 8;*/
            }
        }

        display_swapbuffers();
        usleep(1000000);
    }
}

void test_white(void)
{
    unsigned int i, j;
    uint16_t brightness = 0xffff/2;

    DisplayBuf *buf = display_get_backbuffer();

    display_clear(buf, 0, 0, 0);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            (*buf)[i][j].r = brightness;
            (*buf)[i][j].g = brightness;
            (*buf)[i][j].b = brightness;
        }
    }

    display_swapbuffers();
    usleep(1000000);
}

void test_random(void)
{
    unsigned int i, j, k;

    for (k = 0; k < 100; k++) {
        DisplayBuf *buf = display_get_backbuffer();
        memset(buf, 0, sizeof(*buf));

        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                (*buf)[i][j].r = rand() % 0xffff;
                (*buf)[i][j].g = rand() % 0xffff;
                (*buf)[i][j].b = rand() % 0xffff;
            }
        }

        display_swapbuffers();

        usleep(100000);
    }
}

void test_fade(void)
{
    unsigned int i, k;

    const struct Color colors[] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0},
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
    };

    for (i = 0; i < sizeof(colors) / sizeof(*colors); i++) {
        const struct Color c = colors[i];
        for (k = 0; k < 255; k++) {
            DisplayBuf *buf = display_get_backbuffer();
            display_clear(buf, c.r * k * k, c.g * k * k, c.b * k * k);
            display_swapbuffers();
        }

        for (k = 255; k > 0; k--) {
            DisplayBuf *buf = display_get_backbuffer();
            display_clear(buf, c.r * k * k, c.g * k * k, c.b * k * k);
            display_swapbuffers();
        }
    }
}

void test_patterns(void)
{
    unsigned int i;

    // Lines
    DisplayBuf *buf = display_get_backbuffer();
    display_clear(buf, 0, 0, 0);
    for (i = 0; i < 8; i++) {
        (*buf)[i][i].r = 0xffff;
        (*buf)[7-i][i].g = 0xffff;
        (*buf)[5][i].b = 0xffff;
    }
    display_swapbuffers();

    usleep(5000000);
}

void test_animation(void)
{
    int i;
    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = 1;

    for (i = 0; i < 8 * 8; i++) {
        DisplayBuf *buf = display_get_backbuffer();
        display_clear(buf, 0, 0, 0);

        display_set(buf, 0, i+0, 0xffff, 0x0000, 0x0000);
        display_set(buf, 1, i+5, 0x0000, 0xffff, 0x0000);
        display_set(buf, 2, i+3, 0x0000, 0x0000, 0xffff);
        display_set(buf, 3, i+4, 0xffff, 0xffff, 0x0000);
        display_set(buf, 4, i+2, 0xffff, 0x0000, 0xffff);
        display_set(buf, 5, i+7, 0x0000, 0xffff, 0xffff);
        display_set(buf, 6, i+3, 0xffff, 0xffff, 0xffff);
        display_set(buf, 7, i+0, 0xffff, 0x0000, 0x7fff);

        display_swapbuffers();

        usleep(100000);
    }

    x = 0;
    y = 0;
    dx = 1;
    dy = 0;

    for (i = 0; i < 4 * (8+6+8+6) - 1; i++) {
        DisplayBuf *buf = display_get_backbuffer();
        display_clear(buf, 0, 0, 0);

        (*buf)[y % 8][x % 8].r = 0xffff;
        (*buf)[x % 8][y % 8].g = 0xffff;
        (*buf)[x % 8][x % 8].b = 0xffff;

        display_swapbuffers();

        usleep(100000);

        x = x + dx;
        y = y + dy;

        /*if (x == 7 || x == 0)*/
        if (x == 7 && y == 0) {
            dx = 0;
            dy = 1;
        } else if (x == 7 && y == 7) {
            dx = -1;
            dy = 0;
        } else if (x == 0 && y == 7) {
            dx = 0;
            dy = -1;
        } else if (x == 0 && y == 0) {
            dx = 1;
            dy = 0;
        }
    }

}

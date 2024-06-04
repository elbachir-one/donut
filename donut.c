#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>     
#include <sys/ioctl.h>  
#include "config.h"     

void renderFrame(float A, float B, int width, int height);

int main() {
    float A = 0, B = 0;
    
    // Clear screen
    printf("\x1b[2J");
    for (;;) {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        int width = w.ws_col;
        int height = w.ws_row;

        renderFrame(A, B, width, height);
        A += 0.02; 
        B += 0.01; 
        usleep(30000); // Delay to slow down the animation (30 milliseconds)
    }

    return 0;
}

void renderFrame(float A, float B, int width, int height) {
    int k;
    float i, j;

    int buffer_size = width * height;
    float z[buffer_size];
    char b[buffer_size];

    const char *colors[] = {
        "\x1b[31m", // Red
        "\x1b[32m", // Green
        "\x1b[33m", // Yellow
        "\x1b[34m", // Blue
        "\x1b[35m", // Magenta
        "\x1b[36m", // Cyan
        "\x1b[37m"  // White
    };
    int num_colors = sizeof(colors) / sizeof(colors[0]);

    int centerX1, centerY1;

    // Center first donut if second donut is disabled
    #ifndef ENABLE_SECOND_DONUT
    centerX1 = width / 4;
    centerY1 = height / 2;
    #else
    // Otherwise, do not center either donut
    centerX1 = width / 4;
    centerY1 = height / 2;
    #endif

    // Calculate centerX2 and centerY2 for the second donut if enabled
    #ifdef ENABLE_SECOND_DONUT
    int centerX2 = 3 * width / 4;  // Center of the second donut
    int centerY2 = height / 2;
    #endif

    memset(b, 32, buffer_size);
    memset(z, 0, buffer_size * sizeof(float));

    for (j = 0; j < 6.28; j += 0.07) {
        for (i = 0; i < 6.28; i += 0.02) {
            // Calculations for first donut
            float c = sin(i), d = cos(j), e = sin(A), f = sin(j), g = cos(A), h = d + 2;
            float D = 1 / (c * h * e + f * g + 5);
            float l = cos(i), m = cos(B), n = sin(B);
            float t = c * h * g - f * e;
            int x1 = centerX1 + 50 * D * (l * h * m - t * n);
            int y1 = centerY1 + 25 * D * (l * h * n + t * m);
            int o1 = x1 + width * y1;
            int N1 = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

            if (height > y1 && y1 > 0 && x1 > 0 && width > x1 && D > z[o1]) {
                z[o1] = D;
                b[o1] = ".,-~:;=!*#$@"[N1 > 0 ? N1 : 0];
            }

            // Calculations for second donut (if enabled)
            #ifdef ENABLE_SECOND_DONUT
            if (ENABLE_SECOND_DONUT) {
                float c2 = sin(i), d2 = cos(j), e2 = sin(A + 1), f2 = sin(j), g2 = cos(A + 1), h2 = d2 + 2;
                float D2 = 1 / (c2 * h2 * e2 + f2 * g2 + 5);
                float l2 = cos(i), m2 = cos(B + 1), n2 = sin(B + 1);
                float t2 = c2 * h2 * g2 - f2 * e2;
                int x2 = centerX2 + 50 * D2 * (l2 * h2 * m2 - t2 * n2);
                int y2 = centerY2 + 25 * D2 * (l2 * h2 * n2 + t2 * m2);
                int o2 = x2 + width * y2;
                int N2 = 8 * ((f2 * e2 - c2 * d2 * g2) * m2 - c2 * d2 * e2 - f2 * g2 - l2 * d2 * n2);

                if (height > y2 && y2 > 0 && x2 > 0 && width > x2 && D2 > z[o2]) {
                    z[o2] = D2;
                    b[o2] = ".,-~:;=!*#$@"[N2 > 0 ? N2 : 0];
                }
            }
            #endif
        }
    }

    // Move cursor to home position
    printf("\x1b[H");
    for (k = 0; k < buffer_size; k++) {
        if (k % width == 0) {
            putchar('\n');
        } else {
            printf("%s%c", colors[k % num_colors], b[k]);
        }
    }
    printf("\x1b[0m");
}

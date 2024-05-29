#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h> // For usleep()

int k;
double sin(), cos();

int main() {
    float A = 0, B = 0, i, j, z[1760];
    char b[1760];
    char *colors[] = {
        "\x1b[31m", // Red
        "\x1b[32m", // Green
        "\x1b[33m", // Yellow
        "\x1b[34m", // Blue
        "\x1b[35m", // Magenta
        "\x1b[36m", // Cyan
        "\x1b[37m"  // White
    };
    int num_colors = sizeof(colors) / sizeof(colors[0]);

    printf("\x1b[2J");
    for (;;) {
        memset(b, 32, 1760);
        memset(z, 0, 7040);
        for (j = 0; 6.28 > j; j += 0.07)
            for (i = 0; 6.28 > i; i += 0.02) {
                float c = sin(i), d = cos(j), e = sin(A), f = sin(j), g = cos(A), h = d + 2,
                      D = 1 / (c * h * e + f * g + 5), l = cos(i), m = cos(B), n = sin(B), t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n), y = 12 + 15 * D * (l * h * n + t * m),
                    o = x + 80 * y, N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        printf("\x1b[H");
        for (k = 0; 1760 > k; k++) {
            // Apply color cycling through the colors array
            if (k % 80 == 0) {
                putchar(10); // New line
            } else {
                printf("%s%c", colors[k % num_colors], b[k]);
            }
        }
        printf("\x1b[0m"); // Reset colors
        A += 0.02; // Smaller increment to slow down rotation
        B += 0.01; // Smaller increment to slow down rotation
        usleep(30000); // Delay to further slow down the animation (30 milliseconds)
    }
}

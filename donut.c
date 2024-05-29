#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h> // For usleep()
#include <sys/ioctl.h> // For terminal size

void renderFrame(float A, float B, int width, int height);

int main() {
    float A = 0, B = 0;

    printf("\x1b[2J"); // Clear screen
    for (;;) {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        int width = w.ws_col;
        int height = w.ws_row;

        renderFrame(A, B, width, height);
        A += 0.02; // Increment angle A
        B += 0.01; // Increment angle B
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

    int centerX = width / 2;
    int centerY = height / 2;

    memset(b, 32, buffer_size); // Initialize buffer with spaces
    memset(z, 0, buffer_size * sizeof(float)); // Initialize z-buffer with zeros

    for (j = 0; j < 6.28; j += 0.07) {
        for (i = 0; i < 6.28; i += 0.02) {
            float c = sin(i), d = cos(j), e = sin(A), f = sin(j), g = cos(A), h = d + 2;
            float D = 1 / (c * h * e + f * g + 5);
            float l = cos(i), m = cos(B), n = sin(B);
            float t = c * h * g - f * e;
            int x = centerX + 50 * D * (l * h * m - t * n);
            int y = centerY + 25 * D * (l * h * n + t * m);
            int o = x + width * y;
            int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

            if (height > y && y > 0 && x > 0 && width > x && D > z[o]) {
                z[o] = D;
                b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
            }
        }
    }

    printf("\x1b[H"); // Move cursor to home position
    for (k = 0; k < buffer_size; k++) {
        if (k % width == 0) {
            putchar('\n'); // New line
        } else {
            printf("%s%c", colors[k % num_colors], b[k]);
        }
    }
    printf("\x1b[0m"); // Reset colors
}

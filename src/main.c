#include "snake.h"

int main() {
    srand(time(NULL));

    printf("\033[?25l"); // Hide cursor
    printf("\033[2J");   // Clear screen

    Setup();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        sleep_ms(100);
    }

    printf("\033[?25h"); // Show cursor again
    printf("\nGame Over! Final Score: %d\n", score);

    #ifdef _WIN32
    printf("Press any key to exit...");
    while (!_kbhit());
    #endif

    return 0;
}

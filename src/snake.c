#include "snake.h"

#ifdef _WIN32
void sleep_ms(int ms) { Sleep(ms); }
#else
void sleep_ms(int ms) { usleep(ms * 1000); }

int _kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF) { ungetc(ch, stdin); return 1; }
    return 0;
}

int _getch(void) { return getchar(); }
#endif

// Global variables
int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection dir;

void Setup() {
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % (WIDTH - 2) + 1;
    fruitY = rand() % (HEIGHT - 2) + 1;
    score = 0;
    nTail = 0;
}

void Draw() {
    printf("\033[H"); 

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                printf("#");
            else if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++)
                    if (tailX[k] == j && tailY[k] == i) { printf("o"); print = 1; }
                if (!print) printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d  (Controls: WASD, Q to Quit)\n", score);
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if(dir != RIGHT) dir = LEFT; break;
            case 'd': if(dir != LEFT) dir = RIGHT; break;
            case 'w': if(dir != DOWN) dir = UP; break;
            case 's': if(dir != UP) dir = DOWN; break;
            case 'q': gameOver = 1; break;
        }
    }
}

void Logic() {
    int prevX = tailX[0], prevY = tailY[0], prev2X, prev2Y;
    tailX[0] = x; tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i]; prev2Y = tailY[i];
        tailX[i] = prevX; tailY[i] = prevY;
        prevX = prev2X; prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    if (x <= 0 || x >= WIDTH - 1 || y <= 0 || y >= HEIGHT - 1)
        gameOver = 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % (WIDTH - 2) + 1;
        fruitY = rand() % (HEIGHT - 2) + 1;
        nTail++;
    }
}

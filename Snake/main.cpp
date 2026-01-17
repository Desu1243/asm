#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define WIDTH 16
#define HEIGHT 16
#define MAX_SNAKE 256

unsigned char snakeX[MAX_SNAKE];
unsigned char snakeY[MAX_SNAKE];
unsigned char snakeLength;

unsigned char foodX, foodY;
char direction;
char gameOver;

unsigned short gameSpeed = 200;

COORD cursor;

void hideCursor() {
    CONSOLE_CURSOR_INFO info = { 0 };
    info.dwSize = 100;
    info.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void spawnFood() {
    /*
    int valid = 0; // false
    while (!valid) {
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        valid = 1; // true
        for (int i = 0; i < snakeLength; i++) {
            if (snakeX[i] == foodX && snakeY[i] == foodY) {
                valid = 0; // false
                break;
            }
        }
    }
    */
    _asm {
        MOV AL, 0 // isValid = false

        while_isValid_start:
        CMP AL, 0;
        JNZ while_isValid_end;
    }
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    _asm {
        MOV CL, foodX;
        MOV CH, foodY;
        MOV AL, 1; // isValid = true
        MOV EBX, 0; // for iterator
        MOV AH, snakeLength;
        LEA ESI, snakeX;
        LEA EDI, snakeY;

        for_isValid_start:
            CMP BL, BH;
            JAE for_isValid_end;

            CMP [ESI + EBX], CL; // snakeX[i] == foodX
            JNZ if_isValid_false;
            CMP [EDI + EBX], CH; // snakeY[i] == foodY
            JNZ if_isValid_false;

            JMP for_isValid_start;

            if_isValid_false:
            MOV AL, 0;
            JMP while_isValid_start;

            ADD BL, 1; // i++
        for_isValid_end:
        JMP while_isValid_start;

    while_isValid_end:
    }
}

void initGame() {
    snakeLength = 3;
    snakeX[0] = 8; 
    snakeY[0] = 8;

    snakeX[1] = 7; 
    snakeY[1] = 8;

    snakeX[2] = 6; 
    snakeY[2] = 8;
    direction = 'D';
    gameOver = 0;
    spawnFood();
}

void draw() {
    cursor.X = 0;
    cursor.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);

    for (int y = -1; y <= HEIGHT; y++) {
        for (int x = -1; x <= WIDTH; x++) {
            if (x == -1 || x == WIDTH || y == -1 || y == HEIGHT) {
                printf("#");
            }
            else if (x == foodX && y == foodY) {
                printf("Q");
            }
            else {
                int printed = 0;
                for (int i = 0; i < snakeLength; i++) {
                    if (snakeX[i] == x && snakeY[i] == y) {
                        if (i == 0) printf("@");
                        else printf("o");
                        printed = 1;
                    }
                }
                if (!printed) printf(" ");
            }
        }
        printf("\n");
    }
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if ((key == 'w' || key == 'W') && direction != 'S') direction = 'W';
        if ((key == 's' || key == 'S') && direction != 'W') direction = 'S';
        if ((key == 'a' || key == 'A') && direction != 'D') direction = 'A';
        if ((key == 'd' || key == 'D') && direction != 'A') direction = 'D';
    }
}

void logic() {
    unsigned char prevX = snakeX[0];
    unsigned char prevY = snakeY[0];
    unsigned char tempX, tempY;

    for (int i = 1; i < snakeLength; i++) {
        tempX = snakeX[i];
        tempY = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    if (direction == 'W') snakeY[0]--;
    if (direction == 'S') snakeY[0]++;
    if (direction == 'A') snakeX[0]--;
    if (direction == 'D') snakeX[0]++;

    // Kolizja ze ścianą
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
        gameOver = 1;
    }

    // Kolizja z samym sobą
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = 1;
        }
    }

    // Jedzenie
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        snakeX[snakeLength] = prevX;
        snakeY[snakeLength] = prevY;
        snakeLength++;
        spawnFood();
    }
}

int main() {
    srand(0);
    hideCursor();
    initGame();

    while (!gameOver) {
        input();
        logic();
        draw();
        Sleep(gameSpeed);
    }

    cursor.X = 0;
    cursor.Y = HEIGHT + 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    printf("KONIEC GRY!\n");
    printf("Dlugosc weza: %d\n", snakeLength);

    return 0;
}

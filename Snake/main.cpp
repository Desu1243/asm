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

unsigned short gameSpeed = 400;

COORD cursor;

void hideCursor() {
    CONSOLE_CURSOR_INFO info = { 0 };
    info.dwSize = 100;
    info.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void spawnFood() {
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
                continue;
            }
            if (x == foodX && y == foodY) {
                printf("Q");
                continue;
            }
            
            int printed = 0;
            for (int i = 0; i < snakeLength; i++) {
                if (snakeX[i] == x && snakeY[i] == y) {
                    if (i == 0) printf("@");
                    else printf("o");
                    printed = 1;
                }
            }
            if (printed == 0) printf(" ");
            
        }
        printf("\n");
    }
    

    /*
    _asm {
        MOV AL, -1; // y
        MOV AH, HEIGHT;

        for_draw_Y_start:
        CMP AL, AH;
        JG for_draw_Y_end;

            MOV BL, -1; // x
            MOV BH, WIDTH;
            for_draw_X_start:
            CMP BL, BH;
            JG for_draw_X_end;

                CMP BL, -1;
                JE draw_print_border;
                CMP BL, BH;
                JE draw_print_border;
                CMP AL, -1;
                JE draw_print_border;
                CMP AL, AH;
                JE draw_print_border;

                MOV CL, foodX;
                MOV CH, foodY;
                CMP CL, BL;
                JNZ draw_food_false;
                CMP CH, AL;
                JNZ draw_food_false; 
    }           printf("Q");
    _asm{
                JMP for_draw_X_continue;


                draw_food_false:/// ecx i edx sa wolne
                MOV CH, 0; // isPrinted
                MOV EDX, 0; // i
                MOV CL, snakeLength;
                LEA ESI, snakeX;
                LEA EDI, snakeY;
                for_draw_snake_start:
                    CMP DL, CL;
                    JAE for_draw_snake_end;

                    CMP [ESI + EDX], BL;
                    JNZ skip_print_snake;
                    CMP [ESI + EDX], AL;
                    JNZ skip_print_snake;

                    CMP DL, 0;
                    JZ print_snake_head;
    }               printf("o"); 
    _asm {
                    JMP print_end;

                    print_snake_head:
    }               printf("@"); 
    _asm {
                    print_end:
                    MOV CH, 1;
                    skip_print_snake:

                    ADD DH, 1;
                    JMP for_draw_snake_start;
                for_draw_snake_end:
                CMP CH, 0;
                JNZ for_draw_X_continue;
    }           printf(" "); 
    _asm {
                JMP for_draw_X_continue;


                draw_print_border:
    }           printf("#"); 
    _asm {
                JMP for_draw_X_continue;
                
                
            for_draw_X_continue:
            ADD BL, 1;
            JMP for_draw_X_start;
            for_draw_X_end:

        ADD AL, 1;
    }   printf("\n"); 
    _asm {
        JMP for_draw_Y_start;
        for_draw_Y_end:
    }
    
    */
/*
_asm {
    push ebx
    push esi
    push edi

    mov al, -1; //y = -1
    mov ah, HEIGHT; //AH = HEIGHT

    for_draw_Y_start :
    cmp al, ah
        jg for_draw_Y_end

        mov bl, -1; // x = -1
        mov bh, WIDTH; //BH = WIDTH

        for_draw_X_start :
    cmp bl, bh
        jg for_draw_X_end

        ; if border
        cmp bl, -1
        je draw_print_border
        cmp bl, bh
        je draw_print_border
        cmp al, -1
        je draw_print_border
        cmp al, ah
        je draw_print_border

        ; if food
        mov cl, foodX
        cmp cl, bl
        jne draw_food_false
        mov cl, foodY
        cmp cl, al
        jne draw_food_false
}
printf("Q");
_asm {
    jmp for_draw_X_continue

    draw_food_false :
    xor ch, ch; //printed = 0
        xor edx, edx; //i = 0
        mov cl, snakeLength
        lea esi, snakeX
        lea edi, snakeY

        for_draw_snake_start :
    cmp dl, cl
        jae for_draw_snake_end

        mov al, [esi + edx]
        cmp al, bl
        jne skip_print_snake
        mov al, [edi + edx]
        cmp al, al; //porównanie z y(AL zawiera y)
        jne skip_print_snake

        cmp dl, 0
        jz print_snake_head
}
printf("o");
_asm {
    jmp print_end

    print_snake_head :
}
printf("@");
_asm {
print_end:
    mov ch, 1; printed = 1

        skip_print_snake:
    inc dl
        jmp for_draw_snake_start

        for_draw_snake_end :
    cmp ch, 0
        jne for_draw_X_continue
}
printf(" ");
_asm {
    jmp for_draw_X_continue

    draw_print_border :
}
printf("#");
_asm {

for_draw_X_continue:
    inc bl
        jmp for_draw_X_start

        for_draw_X_end :
}
printf("\n");
_asm {
    inc al
    jmp for_draw_Y_start

    for_draw_Y_end :
    pop edi
        pop esi
        pop ebx
}
*/


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

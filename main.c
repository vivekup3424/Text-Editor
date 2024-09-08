#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <termio.h>
#include <stdlib.h>

struct termios original_termios;
void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}
void enableRawMode(){
    struct termios raw;
    tcgetattr(STDIN_FILENO, &original_termios);
    atexit(disableRawMode);

    raw = original_termios;
    raw.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
int main(){
    char c;
    while(read(fileno(stdin), &c, 1)){
        printf("%c#",c);
    }
    return 0;
}

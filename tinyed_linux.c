#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define MAX_SIZE 10000

char buffer[MAX_SIZE];
int pos = 0, len = 0;
char filename[256] = "untitled.txt";
int modified = 0;

struct termios orig_termios, raw_termios;

void init_terminal() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    raw_termios = orig_termios;
    raw_termios.c_lflag &= ~(ICANON | ECHO);
    raw_termios.c_cc[VMIN] = 0;
    raw_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);
}

void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void clear_screen() {
    printf("\x1b[2J\x1b[H");
    fflush(stdout);
}

void draw_ui() {
    clear_screen();
    printf("\x1b[7m%-70s\x1b[0m\n", "");
    printf("File: %s | %s\n\n", filename, modified ? "[Modified]" : "[Saved]");
    
    for (int i = 0; i < len; i++) {
        if (i == pos) printf("\x1b[7m");
        printf("%c", buffer[i]);
        if (i == pos) printf("\x1b[0m");
    }
    if (pos == len) printf("\x1b[7m \x1b[0m");
    fflush(stdout);
}

void save_file() {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Error saving file.\n");
        return;
    }
    fwrite(buffer, 1, len, f);
    fclose(f);
    modified = 0;
}

void open_file() {
    printf("\x1b[0m\x1b[?25h");
    restore_terminal();
    printf("Open file: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    
    FILE *f = fopen(filename, "r");
    if (f) {
        len = fread(buffer, 1, MAX_SIZE - 1, f);
        buffer[len] = 0;
        fclose(f);
    } else {
        len = 0;
    }
    pos = 0;
    modified = 0;
    init_terminal();
}

void save_as() {
    printf("\x1b[0m\x1b[?25h");
    restore_terminal();
    printf("Save as: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    init_terminal();
    save_file();
}

int main(int argc, char *argv[]) {
    if (argc > 1) strcpy(filename, argv[1]);
    
    FILE *f = fopen(filename, "r");
    if (f) {
        len = fread(buffer, 1, MAX_SIZE - 1, f);
        buffer[len] = 0;
        fclose(f);
    }
    
    init_terminal();
    printf("\x1b[?25l");
    
    while (1) {
        draw_ui();
        
        unsigned char c;
        if (read(STDIN_FILENO, &c, 1) > 0) {
            if (c == 27) {
                unsigned char seq[3];
                if (read(STDIN_FILENO, &seq[0], 1) > 0 && seq[0] == '[') {
                    if (read(STDIN_FILENO, &seq[1], 1) > 0) {
                        if (seq[1] == 'C' && pos < len) pos++;
                        else if (seq[1] == 'D' && pos > 0) pos--;
                    }
                }
            } else if (c == 19) {
                save_as();
            } else if (c == 15) {
                open_file();
            } else if (c == 27 || c == 3) {
                break;
            } else if (c == 127 || c == 8) {
                if (pos > 0) {
                    memmove(&buffer[pos - 1], &buffer[pos], len - pos);
                    pos--;
                    len--;
                    modified = 1;
                }
            } else if (c >= 32 && c < 127) {
                if (len < MAX_SIZE - 1) {
                    memmove(&buffer[pos + 1], &buffer[pos], len - pos);
                    buffer[pos] = c;
                    pos++;
                    len++;
                    modified = 1;
                }
            }
        }
    }
    
    printf("\x1b[?25h\x1b[0m");
    restore_terminal();
    clear_screen();
    return 0;
}

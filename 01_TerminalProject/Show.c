#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// char *s = "aaaaaaaaaaaaaaaaaaaaaaa\0aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

char** data;
// char *s = "aaaaaaaaaaaaaaaaaaaaaaa\0aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
int datalen;

int width = 20;
int height = 20;

int lineCount(char* fname) {
    FILE* file = fopen(fname, "r");
    char* line = NULL;
    size_t len = 0;
    size_t n;
    int i = 0;
    while ((n = getline(&line, &len, file)) != -1) {
        i ++;
    }
    fclose(file);
    return i;
}

void parseFile(char* fname) {
    FILE* file = fopen(fname, "r");
    size_t len=0;
    size_t n =0;
    int i = 0;

    int fileLen = lineCount(fname);
    data = calloc(fileLen, sizeof(char*));

    while (n != -1) {
        char* line=NULL;
        n = getline(&line, &len, file);
        if (line[n-1] == "\n"[0]) {
            line[n-1] = "\0"[0];
        }
        if (n > width) {
            line[width-2] = "\0"[0];
        }
        data[i] = line;
        i ++;
    }
    fclose(file);
    datalen = i;
}

void print(WINDOW* win, int from) {
    int rowCnt = height-2;
    if (rowCnt > datalen) {
        rowCnt = datalen;
    }
    if (from + rowCnt >= datalen) {
        from = datalen - rowCnt;
    }
    for (int i=0; i < rowCnt; i++) {
        if (i+from >= datalen) {
            break;
        }
        mvwaddstr(win, i+1, 1, data[i+from]);
    }
}

int main(int argc, char** argv){
    if (argc != 2) {
        fprintf(stderr, "wrong args counts");
        exit(1);
    }

    if (!initscr())
    {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(1);
    }

    curs_set(0);
    refresh();

    width = COLS-2;
    height = LINES-2;

    char* fname = argv[1];
    parseFile(fname);

    addstr(fname);

    int offsetx = (COLS - width) / 2;
    int offsety = (LINES - height) / 2;

    WINDOW *win = newwin(height, width, offsety, offsetx);


    int from = 0;
    bool loop = true;
    while (loop) {
        wclear(win);
        curs_set(0);

        box(win, 0, 0);
        print(win, from);
        wrefresh(win);

        char ch = getch();
        switch (ch)
        {
        case ' ':
            from ++;
            break;
        case 27:
            loop = false;
            break;
        }
    }

    delwin(win);
    endwin();
}
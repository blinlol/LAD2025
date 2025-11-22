#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROOMS 6
#define GRID (ROOMS * 2 + 1)

int visited[ROOMS][ROOMS];
char maze[GRID][GRID + 1];

void shuffle(int *arr, size_t n) {
    for (size_t i = n - 1; i > 0; --i) {
        size_t j = (size_t)(rand() % (int)(i + 1));
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

void carve_from(int r, int c) {
    visited[r][c] = 1;
    int dirs[4] = {0, 1, 2, 3};
    shuffle(dirs, 4);

    for (int i = 0; i < 4; ++i) {
        int dir = dirs[i];
        int nr = r;
        int nc = c;

        switch (dir) {
            case 0: nr = r - 1; break;
            case 1: nc = c + 1; break;
            case 2: nr = r + 1; break;
            case 3: nc = c - 1; break;
        }

        if (nr < 0 || nr >= ROOMS || nc < 0 || nc >= ROOMS) {
            continue;
        }
        if (visited[nr][nc]) {
            continue;
        }

        int gr = 2 * r + 1;
        int gc = 2 * c + 1;
        int ngr = 2 * nr + 1;
        int ngc = 2 * nc + 1;
        maze[(gr + ngr) / 2][(gc + ngc) / 2] = '.';
        carve_from(nr, nc);
    }
}

void init_maze(void) {
    for (int r = 0; r < GRID; ++r) {
        for (int c = 0; c < GRID; ++c) {
            maze[r][c] = '#';
        }
        maze[r][GRID] = '\0';
    }
    for (int r = 0; r < ROOMS; ++r) {
        for (int c = 0; c < ROOMS; ++c) {
            maze[2 * r + 1][2 * c + 1] = '.';
        }
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    init_maze();
    carve_from(0, 0);

    for (int r = 0; r < GRID; ++r) {
        puts(maze[r]);
    }
    return 0;
}


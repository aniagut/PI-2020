#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, s_x, s_y, e_x, e_y;
    scanf("%d %d %d %d %d", &n, &s_x, &s_y, &e_x, &e_y);

    if (e_x >= s_x && e_y >= s_y) {
        int size_x = e_x - s_x + 1;
        int size_y = e_y - s_y + 1;

        int* board_memblock = malloc(size_x * size_y * sizeof(*board_memblock));
        int** board = malloc(size_x * sizeof(*board));

        for (int i = 0; i < size_x; i++) {
            board[i] = board_memblock + i * size_y;
        }

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                int read;
                scanf("%d", &read);

                if (x >= s_x && y >= s_y && x <= e_x && y <= e_y) {
                    board[x - s_x][y - s_y] = read == 1 ? 0 : -1;
                }
            }
        }

        if (board[0][0] == -1 || board[size_x - 1][size_y - 1] == -1) {
            printf("0\n");
        }
        else {
            board[0][0] = 1;

            for (int x = 0; x < size_x; ++x) {
                for (int y = 0; y < size_y; ++y) {
                    if ((x != 0 || y != 0) && board[x][y] != -1) {
                        int new_val = 0;

                        if (x - 1 >= 0) {
                            new_val += board[x - 1][y] != -1 ? board[x - 1][y] : 0;
                            if (y - 1 >= 0) {
                                new_val += board[x - 1][y - 1] != -1 ? board[x - 1][y - 1] : 0;
                            }
                        }
                        if (y - 1 >= 0) {
                            new_val += board[x][y - 1] != -1 ? board[x][y - 1] : 0;
                        }

                        board[x][y] = new_val;
                    }
                }
            }

            printf("%d\n", board[size_x - 1][size_y - 1]);
        }

        free(board);
        free(board_memblock);
    }
    else {
        printf("0\n");
    }
}

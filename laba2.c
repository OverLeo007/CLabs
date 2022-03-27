//Соколов Лев Максимович КИ21-17 вар26

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAX_RANDOM_NUMBER 1000
#define MAX_ARRAY_LEN 5


int array_check(const int **array);

int **generate_array(int ar_row, int ar_col, int is_count);

int **upgrade_array(int **array, int ar_row, int ar_col);

int **transpose_array(int **array, int ar_row, int ar_col);

int **sort_array(int **array, int ar_row, int ar_col);

void print_array(int **array, int ar_row, int ar_col);

void free_array(int **array, int ar_row);

int input_int_check(char value_array[]);

int input_int();


int main(void) {
    int **array = NULL;
    int **upgraded_array = NULL;
    int **sorted_array = NULL;
    int n, m;


    system("chcp 65001 > nul");

    srand(time(NULL));

    while (1) {
        puts("1. Ввести n и m (n строк, m столбцов), для заполнения случайными числами");
        puts("2. Вывести исходный массив");
        puts("3. Вывести массив с n+1 строкой с суммами");
        puts("4. Вывести массив с n+1 строкой с суммами, отсоритрованный по этим суммам");
        puts("5. Выйти");


        int menu_variant = input_int();
        switch (menu_variant) {
            case 1:
                puts("Введите n (кол-во строк):");
                n = input_int();
                puts("Введите m (кол-во столбцов):");
                m = input_int();
                if (n < 1 || m < 1) {
                    puts("[ERR]Некорректное значение!\n");
                    break;
                }
                if (array != NULL) free_array(array, n);
                array = generate_array(n, m, 0);
                upgraded_array = upgrade_array(array, n, m);
                sorted_array = sort_array(upgraded_array, n + 1, m);
                puts("Массив сгенерирован");
                break;

            case 2:
                if (array_check(array)) break;
                puts("Исходный массив:");
                print_array(array, n, m);
                break;
            case 3:
                if (array_check(array)) break;
                puts("Массив с n+1 строкой с суммами:");
                print_array(upgraded_array, n + 1, m);
                break;
            case 4:
                if (array_check(array)) break;
                puts("Массив с n+1 строкой с суммами, с отсортированными по этим суммам столбцами:");
                print_array(sorted_array, n + 1, m);
                break;
            case 5:
                free(array);
                return 0;
            default:
                puts("[ERR]Такого варианта выбора нет\n");
                break;
        }
    }
}


int array_check(const int **array) {
    if (array == NULL) {

        puts("[ERR]Массив еще не сгенерирован\n");
        return 1;
    } else {
        return 0;
    }
}


int **generate_array(int ar_row, int ar_col, int is_count) {
    int **array = malloc((ar_row + 1) * (sizeof(int *)));
    int counter = 0;

    for (int i = 0; i < ar_row + 1; ++i) {
        array[i] = malloc(ar_col * sizeof(int));
        for (int j = 0; j < ar_col; ++j) {
            if (i != ar_row) {
                if (is_count) {
                    array[i][j] = ++counter;
                } else {
                    array[i][j] = rand() % MAX_RANDOM_NUMBER;
                }
            } else {
                array[i][j] = -1;
            }
        }
    }
    return array;
}


int **upgrade_array(int **array, int ar_row, int ar_col) {
    int *sum_array = malloc(ar_col * sizeof(int));
    int **up_array = malloc((ar_row + 1) * (sizeof(int *)));

    for (int i = 0; i < ar_row + 1; ++i) {
        up_array[i] = malloc(ar_col * sizeof(int));
        for (int j = 0; j < ar_col; ++j) {
            up_array[i][j] = array[i][j];
        }
    }

    for (int i = 0; i < ar_col; ++i) {
        sum_array[i] = 0;
    }
    for (int i = 0; i < ar_row; ++i) {
        for (int j = 0; j < ar_col; ++j) {
            sum_array[j] += up_array[i][j];
        }
    }
    for (int i = 0; i < ar_col; ++i) {
        up_array[ar_row][i] = sum_array[i];
    }
    return up_array;
}


int **transpose_array(int **array, int ar_row, int ar_col) {
    int **transposed_array = malloc((ar_col) * (sizeof(int *)));

    for (int i = 0; i < ar_col; ++i) {
        transposed_array[i] = malloc((ar_row) * sizeof(int));
        for (int j = 0; j < ar_row; ++j) {
            transposed_array[i][j] = array[j][i];
        }
    }
    return transposed_array;
}


int **sort_array(int **array, int ar_row, int ar_col) {
    int *swap;
    int **trans_array = transpose_array(array, ar_row, ar_col);
    for (int i = 0; i < ar_col - 1; i++) {
        for (int j = 0; j < ar_col - i - 1; j++) {
            if (trans_array[j][ar_row - 1] < trans_array[j + 1][ar_row - 1]) {
                swap = trans_array[j];
                trans_array[j] = trans_array[j + 1];
                trans_array[j + 1] = swap;
            }
        }
    }

    trans_array = transpose_array(trans_array, ar_col, ar_row);
    return trans_array;
}


void free_array(int **array, int ar_row) {
    for (int i = 0; i < ar_row; ++i) {
        free(array[i]);
    }
    free(array);
}


void print_array(int **array, int ar_row, int ar_col) {
    for (int i = 0; i < ar_row; ++i) {
        for (int j = 0; j < ar_col; ++j) {
            if (array[i][j] > -1) {
                printf("%-5d ", array[i][j]);
            }
        }
        if (array[i][0] > -1) {
            printf("\n");
        }
    }
    printf("\n");
}


int input_int() {
    char str_array_len[MAX_ARRAY_LEN];
    fgets(str_array_len, MAX_ARRAY_LEN, stdin);
    fflush(stdin);
    if (input_int_check(str_array_len) || strlen(str_array_len) == 1) {
        return -1;
    }

    return strtol(str_array_len, NULL, 10);
}


int input_int_check(char value_array[]) {
    for (int i = 0; i < strlen(value_array) - 1; ++i) {
        if ((value_array[i] < '0') || (value_array[i] > '9')) {
            return 1;
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>


#define MAX_RANDOM_NUMBER 1000
#define MAX_ARRAY_LEN 5


int array_check(const int *array);

int *generate_array(int ar_len);

int *sort_array(int *array, int ar_len);

void print_array(const int *array, int ar_len);

int input_int_check(char value_array[]);

int input_int();

float get_expected_value(const int *array, int ar_len);

float get_dispersion(const int *array, float exp_val, int ar_len);

float get_standard_deviation(float dispersion);

int get_median(int *array, int ar_len);

int main() {
    int *array = NULL;

    int array_len;
    int median;
    float math_wait;
    float dispersion;
    int is_dispersion;
    float standard_deviation;

    system("chcp 65001 > nul");

    srand(time(NULL));

    while (1) {
        puts("1. Ввести длину массива, для заполнения случайными числами");
        puts("2. Вывести математическое ожидание");
        puts("3. Вывести дисперсию");
        puts("4. Вывести среднеквадратическое отклонение");
        puts("5. Вывести медиану");
        puts("6. Вывести исходный массив");
        puts("7. Выйти");



        int menu_variant = input_int();
        switch (menu_variant) {
            case 1:
                puts("Введите длину массива:");
                array_len = input_int();
                if (array_len == -1) {
                    puts("[ERR]Некорректное значение!\n");
                    break;
                }
                if (!(array == NULL)) free(array);
                array = generate_array(array_len);
                is_dispersion = 0;
                puts("Массив сгенерирован");
                break;

            case 2:
                if (array_check(array)) break;
                math_wait = get_expected_value(array, array_len);
                printf("Математическое ожидание: %f\n", math_wait);
                break;
            case 3:
                if (array_check(array)) break;
                dispersion = get_dispersion(array, math_wait, array_len);
                printf("Диперсия: %f\n", dispersion);
                is_dispersion = 1;
                break;
            case 4:
                if (array_check(array)) break;
                if (!is_dispersion) {
                    dispersion = get_dispersion(array, math_wait, array_len);
                }

                if (dispersion >= 0) {
                    printf("Среднеквадратическое отклонение %f\n", get_standard_deviation(dispersion));
                } else {
                    puts("Среднеквадратическое отклонение посчитать невозможно, так как дисперсия отрицательна");
                }
                break;
            case 5:
                if (array_check(array)) break;
                median = get_median(array, array_len);
                printf("Медиана %d\n", median);
                break;
            case 6:
                if (array_check(array)) break;
                puts("Исходный массив:");
                print_array(array, array_len);
                puts("");
                break;
            case 7:
                free(array);
                return 0;
            default:
                puts("[ERR]Такого варианта выбора нет\n");
                break;
        }
    }
}


int array_check(const int *array) {
    if (array == NULL) {

        puts("[ERR]Массив еще не сгенерирован\n");
        return 1;
    } else {
        return 0;
    }
}


int *generate_array(int ar_len) {
    int *array = malloc(ar_len * sizeof(int));
    for (int i = 0; i < ar_len; ++i) {
        array[i] = rand() % MAX_RANDOM_NUMBER * (int) pow(-1, rand());
//        array[i] = rand() % MAX_RANDOM_NUMBER;
    }
    return array;

}

int *sort_array(int *array, int ar_len) {
    int swap;
    for (int i = 0; i < ar_len - 1; i++) {
        for (int j = 0; j < ar_len - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap = array[j];
                array[j] = array[j + 1];
                array[j + 1] = swap;
            }
        }
    }
    return array;
}

void print_array(const int *array, int ar_len) {
    for (int i = 0; i < ar_len; ++i) {
        printf("%d ", array[i]);
    }
}


int input_int() {
    char str_array_len[MAX_ARRAY_LEN];
    fgets(str_array_len, MAX_ARRAY_LEN, stdin);
    fflush(stdin);
    if (!(input_int_check(str_array_len))
        || strlen(str_array_len) == 1) {
        return -1;
    }

    return strtol(str_array_len, NULL, 10);
}


int input_int_check(char value_array[]) {
    for (int i = 0; i < strlen(value_array) - 1; ++i) {
        if ((value_array[i] < '0') || (value_array[i] > '9')) {
            return 0;
        }
    }
    return 1;
}

float get_expected_value(const int *array, int ar_len) {
    long int temp_sum = 0;
    for (int i = 0; i < ar_len; ++i) {
        temp_sum += array[i];
    }
    return ((1.f / (float) ar_len) * temp_sum);
}

float get_dispersion(const int *array, float exp_val, int ar_len) {
    float disp_sum = 0;
    for (int i = 0; i < ar_len; ++i) {
        disp_sum += (float) array[i] - exp_val;
    }
    return disp_sum / (float) (ar_len - 1);
}

float get_standard_deviation(float dispersion) {
    return sqrt((double) dispersion);
}

int get_median(int *array, int ar_len) {
    int *sorted_array = malloc(ar_len * sizeof(int));
    for (int i = 0; i < ar_len; ++i) {
        sorted_array[i] = array[i];
    }

    sorted_array = sort_array(sorted_array, ar_len);
    if (ar_len % 2 == 0) {
        return 0.5 * (sorted_array[ar_len / 2] + sorted_array[ar_len / 2 - 1]);
    } else {
        return sorted_array[ar_len / 2];
    }
}
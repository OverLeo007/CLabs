//Демёхина Арина КИ21-17/1b p1v22

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define MAX_RANDOM_NUMBER 41
#define MAX_ARRAY_LEN 5


int array_check(const int *array);

int *generated_array(int ar_len);

void print_array(const int *array, int ar_len);

void print_leo_array(const int *array, int ar_len);

void print_mult_3(const int *array, int ar_len);

int get_leonardo(int n);

int check_entry(int *array, int ar_len, int elem);

int *leonardo_array(int *array, int ar_len);

int input_int_check(char value_array[]);

int input_int();



int main() {
    int *array = NULL;
    int *ar_leonardo = NULL;
    int array_len;

    system("chcp 65001 > nul");

    srand(time(NULL));


    while (1) {
        puts("1. Задать длину массива");
        puts("2. Вычислить и вывести получившуюся последовательность чисел Леонардо");
        puts("3. Вывести числа новой последовательности кратные трём");
        puts("4. Вывести исходный массив");
        puts("5. Выйти");


        int menu_variant = input_int();
        switch (menu_variant) {
            case 1:
                puts("Введите длину массива:");
                array_len = input_int();
                if (array_len <= 1) {
                    puts("[ERR]Некорректное значение\n");
                    break;
                }
                if (!(array == NULL)) {
                    free(ar_leonardo);
                    free(array);
                }
                array = generated_array(array_len);
                puts("Массив сгенерирован");
                break;

            case 2:
                if (array_check(array)) break;
                ar_leonardo = leonardo_array(array, array_len);
                puts("Массив чисел Леонардо:");
                print_leo_array(ar_leonardo, array_len);
                puts("");
                break;
            case 3:
                if (array_check(ar_leonardo)) break;
                puts("Числа Леонардо, кратные трем:");
                print_mult_3(ar_leonardo, array_len);
                puts("");
                break;
            case 4:
                if (array_check(array)) break;
                puts("Исходный массив:");
                print_array(array, array_len);
                puts("");
                break;
            case 5:
                free(array);
                free(ar_leonardo);
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


int *generated_array(int ar_len) {
    int *array = malloc(ar_len * sizeof(int));
    for (int i = 0; i < ar_len; ++i) {
        array[i] = rand() % MAX_RANDOM_NUMBER;
    }
    return array;

}


int check_entry(int *array, int ar_len, int elem){
    for (int i = 0; i < ar_len; ++i){
        if (array[i] == elem){
            return 1;
        }
    }
    return 0;
}


int *leonardo_array(int *array, int ar_len) {
    int leo_ar_len = 0;
    int new_leo;
    int *leo_array = malloc(ar_len * sizeof(int));
    for (int i = 0; i < ar_len; ++i) {
        new_leo = get_leonardo(array[i]);
        if (!check_entry(leo_array, leo_ar_len, new_leo)){
            leo_array[i] = new_leo;
        } else {
            leo_array[i] = 0;
        }
        leo_ar_len++;
    }
    return leo_array;
}


int get_leonardo(int n){
    if (n == 0 || n == 1){
        return 1;
    }
    else {
        return get_leonardo(n - 1) + get_leonardo(n - 2) + 1;
    }
}


void print_array(const int *array, int ar_len) {
    for (int i = 0; i < ar_len; ++i) {
        printf("%d ", array[i]);
    }
}


void print_leo_array(const int *array, int ar_len){
    for (int i = 0; i < ar_len; ++i) {
        if (array[i] != 0){
            printf("%d ", array[i]);
        }
    }
}


void print_mult_3(const int *array, int ar_len){
    for (int i = 0; i < ar_len; ++i) {
        if (array[i] != 0 && array[i] % 3 == 0){
            printf("%d ", array[i]);
        }
    }
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
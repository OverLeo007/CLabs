#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_int();

int input_int_check(char value_array[]);

int get_gcd(int num1, int num2);

int main(void) {
    int menu_variant;
    int num1, num2;

    system("chcp 65001 > nul");

    while (1){
        puts("1. Ввести два числа для отыскания НОД");
        puts("2. Завершить программу");

        menu_variant = input_int();
        switch (menu_variant) {
            case 1:
                num1 = input_int();
                num2 = input_int();
                if (num1 == -1 || num2 == -1){
                    puts("Введены некорректные значения");
                    break;
                }
                printf("НОД: %d\n", get_gcd(num1, num2));
                break;
            case 2:
                return 0;
            default:
                puts("Такого варианта выбора нет");
                break;
        }


    }
}


int get_gcd(int num1, int num2){
    if (num1 == 0) return num2;
    return get_gcd(num2 % num1, num1);
}



int input_int() {
    char str_array_len[9];
    fgets(str_array_len, 9, stdin);
    fflush(stdin);
    if (input_int_check(str_array_len) ||
        strlen(str_array_len) == 1) {
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "proto.h"



int main() {
    char *text = NULL;
    char *clear_text = NULL;
    char *enc_text = NULL;

    system("chcp 65001 > nul");

    while (1) {
        puts("1. Ввести путь до файла с текстом для зашифровки");
        puts("2. Вывести исходный текст");
        puts("3. Вывести текст очищенный от знаков"
             " препинания и лишних пробелов ");
        puts("4. Вывести зашифрованный текст");
        puts("5. Сохранить зашифрованный текст в файл");
        puts("6. Выход");


        int menu_variant = input_int();
        switch (menu_variant) {
            case 1:

                if (text != NULL) {
                    free(text);
                    free(clear_text);
                    free(enc_text);
                };

                puts("Введите путь до файла");
                text = read(input_string());
                if (text[0] == '\0') {
                    puts("[ERR]Некорректное значение!\n");
                    break;
                }

                clear_text = reformat_text(text);
                enc_text = do_encrypt(clear_text);
                puts("Текст успешно считан");
                break;

            case 2:
                if (text_check(text)) break;
                puts("Исходный текст:");
                printf("%s\n", text);
                break;
            case 3:
                if (text_check(text)) break;
                puts("Текст очищенный от знаков"
                     " препинания и лишних пробелов:");
                printf("%s\n", clear_text);
                break;
            case 4:
                if (text_check(text)) break;
                puts("Зашифрованный текст:");
                printf("%s\n", enc_text);
                break;
            case 5:
                if (text_check(text)) break;
                puts("Введите путь до файла");
                write(input_string(), enc_text);
                puts("Файл сохранен");
                break;
            case 6:
                free(text);
                free(clear_text);
                free(enc_text);
                return 0;
            default:
                puts("[ERR]Такого варианта выбора нет\n");
                break;
        }
    }
}


int text_check(const char *text) {
    if (text == NULL) {

        puts("[ERR]Текст еще не считан");
        return 1;
    } else {
        return 0;
    }
}


char *input_string() {
    size_t size = 80;
    size_t curr = 0;
    char *buffer = malloc(size);
    while (fgets(buffer + curr, size - curr, stdin)) {
        if (strchr(buffer + curr, '\n')) {
            buffer[strcspn(buffer, "\n")] = '\0';
            return buffer;
        }

        curr = size - 1;
        size *= 2;
        char *tmp = realloc(buffer, size);
        free(buffer);
        buffer = tmp;
    }

    return buffer;
}

int input_int() {
    char str_array_len[5];
    fgets(str_array_len, 5, stdin);
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


char *read(char *filename) {
    char *text = NULL;
    long long int size;
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fseek(file, 0, SEEK_SET);

        text = calloc(size + 1, sizeof(char));
        fread(text, 1, size, file);
        text[size] = '\0';
    } else return "\0";
    fclose(file);
    return text;
}

void write(char *filename, char *text) {
    FILE *file;
    file = fopen(filename, "w");
    fprintf(file, text);
    fclose(file);
}

char *reformat_text(char *text) {
    int new_size = 0;
    int index = 0;
    char *ref_text = NULL;

    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == 32 || text[i] == 10
            || text[i] == 0 || is_let(text[i])
            || is_num(text[i])) {
            new_size++;
        }
    }
    ref_text = calloc(new_size, sizeof(char));
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == 32 || text[i] == 10
            || text[i] == 0 || is_let(text[i])
            || is_num(text[i])) {
            if (text[i] == 32 && text[i + 1] == 32) continue;
            if (65 <= text[i] && text[i] <= 90)
                ref_text[index] = (char) (text[i] + 32);
            else ref_text[index] = (char) (text[i]);
            index++;
        }
    }
    return ref_text;
}


char *do_encrypt(char *text) {
    char matrix1[5][5] = {'e', 'n', 'c', 'r', 'y',
                          'p', 't', 'a', 'b', 'd',
                          'f', 'g', 'h', 'i', 'j',
                          'k', 'l', 'm', 'o', 's',
                          'u', 'v', 'w', 'x', 'z'};

    char matrix2[5][5] = {'w', 'o', 'r', 'd', 's',
                          'a', 'b', 'c', 'e', 'f',
                          'g', 'h', 'i', 'j', 'k',
                          'l', 'm', 'n', 'p', 't',
                          'u', 'v', 'x', 'y', 'z'};
    char *bigramm = calloc(2, sizeof(char));
    char *enc_bigramm = calloc(2, sizeof(char));
    char *enc_text = calloc(strlen(text), sizeof(char));
    int index = 0;
    while (text[index] != '\0') {

        if (text[index] == 32 || text[index] == 10 ||
            text[index] == 0 || text[index] == 113 || is_num(text[index])) {
            enc_text[index] = text[index];
            index++;
            continue;
        }

        int counter = 1;
        while (1) {
            if ((is_let(text[index + counter]) &&
                 text[index + counter] != 'q') || text[index + counter] == '\0')
                break;
            enc_text[index + counter] = text[index + counter];
            counter++;
        }

        if (text[index + counter] == '\0') {
            enc_text[index] = text[index];
            break;
        }

        bigramm[0] = text[index];
        bigramm[1] = text[index + counter];

        enc_bigramm = replace(matrix1, matrix2, bigramm);
        enc_text[index] = enc_bigramm[0];
        enc_text[index + counter] = enc_bigramm[1];
        index += counter + 1;
    }
    free(bigramm);
    free(enc_bigramm);
    return enc_text;
}

char *replace(const char matrix1[5][5], const char matrix2[5][5],
              const char bigramm[2]) {
    int fr, fc, sr, sc;
    char *res_bigramm = calloc(2, sizeof(char));

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            if (matrix1[row][col] == bigramm[0]) {
                fr = row;
                fc = col;
            }
            if (matrix2[row][col] == bigramm[1]) {
                sr = row;
                sc = col;
            }
        }
    }
    if (fc == sc) {
        res_bigramm[0] = matrix1[sr][sc];
        res_bigramm[1] = matrix2[fr][fc];
    } else {
        res_bigramm[0] = matrix1[fr][sc];
        res_bigramm[1] = matrix2[sr][fc];
    }

    return res_bigramm;
}

int is_let(char ch) {
    if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) return 1;
    return 0;
}

int is_num(char ch) {
    if ('0' <= ch && ch <= '9') return 1;
    return 0;
}
int text_check(const char *text);

char *input_string();

int input_int();

int input_int_check(char value_array[]);

char *read(char *filename);

void write(char *filename, char *text);

char *reformat_text(char *text);

char *do_encrypt(char *text);

char *replace(const char matrix1[5][5], const char matrix2[5][5],
              const char bigramm[2]);

int is_let(char ch);

int is_num(char ch);
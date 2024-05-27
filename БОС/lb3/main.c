#include <stdio.h>
#include <string.h>

#define PAGE_HEIGHT 5
#define LINE_WIDTH 45

void print_file(FILE *fp) {
    char buffer[LINE_WIDTH + 1]; // Дополнительный символ для '\0'

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        int len = strlen(buffer);
        int lines_to_print = (len + LINE_WIDTH - 1) / LINE_WIDTH; // Определяем количество строк для вывода

        for (int i = 0; i < lines_to_print; ++i) {
            printf("%.45s\n", buffer + i * LINE_WIDTH); // Выводим по 45 символов из буфера
        }

        for (int i = lines_to_print; i < PAGE_HEIGHT; ++i) {
            if (fgets(buffer, sizeof(buffer), fp) != NULL) {
                len = strlen(buffer);
                lines_to_print = (len + LINE_WIDTH - 1) / LINE_WIDTH;
                for (int j = 0; j < lines_to_print; ++j) {
                    printf("%.45s\n", buffer + j * LINE_WIDTH); // Выводим остальные строки
                }
            } else {
                return; // Достигнут конец файла
            }
        }

        int c;
        printf("\nPress 'q' to quit or Enter to continue: ");
        c = getchar();
        if (c == 'q' || c == 'Q') {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    print_file(file);
    fclose(file);

    return 0;
}

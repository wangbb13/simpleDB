#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct InputBuffer_t {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
};
typedef struct InputBuffer_t InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

void print_prompt() {
    printf("db > ");
}

ssize_t getline(char **__lineptr, size_t *n, FILE *stream) {
    char *lineptr = *__lineptr;
    int len_max = 10, length = 0, remain = len_max, ch;
    char *ptr;
    if (lineptr == NULL) {
        lineptr = malloc(len_max);
    } else if (*n < len_max) {
        char *temptr = realloc(lineptr, len_max);
        if (temptr == NULL) {
            free(lineptr);
            return -1;
        }
        lineptr = temptr;
    }
    if (lineptr == NULL)
        return -1;
    ptr = lineptr;
    while (true) {
        ch = fgetc(stream);
        if (ch == EOF)
            break;
        if (-- remain < 2) {
            remain = len_max;
            char *temptr = realloc(lineptr, len_max *= 2);
            if (temptr == NULL) {
                free(lineptr);
                return -1;
            }
            *n = len_max;
            ptr = temptr + (ptr - lineptr);
            lineptr = temptr;
        }
        length ++;
        if (ch == '\n') {
            break;
        } else {
            *ptr++ = ch;
        }
    }
    *ptr = '\0';
    *__lineptr = lineptr;
    return length;
}

void read_input(InputBuffer *input_buffer) {
    ssize_t read_len = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (read_len > 0) {
        input_buffer->input_length = read_len - 1;
    } else {
        if (input_buffer->buffer == NULL) {
            input_buffer->buffer = malloc(1);
            if (input_buffer->buffer == NULL) {
                exit(EXIT_FAILURE);
            }
            input_buffer->buffer_length = 1;
            input_buffer->buffer[0] = '\0';
        }
        input_buffer->input_length = 0;
    }
}

int main(int argc, char const *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, "exit") == 0 || strcmp(input_buffer->buffer, "quit") == 0) {
            printf("bye.\n");
            system("pause");
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command : %s \n", input_buffer->buffer);
        }
    }
}
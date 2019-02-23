#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Definition of some types

struct InputBuffer_t {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
};
typedef struct InputBuffer_t InputBuffer;

enum MetaCommandResult_t {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
};
typedef enum MetaCommandResult_t MetaCommandResult;

enum PrepareResult_t {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
};
typedef enum PrepareResult_t PrepareResult;

enum StatementType_t {
    STATEMENT_INSERT,
    STATEMENT_SELECT
};
typedef enum StatementType_t StatementType;

struct Statement_t {
    StatementType type;
};
typedef struct Statement_t Statement;

// End Definition of some types


// Definition of functions

void exit_db();
void print_prompt();
InputBuffer* new_input_buffer();
ssize_t getline(char **__lineptr, size_t *n, FILE *stream);
void read_input(InputBuffer *input_buffer);

MetaCommandResult do_meta_command(InputBuffer *input_buffer);
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);
void execute_statement(Statement *statement);

// End Definition of functions

int main(int argc, char const *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        // handle meta commands, e.g. .exit
        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                printf("Unrecognized command : %s\n", input_buffer->buffer);
                continue;
            }
        }

        // handle SQL commands
        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            printf("Unrecognized keyword at start of %s\n", input_buffer->buffer);
            continue;
        }

        execute_statement(&statement);
        printf("Executed.\n");
    }
}


// implementation of functions

void print_prompt() {
    printf("db > ");
}

void exit_db() {
    printf("bye.\n");
    system("pause");
    exit(EXIT_SUCCESS);
}

InputBuffer* new_input_buffer() {
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
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

MetaCommandResult do_meta_command(InputBuffer *input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        exit_db();
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strncmp(input_buffer->buffer, "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement *statement) {
    switch (statement->type) {
    case (STATEMENT_INSERT):
        printf("This is where we would do an insert.\n");
        break;
    case (STATEMENT_SELECT):
        printf("This is where we would do a select.\n");
        break;
    }
}
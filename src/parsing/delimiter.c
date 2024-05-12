#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int delim(char *delimiters, char ch) {
    while (*delimiters) {
        if (*delimiters == ch) {
            return 1;
        }
        delimiters++;
    }
    return 0;
}

char **split_string(char *word) {
    int db_quote_open = 0;
    int s_quote_open = 0;
    int i = 0;
    char *delimiter = "><|";

    // Determine the maximum number of substrings
    int max_substrings = 1;
    while (word[i]) {
        if (delim(delimiter, word[i]) && (!s_quote_open && !db_quote_open)) {
            max_substrings++;
        }
        if (word[i] == '"' || word[i] == '\'') {
            if (word[i] == '\'') {
                s_quote_open = !s_quote_open;
            } else {
                db_quote_open = !db_quote_open;
            }
        }
        i++;
    }

    // Allocate memory for the container
    char **container = malloc(max_substrings * sizeof(char *));
    if (container == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int substring_index = 0;
    int start_index = 0;

    // Iterate through the input string
    for (i = 0; word[i]; i++) {
        if (delim(delimiter, word[i]) && (!s_quote_open && !db_quote_open)) {
            // Found a delimiter, create a substring
            int length = i - start_index;
            container[substring_index] = malloc((length + 1) * sizeof(char));
            if (container[substring_index] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(EXIT_FAILURE);
            }
            strncpy(container[substring_index], word + start_index, length);
            container[substring_index][length] = '\0';
            substring_index++;
            start_index = i + 1;
        }
        if (word[i] == '"' || word[i] == '\'') {
            if (word[i] == '\'') {
                s_quote_open = !s_quote_open;
            } else {
                db_quote_open = !db_quote_open;
            }
        }
    }

    // Copy the last substring
    int length = i - start_index;
    container[substring_index] = malloc((length + 1) * sizeof(char));
    if (container[substring_index] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strncpy(container[substring_index], word + start_index, length);
    container[substring_index][length] = '\0';

    // Add NULL terminator to indicate end of the container
    container[max_substrings - 1] = NULL;

    return container;
}

int main() {
    char *input = "test>ok";
    char **result = split_string(input);

    int i = 0;
    while (result[i] != NULL) {
        printf("container[%d] = %s\n", i, result[i]);
        free(result[i]); // Free memory allocated for each substring
        i++;
    }
    free(result); // Free memory allocated for the container

    return 0;
}

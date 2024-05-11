#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to check if a character is a delimiter
int is_delimiter(char ch, const char *delimiters) {
    while (*delimiters) {
        if (ch == *delimiters)
            return 1;
        delimiters++;
    }
    return 0;
}

// Function to parse the input word into an array of strings
char **parse_words(char *word, const char *delimiters, int *num_tokens) {
    int db_quote_open = 0;
    int s_quote_open = 0;
    int word_count = 0;
    int i = 0;

    // Allocate an initial array of string pointers
    char **tokens = (char **)malloc(sizeof(char *) * 10); // Start with a small size, can expand if needed
    if (!tokens) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    char *current_token = NULL;
    while (word[i]) {
        // Check for single or double quotes to toggle quote state
        if (word[i] == '"' || word[i] == '\'') {
            if (word[i] == '\'')
                s_quote_open = !s_quote_open;
            else
                db_quote_open = !db_quote_open;
        }

        // Check if we encounter a delimiter outside of quotes
        if (is_delimiter(word[i], delimiters) && !s_quote_open && !db_quote_open) {
            // Terminate the current token and add it to the tokens array
            if (current_token) {
                current_token[word + i - current_token] = '\0'; // Null-terminate the token
                tokens[word_count++] = current_token;
                current_token = NULL;
            }

            // Handle consecutive identical delimiters like "><"
            if (word[i + 1] == word[i] && word[i] != '|') {
                // Allocate memory for the consecutive delimiter
                current_token = (char *)malloc(3); // Assuming we need two characters + null terminator
                if (!current_token) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                sprintf(current_token, "%c%c", word[i], word[i]); // Store the consecutive delimiter
                tokens[word_count++] = current_token;
                i++; // Skip the next character since it's part of the delimiter
            } else {
                // Allocate memory for the single delimiter
                current_token = (char *)malloc(2); // Assuming we need one character + null terminator
                if (!current_token) {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                sprintf(current_token, "%c", word[i]); // Store the single delimiter
                tokens[word_count++] = current_token;
            }
        } else {
            // If not a delimiter, append character to the current token
            if (!current_token) {
                // Start a new token
                current_token = word + i;
            }
        }

        i++;
    }

    // If there's a remaining token after the loop ends, add it to the tokens array
    if (current_token) {
        tokens[word_count++] = current_token;
    }

    // Set the number of tokens
    *num_tokens = word_count;

    return tokens;
}

int main() {
    char *input_word = "Hello>world|'with|quotes'";
    const char *delimiters = "><|";
    int num_tokens;

    char **tokens = parse_words(input_word, delimiters, &num_tokens);

    printf("Parsed Tokens:\n");
    for (int i = 0; i < num_tokens; i++) {
        printf("%s\n", tokens[i]);
        free(tokens[i]); // Free each token after printing
    }

    free(tokens); // Free the tokens array

    return 0;
}

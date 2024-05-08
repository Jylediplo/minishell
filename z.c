#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** split_string(const char *str, int *count)
{
    int max_tokens = 10;
    char **tokens = (char **)malloc(max_tokens * sizeof(char *));
    if (!tokens)
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    const char *delimiters = "<|>";
    const char *start = str;
    const char *end = str;
    int index = 0;
    while (*end != '\0')
    {
        if (strchr(delimiters, *end) != NULL)
        {
            if (start != end)
            {
                int length = end - start;
                tokens[index] = (char *)malloc((length + 1) * sizeof(char));
                strncpy(tokens[index], start, length);
                tokens[index][length] = '\0';
                index++;
                if (index >= max_tokens)
                {
                    printf("Too many tokens, increase max_tokens\n");
                    exit(EXIT_FAILURE);
                }
            }
            if ((*end == '<' || *end == '>') && (*(end + 1) == *end))
            {
                char double_delimiter[3];
                double_delimiter[0] = *end;
                double_delimiter[1] = *end;
                double_delimiter[2] = '\0';
                tokens[index] = (char *)malloc(3 * sizeof(char));
                strncpy(tokens[index], double_delimiter, 3);
                index++;
                if (index >= max_tokens)
                {
                    printf("Too many tokens, increase max_tokens\n");
                    exit(EXIT_FAILURE);
                }
                start = end + 2;
                end++;
            }
            else
            {
                char delimiter[2];
                delimiter[0] = *end;
                delimiter[1] = '\0';
                tokens[index] = (char *)malloc(2 * sizeof(char));
                strncpy(tokens[index], delimiter, 2);
                index++;
                if (index >= max_tokens)
                {
                    fprintf(stderr, "Too many tokens, increase max_tokens\n");
                    exit(EXIT_FAILURE);
                }
                start = end + 1;
            }
        }
        end++;
    }
    if (start != end) {
        int length = end - start;
        tokens[index] = (char *)malloc((length + 1) * sizeof(char));
        strncpy(tokens[index], start, length);
        tokens[index][length] = '\0';
        index++;
    }
    *count = index;
    return tokens;
}

void free_tokens(char **tokens, int count)
{
    for (int i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

int main() {
    const char *input = "<<>>oui<<";
    int token_count = 0;
    char **tokens = split_string(input, &token_count);
    
    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++)
    {
        printf("%s\n", tokens[i]);
    }
    free_tokens(tokens, token_count);

    return 0;
}

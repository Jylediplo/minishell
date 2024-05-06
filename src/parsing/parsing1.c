#include "../../includes/minishell.h"

typedef struct s_quote
{
    int input_length;
    int output_index;
    int quote_open;
    int i;
    char current_quote;
    char *output;
} t_quote;

void init_cmd(t_quote *cmd, char *command)
{
    cmd->input_length = (int)ft_strlen(command);
    cmd->i = 0;
    cmd->quote_open = 0;
    cmd->output_index = 0;
    cmd->output = malloc(sizeof(char) * (cmd->input_length + 1));
    if (!cmd->output)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}
void current_is_quote(t_quote *cmd, char *command)
{
    if (!cmd->quote_open)
    {
        cmd->quote_open = 1;
        cmd->current_quote = command[cmd->i];
    }
    else if (cmd->current_quote == command[cmd->i])
        cmd->quote_open = 0;
    else
        cmd->output[cmd->output_index++] = command[cmd->i];
}

void current_is_not_quote(t_quote *cmd, char *command)
{
    if (cmd->quote_open)
    {
        cmd->output[cmd->output_index++] = command[cmd->i];
    }
    else if (command[cmd->i] != ' ')
    {
        cmd->output[cmd->output_index++] = command[cmd->i];
    }
    else
    {
        if (cmd->output_index > 0 && cmd->output[cmd->output_index - 1] != ' ')
        {
            cmd->output[cmd->output_index++] = command[cmd->i];
        }
    }
}

char *manage_quotes(char *command)
{
    t_quote cmd;

    init_cmd(&cmd, command);    
    while (cmd.i < cmd.input_length)
    {
        if (command[cmd.i] == '"' || command[cmd.i] == '\'')
            current_is_quote(&cmd, command);
		else
           current_is_not_quote(&cmd, command);
		cmd.i++;
    }
    if (cmd.quote_open)
    {
        free(cmd.output);
        printf("Error: Quote not properly closed.\n");
        return NULL;
    }
    cmd.output[cmd.output_index] = '\0';
	return (cmd.output);
}

void split_words(char *command, char ***words, int *num_words)
{
    int len = strlen(command);
    *num_words = 0;
    int in_quote = 0;
    int word_start = 0;
    int i;

    // Counting the number of words
    for (i = 0; i < len; i++)
    {
        if (command[i] == '"' || command[i] == '\'')
            in_quote = !in_quote;
        else if (!in_quote && (command[i] == ' ' || command[i] == '\t'))
        {
            if (i > word_start)
                (*num_words)++;
            word_start = i + 1;
        }
    }
    if (i > word_start && !in_quote)
        (*num_words)++;

    // Allocating memory for words array
    *words = malloc((*num_words) * sizeof(char *));
    if (*words == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Extracting words
    *num_words = 0;
    in_quote = 0;
    word_start = 0;
    for (i = 0; i < len; i++)
    {
        if (command[i] == '"' || command[i] == '\'')
        {
            in_quote = !in_quote;
        }
        else if (!in_quote && (command[i] == ' ' || command[i] == '\t'))
        {
            if (i > word_start)
            {
                (*words)[*num_words] = (char *)malloc((i - word_start + 1) * sizeof(char));
                if ((*words)[*num_words] == NULL)
                {
                    printf("Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                strncpy((*words)[*num_words], command + word_start, i - word_start);
                (*words)[*num_words][i - word_start] = '\0';
                (*num_words)++;
            }
            word_start = i + 1;
        }
    }
    if (i > word_start && !in_quote)
    {
        (*words)[*num_words] = malloc((i - word_start + 1) * sizeof(char));
        if ((*words)[*num_words] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        strncpy((*words)[*num_words], command + word_start, i - word_start);
        (*words)[*num_words][i - word_start] = '\0';
        (*num_words)++;
    }

    // Check for unclosed quote
    if (in_quote)
    {
        printf("Error: Unclosed quote\n");
        exit(EXIT_FAILURE);
    }
}

typedef struct s_lexer
{
	int index;
	//check for builtins
	enum
	{
		NONE = 258,
		WORD = 259,
		PIPE = 260,
		GREATER = 261,
	}	flag;
	char *content;
	struct
	{
		int dollar;
		int *expand;
	} t_dollar;

} t_lexer;

int word_count_dollars(char *word)
{
	char *token;
	char *word_t;
	int count = 0;
 
	word_t = ft_strdup(word);
	if (word[0] == '$')
		count++;
    token = strtok(word_t, "$");

    while (token != NULL)
	{
        count++;
        token = strtok(NULL, "$");
    }
   // printf("Total dollars: %d\n", count -1);
	return (count - 1);
}

void fill_tab(int *tab, char *word)
{
	int i;
	(void)tab;
	i = 0;
	char **words;
	words = ft_split(word, '$');
	while(words[i])
	{
		//printf("leo : %s \n", words[i]);
		i++;
	}
}

void split_word(char *command)
{
	//dollars detection
	//if single quotes -> 
    char **words;
    int num_words;
	t_lexer **lexer;
	int count_dolls;
	int i;
	i = 0;
    split_words(command, &words, &num_words);
    //printf("Number of words: %d\n", num_words);
	lexer = malloc(sizeof(t_lexer *) * (num_words + 1));
    while (i < num_words)
	{
		lexer[i] = malloc(sizeof(t_lexer) * 1);
		count_dolls = word_count_dollars(words[i]);
		if(count_dolls)
		{
			lexer[i]->t_dollar.dollar = 1;
			lexer[i]->t_dollar.expand = malloc(sizeof(int) * (count_dolls + 1));
			lexer[i]->t_dollar.expand[count_dolls] = '\0';
			fill_tab((lexer[i]->t_dollar.expand), words[i]);
		}
		else
		{
			lexer[i]->content = words[i];
			if (*words[i] == '|')
			{
				lexer[i]->flag = PIPE;
			}
			else if (*words[i] == '<' || *words[i] == '>')
			{
				lexer[i]->flag = GREATER;
			}
			else
				lexer[i]->flag = WORD;
			//manage_quotes(words[i]);
        	printf("lexer content : %s || flag : %d\n", lexer[i]->content, lexer[i]->flag);
		}
        //free(words[i]); // Free memory allocated for each _t
		i++;
    }
	lexer[i] = 0;
   // free(words); // Free memory allocated for words array
}


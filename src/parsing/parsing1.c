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


char *ft_strncpy(char *dst, const char *src,  size_t n)
{
	if (n != 0)
    {
		char *d = dst;
		const char *s = src;
		do
        {
			if ((*d++ = *s++) == 0)
            {
				/* NUL pad the remaining n-1 bytes */
				while (--n != 0)
					*d++ = 0;
				break;
			}
		} while (--n != 0);
	}
	return (dst);
}

void split_words(char *command, char ***words, int *num_words)
{
    int len = strlen(command);
    *num_words = 0;
    int in_quote = 0;
    int word_start = 0;
    int i;

    // Count the number of words
    i = 0;
    while (i < len)
    {
        if (command[i] == '"' || command[i] == '\'')
            in_quote = !in_quote;
        else if (!in_quote && (command[i] == ' ' || command[i] == '\t'))
        {
            if (i > word_start)
                (*num_words)++;
            word_start = i + 1;
        }
        i++;
    }
    if (i > word_start && !in_quote)
        (*num_words)++;

    // Allocating memory for words array
    *words = malloc((*num_words) * sizeof(char *));
    if (*words == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    *num_words = 0;
    in_quote = 0;
    word_start = 0;
    i = 0;
    while (i < len)
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
                ft_strncpy((*words)[*num_words], command + word_start, i - word_start);
                (*words)[*num_words][i - word_start] = '\0';
                (*num_words)++;
            }
            word_start = i + 1;
        }
        i++;
    }
    if (i > word_start && !in_quote)
    {
        (*words)[*num_words] = malloc((i - word_start + 1) * sizeof(char));
        if ((*words)[*num_words] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        ft_strncpy((*words)[*num_words], command + word_start, i - word_start);
        (*words)[*num_words][i - word_start] = '\0';
        (*num_words)++;
    }
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
        LESSER = 262,
        BUILTIN = 263,
        HEREDOC = 264,
        APPEND = 265
    
	}	flag;
	char *content;
	int dollar;

} t_lexer;

int count_dollars(char *word)
{
	int i;

    i = 0;
    while (word[i])
    {
        if (word[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

int is_builtin(char *word)
{
    int i;
    char builtins[7][7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    i = 0;

    while (i < 7)
    {
        if (!ft_strncmp(word, builtins[i], ft_strlen(word)) && (ft_strlen(word) == ft_strlen(builtins[i])))
            return (1);
        i++;
    }
    return (0);
}

void split_word(char *command)
{
	//dollars detection
	//if single quotes -> 
    char **words;
    static int previous_is_builtin;
    int num_words;
	t_lexer **lexer;
	int i;
	i = 0;
    split_words(command, &words, &num_words);
    //printf("Number of words: %d\n", num_words);
	lexer = malloc(sizeof(t_lexer *) * (num_words + 1));
    while (i < num_words)
	{
		lexer[i] = malloc(sizeof(t_lexer) * 1);
        lexer[i]->dollar = 0;
		if(count_dollars(words[i]))
		{
			lexer[i]->dollar = 1;
            lexer[i]->flag = WORD;
            lexer[i]->content = words[i];
		}
		else
		{
            if (!previous_is_builtin)
			    lexer[i]->content = manage_quotes(words[i]);
            else
                lexer[i]->content = words[i];
			if (!ft_strncmp(words[i], "|", ft_strlen(words[i])) && (ft_strlen(words[i]) == 1))
			{
				lexer[i]->flag = PIPE;
                previous_is_builtin = 0;
			}
			else if (!ft_strncmp(words[i], ">", ft_strlen(words[i])) && (ft_strlen(words[i]) == 1))
			{
				lexer[i]->flag = GREATER;
                previous_is_builtin = 0;
			}
            else if (!ft_strncmp(words[i], "<", ft_strlen(words[i])) && (ft_strlen(words[i]) == 1))
			{
				lexer[i]->flag = LESSER;
                previous_is_builtin = 0;
			}
            else if (!ft_strncmp(words[i], "<<", ft_strlen(words[i])) && (ft_strlen(words[i]) == 2))
			{
				lexer[i]->flag = HEREDOC;
                previous_is_builtin = 0;
			}
            else if (!ft_strncmp(words[i], ">>", ft_strlen(words[i])) && (ft_strlen(words[i]) == 2))
			{
				lexer[i]->flag = APPEND;
                previous_is_builtin = 0;
			}
			else
            {
				lexer[i]->flag = WORD;
                if (is_builtin(lexer[i]->content))
                {
                    lexer[i]->flag = BUILTIN;
                    previous_is_builtin = 1;

                }
            }
			//manage_quotes(words[i]);
		}
        printf("Content : %s || flag : %d || dollar : %d\n", lexer[i]->content, lexer[i]->flag, lexer[i]->dollar);

        //free(words[i]); // Free memory allocated for each _t
		i++;
    }
	lexer[i] = 0;
   // free(words); // Free memory allocated for words array
}

//<< stop cat
// > $USER
// > cat
// > stop
// lefabreg
// cat

//cat | cat | ls
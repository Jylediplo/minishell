#include "../../includes/minishell.h"

typedef struct s_lexer
{
	int index;
	enum
	{
		NONE = 258,
		WORD = 259,
		PIPE = 260,
		GREATER = 261,
        LESSER = 262,
        BUILTIN = 263,
        HEREDOC = 264,
        APPEND = 265,
        DELIMITER = 266,
    
	}	flag;
	char *content;
	int dollar;
} t_lexer;

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
typedef struct s_words
{
    int len;
    int in_quote;
    int word_start;
    int i;
    char **words;
    int num_words;
    char *command;
    char **wds_delim;
    int count_del;
    t_lexer **lexer;
} t_words;

void init_words_struct(t_words *words, char *command)
{
    words->len = ft_strlen(command);
    words->in_quote = 0;
    words->word_start = 0;
    words->num_words = 0;
    words->count_del = 0;
    words->command = command;
}

void check_words(t_words *words)
{
    int i;

    i = 0;
    while (i < words->len)
    {
        if (words->command[i] == '"' || words->command[i] == '\'')
            words->in_quote = !words->in_quote;
        else if (!words->in_quote && (words->command[i] == ' ' || words->command[i] == '\t'))
        {
            if (i > words->word_start)
                words->num_words++;
            words->word_start = i + 1;
        }
        i++;
    }
    if (i > words->word_start && !words->in_quote)
        (words->num_words)++;
    words->words = malloc((words->num_words) * sizeof(char *));
    if (words->words == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void create_words(t_words *words, int *i)
{
    while (*i < words->len)
    {
        if (words->command[*i] == '"' || words->command[*i] == '\'')
            words->in_quote = !words->in_quote;
        else if (!words->in_quote && (words->command[*i] == ' ' || words->command[*i] == '\t'))
        {
            if (*i > words->word_start)
            {
                (words->words)[words->num_words] = malloc((*i - words->word_start + 1) * sizeof(char));
                if ((words->words)[words->num_words] == NULL)
                {
                    printf("Memory allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                ft_strncpy((words->words)[words->num_words],
                    words->command + words->word_start, *i - words->word_start);
                (words->words)[words->num_words][*i - words->word_start] = '\0';
                (words->num_words)++;
            }
            words->word_start = *i + 1;
        }
        (*i)++;
    }
}
void reset_values(t_words *words)
{
    words->num_words = 0;
    words->in_quote = 0;
    words->word_start = 0;
}

void split_words(t_words *words)
{
    int i;

    i = 0;
    check_words(words);
    reset_values(words);
    create_words(words, &i);
    if (i > words->word_start && !words->in_quote)
    {
        (words->words)[words->num_words] = malloc((i - words->word_start + 1) * sizeof(char));
        if ((words->words)[words->num_words] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        ft_strncpy((words->words)[words->num_words],
            words->command + words->word_start, i - words->word_start);
        (words->words)[words->num_words][i - words->word_start] = '\0';
        (words->num_words)++;
    }
    if (words->in_quote)
    {
        printf("Error: Unclosed quote\n");
        exit(EXIT_FAILURE);
    }
}

int count_dollars(char *word)
{
	int i;

    i = 0;
    while (word && word[i])
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
        if (!ft_strncmp(word, builtins[i], ft_strlen(word))
            && (ft_strlen(word) == ft_strlen(builtins[i])))
        {
            return (1);
        }
        i++;
    }
    return (0);
}
int is_matching(char *word, char *token, size_t length, int *previous)
{
    if (!word)
        return (0);
    if (!ft_strncmp(word, token, ft_strlen(word))
        && (ft_strlen(word) == length))
    {
        *previous = 0;
        return (1);
    }
    return (0);
}
void create_lexer(t_words *words, int *previous_is_builtin, t_lexer **lexer, int i)
{
     if (!(*previous_is_builtin))
			    lexer[i]->content = manage_quotes(words->wds_delim[i]);
            else
                lexer[i]->content = words->wds_delim[i];
			if (is_matching(words->wds_delim[i], "|", 1, previous_is_builtin))
				lexer[i]->flag = PIPE;
			else if (is_matching(words->wds_delim[i], ">", 1, previous_is_builtin))
				lexer[i]->flag = GREATER;
            else if (is_matching(words->wds_delim[i], "<", 1, previous_is_builtin))
				lexer[i]->flag = LESSER;
            else if (is_matching(words->wds_delim[i], "<<", 2, previous_is_builtin))
				lexer[i]->flag = HEREDOC;
            else if (is_matching(words->wds_delim[i], ">>", 2, previous_is_builtin))
				lexer[i]->flag = APPEND;
			else
            {
				lexer[i]->flag = WORD;
                if (is_builtin(lexer[i]->content))
                {
                    lexer[i]->flag = BUILTIN;
                    *previous_is_builtin = 1;
                }
            }
}
void dollars_handler(t_lexer **lexer, int i, t_words *words)
{
    lexer[i]->dollar = 1;
    lexer[i]->flag = WORD;
    lexer[i]->content = words->wds_delim[i];
}

typedef struct s_delim
{
    char **tokens;
    char *del;
    char *start;
    char *end;
    int index;

} t_delim;

void init_struct_del(t_delim *delim, char *str)
{
    delim->del = "<|>";
    delim->start = str;
    delim->end = str;
    delim->index = 0;

}
void handle_db_del(t_delim *delim)
{
    char delimiter[2];
    char double_delimiter[3];

     if ((*delim->end == '<' || *delim->end == '>') && (*(delim->end + 1) == *delim->end))
            {
                double_delimiter[0] = *delim->end;
                double_delimiter[1] = *delim->end;
                double_delimiter[2] = '\0';
                delim->tokens[delim->index] = malloc(3 * sizeof(char));
                ft_strncpy(delim->tokens[delim->index], double_delimiter, 3);
                delim->index++;    
                delim->start = delim->end + 2;
                delim->end++;
            }
            else
            {
                delimiter[0] = *delim->end;
                delimiter[1] = '\0';
                delim->tokens[delim->index] = (char *)malloc(2 * sizeof(char));
                strncpy(delim->tokens[delim->index], delimiter, 2);
                delim->index++;
                delim->start = delim->end + 1;
            }
}

void handle_start_del(t_delim *delim)
{
    int length;

    if (delim->start != delim->end)
    {
        length = delim->end - delim->start;
        delim->tokens[delim->index] = malloc((length + 1) * sizeof(char));
        if (!delim->tokens[delim->index])
        {
            printf("error malloc !\n");
            exit(EXIT_FAILURE);
        }
        ft_strncpy(delim->tokens[delim->index], delim->start, length);
        delim->tokens[delim->index][length] = '\0';
        delim->index++;
    }
}

void handle_end_del(t_delim *delim)
{
    int length;

    if (delim->start != delim->end)
    {
        length = delim->end - delim->start;
        delim->tokens[delim->index] = malloc((length + 1) * sizeof(char));
        if (!delim->tokens[delim->index])
        {
            printf("error malloc !\n");
            exit(EXIT_FAILURE);
        }
        ft_strncpy(delim->tokens[delim->index], delim->start, length);
        delim->tokens[delim->index][length] = '\0';
        delim->index++;
    }
}

char** split_string(char *str, int *count)
{
     int count1 = 0;
    int match = 0;
    t_delim delim;
    delim.tokens = malloc((ft_strlen(str) + 1) * sizeof(char *));
    if (!delim.tokens)
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    init_struct_del(&delim, str);
    while (*delim.end != '\0')
    {   
        count1++;
        match = 0;
         if (ft_strchr(delim.del, *delim.end) != NULL)
         {
            for (int j = count1 -1; j >= 0; j--)
            {
                printf("jjj : %c\n", str[j]);
                if (str[j] == '"')
                {
                    match++;
                    break;
                }
            }
            for (int k = count1; k <= (int)ft_strlen(str); k++)
            {
                if (str[k] == '"')
                {
                    match++;
                    break;
                }
            }
            if (match != 2)
            {
                printf("match : %d\n", match);
                handle_start_del(&delim);
                handle_db_del(&delim);
            }
        }
        delim.end++;
    }
    handle_end_del(&delim);
    *count = delim.index;
    return (delim.tokens);
}

void handle_lexer(t_words *words, int *previous_is_builtin)
{
    int i;

    i = -1;
    words->lexer = malloc(sizeof(t_lexer *) * (words->count_del + 1));
    if (!words->lexer)
    {
        printf("Error MALLOC !\n");
        exit(EXIT_FAILURE);
    }
    while (++i < words->count_del)
	{
		words->lexer[i] = malloc(sizeof(t_lexer) * 1);
        if (!words->lexer[i])
        {
            printf("error MALLOC !\n");
            exit(EXIT_FAILURE);
        }
        words->lexer[i]->dollar = 0;
		if(count_dollars(words->wds_delim[i]))
			dollars_handler(words->lexer, i, words);
		else
           create_lexer(words, previous_is_builtin, words->lexer, i);
        printf("Content : %s & flag : %d || dollar : %d\n", 
            words->lexer[i]->content, words->lexer[i]->flag, words->lexer[i]->dollar);
    }
    *previous_is_builtin = 0;
	words->lexer[i] = 0;
}

void manage_delim(t_words *words)
{
    int i;
    int token_count;

    i = 0;
    while (i < words->num_words)
    {
        token_count = 0;
        if (!split_string(words->words[i], &token_count))
            printf("error malloc !\n");
        i++;
        words->count_del += token_count;
    }
    words->wds_delim = malloc(sizeof(char *) * (words->count_del + 1));
    if (!words->wds_delim)
    {
        printf("error malloc !\n");
        exit(EXIT_FAILURE);
    }
}

void fill_with_delim(t_words *words)
{
    char **tokens;
    int i;
    int j;
    int k;
    int token_count;

    i = 0;
    j = 0;
    while (i < words->num_words)
    {
        token_count = 0;
        tokens = split_string(words->words[i], &token_count);
        k = 0;
        while (k < token_count)
        {
            words->wds_delim[j] = tokens[k];
            j++;
            k++;
        }
        i++;
    }
}

void split_word(char *command)
{
    static int previous_is_builtin;
    t_words words;
   
	int i;

	i = 0;
    init_words_struct(&words, command);
    split_words(&words);
    manage_delim(&words);
    fill_with_delim(&words);
    handle_lexer(&words, &previous_is_builtin);
}

//<< stop cat
// > $USER
// > cat
// > stop
// lefabreg
// cat

//cat | cat | ls
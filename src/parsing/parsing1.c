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

void	init_cmd(t_quote *cmd, char *command)
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
        return (NULL);
    }
    cmd.output[cmd.output_index] = '\0';
	return (cmd.output);
}

char *ft_strncpy(char *dst, const char *src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
    {
        if (i < ft_strlen(src))
            dst[i] = src[i];
        else
            dst[i] = '\0';
        i++;
    }
    return (dst);
}
typedef struct s_words
{
    int len;
    int in_s_q;
    int in_db_q;
    int in_dollar;
    int word_start;
    int i;
    char **words;
    int num_words;
    char *command;
    char **wds_delim;
    int count_del;
    char **tokens;
    t_lexer **lexer;
} t_words;

void init_words_struct(t_words *words, char *command)
{
    words->len = ft_strlen(command);
    words->in_s_q = 0;
    words->in_dollar = 0;
    words->in_db_q = 0;
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
         
            if (words->command[i] == '$' && words->command[i + 1] == '{' && (!words->in_s_q && !words->in_db_q))
                words->in_dollar = 1;
            if (words->command[i] == '}' && words->in_dollar)
                words->in_dollar = 0;
        if (words->command[i] == '"' || words->command[i] == '\'')
        {
            if (words->command[i] == '"' && (!words->in_s_q))
                words->in_db_q = !words->in_db_q;
            else if (words->command[i] == '\'' && (!words->in_db_q))
                words->in_s_q = !words->in_s_q;
        }
        else if ((!words->in_s_q && !words->in_db_q && !words->in_dollar) &&
            (words->command[i] == ' ' || words->command[i] == '\t'))
        {
            if (i > words->word_start)
                words->num_words++;
            words->word_start = i + 1;
        }
        i++;
    }
    if (i > words->word_start && (!words->in_s_q && !words->in_db_q))
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
        
            if (words->command[*i] == '$' && words->command[*i + 1] == '{' && (!words->in_s_q && !words->in_db_q))
                words->in_dollar = 1;
            if (words->command[*i] == '}' && words->in_dollar)
                words->in_dollar = 0;
        if (words->command[*i] == '"' || words->command[*i] == '\'')
        {
             if (words->command[*i] == '"' && (!words->in_s_q))
                words->in_db_q = !words->in_db_q;
            else if (words->command[*i] == '\'' && (!words->in_db_q))
                words->in_s_q = !words->in_s_q;
        }
        else if ((!words->in_s_q && !words->in_db_q && !words->in_dollar) && (words->command[*i] == ' ' || words->command[*i] == '\t'))
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
    words->in_s_q = 0;
    words->in_db_q = 0;
    words->word_start = 0;
}

void split_words(t_words *words)
{
    int i;

    i = 0;
    check_words(words);
    reset_values(words);
    create_words(words, &i);
    if (i > words->word_start && (!words->in_s_q && !words->in_db_q))
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
    if (words->in_dollar)
    {
        printf("Error: BAD substitution\n");
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
void dollars_handler(t_lexer **lexer, int i, t_words *words, int *previous)
{
    lexer[i]->dollar = 1;
    lexer[i]->flag = WORD;
    lexer[i]->content = ft_strdup(words->wds_delim[i]);
    if (i == 0)
        *previous = 1;

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
    delim->tokens = malloc((ft_strlen(str) + 1) * sizeof(char *));
    if (!delim->tokens)
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

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
			dollars_handler(words->lexer, i, words, previous_is_builtin);
		else
           create_lexer(words, previous_is_builtin, words->lexer, i);
    }
    *previous_is_builtin = 0;
	words->lexer[i] = 0;
}

char delim(char *delimiter, char letter)
{
    int i;

    i = 0;
    while (delimiter[i])
    {
        if (delimiter[i] == letter)
            return (letter);
        i++;
    }
    return (0);
}

void delimiter(char *word)
{
    int db_quote_open;
    int s_quote_open;
    int i;

    db_quote_open = 0; 
    s_quote_open = 0;
    i = 0;
    char *delimiter = "><|";
    while (word[i])
    {
        if (word[i] == '"' || word[i] == '\'')
        {
            if (word[i] == '\'')
                s_quote_open = !s_quote_open;
            else
                db_quote_open = !db_quote_open;
        }
        if (word[i] == delim(delimiter, word[i]) && (!s_quote_open && !db_quote_open))
        {
            if (word[i + 1] == delim(delimiter, word[i]) && word[i] != '|')
                i++;
        }
        i++;
    }
}

int count_delim(char *word)
{
    int db_quote_open;
    int s_quote_open;
    int i;
	int count;
    db_quote_open = 0; 
    s_quote_open = 0;
    i = 0;
	count = 0;
    char *delimiter = "><|";
    while (word[i])
    {
        if (word[i] == '"' || word[i] == '\'')
        {
            if (word[i] == '\'')
                s_quote_open = !s_quote_open;
            else
                db_quote_open = !db_quote_open;
        }
        if (word[i] == delim(delimiter, word[i]) && (!s_quote_open && !db_quote_open))
        {

            if (word[i + 1] == delim(delimiter, word[i]) && word[i] != '|')
            {
                printf("%c%c detected index : %d!\n", delim(delimiter, word[i]), delim(delimiter, word[i]), i);
				count++;
                i++;
            }
            else
            {
                printf("%c detected index : %d!\n", delim(delimiter, word[i]), i);
				count++;
            }
        }
        i++;
    }
	return (count);
}

typedef struct s_delims
{
	int index;
	char *delim;
} t_delims;

void free_delim(t_delims **delim, int nb_delim)
{
    int i;
    (void)nb_delim;
    i = 0;
    while (delim[i])
    {
        free(delim[i]->delim);
        free(delim[i]);
        i++;
    }
    free(delim[i]);
    free(delim);
}

t_delims **create_tab_delim(char *word, int nb_delim)
{
	int db_quote_open;
    int s_quote_open;
    int i;

    db_quote_open = 0; 
    s_quote_open = 0;
    i = 0;
    char *delimiter = "><|";
	t_delims **delims;
	int cursor_tab = 0;
	delims = malloc(sizeof(t_delims *) * (nb_delim + 1));
	delims[nb_delim] = 0;
    while (word[i])
    {
        if (word[i] == '"' || word[i] == '\'')
        {
            if (word[i] == '\'')
                s_quote_open = !s_quote_open;
            else
                db_quote_open = !db_quote_open;
        }
        if (word[i] == delim(delimiter, word[i]) && (!s_quote_open && !db_quote_open))
        {
            if (word[i + 1] == delim(delimiter, word[i]) && word[i] != '|')
            {
				delims[cursor_tab] = malloc(sizeof(t_delims) * 1);
				delims[cursor_tab]->delim = malloc(sizeof(char) * (3));
				delims[cursor_tab]->delim[0] = delim(delimiter, word[i]);
				delims[cursor_tab]->delim[1] = delim(delimiter, word[i]);
				delims[cursor_tab]->delim[2] = '\0';
				delims[cursor_tab]->index = i;
				cursor_tab++;
                i++;
            }
            else
            {
				delims[cursor_tab] = malloc(sizeof(t_delims) * 1);
				delims[cursor_tab]->delim = malloc(sizeof(char) * (2));
				delims[cursor_tab]->delim[0] = delim(delimiter, word[i]);
				delims[cursor_tab]->delim[1] = '\0';
				delims[cursor_tab]->index = i;
				cursor_tab++;
            }
        }
        i++;
    }
	return (delims);
}

int count_with_delim(t_delims **delims, int nb_delim, char *word)
{
	int i;
	int count = 0;
	i = 0;
    char *delimiter = "<>|";
	while (delims[i])
	{
		if (i == 0 && i == nb_delim - 1 && delims[i]->index != 0)
        {
            count++;
            if (word[delims[i]->index - 1] != '\0')
                count++;
            if (word[delims[i]->index + ft_strlen(delims[i]->delim)] != '\0' && word[delims[i]->index + ft_strlen(delims[i]->delim)] != delim(delimiter, word[delims[i]->index + 1]))
                count++;
        }
        else if (i == 0 && delims[i]->index != 0)
        {
            count++;
            if (word[delims[i]->index - 1] != '\0')
                count++;
        }
        else if (i == nb_delim - 1 && delims[i]->index != 0)
        {
            count++;
            if ((word[delims[i]->index - 1] != '\0') && (word[delims[i]->index - 1] != delim(delimiter, word[delims[i]->index - 1])))
                count++;
            if (word[delims[i]->index + ft_strlen(delims[i]->delim)] != '\0' && word[delims[i]->index + ft_strlen(delims[i]->delim)] != delim(delimiter, word[delims[i]->index + 1]))
                count++;
        }
        else
        {
            count++;
            if (delims[i]->index != 0)
            {
             if (word[delims[i]->index - 1] != '\0' && word[delims[i]->index - 1] != delim(delimiter, word[delims[i]->index -1]))
                count++;
            }
            else if (nb_delim == 1 && word[delims[i]->index + ft_strlen(delims[i]->delim)] != '\0')
                count++;
        }
		i++;
	}
	return (count);
}

char **create_words_tab(t_delims **delims, int nb_delim, char *word, int nb_words)
{
    char **sentence;
    int i;
    sentence = malloc(sizeof(char *) * (nb_words + 1));
    sentence[nb_words] = NULL;
    i = 0;
    int j = 0;
    int count = 0;
    while (delims[i])
    {
        sentence[count] = ft_substr(word, j, (delims[i]->index - j));
        if (!*sentence[count])
        {
            sentence[count] = ft_strdup(delims[i]->delim);
        }
        else
        {
            count++;
            sentence[count] = ft_strdup(delims[i]->delim);
        }
        j = delims[i]->index + ft_strlen(delims[i]->delim);
        if (i == nb_delim - 1 && word[delims[i]->index + ft_strlen(delims[i]->delim)] != '\0')
        {
            sentence[count] = ft_strdup(delims[i]->delim);
            count++;
            sentence[count] = ft_substr(word, delims[i]->index + ft_strlen(delims[i]->delim), (ft_strlen(word) - delims[i]->index));
        }
        count++;
        i++;
    }
    printf("count : %d && nb_words : %d\n", count, nb_words);
    return (sentence);
}

int check_quotes(char *command)
{
    char *quotes;

    quotes = manage_quotes(command);
    if (quotes)
    {
        free(quotes);
        return (1);
    }
    return (0);
}

void free_words(t_words *words)
{
    int i;

    i = 0;
    while (i < words->num_words)
    {
        free(words->words[i++]);
    }
    free(words->words);
}


void free_wds_delim(t_words *words, int nb)
{
    int i;

    i = 0;
    while (i < nb)
    {
        free(words->wds_delim[i++]);
    }
    free(words->wds_delim[i]);
    free(words->wds_delim);
}

void nb_words_with_delim(t_words *words)
{
    t_delims    **delim;
    int nb_delim;
    int i;
    int nb_words;

    i = 0;
    while (i < words->num_words)
    {
		nb_delim = count_delim(words->words[i]);
		delim = create_tab_delim(words->words[i], nb_delim);
		nb_words = count_with_delim(delim, nb_delim, words->words[i]);
        if (!nb_delim)
            nb_words += 1;
        words->count_del += nb_words;
        free_delim(delim, nb_delim);
        i++;
    }
    words->wds_delim = malloc(sizeof(char *) * (words->count_del + 1));
    words->wds_delim[words->count_del] = 0;
}

void free_temp_word(char **word)
{
    int i;

    i = 0;
    while (word[i])
    {
        free(word[i]);
        i++;
    }
    free(word[i]);
    free(word);
}

void create_wds_lexer(t_words *words)
{
    t_delims **delim;
    char **word;
     int b = 0;
     int i = 0;
    while (i < words->num_words)
    {
		int nb_delim = count_delim(words->words[i]);
		delim = create_tab_delim(words->words[i], nb_delim);
		int nb_words = count_with_delim(delim, nb_delim, words->words[i]);
        word = create_words_tab(delim, nb_delim, words->words[i], nb_words);
        free_delim(delim, nb_delim);
        if (!nb_words)
        {
            free_temp_word(word);
            word = malloc(sizeof(char *) * 2);
            word[0] = ft_strdup(words->words[i]);
            word[1] = NULL;
        }
        int d = 0;
        while (word[d])
        {
            words->wds_delim[b] = ft_strdup(word[d]);
            free(word[d]);
            b++;
            d++;
        }
        free(word[d]);
        free(word);
        i++;
    }
}

void free_lexer(t_words *words)
{
    int i;

    i = 0;
    while (words->lexer[i])
    {
        //free(words->lexer[i]->content);
        free(words->lexer[i]);
        i++;
    }
    free(words->lexer[i]);
    free(words->lexer);
}

void split_word(char *command)
{
    static int previous_is_builtin;
    t_words words;
    words.wds_delim = NULL;
    init_words_struct(&words, command);
    if (check_quotes(command))
        split_words(&words);
    nb_words_with_delim(&words);
    create_wds_lexer(&words);
    handle_lexer(&words, &previous_is_builtin);
    free_wds_delim(&words, words.count_del);
    int j = 0;
    while (j < words.count_del)
    {
        printf("Content : %s & flag : %d || dollar : %d\n", 
        words.lexer[j]->content, words.lexer[j]->flag, words.lexer[j]->dollar);
        j++;
    }
    free_words(&words);
    get_cmdlist(words.lexer, shell);
    free_lexer(&words);
    //free_struct(&words);
    //free(words.lexer);
}

//<< stop cat
// > $USER
// > cat
// > stop
// lefabreg
// cat

//cat | cat | ls
//pol free lexer[i]->content;

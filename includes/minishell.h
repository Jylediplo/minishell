#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
//readline
#include <readline/readline.h>
//signal
#include <signal.h>
void    handle_signals(struct sigaction *catch);

#endif

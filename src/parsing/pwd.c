

#include "../../includes/minishell.h"

int main(void)
{
    char path[4096];
    if (!getcwd(path, 4096))
    {
        write(2, "Error line too long !\n", 22);
    }
    printf("pwd : %s\n", path);
}


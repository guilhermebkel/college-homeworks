#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Answers can be either in Portuguese or in English.
Respostas podem sem tanto em português como em inglês.
*/

/*
1. Term of commitment

The group members declare that all code developed for this project is their own.
The group members declare that they have not copied material from the Internet
  nor obtained code from third parties.

2. Group members and allocation of effort

Fill in the lines below with the name and email of the group members.
Replace XX with the contribution of each group member in the development of the work.

Name guilhermebkel@ufmg.br 100%

3. Solutions

Briefly describe the solutions implemented for this project and justify their choices.

- Task 1: Foi adicionado o código que realiza a chamada fork() para criar um novo processo. Caso o valor retornado seja
negativo (erro), uma mensagem de erro é exibida e a função retorna -1. Caso contrário, o PID do processo filho é retornado.

- Task 2: Foi inserido o uso de execvp() para executar comandos simples, passando os argumentos do comando. Em caso de
falha (retorno -1), uma mensagem de erro é exibida indicando que o comando não foi encontrado, e o processo é encerrado.

- Task 3: Foi incluído o fechamento do descritor de arquivo original e, em seguida, a abertura do novo arquivo, utilizando os
parâmetros especificados na estrutura rcmd. Caso a abertura falhe, é exibida uma mensagem de erro, e o processo é encerrado.

- Task 4: O código adicionado implementa a criação de um pipe e a lógica de fork de dois processos filhos. Um filho redireciona
a saída padrão para a escrita do pipe (lado esquerdo do comando) e o outro redireciona a entrada padrão para a leitura do pipe (lado direito).
Ambos executam seus respectivos comandos com runcmd(). O processo pai fecha os descritores do pipe e espera ambos os filhos com wait().

- Task 5: No loop principal, existe um if que verifica se o comando digitado começa com "cd ". Se for o caso, o caractere de nova
linha ao final da entrada é removido e a função chdir() é chamada para alterar o diretório atual. Caso chdir() falhe, uma mensagem de erro
é exibida. No entanto, a mensagem atual ("process does not exist") é inadequada, pois chdir() lida com diretórios, não com processos.

4. Bibliographic references

Add the bibliographic references here.

- Bash Reference Manual: https://www.gnu.org/software/bash/manual/bash.html
- Linux man page: https://linux.die.net/man

*/

/****************************************************************
 * Simplified xv6 Shell
 *
 * This code was adapted from the UNIX xv6 code and material from
 * the MIT Operating Systems course (6.828).
 ***************************************************************/

#define MAXARGS 10

/* Every command has a type. After identifying the command's type,
    the code converts a *cmd into the specific command type. */
struct cmd {
    int type; /* ' ' (exec)
                 '|' (pipe)
                 '<' or '>' (redirection) */
};

struct execcmd {
    int type;             // ' ' (exec)
    char *argv[MAXARGS];  // Arguments for the command to be executed
};

struct redircmd {
    int type;         // < or > (redirection)
    struct cmd *cmd;  // The command to execute (e.g., an execcmd)
    char *file;       // The input or output file
    int mode;         // The mode in which the file should be opened
    int fd;           // The file descriptor number to be used
};

struct pipecmd {
    int type;           // | (pipe)
    struct cmd *left;   // Left side of the pipe
    struct cmd *right;  // Right side of the pipe
};

int fork1(void);                                        // Fork but exit if an error occurs
struct cmd *parsecmd(char *);                           // Process the command line
void handle_simple_cmd(struct execcmd *ecmd);           // Handle simple commands
void handle_redirection(struct redircmd *rcmd);         // Handle redirection
void handle_pipe(struct pipecmd *pcmd, int *p, int r);  // Handle pipes

/* Execute the command cmd. It never returns. */
void runcmd(struct cmd *cmd) {
    int p[2], r;
    struct execcmd *ecmd;
    struct pipecmd *pcmd;
    struct redircmd *rcmd;

    if (cmd == 0)
        exit(0);

    switch (cmd->type) {
        default:
            fprintf(stderr, "Unknown command type\n");
            exit(-1);

        case ' ':
            ecmd = (struct execcmd *)cmd;
            if (ecmd->argv[0] == 0)
                exit(0);
            handle_simple_cmd(ecmd);
            break;

        case '>':
        case '<':
            rcmd = (struct redircmd *)cmd;
            handle_redirection(rcmd);
            runcmd(rcmd->cmd);
            break;

        case '|':
            pcmd = (struct pipecmd *)cmd;
            handle_pipe(pcmd, p, r);
            break;
    }
    exit(0);
}

int fork1(void) {
    /* Task 1: Implement the fork1 function.
    The function is supposed to create a new process using the `fork()` system call.
    It should print a message if the fork fails, otherwise return the process ID of the child process (or -1 if the fork fails).
    */
    int child_process_id = fork();
    int failed_to_create_child_process = (child_process_id < 0);

    if (failed_to_create_child_process) {
        fprintf(stderr, "Error: failed to create a new process with fork()\n");
        return -1;
    }

    return child_process_id;
    /* END OF TASK 1 */
}

void handle_simple_cmd(struct execcmd *ecmd) {
    /* Task 2: Implement the code below to execute simple commands. */
    int execvp_result = execvp(ecmd->argv[0], ecmd->argv);
    int failed_to_execute_command = (execvp_result == -1);

    if (failed_to_execute_command) {
        fprintf(stderr, "Error: command not found: %s\n", ecmd->argv[0]);
        exit(EXIT_FAILURE);
    }
    /* END OF TASK 2 */
}

void handle_redirection(struct redircmd *rcmd) {
    /* Task 3: Implement the code below to handle input/output redirection. */
    close(rcmd->fd);

    int permission_code_for_read_and_write_access_for_all_users = 0666;
    int file_descriptor = open(rcmd->file, rcmd->mode, permission_code_for_read_and_write_access_for_all_users);
    int failed_to_open_file = (file_descriptor < 0);

    if (failed_to_open_file) {
        fprintf(stderr, "Error: failed to open file: %s\n", rcmd->file);
        exit(EXIT_FAILURE);
    }
    /* END OF TASK 3 */
}

void handle_pipe(struct pipecmd *pcmd, int *p, int r) {
    /* Task 4: Implement the code below to handle pipes. */
    int pipe_creation_result = pipe(p);
    int failed_to_create_pipe = (pipe_creation_result < 0);

    if (failed_to_create_pipe) {
        fprintf(stderr, "Error: failed to create pipe\n");
        exit(EXIT_FAILURE);
    }

    int left_child_pid = fork1();
    int is_left_child_process = (left_child_pid == 0);

    if (is_left_child_process) {
        close(1); // Close the standard output descriptor (stdout)
        dup(p[1]); // Redirect stdout to the write end of the pipe
        close(p[0]); // Close the read end of the pipe, which will not be used
        close(p[1]); // Close the original write end of the pipe, as it has been duplicated
        runcmd(pcmd->left); // Execute the command associated with the left side of the pipe
    }

    int right_child_pid = fork1();
    int is_right_child_process = (right_child_pid == 0);

    if (is_right_child_process) {
        close(0); // Close the standard input descriptor (stdin)
        dup(p[0]); // Redirect stdin to the read end of the pipe
        close(p[0]); // Close the original read end of the pipe, as it has been duplicated
        close(p[1]); // Close the write end of the pipe, which will not be used
        runcmd(pcmd->right); // Execute the command associated with the right side of the pipe
    }

    // Parent process closes both ends of the pipe and waits for the children
    close(p[0]);
    close(p[1]);

    wait(NULL); // Wait for the termination of the first child
    wait(NULL); // Wait for the termination of the second child
    /* END OF TASK 4 */
}

int getcmd(char *buf, int nbuf) {
    if (isatty(fileno(stdin)))
        fprintf(stdout, "$ ");
    memset(buf, 0, nbuf);
    fgets(buf, nbuf, stdin);
    if (buf[0] == 0)  // EOF
        return -1;
    return 0;
}

int main(void) {
    static char buf[100];
    int r;

    // Read and execute commands.
    while (getcmd(buf, sizeof(buf)) >= 0) {
        /* Task 5: Explain the purpose of the if statement below and correct the error message.
        Why is the current error message incorrect? Justify the new message. */
        /* Answer:
            O propósito do if é verificar se o comando digitado começa com "cd ", o que indica que o usuário quer mudar de diretório.
            Se for o caso, ele remove o caractere de nova linha no final do comando (buf[strlen(buf) - 1] = 0) e tenta mudar para o diretório especificado com chdir(buf + 3).

            A mensagem de erro atual ("process does not exist") está incorreta, porque a função chdir não lida com processos, e sim com diretórios.
            Quando chdir falha, geralmente é porque o diretório especificado não existe ou não pode ser acessado.

            Uma mensagem correta e mais descritiva seria:
            fprintf(stderr, "cd: diretório não encontrado\n");
            Isso informa corretamente ao usuário que houve um problema ao tentar mudar de diretório.
         */
        if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ') {
            buf[strlen(buf) - 1] = 0;
            if (chdir(buf + 3) < 0)
                fprintf(stderr, "process does not exist\n");
            continue;
        }
        /* END OF TASK 5 */

        if (fork1() == 0)
            runcmd(parsecmd(buf));
        wait(&r);
    }
    exit(0);
}

/****************************************************************
 * Helper functions for creating command structures
 ***************************************************************/

struct cmd *
execcmd(void) {
    struct execcmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = ' ';
    return (struct cmd *)cmd;
}

struct cmd *
redircmd(struct cmd *subcmd, char *file, int type) {
    struct redircmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = type;
    cmd->cmd = subcmd;
    cmd->file = file;
    cmd->mode = (type == '<') ? O_RDONLY : O_WRONLY | O_CREAT | O_TRUNC;
    cmd->fd = (type == '<') ? 0 : 1;
    return (struct cmd *)cmd;
}

struct cmd *
pipecmd(struct cmd *left, struct cmd *right) {
    struct pipecmd *cmd;

    cmd = malloc(sizeof(*cmd));
    memset(cmd, 0, sizeof(*cmd));
    cmd->type = '|';
    cmd->left = left;
    cmd->right = right;
    return (struct cmd *)cmd;
}

/****************************************************************
 * Command Line Processing
 ***************************************************************/

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>";

int gettoken(char **ps, char *es, char **q, char **eq) {
    char *s;
    int ret;

    s = *ps;
    while (s < es && strchr(whitespace, *s))
        s++;
    if (q)
        *q = s;
    ret = *s;
    switch (*s) {
        case 0:
            break;
        case '|':
        case '<':
            s++;
            break;
        case '>':
            s++;
            break;
        default:
            ret = 'a';
            while (s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
                s++;
            break;
    }
    if (eq)
        *eq = s;

    while (s < es && strchr(whitespace, *s))
        s++;
    *ps = s;
    return ret;
}

int peek(char **ps, char *es, char *toks) {
    char *s = *ps;
    while (s < es && strchr(whitespace, *s)) s++;
    *ps = s;
    return *s && strchr(toks, *s);
}

struct cmd *parseline(char **, char *);
struct cmd *parsepipe(char **, char *);
struct cmd *parseexec(char **, char *);

/* Copy characters from the input buffer, starting from s to es.
 * Place a null terminator at the end to create a valid string. */
char *mkcopy(char *s, char *es) {
    int n = es - s;
    char *c = malloc(n + 1);
    assert(c);
    strncpy(c, s, n);
    c[n] = 0;
    return c;
}

struct cmd *
parsecmd(char *s) {
    char *es;
    struct cmd *cmd;

    es = s + strlen(s);
    cmd = parseline(&s, es);
    peek(&s, es, "");
    if (s != es) {
        fprintf(stderr, "leftovers: %s\n", s);
        exit(-1);
    }
    return cmd;
}

struct cmd *
parseline(char **ps, char *es) {
    struct cmd *cmd;
    cmd = parsepipe(ps, es);
    return cmd;
}

struct cmd *
parsepipe(char **ps, char *es) {
    struct cmd *cmd;

    cmd = parseexec(ps, es);
    if (peek(ps, es, "|")) {
        gettoken(ps, es, 0, 0);
        cmd = pipecmd(cmd, parsepipe(ps, es));
    }
    return cmd;
}

struct cmd *
parseredirs(struct cmd *cmd, char **ps, char *es) {
    int tok;
    char *q, *eq;

    while (peek(ps, es, "<>")) {
        tok = gettoken(ps, es, 0, 0);
        if (gettoken(ps, es, &q, &eq) != 'a') {
            fprintf(stderr, "missing file for redirection\n");
            exit(-1);
        }
        switch (tok) {
            case '<':
                cmd = redircmd(cmd, mkcopy(q, eq), '<');
                break;
            case '>':
                cmd = redircmd(cmd, mkcopy(q, eq), '>');
                break;
        }
    }
    return cmd;
}

struct cmd *
parseexec(char **ps, char *es) {
    char *q, *eq;
    int tok, argc;
    struct execcmd *cmd;
    struct cmd *ret;

    ret = execcmd();
    cmd = (struct execcmd *)ret;

    argc = 0;
    ret = parseredirs(ret, ps, es);
    while (!peek(ps, es, "|")) {
        if ((tok = gettoken(ps, es, &q, &eq)) == 0)
            break;
        if (tok != 'a') {
            fprintf(stderr, "syntax error\n");
            exit(-1);
        }
        cmd->argv[argc] = mkcopy(q, eq);
        argc++;
        if (argc >= MAXARGS) {
            fprintf(stderr, "too many args\n");
            exit(-1);
        }
        ret = parseredirs(ret, ps, es);
    }
    cmd->argv[argc] = 0;
    return ret;
}
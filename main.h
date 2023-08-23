#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

/*
 *set of delimiter characters for tokenization:
 *space,carriage return, tab , newline, and bell
 */
#define TOKEN_DELIMITERS " \r\t\n\a"

/*  size of a buffer to hold data as 1250 bytes */
#define BUFFER_SIZE 1250

/*  size of a buffer for storing tokens as 130 characters */
#define TOKEN_BUFFER_SIZE 130


/* declaration of  environment varible */
extern char **environ;


/**
 * struct User_data - struct that contains all relevant data on runtime
 * @argv: argument vector
 * @info: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @count: lines counter
 * @Environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct User_data
{
	char **argv;
	char *info;
	char **args;
	int status;
	int count;
	char **Environ;
	char *pid;
} data;

/**
 * struct S_list - a linked list
 * @separate: | ;  &
 * @next: next node
 * Description: a linked list that stores separators
 */
typedef struct S_list
{
	char separate;
	struct S_list *next;
} S_list_t;

/**
 * struct line_list - a linked list
 * @line: cmd line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list
{
	char *line;
	struct line_list *next;
} L_list;

/**
 * struct r_var_s - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_s
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_s *next;
} r_var_t;

/**
 * struct cmdArgs - struct for command args
 * @name: The name of the cmds
 * @f:pointer
 */
typedef struct cmdArgs
{
	char *name;
	int (*f)(data *);
} cmdArgs_t;


S_list_t *add_Snode_end(S_list_t **head, char sep);
void free_Slist(S_list_t **head);
L_list *add_Lnode_end(L_list **head, char *line);
void free_Llist(L_list **head);

r_var_t *add_v(r_var_t **head, int lvar, char *var, int lval);
void free_rvar(r_var_t **head);


int strCmp(char *first, char *second);
char *strCpy(char *des, char *src);
int strSpn(char *s, char *valid);
char *strChr(char *str, char c);
char *strCat(char *des, const char *src);

void memCpy(void *nptr, const void *ptr, unsigned int size);
void *Realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **Reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

int strLen(const char *str);
int isDigit(const char *s);
int cmpChars(char str[], const char *dem);
char *strdUp(const char *str);
char *strTok(char str[], const char *dem);


void rev_str(char *s);

int rep_c(char *input, int i);
int error_rep(char *input, int i, char last);
int firstC(char *input, int *i);
void syntax_err(data *runtime_data, char *input, int i, int bool);
int check_syntax_err(data *runtime_data, char *input);

char *no_comment(char *n);
void sh_loop(data *runtime_data);

char *readLine(int *eof);

char *swap(char *input, int bool);
void next(S_list_t **listS, L_list **listL, data *runtime_data);
int splitcmd(data *runtime_data, char *input);
char **sptLine(char *input);
void addNodes(S_list_t **s_head, L_list **c_head, char *input);


void envCheck(r_var_t **head, char *input, data *data);
int varsCheck(r_var_t **h, char *in, char *st, data *data);
char *replacedInput(r_var_t  **head, char *input, char *new_input, int nlen);
char *repVar(char *input, data *runtime_data);

void Bline(char **lineptr, size_t *n, char *buf, size_t j);
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);
int exec_line(data *runtime_data);

int cdir(char *path, int *i);
char *locates(char *cmd, char **_environ);
int Executes(data *runtime_data);
int error_cmd(char *dir, data *runtime_data);
int exec_cmd(data *runtime_data);

char *getEnv(const char *name, char **_environ);
int Env(data *runtime_data);

char *c_info(char *name, char *value);
void set_Env(char *name, char *value, data *runtime_data);
int setenv_c(data *runtime_data);
int unsetEnv(data *runtime_data);

void cdDot(data *runtime_data);
void cdTo(data *runtime_data);
void cd_pre(data *runtime_data);
void cd_home(data *runtime_data);

int cd_sh(data *runtime_data);

int (*getBuiltinf(char *cmd))(data *runtime_data);

int Exit(data *runtime_data);

int getLength(int x);
char *intTostr(int nt);
int strToint(char *s);

char *err_cd(data *runtime_data);
char *error_not_found(data *runtime_data);
char *err_exit_msg(data *runtime_data);
char *strCatCd(data *, char *, char *, char *);



char *err_env(data *runtime_data);
char *err_path(data *runtime_data);

int getError(data *runtime_data, int err_v);

void getSigint(int s);

void HelpEnv(void);
void HelpSetEnv(void);
void Help_exit(void);
void HelpS(void);
void Help_alias(void);
void Help_general(void);
void Help_cd(void);
int Help(data *runtime_data);
void helpUnsetEnv(void);
#endif

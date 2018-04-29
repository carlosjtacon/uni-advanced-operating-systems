#ifndef _COMMAND_FUNCTIONS_H_
#define _COMMAND_FUNCTIONS_H_ 

#include "parser.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "errno.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>

#define BUFSIZE sysconf(_SC_PAGE_SIZE)
#define HELP "Usage: minishell $ [command] [arguments]\nWhere command is one of:\n\thelp (print this help).\n\tmypwd (print working directory).\n\tmyls [dir] [-l] (list current or given directory, use -l for details).\n\tmymkdir [dir] (create directory passed as argument).\n\tmyrmdir [dir] (remove directory passed as argument).\n\tmycd [dir] (change directory, if no arguments go to initial dir).\n\tmycat [file] (print the contents of the file passed).\n\tmycp [file1] [file2] (copy the contents of file1 in the file2).\n\tmyrm [file] (delete the file passed as parameter)\n\texit (quit the minishell)."

void show_command (command * C);
void exec_cmd(command * C, char *initpath);

char *mypwd();
void myls(char *arg1, char *arg2);
void mymkdir(char *inputPath);
void myrmdir(char *inputPath);
void mycd(char *inputPath, char *init);
void mycat(char *inputPath);
void mycp(char *file1, char *file2);
void myrm(char *inputPath);

char *parse_permissions(mode_t mode);
void print_dir_details(DIR *tdir, char *inputPath);

#endif
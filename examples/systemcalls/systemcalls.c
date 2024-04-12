#include "systemcalls.h"
#include <sys/types.h>       
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define REDIRECT_FILE "./sysCallTextFile.txt"
/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/

int pid ;
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
    int rc = system(cmd);
    if(rc == 0)
        return true;
    else
        perror("do_system");
    return false;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

    va_end(args);
/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/
    pid = fork();
    if(pid == 0){
        int rv = execv(command[0],command);
        printf(" \n execv rv: %d",rv);
        if(rv){
            perror("\ndo_exec if(rv)\n");
            exit(1);
            return false;
        }
    }
    else{
    // perror("do_exec fork failed");
    // printf("\nchild PID : %i ", pid);
        int wstatus = 0;
        do {
            int w= waitpid(pid, &wstatus, 0);
            if (w == -1) {
                perror("waitpid");
                exit(0);
            }

            if (WIFEXITED(wstatus)) {
                printf("exited, status=%d\n", WEXITSTATUS(wstatus));
                if(WEXITSTATUS(wstatus))
                    return false;
            } else if (WIFSIGNALED(wstatus)) {
                printf("killed by signal %d\n", WTERMSIG(wstatus));
            } else if (WIFSTOPPED(wstatus)) {
                printf("stopped by signal %d\n", WSTOPSIG(wstatus));
            } else if (WIFCONTINUED(wstatus)) {
                printf("continued\n");
            }
        } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));

    }

    return true;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

    va_end(args);

/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/
    pid = fork();
    if(pid == 0){

        int fd = open(outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644);
        if (fd < 0) { perror("open redirected.txt"); abort(); }
        if (dup2(fd, 1) < 0) { perror("dup2"); abort(); }
        close(fd);

        int rv = execv(command[0],command);
        printf(" \n execv rv: %d",rv);
        if(rv){
            perror("\ndo_exec if(rv)\n");
            exit(1);
            return false;
        }
    }
    else{
    // perror("do_exec fork failed");
    // printf("\nchild PID : %i ", pid);
        int wstatus = 0;
        do {
            int w= waitpid(pid, &wstatus, 0);
            if (w == -1) {
                perror("waitpid");
                exit(0);
            }

            if (WIFEXITED(wstatus)) {
                printf("exited, status=%d\n", WEXITSTATUS(wstatus));
                if(WEXITSTATUS(wstatus))
                    return false;
            } else if (WIFSIGNALED(wstatus)) {
                printf("killed by signal %d\n", WTERMSIG(wstatus));
            } else if (WIFSTOPPED(wstatus)) {
                printf("stopped by signal %d\n", WSTOPSIG(wstatus));
            } else if (WIFCONTINUED(wstatus)) {
                printf("continued\n");
            }
        } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));

    }

    return true;
}



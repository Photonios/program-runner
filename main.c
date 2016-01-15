#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

static bool running = true;
static char *program = NULL;
static pid_t pid = -1;
static char **mainargv = NULL;

void
start_program()
{
    pid = fork();
    if(pid == 0) {
        execv(program, (mainargv + 2));
    }
}

void
stop_program()
{
    kill(pid, SIGKILL);
    pid = -1;
}

void
on_exit(int signal)
{
    /* also kill the child process if we're exiting */
    if(pid != -1) {
       stop_program(); 
    }

    running = false;
}

void
on_program_stop(int signal)
{
    /* make sure there's actually a program running */
    if(pid == -1) {
        fprintf(stderr, "[program-runner] cannot stop program, not running\n");
        return;
    }

    stop_program();
    fprintf(stdout, "[program-runner] stopped program\n");
}

void
on_program_start(int signal)
{
    /* make sure we don't start it twice */
    if(pid != -1) {
        fprintf(stderr, "[program-runner] not starting, already running\n");
        return;
    }

    fprintf(stdout, "[program runner] starting program\n");

    /* start program as a child process */
    start_program();
}

bool
file_exists(char *path)
{
    FILE *fp = fopen(path, "r");
    if(!fp) {
        return false;
    }

    fclose(fp);
    return true;
}

int
main(int argc, char **argv)
{
    mainargv = argv;

    if(argc < 2) {
        fprintf(stderr, "Usage: ./program-runner [program]\n");
        return 1;
    }

    /* make sure the specified program exists */
    program = argv[1];
    if(!file_exists(program)) {
        fprintf(stderr, "[program-runner] '%s' does not exists\n", program);
        return 1;
    }

    /* based on these signals we'll start/stop the current program */
    signal(SIGUSR1, on_program_start);
    signal(SIGUSR2, on_program_stop);

    /* these our for this program, we'll exit whenever we'll receive them */
    signal(SIGINT, on_exit);
    signal(SIGTERM, on_exit);

    /* keep running until we're actually terminated */
    while(running) {
        usleep(500 * 1000 /* 500 ms */);
    }

    return 0;
}

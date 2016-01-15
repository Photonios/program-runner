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
on_exit(int signal)
{
    running = false;
}

void
on_program_stop(int signal)
{
    if(pid == -1) {
        fprintf(stderr, "[program-runner] cannot stop program, not running\n");
        return;
    }

    kill(pid, SIGKILL);
    pid = -1;

    fprintf(stdout, "[program-runner] stopped program\n");
}

void
on_program_start(int signal)
{
    if(pid != -1) {
        fprintf(stderr, "[program-runner] not starting, already running\n");
        return;
    }

    fprintf(stdout, "[program runner] starting program\n");

    pid = fork();
    if(pid == 0) {
        execv(program, ++mainargv);
    }
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

////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        intdate.c
// Other Files:      sendsig.c, division.c
// Semester:         CS 354 Fall 2018
//
// Author:           Kendra Raczek
// Email:            raczek@wisc.edu
// CS Login:         raczek
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
// Persons:
//
// Online sources:   tutorialspoint.com
//                   definitions of functions
//////////////////////////// 80 columns wide ///////////////////////////////////

#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// number of SIGUSR1 signals received
int counter = 0;

/* signal handler for alarm (SIGALRM)
 *
 * sig signal number
 */
void handler_SIGALRM(int sig)
{
    time_t curr_time;
    if ((time(&curr_time) == (time_t)-1) || (time(&curr_time) == 0)) {
        printf("time() ERROR\n");
        exit(1);
    }
    time(&curr_time);

    pid_t pid;
    pid = getpid();

    if (ctime(&curr_time) == NULL) {
        printf("ctime ERROR\n");
        exit(1);
    }
    printf("PID: %d | Current Time: %s", pid, ctime(&curr_time));
    alarm(3);    // recurring alarm
}

/* signal handler for user signal (SIGUSR1)
 *
 * sig signal number
 */
void handler_SIGUSR1(int sig) {
    counter++;
    printf("SIGUSR1 caught!\n");
}

/* signal handler for termination (SIGINT)
 *
 * sig signal number
 */
void handler_SIGINT(int sig) {
    printf("SIGUSR1 was received %d times. Exiting now.\n", counter);
    exit(0);
}

// infinitely displays date & time every 3 seconds and receives signals
int main(int argc, char *argv[]) {
    // SIGALRM
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler_SIGALRM;
    sa.sa_flags = 0;

    // SIGUSR1
    struct sigaction su1;
    memset(&su1, 0, sizeof(su1));
    su1.sa_handler = handler_SIGUSR1;
    su1.sa_flags = 0;

    // SIGINT
    struct sigaction sint;
    memset(&sint, 0, sizeof(sint));
    sint.sa_handler = handler_SIGINT;
    sint.sa_flags = 0;

    printf("Pid and time will be printed every 3 seconds.\nEnter ^C to end the program.\n");

    if(sigaction(SIGALRM, &sa, NULL) != 0) {
        printf("ERROR: BINDING SIGALARM HANDLER.\n");
        exit(1);
    }

    if(sigaction(SIGUSR1, &su1, NULL) != 0) {
        printf("ERROR: BINDING SIGUSR1 HANDLER.\n");
        exit(1);
    }

    if(sigaction(SIGINT, &sint, NULL) != 0) {
        printf("ERROR: BINDING SIGINT HANDLER.\n");
        exit(1);
    }

    alarm(3);

    while (1){
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      intdate.c, division.c
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// sends signals to other processes
int main(int argc, char *argv[]){

    if(argc != 3) {
        printf("Usage: <signal type> <pid>");
    }
    // extract command line arguments
    char *sigtype = argv[1];
    int pid = atoi(argv[2]);

    // send signal to other programs
    if (strcmp(sigtype, "-i") == 0) {
        if (kill(pid, SIGINT) == -1) {
            printf("kill() ERROR\n");
            exit(1);
        }
        kill(pid, SIGINT);
    }
    else if (strcmp(sigtype, "-u") == 0){
        if (kill(pid, SIGINT) == -1) {
            printf("kill() ERROR\n");
            exit(1);
        }
        kill(pid, SIGUSR1);
    }
    else {
        printf("ERROR: INVALID ARGUMENT");
        exit(1);
    }
    exit(0);
}
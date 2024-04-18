
/**
 * Assignment 2: Simple UNIX Shell
 * @file prog.cpp
 * @author Jeremiah Shue
 * @brief This is the main function of a simple UNIX Shell. You may add
 * additional functions in this file for your implementation
 * @version 0.1
 */

#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>


using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated
 * by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[]) {
  // replace trailing newline with null
  command[strcspn(command, "\n")] = 0;
  char *token = strtok(command, " ");
  int i = 0;
  while (token != NULL) {
    args[i++] = token;
    token = strtok(NULL, " ");
  }
  args[i] = NULL;
  return i;
}

/**
 * @brief The main function of a simple UNIX Shell. You may add additional
 * functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) {
  char command[MAX_LINE]; // the command that was entered
  char last_command[MAX_LINE];
  last_command[0] = '\0';

  char *args[MAX_LINE / 2 + 1];      // hold parsed out command line arguments
  int should_run = 1; /* flag to determine when to exit program */

  while (should_run) {
    printf("osh>");
    fflush(stdout);
    // Read the input command
    fgets(command, MAX_LINE, stdin);
    // if command is "!!"
    if (strcmp(command, "!!\n") == 0) {
      if (last_command[0] == '\0') {
        printf("%s", "No command history\n");
        fflush(stdout);
        continue;
      }
      // copy last_command into command
      strncpy(command, last_command, MAX_LINE);
      printf("%s\n", command);
    }
    strncpy(last_command, command, MAX_LINE);
    // Parse the input command
    int num_args = parse_command(command, args);
    // Empty Line
    if (num_args == 0) {
      continue;
    }
    if (strcmp(args[0], "exit") == 0) {
      break;
    }

    char *lastarg = args[num_args - 1];
    bool background = (lastarg[strlen(lastarg) - 1] == '&');
    if (background) {
      // strip off the trailing &
      lastarg[strlen(lastarg) - 1] = '\0';
      if (strlen(lastarg) == 0) {
        num_args--;
      }
    }

    int child_pid = fork();
    if (child_pid) {
      // this executes in main process
      int status = 0;
      if (background) {
        continue;
        // split as background task
      } else {
        waitpid(child_pid, &status, 0);
        if (status == 65280) {
          printf("Command not found\n");
        } else {
          printf("Exited with code %d\n", status);
        }
      }
      // in parent process, wait for child to finish

    } else {
      // search for < or > (to be valid, there must be at least one arg on each
      // side)
      for (int i = 1; i < num_args - 1; i++) {
        if (strcmp(args[i], ">") == 0) {
          // redirecting output
          close(STDOUT_FILENO);
          open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
          // ignore the > and all after it
          args[i] = NULL;
        } else if (strcmp(args[i], "<") == 0) {
          // redirect input
          close(STDIN_FILENO);
          open(args[i + 1], O_CREAT | O_RDONLY, S_IRWXU);
          // ignore the < and all after it
          args[i] = NULL;
        }
      }
      // this executes in child process
      exit(execvp(args[0], args));
    }
  }
  return 0;
}

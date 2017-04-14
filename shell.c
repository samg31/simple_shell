// ACADEMIC INTEGRITY PLEDGE
//
// - I have not used source code obtained from another student nor
//   any other unauthorized source, either modified or unmodified.
//
// - All source code and documentation used in my program is either
//   my original work or was derived by me from the source code
//   published in the textbook for this course or presented in
//   class.
//
// - I have not discussed coding details about this project with
//   anyone other than my instructor. I understand that I may discuss
//   the concepts of this program with other students and that another
//   student may help me debug my program so long as neither of us
//   writes anything during the discussion or modifies any computer
//   file during the discussion.
//
// - I have violated neither the spirit nor letter of these restrictions.
//
//
//
// Signed: Sam Goodrick & Kerry Holmes Date: 14 April 2017

// 3460:426 Lab 4A - Basic C shell

/* Basic shell */

/*
 * This is a very minimal shell. It finds an executable in the
 * PATH, then loads it and executes it (using execv). Since
 * it uses "." (dot) as a separator, it cannot handle file
 * names like "minishell.h"
 *
 * The focus on this exercise is to use fork, PATH variables,
 * and execv. 
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_ARGS	64
#define MAX_ARG_LEN	16
#define MAX_LINE_LEN	80
#define WHITESPACE	" ,\t\n"
#define TRUE 1
#define FALSE 0

struct command_t {
   char *name;
   int argc;
   char *argv[MAX_ARGS];
};

/* Function prototypes */
int parseCommand(char *, struct command_t *);
void printPrompt();
void readCommand(char *);
void helpPrompt();

int main(int argc, char *argv[]) {
   int pid;
   int status;
   int index;
   char cmdLine[MAX_LINE_LEN];
   struct command_t command;

   while (TRUE) {
      printPrompt();
      /* Read the command line and parse it */
      readCommand(cmdLine);
      /*...*/
      parseCommand(cmdLine, &command);

	  switch( command.argv[0][0] )
	  {
	  case 'C':
		  command.name = "cp";
		  break;
	  case 'D':
		  command.name = "rm";
		  break;
	  case 'M':
		  command.name = "nano";
		  break;
	  case 'P':
		  command.name = "more";
		  break;
	  case 'S':
		  command.name = "firefox";
		  break;
	  case 'W':
		  command.name = "clear";
		  break;
	  case 'X':
		  command.name = command.argv[1];
		  break;
	  case 'L':
		  command.name = "ls";
		  break;
	  case 'H':
		  helpPrompt();
		  break;
	  case 'E':
		  command.name = "echo";
		  break;
	  case 'Q':
		  exit( 0 );
		  break;
	  default:
		  printf( "Unrecognized command. Enter 'H' for help\n" );
		  break;
	  }

	  command.argv[command.argc] = NULL;
	  
      /* Create a child process to execute the command */
      if ((pid = fork()) == 0) {
         /* Child executing command */
         execvp(command.name, command.argv);
      }
      /* Wait for the child to terminate */
      wait(&status);
   }

   
   /* Shell termination */
   printf("\n\n shell: Terminating successfully\n");
   return 0;
}

/* End basic shell */

/* Parse Command function */

/* Determine command name and construct the parameter list.
 * This function will build argv[] and set the argc value.
 * argc is the number of "tokens" or words on the command line
 * argv[] is an array of strings (pointers to char *). The last
 * element in argv[] must be NULL. As we scan the command line
 * from the left, the first token goes in argv[0], the second in
 * argv[1], and so on. Each time we add a token to argv[],
 * we increment argc.
 */
int parseCommand(char *cLine, struct command_t *cmd) {
   int argc;
   char **clPtr;
   /* Initialization */
   clPtr = &cLine;	/* cLine is the command line */
   argc = 0;
   cmd->argv[argc] = (char *) malloc(MAX_ARG_LEN);
   /* Fill argv[] */
   while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL) {
      cmd->argv[++argc] = (char *) malloc(MAX_ARG_LEN);
   }

   /* Set the command name and argc */
   cmd->argc = argc-1;
   cmd->name = (char *) malloc(sizeof(cmd->argv[0]));
   strcpy(cmd->name, cmd->argv[0]);
   return 1;
}

/* End parseCommand function */

/* Print prompt and read command functions - pp. 79-80 */

void printPrompt() {
	/* Build the prompt string to have the machine name,
	 * current directory, or other desired information
	 */
	char* promptString = "sdg31@linux|>";
	printf("%s ", promptString);
}

void readCommand(char *buffer) {
   /* This code uses any set of I/O functions, such as those in
    * the stdio library to read the entire command line into
    * the buffer. This implementation is greatly simplified,
    * but it does the job.
    */
   fgets(buffer, 80, stdin);
}

/* End printPrompt and readCommand */

void helpPrompt()
{
	printf( "This is a simple shell. Every action begins with\n" );
	printf( "a single capital letter command, followed by the\n" );
	printf( "necessary amount of arguments. View each command\n" );
	printf( "below to see its purpose and needed arguments.\n\n" );

	printf( "C file1 file2\n" );
	printf( "Create a copy of file1 with name 'file2'\n\n" );

	printf( "D file\n" );
	printf( "Delete file with name 'file'\n\n" );

	printf( "M file\n" );
	printf( "Open 'file' in the nano text editor\n\n" );

	printf( "P file\n" );
	printf( "Display 'file' in more\n\n" );

	printf( "S\n" );
	printf( "Open the firefox web browser\n\n" );

	printf( "W\n" );
	printf( "Clear the screen\n\n" );

	printf( "X program\n" );
	printf( "Execute 'program'\n\n" );
}

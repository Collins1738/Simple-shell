#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "> ";
char delimiters[] = " \t\r\n";
extern char **environ;



int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    char cmd_bak[MAX_COMMAND_LINE_LEN];
  
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    	
    while (true) {
      
        do{ 
            char path[4096];
            // Print the current path
            char* directory = getcwd(path, sizeof(path));
            printf("%s ", directory);
            // Print the shell prompt.
            printf("%s", prompt);
            fflush(stdout);

            // Read input from stdin and store it in command_line. If there's an
            // error, exit immediately. (If you want to learn more about this line,
            // you can Google "man fgets")
        
            if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
                fprintf(stderr, "fgets error");
                exit(0);
            }
 
        }while(command_line[0] == 0x0A);  // while just ENTER pressed

      
//         If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // TODO:
        // 
        
			  // 0. Modify the prompt to print the current working directory
      
			
        // 1. Tokenize the command line input (split it on whitespace)
      
      char* iterator = command_line;
      iterator = strsep(&iterator, "\n");
      int i;
      for(i = 0; i<MAX_COMMAND_LINE_LEN; i++){
        char* chr = strsep(&iterator, " ");
        if (chr == NULL){break;}
        if (strchr(chr, '$')!=NULL){
          memmove(chr, chr+1, strlen(chr));
          chr = getenv(chr);
//           printf("%s ", chr);
        };
        arguments[i] = chr;
      }
      
//       for (i  = 0; i<MAX_COMMAND_LINE_ARGS; i++){
//         if (arguments[i] == NULL){break;}
//         printf("%s ", arguments[i]);
//       }
      char* command = arguments[0];
       
      
      
        // 2. Implement Built-In Commands
      if (strcmp(command, "echo") == 0){
        for(i = 1; i<MAX_COMMAND_LINE_ARGS; i++){
          if (arguments[i] == NULL){break;}
          printf("%s ", arguments[i]);
        }
      }else if (strcmp(command, "cd") == 0){
        
      }else if (strcmp(command, "pwd") == 0){
        char path[4096];
          char* directory = getcwd(path, sizeof(path));
          printf("%s ", directory);
      }else if (strcmp(command, "exit") == 0){
        exit(0);
      }else if (strcmp(command, "env") == 0){
        for (i = 0; environ[i]!=NULL; i++){
          printf("%s \n", environ[i]);
        }
      }else if (strcmp(command, "setenv") == 0){
        char* variable_value[2];
        char* rest = arguments[1];
        for (i = 0; i<2; i++){
          char *chr = strsep(&rest, "=");
          variable_value[i] = chr;
        }
        setenv(variable_value[0], variable_value[1], 1);
      }else{
        printf("Invalid command");
      }
      printf("\n");
      
      
      
      
    
        // 3. Create a child process which will execute the command line input

  
        // 4. The parent process should wait for the child to complete unless its a background process
      
      
        // Hints (put these into Google):
        // man fork
        // man execvp
        // man wait
        // man strtok
        // man environ
        // man signals
        
        // Extra Credit
        // man dup2
        // man open
        // man pipes
    }
    // This should never be reached.
    return -1;
}
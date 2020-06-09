#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>




// int counter = 2;
// void myHandler(int sig) {
// counter++;
// safe_printf("%d ", counter);
// exit(0);
// }
// int main() {
// signal(SIGUSR1, myHandler);
// printf("%d ", counter);
// if ((pid = fork()) == 0) {
// while(1) {};
// }
// kill(pid, SIGUSR1);
// waitpid(pid, NULL, 0);
// counter--;
// printf("%d ", counter);
// return 0;
// }



void CtrlZ_SignalHandler(int sig)
{
    //printf("Caught sigtstp");
    write(1, "Caught sigtstp\n361>", 66 );
    
}

void CtrlC_SignalHandler(int sig)
{
    
   // printf("Caught sigint");
    write(1, "Caught sigint\n361>", 66);
}

// From Signal (Lecture 10)
// int counter = 2;
// void myHandler(int sig)
// {
    
//     counter++;
//     safe_printf("%d ", counter);
//     exit(0);
    
// }

void shell_execute(char **args)
{
    
    // Took help from Professor in Office Hours.

    
    pid_t pid;
    
    pid = fork();
    
    if(pid == 0 )
    {
    //    printf("This is the child.\n");
        execv(args[0], args);
        exit(0);
    }
    
    
    else {
      //  printf("This is the parent.\n");
        int status;
        wait(&status);

	// Earlier when I called this print statement in the main the value of child was 127, when I added it here I got the required value for the status = 0.
	// TA helped
	 printf("pid:%d status:%d\n", pid, WEXITSTATUS(status));

    }
        
}    
 

    
        // Exec would be called for the child process
        
        // Using execvp where v stands for the vector value of string arguments
        // and p means instead of providing the full file path of the program to run, we’re going to give its name, 
        // and let the operating system search for the program in the path.
//         if(execvp(args[0], args) == -1)
//         {

         
//          // perror shows the systems error, it would only invoke if the 
//         // exec command would return -1 or it would return at all.
//             perror("Shell");
        
//         }
        
//         exit(EXIT_FAILURE);
    
//     }
    
//     // This would just check if the fork() would have any errors.
// //     if(pid < 0)
// //     {
     
     
// //         perror("Shell");
        
// //     }

//     if(wait(&status) < 0)
//       //  printf("Wait error");
    
//     else if ((status == 0))
//     {

//         printf("Exit");
//     }
    
//     // Else the Parent Process would work.
//     else {
        
//         printf("PID:%i status:%i\n", pid, WEXITSTATUS(status));
//     }
    
    
// }

int main(){

    // Most of the stuff is from Lab 4.
  //create some space for our strings
 
    
   // Statically allocated first, this goes on heap.
  //char args[20][100];
    
while(1){
    
    // I first declared it outside the while loop, now when I moved it inside I do not need to redclare it again and again.
     char line[500];
//    int status;
    // Allocating the memory for the array to be used
    // This would go on the stack.
    char **args = (char **)malloc(100 *sizeof(char*));
    
    
    for(int counter=0; counter < 1000; counter++)
    {
        // Rows and Columns
        args[counter] = (char *)malloc(20 * sizeof(char));
        
    }
    
    
    printf("CS361 > ");
    
    signal(SIGINT, CtrlC_SignalHandler);
    signal(SIGTSTP, CtrlZ_SignalHandler);
  //print prompt
  //printf("Please enter a string: ");
  //read line from terminal
  fgets(line, 500, stdin);

  //break the string up into words
  char *word = strtok(line, " ");
  int i = 0;
  while (word) {
     // printf("Reached here.\n");
   // printf("word: %s\n", word);
    //copy a word to the arg array
  //  strcpy(args[i], word);
      
      // When user enters the last element should be the terminating characther.
      
      
    //  int counter2 = 0;
      
      for (int counter2 = 0; counter2 < strlen(word); counter2++)
      {

          if(word[counter2] == '\n')
          {
                word[counter2] = '\0';
          }
	  
          
      }
    //  printf("Reached here returns.\n");
      
    //get next word
    strcpy(args[i], word);
    word = strtok(NULL, " ");
    i = i + 1;
  }
    
    args[i] = (char *)0;
    
 //   printf("Reached here rises again.\n");

  //print out our array
//   int j=0;
//   for (;j<i;j++){
//     printf("args[%d]: %s\n", j, args[j]);
//   }
    
    shell_execute(args);
    
        if(strcmp(args[0], "exit")== 0 )
    {

        break;
    }
//    printf("PID:%i status:%i\n", getpid(), WEXITSTATUS(status));

//	 printf("My child has died with status %d. :(\n", WEXITSTATUS(status));

}
}

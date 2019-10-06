#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int arg, char** args){

  int n = (arg - 1)/5;
  int p;
  int pipefd[n][2];
  int pid[n];

  for(int i = 0; i<n; i++){
    if(pipe(pipefd[i]) == -1){
      perror("pipe :(");
      return 1;
    }

   if((p = fork()) == -1){
      perror("fork :(");
      return 1;
    }

    //First Child
    else if(p == 0 && i == 0){
	if(dup2(pipefd[i][1], STDOUT_FILENO)==-1){
	  perror("dup2 failed\n");
        }
        close(pipefd[i][1]);
    }

    //Last Child
    else if(i == (n-1) && p == 0){
      dup2(pipefd[i-1][0], STDIN_FILENO);
      close(pipefd[i-1][0]);
    }

    //Rest of the children
     else if(p == 0){
      dup2(pipefd[i][1], STDOUT_FILENO);
      dup2(pipefd[i-1][0], STDIN_FILENO);
      close(pipefd[i][1]);
      close(pipefd[i-1][0]);
    }

    //Parent
    else if(p != 0){
      if (i == 0){
	close(pipefd[i][1]);
      }
      else if (i == n-1){
	close(pipefd[i-1][0]);
      }
      else{
	close(pipefd[i][1]);
	close(pipefd[i-1][0]);
      }
    }

    pid[i] = p;
    if(p==0){
      if(execlp("./biquad", "biquad", args[5*i+1], args[5*i+2], args[5*i+3], args[5*i+4], args[5*i+5], (char*)NULL)==-1){
        perror("biquad fail :(");
        return 1;
      }
    }
  }
  for(int j = 0; j<n; j++){
      waitpid(pid[j], NULL, 0);
  }
  return 0;
}

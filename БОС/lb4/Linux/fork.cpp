#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
  int pid = fork();
  
  if (pid < 0){
    printf("error");
  } else if (pid == 0){
    execl(argv[1], argv[1], argv[2], NULL);
  } else {
    int status;
    waitpid(pid, &status, 0);
  }
  return 0;
}


// text -parametr
// /bin/firefox -private-window

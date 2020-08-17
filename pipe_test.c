#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int pipedes[2];

int main (int argc, char *argv[], char *envp[]) {

  pid_t pid;
  int i;
  char *argvs[] = { 0, NULL};

     if (argc < 3) {
        printf ("usage: %s prog1 prog2\n", argv[0]);
        return 1;
        }

    for(i = 1; i < argc; i++){
    pipe(pipedes);
    if (!(pid=fork())){
      argvs[0]=argv[i];
      dup2 (pipedes[1], 1);
      close (pipedes[0]);
      execvp (argvs[0], argvs);
	  exit(0);
    }
    else{
		argvs[0] = argv[i + 1];
		dup2 (pipedes[0], 0);
		close (pipedes[1]);
		execvp (argvs[0], argvs);
    }
	close (pipedes[0]);
    close (pipedes[1]);
    }
  	
  return 0;
}

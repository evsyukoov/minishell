#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int pipedes[2];

int main (int ac, char *av[], char *envp[]) {

  pid_t pid;
  int i;
  int pfd[2], input;

    for (int i = 1; i < ac; i++) {
    pipe(pfd);

    if (!(pid = fork())) {
      //      printf("child %d of %d grp %d\n", (int)getpid(), (int)getppid(), (int)getpgrp());

      if (i != 1) {      // first command read inhereted stdin
        dup2(input, 0);  //   any other read pfd[0] from previous iteration
        close(input);
      }
      if (i != ac - 1)   // last command write to inhereted stdout
        dup2(pfd[1], 1); //   any other write to current pfd[1]
      close(pfd[0]);
      close(pfd[1]);

      char *argv [2] = {av[i], NULL};
      execvp(av[i], argv);
      fprintf(stderr, "command `%s` not found, terminate\n", av[i]);
      exit(-1);
    }

    //    printf("fork to %d\n", (int)pid);
    //puts(">>>"); getchar();

    if (i != 1)
      close(input);
    close(pfd[1]);
    input = pfd[0];  // the next member of commands pipe will read this fd

    // Well,  the icing on the cake

  }
	close(input);
  return 0;
}

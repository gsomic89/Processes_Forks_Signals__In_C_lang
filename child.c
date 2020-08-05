#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int lil_cubby_bear = 0;

void SigTermHandler(int sig){
lil_cubby_bear = 1;
  }

int main(int argc, char* argv[]){
  srand(getpid());

  char* x;
  x = argv[1];

  int     haveFoundPin    = 0;
  int     numAttempts     = 0;

  struct sigaction sa;
  memset(&sa, '\0', sizeof(sa));
  sa.sa_handler = SigTermHandler;
  sigaction(SIGTERM, &sa,NULL);

  while (lil_cubby_bear == 0 && !haveFoundPin) {

    sleep(1);

    numAttempts++;
    switch(rand() % 4) 
      {
      case 0 : printf("%s %d : I cant find it anywhere!.\"\n", x,getpid());    break;
      case 1 : printf("%s %d : Still NOTHING .\"\n", x,getpid());     break;
      case 2 : printf("%s %d : Ridiculous, still nothing.\"\n", x,getpid());    break;
      case 3 : printf("%s %d : JACKPOT GOT IT.\"\n", x,getpid());
	kill(getppid(),SIGUSR1);
	haveFoundPin = 1;
	break;

      }
  }
  sleep(1);
  if  (haveFoundPin == 1)
  {
      printf("%s %d: Winner winner chicken dinner, i win $20!\"\n", x, getpid());
      }
      else
      {
      printf("%s %d: RATS! I lost\"\n", x, getpid());
      }
  return(EXIT_SUCCESS);
        }

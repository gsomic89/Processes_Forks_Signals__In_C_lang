#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#define child "./child"


const char* FEMALE_NAME_ARRAY[]
= {"Taylor",
   "Anna",
   "Bertha",
      "Pamela"
};

const char* MALE_NAME_ARRAY[]
= {"Sam",
   "George",
   "Peter",
      "David"
};

int big_momma = 0;

const int       NUM_CHILDREN    = 2;

void SigChildHandler (int    sig){

    big_momma      = 1;
    printf("Mother: \"Thank you for finding my pin, here is $20.\"\n");

  }

int main(){

srand(getpid());

pid_t   childIdArray[NUM_CHILDREN];
        int i=0;
        int a =0;

struct sigaction   sa;
memset(&sa,'\0',sizeof(sa));
sa.sa_handler = SigChildHandler;
sigaction(SIGUSR1,&sa,NULL);

printf("Mother: \"I will give $20 to whomever finds my "
         "decorative pin in the pile of grass.  Go!\"\n");

while(i<NUM_CHILDREN){
  if ((childIdArray[i]=fork())==0){
      const char**    nameArray;
      const char*     nameCPtr;

      nameArray       = (i == 0) ? FEMALE_NAME_ARRAY : MALE_NAME_ARRAY;
      nameCPtr        = nameArray[ rand() % (sizeof(FEMALE_NAME_ARRAY) / sizeof(const char*)) ];
      execl(child,child,nameCPtr,NULL);
}

  i++;
}
while (big_momma == 0){
    sleep(1);
}
while(a<NUM_CHILDREN){
    kill(childIdArray[a],SIGTERM);
    wait(NULL);
    a++;
}
return(EXIT_SUCCESS);
}

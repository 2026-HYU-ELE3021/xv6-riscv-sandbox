#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid = fork();
  if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }

  if(pid == 0){
    // child
    for(int i = 0; i < 100; i++){
      printf("Child\n");
      // toggle below function call
      // yield();
    }
  } else {
    // parent
    for(int i = 0; i < 100; i++){
      printf("Parent\n");
      // toggle below function call
      // yield();
    }
    wait(0);
  }
  exit(0);
}

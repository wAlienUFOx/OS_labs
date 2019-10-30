#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  int fd[2], rv;
  pid_t pid;
  int arr[4];
  char op;
  if (pipe(fd) < 0){
        printf("Cant create pipe\n");
        return -1;
    }
  pid = fork();
  if(pid == -1){
    printf("Can\'t fork\n");
    return -1;
  }else if(pid == 0){
    read(fd[0], arr, 4 * sizeof(int));
    close(fd[0]);
    if (arr[1] == 1)
      arr[3] = arr[0] + arr[2];
    if (arr[1] == -1)
      arr[3] = arr[0] - arr[2];
    write(fd[1], arr, 4 * sizeof(int));
    close(fd[1]);
    exit(0);
  }else{
    scanf("%d%c%d", &arr[0], &op, &arr[2]);
    if (op == '+')
      arr[1] = 1;
    if (op == '-')
      arr[1] = -1;
    write(fd[1], arr, 4 * sizeof(int));
    close(fd[1]);

    wait(&rv);
    if(WEXITSTATUS(rv) != 0){
      printf("Child error\n");
      return -2;
    }
    
    read(fd[0], arr, 4 * sizeof(int));
    close(fd[0]);
    printf("%d %c %d = %d\n", arr[0], op, arr[2], arr[3]);
  }
  return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int fd1[2], fd2[2];
  pid_t pid;
  int arr[4];
  char op;
  if (pipe(fd1) < 0 || pipe (fd2) < 0){
        printf("Cant create pipes\n");
        return -1;
    }
  pid = fork();
  if(pid == -1){
    printf("Can\'t fork\n");
    return -1;
  }else if(pid == 0){
    close(fd1[1]);
    close(fd2[0]);
    while(read(fd1[0], arr, 4 * sizeof(int))){
      if (arr[1] == 1)
	arr[3] = arr[0] + arr[2];
      if (arr[1] == -1)
	arr[3] = arr[0] - arr[2];
      write(fd2[1], arr, 4 * sizeof(int));
    }
    close(fd1[0]);
    close(fd2[1]);
  }else{
    close(fd1[0]);
    close(fd2[1]);
    while(scanf("%d %c %d", &arr[0], &op, &arr[2]) == 3) {
      if (op == '+')
	arr[1] = 1;
      if (op == '-')
	arr[1] = -1;
      write(fd1[1], arr, 4 * sizeof(int));
      read(fd2[0], arr, 4 * sizeof(int));
      printf("%d %c %d = %d\n", arr[0], op, arr[2], arr[3]);
    }
    close(fd1[1]);
    close(fd2[0]);
  }
  return 0;
}


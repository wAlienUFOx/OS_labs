#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>


int main()
{
  FILE* tmp_file = fopen("file", "w+");
  if (!tmp_file) {
    printf("can`t open file\n");
    return -1;
  }
  int fd = fileno(tmp_file);
  write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 20);
  int* file_ptr = mmap(NULL, 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (file_ptr == MAP_FAILED) {
    printf("failed to map\n");
    return -1;
  }
  sem_t *sem_calc = sem_open("/calc", O_CREAT, 777, 0);
  sem_t *sem_out = sem_open("/out", O_CREAT, 777, 0);
  if (sem_calc == SEM_FAILED || sem_out == SEM_FAILED) {
    printf("Cant create semaphore(s)\n");
    return -1;
  }
  sem_unlink("/calc");
  sem_unlink("/out");
  pid_t pid;
  int arr[4];
  char op;
  pid = fork();
  if(pid == -1){
    printf("Can\'t fork\n");
    return -1;
  }else if(pid == 0){
    while(1){
      sem_wait(sem_calc);
      if(file_ptr[4] == 1){
	break;
      }
      for(int i = 0; i < 3; i++){
	arr[i] = file_ptr[i];
      }
      if (arr[1] == 1)
	arr[3] = arr[0] + arr[2];
      if (arr[1] == -1)
	arr[3] = arr[0] - arr[2];
      file_ptr[3] = arr[3];
      sem_post(sem_out);
    }
    sem_close(sem_calc);
    sem_close(sem_out);
    munmap(file_ptr, 20);
    close(fd);
  }else{
    while(scanf("%d %c %d", &arr[0], &op, &arr[2]) == 3) {
      if (op == '+')
	arr[1] = 1;
      if (op == '-')
	arr[1] = -1;
      for(int i = 0; i < 3; i++){
	file_ptr[i] = arr[i];
      }
      sem_post(sem_calc);
      sem_wait(sem_out);
      arr[3] = file_ptr[3];
      printf("%d %c %d = %d\n", arr[0], op, arr[2], arr[3]);
    }
    file_ptr[4] = 1;
    sem_post(sem_calc);
    sem_close(sem_calc);
    sem_close(sem_out);
    close(fd);
 }
return 0;
}

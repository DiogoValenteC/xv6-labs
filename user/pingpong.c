
#include "kernel/types.h"
#include "user/user.h"

int main() {
  int p1[2], p2[2];
  pipe(p1); // pai -> filho
  pipe(p2); // filho -> pai

  int pid = fork();
  if (pid < 0) {
    fprintf(2, "fork falhou\n");
    exit(1);
  }

  if (pid == 0) {
    // filho
    char buf;
    read(p1[0], &buf, 1);
    printf("%d: received ping\n", getpid());
    write(p2[1], "!", 1);
    exit(0);
  } else {
    // pai
    write(p1[1], "!", 1);
    char buf;
    read(p2[0], &buf, 1);
    printf("%d: received pong\n", getpid());
    wait(0);
  }

  exit(0);
}
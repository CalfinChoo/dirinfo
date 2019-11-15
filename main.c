#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>

int main() {
  DIR * d = opendir(".");
  if (d == NULL) {
        printf("Could not open current directory");
        return 0;
  }
  struct dirent * p = readdir(d);
  while (p != NULL) {
    printf("%s, %d\n", p->d_name, p->d_type);
    p = readdir(d);
  }

}

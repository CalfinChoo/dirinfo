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
  struct dirent * p = readdir(d), c = readdir(d);
  int num_files = 0, num_dirs = 0;
  while (c != NULL) {
    if (c->d_type == 4) num_dirs++;
    else num_files++;
    c = readdir(d);
  }
  char directories[num_dirs][256], files[num_files][256];
  int d_count = 0, f_count = 0;
  while (p != NULL) {
    // printf("%s, %d\n", p->d_name, p->d_type);
    if (p->d_type == 4) {
      strcpy(directories[d_count], p->d_name);
      d_count++;
    }
    else {
      strcpy(files[f_count], p->d_name);
      f_count++;
    }
    p = readdir(d);
  }


  printf("Statistics for directory: .\n");
  printf("Total directory size: placeholder\n");
  printf("Directories:\n");
  int i = 0;
  for (; i < sizeof(directories)/sizeof(directories[0]); i++) {
    printf("%s\n", directories[i]);
  }
  printf("Regular files:\n");
  i = 0;
  for (; i < sizeof(files)/sizeof(files[0]); i++) {
    printf("%s\n", directories[i]);
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char * argv[]) {
  DIR * d;
  char s[256];
  if (argc == 1) {
    fgets(s, sizeof(s), stdin);
    size_t ln = strlen(s) - 1;
    if (s[ln] == '\n') s[ln] = '\0';
  }
  else strcpy(s, argv[1]);
  d = opendir(s);
  if (d == NULL) {
    printf("%s\n", strerror(errno));
        return 0;
  }
  struct dirent * p = readdir(d);
  int num_files = 0, num_dirs = 0;
  int size = 0;
  while (p != NULL) {
    if (p->d_type == 4) num_dirs++;
    else {
      num_files++;
      struct stat sb;
      stat(p->d_name, &sb);
      size += sb.st_size;
    }
    p = readdir(d);
  }
  char directories[num_dirs][256], files[num_files][256];
  closedir(d);
  d = opendir(s);
  p = readdir(d);
  int d_count = 0, f_count = 0;
  while (p != NULL) {
    // printf("%s, %d\n", p->d_name, p->d_type);
    if ((int)p->d_type == 4) {
      strcpy(directories[d_count], p->d_name);
      d_count++;
    }
    else {
      strcpy(files[f_count], p->d_name);
      f_count++;
    }
    p = readdir(d);
  }


  printf("Statistics for directory: %s\n", s);
  char buffer[50];
  char metric[8];
  int m = 1;
  if (size / 1000000000 > 0) {
    sprintf(metric, "%s", "GB");
    m = 1000000000;
  }
  else if (size / 1000000 > 0) {
    sprintf(metric, "%s", "MB");
    m = 1000000;
  }
  else if (size / 1000 > 0) {
    sprintf(metric, "%s", "KB");
    m = 1000;
  }
  else sprintf(metric, "%s", "B");
  sprintf(buffer, "%0.1lf %s", (double)size/m, metric);
  printf("Total directory size: %s\n", buffer);
  printf("Directories:\n");
  int i = 0;
  for (; i < sizeof(directories)/sizeof(directories[0]); i++) {
    printf("%s\n", directories[i]);
  }
  printf("Regular files:\n");
  i = 0;
  for (; i < sizeof(files)/sizeof(files[0]); i++) {
    printf("%s\n", files[i]);
  }
}

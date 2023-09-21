#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
  int year, month, day;

  // scanf("%d-%d-%d", &year, &month, &day);
  FILE *fp = fopen("date.txt", "r");
  fscanf(fp, "%d-%d-%d", &year, &month, &day);
  fclose(fp);
  // scanf(buf, "%d-%d-%d", &year, &month, &day);

  printf("printf: %d-%d-%d\n", year, month, day);
  fprintf(stdout, "fprintf: %d-%d-%d\n", year, month, day);
  // FILE *fp;
  // fp = fopen("out.txt", "w");
  // fprintf(fp, "%d-%d-%d\n", year, month, day);
  // fclose(fp);

  char buf[BUFSIZE];
  sprintf(buf, "sprintf: %d-%d-%d", year, month, day);
  // size_t len = 20;
  // snprintf(buf, len, "snprintf: %d-%d-%d", year, month, day);
  puts(buf);
  // 实现将多个字符组合为字符串

  exit(0);
}
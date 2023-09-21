#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp = fopen("date.txt", "w");
  fprintf(fp, "%s\n%s\n%s", "2019:08:13", "2021:05:20", "2023:09:16");

  fseek(fp, -13L, SEEK_END);
  printf("%ld\n", ftell(fp));
  fprintf(fp, "%s", "07");

  rewind(fp);
  fseek(fp, 5L, SEEK_CUR);
  printf("%ld\n", ftell(fp));
  fprintf(fp, "%s", "12");

  fclose(fp);
  exit(0);
}
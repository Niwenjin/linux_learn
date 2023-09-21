#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
  FILE *fps, *fpd;
  char buf[BUFSIZ];
  int n;

  fps = fopen("read.txt", "r");
  fpd = fopen("write.txt", "w");

  //   while (fread(buf, 1, BUFSIZE, fps))
  //     fwrite(buf, 1, BUFSIZE, fpd);

  //   while ((n = fread(buf, 100, BUFSIZE, fps)) > 0)
  //     fwrite(buf, 100, n, fpd);

  while ((n = fread(buf, 1, BUFSIZE, fps)) > 0)
    fwrite(buf, 1, n, fpd);

  fclose(fps);
  fclose(fpd);
  exit(0);
}
#ifndef CLFILE_H
#define CLFILE_H
#include <string>
#include <sys/types.h>

#define MAX_SIZE 4096

class CLFile {
public:
  CLFile();
  ~CLFile();
  int readwithBuf(char *, int, int);
  int writewithBuf(char *, int, int);
  int lseek(off_t, int);

private:
  char readbuf[MAX_SIZE];
  char writebuf[MAX_SIZE];
  int open(const char *);
  int close(int);
};
#endif
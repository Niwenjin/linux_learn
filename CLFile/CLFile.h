#ifndef CLFILE_H
#define CLFILE_H
#include <sys/types.h>

#define MAX_SIZE 4096

class CLFile {
public:
  CLFile(const char *);
  ~CLFile();
  int readwithBuf(char *, int, int);
  int writewithBuf(char *, int, int);
  off_t seek(off_t);
  off_t seek(off_t, int);

private:
  int m_fd;
  off_t m_pos;
  off_t m_readbufpos;
  off_t m_writebufpos;
  int m_writebufsize;
  char readbuf[MAX_SIZE];
  char writebuf[MAX_SIZE];
  int openfile(const char *);
  int closefile();
  int flushwritebuf();
};
#endif
#ifndef CLFILE_H
#define CLFILE_H
#include <sys/types.h>

#define MAX_SIZE 4096

class CLFile {
public:
  CLFile(const char *);
  ~CLFile();
  int readwithBuf(char *, int);
  int writewithBuf(const char *, int);
  off_t seek(off_t);
  off_t seek(off_t, int);

private:
  int m_fd;
  off_t m_pos;
  off_t m_bufpos;
  int m_bufsize;
  char buf[MAX_SIZE];
  bool m_iswrite;
  int openfile(const char *);
  int closefile();
  void flushbuf();
  void renewbuf();
};
#endif
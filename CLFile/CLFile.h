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
  off_t seekwithBuf(off_t, int);

private:
  int m_fd;
  off_t m_pos;
  off_t m_bufpos;
  int m_bufsize;
  char buf[MAX_SIZE];
  bool m_iswrite;
  int m_countr = 1, m_countw = 0, m_counts = 0;
  int openfile(const char *);
  int closefile();
  off_t seek(off_t, int);
  void flushbuf();
  void renewbuf();
};
#endif
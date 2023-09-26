#include "CLFile.h"
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

CLFile::CLFile(const char *filename)
    : m_pos(0), m_readbufpos(-1), m_writebufsize(0) {
  m_fd = openfile(filename);
  if (m_fd == -1)
    std::cerr << "open" << filename << "failed" << std::endl;
}

CLFile::~CLFile() { closefile(); }

int CLFile::openfile(const char *filename) { return open(filename, O_RDWR); }

int CLFile::closefile() { return close(m_fd); }

int CLFile::readwithBuf(char *buf, int fd, int size) {
  if (m_pos + size > m_writebufpos && m_pos < m_writebufpos + MAX_SIZE)
    flushwritebuf();
  if (size > MAX_SIZE)
    return read(m_fd, buf, size);
  if (m_readbufpos < 0 || m_pos < m_readbufpos ||
      m_pos + size > m_readbufpos + MAX_SIZE) {
    read(m_fd, readbuf, MAX_SIZE);
    seek(-MAX_SIZE);
    m_readbufpos = m_pos;
  }

  int i, pos = m_pos - m_readbufpos;
  for (i = 0; i < size; i++)
    buf[i] = readbuf[pos + i];
  buf[i] = '\0';

  seek(size);

  return size;
}

int CLFile::writewithBuf(char *buf, int fd, int size) {
  if (m_pos + size > m_readbufpos && m_pos < m_readbufpos + MAX_SIZE)
    m_readbufpos = -1;
  if (size > MAX_SIZE)
    write(m_fd, buf, size);
  if (m_writebufpos + size > MAX_SIZE)
    flushwritebuf();
  return size;
}

int CLFile::flushwritebuf() {
  int size = write(m_fd, writebuf, m_writebufsize);
  seek(-size);
  return size;
}

off_t CLFile::seek(off_t offset) {
  m_pos = lseek(m_fd, offset, SEEK_CUR);
  return m_pos;
}

off_t CLFile::seek(off_t offset, int whence) {
  m_pos = lseek(m_fd, offset, whence);
  return m_pos;
}
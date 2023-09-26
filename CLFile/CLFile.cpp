#include "CLFile.h"
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

CLFile::CLFile(const char *filename)
    : m_pos(0), m_bufpos(-1), m_iswrite(false) {
  m_fd = openfile(filename);
  if (m_fd < 0)
    std::cerr << "open " << filename << " failed" << std::endl;
}

CLFile::~CLFile() {
  flushbuf();
  closefile();
}

int CLFile::openfile(const char *filename) {
  int fd = open(filename, O_RDWR | O_CREAT);
  return fd;
}

int CLFile::closefile() { return close(m_fd); }

int CLFile::readwithBuf(char *readbuf, int size) {
  if (size > MAX_SIZE) {
    seek(m_pos, SEEK_SET);
    size = read(m_fd, readbuf, MAX_SIZE);
    m_pos += size;
    return size;
  }
  // 需要刷新缓冲
  if (m_bufpos < 0 || m_pos < m_bufpos || m_pos + size > m_bufpos + MAX_SIZE) {
    flushbuf();
    renewbuf();
    m_iswrite = false;
  }

  size = snprintf(readbuf, size, "%s", &buf[m_pos - m_bufpos]);
  m_pos += size;

  return size;
}

int CLFile::writewithBuf(const char *writebuf, int size) {
  if (size > MAX_SIZE) {
    seek(m_pos, SEEK_SET);
    write(m_fd, writebuf, size);
    m_pos += size;
    return size;
  }
  if (m_bufpos < 0 || m_pos < m_bufpos || m_pos + size > m_bufpos + MAX_SIZE) {
    flushbuf();
    renewbuf();
  }

  size = snprintf(&buf[m_pos - m_bufpos], size, "%s", writebuf);
  m_pos += size;
  if (m_pos > m_bufpos + m_bufsize)
    m_bufsize = m_pos - m_bufpos;
  m_iswrite = true;

  return size;
}

void CLFile::flushbuf() {
  lseek(m_fd, m_bufpos, SEEK_SET);
  if (m_iswrite)
    write(m_fd, buf, m_bufsize);
}

void CLFile::renewbuf() {
  seek(m_pos, SEEK_SET);
  m_bufsize = read(m_fd, buf, MAX_SIZE);
  m_bufpos = m_pos;
}

off_t CLFile::seek(off_t offset) {
  m_pos += offset;
  return m_pos;
}

off_t CLFile::seek(off_t offset, int whence) {
  if (whence == SEEK_CUR)
    m_pos += offset;
  else if (whence == SEEK_SET)
    m_pos = offset;
  else
    return -1;
  return m_pos;
}
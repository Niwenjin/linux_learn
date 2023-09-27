#include "CLFile.h"
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

CLFile::CLFile(const char *filename) : m_pos(0), m_bufpos(0), m_iswrite(false) {
  m_fd = openfile(filename);
  if (m_fd < 0)
    std::cerr << "open " << filename << " failed" << std::endl;
  m_bufsize = read(m_fd, buf, MAX_SIZE);
}

CLFile::~CLFile() {
  flushbuf();
  closefile();
  std::cout << "Read: " << m_countr << std::endl
            << "Write: " << m_countw << std::endl
            << "Lseek: " << m_counts << std::endl;
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
    m_countr++;
    m_pos += size;
    return size;
  }

  // 需要刷新缓冲
  if (m_pos < m_bufpos || m_pos + size > m_bufpos + MAX_SIZE) {
    flushbuf();
    renewbuf();
    m_iswrite = false;
  }

  if (m_bufsize != MAX_SIZE && m_pos > m_bufpos + m_bufsize) {
    std::cerr << "Read out_of_range" << std::endl;
    return -1;
  }
  
  memcpy(readbuf, &buf[m_pos - m_bufpos], size);
  m_pos += size;

  return size;
}

int CLFile::writewithBuf(const char *writebuf, int size) {
  if (size > MAX_SIZE) {
    seek(m_pos, SEEK_SET);
    write(m_fd, writebuf, size);
    m_countw++;
    m_pos += size;
    return size;
  }
  if (m_pos < m_bufpos || m_pos + size > m_bufpos + MAX_SIZE) {
    flushbuf();
    renewbuf();
  }

  memcpy(&buf[m_pos - m_bufpos], writebuf, size);
  m_pos += size;

  if (m_pos > m_bufpos + m_bufsize)
    m_bufsize = m_pos - m_bufpos;
  m_iswrite = true;

  return size;
}

off_t CLFile::seekwithBuf(off_t offset, int whence) {
  if (whence == SEEK_CUR)
    m_pos += offset;
  if (whence == SEEK_SET)
    m_pos = offset;
  return m_pos;
}

void CLFile::flushbuf() {
  if (m_iswrite) {
    seek(m_bufpos, SEEK_SET);
    write(m_fd, buf, m_bufsize);
    m_countw++;
  }
}

void CLFile::renewbuf() {
  seek(m_pos, SEEK_SET);
  m_bufsize = read(m_fd, buf, MAX_SIZE);
  m_countr++;
  m_bufpos = m_pos;
}

off_t CLFile::seek(off_t offset, int whence) {
  off_t pos = lseek(m_fd, offset, whence);
  m_counts++;
  return pos;
}
#include "CLFile.h"
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
  CLFile f("file.txt");
  char s[30];

  f.readwithBuf(s, 20);
  puts(s);
  
  f.seekwithBuf(0, SEEK_SET);
  f.writewithBuf("hello world!", 12);
  f.seekwithBuf(1024, SEEK_CUR);
  f.seekwithBuf(1024, SEEK_CUR);
  f.seekwithBuf(-2060, SEEK_CUR);
  f.readwithBuf(s, 20);
  puts(s);

  f.seekwithBuf(0, SEEK_SET);
  f.readwithBuf(s, 10);
  f.seekwithBuf(1024, SEEK_CUR);
  f.readwithBuf(s, 20);
  f.seekwithBuf(-50, SEEK_CUR);
  f.readwithBuf(s, 10);
  f.seekwithBuf(300, SEEK_CUR);
  f.readwithBuf(s, 5);
  f.seekwithBuf(-1000, SEEK_CUR);
  f.readwithBuf(s, 20);

  char large[5000];
  f.seekwithBuf(2048, SEEK_SET);
  f.readwithBuf(large, MAX_SIZE);
  puts(large);

  f.writewithBuf(large, MAX_SIZE);
  f.seekwithBuf(-MAX_SIZE, SEEK_CUR);
  f.readwithBuf(s, 20);
  puts(s);

  f.seekwithBuf(6000, SEEK_SET);
  f.writewithBuf("hello ", 6);
  f.writewithBuf("world!", 6);
  f.seekwithBuf(-12, SEEK_CUR);
  f.readwithBuf(s, 10);
  puts(s);

  return 0;
}
#include "CLFile.h"
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
  // 创建CLFile对象并打开"file.txt"文件
  CLFile f("file.txt");
  char s[30];

  // 在缓冲内读20个字节
  f.readwithBuf(s, 20);
  puts(s);            // 打印读结果
  
  // 写文件并多次改变偏移量
  f.seekwithBuf(0, SEEK_SET);
  f.writewithBuf("hello world!", 12);
  f.seekwithBuf(1024, SEEK_CUR);
  f.seekwithBuf(1024, SEEK_CUR);
  f.seekwithBuf(-2060, SEEK_CUR);
  // 改变偏移量后读
  f.readwithBuf(s, 20);
  puts(s);            // 打印读结果

  // 缓冲内多次读
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

  // 读超出缓冲区大小
  char large[5000];
  f.seekwithBuf(2048, SEEK_SET);
  f.readwithBuf(large, MAX_SIZE);
  puts(large);     // 打印读结果

  // 写超出缓冲区大小
  f.writewithBuf(large, MAX_SIZE);
  f.seekwithBuf(-MAX_SIZE, SEEK_CUR);
  f.readwithBuf(s, 20);
  puts(s);            // 打印读结果

  // 改变偏移量至缓冲区外并读写
  f.seekwithBuf(6000, SEEK_SET);
  f.writewithBuf("hello ", 6);
  f.writewithBuf("world!", 6);
  f.seekwithBuf(-12, SEEK_CUR);
  f.readwithBuf(s, 10);
  puts(s);             // 打印读结果

  return 0;
}
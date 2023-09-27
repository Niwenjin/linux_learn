#include "CLFile.h"
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
  CLFile f("file.txt");
  char s[10];
  f.readwithBuf(s, 20);
  cout << s << endl;
  f.writewithBuf("hello ", 6);
  f.writewithBuf("world!", 6);
  f.seekwithBuf(20, SEEK_SET);
  f.readwithBuf(s, 10);
  cout << s << endl;
  return 0;
}
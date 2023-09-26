#include "CLFile.h"
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
  CLFile f("hello.txt");
  f.writewithBuf("hello ", 10);
  f.writewithBuf("world!", 10);
  char s[10];
  f.seek(0, SEEK_SET);
  f.readwithBuf(s, 30);
  cout << s << endl;
  return 0;
}
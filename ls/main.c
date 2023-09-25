#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

char *getmode(mode_t);
char *gettime(struct timespec);

int main(int argc, char *argv[]) {
  // 打开当前目录
  DIR *dirp = opendir(".");
  // 出错检查
  if (NULL == dirp) {
    fprintf(stderr, "fail to open current directory\n");
    return -1;
  }

  struct stat buf;
  struct dirent *dir = NULL;

  while ((dir = readdir(dirp)) != NULL) {
    // 忽略隐藏文件
    if (dir->d_name[0] == '.')
      continue;
    lstat(dir->d_name, &buf);

    // 读取各项所需的文件属性

    // 自定义函数获取文件类型及权限位
    char *mode = getmode(buf.st_mode);
    unsigned nlink = buf.st_nlink;
    char *uname = getpwuid(buf.st_uid)->pw_name;
    char *gname = getgrgid(buf.st_gid)->gr_name;
    long size = buf.st_size;
    // 自定义函数格式化文件时间
    char *mtime = gettime(buf.st_mtim);
    char *filename = dir->d_name;

    // 格式化打印各项文件属性
    printf("%s %d %s %s %ld %s %s\n", mode, nlink, uname, gname, size, mtime,
           filename);
  }
  closedir(dirp);
  return 0;
}

char *getmode(mode_t st_mode) {
  static char mode[11];

  // 获取文件类型
  char type;
  switch (st_mode & S_IFMT) {
  case S_IFIFO:
    type = 'p';
    break;
  case S_IFCHR:
    type = 'c';
    break;
  case S_IFDIR:
    type = 'd';
    break;
  case S_IFLNK:
    type = 'l';
    break;
  case S_IFSOCK:
    type = 's';
    break;
  case S_IFBLK:
    type = 'b';
    break;
  case S_IFREG:
    type = '-';
    break;
  default:
    break;
  }
  mode[0] = type;

  // 获取文件权限
  
  int k = 0400;
  int i = 0;
  // 逐位判断文件权限
  while (i < 9) {
    // 将读、写、执行权限打印为'r''w''x'
    mode[++i] = (st_mode & k) == k ? 'r' : '-';
    k >>= 1;
    mode[++i] = (st_mode & k) == k ? 'w' : '-';
    k >>= 1;
    mode[++i] = (st_mode & k) == k ? 'x' : '-';
    k >>= 1;
  }
  mode[10] = '\0';
  return mode;
}

char *gettime(struct timespec st_mtim) {
  static char time[13];
  struct tm tm;
  // 获取timespec结构中的秒级精度时间并转换为tm结构
  localtime_r(&st_mtim.tv_sec, &tm);
  // 将tm结构时间格式化为“月 日 时：分”的格式返回
  strftime(time, sizeof(time), "%b %d %H:%M", &tm);
  return time;
}
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
  DIR *dirp = opendir(".");
  if (NULL == dirp) {
    fprintf(stderr, "fail to open current directory\n");
    return -1;
  }

  struct stat buf;
  struct dirent *dir = NULL;

  while ((dir = readdir(dirp)) != NULL) {
    if (dir->d_name[0] == '.')
      continue;
    stat(dir->d_name, &buf);

    char *mode = getmode(buf.st_mode);
    unsigned nlink = buf.st_nlink;
    char *uname = getpwuid(buf.st_uid)->pw_name;
    char *gname = getgrgid(buf.st_gid)->gr_name;
    long size = buf.st_size;
    char *mtime = gettime(buf.st_mtim);
    char *filename = dir->d_name;

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
  while (i < 9) {
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
  localtime_r(&st_mtim.tv_sec, &tm);

  char *month;
  switch (tm.tm_mon) {
  case (0):
    month = "Jan";
    break;
  case (1):
    month = "Feb";
    break;
  case (2):
    month = "Mar";
    break;
  case (3):
    month = "Apr";
    break;
  case (4):
    month = "May";
    break;
  case (5):
    month = "Jun";
    break;
  case (6):
    month = "Jul";
    break;
  case (7):
    month = "Aug";
    break;
  case (8):
    month = "Sep";
    break;
  case (9):
    month = "Oct";
    break;
  case (10):
    month = "Nov";
    break;
  case (11):
    month = "Dec";
    break;
  }

  sprintf(time, "%s %d %d:%d", month, tm.tm_mday, tm.tm_hour, tm.tm_min);
  return time;
}
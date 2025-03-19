#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int overwrite(int t_fd, int r_fd, struct stat t_file) {
  int buffer[t_file.st_size];

  read(r_fd, &buffer, t_file.st_size);
  write(t_fd, buffer, t_file.st_size);

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: srm [path_to_file]");
    return -1;
  }

  struct stat t_fileStats;
  int fd = open("/dev/random", O_RDONLY);
  int fd_t = open(argv[1], O_WRONLY, 0644);

  if (fd == -1) {
    printf("Error while reading /dev/zero");
    return 1;
  }
  if (fd_t == -1) {
    printf("Error while reading target file");
    return 1;
  }
  if (stat(argv[1], &t_fileStats) == -1) {
    printf("Error while getting file info");
    return 1;
  }

  for (int i = 0; i < 5; i++) {
    overwrite(fd_t, fd, t_fileStats);
  }

  close(fd);
  close(fd_t);

  if (remove(argv[1]) == -1) {
    printf("Error while deleting file");
    return 1;
  }

  return 0;
}

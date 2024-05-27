#include <stdio.h>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char *argv[]) {
  execl(argv[1], argv[1], argv[2], NULL); // "/bin/firefox" = argv[0]
  return 0;
}
// ./execl text -parametr
// /bin/firefox -private-window

//which firefox

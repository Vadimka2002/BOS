#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  execl(argv[1], argv[1], argv[2], NULL); 
  return 0;
}
// exec "C:\Program Files\Google\Chrome\Application\chrome.exe" -incognito
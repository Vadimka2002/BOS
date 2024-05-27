#include <string>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char *argv[]) {
  std::string str = argv[1]; // "/bin/firefox"
  for (int i = 2; i < argc; ++i){
	str = str + " " + argv[i]; 
  }
  system(str.c_str());
  return 0;
}
// bin/firefox -private-window
// ./system /home/kali/text -parametr
 
//which firefox
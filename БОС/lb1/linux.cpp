#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
  setlocale(LC_ALL, "Russian");

  cout << "Устройства хранения:\n";
  system("lsblk");

  cout << "\nВведите адрес утсройства (sdb): ";
  string devicePath;
  cin >> devicePath;

  cout << "\nИнформация о устройствах:\n";
  string command = "udevadm info --query=all --name=" + devicePath;
  system(command.c_str());

  ifstream isRemovable("/sys/block/" + devicePath + "/removable");
  int removable = 0;
  isRemovable >> removable;
  isRemovable.close();

  if (removable == 1) {
    cout << "\nИзвлечь? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        string command = "eject " + devicePath;
        system(command.c_str());
        cout << "Извлечение устройства\n";
    }
    else{
      cout << "\nУстройство не извлечено\n";
      }
  }

    return 0;
}
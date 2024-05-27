#include <Windows.h>
#include <stdio.h>
#include <string>

//shell "C:\Program Files\Google\Chrome\Application\chrome.exe" -incognito
using namespace std;

int main(int argc, char* argv[]){
	setlocale(LC_ALL, "Russian");
	if (argc > 1)	{

		string stroka = ""; // argument

		for (int i = 2; i < argc; i++){
			stroka = stroka + (string)argv[i];
			stroka = stroka + " ";
		}
		
		bool result = ShellExecuteA(NULL, "open", (LPCSTR)argv[1], (LPCSTR) stroka.c_str(), NULL, SW_SHOW);
	}
	else{
		printf("Not enough input arguments\n");
	}


	return 0;
}
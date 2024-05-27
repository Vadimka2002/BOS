#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
//create C:\Program Files\Google\Chrome\Application\chrome.exe -incognito
//create text -parametr
using namespace std;

int main(int argc, char* argv[]){
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	setlocale(LC_ALL, "Russian");
	if (argc > 1){

		string stroka = "";

		for (int i = 1; i < argc; i++){
			stroka = stroka + (string)argv[i];
			stroka = stroka + " ";
		}

		bool result = CreateProcessA(NULL,   // No module name (use command line)
			(LPSTR)stroka.c_str(),        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi);           // Pointer to PROCESS_INFORMATION structure

		WaitForSingleObject(pi.hProcess, INFINITE);
	}
	else{
		printf("Empty arguments\n");
	}
	return 0;
}
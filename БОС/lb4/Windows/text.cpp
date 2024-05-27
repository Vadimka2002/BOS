#include <stdio.h>
#include <string.h>
#include <Windows.h>
int main(int argc, char* argv[]){
	
	printf("executable text.cpp\n");
	
	for (int i = 1; i < argc; ++i){
		if (strcmp(argv[i], "--parametr") == 1){
			printf("parameter is passed %s\n", argv[i]);
		}
	}

	system("pause");
	return 0;
}
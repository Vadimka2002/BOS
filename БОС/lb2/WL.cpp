#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
	bool flag = 0;
    int charS = 0, word = 0, stringS = 0, number = 0; 

    while ((ch = getchar()) != EOF) {
        if (ch == '\n'){ 
            stringS++; 
		}
		else if (isdigit(ch)){
			number++;
		}
		else{
            charS++; 
		}
		
        if (ch == ' ' || ch == '\n'){
            flag = 0; 
		}
        else if (flag == 0) {
            flag = 1;
            word++;
        }
    }
 
    printf("\nChar: %u\n", charS+number);
    printf("Word: %u\n", word);
    printf("String: %u\n", stringS);
    //printf("Numbers: %u\n", number);
    return 0;
}
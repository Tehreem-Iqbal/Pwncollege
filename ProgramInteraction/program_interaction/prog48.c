#include <stdio.h>
#include </flag>
void getmessage(void){
	char msg[200];
	printf("Enter the message: ");
	scanf(" %s", msg);
	printf("Message received.\n");
}

int main(void){
	getmessage();
	return 0;
}

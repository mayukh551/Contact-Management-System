/*
  Given a string s containing just the characters '(', ')', '{', '}', '[' and ']'
  Determine if the input string is valid.                                                          */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
	char s[6];
	int i=0;
	printf("Enter the string: \n"); 	gets(s);
	int x=0;
	if(s[0]=='}' || s[0]==']' || s[0]==')'){
		printf("False\n");
		exit(0);
	}
	while(i<strlen(s)){
		if(s[i+1]=='{' || s[i+1]=='(' || s[i+1]=='['){
			i++; continue;}
			
		else if((s[i]=='}' && s[i-x-1]=='{') || (s[i]==')' && s[i-x-1]=='(') || (s[i]==']' && s[i-x-1]=='[')){
			
			x=x+2; 
		}
		
		else if((i+1)<strlen(s) && (s[i]=='{' && s[i+1]=='}') || (s[i]=='(' && s[i+1]==')') || (s[i]=='[' && s[i+1]==']')){
			
			x=x+2;	i++;
		}

		else{
			printf("False\n");
			exit(0);}	
		i++;	
	}
	printf("True\n");
}

/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
	char s[6];
	char b[6]={'[','{','(',')','}',']'};
	int i=0,c=0;
	printf("Enter the string: \n");
	gets(s);
	int x=0;
	if(s[0]=='}' || s[0]==']' || s[0]==')'){
		printf("False\n");
		exit(0);
	}
	printf("First condition failed\n");
	printf("Trying second condition\n");
	while(i<strlen(s)){
		printf("Starting from top\n");
		if(s[i+1]=='{' || s[i+1]=='(' || s[i+1]=='['){
			printf("condition 1\n");
			i++; continue;
		}
		else if((s[i]=='}' && s[i-x-1]=='{') || (s[i]==')' && s[i-x-1]=='(') || (s[i]==']' && s[i-x-1]=='[')){
			printf("condition 3\n");
			i++; x=x+2; continue;
		}
		else if((i+1)<strlen(s) && (s[i]=='{' && s[i+1]=='}') || (s[i]=='(' && s[i+1]==')') || (s[i]=='[' && s[i+1]==']')){
			printf("condition 2\n");
			x=x+2;
			i=i+2;
			continue;
		}
		else{
			printf("Last condition\n");
			printf("False\n");
			exit(0);
		}
		i++;	

		printf("Reached the end\n");
	}
	printf("True\n");
}*/

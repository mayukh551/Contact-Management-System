#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*int main(){
	FILE *fp = fopen("C:\\Users\\MAYUKH\\Desktop\\Discord_Content.txt","r");
	if(fp==NULL){
		printf("File can't be opened");
	}
	else{
		printf("File can be opened");
	}
	fclose(fp);
}*/



struct contact{
	char name[50];  // to store the name of a person
	char email[50]; // to store the email address
	double phone_no;   // to store the phone number
	struct contact *next;  // to store the MA of next node
};

void display(struct contact *ptr){
	while(ptr!=0){
		printf("Name     : %s",ptr->name);
		printf("Email ID : %s\n", ptr->email);
		printf("Phone_No : %.0lf\n",ptr->phone_no);
		printf("\n");
		ptr=ptr->next;
	}
}

int main()
{
	FILE *file_read = fopen("contact_names.txt","r");
	if(file_read==NULL){
		printf("File Can't be opened #0");
		exit(0);
	}
	
	// counting no. of lines in file
	int size=0;
	struct contact *head,*ptr,*last,*newnode;
	head=0;
	char ch;
	while((ch=fgetc(file_read))!=EOF)
	{
      if(ch=='\n')
         size++;
   	}
   	
   	fclose(file_read);
   	
   	//extracting info from file
   	FILE *fo1 = fopen("contact_names.txt","r");
   	if(fo1==NULL){
		printf("File can't be opened#1"); exit(0);
	}
   	printf("Size : %d\n\n",size+1); int i;
   	
	for(i=0;i<(size+1);i++)
	{
		newnode=(struct contact*)malloc(sizeof(struct contact));
		double num;
		fgets(newnode->name,50,fo1); // storing the name from file into a node
		newnode->next=0;
		if(head==0) // condition for 1st node created 
		{
			head=ptr=newnode;
		}
		else  // for rest of the nodes
		{
			ptr->next=newnode;
			ptr=newnode;
		}
	}
	//display(head);
	last=ptr;
	fclose(fo1);
	
	printf("Reached file fu\n");
		
	FILE *fu = fopen("emails.txt","r");
	printf("Reached after file fu opened\n");
	
	if(fu==NULL){
		printf("File can't be opened#2");
		exit(0);
	}
	printf("Reached after if condition of fu\n");
	ptr=head;
	printf("Reached after ptr=head\n");
	while(ptr!=0){
		fscanf(fu,"%s",ptr->email);
		ptr=ptr->next;
	}
	printf("Reached after while loop #1\n");
	fclose(fu);
		
	
	FILE *file_phone = fopen("phone_no.txt","r");
	if(file_phone==NULL)
	{
		printf("File can't be opened #3");
		exit(0);
	}
	ptr=head;
	printf("Reached before while loop #2\n");
	while(ptr!=0)
	{
		printf("Hi there\n");
		fscanf(file_phone,"%lf",&ptr->phone_no);
		printf("Accepted\n");
		ptr=ptr->next;
	}
	printf("Reached after while loop #2\n");
	display(head);
	fclose(file_phone);
}

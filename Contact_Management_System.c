#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

void update_names(struct contact* ptr)       // updating contact names
{	
	FILE *file_update = fopen("contact_names.txt","w");
	
	if(file_update==NULL){
		printf("File contact_names.txt cannot be opened"); exit(0);
	}
	while(ptr!=0){
		fputs(ptr->name,file_update); ptr=ptr->next;}
		
	fclose(file_update);
}

void update_emails(struct contact* ptr){	// updating emails
		
	FILE *file_update = fopen("emails.txt","w");
	
	if(file_update==NULL){
		printf("File emails.txt cannot be opened"); exit(0);
	}
	while(ptr!=0){
		fprintf(file_update,"%s",ptr->name); ptr=ptr->next; }
		
	fclose(file_update);
}

void update_numbers(struct contact* ptr)  // updating phone numbers
{		
	FILE *file_update = fopen("phone_no.txt","w");
	if(file_update==NULL){
		printf("File emails.txt cannot be opened"); exit(0);
	}
	
	while(ptr!=0);
	{
		fprintf(file_update,"%d",ptr->name); ptr=ptr->next;
	}
	fclose(file_update);
}


void insert(struct contact* head, struct contact* last){
	struct contact* ptr = head;
	struct contact* info = (struct contact*)malloc(sizeof(struct contact));
	info->next=0;
	printf("Enter your name : ");
	fgets(info->name,50,stdin);
	printf("Enter your email address : ");
	scanf("%s",info->email);
	printf("Enter your phone number : ");
	scanf("%n",&info->phone_no);
	
	if(head!=0)
	{
		if(strcmp(info->name,head->name)==-1)  // insert at front
		{
			info->next=head;
			head=info;
		}
		
		else if(strcmp(info->name,last->name)==1 || strcmp(info->name,last->name)==0) // insert at end
		{ 
			last->next=info;
		}
		
		else{
			while(ptr!=0){
				if(ptr->next!=0 && strcmp(info->name,ptr->name)==-1 && strcmp(info->name,ptr->next->name)==1) // meaning (ptr->name) < (info->name) < (ptr->next->name)
				{
					info->next=ptr->next;  ptr->next = info;
				}
				
				ptr = ptr->next;
			}
		}
	}
	else // if contact list or file is empty...
	{
		head = info; }
		
	update_names(head); update_emails(head); update_numbers(head);
}


int main()
{
	FILE *file_read = fopen("contact_names.txt","r");
	if(file_read==NULL){
		printf("File contact_names.txt can't be opened");
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
   	
   	//extracting contact names from file
   	
   	FILE *fo1 = fopen("contact_names.txt","r");
   	if(fo1==NULL){
		printf("File contact_names.txt can't be opened"); exit(0);
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
	
	last=ptr;
	fclose(fo1);
	
	// Extracting emails from emails file into linked list
	
	FILE *fu = fopen("emails.txt","r");
	if(fu==NULL){
		printf("File emails.txt can't be opened");
		exit(0);
	}
	ptr=head;
	while(ptr!=0){
		fscanf(fu,"%s",ptr->email);
		ptr=ptr->next;
	}
	fclose(fu);
	
	// Extracting phone numbers from phone_no file into linked list
		
	FILE *file_phone = fopen("phone_no.txt","r");
	if(file_phone==NULL)
	{
		printf("File phone_no.txt can't be opened");
		exit(0);
	}
	ptr=head;
	while(ptr!=0)
	{
		fscanf(file_phone,"%lf",&ptr->phone_no);
		ptr=ptr->next;
	}
	//display(head);
	fclose(file_phone);
	
}

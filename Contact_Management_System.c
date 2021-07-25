#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//  Status
//  Options() : Success
//  insert()  : Success ... Extra task : check if inputs are valid --> number
//  del()     : Success
//  update()  : Success
//  search()  : Not done
//  edit()    : Not done

struct contact *head, *last;  int size;

struct contact{
	char name[50];  // to store the name of a person
	char email[50]; // to store the email address
	double phone_no;   // to store the phone number
	struct contact *next;  // to store the MA of next node
};

void display()
{
	if(head!=0)
	{
		struct contact *ptr=head;
		int i=1;
		printf("\nTotal Contacts : %d\n",size);
		while(ptr!=0)
		{
			printf("%d.  Name     : ",i);
			puts(ptr->name);
			printf("     Phone No : %.0lf\n",ptr->phone_no);
			printf("     Email ID : %s\n", ptr->email);
			printf("\n");
			ptr=ptr->next; i++;
		}
	}
	
	else
	{
		printf("Contact List Empty\n");
	}
	
}

void update_names(struct contact* ptr)       // updating contact names
{	
	FILE *name_update = fopen("contact_names.txt","w");
	
	if(name_update==NULL){
		printf("File contact_names.txt cannot be opened"); exit(0);
	}
	while(ptr!=0){
		fprintf(name_update,"%s",ptr->name);
		ptr=ptr->next;
	}
	fclose(name_update);
	printf("\nContact Names updated\n");
}
 
void update_emails(struct contact* ptr){	// updating emails
		
	FILE *emails_update = fopen("emails.txt","w");
	
	if(emails_update==NULL){
		printf("File emails.txt cannot be opened"); exit(0);
	}
	while(ptr!=0){
		fprintf(emails_update,"%s\n",ptr->email); ptr=ptr->next; }
	
	fclose(emails_update);
	printf("\nEmail ids updated\n");
	
}

void update_numbers(struct contact* ptr)  // updating phone numbers
{		
	FILE *no_update = fopen("phone_no.txt","w");
	if(no_update==NULL){
		printf("File phone_no.txt cannot be opened"); exit(0);
	}
	//printf("Entering while loop of update_numebrs()\n");
	while(ptr!=0)
	{
		fprintf(no_update,"%lf\n",ptr->phone_no); ptr=ptr->next;
	}
	fclose(no_update);
	printf("\nPhone numbers updated\n");
}

 
void insert(){	

	struct contact* ptr = head; char pass[50]; double num; char email[50];
	struct contact* info = (struct contact*)malloc(sizeof(struct contact));
	double *d = &(info->phone_no);
	info->next=0;
	do{
		printf("Enter your phone number : ");
		scanf("%lf",&num); 
		if(num==0){
			printf("\nNot a Number... Try Again!!!\n"); num=0;
		}
		else{
			*d =  num; break;
		}
	}while(num!=0);
		
	printf("Enter your name : ");
	fgets(info->name,50,stdin);
	fgets(info->name,50,stdin);
	printf("Enter your email address : ");
	scanf("%s",info->email);
	
	//strcpy(info->name,pass); strcpy(info->email,email); info->phone_no=num;
	
	if(head!=0)
	{
		if(strcmp(info->name,head->name)<0)  // insert at front
		{
			info->next=head;
			head=info;
		}
		
		/*else if(strcmp(info->name,last->name)>0) // insert at end
		{
			last->next=info;
		}*/
		
		//else{   // insert between two nodes
		while(ptr!=0){
			
			if(ptr->next==0)
			{
				if(strcmp(info->name,ptr->name)>0) // insert at end
				{
					ptr->next=info;
				}
			}
			
			 // meaning (ptr->name) < (info->name) < (ptr->next->name)
			else if(ptr->next!=0 && strcmp(info->name,ptr->name)>0 && strcmp(info->name,ptr->next->name)<0)
			{
				info->next=ptr->next;  ptr->next = info;
			}
			
			ptr = ptr->next;
		}
	}
	
	else // if contact list or file is empty...
	{
		head = last = info; }
		
	printf("\nNew Contact Added\n\n");
	//display(head);
	size=size+1;
}


void del(){				
	struct contact *ptr=head;
	display();
	printf("\nTotal contacts : %d\n",size);
	printf("\nEnter the no. of contacts you want to delete : ");	int n;
	scanf("%d",&n);
	if(n>=size)
	{
		head=0; size=0;
		printf("Are you sure you want to delete all existing contacts?\n");
		printf("Y/y --> Yes\n");
		printf("N/n --> No\n");
		printf("All contacts Deleted\n");
	}
	else if(n>0 && n<size)
	{
		printf("Enter the no. preceding the contact you want to delete :\n");
		int choice[n]; int i,j;
		for(i=0;i<n;i++)
		{
			scanf("%d",&choice[i]);
		}
		i=1,j=0;
		//sort(choice);  // sorting the elements in array 
		while(i<=size && j<n)
		{
			if(i==choice[j]){
				head=ptr->next; j++; ptr=head;	
				//free(ptr); 
			}
						
			else if((i+1)==choice[j]){
				struct contact *nx=ptr->next;
				ptr->next=nx->next; j++;		
			}	
			else
				ptr=ptr->next;		
			
			i++;
			
		}
		size=size-n;
		printf("\nChosen contacts deleted\n");
		printf("\nTotal Contacts after deletion : %d\n",size);
	}
	  
}

void options(){     
	
	int ch=0;
	
	while(ch>=0){
		
		printf("\n\n\nThis is a Contact Management System\n");
		printf("A System to manage your contacts for you by providing you with the following \nfunctions : \n\n");
		printf("Press 1 -> To add a new contact\n");
		printf("Press 2 -> To edit an existing contact\n");
		printf("Press 3 -> To del one or more contacts\n");
		printf("Press 4 -> To search your existing contacts\n");
		printf("Press 5 -> To print all available contacts\n");
		printf("Press 0 -> To exit the application\n");
		printf("\nEnter your choice : ");  
		scanf("%d",&ch);
		printf("\n");
		if(ch==1)
			insert();
			
		/*else if(ch==2)
			edit();*/
			
		else if(ch==3)
			del();
			
		/*else if(ch==4)
			search();*/
			
		else if(ch==5)
			display();
			
		else if(ch==0){
			printf("\nThank You");
			update_names(head); 
			update_emails(head);				
			update_numbers(head);
			exit(0);
		}
		
		else{
			printf("\nInvalid Input\n");
			ch=0;	
		}
				
	}	
}


int main()
{
	FILE *file_read = fopen("contact_names.txt","r");
	if(file_read==NULL){
		printf("File contact_names.txt can't be opened");
		exit(0);
	}
	
	// counting no. of lines in file
	size=0;
	struct contact *ptr,*newnode;
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
   	printf("Size : %d\n\n",size); int i; 
	size=size;
   	
	for(i=0;i<(size);i++)
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
	/*
	int c =fgetc(fo1);
	if(c==EOF){
		printf("End of file | @%c@\n",c);
	
		int x=ftell(fo1);
		fseek(fo1,x-3,SEEK_SET); // pointer pointing to the last character just before the end of file
		c=fgetc(fo1);
		printf("@%c@",c);
	}*/

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
	display();
	fclose(file_phone);
	options();
}
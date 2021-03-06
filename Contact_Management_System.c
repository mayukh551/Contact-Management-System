#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//	Status
//	Options() 		: Success without including update functions
//  display()		: to print all available contacts
//	disp()			: to print a specific contact
//  insert()  		: Success ... Extra task : check if inputs are valid --> Name and number
//  del()    		: Success
//  update()  		: All details successfully updated
//  update_stats()  : #3
//  search()     	: All done
//	edit()			: #1
//  fav_disp()	 	: #2

struct contact
{
	char name[50];  // to store the first name of a person
	char email[50]; // to store the email address
	char phone_no[10];   // to store the phone number
	struct contact *next;  // to store the MA of next node
}*head,*last;


int size,counter;

void options(), display(),disp(struct contact* ptr); 
void search(), edit(), error_message(),empty_message();
int searchByAlphabets(char str[50]);
int searchByNumber();
struct contact* searchByName(char str[50]);
void edit_again(struct contact* ptr, struct contact* prev);
void insertion_sort(struct contact* ptr);


void error_message(){
	printf("\nInvalid Input... Try Again!!\n");
}

void empty_message(){
	//system("cls");
	printf("\nContact List is EMPTY\n\n");
}

void disp(struct contact* ptr)    //to print a specific contact
{
	if(head==0)
		empty_message();
	else
	{
		printf("Full Name :%s\n",ptr->name);
		printf("Phone No :+91-%s\n\n",ptr->phone_no);
		printf("Email ID :%s\n\n",ptr->email);
		printf("\n\n");
	}
}


void display()
{
	if(head!=0)
	{
		struct contact *ptr=head;
		int i=1;
		while(ptr!=0)
		{
			printf("Contact No. - %d\n\n",i);
			printf("Full Name  : %s\n",ptr->name);
			printf("Phone No   : +91-%s\n\n",ptr->phone_no);
			printf("Email ID   : %s\n\n",ptr->email);
			printf("\n\n");
			ptr=ptr->next; i++;
		}
		printf("\nTotal no. of contacts : %d\n",size);
	}
	
	else
	{
		empty_message();
	}
}


void update_file(struct contact* ptr)       // updating contact 
{	
	FILE *file_update = fopen("C:\\Users\\MAYUKH\\Desktop\\contact#1.txt","w");
	
	if(file_update==NULL){
		printf("\nFile contact_names.txt cannot be opened\n"); exit(0);
	}
	if(head==0){
		fprintf(file_update,"%c",'0');
	}
	else
	{
		while(ptr!=0)
		{
			fputs(ptr->name,file_update);
			fprintf(file_update,"%s\n",ptr->email);
			fprintf(file_update,"%s\n",ptr->phone_no);
			ptr=ptr->next;
		}
	}
	fclose(file_update);
	printf("\nContact Names updated\n");
}


void insert()
{
	char ch; int i; char str[50]; int choice;
	struct contact* ptr = 0; char pass[50]; char num[10]; char email[50];
	struct contact* info = (struct contact*)malloc(sizeof(struct contact));
	info->next=0;
	
	// Accepting details of the contact
	do{
		printf("Press 1 to enter the contact details :\n");
		printf("Press 2 to Skip :\n\n");
		fflush(stdin);
		choice = getch();
		if(choice!=(48+1) && choice!=(48+2))
			error_message();
		
	}while(choice!=(48+1) && choice!=(48+2));
	
	if(choice==(48+2)){  // user skipping this function insert()
		return;
	}
	
	// else user enter its details
	
	printf("Phone number : +91-");
	fflush(stdin);
	scanf("%[^\t\n]s", str);
	
	
	// phone size should be exactly = 10

	if(strlen(str)!=10)
	{
		printf("#1 Invalid Phone Number\nTry Again!!\n");
		insert(); return;
	}
	
	// to check if phone_no has only digits

	for(i=0;i<strlen(str);i++)
	{
		if(str[i]<48 || str[i]>57)
		{
			printf("#3 Invalid Phone Number\nTry Again!!\n"); // means it is not a phone number
			insert(); return;
		}
	}
	
	// to check if phone no. is already available or not...
	strcpy(info->phone_no,str);
	
	int k=searchByNumber(info->phone_no);
	if(k==1)
	{
		printf("This Contact matches with %s",info->name);
		disp(info);
		printf("Contact Already Available!!\n");
		free(info);
		return;
	}
	
	printf("Name : ");
	fgets(info->name,50,stdin);
	fgets(info->name,50,stdin);
	
	// checking if the contact name is already available or not
	ptr=searchByName(info->name);
	if(ptr!=0){
		printf("This Contact matches with %s",info->name);
		disp(ptr);
		printf("Contact Already Available\n");
		free(info);
		return;
	}
	
	printf("Email address (Optional) \nOr press E to skip: ");
	fflush(stdin);
	scanf("%s",info->email);
	
	if((info->email[0]=='E' || info->email[0]=='e') && strlen(info->email)==1)   // a condition if a user do not want to store the email address
	{  
		strcpy(info->email,"N/A");
	}
	
	// Insertion	
	
	ptr=head;
	
	if(head!=0)
	{
		insertion_sort(info);   // a function to insert a contact in an alphabetic order
	}
	
	else // if contact list or file is empty...
	{
		head = last = info; }
			
	printf("\nNew Contact Added\n");
	
	size=size+1; // 1 insertion is +1 increase in total contacts
}


void insertion_sort(struct contact* ptr)  // insert a node by sorting before insertion
{
	printf("In insertion_sort()\n");
	struct contact* info = ptr;
	disp(info);
	
	if(strcmpi(info->name,head->name)<0)  // insert at front
	{
		info->next=head;
		head=info;
	}
	
	else if(strcmpi(info->name,last->name)>0) // insert at end
	{
		last->next=info;
	}
	
	else  // insert between two nodes
	{   
		printf("Insertion in between nodes\n");
		ptr=head;
		while(ptr!=0)
		{		
			/*if(ptr->next==0)
			{	if(strcmp(info->name,ptr->name)>0) // insert at end
					ptr->next=info;		}*/
			
			// meaning (ptr->name) < (info->name) < (ptr->next->name)
			
			// Insertion in between two nodes
			if(ptr->next!=0 && strcmpi(info->name,ptr->name)>0 && strcmpi(info->name,ptr->next->name)<0)
			{
				info->next=ptr->next;  ptr->next = info; disp(info);
				return;
			}		
			ptr = ptr->next;
		}
	}
}


void del()
{	
	if(head==0)
	{
		empty_message();
		options();
	}
	struct contact *ptr,*prev; int choice;
	ptr=prev=head;
	printf("\nTotal contacts : %d\n",size);
	printf("\nEnter the no. of contacts you want to delete : ");	int n;
	scanf("%d",&n);
	if(n>=size)
	{
		printf("Are you sure you want to delete all existing contacts?\n");
		do{
			printf("Y --> Yes\n");
			printf("N --> No\n");
			fflush(stdin);
			choice = getch();
			if(choice!=(89) && choice!=(89+32) && choice!=(110) && choice!=(110-32))
				error_message();
				
		}while(choice!=(89) && choice!=(89+32) && choice!=(110) && choice!=(110-32));
		
		if(choice=='Y' || choice=='y')
		{
			head=last=0; size=0;
			printf("All contacts Deleted\n");
		}
			
		else
		{
			options();
		}
	}
	
	else if(n>0 && n<size)
	{
		display();
		printf("Enter the Contact No. you want to delete :\n");
		int choice[n]; int i,j;
		for(i=0;i<n;i++)
		{
			scanf("%d",&choice[i]);
		}
		
		// sort the array of choices
		i=j=0; int temp=0;
		for(i=0;i<n-1;i++){
			for(j=i+1;j<n;j++)
			{
				if(choice[i]>choice[j])
				{
					temp=choice[i]; 	choice[i]=choice[j];   choice[j]=temp;
				}
			}
		}
		
		i=1,j=0;	
		
		// loop for deleting nodes at position = choice
		/*
		while(i<=size && j<n)
		{
			if(i==choice[j]){
				head=ptr->next; j++; ptr=head;	
				free(ptr); 
			}
						
			else if((i+1)==choice[j]){
				struct contact *nx=ptr->next;
				ptr->next=nx->next; j++;		
			}	
			else
				ptr=ptr->next;
			
			i++;
						
		}*/
		
		while(i<=size && j<n)
		{
			if(i==choice[j])
			{
				if(ptr==head)
				{   head=ptr->next; 
					prev=head; }
					
				else
					prev->next=ptr->next;
				j++;
			}
			
			else if(prev!=ptr)
				prev=prev->next;
	
			ptr=ptr->next;
			i++;				
		}
		
		size=size-n;
		printf("\nChosen contacts deleted\n");
		printf("\nTotal Contacts after deletion : %d\n",size);
	}
	else
	{
		error_message();
		del();
	}
}


struct contact* searchByName(char str[50])
{
	struct contact* ptr = head;
	while (ptr!=0)  
	{
		if (strcmp(str,ptr->name) == 0)
			return ptr;
		else
			ptr = ptr->next;
	}
	return 0;
}


int searchByNumber(char str[10])
{
	printf("\n");
	struct contact *ptr = head; int i=0,k=0;
	int x=strlen(str);
    char num[10];
    while (ptr!=0)  
	{
		int c=0;
		for(i=0;i<x;i++)      // i processing through each character of str and ptr->phone_no
		{
			// comparing each character of str with that of ptr->phone_no
			if(str[i]!=ptr->phone_no[i])
			{
				c=-5; break; // comes out of loop when str is not in ptr->phone_no
			}
			else
				c++; // counting the no. of times str[i]==ptr->phone_no[i]
		}
		
		if(c==x)  // if every character of str is present in ptr->phone_no
		{
			printf("This Contact matches with %s\n\n",str);
			disp(ptr); k=1;
		}
		
		ptr=ptr->next; // moves to next contact
	}
	
    return k;
}



int searchByAlphabets(char str[50])
{
	printf("\n");
	struct contact* ptr = head; int i;
	int k=0; // a flag value to check if any contact name with str in it is found
	
	if(ptr == 0)  
    {  
        empty_message();
    }
    
    else
    {
		int x=strlen(str);    // used x for storing size, because size name globally declared variable already used 
		
		struct contact *lb = head;
		
		struct contact * lowerBoundary (struct contact* lb, char str[50])   // caller function is available after this function
		{
			//printf("In lowerboundary func()\n");
			struct contact *ptr = lb;
		
		    while (ptr!=0)
		    {
		    	if (tolower(str[0]) == tolower(ptr->name[0]))
		    		return ptr;
		    		
		    	ptr = ptr->next;
			}
			return 0;
		}
    		
		lb = lowerBoundary(lb, str);
		
		if(lb!=0)
		{
			ptr=lb; // pointing to starting position of contacts starting with str[0]
			while(tolower(ptr->name[0])==tolower(str[0]))  // ub set to when str[0]!=ptr->name[0] or End of File reached
			{
				int c=0;
				for(i=0;i<x;i++)      // i processing through each character of str and ptr->name
				{
					// comparing each character of str with that of ptr->name
					if(tolower(ptr->name[i])!=tolower(str[i]))
					{
						c=-1; break; // comes out of loop when str is not in ptr->name
					}
					else
						c++; // counting the no. of times str[i]==ptr->name[i]
				}
				if(c==x)  // if every character of str is present in ptr->name
				{
					disp(ptr);
					k=1;
				}
				ptr=ptr->next; // moves to next contact
				
				if(ptr==0)  // if last contact visited...
					break;
			}
		}
    }
    return k;
}


void search()
{
	
	int ch=0; struct contact *ptr = 0; int k=0;
	int check_int=1;
	if (head==0)
	{
		empty_message();
	}
	else
	{
		char str[50];
		printf("\nEnter the name or number you want to search or Press 4 to exit : ");
		fflush(stdin);
		scanf("%[^\t\n]s",str);
		int i,k=0;
		//printf("str in search() is %s\n",(str));
		for(i=0;i<(strlen(str));i++)
		{
			if((str[i]>=97 && str[i]<=122) || (str[i]>=65 && str[i]<=90))
			{
				check_int=0; // means it is not a phone number
				break;
			}
		}
		
		if(str[0]=='4'){
			options();
		}
		
		else if(check_int==1)
		{
			//printf("Number search\n");
			k = searchByNumber(str);
		}
			
		else if (check_int==0)   
		{
			//printf("Name Search\n");
			k=searchByAlphabets(str);   // checks every character of the input if present in the contact list
		}
	
		if ((check_int==1 || check_int==0) && (k==1))
		{
			printf ("Search Successful!\n");
			//return 1;
		}
		
		else if ((check_int==1 || check_int==0) && (k==0))
		{
			printf ("\nSearch Unsuccessful!\n");
			//return 0;
		}
		
	}
}


void edit()
{
	// accept the contact that the user wants to edit...
	struct contact *info = (struct contact*)malloc(sizeof(struct contact));
	int ch=0; struct contact *ptr = head; struct contact *prev = head; int k=0;
	int check_int=1;
	if (ptr==0)
	{
		empty_message();
	}
	
	else
	{
		int choice; int i;
		do
		{
			display();
			printf("Enter the Contact No. you want to edit :\n");
			scanf ("%d", &choice);
			
			if (choice<1 || choice>size)
				error_message();
				
		}while (choice<1 || choice>size);
		
		// if ptr is the address for that contact
		
		for (i=1;i<=choice;i++)
		{	
			if (i==choice)
				break;
				
			if (ptr!=prev)
				prev = prev->next;
				
			ptr = ptr->next;
		}
		
		// make the necessary changes in the contact as suggested by the user
		int ch=0; int x=0;
		
		void edit_again(struct contact *ptr, struct contact *prev)
		{
			do
			{
				printf("\nPress 1 -> Edit name\n");
				printf("Press 2 -> Edit number\n");
				printf("Press 3 -> Edit e-mail\n");
				printf("Press 0 -> Exit\n");
				printf("\n");
				ch=getch();
			
				if (ch!=(48+1) && ch!=(48+2) && ch!=(48+3) && ch!=(48))
					error_message();
				
			}while (ch!=(48+1) && ch!=(48+2) && ch!=(48+3) && ch!=(48));
		
			// then the node before ptr (say prev) ; prev->next=ptr->next; 	
			// ptr is extracted from linked list
			
				
			if (ch==(48+1))
			{
				x++;
				if (x==1)
				{
					//info = (struct contact*)malloc(sizeof(struct contact));
					strcpy(info->phone_no, ptr->phone_no);
					strcpy(info->email, ptr->email);
					
					if (ptr==head)
					{
						head = ptr->next;
						prev = head;
					}
				
					else if (ptr->next == 0)
						prev->next = 0;
					
					else
						prev->next = ptr->next;
				}	
					
				struct contact *p = 0;
				char str[50];
				
				void name_change()
				{
					printf ("\nEnter the edited name :\n");
					printf("\nName : ");
					fflush(stdin);
					//scanf("%[^\t\n]s", str);
					fgets(str,50,stdin);
					//str[strlen(str)] = '\n';

					p=searchByName(str);
					if(p!=0)
					{
  						printf("\nThis Contact matches with %s",str);
						disp(p);
 						printf("\nContact Already Available\n...\n");
  						//free(info);
 						name_change();
					}
					
					//strcpy (info->name, str);
				}
				name_change();
				strcpy (info->name, str);
				printf ("\nContact Edited!\n");
				// insertion_sort(ptr);  // passed for insertion into LL by sorting
				// insertion_sort(info);
				disp(info);
			}
			
			else if (ch==(48+2))
			{
				char str[50];

				if (x!=0)	
					ptr = info;
				
				void phone_number()
				{
					printf ("\nEnter the edited phone no. :\n");
					printf ("\nPhone no. : +91-");
					fflush(stdin);
					scanf ("%s", str);
				
					if(strlen(str)<10 || strlen(str)>10)
					{
						printf("\nInvalid Phone Number\nTry Again!!\n");
						phone_number();
					}
	
					// to check if phone_no has only digits
	
					for(i=0;i<strlen(str);i++)
					{
						if(str[i]<48 || str[i]>57)
						{
							printf("\nInvalid Phone Number\nTry Again!!\n"); // means it is not a phone number
							phone_number();
						}
					}
	
					// to check if phone no. is already available or not...
	
					int k=searchByNumber(str);
					if(k==1)
					{
						printf("\nContact Already Available!!\n");
						phone_number();
					}
				}
				phone_number();
				strcpy (ptr->phone_no, str);
				printf ("Contact Edited!\n");
			}
			
			else if (ch==(48+3))
			{
				if (x!=0)	
					ptr = info;
				
				printf ("\nEnter the edited E-mail ID:\n");
				printf ("\nE-mail : ");
				scanf ("%s", ptr->email);
				printf ("\nContact Edited!\n");
			}
			
			else if (ch==(48)){
				if(x>0)
				{
					insertion_sort(info);   // the user has changed this contact name for at least once...
				}
				options();
			}
			
			char ch1;
			do
			{
				printf ("\nDo you want to continue editing this contact ?\nY/N : \n");
				fflush(stdin);
				ch1 = getch();
				fflush(stdin);
				
				if (ch1!='Y' && ch1!='y' && ch1!='N' && ch1!='n')
					error_message();
				
			}
			while (ch1!='Y' && ch1!='y' && ch1!='N' && ch1!='n');
			
			if (ch1=='Y' || ch1=='y')
				edit_again(ptr, prev);
				
			else if (ch1=='N' || ch1=='n')
			{
				if(x>0)
				{
					insertion_sort(info);   // the user has changed this contact name for at least once...
				}
				
				char ch2;
				do
				{
					printf ("\n\nDo you want to edit another contact ?\nY/N : \n");
					fflush(stdin);
					ch2 = getch();
				
					if (ch1!='Y' && ch1!='y' && ch1!='N' && ch1!='n')
						error_message();
				
				}
				while (ch1!='Y' && ch1!='y' && ch1!='N' && ch1!='n');
				
				
				if (ch2=='Y' || ch2=='y')
					edit();
					
					
				else if (ch1=='N' || ch=='n')
					options();
			}
		}
		edit_again(ptr, prev);
	}
}


void options()
{     
	int ch=0,x;
	
	while(ch>= 0){
		
		printf("\nHome\n");
		printf("Press 1 -> To add a new contact\n");
		printf("Press 2 -> To edit an existing contact\n");
		printf("Press 3 -> To del one or more contacts\n");
		printf("Press 4 -> To search your existing contacts\n");
		printf("Press 5 -> To print all available contacts\n");
		printf("Press 0 -> To exit the application\n");
		printf("Press C -> to clear screen\n");
		printf("\n");
		ch=getch();
		if(ch==(48+1))
			insert();
			
		else if(ch==(48+2))
			edit();
			
		else if(ch==(48+3))
			del();
			
		else if(ch==(48+4)){
			search();
		}
		
		else if(ch==(48+5))
			display();
			
		else if(ch==99 || ch==67){
			system("cls");
		}
			
		else if(ch==48){
			do{
				printf("\n\n\t\t\tAre you sure you want to exit? --> Y/N\n");
				printf("\t\t\t\t\t");
				x=getch();
				if(x==121 || x==89)   // 121 stands for y | 89 stands for Y
				{
					printf("\nThank You\n");
					update_file(head);
					exit(0);
				}
				else if(x==110 || x==78)
					options();
				else{
					error_message();
				}	
					
			}while(x!=121 && x!=89 && x!=78 && x!=110);
		}
		
		else{
			error_message();
			ch=0;	
		}
	}
}


int main()
{
	FILE *file_read = fopen("C:\\Users\\MAYUKH\\Desktop\\contact#1.txt","r");
	
	if(file_read==NULL){
		printf("File contact#1.txt can't be opened");
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
   	
   	printf("\nThis is a Contact Management System\n");
	printf("A System to manage your contacts for you by providing you with the following \nfunctions : \n\n");
	printf("Press any key to continue : ");
	getch();
	
   	if(size>0)
   	{
	   	//extracting contact names from file
	   	
	   	FILE *fo1 = fopen("C:\\Users\\MAYUKH\\Desktop\\contact#1.txt","r");
	   	if(fo1==NULL){
			printf("File contact#1.txt can't be opened"); exit(0);
		}
	   	//printf("Size : %d\n\n",size);
		int i; 
	   	size=size/3;
		   	
		for(i=0;i<(size);i++)
		{
			newnode=(struct contact*)malloc(sizeof(struct contact));
			if(i>0)
				fgets(newnode->name,50,fo1); // storing the name from file into a node
			fgets(newnode->name,50,fo1); // storing the name from file into a node
			fscanf(fo1,"%s",newnode->email);
			fscanf(fo1,"%s",newnode->phone_no);
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
			//printf("\nContact Created\n");
		}
		
		
		last=ptr;
		fclose(fo1);
		
	}
	else if(size==0){
		head=last=0;
	}
	options();
}

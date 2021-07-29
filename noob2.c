#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//	Status
//	Options() 		: Success without including update functions
//  display()		: to print all available contacts
//	disp()			: to print a specific contact
//  insert()  		: Success ... Extra task : check if inputs are valid --> Name and number
//  del()    		: Success
//  update()  		: All details successfully updated
//  update_stats()  : #3
//  search()     	: All done except search by Number
//	edit()			: #1
//  fav_disp()	 	: #2

struct contact{
	char name[50];  // to store the first name of a person
	char email[50]; // to store the email address
	char phone_no[10];   // to store the phone number
	struct contact *next;  // to store the MA of next node
	int xtimes;
	int favourites;  // take 1 for Yes and 0 for No
}*head,*last,*last_inserted,*last_searched,*most_searched,*stat_node,*stat_head;


int size,counter;

void options(), display(),disp(struct contact* ptr), fav(); 
int search();
int searchByAlphabets(char str[50]);
int searchByNumber();
struct contact* searchByName(char str[50]);


void disp(struct contact* ptr)    //to print a specific contact
{
	printf("Full Name :%s",ptr->name);
	printf("Phone No :%s\n",ptr->phone_no);
	printf("Email ID :%s\n",ptr->email); 
	printf("\n\n");
}

void fav_disp(struct contact* ptr){
	
	while(ptr!=0)
	{
		if(ptr->favourites==1)
		{
			fav_disp(ptr->next);
			disp(ptr);
		}
		
		else
			disp(ptr);
		
		if(ptr->next==0)
			return;
		
		ptr=ptr->next;
		
	}
	
	/*while(ptr!=0){
		if(ptr->favourites==1){
			disp(ptr);
		}
		ptr=ptr->next;
	}*/
}

void display()
{
	if(head!=0)
	{
		struct contact *ptr=head;
		int i=1;
		//printf("\nTotal Contacts : %d\n",size);
		while(ptr!=0)
		{
			printf("%d.  Full Name  : %s",i,ptr->name);
			printf("     Phone No   : %s\n",ptr->phone_no);
			printf("     Email ID   : %s\n",ptr->email);
			printf("\n\n");
			ptr=ptr->next; i++;
		}
		printf("\nTotal no. of contacts : %d\n",size);
	}
	
	else
	{
		printf("Contact List Empty\n");
	}
}


void update_file(struct contact* ptr)       // updating contact 
{	
	FILE *file_update = fopen("C:\\Users\\MAYUKH\\Desktop\\contact#1.txt","w");
	
	if(file_update==NULL){
		printf("File contact_names.txt cannot be opened"); exit(0);
	}
	while(ptr!=0){
		fputs(ptr->name,file_update);
		fprintf(file_update,"%s\n",ptr->email);
		fprintf(file_update,"%s\n",ptr->phone_no);
		ptr=ptr->next;
	}
		
	fclose(file_update);
	printf("\nContact Names updated\n");
}


void insert()
{
	char ch;
	struct contact* ptr = 0; char pass[50]; char num[10]; char email[50];
	struct contact* info = (struct contact*)malloc(sizeof(struct contact));
	info->next=0;
	
	// Accepting details of the contact 
	printf("Enter the contact details :\n\n");
	printf("Phone number : ");
	scanf("%s",info->phone_no);
	if(strlen(info->phone_no)<10){
		printf("Invalid Phone Number\nTry Again!!\n");
		insert();
	}
	printf("Name : ");
	fgets(info->name,50,stdin);
	fgets(info->name,50,stdin);
	ptr=searchByName(info->name);
	if(ptr!=0){
		printf("Contact Already Available\n");
		disp(ptr);
		free(info);
		options();
	}
	printf("Email address (Optional) \nOr press E to skip: ");
	scanf("%s",info->email);
	
	if(info->email[0]=='E' || info->email[0]=='e')   // a condition if a user do not want to store the email address
	{  
		strcpy(info->email,"N/A");
	}
	
	last_inserted=info;
	
	// Insertion	
	
	ptr=head;
	
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
		
	printf("\nNew Contact Added\n");
	
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
		printf("Are you sure you want to delete all existing contacts?\n");
		printf("Y/y --> Yes\n");
		printf("N/n --> No\n");
		head=0; size=0;
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


struct contact* searchByName(char str[50])
{
	//printf("in searchByName()\n");
	struct contact* ptr = head;
	/*printf("\nEnter the full name of the conatct which you want to search : ");
	fgets(str,50,stdin); 
	fgets(str,50,stdin); */
		
	while (ptr!=0)  
	{
		if (strcmp(str,ptr->name) == 0)
		{
			return ptr;
		}
			
		else
		{
			ptr = ptr->next;
		}
	}
	return 0;
}


int searchByNumber(char str[10])
{
	
	struct contact *ptr = head; int i=0,k=0;
	int x=strlen(str)-1;
    char num[10];
    /*printf("\nEnter the number of the contact which you want to search : ");
    scanf ("%s", num);*/
    	
    while (ptr!=0)  
	{
		int c=0;
		for(i=0;i<x;i++)      // i processing through each character of str and ptr->phone_no
		{
			// comparing each character of str with that of ptr->phone_no
			if(str[i]!=ptr->phone_no[i])
			{
				c=-1; break; // comes out of loop when str is not in ptr->phone_no
			}
			else
				c++; // counting the no. of times str[i]==ptr->phone_no[i]
		}
		if(c==x)  // if every character of str is present in ptr->phone_no
		{
			disp(ptr); k=1;
		}
		
		ptr=ptr->next; // moves to next contact
	}
	
    return k;
}



int searchByAlphabets(char str[50])
{
	struct contact* ptr = head; int i;
	int k=0; // a flag value to check if any contact name with str in it is found
	
	if(ptr == 0)  
    {  
        printf("\nContact is Empty!\n");  
    }  
    
    else
    {
		int x=strlen(str)-1;    // used x for storing size, because size name globally declared variable already used 
		printf("size of str : %d\n",x);
		
		struct contact *lb = head;
		
		struct contact * lowerBoundary (struct contact* lb, char str[50])   // caller function is available after this function
		{
			printf("In lowerboundary func()\n");
			struct contact *ptr = lb;
		
		    while (ptr!=0)
		    {
		    	if (str[0] == ptr->name[0])
		    		return ptr;
		    		
		    	ptr = ptr->next;
			}
			return 0;
		}
    		
		lb = lowerBoundary(lb, str);
		
		
		
		if(lb!=0)
		{
			printf("Lower boundary found\n");
			puts(lb->name);
			ptr=lb; // pointing to starting position of contacts starting with str[0]
						
			while(ptr->name[0]==str[0])  // ub set to when str[0]!=ptr->name[0] or End of File reached
			{
				int c=0;
				printf("\nComparing %s with %s",str,ptr->name);
				for(i=0;i<x;i++)      // i processing through each character of str and ptr->name
				{
					
					// comparing each character of str with that of ptr->name
					
					if(str[i]!=ptr->name[i])  
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
				else{
					printf("Not matched\n Moving to next contact\n");
				}
				ptr=ptr->next; // moves to next contact
				
				if(ptr==0)  // if last contact visited...
					break;
			}
		}
		/*if(k==0)
			printf("Search Unsuccessful!\n\n");*/
    }
    return k;
}

int search()
{
	
	int ch=0; struct contact *ptr = 0; int k=0;
	
	if (head==0)
	{
		printf ("\nContact List is Empty!\n");
	}
	else
	{
		/*do
		{
			printf("\n Which way do you want to search ?\n");
			printf("Press 1 -> Search By Name\n");
			printf("Press 2 -> Search By Number\n");
			//printf("Press 3 -> Search By Alphabets\n");
			printf("Press 4 -> Exit\n");
			printf ("\nYour choice : ");
			scanf("%d", &ch);
			
			printf("%d\n",ch);
			if (ch!=1 && ch!=2 && ch!=3 && ch!=4)
				printf ("\nInvalid choice! Try Again...\n");
			
		}while(ch!=1 && ch!=2 && ch!=3 && ch!=4);*/
	
		/*if (ch==1)
		{
			ptr = searchByName();
		}*/
		
		/*if(ch==4)
			options();*/
		
		char str[50];
		printf("\nEnter the name or number you want to search or Press 4 to exit : ");
		fgets(str,50,stdin); // fgets(str,50,stdin);
		int i,k=0,check_int=1;
		printf("size in search() is %d\n",strlen(str));
		for(i=0;i<strlen(str)-1;i++)
		{
			if(str[i]<48 && str[i]>57)
			{
				check_int=0; // means it has an alphabet
				break;
			}
		}
		
		if(str[0]=='4'){
			options();
		}
		
		if(check_int==1)
		{
			printf("Numebr searach\n");
			k = searchByNumber(str);
		}
	
		/*if (ch==2)
		{
			ptr = searchByNumber();
		}*/
	
		else if (check_int==0)   
		{
			printf("Name Search\n");
			k=searchByAlphabets(str);   // checks every character of the input if present in the contact list
		}
	
		if ((check_int==1 || check_int==0) && (k==1))
		{
			//disp(ptr);
			printf("\n");
			return 1;
		}
		
		else if ((check_int==1 || check_int==0) && (k==0))
		{
			printf ("\nSearch Unsuccessful!\n");
			return 0;
		}
		
	}
}

/*void mark_fav_contacts(){
	struct contact* ptr=head;
	display();
	int ch,i;
	printf("\nEnter the no. preceding the contacts to mark as favourite : ");
	scanf("%d",&ch);
	int arr[size];
	for(i=0;i<size;i)
	
}*/


void options(){     
	
	int ch=0,x;
	
	while(ch>= 0){
		
		printf("\nHome\n");
		printf("Press 1 -> To add a new contact\n");
		printf("Press 2 -> To edit an existing contact\n");
		printf("Press 3 -> To del one or more contacts\n");
		printf("Press 4 -> To search your existing contacts\n");
		printf("Press 5 -> To print all available contacts\n");
		//printf("Press 7 -> To mark your favourite contacts\n");
		//printf("Press 6 -> To view stats\n");
		printf("Press s -> to clear screen\n");
		printf("Press 0 -> To exit the application\n");
		//printf("\nEnter your choice : ");
		//scanf("%d",&ch);
		printf("\n");
		ch=getch();
		if(ch==(48+1))
			insert();
			
		/*else if(ch==(48+2))
			edit();*/
			
		else if(ch==(48+3))
			del();
			
		else if(ch==(48+4)){
			int f=search();		
		}
		
		else if(ch==(48+5))
			display();
			
		//else if(ch==(48+6))
			//mark_fav_contact(head);
			
		else if(ch==115 || ch==83){
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
					printf("\nInvalid Input!!! Try again...\n");
				}	
					
			}while(x!=121 && x!=89 && x!=78 && x!=110);
		}
		
		else{
			printf("\nInvalid Input\n");
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
   	
   	//extracting contact names from file
   	
   	FILE *fo1 = fopen("C:\\Users\\MAYUKH\\Desktop\\contact#1.txt","r");
   	if(fo1==NULL){
		printf("File contact#1.txt can't be opened"); exit(0);
	}
   	printf("Size : %d\n\n",size); int i; 
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
	
	//printf("\nDone\n");
	last=ptr;
	fclose(fo1);
	printf("\nThis is a Contact Management System\n");
	printf("A System to manage your contacts for you by providing you with the following \nfunctions : \n\n");
	printf("Press any key to continue : ");
	getch();
	//fav_disp(head);
	options();
	//display();
	
}

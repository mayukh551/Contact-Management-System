void search()
{
	int ch=0; struct contact* ptr = head;
	do
	{
		printf("\n Which way do you want to search ?\n");
		printf("Press 1 -> Search By Name\n");
		printf("Press 2 -> Search By Number\n");
		printf("Press 3 -> Search By Alphabets\n");
		printf("Press 4 -> Exit\n");
		scanf("%d", &ch);
		
		if (ch!=1 || ch!=2 || ch!=3 || ch!=4)
			printf ("\nInvalid choice! Try Again...\n");
			
	}while(ch!=1 || ch!=2 || ch!=3 || ch!=4);
	
	if (ch==1)
	{
		ptr = searchByName();
	}
	
	else if (ch==2)
	{
		ptr = searchByNumber();
	} 
	
	else if (ch==3)
	{
		searchByAlphabets();
	}
	
	if ((ch==1 || ch==2) && (ptr!=0))
	{
		printf ("\nSearch Successful!\n");
		printf("  Name     : ");
		puts(ptr->name);
		printf("     Phone No : %.0lf\n",ptr->phone_no);
		printf("     Email ID : %s\n", ptr->email);
		printf("\n");
		
	}
	else if ((ch==1 || ch==2) && (ptr==0))
	{
		printf ("\nSearch Unsuccessful!\n");
	}
}

struct contact* searchByName()
{
	struct contact* ptr = head;
	
	if(ptr == 0)  
    {  
        printf("\nContact is Empty!\n");  
    }  
    
    else
    {
    	char str[50];
		printf("\nEnter the full name of the conatct which you want to search : ");
		fgets(str,50,stdin); 
		fgets(str,50,stdin); 
		
		while (ptr!=0)  
		{
			if (strcmp( str, ptr->name ) == 0)
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
}

struct contact* searchByNumber()
{
	struct contact* ptr = head;
	
	if(ptr == 0)  
    {  
        printf("\nContact is Empty!\n");  
    }  
    
    else
    {
    	double num;
    	printf("\nEnter the number of the contact which you want to search : ");
    	scanf ("%lf", &num);
    	
    	while (ptr!=0)  
		{
			if (num == ptr->phone_no)
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
}

void searchByAlphabets()
{
	struct contact* ptr = head;
	
	if(ptr == 0)  
    {  
        printf("\nContact is Empty!\n");  
    }  
    
    else
    {
		char str[50];
		printf("\nEnter the name or the first few alphabets of the conatct which you want to search : ");
		fgets(str,50,stdin); 
		fgets(str,50,stdin); 
		
		struct contact* lb = head;
    	struct contact* ub = head;
		
		for (int i=0; i<strlen(str); i++)
		{
			lb = lowerBoundary(lb, str, i);
			ub = upperBoundary(lb, str, i);
		}
		
		if (lb!=0 || ub!=0)
		{
			printf ("\nSearch Successful!\n");
			
			while (lb != ub)
			{
				printf("  Name     : ");
				puts(lb->name);
				printf("     Phone No : %.0lf\n",lb->phone_no);
				printf("     Email ID : %s\n", lb->email);
				printf("\n");
				lb = lb->next;
			}
		}
		
		else
		{
			printf ("\nSearch Unsuccessful!\n");
		}
    }
}

struct contact* lowerBoundary (struct contact* lb, char str[50], int f)
{
	struct contact* ptr = lb;
	
	if(ptr == 0)  
    {  
        printf("\nContact is Empty!\n");  
    }  
    
    else
    {
    	while (ptr!=0)
    	{
    		if (str[f] == ptr->name[f])
    			return ptr;
    			
    		ptr = ptr->next;
		}
		return 0;
    }
}

struct contact* upperBoundary (struct contact* lb, char str[50], int f)
{
	struct contact *ptr = lb;
	struct contact *p = ptr->next;
	
	if(ptr == 0)  
    {  
        printf("\nContact is Empty!\n");  
    }  
    
    else
    {
    	while (ptr!=0 || p!=0)
    	{
    		if (str[f] != p->name[f])
    			return ptr;
    			
    		ptr = ptr->next;
    		p = p->next;
		}
		return 0;
    }
}

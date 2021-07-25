void search()
{
	int ch=0; struct contact* ptr = head;
	do
	{
		printf("\n Which way do you want to search ?\n");
		printf("Press 1 -> Search By Name\n");
		printf("Press 2 -> Search By Number\n");
		printf("Press 3 -> Exit\n");
		scanf("%d", &ch);
		
		if (ch!=1 || ch!=2 || ch!=3)
			printf ("\nInvalid choice! Try Again...\n");
			
	}while(ch!=1 || ch!=2 || ch!=3);
	
	if (ch==1)
	{
		ptr = searchByName();
	}
	
	else if (ch==2)
	{
		ptr = searchByNumber();
	} 
	
	if ((ch==1 || ch==2) && (ptr!=0))
	{
		printf ("\nSearch Successful!\n");
		printf("%d.  Name     : ",i);
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
		printf("\nEnter the name of the conatct which you want to search : ");
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

void search()
{
	int ch=0, n=0;
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
		n = searchByName();
	}
	
	else if (ch==2)
	{
		n = searchByNumber();
	} 
	
	if ((ch==1 || ch==2) && (n==1))
	{
		printf ("\nSearch Successful!\n");
	}
	else if ((ch==1 || ch==2) && (n==0))
	{
		printf ("\nSearch Unsuccessful!\n");
	}
}

int searchByName()
{
	struct contact* ptr = head;
	
	if(ptr == NULL)  
    {  
        printf("\nContact is Empty!\n");  
    }  
    
    else
    {
    	char str[50];
		printf("\nEnter the name of the conatct which you want to search : ");
		fgets(str,50,stdin); 
		fgets(str,50,stdin); 
		
		while (ptr!=NULL)  
		{
			if (strcmp( str, ptr->name ) == 0)
			{
				return 1;
			}
			
			else
			{
				ptr = ptr->next;
			}
		}
		return 0;
	}
}

int searchByNumber()
{
	struct contact* ptr = head;
	
	if(ptr == NULL)  
    {  
        printf("\nContact is Empty!\n");  
    }  
    
    else
    {
    	double num;
    	printf("\nEnter the number of the contact which you want to search : ");
    	scanf ("%lf", &num);
    	
    	while (ptr!=NULL)  
		{
			if (num == ptr->phone_no)
			{
				return 1;
			}
			
			else
			{
				ptr = ptr->next;
			}
		}
		return 0;
    }
}

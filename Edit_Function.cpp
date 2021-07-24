void edit()
{
	int ch=0, n=0;
	do
	{
		printf("\n Which way do you want to search ?\n");
		printf("Press 1 -> Edit By Name\n");
		printf("Press 2 -> Edit By Number\n");
		printf("Press 3 -> Exit\n");
		scanf("%d", &ch);
		
		if (ch!=1 || ch!=2 || ch!=3)
			printf ("\nInvalid choice! Try Again...\n");
			
	}while(ch!=1 || ch!=2 || ch!=3);
	
	if (ch==1)
	{
		n = editByName();
	}
	
	else if (ch==2)
	{
		n = editByNumber();
	} 
}

int editByName()
{
	struct contact* ptr = head;
	
	if(ptr == NULL)  
    {  
        printf("\nContact is Empty!\n");  
    }  
    
    else
    {
    	char str[50]; int n=0;
		printf("\nEnter the name of the conatct which you want to edit : ");
		fgets(str,50,stdin); 
		fgets(str,50,stdin); 
		
		while (ptr!=NULL)  
		{
			if (strcmp( str, ptr->name ) == 0)
			{
				n = 1;
				break;
			}
			
			else
			{
				ptr = ptr->next;
			}
		}
		
		if (n==1)
		{
			char st[50]; int c=0;
			do
			{
				printf("\n What do you want to edit ?\n");
				printf("Press 1 -> Edit Name\n");
				printf("Press 2 -> Edit Number\n");
				printf("Press 3 -> Edit E-mail\n");
				printf("Press 4 -> Confirm\n");
				printf("Press 5 -> Exit\n");
				scanf("%d", &c);
		
				if (c!=1 || c!=2 || c!=3 || c!=4 || c!=5)
					printf ("\nInvalid choice! Try Again...\n");
			
			}while(c!=1 || c!=2 || c!=3 || c!=4 || c!=5);
			
			if (c==1)
			{
				printf ("\nEnter the name : \n");
				fgets(st,50,stdin);
				fgets(st,50,stdin);
				ptr->name = st;
			}
		}
		
		else if (n==0)
		{
			printf ("\nName Not Found!\n");
		}
		
		return 0;
	}
}

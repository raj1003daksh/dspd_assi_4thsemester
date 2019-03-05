#include <stdio.h>
#include <string.h>
#include<stdlib.h>
typedef enum{FAILURE,SUCCESS} statuscode;
typedef enum{FALSE,TRUE} boolean;
typedef struct item_tag
{ char itemname[100];
  float price;
}items;
typedef struct menu_tag
{
   int no_of_items;
   items item[100]; 
}menu;
typedef struct location_tag
{  char name[50];
   char address[100];
   char zone[50];
   int no_of_seats;
   menu *res_menu;
   int category;//1 for restaurant 2 for cafe 3 for pub
   int cuis_category;//1 for north indian 2 for south indian 3 for continental
   //char sp_facilities[20][100];
   struct location_tag *next;
}location;
typedef struct cat_tag{
	char name[100];
	char address[50];
	struct cat_tag* next;
}cat_location;
typedef struct cuisine_tag{
	char name[100];
	char address[50];
	struct cuisine_tag* next;
}cuis_location;
typedef struct agent_tag
{ char id[21];
  char name[50];
  char phone_no[11];
  float curr_accu_commi;
  struct agent_tag *next_agen;
}agent;
typedef struct user_tag
{ char us_id[21];
  char name[50];
  char address[50];
  char phone_no[11];
  struct user_tag *next_user;
}user;
typedef struct order_tag
{ char res_name[50];
  char res_address[50];
  int no_of_items;
  int item_index[100];
  char ag_id[21];
  char ag_phone[11];
  struct order_tag *next_order;
}orders;
menu* create_menu()
{
	menu *lptr=(menu*)malloc(sizeof(menu));
	int n;char name[100];float price;
	printf("Enter the number of items\t:\n");
    scanf("%d",&n);
	lptr->no_of_items=n;
	int i;
	for(i=0;i<n;i++)
	{
		printf("Enter item name\t:\n");
		scanf("%s",name);
		printf("Enter the pricw\t:\n");
		scanf("%f",&price);
		strcpy(lptr->item[i].itemname,name);
		lptr->item[i].price=price;	
	}
	return lptr;
}
statuscode insert_cat_location(cat_location **nptr,char name[],char address[])
{
	cat_location *lptr=	(cat_location*)malloc(sizeof(cat_location));
	statuscode sc=FAILURE;
	if(lptr!=NULL)
	{
		sc=SUCCESS;
		strcpy(lptr->name,name);
		strcpy(lptr->address,address);
		lptr->next=*nptr;
		*nptr=lptr;
	}
	return sc;
}
statuscode insert_cuis_location(cuis_location **nptr,char name[],char address[])
{
	cuis_location *lptr=(cuis_location*)malloc(sizeof(cuis_location));
	statuscode sc=FAILURE;
	if(lptr!=NULL)
	{
		sc=SUCCESS;
		strcpy(lptr->name,name);
		strcpy(lptr->address,address);
		lptr->next=*nptr;
		*nptr=lptr;
	}
	return sc;
}
statuscode insert_eat_location(location **all_eatspots,char name[],char address[],char zone[],int no_of_seats,menu *res_menu,int category,int cuis_category)
{
	location *nptr=	(location*)malloc(sizeof(location));
	statuscode sc=FAILURE;
	if(nptr!=NULL)
	{
		sc=SUCCESS;
		strcpy(nptr->name,name);
		strcpy(nptr->address,address);
		strcpy(nptr->zone,zone);
		nptr->no_of_seats=no_of_seats;
		nptr->res_menu=res_menu;
		nptr->category=category;
		//insert_cat_location(ca_ptr,name,address);
		
		nptr->cuis_category=cuis_category;
		nptr->next=*all_eatspots;
		*all_eatspots=nptr;
	}
	return sc;
}
void visit_menu(menu *lptr)
{
	int i=0;
	printf("%d\n",lptr->no_of_items);
	while(i<(lptr->no_of_items))
	{
		printf("%s\n",lptr->item[i].itemname);
		printf("%f\n",lptr->item[i].price);
		i++;
	}
}
void print_location(location *nptr)
{
	printf("%s\n",nptr->name);
	printf("%s\n",nptr->address);
	printf("%s\n",nptr->zone);
	printf("%d\n",nptr->no_of_seats);
	menu *lptr=nptr->res_menu;
	visit_menu(lptr);
	printf("%d\n",nptr->category);
	printf("%d\n",nptr->cuis_category);
}
void Traverse(location *all_eatspots)
{
	location *nptr=all_eatspots;
	while(nptr!=NULL)
	{
		print_location(nptr);
		nptr=nptr->next;
	}
}
void Traverse_cat(cat_location *lptr)
{ 	cat_location *nptr=lptr;
	while(nptr!=NULL)
	{
	    printf("%s\n%s\n",nptr->name,nptr->address);
		nptr=nptr->next;
	}
}
void Traverse_cuis(cuis_location *lptr)
{ 	cuis_location *nptr=lptr;
	while(nptr!=NULL)
	{
	    printf("%s\n%s\n",nptr->name,nptr->address);
		nptr=nptr->next;
	}
}
void search_category(cat_location *nptr)
{
	Traverse_cat(nptr);
}
void search_cuisine(cuis_location *nptr)
{
	Traverse_cuis(nptr);
}
void search_area(location* lptr)
{ 
	int flag=0;
	char x[100],y[50];
 	printf("Enter area: ");
  	scanf("%s",x);
  	printf("Enter zone: ");
  	scanf("%s",y);
  	location* nptr=lptr;
  	while(nptr!=NULL)
  	{ 
   		if(strcmp(nptr->address,x)==0)
      	{ 
	  		if(flag==0)
         	{ 
			 	printf("Restaurant in area:\n");
           		printf("%s\n",nptr->address);
           		flag=1;
         	}
        	else
         	{
            	printf("%s\n",nptr->address);
         	}
      	}
     	nptr=nptr->next;
   	}
  	if(flag==0)
   	printf("No restaurant found in area\n");
  	flag=0;
  	nptr=lptr;
  	while(nptr!=NULL)
   	{ 
	   if(strcmp(nptr->zone,y)==0)
      	{ 
			if(flag==0)
         {
		 	printf("Restaurant in nearby area:\n");
           	printf("%s\n",nptr->address);
           	flag=1;
         }
        	else
         {
            printf("%s\n",nptr->address);
         }
      	}
     	nptr=nptr->next;
   	}
   	if(flag==0)
   	printf("No restaurant found in nearby areas\n");
} 
int main()
{ 
	cat_location *res=NULL;
	cat_location *pub=NULL;
	cat_location *cafe=NULL;
	cuis_location *north=NULL;
	cuis_location *south=NULL;
	cuis_location *cont=NULL;
	location *all_eatspots=NULL;
	location *fptr;
	char res_name[50];
    char res_address[100];
    char res_zone[50];
    int res_no_of_seats;
    menu *res_res_menu;
    int res_category; 
    int res_cuis_category;
    int i;
   for(i=0;i<3;i++)
   {
	
    //strcpy(res_name,"PRATHAMESH");
    printf("Enter the name of your restaurant\t:\n");
    scanf("%s",res_name);
    printf("Enter the address of your restaurant\t:\n");
    //strcpy(res_address,"NAGPUR");
    scanf("%s",res_address);
    printf("Enter the zone of your restaurant\t:\n");
    //strcpy(res_zone,"EAST");
    scanf("%s",res_zone);
   // res_no_of_seats=100;
    printf("Enter the number of seats in your restaurant\t:\n");
	scanf("%d",&res_no_of_seats);
    res_res_menu=create_menu();
    printf("Enter the category of your restaurant\t:\n");
    scanf("%d",&res_category);
    printf("Enter the cuisine of your restaurant\t:\n");
    scanf("%d",&res_cuis_category);
	//res_category=1;
    //res_cuis_category=2;
    statuscode sc;
    //fptr=all_eatspots;
    sc=insert_eat_location(&all_eatspots,res_name,res_address,res_zone,res_no_of_seats,res_res_menu,res_category,res_cuis_category);
	if(res_category==1)
	{
		insert_cat_location(&res,res_name,res_address);
	}
	else if(res_category==2)
	{
		insert_cat_location(&cafe,res_name,res_address);
	}
	else
	{
		insert_cat_location(&pub,res_name,res_address);
	}
	if(res_cuis_category==1)
	{
		insert_cuis_location(&north,res_name,res_address);
	}
	else if(res_cuis_category==2)
	{
		insert_cuis_location(&south,res_name,res_address);
	}
	else
	{
		insert_cuis_location(&cont,res_name,res_address);
	}
   }
	Traverse(all_eatspots);
	Traverse_cat(res);
    Traverse_cat(cafe);
    Traverse_cat(pub);
   //char sp_facilities[20][100];
    /*int i,x,query=-1;
	printf("\t\t\t\t\t  *********************************************\n");
	printf("\t\t\t\t\t* WELCOME TO OUR LIVE FOOD ORDER TRACKING SYSTEM *\n");
	printf("\t\t\t\t\t  *********************************************\n");
    printf("\n\n\n");  
    int flag=0;
    while(query!=0&&flag==0)
    {
		printf("\nPress <0> to quit from the system\n");
    	printf("Press <1> to add a restaurant(add Restaurant)\n");
    	printf("Press <2> to delete a restaurant(delete Restaurant)\n");
    	printf("Press <3> to view details of all restaurants\n");
    	switch(query)
		{
    		case 0:flag=1;break;
        	case 1:insert_eat_location();break;
        	case 2:deleteRestaurant();break;

      
        	default:printf("Please enter appropriate choice");
        			break;
    	}
	}*/     
   return 0;   
}

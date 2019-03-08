#include <stdio.h>
#include <string.h>
#include<stdlib.h>
typedef enum{FAILURE,SUCCESS} statuscode;
typedef enum{FALSE,TRUE} boolean;
typedef struct item_name_tag
{
	char name[50];
	int no_of_time;
}item_name;
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
{ int  id;
  char name[50];
  char phone_no[11];
  boolean is_available;
  char ord_id[21];
  float curr_accu_commi;
  struct agent_tag *next;
}agent;
typedef struct user_tag
{// char us_id[21];
  char name[50];
  char address[50];
  char phone_no[11];
  //orders *ord;
  item_name *ordered_items;
  struct user_tag *next;
}user;
int order_id_allocator=1000;
typedef struct order_tag
{ char res_name[50];
  char res_address[50];
  int ord_id;
  int no_of_items;
  int item_index[100];
  int quantity_index[100];
 /* char ag_id[21];
  char ag_phone[11];
  */
  agent *allocated_agent;
 /* char us_name[50];
  char us_address[50];
  char us_phone_no[11];*/
  user *username;
  float total_price;
  location *ordered_restaurant;
  struct order_tag *next;
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
	printf("MENU\n");
	printf("No.of items\t:%d\n",lptr->no_of_items);
	while(i<(lptr->no_of_items))
	{
		printf("%d.	%s\n",i+1,lptr->item[i].itemname);
		printf("  Price\t:%f\n",lptr->item[i].price);
		i++;
	}
}
void print_location(location *nptr)
{
	printf("Eating spot name\t:%s\n",nptr->name);
	printf("Address\t:%s\n",nptr->address);
	printf("Zone\t:%s\n",nptr->zone);
	if(nptr->category==1)
	{
		printf("Category\t:Restaurant\n");
	}
	else if(nptr->category==2)
	{
		printf("Category\t:Cafe\n");
	}
	else if(nptr->category==3)
	{
		printf("Category\t:Pub\n");
	}
		if(nptr->cuis_category==1)
	{
		printf("Cuisine\t:NORTH INDIAN\n");
	}
	else if(nptr->cuis_category==2)
	{
		printf("Cuisine\t:SOUTH INDIAN\n");
	}
	else if(nptr->cuis_category==3)
	{
		printf("Cuisine\t:CONTINENTAL\n");
	}
	printf("No. of seats\t:%d\n",nptr->no_of_seats);
	menu *lptr=nptr->res_menu;
	visit_menu(lptr);
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
	    printf("Eating Spot Name\t:%s\nEating Spot Address\t:%s\n",nptr->name,nptr->address);
		nptr=nptr->next;
	}
}
void Traverse_cuis(cuis_location *lptr)
{ 	cuis_location *nptr=lptr;
	while(nptr!=NULL)
	{
	    printf("Eating Spot Name\t:%s\nEating Spot Address\t:%s\n",nptr->name,nptr->address);
		nptr=nptr->next;
	}
}
void search_category(cat_location *jptr,cat_location *kptr,cat_location *lptr)
{
	int x;
	printf("Enter the category of restaurant you are searching for\t:\n");
	printf("PRESS 1 FOR RESTAURANT\nPRESS 2 FOR CAFE\nPRESS 3 FOR PUB\n");
	scanf("%d",&x);
	if(x==1)
	{
		Traverse_cat(jptr);
	}
	else if(x==2)
	{
		Traverse_cat(kptr);
	}
	else if(x==3)
	{
		Traverse_cat(lptr);
	}
}
void search_cuisine(cuis_location *jptr,cuis_location *kptr,cuis_location *lptr)
{
	int x;
	printf("Enter the cuisine of restaurant you are searching for\t:\n");
	printf("PRESS 1 FOR NORTH INDIAN\nPRESS 2 FOR SOUTH INDIAN\nPRESS 3 FOR CONTINENTAL\n");
	scanf("%d",&x);
	if(x==1)
	{
		Traverse_cuis(jptr);
	}
	else if(x==2)
	{
		Traverse_cuis(kptr);
	}
	else if(x==3)
	{
		Traverse_cuis(lptr);
	}
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
           		printf("%s\n",nptr->name);
           		flag=1;
         	}
        	else
         	{
            	printf("%s\n",nptr->name);
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
	   if(strcmp(nptr->address,x)!=0&&strcmp(nptr->zone,y)==0)
      	{ 
			if(flag==0)
         {
		 	printf("Restaurant in nearby area:\n");
           	printf("%s\n",nptr->name);
           	flag=1;
         }
        	else
         {
            printf("%s\n",nptr->name);
         }
      	}
     	nptr=nptr->next;
   	}
   	if(flag==0)
   	printf("No restaurant found in nearby areas\n");
} 
statuscode insert_agent(agent **ag_ptr,int id,char name[50],char phone_no[11],float curr_accu_comm)
{	
	statuscode sc=FAILURE;
	agent *nptr=(agent*)malloc(sizeof(agent));
	if(nptr!=NULL)
	  {  nptr->id=id;
	     strcpy(nptr->name,name);
	     strcpy(nptr->phone_no,phone_no);
	     nptr->curr_accu_commi=curr_accu_comm;
	     nptr->is_available=TRUE;
		 nptr->next=*ag_ptr;
         *ag_ptr=nptr;
	  	 sc=SUCCESS;
	  }
}
void print_agents(agent *ag_ptr)
{
	agent *nptr=ag_ptr;
	while(nptr!=NULL)
	{
			printf("Agent Id\t:%d\n",nptr->id);
			printf("Agent Name\t:%s\n",nptr->name);
			printf("Agent Phone No.\t:%s\n",nptr->phone_no);
			printf("Accumulated Commission\t:%f\n",nptr->curr_accu_commi);
			if(nptr->is_available==TRUE)
			{
				printf("Availability\t:Available\n");
			}
			else
			{
				printf("Availability\t:Not Available\n");
				printf("Busy with Order ID\t:%s\n",nptr->ord_id);
			}
			nptr=nptr->next;
	}
}
void print_live_orders(orders *optr)
{
	int i;orders *nptr=optr;
	while(nptr!=NULL)
	{
			printf("Order Id\t:%d\n",nptr->ord_id);
			printf("Restaurant Name\t:%s\n",nptr->res_name);
			printf("Restaurant Address\t:%s\n",nptr->res_address);
			printf("No. of items\t:%d\n",nptr->no_of_items);
			for(i=0;i<nptr->no_of_items;i++)
			{
				printf("%d. %s\n",i+1,nptr->ordered_restaurant->res_menu->item[nptr->item_index[i]].itemname);
				printf(" Price\t:%f\n",nptr->ordered_restaurant->res_menu->item[nptr->item_index[i]].price);
			} 
			printf("Username\t:%s",nptr->username->name);
			printf("User Address\t:%s",nptr->username->address);
			printf("User Phone No.\t:%s",nptr->username->phone_no);
			printf("Total price to be paid\t:%f",nptr->total_price);
			printf("Agent Name\t:%s",nptr->allocated_agent->name);
			printf("Agent Phone No.\t:%s",nptr->allocated_agent->phone_no);
	  nptr=nptr->next;   
     
  }
}
statuscode takeorder(location *all_eatspots,orders **pending_order,cuis_location *north,cuis_location *south,cuis_location *cont,user **users,agent **agent_list,agent **agent_busy_list)
{ Traverse(all_eatspots);
  int temp=1;
  int food_type;
  char name[100],address[100];
  statuscode sc=SUCCESS;
  printf("Enter cuisine you want:1)North Indian 2)South Indian 3)Continental ");
  scanf("%d",&food_type);
  if(food_type==1)
   {
   	 if(north==NULL)
   	  { temp=0;
   	    sc=FAILURE;
   	    printf("No eating place available for required cuisine\n");
	  }
     else
      { printf("Following are the places available\n");
        Traverse_cuis(north);
	  }
   }
  else if(food_type==2)
   { 
     if(south==NULL)
   	  {  temp=0;
   	     sc=FAILURE;
   	     printf("No eating place available for required cuisine\n");
	  }
	 else
	  {  printf("Following are the places available\n");
         Traverse_cuis(south);
	  }	 
   }
  else if(food_type==3)
   {
   	 if(cont==NULL)
   	  {
		 temp=0;
   	     sc=FAILURE;
   	     printf("No eating place available for required cuisine\n"); 
		 
	  }
	 else
	  { printf("Following are the places available\n");
         Traverse_cuis(cont);
	  	
	  }
   }
  if(temp==1)
  {
  
  printf("Enter name of the restaurant:");
  scanf("%s",name);
  printf("Enter address of the restaurant: ");
  scanf("%s",address);
  orders *orde=(orders*)malloc(sizeof(orders));
  strcpy(orde->res_name,name);
  strcpy(orde->res_address,address);
  location *nptr=all_eatspots;
  temp=0;
  while(nptr!=NULL && temp==0)
   { 
     if((strcmp(nptr->name,name)==0) && (strcmp(nptr->address,address)==0))
   	  { temp=1;
   	  }
	 else
	  nptr=nptr->next;
   }
  if(temp==0)
   { printf("Invalid name and address: ");
   }
  else
   { printf("You can order now:\n ");
     printf("Below is the menu: \n");
	 visit_menu(nptr->res_menu);
	 orde->ordered_restaurant=nptr;
	 printf("Enter no of items you want to order: ");
	 int n;
	 scanf("%d",&n);
	 int a[n];
	 printf("Enter choice nos :");
	 int i=0,p=0; 
	 float price=0; 
	 for(i=0;i<n;i++)
	  {  printf("ENTER YOUR CHOICE No %d: \n",i+1);
	  	 scanf("%d",&a[i]);
	  	 int x;
	  	 printf("Enter quantity: ");
	  	 scanf("%d",&x);
	  	 if(a[i]<=nptr->res_menu->no_of_items)
	  	  { 
			orde->item_index[p]=a[i]-1;
	  	    orde->quantity_index[p]=x;
	  	    price=price+(orde->ordered_restaurant->res_menu->item[a[i]-1].price)*x;
	  	  	p++;
		  }
		  
	  }
	 orde->no_of_items=p;
	 orde->total_price=price;
	 char us_phone[50];
	 printf("ENTER USER PHONE NO: ");
	 scanf("%s",us_phone);
	 user *kptr=*users;
	 temp=0;
	 while(kptr!=NULL && temp==0)
	  { if(strcmp(kptr->phone_no,us_phone)==0)
	     { 
	       temp=1;
		 }
		else
		 {
		 	kptr=kptr->next;
		 }
	  }
	 if(temp==0)
	  { printf("Register new user:\n");
	    user* new_user=(user*)malloc(sizeof(user));
	    strcpy(new_user->phone_no,us_phone);
	    char us_name[50];
	    char us_address[50];
	    printf("Enter new user name: ");
	    scanf("%s",us_name);
	    printf("Enter new user address: ");
	    scanf("%s",us_address);
		strcpy(new_user->name,us_name);   
		strcpy(new_user->address,us_address);
		new_user->next=*users;
		*users=new_user;
		kptr=new_user;
		printf("New user registered successfully: ");
	  }
	 orde->username=kptr;
	
	 if(*agent_list!=NULL)
	 { agent *alloc_agent;
	   alloc_agent=*agent_list;
	   *agent_list=(*agent_list)->next;
	   orde->allocated_agent=alloc_agent;
	   alloc_agent->next=*agent_busy_list;
	   *agent_busy_list=alloc_agent;
	   orde->ord_id=order_id_allocator;
	   order_id_allocator++;
	   orde->next=*pending_order;
	   *pending_order=orde;
	   printf("Your order is registered successfully: Agent %s is assigned to you.\nContact no of agent:%s",alloc_agent->name,alloc_agent->phone_no);
     }
    else
     { printf("No free agents available:");
	 }
   }
 
  
  }
  return sc;
}
statuscode delivery(orders **pending_orders,agent **agent_list,agent **agent_busy_list)
{ orders *nptr=*pending_orders,*kptr;
  orders *prev=NULL;
  statuscode sc=SUCCESS;
  int order_id;
  printf("Enter order id: ");
  scanf("%d",&order_id);
  int temp=0;
  while(nptr!=NULL && temp==0)
    { if(nptr->ord_id==order_id)
       { 
       	 temp=1;
	   }
	  else
	   {prev=nptr;
	   	nptr=nptr->next;
	   }
	}
  if(temp==0)
   {
   	  printf("Order with given id does not exist:");
   	  sc=FAILURE;
   }
  else
   { kptr=nptr;
     printf("Price=%f",kptr->total_price);
     if(prev==NULL)
      { *pending_orders=nptr->next;
      }
     else 
      { prev->next=nptr->next;
      }
     kptr->next=NULL;
    // kptr->allocated_agent->curr_accu_commi=(kptr->allocated_agent->curr_accu_commi)+0.10*kptr->total_price;
   	 agent *p=*agent_busy_list,*pr=NULL;
   	 temp=0;
   	 while(p!=NULL && temp==0)
   	  { if(p->id == kptr->allocated_agent->id)
	      { 
	        temp=1;
		  }
		else
		  { pr=p;
		  	p=p->next;
		  }
	  }
	p->curr_accu_commi=(p->curr_accu_commi)+((1.0*kptr->total_price)/10);
	free(kptr);
   	if(temp==1)
   	{
	   
	if(pr==NULL)
   	  { *agent_busy_list=(*agent_busy_list)->next;
	    p->next=*agent_list;
	    *agent_list=p;
	  }
	 else
	  { pr->next=p->next;
	    p->next=*agent_list;
	    *agent_list=p;
	  } 
    }
   }
   return sc;
}
statuscode cancel_order(orders **pending_orders,agent **agent_list,agent **agent_busy_list)
{ orders *nptr=*pending_orders,*kptr;
  orders *prev=NULL;
  statuscode sc=SUCCESS;
  int order_id;
  printf("Enter order id: ");
  scanf("%d",&order_id);
  int temp=0;
  while(nptr!=NULL && temp==0)
    { if(nptr->ord_id==order_id)
       { 
       	 temp=1;
	   }
	  else
	   {prev=nptr;
	   	nptr=nptr->next;
	   }
	}
  if(temp==0)
   {
   	  printf("Order with given id does not exist:");
   	  sc=FAILURE;
   }
  else
   { kptr=nptr;
     printf("Price=%f",kptr->total_price);
     if(prev==NULL)
      { *pending_orders=nptr->next;
      }
     else 
      { prev->next=nptr->next;
      }
     kptr->next=NULL;
    // kptr->allocated_agent->curr_accu_commi=(kptr->allocated_agent->curr_accu_commi)+0.10*kptr->total_price;
   	 agent *p=*agent_busy_list,*pr=NULL;
   	 temp=0;
   	 while(p!=NULL && temp==0)
   	  { if(p->id == kptr->allocated_agent->id)
	      { 
	        temp=1;
		  }
		else
		  { pr=p;
		  	p=p->next;
		  }
	  }
	//p->curr_accu_commi=(p->curr_accu_commi)+((1.0*kptr->total_price)/10);
	free(kptr);
   	if(temp==1)
   	{
	   
	if(pr==NULL)
   	  { *agent_busy_list=(*agent_busy_list)->next;
	    p->next=*agent_list;
	    *agent_list=p;
	  }
	 else
	  { pr->next=p->next;
	    p->next=*agent_list;
	    *agent_list=p;
	  } 
    }
   }
   return sc;
}
int main()
{   statuscode sc;
	cat_location *res=NULL;
	cat_location *pub=NULL;
	cat_location *cafe=NULL;
	cuis_location *north=NULL;
	cuis_location *south=NULL;
	cuis_location *cont=NULL;
	location *all_eatspots=NULL;
	location *fptr;
	orders *pending_orders=NULL;
	user *users=NULL;
	agent *agent_list=NULL,*agent_busy_list=NULL;
	sc=insert_agent(&agent_list,111,"RAMU","912345678",0.0);
	sc=insert_agent(&agent_list,112,"SHAMU","912345678",0.0);
	sc=insert_agent(&agent_list,113,"GOLU","9423123458",0.0);
	
	char res_name[50];
    char res_address[100];
    char res_zone[50];
    int res_no_of_seats;
    menu *res_res_menu;
    int res_category; 
    int res_cuis_category;
    int i;
   	for(i=0;i<1;i++)
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
    printf("PRESS 1 FOR RESTAURANT\nPRESS 2 FOR CAFE\nPRESS 3 FOR PUB\n");
    scanf("%d",&res_category);
    printf("Enter the cuisine of your restaurant\t:\n");
    printf("PRESS 1 FOR NORTH INDIAN\nPRESS 2 FOR SOUTH INDIAN\nPRESS 3 FOR CONTINENTAL\n");
    scanf("%d",&res_cuis_category);
	//res_category=1;
    //res_cuis_category=2;
 
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
   //	Traverse(all_eatspots);
	/*Traverse_cat(res);
    Traverse_cat(cafe);
    Traverse_cat(pub);
   //char sp_facilities[20][100];*/
   
    int x,query=-1;
	printf("\t\t\t\t\t  *********************************************\n");
	printf("\t\t\t\t\t* WELCOME TO OUR LIVE FOOD ORDER TRACKING SYSTEM *\n");
	printf("\t\t\t\t\t  *********************************************\n");
    printf("\n\n\n");  
    int flag=0;
   
    while(query!=0 && flag==0)
    {
		printf("\nPress <0> to quit from the system\n");
    	printf("Press <1> to search a restaurant by category\t:\n");
    	printf("Press <2> to search a restaurant by cuisine\t:\n");
    	printf("Press <3> search a restaurant by area\t:\n");
    	printf("Press <4> to insert a eat location\t:\n");
    	printf("Press <5> to take order from a eating pot\t:\n");
    	printf("Press <6> to get the list of all live orders\t:\n");
    	printf("Press <7> to get the details of available agents:\n");
    	printf("Press <8> to complete delivery of a order:\n");
    	printf("Press <9> to get the details of busy agents:\n");
    	scanf("%d",&query);
    	switch(query)
		{
    		case 0:flag=1;break;
        	case 1:search_category(res,cafe,pub);break;
        	case 2:search_cuisine(north,south,cont);break;
        	case 3:search_area(all_eatspots);break;
        	case 5:takeorder(all_eatspots,&pending_orders,north,south,cont,&users,&agent_list,&agent_busy_list);break;
        	case 6:print_live_orders(pending_orders);break;
        	case 7:print_agents(agent_list);break;
        	case 8:sc=delivery(&pending_orders,&agent_list,&agent_busy_list);
        	case 9:print_agents(agent_busy_list);break;
			default:printf("Please enter appropriate choice");
        			break;
    	}
	}    
   return 0;   
}

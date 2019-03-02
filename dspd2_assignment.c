#include <stdio.h>
#include <string.h>
typedef enum{FAILURE,SUCCESS} statuscode;
typedef enum{FALSE,TRUE} boolean;
typedef struct item_tag
{ char itemname[100];
  float price;
  int category; // if 1 then north indian if 2 then south indian if 3 then continental
}items;
typedef struct menu_tag
{
   items item[100]; 
}menu;
typedef struct restaurant_tag
{  char name[50];
   char adderess[100];
   int no_of_seats;
   menu res_menu;
   struct restaurant_tag *next_res;
}restaurant;
typedef struct agent_tag
{ char id[21];
  char name[50];
  char phone_no[11];
  float curr_accu_commi;
  struct agent_tag *next_agen;
}agent;
typedef user_tag
{ char us_id[21];
  char name[50];
  char address[50];
  char phone_no[11];
  struct user_tag *next_user;
}user;
typedef order_tag
{ char res_name[50];
  char res_address[50];
  int no_of_items;
  int item_index[100];
  char ag_id[21];
  char ag_phone[11];
  struct order_tag *next_order;
}orders;


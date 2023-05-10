                          ////   Programmer   -   Anoop Shukla      /////
                      /////    RESTAURANT BIILING SYSTEM SOFTWARE    //////

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// General Purpose Standerd Library Which Include Functions, Control, Conversionl

struct items
{
  char item[50];
  float price;
  int quantity;
};

struct orders
{
    char customer[50];
    char date[50];
    int numofitems;
    struct items itm[50];
};

// FUNCTIONS TO GENERATE BILLS
void Bills_Generator_Header( char name[50], char date[50])
{
  printf("\n\n\t\t\t         A.S. Restaurant");
  printf("\n\t\t\t     **********************\n");
  printf("\nDate:%s",date);
  printf("\nInvoice to: %s",name);
  printf("\n");
  printf("================================================================================\n\n");
  printf("Items\t\t\t\t");
  printf("Quantity\t\t\t");
  printf("Total\t\t\t\t\n");
}

void Bills_Generator_Body(char itm[30], int qty,float price )
{
  printf("%s\t\t\t\t",itm);
  printf("%d\t\t\t",qty);
  printf("\t%.2f\t\t\t",qty*price);
  printf("\n");
}
void Bills_Generator_Footer( float total)
{
  float grandtotal;
  float discount = 0.1*total;   /// total*10/100 = 10% discount
  float nettotal = total-discount;
  float GST = 0.04 * nettotal;
  grandtotal = GST + nettotal;  // nettotal + GST = grandtotal
  printf("\n=================================================================================");
  printf("\n\nSub Total\t\t\t\t%.2f\n",total);
  printf("Discount @10%s\t\t\t\t%.2f\n","%",discount);
  printf("\t\t\t\t\t--------------");
  printf("\nNet Total\t\t\t\t%.2f\n",nettotal);
  printf("GST @4%s\t\t\t\t\t%.2f\n","%",GST);
  printf("\n=================================================================================");
  printf("\n\nGrand Total\t\t\t\t%.2f\n",grandtotal);
  printf("\n=================================================================================");
}

int main()
{ 
  float total ;
  int option,n,invoiceFound = 0;
  struct orders ord;
  struct orders order;
  char SaveBill = 'y';
  char name[50];

  FILE *fp;
  
  printf("\n\t     ======================A.S. Restaurant======================");
  printf("\n\nPlease select your prefered operation");
  printf("\n\n1. General Invoice");
  printf("\n2. Show All Invoices");
  printf("\n3. Search Invoice");
  printf("\n4. Exit");
  printf("\n\nYour choice is:\t");
  scanf("%d",&option);

  fgetc(stdin);
  
  switch (option)
 {
   case 1:
   //system("clear");
   printf("\n\nPlease Enter The Name Of Customer: ");
   fgets(ord.customer,50,stdin);
   ord.customer[strlen(ord.customer)-1]=0;
   strcpy(ord.date,__DATE__);
   printf("\nPlease Enter The Number Of Items:\t");
   scanf("%d",&n);
   ord.numofitems = n ;

   for (int i=0; i<n; i++)
   {
      fgetc(stdin);
      printf("\n\n");
      printf("Please Inter The Item %d :\t",i+1);
      fgets(ord.itm[i].item, 50, stdin);
      ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;  
      printf("Please Enter The Quantity:\t");
      scanf("%d",&ord.itm[i].quantity);
      printf("Please Enter The Unit  Price\t");
      scanf("%f",&ord.itm[i].price);
      total += ord.itm[i].quantity*ord.itm[i].price;
   }
  
   Bills_Generator_Header(ord.customer,ord.date);
  
   for (int i = 0; i < ord.numofitems; i++)
   {
    Bills_Generator_Body(ord.itm[i].item, ord.itm[i].quantity, ord.itm[i].price);
   }
  
   Bills_Generator_Footer(total);
  
   printf("\n\nDo you want to save the invoice[y/n]:\t");
   scanf("%s",&SaveBill);

   if (SaveBill=='y')
   {
     fp = fopen("RestaurantBill1.txt","a+");// open file in open mod
     fwrite(&ord, sizeof(struct orders),1,fp);
     if (fwrite != 0)
     {
       printf("\nSuccessfully saved");
     }
     else
     printf("Error saving");
     fclose(fp);
   }
    break;
  case 2:
  fp = fopen("RestaurantBill1.txt","r");  /// remode
  //fclose(fp);
  printf("\n\n  /////-> Your privious invoices <-/////\n\n");
  while (fread(&order,sizeof(struct orders),1,fp))
  { 
    float tot = 0;
    Bills_Generator_Header(order.customer,order.date);
    for ( int i = 0; i < order.numofitems; i++)
    {
      Bills_Generator_Body(order.itm[i].item,order.itm[i].quantity,order.itm[i].price);
      tot +=order.itm[i].quantity * order.itm[i].price;
    }
    Bills_Generator_Footer(tot);
  }  
  fclose(fp);
  break;

   case 3:
   printf("\nEnter Name Of Customer:\t");
   // fgetc(stdin);  /// Taking The string as Input
   fgets(name, 50, stdin);
   name[strlen(name)-1]=0;
   fp = fopen("RestaurantBill1.txt","r");  /// remode
  printf("\n\t\t     /////-> Invoice of %s <-/////\n",name);
  while (fread(&order,sizeof(struct orders),1,fp))
  { 
    float tot = 0;
    if(!strcmp(order.customer,name))
    {
     Bills_Generator_Header(order.customer,order.date);
     for ( int i = 0; i < order.numofitems; i++)
     {
       Bills_Generator_Body(order.itm[i].item,order.itm[i].quantity,order.itm[i].price);
       tot +=order.itm[i].quantity * order.itm[i].price;
     }
     Bills_Generator_Footer(tot);
     invoiceFound = 1;
    }
   
  }  
  if (!invoiceFound)
  {
    printf("Sorry the invoice for %s dosenot exists",name);
  }
  
  fclose(fp);
  break;

  case 4:
  printf("\n\t\tThank You\n\n\n");
  exit(0);
  break;

  default:
  printf("\nSorry Invalid Option\n\n");
  break;
  }  
  printf("\n\n");
 
  return 0;
}
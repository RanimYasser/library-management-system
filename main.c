#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
    int year;
    int month;
} date;

typedef struct
{
    char ISBN[14];
    char title[60];
    char name[30];
    int quantity;
    float price;
    date pubdate;

} book;

book b[100];    //array that holds the books copied from the file

int i=0;    //number of books


int check_ISBN(char check[20])      //makes sure entered ISBN is all numbers
{
    int j,flag=0;
    for(j=0; j<strlen(check); j++)
    {
        if(check[j]>='0' && check[j]<='9')
        {
            flag=1;
        }
        else
        {
            flag=0;
            break;
        }
    }
    if(flag==1)
        return 1;
    else return 0;
}


int validate_Date(char month[],char year[])     //makes sure date entered exists
{
    int j;
    for(j=0; j<strlen(month); j++)
    {
        if(!isdigit(month[j]))
            return 0;
    }
    for(j=0; j<strlen(year); j++)
    {
        if(!isdigit(year[j]))
            return 0;
    }
    int x=atoi(month);
    if(x<1 ||x>12)
        return 0;
    int y=atoi(year);
    if(y>2022)
        return 0;

    return 1;
}


int validate_quantity(char quantity[])      //makes sure quantity entered is a number
{
    int j;
    for(j=0; j<strlen(quantity); j++)
    {
        if(!isdigit(quantity[j]))
            return 0;
    }
    return 1;
}


float validate_price(char price[])      //makes sure price entered is a number
{
    int j;

    for(j=0; j<strlen(price); j++)
    {
        if(!isdigit(price[j])&&price[j]!='.')
            return 0;
    }
    float x=atof(price);
    return  x;
}


int check()     //checks whether the entered username and password are correct (exist in the credentials file)
{
    char pass1[20];
    char username1[20];

    FILE*f=fopen("credentials.txt","r");

    if(f==NULL)
        printf("\aFile not found.");
    else
        while(!feof(f))
        {
            fscanf(f,"%s%s",username1,pass1);
        }

    char pass2[20];
    char username2[20];

    printf("\nEnter username :\n");
    scanf("%s",username2);
    printf("Enter password :\n");
    scanf("%s",pass2);

    if(((strcmp(username1,username2)==0)&&(strcmp(pass1,pass2)==0)))
        menu();
    else if((strcmp(username1,username2)!=0)&&(strcmp(pass1,pass2)!=0))
        printf("\aInvalid username and password, try again.\n");
    else if (strcmp(username1,username2)!=0)
        printf("\aInvalid username, try again.\n");
    else if (strcmp(pass1,pass2)!=0)
        printf("\aInvalid password, try again.\n");
    check();

    fclose(f);
}


void load()     // reads books from file into array b
{
    int j;
    FILE*f1=fopen("books.txt","r");
    if(f1==NULL)
        printf("\aFile not found.\n");
    else while(!feof(f1))
        {
            fscanf(f1,"%[^,],%[^,],%[^,],%d,%f,%d-%d\n",b[i].ISBN,b[i].title,b[i].name,&b[i].quantity,&b[i].price,&b[i].pubdate.month,&b[i].pubdate.year);
            i++;
        }
    fclose(f1);
}


void search()       //searches for a book using its ISBN
{
    int j;
    int flag=0;
    char x[20];     //ISBN entered by the user

    printf("Enter ISBN: ");
    gets(x);

    for(j=0; j<i; j++)
    {
        if(strcmp(x,b[j].ISBN)==0)
        {
            printf("\n------------------------------------\n\n");
            flag=1;
            printfunction(b,j);
        }
    }

    if(flag==0)
    {
        printf("\aNo book found with the entered ISBN.\n");
    }
}


void adv_search()       //searches for a book using a keyword
{
    int j, flag=0;
    char key[60];
    char*x,*y;

    printf("Enter keyword to search for: ");
    gets(key);

    printf("Search results: \n");
    for(j=0; j<i; j++)
    {
        x = strstr(b[j].title, key);
        y = strstr(b[j].name, key);
        if(x||y)
        {
            flag=1;
            printfunction(b,j);
        }
    }

    if(flag==0)
        printf("\aEntered keyword not found!");
}


void add()      //adds a new book
{
    char check[20];
    char quantity[100];
    char price[100];

    printf("Enter ISBN of book to be added: ");
    gets(b[i].ISBN);

    int j;

    for(j=0; j<i; j++)
    {
        if(strcmp(b[i].ISBN,b[j].ISBN) == 0)
        {
            printf("\aThe entered ISBN already exists.\n");
            return 0;
        }
    }

    strcpy(check,b[i].ISBN);
    if(check_ISBN(check) == 1 && strlen(check) == 13)
    {
        printf("Enter book title: ");
        gets(b[i].title);
        printf("Enter author name: ");
        gets(b[i].name);

        do
        {
            printf("Enter quantity: ");
            gets(quantity);

            if(validate_quantity(quantity))
                b[i].quantity = atoi(quantity);
        }
        while(validate_quantity(quantity)==0);

        do
        {
            printf("price:");
            gets(price);

            if(validate_price(price))
                b[i].price = validate_price(price);

        }
        while(!validate_price(price));

        char month[20];
        char year[10];

        do
        {
            printf("Date of publication\n");
            printf("month: ");
            gets(month);
            printf("year: ");
            gets(year);

            if(validate_Date(month, year))
            {
                b[i].pubdate.month = atoi(month);
                b[i].pubdate.year = atoi(year);
            }
        }
        while(validate_Date(month, year) == 0);

    }
    else
    {
        printf("Entered ISBN is invalid.\n");
        add();
    }
    i++;

}


void delete_book()      //takes ISBN from user and deletes book
{
    char x[20];
    int j;
    int flag=0;

    printf("Insert ISBN of the book to be deleted: ");
    gets(x);

    for(j=0; j<i; j++)
    {
        if(strcmp(b[j].ISBN,x) == 0)
        {

            flag = 1;
            b[j] = b[i-1];
            i--;
            printf("book deleted ,make sure to save changes\n");

            break;
        }
    }

    if(flag==0)
        printf("\aNo book found with the entered ISBN.\n");
}


void modify()       //takes ISBN from user and changes what user wants changed
{
    char ch[20];
    int j,x,indx,k;
    int flag=0;

    printf("Enter ISBN for the book you need modified: ");
    scanf("%s",ch);
    getchar();

    for(j=0; j<i; j++)
    {
        if(strcmp(ch,b[j].ISBN)==0)
        {
            flag=1;
            indx=j;
            break;
        }
    }

    if(flag==0)
    {
        printf("No book found with the entered ISBN.\n");
        return;
    }
    else
    {
        printfunction(b,indx);

        do
        {
            printf("Modify ISBN?\n");
            printf("1.yes\n2.no\n");
            scanf("%d",&x);
            getchar();
            if(x==1)
            {
                gets(b[indx].ISBN);
            }
        }
        while(x!=1 && x!=2);

        do
        {
            printf("Modify title?\n");
            printf("1.yes\n2.no\n");
            scanf("%d",&x);
            getchar();
            if(x==1)
            {
                gets(b[indx].title);
            }

        }
        while(x!=1 && x!=2);

        do
        {
            printf("Modify author name?\n");
            printf("1.yes\n2.no\n");
            scanf("%d",&x);
            getchar();
            if(x==1)
            {
                gets(b[indx].name);
            }
        }
        while(x!=1 && x!=2);

        do
        {
            printf("Modify quantity?\n");
            printf("1.yes\n2.no\n");
            scanf("%d",&x);
            if(x==1)
                scanf("%d",&b[indx].quantity);
        }
        while(x!=1 && x!=2);

        do
        {
            printf("Modify price?\n");
            printf("1.yes\n2.no\n");
            scanf("%d",&x);
            if(x==1)
                scanf("%f",&b[indx].price);
        }
        while(x!=1 && x!=2);

        do
        {
            printf("Modify publication date:\n");
            printf("1.yes\n2.no\n");
            scanf("%d",&x);
            if(x==1)
            {
                printf("Enter month: ");
                scanf("%d",&b[indx].pubdate.month);
                printf("Enter year: ");
                scanf("%d",&b[indx].pubdate.year);
            }
        }
        while(x!=1 && x!=2);
    }

    getchar();
}


void sort()     //Function that allows user to choose how they want to sort the list of books before printing it
{
    char s[5];

    printf("How do you want to sort your books?\n1. Sort by title\n2. Sort by date \n3. Sort by price\n");
    printf("Enter your choice number:\n");
    scanf("%s",s);
    getchar();

    if (strcmp(s,"1")==0)
        sortbytitle(b,i);

    else if (strcmp(s,"2")==0)
        sortbydate(b,i);

    else if (strcmp(s,"3")==0)
        sortbyprice(b,i);

    else
    {
        printf("\aInvalid choice \n");
        sort();
    }
}


void sortbytitle(book b[100],int i)      //sorts the books according to title ascendingly from A to Z
{
    int x,z;
    book temp;
    int pass;

    for (pass=1; pass<i; pass++)
    {
        for (x=0; x<i-pass; x++)
        {
            if (strcasecmp(b[x].title,b[x+1].title)>0)
            {
                temp=b[x];
                b[x]=b[x+1];
                b[x+1]=temp;
            }
        }
    }

    printf("\n------------------------------------\n\n");

    for (z=0; z<i; z++)
    {
        printfunction(b,z);
    }
}


void sortbydate(book b[],int i)      //sorts the books according to publishing date from newest to oldest
{
    int x,a,z;
    int pass;

    for (pass=1; pass<i; pass++)
    {
        for(x=0; x<i-pass; x++)
        {
            if (b[x].pubdate.year<b[x+1].pubdate.year)
            {
                book temp = b[x];
                b[x] = b[x+1];
                b[x+1] = temp;
            }
            else if (b[x].pubdate.year==b[x+1].pubdate.year)
            {
                if (b[x].pubdate.month<b[x+1].pubdate.month)
                {
                    book temp = b[x];
                    b[x] = b[x+1];
                    b[x+1] = temp;
                }
            }
        }
    }

    printf("\n------------------------------------\n\n");

    for (z=0; z<i; z++)
    {
        printfunction(b,z);
    }
}


void sortbyprice(book b[100],int i)      //sorts the books according to price ascendingly from cheapest to most expensive
{
    int a, x, pass, z;

    for (pass=1; pass<i; pass++)
    {
        for (x=0; x<i-pass; x++)
        {
            if (b[x].price>b[x+1].price)
            {
                book temp=b[x];
                b[x]=b[x+1];
                b[x+1]=temp;
            }
        }
    }

    printf("\n------------------------------------\n\n");

    for (z=0; z<i; z++)
    {
        printfunction(b,z);
    }
}


void printfunction(book b[],int x)      //prints the list of books after sorting
{
    int k;

    char month_array[12][12]= {"January","February","March","April","May","June","July","August","September","October","November","December"};

    k=b[x].pubdate.month;

    printf(" ISBN: %s\n",b[x].ISBN);
    printf(" Title: %s\n",b[x].title);
    printf(" Author: %s\n",b[x].name);
    printf(" Quantity: %d\n",b[x].quantity);
    printf(" Price: %0.2f$\n",b[x].price);
    printf(" Publishing Date: %s %d\n", month_array[k-1], b[x].pubdate.year);
    printf("\n------------------------------------\n\n");
}


void save()     //saves books from array to file
{
    int j;
    FILE *f = fopen("books.txt","w");
    for(j=0; j<i; j++)
    {
        fprintf(f,"%s,%s,%s,%d,%.2f,%d-%d\n",b[j].ISBN,b[j].title,b[j].name,b[j].quantity,b[j].price,b[j].pubdate.month,b[j].pubdate.year);
    }
    fclose(f);
}


void quit()     //exits program without saving
{
    char n[5];

    printf("\nWarning: changes may not be saved\n");   //warning
    printf("1. Save\n2. Quit\n");
    scanf("%s",n);

    if(strcmp(n,"1")==0)
    {
        save();
        exit(0);
    }
    else
        exit(0);
}


void menu()
{

    char z[10];

    getchar();
    while(1)
    {
        printf("~~~~~~~~~~~~~~~~~~~\n");
        printf("   MAIN MENU       \n");
        printf("~~~~~~~~~~~~~~~~~~~\n");

        printf("\nThe available operations :-\n");
        printf("1. Search for book via ISBN \n2. Search for  book via keyword \n");
        printf("3. Add a new book \n4. Delete a book \n5. Modify a book's details \n");
        printf("6. Print a sorted list of the books \n7. Save the books' data \n8. Quit \n");

        printf("\n\nInsert number of operation needed: ");
        gets(z);

        if(strcmp(z,"1")==0)
        {
            search();
        }
        else if(strcmp(z,"2")==0)
        {
            adv_search();
        }
        else if(strcmp(z,"3")==0)
        {
            add();
        }
        else  if(strcmp(z,"4")==0)
        {
            delete_book();
        }
        else  if(strcmp(z,"5")==0)
        {
            modify();
        }
        else  if(strcmp(z,"6")==0)
        {
            sort();
        }
        else  if(strcmp(z,"7")==0)
        {
            save();
        }
        else  if(strcmp(z,"8")==0)
        {
            quit();
        }
        else printf("\ainvalid number\n");


    }
}


int main()
{
    char choice[5] ;
    char pass1[20];
    char username1[20];
    load();
    printf("\t\t\t\t***************************************\n");
    printf("\t\t\t\t*****                             *****\n");
    printf("\t\t\t\t*****  Library Management System  *****\n");
    printf("\t\t\t\t*****                             *****\n");
    printf("\t\t\t\t***************************************\n");
    while(1)
    {
        printf("1-login\n2-Quit\nenter your choice number : \n");
        gets(choice);
        if (strcmp(choice,"1")==0)
        {
            check();

        }

        else if (strcmp(choice,"2")==0)
        {

            printf("Thank you :) ");

            exit(0);
        }
        else
        {
            printf("\ainvalid option\n");
        }
    }
    return 0;
}

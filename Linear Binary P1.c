#include<stdio.h>

int Linear_search(int rollno[],int count,int key)
{
    
 for(int i=0;i<count;i++)
    {
        if(rollno[i]==key)
        {
            printf("\n %d rollno is found..",rollno[i]);
            break;
        }
        else
        {
             printf("\n rollno is not found try again..");
        }
       
        
    }

};

int  Binary_search(int rollno[],int low,int high,int key)
{
       while (low <= high) 
    {
        int mid = low + (high - low) / 2; 
        if (rollno[mid] == key) 
        {
            printf("\n Rollno is found at index : %d",mid); 
            break;
        }

       
        if (rollno[mid] > key) 
        {
            high = mid - 1;
        }
        else 
        {
            low = mid + 1;
        }
    }
   
printf("\n rollno is not found...");

}
int main()
{
    int ch,rollno[100],key,count;

    printf("\n 1. Linear Search \n 2. Binary Search");
    printf("\n Enter Your Choice: ");
    scanf("%d",&ch);

    switch(ch)
    {

        case 1: 
        {
            printf("\n Enter count of Students...");
            scanf("%d",&count);

    for(int i=0;i<count;i++)
    {
        printf("\n Enter rollno in array...");
        scanf("%d",&rollno[i]);
    }       
        printf("\n Rollno in array are: ");
    for(int i=0;i<count;i++)
    {
        
      printf(" %d ",rollno[i]); 
    }
 
        printf("\n Enter rollno to search in array...");
        scanf("%d",&key);
    Linear_search(rollno,count,key);
            break;
        }

        case 2: 
        {
            printf("\n Enter count of Students...");
            scanf("%d",&count);

    for(int i=0;i<count;i++)
    {
        printf("\n Enter rollno in array...");
        scanf("%d",&rollno[i]);
    }       
        printf("\n Rollno in array are: ");
    for(int i=0;i<count;i++)
    {
        
      printf(" %d ",rollno[i]); 
    }
 
        printf("\n Enter rollno to search in array...");
        scanf("%d",&key);
       Binary_search(rollno,0,count-1,key);
            break;
        }

        default:
        {
            printf("\n Invalid Entry..");
            break;
        }
    }
    
return 0;
}

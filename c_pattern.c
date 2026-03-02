#include<stdio.h>

int main()
{
    int num,i,j,k;
    scanf("%d",&num);
    
    for(i=num;i>=0;i--,printf("\n"))
    {
        for(j=0;j<=i;j++){
        printf("* ");
        }
    }
    for(i=0;i<num;i++,printf("\n"))
    {
        for(j=0;j<=i;j++)
        printf("* ");
    }
    
    /*for(i=num;i>0;i--,printf("\n"))
    {
        for(j=0;j<i;j++)
        printf("*");
    
    }
    */
    for(i=0;i<num;i++,printf("\n"))
    {
        //right triangle
       /* for(j=num;j>i;j--)
        printf(" ");*/
        
        for(k=0;k<=i;k++)
        printf("*");//printf(" ");//change alternat to inverse right triangle
        
        //inverse right triangle
         /* for(j=num;j>i;j--)
          printf("*");*/
    }
}

/*Write a program to divide the message into variable length frames and sort
them and display the message at the receiving side*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 100
typedef struct
{
    int id;
    char data[MAX];
}frame;
void shuffleFrames(frame f[MAX], int n)
{
    int i;
    for(i=n-1; i>=0; i--)
    {
        int j = rand()%(i+1);
        frame temp = f[j];
        f[j] = f[i];
        f[i] = temp;
    }
}
void sortFrames(frame f[MAX], int n)
{
    int i, j;
    for(i=1; i<n; i++)
    {
        frame t = f[i];
        j = i-1;
        while(j>=0 && f[j].id > t.id)
        {
            f[j+1] = f[j];
            j = j-1;
        }
        f[j+1] = t;
    }
}
void showFrames(frame f[MAX] , int n ){
    int i;
    printf("\nframe_id \t frame_data \n");
    printf("----------------------------\n");
    for(i=0 ; i < n; i++)
        printf("%d \t\t %s \n", f[i].id, f[i].data);
}
int main()
{
    frame f[MAX];
    int i, j,n = 0,m = 0;
    int fsize;
    char msg[MAX];
    printf("Enter a message : ");
    fgets(msg , MAX, stdin);
    msg[strlen(msg)-1] = '\0';
    srand(time(NULL));
    for(i=0 ; m < strlen(msg) ; i++)
    {
        f[i].id = i;
        fsize = rand()%5+1;
        n++;
        strncpy(f[i].data , msg+m , fsize) ;
        m = m+fsize ;
    }
    shuffleFrames(f, n);
    printf("\nShuffled frames:");
    showFrames(f,n);
    sortFrames(f, n);
    printf("\nSorted frames:");
    showFrames(f,n);
    printf("\nfinal message : ");
    for(i=0; i< n; i++)
        printf("%s", f[i].data);
    printf("\n");
}

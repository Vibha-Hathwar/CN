//Write a program for error detecting code using 16 bits CRC-CCITT
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# define MAX 30
void crc(char *data, char *gen, char *rem)
{
    int i, j ;
    int dwordSize = strlen(data)-(strlen(gen)-1) ;
    char out[MAX];
    strcpy(out, data);
    for(i=0; i<dwordSize ; i++)
    {
        if(out[i]=='0') continue ;
        for(int j = 0 ; j<strlen(gen) ; j++)
            out[i+j] = (gen[j] == out[i+j] ? '0' : '1') ;
    }
    for(i=0;i<strlen(gen)-1;i++)
        rem[i]=out[dwordSize+i];
}
int main()
{
    int i, j;
    char dword[MAX],augWord[MAX],cword[MAX],char rem[MAX];
    char recv[MAX];
    char gen[MAX] = "10001000000100001";
    printf("\nCRC-16 Generator : x^16 + x^12 + x^5 + 1 ");
    printf("\nBinary Form : %s", gen);
    printf("\n\nEnter Dataword : ");
    scanf("%s", dword);
    strcpy(augWord, dword);
    for(i=0; i<strlen(gen)-1; i++)
        strcat(augWord, "0");
    printf("\nAugmented dataword is : %s",augWord);
    crc(augWord, gen, rem);
    strcpy(cword, dword);
    strcat(cword, rem);
    printf("\n\nFinal data transmitted : %s", cword);
        printf("\n\nEnter the data received : ");
    scanf("%s", recv);
    if(strlen(recv) < strlen(cword))
    {
        printf("\n Invalid input \n");
        exit(0);
    }
    crc(recv, gen, rem);
    printf("\nSyndrome = %s ", rem);
    for(i=0; i<strlen(rem); i++)
        if( rem[i] == '1')
        {
            printf("\nError occured !!! Corrupted data received.\n");
            exit(0);
        }
    printf("\nNo Error. Data received successfully.\n");
}

// Program No: 4(a) Server

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main()
{
char p[100],c[5000],ch;
int num,fd,fd2,f1;
mknod(FIFO1,S_IFIFO|0666,0);
mknod(FIFO2,S_IFIFO|0666,0);
printf("\n Server online...\n");
fd=open(FIFO1,O_RDONLY);
fd2=open(FIFO2,O_WRONLY);
printf("Server online\n waiting for client \n\n");
if((num=read(fd,p,100))==-1)
perror("\n Read Error ");
else
{
p[num]='\0';
printf("\n File is %s .\n",p);
if((f1=open(p,O_RDONLY))<0)
{
write(fd2,"File not found",15);
return 1;
}
else
{
stdin=fdopen(f1,"r");
num=0;
while((ch=fgetc(stdin))!=EOF)
c[num++]=ch;
c[num]=0;
printf(" Server: Transfering the contents of :%s ",p);
if(num=write(fd2,c,strlen(c))==-1)
printf("\n Error in writting to FIFO\n");
else
printf("\n File transfer completed \n");
}}}





 
// Program No: 4(b) Client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main()
{
char p[100],c[5000];
int num,fd,fd2,f1;
mknod(FIFO1,S_IFIFO|0666,0);
mknod(FIFO2,S_IFIFO|0666,0);
printf("\n Client online...\n");
fd=open(FIFO1,O_WRONLY);
fd2=open(FIFO2,O_RDONLY);
printf("Client : Enter the filename . \n\n");
scanf("%s",p);
num=write(fd,p,strlen(p));
if(num==-1)
{
perror("\nWrite Error.\n");
return 1;
}
else
{
printf("\n Waiting for reply\n");
if((num=read(fd2,c,5000))==-1)
perror("\nError while reading from fifo \n");
else
{
c[num]=0;
printf("%s",c);
}}
return 1;
}

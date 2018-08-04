#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>
#define SNAME "mysem"
char cnum[2];
void *readfn(void *x)
{
  char *cfifo=(char*)x;
  //fgets(message,100,stdin);
  while(1){
    char message[100];
    int cf=open(cfifo,O_RDONLY);
    read(cf,message,sizeof(message));
    printf("\t\t\tClient %c:",message[strlen(message)-1]);message[strlen(message)-1]='\0';
    printf("%s\n",message);
    close(cf);
  }
}

void *writefn(void *x)
{
  printf("My messages\n");
  char *sfifo="./sfifo";//(char*)x;
  while(1){
    char msg[100];
    fgets(msg,100,stdin);msg[strlen(msg)-1]=cnum[0];//printf("message:%s\n",msg);
    int sf=open(sfifo,O_WRONLY);
    write(sf,msg,strlen(msg)+1);
    close(sf);
  }
}
int main()
{
  char *sfifo="./sfifo";
  char cfifo[]="./cfifo";
  int c=mkfifo(sfifo,0666);

  int x[1];
  sem_t *sem;sem=sem_open(SNAME, 0);sem_getvalue(sem,x);
  //printf("Sem:%d",x[0]);
  sem_post(sem);
  sem_getvalue(sem,x);//printf("=>Sem:%d\n",x[0]);
  sprintf(cnum, "%d", x[0]);
  strcat(cfifo,cnum);
  c=mkfifo(cfifo,0666);printf("Enter any group number(n to no):");
  while(1){
    char ch[2];
    
    fgets(ch,sizeof(ch),stdin);
    if(ch[0]=='\0') continue;
    if(ch[0]=='n') break;
    cnum[1]=ch[0];
    int fd=open(sfifo,O_WRONLY);
    write(fd,cnum,strlen(cnum)+1);
    close(fd);
  }
  
  printf("client fifo:%s\n",cfifo);
  pthread_t r,w;
  pthread_create(&r,NULL,readfn,&cfifo);
  pthread_create(&w,NULL,writefn,&sfifo);
  pthread_join(r,NULL);
  pthread_join(w,NULL);
}

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#define SNAME "mysem"

int main()
{
  char *sfifo="./sfifo";
  int c=mkfifo(sfifo,0666);
  sem_t *sem = sem_open(SNAME, O_CREAT, 0644, 1);

  //sem_t *sem = sem_open(SNAME, 0);
  sem_init(sem,0,0);
  int n;char p[2];
  printf("Enter number of groups:");
  fgets(p,sizeof(p),stdin);
  n=p[0]-'0';printf("Total groups:%d\n",n);
  int groups[100][100];
  for(int i=1;i<=n;i++){groups[i][0]=0;}printf("Chat:\n");
  while(1)
  {
    char cfifo[100];

    int sf=open(sfifo,O_RDONLY);
    //while(cfifo[0]=='\0')
    read(sf,cfifo,sizeof(cfifo));
    close(sf);
    
    if(cfifo[0]>='0'&& cfifo[0]<='9')
    {
      groups[cfifo[1]-'0'][0]++;
      groups[cfifo[1]-'0'][groups[cfifo[1]-'0'][0]]=cfifo[0]-'0';
      continue;
    }
    
    int sender=cfifo[strlen(cfifo)-1]-'0';
    int grp=cfifo[strlen(cfifo)-2]-'0';
    cfifo[strlen(cfifo)-2]=cfifo[strlen(cfifo)-1];cfifo[strlen(cfifo)-1]='\0';
    printf("Sender:%d",sender);

    int x[1];sem=sem_open(SNAME, 0);sem_getvalue(sem,x);
    //printf("group %d message %s",grp,cfifo);
    for(int i=1;i<=groups[grp][0];i++)
    {
      if(sender==groups[grp][i])
      {
        for(int t=1;t<=groups[grp][0];t++)
          {  
            if(groups[grp][t]==sender) continue;
            char ch[]="./cfifo";char x[2];
            sprintf(x, "%d",groups[grp][t] );
            strcat(ch,x);
            //printf("%s\n",cfifo);
            int cf=open(ch,O_WRONLY);
        
            write(cf,cfifo,strlen(cfifo)+1);
            close(cf);
          }
          break;
      }
    }
    printf("  %s\n",cfifo);
  }
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define BUFFER 4096
int main (int argc,char *argv[]){
int i,j,k,l;
mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;/*Modes für das zu erstellende File setzen*/ 
char buf[BUFFER];/*Buffer anlegen*/
if (argc>2){/*Prüfung auf ausreichende Argumente*/
  if ((i=open(argv[1],O_RDONLY))!=-1){/*Versuch das erste File zum Lesen zu öffnen*/
    if((j=creat(argv[2],mode))!=-1){/*Versuch das zweite File zu erstellen*/
      while((k=read(i,buf,BUFFER))>0 && l!=-1){/*Versuch erstes File bis zum Ende lesen und Prüfung auf korrektes Schreiben*/
	l=write(j,buf,k);/*Versuch zweites File schreiben*/
      }
      if (k==-1){
	perror ("read");
	exit(1);
      }
      else if (l==-1){
	perror ("write");
	exit(1);
      }
      l=close(j);/*Kopie schliessen*/
      if (l==-1){
	fprintf(stderr,"Kopie:");
	perror ("close");
	exit(1);
      }
    }
    else{
	perror ("creat");
	exit(1);
    }
    l=close(i);/*Zu kopierendes File schliessen*/
    if (l==-1){
      	fprintf(stderr,"Zu kopierendes File:");
	perror ("close");
	exit(1);
    }
  }
  else{
    perror("open");
    exit(1);
  }
}
else{
  fprintf(stderr,"Too few parameters for application %s\n",argv[0]);
  exit(1);
}
return 0;
}
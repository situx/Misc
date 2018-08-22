#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]){
  int fd,rd,zaehler=0,top,end,j=0;
  char buffer[1];/*Buffer zum Schreiben*/
  if (argc<3){/*Prüfung auf ausreichende Argumente*/
    fprintf(stderr,"Zu wenig Argumente eingegeben\n");
    exit(1);
  }
  top=atoi(argv[2]);/*Umwandlung des 2. Arguments in einen Int*/
  if((fd=(open(argv[1],O_RDONLY)))==-1){/*Versuch das File zu öffnen*/
    perror("open");
    exit(1);
  }
  end=lseek(fd,0,SEEK_END);/*Speichern der Filelänge*/
  lseek(fd,0,SEEK_SET);/*Setzen des Pointers an den Anfang*/
  while((rd=read(fd,buffer,1))>0 && zaehler<top && j<end){/*Solange wir etwas lesen, unsere geforderten Zeilen und das Dateiende noch nicht erreicht sind*/
    printf("%c",buffer[0]);/*Gebe Buffer aus*/
    if (buffer[0]=='\n')/*Wenn Buffer ein \n ist erhöhe den Zähler*/
      zaehler++;
    j++;
  }
  if(rd==-1){/*Abfangen des readFehlers*/
    perror("read");
    exit(1);
  }
  if(close(fd)==-1){/*Abfangen des Closefehlers*/
    perror("close");
    exit(1);
  }
  return 0;
}

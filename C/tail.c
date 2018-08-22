#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]){
  int fd,rd,zaehler=0,top,end,offset=0;
  char buffer[1];/*Buffer für das Einlesen*/
  if (argc<3){/*Argumentsprüfung*/
    fprintf(stderr,"Zu wenig Argumente eingegeben\n");
    exit(1);
  }
  top=atoi(argv[2]);/*Umwandlung des zweiten Arguments (Menge der auszugebenden Zeilen) in einen Int*/
  if((fd=(open(argv[1],O_RDONLY)))==-1){/*Versuch das File zu öffnen*/
    perror("open");
    exit(1);
  }
  end=lseek(fd,offset,SEEK_END);/*Speicherung der Länge des Files in end*/
  offset=end;/*Speicherung von end in offset zur späteren Verwendung*/
  lseek(fd,--offset,SEEK_SET);/*Springen zum letzten Buchstaben der Datei*/
  while((rd=read(fd,buffer,1))>=0){/*Solange noch etwas eingelesen wird*/
    lseek(fd,--offset,SEEK_SET);/*Erniedrige offset und springe an diese Stelle*/
    if (buffer[0]=='\n')/*Wenn ein '\n' gefunden wird wird der Zeilenzähler erhöht*/
      zaehler++;
    if (offset==0)/*Wenn der Offset 0 ist und wir haben noch keine Ausgabe gehabt wird das bisher erreichte ausgegeben (File ist zuEnde)*/
      zaehler=top;
    if (zaehler>=top){/*Wenn wir die geforderte Zeilenmenge erreicht haben*/
      while(offset<end && rd!=-1){/*Schreiben ab der Offsetposition bis zum Dateiende*/
	lseek(fd,offset++,SEEK_SET);
	rd=read(fd,buffer,1);
	printf("%c",buffer[0]);
      }
      if (rd==-1){/*Abfangen eventueller Fehler bei read*/
	perror("read");
	exit(1);
      }
    break;/*Abbrechen der äußeren Schleife*/
    }
  }
  if(close(fd)==-1){/*Fehlerbehandlung beim Schließen des Files*/
    perror("close");
    exit(1);
  }
  return 0;
}

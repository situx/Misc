#include <stdio.h>
#include <stdlib.h>
void readFile(FILE *f,FILE *out1,FILE *out2,FILE *out3,FILE *out4){/*Funktion für das Einlesen der Eingabedatei und zum Verteilen auf die 4 RAID-Dateien*/
char get,save[2];/*get als Einlesebyte und save als Speicherarray für die Einlesewerte*/
int i=3;/*Variable zur Bestimmung wo das Paritätsbit liegen soll*/
    while ((get=fgetc(f))!=EOF){/*Solange das File noch nicht zu Ende ist lese ein*/
	  save[0]=get;/*Der erste Wert wird an die erste Stelle des Arrays geschrieben*/
	  if ((get=fgetc(f))!=EOF){/*Weitere Prüfung auf das zweite Byte*/
	      save[1]=get;/*Speichern des zweiten Byte*/
	      if ((get=fgetc(f))!=EOF){/*Prüfung auf das dritte Byte*/
		switch (i){
		case 0:fputc((save[0]^save[1]^get),out1);/*Errechnen des Paritätsbytes und speichern in Datei out1.txt*/
		       fputc(save[0],out2);/*Schreiben des 1. Byte indie Datei out2.txt*/
		       fputc(save[1],out3);/*Schreiben des 2. Byte in die Datei out3.txt*/
		       fputc(get,out4);/*Schreiben des 3. Byte in die Datei out4.txt*/
		       i=3;
		       break;
		case 1:fputc(save[0],out1);/*Schreiben des 1. Byte indie Datei out1.txt*/
		       fputc((save[0]^save[1]^get),out2);/*Errechnen des Paritätsbytes und speichern in Datei out2.txt*/
		       fputc(save[1],out3);/*Schreiben des 2. Byte in die Datei out3.txt*/
		       fputc(get,out4);/*Schreiben des 3. Byte in die Datei out4.txt*/
		       i--;
		       break;
		case 2:fputc(save[0],out1);/*Schreiben des 1. Byte indie Datei out1.txt*/
		       fputc(save[1],out2);/*Schreiben des 2. Byte in die Datei out2.txt*/
		       fputc((save[0]^save[1]^get),out3);/*Errechnen des Paritätsbytes und speichern in Datei out3.txt*/
		       fputc(get,out4);/*Schreiben des 3. Byte in die Datei out4.txt*/
		       i--;
		       break;
		case 3:fputc(save[0],out1);/*Schreiben des 1. Byte indie Datei out1.txt*/
		       fputc(save[1],out2);/*Schreiben des 2. Byte in die Datei out2.txt*/
		       fputc(get,out3);/*Schreiben des 3. Byte in die Datei out3.txt*/
		       fputc((save[0]^save[1]^get),out4);/*Errechnen des Paritätsbytes und speichern in Datei out4.txt*/
		       i--;
		 }
	      }
	  }
    }	
}
void reconstruct(FILE *rec,FILE *out1,FILE *out2,FILE *out3,int gone){/*Funktion zur Rekonstruktion der Ausgangsdatei*/
char get,save[2];/*get als Einlesebyte und save als Speicherarray für die Einlesewerte*/
int i=4;/*Variable zur Bestimmung wo das Paritätsbit liegt*/
fseek(out1,0,SEEK_SET);/*Setzen der Pointer auf den Anfang ihres jeweiligen Files*/
fseek(out2,0,SEEK_SET);
fseek(out3,0,SEEK_SET);
  while ((get=fgetc(out1))!=EOF){/*Solange das File noch nicht zu Ende ist speichere den aktuellen Char in get*/
    save[0]=get;/*Speichern des get-Wertes im Array*/
    if ((get=fgetc(out2))!=EOF){/*Weiteres Einlesen*/
	save[1]=get;/*Speichern des get-Wertes im Array*/
	if ((get=fgetc(out3))!=EOF){/*Weiteres Einlesen*/
	switch(gone){/*Je nachdem welche Datei zum Rekonstruieren fehlt, gibt es verschiedene Fälle*/
	case 1:switch (i){/*1.Die erste Datei fehlt: Es wird mithilfe von i ermittelt wo das Paritybyte der jeweiligen 4 Byte steht*/
	       case 1:fputc(save[0],rec);/*Ist das Paritybyte an der ersten Stelle, so kann der Rest der Reihe nach übertragen werden*/
		      fputc(save[1],rec);/*da kein Informationsverlust entstanden ist*/
		      fputc(get,rec);
		      break;
	       case 2:fputc((save[0]^save[1]^get),rec);/*Ist das Paritybyte an der zweiten Stelle, so muss diese zum Ersetzen benutzt werden*/
		      fputc(save[1],rec);/*Der Rest wird normal weiterkopiert*/
		      fputc(get,rec);
		      break;
	       case 3:fputc((save[0]^save[1]^get),rec);/*Ist das Paritybyte an der dritten Stelle, so wird wiederum die Ersetzung des ersten Bytes vorgenommen und der Rest kopiert*/
		      fputc(save[0],rec);
		      fputc(get,rec);
		      break;
	       case 4:fputc((save[0]^save[1]^get),rec);/*An der 4. Stelle geschieht die Ersetzung analog*/
		      fputc(save[0],rec);
		      fputc(save[1],rec);
	}
	break;
	case 2:switch (i){/*2.Die zweite Datei fehlt: Es wird mithilfe von i ermittelt wo das Paritybyte der jeweiligen 4 Byte steht*/
	       case 1:fputc((save[0]^save[1]^get),rec);/*Ist das Paritybyte an erster Stelle so wird es ersetzt*/
		      fputc(save[1],rec);
		      fputc(get,rec);
		      break;
	       case 2:fputc(save[0],rec);/*Ist das Paritybyte an der zweiten Stelle, so kann der Rest der Reihe nach übertragen werden da kein Informationsverlust entstanden ist*/
		      fputc(save[1],rec);
		      fputc(get,rec);
		      break;
	       case 3:fputc(save[0],rec);/*Ist das Paritybyte an dritter Stelle, so wird statt dem Wert save[1] der Paritywert errechnet*/ 
	       	      fputc((save[0]^save[1]^get),rec);
		      fputc(get,rec);
		      break;
	       case 4:fputc(save[0],rec);/*Analog zu 1. und 3.*/
	       	      fputc((save[0]^save[1]^get),rec);
		      fputc(save[1],rec);
	}
	break;
	case 3:switch (i){/*3.Die dritte Datei fehlt: Es wird mithilfe von i ermittelt wo das Paritybyte der jeweiligen 4 Byte steht*/
	       case 1:fputc(save[1],rec);/*Ist das Paritybyte an der ersten Stelle,so wird die dritte Stelle errechnet*/
		      fputc((save[0]^save[1]^get),rec);
		      fputc(get,rec);
		      break;
	       case 2:fputc(save[0],rec);/*Analog an zweiter Stelle mit vertauschten Abspeicherpositionen*/
	       	      fputc((save[0]^save[1]^get),rec);
		      fputc(get,rec);
		      break;
	       case 3:fputc(save[0],rec);/*Ist das Paritybyte an der dritten Stelle, so kann der Rest der Reihe nach übertragen werden da kein Informationsverlust entstanden ist*/
		      fputc(save[1],rec);
		      fputc(get,rec);
		      break;
	       case 4:fputc(save[0],rec);/*Das Paritybyte wird zur Berechnung der vierten Stelle benutzt*/
		      fputc(save[1],rec);
		      fputc((save[0]^save[1]^get),rec);
	}
	break;
	case 4:	switch (i){/*4.Die vierte Datei fehlt: Es wird mithilfe von i ermittelt wo das Paritybyte der jeweiligen 4 Byte steht*/
		case 1:fputc(save[1],rec);/*Ist das Paritybyte an der ersten Stelle,so wird die vierte Stelle errechnet*/
		       fputc(get,rec);
		       fputc((save[0]^save[1]^get),rec);
		       break;
		case 2:fputc(save[0],rec);/*Ebenso an zweiter Stelle*/
		       fputc(get,rec);
		       fputc((save[0]^save[1]^get),rec);
		       break;
		case 3:fputc(save[0],rec);/*Analog an dritter Stelle, jedoch wie schon bei 2 mit anderer Reihenfolge beim Abspeichern*/
		       fputc(save[1],rec);
		       fputc((save[0]^save[1]^get),rec);
		       break;
		case 4:fputc(save[0],rec);/*Ist das Paritybyte an der vierten Stelle, so kann der Rest der Reihe nach übertragen werden da kein Informationsverlust entstanden ist*/
		       fputc(save[1],rec);
		       fputc(get,rec);
		}
	    }
	}
	else{/*Ist die Datei byteweise gesehen nicht durch 3 teilbar, so können noch letzte Bytes übrig bleiben die in diesem Teil geschrieben werden*/
	    if (i==gone || (gone<3 && (i==2 || i==4)) || (gone>2 && i>2)){
	      fputc(save[0],rec);
	      fputc(save[1],rec);
	    }
	}
    }
    else{/*Ist die Datei byteweise gesehen nicht durch 3 teilbar, so können noch letzte Bytes übrig bleiben die in diesem Teil geschrieben werden*/
      if (i==gone || (gone>1 && i>1))
	fputc(save[0],rec);
    }
    i--;
    if (i==0)/*Wenn der Zähler bei 0 angekommen ist, so soll wieder mit dem vierten Paritybyte fortgesetzt werden*/
      i=4;
  }
} 
int main (int argc, char *argv[]){
FILE *input,*out1,*out2,*out3,*out4;/*Filepointer für die zu verarbeitenden Files*/
    if (argv[1]!=NULL){
    input=fopen(argv[1],"r");/*Versuch den eingegebenen Pfad zu öffnen und die Ausgabedateien zu erstellen*/
    out1=fopen("out1.txt","w");
    out2=fopen("out2.txt","w");
    out3=fopen("out3.txt","w");
    out4=fopen("out4.txt","w");
    if (input!=NULL){/*Überprüfung der Öffnung der Eingabedatei*/
      if (out1!=NULL && out2!=NULL && out3!=NULL && out4!=NULL){/*Überprüfung der Erstellung der Ausgabedateien*/
	  readFile(input,out1,out2,out3,out4);/*Aufrufen der readFile Funktion zur Verteilung der Eingabedatei*/
	  fclose(input);/*Schließen der Files um sicherzugehen das auch alle Daten geschrieben wurden*/
	  fclose(out1);
	  fclose(out2);
	  fclose(out3);
	  fclose(out4);
	  out1=fopen("out1.txt","r");/*Erneutes Öffnen der Outputfiles, diesmal im Lesemodus zum Rekonstruieren*/
	  out2=fopen("out2.txt","r");
	  out3=fopen("out3.txt","r");
	  out4=fopen("out4.txt","r");
	  if (out1!=NULL && out2!=NULL && out3!=NULL && out4!=NULL){/*Prüfung ob das Öffnen funktioniert hat*/
	    if ((input=fopen("rec1.txt","w"))!=NULL){/*Öffnen des ersten Rekonstruktionsfiles*/
	      reconstruct(input,out1,out2,out4,3);/*Aufrufen der Rekonstruktionsfunktion wenn das Öffnen funktioniert hat*/
	      fclose(input);/*Schließen des Files um alle Daten zu schreiben*/
	    }
	    else/*Fehlermeldung falls das Öffnen der 1. Rekonstruktionsdatei fehlschlägt*/
	      printf("Rekonstruktionsfile 1 (out2,out3,out4) konnte nicht erstellt werden!");
	    if ((input=fopen("rec2.txt","w"))!=NULL){/*Öffnen des zweiten Rekonstruktionsfiles*/
	      reconstruct(input,out1,out3,out4,2);/*Aufrufen der Rekonstruktionsfunktion wenn das Öffnen funktioniert hat*/
	      fclose(input);/*Schließen des Files um alle Daten zu schreiben*/
	    }
	    else/*Fehlermeldung falls das Öffnen der 2. Rekonstruktionsdatei fehlschlägt*/
	      printf("Rekonstruktionsfile 2 (out1,out3,out4) konnte nicht erstellt werden!");
	    if ((input=fopen("rec3.txt","w"))!=NULL){/*Öffnen des dritten Rekonstruktionsfiles*/
	      reconstruct(input,out2,out3,out4,1);/*Aufrufen der Rekonstruktionsfunktion wenn das Öffnen funktioniert hat*/
	      fclose(input);/*Schließen des Files um alle Daten zu schreiben*/
	    }
	    else/*Fehlermeldung falls das Öffnen der 3. Rekonstruktionsdatei fehlschlägt*/
	      printf("Rekonstruktionsfile 3 (out1,out2,out4) konnte nicht erstellt werden!");
	    if ((input=fopen("rec4.txt","w"))!=NULL){/*Öffnen des dritten Rekonstruktionsfiles*/
	      reconstruct(input,out1,out2,out3,4);/*Aufrufen der Rekonstruktionsfunktion wenn das Öffnen funktioniert hat*/
	      fclose(input);/*Schließen des Files um alle Daten zu schreiben*/
	    }
	    else/*Fehlermeldung falls das Öffnen der 4. Rekonstruktionsdatei fehlschlägt*/
	      printf("Rekonstruktionsfile 4 (out1,out2,out3) konnte nicht erstellt werden!");
	    fclose(out1);/*Schließen der restlichen offenen Files*/
	    fclose(out2);
	    fclose(out3);
	    fclose(out4);
	    printf("Die Ausgabedateien out1-out4.txt sowie die Rekonstruktionsdateien rec1-rec4.txt wurden erfolgreich im Verzeichnis des Programmes erstellt!\n");/*Bestätigungsausgabe für den Benutzer*/
	}
	else{/*Fehlermeldung falls das öffnen der Outputfiles fehlschlägt*/
	   printf("Eines der Files zum Einlesen für die Rekonstruktionsdateien konnte nicht geöffnet werden!");
	   return 1;
	  }
	}
	else{/*Fehlermeldung falls eines der Outputfiles nicht erstellt werden konnte*/
	  printf("Eines der Outputfiles konnte nicht erstellt werden! Das Programm beendet sich...");
	  return 1;
	}
      }
      else/*Fehlermeldung falls die Eingabedatei nicht existiert*/
	printf("Die Eingabedatei existiert nicht! Das Programm beendet sich....\n");
    }
else/*Fehlermeldung wenn der Dateipfad nicht angegeben wurde*/
	printf("Zu wenige Parameter angegeben. Das Programm beendet sich...\n");
return 0;
}


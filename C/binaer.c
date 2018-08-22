/*
binaer.c 
Programm zur Umrechnung von Dezimalzahlen in Binärzahlen (32Bit)
*/ 

#include <stdio.h> 

int main (void) 
{ 
  int i,z; /*Definition der Variablen i (Zählervariable), k (Schleifenkontrollvariable) und z (Dezimalzahlenvariable) als Integer)*/
  i=0;
  z=0;
  printf ("\nUmwandlung einer Dezimalzahl in eine Binärzahl\n\n");
  do /*Die gewünschte Bitlänge wird vom Benutzer eingegeben. Die do-while Schleife prüft ob eine natürliche Zahl eingegeben wurde*/
  {
	printf("Bitte die gewünschte Länge der Binärzahl eingeben: ");
	if (scanf("%d", &i) > 0)/*Scanf gibt den Wert 0 bei fehlerhafter Eingabe zurück*/
	{
		if(i<=0)/*Ist die eingegebene Zahl i<=0 so ist i keine natürliche Zahl*/
			printf("\nEine negative Länge (%d) ist nicht definiert!\n\n",i);
	}
	else
	{
		printf("\nSie haben keine Zahl eingegeben!\n\n"); 
		scanf("%*s"); /*Ist die Eingabe fehlerhaft so wird der Eingabepuffer geleert*/
	}
  } /*Eine Fehlermeldung wird ausgegeben und es wird nach einer neuen Zahl gefragt*/
  while (i<=0);
  if (i>32)/*Ist die angegebene Bitlänge über 32Bit so soll sie auf 32Bit korrigiert werden*/
  {
  	i=32;
  	printf ("\nDie Bitlänge ist auf %d Bit begrenzt und wurde auf %d Bit angepasst!\n",i,i);
  }
  do /*Die Dezimalzahl wird vom Benutzer eingegeben. Die do-while Schleife prüft ob eine Zahl eingegeben wurde*/
  {
	printf("\nBitte die Dezimalzahl eingeben: ");
	if (scanf("%d", &z) < 1)/*Scanf gibt den Wert 0 bei fehlerhafter Eingabe zurück*/
	{
		printf("\nSie haben keine Zahl eingegeben!\n");
		scanf("%*s"); /*Ist die Eingabe fehlerhaft so wird der Eingabepuffer geleert*/
	}
  } /*Eine Fehlermeldung wird ausgegeben und es wird nach einer neuen Zahl gefragt*/
  while (z==0);
  printf ("\n%d ist in %d-Bit Binärdarstellung:\n\n",z,i);
  i--;
  while (i>=0) /*Die Binärzahl wird i-stellig nacheinander ausgegeben indem jeweils eine Stelle weiter links der Zahl darauf überprüft wird ob ihr Wert 1 ist*/
  {
 	if (z&(1<<i)) /*Ist der Wert 1 wird eine 1 ausgegeben, andernfalls eine 0*/
		printf ("1");
	else 
		printf("0");
	i--;
  }
  printf ("\n\n");
  return 0;
}

/*
caesar.c 
Programm für die Caesarverschlüsselung mit Argumenten
*/ 

#include <stdio.h>
#include <ctype.h>

int main (int argc, char *argv[]) 
{  
	char *p;
	int i;
	i=0;
	if (argc>2) /*Wenn argc größer 2 ist sind Argumente vorhanden*/
	{
		i=1;
		p=argv[2];
		if (sscanf(argv[1],"%d",&i)>0)
		{
			while (*p!='\0') /*Überprüfung der Argumenteingabe auf Buchstaben*/
			{
				if (isalpha(*p)<1) /*Ist eine Stelle der Eingabe kein Buchstabe wird i=0 gesetzt*/
				{
					i=0;
					break;
				}
				p++;
			}
		}
		else
			i=0;
	}
	if (i!=0)/*Wenn i!=0 ist und *argv[1] eine Zahl ist liegt eine gültige Eingabe vor*/
		p=argv[2];
	else
	{
		printf("\nProgramm zur Verschlüsselung von Worten in der Cäsarverschlüsselung\n\n");
		do
  		{
			printf("Bitte geben sie die Anzahl der Buchstaben ein um die verschoben werden soll:\n\n");
			if (scanf("%d", &i) < 1)/*Scanf gibt den Wert 0 bei fehlerhafter Eingabe zurück*/
			{
				printf("\nSie haben keine Zahl eingegeben!\n\n");
				scanf("%*s"); /*Ist die Eingabe fehlerhaft so wird der Eingabepuffer geleert*/
			}
  		} /*Eine Fehlermeldung wird ausgegeben und es wird nach einer neuen Zahl gefragt*/
		while (i==0);
		p=argv [0]; /*Der Pointer wird auf den ersten Wert des Arrays gesetzt*/
		do
		{
			printf("Bitte geben die das zu verschlüsselnde Wort (maximal 100 Zeichen) ein:\n\n");
			scanf("%s",*argv);
			while (*p!='\0')
			{
				if (isalpha(*p)<1) /*Hier wird überprüft ob die Eingabe ein Buchstabe ist*/
				{
					printf("\nDie Eingabe war fehlerhaft!\n\n");
					p=argv[0];
					break;
				}
				p++;
			}
		}
		while (*p!='\0');
		p=argv[0];
	}
	if (i>26) /*Wenn i>26 so ist das Alphabet bereits einmal durchlaufen und die Zahl wird angepasst*/
		i=i%26;
	if (i<-26) /*Ebenso in der Gegenrichtung*/
		i=i%-26;
	printf("\nDas verschlüsselte Wort lautet:\n\n");
	while (*p!='\0')/*Wenn an der Stelle p keine '\0' steht, so kann der Buchstabe um i verschoben werden*/
	{	
		if (*p<90) /*Unterscheidung zwischen Groß-und Kleinbuchstaben*/
		{
			*p=*p+i;
			if (*p>90)/*Wird *p dabei größer als 90 oder kleiner als 65, so wird die Zahl angepasst um zum vorderen bzw. hinteren Ende des Alphabets zu verschieben*/
				*p=*p-26;	
			if (*p<65)
				*p=*p+26;
		}
		else
		{
			*p=*p-26+i; /*Bei Kleinbuchstaben werden zuerst 26 abgezogen und danach i addiert um im Ascii-Zeichensatz zu bleiben*/
			while (*p<97) /*Danach wird solange aufaddiert bis der Buchstabe wieder ein Kleinbuchstabe ist*/
			{
				*p=*p+26;
			}
		}
		printf("%c",*p);/*Die verschobenen Buchstaben werden nacheinander ausgegeben*/
		p++;
	}
	printf("\n\n");
	return 0;
}

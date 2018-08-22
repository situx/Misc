/* ---------------------------------------------------------------------------------------------------------------
freund.c
Programm zum Berechnen von befreundeten Zahlen
------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>

int main (void)
{
	int n,p,h,t,s,k,l; /* Definition der Variablen n,p,h,t,s,k und l als Integer*/
	n=0;
	p=0;
	h=1;
	do /*Die erste Zahl des Intervalls wird vom Benutzer eingegeben. Die do-while Schleife prüft ob eine natürliche Zahl eingegeben wurde*/
	{
	printf("\nBitte die erste natürliche Zahl eingeben: ");
	if (scanf("%d", &n) > 0)/*Scanf gibt den Wert 0 bei fehlerhafter Eingabe zurück*/
	{
		if(n<=0)/*Ist die eingegebene Zahl n<=0 so ist n keine natürliche Zahl*/
		printf("\n%d ist keine natürliche Zahl!\n",n);
	}
	else
	{
		printf("\nSie haben keine Zahl eingegeben!\n"); /*Ist die Eingabe fehlerhaft so wird der Eingabepuffer geleert*/
		scanf("%*s");
	}
	} /*Eine Fehlermeldung wird ausgegeben und es wird nach einer neuen Zahl gefragt*/
	while (n<=0);
	do /*Die zweite Zahl des Intervalls wird vom Benutzer eingegeben. Die do-while Schleife prüft ob eine natürliche Zahl eingegeben wurde*/
	{
	printf("\nBitte die zweite natürliche Zahl eingeben: ");
	if (scanf("%d", &p) > 0)/*Scanf gibt den Wert 0 bei fehlerhafter Eingabe zurück*/
	{
		if(p<=0)/*Ist die eingegebene Zahl p<=0 so ist n keine natürliche Zahl*/
		printf("\n%d ist keine natürliche Zahl!\n",p);
	}
	else
	{
		printf("\nSie haben keine Zahl eingegeben!\n");
		scanf("%*s");/*Ist die Eingabe fehlerhaft so wird der Eingabepuffer geleert*/
	}
	}
	while (p<=0);
	if (n<p) /*Wenn n kleiner als p ist, werden die Werte von p und n mithilfe von h vertauscht*/
	{ 
		h=n;
		n=p;
		p=h;
	}
	while (n>p && n>283) /*Solange n größer als p und größer als 283 ist wird für jede Zahl das Teilerverhältnis bestimmt*/
		{
		k=0;
		t=n-1; /*t als Variable für den Teiler wird n-1 gesetzt*/
		while (t>0) /*Solange t>0 soll auf Teiler geprüft werden*/
		{
			if (n%t==0) /*Wenn n%t == 0 so ist die Zahl teilbar und der Teiler wird zur Variablen s hinzuaddiert*/
			k=k+t; 
			t--; /*t wird um 1 erniedrigt*/
		}
		if (k==n || l==n) /*Wenn k=n ist, so ist die Zahl vollkommen und wird nicht ausgegeben, ist l=n so wurde die Zahl bereits ausgegeben*/
			s=0;
		else 
		{
			s=0;
			t=k-1;
			while (t>0) /*Solange t>0 soll auf Teiler geprüft werden*/
			{
				if (k%t==0) /*Wenn k%t == 0 so ist die Zahl teilbar und der Teiler wird zur Variablen s hinzuaddiert*/
					s=s+t; 
			t--; /*t wird um 1 erniedrigt*/
			}
		}
		if (s==n) /*Ist das Teilerverhältnis s(k) gleich der Ausgangszahl n so wird die Zahl ausgegeben und die Hilfsvariable h gleich 0 gesetzt*/
		{
			printf("\n%d %d\n",s,k);
			h=0;
			l=k; /*l wird der Wert von k zugewiesen um Doubletten bei der Ausgabe zu vermeiden*/
		}
		n--;
	}
	if (h!=0) /*Demnach gibt es wenn h ungleich 0 ist keine befreundeten Zahlen*/
		printf("\nKeine befreundeten Zahlen gefunden!\n\n");
	return 0;
}

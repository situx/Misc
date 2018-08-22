/* ---------------------------------------------------------------------------------------------------------------
dav.c
Programm zur Überprüfung natürlicher Zahlen auf Abundanz, Defizienz und Vollkommenheit
*/
#include <stdio.h>
int n,s;
int check (s)
	{
		int t; /* Definition der Variablen n,t und s als Integer*/
		s=0;
		t=n-1; /*t als Variable für den Teiler wird n-1 gesetzt*/
		while (t>0) /*Solange t>0 soll auf Teiler geprüft werden*/
			{
			if (n%t==0) /*Wenn n%t == 0 so ist die Zahl teilbar und der Teiler wird zur Variablen s hinzuaddiert*/
			s=s+t; 
			t--; /*t wird um 1 erniedrigt*/
			}
	}
int vollkommen (int n)
{
int check;
if (n==s) /*Wenn n=s so ist die Zahl vollkommen und der Wert 1 wird ausgegeben*/
return=1;
else
return=0;
}
int defizient (void) /*Prüfung auf Defizienz*/
{
int check;
if (n>s) /*Wenn n>s so ist die Zahl defizient und der Wert 1 wird ausgegeben*/
return=1;
else
return=0;
}
int abundant (n,s)
{
int check;
if (n<s) /*Wenn n<s so ist die Zahl abundant und der Wert 1 wird ausgegeben*/
return=1;
else
return=0;}
int main (void)
{
int vollkommen;
int defizient;
int abundant;
}

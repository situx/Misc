/*
palindrom.c 
Programm zur Prüfung auf Palindrome
*/ 

#include <stdio.h> 

int main(void) 
{  
	char c []="trug tim eine so helle hose nie mit gurt?";
	int l,i,f,g,j;
	printf("Prüfung auf Palindrome! Für andere Sätze bitte das Array c editieren!");
	i=0;
	f=1;
	g=-1;
	j=0;
	l=sizeof(c)-2;
	while (i<=l)
	{
		if (c [i] >65 && c [i]< 123)
			g++;
		i++;
	}
	char b [g];
	i=0;
	while (i<=l)
	{
		if (c [i] >65 && c [i] < 123)
		{
			b [j]=c [i];
			j++;
		}
		i++;
	}
	i=0;
	while (g>0)
	{
		if (b[g]!=b[i])
			f=0;
		g--;
		i++;
	}
	if (f==0)
		printf("\n\n'%s' ist kein Palindrom!\n\n",c);
	else
		printf("\n\n'%s' ist ein Palindrom!\n\n",c);
	return 0;
}




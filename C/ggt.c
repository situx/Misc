#include <stdio.h>
#include <stdlib.h>

unsigned long ggt(unsigned long a, unsigned long b) {
   if(a==b)/*Sind beide Zahlen gleich ist die Zahl der ggt und wird zurückgegeben*/
      return a;
   else if(a < b)/*Ist a<b so wird die Funktion erneut mit einem um a erniedrigten b aufgerufen*/
       return ggt(a, b-a);
   else
       return ggt(a-b, b);/*Andernfalls wird das a solange erniedrigt bis es gleich b ist*/
}

int main(void) {
unsigned long a, b;
int ende;
printf("Programm zur Berechnung des größten gemeinsamen Teilers\n");
do{
printf("1: GGT bestimmen\n2: Programm beenden\n");
scanf("%d",&ende);
if(ende!=2){
printf("Zahl 1: ");
scanf("%lu",&a);
printf("Zahl 2: ");
scanf("%lu",&b);
printf("Der ggT von %lu und %lu ist %lu\n", a, b, ggt(a,b));
}
}while(ende!=2);
return 0;
}


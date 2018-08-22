#include <stdio.h>
#include <stdlib.h>

void prim(unsigned int grenze,int ausgabe){
int check[grenze],k=0;
unsigned int j=0,i,output=0;
for(i=0;i<grenze;i++){ //Zahlen in das Array eintragen, Gerade Zahlen werden sofort mit "false gekennzeichnet
  if((i%2!=0 || i==2) && i!=1)
    check[i]=1;
  else
    check[i]=0;
}
i=2;
while (i*i <= grenze){
  if(check[i]==1){//Wenn an der Stelle i eine Primzahl steht setze alle Vielfache davon auf "false"
    for(j=i*i;j<grenze;j+=i){
      check[j] = 0;
    }
  }
  i++;
}
j=0;
for(i=0;i<grenze;i++){//Filtere alle True-Werte aus dem Array und gebe die Zahlen aus
  if(check[i]==1){
    if(ausgabe==-1 || k<ausgabe){
      printf("%d,",i);
      output++;
    }
    k++;
    if(j++%20==0 && (ausgabe==-1 || k<ausgabe))
      printf("\n");
  }
}
if(ausgabe==-1)
  printf("\n %d Primzahlen",k);
else
  printf("\nAngezeigt: %d von %d Primzahlen\n",output,k);
}

int main(int argc,char *argv[]){
  unsigned int grenze=2;
  int ausgabe=-1;
  if(argc<2){
    printf("Sie haben zu wenig Argumente angegeben!\nSyntax: %s 'Obere Prüfgrenze','Ausgabenbegrenzung'\n",argv[0]);
    exit(1);
  }
  if(argc>2){
    ausgabe=atoi(argv[2]);
  }
  grenze=atoi(argv[1]);
  if(grenze<2)
    printf("Ihre Grenze liegt nicht im Bereich der positiven Primzahlen oder stellte keine gültige Zahl dar");
  prim(grenze,ausgabe);
  return 0;
}

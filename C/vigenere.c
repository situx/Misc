#include <stdio.h>
#include <string.h>
char* decrypt(char *result, char* key, int deen){
int i=0,j=0;
int ln=strlen(key),ln2=strlen(result);
while(i<ln2){
if(key[i-j]=='\n')
  j+=ln;
if(deen)
	result[i]-=(key[i-j]-65)%26;
else
	result[i]+=(key[i-j]-65)%26;
if(result[i]>'Z')
	result[i]-=26;
else if(result[i]<'A')
	result[i]+=26;
i++;
}
return result;
}

int main(int argc, char *argv[]){
char str[100],str2[100],end;
int choose;
do{
	printf("1: Verschlüsseln\n2: Entschlüsseln\n");
	scanf("%d",&choose);
	switch(choose){
	case 1: printf("Bitte geben Sie das zu verschlüsselnde Wort ein:\n");
		scanf("%s",str);
		printf("Bitte geben Sie das zugehörige Schlüsselwort ein:\n");
		scanf("%s",str2);
		printf("Das verschlüsselte Wort ist %s\n",decrypt(str,str2,0));break;
	case 2: printf("Bitte geben Sie das zu entschlüsselnde Wort ein:\n");
		scanf("%s",str);
		printf("Bitte geben Sie das zugehörige Schlüsselwort ein:\n");
		scanf("%s",str2);
		printf("Das gesuchte Wort war %s\n",decrypt(str,str2,1));break;
	}
printf("Programm beenden? (y/n)\n");
scanf("%s",&end);
}while(end!='y');
return 0;
}

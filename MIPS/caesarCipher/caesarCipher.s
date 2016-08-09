.data
string:   .space 128
verschiebung: .space 4
eingabe:  .asciiz "Bitte geben sie den zu verschluesselnden String (max 128 Zeichen) ein:\n"
eingabe2: .asciiz "Bitte geben sie die Verschiebung ein:\n"
errors:   .asciiz "Die Eingabe enthielt ungueltige Zeichen!\n"
message:  .asciiz "Nun wird der verschluesselte String wieder entschluesselt:\n"
.text
main:	li $16,10		#Speichern des letzten Zeichens des Strings in Register 16
	li $17,0		#Der Zähler für die Anzeige ob verschlüsselt oder entschlüsselt wird bekommt den Wert 0
	li $18,32		#Speichern des Leerzeichencharakters in Register 18
	li $19,0
	la $4,eingabe		#Die Adresse für den String "Eingabe" wird in Register 4 geladen
	li $2,4			#Syscallaufrufnummer 4 (print string) wird in Register 2 geladen
	syscall			#Aufruf des Syscalls
	li $2, 8		#Einlesen des Strings Ã¼ber Syscallfunktion 8
	la $4, string		#Adresse an die der String geschrieben werden soll
	li $5, 128		#Festlegung der PufferlÃ¤nge des Strings (maximale Eingabe)
	syscall			#Aufruf des Syscalls
	la $4,eingabe2		#Die Adresse für den String "Eingabe2" wird in Register 4 geladen
	li $2,4			#Syscallaufrufnummer 4 (print string) wird in Register 2 geladen
	syscall			#Aufruf des Syscalls
	li $2,5			#Syscallnummer 5 wird in Register 2 geladen (read Integer)
	syscall			#Festlegung der Verschiebung der Asciiwerte
	li $8,0			#Register 8 wird auf null gesetzt
	add $8,$8,$2		#Kopieren des Verschiebungswertes
test:	slti $11,$2,26		#Wenn der Verschiebungswert kleiner als 26 ist gehe zur nÃ¤chsten PrÃ¼fung
	bne $0,$11,check2
	bltz $8,endtest		
	addi $8,-26		#Und ziehe solange 26 vom Verschiebungswert ab bis $8<$0
	j test
check2:	slti $11,$2,-26		#2.Testfall: Der Verschiebungswert ist kleiner als -26
	beq $0,$11,endtest
test2:	bgtz $8,begin	 
	addi $8,26		#Addiere solange 26 bis $8>$0
	j test2
endtest:bgtz $8,begin		#Wenn der Verschiebungswert kleiner als 26 ist gehe zur nÃ¤chsten PrÃ¼fung
	addi $8,26		#3.Fall:Verschiebungswert kleiner als 0 und grÃ¶ÃŸer als -26: Ziehe V-Wert von 26 ab
begin:  add $19,$0,$8
endtest2:la $12,string
loop:	lb $9,($12)		#laden des ersten Zeichens des Strings in ein Speicherregister
	beq $16,$9,ausgabe	#Solange bis das eingelesene Zeichen '\n' ist
	beq $18,$9,leer
	slti $10,$9,65		#PrÃ¼fung ob das eingelesene Zeichen unter dem zulÃ¤ssigen Asciibereich liegt
	bne $0,$10,error
	slti $10,$9,123		#PrÃ¼fung ob das eingelesene Zeichen Ã¼ber dem zulÃ¤ssigen Asciibereich liegt
	beq $0,$10,error
	slti $10,$9,91		#PrÃ¼fung ob das eingegebene Zeichen ein GroÃŸbuchstabe ist
	beq $10,$0,else 	
	add $9,$9,$8		#erhÃ¶hen um die Zahl des SchlÃ¼ssels
	slti $10,$9,91		#PrÃ¼fung ob die obere Asciigrenze Ã¼berschritten wurde
	bne $10,$0,store
	addi $9,-26
	j store			#Evtl Korrektur des Asciiwertes durch Abzug von 26
else:	slti $10,$9,97		#PrÃ¼fung ob das eingelesene Zeichen im zulÃ¤ssigen Asciibereich liegt
	bne $0,$10,error
	add $9,$9,$8		#erhÃ¶hen um die Anzahl des SchlÃ¼ssels
	slti $10,$9,123		#PrÃ¼fung ob die obere Asciigrenze Ã¼berschritten wurde
	bne $10,$0,store	#Entweder Sprung zum Speichern des Wertes
	addi $9,-26		#Oder Korrektur des Asciiwertes durch Abzug von 26
	j store
leer:   add $9,$9,$19
store:	sb $9,($12)		#speichern des Asciiwertes im Databereich
	addi $12,1		#ErhÃ¶hen des Pointers um 1
	j loop			#Sprung zur Schleifenbedingung
ausgabe:li $2,4
	la $4, string		#Ausgabe des verÃ¤nderten Buchstabens Ã¼ber einen Syscall im Terminal
	syscall			#Aufruf des Syscalls
	bne $0,$17,ende		#Wenn der ZÃ¤hler in Register 17 auf 0 steht, soll noch die RÃ¼ckÃ¼bersetzung durchgefÃ¼hrt werden
	addi $17,1		#ErhÃ¶hen des ZÃ¤hlers fÃ¼r den Status (Ver-oder EntschlÃ¼sseln)
	add $18,$18,$19		#Erhöhen von Register 18 um den verschlüsselten Charakter "Leerzeichen" wieder zu entschlüsseln
	li $13,0
	sub $19,$13,$8
	li $13,26
	sub $8,$13,$8		#Bildung der Gegenzahl des VerschlÃ¼sselungswertes zum EntschlÃ¼sseln
	li $2,4
	la $4, message		#Ausgabe des verÃ¤nderten Buchstabens Ã¼ber einen Syscall im Terminal
	syscall	
	j endtest2		#Rücksprung für die Entschlüsselung
ende:	jr $31			#Programmende
error:	li $2,4
	la $4, errors		#Ausgabe einer Errormessage im Terminal
	syscall			#Aufruf des Syscalls
	j main			#Neustart des Einlesens

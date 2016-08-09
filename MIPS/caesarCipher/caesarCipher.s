#Timo Homburg Mn:458502      1. Hausaufgabe Rechnerorganisation: Caesarverschl�sselung
.data
string:   .space 128
verschiebung: .space 4
eingabe:  .asciiz "Bitte geben sie den zu verschluesselnden String (max 128 Zeichen) ein:\n"
eingabe2: .asciiz "Bitte geben sie die Verschiebung ein:\n"
errors:   .asciiz "Die Eingabe enthielt ungueltige Zeichen!\n"
message:  .asciiz "Nun wird der verschluesselte String wieder entschluesselt:\n"
.text
main:	li $16,10		#Speichern des letzten Zeichens des Strings in Register 16
	li $17,0		#Der Z�hler f�r die Anzeige ob verschl�sselt oder entschl�sselt wird bekommt den Wert 0
	li $18,32		#Speichern des Leerzeichencharakters in Register 18
	li $19,0
	la $4,eingabe		#Die Adresse f�r den String "Eingabe" wird in Register 4 geladen
	li $2,4			#Syscallaufrufnummer 4 (print string) wird in Register 2 geladen
	syscall			#Aufruf des Syscalls
	li $2, 8		#Einlesen des Strings über Syscallfunktion 8
	la $4, string		#Adresse an die der String geschrieben werden soll
	li $5, 128		#Festlegung der Pufferlänge des Strings (maximale Eingabe)
	syscall			#Aufruf des Syscalls
	la $4,eingabe2		#Die Adresse f�r den String "Eingabe2" wird in Register 4 geladen
	li $2,4			#Syscallaufrufnummer 4 (print string) wird in Register 2 geladen
	syscall			#Aufruf des Syscalls
	li $2,5			#Syscallnummer 5 wird in Register 2 geladen (read Integer)
	syscall			#Festlegung der Verschiebung der Asciiwerte
	li $8,0			#Register 8 wird auf null gesetzt
	add $8,$8,$2		#Kopieren des Verschiebungswertes
test:	slti $11,$2,26		#Wenn der Verschiebungswert kleiner als 26 ist gehe zur nächsten Prüfung
	bne $0,$11,check2
	bltz $8,endtest		
	addi $8,-26		#Und ziehe solange 26 vom Verschiebungswert ab bis $8<$0
	j test
check2:	slti $11,$2,-26		#2.Testfall: Der Verschiebungswert ist kleiner als -26
	beq $0,$11,endtest
test2:	bgtz $8,begin	 
	addi $8,26		#Addiere solange 26 bis $8>$0
	j test2
endtest:bgtz $8,begin		#Wenn der Verschiebungswert kleiner als 26 ist gehe zur nächsten Prüfung
	addi $8,26		#3.Fall:Verschiebungswert kleiner als 0 und größer als -26: Ziehe V-Wert von 26 ab
begin:  add $19,$0,$8
endtest2:la $12,string
loop:	lb $9,($12)		#laden des ersten Zeichens des Strings in ein Speicherregister
	beq $16,$9,ausgabe	#Solange bis das eingelesene Zeichen '\n' ist
	beq $18,$9,leer
	slti $10,$9,65		#Prüfung ob das eingelesene Zeichen unter dem zulässigen Asciibereich liegt
	bne $0,$10,error
	slti $10,$9,123		#Prüfung ob das eingelesene Zeichen über dem zulässigen Asciibereich liegt
	beq $0,$10,error
	slti $10,$9,91		#Prüfung ob das eingegebene Zeichen ein Großbuchstabe ist
	beq $10,$0,else 	
	add $9,$9,$8		#erhöhen um die Zahl des Schlüssels
	slti $10,$9,91		#Prüfung ob die obere Asciigrenze überschritten wurde
	bne $10,$0,store
	addi $9,-26
	j store			#Evtl Korrektur des Asciiwertes durch Abzug von 26
else:	slti $10,$9,97		#Prüfung ob das eingelesene Zeichen im zulässigen Asciibereich liegt
	bne $0,$10,error
	add $9,$9,$8		#erhöhen um die Anzahl des Schlüssels
	slti $10,$9,123		#Prüfung ob die obere Asciigrenze überschritten wurde
	bne $10,$0,store	#Entweder Sprung zum Speichern des Wertes
	addi $9,-26		#Oder Korrektur des Asciiwertes durch Abzug von 26
	j store
leer:   add $9,$9,$19
store:	sb $9,($12)		#speichern des Asciiwertes im Databereich
	addi $12,1		#Erhöhen des Pointers um 1
	j loop			#Sprung zur Schleifenbedingung
ausgabe:li $2,4
	la $4, string		#Ausgabe des veränderten Buchstabens über einen Syscall im Terminal
	syscall			#Aufruf des Syscalls
	bne $0,$17,ende		#Wenn der Zähler in Register 17 auf 0 steht, soll noch die Rückübersetzung durchgeführt werden
	addi $17,1		#Erhöhen des Zählers für den Status (Ver-oder Entschlüsseln)
	add $18,$18,$19		#Erh�hen von Register 18 um den verschl�sselten Charakter "Leerzeichen" wieder zu entschl�sseln
	li $13,0
	sub $19,$13,$8
	li $13,26
	sub $8,$13,$8		#Bildung der Gegenzahl des Verschlüsselungswertes zum Entschlüsseln
	li $2,4
	la $4, message		#Ausgabe des veränderten Buchstabens über einen Syscall im Terminal
	syscall	
	j endtest2		#R�cksprung f�r die Entschl�sselung
ende:	jr $31			#Programmende
error:	li $2,4
	la $4, errors		#Ausgabe einer Errormessage im Terminal
	syscall			#Aufruf des Syscalls
	j main			#Neustart des Einlesens

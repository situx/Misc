public class Rucksack {

	// Das maximale Gewicht und der maximale Nutzwert der
	// im Rucksack zu verstauenden Gegenstaende
	static final int MAX_GEWICHT = 10;
	static final int MAX_NUTZEN = 10;

	// die zur Auswahl stehenden Objekte werden in einem
	// statischem Array auswahlObjekte[anzahlObjekte][2] gespeichert,
	// wobei [x][0] das Gewicht und [x][1] der Wert von 
	// Objekt x ist. Die Anzahl der Objektwerte kann als
	// Kommandozeilenparameter uebergeben werden und hat den
	// Default-Wert 10.
	static int anzahlObjekte = 10;
	static int[][] auswahlObjekte = null; 

	// was passt in einen Rucksack? spaeter initialisiert als
	// anzahlObjekte * MAX_GEWICHT * 0.25 (durchschnittliches Gewicht 
	// der Objekte ist MAX_GEWICHT * 0.5, so wird sichergestellt, dass
	// als Erwartungswert die Haelfte der Gegenstaende in den
	// Rucksack passen)
	static int kapazitaet;
	// Welche der Objekte sollen in einen konkreten Rucksack? 
	// (Variable ist nicht statisch!!!) Erzeugt mit Groesse:
	// auswahl[anzahlObjekte], auswahl[x] == true wenn Objekt x 
	// im Rucksack ist
	boolean[] auswahl = null;

	Rucksack () {
		auswahl = new boolean[anzahlObjekte];
		for (int i = 0; i < auswahl.length; i ++)
			auswahl[i] = false;
	}

	Rucksack (Rucksack r) {
		auswahl = new boolean[anzahlObjekte];
		for (int i = 0; i < auswahl.length; i ++)
			auswahl[i] = r.auswahl[i];
	}

	int gewicht () {
		int g = 0;
		for (int i=0; i < auswahl.length; i ++)
			if (auswahl[i] == true)
				g = g + auswahlObjekte[i][0];
		return g;
	}

	int nutzen () {
		int n = 0;
		for (int i=0; i < auswahl.length; i ++)
			if (auswahl[i] == true)
				n = n + auswahlObjekte[i][1];
		return n;
	}

	
	public String toString() {
		String r = "|";
		for (int i=0; i < auswahl.length; i++) 
			r = r + (auswahl[i] ? "1" : "0") + "|";	
		r = r + " Gewicht: " + gewicht()
			+ " Nutzen: " + nutzen();
		return r;
	}

	// statische Hilfsmethoden

   	static int[][] erzeugeObjekte() {
		java.util.Random ra = new java.util.Random();
		int[][] r = new int[anzahlObjekte][2];
		for (int i=0; i < r.length; i++) {
			r[i][0]= ra.nextInt(MAX_GEWICHT)+1;
			r[i][1]= ra.nextInt(MAX_NUTZEN)+1;
		}
	   	return r;
   	}

	static String objekteToString(int[][] a) {
	   
		String r = "Auswahlobjekte: ";
		for (int i=0; i < a.length; i++) 
			r = r + "(" + a[i][0] + "," + a[i][1] +")";
		return r;
	}

	// erster Greedy-Ansatz: pack immer das leichteste Teil in den Rucksack 

	static Rucksack packeGierigNachGewicht() {
		int i=0,j=0,k=0;
		Rucksack r = new Rucksack();
		System.out.println("Packe immer den leichtesten Gegenstand ein");
		while (k<kapazitaet)
		{
			j=0;
			i=0;
			while (r.auswahl[j]==true)
			{
				j++;
			}
			while (i<10)
			{
				if (auswahlObjekte[i][0]<=auswahlObjekte[j][0] && r.auswahl[i]==false)
					j=i;
				i++;
			}
		if  ((k+auswahlObjekte[j][0])<=kapazitaet)
		{
			r.auswahl[j]=true;
			k+=auswahlObjekte[j][0];
		}
		else
			k=kapazitaet;	
		}
		return r;
	}

	// zweiter Greedy-Ansatz: pack immer das nuetzlichste Objekt in den Rucksack

	static Rucksack packeGierigNachNutzen() {
		int i=0,j=0,k=0;
		Rucksack r = new Rucksack();
		System.out.println("Packe immer den nuetzlichsten Gegenstand ein");
		while (k<kapazitaet)
		{		
			j=0;
			i=0;
			while (r.auswahl[j]==true)
			{
				j++;
			}
			while (i<10)
			{
				if (auswahlObjekte[i][1]>=auswahlObjekte[j][1] && r.auswahl[i]==false)
					j=i;
				i++;
			}
			if  ((k+auswahlObjekte[j][0])<=kapazitaet)
			{
				r.auswahl[j]=true;
				k+=auswahlObjekte[j][0];
			}
			else
				k=kapazitaet;	
		}
		return r;
	}

//	 finden der optimalen Loesung mit Backtracking

	static Rucksack packeOptimalmitBacktracking() {
		return rucksackRekursiv(0,new Rucksack());
	}
	
	static Rucksack packedynamischmitBacktracking() {
		return rucksackdynamisch(0,new Rucksack(),new Rucksack[kapazitaet][anzahlObjekte]);
	}
	// finden der optimalen Loesung mit Backtracking
        
	static Rucksack rucksackRekursiv(int i,Rucksack r)
	{
		if (i==auswahlObjekte.length)
			return r;
		Rucksack r1 = new Rucksack(r);		// teste alle von r abgeleiteten Rucksaecke r1, in 
		r1 = rucksackRekursiv(i+1,r1);		// denen Objekt i nicht drin ist
		if (r.gewicht()+auswahlObjekte[i][0]<=kapazitaet)
		{	
			Rucksack r2 = new Rucksack(r);	// wenn Objekt i noch in r passt, teste auch diese
			r2.auswahl[i]=true;			 	// abgeleiteten Rucksaecke r2
			r2=rucksackRekursiv(i+1,r2);
			if (r2.nutzen()>r1.nutzen()) 	// sollte das Ergebnis besser sein als bei r1,
				return r2;					// gib diesen Rucksack zurueck
		}
		return r1;							// in allen anderen Faellen basiert das bessere Ergebnis
		}									// auf r1

	static Rucksack rucksackdynamisch(int i,Rucksack r, Rucksack [][]Ergebnisse)
	{
		int gewicht = r.gewicht(),j=i;
		if (i==auswahlObjekte.length)
			return r;
		if (Ergebnisse[gewicht][i] != null) //Liegt bereits ein berechnetes Zwischenergebnis vor
		{
			while (j<anzahlObjekte)//so können die restlichen Ergebnisse anhand der folgenden Schleife gewonnen werden
			{
				r.auswahl[j]=Ergebnisse[gewicht][i].auswahl[j];
				j++;
			}
			return r;
		}
		Rucksack r1 = new Rucksack(r);		// teste alle von r abgeleiteten Rucksaecke r1, in 
		r1 = rucksackdynamisch(i+1,r1,Ergebnisse);		// denen Objekt i nicht drin ist
		if (r.gewicht()+auswahlObjekte[i][0]<=kapazitaet)
		{	
			Rucksack r2 = new Rucksack(r);	// wenn Objekt i noch in r passt, teste auch diese
			r2.auswahl[i]=true;			 	// abgeleiteten Rucksaecke r2
			r2=rucksackdynamisch(i+1,r2,Ergebnisse);
			if (r2.nutzen()>r1.nutzen()) 	// sollte das Ergebnis besser sein als bei r1,
				return r2;					// gib diesen Rucksack zurueck
		}
		Ergebnisse[gewicht][i]=r1;			// hier werden die Zwischenergebnisse für r1 gespeichert
		return r1;							// in allen anderen Faellen basiert das bessere Ergebnis
		}									// auf r1










	// finden einer optimalen Loesung mit dynamischer Programmierung: 
	// dies ist (im Gegensatz zur bereits in der Vorlesung vorgestellten 
	// iterativen Loesung) eine Abwandlung der Backtracking-Loesung, bei 
	// der die Rekursion abgebrochen wird, wenn bereits ein berechnetes
	// Zwischenergebnis vorliegt
	


	
	
	
	public static void main (String args[]) {
		if (args.length == 1)
			anzahlObjekte = Integer.parseInt(args[0]);
		kapazitaet = (int)(anzahlObjekte * MAX_GEWICHT / 4);

		auswahlObjekte = erzeugeObjekte();
		System.out.println(objekteToString(auswahlObjekte));
		System.out.println("Kapazitaet: " + kapazitaet);

		Rucksack r1 = packeGierigNachGewicht();
		System.out.println("Greedy nach Gewicht: " + r1 );

		Rucksack r2 = packeGierigNachNutzen();
		System.out.println("Greedy nach Nutzen: " + r2 );

		Rucksack r3 = packeOptimalmitBacktracking();
		System.out.println("Optimal mit Backtracking: " + r3 );
		
		Rucksack r4 = packeOptimalmitBacktracking();
		System.out.println("Optimal und dynamisch mit Backtracking: " + r4 );


	}
}


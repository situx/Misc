public class BubbleSort {
	public static void Suche (int[] Array,int first,int last,int mitte,int suche)
	{
		if (Array[mitte]==suche)
			System.out.println("Das gesuchte Objekt befindet sich an Position: "+(mitte+1));
		else if(mitte==first || mitte==last)
			System.out.println("Das gesuchte Objekt existiert nicht im Array");
		else if (suche<Array[mitte]){
			last=mitte;
			mitte=last/2;
			Suche(Array,first,last,mitte,suche);
		}
		else {
			first=mitte;
			mitte+=(last-mitte)/2;
			Suche(Array,first,last,mitte,suche);
		}	
	}
	 
	public static void bubble(int[] Array, int n)
	{
		int i=1, k,j=0,l=0;
		boolean tauschen;
		System.out.println(ArrayHlp.toString(Array));
		System.out.println("Nun wird die Liste geordnet:");
		do {
			i=0;
			tauschen = false;
			while (i < (n-1)) {
				if (Array[i] > Array[i + 1]) {
					k = Array[i];
					Array[i] = Array[i + 1];
					Array[i + 1] = k;
					tauschen = true;
					j++;
				}
				l++;
				i++;
			}
			n--;
		} 
		while (tauschen == true && n >= 1);
		System.out.println(ArrayHlp.toString(Array));
		System.out.println("Vertauschungen: "+j+"\nAnzahl der Vergleiche: "+l);
	}
	public static void main(String[] args) {
		int[]Array=ArrayHlp.initArray();
		int[]test1={1,2,3,4,5,6,7};
		int[]test2={6,5,4,3,2,1};
		int[]test3={1,2,3,6,5,4};
		int n=Array.length;
		bubble(Array,n);
		n=test1.length;
		bubble(test1,n);
		n=test2.length;
		bubble(test2,n);
		n=test3.length;
		bubble(test3,n);
		Suche(Array,0,(Array.length),(Array.length/2),10);
		Suche(test1,0,(test1.length),(test1.length/2),3);
	}
}

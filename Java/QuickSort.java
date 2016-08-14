
public class QuickSort {
	public static void Quick(int[] Array,int links,int rechts){
		int teiler;
		if (links<rechts)//solange noch zu sortierende Elemente vorhanden sind tue...
		{
			teiler=teile(Array,links,rechts);//Ermittlung des Pivotelements (dieses ist sortiert!)
			Quick(Array,links,teiler-1);//Aufruf der ersten Liste zur weiteren Sortierung
			Quick(Array,teiler+1,rechts);//Aurruf der zweiten Liste zur weiteren Sortierung 
		}
	}
	public static int teile(int[] Array,int links,int rechts)
	{
		int i,j,pivot,tmp;
		i=links;									//i wird auf die linke Position gesetzt
		j=rechts-1;									// j wird auf die rechte Position gesetzt
		pivot=Array[rechts];						//das Pivotelement nimmt den Wert des rechten Elementes an
		do{
			while (Array[i]<=pivot && i<rechts)		//Suche nach einem Element>= Pivot (von links)
			{
				i++;
			}
			while (Array[j]>=pivot && j>links)		// Suche nach einem Element<=pivot (von rechts)
			{
				j--;
			}
			if (i<j)								//Wenn i kleiner als j ist erfolgt ein Tausch
			{										//(denn das Element steht an der falschen Stelle)
				tmp=Array[i];
				Array[i]=Array[j];
				Array[j]=tmp;
			}
		}
		while (i<j);								//Wird nicht mehr getauscht ist die Position von Pivot bekannt
		if (Array[i]>pivot)
		{
			tmp=Array[i];
			Array[i]=Array[rechts];
			Array[rechts]=tmp;
		}
		return i;//Die Position des Pivotelements wird zur weiteren Verwendung zurckgegeben
	}
	public static void main(String[] args) {
		int Array[]=ArrayHelper.initArray();
		System.out.println(ArrayHelper.toString(Array));
		System.out.println("Nun wird die Liste geordnet:");
		Quick(Array,0,Array.length-1);
		System.out.println(ArrayHelper.toString(Array));
	}
}

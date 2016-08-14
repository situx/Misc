
public class HeapSort {
	public static void generateMaxHeap(int[] Array) {/*Erstelle einen MaxHeap Baum aus dem Array*/
		int i=Array.length-1;
		while(i>=0) {
			einsickern(Array,i,Array.length);//Aufruf der Funktion zum Einsickern
			i--;
		}
	}
	 
	public static void einsickern(int[] Array, int i,int n) {
		while(i<=(n/2)-1) {//Da die zweite Hälfte des Arrays nur als Blattknoten vorkommen, muss sie nicht in den Heap überführt werden
			int kindIndex = ((i+1)*2)-1; // berechnet den Index des linken Kindes des Binärbaumes
	 
			//bestimme ob ein rechtes Kind existiert
			if(kindIndex+1 < n) {
				//wenn rechtes kind existiert prüfe ob das rechte Kind größer ist als das linke Kind
				if(Array[kindIndex] < Array[kindIndex+1]) {
					kindIndex++; // wenn rechtes kind größer ist nehme das rechte Kind
				}
			}
	 
			//teste ob element sinken muss 
			if(Array[i] < Array[kindIndex]) {
				int temp = Array[i];/*Vertauschen der beiden Arraywerte*/
				Array[i] = Array[kindIndex];
				Array[kindIndex] = temp; //element versenken
				i = kindIndex; // wiederhole den vorgang mit der neuen position
			} else break;
		}
	} 
	
 public static void main(String[] args) {
	 int[]Array=ArrayHelper.initArray();
	 int i=Array.length-1;
	 System.out.println("Generiertes Array: "+ArrayHelper.toString(Array));
	 generateMaxHeap(Array);
	 System.out.println("Array als Max-Heap: "+ArrayHelper.toString(Array));
	 while(i>=0) {
		int temp = Array[i];/*Vertauschen der beiden Arraywerte*/
		Array[i] = Array[0];
		Array[0] = temp;
		einsickern(Array,0,i);
		System.out.println("Sortieren: "+ArrayHelper.toString(Array));
		i--;
	 } 
	 System.out.println("Sortiert mit HeapSort: "+ArrayHelper.toString(Array));
   }
}

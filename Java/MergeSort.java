
public class MergeSort {
public static void MSort(int[] Array,int half){
	int[]links;
	int[]rechts=Array;
	int i=0;
	if (Array.length<=1)
		System.out.println(ArrayHelper.toString(Array));
	else
		while (i<Array.length/2)
		{
			links[i]=Array[i];
		}
		while (i<Array.length)
			rechts[i]=Array[i];
		merge(MSort(links,links.length),MSort(rechts,links.length));
		
		public static int[] merge (int[]links,int[]rechts)
		{
			int[]merged;
			int i=0,status=0;
			while (i<links.length && j<rechts.length)
			{
				if (links[i]<=rechts[i]){
					merged[status]=links[i];
					i++;}
				else{
					merged[status]=rechts[j];
					j++;
				}
				status++;
			while (i<links.length)
			{
				merged[status]=links[i];
				i++;
			}
			while (j<links.length)
			{
				merged[status]=rechts[j];
				j++;
			}
		}
			return Array;
}
public static void main(String[] args) {
	int Array[]=ArrayHelper.initArray();
	System.out.println(ArrayHelper.toString(Array));
	System.out.println("Nun wird die Liste geordnet:");
	MSort(Array,(Array.length/2));
	System.out.println(ArrayHelper.toString(Array));
}
}

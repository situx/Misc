import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

import utils.Pair;


public class ClosestPair {

	public List<Pair> pairlist;
	public HashSet<Pair> hashset=new HashSet<Pair>();
	public Integer closestDistance=-1;
	public Integer currentDistance;
	public Pair closestPair1;
	public Pair closestPair2;
	public Integer comparisons;
	public Integer gridDistance;
	
	public ClosestPair(){
		this.pairlist=new LinkedList<Pair>();
	}
	
	public void generatePairs(final Integer amount){
		Random random = new Random();
		for(int i=0;i<amount;i++){
			pairlist.add(new Pair(random.nextInt(10000),random.nextInt(10000)));
			System.out.println("Added: "+this.pairlist.get(this.pairlist.size()-1));
		}
	}
	
	public void detClosestPair(){
		System.out.println("Deterministic Approach: Brute Force Comparison with 0(n²)");
		comparisons=0;
		for(Pair pair:pairlist){
			for(Pair paircomp:pairlist){
				comparisons++;
				currentDistance=pair.distance(paircomp);
				if(currentDistance!=0 && (closestDistance==-1 || currentDistance<closestDistance)){
						System.out.println("Closer Distance: "+currentDistance+" < "+closestDistance+"\n"+pair+" and "+paircomp);
						closestDistance=currentDistance;
						closestPair1=pair;
						closestPair2=paircomp;
					}
				}
			}
			System.out.println("Closest Pair: "+closestPair1+" and "+closestPair2+" with distance "+closestDistance+" after "+comparisons+" comparisons");
	}
	
	public void randClosestPair(){
		comparisons=0;
		currentDistance=0;
		closestDistance=-1;
		Random rand=new Random();
		Pair randpair=pairlist.get(rand.nextInt(pairlist.size()-1));
		System.out.println("Random Pair: "+randpair+"\n For this random pair we will find the closest neighbour like in the deterministic approach!");
		for(Pair paircomp:pairlist){
			comparisons++;
			currentDistance=randpair.distance(paircomp);
			if(currentDistance!=0 && (closestDistance==-1 || currentDistance<closestDistance)){
					System.out.println("Closer Distance: "+currentDistance+" < "+closestDistance+" with "+randpair+" and "+paircomp);
					closestDistance=currentDistance;
					closestPair1=randpair;
					closestPair2=paircomp;
			}
		}
		System.out.println("The closest pair with the random pair we will add to our Hashtable");
		System.out.println("Closest Pair: "+closestPair1+" and "+closestPair2+" with distance "+closestDistance+" after "+comparisons+" comparisons");
		hashset.add(closestPair1);
		hashset.add(closestPair2);
	}
	
	public static void main(String[] args) {
		ClosestPair pair=new ClosestPair();
		pair.generatePairs(6);
		pair.detClosestPair();
		pair.randClosestPair();
	}
}

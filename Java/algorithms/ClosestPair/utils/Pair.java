package utils;

public class Pair implements Comparable<Pair>{
	
	private Integer first;
	private Integer second;
	
	public Pair(Integer first,Integer second){
		this.first=first;
		this.second=second;
	}
	
	public Integer getFirst(){
		return this.first;
	}
	
	public Integer getSecond(){
		return this.second;
	}
	
	@Override
	public String toString() {
		return "["+this.first+","+this.second+"]";
	}
	
	public int distance(Pair comp){
		return (int)Math.sqrt(Math.pow(this.first-comp.first,2)+Math.pow(this.second-comp.second,2));
	}

	@Override
	public int compareTo(Pair comp) {
		return this.first-comp.first;
	}

}

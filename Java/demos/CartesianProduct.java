package com.github.situx.lecturehelpers.cartesianproduct;

import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import com.google.common.collect.Sets;

/**
 * This class implements the calculation of a cartesian product using String merging and set theory.
 *
 */
public class CartesianProduct {
	
	Set<String> L=new TreeSet<String>(Arrays.asList("01", "10", "11"));
	Set<String> LStar=new TreeSet<String>(Arrays.asList("e","01", "10", "11"));
	Set<String> LPlus=new TreeSet<String>(Arrays.asList("01", "10", "11"));
	Set<String> LWo1011=new TreeSet<String>(Arrays.asList("01"));
	Set<String> listM=new TreeSet<String>(Arrays.asList("001", "110"));
	Set<String> listMStar=new TreeSet<String>(Arrays.asList("e","001", "110"));
	
	
	public static Set<Set<Object>> cartesianProduct(Set<?>... sets) {
	    if (sets.length < 2)
	        throw new IllegalArgumentException(
	                "Can't have a product of fewer than two sets (got " +
	                sets.length + ")");

	    return _cartesianProduct(0, sets);
	}

	private static Set<Set<Object>> _cartesianProduct(int index, Set<?>... sets) {
	    Set<Set<Object>> ret = new HashSet<Set<Object>>();
	    if (index == sets.length) {
	        ret.add(new HashSet<Object>());
	    } else {
	        for (Object obj : sets[index]) {
	            for (Set<Object> set : _cartesianProduct(index+1, sets)) {
	                set.add(obj);
	                ret.add(set);
	            }
	        }
	    }
	    return ret;
	}
	
	/**
	 * Calculates a cartesian product interpreted as a method to merge Strings.
	 * @param one the first set of Strings to merge
	 * @param two the second set of String so be merged
	 * @return the merged set of Strings
	 */
	public Set<String> cartesianProductOnStrings (Set<String> one,Set<String> two)
	{
	    Set<String> result=new TreeSet<String>();
	    for (String onestr : one){
	        for (String twostr : two){
	            result.add(onestr+twostr);
	        }
	    }
	    return result;
	}
	
	/**
	 * Method to print the results of a regular cartesian Product calculation.
	 */
	@SuppressWarnings("unchecked")
	public void cartProduct(){
		Set<List<String>> listM2=Sets.cartesianProduct(listM,listM);	
		Set<List<String>> listL2=Sets.cartesianProduct(L,L);
		Set<Set<Object>> listL3=cartesianProduct(cartesianProduct(L,L),L);
		System.out.println("L= "+L);
		System.out.println("Assignment 6.1a) ListL2: "+listL2);
		System.out.println("M= "+listM);
		System.out.println("M2= "+listM2);
		System.out.println("M*= "+listMStar);
		System.out.println("L3= "+listL3);
		System.out.println("Assignment 6.1b) "+Sets.union(listM2, LWo1011));
		System.out.println("Assignment 6.1c) "+Sets.intersection(listMStar, listL3));
		System.out.println("Assignment 6.4d): "+Sets.difference(LStar, LPlus));
	}
	
	/**
	 * Method to print the results of a String merging cartesian Product calculation.
	 */
	public void cartProductString(){
		Set<String> listM2=this.cartesianProductOnStrings(listM,listM);
		Set<String> listL2=this.cartesianProductOnStrings(L,L);
		Set<String> listL3=cartesianProductOnStrings(cartesianProductOnStrings(L, L),L);
		System.out.println("L= "+L);
		System.out.println("Assignment 6.1a) ListL2: "+listL2);
		System.out.println("M= "+listM);
		System.out.println("M2= "+listM2);
		System.out.println("L3= "+listL3);
		System.out.println("Assignment 6.1b) "+cartesianProductOnStrings(listM2, LWo1011));
		System.out.println("Assignment 6.1c) "+Sets.intersection(listM2, listL3));
		System.out.println("Assignment 6.4d): "+Sets.difference(LStar, LPlus));
	}
	
	 /**
	  * Main method parsing two integer from the args array and executing the ggt in the original version and its modified version.
	  * @param args
	  */
	public static void main(String[] args){
		CartesianProduct cart=new CartesianProduct();
		System.out.println("Interpretation of the bit strings as sets including one element");
		cart.cartProduct();
		System.out.println(System.lineSeparator()+"Interpretation of the bit strings as Strings to be merged when building a cartesian product");
		cart.cartProductString();
		System.out.println(cart.cartesianProductOnStrings(cart.cartesianProductOnStrings(cart.L, cart.L),cart.L));
	}
	
}

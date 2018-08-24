package com.github.situx.lecturehelpers.sort;

import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * Demonstration of sorting lexicogra
 * phically and numerically in Java.
 *
 */
public class SortingDemo {
	
		
	public static void main(String[] args) {
		List<String> listAsString=Arrays.asList(new String[]{"111","0","11100","01011","0101","1100","100","0100","10","011","1","110","001","0000","01","01","1110"});
		List<String> alphListAsString=Arrays.asList(new String[]{"bbb","a","bbbaa","ababb","abab","bbaa","baa","abaa","ba","abb","b","bba","aab","aaaa","ab","ab","bbba"});
		List<String> listAsString2=Arrays.asList(new String[]{"013","777","5","3","015","04","053","e","203","0530","146","31112","20111","0","310","051","01","32","312"});
		List<String> listAsString2WOe=Arrays.asList(new String[]{"013","777","5","3","015","04","053","203","0530","146","31112","20111","0","310","051","01","32","312"});
		System.out.println("List 1: "+listAsString);
		Collections.sort(listAsString);
		System.out.println("Lexicographic Sort of List 1: "+listAsString);
		Collections.sort(listAsString, new NumericalComparator());
		System.out.println("Numerical Sort of List 1: "+listAsString+System.lineSeparator());
		System.out.println("Alphabetical List 1=List 1 where b=1 and a=0: "+alphListAsString);
		Collections.sort(alphListAsString);
		System.out.println("Lexicographic Sort of Alphabetical List 1: "+alphListAsString+System.lineSeparator());
		System.out.println("List 2: "+listAsString2);
		Collections.sort(listAsString2);
		System.out.println("Lexicographic Sort of List 2: "+listAsString2);
		Collections.sort(listAsString2WOe, new NumericalComparator());		
		System.out.println("Numerical Sort of List 2 without e: "+listAsString2WOe);	
	}

}



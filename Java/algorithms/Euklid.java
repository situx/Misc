package com.github.situx.lecturehelpers.euklid;

import java.util.LinkedList;
import java.util.List;

/**
 * This class implements the Euclidean algorithm in a recursive way. It can be
 * used to verify results calculated manually.
 */
public class Euklid {
	/**
	 * Step counter for the algorithm.
	 */
	public static Integer steps = 0;
	/**
	 * List of calculations on paper.
	 */
	public static List<String> calculations = new LinkedList<String>();
	/**
	 * Counter for repeating calculations.
	 */
	public static Integer counter = 0;

	/**
	 * Calculates ggt in a recursive way using the standard set of rules
	 * 
	 * @param a
	 *            the first number
	 * @param b
	 *            the second number
	 * @param steps
	 *            current number of steps
	 * @return ggt as int
	 */
	public static int ggt(int a, int b) {
		if (a == b) {
			steps++;
			System.out.println("(" + a + "," + b + ")");
			calculations.add((b * (counter) ) +"=" + (counter)+"*"+b+ " Remainder: "+(a-b));
			return (a);
		} else {
			System.out.println("(" + a + "," + b + ")");
			if (a > b) {
				if(steps>0 && b>(a-b)) {
					//System.out.println((a * counter + b) + "=" + (counter+1)+ "*"+b +" Remainder: " + (a-b));+b+"*"+counter+"+"+(a-b)+"="+
					calculations.add((b * counter +(a-b)) + "=" + (counter)+ "*"+b +" Remainder: " + (a-b));
					counter = 0;
				}
				counter++;
				steps++;
				return (ggt(a - b, b));
			} else {
				if(steps>0 && a>(b-a)) {
					//System.out.println((b * (counter) + a) +"=" + (counter)+"*"+(counter*b)+ " Remainder: " + a);a+"*"+counter+"+"+(b-a)+"="+
					calculations.add((a * counter +(b-a)) +"=" + (counter)+"*"+a+ " Remainder: " + (b-a));
					counter = 0;
				}
				counter++;
				steps++;
				return (ggt(b - a, a));
			}
		}
	}

	/**
	 * Calculates ggt in a recursive way using the standard set of rules. It
	 * additionally corrects negative values of a or b to positive values.
	 * 
	 * @param a
	 *            the first number
	 * @param b
	 *            the second number
	 * @param steps
	 *            current number of steps
	 * @return ggt as int
	 */
	public static int initializeggT(int a, int b, boolean normalizeValues) {
		if(normalizeValues){
			if (a < 0) a *= -1;
			if (b < 0) b *= -1;
		}
		steps=0;
		counter=1;
		calculations.clear();
		return ggt(a,b);
	}

	/**
	 * Main method parsing two integer from the args array and executing the ggt
	 * in the original version and its modified version.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		int a = Integer.valueOf(args[0]);
		int b = Integer.valueOf(args[1]);
		System.out.println("ggT(" + a + "," + b + ")=" + 		initializeggT(a, b, false) + " with " + steps + " steps"
				+ System.lineSeparator() + "Manual Calculations: ");
		for (String calc : calculations) {
			System.out.println(calc);
		}
		System.out.println("====================");
	}

}

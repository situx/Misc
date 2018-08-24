package com.github.situx.lecturehelpers.sort;

import java.util.Comparator;

/**
 * Comparator comparing String numbers to sort them in a numerical order.
 */
public class NumericalComparator implements Comparator<String> {

	@Override
	public int compare(String a, String b) {
        return Integer.valueOf(a.toString()).compareTo(Integer.valueOf(b.toString()));
	}
}
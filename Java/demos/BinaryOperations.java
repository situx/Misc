package com.github.situx.lecturehelpers.binaryoperations;

public class BinaryOperations {

	public static Integer binaryAdd(Integer number1,Integer number2){
		System.out.println(Integer.toBinaryString(number1));
		System.out.println(Integer.toBinaryString(number2));
		System.out.println("================================");
		System.out.println(Integer.toBinaryString(number1+number2));
		return number1+number2;
	}
	
	public static Integer binaryMultiply(Integer number1,Integer number2){
		System.out.println(Integer.toBinaryString(number1));
		System.out.println(Integer.toBinaryString(number2));
		System.out.println("================================");
		System.out.println(Integer.toBinaryString(number1*number2));
		return number1+number2;
	}
	
	public static void main(String[] args) {
		int a = Integer.valueOf(args[0],2);
		int b = Integer.valueOf(args[1],2);
		binaryAdd(a,b);
		binaryMultiply(a,b);
	}
	
}

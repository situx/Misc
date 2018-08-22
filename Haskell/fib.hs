--Implementation of the fibonacci numbers in Haskell

-- Fibonacci of 0 is 0
fib 0 = 0

--Fibonacci of 1 is 1
fib 1 = 1

--Fibonacci of i>1 is fibonacci of i-1 + fibonacci of i-2
fib i = fib (i-1) + fib (i-2)

--Fibonacci implementation with aid of a buffer
fibM i =
	let fibs = [0,1] ++ [fibs!!(i-1) + fibs!!(i-2) | i <- [2..]]
	in fibs!!i 
	
--Fibonacci implementation with aid of a buffer and with saving of abstractions
fibM' =
	let fibs = [0,1] ++ [fibs!!(i-1) + fibs!!(i-2) | i <- [2..]]
	in \i -> fibs!!i 

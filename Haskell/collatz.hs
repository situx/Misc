-- Implementation of the collatz sequence in Haskell
import Debug.Trace
collatz :: Integer -> Integer
collatz 1 = trace("N=1") 1
collatz n = if even n
             then trace("N="++show n++" is even") collatz (div n 2)
	     else trace("N="++show n++" is not even") collatz (3*n+1)

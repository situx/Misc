-- Implementation to represent peano numbers
data Pint = Zero | Succ Pint
 deriving(Eq,Show)

istZahl :: Pint -> Bool
istZahl x  =  case x of {Zero  -> True; (Succ y) ->  istZahl y} 

--If the first is a Boolean use istZahl to check for a valid number
istZahlAll :: PintAll -> Bool
istZahlAll (x,y) = case x of {True -> istZahl y; False -> istZahl y}

peanoPlus :: Pint -> Pint -> Pint
peanoPlus x y  = if istZahl x &&  istZahl y then pplus x y else bot 
  where
   pplus x  y  =  case x of  
                     Zero  -> y
                     Succ  z -> Succ (pplus z y) 
                     
-- If it is a PintAll
-- Check if the first PintAll is positive or negative
-- Then check the second one.... if both are positive or both are negative use peanoPlus and set the Boolean accordingly
-- If one is positive and one is negative find out the bigger value and subtract the numbers by using Integers
peanoPlusAll :: PintAll -> PintAll -> PintAll
peanoPlusAll (v, w) (x,y) = if istZahlAll (v,w) &&  istZahlAll (x,y) then pplusAll (v,w) (x,y) else bot 
  where
  pplusAll (v,w) (x,y) = case v of
				 True -> if x then (True, (peanoPlus w y)) else ((peanoLeq y w),intToPeano((peanoToInt(w)-peanoToInt(y))))
				 False -> if not x then (False, (peanoPlus w y)) else ((peanoLeq w y), (intToPeano((peanoToInt(w)-peanoToInt(y)))))
--test:: PintAll -> PintAll -> Integer
--test (v,w) (x,y) = seq x (peanoToInt(w)-peanoToInt(y))
				 				 
bot = bot

peanoEq :: Pint -> Pint -> Bool
peanoEq x y = if istZahl x &&  istZahl y then eq x y else bot 
 where
  eq Zero Zero          = True
  eq (Succ x) (Succ y)  = eq x y
  eq _        _         = False

peanoLeq :: Pint -> Pint -> Bool
peanoLeq x y = if istZahl x &&  istZahl y then leq x y else bot 
 where
  leq Zero y            = True
  leq x    Zero         = False
  leq (Succ x) (Succ y) = leq x y

peanoMult :: Pint -> Pint -> Pint
peanoMult x y  = if istZahl x &&  istZahl y then mult x y else bot 
  where
   mult x  y  =  case x of  
                     Zero   -> Zero
                     Succ z -> peanoPlus y (mult z y)

 
-- Konvertieren Integer <-> Pint
-- z.B. zum Testen peanoToInt ( (intToPeano 50) `peanoPlus` (intToPeano 10))
                     
intToPeano :: Integer -> Pint                     
intToPeano i
  | i == 0   = Zero
  | i > 0    = Succ (intToPeano (i-1))
  | i < 0    = Succ (intToPeano ((i*(-1))-1))
  
peanoToInt :: Pint -> Integer
peanoToInt Zero     = 0
peanoToInt (Succ x) = 1 + (peanoToInt x)

--Converts an Integer to PintAll
peanoAllToInt (neg, pint) = peanoAllToInt_acc pint neg 0 
  where
    peanoAllToInt_acc Zero neg n = n * (if neg then (-1) else 1)
    peanoAllToInt_acc (Succ x) neg n = peanoAllToInt_acc x neg (n + 1)

-- Convert PintAll to Integer
-- Uses intToPeano to convert the value and sets the boolean appropriately
intToPeanoAll :: Integer -> PintAll
intToPeanoAll i
  | i==0  =(True,Zero)
  | i>0   =(True,intToPeano (i))
  | i<0   =(False,intToPeano (i*(-1)))
  
type PintAll = (Bool,Pint)

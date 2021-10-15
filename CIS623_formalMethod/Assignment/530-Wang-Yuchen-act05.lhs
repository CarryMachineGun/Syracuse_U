---------------------------------------------------------------------------
Fall 2021 CIS 623
Activity 5
---------------------------------------------------------------------------

Lastname :  < Wang >
Firstname:  < Yuchen > 
Stud. num:  < 530 >

---------------------------------------------------------------------------

> import Prelude hiding (scanl)
> import Data.List hiding (inits, tails, scanl)

We will use the following function in our demonstrations:


> rmdups :: Eq a => [a] -> [a]
> rmdups []
>               = []
> rmdups (n:ns) =  n : filter (/= n) (rmdups ns)


-- 1. By using the higher order function map and recursion, define
      the higher order function inits.

      The function inits will take a list xs of type [a] as input, 
      return the list of initial segments of xs in ascending 
      (w.r.t. length) order 

Show the code for inits in the space below:

> inits :: [a] -> [[a]]
> inits [] = [[]]
> inits (n:ns) = [] : (map (n:)) (inits ns)




-- 2. By using recursion, define the function tails

      The function tails will take a list xs of type [a] as input, 
      return the list of tail segments of xs in descending 
      (w.r.t. length) order 

Show the code for tails in the space below:


> tails :: [a] -> [[a]]
> tails [] = [[]]
> tails (n:ns) = (n:ns) : tails ns



-- 3. By using recursion, define the function scanl

Show the code for scanl in the space below:



> scanl :: (c -> a -> c) -> c -> [a] -> [c]
> scanl f e [] = [e]
> scanl f e (n:ns) = e : scanl f (f e n) ns



-- 4. Experiments with inits, tails and scanl

Show test examples you have created for the three functions
and document the results in the space below:


> test1 = inits [4,5,7]


[[],[4],[4,5],[4,5,7]]


> test2 = tails [7,8,6]


[[7,8,6],[8,6],[6],[]]


> test3 = (rmdups . concat . map inits . tails) [7..9]

[[],[7],[7,8],[7,8,9],[8],[8,9],[9]]

> test4 = scanl (+) 6 [60,600,6000]

[6,66,666,6666]
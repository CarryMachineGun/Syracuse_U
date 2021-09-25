---------------------------------------------------------------------------
Fall 2021 CIS 623
Activity 3
---------------------------------------------------------------------------

Lastname :  < Wang >
Firstname:  < Yuchen > 
Stud. num:  < 530 >

> import Data.Char
> import Cipher


---------------------------------------------------------------------------

-- 1. (Demo)  Creating a module for the cipher

The instructor will follow Bird, section 2.6 to create a module from
the implementation given in the file: cipher.hs 

Please follow the steps in the demo to create a module in your machine.
Give a concise summary for the steps you carried out. 

Put your answer to question 1 below:

-- put cipher.hs and act03.lhs into the same folder
-- put the code 'module Cipher where' at the first line of cipher.hs
-- compile act03.lhs with ghci
-- wait till "Ok, two modules loaded." showing up
-- input '2intlet 8' and get the result of 'i'

---------------------------------------------------------------------------

-- 2. Implementing the elem function as elem1 by recursion
      (with at least one test case)

Put your answer to question 2 below:

> elem1      :: (Eq a) => a -> [a] -> Bool
> elem1 x []  =  False
> elem1 x (y:ys)
>  | x == y    = True
>  | otherwise = elem1 x ys

> test1 :: Bool
> test1 = elem1 6 [18,77,24,6]
> test2 :: Bool
> test2 = elem1 'b' ['a','b','c']

---------------------------------------------------------------------------

-- 3. Practice

Use your elem1 function to write a function makeSet which, 

given a list, returns a list which contains all the elements of 
the original list, but has no duplicate elements.

Put your answer to question 3 below:


> makeSet   :: (Eq a) => [a] -> [a]
> makeSet [] = []
> makeSet (n:ns)
>   | elem1 n ns == True = makeSet ns
>   | otherwise = n : (makeSet ns)

---------------------------------------------------------------------------

-- 4  

Use a list comprehension to build a list of all positive 
numbers less than 10000 which have both 21 and 83 as factors

Put your answer to question 4 below:

> list4 :: [Int]
> list4 = [ n| n <- [1..9999], (n `rem` 21 == 0) && (n `rem` 83 == 0)]


---------------------------------------------------------------------------

-- 5. Practice

Use a list comprehension to build a list of all positive 
numbers less than 10000 which have either 21 and 83 as factors
(no repetitions are allowed).

Put your answer to question 5 below:

> list5 :: [Int]
> list5 = makeSet [ n| n <- [1..9999], (n `rem` 21 == 0) || (n `rem` 83 == 0)]


---------------------------------------------------------------------------

-- 6. 

Note: You may use functions given in Data.Char for this question.

Use list comprehension to write a function which will take a 
String (ie. of type [Char]) as input and return the string
where all uppper case letters are being turned to lowercase.

Put your answer to question 6 below:

> toLowerString    :: [Char] -> [Char]
> toLowerString  []      = []
> toLowerString  (n:ns)
>   | isUpper n = (toLower n) : (toLowerString ns)
>   | otherwise = n :(toLowerString ns)



---------------------------------------------------------------------------


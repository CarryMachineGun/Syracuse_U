______________________________________________________________________
Fall 2021  CIS 623 

Quiz 3 Version B solution
______________________________________________________________________

> import Prelude hiding (foldr, foldl)

Q1

a).

expr 
={def}
iterate (*3) 1
={iterate.1} 
1:iterate (*3) ((*3) 1) 
={iterate.1 and arithmetic} 
1:3:iterate (*3) ((*3) (*3) 1))
={iterate.1 and arithmetic} 
1:3:9:iterate (*3) ((*3) (*3) (*3) 1)))

b).

Given

> compute1    :: [Integer] -> [Integer]
> compute1 xs = [ x^3  | x <- xs, x^2 > 1]

Equivalently, (using map and filter) we can write the 
function as:

> compute2    :: [Integer] -> [Integer]
> compute2 xs = map (\x -> x^3) (filter (\x -> x^2 > 1) xs)   

----------------------------------------------------------------------

Question 2

a).

Recall:

> foldr        :: (a -> b -> b) -> b -> [a] -> b
> foldr f v []     = v
> foldr f v (x:xs) = f x (foldr f v xs)

so for foldl:

> foldl :: (b -> a -> b) -> b -> [a] -> b
> foldl f v [] = v
> foldl f v (x:xs) = foldl f (f v x) xs


b). 

Consider the function 

> doubleit    :: [a] -> [a]
> doubleit [] = []
> doubleit (x:xs) = x:x:doubleit xs

rewrite doubleit using the recursion operator foldr.

> doubleit2    :: [a] -> [a]
> doubleit2 xs = foldr k [] xs
>     where
>     k      :: a -> [a] -> [a]
>     k a bs = a:a:bs


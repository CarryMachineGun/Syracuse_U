______________________________________________________________________
Fall 2021  CIS 623 

The code used in quiz 2.
______________________________________________________________________

> import Data.Char

> let2int :: Char -> Int
> let2int c = ord c - ord 'a'

> int2let :: Int -> Char
> int2let n = chr (ord 'a' + n)

> f       :: [Int -> Int] -> Int -> Int
> f [] a     =  a
> f (g:gs) a =  g (f gs a)

> g       :: Int -> Int 
> g x     = x + x

> h    :: [a] -> [a]
> h []  = []
> h [x]      = [x]
> h (x:y:xs) = h xs

*Main> :t h [f]
h [f] :: [[Int -> Int] -> Int -> Int]

*Main> :t h []
h [] :: [a]

*Main> :t f [let2int]
type error

*Main> :t (let2int) . (int2let)
(let2int) . (int2let) :: Int -> Int



______________________________________________________________________

2. Write a function keepodd so that

> keepodd    :: [a] -> [a]
> keepodd xs = [u  | (u,v) <- zip xs [0..], v `mod` 2 == 1]  


______________________________________________________________________

3. Write a function consec so that

> elem2    :: (Eq a) => [a] -> Bool
> elem2 []  = False
> elem2 [y] = False
> elem2 (x:y:ys) 
>     | x == y =  True
>     | otherwise = (elem x ys) || (elem y ys) || (elem2 ys)

Another approach

> elem_2 [] = False
> elem_2 [x] = False
> elem_2 (x:xs) | x == elem x xs = True
> 	       	| otherwise = elem_2 xs

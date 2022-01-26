----------------------------------------------------------------------

CIS 623
Lecture 9 haskell script: 623-f21-09.lhs

----------------------------------------------------------------------

> import Prelude hiding (map, filter)
> import Data.Char
> import Cipher


List comprehension

1. Examples using functions from Cipher

> eg1a :: [(Char,Int)]
> eg1a =  [(c, let2int c) | c <- ['a'..'z']]

> eg1b :: [(Char,Int)]
> eg1b=  [(c, let2int c) | c <- ['A'..'Z']]

> eg1c :: [(Int, Char)]
> eg1c = [(x,int2let x) | x<-[-97,(-96)..30]]

2. Example: Determine if a string is a parlindrome

> isParlindrome    :: [Char] -> Bool
> isParlindrome xs = ys == reverse ys
>     where
>       ys = [ toLower c | c <- xs, isAlpha c]

3. Examples of using enumerations in Haskell (Bird, 4.2)

a. [m..n] represents the list [m,m+1,..,n]

> eg3a1 ::[(Char,Int)]
> eg3a1 = [(c, i) | (c, i) <- zip ['a'..'z'] [0..25]]  


> eg3a2 ::[(Char,Int)]
> eg3a2 = [(c, i) | (c, i) <- zip ['A'..'Z'] [(-32)..(-7)]]  


b. Other cases

i.    [m..]  represents the list [m, m+1, ..]

> eg3b1 :: [Integer]
> eg3b1 =  [(-2)..]

ii.  (n > m) [m,n..p]  represents the list 
     [m, m+(n-m), m + 2(n-m), .., until the bdd p is reached] 

> eg3b2 :: [Integer]
> eg3b2 =  [(-2),3..11]

iii.  [m,n..]

> eg3b3 :: [Integer]
> eg3b3 =  [(-2),3..]


4. Introduction to higher order functions: beginning examples
   from the Anagrams program

a. (Practice) implement the map function via list comprehension

> map      :: (a -> b) -> [a] -> [b]
> map f xs = [ f x| x<- xs]


b. (Practice) implement the filter function via list comprehension

> filter      :: (a -> Bool) -> [a] -> [a]
> filter t xs = [ x | x <- xs, t x]

5. Example: A property for the map function

  ( map f) . (map g) = map  (f . g)


6. Examples of frequently used higher order function 

   (.), all, any, takeWhile and dropWhile


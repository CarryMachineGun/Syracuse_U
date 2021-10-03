----------------------------------------------------------------------

CIS 623
Lecture 7 haskell script: 623-f21-07.lhs

----------------------------------------------------------------------

List comprehension

1. Beginning examples

> import Prelude hiding (concat)

> eg1 :: [Int]
> eg1 =  [ x^2 | x <- [1..5]]

> eg2 :: [(Int, Int)]
> eg2 = [(x,y) | x<- [1,2,3], y <- [4,5]]

> eg3 :: [(Int, Int)]
> eg3 = [(x,y) | y <-[4,5], x <-[1,2,3]]

> eg4 :: [(Int, Int)]
> eg4 = [(x,y) | x<-[1..3], y <-[x..3]]

> concat     :: [[a]] -> [a]
> concat xss =  [x | xs <- xss, x <- xs]

2. Examples: translating standard definitions

a. Definition (factors)

Given two positive integers n and x. The integer x is said to be 
a factor of n if x|n, or equivalently, n `mod` x equals 0.

Implementation:

> factors   :: Int -> [Int]
> factors n =  [x | x <- [1..n], n `mod` x == 0] -- {x in A | p(x)}

b. Definition (primes)

A positive integer x is prime provided its only factors are 1
and itself and x > 1.

Implementation:

> prime   :: Int -> Bool
> prime k = factors k == [1,k]

> primes :: [Int]
> primes = [ p | p <-[2..], prime p]

Note: 

1. Haskell allow `infinite' (unbounded) lists.
2. Haskell adopts the lazy evaluation strategy. 

3. Indexing a list with numbers

> index    :: [a] -> [(a,Int)]
> index xs = [ (x,i) | (x, i) <- zip xs [0..]]
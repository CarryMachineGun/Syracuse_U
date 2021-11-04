---------------------------------------------------------------------------
Fall 2021 CIS 623
Activity 4
---------------------------------------------------------------------------

Lstname :  < Wang >
Firstname:  < Yuchen > 
Stud. num:  < 530 >

> import Data.Char

---------------------------------------------------------------------------

-- 1. Use the function until to perform an iteration
      Implement a function f which computes the sqrt of a nonnegative 
      number x (of type Float) using the Newton's method


> f :: Float -> Float 
> f x = until okay update x 
>  where
>   okay y = abs (y*y-x) < tol*x
>   update y = (y+x/y)/2
>   tol = 0.00001

-- 2. Display iteration results for a list of inputs via the map function

> result :: [Float]
> result = map f [1..9]

-- 3. a.

      Use the until function to drop the initial segment of a list
      (of length > 2) down to length 2.  We only consider cases
      where 0 <= k <= length xs

> d1 :: Int -> [a] -> [a]
> d1 k xs = until okay update xs
>  where
>   okay ys = (length ys <= k)
>   update ys = tail ys

-- 3. b.

      The function iterate is written to show each iterations.
      Re-implement the function required in 3 a using the function
      iterate


> d2 :: Int -> [a] -> [a]
> d2 k xs = (iterate  tail xs) !! (length xs - k)

> play xs = iterate tail xs

> play2 xs = iterate tail xs


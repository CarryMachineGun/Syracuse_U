----------------------------------------------------------------------

CIS 623
Lecture 2 haskell script: 623-f21-02.lhs

----------------------------------------------------------------------

> import Prelude hiding (sum)

Example 1: the function double

> double :: Int -> Int
> double x = x + x                                                        

Example 2: the function sum

> sum    :: [Int] -> Int
> sum []     = 0
> sum (n:ns) = n + sum ns

Example 3: the function qsort (revised from prev. lecture)
    
> qsort    :: (Ord a) => [a] -> [a] 
> qsort []     = []
> qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
>     where 
>       smaller = [a | a <- xs, a <= x]
>       larger  = [b | b <- xs, b > x ]

To describe how qsort is being evaluated, consider the following
two instances. Using Feijen's notation:

1. qsort [x]

qsort [x]
= { applying qsort }
qsort [] ++ [x] ++ qsort []
= { applying qsort }
[] ++ [x] ++ []
= { applying ++ }
[x]


2. qsort [3,5,1,4,2]

qsort [3,5,1,4,2]
= { applying qsort }
qsort [1,2] ++ [3] ++ qsort [5,4]
= { applying qsort }
(qsort [] ++ [1] ++ qsort [2]) ++ [3] ++ (qsort [4] ++ [5] ++ qsort [])
= { applying qsort , above property }
([] ++ [1] ++ [2]) ++ [3] ++ ([4] ++ [5] ++ [])
= { applying ++ }
[1,2] ++ [3] ++ [4,5]
= { applying ++ }
[1,2,3,4,5]

Example 4: 

> f   :: Int -> Int -> Int -> Int
> f x y z = x + y + z


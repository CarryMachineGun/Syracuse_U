______________________________________________________________________
Fall 2021  CIS 623 

The code used in quiz 1.
______________________________________________________________________


> f       :: Int -> Int -> Int -> [Int]
> f a b c = [a,b,c]

> g       :: Int -> Int 
> g x     = x + x

> qsort1    :: (Ord a) => [a] -> [a] 
> qsort1 []     = []
> qsort1 (x:xs) = qsort1 larger ++ [x] ++ qsort1 smaller
>     where 
>       smaller = [a | a <- xs, a < x]
>       larger  = [b | b <- xs, b > x ]

> type Words  = [Char]
> type Key    = [Char]  

> getWords :: Int -> [Words] -> [Words]
> getWords n = filter ((==n) . length)


______________________________________________________________________

Answers to question 1


a. [Int]

b. Type error

c. Int -> [Int]

d. [[Char]]

e. (Int -> Int -> Int -> [Int], Int -> Int)

______________________________________________________________________

Answers to question 2

a. 

qsort1 [3,5,1,4,2]
={qsort1.2}
qsort1 [5,4] ++ [3] ++ qsort1 [1,2]
={qsort1.2}
(qsort1 [] ++ [5] ++ qsort1 [4]) ++ [3] ++ (qsort1 [2] ++ [1] ++ qsort1 [])
={qsort1.1 for [] and qsort1.2 for singleton}
([] ++ [5] ++ ([] ++ [4] ++ []) ++ [3] ++ (([] ++ [2] ++ []) ++ [1] ++ [])
={by rules of ++}
[5,4,3,2,1]



b.

No. Consider the input [1,1], where sorting the list [1,1] in descending 
order should the same list. However, qsort1 [1,1] will return [1].

qsort1 [1,1]
={qsort1.2}
[] ++ [1] ++ []
={rules for ++}
[1]



----------------------------------------------------------------------

CIS 623
Lecture 1 haskell script: 623-f21-01.lhs

----------------------------------------------------------------------

Example 1: the function double

> double :: Int -> Int
> double x = x + x


double x = x + x + x

Example 2: the function sum1

> sum1    :: [Int] -> Int
> sum1 []     = 0
> sum1 (n:ns) = n + sum ns

Example 3: the function qsort
    
> qsort    :: [Int] -> [Int]
> qsort []     = []
> qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
>     where 
>       smaller = [a | a <- xs, a <= x]
>       larger  = [b | b <- xs, b > x ]

Example 4: the function product

> product1 :: [Int] -> Int
> product1 [] 	= 1
> product1 (a:as)= a * product as 

Example 5: the function qsort reverse
    
> qsortR    :: [Int] -> [Int]
> qsortR []     = []
> qsortR (x:xs) = qsortR larger ++ [x] ++ qsortR smaller
>     where 
>       larger  = [b | b <- xs, b > x ]
>       smaller = [a | a <- xs, a <= x]


Example 6: quadruple 

> quadruple :: Int -> Int
> quadruple x = double(double x)

> average :: [Int] -> Int
> average (ns) = div (sum ns) (length ns) 

> {- n = (double a) 'div' (length xs)
>  where 
>    a = 10
>    xs = [1,2,3,4,5] -}

> -- n = div (double a) (length xs) where a = 5; xs = [1,2,3,4,5]; b = 3
> n = div (double a) (length xs) where {a = 5; xs = [1,2,3,4,5]}; b = 3

> n2 = div (double a) (length xs) 
>  where 
>   a = 5
>   xs = [1,2,3,4,5] 
> b2 = 3

> k = div (sum ns) (length ns) where ns = [3,7] 
> last1 :: [Int] -> Int
> last1 ns = head (reverse ns)

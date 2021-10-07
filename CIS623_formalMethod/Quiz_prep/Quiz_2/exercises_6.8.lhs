> -- 1

> fac1 :: Int -> Int 
> fac1 0 = 1
> fac1 n 
>  | n >= 0 = n * fac1(n-1)
>  | otherwise = n * fac1(n+1) 

> fac2 :: Int -> Int 
> fac2 0 = 1
> fac2 n = 
>  if n >=0 then n * fac1(n-1)
>  else n * fac1(n+1)


> --2

> sumdown1 :: Int -> Int 
> sumdown1 0 = 0
> sumdown1 n = n + sumdown1(n-1)

> -- 3

> (^*) :: Int  -> Int  -> Int 
> a ^* 0 = 1
> a ^* b = a * (a ^* (b-1)) 

> -- 4
> euclid1 :: Int -> Int -> Int
> euclid1 a b
>  | a == b = a
>  | a < b = euclid1 a (b-a)
>  | otherwise  = euclid1 b (a-b)

> -- 5

> --6

> and1 :: [Bool] -> Bool 
> and1 [] = True
> and1 (n:ns)
>  | n == False  =  False 
>  | otherwise = and1 ns

> concat1 :: [[a]] -> [a]
> concat1 [] = []
> concat1 (ns:nss) = ns ++ (concat1 nss)

> concat2 :: [[a]] -> [a]
> concat2 ass = [a | as <- ass, a <- as]

> (!!!) :: [a] -> Int -> a
> ns !!! 1 = head ns
> ns !!! x = (tail ns) !!! (x-1)

> replicate1 :: Int -> a -> [a]
> replicate1 0 n = []
> replicate1 x n = [n] ++ (replicate (x-1) n)

> replicate2 :: Int -> a -> [a]
> replicate2 n x = [x | _ <- [0..n]]

> elem1 :: Eq a => a -> [a] -> Bool 
> elem1 _ [] = False 
> elem1 x (a:as) =
>  if x == a then True 
>  else elem1 x as

> --7

> merge1 :: Ord a => [a] -> [a] -> [a]
> merge1 x [] = x
> merge1 [] x = x
> merge1 (a:as) (b:bs)  
>  | a < b = a : (merge1 as (b:bs))
>  | otherwise = b : (merge1 (a:as) bs)

> --8

> msort1 :: Ord a => [a] -> [a]
> msort1 [] = []
> msort1 [x] = [x]
> msort1 ns = merge1 (msort1 left) (msort1 right)
>  where
>   left = take (div (length ns) 2) ns
>   right = drop (div (length ns) 2) ns



> zip1 :: [a] -> [b] -> [(a,b)]
> zip1 [] ns = []
> zip1 ns [] = []
> zip1 (a:as) (b:bs) = [(a,b)] ++ (zip as bs)

> and1 :: [Bool] -> Bool
> and1 [True] = True
> and1 [] = False
> and1 (n:ns) | n == False = False
>             | otherwise  = and1 ns

> concat1 :: [[a]] -> [a]
> concat1 [] = []
> concat1 (n:ns) = n ++ (concat1 ns)

> elem1 :: Eq a => a -> [a] -> Bool
> elem1 a [] = False
> elem1 a (n:ns) = if a == n then True else (elem1 a ns) 

> merge1 :: Ord a => [a] -> [a] -> [a]
> merge1 ns [] = ns
> merge1 [] ns = ns
> merge1 (n:ns) (x:xs) | n <= x = [n] ++ (merge1 ns (x:xs))
>                      | otherwise = [x] ++ (merge1 xs (n:ns))

> -- msort :: Ord a => [a] -> [a]
> -- msort ns 

> reverse1 :: [a] -> [a]
> reverse1 [] = []
> reverse1 (n:ns) = reverse1(ns) ++ [n]

> insert :: (Ord a) => a-> [a] -> [a]
> insert x []=[x] --insert 1.1
> insert x (y:ys)
>     | x<=y      = (x:y:ys) -- insert 2.1
>     | otherwise = y:(insert x ys) -- insert 2.2

> first3 :: [a] -> [a] 
> first3 (a1:a2:a3:an) = [a1,a2,a3]
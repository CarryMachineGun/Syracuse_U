> quicksort :: Ord a => [a] -> [a] 
> quicksort [x] = [x]
> quicksort [] = []
> quicksort (n:ns) = quicksort(l) ++ [n] ++ quicksort(r)
>  where
>   l = [x | x <- ns, x <= n]
>   r = [x | x <- ns, x > n ]

> count1 :: Char -> String -> Int 
> count1 x xs = length [n | n <- xs, n == x]


> positions :: Char -> String -> [Int]
> positions n ns = [y | (x, y) <- zip ns [0..], x == n]

> prime1 :: Int -> Bool 
> prime1 n =  [x | x <- [1..n], mod n x  == 0] == [1,n]

> pyths :: Int -> [(Int, Int, Int)]
> pyths n = [ (x,y,z) | x <- [0..n], y<-[0..n],z<-[0..n], x^2 + y^2 == z^2]

> concat1 :: [[a]] -> [a]
> concat1 nss = [x | ns<- nss, x <- ns]
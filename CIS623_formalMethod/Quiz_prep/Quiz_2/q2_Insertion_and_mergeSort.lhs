> insert2 :: Ord a => a -> [a] -> [a]
> insert2 x [] = [x]
> insert2 x (n:ns) 
>  | n >= x = x:n:ns
>  | otherwise = n : (insert2 x ns)


> inSort :: Ord a => [a] -> [a]
> inSort [] = []
> inSort (n:ns) = insert2 n (inSort ns)



> merge2 :: Ord a => [a] -> [a] ->[a] 
> merge2 [] ns = ns
> merge2 ns [] = ns 
> merge2 (n:ns) (x:xs) 
>  | n < x = n : (merge2 ns (x:xs))
>  | otherwise = x : (merge2(n:ns) xs)


> merSort :: Ord a => [a] -> [a]
> merSort [] = []
> merSort [x] = [x]
> merSort ns = merge2 (merSort l) (merSort r) 
>  where
>   l = take (div (length ns) 2) ns
>   r = drop (div (length ns) 2) ns


> even1 :: Int -> Bool 
> even1 0 = True 
> even1 n = odd1 (n-1)

> odd1 :: Int -> Bool 
> odd1 0 = False 
> odd1 n = even1 (n-1)



> zip1 :: [a] -> [b] -> [(a,b)]
> zip1 _ [] = []
> zip1 [] _ = []
> zip1 (x:xs) (y:ys) = [(x,y)] ++ (zip1 xs ys)

> drop1 :: Int -> [a] -> [a]
> drop1 _ [] = []
> drop1 0 xs = xs
> drop1 n (x:xs) = drop1 (n-1) xs

> merge1 :: [a] -> [a] -> [a]
> merge1 xs ys = xs ++ ys

> and1 :: [Bool] -> Bool 
> and1 [] = True
> and1 (x:xs) = x && (and1 xs)

> and2 :: [Bool] -> Bool 
> and2 = foldr (\x xs -> x && xs) True

> merge2 :: Ord a => [a] -> [a] -> [a]
> merge2 [] x = x
> merge2 x [] = x
> merge2 (x:xs) (y:ys)
>  | x >= y = [y] ++ (merge2 (x:xs) ys)
>  | otherwise = [x] ++ (merge2 xs (y:ys))

> mergeSort1 :: Ord a => [a] -> [a]
> mergeSort1 [] = [] 
> mergeSort1 [x] = [x] 
> mergeSort1 xs = merge2 (mergeSort1 left) (mergeSort1 right)
>  where 
>   left = take (div (length xs) 2) xs
>   right = drop (div (length xs) 2) xs

> concat1 :: [[a]] -> [a]
> concat1 [] = []
> concat1 (xs:xss) = xs ++ concat1 xss


> elem1 :: Eq a => a -> [a] -> Bool
> elem1 x [] = False
> elem1 x (y:ys) 
>  | x == y = True
>  | otherwise = elem1 x ys

> abs1 :: Int -> Int
> abs1 x = 
>  if x >= 0 then x
>  else -x


> abs2 :: Int -> Int
> abs2 x 
>  | x >= 0 = x
>  | otherwise = -x

> andSymbol :: Bool -> Bool -> Bool
> andSymbol True True = True
> andSymbol _ _ = False

> add1 :: Int -> Int -> Int
> add1 = \x -> (\y -> (x+y)) 

> safetail1 :: [a] -> [a]
> safetail1 [] = []
> safetail1 (x:xs) = xs

> safetail2 :: [a] -> [a]
> safetail2 xs = 
>  if null xs then []
>  else tail xs

> concat2 :: [[Int]] -> [Int]
> concat2 xss = [x | xs <- xss, x <- xs, x `div` 2 == 0] 

> mult1 :: Int -> Int
> mult1 a = a * a

> pos1 :: Eq a => a -> [a] -> [Int]
> pos1 x xs = [b | (a,b) <- zip xs [0..], a == x]

> pyths :: Int -> [(Int, Int, Int)]
> pyths n = [(x,y,z) | x <- [1..n], y <- [1..n], z <- [1..n], (x * x) + (y * y) == z * z]

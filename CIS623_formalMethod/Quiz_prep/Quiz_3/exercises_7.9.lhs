> -- Q1
> -- import Data.Char

> type Bit = Int
> -- super1 :: (a -> b) -> (a -> Bool) -> [a] -> [b]
> super1 f p xs = map f (filter p xs)


> -- Q2

> -- 2.a
> all1 f = foldr (\n ns -> (f n) && ns) True 

> all2 f = (and . map f)

> -- 2.b
> -- any1 :: (a -> Bool) -> [a] -> Bool
> any1 f = or . map f 

> -- 2.c
> takeWhile1 f = filter f 

> takeWhile2 f = foldr (\x xs -> if f x then x : xs else xs) []

> takeWhile3 f xs = [x | x <- xs, f x]

> takeWhile4 f [] = []
> takeWhile4 f (x:xs) = 
>  if f x then x : (takeWhile4 f xs)
>  else (takeWhile4 f xs)

> takeWhile5 f = foldr (\x xs -> if f x then [] else x : xs) []

> -- 2.d

> dropWhile1 f = foldr (\x xs -> if f x then xs else x : xs) []

> dropWhile2 f = foldl (\xs x -> if f x then xs else xs ++ [x]) []

> dropWhile3 f = foldr (\x xs -> if f x then xs else x : xs) []

> dropWhile4 f = foldl (\xs x -> if f x then [] else xs ++ [x]) []

> --3

> map1 f = foldr (\x xs -> [f x] ++ xs) []

> -- 4

> dec2Int :: [Int] -> Int 
> dec2Int = foldl (\xs x -> xs*10 + x) 0

> a = (reverse . map even)


> bin2int :: [Bit] -> Int
> bin2int = foldl (\xs x -> xs*2 + x) 0

> int2bin :: Int -> [Bit]
> int2bin 0 = []
> int2bin n = n `mod` 2 : int2bin (n `div` 2)

> length3 :: [a] -> Int 
> length3 = foldr (\_ n -> 1 + n) 0


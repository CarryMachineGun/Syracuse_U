> map1 :: (a -> b) -> [a] -> [b]
> map1 f [] = []
> map1 f (x:xs) = [f x] ++ (map1 f xs)

> length1 :: [a] -> Int
> length1 = foldr (\x xs -> 1 + xs) 0

> all1 :: (a -> Bool) -> [a] -> Bool
> all1 f = foldr (\x xs -> (f x) && xs) True

> any1 :: (a -> Bool) -> [a] -> Bool
> any1 f = foldr (\x xs -> f x || xs) False


> takeWhile1 :: (a -> Bool) -> [a] -> [a]
> takeWhile1 f [] = []
> takeWhile1 f (x : xs) =
>  if f x then [x] ++ takeWhile1 f xs
>  else []

> takeWhile2 :: (a -> Bool) -> [a] -> [a]
> takeWhile2 f = foldr (\x xs -> if f x then [x] ++ xs else []) [] 

> test = takeWhile2 ((== 0).(`mod` 2)) [2,4,6,8,9]

> --dropWhile1 :: (a -> Bool) -> [a] -> [a]
> --dropWhile1 f = foldl (\x xs -> )

> bin2int1 :: [Int] -> Int 
> bin2int1 = foldl (\xs x -> x + (xs * 2)) 0

> f1 x = until ((== 55) . (* 11)) (+1) x

> f2 x = until ((== 0) . (`mod` 11)) (+1) x

> f3 x = until ((== 0) . (`mod` 11)) (+1) (2 * x)

> f4 x = until even (+1) x

> play xs = iterate tail xs

> f5 xs = filter ((> 100) . (^2)) xs

> compute3 :: [Int] -> [Int] 
> compute3 xs = map (^3) (filter ((>1).(^2)) xs)
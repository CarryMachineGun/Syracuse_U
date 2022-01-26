> map1 :: (a -> b) -> [a] -> [b]
> map1 f [] = []
> map1 f (x : xs) = [f x] ++ map1 f xs 

> map2 f xs = [f x| x <- xs]

> reverse1 :: [a] -> [a]
> reverse1 = foldr (\x  xs -> xs ++ [x]) []

> reverse2 :: [a] -> [a]
> reverse2 = foldl (\xs  x -> [x] ++ xs) []

> and1 :: [Bool] -> Bool 
> and1 = foldr (&&) True 

> myAnd :: Bool -> Bool -> Bool 
> myAnd True True = True  
> myAnd _ _ = False 

> and2 :: [Bool] -> Bool 
> and2 = foldr (\x xs -> if myAnd x xs then True else False) True 

> cb :: [a] -> [a]
> cb = foldr (:) []

> cb2 :: [a] -> [a] -> [a]
> cb2 ys = foldr (:) ys

> map3 :: (a->b) -> [a] -> [b]
> map3 f = foldr (\x xs -> f x : xs) []

> all1 :: (a -> Bool) -> [a] -> Bool 
> all1 f = foldr (\x xs -> f x && xs) True 

> sum1 :: [Int] -> Int 
> sum1 [] = 0
> sum1 (x:xs) = x + (sum1 xs)

> test1 :: [a] -> [a]
> test1 = foldr (\x xs -> [x] ++ xs) []

> test2 :: [a] -> [a]
> test2 = foldl (\xs x -> xs ++ [x]) []
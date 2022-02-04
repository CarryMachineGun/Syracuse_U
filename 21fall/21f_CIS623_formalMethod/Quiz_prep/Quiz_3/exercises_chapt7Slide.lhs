> -- super :: (a -> Bool) -> (a -> b) -> [a] -> [b] 
> super1 g f xs = map f (filter g xs)


> map1 f = foldr f []   

> map2 f = foldr (\x xs  -> f x : xs) []   


> add1 = (\x y -> x + y)



> map3 f = foldr (\x y -> [f x] ++ y ) []   

> fliter1 f = foldr (\x xs -> if f x then x : xs else xs) []
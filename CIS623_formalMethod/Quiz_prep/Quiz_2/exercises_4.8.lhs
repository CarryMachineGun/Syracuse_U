> -- 1

> halve1 :: [a] -> ([a],[a])
> halve1 ns = (left, right)
>  where 
>   left = [x | x <- take (div (length ns) 2) ns]
>   right = [x | x <- drop (div (length ns) 2) ns]

> halve2 :: [a] -> ([a],[a])
> halve2 ns = (take n ns, drop n ns)
>  where n = div (length ns) 2

> --2.

> third4 :: [a] ->a
> third4 ns = ns !! 2

> third1 :: [a] -> a
> third1 ns = (head . tail . tail) ns

> third2 :: [a] -> a
> third2 (_:_:c:ns) = c

> third3 :: [a] -> a
> third3 ns = ns !! 2

> --3.

> safetail1 :: [a] -> [a]
> safetail1 [] = []
> safetail1 (n:ns) = ns

> safetail2 :: [a] -> [a]
> safetail2 ns = 
>  if null ns then []
>  else tail  ns

> safetail3 :: [a] -> [a]
> safetail3 ns 
>  | null ns = []
>  | otherwise  = tail ns


> ------- 4
> or1 :: Bool -> Bool -> Bool 
> or1 a b 
>  | a  = True 
>  | b  = True 
>  | otherwise = False  


> or2 :: Bool -> Bool -> Bool 
> or2 True True = True 
> or2 True False = True 
> or2 False True = True 
> or2 False False = False 


> or3 :: Bool -> Bool -> Bool 
> or3 False False = False 
> or3 _ _ = True 


> -- 5. 
> and1 :: Bool  -> Bool  -> Bool 
> and1 n s = 
>  if n == False then False else 
>   if s == False then False else True 

> and2 :: Bool  -> Bool  -> Bool 
> and2 n s = 
>  if n then
>   if s then True 
>   else False 
>  else False 

> and3 :: Bool  -> Bool -> Bool
> and3 n x = 
>  if n && x then True 
>  else False 

> and4 :: Bool  -> Bool -> Bool
> and4 True True = True 
> and4 _ _ = False 

> -- 6 
> opt1 :: Bool -> Bool -> Bool 
> opt1 n x =
>  if x == False then False 
>  else 
>   if n == False then False 
>   else True 

> -- 7
> mult1 :: Int -> Int -> Int -> Int 
> mult1 = \x -> (\y -> (\z-> (x*y*z))) 

> add1 :: Int -> Int -> Int 
> add1 = \x -> (\y -> (x + y))

> concat1 :: [[a]] -> [a]
> concat1 xss = [x | xs<- xss, x <- xs]

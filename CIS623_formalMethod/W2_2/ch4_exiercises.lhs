> --safetail :: [ns] -> [ns]
> --safetail ns |null ns = []
> --            |otherwise = tail ns

> safetail :: [ns] -> [ns]
> safetail [] = []
> safetail (_:ns) = ns 

> halve :: [a] -> ([a],[a])
> halve xs = splitAt (div (length xs) 2) xs

> or1 :: Bool -> Bool -> Bool
> or1 False _ = False
> or1 _ False = False
> or1 _ _ = True

> and1 :: Bool -> Bool -> Bool
> and1 a b = if a == False then False else 
>   if b == False then False else True
> f1 x = until ((== 55) . (* 11)) (+1) x

> f2 x = until ((== 0) . (`mod` 11)) (+1) x

> --f3 x = until ( (even) `&&` (== 6)) (+1) 1

> floor1 x = until (`leq` x) (subtract 1) (-1)
>  where m `leq` x = fromInteger m <= x

> floor2 x = until (x `lt`) (+1) 1 -1
>  where f `lt` n = f < fromInteger n

> f4 = iterate (tail) [1,2,3,45,6,7]

> f5 = iterate ((* 3) . (+1)) 10 

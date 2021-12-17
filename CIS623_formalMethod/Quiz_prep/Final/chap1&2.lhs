> a = False

> b = [1,2,3,4,5]

> c = [False,True]

> d = (True, 1)

> f = [(True, 2), (False, 4)]

> g = ([True, False], ['a', '2'], (2, False))

> take1 :: Int  -> [b] -> [b]
> take1 _ [] = []
> take1 0 _ = []
> take1 n (x:xs) = [x] ++ (take1 (n-1) xs)

> plus1 :: Num a => a -> a -> a
> plus1 x y = x + y

> h :: [Char]
> h = ['a', 'b']

> i :: (Char, Char)
> i = ('a', 'b')

> j :: [([a] -> [a])]
> j = [tail, init, reverse]

> k :: ([Bool], [Char])
> k = ([False, True], ['0', '2'])

> copy1 :: a -> (a,a)
> copy1 x = (x,x)

> apply1 :: (a -> b) -> a ->b
> apply1 f x = (f x)

> quickSort :: Ord a => [a] -> [a]
> quickSort [] = []
> quickSort [x] = [x]
> quickSort (x:xs) = (quickSort l) ++ [x] ++ (quickSort r)
>  where
>   l = [n | n <- xs, n <= x] 
>   r = [n | n <- xs, n > x] 

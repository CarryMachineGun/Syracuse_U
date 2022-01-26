cartesian product

> cp :: [[a]] -> [[a]]
> cp [] = [[]]
> cp (xs:xss) = [x:ys | x <- xs, ys <- yss]
>			where yss = cp xss

cp [[1,2],[],[4,5]]

cp [[1],[2],[3]]

cp [[1,2],[3,4]]

cp [[1,2],[3,4],[5,6]]
= cp ([1,2]: [[3,4], [5,6]])
= [x:ys | x <- [1,2], ys <- yss]
	where yss = cp [[3,4], [5,6]]
= [x:ys | x <- [1,2], ys <- [[3,5], [3,6], [4,5], [4,6]]]
= [1:[3,5], 1:[3,6], ..., 2:[3,5], ...,2:[4,6]]
= [[1,3,5],[1,3,6],[1,4,5],[1,4,6],[2,3,5],[2,3,6],[2,4,5],[2,4,6]]

cp [[3,4], [5,6]]
= cp ([3,4]:[[5,6]])
= [x:ys | x <- [3,4], ys <- yss]
	where yss = cp [[5,6]]
= [x:ys | x <- [3,4], ys <- [[5], [6]]]
= [3:[5], 3:[6], 4:[5], 4:[6]]
= [[3,5], [3,6], [4,5], [4,6]]

cp [[5,6]]
= cp ([5,6]:[])
= [x:ys | x <- [5,6], ys <- yss]
	where yss = cp []  -- cp [] = [[]]
= [x:ys | x <- [5,6], ys <- [[]]]
= [5:[], 6:[]]
= [[5], [6]]  
	
-------------------------------------------------------------

foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f e [] = e
foldr f e (x:xs) = f x (foldr f e xs)

e is the identity value of function f
for example, 0 for (+), 1 for (*), [] for (++)
f e p = p


sum = foldr (+) 0
concat = foldr (++) []
filter p = foldr (\x xs -> if p x then x:xs else xs) []
map f = foldr ((:) . f) []
length = foldr (\_ n -> 1+n) 0

To rewrite a function using foldr:
1. Find what is e - foldr f e [] = e
2. Use a simple example to find out what is f, 
   f may be a lambda function
   
---------------------------------------
higher order function
a function that takes function as input
like foldr, map, filter, all, any etc.  

Show how the list comprehension [f x | x <- xs, p x] can be re-expressed using the higher 
order functions map and filter.

map f (filter p xs)
filter p xs first filer out the elements which make p x = True
map f will apply f on every satisfying element






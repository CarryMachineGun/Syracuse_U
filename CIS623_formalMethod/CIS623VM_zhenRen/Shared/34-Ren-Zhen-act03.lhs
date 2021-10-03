Activity 3
Student No:34
Last Name:Ren
First Name:Zhen

---------------------------
If we want to use comparsion operations,like <=, we are required to  make a the derived Ord instance. For the insert function, we could just insert the elment if the list is empty. We should insert x when x is larger than the element in the ordered list,which makes the list ordered.

> insert :: (Ord a) => a-> [a] -> [a]
> insert x []=[x] --insert 1.1
> insert x (y:ys)
>     | x<=y      = (x:y:ys) -- insert 2.1
>     | otherwise = y:(insert x ys) -- insert 2.2

isort function based on the insert function to finish ordering. We recursively call the insert function to make the list empty, which meets the first pattern matching. Then we could orderedly insert element into the list due to the insert function.


> isort :: (Ord a) => [a] -> [a]
> isort []     = [] --isort 1
> isort (x:xs) = insert x (isort xs) -- isort 2


isort1 is the same function as the isort. Its main purpose is to illustrate the insert1 can not be called directly, if we define it inner the function. 

> isort1 :: (Ord a) => [a] -> [a]
> isort1 [] = []  -- isort 1
> isort1 (x:xs) = insert1 x (isort1 xs)
>     where
>       insert1 :: (Ord a) => a -> [a] -> [a]
>       insert1 x [] = [x] -- isort 2.1
>       insert1 x (y:ys) 
>           | x==y = (x:y:ys) -- isort 3.1
>           | otherwise = y:(insert1 x ys) --isort 3.2

msort function split up the list into left and right, both have a half elments of the original list.And call merge function to merge them up.

> msort :: (Ord a) => [a] -> [a]
> msort [] = [] -- msort 1
> msort [x] =[x] -- msort 2
> msort  xs =merge (msort left) (msort right)--msort 3
>             where
>               left=take((length xs) `div` 2) xs 
>               right=drop((length xs) `div` 2) xs

merge function mainly merge the two lists and compare the two lists' elments at the same time. We merge the ordered  elments up .

> merge :: (Ord a) =>[a]->[a]->[a]
> merge [] lst = lst --merge 1
> merge lst [] = lst --merge 2
> merge (x:xs) (y:ys) 
>     | x<y   = x:merge xs (y:ys) --merge 3.1
>     | otherwise=y:merge (x:xs) ys -- merge 3.2

Feijen's notation:
a. insert 3 [1,1,2,3,5,9]={insert 2.2}
=1:insert 3 [1,2,3,5,9]={insert 2.2}
=1:1:insert 3 [2,3,5,9]={insert 2.2}
=1:1:2:insert 3 [3,5,9]={insert 2.2}
=1:1:2:3 insert 3 [5,9]={insert 2.1}
=[1,1,2,3,3,5,9]

b. isort [53,9,2,6,19]={isort 2}
=insert 53 isort [9,2,6,19]={isort 2}
=insert 53 insert 9 isort [2,6,19]={isort 2}
=...
=insert 53 insert 9 insert 2 insert 6 insert 19={insert 1.1}
=insert 53 insert 9 insert 2 insert 6 [19]={insert 2.1}
=insert 53 insert 9 insert 2 [6,19]={insert 2.1}
=insert 53 insert 9 [2,6,19]={insert 2.2}
=insert 53 2:insert 9 [6,19]={insert 2.2}
=insert 53 2:6:insert 9 [19]={insert 2.1}
=insert 53 [2,6,9,19]={insert 2.2}
=...
=[2,6,9,19,53]

b. msort [53,9,2,6,19]={msort 3}
=merge msort [53,9] msort [2,6,19]={msort 3}
=merge merge msort[53] msort[9] merge msort[2] merge [6,19]={msort 2 msort3}
=...
=merge merge [53] [9] merge [2] merge [6] [19]={merge 3.1 merge 3.2}
=merge [9,53] merge [2] [6,19]={merge 3.1}
=merge [9,53] [2,6,19]={merge 3.2}
=2:merge [9,53] [6,19]={merge 3.2}
=2:6:merge [9,53] [19]={merge 3.1}
=...
=[2,6,9,19,53]


> insert2 :: Ord a => a -> [a] -> [a]
> insert2 x [] = [x]
> insert2 x (n:ns) 
>  | n >= x = x:n:ns
>  | otherwise = n : (insert x ns)

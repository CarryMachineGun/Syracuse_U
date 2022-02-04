Activity 2
Student No:34
Last Name:Ren
First Name:Zhen

>dropodd :: [a] -> [a] --define the type
>dropodd [] =[]--using pattern matching deals with the empty input list
>dropodd [x] = []--using pattern matching deals with the one element list,which will be dropped. Because 1 element is odd.
>dropodd (x:y:zs) = (y:dropodd zs)--using pattern matching deals with two or more elements as input. Firstly,we drop the odd element x,and save the even element y.Then we could recall the dropodd function to drop the next odd element. After finishing the recursion function, all the odd elements will be dropped. By the way, zs can be [] and odd means odd locations in the list, like 1st 3rd and 5th.


>getkeyvalue :: (Eq k)=>k->[(k,v)]->[v]--define the type of function. Due to == operation belongs to Eq class. We can not use == operation without importing the Eq class. We can use :t (==) find its defination
>getkeyvalue a [] = []--using pattern matching deals with empty input list
>getkeyvalue a ((x,y):zs)--using pattern matching to deal with list with elements. And we split up the element of x,y,zs.
>            | (a == x) =y:(getkeyvalue a zs)--if a equals to x that means we find our key and y is our needed value. Then we recall the getkeyvalue to find the next key and value in the left list. 
>            | otherwise = getkeyvalue a zs -- a do not equal to x . we just recall the getkeyvalue to find the next key and value in the left list.

--The whole function helps us to find all the value where k equals to k,we use pattern matching and recursion solving  the problem
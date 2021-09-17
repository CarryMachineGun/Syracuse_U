---------------------------------------------------------------------------
Fall 2021 CIS 623
Activity 2
---------------------------------------------------------------------------

Lastname :  < Wang >
Firstname:  < Yuchen > 
Stud. num:  < 530 >

---------------------------------------------------------------------------

1. The reverse1 function

In the space provided below, write a version of the reverse function,

reverse1

using the function (++) as a main helper. Give a concise description
of the function together with the code.

-- Put your description here
Input a list, output the reverse of the list

reverse1 [3,5,2]
= { applying reverse1 }
reverse1 [5,2] ++ [3] 
= { applying reverse1 }
(reverse1 [2] ++ [5]) ++ [3] 
= { applying reverse1 }
((reverse1 [] ++ [2]) ++ [5]) ++ [3] 
= { applying reverse1 }
(([] ++ [2]) ++ [5]) ++ [3] 
= { applying ++ }
([2] ++ [5]) ++ [3] 
= { applying ++ }
[2,5] ++ [3] 
= { applying ++ }
[2,5,3] 

> -- Put your code there
> reverse1 :: [a] -> [a] 
> reverse1 [] = []
> -- push head node of the list and sublists to the very right
> reverse1 (n : ns) = reverse1 ns ++ [n]


---------------------------------------------------------------------------

2. the first1 function


In the space provided below, write a version of the fst function, 

first1

and include a short description for the function.

-- Put your description here
Input a tuple, output the first element of the tuple

first1 (1,2)
= { applying first1}
1

> -- Put your code there
> first1 :: (a,b) -> a 
> first1 (x,y) = x


---------------------------------------------------------------------------

3. the move function

In the space provided below, write the move function as described by
the instructor. Include a short description for the function.

-- Put your description here
Input a tuple of list, output a tuple of list which the first element of the second list is move to the head of the 
first list

move ([1,2], [3])
= { applying move }
([3,1,2],[])

> -- Put your code there
> move :: ([a],[a]) -> ([a],[a])
> move (xs,[]) = (xs,[]) 
> move (xs,(y : ys)) = ((y : xs), ys)


---------------------------------------------------------------------------

4. the transfer function  

In the space provided below, write the transfer function as described by
the instructor. Include a short description for the function.

-- Put your description here
Input a tuple of list, output a tuple of list which the first list is the combination of reverse of 
the second list and the first list, the second list is a empty list

transfer ([1,2], [3])
= { applying transfer }
transfer(move ([1,2],[3]))
= { applying move }
transfer([3,1,2],[])
= { applying transfer }
([3,1,2],[])


> -- Put your code there
> transfer :: ([a],[a]) -> ([a],[a])
> transfer (xs,[]) = (xs,[])
> transfer (xs, ys) = transfer(move (xs,ys))  


---------------------------------------------------------------------------

5. the reverse2 function

In the space provided below, write the transfer function in point free 
style as described by the instructor. Include a short description for 
the function.


-- Put your description here

Input a list, output the reverse of the list

reverse2 [3,2]
= { applying reverse2 }
first1( transfer ([],[3,2] ) )
= { applying transfer }
first1( transfer (move ([],[3,2])))
= { applying move }
first1( transfer ([3],[2]))
= { applying transfer }
first1( transfer ( move ([3],[2])))
= { applying move }
first1( transfer ([2,3],[]))
= { applying transfer }
first1([2,3],[])
= { applying first1 }
[2,3]

> -- Put your code there
> reverse2 :: [a] -> [a]
> reverse2 ns = first1 (transfer ([],ns))


---------------------------------------------------------------------------


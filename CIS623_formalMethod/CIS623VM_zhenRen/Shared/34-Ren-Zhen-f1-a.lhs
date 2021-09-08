CIS 623 Spring 2021 Final examination

version       A

Last name:  Ren
First name: Zhen

SU-email: zren08@syr.edu

Acknowledgement:

By submitting this file (my answers to this final examination), 
I acknowledge that I accept the terms as stated in the rules section 
of the examination document.

Note:

Rename this file as 

XX-Lastname-Firstname-623-Final-A-Y.lhs

BEFORE your attempting the test. XX is the student number assigned
to your for this class and Y is the version of the test.  For example, 
if my student number is 50 and is taking version A, then my submission 
should  be named as 50-Lee-Andrew-623-Final-A-A.lhs


----------------------------------------------------------------------

----------------------------------------------------------------------
PUT YOUR ANSWERS TO THIS TEST IN THE SPACE PROVIDED BELOW. 
----------------------------------------------------------------------

Question 1 (Total: 25 point)

a. (10 point)

>fixedpt::(Eq a)=>(a->a)->a->Int
>fixedpt f n
>        |(x==(f n))=1
>        |otherwise=1+ fixedpt f (f n)

>converge::(Eq a)=>(a->a)->a->Int->Bool
>converge f x n
>         |((fixedpt f x)<=n)=False
>         |otherwise =True

b. (15 point)

>noofsteps::(Eq a)=>[a]->Int
>noofsteps []=0
>noofsteps x:[]=1
>noofsteps (x:y:zs)
>          |x==y=1
>          |otherwise=1+noofsteps (y:zs)




-- End of Question 1
---------------------------------------------------

Question 2 (Total: 20 point)

Example code referenced in exam is stated below:

> infix @@
> (@@) = max1

> max1 :: Int -> Int -> Int       -- use it to define the operator @@
> max1 x y = 0 `max` (x+y)
> 

> mss1 :: [Int] -> Int            -- An O(n) solution to MSS problem
> mss1 = maximum . (scanr (@@) 0)

>infix $$
>($$)=max2

>max2::[Int]->Int->[Int]
>max2 (x:xs) y=((max 0 (x+y)):x:xs)






-- End of Question 2
---------------------------------------------------

Question 3 (Total: 20 point)

> data Expr = Val Int | App Op Expr Expr
> data Op   = Add | Mul  -- represent addition and multiplication accordingly

a.
>eg1::Expr
>eg1=App Add (Val 1) (Val 2)

>eg2::Expr
>eg2=Val 3

>eg3::Expr
>eg3=App Mul (Val 4) (Val 5)


b.

>eval::Expr->Int
>eval (Val x)=x
>eval (App Add x y)=(eval x)+(eval y)
>eval (App Mul x y)=(eval x)*(eval y)

testcase1 eval eg1 
output:3

testcase2 eval eg3
output:20

>values::Expr->[Int]
>values (Val x)=[x]
>values (App Add x y)=(values x)++ (values y)
>values (App Mul x y)=(values x)++(values y)

testcase3 values eg2
output:[3]

testcase4 values eg3
output:[4,5]


-- End of Question 3
---------------------------------------------------

-- End of Part A of the Final
--------------------------------------------------- 
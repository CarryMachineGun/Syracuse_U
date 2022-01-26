CIS 623 Spring 2021 Test 2 

version       A

Last name:  Ren
First name:  Zhen

SU-email: zren08@syr.edu

Acknowledgement:

By submitting this file (my answers to final examination, part 2), 
I acknowledge that I accept the terms as stated in the rules section 
of the examination document.

Note:

Rename this file as 

XX-Lastname-Firstname-623t2y.lhs

BEFORE your attempting the test. XX is the student number assigned
to your for this class and y is the version of the test.  For example, 
if my student number is 50 and is taking version A, then my submission 
should  be named as 50-Lee-Andrew-623t2A.lhs


----------------------------------------------------------------------
PUT YOUR ANSWERS TO THIS TEST IN THE SPACE PROVIDED BELOW. 
----------------------------------------------------------------------

Question 1 (Total: 20 point)

a. (15 point)

>fixedpt::(Eq a)=>(a->a)->a->a
>fixedpt f x 
>            |(f x)==x   =x
>            |otherwise=fixedpt f (f x)


b. (5 point)

> safetail    :: [a] -> [a]
> safetail []     = []
> safetail (x:xs) = xs

fixedpt safetail [1..3]
={.. defiation}
fixedpt safetail [1,2,3]
={safetail.2 fixedpt.2} [2,3]/=[1,2,3]
fixedpt safetail [2,3]
={safetail.2 fixedpt.2} [3]/=[2,3]
fixedpt safetail [3]
={safetail.2 fixedpt.2} [3]/=[]
fixedpt safetail []
={safetail.2} []==[]
[]




-- End of Question 1
---------------------------------------------------

Question 2 (Total: 20 point)

a. (10 point)

>applyfunsa:: [a->b]->a->[b]
>applyfunsa [] x =[]
>applyfunsa (f:fs) x=(f x):(applyfunsa fs x) 


b. (10 point)

>applyfunsb::[a->b]->a->[b]
>applyfunsb fs x =map (\x->f x) fs


-- End of Question 2
---------------------------------------------------

Question 3 (Total: 20 point)

> data Shapes = Circle Float | Rect Float Float | Tri Float Float Float
>               deriving  Show

a.

>dropcircle::[Shapes]->[Shapes]
>dropcircle []=[]
>dropcircle ((Circle a):xs)= dropcircle xs
>dropcircle ((Rect a b):xs)=(Rect a b):(dropcircle xs)
>dropcircle ((Tri a b c):xs)=(Tri a b c):(dropcircle xs)


b.

>selectcircle::[Shapes]->[Shapes]
>selectcircle []=[]
>selectcircle ((Circle a):xs)=(Circle a):(selectcircle xs)
>selectcircle ((Rect a b):xs)=selectcircle xs
>selectcircle ((Tri a b c):xs)=selectcircle xs



-- End of Question 3
---------------------------------------------------

Question 4 (Total: 20 point)


> data LIT = Var Char | NVar Char
>          deriving Show

> type DJS = [LIT]
> type CNF = [DJS]

> type Subst     = Assoc Char Bool
> type Assoc k v = [(k,v)]

> find     :: Eq k => k -> Assoc k v -> v
> find k t = head [ v | (k',v) <- t, k == k']

> eg :: CNF
> eg = [[Var 'a'], [NVar 'b']]


a.

>phi1::CNF
>phi1 =[[[Var 'p'],[NVar 'q']],[[NVar 'p'],[NVar 'q']]]

>phi2::CNF
>phi2 =[[[Var 'p'],[NVar 'q']],[[NVar 'p'],[Var 'q']]]


b.

>evalcnf::Subst->CNF->Bool
>evalcnf s (Var 'x')= find 'x' s
>evalcnf s (NVar 'p')=not (evalcnf s (Var 'p'))

-- End of Question 4
--------------------------------------------------- 
Student No:34
Last Name:Ren
First Name:Zhen

Question1:
(a):
The universal property of fold has its origins in recursion theory. In the functional programming of Malcolm, to finite lists, the universal property of fold can be stated as the following equivalence between two definiations for a function g that:
g []= v
x (x:xs)=f x (g xs)
->
g= fold f v

The key of universal property is that  it makes explicit the two assumptions required for a certain pattern of inductive proof. For the specific cases, we can verify the two assumptions (which can typically be done without the need for induction) we can then appeal to the universal property of fold encapsulates a simple pattern of inductive proof conceriing lists, as the fold operator itself encapsulates a simple pattern of recursion for processing lists.


(b):
the appication of the universal property of fold is as a proof principle that avoids the need for inductive proofs. As a simple first example, consider the following equation:
(3*).product=fold (*) 3
by using the right-hand side g=fold f v with g=(3*). product,f=(*),v=3. 
Hence, 
((*3).product) []=3
((*3).product) (x:xs)=(*) x (((*3).product) xs)
simplifying using the definitions of composition and sectioning gives
product [] *3 =3
product (x:xs) *3 =x *(product xs * 3)

product [] * 3 = {Definition of product}
1*3={arithmetic}
3
product (x:xs) *3={Definition of product}
(x* product xs) *3={Arithmetic}
x*(product xs * 3)

Question2:
(a):
product::[Int]->Int
product []=1
product (x:xs)=x * product xs

We begin by observing that the equation matches the right-hand side of the universal property, from which we conclude that the equation is equivalent to the following two equations:
product []=v
product (x:xs)=f x (product xs)

From the first equation and the definition of product, it is immediate that v=1. From the second equation, we calculate a defintion for f as follows:

product (x:xs)=f x (product xs)     ={Definition of product}
x * product xs=f x (product xs)     ={Generalising (product xs) to y}
x*y=f x y                           ={Functions}
f= (*)
So,
product=fold (*) 1

(b):
and::[Bool]->Bool
and []=True
and (x:xs)=x (&&) and xs

We begin by observing that the equation matches the right-hand side of the universal property, from which we conclude that the equation is equivalent to the following two equations:

and []=v
and (x:xs)=f x (and xs)
From the first equation and the definition of product, it is immediate that v=True. From the second equation, we calculate a defintion for f as follows:

and (x:xs)=f x (and xs)        ={Definition of and}
x (&&) and xs=f x (and xs)     ={Generalising (and xs) to y}
x (&&) y=f x y                 ={Functions}
f= (&&)
So,
and=fold (&&) True


Question3:
(a):
Based on the universal property of fold we have calculated-without an explicit use of induction- two simple conditions that are togther sufficient to ensure for all finite lists that the composition of an arbitary function and a fold can be fused together to give a single fold. So this property is called fusion property of fold operator, and can be stated as follows:
h w = v
h (g x y)=f x (h y)
->
h.fold g w=fold f v

(b):
(⊕ a). fold (⊕) b=fold (⊕) (b ⊕ a)
Using the universal property of fold to calculate conditions under which equation will indeed be true. The equation matches the right-hand side of the universal property from  which we conclude that the equation is equivalent to the following two equations:
((⊕ a). fold (⊕) b) []=(b ⊕ a)
((⊕ a). fold (⊕) b) (x:xs)=(⊕) x ((⊕ a).fold (⊕) b xs)
Simplifying using the defintion of compostion gives
(⊕) a (fold (⊕) b [])=(b (⊕) a)
(⊕) a (fold (⊕) b (x:xs))=(⊕) x (⊕) a (fold (⊕) b xs)
which can now be further simplified by two caluctions:
(⊕) a (fold (⊕) b [])=(b (⊕) a)        ={defintion of fold}
(⊕) a b=(b (⊕) a)
and 
(⊕) a (fold (⊕) b (x:xs))=(⊕) x (⊕) a (fold (⊕) b xs)  
={definition of fold}
(⊕) a ((⊕) x (fold (⊕) b xs))=(⊕) x ((⊕ a) (fold (⊕) b xs))
={generatlising (fold (⊕) b xs) to a fresh variable y}
(⊕) a (⊕ x y)=(⊕) x (⊕ a y)
Using the universal property of fold we have calculated-without an explicit use of induction- two simple conditions that are together sufficient to ensure for all finite lists that the composition of an arbitrary function and a fold can be fused together to give a single fold. Following this interpretation, this property is called the fusion proerty of the fold operator, and can be stated as follows:
(⊕) a b= (b (⊕) a)
(⊕) a (⊕ x y)=(⊕) x ((⊕ a) y)
->
(⊕ a). fold (⊕) b=fold (⊕) (b ⊕ a)

(c):
double.sum=fold ((+).double) 0
First, we replace the fuction sum
double.fold (+) 0=fold ((+).double) 0
According to the fusion property, from which we conclude that the equation follows from the following two assumptions:
double 0=0
double ((+) x y)=((+).double) x (double y)
Simplifying these equations using the definition  of sectioning gives double 0=0 and double ((+) x y)=((+).double) x (double y), which are true by simple properties of arithmetic
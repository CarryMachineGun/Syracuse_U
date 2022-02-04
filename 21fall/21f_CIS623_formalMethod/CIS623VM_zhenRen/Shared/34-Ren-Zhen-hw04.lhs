hw04
Student No:34
Last Name:Ren
First Name:Zhen

Problem1

>import Prelude hiding (exp,reverse)

>data Nat= Zero
>         |Succ Nat

>exp::Num a=>a->Nat->a
>exp x Zero =1                    --exp.1
>exp x (Succ n)=x * exp x n       --exp.2


proof:
P(n):exp x (m+n)=exp x m * exp x n

1.P(0) holds
Case 0:
exp x (m+0)
={since m+0=m}
exp x m

exp x m * exp x 0
={exp.1}
exp x m * 1
={since x * 1 =x}
exp x m

2.P(n+1) holds assuming that P(n) does.
Case n+1:
exp x (m+(n+1))
={arithmetic}
exp x ((m+n)+1)
={exp.2}
x * exp x (m+n)
={induction}
x * (exp x m * exp x n)

exp x m * exp x (n+1)
={exp.2}
exp x m * (x * exp x n)
={since * is associative}
x * exp x m * exp x n

By using induction proofs, the proof holds.

problem2:

>reverse :: [a]->[a] ---(*)
>reverse []=[] ---r.1
>reverse (x:xs)= reverse xs ++ [x] ---r.2


2.1 Motivation:
First of all, it is obvious that the number of reduction steps required to evaluate xs ++ ys is one greater than the length of xs,  just for implicity both xs and ys already fully evaluated. So, ++ would take linear time in the length of its first argument. In turn, the number of steps required by reverse xs for a list of length can be shown to be the sum of the integers from 1 to n+1, which is (n+1)(n+2)/2. Mutiplying out these brackets using the equation verified at the start, which gives (n"2+3n+2)/2, so the reverse function would take quadratic time inthe length of its argument.
However, we could use induction to eliminate the use of append in the defination of reverse, and hence improve its efficiency.

2.2 Guess

>g::[a]->[a]->[a]
>g [] ys = ys
>g (x:xs) ys =g xs (x:ys)

2.3 Specification

>reverse2::[a]->[a]
>reverse2 xs=g xs []

2.4 Apply
the defination of concatenation (++):
[]++ys=ys
(x:xs) ++ ys = x:(xs++ys)

defincation of reverse:
reverse [] =[]
reverse (x:xs)= reverse xs ++ [x]

Base Case:
1.P([]) holds.
2.For all x and for all finite lists xs, P (x:xs) holds when P(xs) holds.

The base case results in an equation that gives the definition for g [] ys, while the inductive cases result in an equation that gives the definition of g (x:xs) ys

2.5
Base case:
g [] ys
={specification of g}
ys

reverse []++ys
={using reverse}
[]++ys
={using ++}
ys

Inductive case:
g (x:xs) ys
={specification of g}
g xs (x:ys)

reverse (x:xs)++ ys
={using reverse}
(reverse xs ++[x])++ys
={associativity of ++}
reverse xs ++ ([x] ++ ys)
={induction hypothesis holds}
g xs ([x]++ys)
={using ++}
g xs (x:ys)
 

2.6
The new definition for reverse2 is much more efficient. In paticular, the number of reduction steps required to evaluate reverse2 xs for a list of length n using the new definition is simply n+2, and hence reverse2 now takes linear time inthe length of its argument.
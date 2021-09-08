CIS 623 Spring 2021 Final examination

version       A

Last name:  Ren
First name:  Zhen

SU-email: zren08@syr.edu

Acknowledgement:

By submitting this file (my answers to this final examination), 
I acknowledge that I accept the terms as stated in the rules section 
of the examination document.

Note:

Rename this file as 

XX-Lastname-Firstname-623-Final-B-Y.lhs

BEFORE your attempting the test. XX is the student number assigned
to your for this class and Y is the version of the test.  For example, 
if my student number is 50 and is taking version A, then my submission 
should  be named as 50-Lee-Andrew-623-Final-B-A.lhs


----------------------------------------------------------------------

----------------------------------------------------------------------
PUT YOUR ANSWERS TO THIS TEST IN THE SPACE PROVIDED BELOW. 
----------------------------------------------------------------------

Question 4 (Total: 18 point)

> data Nat = Zero | Succ Nat
      
> add           :: Nat -> Nat -> Nat
> add Zero y     = y   --add.1
> add (Succ x) y = Succ (add x y)  -- add.2

We have already know thing about Succ n

Case 0:
add  Zero (add y z)={outer add}
=add y z={unapplying add}
=add (add Zero y) z

Inductive case:
add (Succ x) (add y z)={outer add}
=Succ (add x (add y z))={induction hypothesis}
=Succ (add (add x y) z)={unapplying outer add}
=add (Succ (add x y) z)={unapplying the inner add}
=add (add (Succ x) y) z)



-- End of Question 4
---------------------------------------------------

Question 5 (Total: 17 point)

a.
> fold            :: (a -> b -> b) -> b -> ([a] -> b)
> fold f v []     = v
> fold f v (x:xs) = f x (fold f v xs)

f ::  r -> s -> s
v ::  s
g ::  r -> s -> s
w ::  s
h ::  s -> s
x :: s
y :: s

And the fusion property of fold state that:

h w        = v           -- fusion.1
h (g x y)  = f x (h y)   -- fusion.2
->
h . fold g w = fold f v    -- fusion 3

b.
(<+>1 a) . fold (<+>2) b = fold (<+>2) (b (<+>1) a)        


Firstly,
f: (<+>2)        -- d.1
v: (b (<+>1) a)  -- d.2       
g: (<+>2)        -- d.3   
w: b            -- d.4
h: (<+>1 a)      -- d.5

According to fusion 1 and 2
      
verify  fusion.1

LHS
={fusion.1}
h w        
={d.4 and d.5}
(<+>1 a) b
={property of the <+> operator}
b <+>1 a
={d.2}
v
={fusion.1}  
         
RHS
Hence fusion.1 holds 
verify fusion.2
LHS
={fusion.2}
h (g x y)  
= {d.5 and d.3}
(<+>1 a) ((<+>2) x y)
={<+>1 <+> is infix operator2}
(<+>1 a) (x <+>2 y)
= {property of (<+>1 a)}
((x <+>2 y) <+>1 a) 

RHS
={fusion.2}
f x (h y) 
={d.1 and d.5}
(<+>2) x ((<+>1 a) y)
={property of (<+>2 a)}
(<+>2) x (y <+>1 a)
={property of (<+>2)}
x <+>2 (y <+>1 a)
={<+>1 <+>2 are different}
RHS/=LHS

Hence fusion.2 not holds.
  

-- End of Question 5
---------------------------------------------------
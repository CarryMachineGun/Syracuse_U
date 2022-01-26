No: 34
Last Name:Ren
First Name:Zhen

1.Define (mathematically) a sub-collection of propsitional formula, S, as follows:

Defination:

1.Every x (of type Char) is a S.
2.If x is a S, then Not x is also a S.
3.If x and y are S's, then And x y is also a S.


2.define the datatype

>data S= Var Char
>      | Not S
>      | And S S

q1 is to represent the formula ("s" and "t" both are S's)

>q1 :: S
>q1 =And (Var 's') (Var 't')

q2 is to represent the Not s is a S's

>q2 :: S
>q2 =Not (Var 's')

>q3 :: S
>q3 =And (Not (Var 's')) (Var 't')

>q4 :: S
>q4 =And (Var 's') (Not (Var 't'))

>q5 :: S
>q5 =And (And (Var 's') (Var 't')) (Var 'x')

3.manipulate formula.

>noOfAnds :: S->Int
>noOfAnds (Var x)= 0
>noOfAnds (Not p)= noOfAnds p
>noOfAnds (And p q)= 1 + (noOfAnds p) + (noOfAnds q)


4.test cases.
q1 has 1 And
q2 does not have And
q3 has 1 And
q4 has 1 And
q5 has 2 Ands

*Main>noOfAnds q1
1
*Main>noOfAnds q2
0
*Main>noOfAnds q3
1
*Main>noOfAnds q4
1
*Main>noOfAnds q5
2
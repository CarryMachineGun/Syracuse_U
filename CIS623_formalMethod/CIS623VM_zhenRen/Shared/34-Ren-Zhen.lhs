CIS 623 Spring 2021 Test 1 

version       A

Last name:  Ren
First name: Zhen

SU-email: zren08@syr.edu

Acknowledgement:

By submitting this file (my answers to final examination, part 2), 
I acknowledge that I accept the terms as stated in the rules section 
of the examination document.

Note:

Rename this file as 

XX-Lastname-Firstname-623t1.lhs

BEFORE your attempting the test. XX is the student number assigned
to your for this class. For example, if my student number is 50, 
then my submission should be named as 50-Lee-Andrew-623t1.lhs


----------------------------------------------------------------------
PUT YOUR ANSWERS TO THIS TEST IN THE SPACE PROVIDED BELOW. 
----------------------------------------------------------------------

Question 1  (20 point)

>insertLast2 ::a->[a]->[a]
>insertLast2 x []=[] --1.1
>insertLast2 x [y]=[x,y]--1.2
>insertLast2 x (y:ys)=y:insertLast2 x ys    --1.3

insertLast2 1 [2,0]={1.3}
=2:insertLast2 1 [0]={1.2}
=2:[1,0]
=[2,1,0]



---------------------------------------------------
-- End of Question 1
---------------------------------------------------

Question 2  (20 point)

>factors   :: Int -> [Int]
>factors n =  [x | x <- [1..n], n `mod` x == 0] 

>isprime   :: Int -> Bool
>isprime n = (n > 1) && (factors n == [1,n])

>prime::Int->[Int]
>prime k=[x|x<-[3..k],isprime x]

>gbc::Int->[(Int,Int)]
>gbc r=[(x,y)|x<-prime r,y<-prime r,x+y==r]


---------------------------------------------------
-- End of Question 2
---------------------------------------------------

Question 3  (20 point)

>part::[Int]->[([Int],[Int])]
>part [_]=[]
>part []=[]
>part (x:xs)=[(x:rs,ts)|(rs,ts)<-part xs]++[([x],xs)]


---------------------------------------------------
-- End of Question 3
---------------------------------------------------

Question 4  (20 point)

>firstpos::(Eq a)=>(a->a)->(a->a)->[a]->Int
>firstpos f g (x:xs)
>	|length [i| (x,i)<-zip ns [0..] ,f x /= g x ] > 0=head [i |(x,i)<-zip ns [0..]
>	|otherwise =-1


---------------------------------------------------
-- End of Question 4
---------------------------------------------------

Question 5  (20 point)

>rinsert::(Ord a)=>a->[a]->[a]
>rinsert x [] =[x]
>rinsert x (y:ys) 
>        |x>=y=(x:y:ys)
>        |otherwise=y:(rinsert x ys)

>rsort::(Ord a)=>[a]->[a]
>rsort []=[]
>rsort (x:xs)=rinsert x (rsort xs)



---------------------------------------------------
-- End of Question 5
---------------------------------------------------


----------------------------------------------------------------------
END OF TEST. DO NOT PUT YOUR ANSWERS TO THIS TEST IN THE SPACE BELOW. 
----------------------------------------------------------------------
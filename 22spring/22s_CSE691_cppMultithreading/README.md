# [CIS691 C++ Multithreading](https://learn-us-east-1-prod-fleet01-xythos.content.blackboardcdn.com/blackboard.learn.xythos.prod/5956621d575cd/30637535?X-Blackboard-Expiration=1643230800000&X-Blackboard-Signature=PvXglr2Qe1YVfPq%2Bhqz0hs%2FhxhPFddfLoOTauih7ecs%3D&X-Blackboard-Client-Id=311690&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%272022_01_25_CSE691_Syllabus.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEID%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJHMEUCIQCMer6%2FGhjigAwOhOFVRjWGWeQCUP%2BgT1BZ7vU7jzzuGAIgHzYLcssGc8vdWqNHNpe%2BIFfZURbhtqbeRezGe9ytSwsqgwQIqf%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FARAAGgw1NTY5MDM4NjEzNjEiDLwMYGNOP0rJuEWmGCrXA8viu0Sgu7iygrz4aa2zCkxIAZUcvZXCmP2gjiKgK%2Bzprp9y%2B%2BwWaPFt2sPOBHwlGyIqsGDDTGtTHGjqy23Yk3iuXdAlQt1nvn%2BO1RqWS3IyxeeEyBIG1unroFhZQe%2FD%2BFFW49w2G03KuuKHJpxcNzlNPEgh92w6haOIv4XPCHq69XWNG2UdpFRNMvypdRxZoG4Zfx8KpMnkG18iwE3OXWMal2cHRpi7tSkeMpiuh3VSXodjZVOjcuxQA1ubv9M8J%2FHjJlxhet8GNCOu8kIkz%2FonoXL5D2XYgZezTDLS6ul8QSALPPwL4O462dQ%2BZsmwxCgGR6vs5ei3Tr8e%2F7qabksHtHtn75tjoWz57mZm0YpDlh%2FoVs5syK7LrQzwI1B%2FaTU%2FgQsOboKStiTAS3rHtWc1lL6%2FjQFMviy8c2aWJS0chLti4Q81XDz5fVAMi4apM9%2BBhEdt8BFGz7FOAkl3e1Oj1mfXCduFD7BfvA8syQD%2FcKtOEyV%2FZOF1Eas65IRZvIzmRdjVmV5lfvBiKV52vBcSMI0s1wwh7x4mhlfekWVxxK7AD86E%2Bfo9Xn5e0uM%2BreRsc32EsUGfZ%2BzqtzTM9FLuZQQ%2FS81Cd0r7BIbw4C83nWkCRj7zXzDr0sWPBjqlAdesUbRZn43dgGYYaMKHs5LjaSq1hounQeO3WmmPQt4AngiymxYJgiMS%2Byvb274sztRtGjuGblosFVDqcMsYxMLkk1tuWsH7BpuWCA9ONK1WtmGdnH%2Fi2xLYtccoaazHtIL0bHk0w2r7oKsfWVi4zXAe9QHjgbr0rWn%2BatJMuVsihb5omrlmi6PU63zgT5oeYv7pDncsBMuEVs97Cd101Fr4e09TGA%3D%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20220126T150000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAYDKQORRY3JNMHKXB%2F20220126%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=a93d01e73006a059681fade0eda619f510d1f157347dc1e4787fb2a6f61c42fb) 

## Introduction:  

Programming techniques and approaches for synchronizing concurrent task
using C++ threads will be addressed. Develop threaded programs for applications. Will discuss
more on advanced C++ language features, such as RAII, safety, race, exceptions, etc
- **Instructor**: C-Y (Roger) Chen Email: crchen@syr.edu
- **Lecture Time**: 11:00am - 12:20pm Tuesdays & Thursdays
- **Office Location**: 4-281 CST
- **TA**: Abel Armede
- **On-Line Office Hours**: 1:30pm-2:00pm Tuesday & Thursday  

## Questions:

### Week 1

- Why we need `ref()` symbol inside the tread creating function?
  - This is the special case only needed when using mutitreading in C++
- Can we have treads on a computer exceeding the maxmium number of treads on the computer?
  -  We can have as many treads as we want in a C++ program. But only the number of treads equalling to the double of cores numbers will be truly processed in parallel
- can we put T6 as 'T6{mf1::f1, 200, ....}'

### Week 2
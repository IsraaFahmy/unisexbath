
Unisex Bathroom 

Problem:
A unisex bathroom is shared by men and women. A man or a woman may be using
the room, waiting to use the room, or doing something else. They work, use the bathroom and
come back to work. The rule of using the bathroom is very simple: there must never be a man
and a woman in the room at the same time; however, people with the same gender can use the
room at the same time

Solution:
This is a simple variation of the reader-priority readers-writers problem. More precisely,
we allow the “writers” to write simultaneously. Therefore, the writers have the same structures as
the readers. We need to maintain two counters, one for the males MaleCounter and the other for
the females FemaleCounter. Of course, we need two Mutexes MaleMutex and FemaleMutex for
mutual exclusion. In addition, there is a semaphore BathRoom to block the males (resp., females)
if the room is being used by the females (reap., males). Note that the male thread and female
thread are symmetric.





Environment
It run on linux 
argv[0] ==> source file (unisexbath.c)
argv[1] ==> males number 
argv[2] ==> females number 

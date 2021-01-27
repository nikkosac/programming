the mulproc program starts by declaring an array of string(args) a int for status(status)
and 3 pid_t variables; two for the child processes(child_a,child_a) and one for checking
which child was completed during the wait loop(wpid).

then the program forks into the first child process(child_a) via an if statement, 
if the pid_t equals zero then the child_a code will execute other wise it will continue
to the else in which the program forks again into the child_b process if it equals 0,
otherwise it will continue into the parent code. inside each of the child process
is a print and an execute function. It firsts prints which program it is going to execute
via execv(), then executes that program.

in the parent code it has a wait function in a for loop that checks if the wpid is greater than zero
if it is then it will print which process was completed, if it is zero then all the child 
processes have been terminated and thus the program can return.

OUTPUT:
Child<27459> is executing testalphabet
Child<27460> is executing testspecial
, -> 745668
. -> 798072
: -> 15708
; -> 32340
! -> 63228
Child<27460> is done executing testalspecial see results above
A -> 111804
B -> 62436
C -> 18612
D -> 22308
E -> 27324
F -> 14124
G -> 13596
H -> 128436
I -> 164340
J -> 6600
K -> 4752
L -> 29040
M -> 170808
N -> 33000
O -> 33924
P -> 57948
Q -> 792
R -> 8712
S -> 108240
T -> 133716
U -> 7128
V -> 2904
W -> 83952
X -> 0
Y -> 37356
Z -> 0
a -> 2861232
b -> 494472
c -> 747252
d -> 1764444
e -> 4855752
f -> 751212
g -> 795696
h -> 2689632
i -> 2421936
j -> 28512
k -> 396660
l -> 1699236
m -> 880044
n -> 2476320
o -> 2732268
p -> 504900
q -> 27984
r -> 2168364
s -> 2357256
t -> 3157968
u -> 1008480
v -> 273900
w -> 1001088
x -> 46860
y -> 693396
z -> 12936
Child<27459> is done executing testalphabet see results above
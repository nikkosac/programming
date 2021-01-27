My program uses pthreads in order to make use  of mulithreading to 
parse the 31 files.
The program begins by opening the specified directory and reading the files into a 
char[100][50] named files and counts how many files there are that end in .txt, if 
it ends in .txt it adds it. It then gets the required data such as the floor of the
quoteint of size/trhead_nums and the mdo. It uses this information in order to
determine the offset for each thread and how many more files it should add to 
each thread depending on the amount of threads the user wishes to use. then these
arguments are added the the structure and the amount of threads are created.
Each thread begins by setting each value in its own alphabet array to zero 
to prevent any bugs. Next it determines its offset and parses the files it 
is supposed to and increments the value in its alphabetfreq[] array accordingly.
Next it locks the global alphabet array with a mutex and adds its data to it and 
dies. after all the threads are completed the global alphabetfreq[] array data gets
copied to the local one and the data is printed the the results folder. 

results for 7 thread:

[cssc2375@edoras two]$ ./testmulthreads 7
Please enter 2 arguments only eg."./testmulthreads #_of__threads!!"
Thread id = 4150126336 starts processing files with index from 5 to 9
Thread id = 4158519040 starts processing files with index from 0 to 4
Thread id = 4133340928 starts processing files with index from 15 to 18
Thread id = 4141733632 starts processing files with index from 10 to 14
Thread id = 4158519040 is currently processing file ../data/input_00.txt
Thread id = 4133340928 is currently processing file ../data/input_15.txt
Thread id = 4141733632 is currently processing file ../data/input_10.txt
Thread id = 4150126336 is currently processing file ../data/input_05.txt
Thread id = 3990730496 starts processing files with index from 19 to 22
Thread id = 3990730496 is currently processing file ../data/input_19.txt
Thread id = 4124948224 starts processing files with index from 23 to 26
Thread id = 4116555520 starts processing files with index from 27 to 30
Thread id = 4124948224 is currently processing file ../data/input_23.txt
Thread id = 4116555520 is currently processing file ../data/input_27.txt
Thread id = 4158519040 is currently processing file ../data/input_01.txt
Thread id = 4141733632 is currently processing file ../data/input_11.txt
Thread id = 4133340928 is currently processing file ../data/input_16.txt
Thread id = 4150126336 is currently processing file ../data/input_06.txt
Thread id = 3990730496 is currently processing file ../data/input_20.txt
Thread id = 4116555520 is currently processing file ../data/input_28.txt
Thread id = 4124948224 is currently processing file ../data/input_24.txt
Thread id = 4141733632 is currently processing file ../data/input_12.txt
Thread id = 4150126336 is currently processing file ../data/input_07.txt
Thread id = 3990730496 is currently processing file ../data/input_21.txt
Thread id = 4133340928 is currently processing file ../data/input_17.txt
Thread id = 4116555520 is currently processing file ../data/input_29.txt
Thread id = 4124948224 is currently processing file ../data/input_25.txt
Thread id = 4141733632 is currently processing file ../data/input_13.txt
Thread id = 4158519040 is currently processing file ../data/input_02.txt
Thread id = 4150126336 is currently processing file ../data/input_08.txt
Thread id = 3990730496 is currently processing file ../data/input_22.txt
Thread id = 4133340928 is currently processing file ../data/input_18.txt
Thread id = 4116555520 is currently processing file ../data/input_30.txt
Thread id = 4124948224 is currently processing file ../data/input_26.txt
Thread id = 4141733632 is currently processing file ../data/input_14.txt
Thread id = 4150126336 is currently processing file ../data/input_09.txt
Thread id = 4158519040 is currently processing file ../data/input_03.txt
Thread id = 4124948224 is done !
Thread id = 3990730496 is done !
Thread id = 4116555520 is done !
Thread id = 4133340928 is done !
Thread id = 4141733632 is done !
Thread id = 4150126336 is done !
Thread id = 4158519040 is currently processing file ../data/input_04.txt
Thread id = 4158519040 is done !
The results are counted as follows :
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
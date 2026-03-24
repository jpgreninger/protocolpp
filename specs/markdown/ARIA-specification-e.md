Speciﬁcation of ARIA

January, 2005

Contents

1 Introduction

2 Speciﬁcation

2.1 Notations . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
2.2 Overall structure . . . . . . . . . . . . . . . . . . . . . . . . . . .
2.3 Substitution layer . . . . . . . . . . . . . . . . . . . . . . . . . . .
2.4 Diﬀusion layer
. . . . . . . . . . . . . . . . . . . . . . . . . . . .
2.5 Key expansion . . . . . . . . . . . . . . . . . . . . . . . . . . . .
2.5.1
Initialization . . . . . . . . . . . . . . . . . . . . . . . . .
2.5.2 Round key generation . . . . . . . . . . . . . . . . . . . .

A History

B Implementation issues

B.1 32-bit software implementation . . . . . . . . . . . . . . . . . . .
B.2 Notes on hardware implementation . . . . . . . . . . . . . . . . .

C Test vectors

C.1 Round key generation example for a 128-bit key . . . . . . . . . .
C.2 Round key generation example for a 192-bit key . . . . . . . . . .
C.3 Round key generation example for a 256-bit key . . . . . . . . . .
C.4 Encryption and Decryption example: 128-bit case . . . . . . . . .
C.5 Encryption and Decryption example: 192-bit case . . . . . . . . .
C.6 Encryption and Decryption example: 256-bit case . . . . . . . . .

3

3
3
3
4
8
8
8
9

11

11
11
13

13
13
15
17
19
23
26

1

List of Figures

1
2
3
4

Encryption and decryption processes . . . . . . . . . . . . . . . .
ARIA substitution layer, type 1 . . . . . . . . . . . . . . . . . . .
ARIA substitution layer, type 2 . . . . . . . . . . . . . . . . . . .
Initialization for ARIA key expansion . . . . . . . . . . . . . . . .

List of Tables

1

2

S-box S1 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
1
S-box S−1
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
2
S-box S2 . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
3
S-box S−1
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
4
Constants CK i depending on the key size . . . . . . . . . . . . .
5
Four values used in round key generation: 128-bit case . . . . . .
6
Intermediate values for Wi: 128-bit case . . . . . . . . . . . . . .
7
Round keys — 128-bit case . . . . . . . . . . . . . . . . . . . . .
8
Four values used in round key generation: 192-bit case . . . . . .
9
10
Intermediate values for Wi: 192-bit case . . . . . . . . . . . . . .
11 Round keys — 192-bit case . . . . . . . . . . . . . . . . . . . . .
12 Four values used in round key generation: 256-bit case . . . . . .
13
Intermediate values for Wi: 256-bit case . . . . . . . . . . . . . .
14 Round keys — 256-bit case . . . . . . . . . . . . . . . . . . . . .
15 Encryption example for ARIA-128 . . . . . . . . . . . . . . . . . .
16 Decryption example for ARIA-128 . . . . . . . . . . . . . . . . . .
17 Encryption example for ARIA-192 . . . . . . . . . . . . . . . . . .
18 Decryption example for ARIA-192 . . . . . . . . . . . . . . . . . .
19 Encryption example for ARIA-256 . . . . . . . . . . . . . . . . . .
20 Decryption example for ARIA-256 . . . . . . . . . . . . . . . . . .

5
5
5
10

4
6
6
7
9
14
14
14
15
15
16
17
17
18
19
21
23
24
26
27

2

1

Introduction

This document provides a complete description of ARIA. ARIA is a block cipher
with the following characteristics:

• ARIA accommodates key sizes of 128, 192, and 256 bits, and the block size

is 128-bit long.

• ARIA uses a 16 × 16 involutional binary matrix with maximum branch

number of 8 as its diﬀusion layer.

• ARIA uses the same algorithm for encryption and decryption, taking ad-

vantage of its involutional diﬀusion matrix.

• ARIA is designed to resist many known attacks on block ciphers, including

diﬀerential cryptanalysis and linear cryptanalysis.

• ARIA is designed to be eﬃcient both in software and hardware implemen-

tations.

2 Speciﬁcation

2.1 Notations

We use the following notations for describing ARIA.

• Si(x) : The output of S-box Si(i = 1, 2) for an input x

• A(x)

: The output of diﬀusion layer for an input x

•

•

⊕ : A bitwise XOR operation

(cid:107)

: Concatenation of two operands

• ≫ n : Right circular rotation of operand by n bits

• ≪ n : Left circular rotation of operand by n bits

•

·

: Multiplication of two operands

2.2 Overall structure

ARIA is a SPN block cipher with 128-, 192-, and 256-bit keys. It processes 128-
bit blocks, and the number of rounds is 12, 14, and 16, depending on the key
size of 128, 192, and 256 bits, respectively.

The ARIA algorithm can be considered as a series of operations done to a
128-bit array called the state. The state is initialized as the plaintext input,
and each operation in each round modiﬁes the state. The ﬁnal value of the
state is the output of the ARIA algorithm. Most of the operations of ARIA

3

are byte-oriented, therefore sometimes the state is considered as an array of 16
bytes.

Each round of the cipher consists of the following three parts:

1. Round key addition, where the state is XORed with a 128-bit round

key.

2. Substitution layer, where the state goes through 16 S-boxes. There
are two kinds of ARIA substitution layers, Type 1 and Type 2, and they
alternate between the rounds.

3. Diﬀusion layer, where a simple 16 × 16 binary matrix is multiplied to

the state, considered as an array of 16 bytes.

Also, there is key expansion operation, where a given secret key is ex-
panded into 13, 15, and 17 round keys, depending on the key size of 128, 192,
and 256 bits, respectively. This is because, in the last round, instead of the
diﬀusion layer, there is another key addition.

Figure 1 illustrates the encryption and decryption processes of ARIA, where

n = 12, 14, or 16.

2.3 Substitution layer
ARIA uses two types of S-boxes S1, S2 and their inverses S−1
in its sub-
stitution layers. They are given in Table 1, Table 2, Table 3, and Table 4. For
example, S1(0x00) = 0x63), S1(0x05) = 0x6b), and S1(0x72) = 0x40).

1 , S−1
2

ARIA has two types of substitution layers as shown in Figure 2 and Figure 3.
The two types alternate between rounds. Type 1 is used in the odd rounds, and
type 2 is used in the even rounds.

0
63
ca
b7
04
09
53
d0
51
cd
60
e0
e7
ba
70
e1
8c

1
7c
82
fd
c7
83
d1
ef
a3
0c
81
32
c8
78
3e
f8
a1

2
77
c9
93
23
2c
00
aa
40
13
4f
3a
37
25
b5
98
89

3
7b
7d
26
c3
1a
ed
fb
8f
ec
dc
0a
6d
2e
66
11
0d

4
f2
fa
36
18
1b
20
43
92
5f
22
49
8d
1c
48
69
bf

0
1
2
3
4
5
6
7
8
9
a
b
c
d
e
f

Table 1: S-box S1
9
7
01
c5
d4
f0
a5
cc
12
9a
3b
a0
cb
5b
f9
85
b6
f5
a7
17
ee
88
d3
5c
56
a9
dd
c6
35
0e
1e
94
99
68

6
6f
47
f7
05
5a
b1
33
38
44
90
24
4e
b4
f6
8e
42

8
30
ad
34
07
52
6a
45
bc
c4
46
c2
6c
e8
61
9b
41

5
6b
59
3f
96
6e
fc
4d
9d
97
2a
06
d5
a6
03
d9
e6

a
67
a2
e5
80
d6
be
02
da
7e
b8
ac
f4
74
57
87
2d

b
2b
af
f1
e2
b3
39
7f
21
3d
14
62
ea
1f
b9
e9
0f

c
fe
9c
71
eb
29
4a
50
10
64
de
91
65
4b
86
ce
b0

d
d7
a4
d8
27
e3
4c
3c
ff
5d
5e
95
7a
bd
c1
55
54

e
ab
72
31
b2
2f
58
9f
f3
19
0b
e4
ae
8b
1d
28
bb

f
76
c0
15
75
84
cf
a8
d2
73
db
79
08
8a
9e
df
16

4

Plaintext

⊕

ek 1

Ciphertext

⊕

Substitution layer type 1

Substitution layer type 1

Diﬀusion layer A

Diﬀusion layer A

⊕

ek 2

⊕

Substitution layer type 2

Substitution layer type 2

Diﬀusion layer A

Diﬀusion layer A

⊕

⊕

ek 3

ek n−1

⊕

⊕

dk 1

dk 2

dk 3

dk n−1

Substitution layer type 1

Substitution layer type 1

Diﬀusion layer A

Diﬀusion layer A

⊕

ek n

⊕

dk n

Substitution layer type 2

Substitution layer type 2

⊕

ek n+1

Ciphertext

⊕

Plaintext

dk n+1

Figure 1: Encryption and decryption processes

S1

S2

S−1
1

S−1
2

S1

S2

S−1
1

S−1
2

S1

S2

S−1
1

S−1
2

S1

S2

S−1
1

S−1
2

Figure 2: ARIA substitution layer, type 1

S−1
1

S−1
2

S1

S2

S−1
1

S−1
2

S1

S2

S−1
1

S−1
2

S1

S2

S−1
1

S−1
2

S1

S2

Figure 3: ARIA substitution layer, type 2

5

(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:111)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
(cid:178)
0
52
7c
54
08
72
6c
90
d0
3a
96
47
fc
1f
60
a0
17

0
e2
5e
1d
00
2d
08
ff
b7
ec
d8
15
a7
30
e6
90
ed

1
09
e3
7b
2e
f8
70
d8
2c
91
ac
f1
56
dd
51
e0
2b

1
4e
fa
06
73
7f
7a
87
ab
20
c0
dd
e1
c6
75
0b
14

2
6a
39
94
a1
f6
48
ab
1e
11
74
1a
3e
a8
7f
3b
04

2
54
64
41
66
f4
88
0e
0c
8c
9e
fd
d0
51
a2
5b
e0

3
d5
82
32
66
64
50
00
8f
41
22
71
4b
33
a9
4d
7e

3
fc
cb
6b
fb
29
38
31
d7
bd
57
17
f5
4b
ef
33
a5

4
30
9b
a6
28
86
fd
8c
ca
4f
e7
1d
c6
88
19
ae
ba

4
94
b4
55
96
ac
5c
36
c4
a0
e3
a9
68
1e
2c
7d
3d

0
1
2
3
4
5
6
7
8
9
a
b
c
d
e
f

0
1
2
3
4
5
6
7
8
9
a
b
c
d
e
f

1

Table 2: S-box S−1
9
5
7
40
38
36
8e
87
2f
4c
3d
c2
5b
b2
d9
a4
16
68
15
da
ed
e4
0a
bc
af
02
3f
f2
ea
67
f9
85
ad
b7
89
29
db
20
d2
12
31
07
e5
0d
b5
eb
b0
2a
69
26
77

6
a5
ff
23
24
98
b9
d3
0f
dc
35
c5
79
c7
4a
f5
d6

8
bf
34
ee
76
d4
5e
f7
c1
97
e2
6f
9a
b1
2d
c8
e1

Table 3: S-box S2
9
7
0d
cc
77
2b
9c
69
09
e4
78
91
db
28
8e
48
98
26
23
04
02
65
c5
9a
05
34
d2
f6
6f
9f
a1
f3
de
f8

6
4a
be
99
85
ad
2a
58
42
84
7b
d4
1b
27
1c
52
b3

8
62
bc
ea
3a
8d
47
01
07
49
3b
7e
70
35
5d
61
89

5
c2
97
f0
4c
cf
83
21
56
c9
c3
bf
f2
a6
b2
5a
22

6

a
a3
43
95
a2
5c
46
58
bd
cf
37
62
c0
10
7a
bb
14

a
6a
2e
18
45
c8
b8
37
60
f1
8f
39
a3
6e
80
f7
71

b
9e
44
0b
49
cc
57
05
03
ce
e8
0e
fe
59
9f
3c
63

b
46
03
ae
aa
95
c7
74
d9
4f
3e
67
8a
24
0a
b0
1a

c
81
c4
42
6d
5d
a7
b8
01
f0
1c
aa
78
27
93
83
55

c
3c
d3
63
0f
f9
93
32
b6
50
e8
fe
d5
16
72
d6
af

d
f3
de
fa
8b
65
8d
b3
13
b4
75
18
cd
80
c9
53
21

d
4d
19
df
ee
2f
a4
ca
b9
1f
25
76
79
82
44
3f
ba

e
d7
e9
c3
d1
b6
9d
45
8a
e6
df
be
5a
ec
9c
99
0c

e
8b
59
e7
10
ce
12
e9
11
13
92
9d
86
5f
9b
7c
b5

f
fb
cb
4e
25
92
84
06
6b
73
6e
1b
f4
5f
ef
61
7d

f
d1
c1
bb
eb
cd
53
b1
40
dc
e5
43
a8
da
6c
6d
81

0
30
3e
81
c0
7f
8c
7a
b8
da
e0
84
eb
91
b2
f2
25

1
68
7e
65
63
22
c2
e8
fa
ff
47
e9
6f
1f
0f
b1
8a

2
99
5e
f5
6c
76
e6
08
dc
cd
9e
d2
d5
05
c9
00
b5

3
1b
8e
89
e3
af
5f
2c
31
55
5c
ba
f6
95
1c
94
e7

4
87
f1
cb
b7
dd
02
12
6b
86
04
5d
14
74
a6
37
42

0
1
2
3
4
5
6
7
8
9
a
b
c
d
e
f

2

Table 4: S-box S−1
9
7
5
39
78
b9
1d
a3
a0
43
c6
9d
aa
6a
c8
88
58
3a
1e
93
24
27
ab
97
bd
19
d1
f8
61
36
26
15
4b
a4
b0
f3
7d
70
fe
85
5b
a9
7b
73
bc
6e
2e
9f
4c
ea
b3

6
21
cc
77
64
0b
75
32
ad
be
34
c5
7c
c1
ec
d0
c7

8
50
2a
57
53
67
66
b4
49
52
79
bf
5a
4a
90
9c
f7

a
db
fb
56
38
06
e5
0a
51
bb
a7
3b
fd
6d
cf
28
11

b
e1
b6
17
98
c3
e2
23
96
0e
de
71
2f
13
59
3f
33

c
72
d6
d4
0c
35
54
df
ee
82
29
44
18
07
8f
80
03

d
09
20
40
f4
0d
d8
ef
e4
48
ae
46
83
4f
a1
f0
a2

e
62
c4
1a
9b
01
10
ca
a8
69
92
2b
16
4e
f9
3d
ac

f
3c
8d
4d
ed
8b
ce
d9
41
9a
d7
fc
a5
45
2d
d3
60

7

2.4 Diﬀusion layer

The diﬀusion layer A of ARIA is a function which maps an input (x0, x1, . . . , x15)
of 16 bytes into an output (y0, y1, . . . , y15). It is deﬁned as follows:

y0 = x3 ⊕ x4 ⊕ x6 ⊕ x8 ⊕ x9 ⊕ x13 ⊕ x14,
y1 = x2 ⊕ x5 ⊕ x7 ⊕ x8 ⊕ x9 ⊕ x12 ⊕ x15,
y2 = x1 ⊕ x4 ⊕ x6 ⊕ x10 ⊕ x11 ⊕ x12 ⊕ x15,
y3 = x0 ⊕ x5 ⊕ x7 ⊕ x10 ⊕ x11 ⊕ x13 ⊕ x14,
y4 = x0 ⊕ x2 ⊕ x5 ⊕ x8 ⊕ x11 ⊕ x14 ⊕ x15,
y5 = x1 ⊕ x3 ⊕ x4 ⊕ x9 ⊕ x10 ⊕ x14 ⊕ x15,
y6 = x0 ⊕ x2 ⊕ x7 ⊕ x9 ⊕ x10 ⊕ x12 ⊕ x13,
y7 = x1 ⊕ x3 ⊕ x6 ⊕ x8 ⊕ x11 ⊕ x12 ⊕ x13,

y8 = x0 ⊕ x1 ⊕ x4 ⊕ x7 ⊕ x10 ⊕ x13 ⊕ x15,
y9 = x0 ⊕ x1 ⊕ x5 ⊕ x6 ⊕ x11 ⊕ x12 ⊕ x14,
y10 = x2 ⊕ x3 ⊕ x5 ⊕ x6 ⊕ x8 ⊕ x13 ⊕ x15,
y11 = x2 ⊕ x3 ⊕ x4 ⊕ x7 ⊕ x9 ⊕ x12 ⊕ x14,
y12 = x1 ⊕ x2 ⊕ x6 ⊕ x7 ⊕ x9 ⊕ x11 ⊕ x12,
y13 = x0 ⊕ x3 ⊕ x6 ⊕ x7 ⊕ x8 ⊕ x10 ⊕ x13,
y14 = x0 ⊕ x3 ⊕ x4 ⊕ x5 ⊕ x9 ⊕ x11 ⊕ x14,
y15 = x1 ⊕ x2 ⊕ x4 ⊕ x5 ⊕ x8 ⊕ x10 ⊕ x15.

The mapping A can also be considered as a 16 × 16 binary matrix multipli-

cation as follows:







































y0
y1
y2
y3
y4
y5
y6
y7
y8
y9
y10
y11
y12
y13
y14
y15




















0
0
0
1
1
0
1
0
1
1
0
0
0
1
1
0

=

0
0
1
0
0
1
0
1
1
1
0
0
1
0
0
1

0
1
0
0
1
0
1
0
0
0
1
1
1
0
0
1

1
0
0
0
0
1
0
1
0
0
1
1
0
1
1
0

1
0
1
0
0
1
0
0
1
0
0
1
0
0
1
1

0
1
0
1
1
0
0
0
0
1
1
0
0
0
1
1

1
0
1
0
0
0
0
1
0
1
1
0
1
1
0
0

0
1
0
1
0
0
1
0
1
0
0
1
1
1
0
0

1
1
0
0
1
0
0
1
0
0
1
0
0
1
0
1

1
1
0
0
0
1
1
0
0
0
0
1
1
0
1
0

0
0
1
1
0
1
1
0
1
0
0
0
0
1
0
1

0
0
1
1
1
0
0
1
0
1
0
0
1
0
1
0

0
1
1
0
0
0
1
1
0
1
0
1
1
0
0
0

1
0
0
1
0
0
1
1
1
0
1
0
0
1
0
0

1
0
0
1
1
1
0
0
0
1
0
1
0
0
1
0




















·







































x0
x1
x2
x3
x4
x5
x6
x7
x8
x9
x10
x11
x12
x13
x14
x15

0
1
1
0
1
1
0
0
1
0
1
0
0
0
0
1

The ARIA diﬀusion layer A is designed to be an involution, i.e., for any input

vector x, it satisﬁes x = A(A(x)).

2.5 Key expansion

The ARIA key expansion consists of two parts, which are initialization and round
key generation as follows.

2.5.1 Initialization

In the initialization part, four 128-bit values W0, W1, W2, and W3 are generated
from the master key MK , by using a 3-round 256-bit Feistel cipher.

Note that MK can be of 128-, 192-, or 256-bit. We ﬁrst ﬁll out the 128-bit
value KL with bits from MK and use what is left of MK (if any) on the 128-bit
value KR. The space remaining on KR (if any) is ﬁlled with zero, so that the
following will hold.

8

Then we set

KL||KR = M K||0 · · · 0.

W0 = KL,
W1 = Fo(W0, CK 1) ⊕ KR,

W2 = Fe(W1, CK 2) ⊕ W0,
W3 = Fo(W2, CK 3) ⊕ W1.

Here, Fo and Fe are even and odd round functions, respectively, given in the
previous subsections. And CKi are constants used in this process as round keys
of the round functions Fo and Fe. They are given as follows. First, the ﬁrst
128 × 3 bits of the fractional part of π−1 is broken into three 128-bit constants
Ci:

C1 = 0x517cc1b727220a94fe12abe8fa9a6ee0
C2 = 0x6db14acc9e21c820ff28b1d5ef5de2b0
C3 = 0xdb92371d2126e9700324977504e8c90e

Then the constants CK i are deﬁned by the following table:

Table 5: Constants CK i depending on the key size
Key size CK 1 CK 2 CK 3
C3
C1
C2

128
192
256

C1
C2
C3

C2
C3
C1

This initialization process is given in Figure 4.

2.5.2 Round key generation

In the round key generation, the four values Wi are combined to generate the
encryption round keys ek i and the decryption round keys dk i.

The following is the deﬁnition for ek i.

3

1

ek 1 = (W0) ⊕ (W ≫19
ek 3 = (W2) ⊕ (W ≫19
ek 5 = (W0) ⊕ (W ≫31
ek 7 = (W2) ⊕ (W ≫31
ek 9 = (W0) ⊕ (W ≪61
ek 11 = (W2) ⊕ (W ≪61

1

1

3

3

),

2
) ⊕ (W3),
),

ek 2 = (W1) ⊕ (W ≫19
ek 4 = (W ≫19
0
ek 6 = (W1) ⊕ (W ≫31
ek 8 = (W ≫31
0
ek 10 = (W1) ⊕ (W ≪61
ek 12 = (W ≪61

2
) ⊕ (W3),
),

2
) ⊕ (W3),

0

),

),

),

),

),

),

9

Figure 4: Initialization for ARIA key expansion

ek 13 = (W0) ⊕ (W ≪31
ek 15 = (W2) ⊕ (W ≪31
ek 17 = (W0) ⊕ (W ≪19

1

3

1

),

),

)

ek 14 = (W1) ⊕ (W ≪31
ek 16 = (W ≪31

2
) ⊕ (W3),

),

0

Note that the number of rounds we use are 12, 14, or 16, corresponding to
the key size 128, 192, or 256 of the master key, respectively. Since there is one
more key addition layer after the last round, in fact the number of round keys
need is 13, 15, or 17.

The decryption round keys are diﬀerent from the encryption round keys,
and derived from the encryption round keys. The ordering of round keys are
reversed followed by the output of the diﬀusion layer A to all round keys except
for the ﬁrst and the last. The following gives the deﬁnition of dk i.

10

KLKRFoCK1W0FeCK2W1FoCK3W2W3dk 1 = ek n+1, dk 2 = A(ek n), dk 3 = A(ek n−1), . . . , dk n = A(ek 2), dk n+1 = ek 1.

A History

ARIA version 0.8 was ﬁrst announced at an annual conference on security in
Korea. Originally, ARIA had 10/12/14 rounds for key sizes of 128/192/256,
respectively, and only two kinds of S-boxes were used.

ARIA version 0.9 was announced at ICISC 2003. In this version, four kinds

of S-boxes were used.

ARIA version 1.0, the current one, was announced and distributed on its
oﬃcial website at http://www.nsri.re.kr/ARIA/ in mid 2004. The number
of rounds was increased to 12/14/16, and there were some modiﬁcations to the
key expansion.

In December 2004, ATS(Agency for Technology and Standards) of Korea
standardized ARIA as ‘128-bit Block Encryption Algorithm ARIA (KS X 1213)’.

B Implementation issues

B.1

32-bit software implementation

The ARIA software implementation mainly consists of S-box and diﬀusion layer
implementation. Since in most cases lookup tables are adequate and very eﬃ-
cient implementation for S-boxes, the most important factor for eﬃcient imple-
mentation is the diﬀusion layer.

The original description of the diﬀusion function A in Subsection 2.4 takes
96 XOR operations in total. In case of software implementation on 8-bit archi-
tectures, one can compute A more eﬃciently by introducing some intermediate
variables which hold values commonly appearing in more than one output val-
ues.

In case of 32-bit software environments, we can do better by extending the
lookup table for the substitution layer to some part of the diﬀusion layer A.
Similar techniques are being used for 32-bit software implementations of other
block ciphers such as AES and Camellia. We will explain this method in this
subsection.

The ARIA diﬀusion layer A can be represented as the following matrix prod-

uct:

where

M1 =

A = M1 · P · M1 · M,


I
I

I
0

I
0
I
I

I
I
0
I

0
I
I
I



, P =


0
I
0 P1

0
0
0
0

0
0
P2
0

0
0
0
P3



, M =

11





P4
0
0
0

0
P4
0
0

0
0
P4
0



.

0
0
0
P4

The submatrices I, and Pi are all 4 × 4. I is the 4 × 4 identity matrix, and

Pi are given as follows.

P1 =

(cid:195)

0
1
0
0

1
0
0
0

0
0
0
1

0
0
1
0

(cid:33)

, P2 =

(cid:195)

0
0
1
0

0
0
0
1

1
0
0
0

0
1
0
0

(cid:33)

, P3 =

(cid:195)

0
0
0
1

0
0
1
0

0
1
0
0

1
0
0
0

(cid:33)

, P4 =

(cid:195)
0
1
1
1

1
0
1
1

1
1
0
1

(cid:33)

.

1
1
1
0

1 , S−1

2 ) and L−1 = (S−1

Let’s deﬁne L = (S1, S2, S−1

2 , S1, S2). Then we
can represent the ARIA substitution layer type 1 as (L, L, L, L), and type 2 as
(L−1, L−1, L−1, L−1). Note that, if we may implement P4 ◦ L and P4 ◦ L−1
eﬃciently, then using these we may implement the substitution layer combined
with the diﬀusion layer eﬃciently. And P4 ◦ L and P4 ◦ L−1 can be implemented
as lookup tables. More precisely, if (x0, x1, x2, x3) is an array of four bytes, then

1 , S−1

P4 ◦ L







x0
x1
x2
x3







 =











=






1

1

 ·
1
0









S1(x0)
1
0 1
S2(x1)
1
1 0
S−1
1 (x2)
0
1 1
S−1
1
1 1
2 (x3)
1 (x2) ⊕ S−1
0 ⊕ S2(x1) ⊕ S−1
S1(x0) ⊕ 0 ⊕ S−1
1 (x2) ⊕ S−1
S1(x0) ⊕ S2(x1) ⊕ 0 ⊕ S−1
S1(x0) ⊕ S2(x1) ⊕ S−1

2 (x3)
2 (x3)
2 (x3)
1 (x2) ⊕ 0







= T0(x0) ⊕ T1(x1) ⊕ T2(x2) ⊕ T3(x3),

where Ti are 8 × 32 lookup tables as follows:

T0(x) =





 , T1(x) =







0
S1(x)
S1(x)
S1(x)







S2(x)
0
S2(x)
S2(x)





 , T2(x) =









S−1
1 (x)
S−1
1 (x)
0
S−1
1 (x)



 , T3(x) =











 .

S−1
2 (x)
S−1
2 (x)
S−1
2 (x)
0

Similarly, P4 ◦ L−1 can be implemented using the following four tables:













T4(x) =



 , T5(x) =







 , T6(x) =







 , T7(x) =









0
S−1
1 (x)
S−1
1 (x)
S−1
1 (x)

S−1
2 (x)
0
S−1
2 (x)
S−1
2 (x)

S1(x)
S1(x)
0
S1(x)





 .

S2(x)
S2(x)
S2(x)
0

In fact, using a special property of ARIA diﬀusion layer, we can implement
this using only four tables T0, T1, T2, and T3, without loss of eﬃciency. Note
that the tables T4, T5, T6, and T7 can be obtained from T2, T3, T0, and T1 by
2-byte rotation, which is simply the matrix P2.

And in the matrix decomposition A = M1 · P · M1 · M , M1 consists of simple
XOR operations on 32-bit words. Therefore the order of operations of M1 and
the 2-byte rotations can be exchanged. Also, we have the following relations
among I and Pi:

I · P2 = P2, P1 · P2 = P3, P2 · P2 = I, P3 · P2 = P1.

12

Therefore, in order to implement the type 2 round function A·(L−1, L−1, L−1, L−1),

we may use the same table lookup T0(x0) ⊕ T1(x1) ⊕ T2(x2) ⊕ T3(x3) as in
A · (L, L, L, L), but in the decomposition A = M1 · P · M1 · M , instead of P we
have to use the following matrix P (cid:48):

P (cid:48) =







P2
0
0
0

0
P3
0
0





 .

0
0
0
0
I
0
0 P1

B.2 Notes on hardware implementation

The hardware eﬃciency is mainly determined by the number of S-box layers
unless diﬀusion layers are too heavy. Since the number of S-box layers are same
as that of AES and smaller than that of Camellia, throughput is almost same
as that of AES and faster than that of Camellia.

C Test vectors

In this section some test vectors for round key generation and encryption/decryption
of ARIA are given. Each type of example is given for each key sizes of 128, 192,
and 256. The following conventions are used to denote the state of ARIA in
various operations.

• input: plaintext input

• start: input to the round function

• key add: the state after XORing the round input and the round key

• s box: the state after the substition layer

• diff lay(er): the state after the diﬀusion layer

• output: ciphertext output

C.1 Round key generation example for a 128-bit key

In this subsection, an example of round key generation is given for the following
key.

key: 000102030405060708090a0b0c0d0e0f

Four values W0, W1, W2, and W3 used in the round key generation are

displayed in Table 6.

The intermediate values for computing W0, W1, W2, and W3 are presented

in Table 7.

Table 8 shows the encryption and decryption round keys.

13

Table 6: Four values used in round key generation: 128-bit case

Variable
W0
W1
W2
W3

Value
000102030405060708090a0b0c0d0e0f
2afbea741e1746dd55c63ba1afcea0a5
7c8578018bb127e02dfe4e78c288e33c
6785b52b74da46bf181054082763ff6d

Table 7: Intermediate values for Wi: 128-bit case

Round
1

2

3

State

key round[1].input
key round[1].key add
key round[1].s box
key round[1].diff layer
key round[2].start
key round[2].key add
key round[2].s box
key round[2].diff layer
key round[3].start
key round[3].key add
key round[3].s box
key round[3].diff layer
key round[3].output

Value
000102030405060708090a0b0c0d0e0f
517dc3b423270c93f61aa1e3f69760ef
d1b933142669815c422ef194426590d3
2afbea741e1746dd55c63ba1afcea0a5
2afbea741e1746dd55c63ba1afcea0a5
474aa0b880368efdaaee8a7440934215
1606e0703a6419ba623d7ec4725c2c97
7c847a028fb421e725f74473ce85ed33
7c8578018bb127e02dfe4e78c288e33c
a7174f1caa97ce902edad90dc6602a32
5c2b92d6ac65ece03180e509b4ff956c
4d7e5f5f6acd00624dd66fa988ad5fc8
6785b52b74da46bf181054082763ff6d

Table 8: Round keys — 128-bit case

Round
1
2
3
4
5
6
7
8
9
10
11
12

Encryption key
d415a75c794b85c5e0d2a0b3cb793bf6
369c65e4b11777ab713a3e1e6601b8f4
0368d4f13d14497b6529ad7ac809e7d0
c644552b549a263fb8d0b50906229eec
5f9c434951f2d2ef342787b1a781794c
afea2c0ce71db6de42a47461f4323c54
324286db44ba4db6c44ac306f2a84b2c
7f9fa93574d842b9101a58063771eb7b
aab9c57731fcd213ad5677458fcfe6d4
2f4423bb06465abada5694a19eb88459
9f8772808f5d580d810ef8ddac13abeb
8684946a155be77ef810744847e35fad
0f0aa16daee61bd7dfee5a599970fb35

Decryption key
0f0aa16daee61bd7dfee5a599970fb35
ccb3a0230b6dac1d53eef49d961aa57f
60ea3252ac3ea9bc9ac78e79df20b5b5
5794eadaece652f8a2ccbf68ee82a730
468a335e49ec1db45d112aaf2109e5bf
938ebbda880c6bb87fa01c97e68811a9
bfda5018ab33d14cc538ea5c81bd1011
b5a90e77d5b94bb56e47af759fcfa05e
21a6c28c5e1175a4378cd34dd3195a83
8d726063ca2ceddc92afb45dd7db643e
27efd355eb17e90e5963c46515016f8d
d000e81367819b077b0a657f6740e8e4
d415a75c794b85c5e0d2a0b3cb793bf6

14

C.2 Round key generation example for a 192-bit key

In this subsection, an example of round key generation is given for the following
192-bit key. We will show similar tables as in the 128-bit case.

key : 000102030405060708090a0b0c0d0e0f1011121314151617

Table 9: Four values used in round key generation: 192-bit case

Variable
W0
W1
W2
W3

Value
000102030405060708090a0b0c0d0e0f
e48c52301e91d991b649ed7bb7cde8ad
a356ea6cafe4869797a1b4eea56d38cc
e1898f2e0e626ccf1f58bd50713c93bb

Table 10: Intermediate values for Wi: 192-bit case

Round
1

2

3

State

key round[1].input
key round[1].key add
key round[1].s box
key round[1].diff layer
key round[2].start
key round[2].key add
key round[2].s box
key round[2].diff layer
key round[3].start
key round[3].key add
key round[3].s box
key round[3].diff layer
key round[3].output

Value
000102030405060708090a0b0c0d0e0f
6db048cf9a24ce27f721bbdee350ecbf
3ca7d445b855ecc66806fef9110883a5
f49d40230a84cf86b649ed7bb7cde8ad
e48c52301e91d991b649ed7bb7cde8ad
3f1e652d3fb730e1b56d7a0eb32521a3
25c44ddf2570040bd2efda8b4b9dfd17
a357e86fabe180909fa8bee5a96036c3
a356ea6cafe4869797a1b4eea56d38cc
f22a2bdb88c68c0369b21f065ff7562c
89180b59c427f01bf9d0cb21cff8b9d4
0505dd1e10f3b55ea911502bc6f17b16
e1898f2e0e626ccf1f58bd50713c93bb

15

Table 11: Round keys — 192-bit case

Round
1
2
3
4
5
6
7
8
9
10
11
12
13
14

Encryption key
bd14be928e4305d5333b3cc231a278f6
4395c65ac3dc4c6d269b1f8f81503c00
3121965d9e01475bda385705b2c736eb
40486f2e2e220c4fbf985c51507df23a
6f9ad358cd1da267352ab928609ed4f8
ae5623a9583c0d48e980e054988e8170
412fcd1b6cf798cb8b656d709bdc426c
f99393300e6068c91752b15e612e87ad
36c83fac72fcbb12b498804d0fdf353d
167864adca3c7e88222330362231787f
40bdfdc6a1c314e0eb90850b64a17555
0088ae6f6fe3cd0eff589d1011bc337b
0f49eecbdf21f0bad3effe5dfe4b2717
b37e117bd54103e6e4ff711de6669d9b
a467dc0b2048d83faf3ffd3355a9ff5b

Decryption key
a467dc0b2048d83faf3ffd3355a9ff5b
4dd0b9831c584a7f72e931dd8ede23f5
b4a02c5b7e7cff4981137b76a1e8af63
e58ecdefea05c868b394d7dabc7298b3
dc94b739beef8d4acd30f3fb4bbd0a19
518c97ed5d0bfaac5240e7f2dd6e2087
a3cffeff0406d3f6fcce825184d8f470
bab3d61669640fcd9fda3fd0cce02c65
9fe831feae7e081014a882cd3f3396f3
9ad65f61fd36b359f684ac037cc53668
622efcce90b0b68380d667bfeee031ed
a44f0daf2b4489a972d5971afdb359f2
9777f3c8a450e691aed77bb2243af84e
044b0b0eccb4bdfb37747a14e7512e75
bd14be928e4305d5333b3cc231a278f6

16

C.3 Round key generation example for a 256-bit key

In this subsection, an example of round key generation is given for the following
256-bit key. We will show similar tables as in the 128-bit and 192-bit cases.

key : 000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f

Table 12: Four values used in round key generation: 256-bit case

Variable
W0
W1
W2
W3

Value
000102030405060708090a0b0c0d0e0f
15169e6ec54aaf0c975414fead1c71f3
90ec92c2a800405af99389e9c88b4e62
b68cd7a1ba16abee905f7009a8e968a9

Table 13: Intermediate values for Wi: 256-bit case

Round
1

2

3

State

key round[1].input
key round[1].key add
key round[1].s box
key round[1].diff layer
key round[2].start
key round[2].key add
key round[2].s box
key round[2].diff layer
key round[3].start
key round[3].key add
key round[3].s box
key round[3].diff layer
key round[3].output

Value
000102030405060708090a0b0c0d0e0f
db93351e2523ef770b2d9d7e08e5c701
b957d9c43f6b61192bdf75a8305a3168
05078c7dd15fb91b8f4d0ee5b1016fec
15169e6ec54aaf0c975414fead1c71f3
446a5fd9e268a5986947bf1657861f13
860acf6f3bb4063be45808bedabec0cb
90ed90c1ac05465df19a83e2c486406d
90ec92c2a800405af99389e9c88b4e62
fd5dd80e3621887a06bb383c27d6acd2
54a42d62050697516f8a760ccc1caac9
a39a49cf7f5c04e2070b64f705f5195a
b68cd7a1ba16abee905f7009a8e968a9

17

Table 14: Round keys — 256-bit case

Round
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16

Encryption key
8e3f60a1d7c8deae5de898e18e92dbac
7cdacc735712fa0c9f5f4bccdc2148e2
bdf9a41332f477182cee5be2268a7b7f
174d37a19a56cb6e309f910889a80928
5a39e1e52e283ada829c541222a527f2
840002abe4938a89c754944b5e3b6220
c13e4391c519ef198dbede34e835ae71
ae96cbbfba14afe898557c07b8fb7cbf
92eb809cd1a688396aabd9c6d4a45bee
4a24ef53fc5bc6c0c54986a6f81c79f8
42e77cc39d1d6d4fcf42131dffc99b1f
578df6e0db970a2f705f5049c869c869
62a455854faf0c785e8732f286864138
4116be43b9836bf87311b3cfe56a3892
4de7c735e02ff85e2de73dbd13cd25b2
348e54a23e122eeb1659f70e28e9e9a8
f37728567c61bca7affc62e88395a6bb

Decryption key
f37728567c61bca7affc62e88395a6bb
fd62e7342bfde4dbd9499dbb605b04bf
0fddde54a27fd06456f6779dcf03c84d
a1d0cf146ae42a0d5dad9e70003bdec0
d8e599b24da2fa817d5093a776793345
bfc0e457ae1820ff7e0efbbd80db257e
ec43f94c756c16adb2acd64b19b6c5d8
80f83e941cc54e3630d40048da4028d7
fbe497edad612923021e12d063a84f41
e0fdffae2d79e75a524013b7f04991a8
13e967b0fdd52624b97bedf6e9c0a883
0ff5cf18dbcdaac866ea6cac40442506
6dddbb6cd6ef2ef19466c369942c10fa
fe0124176f59613ebf4fbb7dc11ae43f
65d35c19276918ffc078ed2e183c1f93
772cce8c5b4055fd75160b2faf0c9165
8e3f60a1d7c8deae5de898e18e92dbac

18

C.4 Encryption and Decryption example: 128-bit case

In this subsection, an example in ARIA encryption and decryption for a 128-bit
key is given. In this and the following subsections for 192-bit and 256-bit keys,
we will use the following plaintext.

00112233445566778899aabbccddeeff.

In this subsection, we will use the following 128-bit key:

000102030405060708090a0b0c0d0e0f.

Table 15: Encryption example for ARIA-128

Round

State

Value

1

2

3

4

5

6

7

8

round[ 0].input
round[ 1].start
round[ 1].key add
round[ 1].s box
round[ 1].diff lay
round[ 2].start
round[ 2].key add
round[ 2].s box
round[ 2].diff lay
round[ 3].start
round[ 3].key add
round[ 3].s box
round[ 3].diff lay
round[ 4].start
round[ 4].key add
round[ 4].s box
round[ 4].diff lay
round[ 5].start
round[ 5].key add
round[ 5].s box
round[ 5].diff lay
round[ 6].start
round[ 6].key add
round[ 6].s box
round[ 6].diff lay
round[ 7].start
round[ 7].key add
round[ 7].s box
round[ 7].diff lay
round[ 8].start
round[ 8].key add
round[ 8].s box
round[ 8].diff lay

00112233445566778899aabbccddeeff
00112233445566778899aabbccddeeff
d404856f3d1ee3b2684b0a0807a4d509
489467d927594dd54595a350c5a9b539
7fc7f12befd0a0791de87fa96b469f52
7fc7f12befd0a0791de87fa96b469f52
495b94cf5ec7d7d26cd241b70d4727a6
a4e222da9d5b0ea2b8c98334f358ccd4
ac8de17e49f7c5117618993162b189e9
ac8de17e49f7c5117618993162b189e9
afe5358f74e38c6a1331344baab86e39
795ad99a9233f00a7d7328c3ac7045aa
c3e8d59ec2e62d5249ca2741653cb7dd
c3e8d59ec2e62d5249ca2741653cb7dd
05ac80b5967c0b6df11a9248631e2931
3644cdf235ee2bca2bfb4f8d00c4a573
5d4aebb165e141ff759f669e1e85cc45
5d4aebb165e141ff759f669e1e85cc45
02d6a8f83413931041b8e12fb904b509
771c6ff718cb223e8370e04d5694d239
7806e469f68874c5004b5f4a046bbcfa
7806e469f68874c5004b5f4a046bbcfa
d7ecc8651195c21b42ef2b2bf05980ae
0d80e821e34b2503f6d3f1ae171ecd9d
110f93c9a630cdd51f97d2202413345a
110f93c9a630cdd51f97d2202413345a
234d1512e28a8063dbdd1126d6bb7f76
262f2f5e98f13a2cb944e377f68a6bad
e054428ef088fef97928241cd3be499e
e054428ef088fef97928241cd3be499e
9fcbebbb8450bc4069327c1ae4cfa2e5
6e13e98a4f8c652de46c102eae453a5a
5734f38ea1ca3ddd102e71f95e1d5f97
Continues on next page. . .

19

Round

9

10

11

12

State

round[ 9].start
round[ 9].key add
round[ 9].s box
round[ 9].diff lay
round[10].start
round[10].key add
round[10].s box
round[10].diff lay
round[11].start
round[11].key add
round[11].s box
round[11].diff lay
round[12].start
round[12].key add
round[12].s box
round[12].output

Continued from previous page. . .

Value

5734f38ea1ca3ddd102e71f95e1d5f97
fd8d36f99036efcebd7806bcd1d2b943
541f244c6085614e7a07a5183ea2dbaf
4903325be3e500cccd52fba4354a39ae
4903325be3e500cccd52fba4354a39ae
664711e0e5a35a7617046f05abf2bdf7
d35882902ababe428787a8c20eb57af8
cb8c508e2c4f87880639dc896d25ec9d
cb8c508e2c4f87880639dc896d25ec9d
540b220ea312df8587372454c1364776
204694620a64ef3617e4a602788516ad
e7e0d2457ed73d23d481424095afdca0
e7e0d2457ed73d23d481424095afdca0
6164462f6b8cda5d2c913608d24c830d
d8125abb058257a4424705627f35ec4d
d718fbd6ab644c739da95f3be6451778

20

Table 16: Decryption example for ARIA-128

Round

State

Value

1

2

3

4

5

6

7

8

9

10

11

round[ 0].input
round[ 1].start
round[ 1].key add
round[ 1].s box
round[ 1].diff lay
round[ 2].start
round[ 2].key add
round[ 2].s box
round[ 2].diff lay
round[ 3].start
round[ 3].key add
round[ 3].s box
round[ 3].diff lay
round[ 4].start
round[ 4].key add
round[ 4].s box
round[ 4].diff lay
round[ 5].start
round[ 5].key add
round[ 5].s box
round[ 5].diff lay
round[ 6].start
round[ 6].key add
round[ 6].s box
round[ 6].diff lay
round[ 7].start
round[ 7].key add
round[ 7].s box
round[ 7].diff lay
round[ 8].start
round[ 8].key add
round[ 8].s box
round[ 8].diff lay
round[ 9].start
round[ 9].key add
round[ 9].s box
round[ 9].diff lay
round[10].start
round[10].key add
round[10].s box
round[10].diff lay
round[11].start
round[11].key add
round[11].s box
round[11].diff lay

d718fbd6ab644c739da95f3be6451778
d718fbd6ab644c739da95f3be6451778
d8125abb058257a4424705627f35ec4d
6164462f6b8cda5d2c913608d24c830d
ecf534410109432b440a529fee9fb3d2
ecf534410109432b440a529fee9fb3d2
204694620a64ef3617e4a602788516ad
540b220ea312df8587372454c1364776
b3b2b0c2868417fe1d4026bbd195cf4d
b3b2b0c2868417fe1d4026bbd195cf4d
d35882902ababe428787a8c20eb57af8
664711e0e5a35a7617046f05abf2bdf7
038bce968c6333b6d8cb1a70d0207c9f
038bce968c6333b6d8cb1a70d0207c9f
541f244c6085614e7a07a5183ea2dbaf
fd8d36f99036efcebd7806bcd1d2b943
2899dad406607899b97d3a818f4cdfe5
2899dad406607899b97d3a818f4cdfe5
6e13e98a4f8c652de46c102eae453a5a
9fcbebbb8450bc4069327c1ae4cfa2e5
b5a1948410fd5194c6e4ffe010027a04
b5a1948410fd5194c6e4ffe010027a04
262f2f5e98f13a2cb944e377f68a6bad
234d1512e28a8063dbdd1126d6bb7f76
b25ab8394878f44f33eb1bf296a3dd8c
b25ab8394878f44f33eb1bf296a3dd8c
0d80e821e34b2503f6d3f1ae171ecd9d
d7ecc8651195c21b42ef2b2bf05980ae
c2b56180cd72698bed374f38c95b7267
c2b56180cd72698bed374f38c95b7267
771c6ff718cb223e8370e04d5694d239
02d6a8f83413931041b8e12fb904b509
17e20f7e6bff5e6e1c779cc0d3ddfff0
17e20f7e6bff5e6e1c779cc0d3ddfff0
3644cdf235ee2bca2bfb4f8d00c4a573
05ac80b5967c0b6df11a9248631e2931
f428b9f9581f1dd6efdc9c9e7bab2194
f428b9f9581f1dd6efdc9c9e7bab2194
795ad99a9233f00a7d7328c3ac7045aa
afe5358f74e38c6a1331344baab86e39
830df18f764ce7ace1aa4751e659a359
830df18f764ce7ace1aa4751e659a359
a4e222da9d5b0ea2b8c98334f358ccd4
495b94cf5ec7d7d26cd241b70d4727a6
98948fca40d8d6d23e9fc62fa2e95ddd
Continues on next page. . .

21

Round

12

State

Value

Continued from previous page. . .

round[12].start
round[12].key add
round[12].s box
round[12].output

98948fca40d8d6d23e9fc62fa2e95ddd
489467d927594dd54595a350c5a9b539
d404856f3d1ee3b2684b0a0807a4d509
00112233445566778899aabbccddeeff

22

C.5 Encryption and Decryption example: 192-bit case

In this subsection, an example in ARIA encryption and decryption for a 192-bit
key is given. The same plaintext used for 128-bit example will be used, and the
key is:

000102030405060708090a0b0c0d0e0f1011121314151617.

Table 17: Encryption example for ARIA-192

Round

State

Value

1

2

3

4

5

6

7

8

9

round[ 0].input
round[ 1].start
round[ 1].key add
round[ 1].s box
round[ 1].diff lay
round[ 2].start
round[ 2].key add
round[ 2].s box
round[ 2].diff lay
round[ 3].start
round[ 3].key add
round[ 3].s box
round[ 3].diff lay
round[ 4].start
round[ 4].key add
round[ 4].s box
round[ 4].diff lay
round[ 5].start
round[ 5].key add
round[ 5].s box
round[ 5].diff lay
round[ 6].start
round[ 6].key add
round[ 6].s box
round[ 6].diff lay
round[ 7].start
round[ 7].key add
round[ 7].s box
round[ 7].diff lay
round[ 8].start
round[ 8].key add
round[ 8].s box
round[ 8].diff lay
round[ 9].start
round[ 9].key add
round[ 9].s box
round[ 9].diff lay

00112233445566778899aabbccddeeff
00112233445566778899aabbccddeeff
bd059ca1ca1663a2bba29679fd7f9609
7ac21ce974be00d2eafd35bd54403539
ff0a53eb839b686852dad8cf18de2cf2
ff0a53eb839b686852dad8cf18de2cf2
bc9f95b1404724057441c740998e10f2
78d72ae1725836c2ca22c62df969cae0
ee4161aac78ae47750dfe66aff08763b
ee4161aac78ae47750dfe66aff08763b
df60f7f7598ba32c8ae7b16f4dcf40d0
9eff26eacb4f71d47ef356d9e3da72b2
75619b2290bbf0fa4017e4b1b523a8c7
75619b2290bbf0fa4017e4b1b523a8c7
3529f40cbe99fcb5ff8fb8e0e55e5afd
d943bf3c5a26b0f27d9a6c902a10beba
9f1cc55fa9d75818f408c2259ea62d2b
9f1cc55fa9d75818f408c2259ea62d2b
f086160764cafa7fc1227b0dfe38f9d3
8c84ff78436e144178410309bb3a691c
454e7efa1988f1182fa9a316dde0f831
454e7efa1988f1182fa9a316dde0f831
eb185d5341b4fc50c6294342456e7941
3c2a4c38f814b008c7431af468cab67f
88c39bb29e7a83334998a21901abe928
88c39bb29e7a83334998a21901abe928
c9ec56a9f28d1bf8c2fdcf699a77ab44
ddd6b9a4891f44f725ba5f27b8260edd
deab0665aacde8aad1c1986ff9967c5e
deab0665aacde8aad1c1986ff9967c5e
27389555a4ad8063c693293198b8fbf3
3d532a831d46cd31c75ca573e25a0fa5
9d8112c94f9e6711187b1a34487ac5e5
9d8112c94f9e6711187b1a34487ac5e5
ab492d653d62dc03ace39a7947a5f0d8
6278fa97270e931b913337bda0bf1790
297d76553d4b984f3e8d4ed52464459d
Continues on next page. . .

23

Round

10

11

12

13

14

State

round[10].start
round[10].key add
round[10].s box
round[10].diff lay
round[11].start
round[11].key add
round[11].s box
round[11].diff lay
round[12].start
round[12].key add
round[12].s box
round[12].diff lay
round[13].start
round[13].key add
round[13].s box
round[13].diff lay
round[14].start
round[14].key add
round[14].s box
round[14].output

Continued from previous page. . .

Value

297d76553d4b984f3e8d4ed52464459d
3f0512f8f777e6c71cae7ee306553de2
25b9c98926198ef6c42bf333a524275b
cd372f097eb243c8c0ba6c39b5c7ac23
cd372f097eb243c8c0ba6c39b5c7ac23
8d8ad2cfdf7157282b2ae932d166d976
5df17f459eabda57f118eb6c3e58e5ad
55f9a19b5c91e0957b6a4f3049d7bc0c
55f9a19b5c91e0957b6a4f3049d7bc0c
55710ff433722d9b8432d220586b8f77
edfa763d66dcd83e4f6cb51d5e237326
f0cf94f7402d0130ff23055245ef68ea
f0cf94f7402d0130ff23055245ef68ea
ff867a3c9f0cf18a2cccfb0fbba44ffd
1684bd0cdb3c2bbb7116633ceaa992a2
a01563f5ea1626ad9ac1dcbf6931456e
a01563f5ea1626ad9ac1dcbf6931456e
136b728e3f57254b7e3eada28f57d8f5
8223401325933f958a9b95fd73936122
26449c1805dbe7aa25a468ce263a9e79

Table 18: Decryption example for ARIA-192

Round

State

Value

1

2

3

4

5

round[ 0].input
round[ 1].start
round[ 1].key add
round[ 1].s box
round[ 1].diff lay
round[ 2].start
round[ 2].key add
round[ 2].s box
round[ 2].diff lay
round[ 3].start
round[ 3].key add
round[ 3].s box
round[ 3].diff lay
round[ 4].start
round[ 4].key add
round[ 4].s box
round[ 4].diff lay
round[ 5].start
round[ 5].key add
round[ 5].s box
round[ 5].diff lay

26449c1805dbe7aa25a468ce263a9e79
26449c1805dbe7aa25a468ce263a9e79
8223401325933f958a9b95fd73936122
136b728e3f57254b7e3eada28f57d8f5
5b54048fc76461c403ff52e16477b157
5b54048fc76461c403ff52e16477b157
1684bd0cdb3c2bbb7116633ceaa992a2
ff867a3c9f0cf18a2cccfb0fbba44ffd
595a5a6618a02777ce7fce6bffcbdc45
595a5a6618a02777ce7fce6bffcbdc45
edfa763d66dcd83e4f6cb51d5e237326
55710ff433722d9b8432d220586b8f77
b87fb2aa74ae123f428c3cb6822a7d1e
b87fb2aa74ae123f428c3cb6822a7d1e
5df17f459eabda57f118eb6c3e58e5ad
8d8ad2cfdf7157282b2ae932d166d976
f92d7eb098f603bc091b00c8ee992d42
f92d7eb098f603bc091b00c8ee992d42
25b9c98926198ef6c42bf333a524275b
3f0512f8f777e6c71cae7ee306553de2
33f46d7a7a0569b7c373d04f7dd13717
Continues on next page. . .

24

Round

State

Value

Continued from previous page. . .

6

7

8

9

10

11

12

13

14

round[ 6].start
round[ 6].key add
round[ 6].s box
round[ 6].diff lay
round[ 7].start
round[ 7].key add
round[ 7].s box
round[ 7].diff lay
round[ 8].start
round[ 8].key add
round[ 8].s box
round[ 8].diff lay
round[ 9].start
round[ 9].key add
round[ 9].s box
round[ 9].diff lay
round[10].start
round[10].key add
round[10].s box
round[10].diff lay
round[11].start
round[11].key add
round[11].s box
round[11].diff lay
round[12].start
round[12].key add
round[12].s box
round[12].diff lay
round[13].start
round[13].key add
round[13].s box
round[13].diff lay
round[14].start
round[14].key add
round[14].s box
round[14].output

33f46d7a7a0569b7c373d04f7dd13717
6278fa97270e931b913337bda0bf1790
ab492d653d62dc03ace39a7947a5f0d8
9e9cd47c19401ec73b9227226682fbd5
9e9cd47c19401ec73b9227226682fbd5
3d532a831d46cd31c75ca573e25a0fa5
27389555a4ad8063c693293198b8fbf3
67656fb2e07b4b3aba6060f774c622b8
67656fb2e07b4b3aba6060f774c622b8
ddd6b9a4891f44f725ba5f27b8260edd
c9ec56a9f28d1bf8c2fdcf699a77ab44
a3c27dc6566ab818d3eb983957f9208c
a3c27dc6566ab818d3eb983957f9208c
3c2a4c38f814b008c7431af468cab67f
eb185d5341b4fc50c6294342456e7941
1652a019be58a7188ec5af0ac7ff5f74
1652a019be58a7188ec5af0ac7ff5f74
8c84ff78436e144178410309bb3a691c
f086160764cafa7fc1227b0dfe38f9d3
bb6d43f2ca960671fd4c0b2fc4f08f57
bb6d43f2ca960671fd4c0b2fc4f08f57
d943bf3c5a26b0f27d9a6c902a10beba
3529f40cbe99fcb5ff8fb8e0e55e5afd
3ab02b45e00bf87d0c26c1c31e692b40
3ab02b45e00bf87d0c26c1c31e692b40
9eff26eacb4f71d47ef356d9e3da72b2
df60f7f7598ba32c8ae7b16f4dcf40d0
efa0d929d608d05364f5bd9fdd5332ae
efa0d929d608d05364f5bd9fdd5332ae
78d72ae1725836c2ca22c62df969cae0
bc9f95b1404724057441c740998e10f2
7e8917e7b80abd29dd894fa9b3111b4c
7e8917e7b80abd29dd894fa9b3111b4c
7ac21ce974be00d2eafd35bd54403539
bd059ca1ca1663a2bba29679fd7f9609
00112233445566778899aabbccddeeff

25

C.6 Encryption and Decryption example: 256-bit case

In this subsection, an example in ARIA encryption and decryption for a 256-bit
key is given. The same plaintext used for 128-bit and 192-bit example will be
used, and the key is:

000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f.

Table 19: Encryption example for ARIA-256

Round

State

Value

1

2

3

4

5

6

7

8

9

round[ 0].input
round[ 1].start
round[ 1].key add
round[ 1].s box
round[ 1].diff lay
round[ 2].start
round[ 2].key add
round[ 2].s box
round[ 2].diff lay
round[ 3].start
round[ 3].key add
round[ 3].s box
round[ 3].diff lay
round[ 4].start
round[ 4].key add
round[ 4].s box
round[ 4].diff lay
round[ 5].start
round[ 5].key add
round[ 5].s box
round[ 5].diff lay
round[ 6].start
round[ 6].key add
round[ 6].s box
round[ 6].diff lay
round[ 7].start
round[ 7].key add
round[ 7].s box
round[ 7].diff lay
round[ 8].start
round[ 8].key add
round[ 8].s box
round[ 8].diff lay
round[ 9].start
round[ 9].key add
round[ 9].s box
round[ 9].diff lay

00112233445566778899aabbccddeeff
00112233445566778899aabbccddeeff
8e2e4292939db8d9d571325a424f3553
19e7f69edc259a7b03aba1e52ccdd95f
64739617aa297fe46a5146919209e915
64739617aa297fe46a5146919209e915
18a95a64fd3b85e8f50e0d5d4e28a1f7
34a4be36219897617762d7a4b65732f8
f01c2fdb0bccbf37a8bf5f2e9c034ffb
f01c2fdb0bccbf37a8bf5f2e9c034ffb
4de58bc83938c82f845104ccba893484
e35ace4a123ab14d5f7a3007f4232886
c7eebca8e1e6fd2e73e9f57de119d455
c7eebca8e1e6fd2e73e9f57de119d455
d0a38b097bb036404376647568b1dd7d
60ba3d0d03eb052d64ad4356f76fc1b9
6c7ce71dfc22061861546c85a30dbff1
6c7ce71dfc22061861546c85a30dbff1
364506f8d20a3cc2e3c8389781a89803
05cfa5f7b56a6d05113576150c7ee21b
97f9639537379423693621392e83efc9
97f9639537379423693621392e83efc9
13f9613ed3a41eaaae62b57270b88de9
824cef10a95d7239be08d50cd05a5da1
7a4c3f387ed40316706095ea3ce83f9d
7a4c3f387ed40316706095ea3ce83f9d
bb727ca9bbcdec0ffdde4bded4dd91ec
ea0c01a4ea82833c549bccf94844ac80
eab89889e8398c8a38fa340c982de87d
eab89889e8398c8a38fa340c982de87d
442e5336522d2362a0af480b20d694c2
861aed854840260e47fc524654ec2251
9e1d6512590a730035caf4a431d293bb
9e1d6512590a730035caf4a431d293bb
0cf6e58e88acfb395f612d62e576c855
feb32a69c4fe63aacf87fa08d942b124
75cb1bab78f698e5bfb077c2062993b2
Continues on next page. . .

26

Round

10

11

12

13

14

15

16

State

round[10].start
round[10].key add
round[10].s box
round[10].diff lay
round[11].start
round[11].key add
round[11].s box
round[11].diff lay
round[12].start
round[12].key add
round[12].s box
round[12].diff lay
round[13].start
round[13].key add
round[13].s box
round[13].diff lay
round[14].start
round[14].key add
round[14].s box
round[14].diff lay
round[15].start
round[15].key add
round[15].s box
round[15].diff lay
round[16].start
round[16].key add
round[16].s box
round[16].output

Continued from previous page. . .

Value

75cb1bab78f698e5bfb077c2062993b2
3feff4f884ad5e257af9f164fe35ea4a
25d3bf894f4658f0bd4ca1360cc887c8
203c974b18b7434de855954eb2d058b1
203c974b18b7434de855954eb2d058b1
62dbeb8885aa2e02271786534d19c3ae
aa0a3c529739c399cc2bdc5fe377332b
a5b315cd24206c9c2ed5049bfbc511a3
a5b315cd24206c9c2ed5049bfbc511a3
f23ee32dffb766b35e8a54d233acd9ca
049b11df7d7033f59dbb20a26644356e
c6ba5f7201f9596a1d2d3aae33e4fa54
c6ba5f7201f9596a1d2d3aae33e4fa54
a41e0af74e56551243aa085cb562bb6c
4959a3ea2f2aed5e1a39bf54d50efedf
fbfe7a26af3be9cb0fa8452af1bb3585
fbfe7a26af3be9cb0fa8452af1bb3585
bae8c46516b882337cb9f6e514d10d17
c09c1c21ff5a13fb017d425a9b0fd72b
6971d8a121818c613e035108d445b44d
6971d8a121818c613e035108d445b44d
24961f94c1ae743f13e46cb5c78891ff
367bcb04789dcaed7d7db8fec649ac60
531d29e52f0e5ab9498ecc4dd299f8f0
531d29e52f0e5ab9498ecc4dd299f8f0
67937d47111c74525fd73b43fa701158
0a5cff91e3d692888473e22914b88247
f92bd7c79fb72e2f2b8f80c1972d24fc

Table 20: Decryption example for ARIA-256

Round

State

Value

1

2

3

round[ 0].input
round[ 1].start
round[ 1].key add
round[ 1].s box
round[ 1].diff lay
round[ 2].start
round[ 2].key add
round[ 2].s box
round[ 2].diff lay
round[ 3].start
round[ 3].key add
round[ 3].s box
round[ 3].diff lay

f92bd7c79fb72e2f2b8f80c1972d24fc
f92bd7c79fb72e2f2b8f80c1972d24fc
0a5cff91e3d692888473e22914b88247
67937d47111c74525fd73b43fa701158
cb192c3053602e36a4342545a612a8df
cb192c3053602e36a4342545a612a8df
367bcb04789dcaed7d7db8fec649ac60
24961f94c1ae743f13e46cb5c78891ff
cf41c2755d25c39f578b35c7540c1f66
cf41c2755d25c39f578b35c7540c1f66
c09c1c21ff5a13fb017d425a9b0fd72b
bae8c46516b882337cb9f6e514d10d17
e8896cfe45cec75347942124d535201f
Continues on next page. . .

27

Round

State

Value

Continued from previous page. . .

4

5

6

7

8

9

10

11

12

13

14

15

round[ 4].start
round[ 4].key add
round[ 4].s box
round[ 4].diff lay
round[ 5].start
round[ 5].key add
round[ 5].s box
round[ 5].diff lay
round[ 6].start
round[ 6].key add
round[ 6].s box
round[ 6].diff lay
round[ 7].start
round[ 7].key add
round[ 7].s box
round[ 7].diff lay
round[ 8].start
round[ 8].key add
round[ 8].s box
round[ 8].diff lay
round[ 9].start
round[ 9].key add
round[ 9].s box
round[ 9].diff lay
round[10].start
round[10].key add
round[10].s box
round[10].diff lay
round[11].start
round[11].key add
round[11].s box
round[11].diff lay
round[12].start
round[12].key add
round[12].s box
round[12].diff lay
round[13].start
round[13].key add
round[13].s box
round[13].diff lay
round[14].start
round[14].key add
round[14].s box
round[14].diff lay
round[15].start
round[15].key add

e8896cfe45cec75347942124d535201f
4959a3ea2f2aed5e1a39bf54d50efedf
a41e0af74e56551243aa085cb562bb6c
dc7e886d30d2c974e0ebb305103d062b
dc7e886d30d2c974e0ebb305103d062b
049b11df7d7033f59dbb20a26644356e
f23ee32dffb766b35e8a54d233acd9ca
15cad8053921e366b22527e263ac1655
15cad8053921e366b22527e263ac1655
aa0a3c529739c399cc2bdc5fe377332b
62dbeb8885aa2e02271786534d19c3ae
c99046c53a2a4e5d0fe0777d157e4210
c99046c53a2a4e5d0fe0777d157e4210
25d3bf894f4658f0bd4ca1360cc887c8
3feff4f884ad5e257af9f164fe35ea4a
7e4b14fdd83b2d9cff53fa40030299f3
7e4b14fdd83b2d9cff53fa40030299f3
feb32a69c4fe63aacf87fa08d942b124
0cf6e58e88acfb395f612d62e576c855
7dfe7a68e5210f2d45e2409637446d10
7dfe7a68e5210f2d45e2409637446d10
861aed854840260e47fc524654ec2251
442e5336522d2362a0af480b20d694c2
0af1fe0ac7fb646606dbdf4eb80d3d28
0af1fe0ac7fb646606dbdf4eb80d3d28
ea0c01a4ea82833c549bccf94844ac80
bb727ca9bbcdec0ffdde4bded4dd91ec
91a588a05488541d077338fa399af522
91a588a05488541d077338fa399af522
824cef10a95d7239be08d50cd05a5da1
13f9613ed3a41eaaae62b57270b88de9
0a3a6aef6ea7c7cd77df1ab94c3ac71d
0a3a6aef6ea7c7cd77df1ab94c3ac71d
05cfa5f7b56a6d05113576150c7ee21b
364506f8d20a3cc2e3c8389781a89803
0d678661d5042bdcf0cb803f6343d143
0d678661d5042bdcf0cb803f6343d143
60ba3d0d03eb052d64ad4356f76fc1b9
d0a38b097bb036404376647568b1dd7d
1d5bea5d7d63d073e0358b7a3539ccb9
1d5bea5d7d63d073e0358b7a3539ccb9
e35ace4a123ab14d5f7a3007f4232886
4de58bc83938c82f845104ccba893484
5177e22f06f18f9eb71a3a8aae6b2d6b
5177e22f06f18f9eb71a3a8aae6b2d6b
34a4be36219897617762d7a4b65732f8
Continues on next page. . .

28

Round

State

16

round[15].s box
round[15].diff lay
round[16].start
round[16].key add
round[16].s box
round[16].output

Continued from previous page. . .

Value
18a95a64fd3b85e8f50e0d5d4e28a1f7
6ecb38128765cf8676bdaaca83c1483a
6ecb38128765cf8676bdaaca83c1483a
19e7f69edc259a7b03aba1e52ccdd95f
8e2e4292939db8d9d571325a424f3553
00112233445566778899aabbccddeeff

29


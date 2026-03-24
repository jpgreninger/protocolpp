ETSI/SAGE
Specification

Version:  1.1
Date: 6th September 2006

Specification of the 3GPP Confidentiality and
Integrity Algorithms UEA2 & UIA2.
Document 1: UEA2 and UIA2 Specification

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 1 of 27

V1.0

V1.1

Document History

10th January 2006

Publication

6th September 2006

No change to the algorithm specification at all, just
removal of an unwanted page header

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 2 of 27

PREFACE

This specification has been prepared by the 3GPP Task Force, and gives a detailed
specification of the 3GPP confidentiality algorithm UEA2 and the 3GPP integrity algorithm
UIA2.

This document is the first of four, which between them form the entire specification of 3GPP
Confidentiality and Integrity Algorithms:

•  Specification of the 3GPP Confidentiality and Integrity Algorithms UEA2 &

UIA2.
Document 1: UEA2 and UIA2 Algorithm Specifications.

•  Specification of the 3GPP Confidentiality and Integrity Algorithms UEA2 &

UIA2.
Document 2: SNOW 3G Algorithm Specification.

•  Specification of the 3GPP Encryption and Confidentiality Algorithms UEA2 &

UIA2.
Document 3: Implementors’ Test Data.

•  Specification of the 3GPP Encryption and Confidentiality Algorithms UEA2 &

UIA2.
Document 4: Design Conformance Test Data.

The normative part of the specification of the UEA2 (confidentiality) and UIA2 (integrity)
algorithms is in the main body of this document. The annexes to this document are purely
informative.

The informative section of this document includes four informative annexes: Annex 1
contains remarks about the mathematical background of some functions of UIA2. Annex 2
contains implementation options for some functions of UIA2. Annex 3 contains illustrations
of functional elements of the algorithms, while Annex 4 contains an implementation program
listing of the cryptographic algorithm specified in the main body of this document, written in
the programming language C.

The normative section of the specification of the stream cipher (SNOW 3G) on which they
are based is in the main body of Document 2. The annexes to that document, and Documents
3 and 4 above, are purely informative.

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 3 of 27

Blank Page

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 4 of 27

TABLE OF CONTENTS

1.  OUTLINE OF THE NORMATIVE PART........................................................................8

2.

INTRODUCTORY INFORMATION................................................................................8
2.1.  Introduction.................................................................................................................8
2.2.  Notation ......................................................................................................................8
2.3.  List of Variables .......................................................................................................10

3.  CONFIDENTIALITY ALGORITHM UEA2...................................................................11
3.1.  Introduction...............................................................................................................11
3.2.  Inputs and Outputs....................................................................................................11
3.3.  Components and Architecture ..................................................................................11
3.4.  Initialisation ..............................................................................................................11
3.5.  Keystream Generation ..............................................................................................12
3.6.  Encryption/Decryption..............................................................................................12

4.

INTEGRITY ALGORITHM UIA2 ..................................................................................13
4.1.  Introduction...............................................................................................................13
4.2.  Inputs and Outputs....................................................................................................13
4.3.  Components and Architecture ..................................................................................13
4.4.  Initialisation ..............................................................................................................14
4.5.  Calculation................................................................................................................15

ANNEX 1  Remarks about the mathematical background of some operations of the
UIA2  Algorithm.......................................................................................................................17
1.1.  The function EVAL_M.............................................................................................17
1.2.  The function MUL(V, P, c) ......................................................................................17

ANNEX 2

Implementation options for some operations of the UIA2 Algorithm ................18
2.1.  Procedure Pre_Mul_P...............................................................................................18
2.2.  Function Mul_P ........................................................................................................18

ANNEX 3  Figures of the UEA2 and UIA2 Algorithms........................................................20

ANNEX 4  Simulation Program Listing................................................................................23
4.1.  UEAII .......................................................................................................................23
4.2.  UIAII.........................................................................................................................24

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 5 of 27

REFERENCES

[1]

[2]

[3]

[4]

[5]

[6]

[7]

[8]

3rd Generation Partnership Project; Technical Specification Group Services and
System Aspects; 3G Security; Security Architecture (3G TS 33.102 version 6.3.0).

3rd Generation Partnership Project; Technical Specification Group Services and
System Aspects; 3G Security; Cryptographic Algorithm Requirements; (3G TS
33.105 version 6.0.0).

Specification of the 3GPP Confidentiality and Integrity Algorithms;
Document 1: f8 and f9 specifications; (3GPP TS35.201 Release 6).

Specification of the 3GPP Confidentiality and Integrity Algorithms UEA2 & UIA2.
Document 1: UEA2 and UIA2 specifications.

Specification of the 3GPP Confidentiality and Integrity Algorithms UEA2 & UIA2.
Document 2: SNOW 3G specification.

Specification of the 3GPP Confidentiality and Integrity Algorithms UEA2 & UIA2.
Document 3: Implementors’ Test Data.

Specification of the 3GPP Confidentiality and Integrity Algorithms UEA2 & UIA2.
Document 4: Design Conformance Test Data.

P. Ekdahl and T. Johansson, “A new version of the stream cipher SNOW”, in
Selected Areas in Cryptology (SAC 2002), LNCS 2595, pp. 47–61, Springer-
Verlag.

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 6 of 27

NORMATIVE SECTION

This part of the document contains the normative specification of the Confidentiality and
Integrity algorithms.

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 7 of 27

1.  OUTLINE OF THE NORMATIVE PART

Section 2 introduces the algorithm and describes the notation used in the subsequent sections.

Section 3 specifies the confidentiality algorithm UEA2.

Section 4 specifies the integrity algorithm UIA2.

2.

INTRODUCTORY INFORMATION

2.1.

Introduction

Within the security architecture of the 3GPP system there are standardised algorithms for
confidentiality (f8) and integrity (f9). A first set of algorithms for f8 and f9 (UEA1 and UIA1)
has already been specified [3]. A second set of algorithms for f8 and f9 (UEA2 and UIA2) are
fully specified here: The second set of these algorithms is based on the SNOW 3G algorithm
that is specified in a companion document [5].

The confidentiality algorithm UEA2 is a stream cipher that is used to encrypt/decrypt blocks
of data under a confidentiality key CK. The block of data may be between 1 and 20000 bits
long. The algorithm uses SNOW 3G as a keystream generator

The integrity algorithm UIA2 computes a 32-bit MAC (Message Authentication Code) of a
given input message using an integrity key IK. The approach adopted uses SNOW 3G.

2.2.  Notation

2.2.1.  Radix

We use the prefix 0x to indicate hexadecimal numbers.

2.2.2.  Conventions

We use the assignment operator ‘=’, as used in several programming languages. When we
write

<variable> = <expression>

we mean that <variable> assumes the value that <expression> had before the assignment took
place.  For instance,

x = x + y + 3

means

(new value of x) becomes (old value of x) + (old value of y) + 3.

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 8 of 27

2.2.3.  Bit/Byte ordering

All data variables in this specification are presented with the most significant bit (or byte) on
the left hand side and the least significant bit (or byte) on the right hand side.  Where a
variable is broken down into a number of sub-strings, the left most (most significant) sub-
string is numbered 0, the next most significant is numbered 1 and so on through to the least
significant.

For example an n-bit MESSAGE is subdivided into 64-bit substrings MB0, MB1, MB2, ….
So if we have a message:

0x0123456789ABCDEFFEDCBA98765432108654381AB594FC28786404C50A37…

we have:

MB0 = 0x0123456789ABCDEF

MB1 = 0xFEDCBA9876543210

MB2 = 0x86545381AB594FC2

MB3 = 0x8786404C50A37…

In binary this would be:

000000010010001101000101011001111000100110101011110011011110111111111110

with MB0 = 0000000100100011010001010110011110001001101010111100110111101111

  MB1 = 1111111011011100101110101001100001110110010101000011001000010000

  MB2 = 1000011001010100010100111000000110101011010110010100111111000010

  MB3 = 1000011110000110010000000100110001010000101000110111…

2.2.4.  List of Symbols

=

⊕

||

The assignment operator.

The bitwise exclusive-OR operation

The concatenation of the two operands.

x  The smallest integer greater than or equal to the real number x.

&n

The bitwise AND operation in an n-bit register.

<<n t  t-bit left shift in an n-bit register.

>>n t  t-bit right shift in an n-bit register

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 9 of 27

2.3.  List of Variables

BEARER

the 5-bit input to the UEA2 function.

CK

the 128-bit confidentiality key.

COUNT

the 32-bit time variant input to the UEA2 and UIA2 functions (COUNT-
C for UEA2 and COUNT-I for UIA2)

DIRECTION

the 1-bit input to both the UEA2 and UIA2 functions indicating the
direction of transmission (uplink or downlink).

FRESH

the 32-bit random input to the UIA2 function.

IBS

IK

KS[i]

LENGTH

MAC-I

the input bit stream to the UEA2 function.

the 128-bit integrity key.

the ith bit of keystream produced by the keystream generator.

the input to the UEA2 and UIA2 functions which specifies the number of
bits in the input bitstream (1-20000).

the 32-bit message authentication code (MAC) produced by the integrity
function UIA2.

MESSAGE

the input bitstream of LENGTH bits that is to be processed by the UIA2
function.

OBS

the output bit stream from the UEA2 function.

z1, z2, …

the 32-bit words forming the keystream sequence of SNOW 3G. The
word produced first is z1, the next word z2 and so on.

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 10 of 27

3.

CONFIDENTIALITY ALGORITHM UEA2

3.1.

Introduction

The confidentiality algorithm UEA2 is a stream cipher that encrypts/decrypts blocks of data
between 1 and 20000 bits in length.

3.2.

Inputs and Outputs

The inputs to the algorithm are given in Table 1, the output in Table 2:

Parameter

Size (bits)  Comment

COUNT-C

32  Frame dependent input COUNT-

C[0]…COUNT-C[31]

BEARER

5  Bearer identity BEARER[0]…BEARER[4]

DIRECTION

1  Direction of transmission DIRECTION[0]

CK

128  Confidentiality key CK[0]….CK[127]

LENGTH

16  The number of bits to be encrypted/decrypted

IBS

LENGTH  Input bit stream IBS[0]….IBS[LENGTH-1]

Table 1. UEA2 inputs

Parameter

Size (bits)  Comment

OBS

LENGTH  Output bit stream

OBS[0]….OBS[LENGTH-1]

Table 2. UEA2 output

3.3.  Components and Architecture

The keystream generator is based on SNOW 3G that is specified in [5]. SNOW 3G is a word
oriented stream cipher and generates a keystream in multiples of 32-bits.

3.4.

Initialisation

In this section we define how the keystream generator is initialised with the key variables
before the generation of keystream bits.

All variables have length 32 and are presented with the most significant bit on the left hand
side and the least significant bit on the right hand side.

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 11 of 27

K3 = CK[0] || CK[1] || CK[2] || … || CK[31]

K2 = CK[32] || CK[33] || CK[34] || … || CK[63]

K1 = CK[64] || CK[65] || CK[66] || … || CK[95]

K0 = CK[96] || CK[97] || CK[98] || … || CK[127]

IV3 = COUNT-C[0] || COUNT-C[1] || COUNT-C[2] || … || COUNT-C[31]

IV2 = BEARER[0] || BEARER[1] || … || BEARER[4] || DIRECTION[0] || 0 || … || 0

IV1 = COUNT-C[0] || COUNT-C[1] || COUNT-C[2] || … || COUNT-C[31]

IV0 = BEARER[0] || BEARER[1] || … || BEARER[4] || DIRECTION[0] || 0 || … || 0

SNOW 3G is initialised as described in document [5].

3.5.  Keystream Generation

Set L = LENGTH / 32.

SNOW 3G is run as described in document [5] to produce the keystream consisting of the 32-
bit words z1 … zL. The word produced first is z1, the next word z2 and so on.

The sequence of keystream bits is KS[0] … KS[LENGTH-1], where KS[0] is the most
significant bit and KS[31] is the least significant bit of z1, KS[32] is the most significant bit of
z2 and so on.

3.6.  Encryption/Decryption

Encryption/decryption operations are identical operations and are performed by the exclusive-
OR of the input data (IBS) with the generated keystream (KS).

For each integer i with 0 ≤ i ≤ LENGTH-1 we define:

OBS[i] = IBS[i] ⊕ KS[i].

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 12 of 27

4.

INTEGRITY ALGORITHM UIA2

4.1.

 Introduction

The integrity algorithm UIA2  computes a Message Authentication Code (MAC) on an input
message under an integrity key IK. The message may be between 1 and 20000 bits in length.

For ease of implementation the algorithm is based on the same stream cipher (SNOW 3G) as
is used by the confidentiality algorithm UEA2.

4.2.

Inputs and Outputs

The inputs to the algorithm are given in table 3, the output in table 4:

Parameter

Size (bits)  Comment

COUNT-I

32  Frame dependent input  COUNT-I[0]…COUNT-

I[31]

FRESH

32  Random number FRESH[0]…FRESH[31]

DIRECTION

1  Direction of transmission DIRECTION[0]

IK

128  Integrity key  IK[0]…IK[127]

LENGTH

64  The number of bits to be ‘MAC’d

MESSAGE

LENGTH  Input bit stream

Table 3. UIA2 inputs

Parameter

Size (bits)  Comment

MAC-I

32  Message authentication code MAC-I[0]…MAC-

I[31]

Table 4. UIA2 output

4.3.  Components and Architecture

4.3.1.  SNOW 3G

The integrity function uses SNOW 3G that is specified in [5]. SNOW 3G is a word oriented
stream cipher and generates from the key and an initialisation variable five 32-bit-words z1, z2,
z3, z4 and z5.

4.3.2.  MULx

MULx maps 128 bits to 64 bits. Let V and c be 64-bit input values. Then MULx is defined:
If the leftmost (i.e. the most significant) bit of V equals 1, then

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 13 of 27

  MULx(V, c) = (V <<64 1) ⊕ c,
else
  MULx(V, c) = V <<64 1.

4.3.3.  MULxPOW

MULxPOW maps 128 bits and a positive integer i to 64 bit. Let V and c be 64-bit input
values, then MULxPOW(V,  i, c) is recursively defined:
If i equals 0, then
  MULxPOW(V, i, c) = V,
else
  MULxPOW(V, i, c) = MULx(MULxPOW(V, i – 1, c), c).

4.3.4.  MUL

MUL maps 192 bits to 64 bit. Let V, P and c be 64-bit input values.

Then the 64-bit output result of MUL(V, P, c) is computed as follows:

•

•

result = 0.

for i = 0 to 63 inclusive

o

if (P >>64 i) &64 0x01 equals 0x01, then

result = result ⊕ MULxPOW(V, i, c).

4.4.

Initialisation

In this section we define how the keystream generator is initialised with the key and
initialisation variables before the generation of keystream bits.

All variables have length 32 bits and are presented with the most significant bit on the left
hand side and the least significant bit on the right hand side.

K3  =

K2  =

K1  =

K0  =

IK[0]

||  IK[1]

||  IK[2]

||  …

||  IK[31]

IK[32]

||  IK[33]

||  IK[34]

||  …

||  IK[63]

IK[64]

||  IK[65]

||  IK[66]

||  …

||  IK[95]

IK[96]

||  IK[97]

||  IK[98]

||  …

||  IK[127]

IV3

IV2

=  COUNT-I[0] || COUNT-I[1] || COUNT-I[2] || … || COUNT-I[31]

=  FRESH[0] || FRESH[1] || FRESH[2] || … || FRESH[31]

IV1

=  DIRECTION[0] ⊕ COUNT-I[0] || COUNT-I[1] || COUNT-I[2] || … || COUNT-I[31]

IV0

=  FRESH[0] || FRESH[1] || … || FRESH[15] || FRESH[16] ⊕ DIRECTION[0] || FRESH[17] || … || FRESH[31]

SNOW 3G is initialised as described in document [5].

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 14 of 27

4.5.  Calculation

Set D = LENGTH / 64 + 1.

SNOW 3G is run as described in document [5] in order to produce 5 keystream words z1, z2,
z3, z4, z5.

Set  P = z1 || z2

and  Q = z3 || z4.

Let OTP[0], OTP[1], OTP[2], …, OTP[31] be bit-variables such that

z5 = OTP[0] || OTP[1] ||… || OTP[31],

i.e. OTP[0] is the most and OTP[31] the least significant bit of z5.

For 0 ≤ i ≤ D - 3 set

Mi = MESSAGE[64i] || MESSAGE[64i+1] ||...|| MESSAGE[64i+63].

Set

MD-2 = MESSAGE[64(D-2)] || … || MESSAGE[LENGTH-1] || 0…0.

Let LENGTH[0], LENGTH[1], …, LENGTH[63] be the bits of the 64-bit representation of
LENGTH, where LENGTH[0] is the most and LENGTH[63] is the least significant bit.

Set MD-1 = LENGTH[0] || LENGTH[1] || … || LENGTH[63].

Compute the function Eval_M:

•  Set the 64-bit variable EVAL = 0.

•  for i = 0 to D – 2 inclusive:

o  EVAL = Mul(EVAL ⊕ Mi, P, 0x000000000000001b ).

Set EVAL = EVAL ⊕ MD - 1

Now we multiply EVAL by Q:

EVAL = Mul(EVAL, Q, 0x000000000000001b).

Let EVAL = e0 || e1 || … || e63 with e0 the most and e63 the least significant bit.

For 0 ≤ i ≤ 31, set

The bits e32, …, e63 are discarded.

MAC-I[i] = ei ⊕ OTP[i].

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 15 of 27

INFORMATIVE SECTION

This part of the document is purely informative and does not form part of the normative
specification of the Confidentiality and Integrity algorithms.

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 16 of 27

ANNEX 1
Remarks about the mathematical background of some operations of
the UIA2  Algorithm

1.1.  The function EVAL_M

The first part (the function EVAL_M) of the calculations for the UIA2 algorithm corresponds
to the evaluation of a polynomial at a secret point: From the bits and the length of
MESSAGE a polynomial M∈GF(264)[X] is defined. This polynomial is evaluated at the point
P ∈ GF(264) defined by z1||z2.

This can be seen as follows:

Consider the Galois Field GF(264) where elements of the field are represented as polynomials
over GF(2) modulo the irreducible polynomial x64 + x4 + x3 + x + 1.

Variables consisting of 64 bits can be mapped to this field by interpreting the bits as the
coefficients of the corresponding polynomial.

For example for 0 ≤ i ≤ D-3 the variable
Mi = MESSAGE[64i] || MESSAGE[64i+1] ||...|| MESSAGE[64i+62] || MESSAGE[64i+63]
is interpreted as
MESSAGE[64i]x63+ MESSAGE[64i+1]x62 + ... + MESSAGE[64i+62]x +
MESSAGE[64i+63].

Construct the polynomial M of degree D-1 in GF(264)[X] as
M(X) = M0XD-1 + M1XD-2+ … + MD-2X + MD-1.

Evaluate the polynomial M at the point P, i.e. compute
M(P) = M0PD-1 + M1PD-2 + … + MD-2P + MD-1= (…(M0P + M1)P + M2)P + … + MD-2)P +
MD-1.

This is done in the function Eval_M in 4.5.

1.2.  The function MUL(V, P, c)

The function MUL(V, P, c) (see 4.3.4) corresponds to a multiplication of V by P in GF(264).
Here GF(264) is described as GF(2)(β) where β is a root of the GF(2)[x] polynomial x64 +
c0x63+ … + c62x +c63 and c = c0 || c1 || … || c63.

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 17 of 27

ANNEX 2
Implementation options for some operations of the UIA2 Algorithm

The function MUL (see 4.3.4) can be implemented using table lookups. This might accelerate
execution of the function EVAL_M, as for the evaluation of the polynomial only
multiplication by a constant factor P is needed.

There are different possible sizes for the tables. Here we use 8 tables with 256 entries, but for
example it is also possible to use 16 tables with 16 entries.

In order to execute MUL by table-lookups first Pre_Mul_P (see 2.1) is executed, which
generates the tables. Then in MUL_P (see 2.2) the multiplication is performed by 8 table-
lookups and an xor of the results.

Hence in 4.5 instead of EVAL = Mul(EVAL ⊕ Mi, P, 0x1b ) we can use EVAL =
Mul_P(EVAL ⊕ Mi).

2.1.  Procedure Pre_Mul_P

In order to be able to compute Mul_P (see 2.2) the procedure Pre_Mul_P is executed once
before the first call of Mul_P.
Pre_Mul_P computes from the 64-bit input P eight tables PM[0], PM[1], …, PM[7]. Each of
these tables contains 256 entries PM[j][0], PM[j][1], …, PM[j][255] with 64 bits.

For 0 ≤ j ≤ 7 and 0 ≤ X ≤ 255 the value PM[j][X] corresponds to X P x8j.

Let r be the 64-bit value 0x000000000000001b.

•  The tables are computed as follows:

PM[0][0] = PM[1][0] = PM[2][0] = PM[3][0] = PM[4][0] = PM[5][0] = PM[6][0] =
PM[7][0] = 0.

•  PM[0][1] = P.

•  for i = 1 to 63 inclusive:

o  PM[i >>8 3][1 <<8 (i &8 0x07)] = PM[(i – 1) >>8 3][1 <<8 ((i – 1) &8 0x07)] <<64 1.

o  if the leftmost bit of PM[(i – 1) >>8 3][1 << ((i – 1) &8 0x07)] equals 1, then
  PM[i >>8 3][1 <<8 (i &8 0x07)] = PM[i >>8 3][1 << (i &8 0x07)] ⊕ r.

•  for i = 0 to 7 inclusive

o  for j = 1 to 7 inclusive

(cid:1)  for k = 1 to (1 <<8 j) – 1 inclusive

•  PM[i][(1 <<8 j) + k] = PM[i][1 <<8 j] ⊕ PM[i][k].

2.2.  Function Mul_P

The function Mul_P maps a 64-bit input X to a 64-bit output.

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 18 of 27

Let X = X0 || X1 || X2 || X3 || X4|| X5 || X6|| X7, with X0 the most and X7 the least significant byte.

Compute Mul_P(X) as

Mul_P(X) = PM[0][X7] ⊕ PM[1][X6] ⊕ PM[2][X5] ⊕ PM[3][X4] ⊕ PM[4][X3] ⊕

PM[5][X2] ⊕ PM[6][X1] ⊕ PM[7][X0].

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 19 of 27

ANNEX 3
Figures of the UEA2 and UIA2 Algorithms

COUNT-C

||  BEARER || DIRECTION || 0 ... 0

IV3

||

IV2

||

||

COUNT-C

||  BEARER || DIRECTION || 0 ... 0

IV1

||

IV0

CK

K3

||  K2

||  K1

||  K0

SNOW 3G

z1

||

z2

||

...

||

zL

KS[0] ... KS[31]

||  KS[32] ... KS[63]

||

...

||  KS[32L-32] ... KS[32L-1]

Figure 1: UEA2 Keystream Generator

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 20 of 27

COUNT-I

||  FRESH

||

DIRECTION || 0....0
 ⊕
COUNT-I

IV3

||

IV2

||

IV1

||

||

0000000000000000 || DIRECTION || 000000000000000
⊕
 FRESH

IV0

IK

K3

||  K2

||  K1

||  K0

SNOW 3G

z1

||

z2

            P

z3

||

||

||

Q

z4

||

z5

||  OTP[0] ... OTP[31]

Figure 2: UIA2 Integrity function, part 1

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 21 of 27

z1 || z2

P

MESSAGE || 0 ... 0

M0 || ... || MD-2

EVAL_M

LENGTH

MD-1

z3 || z4

Q

z5

⊕

MUL

e0 || e1 || ... || e31

(left 32 bits)

OTP[0] || ... || OTP[31]

⊕

MAC-I

Figure 3: UIA2 Integrity function, part 2

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 22 of 27

ANNEX 4
Simulation Program Listing

4.1.  UEAII

4.1.1  Header File

/*---------------------------------------------------------
 *
 *---------------------------------------------------------*/
#ifndef F8_H_
#define F8_H_

f8.h

#include "SNOW_3G.h"

/* f8.
 * Input key: 128 bit Confidentiality Key.
 * Input count:32-bit Count, Frame dependent input.
 * Input bearer: 5-bit Bearer identity (in the LSB side).
 * Input dir:1 bit, direction of transmission.
 * Input data: length number of bits, input bit stream.
 * Input length: 16 bit Length, i.e., the number of bits to be encrypted or
 *               decrypted.
 * Output data: Output bit stream. Assumes data is suitably memory
 * allocated.
 * Encrypts/decrypts blocks of data between 1 and 20000 bits in length as
 * defined in Section 3.
 */

void f8( u8 *key, int count, int bearer, int dir, u8 *data, int length );

#endif

4.1.2  Code

f8.c

/*---------------------------------------------------------
 *
 *---------------------------------------------------------*/
#include "f8.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* f8.
 * Input key: 128 bit Confidentiality Key.
 * Input count:32-bit Count, Frame dependent input.
 * Input bearer: 5-bit Bearer identity (in the LSB side).
 * Input dir:1 bit, direction of transmission.
 * Input data: length number of bits, input bit stream.
 * Input length: 16 bit Length, i.e., the number of bits to be encrypted or
 *               decrypted.
 * Output data: Output bit stream. Assumes data is suitably memory
 * allocated.
 * Encrypts/decrypts blocks of data between 1 and 20000 bits in length as
 * defined in Section 3.
 */

void f8( u8 *key, int count, int bearer, int dir, u8 *data, int length )
{
  u32 K[4],IV[4];
  int n = ( length + 31 ) / 32;
  int i=0;
  u32 *KS;

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 23 of 27

  /*Initialisation*/

  /* Load the confidentiality key for SNOW 3G initialization as in section
3.4. */
  memcpy(K+3,key+0,4);  /*K[3] = key[0]; we assume
K[3]=key[0]||key[1]||...||key[31] , with key[0] the
                         * most important bit of key*/
  memcpy(K+2,key+4,4);  /*K[2] = key[1];*/
  memcpy(K+1,key+8,4);  /*K[1] = key[2];*/
  memcpy(K+0,key+12,4); /*K[0] = key[3]; we assume
K[0]=key[96]||key[97]||...||key[127] , with key[127] the
                 * least important bit of key*/

  /* Prepare the initialization vector (IV) for SNOW 3G initialization as in
section 3.4. */
  IV[3] = count;
  IV[2] = (bearer << 27) | ((dir & 0x1) << 26);

  IV[1] = IV[3];
  IV[0] = IV[2];

  /* Run SNOW 3G algorithm to generate sequence of key stream bits KS*/
  Initialize(K,IV);

  KS = (u32 *)malloc(4*n);
  GenerateKeystream(n,(u32*)KS);

  /* Exclusive-OR the input data with keystream to generate the output bit
stream */
  for (i=0;i<n*4;i++)
    data[i] ^= *(((u8*)KS)+i);

  free(KS);
}

/* End of f8.c */

4.2.  UIAII

4.2.1  Header File

/*---------------------------------------------------------
 *
 *---------------------------------------------------------*/
#ifndef F9_H_
#define F9_H_

f9.h

#include "SNOW_3G.h"

/* f9.
 * Input key: 128 bit Integrity Key.
 * Input count:32-bit Count, Frame dependent input.
 * Input fresh: 32-bit Random number.
 * Input dir:1 bit, direction of transmission (in the LSB).
 * Input data: length number of bits, input bit stream.
 * Input length: 64 bit Length, i.e., the number of bits to be MAC'd.
 * Output  : 32 bit block used as MAC
 * Generates 32-bit MAC using UIA2 algorithm as defined in Section 4.
 */

u8* f9( u8* key, int count, int fresh, int dir, u8 *data, u64 length);

#endif

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 24 of 27

4.2.2  Code

f9.c

/*---------------------------------------------------------
 *
 *---------------------------------------------------------*/
#include "f9.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

/* MUL64x.
 * Input V: a 64-bit input.
 * Input c: a 64-bit input.
 * Output : a 64-bit output.
 * A 64-bit memory is allocated which is to be freed by the calling
 * function.
 * See section 4.3.2 for details.
 */

u64 MUL64x(u64 V, u64 c)
{
   if ( V & 0x8000000000000000 )

return (V << 1) ^ c;

   else

return V << 1;

}

/* MUL64xPOW.
 * Input V: a 64-bit input.
 * Input i: a positive integer.
 * Input c: a 64-bit input.
 * Output : a 64-bit output.
 * A 64-bit memory is allocated which is to be freed by the calling
function.
 * See section 4.3.3 for details.
 */

u64 MUL64xPOW(u64 V, u8 i, u64 c)
{
   if ( i == 0)

return V;

   else

return MUL64x( MUL64xPOW(V,i-1,c) , c);

}

/* MUL64.
 * Input V: a 64-bit input.
 * Input P: a 64-bit input.
 * Input c: a 64-bit input.
 * Output : a 64-bit output.
 * A 64-bit memory is allocated which is to be freed by the calling
 * function.
 * See section 4.3.4 for details.
 */

u64 MUL64(u64 V, u64 P, u64 c)
{
   u64 result = 0;
   int i = 0;

   for ( i=0; i<64; i++)
   {

if( ( P>>i ) & 0x1 )
   result ^= MUL64xPOW(V,i,c);

   }

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 25 of 27

   return result;
}

/* mask32bit.
 * Input n: an integer in 1-32.
 * Output : a 32 bit mask.
 * Prepares a 32 bit mask with required number of 1 bits on the MSB side.
 */
u32 mask32bit(int n)
{
  u32 mask=0x0;
  if ( n%32 == 0 )
   return 0xffffffff;

  while (n--)
    mask =  (mask>>1) ^ 0x80000000;
  return mask;
}

/* f9.
 * Input key: 128 bit Integrity Key.
 * Input count:32-bit Count, Frame dependent input.
 * Input fresh: 32-bit Random number.
 * Input dir:1 bit, direction of transmission (in the LSB).
 * Input data: length number of bits, input bit stream.
 * Input length: 64 bit Length, i.e., the number of bits to be MAC'd.
 * Output  : 32 bit block used as MAC
 * Generates 32-bit MAC using UIA2 algorithm as defined in Section 4.
 */
u8* f9( u8* key, int count, int fresh, int dir, u8 *data, u64 length)
{
  u32 K[4],IV[4], z[5];
  int i=0,D;
  static u32 MAC_I = 0; /* static memory for the result */
  u64 EVAL;
  u64 V;
  u64 P;
  u64 Q;
  u64 c;

  u64 M_D_2;
  int rem_bits = 0;
  u32 mask = 0;
  u32 *message;

  message = (u32*)data; /* To operate 32 bit message internally. */

  /* Load the Integrity Key for SNOW3G initialization as in section 4.4. */
  memcpy(K+3,key+0,4);  /*K[3] = key[0]; we assume
K[3]=key[0]||key[1]||...||key[31] , with key[0] the
                         * most important bit of key*/
  memcpy(K+2,key+4,4);  /*K[2] = key[1];*/
  memcpy(K+1,key+8,4);  /*K[1] = key[2];*/
  memcpy(K+0,key+12,4); /*K[0] = key[3]; we assume
K[0]=key[96]||key[97]||...||key[127] , with key[127] the
                         * least important bit of key*/

  /* Prepare the Initialization Vector (IV) for SNOW3G initialization as in
section 4.4. */
  IV[3] = count;
  IV[2] = fresh;
  IV[1] = count ^ ( dir << 31 ) ;
  IV[0] = fresh ^ (dir << 15);

  z[0] = z[1] = z[2] = z[3] = z[4] = 0;

  /* Run SNOW 3G to produce 5 keystream words z_1, z_2, z_3, z_4 and z_5. */
page 26 of 27
3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

  Initialize(K,IV);
  GenerateKeystream(5,z);

  P = (u64)z[0] << 32 | (u64)z[1];
  Q = (u64)z[2] << 32 | (u64)z[3];

  /* Calculation */

  D = ceil( length / 64.0 ) + 1;
  EVAL = 0;

  c = 0x1b;

  /* for 0 <= i <= D-3 */
  for (i=0;i<D-2;i++)
  {
     V = EVAL ^ ( (u64)message[2*i] << 32 | (u64)message[2*i+1] );
     EVAL = MUL64(V,P,c);
  }

  /* for D-2 */
  rem_bits = length % 64;
  if (rem_bits == 0)
     rem_bits = 64;

  mask = mask32bit(rem_bits%32);

  if (rem_bits > 32)
  {
    M_D_2 = ( (u64) message[2*(D-2)] << 32 ) |  (u64) (message[2*(D-2)+1] &
mask);
  } else
  {
    M_D_2 = ( (u64) message[2*(D-2)] & mask) << 32 ;
  }

  V = EVAL ^ M_D_2;
  EVAL = MUL64(V,P,c);

  /* for D-1 */
  EVAL ^= length;

  /* Multiply by Q */
  EVAL = MUL64(EVAL,Q,c);

  MAC_I = (u32)(EVAL >> 32) ^ z[4];

  return (u8*) &MAC_I;
}

/* End of f9.c */

/*------------------------------------------------------------------------*/

3GPP Confidentiality and Integrity Algorithms UEA2&UIA2
UEA2 and UIA2 Specification Version 1.1

page 27 of 27


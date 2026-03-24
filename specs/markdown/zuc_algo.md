ETSI/SAGE
Specification

Version:  1.6
Date: 28th June 2011

Specification of the 3GPP Confidentiality and
Integrity Algorithms 128-EEA3 & 128-EIA3.
Document 2: ZUC Specification

     The ZUC algorithm is the core of the
standardised 3GPP Confidentiality and Integrity
algorithms 128-EEA3 & 128-EIA3.

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 1 of 18

Document History

18-06-2010

Publication

26-07-2010

Improvements to C code

27-07-2010

Minor corrections to C code

30-07-2010

Corrected preface

04-01-2011

A modification of ZUC in the initialization

28-06-2011

Minor adjustment to C code

1.0

1.2

1.3

1.4

1.5

1.6

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 2 of 18

Blank Page

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 3 of 18

PREFACE

This specification has been prepared by the 3GPP Task Force, and gives a detailed
specification of the 3GPP algorithm ZUC. ZUC is a stream cipher that forms the heart of the
3GPP confidentiality algorithm 128-EEA3 and the 3GPP integrity algorithm 128-EIA3. This
document is the second of three, which between them form the entire specification of the
3GPP Confidentiality and Integrity Algorithms:

•  Specification of the 3GPP Confidentiality and Integrity Algorithms 128-EEA3 &

128-EIA3.
Document 1: 128-EEA3 and 128-EIA3 Specifications.

•  Specification of the 3GPP Confidentiality and Integrity Algorithms 128-EEA3 &

128-EIA3.
Document 2: ZUC Specification.

•  Specification of the 3GPP Confidentiality and Integrity Algorithms 128-EEA3 &

128-EIA3.
Document 3: Implementor’s Test Data.

The normative part of the specification of ZUC is in the main body of this document. Annex
A, which is purely informative, contains an implementation program listing of the
cryptographic algorithm specified in the main body of this document, written in the
programming language C.

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 4 of 18

TABLE OF CONTENTS

1

Introduction ........................................................................................................................7

2  Notations and conventions..................................................................................................7
2.1  Radix...........................................................................................................................7
2.2  Bit ordering .................................................................................................................7
2.3  Notations.....................................................................................................................7

3  Algorithm description.........................................................................................................9
3.1  General structure of the algorithm ..............................................................................9
3.2  The linear feedback shift register (LFSR) ..................................................................9
3.3  The Bit-reorganization..............................................................................................10
3.4  The nonlinear function F ..........................................................................................11
3.5  Key loading...............................................................................................................13
3.6  The execution of ZUC ..............................................................................................14

Appendix A: A C implementation of ZUC ..............................................................................15

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 5 of 18

NORMATIVE SECTION

This part of the document contains the normative specification of the ZUC algorithm.

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 6 of 18

1  Introduction

ZUC is a word-oriented stream cipher. It takes a 128-bit initial key and a 128-bit initial vector
(IV) as input, and outputs a keystream of 32-bit words (where each 32-bit word is hence
called a key-word). This keystream can be used for encryption/decryption.

The execution of ZUC has two stages: initialization stage and working stage. In the first
stage, a key/IV initialization is performed, i.e., the cipher is clocked without producing output
(see section 3.6.1). The second stage is a working stage. In this stage, with every clock pulse,
it produces a 32-bit word of output (see section 3.6.2).

2  Notations and conventions

2.1  Radix

In this document, integers are represented as decimal numbers unless specified otherwise. We
use the prefix “0x” to indicate hexadecimal numbers, and the subscript “2” to indicate a
number in binary representation.

Example  1

Integer a can be written in different representations:

a = 1234567890                                                  decimal representation

= 0x499602D2                                                hexadecimal representation

= 10010011001011000000010110100102      binary representation

2.2  Bit ordering

In this document, all data variables are presented with the most significant bit(byte) on the left
hand side and the least significant bit(byte) on the right hand side.

Example  2  Let a=10010011001011000000010110100102. Then its most significant bit is
1 (the leftmost bit) and its least significant bit is 0 (the rightmost bit).

2.3  Notations

+       The addition of two integers.

ab  The product of integers a and b.

=

The assignment operator.

mod

The modulo operation of integers.

⊕   The bit-wise exclusive-OR operation of integers.

⊞   The modulo 232 addition .

a || b

The concatenation of strings a and b.

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 7 of 18

aH

aL

The leftmost 16 bits of integer a.

The rightmost 16 bits of integer a.

a <<<n k

The k-bit cyclic shift of the n bit register a to the left.

a >> 1   The l-bit right shift of integer a.

     (a1, a2,…, an)→ (b1, b2,…, bn)  The assignment of the values of ai to bi in parallel.

 For any two strings a and b, the presentation of string c created by the

Example  3
concatenation of a and b also follows the rules defined in section 2.2 i.e., the most significant
digits are on the left hand side and the least significant digits are on the right hand side. For
instance,

a=0x1234,

b=0x5678,

c = a||b =0x12345678.

a=10010011001011000000010110100102

aH=10010011001011002,

aL=00000010110100102.

a=110010011001011000000010110100102.

Then we have

Example  4  Let

Then we have

Example  5  Let

Then we have

a >> 1=11001001100101100000001011010012.

Example  6  Let a0, a1, …, a15, b0, b1, …, b15 be all integer variables. Then

(a0, a1, …, a15)→ (b0, b1, …, b15)

will result in bi=ai, 0≤ i≤ 15.

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 8 of 18

3  Algorithm description

3.1  General structure of the algorithm

ZUC has three logical layers, see Fig.  1. The top layer is a linear feedback shift register
(LFSR) of 16 stages, the middle layer is for bit-reorganization ( BR), and the bottom layer is a
nonlinear function F.

Figure 1. General structure of ZUC

3.2  The linear feedback shift register (LFSR)

The linear feedback shift register (LFSR) has 16 of 31-bit cells (s0, s1,…, s15). Each cell si (0≤

i≤ 15) is restricted to take values from the following set

The LFSR has 2 modes of operations: the initialization mode and the working mode.

{1,2,3, …,231– 1}.

In the initialization mode, the LFSR receives a 31-bit input word u, which is obtained by
removing the rightmost bit from the 32-bit output W of  the nonlinear function F, i.e.,
u=W>>1. More specifically, the initialization mode works as follows:

LFSRWithInitialisationMode(u)
{

1.

v=215s15+217s13+221s10+220s4+(1+28)s0 mod (231-1);

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 9 of 18

s16=(v+u) mod (231-1);

If s16=0, then set s16=231-1;

(s1,s2, …,s15,s16)→ (s0,s1, …,s14,s15).

2.

3.

4.

}

In the working mode, the LFSR does not receive any input, and it works as follows:

LFSRWithWorkMode()
{

s16=215s15+217s13+221s10+220s4+(1+28)s0 mod (231-1);
If s16=0, then set s16=231-1;

(s1,s2, …,s15,s16)→ (s0,s1, …,s14,s15).

1.

2.

3.

}

Informative note: Since the multiplication of a 31-bit string s by 2i over GF(231-1) can be
implemented by a cyclic shift of s to the left by i bits, only addition modulo 231-1 is needed in
step 1 of the above functions.  More precisely, step 1 of the function
LFSRWithInitialisationMode can be implemented by

v=(s15<<<3115)+(s13<<<3117)+(s10<<<3121)+(s4<<<3120)+(s0 <<<318)+s0 mod (231-1),

and the same implementation is needed for step 1 of the function LFSRWithWorkMode.

Informative note: For two elements a, b over GF(231-1), the computation of v=a+b mod (231-1)
can be done by (1) compute v=a+b; and (2) if the carry bit is 1, then set v=v+1. Alternatively
(and better if the implementation should resist possible timing attacks): (1) compute w=a+b,
where w is a 32-bit value; and (2) set v = (least significant 31 bits of w) + (most significant bit
of w).

3.3  The bit-reorganization

The middle layer of the algorithm is the bit-reorganization. It extracts 128 bits from the cells
of the LFSR and forms 4 of 32-bit words, where the first three words will be used by the
nonlinear function F in the bottom layer, and the last word will be involved in producing the
keystream.

Let s0, s2, s5, s7, s9, s11, s14, s15 be  8  cells of LFSR as in section 3.2. Then the bit-
reorganization forms 4 of 32-bit words X0, X1, X2, X3 from the above cells as follows:

Bitreorganization()
{

1．  X0=s15H  || s14L;

2.  X1=s11L || s9H;

3．  X2=s7L || s5H;

4.  X3=s2L ||s0H.

}

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 10 of 18

Note: The si are 31-bit integers, so siH means bits 30...15 and not 31...16 of si, for 0≤ i≤ 15.

3.4  The nonlinear function F

The nonlinear function F has 2 of 32-bit memory cells R1 and R2. Let the inputs to F be X0, X1
and X2, which come from the outputs of the bit-reorganization (see section 3.3), then the
function F outputs a 32-bit word W. The detailed process of F is as follows:

F (X0, X1, X2)
{

1.  W=( X0⊕ R1) ⊞ R2;

2.  W1= R1⊞X1;

3.  W2= R2⊕ X2;

4.  R1=S(L1(W1L||W2H));

5.  R2=S(L2(W2L||W1H)).

}

where S is a 32×32 S-box, see section 3.4.1, L1 and L2 are linear transforms as defined in
section 3.4.2.

3.4.1  The S-box S

The  32×32 S-box S is composed of 4 juxtaposed  8×8 S-boxes, i.e., S=(S0,S1,S2,S3), where
S0=S2, S1=S3. The definitions of S0 and S1 can be found in table 3.1 and table 3.2 respectively.

Let x be an 8-bit input to S0 (or S1). Write x into two hexadecimal digits as x=h||l, then the
entry at the intersection of the h-th row and the l-th column in table 3.1 (or table 3.2) is the
output of S0 (or S1).

Example  7

S0(0x12)=0xF9 and S1(0x34)=0xC0.

Let the 32-bit input X and the 32-bit output Y of the S-box S be as follows:

X = x0 || x1 || x2 || x3,

Y = y0 || y1 || y2 || y3,

where xi and yi are all bytes, i=0,1,2,3. Then we have

yi=Si(xi), i=0,1,2,3.

Example  8  Let X=0x12345678 be a 32-bit input to the S-box and Y its 32-bit output. Then
we have

Y=S(X)=S0(0x12)||S1(0x34)||S2(0x56)||S3(0x78)=0xF9C05A4E.

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 11 of 18

Table 3.1. The S-box S0

0

1   2   3   4

5

6  7

8

9  A  B  C  D   E   F

3E   72   5B   47   CA  E0  00  33  04  D1  54  98  09  B9   6D   CB

7B   1B   F9   32   AF  9D  6A  A5  B8  2D  FC  1D  08  53   03   90

4D   4E   84   99   E4  CE  D9  91  DD  B6  85  48  8B  29   6E   AC

CD   C1   F8   1E   73  43  69  C6  B5  BD  FD  39  63  20   D4   38

76   7D   B2   A7   CF  ED  57  C5  F3  2C  BB  14  21  06   55   9B

E3   EF   5E   31   4F  7F  5A  A4  0D  82  51  49  5F  BA  58   1C

4A   16   D5   17   A8  92  24  1F  8C  FF  D8  AE  2E  01   D3   AD

3B   4B  DA  46   EB  C9  DE  9A  8F  87  D7  3A  80  6F   2F   C8

B1   B4   37   F7   0A  22  13  28  7C  CC  3C  89  C7  C3   96   56

07   BF   7E   F0   0B  2B  97  52  35  41  79  61  A6  4C   10   FE

BC   26   95   88   8A  B0  A3  FB  C0  18  94  F2  E1  E5   E9   5D

D0   DC  11   66   64  5C  EC  59  42  75  12  F5  74  9C  AA  23

0E   86   AB  BE   2A  02  E7  67  E6  44  A2  6C  C2  93   9F   F1

F6   FA   36   D2   50  68  9E  62  71  15  3D  D6  40  C4   E2   0F

8E   83   77   6B   25  05  3F  0C  30  EA  70  B7  A1  E8   A9   65

8D   27   1A  DB  81  B3  A0  F4  45  7A  19  DF  EE  78   34   60

Table 3.2. The S-box S1

0   1   2   3   4

5

6

7

8

9  A  B  C  D   E   F

55   C2   63   71   3B  C8  47  86  9F  3C  DA  5B  29  AA  FD   77

8C   C5   94   0C   A6  1A  13  00  E3  A8  16  72  40  F9   F8   42

44   26   68   96   81  D9  45  3E  10  76  C6  A7  8B  39   43   E1

3A   B5   56   2A   C0  6D  B3  05  22  66  BF  DC  0B  FA   62   48

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

A

B

C

D

E

F

0

1

2

3

4   DD  20   11   06   36  C9  C1  CF  F6  27  52  BB  69  F5   D4   87

5

6

7F   84   4C   D2   9C  57  A4  BC  4F  9A  DF  FE  D6  8D   7A   EB

2B   53   D8   5C   A1  14  17  FB  23  D5  7D  30  67  73   08   09

7   EE   B7   70   3F   61  B2  19  8E  4E  E5  4B  93  8F  5D   DB  A9

8   AD  F1   AE   2E   CB  0D  FC  F4  2D  46  6E  1D  97  E8   D1   E9

9

A

4D   37   A5   75   5E  83  9E  AB  82  9D  B9  1C  E0  CD   49   89

01   B6  BD  58   24  A2  5F  38  78  99  15  90  50  B8   95   E4

B   D0   91   C7   CE  ED  0F  B4  6F  A0  CC  F0  02  4A  79   C3   DE

C   A3   EF   EA   51   E6  6B  18  EC  1B  2C  80  F7  74  E7   FF   21

D

E

F

5A   6A   54   1E   41  31  92  35  C4  33  07  0A  BA  7E   0E   34

88   B1   98   7C   F3  3D  60  6C  7B  CA  D3  1F  32  65   04   28

64   BE  85   9B   2F  59  8A  D7  B0  25  AC  AF  12  03   E2   F2

Note: The entries in the above S-boxes S0 and S1 are all in hexadecimal representation.

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 12 of 18

3.4.2  The linear transforms L1 and L2

Both L1 and L2 are linear transforms from 32-bit words to 32-bit words, and are defined as
follows:

L1(X)=X⊕ (X<<<322)⊕ (X<<<3210)⊕ (X<<<3218)⊕ (X<<<3224),

L2(X)=X⊕ (X<<<328)⊕ (X<<<3214)⊕ (X<<<3222)⊕ (X<<<3230).

3.5  Key loading

The key loading procedure will expand the initial key and the initial vector into 16 of 31-bit
integers as the initial state of the LFSR. Let the 128-bit initial key k and the 128-bit initial
vector iv be

and

k=k0||k1||k2||…||k15

iv= iv0|| iv1|| iv2||…|| iv15

respectively, where ki and ivi, 0≤ i≤ 15, are all bytes. Then k and iv are loaded to the cells s0,
s1, …, s15 of LFSR as follows:

1.  Let D be a 240-bit long constant string composed of 16 substrings of 15 bits:

where

D= d0||d1 ||…||d15,

d0 = 1000100110101112,

d1 = 0100110101111002,

d2 = 1100010011010112,

d3 = 0010011010111102,

d4 = 1010111100010012,

d5 = 0110101111000102,

d6 = 1110001001101012,

d7 = 0001001101011112,

d8= 1001101011110002,

d9 = 0101111000100112,

d10 = 1101011110001002,

d11 = 0011010111100012,

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 13 of 18

d12 = 1011110001001102,

d13 = 0111100010011012,

d14 = 1111000100110102,

d15 = 1000111101011002.

2.  For 0≤ i≤ 15, let si=ki||di||ivi.

3.6  The execution of ZUC

The execution of ZUC has two stages: the initialization stage and the working stage.

3.6.1  The initialization stage

During the initialization stage, the algorithm calls the key loading procedure (see section 3.5)
to load the 128-bit initial key k and the 128-bit initial vector iv into the LFSR, and set the 32-
bit memory cells R1 and R2 to be all 0. Then the cipher runs the following operations 32 times:

1.   Bitreorganization();                                  // see section 3.3

2.   w=F(X0, X1, X2);                                       // see section 3.4

3.

 LFSRWithInitialisationMode(w>>1).

// see section 3.2

3.6.2  The working stage

After the initialization stage, the algorithm moves into the working stage. At the working
stage, the algorithm executes the following operations once, and discards the output W of F:

1.   Bitreorganization();

// see section 3.3

2.      F(X0, X1, X2);

//output discarded, see section 3.4

3.   LFSRWithWorkMode().

// see section 3.2

Then the algorithm goes into the stage of producing keystream, i.e., for each iteration, the
following operations are executed once, and a 32-bit word Z is produced as an output:

1.   Bitreorganization();

// see section 3.3

2.      Z= F(X0, X1, X2)⊕ X3;

// for the definition of X3, see section 3.3

3.   LFSRWithWorkMode() .

// see section 3.2

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 14 of 18

Appendix A: A C implementation of ZUC

/* ——————————————————————- */
typedef unsigned char u8;
typedef unsigned int u32;
/* ——————————————————————- */
/* the state registers of LFSR */
u32 LFSR_S0;
u32 LFSR_S1;
u32 LFSR_S2;
u32 LFSR_S3;
u32 LFSR_S4;
u32 LFSR_S5;
u32 LFSR_S6;
u32 LFSR_S7;
u32 LFSR_S8;
u32 LFSR_S9;
u32 LFSR_S10;
u32 LFSR_S11;
u32 LFSR_S12;
u32 LFSR_S13;
u32 LFSR_S14;
u32 LFSR_S15;

/* the registers of F */
u32 F_R1;
u32 F_R2;

/* the outputs of BitReorganization */
u32 BRC_X0;
u32 BRC_X1;
u32 BRC_X2;
u32 BRC_X3;

/* the s-boxes */
u8 S0[256] = {

0x3e,0x72,0x5b,0x47,0xca,0xe0,0x00,0x33,0x04,0xd1,0x54,0x98,0x09,0xb9,0x6d,0xcb,
0x7b,0x1b,0xf9,0x32,0xaf,0x9d,0x6a,0xa5,0xb8,0x2d,0xfc,0x1d,0x08,0x53,0x03,0x90,
0x4d,0x4e,0x84,0x99,0xe4,0xce,0xd9,0x91,0xdd,0xb6,0x85,0x48,0x8b,0x29,0x6e,0xac,
0xcd,0xc1,0xf8,0x1e,0x73,0x43,0x69,0xc6,0xb5,0xbd,0xfd,0x39,0x63,0x20,0xd4,0x38,
0x76,0x7d,0xb2,0xa7,0xcf,0xed,0x57,0xc5,0xf3,0x2c,0xbb,0x14,0x21,0x06,0x55,0x9b,
0xe3,0xef,0x5e,0x31,0x4f,0x7f,0x5a,0xa4,0x0d,0x82,0x51,0x49,0x5f,0xba,0x58,0x1c,
0x4a,0x16,0xd5,0x17,0xa8,0x92,0x24,0x1f,0x8c,0xff,0xd8,0xae,0x2e,0x01,0xd3,0xad,
0x3b,0x4b,0xda,0x46,0xeb,0xc9,0xde,0x9a,0x8f,0x87,0xd7,0x3a,0x80,0x6f,0x2f,0xc8,
0xb1,0xb4,0x37,0xf7,0x0a,0x22,0x13,0x28,0x7c,0xcc,0x3c,0x89,0xc7,0xc3,0x96,0x56,
0x07,0xbf,0x7e,0xf0,0x0b,0x2b,0x97,0x52,0x35,0x41,0x79,0x61,0xa6,0x4c,0x10,0xfe,
0xbc,0x26,0x95,0x88,0x8a,0xb0,0xa3,0xfb,0xc0,0x18,0x94,0xf2,0xe1,0xe5,0xe9,0x5d,
0xd0,0xdc,0x11,0x66,0x64,0x5c,0xec,0x59,0x42,0x75,0x12,0xf5,0x74,0x9c,0xaa,0x23,
0x0e,0x86,0xab,0xbe,0x2a,0x02,0xe7,0x67,0xe6,0x44,0xa2,0x6c,0xc2,0x93,0x9f,0xf1,
0xf6,0xfa,0x36,0xd2,0x50,0x68,0x9e,0x62,0x71,0x15,0x3d,0xd6,0x40,0xc4,0xe2,0x0f,
0x8e,0x83,0x77,0x6b,0x25,0x05,0x3f,0x0c,0x30,0xea,0x70,0xb7,0xa1,0xe8,0xa9,0x65,
0x8d,0x27,0x1a,0xdb,0x81,0xb3,0xa0,0xf4,0x45,0x7a,0x19,0xdf,0xee,0x78,0x34,0x60

};

u8 S1[256] =  {

0x55,0xc2,0x63,0x71,0x3b,0xc8,0x47,0x86,0x9f,0x3c,0xda,0x5b,0x29,0xaa,0xfd,0x77,
0x8c,0xc5,0x94,0x0c,0xa6,0x1a,0x13,0x00,0xe3,0xa8,0x16,0x72,0x40,0xf9,0xf8,0x42,
0x44,0x26,0x68,0x96,0x81,0xd9,0x45,0x3e,0x10,0x76,0xc6,0xa7,0x8b,0x39,0x43,0xe1,
0x3a,0xb5,0x56,0x2a,0xc0,0x6d,0xb3,0x05,0x22,0x66,0xbf,0xdc,0x0b,0xfa,0x62,0x48,
0xdd,0x20,0x11,0x06,0x36,0xc9,0xc1,0xcf,0xf6,0x27,0x52,0xbb,0x69,0xf5,0xd4,0x87,
0x7f,0x84,0x4c,0xd2,0x9c,0x57,0xa4,0xbc,0x4f,0x9a,0xdf,0xfe,0xd6,0x8d,0x7a,0xeb,
0x2b,0x53,0xd8,0x5c,0xa1,0x14,0x17,0xfb,0x23,0xd5,0x7d,0x30,0x67,0x73,0x08,0x09,
0xee,0xb7,0x70,0x3f,0x61,0xb2,0x19,0x8e,0x4e,0xe5,0x4b,0x93,0x8f,0x5d,0xdb,0xa9,
0xad,0xf1,0xae,0x2e,0xcb,0x0d,0xfc,0xf4,0x2d,0x46,0x6e,0x1d,0x97,0xe8,0xd1,0xe9,
0x4d,0x37,0xa5,0x75,0x5e,0x83,0x9e,0xab,0x82,0x9d,0xb9,0x1c,0xe0,0xcd,0x49,0x89,
0x01,0xb6,0xbd,0x58,0x24,0xa2,0x5f,0x38,0x78,0x99,0x15,0x90,0x50,0xb8,0x95,0xe4,
0xd0,0x91,0xc7,0xce,0xed,0x0f,0xb4,0x6f,0xa0,0xcc,0xf0,0x02,0x4a,0x79,0xc3,0xde,
0xa3,0xef,0xea,0x51,0xe6,0x6b,0x18,0xec,0x1b,0x2c,0x80,0xf7,0x74,0xe7,0xff,0x21,
0x5a,0x6a,0x54,0x1e,0x41,0x31,0x92,0x35,0xc4,0x33,0x07,0x0a,0xba,0x7e,0x0e,0x34,
0x88,0xb1,0x98,0x7c,0xf3,0x3d,0x60,0x6c,0x7b,0xca,0xd3,0x1f,0x32,0x65,0x04,0x28,
0x64,0xbe,0x85,0x9b,0x2f,0x59,0x8a,0xd7,0xb0,0x25,0xac,0xaf,0x12,0x03,0xe2,0xf2

};

/* the constants D */
u32 EK_d[16] = {

0x44D7, 0x26BC, 0x626B, 0x135E, 0x5789, 0x35E2, 0x7135, 0x09AF,
0x4D78, 0x2F13, 0x6BC4, 0x1AF1, 0x5E26, 0x3C4D, 0x789A, 0x47AC

};

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 15 of 18

/* ——————————————————————- */
/* c = a + b mod (2^31 – 1) */
u32 AddM(u32 a, u32 b)
{

u32 c = a + b;
return (c & 0x7FFFFFFF) + (c >> 31);

}

/* LFSR with initialization mode */
#define MulByPow2(x, k) ((((x) << k) | ((x) >> (31 - k))) & 0x7FFFFFFF)
void LFSRWithInitialisationMode(u32 u)
{

u32 f, v;

f = LFSR_S0;
v = MulByPow2(LFSR_S0, 8);
f = AddM(f, v);

v = MulByPow2(LFSR_S4, 20);
f = AddM(f, v);

v = MulByPow2(LFSR_S10, 21);
f = AddM(f, v);

v = MulByPow2(LFSR_S13, 17);
f = AddM(f, v);

v = MulByPow2(LFSR_S15, 15);
f = AddM(f, v);

f = AddM(f, u);

/* update the state */
LFSR_S0 = LFSR_S1;
LFSR_S1 = LFSR_S2;
LFSR_S2 = LFSR_S3;
LFSR_S3 = LFSR_S4;
LFSR_S4 = LFSR_S5;
LFSR_S5 = LFSR_S6;
LFSR_S6 = LFSR_S7;
LFSR_S7 = LFSR_S8;
LFSR_S8 = LFSR_S9;
LFSR_S9 = LFSR_S10;
LFSR_S10 = LFSR_S11;
LFSR_S11 = LFSR_S12;
LFSR_S12 = LFSR_S13;
LFSR_S13 = LFSR_S14;
LFSR_S14 = LFSR_S15;
LFSR_S15 = f;

}

/* LFSR with work mode */
void LFSRWithWorkMode()
{

u32 f, v;

f = LFSR_S0;
v = MulByPow2(LFSR_S0, 8);
f = AddM(f, v);

v = MulByPow2(LFSR_S4, 20);
f = AddM(f, v);

v = MulByPow2(LFSR_S10, 21);
f = AddM(f, v);

v = MulByPow2(LFSR_S13, 17);
f = AddM(f, v);

v = MulByPow2(LFSR_S15, 15);
f = AddM(f, v);

/* update the state */
LFSR_S0 = LFSR_S1;
LFSR_S1 = LFSR_S2;
LFSR_S2 = LFSR_S3;
LFSR_S3 = LFSR_S4;

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 16 of 18

LFSR_S4 = LFSR_S5;
LFSR_S5 = LFSR_S6;
LFSR_S6 = LFSR_S7;
LFSR_S7 = LFSR_S8;
LFSR_S8 = LFSR_S9;
LFSR_S9 = LFSR_S10;
LFSR_S10 = LFSR_S11;
LFSR_S11 = LFSR_S12;
LFSR_S12 = LFSR_S13;
LFSR_S13 = LFSR_S14;
LFSR_S14 = LFSR_S15;
LFSR_S15 = f;

}

/* BitReorganization */
void BitReorganization()
{

BRC_X0 = ((LFSR_S15 & 0x7FFF8000) << 1) | (LFSR_S14 & 0xFFFF);
BRC_X1 = ((LFSR_S11 & 0xFFFF) << 16) | (LFSR_S9 >> 15);
BRC_X2 = ((LFSR_S7 & 0xFFFF) << 16) | (LFSR_S5 >> 15);
BRC_X3 = ((LFSR_S2 & 0xFFFF) << 16) | (LFSR_S0 >> 15);

}

#define ROT(a, k) (((a) << k) | ((a) >> (32 - k)))

/* L1 */
u32 L1(u32 X)
{

return (X ^ ROT(X, 2) ^ ROT(X, 10) ^ ROT(X, 18) ^ ROT(X, 24));

}

/* L2 */
u32 L2(u32 X)
{

return (X ^ ROT(X, 8) ^ ROT(X, 14) ^ ROT(X, 22) ^ ROT(X, 30));

}

#define MAKEU32(a, b, c, d) (((u32)(a) << 24) | ((u32)(b) << 16)
| ((u32)(c) << 8) | ((u32)(d)))

/* F */
u32 F()
{

u32 W, W1, W2, u, v;
W = (BRC_X0 ^ F_R1) + F_R2;
W1 = F_R1 + BRC_X1;
W2 = F_R2 ^ BRC_X2;
u = L1((W1 << 16) | (W2 >> 16));
v = L2((W2 << 16) | (W1 >> 16));
F_R1 = MAKEU32(S0[u >> 24], S1[(u >> 16) & 0xFF],

S0[(u >> 8) & 0xFF], S1[u & 0xFF]);

F_R2 = MAKEU32(S0[v >> 24], S1[(v >> 16) & 0xFF],

S0[(v >> 8) & 0xFF], S1[v & 0xFF]);

return W;

}

#define MAKEU31(a, b, c) (((u32)(a) << 23) | ((u32)(b) << 8) | (u32)(c))

/* initialize */
void Initialization(u8* k, u8* iv)
{

u32 w, nCount;

/* expand key */
LFSR_S0 = MAKEU31(k[0], EK_d[0], iv[0]);
LFSR_S1 = MAKEU31(k[1], EK_d[1], iv[1]);
LFSR_S2 = MAKEU31(k[2], EK_d[2], iv[2]);
LFSR_S3 = MAKEU31(k[3], EK_d[3], iv[3]);
LFSR_S4 = MAKEU31(k[4], EK_d[4], iv[4]);
LFSR_S5 = MAKEU31(k[5], EK_d[5], iv[5]);
LFSR_S6 = MAKEU31(k[6], EK_d[6], iv[6]);
LFSR_S7 = MAKEU31(k[7], EK_d[7], iv[7]);
LFSR_S8 = MAKEU31(k[8], EK_d[8], iv[8]);
LFSR_S9 = MAKEU31(k[9], EK_d[9], iv[9]);
LFSR_S10 = MAKEU31(k[10], EK_d[10], iv[10]);
LFSR_S11 = MAKEU31(k[11], EK_d[11], iv[11]);
LFSR_S12 = MAKEU31(k[12], EK_d[12], iv[12]);
LFSR_S13 = MAKEU31(k[13], EK_d[13], iv[13]);

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 17 of 18

LFSR_S14 = MAKEU31(k[14], EK_d[14], iv[14]);
LFSR_S15 = MAKEU31(k[15], EK_d[15], iv[15]);

/* set F_R1 and F_R2 to zero */
F_R1 = 0;
F_R2 = 0;
nCount = 32;
while (nCount > 0)
{

BitReorganization();
w = F();
LFSRWithInitialisationMode(w >> 1);
nCount --;

}

}

void GenerateKeystream(u32* pKeystream, int KeystreamLen)
{

int i;

{

}

BitReorganization();
F();
LFSRWithWorkMode();

/* discard the output of F */

for (i = 0; i < KeystreamLen; i ++)
{

BitReorganization();
pKeystream[i] = F() ^ BRC_X3;
LFSRWithWorkMode();

}

}

3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
ZUC Algorithm Specification Version 1.6

page 18 of 18


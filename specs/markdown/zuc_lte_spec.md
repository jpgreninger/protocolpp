ETSI/SAGE
Specification

Version:    1.7
Date: 30th Dec, 2011

Specification of the 3GPP Confidentiality and
Integrity Algorithms 128-EEA3 & 128-EIA3.
Document 1: 128-EEA3 and 128-EIA3 Specification

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 1 of 16

V1.0

18th June 2010

Publication

Document History

1.2

1.3

1.4

1.5

1.6

1.7

26-07-2010

Improvements to C code

27-07-2010

Minor corrections to C code

30-07-2010

Corrected preface

04-01-2011

A modification of 128-EIA3 and text improved

01-07-2011

Minor corrections

30-12-2011

Increase maximum data length for encryption algorithm

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 2 of 16

Blank Page

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 3 of 16

PREFACE

This specification has been prepared by the 3GPP Task Force, and gives a detailed specification of
the  3GPP  confidentiality  algorithm  128-EEA3  and  the  3GPP  integrity  algorithm  128-EIA3.  This
document  is  the  first  of  three,  which  between  them  form  the  entire  specification  of  the  3GPP
Confidentiality and Integrity Algorithms:

  Specification of the 3GPP Confidentiality and Integrity Algorithms 128-EEA3 &

128-EIA3.
Document 1: 128-EEA3 and 128-EIA3 Specifications.

  Specification of the 3GPP Confidentiality and Integrity Algorithms 128-EEA3 &

128-EIA3.
Document 2: ZUC Specification.

  Specification of the 3GPP Confidentiality and Integrity Algorithms 128-EEA3 &

128-EIA3.
Document 3: Implementor’s Test Data.

The normative part of the specification of the 128-EEA3 (confidentiality) and 128-EIA3 (integrity)
algorithms  is  in  the  main  body  of  this  document.  The  annexes  to  this  document  are  purely
informative,  and  contain  implementation  program  listings  of  the  cryptographic  algorithms
specified in the main body of this document, written in the programming language C.

The  normative  section  of  the  specification  of  the  stream  cipher  (ZUC)  on  which  128-EEA3  and
128-EIA3 are based is in the main body of Document 2.

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 4 of 16

TABLE OF CONTENTS

1  OUTLINE OF THE NORMATIVE PART ........................................................................ 8

2

INTRODUCTORY INFORMATION ................................................................................ 8
2.1  Introduction ................................................................................................................. 8
2.2  Notations ..................................................................................................................... 8

3  CONFIDENTIALITY ALGORITHM 128-EEA3 ............................................................ 10
3.1  Introduction ............................................................................................................... 10
3.2  Inputs and Outputs .................................................................................................... 10
3.3  Initialisation .............................................................................................................. 10
3.4  Keystream Generation .............................................................................................. 11
3.5  Encryption/Decryption.............................................................................................. 11

4

INTEGRITY ALGORITHM 128-EIA3 ........................................................................... 12
4.1  Introduction ............................................................................................................... 12
4.2  Inputs and Outputs .................................................................................................... 12
4.3  Initialisation .............................................................................................................. 12
4.4  Generating the keystream ......................................................................................... 12
4.5  Compute the MAC .................................................................................................... 13

ANNEX 1  A C implementation of 128-EEA3 ..................................................................... 15

ANNEX 2  A C implementation of 128-EIA3 ...................................................................... 16

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 5 of 16

REFERENCES
[1]

Specification of the 3GPP Confidentiality and Integrity Algorithms; Document 1: f8 and
f9 specifications; (3GPP TS35.201 Release 6).

[2]

[3]

3GPP System Architecture Evolution (SAE); Security architecture; (3GPP TS33.401
Release 9).

Specification of the 3GPP Confidentiality and Integrity Algorithms 128-EEA3 & 128-EIA3.
Document 2: ZUC Specification.

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 6 of 16

NORMATIVE SECTION
This  part  of  the  document  contains  the  normative  specification  of  the  Confidentiality  and
Integrity algorithms.

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 7 of 16

1

OUTLINE OF THE NORMATIVE PART

Section 2 introduces the algorithm and describes the notation used in the subsequent sections.
Section 3 specifies the confidentiality algorithm 128-EEA3.
Section 4 specifies the integrity algorithm 128-EIA3.

2

INTRODUCTORY INFORMATION

2.1

Introduction

Within  the  security  architecture  of  the  LTE  system  there  are  standardized  algorithms  for
confidentiality  and  integrity.  Two  sets  of  algorithms  128-EEA1/128-EIA1  and  128-EEA2/128-EIA2
have  already  been  specified  [1-2].  In  this  document  the  third  set  of  these  algorithms
(128-EEA3/128-EIA3) based on ZUC [3] are proposed.
The confidentiality algorithm 128-EEA3 is a stream cipher that is used to encrypt/decrypt blocks
of data using a confidentiality key CK. The block of data may be between 1 and 232 bits long. The
algorithm uses ZUC as a keystream generator.
The  integrity  algorithm  128-EIA3  computes  a  32-bit  MAC  (Message  Authentication  Code)  of  a
given  input  message  using  an  integrity  key  IK.  The  core  algorithms  adopted  by  the  MAC  are  a
universal hash and ZUC.

2.2

Notations

2.2.1  Radix

In  this document,  integers are  represented  as decimal  numbers unless  specified otherwise. We
use the prefix “0x” to indicate hexadecimal numbers and the subscript “2” to indicate a number
in binary representation.
Example 1.

Integer a can be written in different representations:

a = 1234567890
    = 0x499602D2

// decimal representation
// hexadecimal representation

  = 10010011001011000000010110100102 //binary representation

2.2.2  Bit/Byte ordering

All  data  variables  in  this  document  are presented  with  the  most  significant  bit/byte on  the  left
and the least significant bit/byte on the right. When a variable is broken down into a number of
substrings,  the  leftmost  substring  is  numbered  by  0,  the  next  most  significant  substring  is
numbered by 1 and so on throughout to the least significant substring.
Example 2.
represents its most significant bit, and the rightmost bit 0 represents its least significant bit.
Example 3.
substrings a [0], a [1], a [2] and a [3], then we have

Let  a  =100100101001011000000010110100102.  If  a  is  subdivided  into  4  of  8-bit

Let a=10010011001011000000010110100102. Then the leftmost bit 1 of integer a

  a [0] = 100100102,    a [1] = 100101102, a [2] = 000000102,    a [3] = 110100102.

2.2.3  Operation notations

In this document, operation notations are defined as follows:
a║b
 x 
⊕

Concatenation of substrings a and b
The smallest integer no less than x
Exclusive-OR

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 8 of 16

a<< t

Left shift of integer a by t bits

Example 4.

For two substrings a= 0x1234 and b= 0x5678, then their concatenation will be

c=a║b =0x12345678.

2.2.4  List of Variables

COUNT
BEARER
DIRECTION
CK
IK
LENGTH
M
C
KEY
IV
L
z[i]

The 32-bit counter.
The 5-bit bearer identity.
The 1-bit input indicating the direction of transmission.
The 128-bit confidentiality key.
The 128-bit integrity key.
The number of bits to be encrypted/decrypted.
The input message.
The output message.
The 128-bit initial key to ZUC.
The 128-bit initial vector to ZUC.
The number of key words generated by ZUC.
The i-th key bit of keystream generated by ZUC.

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 9 of 16

3

CONFIDENTIALITY ALGORITHM 128-EEA3

3.1

Introduction

The confidentiality algorithm 128-EEA3 is a stream cipher that is used to encrypt/decrypt blocks
of data under a confidentiality key. The block of data can be between 1 and 232 bits in length.

3.2

Inputs and Outputs

The inputs to the algorithm are given in Table 1, the output in Table 2.

Table 1 The inputs to 128-EEA3

Parameter
COUNT
BEARER
DIRECTION
CK
LENGTH
M

Parameter
C

3.3

Initialisation

Size(bits)
32
5
1
128
32
LENGTH

Remark
The counter
The bearer identity
The direction of transmission
Confidentiality key
The length of the input message
The input bit stream

Table 2 The output of 128-EEA3

Size(bits)
LENGTH

Remark
The output bit stream

In this section we define how ZUC’s parameters, the initial key KEY and the initial vector IV, are
initialized  with  the  confidentiality  key  CK  and  initialization  variables  before  the  generation  of
keystream.
Let

CK=CK[0] ║CK[1] ║CK[2] ║…║CK[15]
be the 128-bit confidentiality key, where CK[i] (0
KEY to ZUC as

≤

i

≤

15) are bytes. We set the 128-bit initial key

KEY = KEY[0] ║KEY[1] ║KEY[2] ║…║KEY[15],

where KEY[i] (0

≤

≤
i
KEY[i]=CK[i], i=0,1,2,…,15.

15) are bytes. Then

Let

COUNT=COUNT[0]║COUNT[1]║COUNT[2]║COUNT[3]

be the 32-bit counter, where COUNT[i] ( 0
ZUC as

≤

≤

i

3) are bytes. We set the 128-bit initial vector to

IV = IV[0]║IV[1] ║IV[2] ║…║IV[15],

where IV[i] ( 0

15) are bytes. Then

≤

≤

i

IV[0] = COUNT[0], IV[1] = COUNT[1],
IV[2] = COUNT[2], IV[3] = COUNT[3],
IV[4] = BEARER║DIRECTION║002,
IV[5] = IV[6] = IV[7] = 000000002,
IV[8] = IV[0], IV[9] = IV[1],
IV[10] = IV[2], IV[11] = IV[3],
IV[12] = IV[4], IV[13] = IV[5],
IV[14] = IV[6], IV[15] = IV[7].

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 10 of 16

3.4  Keystream Generation

Let ZUC generate keystream of L words. When each of the word is expanded into a 32-bit string,
then  we  get  a binary string  z[0], z[1], …,  z[32L-1],  where  z[0] is the  most  significant bit of the
first output word of ZUC and z[31] is the least significant bit. To encrypt a message of LENGTH bits,
it is required that L=LENGTH/32.

3.5

Encryption/Decryption

Encryption/decryption operations are identical operations and are performed by the exclusive-OR
of the input message M with the generated keystream z.
Let

M = M[0] ║M[1] ║M[2] ║…║M[LENGTH-1]

be the input bit stream of length LENGTH and
C = C[0] ║C[1] ║C[2] ║…║C[LENGTH-1]

be  the  corresponding  output  bit  stream  of  length  LENGTH,  where  M[i]  and  C[i]  are  bits,
i=0,1,2,…,LENGTH-1. Then

C[i] = M[i]  z[i],i=0,1,2,…,LENGTH-1.

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 11 of 16

4

INTEGRITY ALGORITHM 128-EIA3

4.1

Introduction

The integrity algorithm 128-EIA3 is a message authentication code (MAC) function that is used to
compute the MAC of an input message using an integrity key IK. The message can be between 1
and 65504 bits in length.

4.2

Inputs and Outputs

The inputs to the algorithm are given in Table 3, and the output is in Table 4.

Table 3 The inputs to 128-EIA3

Parameter
COUNT
BEARER
DIRECTION
IK
LENGTH
M

Parameter
MAC

4.3

Initialisation

Size (bits)
32
5
1
128
32
LENGTH

Remark
The counter
The bearer identity
The direction of transmission
The integrity key
The bits of the input message
The input message

Table 4 The output of 128-EIA3

Size(bits)
32

Remark
The MAC

In this section we define how ZUC’s parameters, the initial key KEY and the initial vector IV, are
initialized with the integrity key IK and initialization variables before the generation of keystream.
Let

IK = IK[0] ║IK[1] ║IK[2] ║…║IK[15]

be the 128-bit integrity key, where IK[i]( 0
ZUC as

≤
i

≤

15) are bytes. We set the 128-bit initial key KEY to

KEY = KEY[0] ║KEY[1] ║KEY[2] ║…║KEY[15]

≤

where KEY[i](0

≤
i
KEY[i] = IK[i], i=0,1,2,…,15.
Let the 32-bit counter COUNT be

15) are bytes. Then

COUNT=COUNT[0] ║COUNT[1] ║COUNT[2] ║COUNT[3]

where COUNT[i] are bytes, i=0,1,2,3. We set the 128-bit initial vector IV to ZUC as

IV = IV[0] ║IV[1] ║IV[2] ║…║IV[15],

where IV[i]( 0

15) are bytes. Then

≤

≤

i

IV[0] = COUNT[0], IV[1] = COUNT[1],
IV[2] = COUNT[2], IV[3] = COUNT[3],
IV[4] = BEARER║0002, IV[5] =000000002,
IV[6] = 000000002, IV[7] = 000000002,
IV[8] = IV[0]  (DIRECTION << 7), IV[9] = IV[1],
IV[10] = IV[2], IV[11] = IV[3],
IV[12] = IV[4], IV[13] = IV[5],
IV[14] = IV[6]  (DIRECTION << 7), IV[15] = IV[7].

4.4  Generating the keystream

Let ZUC generate a keystream of L=LENGTH/32+2 words. Denote the generated bit string by z[0],
z[1], …, z[32L-1], where z[0] is the most significant bit of the first output word of ZUC and z[31]

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 12 of 16

is the least significant bit.

For each i=0,1,2,…,32(L-1), let

zi = z[i] ║z[i+1] ║…║z[i+31].

Then each zi is a 32-bit word.

4.5

Compute the MAC

Let T be a 32-bit word. Set T = 0.
For each i=0,1,2,…,LENGTH-1, if M[i] = 1, then

T=T  zi.

Set

T=T  zLENGTH.

Finally we take T  z32(L-1) as the output MAC, i.e.

MAC= T  z32(L-1).

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 13 of 16

INFORMATIVE SECTION
This  part  of  the  document  is  purely  informative  and  does  not  form  part  of  the  normative
specification of the Confidentiality and Integrity algorithms.

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 14 of 16

ANNEX 1
A C implementation of 128-EEA3

typedef unsigned char u8;
typedef unsigned int  u32;

/* The ZUC algorithm, see ref. [3]*/
void ZUC(u8* k, u8* iv, u32* ks, int len)
{

/* The initialization of ZUC, see page 17 of ref. [3]*/
Initialization(k, iv);

/*  The procedure of generating keystream of ZUC, see page 18 of ref. [3]*/
GenerateKeystream(ks, len);

}

void EEA3(u8* CK,u32 COUNT,u32 BEARER,u32 DIRECTION,u32 LENGTH,u32* M,u32* C)
{

u32 *z, L, i;
u8  IV[16];

L   = (LENGTH+31)/32;
z   = (u32 *) malloc(L*sizeof(u32));

IV[0]  = (COUNT>>24) & 0xFF;
IV[1]  = (COUNT>>16) & 0xFF;
IV[2]  = (COUNT>>8)  & 0xFF;
IV[3]  = COUNT        & 0xFF;

IV[4]  = ((BEARER << 3) | ((DIRECTION&1)<<2)) & 0xFC;
IV[5]  = 0;
IV[6]  = 0;
IV[7]  = 0;

IV[8]  = IV[0];
IV[9]  = IV[1];
IV[10]  = IV[2];
IV[11]  = IV[3];

IV[12]  = IV[4];
IV[13]  = IV[5];
IV[14]  = IV[6];
IV[15]  = IV[7];

ZUC(CK,IV,z,L);

for (i=0; i<L; i++)
{

C[i] = M[i] ^ z[i];

}

free(z);

}

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 15 of 16

ANNEX 2
A C implementation of 128-EIA3

typedef unsigned char   u8;
typedef unsigned int    u32;
void ZUC(u8* k, u8* iv, u32* keystream, int length); /*see Annex 1*/
u32 GET_WORD(u32 * DATA, u32 i)
{

u32 WORD, ti;

ti  = i % 32;
if (ti == 0) {

WORD = DATA[i/32];

}
else {

WORD = (DATA[i/32]<<ti) | (DATA[i/32+1]>>(32-ti));

}

return WORD;

}
u8 GET_BIT(u32 * DATA, u32 i)
{

return (DATA[i/32] & (1<<(31-(i%32)))) ? 1 : 0;

}
void EIA3(u8* IK,u32 COUNT,u32 DIRECTION,u32 BEARER,u32 LENGTH,u32* M,u32* MAC)
{

u32 *z, N, L, T, i;
u8 IV[16];

IV[0]  = (COUNT>>24) & 0xFF;
IV[1]  = (COUNT>>16) & 0xFF;
IV[2]  = (COUNT>>8) & 0xFF;
IV[3]  = COUNT & 0xFF;

IV[4]  = (BEARER << 3) & 0xF8;
IV[5]  = IV[6] = IV[7] = 0;

IV[8]  = ((COUNT>>24) & 0xFF) ^ ((DIRECTION&1)<<7);
IV[9]  = (COUNT>>16) & 0xFF;
IV[10]  = (COUNT>>8) & 0xFF;
IV[11]  = COUNT & 0xFF;

IV[12]  = IV[4];
IV[13]  = IV[5];
IV[14]  = IV[6] ^ ((DIRECTION&1)<<7);
IV[15]  = IV[7];

N  = LENGTH + 64;
L  = (N + 31) / 32;
z  = (u32 *) malloc(L*sizeof(u32));
ZUC(IK, IV, z, L);

T = 0;
for (i=0; i<LENGTH; i++) {
if (GET_BIT(M,i)) {

T ^= GET_WORD(z,i);

}

}
T ^= GET_WORD(z,LENGTH);

*MAC = T ^ z[L-1];
free(z);

}

3GPP Confidentiality and Integrity Algorithms 128-EEA3&128-EIA3
128-EEA3 and 128-EIA3 Specification Version 1.7

page 16 of 16


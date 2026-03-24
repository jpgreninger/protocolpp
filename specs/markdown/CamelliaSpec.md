Speci(cid:12)cation of

| a 128-bit Block Cipher

C amellia

Kazumaro AOKI

, Tetsuya ICHIKAWA

, Masayuki KANDA

,

y

z

y

Mitsuru MATSUI

, Shiho MORIAI

, Junko NAKAJIMA

, Toshio TOKITA

z

y

z

z

y

z

Nippon Telegraph and Telephone Corporation,

Mitsubishi Electric Corporation

Version 1.0: July 12, 2000

Version 2.0: September 26, 2001

Contents

1 Introduction

3

2 Notations and Conventions

3

2.1 Radix . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

3

2.2 Notations . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

3

2.3 List of Symbols . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

3

2.4 Bit/Byte Ordering . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

3

3 Structure of

5

C amellia

3.1 List of Functions and Variables . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

5

3.2 Encryption Procedure . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

5

3.2.1

128-bit key . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

5

3.2.2

192-bit and 256-bit key . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

6

3.3 Decryption Procedure

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

6

3.3.1

128-bit key . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

6

3.3.2

192-bit and 256-bit key . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

7

3.4 Key Schedule . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

8

4 Components of

10

C amellia

4.1

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 10

F

4.2

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

10

F L

4.3

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

10

(cid:0)

1

F L

4.4

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

10

S

4.5

-boxes

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

11

s

4.6

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 15

P

A Figures of the

Algorithm

16

C amellia

B Test Data

22

1

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

2

C Software Implementation Techniques

22

C.1 Setup . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

22

C.1.1 Store All Subkeys

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

22

C.1.2 Subkey Generation Order

. . . . . . . . . . . . . . . . . . . . . . . . . . . .

23

C.1.3 XOR Cancellation Property in Key Schedule . . . . . . . . . . . . . . . . . .

23

C.1.4 Rotation Bits for

,

,

, and

. . . . . . . . . . . . . . . . . . . . .

23

K

K

K

K

L

R

A

B

C.1.5

and

Generation from

and

. . . . . . . . . . . . . . . . . . . .

23

k l

k l

k

k

5

6

11

12

C.1.6 On-the-(cid:13)y Subkey Generation . . . . . . . . . . . . . . . . . . . . . . . . . . . 23

C.1.7 128-bit key and 192/256-bit key . . . . . . . . . . . . . . . . . . . . . . . . .

23

C.1.8 How to Rotate an Element in

. . . . . . . . . . . . . . . . . . . . . . . . .

23

Q

C.1.9

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 24

F

C.1.10 Keyed Functions . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

24

C.2 Data Randomization . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

24

C.2.1 Endian Conversion . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

24

C.2.2 1-bit Rotation in Little Endian Interpretation . . . . . . . . . . . . . . . . .

25

C.2.3 Whitening . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 25

C.2.4 Key XOR . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

25

C.2.5

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

26

S

C.2.6

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 26

P

C.2.7 Substitution and Permutation . . . . . . . . . . . . . . . . . . . . . . . . . . .

27

C.2.8 Making Indices for

-box . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

29

s

C.3 General Guidelines . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

30

D Design Policy

30

E Design Rationale

31

E.1

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 31

F

E.2

-function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 31

P

E.3

-boxes

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

32

s

F Version Information

32

G Ob ject Identi(cid:12)er

33

H Applications and Products

33

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

3

1

Introduction

This document shows a complete description of the encryption algorithm

, which is a secret

Camel lia

key cipher with 128-bit data block and 128/192/256-bit secret key.

2 Notations and Conventions

2.1 Radix

We use the pre(cid:12)x

to indicate

numbers.

0x

hexadecimal

2.2 Notations

Throughout this document, the following notations are used.

(cid:15)

denotes a vector space of 8-bit (byte) elements; that is,

:= GF(2)

.

B

B

8

(cid:15)

denotes a vector space of 32-bit (word) elements; that is,

:=

.

W

W

B

4

(cid:15)

denotes a vector space of 64-bit (double word) elements; that is,

:=

.

L

L

B

8

(cid:15)

denotes a vector space of 128-bit (quad word) elements; that is,

:=

.

Q

Q

B

16

(cid:15) An element with the su(cid:14)x

(e.g.

) shows that the element is

-bit long.

n

x

n

n

(

)

(

)

(cid:15) An element with the su(cid:14)x

(e.g.

) denotes left-half part of

.

L

L

x

x

(cid:15) An element with the su(cid:14)x

(e.g.

) denotes right-half part of

.

R

R

x

x

The su(cid:14)x

will be omitted if no ambiguity is expected. See section 2.4 for numerical examples

n

(

)

of \left" and \right".

2.3 List of Symbols

(cid:8)

The bitwise exclusive-OR operation.

jj

The concatenation of the two operands.

<<<

n

n

The left circular rotation of the operand by

bits.

\

The bitwise AND operation.

[

The bitwise OR operation.

x

x

The bitwise complement of

.

2.4 Bit/Byte Ordering

We adopt big endian ordering. The following example shows how to compose a 128-bit value

Q

(128)

of two 64-bit values

(

= 1

2), four 32-bit values

(

= 1

2

3

4), sixteen 8-bit values

L

i

i

;

W

i

i

;

;

;

(64)

(32)

B

i

i

;

; : : : ;

E

i

i

;

; : : : ;

(

= 1

2

16), or 128 1-bit values

(

= 1

2

128), respectively.

(8)

(1)

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

4

Q

L

jjL

=

(128)

1(64)

2(64)

=

W

jjW

jjW

jjW

1(32)

2(32)

3(32)

4(32)

=

B

jjB

jjB

jjB

jj : : : : : : jjB

jjB

jjB

jjB

1(8)

2(8)

3(8)

4(8)

13(8)

14(8)

15(8)

16(8)

=

E

jjE

jjE

jjE

jj : : : : : : : : : : : : : : : : : : jjE

jjE

jjE

jjE

1(1)

2(1)

3(1)

4(1)

125(1)

126(1)

127(1)

128(1)

Numerical examples:

Q

=

(128)

(128)

0x0123456789ABCDEF0011223344556677

L

=

Q

=

L

1(64)

(64)

(64)

0x0123456789ABCDEF

L

=

Q

=

R

2(64)

(64)

(64)

0x0011223344556677

W

=

L

=

L

1(32)

1

(32)

(32)

0x01234567

W

=

L

=

R

2(32)

1

(32)

(32)

0x89ABCDEF

W

=

L

=

L

3(32)

2

(32)

(32)

0x00112233

W

=

L

=

R

4(32)

2

(32)

(32)

0x44556677

B

=

; B

; B

; B

;

=

=

=

1(8)

(8)

2(8)

(8)

3(8)

(8)

4(8)

(8)

0x01

0x23

0x45

0x67

B

=

; B

; B

; B

;

=

=

=

5(8)

(8)

6(8)

(8)

7(8)

(8)

8(8)

(8)

0x89

0xAB

0xCD

0xEF

B

=

; B

; B

; B

;

=

=

=

9(8)

(8)

10(8)

(8)

11(8)

(8)

12(8)

(8)

0x00

0x11

0x22

0x33

B

=

; B

; B

; B

;

=

=

=

13(8)

(8)

14(8)

(8)

15(8)

(8)

16(8)

(8)

0x44

0x55

0x66

0x77

E

;

E

;

E

;

E

=

=

=

=

;

1(1)

(1)

2(1)

(1)

3(1)

(1)

4(1)

(1)

0

0

0

0

E

;

E

;

E

;

E

=

=

=

=

;

5(1)

(1)

6(1)

(1)

7(1)

(1)

8(1)

(1)

0

0

0

1

.

.

.

E

;

E

;

E

;

E

=

=

=

=

;

121(1)

(1)

122(1)

(1)

123(1)

(1)

124(1)

(1)

0

1

1

1

E

;

E

;

E

;

E

=

=

=

=

:

125(1)

(1)

126(1)

(1)

127(1)

(1)

128(1)

(1)

0

1

1

1

Q

<<<

E

jjE

jjE

jjE

jj : : : : : : : : : : : : : : : : : : jjE

jjE

jjE

jjE

jjE

=

(128)

2(1)

3(1)

4(1)

5(1)

125(1)

126(1)

127(1)

128(1)

1(1)

1

=

(128)

0x02468ACF13579BDE0022446688AACCEE

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

5

3 Structure of

C amellia

3.1 List of Functions and Variables

M

(128)

The plaintext block.

C

(128)

The ciphertext block.

K

The secret key, whose length is 128, 192, or 256 bits.

kw

; k

; k l

The subkeys.

t(64)

u(64)

v(64)

(

= 1

2

3

4) (

= 1

2

18) (

= 1

2

3

4)

t

;

;

;

u

;

; : : : ;

v

;

;

;

for 128-bit secret key.

(

= 1

2

3

4) (

= 1

2

24) (

= 1

2

6)

t

;

;

;

u

;

; : : : ;

v

;

; : : : ;

for 192-bit and 256-bit secret key.

Y

=

(

F

X

,

k

)

The

-function that transforms a 64-bit input

to a

F

X

(64)

(64)

(64)

(64)

64-bit output

using a 64-bit subkey

.

Y

k

(64)

(64)

Y

F L

X

; k

F L

X

=

(

)

The

-function that transforms a 64-bit input

to a

(64)

(64)

(64)

(64)

64-bit output

using a 64-bit subkey

.

Y

k

(64)

(64)

Y

F L

=

(

X

; k

)

The

-function that transforms a 64-bit input

to

F L

X

(64)

(64)

(64)

(64)

(cid:0)

(cid:0)

1

1

a 64-bit output

using a 64-bit subkey

.

Y

k

(64)

(64)

Y

=

(

S

X

)

The

-function that transforms a 64-bit input

to a

S

X

(64)

(64)

(64)

64-bit output

.

Y

(64)

Y

=

(

P

X

)

The

-function that transforms a 64-bit input

to a

P

X

(64)

(64)

(64)

64-bit output

.

Y

(64)

y

s

x

=

(

)

The

-boxes that transform an 8-bit input to an 8-bit output

s

(8)

(8)

i

(

= 1

2

3

4).

i

;

;

;

3.2 Encryption Procedure

3.2.1

128-bit key

Figure 1 shows the encryption procedure for a 128-bit key. The data randomizing part has an

18-round Feistel structure with two

-function layers after the 6-th and 12-th rounds, and

F L=F L

(cid:0)

1

128-bit XOR operations before the (cid:12)rst round and after the last round. The key schedule part

generates subkeys

kw

(

= 1

2

3

4),

t

;

;

;

k

(

= 1

2

18) and

(

= 1

2

3

4) from the

u

;

; : : : ;

k l

v

;

;

;

t(64)

u(64)

v(64)

secret key

; see section 3.4 for details of the key schedule part.

K

In the data randomizing part, (cid:12)rst the plaintext

is XORed with

and

M

kw

jjkw

(128)

1(64)

2(64)

separated into

L

and

R

of equal length, i.e.,

(

) =

.

M

(cid:8)

kw

jjkw

L

jjR

0(64)

0(64)

(128)

1(64)

2(64)

0(64)

0(64)

Then, the following operations are perfomed from

= 1 to 18, except for

= 6 and 12;

r

r

L

R

(cid:8) F

L

; k

=

(

)

;

r

r

1

r

1

r

(cid:0)

(cid:0)

R

L

:

=

r

r

1

(cid:0)

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

6

For

= 6 and 12, the following is carried out;

r

0

L

R

(cid:8) F

L

; k

=

(

)

;

r

1

r

1

r

(cid:0)

(cid:0)

r

0

R

L

;

=

r

1

r

(cid:0)

0

L

F L

L

; k l

=

(

)

;

(cid:0)

r

r

2r=6

1

R

F L

R

; k l

=

(

)

:

r

r

2r=6

(cid:0)

0

1

Lastly,

R

and

L

are concatenated and XORed with

. The resultant

kw

jjkw

18(64)

18(64)

3(64)

4(64)

value is the ciphertext, i.e.,

C

= (

R

jjL

(cid:8)

kw

jjkw

)

(

).

(128)

18(64)

18(64)

3(64)

4(64)

3.2.2

192-bit and 256-bit key

Figure 2 shows the encryption procedure for a 192-bit or 256-bit key. The data randomizing part

has a 24-round Feistel structure with three

-function layers after the 6-th, 12-th, and

F L=F L

(cid:0)

1

18-th rounds, and 128-bit XOR operations before the (cid:12)rst round and after the last round. The

key schedule part generates subkeys

kw

(

t

= 1

2

3

4),

;

;

;

k

(

u

= 1

2

24), and

;

; : : : ;

k l

t(64)

u(64)

v(64)

(

= 1

2

6) from the secret key

.

v

;

; : : : ;

K

In the data randomizing part, (cid:12)rst the plaintext

is XORed with

and

M

kw

jjkw

(128)

1(64)

2(64)

separated into

L

and

R

of equal length, i.e.,

(

) =

.

M

(cid:8)

kw

jjkw

L

jjR

0(64)

0(64)

(128)

1(64)

2(64)

0(64)

0(64)

Then, perform the following operations from

= 1 to 24, except for

= 6, 12, and 18;

r

r

L

R

(cid:8) F

L

; k

=

(

)

;

r

r

1

r

1

r

(cid:0)

(cid:0)

R

L

:

=

r

r

1

(cid:0)

For

= 6, 12, and 18, perform the following;

r

0

L

R

(cid:8) F

L

; k

=

(

)

;

r

1

r

1

r

(cid:0)

(cid:0)

r

0

R

L

;

=

r

r

1

(cid:0)

0

L

F L

L

; k l

=

(

)

;

(cid:0)

r

r

2r=6

1

R

F L

R

; k l

=

(

)

:

r

r

2r=6

(cid:0)

0

1

Lastly,

R

and

L

are concatenated and XORed with

. The resultant

kw

jjkw

24(64)

24(64)

3(64)

4(64)

value is the ciphertext, i.e.,

C

= (

R

jjL

(cid:8)

kw

jjkw

)

(

).

(128)

24(64)

24(64)

3(64)

4(64)

See section 4 for details of the

-function and

-functions.

F

F L=F L

(cid:0)

1

3.3 Decryption Procedure

3.3.1

128-bit key

The decryption procedure of

can be done in the same way as the encryption procedure

Camel lia

by reversing the order of the subkeys.

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

7

Figure 3 shows the decryption procedure for a 128-bit key. The data randomizing part has an

18-round Feistel structure with two

-function layers after the 6-th and 12-th rounds, and

F L=F L

(cid:0)

1

128-bit XOR operations before the (cid:12)rst round and after the last round. The key schedule part

generates subkeys

kw

(

= 1

2

3

4),

t

;

;

;

k

(

= 1

2

18), and

u

;

; : : : ;

k l

(

v

= 1

2

3

4) from

;

;

;

t(64)

u(64)

v(64)

the secret key

; see section 3.4 for details of the key schedule part.

K

In the data randomizing part, (cid:12)rst the ciphertext

is XORed with

and

C

kw

jjkw

(128)

3(64)

4(64)

separated into

R

and

L

of equal length, i.e.,

(

) =

.

C

(cid:8)

kw

jjkw

R

jjL

18(64)

18(64)

(128)

3(64)

4(64)

18(64)

18(64)

Then, the following operations are perfomed from

= 18 down to 1, except for

= 13 and 7;

r

r

R

=

(

L

(cid:8) F

R

; k

)

;

r

1

r

r

r

(cid:0)

L

R

:

=

r

1

r

(cid:0)

For

= 13 and 7, the following is carried out;

r

0

R

L

(cid:8) F

R

; k

=

(

)

;

(cid:0)

r

r

r

r

1

0

L

R

:

=

(cid:0)

r

1

r

0

R

F L

R

; k l

=

(

)

;

(cid:0)

(cid:0)

(cid:0)

r

1

r

1

2(r

1)=6

L

=

F L

(

L

; k l

)

:

(cid:0)

(cid:0)

(cid:0)

(cid:0)

r

1

r

1

2(r

1)=6

1

(cid:0)

0

1

Lastly,

L

and

R

are concatenated and XORed with

. The resultant

kw

jjkw

0(64)

0(64)

1(64)

2(64)

value is the plaintext, i.e.,

= (

)

(

).

M

L

jjR

(cid:8)

kw

jjkw

(128)

0(64)

0(64)

1(64)

2(64)

3.3.2

192-bit and 256-bit key

Figure 4 shows the decryption procedure for a 192-bit or 256-bit key. The data randomizing part

has a 24-round Feistel structure with three

-function layers after the 6-th, 12-th, and

F L=F L

(cid:0)

1

18-th rounds, and 128-bit XOR operations before the (cid:12)rst round and after the last round. The

key schedule part generates subkeys

kw

(

t

= 1

2

3

4),

;

;

;

k

(

u

= 1

2

24), and

;

; : : : ;

k l

t(64)

u(64)

v(64)

(

= 1

2

6) from the secret key

.

v

;

; : : : ;

K

In the data randomizing part, (cid:12)rst the ciphertext

is XORed with

and

C

kw

jjkw

(128)

3(64)

4(64)

separated into

R

and

L

of equal length, i.e.,

(

) =

.

C

(cid:8)

kw

jjkw

R

jjL

24(64)

24(64)

(128)

3(64)

4(64)

24(64)

24(64)

Then, perform the following operations from

= 24 down to 1, except for

= 19, 13, and 7;

r

r

R

L

(cid:8) F

R

; k

=

(

)

;

r

1

r

r

r

(cid:0)

L

R

:

=

r

1

r

(cid:0)

For

= 19, 13, and 7, perform the following.

r

0

R

L

(cid:8) F

R

; k

=

(

)

;

(cid:0)

r

r

r

r

1

0

L

R

:

=

(cid:0)

r

1

r

0

R

F L

R

; k l

=

(

)

;

(cid:0)

(cid:0)

(cid:0)

r

1

r

1

2(r

1)=6

L

=

F L

(

L

; k l

)

:

(cid:0)

(cid:0)

(cid:0)

(cid:0)

r

1

r

1

2(r

1)=6

1

(cid:0)

0

1

Lastly,

L

and

R

are concatenated and XORed with

. The resultant

kw

jjkw

0(64)

0(64)

1(64)

2(64)

value is the plaintext, i.e.,

= (

)

(

).

M

L

jjR

(cid:8)

kw

jjkw

(128)

0(64)

0(64)

1(64)

2(64)

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

8

3.4 Key Schedule

In the key schedule part of

, we introduce two 128-bit variables

K

,

K

and four

L(128)

R(128)

Camel lia

64-bit variables

K

,

K

,

K

and

K

, which are de(cid:12)ned so that the following

LL(64)

LR(64)

RL(64)

RR(64)

relations are satis(cid:12)ed:

K

K

;

K

=

= 0;

for 128-bit key

;

(128)

L(128)

R(128)

K

K

jjK

; K

=

=

K

;

for 192-bit key

;

(192)

L(128)

RL(64)

RR(64)

RL(64)

K

K

jjK

=

;

for 256-bit key

:

(256)

L(128)

R(128)

K

K

jjK

;

=

L(128)

LL(64)

LR(64)

K

K

jjK

=

;

R(128)

RL(64)

RR(64)

for any size of key.

Using these variables, we generate two 128-bit variables

K

and

K

, as shown in

A(128)

B (128)

(cid:12)gure 8, where

is used only if the length of the secret key is 192 or 256 bits. First

K

B (128)

K

K

=

is XORed with

and \encrypted" by two rounds using the constant values

K

L(128)

R(128)

(cid:6)

and (cid:6)

as \keys". The result is XORed with

and again encrypted by two rounds

K

1(64)

2(64)

L(128)

using the constant values (cid:6)

and (cid:6)

; the resultant value is

. Lastly

is XORed

K

K

3(64)

4(64)

A(128)

A(128)

with

K

and encrypted by two rounds using the constant values (cid:6)

and (cid:6)

; the resultant

R(128)

5(64)

6(64)

value is

. (cid:6)

is de(cid:12)ned as the continuous values from the second hexadecimal place to the

K

B (128)

i

seventeenth hexadecimal place of the hexadecimal representation of the square root of the

-th

i

prime. These constant values are listed in table 1.

The subkeys

, and

are generated from (left-half or right-half part of ) rotate

kw

; k

k l

t(64)

u(64)

v(64)

shifted values of

K

,

K

,

K

, and

. The exact details are shown in table 2 and

K

L(128)

R(128)

A(128)

B (128)

table 3, respectively.

Therefore by setting

K

=

K

, the 256-bit version is compatible with the 192-bit

RR(64)

RL(64)

version.

Table 1

: The key schedule constants

(cid:6)

1(64)

(cid:6)

2(64)

(cid:6)

3(64)

(cid:6)

4(64)

(cid:6)

5(64)

(cid:6)

6(64)

0xA09E667F3BCC908B

0xB67AE8584CAA73B2

0xC6EF372FE94F82BE

0x54FF53A5F1D36F1C

0x10E527FADE682D1D

0xB05688C2B3E6C1FD

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

9

Table 2

Table 3

192

256

=

: Subkeys for 128-bit secret key

: Subkeys for

-bit secret key

subkey

value

subkey

value

Prewhitening

kw

(

K

<<<

)

Prewhitening

kw

(

K

<<<

)

L

L

L

L

1(64)

(64)

1(64)

(64)

0

0

kw

(

K

<<<

)

kw

(

K

<<<

)

L

R

L

R

2(64)

(64)

2(64)

(64)

0

0

F

(Round1)

k

(

K

<<<

)

F

(Round1)

k

(

K

<<<

)

A

L

B

L

1(64)

(64)

1(64)

(64)

0

0

F

(Round2)

k

(

K

<<<

)

F

(Round2)

k

(

K

<<<

)

A

R

B

R

2(64)

(64)

2(64)

(64)

0

0

F

(Round3)

k

(

K

<<<

)

F

(Round3)

k

(

K

<<<

)

L

L

R

L

3(64)

(64)

3(64)

(64)

15

15

F

(Round4)

k

(

K

<<<

)

F

(Round4)

k

(

K

<<<

)

L

R

R

R

4(64)

(64)

4(64)

(64)

15

15

F

(Round5)

k

(

K

<<<

)

F

(Round5)

k

(

K

<<<

)

A

L

A

L

5(64)

(64)

5(64)

(64)

15

15

F

(Round6)

k

(

K

<<<

)

F

(Round6)

k

(

K

<<<

)

A

R

A

R

6(64)

(64)

6(64)

(64)

15

15

F L

k l

(

K

<<<

)

F L

k l

(

K

<<<

)

A

L

R

L

1(64)

(64)

1(64)

(64)

30

30

(cid:0)

(cid:0)

1

1

F L

k l

(

K

<<<

)

F L

k l

(

K

<<<

)

A

R

R

R

2(64)

(64)

2(64)

(64)

30

30

F

(Round7)

k

(

K

<<<

)

F

(Round7)

k

(

K

<<<

)

L

L

B

L

7(64)

(64)

7(64)

(64)

45

30

F

(Round8)

k

(

K

<<<

)

F

(Round8)

k

(

K

<<<

)

L

R

B

R

8(64)

(64)

8(64)

(64)

45

30

F

(Round9)

k

(

K

<<<

)

F

(Round9)

k

(

K

<<<

)

A

L

L

L

9(64)

(64)

9(64)

(64)

45

45

F

(Round10)

k

(

K

<<<

)

F

(Round10)

k

(

K

<<<

)

L

R

L

R

10(64)

(64)

10(64)

(64)

60

45

F

(Round11)

k

(

K

<<<

)

F

(Round11)

k

(

K

<<<

)

A

L

A

L

11(64)

(64)

11(64)

(64)

60

45

F

(Round12)

k

(

K

<<<

)

F

(Round12)

k

(

K

<<<

)

A

R

A

R

12(64)

(64)

12(64)

(64)

60

45

F L

k l

(

K

<<<

)

F L

k l

(

K

<<<

)

L

L

L

L

3(64)

(64)

3(64)

(64)

77

60

(cid:0)

(cid:0)

1

1

F L

k l

(

K

<<<

)

F L

k l

(

K

<<<

)

L

R

L

R

4(64)

(64)

4(64)

(64)

77

60

F

(Round13)

k

(

K

<<<

)

F

(Round13)

k

(

K

<<<

)

L

L

R

L

13(64)

(64)

13(64)

(64)

94

60

F

(Round14)

k

(

K

<<<

)

F

(Round14)

k

(

K

<<<

)

L

R

R

R

14(64)

(64)

14(64)

(64)

94

60

F

(Round15)

k

(

K

<<<

)

F

(Round15)

k

(

K

<<<

)

A

L

B

L

15(64)

(64)

15(64)

(64)

94

60

F

(Round16)

k

(

K

<<<

)

F

(Round16)

k

(

K

<<<

)

A

R

B

R

16(64)

(64)

16(64)

(64)

94

60

F

(Round17)

k

(

K

<<<

)

F

(Round17)

k

(

K

<<<

)

L

L

L

L

17(64)

(64)

17(64)

(64)

111

77

F

(Round18)

k

(

K

<<<

)

F

(Round18)

k

(

K

<<<

)

L

R

L

R

18(64)

(64)

18(64)

(64)

111

77

Postwhitening

kw

(

K

<<<

)

F L

k l

(

K

<<<

)

A

L

A

L

3(64)

(64)

5(64)

(64)

111

77

kw

(

K

<<<

)

F L

k l

(

K

<<<

)

A

R

A

R

4(64)

(64)

6(64)

(64)

111

77

(cid:0)

1

F

(Round19)

k

(

K

<<<

)

R

L

19(64)

(64)

94

F

(Round20)

k

(

K

<<<

)

R

R

20(64)

(64)

94

F

(Round21)

k

(

K

<<<

)

A

L

21(64)

(64)

94

F

(Round22)

k

(

K

<<<

)

A

R

22(64)

(64)

94

F

(Round23)

k

(

K

<<<

)

L

L

23(64)

(64)

111

F

(Round24)

k

(

K

<<<

)

L

R

24(64)

(64)

111

Postwhitening

kw

(

K

<<<

)

B

L

3(64)

(64)

111

kw

(

K

<<<

)

B

R

4(64)

(64)

111

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

10

4 Components of

C amellia

4.1

-function

F

The

-function is shown in (cid:12)gure 5, which is de(cid:12)ned as follows:

F

F

:

(cid:2)

(cid:0)!

L

L

L

(

X

; k

7(cid:0)! Y

P

S

X

(cid:8) k

)

=

(

(

))

:

(64)

(64)

(64)

(64)

(64)

See sections 4.4 and 4.6 for the

-function and the

-function, respectively.

S

P

4.2

-function

F L

The

-function is shown in (cid:12)gure 6, which is de(cid:12)ned as follows:

F L

F L

(cid:2)

(cid:0)!

:

L

L

L

(

X

jjX

; k l

jjk l

7(cid:0)! Y

jjY

;

)

L(32)

R(32)

L(32)

R(32)

L(32)

R(32)

where

Y

X

\ k l

<<<

(cid:8) X

;

= ((

)

)

R(32)

L(32)

L(32)

R(32)

1

Y

Y

[ k l

(cid:8) X

:

= (

)

L(32)

R(32)

R(32)

L(32)

(cid:0)

1

F L

4.3

-function

(cid:0)

1

The

-function is shown in (cid:12)gure 7, which is de(cid:12)ned as follows:

F L

(cid:0)

1

F L

(cid:2)

(cid:0)!

:

L

L

L

(

Y

jjY

; k l

jjk l

7(cid:0)! X

jjX

;

)

L(32)

R(32)

L(32)

R(32)

L(32)

R(32)

X

Y

[ k l

(cid:8) Y

;

= (

)

L(32)

R(32)

R(32)

L(32)

X

X

\ k l

<<<

(cid:8) Y

:

= ((

)

)

R(32)

L(32)

L(32)

R(32)

1

where

4.4

-function

S

The

-function is a part of

-function, which is de(cid:12)ned as follows:

S

F

l

jjl

jjl

jjl

jjl

jjl

jjl

jjl

7(cid:0)! l

jjl

jjl

jjl

jjl

jjl

jjl

jjl

1(8)

2(8)

3(8)

4(8)

5(8)

6(8)

7(8)

8(8)

1(8)

2(8)

3(8)

4(8)

5(8)

6(8)

7(8)

8(8)

S

:

(cid:0)!

L

L

0

0

0

0

0

0

0

0

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

11

0

l

=

s

(

l

)

;

1(8)

1

1(8)

0

l

=

s

(

l

)

;

2(8)

2

2(8)

0

l

=

s

(

l

)

;

3(8)

3

3(8)

0

l

=

s

(

l

)

;

4(8)

4

4(8)

0

l

=

s

(

l

)

;

5(8)

2

5(8)

0

l

=

s

(

l

)

;

6(8)

3

6(8)

0

l

=

s

(

l

)

;

7(8)

4

7(8)

0

l

=

s

(

l

)

;

8(8)

1

8(8)

where the four

-boxes,

,

,

, and

, are described in section 4.5.

s

s

s

s

s

1

2

3

4

4.5

-boxes

s

The four

-boxes of

are a(cid:14)ne equivalent to an inversion function over GF(2

), which are

s

Camel lia

8

shown in tables 4, 5, 6, and 7. An algebraic representation of the

-boxes is shown below:

s

s

:

(cid:0)!

B

B

1

x

7(cid:0)!

(cid:8) x

(cid:8)

;

h

g

f

(

(

(

)))

(8)

(8)

0xc5

0x6e

s

:

(cid:0)!

B

B

2

x

7(cid:0)! s

x

<<<

;

(

)

(8)

(8)

1

1

s

:

(cid:0)!

B

B

3

x

7(cid:0)! s

x

>>>

;

(

)

(8)

(8)

1

1

s

:

(cid:0)!

B

B

4

x

7(cid:0)! s

x

<<<

(

)

;

(8)

(8)

1

1

where the functions

, and

are given as follows:

;

f

g

h

f

B

B

:

(cid:0)!

a

jja

jja

jja

jja

jja

jja

jja

1(1)

2(1)

3(1)

4(1)

5(1)

6(1)

7(1)

8(1)

7(cid:0)! b

jjb

jjb

jjb

jjb

jjb

jjb

jjb

;

1(1)

2(1)

3(1)

4(1)

5(1)

6(1)

7(1)

8(1)

where

b

a

(cid:8) a

;

=

1

6

2

b

a

(cid:8) a

;

=

2

7

1

b

a

(cid:8) a

(cid:8) a

;

=

3

8

5

3

b

a

(cid:8) a

;

=

4

8

3

b

a

(cid:8) a

;

=

5

7

4

b

a

(cid:8) a

;

=

6

5

2

b

a

(cid:8) a

;

=

7

8

1

b

a

(cid:8) a

:

=

8

6

4

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

12

g

B

B

:

(cid:0)!

a

jja

jja

jja

jja

jja

jja

jja

1(1)

2(1)

3(1)

4(1)

5(1)

6(1)

7(1)

8(1)

7(cid:0)! b

jjb

jjb

jjb

jjb

jjb

jjb

jjb

;

1(1)

2(1)

3(1)

4(1)

5(1)

6(1)

7(1)

8(1)

where

(

b

+

+

+

) + (

+

+

+

)

b

(cid:11)

b

(cid:11)

b

(cid:11)

b

b

(cid:11)

b

(cid:11)

b

(cid:11)

(cid:12)

8

7

6

5

4

3

2

1

2

3

2

3

= 1

((

+

+

+

) + (

+

+

+

=

a

a

(cid:11)

a

(cid:11)

a

(cid:11)

a

a

(cid:11)

a

(cid:11)

a

(cid:11)

)

)

(cid:12)

:

8

7

6

5

4

3

2

1

2

3

2

3

This inversion is performed in GF(2

) assuming

= 0, where

is an element in GF(2

) that

(cid:12)

0

8

8

1

satis(cid:12)es

+

+

+

+ 1 = 0, and

=

=

+

+

+

is an element in GF(2

) that

(cid:12)

(cid:12)

(cid:12)

(cid:12)

(cid:11)

(cid:12)

(cid:12)

(cid:12)

(cid:12)

(cid:12)

8

6

5

3

238

6

5

3

2

4

satis(cid:12)es

+

+ 1 = 0.

(cid:11)

(cid:11)

4

h

B

B

:

(cid:0)!

a

jja

jja

jja

jja

jja

jja

jja

1(1)

2(1)

3(1)

4(1)

5(1)

6(1)

7(1)

8(1)

7(cid:0)! b

jjb

jjb

jjb

jjb

jjb

jjb

jjb

;

1(1)

2(1)

3(1)

4(1)

5(1)

6(1)

7(1)

8(1)

where

b

a

(cid:8) a

(cid:8) a

;

=

1

5

6

2

b

a

(cid:8) a

;

=

2

6

2

b

a

(cid:8) a

;

=

3

7

4

b

a

(cid:8) a

;

=

4

8

2

b

a

(cid:8) a

;

=

5

7

3

b

a

(cid:8) a

;

=

6

8

1

b

a

(cid:8) a

;

=

7

5

1

b

a

(cid:8) a

:

=

8

6

3

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

13

Table 4

: The

-box

s

s

1

This table below reads

(

) =

(

) =

s

; s

,

,

(

: : :

s

) =

.

1

1

1

0

112

1

130

255

158

112 130

44 236 179

39 192 229 228 133

87

53 234

12 174

65

35 239 107 147

69

25 165

33 237

14

79

78

29 101 146 189

134 184 175 143 124 235

31 206

62

48 220

95

94 197

11

26

166 225

57 202 213

71

93

61 217

1

90 214

81

86 108

77

139

13 154 102 251 204 176

45 116

18

43

32 240 177 132 153

223

76 203 194

52 126 118

5 109 183 169

49 209

23

4 215

20

88

58

97 222

27

17

28

50

15 156

22

83

24 242

34

254

68 207 178 195 181 122 145

36

8 232 168

96 252 105

80

170 208 160 125 161 137

98 151

84

91

30 149 224 255 100 210

16 196

0

72 163 247 117 219 138

3 230 218

9

63 221 148

135

92 131

2 205

74 144

51 115 103 246 243 157 127 191 226

82 155 216

38 200

55 198

59 129 150 111

75

19 190

99

46

233 121 167 140 159 110 188 142

41 245 249 182

47 253 180

89

120 152

6 106 231

70 113 186 212

37 171

66 136 162 141 250

114

7 185

85 248 238 172

10

54

73

42 104

60

56 241 164

64

40 211 123 187 201

67 193

21 227 173 244 119 199 128 158

Table 5

: The

-box

s

s

2

224

5

88 217 103

78 129 203 201

11 174 106 213

24

93 130

70 223 214

39 138

50

75

66 219

28 158 156

58 202

37 123

13 113

95

31 248 215

62 157 124

96 185 190 188 139

22

52

77 195 114 149 171 142 186 122 179

2 180 173 162 172 216 154

23

26

53 204 247 153

97

90 232

36

86

64 225

99

9

51

191 152 151 133 104 252 236

10 218 111

83

98 163

46

8 175

40 176 116 194 189

54

34

56 100

30

57

44 166

48 229

68

253 136 159 101 135 107 244

35

72

16 209

81 192 249 210 160

85 161

65 250

67

19 196

47 168 182

60

43 193 255 200 165

32 137

0 144

71 239 234 183

21

6 205 181

18 126 187

41

15 184

7

4 155 148

33 102 230 206 237 231

59 254 127 197

164

55 177

76 145 110 141 118

3

45 222 150

38 125 198

92

211 242

79

25

63 220 121

29

82 235 243 109

94 251 105 178

240

49

12 212 207 140 226 117 169

74

87 132

17

69

27 245

228

14 115 170 241 221

89

20 108 146

84 208 120 112 227

73

128

80 167 246 119 147 134 131

42 199

91 233 238 143

1

61

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

14

Table 6

: The

-box

s

s

3

56

65

22 118 217 147

96 242 114 194 171 154 117

6

87 160

145 247 181 201 162 140 210 144 246

7 167

39 142 178

73 222

67

92 215 199

62 245 143 103

31

24 110 175

47 226 133

13

83 240 156 101 234 163 174 158 236 128

45 107 168

43

54 166

197 134

77

51 253 102

88 150

58

9 149

16 120 216

66 204

239

38 229

97

26

63

59 130 182 219 212 152 232 139

2 235

10

44

29 176 111 141 136

14

25 135

78

11 169

12 121

17

127

34 231

89 225 218

61 200

18

4 116

84

48 126 180

40

85 104

80 190 208 196

49 203

42 173

15 202 112 255

50 105

8

98

0

36 209 251 186 237

69 129 115 109 132 159 238

74

195

46 193

1 230

37

72 153 185 179 123 249 206 191 223 113

41 205 108

19 100 155

99 157 192

75 183 165 137

95 177

23

244 188 211

70 207

55

94

71 148 250 252

91 151 254

90 172

60

76

3

53 243

35 184

93 106 146 213

33

68

81 198 125

57 131 220 170 124 119

86

5

27 164

21

52

30

28 248

82

32

20 233 189 221 228 161 224 138 241 214 122 187 227

64

79

Table 7

: The

-box

s

s

4

112

44 179 192 228

87 234 174

35 107

69 165 237

79

29 146

134 175 124

31

62 220

94

11 166

57 213

93 217

90

81 108

139 154 251 176 116

43 240 132 223 203

52 118 109 169 209

4

20

58 222

17

50 156

83 242 254 207 195 122

36 232

96 105

170 160 161

98

84

30 224 100

16

0 163 117 138 230

9 221

135 131 205 144 115 246 157 191

82 216 200 198 129 111

19

99

233 167 159 188

41 249

47 180 120

6 231 113 212 171 136 141

114 185 248 172

54

42

60 241

64 211 187

67

21 173 119 128

130 236

39 229 133

53

12

65 239 147

25

33

14

78 101 189

184 143 235 206

48

95 197

26 225 202

71

61

1 214

86

77

13 102 204

45

18

32 177 153

76 194 126

5 183

49

23 215

88

97

27

28

15

22

24

34

68 178 181 145

8 168 252

80

208 125 137 151

91 149 255 210 196

72 247 219

3 218

63 148

92

2

74

51 103 243 127 226 155

38

55

59 150

75 190

46

121 140 110 142 245 182 253

89 152 106

70 186

37

66 162 250

7

85 238

10

73 104

56 164

40 123 201 193 227 244 199 158

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

15

4.6

-function

P

The

-function is a part of

-function, which is de(cid:12)ned as follows:

P

F

z

jjz

jjz

jjz

jjz

jjz

jjz

jjz

7(cid:0)! z

jjz

jjz

jjz

jjz

jjz

jjz

jjz

;

1(8)

2(8)

3(8)

4(8)

5(8)

6(8)

7(8)

8(8)

1(8)

2(8)

3(8)

4(8)

5(8)

6(8)

7(8)

8(8)

P

:

(cid:0)!

L

L

0

0

0

0

0

0

0

0

where

0

z

=

z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

;

1

3

4

6

7

8

1

0

z

=

z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

;

1

2

4

5

7

8

2

0

z

z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

;

=

1

2

3

5

6

8

3

0

z

z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

;

=

2

3

4

5

6

7

4

0

z

z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

;

=

1

2

6

7

8

5

0

z

z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

;

=

2

3

5

7

8

6

0

z

z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

;

=

3

4

5

6

8

7

0

z

z

(cid:8) z

(cid:8) z

(cid:8) z

(cid:8) z

:

=

1

4

5

6

7

8

Equivalently, this transformation can be given in the following form:

where

z

z

z

8

8

8

0

1

0

1

0

1

0

0

z

z

z

7

7

7

B

C

B

C

B

C

7(cid:0)!

=

P

;

.

.

.

B

C

B

C

B

C

.

.

.

B

C

B

C

B

C

.

.

.

B

C

B

C

B

C

0

@

A

@

A

@

A

1

1

1

z

z

z

0 1 1 1 1 0 0 1

0

1

1 0 1 1 1 1 0 0

B

C

1 1 0 1 0 1 1 0

B

C

B

C

1 1 1 0 0 0 1 1

B

C

P

=

B

C

:

B

C

0 1 1 1 1 1 1 0

B

C

B

C

1 0 1 1 0 1 1 1

B

C

B

C

1 1 0 1 1 0 1 1

B

C

B

C

1 1 1 0 1 1 0 1

@

A

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

16

A Figures of the

Algorithm

C amellia

M(128)

kw1(64)

kw

2(64)

L 0(64)

R0(64)

k1(64),
k4(64),

k2(64),
k5(64),

k3(64),
k 6(64)

6-Round

kl1(64)

FL

FL -1

kl2(64)

k7(64),
k10(64),

k8(64),
k11(64),

k9(64),
k 12(64)

6-Round

kl3(64)

FL

FL -1

kl4(64)

k13(64),
k16(64),

k14(64),
k17(64),

k15(64),
k 18(64)

6-Round

L18(64)

R18(64)

kw3(64)

kw4(64)

C(128)

L 0(64)

k1(64)

L1(64)

k 2(64)

L 2(64)

k 3(64)

L 3(64)

k 4(64)

L 4(64)

k 5(64)

L 5(64)

k 6(64)

R0(64)

R1(64)

R2(64)

R3(64)

R4(64)

R 5(64)

F

F

F

F

F

F

Figure 1

: Encryption Procedure of

for 128-bit key

Camel lia

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

17

L 0(64)

k 1(64)

L1(64)

k 2(64)

L2(64)

k 3(64)

L3(64)

k 4(64)

L4(64)

k 5(64)

L5(64)

k 6(64)

R0(64)

R1(64)

R2(64)

R3(64)

R4(64)

R5(64)

F

F

F

F

F

F

M(128)

kw1(64)

kw

2(64)

L 0(64)

R 0(64)

k1(64),
k4(64),

k2(64),
k5(64),

k3(64),
k 6(64)

6-Round

kl1(64)

FL

FL -1

kl2(64)

k7(64),
k10(64),

k8(64),
k11(64),

k9(64),
k 12(64)

6-Round

kl3(64)

FL

FL -1

kl4(64)

k13(64),
k16(64),

k14(64),
k17(64),

k15(64),
k 18(64)

6-Round

kl5(64)

FL

FL -1

kl6(64)

k19(64),
k22(64),

k20(64),
k23(64),

k21(64),
k 24(64)

6-Round

L24(64)

R24(64)

kw3(64)

kw4(64)

C(128)

Figure 2

: Encryption Procedure of

for 192-bit and 256-bit key

Camel lia

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

18

C(128)

kw3(64)

kw

4(64)

R18(64)

L18(64)

k18(64),
k15(64),

k17(64),
k14(64),

k16(64),
k 13(64)

6-Round

kl4(64)

FL

FL -1

kl3(64)

k12(64),
k9(64),

k11(64),
k8(64),

k10(64),
k 7(64)

6-Round

kl2(64)

FL

FL -1

kl1(64)

k6(64),
k3(64),

k5(64),
k2(64),

k4(64),
k 1(64)

6-Round

R 0(64)

L 0(64)

kw1(64)

kw

2(64)

M(128)

R18(64)

k 18(64)

R17(64)

k 17(64)

R16(64)

k 16(64)

R15(64)

k 15(64)

R14(64)

k 14(64)

R13(64)

k 13(64)

F
F

F
F

F
F

F
F

F
F

F
F

L 18(64)

L 17(64)

L16(64)

L15(64)

L14(64)

L 13(64)

Figure 3

: Decryption Procedure of

for 128-bit key

Camel lia

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

19

C(128)

kw3(64)

kw

4(64)

R 24(64)

L 24(64)

k 24(64),
k 21(64),

k 23(64),
k 20(64),

k 22(64),
k 19(64)

6-Round
6-Round

kl 6(64)

FL

FL -1

kl 5(64)

k18(64),
k15(64),

k17(64),
k14(64),

k16(64),
k 13(64)

6-Round

R24(64)

k 24(64)

R23(64)

k 23(64)

R22(64)

k 22(64)

R21(64)

k 21(64)

kl4(64)

FL

FL -1

kl3(64)

R20(64)

k 20(64)

k12(64),
k 9(64),

k 11(64),
k 8(64),

k10(64),
k 7(64)

6-Round

R19(64)

k 19(64)

L24(64)

L23(64)

L22(64)

L21(64)

L20(64)

L19(64)

F
F

F
F

F
F

F
F

F
F

F
F

kl2(64)

FL

FL -1

kl1(64)

k 6(64),
k 3(64),

k 5(64),
k 2(64),

k4(64),
k 1(64)

6-Round

R0(64)

L 0(64)

kw1(64)

kw2(64)

M(128)

Figure 4

: Decryption Procedure of

for 192-bit and 256-bit key

Camel lia

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

20

k

i (64)

y 8

y 7

y 6

y 5

y 4

y 3

y 2

y 1

z 8

z 7

z 6

z 5

z 4

z 3

z 2

z 1

s
1

s
4

s
3

s
2

s
4

s
3

s
2

s
1

x 8(8)

x 7(8)

x 6(8)

x 5(8)

x 4(8)

x 3(8)

x 2(8)

x 1(8)

z’ 8(8)

z’ 7(8)

z’ 6(8)

z’ 5(8)

z’ 4(8)

z’ 3(8)

z’ 2(8)

z’ 1(8)

S-Function

P-Function

Figure 5

:

-function

F

X(64)

Y(64)

XL(32)

XR(32)

YL(32)

YR(32)

1

kl i L(32)

kl i R(32)

kl i R(32)

kl i L(32)

1

YL(32)

YR(32)

XL(32)

XR(32)

Y(64)

X (64)

Figure 6

Figure 7

:

-function

F L

:

F L

-function

(cid:0)

1

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

21

K L(128)

K R(128)

Σ1(64)

Σ2(64)

Σ3(64)

Σ4(64)

K L(128)

F

F

F

F

K R(128)

F

F

Σ5(64)

Σ6(64)

K A(128)

K B(128)

Figure 8

: Key Schedule

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

22

B Test Data

The following is test data for

in hexadecimal form:

Camel lia

128-bit key

key

01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10

plaintext

01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10

ciphertext

67 67 31 38 54 96 69 73 08 57 06 56 48 ea be 43

192-bit key

key

01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10

00 11 22 33 44 55 66 77

plaintext

01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10

ciphertext

b4 99 34 01 b3 e9 96 f8 4e e5 ce e7 d7 9b 09 b9

256-bit key

key

01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10

00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff

plaintext

01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10

ciphertext

9a cc 23 7d ff 16 d7 6c 20 ef 7c 91 9e 3a 75 09

C Software Implementation Techniques

This section describes how to implement Camellia e(cid:14)ciently in software. In most cases, an imple-

mentation can be divided into two parts:

including key schedule and

, that

setup

data randomization

is, encryption or decryption. We (cid:12)rst describe how to optimize the setup code, and then describe

how to optimize the data randomization code.

This section describes speci(cid:12)c techniques for 8-, 32-, or 64-bit processors. However, a tech-

nique for 8-bit processors may be applicable to 32- or 64-bit processors and a technique for 32-bit

processors may be applicable to 64-bit processors. Other word sizes may need to be considered.

We assume that you (cid:12)rst implement Camellia using the speci(cid:12)cation as it is. This section will

optimize the resulting code.

Note that in this section \word" means the natural size of the target processor. For example,

the words of IA-32 without MMX technology, IA-32 with MMX technology and Alpha are 32-, 64-,

and 64-bits long respectively.

C.1 Setup

C.1.1 Store All Subkeys

Store all subkeys into memory once you generate them if you have su(cid:14)cient memory, and use the

stored subkeys for data randomization.

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

23

C.1.2 Subkey Generation Order

You do not have to compute subkeys in order. For example, when you compute subkeys for a

128-bit key, (cid:12)rst compute the subkeys that only depend on

, and then compute subkeys that

K

L

only depend on

. You can save registers or memory for storing

.

K

K

A

A

C.1.3 XOR Cancellation Property in Key Schedule

The key schedule of Camellia is based on the Feistel structure. Between the 2nd round and the 3rd

round,

is XORed to an intermediate value. This structure causes cancellations of

. More

K

K

L

L

precisely, the input of the 3rd round can be computed by the following equations.

(left half )

=

(

(right half )

(cid:6)

)

F

K

;

2

LR

(cid:8)

(right half ) =

(

(cid:6)

)

F

K

;

1

LL

for 128-bit keys

(

(

(left half )

=

(

(right half )

(cid:6)

)

K

F

K

;

2

RL

LR

(cid:8)

(cid:8)

(right half ) =

(

(cid:6)

)

1

K

F

K

K

;

RR

LL

RL

(cid:8)

(cid:8)

for 192- and 256-bit keys

Using the above equations, we can eliminate 3 and 2 XORs in L for 128- and 192/256-bit keys,

respectively, compared to the straightforward implementation of the speci(cid:12)cation.

C.1.4 Rotation Bits for

,

,

, and

K

K

K

K

L

R

A

B

You do not need to keep

,

,

, and

, but you should keep their rotated values when

K

K

K

K

L

R

A

B

generating subkeys. You can generate subkeys by rotating the kept values by integral multiples of

16

1 bits.

(cid:6)

C.1.5

and

generation from

and

5

6

11

12

kl

kl

k

k

For 192- and 256- bit keys, you can use a word-oriented rotation to generate (

) from (

),

k l

; k l

k

; k

5

6

11

12

since (

) equals (

)

. This saves a few instructions compared to general rotation.

k l

; k l

5

6

k

; k

<<<

11

12

32

C.1.6 On-the-(cid:13)y Subkey Generation

You can generate subkeys

. All subkeys are one of the rotated values of

,

,

,

on-the-(cid:13)y

K

K

K

L

R

A

and

. Thus, you (cid:12)rst generate

,

,

, and

, and then rotate them to get the subkeys.

K

K

K

K

K

B

L

R

A

B

Refer Section C.1.4 for the rotated numbers of bits for

,

,

, and

.

K

K

K

K

L

R

A

B

C.1.7

128-bit key and 192/256-bit key

If your code does not need to use larger key sizes than 128 bits, you do not need to generate

.

K

B

That is, you can omit the computations for the last two

-functions.

F

C.1.8 How to Rotate an Element in Q

8-bit processor. As stated in Section C.1.4, the rotation bits are integral multiples of 16

1.

(cid:6)

Thus, you can rotate an element in Q by 16

1 bits by rotating 1-bit left or right followed by a

(cid:6)

2-byte move.

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

24

32-bit processor. Consider the use of a double precision shift instruction:

or

if you

shrd

shld

are programming on IA-32.

C.1.9

-function

F

Key schedule includes

-functions, but the main usage of the

-function is for data randomization.

F

F

Refer to Section C.2.

C.1.10 Keyed Functions

Camellia has three keyed functions: bitwise XOR, bitwise OR, and bitwise AND. Consider the use

of a self-modifying code, if possible.

C.2 Data Randomization

C.2.1 Endian Conversion

Camellia prefers big endian. Thus, the code for little endian processors needs additional code for

endian conversions.

The most straightforward implementation converts the endian when loading a register from

memory and storing a register to memory. Only

- and

-functions are endian dependent.

F L

F L

More precisely, only the 1-bit rotation in

- or

-function is endian dependent. This means

F L

F L

(cid:0)

1

(cid:0)

1

that you can convert endians just before or just after the 1-bit rotation with the appropriate subkey

generation scheme. A combination of computing endian conversion and 1-bit rotation may increase

the performance of Camellia using this technique. Details are described in Section C.2.2.

Some processors have a special instruction for endian conversion. For example, IA-32 (after

80486) has

instruction. Use these instructions. However, do not use the byte swap technique

bswap

described in [C98, Appendix A]. The technique reduces the code size, but it is not fast, since the

memory load and store instruction incurs long latency.

As described above, the endian problem only e(cid:11)ects the 1-bit rotation of a 32-bit word. Thus,

we do not need full 64-bit word endian conversion.

The following are general methods to realize endian conversion for 32-bit register

.

In the

x

following techniques, you can use either

or

instead of + in the equations, and you can switch the

[

(cid:8)

computational order between shifts including rotations and ANDs with an appropriate conversion

of masked constants.

Straightforward.

x

x

x

x

x

(

) + ((

)

) + ((

24

0xff00

8

8

)

0xff00

) + (

24

)

(cid:28)

\

(cid:28)

(cid:29)

\

(cid:29)

The technique has high parallelism.

Minimum operations without rotation.

x

x

x

(

) + (

16

16

)

(cid:28)

(cid:29)

x

x

x

((

)

) + ((

0xff00ff

8

8

)

0xff00ff

)

\

(cid:28)

(cid:29)

\

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

25

Using rotations.

x

x

>>>

x<<<

((

)

) + ((

0xff00ff

8

8

)

0xff00ff

)

\

\

Using SSE. New Intel Pentium family processors including Pentium III has very e(cid:11)ective in-

struction for reordering data, which is called

[I99]. 5 instructions including

are

pshufw

pshufw

su(cid:14)cient to convert endian for 64-bit data.

C.2.2

1-bit Rotation in Little Endian Interpretation

As described in Section C.2.1, we do not need endian conversion when loading and storing texts if

we can e(cid:14)ciently implement 1-bit rotation in

- and

-functions.

F L

F L

(cid:0)

1

Considering

as a 32-bit register that contains little endian data to be rotated by 1-bit. We

x

can compute 1-bit rotation by the following equation.

x

x

x>>>

((2

)

) + ((

0xfefefefe

15

)

0xfefefefe

)

(1)

\

\

Of course, this technique requires an appropriate changes to subkey setup and other functions.

Note that + in Equation (1) can be replaced with

or

, and computing 2

can be done

[

(cid:8)

x

by

1

,

<<<

1

(cid:28)

or addition with

itself, and you can switch the computational order between shifts

x

including rotations and ANDs with an appropriate conversion of masked constants.

Con(cid:12)rm whether your processor has ANDNOT instruction, such as

in IA-32 and

in

pandn

bic

Alpha. In this case, you do not need to prepare the constant,

0xfefefefe

.

C.2.3 Whitening

The key additions

and

can be combined into other keyed operations using the following

kw

kw

2

4

equations.

(

)

= (

)

x

k

y

x

y

k ;

(cid:8)

(cid:8)

(cid:8)

(cid:8)

(

)

=

(

)

x

k

l

x

k

l

;

(cid:8)

(cid:8)

(cid:8)

(cid:8)

(

)

= (

)

(

)

(2)

x

k

l

x

l

k

l

;

(cid:8)

\

\

(cid:8)

\

(

)

= (

)

(

1

1

1

)

x

k

<<<

x<<<

k<<<

;

(cid:8)

(cid:8)

(

)

= (

)

(

)

x

k

l

x

l

k

l

;

(cid:8)

[

[

(cid:8)

\

where

,

,

,

are bit strings. Adjust subkeys at setup to eliminate 2 XORs in L.

x

y

k

l

C.2.4 Key XOR

Using Equations (2), you can move key XORs to any place if the movement does not go through

the

-function. For example, changing

-function computation

(

(

)) to

(

(

))

may

S

F

P

S

X

k

P

S

X

k

(cid:8)

(cid:8)

0

improve instruction scheduling.

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

26

C.2.5

-function

S

s

1

is de(cid:12)ned by the arithmetics in GF(2

). However, do not compute GF(2

) arithmetics; instead

8

8

precompute and hard-code a table in your program, see Table 4 in the speci(cid:12)cation.

We strongly suggest that you also precompute and hard-code

,

, and

tables in addition

s

s

2

3

s

4

to

, if you have a su(cid:14)cient memory and 8-bit rotation is expensive. If you do not have su(cid:14)cient

s

1

memory, please compute

,

, and

from looked-up values in

table using rotation.

s

s

2

3

s

4

s

1

If you have su(cid:14)cient memory, and cost of table lookup is heavy as is true for Java, consider the

use of a two

-box combined table, for example (

(

)

(

)).

s

s

y

; s

y

1

1

2

2

C.2.6

-function

P

32-bit processor. Let (

) = ((

)

(

)) be the input of

-function and

Z

; Z

z

; z

; z

; z

;

z

; z

; z

; z

P

1

2

3

4

5

6

7

8

L

R

0

0

0

0

0

0

0

0

0

0

(

) = ((

)

(

)) be the output of

-function.

Z

; Z

z

; z

; z

; z

;

z

; z

; z

; z

P

L

R

1

2

3

4

5

6

7

8

From Figure 5 in the speci(cid:12)cation, you can see that

-function can be computed as follows.

P

Z

Z

Z

<<<

(

8

)

L

L

R

(cid:8)

Z

Z

Z

<<<

(

16

)

R

R

L

(cid:8)

Z

Z

Z

>>>

(

8

)

L

L

R

(cid:8)

Z

Z

Z

>>>

(

8

)

R

R

L

(cid:8)

0

Z

Z

R

L

0

Z

Z

R

L

The critical path of the new computation is long. We can modify the computation as follows.

Z

Z

<<<

8

R

R

Z

Z

Z

Z

Z

<<<

8

L

L

R

R

R

(cid:8)

Z

Z

>>>

Z

Z

Z

8

L

L

R

R

L

(cid:8)

Z

Z

Z

Z

Z

<<<

16

L

L

R

R

R

(cid:8)

Z

Z

<<<

Z

Z

Z

8

L

L

R

R

L

(cid:8)

0

0

Z

Z

Z

Z

R

L

L

R

The critical path of the above computation is decreased. It seems that the technique requires one

additional rotation, however, you can probably combine the (cid:12)rst step of the above computation

and

-function without any additional cost.

S

8-bit processor (orthogonal mnemonics).

If the instruction in your processor can XOR any

combination of registers and has su(cid:14)cient registers, you can compute

-function by using just 16

P

XORs using Figure 5 in the speci(cid:12)cation.

8-bit processor (accumulator based).

If your processor is accumulator based, minimizing

the number of XORs is not always a good idea, since the computation may require register load

from memory and store into memory many times. The following computation is optimized for an

accumulator based processor.

0

z

z

z

z

z

z

1

4

5

6

7

8

(cid:8)

(cid:8)

(cid:8)

(cid:8)

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

27

0

0

z

z

z

z

z

1

2

3

4

8

(cid:8)

(cid:8)

(cid:8)

0

0

z

z

z

z

z

2

7

8

7

4

(cid:8)

(cid:8)

(cid:8)

0

0

z

z

z

z

z

1

2

4

3

7

(cid:8)

(cid:8)

(cid:8)

0

0

z

z

z

z

z

1

6

7

6

3

(cid:8)

(cid:8)

(cid:8)

0

0

z

z

z

z

z

1

3

4

2

6

(cid:8)

(cid:8)

(cid:8)

0

0

z

z

z

z

z

4

5

6

5

2

(cid:8)

(cid:8)

(cid:8)

0

0

z

z

z

z

z

2

3

4

1

5

(cid:8)

(cid:8)

(cid:8)

When indexing

costs many operations, the following is useful.

i

0

z

(cid:27)

z

z

z

z

z

z

z

z

1

2

3

4

5

6

7

8

(cid:8)

(cid:8)

(cid:8)

(cid:8)

(cid:8)

(cid:8)

(cid:8)

0

z

(cid:27)

z

z

2

5

(cid:8)

(cid:8)

1

0

z

(cid:27)

z

z

3

6

(cid:8)

(cid:8)

2

0

z

(cid:27)

z

z

4

7

(cid:8)

(cid:8)

3

0

z

(cid:27)

z

z

1

8

(cid:8)

(cid:8)

4

0

z

(cid:27)

z

z

z

3

4

5

(cid:8)

(cid:8)

(cid:8)

5

0

z

(cid:27)

z

z

z

1

4

6

(cid:8)

(cid:8)

(cid:8)

6

0

z

(cid:27)

z

z

z

1

2

7

(cid:8)

(cid:8)

(cid:8)

7

0

z

(cid:27)

z

z

z

2

3

8

8

(cid:8)

(cid:8)

(cid:8)

C.2.7 Substitution and Permutation

This section describes how to e(cid:14)ciently compute

compared to independently computing

P

S

S

(cid:14)

and

.

P

64-bit processor.

If your processor has a su(cid:14)ciently large (cid:12)rst level cache, use the technique

described in [RDP

96]. The technique prepares the following tables de(cid:12)ned by equation (3).

+

SP

y

s

y

; s

y

; s

y

;

; s

y

;

;

; s

y

1

1

1

1

1

1

1

1

1

1

1

1

(

) = (

(

)

(

)

(

)

0

(

)

0

0

(

))

SP

y

2

2

; s

y

; s

y

; s

y

; s

y

; s

y

;

;

2

2

2

2

2

2

2

2

2

2

(

) = (

0

(

)

(

)

(

)

(

)

(

)

0

0)

SP

y

s

y

;

; s

y

; s

y

;

; s

y

; s

y

;

3

3

3

3

3

3

3

3

3

3

3

3

(

) = (

(

)

0

(

)

(

)

0

(

)

(

)

0)

SP

y

s

y

; s

y

;

; s

y

;

;

; s

y

; s

y

4

4

4

4

4

4

4

4

4

4

4

4

(

) = (

(

)

(

)

0

(

)

0

0

(

)

(

))

SP

y

5

5

; s

y

; s

y

; s

y

;

; s

y

; s

y

; s

y

2

5

2

5

2

5

2

5

2

5

2

5

(

) = (

0

(

)

(

)

(

)

0

(

)

(

)

(

))

(3)

SP

y

s

y

;

; s

y

; s

y

; s

y

;

; s

y

; s

y

6

6

3

6

3

6

3

6

3

6

3

6

3

6

(

) = (

(

)

0

(

)

(

)

(

)

0

(

)

(

))

SP

y

s

y

; s

y

;

; s

y

; s

y

; s

y

;

; s

y

7

7

4

7

4

7

4

7

4

7

4

7

4

7

(

) = (

(

)

(

)

0

(

)

(

)

(

)

0

(

))

SP

y

s

y

; s

y

; s

y

;

; s

y

; s

y

; s

y

;

8

8

1

8

1

8

1

8

1

8

1

8

1

8

(

) = (

(

)

(

)

(

)

0

(

)

(

)

(

)

0)

Next, compute the following equation:

0

0

0

0

0

0

0

0

8

(

)

(

)

z

; z

; z

; z

; z

; z

; z

; z

SP

y

1

2

3

4

5

6

7

8

i

i

=1

i

M

This technique requires the following operations.

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

28

# of Table Lookups

8

# of XORs

7

Size of Table (KB)

16

If the (cid:12)rst cache of the target processor is moderately large, replace a few of tables de(cid:12)ned by

equation (3) with the tables below.

SP

y

s

y

; s

y

; s

y

; s

y

; s

y

; s

y

; s

y

; s

y

(

) = (

(

)

(

)

(

)

(

)

(

)

(

)

(

)

(

))

1

1

1

1

1

1

1

1

(cid:11)

SP

y

s

y

; s

y

; s

y

; s

y

; s

y

; s

y

; s

y

; s

y

(

) = (

(

)

(

)

(

)

(

)

(

)

(

)

(

)

(

))

2

2

2

2

2

2

2

2

(cid:12)

(4)

SP

y

s

y

; s

y

; s

y

; s

y

; s

y

; s

y

; s

y

; s

y

(

) = (

(

)

(

)

(

)

(

)

(

)

(

)

(

)

(

))

3

3

3

3

3

3

3

3

(cid:13)

SP

y

s

y

; s

y

; s

y

; s

y

; s

y

; s

y

; s

y

; s

y

(

) = (

(

)

(

)

(

)

(

)

(

)

(

)

(

)

(

))

4

4

4

4

4

4

4

4

(cid:14)

Then, mask the necessary byte positions. This technique requires the following operations if you

use only tables of equation (4).

# of Table Lookups

8

# of XORs

7

# of ANDs

8

Size of Table (KB)

8

When implementing this technique on Alpha architecture [C98], and if the number of registers is

insu(cid:14)cient for storing constants for masking operation, use

or

instructions.

zap

zapnot

If your processor can e(cid:14)ciently copy half bits of a register to the other half, for example,

punpckldq

punpckhdq

pshufw

/

or

instructions in IA-32 [I99] which are realized after Pentium with

MMX technology and Pentium III, respectively, prepare

SP

SP

SP

SP

1

,

2

,

3

4

, and

de(cid:12)ned in equa-

tion (3). Then, compute the following equation:

0

0

0

0

0

0

0

0

(

)

z

; z

; z

; z

; z

; z

; z

; z

1

2

3

4

5

6

7

8

SP

y

SP

y

SP

y

SP

y

(cid:23)

SP

y

SP

y

SP

y

SP

y

;

1

1

2

2

3

3

4

4

1

8

2

5

3

6

4

7

(

)

(

)

(

)

(

)

(

(

)

(

)

(

)

(

))

(cid:8)

(cid:8)

(cid:8)

(cid:8)

(cid:8)

(cid:8)

(cid:8)

where

denotes the operation that copies the (cid:12)rst 4 bytes to the last 4 bytes. This technique

(cid:23)

requires the following operations.

# of Table Lookups

8

# of XORs

7

# of

s

1

(cid:23)

Size of Table (KB)

8

32-bit processor.

[AU00] shows e(cid:14)cient implementations of Camellia-type substitution and

permutation networks. One of the technique prepares the following tables de(cid:12)ned by equation (5):

SP

y

s

y

; s

y

; s

y

;

1110

1

1

1

(

) = (

(

)

(

)

(

)

0)

SP

y

; s

y

; s

y

; s

y

0222

2

2

2

(

) = (

0

(

)

(

)

(

))

SP

y

s

y

;

; s

y

; s

y

3033

3

3

3

(

) = (

(

)

0

(

)

(

))

(5)

SP

y

s

y

; s

y

;

; s

y

4404

4

4

4

(

) = (

(

)

(

)

0

(

))

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

29

Then, compute as follows:

D

SP

y

SP

y

SP

y

SP

y

1110

8

0222

5

3033

6

4404

7

(

)

(

)

(

)

(

)

(cid:8)

(cid:8)

(cid:8)

U

SP

y

SP

y

SP

y

SP

y

1110

1

0222

2

3033

3

4404

4

(

)

(

)

(

)

(

)

(cid:8)

(cid:8)

(cid:8)

0

0

0

0

z

; z

; z

; z

D

U

(

)

1

2

3

4

(cid:8)

0

0

0

0

0

0

0

0

(

)

(

)

(

8

)

z

; z

; z

; z

z

; z

; z

; z

U >>>

5

6

7

8

1

2

3

4

(cid:8)

This technique requires the following operations.

# of Table Lookups

8

# of XORs

8

# of Rotations

1

Size of Table (KB)

4

[AU00] also shows an implementation that is suitable for a processor in which rotation is very

costly. The technique prepares the following tables in addition to tables de(cid:12)ned by equation (5):

SP

y

s

y

;

;

; s

y

1001

1

1

(

) = (

(

)

0

0

(

))

SP

y

s

y

; s

y

;

;

2200

2

2

(

) = (

(

)

(

)

0

0)

SP

y

; s

y

; s

y

;

0330

3

3

(

) = (

0

(

)

(

)

0)

SP

y

;

; s

y

; s

y

0044

4

4

(

) = (

0

0

(

)

(

))

Then, compute as follows:

D

SP

y

SP

y

SP

y

SP

y

1110

8

0222

5

3033

6

4404

7

(

)

(

)

(

)

(

)

(cid:8)

(cid:8)

(cid:8)

0

0

0

0

(

)

(

)

(

)

(

)

(

)

z

; z

; z

; z

D

SP

y

SP

y

SP

y

SP

y

1110

1

0222

2

3033

3

4404

4

1

2

3

4

(cid:8)

(cid:8)

(cid:8)

(cid:8)

0

0

0

0

(

)

(

)

(

)

(

)

(

)

z

; z

; z

; z

D

SP

y

SP

y

SP

y

SP

y

1001

1

2200

2

0330

3

0044

4

5

6

7

8

(cid:8)

(cid:8)

(cid:8)

(cid:8)

This technique requires the following operations.

# of Table Lookups

12

# of XORs

11

Size of Table (KB)

8

C.2.8 Making Indices for

-box

s

You can make an index for

-box by simply using shifts and ANDs. However, several processors have

s

special instructions for making an index, for example,

in IA-32 [I99],

in Alpha [C98].

movzx

extbl

movzx

is a fast operation in P6, but it can be used only for the two least signi(cid:12)cant bytes. A

straightforward implementation uses

,

,

, and

registers for storing (

), and 2

eax

ebx

ecx

edx

L

; R

r

r

rotations are used for making indices; 2 rotations are used for recovering byte order in the registers

every round. However, you can remove 2 rotations for recovering byte order every round if you

prepare rotated tables. Note that the byte order in registers returns to a natural order every 4

rounds.

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

30

C.3 General Guidelines

This section describes general guidelines. The guidelines are useful to optimize Camellia as well as

other block ciphers. Please refer to the optimization manuals for each processor.

Avoid misaligned data accesses. Almost all processors penalize misaligned data access. Align

data to the word boundary.

Avoid partial data accesses. Most processors have a function to access a smaller part than word

size. However, this function may cause a penalty. Do not access partial data, even if you do

not need full size of word and you have su(cid:14)cient memory.

Be careful of the size of the cache. If the program or its data exceeds the size of the cache,

the speed of the program will signi(cid:12)cantly decrease. Loop unrolling and table expansion are

good techniques to speed up the program, but do not exceed the size of the cache.

Use intrinsic functions. Several compilers support intrinsic functions. For example, when you

use Microsoft Visual C++ 6 compiler on IA-32, and declare \

#pragma intrinsic( lrotl)

"

and use \

", the compiler generates rotation instructions in assembly language. Refer

lrotl

to the manual of the compiler that you use for details.

Measuring precise speeds is di(cid:14)cult. The running time of your code depends on many fac-

tors: cache hit misses, OS interrupts, and so on. Furthermore, the cryptographic properties,

for example, the number of blocks to be encrypted, also e(cid:11)ect the running time.

A few processors have an instruction to get the time stamp. For example, IA-32 (after

Pentium) has

[I99] and Alpha has

[C98].

It is a good idea to use the time

rdtsc

rpcc

stamp counter for measuring speeds, but you should not directly apply these instructions to

out-of-order architectures such as P6 and EV6.

If you want to measure speed precisely, consult good guidebooks. For example, if you use

Pentium family processors, refer to [F00].

D Design Policy

This paper presents a 128-bit block cipher called

, which was jointly developed by NTT

Camel lia

and Mitsubishi Electric Corporation. Camellia supports 128-bit block size and 128-, 192-, and

256-bit key lengths, and so o(cid:11)ers the same interface speci(cid:12)cations as the Advanced Encryption

Standard (AES). The design goals of Camellia are as follows.

High level of security. The recent advances in cryptanalytic techniques are remarkable. A

quantitative evaluation of security against powerful cryptanalytic techniques such as di(cid:11)erential

cryptanalysis [BS93] and linear cryptanalysis [M94] is considered to be essential in designing any

new block cipher. We evaluated the security of Camellia by utilizing state-of-art cryptanalytic

techniques. We have con(cid:12)rmed that Camellia has no di(cid:11)erential and linear characteristics that hold

with probability more than 2

. Moreover, Camellia was designed to o(cid:11)er security against other

(cid:0)

128

advanced cryptanalytic attacks including higher order di(cid:11)erential attacks [K95, JK97], interpolation

attacks [JK97, A00], related-key attacks [B94, KSW96], truncated di(cid:11)erential attacks [K95, MT99],

boomerang attacks [W99], and slide attacks [BW99, BW00].

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

31

E(cid:14)ciency on multiple platforms. As cryptographic systems are needed in various applica-

tions, encryption algorithms that can be implemented e(cid:14)ciently on a wide range of platforms are

desirable, however, few 128-bit block ciphers are suitable for both software and hardware imple-

mentation. Camellia was designed to o(cid:11)er excellent e(cid:14)ciency in hardware and software implemen-

tations, including gate count for hardware design, memory requirements in smart card implemen-

tations, as well as performance on multiple platforms.

Camellia consists of only 8-by-8-bit substitution tables (

-boxes) and logical operations that

s

can be e(cid:14)ciently implemented on a wide variety of platforms. Therefore, it can be implemented

e(cid:14)ciently in software, including the 8-bit processors used in low-end smart cards, 32-bit processors

widely used in PCs, and 64-bit processors. Camellia doesn’t use 32-bit integer additions and

multiplications, which are extensively used in some software-oriented 128-bit block ciphers. Such

operations perform well on platforms providing a high degree of support, e.g., Pentium II/III or

Athlon, but not as well on others. These operations can cause a longer critical path and larger

hardware implementation requirements.

The

-boxes of Camellia are designed to minimize hardware size. The four

-boxes are a(cid:14)ne

s

s

equivalent to the inversion function in the (cid:12)nite (cid:12)eld GF(2

). Moreover, we reduced the inversion

8

function in GF(2

) to a few GF(2

) arithmetic operations. It enabled us to implement the

-boxes

s

8

4

by fewer gate counts.

The key schedule is very simple and shares part of its procedure with encryption. It supports

on-the-key subkey generation and subkeys are computable in any order. The memory requirement

for generating subkeys is quite small; an e(cid:14)cient implementation requires about 32-byte RAM for

128-bit keys and about 64-byte RAM for 192- and 256-bit keys.

E Design Rationale

E.1

-function

F

The design strategy of the

-function of Camellia follows that of the

-function of E2 [KMA

98].

F

F

+

The main di(cid:11)erence between E2 and Camellia is the adoption of the 1-round (conservative) SPN

(Substitution-Permutation Network), not the 2-round SPN, i.e. S-P-S. When the 1-round SPN is

used as the round function in a Feistel cipher, the theoretical evaluation of the upper bound of

di(cid:11)erential and linear characteristic probability becomes more complicated, but the speed under

the same level of \real" security is expected to be improved. See Section 6 for detailed discussions

on security.

E.2

-function

P

The design rationale of the

-function is similar to that of the

-function of E2. That is, for

P

P

computational e(cid:14)ciency, it should be represented using only bytewise exclusive-ORs and for secu-

rity against di(cid:11)erential and linear cryptanalysis, its branch number should be optimal [KTM

99].

+

From among the linear transformations that satisfy these conditions, we chose one considering

highly e(cid:14)cient implementation on 32-processors [AU00] and high-end smart cards, as well as 8-bit

processors.

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

32

E.3

s-boxes

As the

-boxes we adopted functions a(cid:14)ne equivalent to the inversion function in GF(2

) for

s

8

enhanced security and small hardware design.

It is well known that the smallest of the maximum di(cid:11)erential probability of functions in GF(2

)

(cid:0)

6

8

8

was proven to be 2

, and the smallest of the maximum linear probability of functions in GF(2

)

(cid:0)

6

8

is conjectured to be 2

. There is a function a(cid:14)ne equivalent to the inversion function in GF(2

)

(cid:0)

6

that achieves the best known of the maximum di(cid:11)erential and linear probabilities, 2

. We choose

this kind of functions as

-boxes. Moreover, the high degree of the Boolean polynomial of every

s

output bit of the

-boxes makes it di(cid:14)cult to attack Camellia by higher order di(cid:11)erential attacks.

s

The two a(cid:14)ne functions that are performed at the input and output of the inversion function in

8

GF(2

) complicates

F Version Information

Camellia has been proposed in the following activities, where the proposed speci(cid:12)cation is exactly

the same as the speci(cid:12)cation described in this document.

Papers

(cid:15) Technical report of IEICE,

K. Aoki, T. Ichikawa, M. Kanda, M. Matsui, S. Moriai, J. Naka jima, and T. Tokita, \Camel-

lia { A 128-bit Block Cipher", Technical Report ISEC2000-6, The Institute of Electronics,

Information and Communication Engineers, 2000. (in Japanese).

(cid:15) International Workshop SAC 2000

K. Aoki, T. Ichikawa, M. Kanda, M. Matsui, S. Moriai, J. Naka jima, and T. Tokita, \Camellia:

A 128-Bit Block Cipher Suitable for Multiple Platforms | Design and Analysis |," In

Selected Areas in Cryptography, 7th Annual International Workshop, SAC 2000, Waterloo,

Ontario, Canada, August 2000, Proceedings, Lecture Notes in Computer Science 2012, pp.39-

56, Springer-Verlag, 2001.

Standardization

(cid:15) ISO 18033

(cid:15) NESSIE

(cid:15) IETF

The followings were submitted as Internet-Drafts.

J. Naka jima and S. Moriai,\A Description of the Camellia Encryption Algorithm"

<draft-nakajima-camellia-02.txt>

{

{

S. Moriai,\Addition of the Camellia Encryption Algorithm to TLS"

<draft-ietf-tls-camellia-01.txt>

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

33

G Ob ject Identi(cid:12)er

The ob ject identi(cid:12)er of Camellia is described in the Internet-Draft,

A Description of the Camellia

Encryption Algorithm

. The following is extracted from the document.

”

“

The Ob ject Identi(cid:12)er for Camellia in Cipher Block Chaining (CBC) mode is as follows:

(cid:15) 128-bit key length, CBC mode

id-camellia128-cbc OBJECT IDENTIFIER ::=

f

iso(1) member-body(2) 392 200011 61 security(1)

algorithm(1) symmetric-encryption-algorithm(1) camellia128-cbc(2)

g

(cid:15) 192-bit ke length, CBC mode

id-camellia192-cbc OBJECT IDENTIFIER ::=

f

iso(1) member-body(2) 392 200011 61 security(1)

algorithm(1) symmetric-encryption-algorithm(1) camellia192-cbc(3)

g

(cid:15) 256-bit key length, CBC mode

id-camellia256-cbc OBJECT IDENTIFIER ::=

f

iso(1) member-body(2) 392 200011 61 security(1)

algorithm(1) symmetric-encryption-algorithm(1) camellia256-cbc(4)

g

H Applications and Products

Camellia can be used for all applications of symmetric block ciphers. In particular, it is suitable

for secure communications and authentication.

Camellia can be implemented e(cid:14)ciently on a wide range of platforms, including software imple-

mentations on 32-bit/64-bit CPUs and low-end/high-end smart cards, and compact and high-speed

hardware implementations on ASICs and FPGAs.

Most of the information about applications of Camellia can be found at

http://www.security.

melco.co.jp/

References

[A00]

K. Aoki. Practical Evaluation of Security against Generalized Interpolation Attack.

IEICE Transactions Fundamentals of Electronics, Communications and Computer Sci-

ences (Japan)

, Vol. E83-A, No. 1, pp. 33{38, 2000. (A preliminary version was presented

at SAC’99).

[AU00]

K. Aoki and H. Ueda. Optimized Software Implementations of E2.

IEICE Transac-

tions Fundamentals of Electronics, Communications and Computer Sciences (Japan)

,

Vol. E83-A, No. 1, pp. 101{105, 2000. (The full paper is available on

http://info.

isl.ntt.co.% linebreak[3]jp/e2/RelDocs/

).

[B94]

E. Biham. New Types of Cryptanalytic Attacks Using Related Keys.

Journal of Cryp-

tology

, Vol. 7, No. 4, pp. 229{246, 1994.

(The extended abstract was appeared at

EUROCRYPT’93).

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

34

[BS93]

E. Biham and A. Shamir.

Di(cid:11)erential Cryptanalysis of the Data Encryption Standard

.

Springer-Verlag, Berlin, Heidelberg, New York, 1993.

[BW99]

A. Biryukov and D. Wagner. Slide Attacks.

In L. Knudsen, editor,

Fast Software

Encryption | 6th International Workshop, FSE’99

Lecture Notes in

, Volume 1636 of

Computer Science

, pp. 245{259, Berlin, Heidelberg, New York, 1999. Springer-Verlag.

[BW00]

A. Biryukov and D. Wagner. Advanced Slide Attacks. In S. Vaudenay, editor,

Advances

in Cryptology | EUROCRYPT2000

Lecture Notes in Computer Sci-

, Volume 1807 of

ence

, pp. 589{606, Berlin, Heidelberg, New York, 2000. Springer-Verlag.

[C98]

Compaq Computer Corporation.

Alpha Architecture Handbook (Version 4)

,

1998.

(You can download the manual

from Compaq’s technical documentation

library:

http://www.support.compaq.com/alpha-tools/documentation/current/

chip-docs.html

).

[F00]

A. Fog.

, 2000. (

How to optimize for the Pentium microprocessors

http://www.agner.

org/assem/

).

[I99]

Intel Corporation.

Intel Architecture Software Developer’s Manual (Volume 2: Instruc-

tion Set Reference)

, 1999. (You can download the manual from Intel’s developer site:

http://developer.intel.com/

).

[JK97]

T. Jakobsen and L. R. Knudsen. The Interpolation Attack on Block Cipher. In E. Bi-

ham, editor,

, Volume

Fast Software Encryption | 4th International Workshop, FSE’97

1267 of

, pp. 28{40, Berlin, Heidelberg, New York,

Lecture Notes in Computer Science

1997. Springer-Verlag.

[K95]

L. R. Knudsen. Truncated and Higher Order Di(cid:11)erentials. In B. Preneel, editor,

Fast

Software Encryption | Second International Workshop

Lecture Notes

, Volume 1008 of

in Computer Science

, pp. 196{211. Springer-Verlag, Berlin, Heidelberg, New York,

1995.

+

[KMA

98] M. Kanda, S. Moriai, K. Aoki, H. Ueda, M. Ohkubo, Y. Takashima, K. Ohta, and

T. Matsumoto. A New 128-bit Block Cipher

. Technical Report ISEC98-12, The In-

E

2

stitute of Electronics, Information and Communication Engineers, 1998. (in Japanese).

[KSW96]

J. Kelsey, B. Schneier, and D. Wagner. Key-Schedule Cryptanalysis of IDEA, G-

DES, GOST, SAFER, and Triple-DES. In N. Koblitz, editor,

Advances in Cryptology

| CRYPTO’96

Lecture Notes in Computer Science

, Volume 1109 of

, pp. 237{251.

Springer-Verlag, Berlin, Heidelberg, New York, 1996.

+

[KTM

99] M. Kanda, Y. Takashima, T. Matsumoto, K. Aoki, and K. Ohta. A Strategy for Con-

structing Fast Round Functions with Practical Security against Di(cid:11)erential and Linear

Cryptanalysis. In S. Tavares and H. Meijer, editors,

Selected Areas in Cryptography |

5th Annual International Workshop, SAC’98

Lecture Notes in Com-

, Volume 1556 of

puter Science

, pp. 264{279, Berlin, Heidelberg, New York, 1999. Springer-Verlag.

Copyright NTT and Mitsubishi Electric Corporation 2000-2001

35

[M94]

M. Matsui. Linear Cryptanalysis Method for DES Cipher.

In T. Helleseth, editor,

Advances in Cryptology | EUROCRYPT’93

Lecture Notes in Com-

, Volume 765 of

puter Science

, pp. 386{397. Springer-Verlag, Berlin, Heidelberg, New York, 1994. (A

preliminary version written in Japanese was presented at SCIS93-3C).

[MT99]

M. Matsui and T. Tokita. Cryptanalysis of a Reduced Version of the Block Cipher E2. In

L. Knudsen, editor,

Fast Software Encryption | 6th International Workshop, FSE’99

,

Volume 1636 of

, pp. 71{80, Berlin, Heidelberg,

Lecture Notes in Computer Science

New York, 1999. Springer-Verlag. (Japanese version was presented at SCIS99.).

+

[RDP

96] V. Rijmen, J. Daemen, B. Preneel, A. Bosselaers, and E. De Win. The Cipher SHARK.

In D. Gollmann, editor,

Fast Software Encryption | Third International Workshop

,

Volume 1039 of

, pp.

99{111. Springer-Verlag,

Lecture Notes in Computer Science

Berlin, Heidelberg, New York, 1996.

[W99]

D. Wagner. The Boomerang Attack. In L. R. Knudsen, editor,

Fast Software Encryption

| 6th International Workshop, FSE’99

Lecture Notes in Computer

, Volume 1636 of

Science

, pp. 156{170, Berlin, Heidelberg, New York, 1999. Springer-Verlag.

Errata

(cid:15) C.2.7 The equation to calculate using only four tables,

1

,

2

,

3

4

, and

, has be

SP

SP

SP

SP

corrected.

(cid:15) Section D,E,F,G, and H have been added.


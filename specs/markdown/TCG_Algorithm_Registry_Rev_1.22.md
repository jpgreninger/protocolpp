TCG Algorithm Registry

Family “2.0"

Level 00 Revision 01.22

February 9, 2015

Published

Contact: admin@trustedcomputinggroup.org

TCG Published

TCG
TCG

Copyright © TCG 2015

Disclaimers, Notices, and License Terms

TCG Algorithm Registry

IS  PROVIDED

IS"  WITH  NO  WARRANTIES
THIS  SPECIFICATION
WHATSOEVER,
INCLUDING  ANY  WARRANTY  OF  MERCHANTABILITY,
NONINFRINGEMENT,  FITNESS  FOR  ANY  PARTICULAR  PURPOSE,  OR  ANY
WARRANTY OTHERWISE ARISING OUT OF ANY PROPOSAL, SPECIFICATION OR
SAMPLE.

"AS

Without limitation, TCG disclaims all liability, including liability for infringement
of any proprietary rights, relating to use of information in this specification and
to  the  implementation  of  this  specification,  and  TCG  disclaims  all  liability  for
cost of procurement of substitute goods or services, lost profits, loss of use, loss
of  data  or  any  incidental,  consequential,  direct,  indirect,  or  special  damages,
whether  under  contract,  tort,  warranty  or  otherwise,  arising  in  any  way  out  of
use or reliance upon this specification or any information herein.

This document is copyrighted by Trusted Computing Group (TCG), and no license,
express or implied, is granted herein other than as follows:  You may not copy or
reproduce the document or distribute it to others without written permission from
TCG, except that you may freely do so for the purposes of (a) examining or
implementing TCG specifications or (b) developing, testing, or promoting information
technology standards and best practices, so long as you distribute the document with
these disclaimers, notices, and license terms.

Contact  the  Trusted  Computing  Group  at  www.trustedcomputinggroup.org  for
information on specification licensing through membership agreements.

Any  marks  and  brands  contained  herein  are  the  property  of  their  respective
owners.

Page ii

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

CONTENTS

1

Introduction .......................................................................................................................... 1

2  Conventions ......................................................................................................................... 2
Bit and Octet Numbering and Order ........................................................................... 2
Sized Buffer References ............................................................................................ 3
Numbers .................................................................................................................... 3

2.1
2.2
2.3

3  Notation ................................................................................................................................ 4
Named Constants ....................................................................................................... 4
Enumerations ............................................................................................................. 4
Bit Field Definitions .................................................................................................... 4
Name Prefix Convention ............................................................................................. 5

3.1
3.2
3.3
3.4

4

TPM_ALG_ID ....................................................................................................................... 5

5.1
5.2

5  ECC Values ........................................................................................................................ 10
Curve ID Values ....................................................................................................... 10
Curve Parameters .................................................................................................... 11
Introduction ..................................................................................................... 11
NIST P192 ...................................................................................................... 11
NIST P224 ...................................................................................................... 12
NIST P256 ...................................................................................................... 13
NIST P384 ...................................................................................................... 14
NIST P521 ...................................................................................................... 15
BN P256 ......................................................................................................... 16
BN P638 ......................................................................................................... 17
SM2_P256 ...................................................................................................... 18

5.2.1
5.2.2
5.2.3
5.2.4
5.2.5
5.2.6
5.2.7
5.2.8
5.2.9

6  Hash Parameters ................................................................................................................ 19
Introduction .............................................................................................................. 19
SHA1 ....................................................................................................................... 19
SHA256 ................................................................................................................... 19
SHA384 ................................................................................................................... 19
SHA512 ................................................................................................................... 20
SM3_256.................................................................................................................. 20
Hash Algorithms Bit Field ......................................................................................... 20

6.1
6.2
6.3
6.4
6.5
6.6
6.7

7  Symmetric Block Cipher Parameters ................................................................................... 21
Introduction .............................................................................................................. 21
AES ......................................................................................................................... 21
SM4 ......................................................................................................................... 21
Camellia ................................................................................................................... 21

7.1
7.2
7.3
7.4

Annex A — Applicability of this Registry for Other TCG Specifications ....................................... 22

Annex B — Bibliography ............................................................................................................ 24

Family “2.0"

Page iii

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

1

Introduction

TCG Algorithm Registry

lists  each  algorithm  assigned  an

The  Algorithm  Registry
to  be
unambiguously  defined  and  referenced  by  other  TCG  specifications.    This  document  is  a
compendium  of  data  related  to  the  various  algorithms  used  in  specifications  created  by  the
Trusted  Computing  Group  (TCG).    The  compendium  of  algorithm  data  is  intended  to  ensure
interoperability between devices built to be compliant with TCG specifications.

identifier,  allowing

it

Many  TCG  specifications  use  a  layered  architecture  where  a  single  “library”  specification  on  a
bottom layer may be used by numerous platform specific middle layers (e.g. PC Client or Mobile
Platform)  to  enable  a  variety  of  top  level  use  cases.    TCG  specifications  support  products  and
solutions  for  numerous  markets  with  varied  requirements  for  commercial  usefulness  including
requirements,
features,  security,
compatibility,  compliance,  intellectual  property  rights,  certification,  etc.    TCG  as  an  organization
does  not  perform  cryptographic  analysis  of  algorithms.    The  presence  of  an  algorithm  in  the
registry  does  not  endorse  its  use  by  TCG  for  any  specific  use  case  or  indicate  an  algorithm’s
acceptability  for  meeting  any  particular  requirement  set.      The  TCG  endeavors  to  provide  a
variety  of  algorithms  of  varying  strength  for  various  commercial  purposes.    Ultimately,  the  TCG
adds algorithms to its registry based on the needs of its membership.

interoperability,  globalization,  performance,

regulatory

Security  is  built  into  an  increasing  number  of  general  purpose Information  and  Communications
Technology  (ICT)  products,  and  security  standards  are  fundamental  to  the  integrity  and
sustainability of the global ICT infrastructure. The Trusted Computing Group (TCG) believes that
open,  interoperable,  and  internationally  vetted  standards  are  critical  for  the  success  of  trusted
computing, and that the multilateral approach to creating such standards is most effective.

TCG recognizes international standards in the field of IT security as the most appropriate method
to ensure  efficacy,  interoperability,  adoption and  user  acceptance. TCG takes into consideration
international  market  requirements  through  international  membership  and  welcomes  participation
from industry,  academia, and  governments in  a  unified,  worldwide Trusted Computing standards
development process.

Commercial  implementation  of  TCG  standards  is  managed  by  individual  product  and  service
providers.    Implementers  or  adopters  of  any  solution  using  TCG  specifications  must  carefully
assess  the  appropriateness  of  any  algorithms  or  TCG  specification  for  satisfying  their  goals.    In
assessing algorithms, TCG recommends implementers and adopters diligently evaluate available
information  such  as  governmental,  industrial,  and  academic  research.    Solutions  involving
cryptography  are  dependent  on  the  solution  architecture  and  on  the  properties  of  cryptographic
algorithms supported.  Over time, cryptographic algorithms can  develop deficiencies for reasons
like advances in cryptographic techniques or increased computing power.  Solutions that support
a  diversity  of  algorithms  can  remain  durable  when  subsets  of  supported  algorithms  wane  in
usefulness.    Therefore,  implementers  intent  on  providing  robust  solutions  are  responsible  for
evaluating both algorithm appropriateness and diversity.

The TCG classifies algorithms listed in this registry according to the following labels:

•  TCG  Standard  -  The  algorithm  is  mandatory  in  one  or  more  TCG  specifications  that
reference  this  registry.    The  TCG  designates  algorithms  with  this  classification  in
accordance with its goals of promoting international standards and interoperability.

•  TCG  Legacy  –  The  algorithm  is  assigned  an  identifier  for  compatibility  or  historical
reasons  and  is  unlikely  to  be  referenced  by  future  TCG  specifications.    The  TCG
designates  an  algorithm with  this  classification  based  on  the  goals  of  the  organization  to
discontinue  support  for  the  algorithm  and  transition  solutions  to  alternative  algorithms.
Stakeholders using solutions relying on algorithms classified as TCG Legacy are strongly

Family “2.0"

Page 1

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

recommended to reevaluate the algorithm’s appropriateness based on the current state of
the art.

•  Assigned  –  The  algorithm  is  assigned  an  identifier,  allowing  it  to  be  unambiguously
defined  and  referenced  by  other  TCG  specifications,  but  is  not  designated  as  TCG
Standard or TCG Legacy.

In  terms  of  algorithm  lifecycle  in  the  registry,  the  TCG  will  initially  assign  algorithms  to  the
Assigned  classification.    Some  algorithms  will  be  reclassified  as  TCG  Standard  if  they  become
mandatory algorithms in TCG specifications.  Eventually, algorithms are  expected to transition to
the TCG Legacy categorization.

2  Conventions

2.1  Bit and Octet Numbering and Order

An  integer  value  is  considered  to  be  an  array  of  one  or  more  octets.  The  octet  at  offset  zero
within the array is the most significant octet (MSO) of the integer. Bit number 0 of that integer is
its least significant bit and is the least significant bit in the last octet in the array.

EXAMPLE

A  32-bit  integer  is  an  array  of  four  octets;  the  MSO  is  at  offset  [0],  and  the  most  significant  bit  is  bit
number 31. Bit zero of this 32-bit integer is the least significant bit in the octet at offset [3] in the array.

NOTE

Array indexing is zero-based.

Page 2

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

The first listed member of a structure is at the lowest offset within the structure and the last listed
member is at the highest offset within the structure.

For a character string (letters delimited by “”), the first character of the string contains the MSO.

2.2  Sized Buffer References

The  specification  makes  extensive  use  of  a  data  structure  called  a  sized  buffer.  A  sized  buffer
has a size field followed by an array of octets equal in number to the value in the size field.

The  structure  will  have  an  identifying  name.  When  the  specification  references  the  size  field  of
the  structure,  the  structure  name  is  followed  by  “.size”  (a  period  followed  by  the  word  “size”).
When the specification references the octet array of the structure, the structure name is followed
by “.buffer” (a period followed by the word “buffer”).

2.3  Numbers

Numbers are decimal unless a different radix is indicated.

Unless  the  number  appears  in  a  table  intended  to  be  machine  readable,  the  radix  is  a  subscript
following the digits of the number. Only radix values of 2 and 16 are used in this specification.

Radix  16  (hexadecimal)  numbers  have  a  space  separator  between  groups  of  two  hexadecimal
digits.

EXAMPLE 1

40 FF 12 3416

Radix 2 (binary) numbers use a space separator between groups of four binary digits.

EXAMPLE 2

0100 1110 00012

For  numbers  using  a  binary  radix,  the  number  of  digits  indicates  the  number  of  bits  in  the
representation.

EXAMPLE 3

2016 is a hexadecimal number that contains exactly 8 bits and has a decimal value of 32.

EXAMPLE 4

10 00002 is a binary number that contains exactly 6 bits and has a decimal value of 32.

EXAMPLE 5

0 2016 is a hexadecimal number that contains exactly 12 bits and has a decimal value of 32.

A  number  in  a  machine-readable  table  may  use  the  “0x”  prefix  to  denote  a  base  16  number.  In
this  format,  the  number  of  digits  is  not  always  indicative  of  the  number  of  bits  in  the
representation.

EXAMPLE 6

0x20 is a hexadecimal number with a value of 32, and the number of bits is determined by the context.

Family “2.0"

Page 3

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

3  Notation

The  notations  in this clause describe the representation  of  various  data so  that  it  is  both  human
readable and amenable to automated processing.

3.1  Named Constants

A  named  constant  is  a  numeric  value  to  which  a  name  has  been  assigned.  In  the  C  language,
this  is  done  with  a  #define  statement.  In  this  specification,  a  named  constant  is  defined  in  a
table that has a title that starts with “Definition” and ends with “Constants.”

The table title will indicate the name of the class of constants that are being defined in the table.
The title will include the data type of the constants in parentheses.

The table in Example 1 names a collection of 16-bit constants.

EXAMPLE 1

Table xx — Definition of (UINT16) COUNTING Constants

Parameter

Value

Description

first

1

decimal value is implicitly the size of the

second

0x0002

hex value will match the number of bits in the constant

third

fourth

3

0x0004

3.2  Enumerations

A  table  that  defines  an  enumerated  data  type  will  start  with  the  word  “Definition”  and  end  with
“Values.”

A  value  in  parenthesis  will  denote  the  intrinsic  data  size  of  the  value  and  may  have  the  values
"INT8", "UINT8", "INT16", “UINT16”, "INT32", and “UINT32.” If this value is not present, “UINT16”
is assumed.

The table in Example 1 shows how an enumeration would be defined in this specification.

EXAMPLE 1

Table xx — Definition of (UINT16) CARD_SUIT Values

Suit Names

Value

Description

CLUBS

0x0000

DIAMONDS

0x000D

HEARTS

SPADES

0x001A

0x0027

3.3  Bit Field Definitions

Page 4

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

A  table  that  defines  a  structure  containing  bit  fields  has  a  title  that  starts  with  “Definition”  and
ends  with  “Bits.”  A  type  identifier  in  parentheses  in  the  title  indicates  the  size  of  the  datum  that
contains the bit fields.

When the bit fields do not occupy consecutive locations, a spacer field is defined with a name of
“Reserved.” Bits in these spaces are reserved and shall be zero.

The  table  in  Example  1  shows  how  a  structure  containing  bit  fields  would  be  defined  in  this
specification.

When  a  field  has  more  than  one  bit,  the  range  is  indicated  by  a  pair  of  numbers  separated  by  a
colon (“:”). The numbers will be in high:low order.

EXAMPLE1

 Table xx — Definition of (UINT32) SOME_ATTRIBUTE Bits

Bit  Name

Action

0

1

zeroth_bit

first_bit

SET (1): what to do if bit is 1
CLEAR (0): what to do if bit is 0

SET (1): what to do if bit is 1
CLEAR (0): what to do if bit is 0

6:2

Reserved

A placeholder that spans 5 bits

7

third_bit

SET (1): what to do if bit is 1
CLEAR (0): what to do if bit is 0

31:8  Reserved

Placeholder to fill 32 bits

3.4  Name Prefix Convention

Parameters  are  constants,  variables,  structures,  unions,  and  structure  members.  Structure
members  are  given  a  name  that  is  indicative  of  its  use,  with  no  special  prefix.  The  other
parameter types are named according to their type with their name starting with “TPMx_”, where
“x” is an optional character to indicate the data type.

In  some  cases,  additional  qualifying  characters  will  follow  the  underscore.  These  are  generally
used when dealing with an enumerated data type.

Prefix

TPM_

TPM_ALG_

TPM_xx_

Table 1 — Name Prefix Convention

Description

a constant or an enumerated type

an enumerated type that indicates an algorithm
A TPM_ALG_ is often used as a selector for a union.

an enumeration value of a particular type
The  value  of  “xx”  will  be  indicative  of  the  use  of  the  enumerated  type.  A  table  of  “TPM_xx”
constant definitions will exist to define each of the TPM_xx_ values.
EXAMPLE 1

TPM_RC_ indicates that the type is used for a responseCode.

4  TPM_ALG_ID

Family “2.0"

Page 5

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

Table 3 is the list of algorithms to which the TCG has assigned an algorithm identifier along with
its numeric identifier.

An algorithm ID is often used like a tag to determine the type of a structure in a context-sensitive
way. The values for TPM_ALG_ID shall be in the range of 00 0016 – 7F FF16. Other structure tags
will be in the range 80 0016 – FF FF16.

An algorithm shall not be assigned a value in the range 00 C116 – 00 C616 in order to prevent any
overlap with the command structure tags used in TPM 1.2.

The implementation of some algorithms is dependent on the presence of other algorithms. When
there  is  a  dependency,  the  algorithm  that  is  required  is  listed  in  column  labeled  "Dep"
(Dependent) in Table 3.

EXAMPLE

Implementation of TPM_ALG_RSASSA requires that the RSA algorithm be implemented.

TPM_ALG_KEYEDHASH and TPM_ALG_NULL are required of all TPM implementations.

Table 2 — Legend for TPM_ALG_ID Table

Column Title

Comments

Algorithm Name

the mnemonic name assigned to the algorithm

Value

Type

the numeric value assigned to the algorithm

The allowed values are:

A – asymmetric algorithm with a public and private key
S – symmetric algorithm with only a private key
H – hash algorithm that compresses input data to a digest value or indicates a

method that uses a hash

X – signing algorithm
N – an anonymous signing algorithm
E – an encryption mode
M – a method such as a mask generation function
O – an object type

(Classification) The allowed values are:

A – Assigned
S – TCG Standard
L – TCG Legacy

(Dependent)  Indicates  which  other  algorithm  is  required  to  be  implemented  if  this
algorithm is implemented

the reference document that defines the algorithm

clarifying information

C

Dep

Reference

Comments

Page 6

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

Table 3 — Definition of (UINT16) TPM_ALG_ID Constants

Algorithm Name

Value

Type  Dep  C

Reference

Comments

TPM_ALG_ERROR

0x0000

should not occur

TPM_ALG_RSA

TPM_ALG_SHA

TPM_ALG_SHA1

0x0001  A O

0x0004  H

0x0004  H

S

S

S

IETF RFC 3447

the RSA algorithm

ISO/IEC 10118-3

the SHA1 algorithm

ISO/IEC 10118-3

TPM_ALG_HMAC

0x0005  H X

S

ISO/IEC 9797-2

TPM_ALG_AES

0x0006  S

S

ISO/IEC 18033-3

redefinition for documentation
consistency

Hash Message
Authentication Code (HMAC)
algorithm

the AES algorithm with
various key sizes

hash-based mask-generation
function

an object type that may use
XOR for encryption or an
HMAC for signing and may
also refer to a data object that
is neither signing nor
encrypting

the XOR encryption algorithm

IEEE Std 1363TM-
2000
IEEE Std 1363a™-
2004

TCG TPM 2.0 library
specification

TCG TPM 2.0 library
specification

ISO/IEC 10118-3

the SHA 256 algorithm

ISO/IEC 10118-3

the SHA 384 algorithm

ISO/IEC 10118-3

the SHA 512 algorithm

TCG TPM 2.0 library
specification

Null algorithm

GM/T 0004-2012

SM3 hash algorithm

GM/T 0002-2012

SM4 symmetric block cipher

TPM_ALG_MGF1

0x0007  H M

S

TPM_ALG_KEYEDHASH

0x0008  H O

S

TPM_ALG_XOR

0x000A  H S

TPM_ALG_SHA256

TPM_ALG_SHA384

TPM_ALG_SHA512

0x000B  H

0x000C  H

0x000D  H

TPM_ALG_NULL

0x0010

TPM_ALG_SM3_256

0x0012  H

TPM_ALG_SM4

0x0013  S

S

S

A

A

S

A

A

TPM_ALG_RSASSA

0x0014  A X

RSA  S

IETF RFC 3447

TPM_ALG_RSAES

0x0015  A E

RSA  S

IETF RFC 3447

TPM_ALG_RSAPSS

0x0016  A X

RSA  S

IETF RFC 3447

TPM_ALG_OAEP

0x0017  A E H  RSA  S

IETF RFC 3447

TPM_ALG_ECDSA

0x0018  A X

ECC  S

ISO/IEC 14888-3

a signature algorithm defined
in section 8.2 (RSASSA-
PKCS1-v1_5)

a padding algorithm defined
in section 7.2 (RSAES-
PKCS1-v1_5)

a signature algorithm defined
in section 8.1 (RSASSA-PSS)

a padding algorithm defined
in section 7.1
(RSAES_OAEP)

signature algorithm using
elliptic curve cryptography
(ECC)

Family “2.0"

Page 7

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

Algorithm Name

Value

Type  Dep  C

Reference

Comments

TPM_ALG_ECDH

0x0019  A M  ECC  S

NIST SP800-56A

secret sharing using ECC

TCG Algorithm Registry

Based on context, this can be
either One-Pass Diffie-
Hellman, C(1, 1, ECC CDH)
defined in 6.2.2.2 or Full
Unified Model C(2, 2, ECC
CDH) defined in 6.1.1.2

TPM_ALG_ECDAA

0x001A  A X N  ECC  S

TCG TPM 2.0 library
specification

elliptic-curve based,
anonymous signing scheme

TPM_ALG_SM2

0x001B  A X   ECC  A

GM/T 0003.1–2012
GM/T 0003.2–2012
GM/T 0003.3–2012
GM/T 0003.5–2012

SM2 – depending on context,
either an elliptic-curve based,
signature algorithm or a key
exchange protocol
NOTE 1
Type listed as
signing but, other uses are
allowed according to context.

TPM_ALG_ECSCHNORR

0x001C  A X

ECC  S

TCG TPM 2.0 library
specification

elliptic-curve based Schnorr
signature

TPM_ALG_ECMQV

0x001D  A M  ECC  A

NIST SP800-56A

TPM_ALG_KDF1_SP800_56A  0x0020  H M  ECC  S

NIST SP800-56A

TPM_ALG_KDF2

0x0021  H M

A

IEEE Std 1363a-2004

TPM_ALG_KDF1_SP800_108  0x0022  H M

S

NIST SP800-108

two-phase elliptic-curve key
exchange – C(2, 2, ECC
MQV) section 6.1.1.4

concatenation key derivation
function (approved alternative
1) section 5.8.1

key derivation function KDF2
section 13.2

a key derivation method
Section 5.1 KDF in Counter
Mode

TPM_ALG_ECC

0x0023  A O

S

ISO/IEC 15946-1

prime field ECC

TPM_ALG_SYMCIPHER

0x0025  O S

S

TCG TPM 2.0 library
specification

the object type for a
symmetric block cipher

TPM_ALG_CAMELLIA

0x0026   S

A

ISO/IEC 18033-3

TPM_ALG_CTR

0x0040  S E

A

ISO/IEC 10116

TPM_ALG_OFB

0x0041  S E

A

ISO/IEC 10116

Camellia is symmetric block
cipher. The Camellia
algorithm with various key
sizes

Counter mode – if
implemented, all symmetric
block ciphers (S type)
implemented shall be capable
of using this mode.

Output Feedback mode – if
implemented, all symmetric
block ciphers (S type)
implemented shall be capable
of using this mode.

Page 8

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

Algorithm Name

Value

Type  Dep  C

Reference

Comments

TPM_ALG_CBC

0x0042  S E

A

ISO/IEC 10116

TPM_ALG_CFB

0x0043  S E

A

ISO/IEC 10116

TPM_ALG_ECB

0x0044  S E

A

ISO/IEC 10116

reserved

reserved

0x00C1
through
0x00C6

0x8000
through
0xFFFF

Cipher Block Chaining mode
– if implemented, all
symmetric block ciphers (S
type) implemented shall be
capable of using this mode.

Cipher Feedback mode – if
implemented, all symmetric
block ciphers (S type)
implemented shall be capable
of using this mode.

Electronic Codebook mode –
if implemented, all symmetric
block ciphers (S type)
implemented shall be capable
of using this mode.
NOTE 2  This mode is not
recommended for uses unless
the key is frequently rotated such
as in video codecs

0x00C1 – 0x00C6 are
reserved to prevent any
overlap with the command
structure tags used in TPM
1.2

reserved for other structure
tags

Family “2.0"

Page 9

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

5  ECC Values

5.1  Curve ID Values

Table 4 is the list of identifiers for TCG-registered curve ID values for elliptic curve cryptography.

Table 4 — Definition of (UINT16) TPM_ECC_CURVE Constants

Name

Value

Classification  Comments

TPM_ECC_NONE

0x0000

Assigned

TPM_ECC_NIST_P192

0x0001

Assigned

TPM_ECC_NIST_P224

0x0002

Assigned

TPM_ECC_NIST_P256

0x0003

TCG Standard

TPM_ECC_NIST_P384

0x0004

Assigned

TPM_ECC_NIST_P521

0x0005

Assigned

TPM_ECC_BN_P256

0x0010

TCG Standard

curve to support ECDAA

TPM_ECC_BN_P638

0x0011

Assigned

curve to support ECDAA

TPM_ECC_SM2_P256

0x0020

Assigned

#TPM_RC_CURVE

NOTE    This  row  has  meaning  for  other  TCG  specifications
that use automated processing and should be ignored for the
TCG Algorithm Registry.

Page 10

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

5.2  Curve Parameters

5.2.1

Introduction

The  tables  in  this  section  contain  the  curve  parameter  data  associated  with  the  curves  listed  in
Table 4.

5.2.2  NIST P192

Table 5 — Defines for NIST_P192 ECC Values

Parameter  Value

curveID

TPM_ECC_NIST_P192

keySize

192

kdf

{TPM_ALG_KDF1_SP800_56A, TPM_ALG_SHA256}

sign

{TPM_ALG_NULL, TPM_ALG_NULL}

p

a

b

gX

gY

n

h

{24, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF ,0xFF, 0xFF}}

{24, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFC}}

{24, {0x64, 0x21, 0x05, 0x19, 0xE5, 0x9C, 0x80, 0xE7, 0x0F,
0xA7, 0xE9, 0xAB, 0x72, 0x24, 0x30, 0x49, 0xFE, 0xB8, 0xDE,
0xEC, 0xC1, 0x46, 0xB9, 0xB1}}

{24, {0x18, 0x8D, 0xA8, 0x0E, 0xB0, 0x30, 0x90, 0xF6, 0x7C,
0xBF, 0x20, 0xEB, 0x43, 0xA1, 0x88, 0x00, 0xF4, 0xFF, 0x0A,
0xFD, 0x82, 0xFF, 0x10, 0x12}}

{24, {0x07, 0x19, 0x2B, 0x95, 0xFFC, 0x8D, 0xA7, 0x86, 0x31,
0x01, 0x1ED, 0x6B, 0x24, 0xCD, 0xD5, 0x73, 0xF9, 0x77, 0xA1,
0x1E, 0x79, 0x48, 0x11}}

{24, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0x99, 0xDE, 0xF8, 0x36, 0x14, 0x6B, 0xC9,
0xB1, 0xB4, 0xD2, 0x28, 0x31}}

{1,{1}}

Description

identifier for the
curve

size in bits of the
key

the default KDF
and hash

no mandatory
signing scheme

Fp (the modulus)

coefficient of the
linear term in the
curve equation

constant term for
curve equation

x coordinate of
base point G

y coordinate of
base point G

order of G

cofactor (a size of
zero indicates a
cofactor of 1)

Family “2.0"

Page 11

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

5.2.3  NIST P224

Table 6 — Defines for NIST_P224 ECC Values

Parameter  Value

curveID

TPM_ECC_NIST_P224

keySize

224

kdf

{TPM_ALG_KDF1_SP800_56A, TPM_ALG_SHA256}

sign

{TPM_ALG_NULL, TPM_ALG_NULL}

p

a

b

gX

gY

n

h

{28, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01  }}

{28, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE  }}

{28, {0xB4, 0x05, 0x0A, 0x85, 0x0C, 0x04, 0xB3, 0xAB, 0xF5,
0x41, 0x32, 0x56, 0x50, 0x44, 0xB0, 0xB7, 0xD7, 0xBF, 0xD8,
0xBA, 0x27, 0x0B, 0x39, 0x43, 0x23, 0x55, 0xFF, 0xB4  }}

{28, {0xB7, 0x0E, 0x0C, 0xBD, 0x6B, 0xB4, 0xBF, 0x7F, 0x32,
0x13, 0x90, 0xB9, 0x4A, 0x03, 0xC1, 0xD3, 0x56, 0xC2, 0x11,
0x22, 0x34, 0x32, 0x80, 0xD6, 0x11, 0x5C, 0x1D, 0x21  }}

{28, {0xBD, 0x37, 0x63, 0x88, 0xB5, 0xF7, 0x23, 0xFB, 0x4C,
0x22, 0xDF, 0xE6, 0xCD, 0x43, 0x75, 0xA0, 0x5A, 0x07, 0x47,
0x64, 0x44, 0xD5, 0x81, 0x99, 0x85, 0x00, 0x7E, 0x34  }}

{28, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0xA2, 0xE0, 0xB8, 0xF0,
0x3E, 0x13, 0xDD, 0x29, 0x45, 0x5C, 0x5C, 0x2A, 0x3D  }}

{1,{1}}

Description

identifier for the
curve

Size in bits of the
key

the default KDF
and hash

no mandatory
signing scheme

Fp (the modulus)

coefficient of the
linear term in the
curve equation

constant term for
curve equation

x coordinate of
base point G

y coordinate of
base point G

order of G

cofactor

Page 12

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

5.2.4  NIST P256

Table 7 — Defines for NIST_P256 ECC Values

Parameter  Value

curveID

TPM_ECC_NIST_P256

keySize

256

kdf

{TPM_ALG_KDF1_SP800_56A, TPM_ALG_SHA256}

sign

{TPM_ALG_NULL, TPM_ALG_NULL}

p

a

b

gX

gY

n

h

{32, {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF  }}

{32, {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFC  }}

{32, {0x5A, 0xC6, 0x35, 0xD8, 0xAA, 0x3A, 0x93, 0xE7, 0xB3,
0xEB, 0xBD, 0x55, 0x76, 0x98, 0x86, 0xBC, 0x65, 0x1D, 0x06,
0xB0, 0xCC, 0x53, 0xB0, 0xF6, 0x3B, 0xCE, 0x3C, 0x3E, 0x27,
0xD2, 0x60, 0x4B  }}

{32, {0x6B, 0x17, 0xD1, 0xF2, 0xE1, 0x2C, 0x42, 0x47, 0xF8,
0xBC, 0xE6, 0xE5, 0x63, 0xA4, 0x40, 0xF2, 0x77, 0x03, 0x7D,
0x81, 0x2D, 0xEB, 0x33, 0xA0, 0xF4, 0xA1, 0x39, 0x45, 0xD8,
0x98, 0xC2, 0x96  }}

{32, {0x4F, 0xE3, 0x42, 0xE2, 0xFE, 0x1A, 0x7F, 0x9B, 0x8E,
0xE7, 0xEB, 0x4A, 0x7C, 0x0F, 0x9E, 0x16, 0x2B, 0xCE, 0x33,
0x57, 0x6B, 0x31, 0x5E, 0xCE, 0xCB, 0xB6, 0x40, 0x68, 0x37,
0xBF, 0x51, 0xF5  }}

{32, {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBC, 0xE6, 0xFA,
0xAD, 0xA7, 0x17, 0x9E, 0x84, 0xF3, 0xB9, 0xCA, 0xC2, 0xFC,
0x63, 0x25, 0x51  }}

{1,{1}}

Description

identifier for the
curve

Size in bits of the
key

the default KDF
and hash

no mandatory
signing scheme

Fp (the modulus)

coefficient of the
linear term in the
curve equation

constant term for
curve equation

x coordinate of
base point G

y coordinate of
base point G

order of G

cofactor

Family “2.0"

Page 13

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

5.2.5  NIST P384

Table 8 — Defines for NIST_P384 ECC Values

Parameter  Value

curveID

TPM_ECC_NIST_P384

keySize

384

kdf

{TPM_ALG_KDF1_SP800_56A, TPM_ALG_SHA384}

sign

{TPM_ALG_NULL, TPM_ALG_NULL}

p

a

b

gX

gY

n

h

{48, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF  }}

{48, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFC  }}

{48, {0xB3, 0x31, 0x2F, 0xA7, 0xE2, 0x3E, 0xE7, 0xE4, 0x98,
0x8E, 0x05, 0x6B, 0xE3, 0xF8, 0x2D, 0x19, 0x18, 0x1D, 0x9C,
0x6E, 0xFE, 0x81, 0x41, 0x12, 0x03, 0x14, 0x08, 0x8F, 0x50,
0x13, 0x87, 0x5A, 0xC6, 0x56, 0x39, 0x8D, 0x8A, 0x2E, 0xD1,
0x9D, 0x2A, 0x85, 0xC8, 0xED, 0xD3, 0xEC, 0x2A, 0xEF  }}

{48, {0xAA, 0x87, 0xCA, 0x22, 0xBE, 0x8B, 0x05, 0x37, 0x8E,
0xB1, 0xC7, 0x1E, 0xF3, 0x20, 0xAD, 0x74, 0x6E, 0x1D, 0x3B,
0x62, 0x8B, 0xA7, 0x9B, 0x98, 0x59, 0xF7, 0x41, 0xE0, 0x82,
0x54, 0x2A, 0x38, 0x55, 0x02, 0xF2, 0x5D, 0xBF, 0x55, 0x29,
0x6C, 0x3A, 0x54, 0x5E, 0x38, 0x72, 0x76, 0x0A, 0xB7  }}

{48, {0x36, 0x17, 0xDE, 0x4A, 0x96, 0x26, 0x2C, 0x6F, 0x5D,
0x9E, 0x98, 0xBF, 0x92, 0x92, 0xDC, 0x29, 0xF8, 0xF4, 0x1D,
0xBD, 0x28, 0x9A, 0x14, 0x7C, 0xE9, 0xDA, 0x31, 0x13, 0xB5,
0xF0, 0xB8, 0xC0, 0x0A, 0x60, 0xB1, 0xCE, 0x1D, 0x7E, 0x81,
0x9D, 0x7A, 0x43, 0x1D, 0x7C, 0x90, 0xEA, 0x0E, 0x5F  }}

{48, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0x63, 0x4D, 0x81, 0xF4,
0x37, 0x2D, 0xDF, 0x58, 0x1A, 0x0D, 0xB2, 0x48, 0xB0, 0xA7,
0x7A, 0xEC, 0xEC, 0x19, 0x6A, 0xCC, 0xC5, 0x29, 0x73  }}

{1,{1}}

Description

identifier for the
curve

size in bits of the
key

the default KDF
and hash

no mandatory
signing scheme

Fp (the modulus)

coefficient of the
linear term in the
curve equation

constant term for
curve equation

x coordinate of
base point G

y coordinate of
base point G

order of G

cofactor

Page 14

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

5.2.6  NIST P521

Table 9 — Defines for NIST_P521 ECC Values

Parameter  Value

curveID

TPM_ECC_NIST_P521

keySize

521

kdf

{TPM_ALG_KDF1_SP800_56A, TPM_ALG_SHA512}

sign

{TPM_ALG_NULL, TPM_ALG_NULL}

p

a

b

gX

gY

n

h

{66, {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  }}

{66, {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC  }}

{66, {0x00, 0x51, 0x95, 0x3E, 0xB9, 0x61, 0x8E, 0x1C, 0x9A,
0x1F, 0x92, 0x9A, 0x21, 0xA0, 0xB6, 0x85, 0x40, 0xEE, 0xA2,
0xDA, 0x72, 0x5B, 0x99, 0xB3, 0x15, 0xF3, 0xB8, 0xB4, 0x89,
0x91, 0x8E, 0xF1, 0x09, 0xE1, 0x56, 0x19, 0x39, 0x51, 0xEC,
0x7E, 0x93, 0x7B, 0x16, 0x52, 0xC0, 0xBD, 0x3B, 0xB1, 0xBF,
0x07, 0x35, 0x73, 0xDF, 0x88, 0x3D, 0x2C, 0x34, 0xF1, 0xEF,
0x45, 0x1F, 0xD4, 0x6B, 0x50, 0x3F, 0x00  }}

{66, {0x00, 0xC6, 0x85, 0x8E, 0x06, 0xB7, 0x04, 0x04, 0xE9,
0xCD, 0x9E, 0x3E, 0xCB, 0x66, 0x23, 0x95, 0xB4, 0x42, 0x9C,
0x64, 0x81, 0x39, 0x05, 0x3F, 0xB5, 0x21, 0xF8, 0x28, 0xAF,
0x60, 0x6B, 0x4D, 0x3D, 0xBA, 0xA1, 0x4B, 0x5E, 0x77, 0xEF,
0xE7, 0x59, 0x28, 0xFE, 0x1D, 0xC1, 0x27, 0xA2, 0xFF, 0xA8,
0xDE, 0x33, 0x48, 0xB3, 0xC1, 0x85, 0x6A, 0x42, 0x9B, 0xF9,
0x7E, 0x7E, 0x31, 0xC2, 0xE5, 0xBD, 0x66  }}

{66, {0x01, 0x18, 0x39, 0x29, 0x6A, 0x78, 0x9A, 0x3B, 0xC0,
0x04, 0x5C, 0x8A, 0x5F, 0xB4, 0x2C, 0x7D, 0x1B, 0xD9, 0x98,
0xF5, 0x44, 0x49, 0x57, 0x9B, 0x44, 0x68, 0x17, 0xAF, 0xBD,
0x17, 0x27, 0x3E, 0x66, 0x2C, 0x97, 0xEE, 0x72, 0x99, 0x5E,
0xF4, 0x26, 0x40, 0xC5, 0x50, 0xB9, 0x01, 0x3F, 0xAD, 0x07,
0x61, 0x35, 0x3C, 0x70, 0x86, 0xA2, 0x72, 0xC2, 0x40, 0x88,
0xBE, 0x94, 0x76, 0x9F, 0xD1, 0x66, 0x50  }}

{66, {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0x51, 0x86, 0x87, 0x83, 0xBF,
0x2F, 0x96, 0x6B, 0x7F, 0xCC, 0x01, 0x48, 0xF7, 0x09, 0xA5,
0xD0, 0x3B, 0xB5, 0xC9, 0xB8, 0x89, 0x9C, 0x47, 0xAE, 0xBB,
0x6F, 0xB7, 0x1E, 0x91, 0x38, 0x64, 0x09  }}

{1,{1}}

Description

identifier for the
curve

size in bits of the
key

the default KDF
and hash

no mandatory
signing scheme

Fp (the modulus)

coefficient of the
linear term in the
curve equation

constant term for
curve equation

x coordinate of
base point G

y coordinate of
base point G

order of G

cofactor

Family “2.0"

Page 15

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

5.2.7  BN P256

Table 10 — Defines for BN_P256 ECC Values

Parameter  Value

curveID

TPM_ECC_BN_P256

keySize

256

kdf

{TPM_ALG_NULL, TPM_ALG_NULL}

sign

{TPM_ALG_NULL, TPM_ALG_NULL}

p

a

b

gX

gY

n

h

{32, {0xFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFC, 0XF0, 0XCD, 0X46,
0XE5, 0XF2, 0X5E, 0XEE, 0X71, 0XA4, 0X9F, 0X0C, 0XDC, 0X65,
0XFB, 0X12, 0X98, 0X0A, 0X82, 0XD3, 0X29, 0X2D, 0XDB, 0XAE,
0XD3, 0X30, 0X13  }}

{1,{0}}

{1,{3}}

{1,{1}}

{1,{2}};

{32, {0xFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFC, 0XF0, 0XCD, 0X46,
0XE5, 0XF2, 0X5E, 0XEE, 0X71, 0XA4, 0X9E, 0X0C, 0XDC, 0X65,
0XFB, 0X12, 0X99, 0X92, 0X1A, 0XF6, 0X2D, 0X53, 0X6C, 0XD1,
0X0B, 0X50, 0X0D  }}

{1,{1}}

Description

identifier for the
curve

size in bits of the
key

the default KDF
and hash

no mandatory
signing scheme

Fp (the modulus)

coefficient of the
linear term in the
curve equation

constant term for
curve equation

x coordinate of
base point G

y coordinate of
base point G

order of G

cofactor

Page 16

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

5.2.8  BN P638

Table 11 — Defines for BN_P638 ECC Values

Parameter  Value

curveID

TPM_ECC_BN_P638

keySize

638

kdf

{TPM_ALG_NULL, TPM_ALG_NULL}

sign

{TPM_ALG_NULL, TPM_ALG_NULL}

p

a

b

gX

gY

n

{80, {0x23, 0xFF, 0xFF, 0xFD, 0xC0, 0x00, 0x00, 0x0D, 0x7F,
0xFF, 0xFF, 0xB8, 0x00, 0x00, 0x01, 0xD3, 0xFF, 0xFF, 0xF9,
0x42, 0xD0, 0x00, 0x16, 0x5E, 0x3F, 0xFF, 0x94, 0x87, 0x00,
0x00, 0xD5, 0x2F, 0xFF, 0xFD, 0xD0, 0xE0, 0x00, 0x08, 0xDE,
0x55, 0xC0, 0x00, 0x86, 0x52, 0x00, 0x21, 0xE5, 0x5B, 0xFF,
0xFF, 0xF5, 0x1F, 0xFF, 0xF4, 0xEB, 0x80, 0x00, 0x00, 0x00,
0x4C, 0x80, 0x01, 0x5A, 0xCD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xEC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x67  }}

{1,{0}}

{2,{0x01, 0x01}}

{80, {0x23, 0xFF, 0xFF, 0xFD, 0xC0, 0x00, 0x00, 0x0D, 0x7F,
0xFF, 0xFF, 0xB8, 0x00, 0x00, 0x01, 0xD3, 0xFF, 0xFF, 0xF9,
0x42, 0xD0, 0x00, 0x16, 0x5E, 0x3F, 0xFF, 0x94, 0x87, 0x00,
0x00, 0xD5, 0x2F, 0xFF, 0xFD, 0xD0, 0xE0, 0x00, 0x08, 0xDE,
0x55, 0xC0, 0x00, 0x86, 0x52, 0x00, 0x21, 0xE5, 0x5B, 0xFF,
0xFF, 0xF5, 0x1F, 0xFF, 0xF4, 0xEB, 0x80, 0x00, 0x00, 0x00,
0x4C, 0x80, 0x01, 0x5A, 0xCD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xEC, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x66  }}

{1,{0x10}}

{80, {0x23, 0xFF, 0xFF, 0xFD, 0xC0, 0x00, 0x00, 0x0D, 0x7F,
0xFF, 0xFF, 0xB8, 0x00, 0x00, 0x01, 0xD3, 0xFF, 0xFF, 0xF9,
0x42, 0xD0, 0x00, 0x16, 0x5E, 0x3F, 0xFF, 0x94, 0x87, 0x00,
0x00, 0xD5, 0x2F, 0xFF, 0xFD, 0xD0, 0xE0, 0x00, 0x08, 0xDE,
0x55, 0x60, 0x00, 0x86, 0x55, 0x00, 0x21, 0xE5, 0x55, 0xFF,
0xFF, 0xF5, 0x4F, 0xFF, 0xF4, 0xEA, 0xC0, 0x00, 0x00, 0x00,
0x49, 0x80, 0x01, 0x54, 0xD9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xED, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x61  }}

Description

identifier for the
curve

size in bits of the
key

the default KDF
and hash

no mandatory
signing scheme

Fp (the modulus)

coefficient of the
linear term in the
curve equation

constant term for
curve equation

x coordinate of
base point G

y coordinate of
base point G

order of G

h

{1,{1}}

cofactor

Family “2.0"

Page 17

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

5.2.9  SM2_P256

Table 12 — Defines for SM2_P256 ECC Values

Parameter  Value

curveID

TPM_ECC_SM2_P256

keySize

256

kdf

{TPM_ALG_KDF1_SP800_56A, TPM_ALG_SM3_256}

sign

{TPM_ALG_NULL, TPM_ALG_NULL}

p

a

b

gX

gY

n

h

{32, {0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF  }}

{32, {0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFC  }}

{32, {0x28, 0xE9, 0xFA, 0x9E, 0x9D, 0x9F, 0x5E, 0x34, 0x4D,
0x5A, 0x9E, 0x4B, 0xCF, 0x65, 0x09, 0xA7, 0xF3, 0x97, 0x89,
0xF5, 0x15, 0xAB, 0x8F, 0x92, 0xDD, 0xBC, 0xBD, 0x41, 0x4D,
0x94, 0x0E, 0x93  }}

{32, {0x32, 0xC4, 0xAE, 0x2C, 0x1F, 0x19, 0x81, 0x19, 0x5F,
0x99, 0x04, 0x46, 0x6A, 0x39, 0xC9, 0x94, 0x8F, 0xE3, 0x0B,
0xBF, 0xF2, 0x66, 0x0B, 0xE1, 0x71, 0x5A, 0x45, 0x89, 0x33,
0x4C, 0x74, 0xC7  }}

{32, {0xBC, 0x37, 0x36, 0xA2, 0xF4, 0xF6, 0x77, 0x9C, 0x59,
0xBD, 0xCE, 0xE3, 0x6B, 0x69, 0x21, 0x53, 0xD0, 0xA9, 0x87,
0x7C, 0xC6, 0x2A, 0x47, 0x40, 0x02, 0xDF, 0x32, 0xE5, 0x21,
0x39, 0xF0, 0xA0  }}

{32, {0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x72, 0x03, 0xDF,
0x6B, 0x21, 0xC6, 0x05, 0x2B, 0x53, 0xBB, 0xF4, 0x09, 0x39,
0xD5, 0x41, 0x23  }}

{1,{1}}

Description

identifier for the
curve

size in bits of the
key

the default KDF
and hash

no mandatory
signing scheme

Fp (the modulus)

coefficient of the
linear term in the
curve equation

constant term for
curve equation

x coordinate of
base point G

y coordinate of
base point G

order of G

cofactor

Page 18

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

6  Hash Parameters

6.1

Introduction

The  tables  in  this  clause  define  the  basic  parameters  associated  with  the  TCG-registered  hash
algorithms listed in Table 3.

6.2  SHA1

Name

Value

Table 13 — Defines for SHA1 Hash Values

SHA1_DIGEST_SIZE

SHA1_BLOCK_SIZE

SHA1_DER_SIZE

SHA1_DER

6.3  SHA256

20

64

15

0x30, 0x21, 0x30, 0x09, 0x06, 0x05,
0x2B, 0x0E,  0x03, 0x02, 0x1A, 0x05,
0x00, 0x04, 0x14

Name

Value

Table 14 — Defines for SHA256 Hash Values

SHA256_DIGEST_SIZE

SHA256_BLOCK_SIZE

SHA256_DER_SIZE

SHA256_DER

6.4  SHA384

Name

SHA384_DIGEST_SIZE

SHA384_BLOCK_SIZE

SHA384_DER_SIZE

SHA384_DER

32

64

19

0x30, 0x31, 0x30, 0x0d, 0x06, 0x09,
0x60, 0x86,  0x48, 0x01, 0x65, 0x03,
0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20

Table 15 — Defines for SHA384 Hash Values

Value

48

128

19

0x30, 0x41, 0x30, 0x0d, 0x06, 0x09,
0x60, 0x86, 0x48, 0x01, 0x65, 0x03,
0x04, 0x02, 0x02, 0x05, 0x00, 0x04, 0x30

Description

size of digest in octets

size of hash block in octets

size of the DER in octets

the DER

Description

size of digest

size of hash block

size of the DER in octets

the DER

Description

size of digest in octets

size of hash block in octets

size of the DER in octets

the DER

Family “2.0"

Page 19

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

Description

size of digest in octets

size of hash block in octets

size of the DER in octets

the DER

Table 16 — Defines for SHA512 Hash Values

Value

64

128

19

0x30, 0x51, 0x30, 0x0d, 0x06, 0x09,
0x60, 0x86, 0x48, 0x01, 0x65, 0x03,
0x04, 0x02, 0x03, 0x05, 0x00, 0x04, 0x40

6.5  SHA512

Name

SHA512_DIGEST_SIZE

SHA512_BLOCK_SIZE

SHA512_DER_SIZE

SHA512_DER

6.6  SM3_256

Name

Value

Table 17 — Defines for SM3_256 Hash Values

SM3_256_DIGEST_SIZE

SM3_256_BLOCK_SIZE

SM3_256_DER_SIZE

SM3_256_DER

32

64

18

0x30, 0x30, 0x30, 0x0c, 0x06, 0x08,
0x2A, 0x81, 0x1C, 0x81, 0x45, 0x01,
0x83, 0x11, 0x05, 0x00, 0x04, 0x20

Description

size of digest in octets

size of hash block in octets

size of the DER in octets

the DER

6.7  Hash Algorithms Bit Field

This table defines a bit field to concisely convey a set of hash algorithms.  An example of where
this could be useful is a parameter returning the set of hash algorithms an interface supports.

Table 18 — Definition of (UINT32) TPMA_HASH_ALGS Bits

Bit

Name

Action

0

1

2

3

4

hashAlgSHA1

hashAlgSHA256

hashAlgSHA384

hashAlgSHA512

hashAlgSM3_256

SET (1): indicates the SHA1 hash algorithm
CLEAR (0): does not indicate SHA1

SET (1): indicates the SHA256 hash algorithm
CLEAR (0): does not indicate SHA256

SET (1): indicates the SHA384 hash algorithm
CLEAR (0): does not indicate SHA384

SET (1): indicates the SHA512 hash algorithm
CLEAR (0): does not indicate SHA512

SET (1): indicates the SM3_256 hash algorithm
CLEAR (0): does not indicate SM3_256

31:5

Reserved

Shall be zero

Page 20

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

7  Symmetric Block Cipher Parameters

7.1

Introduction

The  tables  in  this  section  define  the  parameters  for  each  of  the  TCG-registered  block  ciphers
listed in Table 3.

7.2  AES

Table 19 — Defines for AES Symmetric Cipher Algorithm Constants

Name

Value

Comments

AES_KEY_SIZES_BITS

AES_BLOCK_SIZES_BITS

AES_ROUNDS

7.3  SM4

{128, 192, 256}

{128, 128, 128}

{10, 12, 14}

Table 20 — Defines for SM4 Symmetric Cipher Algorithm Constants

Name

SM4_KEY_SIZES_BITS

SM4_BLOCK_SIZES_BITS

SM4_ROUNDS

7.4  Camellia

Comments

Value

{128}

{128}

{32}

Table 21 — Defines for CAMELLIA Symmetric Cipher Algorithm Constants

Name

Value

Comments

CAMELLIA_KEY_SIZES_BITS

{128, 192, 256}

CAMELLIA_BLOCK_SIZES_BITS

{128, 128, 128}

the block size is the same for all key sizes

CAMELLIA_ROUNDS

{18, 24, 24}

Family “2.0"

Page 21

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

Annex A — Applicability of this Registry for Other TCG Specifications

As a best practice, TCG specifications that have a dependency on this registry will reference it.   To assist
readers  in  understanding  what  TCG  specifications  contain  cryptographic  algorithms,  but  do  not
reference this registry, the TCG maintains the list in Table 22.  For example, for historical reasons, the
TPM Main Specifications for TPM version 1.2 did not reference the registry because they were published
before it.

Table 22 — TCG specifications that do not reference this registry

TCG Specification

BSI-CC-PP-0030-2008 for PC Client Specific Trusted Platform Module Family 1.2; Level 2 Version 1.1 (Part A)

#

1

2

BSI-CC-PP-0030-2008 for PC Client Specific Trusted Platform Module Family 1.2; Level 2 Version 1.1 (Part B)

3

4

5

6

7

8

9

Infrastructure Work Group Integrity Report Schema Specification, Version 1.0

Infrastructure Work Group Reference Architecture for Interoperability Specification (Part 1), Version 1.0

Infrastructure Work Group Reference Manifest (RM) Schema Specification, Version 1.0

Infrastructure Work Group Security Qualities Schema Specification Version 1.0, Revision 1.0

Infrastructure Work Group Security Qualities Schema Specification Version 1.1, Revision 7.0

Infrastructure Work Group TCG Credential Profiles Specification Version 1.0, Revision 0.981

Infrastructure Work Group TCG Credential Profiles Specification Version 1.1, Revision 1.014

10

Infrastructure Work Group Verification Result Schema Specification, Version 1.0

11  TCG Infrastructure Working Group Core Integrity Schema Specification

12

Infrastructure Work Group Architecture Part II - Integrity Management, Version 1.0

13

Infrastructure Work Group Core Integrity Schema Specification, Version 1.0.1

14

Infrastructure Work Group Platform Trust Services Interface Specification (IF-PTS) Version 1.0 (PDF)

15

Infrastructure Work Group Simple Object Schema Specification, Version 1.0

16

Infrastructure Work Group Subject Key Attestation Evidence Extension, Version 1.0

17  Mobile Phone Work Group Mobile Reference Architecture

18  Mobile Phone Work Group Mobile Trusted Module Specification, Version 1.0

19  Mobile Phone Work Group Mobile Trusted Module Specification, Version 1.0, Revision 7.02

20  PC Client Work Group EFI Platform Specification, Version 1.20 and Version 1.22

21  PC Client Work Group EFI Protocol Specification, Version 1.20

22  PC Client Work Group PC Specific Implementation Specification, Version 1.1

23  PC Client Work Group Specific Implementation Specification for Conventional Bios, Version 1.2

24  PC  Client  Work  Group  Specific  Implementation  Specification  for  Conventional  Bios,  Version  1.21  Errata,

Revision 1.00 for TPM Family 1.2; Level 2

25  Protection Profile PC Client Specific Trusted Platform Module TPM Family 1.2; Level 2 Revision 116 Version:

1.2

26  Server Work Group Itanium Architecture Based Server Specification, Version 1.0

Page 22

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22

TCG Algorithm Registry

#

TCG Specification

27  Storage Work Group Storage Security Subsystem Class: Enterprise Specification Version 1.00 Final, Revision

2.00

28  Storage Work Group Storage Security Subsystem Class: Enterprise, Version 1.0, Revision 3.00 and 1.0

29  Storage Work Group Storage Security Subsystem Class: Opal, Version 1.00 Final, Revision 1.00 to 3.00

30  Storage Work Group Storage Security Subsystem Class: Opal, Version 2.00 Final, Revision 1.00

31  Storage Work Group Storage Security Subsystem Class: Optical, Version 1.0

32  TCG Attestation PTS Protocol: Binding to TNC IF-M, Version 1.0, Revision 27

33  TCG Infrastructure Working Group A CMC Profile for AIK Certificate Enrollment, Version 1.0, Revision 7

34  TCG Infrastructure Working Group Reference Manifest (RM) Schema Specification

35  TCG Software Stack (TSS) Specification Version 1.10

36  TCG Software Stack (TSS) Specification Version 1.2

37  TCG Software Stack (TSS) Specification, Version 1.2, Errata A

38  TCG Storage Architecture Core Specification, Version 1.00, Revision 0.9

39  TCG Storage Architecture Core Specification, Version 2.00, Revision 1.00 and 2.00

40  TCG Trusted Network Connect TNC IF-M: TLV Binding, Version 1.0, Revision 40

41  TCG Trusted Network Connect TNC IF-MAP Binding for SOAP, Version 2.2, Revision 9

42  TCG Trusted Network Connect TNC IF-IMC, Version 1.3, Revision 18

43  TCG Trusted Network Connect TNC IF-IMV, Version 1.3, Revision 13

44  TCG Trusted Network Connect TNC IF-T: Protocol Bindings for Tunneled EAP Methods, Version 2.0, Revision

4

45  TCG Trusted Network Connect TNC IF-TNCCS: TLV Binding, Version 2.0, Revision 20

46  TCG Trusted Network Connect TNC MAP Content Authorization, Version 1.0, Revision 35

47  TCG  Storage  Enterprise  SSC  Feature  Set  Locking  LBA  Ranges  Control  Specification,  Version  1.00,  Revision

1.00

48  TCG Storage Opal SSC Feature Set: Single User Mode Specification, Version 1.00, Revision 1.00

49  TNC IF-T Binding to TLS Version 1.0, Revision 16

50  TNC IF-T Binding to TLS Version 2.0, Revision 7

51  TPM Main Specification Level 2 Version 1.2, all revisions

Family “2.0"

Page 23

Level 00 Revision 01.22

Copyright © TCG 2015

February 9, 2015

TCG Algorithm Registry

Annex B — Bibliography

For dated references, only the edition cited applies. For undated references, the latest edition of
the referenced document (including any amendments) applies.

•  GM/T 0003.1-2012: Public Key Cryptographic Algorithm SM2 Based on Elliptic Curves Part 1:

General

•  GM/T 0003.2-2012: Public Key Cryptographic Algorithm SM2 Based on Elliptic Curves Part 2:

Digital Signature Algorithm

•  GM/T 0003.3-2012: Public Key Cryptographic Algorithm SM2 Based on Elliptic Curves Part 3:

Key Exchange Protocol

•  GM/T 0003.5-2012: Public Key Cryptographic Algorithm SM2 Based on Elliptic Curves Part 5:

Parameter definition

•  GM/T 0004-2012: SM3 Cryptographic Hash Algorithm

•  GM/T 0002-2012: SM4 Block Cipher Algorithm

•

•

•

•

•

•

•

•

•

IEEE Std 1363TM-2000, Standard Specifications for Public Key Cryptography

IEEE  Std  1363a™-2004
Specifications for Public Key Cryptography- Amendment 1: Additional Techniques

IEEE  Std  1363™-2000),

(Amendment

to

IEEE  Standard

IETF  RFC  3447,  Public-Key  Cryptography  Standards  (PKCS)  #1:  RSA  Cryptography
Specifications Version 2.1

ISO/IEC  9797-2,  Information  technology  —  Security  techniques  —  Message  authentication
codes (MACs) — Part 2: Mechanisms using a dedicated hash-function

ISO/IEC  10116,  Information  technology  —  Security  techniques  —  Modes  of  operation  for  an
n-bit block cipher

ISO/IEC 10118-3, Information technology — Security techniques — Hash-functions — Part 3:
Dedicated hash functions

ISO/IEC  14888-3,  Information  technology  --  Security  techniques  --  Digital  signature  with
appendix -- Part 3: Discrete logarithm based mechanisms

ISO/IEC 15946-1, Information technology — Security techniques — Cryptographic techniques
based on elliptic curves — Part 1: General

ISO/IEC 18033-3, Information  technology  — Security  techniques — Encryption algorithms —
Part 3: Block ciphers

•  NIST  SP800-108,  Recommendation  for  Key  Derivation  Using  Pseudorandom  Functions

(Revised)

•  NIST  SP800-56A,  Recommendation  for  Pair-Wise  Key  Establishment  Schemes  Using

Discrete Logarithm Cryptography (Revised)

•  TCG Trusted Platform Module 2.0 Library Specification – Part 1: Architecture

Page 24

Family “2.0"

February 9, 2015

Copyright © TCG 2015

Level 00 Revision 01.22


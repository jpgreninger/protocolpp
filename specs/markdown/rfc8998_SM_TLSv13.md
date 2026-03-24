Stream:
RFC:
Category:
Published:
ISSN:
Author:

Independent Submission
8998
Informational
March 2021
2070-1721
P. Yang
Ant Group

RFC 8998
ShangMi (SM) Cipher Suites for TLS 1.3

Abstract

This document speciﬁes how to use the ShangMi (SM) cryptographic algorithms with Transport
Layer Security (TLS) protocol version 1.3.

The use of these algorithms with TLS 1.3 is not endorsed by the IETF. The SM algorithms are
becoming mandatory in China, so this document provides a description of how to use the SM
algorithms with TLS 1.3 and speciﬁes a proﬁle of TLS 1.3 so that implementers can produce
interworking implementations.

Status of This Memo

This document is not an Internet Standards Track speciﬁcation; it is published for informational
purposes.

This is a contribution to the RFC Series, independently of any other RFC stream. The RFC Editor
has chosen to publish this document at its discretion and makes no statement about its value for
implementation or deployment. Documents approved for publication by the RFC Editor are not
candidates for any level of Internet Standard; see Section 2 of RFC 7841.

Information about the current status of this document, any errata, and how to provide feedback
on it may be obtained at

https://www.rfc-editor.org/info/rfc8998

.

Copyright Notice

Copyright (c) 2021 IETF Trust and the persons identiﬁed as the document authors. All rights
reserved.

This document is subject to BCP 78 and the IETF Trust's Legal Provisions Relating to IETF
Documents (
) in eﬀect on the date of publication of this
document. Please review these documents carefully, as they describe your rights and restrictions
with respect to this document.

https://trustee.ietf.org/license-info

Yang

Informational

Page 1

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

Table of Contents

1.  Introduction

1.1.  The SM Algorithms

1.2.  Terminology

2.  Algorithm Identiﬁers

3.  Algorithm Deﬁnitions

3.1.  TLS Versions

3.2.  Authentication

3.2.1.  SM2 Signature Scheme

3.3.  Key Exchange

3.3.1.  Hello Messages

3.3.2.  CertiﬁcateRequest

3.3.3.  Certiﬁcate

3.3.4.  CertiﬁcateVerify

3.4.  Key Scheduling

3.5.  Cipher

3.5.1.  AEAD_SM4_GCM

3.5.2.  AEAD_SM4_CCM

4.  IANA Considerations

5.  Security Considerations

6.  References

6.1.  Normative References

6.2.  Informative References

Appendix A.  Test Vectors

A.1.  SM4-GCM Test Vectors

A.2.  SM4-CCM Test Vectors

Contributors

Author's Address

Yang

Informational

Page 2

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

1.  Introduction

This document describes two new cipher suites, a signature algorithm and a key exchange
[RFC8446]
mechanism for the Transport Layer Security (TLS) protocol version 1.3 (TLS 1.3) (
These all utilize several ShangMi (SM) cryptographic algorithms to fulﬁll the authentication and
conﬁdentiality requirements of TLS 1.3. The new cipher suites are as follows (see also Section 2):

).

   CipherSuite TLS_SM4_GCM_SM3 = { 0x00, 0xC6 };
   CipherSuite TLS_SM4_CCM_SM3 = { 0x00, 0xC7 };

For a more detailed introduction to SM cryptographic algorithms, please see Section 1.1. These
cipher suites follow the TLS 1.3 requirements. Speciﬁcally, all the cipher suites use SM4 in either
Galois/Counter (GCM) mode or Counter with CBC-MAC (CCM) mode to meet the needs of TLS 1.3
to have an encryption algorithm that is Authenticated Encryption with Associated Data (AEAD)
capable. The key exchange mechanism utilizes Elliptic Curve Diﬃe-Hellman Ephemeral (ECDHE)
over the SM2 elliptic curve, and the signature algorithm combines the SM3 hash function and the
SM2 elliptic curve signature scheme.

For details about how these mechanisms negotiate shared encryption keys, authenticate the peer
(s), and protect the record structure, please see Section 3.

The cipher suites, signature algorithm, and key exchange mechanism deﬁned in this document
are not recommended by the IETF. The SM algorithms are becoming mandatory in China, so this
document provides a description of how to use them with TLS 1.3 and speciﬁes a proﬁle of TLS
1.3 so that implementers can produce interworking implementations.

1.1.  The SM Algorithms

Several diﬀerent SM cryptographic algorithms are used to integrate with TLS 1.3, including SM2
for authentication, SM4 for encryption, and SM3 as the hash function.

SM2 is a set of cryptographic algorithms based on elliptic curve cryptography, including a digital
signature, public key encryption and key exchange scheme. In this document, only the SM2
digital signature algorithm and basic key exchange scheme are involved, which have already
been added to ISO/IEC 14888-3:2018
cipher deﬁned in
[ISO-SM4]
accepted by ISO in ISO/IEC 10118-3:2018
[GBT.32905-2016]

. SM3 is a hash function that produces an output of 256 bits. SM3 has already been

 and now is being standardized by ISO to ISO/IEC 18033-3:2010

 and has also been described by

[GBT.32918.2-2016]

[GBT.32907-2016]

). SM4 is a block

 (as well as to

[ISO-SM2]

[ISO-SM3]

.

Yang

Informational

Page 3

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

1.2.  Terminology

RECOMMENDED NOT RECOMMENDED MAY

", "

", "

MUST MUST NOT

The key words "
NOT
be interpreted as described in BCP 14
all capitals, as shown here.

", "

", "

", "

REQUIRED SHALL
", "
[RFC2119] [RFC8174]

", "
", and "

SHALL NOT

OPTIONAL

", "
", "
SHOULD SHOULD
" in this document are to

 when, and only when, they appear in

Although this document is not an IETF Standards Track publication, it adopts the conventions for
normative language to provide clarity of instruction to the implementer and to indicate
requirement levels for compliant TLS 1.3 implementations.

2.  Algorithm Identiﬁers

The cipher suites deﬁned here have the following identiﬁers:

   CipherSuite TLS_SM4_GCM_SM3 = { 0x00, 0xC6 };
   CipherSuite TLS_SM4_CCM_SM3 = { 0x00, 0xC7 };

To accomplish a TLS 1.3 handshake, additional objects have been introduced along with the
cipher suites as follows:

•

The combination of the SM2 signature algorithm and SM3 hash function used in the
Signature Algorithm extension is deﬁned in

Appendix B.3.1.3 of [RFC8446]

:

      SignatureScheme sm2sig_sm3 = { 0x0708 };

•

The SM2 elliptic curve ID used in the Supported Groups extension is deﬁned in
B.3.1.4 of [RFC8446]

:

Appendix

      NamedGroup curveSM2 = { 41 };

3.  Algorithm Deﬁnitions

3.1.  TLS Versions

The new cipher suites deﬁned in this document are only applicable to TLS 1.3. Implementations
of this document

 apply these cipher suites to any older versions of TLS.

MUST NOT

Yang

Informational

Page 4

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

3.2.  Authentication

3.2.1.  SM2 Signature Scheme

The Chinese government requires the use of the SM2 signature algorithm. This section speciﬁes
the use of the SM2 signature algorithm as the authentication method for a TLS 1.3 handshake.

[ISO-SM2]
The SM2 signature algorithm is deﬁned in
elliptic curves. The SM2 signature algorithm uses a ﬁxed elliptic curve parameter set deﬁned in
[GBT.32918.5-2017]
shown in Section 2. Unlike other public key algorithms based on elliptic curve cryptography like
the Elliptic Curve Digital Signature Algorithm (ECDSA), SM2
But it is acceptable to write test cases that use other elliptic curve parameter sets for SM2; see
Annex F.14 of

. This curve is named "curveSM2" and has been assigned the value 41, as

. The SM2 signature algorithm is based on

 as a reference.

 select other elliptic curves.

[ISO-SM2]

MUST NOT

Implementations of the signature scheme and key exchange mechanism deﬁned in this
document
 requires; that is to say, the only valid
[GBT.32918.5-2017]
elliptic curve parameter set for the SM2 signature algorithm (a.k.a. curveSM2) is deﬁned as
follows:

 conform to what

MUST

curveSM2:

A prime ﬁeld of 256 bits.

y2 = x3 + ax + b

   p  = FFFFFFFE FFFFFFFF FFFFFFFF FFFFFFFF
        FFFFFFFF 00000000 FFFFFFFF FFFFFFFF
   a  = FFFFFFFE FFFFFFFF FFFFFFFF FFFFFFFF
        FFFFFFFF 00000000 FFFFFFFF FFFFFFFC
   b  = 28E9FA9E 9D9F5E34 4D5A9E4B CF6509A7
        F39789F5 15AB8F92 DDBCBD41 4D940E93
   n  = FFFFFFFE FFFFFFFF FFFFFFFF FFFFFFFF
        7203DF6B 21C6052B 53BBF409 39D54123
   Gx = 32C4AE2C 1F198119 5F990446 6A39C994
        8FE30BBF F2660BE1 715A4589 334C74C7
   Gy = BC3736A2 F4F6779C 59BDCEE3 6B692153
        D0A9877C C62A4740 02DF32E5 2139F0A0

The SM2 signature algorithm requests an identiﬁer value when generating or verifying a
signature. In all uses except when a client of a server needs to verify a peer's SM2 certiﬁcate in
the Certiﬁcate message, an implementation of this document
value as the SM2 identiﬁer when doing a TLS 1.3 key exchange:

 use the following ASCII string

MUST

   TLSv1.3+GM+Cipher+Suite

Yang

Informational

Page 5

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

If either a client or a server needs to verify the peer's SM2 certiﬁcate contained in the Certiﬁcate
message, then the following ASCII string value
 be used as the SM2 identiﬁer according to
:
[GMT.0009-2012]

MUST

   1234567812345678

Expressed as octets, this is:

   0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
   0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38

In practice, the SM2 identiﬁer used in a certiﬁcate signature depends on the certiﬁcate authority
(CA) who signs that certiﬁcate. CAs may choose values other than the ones mentioned above.
Implementations of this document

 conﬁrm this information by themselves.

SHOULD

3.3.  Key Exchange

3.3.1.  Hello Messages

The use of the algorithms deﬁned by this document is negotiated during the TLS handshake with
information exchanged in the Hello messages.

3.3.1.1.  ClientHello

To use the cipher suites deﬁned by this document, a TLS 1.3 client includes the new cipher suites
in the "cipher_suites" array of the ClientHello structure deﬁned in

Section 4.1.2 of [RFC8446]

.

Other requirements of this TLS 1.3 proﬁle on the extensions of ClientHello message are as
follows:

•

For the supported_groups extension, "curveSM2"

MUST

 be included.

•

For the signature_algorithms extension, "sm2sig_sm3"

MUST

 be included.

•

For the signature_algorithms_cert extension (if present), "sm2sig_sm3"

MUST

 be included.

•

For the key_share extension, a KeyShareEntry for the "curveSM2" group

MUST

 be included.

3.3.1.2.  ServerHello

If a TLS 1.3 server receives a ClientHello message containing the algorithms deﬁned in this
 put one of the new cipher suites
document, it
deﬁned in this document into its ServerHello's "cipher_suites" array and eventually send it to the
client side.

 choose to use them. If so, then the server

MUST

MAY

A TLS 1.3 server's choice of what cipher suite to use depends on the conﬁguration of the server.
For instance, a TLS 1.3 server may or not be conﬁgured to include the new cipher suites deﬁned
in this document. Typical TLS 1.3 server applications also provide a mechanism that conﬁgures
the cipher suite preference on the server side. If a server is not conﬁgured to use the cipher

Yang

Informational

Page 6

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

suites deﬁned in this document, it
client provides; otherwise, the server
alert.

SHOULD

 choose another cipher suite in the list that the TLS 1.3
 abort the handshake with an "illegal_parameter"

MUST

The following extension

MUST

 conform to the new requirements:

•

For the key_share extension, a KeyShareEntry with SM2-related values
server wants to conform to this proﬁle.

MUST

 be added if the

3.3.2.  CertiﬁcateRequest

If a CertiﬁcateRequest message is sent by the server to require the client to send its certiﬁcate for
authentication purposes, for conformance to this proﬁle, the following is

:
REQUIRED

•

The only valid signature algorithm present in "signature_algorithms" extension
 be
"sm2sig_sm3". That is to say, if the server chooses to conform to this proﬁle, the signature
algorithm for the client's certiﬁcate
document.

 use the SM2/SM3 procedure speciﬁed by this

MUST

MUST

3.3.3.  Certiﬁcate

When a server sends the Certiﬁcate message containing the server certiﬁcate to the client side,
several new rules are added that will aﬀect the certiﬁcate selection:

•

The public key in the certiﬁcate

MUST

 be a valid SM2 public key.

•

The signature algorithm used by the CA to sign the current certiﬁcate

MUST

 be "sm2sig_sm3".

•

The certiﬁcate
extension is set.

MUST

 be capable of signing; e.g., the digitalSignature bit of X.509's Key Usage

3.3.4.  CertiﬁcateVerify

In the CertiﬁcateVerify message, the signature algorithm
the hash function

 be SM3 and the signature algorithm

MUST

MUST

 be SM2.

MUST

 be "sm2sig_sm3", indicating that

3.4.  Key Scheduling

As described in Section 1.1, SM2 is actually a set of cryptographic algorithms, including one key
exchange protocol that deﬁnes methods such as key derivation function, etc. This document does
 be used
not deﬁne an SM2 key exchange protocol, and an SM2 key exchange protocol
in the key exchange steps deﬁned in Section 3.3. Implementations of this document
 always
conform to what TLS 1.3
related methods.

 and its successors require regarding the key derivation and

[RFC8446]

SHALL NOT

MUST

3.5.  Cipher

The new cipher suites introduced in this document add two new AEAD encryption algorithms,
AEAD_SM4_GCM and AEAD_SM4_CCM, which stand for SM4 cipher in Galois/Counter mode and
SM4 cipher
both cipher suites is SM3 (

 in Counter with CBC-MAC mode, respectively. The hash function for

[GBT.32907-2016]

[ISO-SM3]

).

Yang

Informational

Page 7

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

This section deﬁnes the AEAD_SM4_GCM and AEAD_SM4_CCM AEAD algorithms in a style similar
to what

 used to deﬁne AEAD ciphers based on the AES cipher.

[RFC5116]

3.5.1.  AEAD_SM4_GCM

[GCM]

, using SM4

 be constructed using the details in the TLS record header. The
 be the TLS record header. The

The AEAD_SM4_GCM authenticated encryption algorithm works as speciﬁed in
as the block cipher, by providing the key, nonce, plaintext, and associated data to that mode of
operation. An authentication tag conforming to the requirements of TLS 1.3 as speciﬁed in
Section 5.2 of [RFC8446] MUST
additional data input that forms the authentication tag
AEAD_SM4_GCM ciphertext is formed by appending the authentication tag provided as an output
to the GCM encryption operation to the ciphertext that is output by that operation.
AEAD_SM4_GCM has four inputs: an SM4 key, an initialization vector (IV), a plaintext content,
and optional additional authenticated data (AAD). AEAD_SM4_GCM generates two outputs: a
ciphertext and message authentication code (also called an authentication tag). To have a
common set of terms for AEAD_SM4_GCM and AEAD_SM4_CCM, the AEAD_SM4_GCM IV is
referred to as a nonce in the remainder of this document. A simple test vector of
AEAD_SM4_GCM and AEAD_SM4_CCM is given in Appendix A of this document.

MUST

The nonce is generated by the party performing the authenticated encryption operation. Within
the scope of any authenticated encryption key, the nonce value
 be unique. That is, the set
of nonce values used with any given key
for two diﬀerent messages encrypted with the same key destroys the security properties of GCM
mode. To generate the nonce, implementations of this document
[RFC8446], Section 5.3

 contain any duplicates. Using the same nonce

 conform to TLS 1.3 (see

MUST NOT

MUST

MUST

).

The input and output lengths are as follows:

The SM4 key length is 16 octets.

The max plaintext length is 236 - 31 octets.

The max AAD length is 261 - 1 octets.

The nonce length is 12 octets.

The authentication tag length is 16 octets.

The max ciphertext length is 236 - 15 octets.

A security analysis of GCM is available in

.
[MV04]

3.5.2.  AEAD_SM4_CCM

The AEAD_SM4_CCM authenticated encryption algorithm works as speciﬁed in
as the block cipher. AEAD_SM4_CCM has four inputs: an SM4 key, a nonce, a plaintext, and
optional additional authenticated data (AAD). AEAD_SM4_CCM generates two outputs: a

[CCM]

 using SM4

Yang

Informational

Page 8

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

ciphertext and a message authentication code (also called an authentication tag). The formatting
and counter generation functions are as speciﬁed in Appendix A of
, and the values of the
parameters identiﬁed in that appendix are as follows:

[CCM]

The nonce length n is 12.

The tag length t is 16.

The value of q is 3.

 conform to TLS 1.3 (See

An authentication tag is also used in AEAD_SM4_CCM. The generation of the authentication tag
). The AEAD_SM4_CCM ciphertext is formed
MUST
by appending the authentication tag provided as an output to the CCM encryption operation to
the ciphertext that is output by that operation. The input and output lengths are as follows:

[RFC8446], Section 5.2

The SM4 key length is 16 octets.

The max plaintext length is 224 - 1 octets.

The max AAD length is 264 - 1 octets.

The max ciphertext length is 224 + 15 octets.

To generate the nonce, implementations of this document
[RFC8446], Section 5.3

).

MUST

 conform to TLS 1.3 (see

A security analysis of CCM is available in

.
[J02]

4.  IANA Considerations

IANA has assigned the values {0x00,0xC6} and {0x00,0xC7} with the names "TLS_SM4_GCM_SM3"
and "TLS_SM4_CCM_SM3" to the "TLS Cipher Suites" registry with this document as reference:

Value

Description

DTLS-OK

Recommended

Reference

0x00,0xC6

TLS_SM4_GCM_SM3 No

0x00,0xC7

TLS_SM4_CCM_SM3

No

No

No

RFC 8998

RFC 8998

Table 1

IANA has assigned the value 0x0708 with the name "sm2sig_sm3" to the "TLS SignatureScheme"
registry:

Value Description

Recommended

Reference

0x0708

sm2sig_sm3

No

RFC 8998

Table 2

Yang

Informational

Page 9

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

IANA has assigned the value 41 with the name "curveSM2" to the "TLS Supported Groups"
registry:

Value Description DTLS-OK

Recommended

Reference

41

curveSM2

No

No

RFC 8998

Table 3

5.  Security Considerations

At the time of writing, there are no known weak keys for SM cryptographic algorithms SM2, SM3
and SM4, and no security issues have been found for these algorithms.

A security analysis of GCM is available in

[MV04]
.

A security analysis of CCM is available in

[J02]
.

6.  References

6.1.  Normative References

[CCM]

[GCM]

[ISO-SM2]

[ISO-SM3]

[ISO-SM4]

[RFC2119]

,

Dworkin, M. "Recommendation for Block Cipher Modes of Operation: the CCM
Mode for Authentication and Conﬁdentiality" Special Publication 800-38C DOI
10.6028/NIST.SP.800-38C
nistpubs/800-38C/SP800-38C.pdf>

<http://csrc.nist.gov/publications/

, May 2004,

,

,

.

,

Dworkin, M. "Recommendation for Block Cipher Modes of Operation: Galois/
,
Counter Mode (GCM) and GMAC" Special Publication 800-38D DOI 10.6028/
, November 2007,
NIST.SP.800-38D
<http://csrc.nist.gov/publications/
.
nistpubs/800-38D/SP-800-38D.pdf>

,

International Organization for Standardization "IT Security techniques -- Digital
signatures with appendix -- Part 3: Discrete logarithm based mechanisms" ISO/
.
IEC 14888-3:2018

<https://www.iso.org/standard/76382.html>

, November 2018,

,

,

International Organization for Standardization "IT Security techniques -- Hash-
functions -- Part 3: Dedicated hash-functions" ISO/IEC 10118-3:2018
2018,

<https://www.iso.org/standard/67116.html>

, October

,

.

,

International Organization for Standardization "Information technology --
Security techniques -- Encryption algorithms -- Part 3: Block ciphers" ISO/IEC
18033-3:2010

<https://www.iso.org/standard/54531.html>

, December 2010,

,

.

,

,

Bradner, S. "Key words for use in RFCs to Indicate Requirement Levels" BCP 14
, March 1997,
<https://www.rfc-editor.org/info/
RFC 2119 DOI 10.17487/RFC2119
rfc2119>

,
.

,

,

Yang

Informational

Page 10

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

[RFC5116]

[RFC8174]

[RFC8446]

,

McGrew, D. "An Interface and Algorithms for Authenticated Encryption" RFC
5116 DOI 10.17487/RFC5116
,
rfc5116>

<https://www.rfc-editor.org/info/

, January 2008,

,

.

,

Leiba, B. "Ambiguity of Uppercase vs Lowercase in RFC 2119 Key Words" BCP
14 RFC 8174 DOI 10.17487/RFC8174
rfc8174>

<https://www.rfc-editor.org/info/

, May 2017,

,

,

.

,

,
Rescorla, E. "The Transport Layer Security (TLS) Protocol Version 1.3" RFC 8446
DOI 10.17487/RFC8446

<https://www.rfc-editor.org/info/rfc8446>

, August 2018,

,

.

,

6.2.  Informative References

[GBT.32905-2016]

Standardization Administration of China "Information security technology

,

--- SM3 cryptographic hash algorithm" GB/T 32905-2016
www.gmbz.org.cn/upload/2018-07-24/1532401392982079739.pdf>

, March 2017,

.

,

<http://

[GBT.32907-2016]

,
Standardization Administration of the People's Republic of China
"Information security technology -- SM4 block cipher algorithm" GB/T
32907-2016
upload/2018-04-04/1522788048733065051.pdf>

<http://www.gmbz.org.cn/

, March 2017,

,

.

[GBT.32918.2-2016]

Standardization Administration of the People's Republic of China
"Information security technology --- Public key cryptographic algorithm SM2
based on elliptic curves --- Part 2: Digital signature algorithm" GB/T
32918.2-2016
upload/2018-07-24/1532401673138056311.pdf>

<http://www.gmbz.org.cn/

, March 2017,

,

.

,

[GBT.32918.5-2017]

Standardization Administration of the People's Republic of China
"Information security technology --- Public key cryptographic algorithm SM2
,
based on elliptic curves --- Part 5: Parameter deﬁnition" GB/T 32918.5-2017
December 2017,
upload/2018-07-24/1532401863206085511.pdf>

<http://www.gmbz.org.cn/

,

.

,

[GMT.0009-2012]

State Cryptography Administration "SM2 cryptography algorithm application
<http://www.gmbz.org.cn/main/

, November 2012,

,

,

speciﬁcation" GM/T 0009-2012
viewﬁle/2018011001400692565.html>

.

[J02]

[MV04]

Jonsson, J. "On the Security of CTR + CBC-MAC" DOI 10.1007/3-540-36492-7_7
February 2003,

,
<https://link.springer.com/chapter/10.1007%2F3-540-36492-7_7>

,

,

.

McGrew, D. and J. Viega "The Security and Performance of the Galois/Counter
Mode of Operation" DOI 10.1007/978-3-540-30556-9_27
eprint.iacr.org/2004/193>

, December 2004,

<http://

,

.

,

Appendix A.  Test Vectors

All values are in hexadecimal and are in network byte order (big endian).

Yang

Informational

Page 11

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

A.1.  SM4-GCM Test Vectors

Initialization Vector:   00001234567800000000ABCD
Key:                     0123456789ABCDEFFEDCBA9876543210
Plaintext:               AAAAAAAAAAAAAAAABBBBBBBBBBBBBBBB
                         CCCCCCCCCCCCCCCCDDDDDDDDDDDDDDDD
                         EEEEEEEEEEEEEEEEFFFFFFFFFFFFFFFF
                         EEEEEEEEEEEEEEEEAAAAAAAAAAAAAAAA
Associated Data:         FEEDFACEDEADBEEFFEEDFACEDEADBEEFABADDAD2
CipherText:              17F399F08C67D5EE19D0DC9969C4BB7D
                         5FD46FD3756489069157B282BB200735
                         D82710CA5C22F0CCFA7CBF93D496AC15
                         A56834CBCF98C397B4024A2691233B8D
Authentication Tag:      83DE3541E4C2B58177E065A9BF7B62EC

A.2.  SM4-CCM Test Vectors

Initialization Vector:   00001234567800000000ABCD
Key:                     0123456789ABCDEFFEDCBA9876543210
Plaintext:               AAAAAAAAAAAAAAAABBBBBBBBBBBBBBBB
                         CCCCCCCCCCCCCCCCDDDDDDDDDDDDDDDD
                         EEEEEEEEEEEEEEEEFFFFFFFFFFFFFFFF
                         EEEEEEEEEEEEEEEEAAAAAAAAAAAAAAAA
Associated Data:         FEEDFACEDEADBEEFFEEDFACEDEADBEEFABADDAD2
CipherText:              48AF93501FA62ADBCD414CCE6034D895
                         DDA1BF8F132F042098661572E7483094
                         FD12E518CE062C98ACEE28D95DF4416B
                         ED31A2F04476C18BB40C84A74B97DC5B
Authentication Tag:      16842D4FA186F56AB33256971FA110F4

Contributors

Qin Long
Ant Group
Email:

 zhuolong.lq@antﬁn.com

Kepeng Li
Ant Group
Email:

 kepeng.lkp@antﬁn.com

Ke Zeng
Ant Group
Email:

 william.zk@antﬁn.com

Yang

Informational

Page 12

RFC 8998

SM Cipher Suites for TLS 1.3

March 2021

Han Xiao
Ant Group
Email:

 han.xiao@antﬁn.com

Zhi Guan
Peking University
Email:

 guan@pku.edu.cn

Author's Address

Paul Yang
Ant Group
No. 77 Xueyuan Road
Hangzhou
310000
China
Phone:
Email:

 +86-571-2688-8888
 kaishen.yy@antﬁn.com

Yang

Informational

Page 13


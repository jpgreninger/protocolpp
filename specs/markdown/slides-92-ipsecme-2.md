ChaCha20 + Poly1305
For IPsec & IKE

Yoav Nir
IETF 92

Agenda

• ChaCha20 + Poly1305

• CFRG Draft

• IPsecME Candidate Draft

• Please Support

2

ChaCha20 + Poly1305

• ChaCha20 is a stream or counter-mode cipher

• Poly1305 is an authenticator function

• Both were designed by D. J. Bernstein

• Both have been reviewed extensively

3

ChaCha20 + Poly1305

• ChaCha20 offers a performance advantage:

Algorithm Modern Intel Old Intel

ARM

AES-CTR

ChaCha20

Advantage

1.95

1.24

57%

14.19

4.71

201%

19.32

13.29

45%

• Source: http://bench.cr.yp.to/results-stream.html

• When comparing AES-GCM to ChaCha+Poly,

AES-GCM has a slight advantage on modern Intel

4

CFRG Draft

• The algorithms were proposed to both IPsecME

and TLS.

• The feedback from both groups was: go to

CFRG and get their approval.

• So we did: http://tools.ietf.org/html/draft-irtf-cfrg-

chacha20-poly1305

5

CFRG Draft

• NIST-approved algorithms come with a

publication that contains great documentation:

• Algorithm details

• Pseudo-code

• Test vectors

• Implementation advice

• We tried to replicate that in out draft

6

CFRG Draft

• Multiple implementations based on the draft

• Thorough review

• Security review of the AEAD composition

• Approved. Document is in the RFC Editor’s

queue.

7

IPsecME Candidate Draft

• Simple draft - AEAD only for both IKE and IPsec

• Early review said the WG didn’t want ChaCha20

and Poly1305 separately

• Also deﬁnes a UI Suite: “VPN-C” or “Suite-C”

• “C” stands for “civilian” - non-government

• Currently uses P-256 for key exchange, and

HMAC-SHA256 for PRF

• Replace with Curve25519 and Blake2 ?

8

Please Support

• The TLS working group is discussing adopting

the equivalent document.

• They would like (yet to be conﬁrmed on the list)
to make it a SHOULD-level algorithm in TLS 1.3.

• Best algorithm we have around with good

performance and a chance for wide adoption

• Please support

9


3GPP TS 25.323 V13.0.0 (2015-12)

Technical Specification

3rd Generation Partnership Project;
Technical Specification Group Radio Access Network;
Packet Data Convergence Protocol (PDCP) specification
(Release 13)

The present document has been developed within the 3rd Generation Partnership Project (3GPP TM) and may be further elaborated for the purposes of 3GPP..
The present document has not been subject to any approval process by the 3GPP Organizational Partners and shall not be implemented.
This Specification is provided for future development work within 3GPP only. The Organizational Partners accept no liability for any use of this Specification.
Specifications and reports for implementation of the 3GPP TM system should be obtained via the 3GPP Organizational Partners' Publications Offices.

Release 13

2

3GPP TS 25.323 V13.0.0 (2015-12)

Keywords
UMTS, radio, packet mode

3GPP

Postal address

3GPP support office address
650 Route des Lucioles - Sophia Antipolis
Valbonne - FRANCE
Tel.: +33 4 92 94 42 00 Fax: +33 4 93 65 47 16

Internet
http://www.3gpp.org

Copyright Notification

No part may be reproduced except as authorized by written permission.
The copyright and the foregoing restriction extend to reproduction in all media.

© 2015, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC).
All rights reserved.

UMTS™ is a Trade Mark of ETSI registered for the benefit of its members
3GPP™ is a Trade Mark of ETSI registered for the benefit of its Members and of the 3GPP Organizational Partners
LTE™ is a Trade Mark of ETSI currently being registered for the benefit of its Members and of the 3GPP Organizational Partners
GSM® and the GSM logo are registered and owned by the GSM Association

3GPP

Release 13

3

3GPP TS 25.323 V13.0.0 (2015-12)

Contents
Foreword............................................................................................................................................................. 6

1

2

3
3.1
3.2

4
4.1
4.2

Scope ........................................................................................................................................................ 7

References ................................................................................................................................................ 7

Definitions and Abbreviations ................................................................................................................. 7
Definitions ......................................................................................................................................................... 7
Abbreviations ..................................................................................................................................................... 8

General ..................................................................................................................................................... 9
Objective ............................................................................................................................................................ 9
Overview on sublayer architecture .................................................................................................................... 9

5
5.1
5.1.1
5.1.2
5.1.2.1
5.1.2.2
5.1.2.3
5.1.3
5.1.3.1
5.1.3.2
5.1.3.3
5.1.3.4
5.1.3.5
5.1.3.6
5.2
5.3
5.3.1
5.3.2
5.4
5.4.1
5.4.1.1
5.4.1.2
5.4.1.3
5.4.2
5.5
5.6
5.6.1.1
5.6.1.2
5.6.1.3
5.6.1.4
5.7
5.7.1
5.7.2

Functions ................................................................................................................................................ 10
Header Compression ........................................................................................................................................ 10
Mapping of PID values .............................................................................................................................. 10
IP Header Compression (RFC 2507) .......................................................................................................... 11
Context identifiers ................................................................................................................................ 11
Mapping of PID values for RFC 2507 .................................................................................................. 11
Management of Full Header transmission ............................................................................................ 11
Robust Header Compression ...................................................................................................................... 11
Context identifiers ................................................................................................................................ 12
Void ...................................................................................................................................................... 12
Mapping of PID values ......................................................................................................................... 12
Void ...................................................................................................................................................... 12
Protocol Parameters .............................................................................................................................. 12
Configuration by RRC .......................................................................................................................... 13
Void ................................................................................................................................................................. 13
Data Transfer ................................................................................................................................................... 13
Data transfer over acknowledged mode RLC............................................................................................. 14
Data transfer over unacknowledged and transparent mode RLC ............................................................... 14
SRNS Relocation ............................................................................................................................................. 14
Lossless SRNS Relocation ......................................................................................................................... 15
Void ...................................................................................................................................................... 15
Void ...................................................................................................................................................... 15
Void ...................................................................................................................................................... 15
Context relocation ...................................................................................................................................... 15
Lossless DL RLC PDU size change ................................................................................................................ 17
General procedures .......................................................................................................................................... 17
PDCP Sequence Numbering ................................................................................................................. 17
PDCP Sequence Number synchronization ........................................................................................... 18
Sequence Number and Data Forwarding .............................................................................................. 19
CS Counter Handling............................................................................................................................ 19
Header Compression and Decompression for MBMS ..................................................................................... 19
Cell change inside the same cell group ...................................................................................................... 19
Cell change between cell groups ................................................................................................................ 20

6
6.1
6.2

7
7.1

Services .................................................................................................................................................. 20
Services provided to upper layers .................................................................................................................... 20
Services expected from RLC layer .................................................................................................................. 20

Elements for layer-to-layer communication ........................................................................................... 20
Primitives between PDCP and upper layers .................................................................................................... 20

8
8.1
8.2
8.2.1
8.2.2
8.2.3

Elements for peer-to-peer communication ............................................................................................. 22
Protocol data units ........................................................................................................................................... 22
Formats ............................................................................................................................................................ 22
PDCP-No-Header PDU .............................................................................................................................. 22
PDCP Data PDU ........................................................................................................................................ 22
PDCP SeqNum PDU .................................................................................................................................. 23

3GPP

Release 13

4

3GPP TS 25.323 V13.0.0 (2015-12)

8.2.4
8.3
8.3.1
8.3.2
8.3.3
8.3.4
8.3.5

9
9.1
9.2
9.3

PDCP AMR Data PDU .............................................................................................................................. 23
Parameters........................................................................................................................................................ 23
PDU Type .................................................................................................................................................. 23
PID ............................................................................................................................................................. 24
Data ............................................................................................................................................................ 24
Sequence number ....................................................................................................................................... 24
CS counter .................................................................................................................................................. 24

Handling of unknown, unforeseen and erroneous protocol data ............................................................ 24
Invalid PDU type ............................................................................................................................................. 24
Invalid PID value ............................................................................................................................................. 25
PDCP Unrecoverable Error Detection ............................................................................................................. 25

Annex A (normative):
A.1
A.1.1
A.1.2
A.1.3
A.1.4
A.1.5
A.2
A.2.1
A.2.1.1
A.2.1.2
A.2.1.3
A.2.2
A.2.2.1
A.2.2.2
A.2.2.3
A.2.3
A.2.3.1
A.2.3.2
A.2.3.3
A.2.4
A.2.4.1
A.2.4.2
A.2.4.3
A.2.5
A.2.5.1
A.2.5.2
A.2.5.3
A.2.6
A.2.6.1
A.2.6.2
A.2.6.3
A.2.7
A.2.7.1
A.2.7.2
A.2.7.3
A.2.8
A.2.8.1
A.2.8.2
A.2.8.3
A.2.9
A.2.9.1
A.2.9.2
A.2.9.3
A.2.10
A.2.10.1
A.2.10.2
A.2.10.3
A.2.11

ROHC performance testing .......................................................................... 26
Introduction...................................................................................................................................................... 26
Purpose of the performance testing ............................................................................................................ 26
Input sequence for uncompressed headers ................................................................................................. 26
Feedback format for the test cases ............................................................................................................. 27
Feedback generation for test cases (R-mode only) ..................................................................................... 27
Calculation of compressed header size....................................................................................................... 28
Test outline – RoHC RTP Profile 0x0001 ....................................................................................................... 28
Test 1a - Base test of ROHC RTP O-mode compressor ............................................................................. 28
Test purpose.......................................................................................................................................... 28
Sequence details ................................................................................................................................... 28
Test requirement ................................................................................................................................... 29
Test 1b - Base test of ROHC RTP R-mode compressor ............................................................................. 29
Test purpose.......................................................................................................................................... 29
Sequence details ................................................................................................................................... 30
Test requirement ................................................................................................................................... 30
Void ............................................................................................................................................................ 31
Void ...................................................................................................................................................... 31
Void ...................................................................................................................................................... 31
Void ...................................................................................................................................................... 31
Void ............................................................................................................................................................ 31
Void ...................................................................................................................................................... 31
Void ...................................................................................................................................................... 31
Void ...................................................................................................................................................... 31
Test 3a - Re-establishment of TS function after DTX in O-mode.............................................................. 31
Test purpose.......................................................................................................................................... 31
Sequence details ................................................................................................................................... 31
Test requirement ................................................................................................................................... 32
Test 3b - Re-establishment of TS function after DTX in R-mode.............................................................. 32
Test purpose.......................................................................................................................................... 32
Sequence details ................................................................................................................................... 32
Test requirement ................................................................................................................................... 32
Test 4a - Compressor response to single lost packets in O-mode .............................................................. 33
Test purpose.......................................................................................................................................... 33
Sequence details ................................................................................................................................... 33
Test requirement ................................................................................................................................... 33
Test 4b - Compressor response to single lost packets in R-mode .............................................................. 33
Test purpose.......................................................................................................................................... 33
Sequence details ................................................................................................................................... 33
Test requirement ................................................................................................................................... 33
Void ............................................................................................................................................................ 34
Void ...................................................................................................................................................... 34
Void ...................................................................................................................................................... 34
Void ...................................................................................................................................................... 34
Void ............................................................................................................................................................ 34
Void ...................................................................................................................................................... 34
Void ...................................................................................................................................................... 34
Void ...................................................................................................................................................... 34
Test 6a - TS function during DTX with varying delta in O-mode ............................................................. 34

3GPP

Release 13

5

3GPP TS 25.323 V13.0.0 (2015-12)

A.2.11.1
A.2.11.2
A.2.11.3
A.2.12
A.2.12.1
A.2.12.2
A.2.12.3
A.2.13
A.2.13.1
A.2.13.2
A.2.13.3
A.3

Test purpose.......................................................................................................................................... 34
Sequence details ................................................................................................................................... 34
Test requirement ................................................................................................................................... 34
Test 6b - TS function during DTX with varying delta in R-mode ............................................................. 35
Test purpose.......................................................................................................................................... 35
Sequence details ................................................................................................................................... 35
Test requirement ................................................................................................................................... 35
Test 7a – SRNS relocation in O-mode ....................................................................................................... 36
Test purpose.......................................................................................................................................... 36
Sequence details ................................................................................................................................... 36
Test requirement ................................................................................................................................... 36
Test packet structures....................................................................................................................................... 38

Annex B (informative):
B.1
B.2
B.2.1
B.2.2
B.2.3

Reference model for generating ROHC performance requirements ........ 41
Introduction...................................................................................................................................................... 41
For Voice over IP (VoIP) optimisation ............................................................................................................ 41
ROHC parameters optimisations for VoIP ................................................................................................. 41
Parameter setting for ROHC reference model for VoIP ............................................................................. 41
Setting the parameter value N in test cases for VoIP ................................................................................. 41

Annex C (informative):

Change history ............................................................................................... 42

3GPP

Release 13

6

3GPP TS 25.323 V13.0.0 (2015-12)

Foreword
This Technical Specification (TS) has been produced by the 3rd Generation Partnership Project (3GPP).

The contents of the present document are subject to continuing work within the TSG and may change following formal
TSG approval. Should the TSG modify the contents of the present document, it will be re-released by the TSG with an
identifying change of release date and an increase in version number as follows:

Version x.y.z

where:

x

the first digit:

1  presented to TSG for information;

2  presented to TSG for approval;

3  or greater indicates TSG approved document under change control.

y

the second digit is incremented for all changes of substance, i.e. technical enhancements, corrections,
updates, etc.

z

the third digit is incremented when editorial only changes have been incorporated in the document.

3GPP

Release 13

7

3GPP TS 25.323 V13.0.0 (2015-12)

1

Scope

The present document provides the description of the Packet Data Convergence Protocol (PDCP).

2

References

The following documents contain provisions which, through reference in this text, constitute provisions of the present
document.

•  References are either specific (identified by date of publication, edition number, version number, etc.) or

non-specific.

•  For a specific reference, subsequent revisions do not apply.

•  For a non-specific reference, the latest version applies. In the case of a reference to a 3GPP document (including
a GSM document), a non-specific reference implicitly refers to the latest version of that document in the same
Release as the present document.

[1]

[2]

[3]

[4]

[5]

[6]

[7]

[8]

[9]

[10]

[11]

[12]

3GPP TS 23.060: "General Packet Radio Service (GPRS); Service description; Stage 2".

3GPP TS 25.331: "Radio Resource Control (RRC); protocol specification".

3GPP TS 25.301: "Radio Interface Protocol Architecture".

3GPP TS 25.303: "Interlayer Procedures in Connected Mode".

3GPP TS 25.322: "RLC Protocol Specification".

IETF RFC 2507: "IP Header Compression".

3GPP TR 21.905: "Vocabulary for 3GPP Specifications".

IETF RFC 3095: "RObust Header Compression (ROHC): Framework and four profiles: RTP,
UDP, ESP, and uncompressed".

IETF RFC 3096: "Requirements for robust IP/UDP/RTP header compression".

IETF RFC 4815: " RObust Header Compression (ROHC): Corrections and Clarifications to RFC
3095".

3GPP TS 26.101: "Mandatory speech codec speech processing functions; Adaptive Multi-Rate
(AMR) speech codec frame structure".

3GPP TS 26.201: "Speech codec speech processing functions; Adaptive Multi-Rate - Wideband
(AMR-WB) speech codec; Frame structure".

3

Definitions and Abbreviations

3.1

Definitions

For the purposes of the present document, the terms and definitions given in [7] and the following apply.

N-context
N-context*
N-context-C
N-context-C*
N-context-C-static*

Refers collectively to both N-context-C and N-context-D.
Refers collectively to both N-context-C* and N-context-D*.
The compression context for downlink in SRNC at any given point of time.
The frozen snapshot of the compression context for downlink taken by SRNC.

N-context-D
N-context-D*

The frozen snapshot of the static part of the compression context for downlink taken by SRNC.
The decompression context for uplink in SRNC at any given point of time.
The frozen snapshot of the decompression context for uplink taken by SRNC.

3GPP

Release 13

8

3GPP TS 25.323 V13.0.0 (2015-12)

N-context-D-static*

M-context
M-context*
M-context-C
M-context-C*
M-context-C-static*

The frozen snapshot of the static part of the decompression context for uplink taken by SRNC.
Refers collectively to both M-context-C and M-context-D.
Refers collectively to both M-context-C* and M-context-D*.
The compression context for uplink in UE at any given point of time.
The frozen snapshot of the compression context for uplink taken by UE.

M-context-D
M-context-D*
M-context-D-static*

The frozen snapshot of the static part of the compression context for uplink taken by UE.
The decompression context for downlink in UE at any given point of time.
The frozen snapshot of the decompression context for downlink taken by UE.

M-HC
M-HCD
M-HD

N-HC
N-HCD
N-HD

The frozen snapshot of the static part of the decompression context for downlink taken by UE.
Entity located in the mobile terminal that performs header compression for uplink (i.e. UE PDCP)
Refers collectively to both M-HC and M-HD.
Entity located in the mobile terminal that performs header decompression for downlink (i.e. UE
PDCP)
Entity located in the network that performs header compression for downlink (i.e. RNC PDCP)
Refers collectively to N-HC and N-HD
Entity located in the network that performs header decompression for uplink (i.e. RNC PDCP)

3.2

Abbreviations

For the purposes of the present document, the following abbreviations apply:

AMR
AS
CID
C-SAP
HC
IETF
IP
L2
L3
MBMS
M-HC
M-HCD
M-HD
NAS
N-HC
N-HCD
N-HD
PDCP
PDU
PID
PPP
p-t-p
p-t-m
RB
RFC
RLC
RNC
ROHC
RTP
SDU
TCP
UDP
UE
UMTS
UTRA
UTRAN

Adaptive Multi-Rate
Access Stratum
Context Identifier
Control Service Access Point
Header Compression
Internet Engineering Task Force
Internet Protocol
Layer 2 (data link layer)
Layer 3 (network layer)
Multimedia Broadcast Multicast Service
Mobile Header Compressor
Mobile Header Compressor/Decompressor
Mobile Header Decompressor
Non Access Stratum
Network Header Compressor
Network Header Compressor/Decompressor
Network Header Decompressor
Packet Data Convergence Protocol
Protocol Data Unit
Packet Identifier
Point-to-Point Protocol
Point-to-Point
Point-to-Multipoint
Radio Bearer
Request For Comments
Radio Link Control
Radio Network Controller
RObust Header Compression
Real Time Protocol
Service Data Unit
Transmission Control Protocol
User Datagram Protocol
User Equipment
Universal Mobile Telecommunications System
UMTS Terrestrial Radio Access
UMTS Terrestrial Radio Access Network

3GPP

Release 13

9

3GPP TS 25.323 V13.0.0 (2015-12)

4

General

4.1

Objective

The present document describes the functionality of the PDCP.

4.2

Overview on sublayer architecture

Figure 1 shows the model of the PDCP within the radio interface protocol architecture. The radio interface protocol
architecture is defined in [3].

Every PS domain RAB is associated with one RB, which in turn is associated with one PDCP entity. Each PDCP entity
is associated with one or two (one for each direction) RLC entities depending on the RB characteristic (i.e.uni-
directional or bi-directional) and RLC mode. The PDCP entities are located in the PDCP sublayer.

Every PDCP entity uses zero, one or several different header compression protocols. Each individual PDCP entity uses
at most one instance of each header compression protocol. Several PDCP entities may be defined for a UE with each
using the same or a different set of header compression protocols. In this version of the specification, only two header
compression protocols, RFC 2507 [6] and ROHC [8], [10], are supported.

Every CS domain voice RAB is associated with one RB, which in turn is associated with one PDCP entity. Each PDCP
entity is associated with two UM RLC entities as CS voice RBs are always bi-directional. The PDCP entities are located
in the PDCP sublayer. The PDCP entity serving CS service does not use header compression.

The PDCP sublayer is configured by upper layer [2] through the PDCP-C-SAP.

Radio Bearers

      PDCP-SDU

PDCP-SAPs

 . . .

C-SAP

PDCP
entity

PDCP
entity

SDU
numbering

PDCP
entity

PDCP-
sublayer

HC
Protocol 1

HC
Protocol 2

HC
Protocol 1

HC
Protocol 2

HC
Protocol 1

       RLC-SDU

 . . .

 RLC

UM-SAP

AM-SAP

TM-SAP

Figure 1: PDCP structure

Figure 1 represents one possible structure for the PDCP sublayer and should not restrict implementation. A PDCP entity
is mapped to either one AM RLC entity or one or two UM or TM RLC entities. When a PDCP entity is mapped to two
UM or TM RLC entities each RLC entity is used for a different direction.

3GPP

Release 13

10

3GPP TS 25.323 V13.0.0 (2015-12)

5

Functions

PDCP provides its services to the NAS at the UE or the relay at the Radio Network Controller (RNC).

The Packet Data Convergence Protocol shall perform the following functions:

-  header compression and decompression of IP data streams (e.g., TCP/IP and RTP/UDP/IP headers for IPv4 and

IPv6) at the transmitting and receiving entity, respectively.

-

transfer of user data. This function is used for conveyance of data between users of PDCP services.

-  maintenance of PDCP sequence numbers for radio bearers that are configured to support lossless SRNS

Relocation or lossless DL RLC PDU size change.

-

transfer of CS counter if the radio bearer is connected to a CS domain radio access bearer.

-  add and remove the padding in PDCP PDU for octet alignment.

PDCP uses the services provided by the Radio Link Control (RLC) sublayer.

5.1

Header Compression

The header compression protocol is specific to the particular network layer, transport layer or upper layer protocol
combinations e.g. TCP/IP and RTP/UDP/IP. The network layer protocol type, e.g. IP or PPP, is indicated during PDP
context activation as defined in [1]. The header compression protocols and their parameters are configured by upper
layers for each PDCP entity. Compressor and decompressor initiated signalling between peer PDCP entities, during
operation, is accomplished through in-band signalling.

5.1.1  Mapping of PID values

Depending on the configuration by upper layers (i.e. PDCP PDU type to be used and header compressor protocol), the
PDCP sublayer shall be able to:

-

-

identify different types of header compression protocols;

if RFC2507:

-  distinguish different header compression protocol packet types within a header compression protocol.

The above requirements are realised by utilising the PID field in the PDCP PDU.

The mapping of the PID values shall follow the general rules listed below:

-  PID values shall be mapped to the different packet types independently at each PDCP entity;

-  PID value "0" shall indicate "no compression". PID value "0" shall be used in a PDCP PDU containing in its
Data field a PDCP SDU that is unchanged by the Sender and that shall not be decompressed by the Receiver.;

-  PID values are mapped in ascending order, starting from 1, for every configured header compression protocol, in
the order of configuration by upper layer. The first available PID value is assigned to the first packet type of the
header compression protocol as defined in the specification for this header compression protocol. PID values are
mapped for all the specified packet types defined for the header compression protocol and in the order defined in
subclause 5.1.2.2 and 5.1.3.3 for the respective header compression protocol;

-  PID values are re-mapped for the PDCP entity after any reconfiguration of the header compression protocols for

that entity.

The following table illustrates an example of the PID value mapping to the packet types when five arbitrary header
compression methods are configured for one PDCP entity: RFC 2507[6], Methods A and B, ROHC [8], [10] and
Method C. Method A, Method B and Method C are imaginary header compression protocols introduced for the purpose
of illustration.

3GPP

Release 13

11

3GPP TS 25.323 V13.0.0 (2015-12)

Table 1: Example of the PID value mapping table

Optimisation method

Packet type

No header compression
RFC 2507
RFC 2507
RFC 2507
RFC 2507
RFC 2507
Method A
Method A
Method B
Method B
RFC 3095, RFC 4815
Method C
Method C
Unassigned value

-
Full header
Compressed TCP
Compressed TCP nondelta
Compressed non TCP
Context state
Packet Type 1 of Method A
Packet Type 2 of Method A
Packet Type 1 of Method B
Packet Type 2 of Method B
ROHC packet format
Packet Type 1 of Method C
Packet Type 2 of Method C
-

PID
Value
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
10
11
12
13...31

5.1.2

IP Header Compression (RFC 2507)

The detailed operation of the RFC 2507 header compression protocol is specified in IETF RFC 2507 [6]. The
mechanisms related to error recovery and packet reordering are also described in RFC 2507. These mechanisms shall be
included in the functionality of the header compression supported by PDCP. The implementation of the RFC 2507
header compression functionality is not covered in this specification and is left to the implementation.

5.1.2.1

Context identifiers

Context identifiers for RFC 2507 shall only be included in the RFC 2507 packet types format, as defined in [6].

5.1.2.2

Mapping of PID values for RFC 2507

PID values shall be mapped to the RFC 2507 header compression packet types in the order presented in Table 2 below
where "n" is the number of PID values already mapped to other protocol packet types.

Table 2: Mapping of PID values for RFC 2507 header compression protocol

PID value
n+1
n+2
n+3
n+4
n+5

Optimisation method
RFC 2507
RFC 2507
RFC 2507
RFC 2507
RFC 2507

Packet type
Full header
Compressed TCP
Compressed TCP non-delta
Compressed non-TCP
Context state

5.1.2.3

Management of Full Header transmission

Transmission of a full header packet may be controlled by the lower layer information.

For a TCP stream, if the PDCP receives from lower layer the information of failed transmission of a single packet, the
PDCP may send the next packet as a full header.

For a non-TCP stream, if the PDCP receives from lower layer the information of successful transmission of a full
header packet, the PDCP may stop sending a full header packet that contains the same full header as the previously
transmitted one.

5.1.3

Robust Header Compression

The detailed operation of the, "RObust Header Compression (ROHC)" protocol is specified in IETF RFC 3095 [8] and
IETF RFC 4815 [10].

3GPP

Release 13

12

3GPP TS 25.323 V13.0.0 (2015-12)

5.1.3.1

Context identifiers

The context of the ROHC protocol is defined in [8] and [10]. ROHC can be configured to support one or several
contexts. Each context is identified by a value known as the context identifier (CID).

5.1.3.2

Void

5.1.3.3  Mapping of PID values

The following PID value shall be mapped to the robust header compression protocol as presented in the table where n is
the number of PID values already assigned to other protocol packet types.

Table 4: Mapping of PID values for RFC 3905 header compression protocol

PID value
n+1

Optimisation method
RFC 3095, RFC 4815

Packet type
ROHC packet format

5.1.3.4

Void

5.1.3.5

Protocol Parameters

ROHC has two types of parameters [8], [10]:

-  configuration parameters: these are mandatory and must be configured between compressor and decompressor

peers.

-

implementation parameters: these are optional and, when used, stipulate how the compression protocol operates.

These parameters are categorized in four different groups, as defined below:

-  M: Mandatory and configured by upper layers.

-  MO: Parameters that must be supported and when used can only be configured or triggered by upper layers.

-  O: Optional parameters that are not configured by upper layers. They may be used locally (i.e. UTRAN and/or in

UE).

-  N/A: These are not used in ROHC.

The usage and definition of the parameters shall be as specified below.

-  MAX_CID (M): This is the maximum CID value that can be used. One CID value shall always be reserved for

uncompressed flows.

-  LARGE_CIDS: This is not configured by upper layers but inferred from the configured value of MAX_CID

according to the following rule:

If MAX_CID > 15 then LARGE_CIDS = TRUE else LARGE_CIDS = FALSE.

-  PROFILES (M): Profiles are used to define which profiles are allowed to be used by the UE in uplink. In

downlink, all the profiles defined in [8] shall be supported.

-  FEEDBACK_FOR (N/A):

-  MRRU (M): Segmentation is not used by default.

-  NO_OF_PACKET_SIZES_ALLOWED (N/A).

-  PACKET_SIZES_ALLOWED (N/A)

-  PAYLOAD_SIZES (O).

-  NO_OF_PACKET_SIZES_USED (O).

3GPP

Release 13

13

3GPP TS 25.323 V13.0.0 (2015-12)

-  PACKET_SIZES_USED (O).

-  CONTEXT_REINITIALIZATION (MO).

-  MODE (O).

-  CLOCK_RESOLUTION (O).

-  REVERSE_DECOMPRESSION_DEPTH (M): Default value is that reverse decompression is not used.

5.1.3.6

Configuration by RRC

If the variable "PDCP_ROHC_TARGET_MODE" [2] is stored in the UE, and if applicable for the ROHC profile
applied, the de-compressor shall only perform the operational state transitions defined in [8] to the stored mode.

If the variable "PDCP_ROHC_TARGET_MODE" [2] is not stored in the UE, the de-compressor shall not restrict the
operational state transitions defined in [8].

5.2

Void

5.3

Data Transfer

If header compression is configured the PDCP entity in the Sender shall:

-  perform header compression upon reception of a PDCP SDU from upper layers;

-

if the radio bearer is configured for lossless SRNS Relocation or lossless DL RLC PDU size change:

-  maintain PDCP sequence numbering as specified in subclause 5.6.1.1;

-

submit the PDCP PDU to lower layer in the sequence received from the upper layer.

If radio bearer is connected to a CS domain radio access bearer, the sender shall:

-

if the PDCP SDU length is of 1 or more bits:

-

-

-

include the CS counter in the PDCP AMR Data PDU as specified in subclause 5.6.1.4;

indicate the PDCP AMR PDU type in the PDU type field;

fill the data field of the  PDCP AMR PDU type with the PDCP SDU and add padding bits as specified in
subclause 8.2.4.

NOTE:

If no AMR or AMR WB frames is generated by upper layers, no PDCP PDU is submitted to the lower
layer.

When the PDCP entity at the Receiver receives the PDCP PDU from lower layers, it shall:

-

if the received PDCP PDU is of type PDCP AMR Data PDU:

-

the PDCP SDU is derived from the data field of the PDCP AMR Data PDU. The receiver determines the bit
aligned data content and Frame Type from the PDU Data field length, as possible AMR and AMR WB
payload has a unique size when being octet aligned;

-  deliver the PDCP SDU and CS counter from the received PDCP header to the upper layer.

-  else:

-  perform header decompression (if header compression is configured) of the PDCP PDU to obtain the PDCP

SDU; and

-  deliver the PDCP SDU to the upper layer in the order received from the lower layer;

3GPP

Release 13

14

3GPP TS 25.323 V13.0.0 (2015-12)

-

if the received PDCP PDU is of type PDCP SeqNum PDU:

-

follow the procedure in subclause 5.6.1.2.

5.3.1

Data transfer over acknowledged mode RLC

Figure 2 shows the PDCP data transfer over acknowledged mode RLC.

Originator

Receiver

PDCP user

PDCP

RLC

RLC

PDCP

PDCP user

PDCP-DATA.req

RLC-AM-DATA.req

...

Acknowledgement

RLC-AM-DATA.ind

RLC-AM-DATA.cnf
(NOTE)

PDCP-DATA.ind

Figure 2: PDCP data transfer over acknowledged mode RLC

NOTE:

If the primitive RLC-AM-DATA.req is used with parameter CNF, the primitive RLC-AM-DATA.cnf is
delivered. Otherwise, this primitive is not delivered.

5.3.2

Data transfer over unacknowledged and transparent mode RLC

Figure 3 shows the PDCP data transfer over unacknowledged or transparent mode RLC.

Sender

Receiver

PDCP user

PDCP

RLC

RLC

PDCP

PDCP user

PDCP-DATA.req

RLC-UM-DATA.req/
RLC-TM-DATA.req

RLC-UM-DATA.ind/
RLC-TM-DATA.ind

PDCP-DATA.ind

Figure 3: PDCP data transfer over unacknowledged or transparent mode RLC

5.4

SRNS Relocation

In case of SRNS Relocation upper layer indicates to PDCP to perform either the re-initialisation or the context
relocation of compression protocols of an RB, or the release of the compression protocols of an RB. In this version of
the specification, context relocation is only applicable to RFC3095. Each of the compression protocols is handled
independently, but the context relocation capability is optional for the UE and it is indicated as a part of the UE radio
access capabilities.

The re-initialisation of a given compression protocol entails the following:

-  Compression parameters may be reconfigured by upper layers during re-initialisation, otherwise compression

parameters remain valid during re-initialisation.

-  All compression state information is initialised, e.g. header compression contexts. Therefore, the first

'compressed' packet type after SRNS Relocation is a full header.

3GPP

Release 13

15

3GPP TS 25.323 V13.0.0 (2015-12)

-  The PDCP sequence numbers are not changed due to the PDCP header compression protocol re-initialisation.

The context relocation of a given compression protocol entails the following:

-  Configured compression parameters remain valid during context relocation.

-  A snapshot of the compression state information (context) is taken in the source RNC and transferred to the

target RNC, which initialises the header compression protocol according to the transferred snapshot. Therefore,
the (de)compression continues after SRNS Relocation from the context used before relocation.

-  Some additional specific actions are performed both in UE and UTRAN during the SRNS Relocation in order to

keep the (de)compressors consistent.

5.4.1

Lossless SRNS Relocation

Lossless SRNS Relocation is only applicable when RLC is configured for in-sequence delivery and acknowledged
mode. The support of lossless SRNS Relocation is configured by upper layer.

For the support of lossless SRNS Relocation, the PDCP entities maintain sequence numbers for PDCP SDUs, as
described in subclause 5.6.1.1.

These sequence numbers are synchronised between PDCP Sender and Receiver, as described in subclause 5.6.1.2.

When a lossless SRNS Relocation is performed sequence numbers are exchanged between UE and UTRAN. They are
used to confirm PDCP SDUs transmitted but not yet acknowledged by the Receiver, as described in subclause 5.6.1.3.
After relocation the data transfer begins with the first unconfirmed PDCP SDU.

5.4.1.1  Void

5.4.1.2  Void

5.4.1.3  Void

5.4.2

Context relocation

The header compression context relocation is performed by the decision of upper layers in source RNC based on the UE
radio capabilities. The decision is done independently every time the SRNS relocation occurs and is specific for each
header compression protocol. It is indicated to UE as a part of the SRNS relocation signalling of the upper layer and the
selected relocation method is configured to UE PDCP by the upper layer.

The header compression context relocation shall not be performed if the radio bearer is configured to support the
lossless SRNS Relocation.

In the UE, upon reception of the indication about SRNS relocation being performed:

-

the upper layer configures PDCP (CPDCP-CONFIG.Req) to perform either re-initialisation (R) or the context
relocation (C) of header compression protocols;

-

if the context relocation is to be applied for RFC3095 header compression protocol:

-

if the compressor (M-HC) is operating in R mode:

-  uplink data may be compressed and transmitted normally.

-

if the compressor (M-HC) is operating in O mode:

-  compress and transmit uplink data as specified in [8] using the assumption that all ROHC uplink packets
transmitted are likely to be lost. When SRNS relocation is completed, M-HC should return to normal
operation.

3GPP

Release 13

16

3GPP TS 25.323 V13.0.0 (2015-12)

NOTE:  When the M-HC is using the assumption that all ROHC uplink packets transmitted are likely to

be lost:
-

the M-HC can not transit to a higher compression state;

-

for W-LSB encoding, the M-HC updates the set of candidate reference values used by the
decompressor by adding newly transmitted values but not removing old values.

-

if the compressor (M-HC) is operating in U mode:

-  M-HC shall transit to FO state and send IR-DYN to re-synchronise the dynamic part of the uplink

context.

-

if the reverse decompression is applied in the decompressor (M-HD):

-flush the reverse decompression buffer by discarding all packets in the buffer.

-

in the decompressor (M-HD), in all modes:

-  downlink data may be received and decompressed normally.

In the UTRAN source RNC, while SRNS relocation is being performed:

-

if the context relocation is to be applied for RFC3095 header compression protocol:

-  PDCP is requested to take a context snapshot by the upper layer (CPDCP-CONTEXT.Req);

-

if the compressor (source N-HC) is operating in R mode:

-

the source N-HC should take a snapshot of its header compression compressor context (denoted N-
context-C*);

-  header compression contexts should not be updated anymore even though downlink data may be
compressed and transmitted otherwise normally. This can be done by sending R-1* packets.

-

if the compressor (source N-HC) is operating in O mode:

-

the source N-HC should take a snapshot of its header compression compressor context (denoted N-
context-C*);

-  after the snapshot is taken, the source N-HC should only send UO-0 or UO-1* packets. This means only
RTP SN, RTP TS, and IP-ID (for IPv4 only) fields are updated in the decompressor context at M-HD.

-

if the compressor (source N-HC) is operating in U mode:

-

the source N-HC should take a snapshot of the static part of its header compression compressor context
(denoted N-context-C-static*).

-

if the decompressor (source N-HD) is operating in R or O mode:

-

if the source N-HD is sure about the integrity of the N-context-D:

-

the source N-HD should take a snapshot of its header compression decompressor context (denoted as
N-context-D*).

-

if the source N-HD is only sure about the integrity of the static part of the N-context-D (e.g. due to
multiple detected errors):

-

the source N-HD should take a snapshot only of the static part of the N-context-D (denoted as N-
context-D-static*).

-  RFC3095 acknowledgments should not be generated anymore even though uplink data may be received

and decompressed otherwise normally.

-

if the decompressor (source N-HD) is operating in U mode:

-

the source N-HD should take a snapshot of the static part of its header compression decompressor context
(denoted N-context-D-static*).

3GPP

Release 13

17

3GPP TS 25.323 V13.0.0 (2015-12)

-  either N-context-C* or N-context-C-static* and either N-context-D* or N-context-D-static* should be

delivered to the upper layer as Context-Info (CPDCP-CONTEXT.Conf), which is to be transmitted further to
the target RNC.

In the UTRAN target RNC, while SRNS relocation is being performed:

-

-

-

the upper layer configures PDCP (CPDCP-CONFIG.Req) to perform either initialisation (I) or the context
relocation (C) of header compression protocols;

the new header compression entity should be created;

if the context relocation is to be applied for RFC3095 header compression protocol:

-

in the compressor (target N-HC), in all modes:

-

-

the header compression compressor (target N-HC) should be initialised to the same mode as used in the
source N-HC using N-context-C* as the initial header compression compressor context;

in addition, if the source N-HC was operating in U-mode, the target N-HC should first send IR-DYN to
resynchronise the dynamic part of the downlink context.

-

in the decompressor (target N-HD), in all modes:

-

if Context-Info carries N-context-D*:

-

the header compression decompressor (target N-HD) should be initialised to the same mode as used in
the source N-HD using N-context-D* as the initial header compression decompressor context.

-

if Context-Info carries N-context-D-static*:

-

the header compression decompressor (target N-HD) should be initialised to the same mode as used in
the source N-HD using N-context-D-static* as the initial header compression decompressor context;

-

the target N-HD should send a request for IR-DYN.

5.5

Lossless DL RLC PDU size change

Lossless DL RLC PDU size change is only applicable when RLC is configured for in-sequence delivery and
acknowledged mode. The support of lossless DL RLC PDU size change is configured by upper layer.

For the support of lossless DL RLC PDU size change, the PDCP entities maintain sequence numbers for DL PDCP
SDUs, as described in subclause 5.6.1.1.

These DL sequence numbers are synchronised between PDCP Sender in the UTRAN and Receiver in the UE, as
described in subclause 5.6.1.2.

When a lossless DL RLC PDU size change is performed the next expected DL_Receive PDCP SN is sent from the UE
to the UTRAN. It is used to confirm DL PDCP SDUs transmitted but not yet acknowledged by the Receiver in the UE,
as described in subclause 5.6.1.3. After lossless DL RLC PDU size change the data transfer begins with the first
unconfirmed DL PDCP SDU.

5.6

General procedures

5.6.1.1

PDCP Sequence Numbering

The value of the PDCP sequence number ranges from 0 to 65535. The PDCP SN window size indicates the maximum
number of PDCP SDUs, not confirmed to have been successfully transmitted to the peer entity by lower layer, that can
be numbered at any given time. The PDCP SN window size is configured by upper layers. PDCP sequence numbers are
set to "0" when the PDCP entity is set-up for the first time.

In the following the "submission/reception of a PDCP SDU to/from lower layer" is used as a synonym for the
submission/reception of a PDCP Data PDU or a PDCP SeqNum PDU to/from lower layer that carries in its Data field a
compressed or uncompressed PDCP SDU.

3GPP

Release 13

18

3GPP TS 25.323 V13.0.0 (2015-12)

If lossless SRNS relocation and/or lossless DL RLC PDU size change are/is supported by the UE, for each radio bearer
configured to support "lossless SRNS relocation or lossless DL RLC PDU size change" as specified in [1], PDCP
sequence numbers are applied:

-

in the UE:

-

-

the DL_Receive PDCP SN shall be set to "0" for the first PDCP SDU received from lower layer;

the DL_Receive PDCP SN shall be incremented by "1" for the next PDCP SDU received from lower layer.

-

in the UTRAN:

-

-

the DL_Send PDCP SN should be set to "0" for the first PDCP SDU submitted to lower layer;

the DL_Send PDCP SN should be incremented by "1" for the next PDCP SDU submitted to lower layer.

Additionally, if lossless SRNS relocation is supported by the UE, for each radio bearer configured to support "lossless
SRNS relocation or lossless DL RLC PDU size change" as specified in [1], PDCP sequence numbers are applied:

-

in the UE:

-

-

the UL_Send PDCP SN shall be set to "0" for the first PDCP SDU submitted to lower layer;

the UL_Send PDCP SN shall be incremented by "1" for the next PDCP SDU submitted to lower layer;

-

in the UTRAN:

-

-

the UL_Receive PDCP SN should be set to "0" for the first PDCP SDU received from lower layer;

the UL_Receive PDCP SN should be incremented by "1" for the next PDCP SDU received from lower layer.

PDCP sequence numbers shall not be decremented in a PDCP entity.

5.6.1.2

PDCP Sequence Number synchronization

For radio bearers that are configured to support "lossless SRNS Relocation or lossless DL RLC PDU size change" as
specified in [1]:

the UE PDCP entity shall:

-

if the UE supports lossless SRNS relocation,

-

-

if a PDCP entity has to synchronise the UL PDCP SN following a RLC reset or RLC transmitting side re-
establishment not caused by a lossless SRNS Relocation; or

if the UE PDCP entity receives an invalid "next expected UL Receive PDCP SN" from upper layer after a
lossless SRNS Relocation;

-

trigger the PDCP SN synchronisation procedure by submitting one PDCP SeqNum PDU to lower layer;

-  consider that the synchronisation procedure is complete on confirmation by lower layer of the successful

transmission of the PDCP SeqNum PDU.

-

if the UE supports lossless DL RLC PDU size change but not lossless SRNS relocation, the UE PDCP entity
shall not submit PDCP SeqNum PDU to lower layer.

- the UTRAN PDCP entity should:

-

-

if a PDCP entity has to synchronise the DL PDCP SN following a RLC reset or RLC transmitting side re-
establishment not caused by a lossless SRNS Relocation or a lossless DL RLC size change; or

if the UTRAN PDCP entity receives an invalid "next expected DL_Receive PDCP SN" from upper layer after
lossless SRNS Relocation or lossless DL RLC PDU size change:

-

trigger the PDCP SN synchronisation procedure by submitting one PDCP SeqNum PDU to lower layer;

-  consider that the synchronisation procedure is complete on confirmation by lower layer of the successful

transmission of the PDCP SeqNum PDU.

3GPP

Release 13

19

3GPP TS 25.323 V13.0.0 (2015-12)

In the UE/UTRAN, the "next expected UL/DL_Receive PDCP SN" is considered invalid if its value is less than the
UL/DL_Send PDCP SN of the first transmitted but not yet acknowledged PDCP SDU or greater than that of the first
unsent PDCP SDU.

On receiving a PDCP SeqNum PDU:

-

the UE PDCP entity shall:

-

set the value of the DL_Receive PDCP SN to the value indicated in the PDCP SeqNum PDU;

-

the UTRAN PDCP entity should:

-

set the value of the UL_Receive PDCP SN to the value indicated in the PDCP SeqNum PDU.

NOTE:

If UTRAN has the intention to use only the lossless DL RLC PDU size change, UTRAN may not
maintain UL PDCP SN. In this case, UTRAN should still transfer the user data to upper layer.

5.6.1.3

Sequence Number and Data Forwarding

In case of a lossless SRNS Relocation procedure or lossless DL RLC size change, as described in [1]:

-

the UE shall send to the UTRAN the next expected DL_Receive PDCP SN.

Additionally, in case of lossless SRNS relocation procedure, as described in [1]:

-

the UTRAN should send to the UE the next expected UL_Receive PDCP SN.

This information exchange synchronises the Sequence Numbers at the UE and UTRAN PDCP entities.

When requested by the upper layer, for each radio bearer configured to support lossless SRNS Relocation, the PDCP
sublayer in the source RNC should forward the following to the target RNC:

-

-

-

-

the UL_Receive PDCP SN of the next PDCP SDU expected to be received from the UE;

the DL_Send PDCP SN of the first transmitted but not yet acknowledged PDCP SDU;

the transmitted but not yet acknowledged PDCP SDUs together with their related DL_Send PDCP SNs;

the not yet transmitted PDCP SDUs.

5.6.1.4

CS Counter Handling

In case the radio bearer is connected to a CS domain radio access bearer, the CS counter shall be included in the PDCP
AMR Data PDU.

The value of the CS counter shall be set to the first to fifth LSBs of the CFN at which the packet has been received from
higher layers.

In the receiving side, the CS counter shall be delivered to the upper layer together with the PDCP SDU.

The CS counter is used to manage the delay jitter generated by the radio layer. The CS counter plus the value of the
information element "Max CS delay", as signalled in [2], indicates the latest instance at which the AMR or AMR WB
frames is delivered to the upper layer.

5.7

Header Compression and Decompression for MBMS

Header compression and decompression for a p-t-m MBMS service is performed in ROHC U-mode.

Applying ROHC for p-t-m RB configuration is optional and should be configured per MBMS session.

5.7.1

Cell change inside the same cell group

When a UE moves to a cell that is the same cell group with that of the previous cell while reciving a p-t-m MBMS
service which is provided in both cells, the UE shall:

-  continue header decompression during and after cell change.

3GPP

Release 13

20

3GPP TS 25.323 V13.0.0 (2015-12)

5.7.2

Cell change between cell groups

When a UE moves to a cell that is the different cell group with that of the previous cell while reciving a p-t-m MBMS
service which is provided in both cells, the UE shall:

-

-

-

reconfigure and re-initialise the PDCP entity;

reuse the static part of the header decompressor context used in the previous cell;

re-initialise header decompression after receiving IR-DYN or IR packet and correcting the CID of the context
with the CID being used in the new cell.

NOTE:  How to correct CID is implementation issue and is not specified.

6

Services

6.1

Services provided to upper layers

The following services are provided by PDCP to upper layers:

-

transfer of user data;

-  maintenance of PDCP SDU sequence numbers.

6.2

Services expected from RLC layer

For a detailed description of the following functions see [5].

-

transparent data transfer Service;

-  unacknowledged data transfer Service;

-  acknowledged data transfer Service.

7

Elements for layer-to-layer communication

The interaction between the PDCP layer and other layers are described in terms of primitives where the primitives
represent the logical exchange of information and control between the PDCP layer and other layers. The primitives shall
not specify or constrain implementations.

7.1

Primitives between PDCP and upper layers

The primitives between PDCP and upper layers are shown in Table 5.

Table 5: Primitives between PDCP and upper layers

Generic Name

PDCP-DATA
CPDCP-CONFIG

CPDCP-CONTEXT
CPDCP-RELEASE
CPDCP-SN
CPDCP-RELOC

Req.
Data
PDCP-Info, RLC-SAP
SN_Sync, R/I/C/RS,
Context-Info, PDCP
Unrecoverable Error
Detection
None
RLC-SAP
PDCP SN
Next_Receive_SN

Each Primitive is defined as follows:

Parameter

Ind.
Data, CS Counter
Not Defined

Resp.
Not Defined
Not Defined

Conf.
Not Defined
Not Defined

Not Defined
Not Defined
Not Defined
Not Defined

Not Defined
Not Defined
Not Defined
Not Defined

Context-Info
Not Defined
Not Defined
Next_Receive_SN,
Next_Send_SN

3GPP

Release 13

21

3GPP TS 25.323 V13.0.0 (2015-12)

a)  PDCP-DATA-Req./Ind.

-  PDCP-DATA-Req is used by upper user-plane protocol layers to request a transmission of upper layer PDU.
PDCP-DATA-Ind is used to deliver PDCP SDU that has been received to upper user plane protocol layers.

b)  CPDCP-CONFIG-Req.

-  CPDCP-CONFIG-Req is used to configure and – in case of already existing PDCP entity – to reconfigure a

PDCP entity and to assign it to the radio bearer associated with that entity.

c)  CPDCP-RELEASE-Req.

-  CPDCP-RELEASE-Req is used by upper layers to release a PDCP entity.

d)  CPDCP-SN-Req.

-  This primitive is used at the UTRAN. CPDCP-SN-Req is used to transfer the PDCP SN to PDCP.

e)  CPDCP-RELOC-Req/Conf.

-  CPDCP-RELOC-Req initiates the SRNS Relocation procedure in PDCP for those radio bearers that are
configured to support lossless SRNS Relocation. The Next_Receive_SN is only included at the UE side.

-  CPDCP-RELOC-Conf is used to transfer the Next_Receive_SN and/or Next_Send_SN to upper layers for

lossless SRNS Relocation. The Next_Send_SN is only included at the source RNC.

f)  CPDCP-CONTEXT-Req./Conf.

-  CPDCP-CONTEXT-Req initiates specific actions in the source RNC in order to perform context relocation

as a part of the SRNS relocation. The primitive is applicable only in the source RNC.

-  CPDCP-CONTEXT-Conf is used to transfer the header compression context information from PDCP to
upper layer in order to perform context relocation as a part of the SRNS relocation. The primitive is
applicable only in the source RNC.

The following parameters are used in the primitives:

1)  PDCP-Info:

-  Contains the parameters for each of the header compression protocols configured to be used by one PDCP

entity.

2)  RLC-SAP:

-  The RLC-SAP (TM/UM/AM) used by PDCP entity when communicating with RLC sublayer.

3)  SN_Sync:

-

Indicates that PDCP should start PDCP SN synchronisation procedure.

4)  Next_Send_SN:

-  The Send PDCP SN of the next PDCP SDU to be sent. There is one in the uplink (UL_Send PDCP SN) and

one in the downlink (DL_Send PDCP SN). Refer to subclause 5.4.1.

5)  Next_Receive_SN:

-  The Receive PDCP SN of the next PDCP SDU expected to be received. There is one in the uplink

(UL_Receive PDCP SN) and one in the downlink (DL_Receive PDCP SN). Refer to subclause 5.4.1.

6)  PDCP SN:

-  This includes a PDCP sequence number.

7)  R/I/C/RS

-

Indicates that PDCP should Re-initialise (R)/Initialise (I) the header compression protocols. Alternatively
(Context-relocation, C) it indicates that UE PDCP shall perform specific actions related to context relocation

3GPP

Release 13

22

3GPP TS 25.323 V13.0.0 (2015-12)

during SRNS relocation. (RS) indicates to Re-initialise while keeping the static part of the header
compression (only for ROHC). R/I/C/RS indication is given separately for each of the configured header
compression protocol, if several exist for a given radio bearer.

8)  Context-Info:

-  Contains the header compression context information of each of the header compression protocols that are

subject to the context relocation during SRNS relocation.

9)  CS Counter:

-  Contains the timing information of AMR or AMR WB frame that will be used by upper layer.

10) PDCP Unrecoverable Error Detection:

-  Determines whether PDCP Unrecoverable Error Detection shall be performed in a PDCP entity.

8

Elements for peer-to-peer communication

8.1

Protocol data units

Different PDU formats are defined for the PDCP protocol, one not introducing any overhead to the (compressed) PDCP
SDU, others introducing such overhead.

8.2

Formats

A PDCP PDU shall be a multiple of 8 bits, if the RLC entity is configured for unacknowledged or acknowledged mode.
Otherwise, if the RLC entity is configured for transparent mode, it is bit-aligned. In Tables 6, 7 and 8, bit strings are
represented as follows: the first bit is the leftmost one on the first line of the table, the last bit is the rightmost on the last
line of the table, and more generally the bit string is to be read from left to right and then in the reading order of the
lines.

SDUs are bit strings, with any non-null length. If not compressed within PDCP an SDU is included from first bit
onward.

8.2.1

PDCP-No-Header PDU

The PDCP-No-Header PDU does not introduce any overhead to the PDCP SDU. The use of the PDCP-No-Header PDU
is configured by the upper layer.

The format of the PDCP-No-Header PDU is shown in Table 6.

Table 6: PDCP-No-Header PDU

Data

8.2.2

PDCP Data PDU

The PDCP Data PDU is used to convey:

-  data containing an uncompressed PDCP SDU; or

-  header compression related control signalling; or

-  data that has been obtained from PDCP SDU after header compression.

The format of the PDCP Data PDU is shown in Table 7.

3GPP

Release 13

23

3GPP TS 25.323 V13.0.0 (2015-12)

Table 7: PDCP Data PDU format

PDU type

PID

Data

8.2.3

PDCP SeqNum PDU

The PDCP SeqNum PDU is used to convey a PDCP SDU sequence number and:

-  data containing an uncompressed PDCP SDU; or

-  data that has been obtained from PDCP SDU after header compression.

The format of the PDCP SeqNum PDU is shown in Table 8.

Table 8: PDCP SeqNum PDU format

PDU type

PID
Sequence number

Data

8.2.4

PDCP AMR Data PDU

The PDCP AMR Data PDU is used to convey:

-  a PDCP SDU containing AMR or AMR WB frame

The format of the PDCP AMR Data PDU is shown in Table 9.

Table 9: PDCP AMR Data PDU format

PDU type

CS counter

Data

The PDCP PDU is octet aligned but the actual PDCP SDU carrying the AMR or AMR WB frame may not be octet
aligned. The data field contains the "AMR Core Frame" of AMR IF1 as defined in [11] or "AMR-WB Core Frame" of
AMR-WB IF1 as defined in [12]. The AMR classes are always encoded in the order of class A, B and C, where d(0) of
the "AMR Core Frame" or "AMR-WB Core Frame" is carried in the first bit of data field. Any padding for octet
alignment is inserted at the end of the data field.

8.3

Parameters

If not otherwise mentioned in the definition of each field then the bits in the parameters shall be interpreted as follows:
the left most bit string is the first and most significant and the right most bit is the last and least significant bit.

Unless otherwise mentioned, integers are encoded in standard binary encoding for unsigned integers. In all cases the
bits appear ordered from MSB to LSB when read in the PDU.

8.3.1

PDU Type

Length: 3 bits.

The PDU type field indicates the PDCP Data PDU type.

3GPP

Release 13

24

3GPP TS 25.323 V13.0.0 (2015-12)

Bit
000
001
010
011-111

PDU Type

PDCP Data PDU (Table 7)
PDCP SeqNum PDU (Table 8)
PDCP AMR Data PDU (Table 9)
Reserved (PDUs with this encoding are invalid for this version of the
protocol)

8.3.2

PID

Length: 5 bits.

The PID field indicates the used header compression and packet type.

Bit
00000

No header compression

Description

00001-11111  Dynamically negotiated header compression identifier, as described

in subclause 5.1.1

The PID field value indicates the used header compression protocol type and packet type. A specific header
compression protocol may utilize a certain range of consecutive values from the PID field value space for different
packet types. The Receiving PDCP entity performs the necessary operation (e.g. header decompression) according to
the PID field value.

8.3.3

Data

The Data field may include either one of the following:

-  Uncompressed PDCP SDU;

-  Header compressed PDCP SDU;

-  Header compression protocol feedback information.

8.3.4

Sequence number

Length: 16 bits

PDCP SDU sequence number.

8.3.5

CS counter

Length: 5 bits

CS counter field value indicates the timing of AMR or AMR WB frame.

9

Handling of unknown, unforeseen and erroneous
protocol data

9.1

Invalid PDU type

If a PDCP entity receives a PDCP PDU with a PDU Type set to Reserved (see subclause 8.3.1), it shall:

-  discard the PDCP PDU.

If a PDCP entity is not configured for lossless SRNS Relocation or lossless DL RLC PDU size change and receives a
PDCP SeqNum PDU, it shall:

-  discard the PDCP SeqNum PDU.

3GPP

Release 13

25

3GPP TS 25.323 V13.0.0 (2015-12)

9.2

Invalid PID value

If a PDCP entity receives a PDCP PDU with a PID value that is not mapped with a valid packet type (see subclause
5.1.1), it shall:

-  discard the PDCP PDU.

9.3

PDCP Unrecoverable Error Detection

For each radio bearer that is configured to perform PDCP Unrecoverable Error Detection:

-

if the PDCP entity receives 2 or 3 consecutive PDCP PDUs with an unexpected or invalid PDU Type or PID
value:

-

the UE PDCP entity may indicate PDCP Unrecoverable Error to upper layer [2].

-

if the PDCP entity receives 4 consecutive PDCP PDUs with an unexpected or invalid PDU Type or PID value:

-

the UE PDCP entity shall indicate PDCP Unrecoverable Error to upper layer [2].

NOTE1:  Until the UE receives 4 consecutive PDCP PDUs with an unexpected or invalid PDU Type or PID value,

the UE may apply a self-recovery mechanism. For example, the UE PDCP entity may indicate to RLC
layer that HFN can be incremented.

NOTE2:  The PDCP unrecoverable error detection is performed before the invalid PDU type check specified in

subclause 9.1.

NOTE3:  PDCP unrecoverable error detection in the UE can only detect the problem in the downlink.

3GPP

Release 13

26

3GPP TS 25.323 V13.0.0 (2015-12)

Annex A (normative):
ROHC performance testing

A.1

Introduction

This subclause defines performance test cases for ROHC. The ROHC profile within scope is profile 0x0001 for
compression of RTP/UDP/IP headers only. This subclause is not meant to bring incoherent limitations to
implementations, and is not meant to create a sub-specification of [8], [10] either, as a consequence of the requirements
on performance that it defines.

A.1.1

Purpose of the performance testing

The purpose of the test cases is to ensure that ROHC implementations meet minimal requirements that can fairly be
expected when subjected to an input sequence that includes frequently occurring and commonly observed changes in
the values of header fields. The metrics used correspond to:

-

-

the average compressed header size for an entire test sequence, to assess an implementation’s efficiency in
terms of its overall compression ratio, and

the average compressed header size for different sub-sequences within each test case, to assess an
implementation’s ability to minimize the variance in compressed header size with respect to the selection of
the packet format used for individual packets.

The latter is to avoid a less desirable behaviour where a compressor would consistently and exclusively use two types of
compressed header formats; one format that offers no compression but that completely updates and/or repairs the
context e.g. when the patterns of the header fields to be compressed do not allow optimal compression, and another
format that provides the most efficient compression ratio otherwise. While it is noted that the use of larger headers is
perfectly acceptable protocol-wise [8], the tests herein are meant to encourage compressor implementations to actively
and efficiently implement compression.

These metrics are defined so that they are not impacted by an implementation’s specific robustness algorithm(s) as well
as to allow a wide range of compression strategies.

Compressor implementations are expected to implement robustness algorithms according to the optimistic approach for
the U/O-modes of operation. The optimistic approach is the part of the selection of the packet format where a format
that contains the necessary information to update a field is used a number N time, starting from the packet for which a
new value has to be established in the decompressor context. While N is an implementation parameter, the metrics for
each sequence in U/O-mode is expressed in terms of this parameter. Implementation should use the value N as an input
parameter for the testing, to adapt to the expected robustness level required for the testing. The value of the parameter N
is defined in test case definition separately (informative value is given in Annex B.2.3.). Similarly, R-mode operation
requires that an update be conveyed to the decompressor until it gets acknowledged; however for R-mode, relevant test
cases provide explicit feedback messages when necessary.

The performance tests for ROHC as described in this subclause are carried out by providing a sequence of
uncompressed IP/UDP/RTP packets to the ROHC RTP compressor, together with  artificially generated feedback
messages that are synchronized with the packet sequence. All packets in these sequences are built on the same base
structure, with most field values being constant. The performance test cases define different change patterns for three
specific fields: the IPv4 IP ID, the RTP SN, and the RTP TS.

A.1.2

Input sequence for uncompressed headers

The structure of the IPv4/UDP/RTP header and IPv6/UDP/RTP header is outlined in annex A.3, along with tables of the
values to be used for each field. Fields with values marked ANY can have any value;, these are the addressing fields
that uniquely identify the flow of packets being compressed and their respective value does not otherwise affect the
expected compression ratio as they are either sent in uncompressed form or completely omitted in compressed packets.
The checksum values are dependent on the entire content of the packet and are calculated according to their respective
protocol specifications, RFC 768 and RFC 791, which are referred to in the tables. For the input sequence, the UDP
checksum with IPv4 shall always be enabled and thus have a non-zero value, i.e the two octets of the UDP checksum
are always included as part of the calculation of the compressed header size for both IPv4 and IPv6. Each test sequence
defines specific values to create varying change patterns for the IPv4 IP ID, the RTP SN, and the RTP TS. A dummy
payload of an arbitrary non-zero value shall be appended at the end of the header data, following the RTP header.

3GPP

Release 13

27

3GPP TS 25.323 V13.0.0 (2015-12)

The outline of each test case follows the same format with respect to the input sequences and the requirements. Test 1a
and 1b are base tests using a well-behaving flow of packets as one of the inputs. All subsequent tests are based on test
1a or test 1b, each with specific test events added to the packet flow of the base tests.

A.1.3

Feedback format for the test cases

The feedback messages used in the test cases, when applicable, are artificially generated and interspersed with the input
sequence of uncompressed packets.  Feedback messages are generated according to the following format:

     0   1   2   3   4   5   6   7
   | 1   1   1   1   0 |   Code    |  feedback type octet
   +---+--e| Mode  |      SN       |
   +---+---+---+---N               |
   +---+---+---+---+---+---+ 0   1 |
   +---+---+---+---+---+---+---+---+
   +---+---+---+---+---+---+---+---+

Where:

-eedback data above the type octet is 4 octets)

-  Acktype is set to 0x0 (means ACK)

-  Mode is set as defined by the test case

-  SN is set as defined by the test case

-  CRC is the 8-bit CRC computed over the entire feedback payload including any CID fields but excluding the

packet type, the 'Size' field and the 'Code' octet, using the polynomial defined in [8], [10].

NOTE:

If compressor uses CID field in compressed packet, the CID field should be included in the feedback
packet and the Code and CID should be set as defined in [8].

A.1.4

Feedback generation for test cases (R-mode only)

This subclause defines a mechanism by which the test equipment shall dynamically generate feedback messages for
each test case, once a transition to R-mode has been initiated and for the entire R-mode operation thereafter. Test cases
may define additional feedback messages as input to the compressor.

The test equipment shall generate a feedback message when the ROHC packet type octet of the received compressed
header matches any of the values as described in the table A.1.4. The compressed header type can be identified by
inspecting the packet type octet of the compressed header, i.e. the first octet of the ROHC base header [8].

Table A.1.4: Bitmasks for feedback generation

Compressed Header
Type (binary mask)

01xxxxxx
110xxxxx
1111110x

IR-DYN

Other values

Packet Type

Outcome

R-0-CRC
UOR-2*
IR
Send feedback
Other packets

Send feedback
Send feedback
Send feedback

No feedback

11111000

where 'x' means 'any value'.

The feedback message shall be of the format as described in subclause A.1.3 using:

-  Mode is set to 0x3 (means R-mode)

-  SN is set to the RTP SN corresponding to the received compressed header.

The test equipment shall index the input sequence of uncompressed headers using the RTP Sequence Number, and it
shall associate the correct RTP SN to each compressed header that it receives back from the compressor. The test
equipment can derive the RTP SN by counting the number of received compressed headers.

3GPP

Release 13

28

3GPP TS 25.323 V13.0.0 (2015-12)

NOTE:  The purpose of this mechanism is only to provide feedback to the compressor when operating in R-mode;

it is not meant to make further verifications of any specific ROHC functionality and applies only to the
test cases defined in this annex.

A.1.5  Calculation of compressed header size

The following fields shall be excluded from the calculation of the size of the compressed header in evaluation of
compression performance:

-  ROHC CID/add-CID octet(s);

-  ROHC padding octets;

-  ROHC segmentation octets;

-  ROHC feedback octets, either piggybacked on the behalf of an associated decompressor or as feedback packets

interspersed within the flow of compressed packets.

A.2

Test outline – RoHC RTP Profile 0x0001

RoHC compression shall start in U-mode, in accordance with RFC3095. Transition to other compression modes shall be
initiated by the test equipment sending a feedback packet of type 2, indicating the desired mode transition.

A.2.1

Test 1a - Base test of ROHC RTP O-mode compressor

A.2.1.1

Test purpose

The purpose of the base test case is to verify that the compressor properly implements compression for a well-behaved
IP/UDP/RTP packet flow, i.e. that it makes use of efficient compressed packet formats available to ROHC RTP [8]
when operating in O-mode.

A.2.1.2

Sequence details

A sequence consisting of 70 packets in total is used, where all header fields are set according to the basic test packet
structure, as described in subclause A.3, with addition of the following:

1.  The RTP Sequence Number is a linearly increasing counter with a packet-to-packet delta of 1, set to
0x0000 for the first packet and thus ending with 0x0045 (69) in the last packet of the sequence

2.  The RTP Time Stamp is a linearly increasing counter with a packet-to-packet delta of 160, set to

0x00000000 for the first packet and thus ending with 0x00002B20 (11040) in the last packet of the
sequence.

3.  The IP Identification is set to the same value as the RTP Sequence Number; this means that for IPv4 the IP-

ID behaviour is not random, thus value(RND)=0 defined in [8] for both IPv4 and IPv6.

Between the 6th and 7th packets (SN=5 and SN=6) of the sequence, a ROHC feedback packet of feedback type 2 is to be
given to the ROHC compressor to trigger an immediate transition to O-mode operation. The format of that packet is as
follows:

     0   1   2   3   4   5   6   7
   +---+---+---+---+---+---+---+---+
   | 1   1   1   1et
   +---+---+---+---+---+---+---+---+
   |Acktype| Mode  |      S+---+---+
   |              SN               |
   | 0   0   0   1 | 0   0   0   1 |
   +---+          CRC              |

   +---+---+---+- set to 0x4 (indicates that feedback data abovpe is set to 0x0 (means ACK)

-  Mode is set to 0x2 (means O-mode)

3GPP

Release 13

29

3GPP TS 25.323 V13.0.0 (2015-12)

-  SN is set to 0x000

-  CRC is the 8-bit CRC computed over the entire feedback payload including any CID fields but excluding the

packet type, the 'Size' field and the 'Code' octet, using the polynomial defined in [8], [10].

NOTE:

If compressor uses CID field in compressed packet, the CID field should be included in the feedback
packet and the Code and CID should be set as defined in [8].

A.2.1.3

Test requirement

Table A.2.1.3: Test Requirement for Test 1a

SN <= N-1
SN >= N

Average Compressed
Header Size, IPv4
44 octets
5 octets

Average Compressed Header
size, IPv6
68 octets
5 octets

N is smaller than 8.

The sequence of expected compressed headers can be illustrated as follow (informative):

Header Size

(octets)

IR

IR-DYN

5

Feedback-2 (ACK, mode=0x2, SN=0x000)

0

N-1

5

6

RTP SN

69

Figure A.2.1.3: Expected outcome for Test 1a

A.2.2

Test 1b - Base test of ROHC RTP R-mode compressor

A.2.2.1

Test purpose

The purpose of the base test case is to verify that the compressor properly implements compression for a well-behaved
IP/UDP/RTP packet flow, i.e. that it makes use of efficient compressed packet formats available to ROHC RTP [8]
when operating in R-mode.

A.2.2.2

Sequence details

A sequence consisting of 70 packets in total is used where all header fields are set according to the basic test packet
structure, as described in subclause A.3, with addition of the following:

1.  The RTP Sequence Number is a linearly increasing counter with a packet-to-packet delta of 1, set to
0x0000 for the first packet and thus ending with 0x0045 (69) in the last packet of the sequence

2.  The RTP Time Stamp is a linearly increasing counter with a packet-to-packet delta of 160, set to

0x00000000 for the first packet and thus ending with 0x00002B20 (11040) in the last packet of the
sequence.

3.  The IP Identification is set to the same value as the RTP Sequence Number; this means that for IPv4 the IP-

ID behaviour is not random, thus value(RND)=0 defined in [8] for both IPv4 and IPv6.

3GPP

Release 13

30

3GPP TS 25.323 V13.0.0 (2015-12)

Between the 6th and 7th (SN=5 and SN=6) packets of the sequence, the first ROHC feedback packet of feedback type 2
is to be given to the ROHC compressor to initiate transition to R-mode operation. The format of that packet is as follows:

     0   1   2   3   4   5   6   7
   +---+---+---+---+---+---+---+---+
   | 1   1   1   1   0 |   Code    |  feedback type octet
   +---+---+--ode  |      SN       |
   +---+---+---+---+---+---+---+---+
   |   +---+---+---+---+---+---+---+
   | 0   0   0  ---+---+---+---+---+
   |              CRC    --+---+---+

Where:

-  Code is set to 0x4 (indipe octet is 4 octets)

-  Acktype is set to 0x0 ns R-mode)

-  SN is set to 0x000

-  CRC is the 8-bit CRC computed over the entire feedback payload including any CID fields but excluding the

packet type, the 'Size' field and the 'Code' octet, using the polynomial defined in [8], [10].

The test equipment waits for a UOR-2, IR-DYN or IR packet from the RoHC compressor with the mode transition
parameter set to R. The value of x is the RTP SN of this received packet for which the test equipment generates the
second feedback packet of type 2, as described in subclause A.1.4.

A.2.2.3

Test requirement

Table A.2.2.3: Test Requirement for Test 1b

SN <= N-1
N <= SN <= 5
6 <= SN <= x
SN >= x+1

Average Compressed
Header Size, IPv4
44 octets
5 octets
9 octets
5 octets

Average Compressed Header
size, IPv6
68 octets
5 octets
9 octets
5 octets

The sequence of expected compressed headers can be illustrated as follow (informative):

Header Size

(octets)

IR

IR-DYN

9

5

Feedback-2 (ACK, mode=0x3, SN=0x000)

Feedback-2 (ACK, mode=0x3, SN=x)

0

N-1

5

6

x

x+1

RTP SN

69

Figure A.2.2.3: Expected outcome for Test 1b

3GPP

Release 13

31

3GPP TS 25.323 V13.0.0 (2015-12)

A.2.3

Void

A.2.3.1

A.2.3.2

A.2.3.3

Void

Void

Void

A.2.4

Void

A.2.4.1

A.2.4.2

A.2.4.3

Void

Void

Void

A.2.5

Test 3a - Re-establishment of TS function after DTX in O-mode

A.2.5.1

Test purpose

The purpose of the TS re-establishment test case is to verify that the compressor re-establishes the proper TS value after
a DTX period, i.e. that it use efficient header formats available to ROHC RTP [8] when operating in O-mode.

A.2.5.2

Sequence details

The test sequence is the same as in subclause A.2.1, with the following exception:

1.  The RTP Time Stamp is a linearly increasing counter with a packet-to-packet delta of 160, set to

0x00000000 for the first packet.

2.

3.

4.

For packet with SN = 20, TS is increased to represent a 32 (0.64 seconds) packet skip (32x160) and is
thus set to (20+32)x160=8320 (0x00002080). Then TS continues to grow as stated in 1 above.

For packet with SN = 30, TS is increased to represent a 128 (2.56 seconds) packet skip (128x160) and is
thus set to (30+32+128)x160=30400 (0x000076C0). Then TS continues to grow as stated in 1 above.

For packet with SN = 40, TS is increased to represent a 2048 (40.96 seconds) packet skip (2048x160) and
is thus set to (40+32+128+2048)x160=359680 (0x00057D00). Then TS continues to grow as stated in 1
above.

5.  TS thus ends at 364320 (0x00058F20) in the last packet of the sequence with RTP sequence number 69.

A.2.5.3

Test requirement

Table A.2.5.3: Test Requirement for Test 3a

SN <= 19
20 <= SN <= 19 + N
30 <= SN <= 29 + N
40 <= SN <= 39 + N
Other SN values

Average Compressed
Header Size, IPv4

Average Compressed
Header size, IPv6

See Test 1a

10 octets

10 octets
5 octets

10 octets

10 octets
5 octets

The sequence of expected compressed headers can be illustrated as follow (informative):

3GPP

Release 13

32

3GPP TS 25.323 V13.0.0 (2015-12)

Header Size

(octets)

IR

IR-DYN

See
Test 1a

10

5

TS jump(deltaTS=32x160 )

TS jump(deltaTS=128x160 )

TS jump(deltaTS=2048x160 )

0

20

20 + N

30

30 + N

40

40 + N

69

RTP SN

Figure A.2.5.3: Expected outcome for Test 3a

A.2.6

Test 3b - Re-establishment of TS function after DTX in R-mode

A.2.6.1

Test purpose

The purpose of the TS re-establish test case is to verify that  the compressor re-establishes the proper TS value after a
DTX period, i.e. that it use the efficient header formats available to ROHC RTP [8] when operating in R-mode.

A.2.6.2

Sequence details

The test sequence is the same as in subclause A.2.2, with the following exception:

1.  The RTP Time Stamp is a linearly increasing counter with a packet-to-packet delta of 160, set to

0x00000000 for the first packet.

2.

3.

4.

For packet with SN = 20, TS is increased to represent a 32 (0.64 seconds) packet skip (32x160) and is
thus set to (20+32)x160=8320 (0x00002080). Then TS continues to grow as stated in 1 above.

For packet with SN = 30, TS is increased to represent a 128 (2.56 seconds) packet skip (128x160) and is
thus set to (30+32+128)x160=30400 (0x000076C0). Then TS continues to grow as stated in 1 above.

For packet with SN = 40, TS is increased to represent a 2048 (40.96 seconds) packet skip (2048x160) and
is thus set to (40+32+128+2048)x160=359680 (0x00057D00). Then TS continues to grow as stated in 1
above.

5.  TS thus ends at 393120 (0x0005FFA0) in the last packet of the sequence with RTP sequence number 69.

A.2.6.3

Test requirement

Table A.2.6.3: Test Requirement for Test 3b

SN <=19
20 <= SN <= 19 + x
30 <= SN <= 29 + x
40 <= SN <= 39 + x
Other SN values

Average Compressed
Header Size, IPv4

Average Compressed
Header size, IPv6

See Test 1b

10 octets

10 octets
5 octets

10 octets

10 octets
5 octets

The sequence of expected compressed headers can be illustrated as follow (informative):

3GPP

Release 13

33

3GPP TS 25.323 V13.0.0 (2015-12)

Header Size

(octets)

IR

IR-DYN

See
Test 1b

10

5

TS jump(deltaTS=32x160 )

TS jump(deltaTS=128x160 )

TS jump(deltaTS=2048x160 )

0

20

20+x

30

30+x

40

40+x

RTP SN

69

Figure A.2.6.3: Expected outcome for Test 3b

A.2.7

Test 4a - Compressor response to single lost packets in O-mode

A.2.7.1

Test purpose

The purpose of this test is to verify that the compressor does not panic just because there is a single missing packet, i.e.
the compressed packet size should not increase due to such events.

A.2.7.2

Sequence details

The test sequence is the same as in subclause A.2.1, with the following exception:

-  Packets with SN 20, 30, and 40 are removed from the sequence.

A.2.7.3

Test requirement

Maximal compressed header overhead for the test are the same as in A2.1.

A.2.8

Test 4b - Compressor response to single lost packets in R-mode

A.2.8.1

Test purpose

The purpose of this test is to verify that the compressor does not panic just because there is a single missing packet, i.e.
the compressed packet size should not increase due to such events.

A.2.8.2

Sequence details

The test sequence is the same as in subclause A.2.2, with the following exception:

-  Packets with SN 20, 30, and 40 are removed from the sequence.

A.2.8.3

Test requirement

Maximal compressed header overhead for the test are the same as in A2.2.

3GPP

Release 13

34

3GPP TS 25.323 V13.0.0 (2015-12)

A.2.9

Void

A.2.9.1

A.2.9.2

A.2.9.3

Void

Void

Void

A.2.10  Void

A.2.10.1

Void

A.2.10.2

Void

A.2.10.3

Void

A.2.11  Test 6a - TS function during DTX with varying delta in O-mode

A.2.11.1

Test purpose

The purpose of this test case is to verify that the compressor properly handles variations in the function between the TS
value and the SN during and after a DTX period, during which SID packets are sent periodically, i.e. that it uses
efficient header formats available to ROHC RTP [8] when operating in O-mode.

A.2.11.2

Sequence details

The test sequence is the same as in subclause A.2.1, with the following exception:

1.  The RTP Time Stamp is a linearly increasing counter with a packet-to-packet delta of 160, set to

0x00000000 for the first packet.

2.

3.

4.

For packets SN = 20, 21 and 22, TS is increased to represent a 7 (0.14 seconds) packet skip (7x160) and
is thus set to (20+7)x160=4320 (0x000010E0), (21+7+7)x160=5600(0x000015E0) and
(22+7+7+7)x160=6880(0x00001AE0), respectively.

For packets SN = 30, 31, 32, 33 and 34, TS is increased to represent a 7 (0.14 seconds) packet skip
(7x160) and is thus set to 9280 (0x00002440), 10560 (0x00002940), 11840 (0x00002E40), 13120
(0x00003340) and 14400 (0x00003840) respectively.

For packets SN = 40, 41, 42, 43, 44, 45, and 46, TS is increased to represent a 7 (0.14 seconds) packet
skip (7x160) and is thus set to 16480 (0x00004060), 17760 (0x00004560), 19040 (0x00004A60), 20320
(0x00004F60), 21600 (0x00005460), 22880 (0x00005960) and 24160 (0x00005E60) respectively.

5.  TS thus ends at 27840 (0x00006CC0) in the last packet of the sequence with RTP sequence number 69.

A.2.11.3

Test requirement

Table A.2.11.3: Test Requirement for Test 6a

SN <= 19
20 <= SN <= 22 + N
30 <= SN <= 34 + N
40 <= SN <= 46 + N
Other SN values

Average Compressed
Header Size, IPv4

Average Compressed Header
size, IPv6

See Test 1a

15 octets

5 octets

15 octets

5 octets

The sequence of expected compressed headers can be illustrated as follow (informative):

3GPP

Release 13

35

3GPP TS 25.323 V13.0.0 (2015-12)

Header Size

(octets)

IR

IR-DYN

See
Test 1a

16

5

TS jump(deltaTS=7x160 )

TS jump(deltaTS=7x160 )

TS jump(deltaTS=7x160 )

0

20

22

22+N

30

32

34

34+N

40

42

44

46

46+N

69

21

31

33

41

43

45

RTP SN

Figure A.2.11.3: Expected outcome for Test 6a

A.2.12  Test 6b - TS function during DTX with varying delta in R-mode

A.2.12.1

Test purpose

The purpose of this test case is to verify how efficiently the compressor handles variations in the function between the
TS value and the SN during and after a DTX period, during which SID packets are sent periodically, i.e. that it uses the
efficient header formats available to ROHC RTP [8] when operating in R-mode.

A.2.12.2

Sequence details

The test sequence is the same as in subclause A.2.2, with the following exception:

1.  The RTP Time Stamp is a linearly increasing counter with a packet-to-packet delta of 160, set to

0x00000000 for the first packet.

2.

3.

4.

For packets SN = 20, 21 and 22, TS is increased to represent a 7 (0.14 seconds) packet skip (7x160) and
is thus set to (20+7)x160=4320 (0x000010E0), (21+7+7)x160=5600(0x000015E0) and
(22+7+7+7)x160=6880(0x00001AE0), respectively.

For packets SN = 30, 31, 32, 33 and 34, TS is increased to represent a 7 (0.14 seconds) packet skip
(7x160) and is thus set to 9280 (0x00002440), 10560 (0x00002940), 11840 (0x00002E40), 13120
(0x00003340) and 14400 (0x00003840) respectively.

For packets SN = 40, 41, 42, 43, 44, 45, and 46, TS is increased to represent a 7 (0.14 seconds) packet
skip (7x160) and is thus set to 16480 (0x00004060), 17760 (0x00004560), 19040 (0x00004A60), 20320
(0x00004F60), 21600 (0x00005460), 22880 (0x00005960) and 24160 (0x00005E60) respectively.

5.  TS thus ends at 27840 (0x00006CC0) in the last packet of the sequence with RTP sequence number 69.

A.2.12.3

Test requirement

Table A.2.12.3: Test Requirement for Test 6b

SN <= 19
20 <= SN <= 22 + x
30 <= SN <= 34 + x
40 <= SN <= 46 + x
Other SN values

Average Compressed
Header Size, IPv4

Average Compressed Header
size, IPv6

See Test 1b

15 octets

5 octets

15 octets

5 octets

The sequence of expected compressed headers can be illustrated as follow (informative):

3GPP

Release 13

36

3GPP TS 25.323 V13.0.0 (2015-12)

Header Size

(octets)

IR

IR-DYN

See
Test 1b

16

5

TS jump(deltaTS=7x160 )

TS jump(deltaTS=7x160 )

TS jump(deltaTS=7x160 )

0

20

22

22+x

30

32

34

34+x

40

42

44

46

46+x

69

21

31

33

41

43

45

RTP SN

Figure A.2.12.3: Expected outcome for Test 6b

A.2.13  Test 7a – SRNS relocation in O-mode

A.2.13.1

Test purpose

This test applies to UEs supporting header compression context relocation from Rel-5 onwards.

The purpose of this test case is to verify that the compressor does not interrupt efficient header compression upon
reception of the indication about SRNS relocation being performed, i.e. that it makes use of efficient compressed packet
formats available to ROHC RTP [8] when operating in O-mode when data transmission is resumed after SRNS
relocation.

Continuation of efficient header compression upon reception of the indication about SRNS relocation being performed
is possible according to subclause 5.4.2, i.e. the compressor shall compress and transmit uplink data as specified in [8]
using the assumption that all ROHC uplink packets transmitted are likely to be lost.

A.2.13.2

Sequence details

The test sequence is the same as in subclause A.2.1, with the following exception:

Packets with SN = 10 to  SN = 59 are removed from the sequence.

SRNS relocation occurs between packet with SN = 9 and packet with SN = 60, thus simulating a 1s long SRNS
relocation that affects compression of the IP/UDP/RTP packet flow.

NOTE:  The operation of the ROHC compressor is not affected by the time interval between packets with SN = 9

and SN = 60 (timer-based compression is not allowed because no appropriate feedback is provided).

A.2.13.3

Test requirement

Table A.2.13.3: Test Requirement for Test 7a

SN <= N-1
N <= SN <= 9
60 <= SN <= 59+N
SN >= 60+N

Average Compressed
Header Size, IPv4
44 octets
5 octets
8 octets
5 octets

Average Compressed Header
size, IPv6
68 octets
5 octets
8 octets
5 octets

N is smaller than 8. The sequence of expected compressed headers can be illustrated as follow (informative):

3GPP

Release 13

37

3GPP TS 25.323 V13.0.0 (2015-12)

Header Size
( octets )
IR
 IR-DYN

8

5

Feedback(ACK , mode=0x2, SN=0x000)

SRNS relocation

0

N

7  8

9

60

60 + N

69

RTP SN

Figure A.2.13.3: Expected outcome for Test 7a

3GPP

Release 13

38

3GPP TS 25.323 V13.0.0 (2015-12)

A.3

Test packet structures

IPv6/UDP/RTP
                        1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version| Traffic Class |           Flow Label                  |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Payload Length        |  Next Header  |   Hop Limit   |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   +                                                               +
   |                                                               |
   +                         Source Address                        +
   |                                                               |
   +                                                               +
   |                                                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                                                               |
   +                                                               +
   |                                                               |
   +                      Destination Address                      +
   |                                                               |
   +                                                               +
   |                                                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          Source Port          |       Destination Port        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          Length               |       Checksum                |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |V=2|P|X|  CC   |M|     PT      |       sequence number         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           timestamp                           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           synchronization source (SSRC) identifier            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

IPv4/UDP/RTP
                        1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version|  IHL  |Type of Service|          Total Length         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Identification        |R|D|F|      Fragment Offset    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Time to Live |    Protocol   |         Header Checksum       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Source Address                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Destination Address                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- +-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          Source Port          |       Destination Port        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          Length               |       Checksum                |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |V=2|P|X|  CC   |M|     PT      |       sequence number         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           timestamp                           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

3GPP

Release 13

39

3GPP TS 25.323 V13.0.0 (2015-12)

   |           synchronization source (SSRC) identifier            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

3GPP

Release 13

40

3GPP TS 25.323 V13.0.0 (2015-12)

IPv6 header fields
      +---------------------+-------------+----------------+
      | Field               | Size (bits) |     Value      |
      +---------------------+------------ |     0x6        |
      | Traffic Class       |      8      |     0x00000    |
      | Payload Length      |     16      |     0x0034     |
      | Next Header         |      8      |     0x11       |
      | Hop Limit           |      8      | Test dependent |
      | Source Address      |    128      |     ANY        |
      | Destination Address |    128      |     ANY        |
      +---------------------+-------------+----------------+

IPv4 header fields
      +---------------------+-------------+----------------+
      | Field               |-------------+----------      |
      | Header Length (IHL) |      4      |     0x5        |
      | Packet Length       |     16      |     0x0048     |
      | Identification      |     16      | Test dependent |
      | Reserved flag (R)   |      1      |     0x0        |
      | Don't Fragment (D)  |      1      |     0x1        |
      | More Fragments (F)  |      1      |     0x0        |
      | Fragment Offset     |     13      |     0x0000     |
      | Time To Live        |      8      | Test dependent |
      | Protocol            |      8      |     0x11       |
      | Header Checksum     |     16      |  See RFC 791   |
      | Source Address      |     32      |     ANY        |
      | Destination Address |     32      |     ANY        |
      +---------------------+-------------+----------------+

UDP header fields
      +---------------------+-------------+----------------+
      | Field               | Size (bits) +----------------+
      | Destination Port    |     16      |     ANY        |
      | Checksum            |     16      |  See RFC 768   |
      +---------------------+-------------+----------------+

RTP header fields
      +---------------------+-------------+----------------+
      | Field               | Size (bits) |     Value      |
      +---------------------+-------------+----------------+
      | Version (V)         |      2      |     0x2        |
      | Padding (P)         |      1      |     0x0        |
      | Extension (X)       |      1      |     0x0        |
      | CSRC Counter (CC)   |      4      |     0x0        |
      | Marker (M)          |      1      |     0x0        |
      | Payload Type (PT)   |      7      |     0x60       |
      | Sequence Number     |     16      | Test dependent |
      | Timestamp           |     32      | Test dependent |
      | SSRC                |     32      |     ANY        |
      +---------------------+-------------+----------------+

3GPP

Release 13

41

3GPP TS 25.323 V13.0.0 (2015-12)

Annex B (informative):
Reference model for generating ROHC performance
requirements

B.1

Introduction

ROHC compressor and de-compressor may use a set of parameters in order to operate (e.g. L confidence parameter,
dynamic FOtimer and static IRtimer, K1 out of N1, K2 out of N2…) that may be optimised for a given application (e.g.
Voice over IP, Videotelephony over IP, Interactive Gaming over IP…).

NOTE:  L confidence parameter allows setting the number of times an IR or IR-Dyn packet is transmitted and

FOtimer and IRtimer are used in order to determine when a transition to a lower compressor state is
necessary: The dynamic timer FOtimer triggers SO state to FO state transition and the static IRtimer
triggers SO/FO state to IR state transition.

B.2

For Voice over IP (VoIP) optimisation

B.2.1  ROHC parameters optimisations for VoIP

For the support of VoIP in UTRAN, ROHC compressor and de-compressor parameter values (L confidence
parameter, dynamic FOtimer and static IRtimer, K1 out of N1, K2 out of N2) may be used. Values used in ROHC
reference model are given in annex B.2.2 for O-mode.

-  The initialisation phase duration;

-  The reaction delay to decompression failure;

-  The header compression ratio (compressed header size / uncompressed header size);

-  The error rates (in UDP and PDCP layers);

  The amount of transferred data (including ROHC compressed packets and feedbacks);

-  The resource usage (transport block occupancy in the RLC layer).

B.2.2

Parameter setting for ROHC reference model for VoIP

The following parameters setting is applied in the reference model for ROHC performance tests of VoIP application:

Table B.2.2: ROHC parameters setting for VoIP

ROHC parameter
L
FOtimer
IRtimer
K1 / N1
K2  /N2

O-mode
2
0.12 second
0.12 second
2 / 20
1 / 1

B.2.3

Setting the parameter value N in test cases for VoIP

In test cases for VoIP to evaluate ROHC Compression performance for both O- and R-mode, the parameter N (defined
in Annex A) is set to 4.

3GPP

Release 13

42

3GPP TS 25.323 V13.0.0 (2015-12)

Annex C (informative):
Change history

Change history

Rev  Subject/Comment

Date
TSG #
12/1999  RP-06
03/2000  RP-07
RP-07
06/2000  RP-08
09/2000  RP-09
RP-09
RP-09
RP-09
03/2001  RP-11
RP-11
RP-11
06/2001  RP-12
09/2001  RP-13

RP-13
RP-13
RP-13
12/2001  RP-14
RP-14
03/2002  RP-15
RP-15
06/2002  RP-16

RP-16
09/2002  RP-17
RP-17
RP-17
12/2003  RP-22
03/2005  RP-27
06/2005  RP-28
RP-28
RP-28
09/2005  RP-29
12/2005  RP-30
03/2006  RP-31
RP-31
06/2006  RP-32

RP-32
RP-32
09/2006  RP-33
12/2006  RP-34
RP-34
03/2007  RP-35

-

TSG Doc.  CR
RP-99645
RP-000041  004
RP-000041  005
RP-000221  006
RP-000359  009
RP-000359  011
RP-000359  012
RP-000359  015
RP-010027  018
RP-010027  019
RP-010039  017
RP-010310  021
RP-010543  028

RP-010543  030
RP-010543  036
RP-010553  026
RP-010762  038
RP-010772  039
RP-020069  043
-
RP-020328  049

-

-

RP-020345  050
RP-020540  053
RP-020552  055
RP-020552  057
-
RP-050067  059
RP-050315  0060
RP-050303  0062
RP-050303  0064
RP-050468  0065
RP-050784  0067
RP-060083  0069
-
RP-060374  0072

-

RP-060374  0075
RP-060374  0078
RP-060573  0081
RP-060717  0296
RP-060717  0299
RP-070149  0301

06/2007  RP-36
RP-36

RP-070407  0302
RP-070406  0304

09/2007  RP-37

RP-37
12/2007  RP-38
RP-38
03/2008  RP-39
09/2008  RP-41
12/2008  RP-42
03/2009  RP-43
RP-43

06/2009
07/2009

RP-070636  0305
RP-070636  0306
RP-070893  0309
RP-070910  0310
RP-080201  0311
RP-080687  0312
RP-081012  0313
RP-090140  0314
RP-090140  0315

12/2009  RP-46
12/2009  RP-46
09/2010  RP-49

RP-091328  0317
-
RP-100859  0320

-

4
3

2

1
1
2

2
1
2

1

1

1
1

1

1

1

2
-
1

4.1.0  4.2.0
4.1.0  4.2.0
4.1.0  4.2.0
4.2.0  4.3.0
4.2.0  4.3.0
4.3.0  4.4.0
4.4.0  5.0.0
5.0.0  5.1.0

New
Old
-
3.0.0
Approved at TSG-RAN #6 and placed under Change Control
3.0.0  3.1.0
Bit order of PDCP PDUs
Changes to PDCP
3.0.0  3.1.0
Changes in PDCP PDU format due to PDCP sequence numbering  3.1.0  3.2.0
3.1.0  3.2.0
Clarification of PDCP Sequence Numbering
3.2.0  3.3.0
Clarification on how to handle invalid PDUs
3.2.0  3.3.0
Primitives required for SRNS relocation
3.2.0  3.3.0
Handling of invalid PDCP PDU sequence number
3.3.0  3.4.0
Editorial Corrections
3.3.0  3.4.0
Updates necessary for Rel-4 specification
3.4.0  4.0.0
Robust Header Compression
4.0.0  4.1.0
Clarification on PDCP Sequence numbering
4.1.0  4.2.0
Header compression protocol reinitialisation during SRNS
relocation
PDCP SDU Sequence Numbering
Corrections to PDCP
Selection of the RFC 3095 CID transmission
General PDCP corrections
Management of Full Header transmission
Clarification on PDCP sequence numbering
Upgrade to Release 5 - no technical change
Clarification on PDCP sequence number synchronization
procedure
5.0.0  5.1.0
RFC 3095 context relocation
5.1.0  5.2.0
Mapping relation between PDCP and RLC
5.1.0  5.2.0
Corrections to RFC3095 operation
5.1.0  5.2.0
Mismatches between Rel-4 and R'99 in PDCP
5.2.0  6.0.0
Upgrade to Release 6 - no technical changes
6.0.0  6.1.0
Lossless DL RLC PDU size change
6.1.0  6.2.0
Introduction of MBMS
6.1.0  6.2.0
Target mode for ROHC operation
6.1.0  6.2.0
Performance testing of ROHC
6.2.0  6.3.0
Correction of MBMS header compression
6.3.0  6.4.0
Correction of the ROHC context relocation procedure
Reference model for generating ROHC performance requirements  6.4.0  6.5.0
6.5.0  7.0.0
Upgrade to Release 7 - no technical changes
7.0.0  7.1.0
RoHC Segmentation, padding and Packet_sizes_allowed
parameter removal
Removal of unnecessary ROHC test cases
Introduction of ROHC test requirements
Removal of CID indication in PDCP PID
Correction of feedback format for ROHC performance testing
Correction on acceptable configurations for compression entities
Introduction of new test for O-mode including test requirement in
case SRNS relocation for ROHC performance testing
PDCP reinitialisation at SRNS relocation
Update of normative references for Robust Header Compression
(RFC3095)
Incorrect reference to RFC number for Header Compression packet
formats
Correction for configuration of RFC3095 header compression
Clarification on RoHC Performance Testing
Introduction of CS voice over HSPA
CS-HSPA UL AMR Rate and maximum jitter time
Clarification of the CS counter handling
Delivery of CS Counter
Coding of the PDCP AMR Data PDU payload
Condition to identify a CS-HSPA configuration
Corrects Release shown on cover
Corrects file properties. Adds previous line in this history table (and
this one!).
UM RLC ciphering error detection and recovery
Upgrade to the Release 9 - no technical change
Clarification on PDCP CID field (Rel-9)

7.5.0  7.6.0
7.6.0  7.7.0
7.6.0  8.0.0
8.0.0  8.1.0
8.1.0  8.2.0
8.2.0  8.3.0
8.3.0  8.4.0
8.3.0  8.4.0
8.4.0  8.4.1
8.4.1  8.4.2

7.0.0  7.1.0
7.0.0  7.1.0
7.1.0  7.2.0
7.2.0  7.3.0
7.2.0  7.3.0
7.3.0  7.4.0

8.4.2  8.5.0
8.5.0  9.0.0
9.0.0  9.1.0

7.4.0  7.5.0
7.4.0  7.5.0

7.5.0  7.6.0

3GPP

Release 13

03/2011  RP-51
06/2011  RP-52
09/2012  RP-57
09/2014  RP-65
12/2015  RP-70

-

-
RP-110825  0323
-
-
-

-
-
-

43

3GPP TS 25.323 V13.0.0 (2015-12)

-
1
-
-
-

Upgrade to the Release 10 - no technical change
Removing RoHC discrepancy
Upgrade to the Release 11 - no technical change
Upgrade to the Release 12 - no technical change
Upgrade to the Release 13 - no technical change

9.1.0  10.0.0
10.0.0  10.1.0
10.1.0  11.0.0
11.0.0  12.0.0
12.0.0  13.0.0

3GPP


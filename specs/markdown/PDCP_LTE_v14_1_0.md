3GPP TS 36.323 V14.1.0 (2016-12)

Technical Specification

3rd Generation Partnership Project;
Technical Specification Group Radio Access Network;
Evolved Universal Terrestrial Radio Access (E-UTRA);
Packet Data Convergence Protocol (PDCP) specification
(Release 14)

The present document has been developed within the 3rd Generation Partnership Project (3GPP TM) and may be further elaborated for the purposes of 3GPP.
The present document has not been subject to any approval process by the 3GPP Organizational Partners and shall not be implemented.
This Specification is provided for future development work within 3GPP only. The Organizational Partners accept no liability for any use of this Specification.
Specifications and reports for implementation of the 3GPP TM system should be obtained via the 3GPP Organizational Partners' Publications Offices.

Release 14

2

3GPP TS 36.323 V14.1.0 (2016-12)

Keywords
UMTS, radio

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

© 2016, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC).
All rights reserved.

UMTS™ is a Trade Mark of ETSI registered for the benefit of its members
3GPP™ is a Trade Mark of ETSI registered for the benefit of its Members and of the 3GPP Organizational Partners
LTE™ is a Trade Mark of ETSI currently being registered for the benefit of its Members and of the 3GPP Organizational Partners
GSM® and the GSM logo are registered and owned by the GSM Association

3GPP

Release 14

3

3GPP TS 36.323 V14.1.0 (2016-12)

Contents

Foreword............................................................................................................................................................. 5

1

2

3
3.1
3.2

Scope ........................................................................................................................................................ 6

References ................................................................................................................................................ 6

Definitions and abbreviations ................................................................................................................... 7
Definitions ......................................................................................................................................................... 7
Abbreviations ..................................................................................................................................................... 7

4
4.1
4.2
4.2.1
4.2.2
4.3
4.3.1
4.3.2
4.4
4.5

General ..................................................................................................................................................... 8
Introduction........................................................................................................................................................ 8
PDCP architecture ............................................................................................................................................. 8
PDCP structure ............................................................................................................................................. 8
PDCP entities ............................................................................................................................................... 9
Services ............................................................................................................................................................ 10
Services provided to upper layers .............................................................................................................. 10
Services expected from lower layers .......................................................................................................... 10
Functions ......................................................................................................................................................... 11
Data available for transmission ........................................................................................................................ 11

5
5.1
5.1.1
5.1.2
5.1.2.1
5.1.2.1.1
5.1.2.1.2
5.1.2.1.2a
5.1.2.1.3
5.1.2.1.3a
5.1.2.1.4

PDCP procedures ................................................................................................................................... 12
PDCP Data Transfer Procedures ...................................................................................................................... 12
UL Data Transfer Procedures ..................................................................................................................... 12
DL Data Transfer Procedures ..................................................................................................................... 13
Procedures for DRBs ............................................................................................................................ 13
Void ................................................................................................................................................ 13
Procedures for DRBs mapped on RLC AM when the reordering function is not used ................... 13
RN procedures for DRBs mapped on RLC AM ............................................................................. 14
Procedures for DRBs mapped on RLC UM .................................................................................... 14
RN procedures for DRBs mapped on RLC UM ............................................................................. 15
Procedures for DRBs mapped on RLC AM and for LWA bearers when the reordering
function is used ............................................................................................................................... 15
Procedures when a PDCP PDU is received from the lower layers ............................................ 15
Procedures when t-Reordering expires ..................................................................................... 16
Procedures when the value of t-Reordering is reconfigured ..................................................... 17
Procedures for SRBs ............................................................................................................................. 17
SL Data Transmission Procedures ............................................................................................................. 17
SL Data Reception Procedures ................................................................................................................... 17
Re-establishment procedure ............................................................................................................................. 18
UL Data Transfer Procedures ..................................................................................................................... 18
Procedures for DRBs mapped on RLC AM ......................................................................................... 18
Procedures for DRBs mapped on RLC UM ......................................................................................... 18
Procedures for SRBs ............................................................................................................................. 19
DL Data Transfer Procedures ..................................................................................................................... 19
Procedures for DRBs mapped on RLC AM while the reordering function is not used ........................ 19
Procedures for DRBs mapped on RLC AM while the reordering function is used .............................. 19
Procedures for DRBs mapped on RLC UM ......................................................................................... 19
Procedures for SRBs ............................................................................................................................. 20
PDCP Status Report ......................................................................................................................................... 20
Transmit operation ..................................................................................................................................... 20
Receive operation ....................................................................................................................................... 20
PDCP discard ................................................................................................................................................... 20
Header Compression and Decompression ....................................................................................................... 21
Supported header compression protocols and profiles ............................................................................... 21
Configuration of header compression ........................................................................................................ 21
Protocol parameters .................................................................................................................................... 21
Header compression ................................................................................................................................... 22
Header decompression ............................................................................................................................... 22

5.1.2.1.4.1
5.1.2.1.4.2
5.1.2.1.4.3
5.1.2.2
5.1.3
5.1.4
5.2
5.2.1
5.2.1.1
5.2.1.2
5.2.1.3
5.2.2
5.2.2.1
5.2.2.1a
5.2.2.2
5.2.2.3
5.3
5.3.1
5.3.2
5.4
5.5
5.5.1
5.5.2
5.5.3
5.5.4
5.5.5

3GPP

Release 14

4

3GPP TS 36.323 V14.1.0 (2016-12)

5.5.6
5.5.6.1
5.5.6.2
5.6
5.6.1
5.6.2
5.7
5.8
5.9
5.10
5.10.1
5.10.2

PDCP Control PDU for interspersed ROHC feedback packet ................................................................... 22
Transmit Operation ............................................................................................................................... 22
Receive Operation ................................................................................................................................ 22
Ciphering and Deciphering .............................................................................................................................. 22
SL Ciphering and Deciphering for one-to-many communication .............................................................. 23
SL Ciphering and Deciphering for one-to-one communication ................................................................. 23
Integrity Protection and Verification ............................................................................................................... 23
Handling of unknown, unforeseen and erroneous protocol data ...................................................................... 24
PDCP Data Recovery procedure ...................................................................................................................... 24
Status report for LWA ..................................................................................................................................... 25
Transmit operation ..................................................................................................................................... 25
LWA status report ...................................................................................................................................... 25

6
6.1
6.1.1
6.1.2
6.2
6.2.1
6.2.2
6.2.3
6.2.4
6.2.5
6.2.6
6.2.7
6.2.8
6.2.9
6.2.10
6.2.11
6.2.12
6.3
6.3.1
6.3.2
6.3.3
6.3.4
6.3.5
6.3.6
6.3.7
6.3.8
6.3.9
6.3.10
6.3.11
6.3.12
6.3.13
6.3.14
6.3.15
6.3.16
6.3.17
6.3.18

Protocol data units, formats and parameters .......................................................................................... 26
Protocol data units ........................................................................................................................................... 26
PDCP Data PDU ........................................................................................................................................ 26
PDCP Control PDU .................................................................................................................................... 26
Formats ............................................................................................................................................................ 26
General ....................................................................................................................................................... 26
Control plane PDCP Data PDU.................................................................................................................. 26
User plane PDCP Data PDU with long PDCP SN (12 bits) ....................................................................... 27
User plane PDCP Data PDU with short PDCP SN (7 bits) ........................................................................ 27
PDCP Control PDU for interspersed ROHC feedback packet ................................................................... 28
PDCP Control PDU for PDCP status report............................................................................................... 28
Void ............................................................................................................................................................ 29
RN user plane PDCP Data PDU with integrity protection ......................................................................... 29
User plane PDCP Data PDU with extended PDCP SN (15 bits) ............................................................... 29
User plane PDCP Data PDU for SLRB ...................................................................................................... 30
User plane PDCP Data PDU with further extended PDCP SN (18 bits) .................................................... 31
PDCP Control PDU for LWA status report ............................................................................................... 31
Parameters........................................................................................................................................................ 33
General ....................................................................................................................................................... 33
PDCP SN .................................................................................................................................................... 33
Data ............................................................................................................................................................ 33
MAC-I ........................................................................................................................................................ 33
COUNT ...................................................................................................................................................... 33
R ................................................................................................................................................................. 34
D/C ............................................................................................................................................................. 34
PDU type .................................................................................................................................................... 34
FMS ............................................................................................................................................................ 34
Bitmap ........................................................................................................................................................ 34
Interspersed ROHC feedback packet ......................................................................................................... 35
PGK Index .................................................................................................................................................. 35
PTK Identity ............................................................................................................................................... 35
SDU Type .................................................................................................................................................. 35
KD-sess ID ..................................................................................................................................................... 35
NMP ........................................................................................................................................................... 35
HRW .......................................................................................................................................................... 35
P ................................................................................................................................................................. 36

7
7.1
7.2
7.3

Variables, constants and timers .............................................................................................................. 36
State variables .................................................................................................................................................. 36
Timers .............................................................................................................................................................. 36
Constants ......................................................................................................................................................... 37

Annex A (informative):

Change history ............................................................................................... 38

3GPP

Release 14

5

3GPP TS 36.323 V14.1.0 (2016-12)

Foreword
This Technical Specification has been produced by the 3rd Generation Partnership Project (3GPP).

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

Release 14

6

3GPP TS 36.323 V14.1.0 (2016-12)

1

Scope

The present document provides the description of the Packet Data Convergence Protocol (PDCP).

2

References

The following documents contain provisions which, through reference in this text, constitute provisions of the present
document.

•  References are either specific (identified by date of publication, edition number, version number, etc.) or non

specific.

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

[13]

[14]

[15]

3GPP TR 21.905: "Vocabulary for 3GPP Specifications".

3GPP TS 36.300: "Evolved Universal Terrestrial Radio Access (E-UTRA) and Evolved Universal
Terrestrial Radio Access Network (E-UTRAN); Overall description".

3GPP TS 36.331: "Evolved Universal Terrestrial Radio Access (E-UTRA) Radio Resource
Control (RRC); Protocol Specification".

3GPP TS 36.321: "Evolved Universal Terrestrial Radio Access (E-UTRA) Medium Access
Control (MAC) protocol specification".

3GPP TS 36.322: "Evolved Universal Terrestrial Radio Access (E-UTRA) Radio Link Control
(RLC) protocol specification".

3GPP TS 33.401: "3GPP System Architecture Evolution: Security Architecture".

IETF RFC 4995: "The RObust Header Compression (ROHC) Framework".

IETF RFC 4996: "RObust Header Compression (ROHC): A Profile for TCP/IP (ROHC-TCP)".

IETF RFC 3095: "RObust Header Compression (ROHC): Framework and four profiles: RTP,
UDP, ESP and uncompressed".

IETF RFC 3843: "RObust Header Compression (ROHC): A Compression Profile for IP".

IETF RFC 4815: "RObust Header Compression (ROHC): Corrections and Clarifications to RFC
3095".

IETF RFC 5225: "RObust Header Compression (ROHC) Version 2: Profiles for RTP, UDP, IP,
ESP and UDP Lite”.

3GPP TS 33.303: “Proximity-based Services; Security Aspects”.

3GPP TS 23.303: “Proximity-based Services; Stage 2”.

3GPP TS 36.360: “Evolved Universal Terrestrial Radio Access (E-UTRA); LTE-WLAN
Aggregation Adaptation Protocol (LWAAP) specification”.

3GPP

Release 14

7

3GPP TS 36.323 V14.1.0 (2016-12)

3

Definitions and abbreviations

3.1

Definitions

For the purposes of the present document, the terms and definitions given in TR 21.905 [1] and the following apply. A
term defined in the present document takes precedence over the definition of the same term, if any, in TR 21.905 [1].

NB-IoT: NB-IoT allows access to network services via E-UTRA with a channel bandwidth limited to 180 kHz.

Split bearer: in dual connectivity, a bearer whose radio protocols are located in both the MeNB and the SeNB to use
both MeNB and SeNB resources.

LWA bearer: in LTE-WLAN Aggregation, a bearer whose radio protocols are located in both the eNB and the WLAN
to use both eNB and WLAN resources.

3.2

Abbreviations

For the purposes of the present document, the abbreviations given in TR 21.905 [1] and the following apply. An
abbreviation defined in the present document takes precedence over the definition of the same abbreviation, if any, in
TR 21.905 [1].

AM
ARP
CID
DRB
EPS
E-UTRA
E-UTRAN
eNB
FMS
HFN
HRW
IETF
IP
L2
L3
LWA
MAC
MAC-I
MCG
NB-IoT
NMP
PDCP
PDU
PEK
PGK
ProSe
PTK
R
RB
RFC
RLC
RN
ROHC
RRC
RTP
SAP
SCG
SDU

Acknowledged Mode
Address Resolution Protocol
Context Identifier
Data Radio Bearer carrying user plane data
Evolved Packet System
Evolved UMTS Terrestrial Radio Access
Evolved UMTS Terrestrial Radio Access Network
E-UTRAN Node B
First missing PDCP SN
Hyper Frame Number
Highest Received PDCP SN on WLAN
Internet Engineering Task Force
Internet Protocol
Layer 2 (data link layer)
Layer 3 (network layer)
LTE-WLAN Aggregation
Medium Access Control
Message Authentication Code for Integrity
Master Cell Group
Narrow Band Internet of Things
Number of Missing PDCP SDUs
Packet Data Convergence Protocol
Protocol Data Unit
ProSe Encryption Key
ProSe Group Key
Proximity-based Services
ProSe Traffic Key
Reserved
Radio Bearer
Request For Comments
Radio Link Control
Relay Node
RObust Header Compression
Radio Resource Control
Real Time Protocol
Service Access Point
Secondary Cell Group
Service Data Unit

3GPP

Release 14

8

3GPP TS 36.323 V14.1.0 (2016-12)

SLRB
SN
SRB
TCP
UDP
UE
UM
X-MAC

Sidelink Radio Bearer carrying Sidelink Communication data
Sequence Number
Signalling Radio Bearer carrying control plane data
Transmission Control Protocol
User Datagram Protocol
User Equipment
Unacknowledged Mode
Computed MAC-I

4

General

4.1

Introduction

The present document describes the functionality of the PDCP. Functionality specified for the UE equally applies to the
RN for functionality necessary for the RN. There is also functionality which is only applicable to the RN in its
communication with the E-UTRAN, in which case the specification denotes the RN instead of the UE. RN-specific
behaviour is not applicable to the UE. The functionality specified for the UE applies to communication on Uu interface
and PC5 interface [14].

4.2

PDCP architecture

4.2.1

PDCP structure

Figure 4.2.1.1 represents one possible structure for the PDCP sublayer; it should not restrict implementation. The figure
is based on the radio interface protocol architecture defined in [2].

UE/E-UTRAN

Radio Bearers

PDCP
entity

C-SAP

PDCP-SAP

PDCP-SAP

PDCP entity

PDCP entity

PDCP - PDU

RLC - SDU

RLC UM-SAP

RLC AM-SAP

...

PDCP
sublayer

...

RLC
sublayer

Figure 4.2.1.1 - PDCP layer, structure view

Each RB (i.e. DRB, SLRB and SRB, except for SRB0 and SRB1bis) is associated with one PDCP entity. Each PDCP
entity is associated with one or two (one for each direction) RLC entities depending on the RB characteristic (i.e. uni-
directional or bi-directional) and RLC mode. For split bearers, each PDCP entity is associated with two AM RLC

3GPP

Release 14

9

3GPP TS 36.323 V14.1.0 (2016-12)

entities. For LWA bearers, each PDCP entity is associated with an AM RLC entity and the LWAAP entity. The PDCP
entities are located in the PDCP sublayer.

The PDCP sublayer is configured by upper layers [3].

4.2.2

PDCP entities

The PDCP entities are located in the PDCP sublayer. Several PDCP entities may be defined for a UE. Each PDCP
entity carrying user plane data may be configured to use header compression.

Each PDCP entity is carrying the data of one radio bearer. In this version of the specification, only the robust header
compression protocol (ROHC), is supported. Every PDCP entity uses at most one ROHC compressor instance and at
most one ROHC decompressor instance.

A PDCP entity is associated either to the control plane or the user plane depending on which radio bearer it is carrying
data for.

Figure 4.2.2.1 represents the functional view of the PDCP entity for the PDCP sublayer; it should not restrict
implementation. The figure is based on the radio interface protocol architecture defined in [2].

For RNs, integrity protection and verification are also performed for the u-plane.

For split bearers, routing is performed in the transmitting PDCP entity, and reordering is performed in the receiving
PDCP entity. When requested by lower layers to submit PDCP PDUs, the transmitting PDCP entity shall:

-

if ul-DataSplitThreshold is configured and the data available for transmission is larger than or equal to ul-
DataSplitThreshold:

-

submit the PDCP PDUs to either the associated AM RLC entity configured for SCG or the associated AM
RLC entity configured for MCG, whichever the PDUs were requested by;

-  else:

-

if ul-DataSplitDRB-ViaSCG is set to TRUE by upper layers [3]:

-

if the PDUs were requested by the associated lower layers configured for SCG:

-

submit the PDCP PDUs to the associated AM RLC entity configured for SCG;

-  else:

-

if the PDUs were requested by the associated lower layers configured for MCG:

-

submit the PDCP PDUs to the associated AM RLC entity configured for MCG.

For LWA bearers, routing is performed in the transmitting PDCP entity and reordering is performed in the receiving
PDCP entity. The transmitting PDCP entity of the UE shall only submit the PDCP PDUs to the associated AM RLC
entity.

3GPP

Release 14

10

3GPP TS 36.323 V14.1.0 (2016-12)

UE/E-UTRAN/UE A

E-UTRAN/UE/UE B

Transmitting
PDCP  entity

Receiving
PDCP  entity

Sequence numbering

Header Compression (u-plane
only)

Packets associated
to a PDCP SDU

Integrity Protection
(c-plane only)

P
D
C
P
S
D
U

a
s
s
o
c
a
t
e
d

i

t
o

a

P
a
c
k
e
t
s

n
o
t

Ciphering

In order delivery and duplicate
detection (u-plane only)

Header Decompression (u-
plane only)

Packets associated
to a PDCP SDU
Reordering (u-plane
only)

Integrity Verification
(c-plane only)

P
D
C
P
S
D
U

a
s
s
o
c
a
t
e
d

i

t
o

a

P
a
c
k
e
t
s

n
o
t

Add PDCP header

Deciphering

Routing (u-plane only)

Remove PDCP Header

Radio Interface (Uu)/PC5/WLAN

Figure 4.2.2.1 - PDCP layer, functional view

4.3

Services

4.3.1

Services provided to upper layers

PDCP provides its services to the RRC and user plane upper layers at the UE or to the relay at the evolved Node B
(eNB). The following services are provided by PDCP to upper layers:

-

-

transfer of user plane data;

transfer of control plane data;

-  header compression;

-  ciphering;

-

integrity protection.

The maximum supported size of a PDCP SDU is 8188 octets, except in NB-IoT for which the maximum supported size
of a PDCP SDU is 1600 octets. The maximum supported size of a PDCP Control PDU is 8188 octets except in NB-IoT
for which the maximum supported size of PDCP Control PDU is 1600 octets.

4.3.2

Services expected from lower layers

A PDCP entity expects the following services from lower layers per RLC entity (for a detailed description see [5]):

3GPP

Release 14

11

3GPP TS 36.323 V14.1.0 (2016-12)

-  acknowledged data transfer service, including indication of successful delivery of PDCP PDUs;

-  unacknowledged data transfer service;

-

in-sequence delivery, except at re-establishment of lower layers;

-  duplicate discarding, except at re-establishment of lower layers.

A PDCP entity expects the following services from the LWAAP entity (for a detailed description see [15]):

-  user plane data transfer service;

4.4

Functions

The Packet Data Convergence Protocol supports the following functions:

-  header compression and decompression of IP data flows using the ROHC protocol;

-

transfer of data (user plane or control plane);

-  maintenance of PDCP SNs;

-

in-sequence delivery of upper layer PDUs at re-establishment of lower layers;

-  duplicate elimination of lower layer SDUs at re-establishment of lower layers for radio bearers mapped on RLC

AM;

-  ciphering and deciphering of user plane data and control plane data;

-

-

-

-

integrity protection and integrity verification of control plane data;

integrity protection and integrity verification of sidelink one-to-one communication data;

for RNs, integrity protection and integrity verification of user plane data;

timer based discard;

-  duplicate discarding;

-

for split and LWA bearers, routing and reordering.

PDCP uses the services provided by the RLC sublayer and the LWAAP sublayer.

PDCP is used for SRBs, DRBs, and SLRBs mapped on DCCH, DTCH, and STCH type of logical channels. PDCP is
not used for any other type of logical channels. PDCP is not used for SRB1bis.

4.5

Data available for transmission

For the purpose of MAC buffer status reporting, the UE shall consider PDCP Control PDUs, as well as the following as
data available for transmission in the PDCP layer:

For SDUs for which no PDU has been submitted to lower layers:

-

-

the SDU itself, if the SDU has not yet been processed by PDCP, or

the PDU if the SDU has been processed by PDCP.

In addition, for radio bearers that are mapped on RLC AM, if the PDCP entity has previously performed the re-
establishment procedure, the UE shall also consider the following as data available for transmission in the PDCP layer:

For SDUs for which a corresponding PDU has only been submitted to lower layers prior to the PDCP re-
establishment, starting from the first SDU for which the delivery of the corresponding PDUs has not been
confirmed by the lower layer, except the SDUs which are indicated as successfully delivered by the PDCP
status report, if received:

3GPP

Release 14

12

3GPP TS 36.323 V14.1.0 (2016-12)

-

-

the SDU, if it has not yet been processed by PDCP, or

the PDU once it has been processed by PDCP.

For radio bearers that are mapped on RLC AM, if the PDCP entity has previously performed the data recovery
procedure, the UE shall also consider as data available for transmission in the PDCP layer, all the PDCP PDUs that
have only been submitted to re-established AM RLC entity prior to the PDCP data recovery, starting from the first
PDCP PDU whose successful delivery has not been confirmed by lower layers, except the PDUs which are indicated as
successfully delivered by the PDCP status report, if received.

For split bearers, when indicating the data available for transmission to a MAC entity for BSR triggering and Buffer
Size calculation, the UE shall:

-

if ul-DataSplitThreshold is configured and the data available for transmission is larger than or equal to ul-
DataSplitThreshold:

-

indicatethe data available for transmission to both the MAC entity configured for SCG and the MAC entity
configured for MCG;

-  else:

-

if ul-DataSplitDRB-ViaSCG is set to TRUE by upper layer [3]:

-

-

indicate the data available for transmission to the MAC entity configured for SCG only;

if ul-DataSplitThreshold is configured, indicate the data available for transmission as 0 to the MAC entity
configured for MCG;

-  else:

-

-

indicate the data available for transmission to the MAC entity configured for MCG only;

if ul-DataSplitThreshold is configured, indicate the data available for transmission as 0 to the MAC entity
configured for SCG.

5

PDCP procedures

5.1

PDCP Data Transfer Procedures

5.1.1

UL Data Transfer Procedures

At reception of a PDCP SDU from upper layers, the UE shall:

-

start the discardTimer associated with this PDCP SDU (if configured);

For a PDCP SDU received from upper layers, the UE shall:

-  associate the PDCP SN corresponding to Next_PDCP_TX_SN to this PDCP SDU;

NOTE:  Associating more than half of the PDCP SN space of contiguous PDCP SDUs with PDCP SNs, when e.g.,

the PDCP SDUs are discarded or transmitted without acknowledgement, may cause HFN
desynchronization problem. How to prevent HFN desynchronization problem is left up to UE
implementation.

-  perform header compression of the PDCP SDU (if configured) as specified in the subclause 5.5.4;

-  perform integrity protection (if applicable), and ciphering (if applicable) using COUNT based on TX_HFN and

the PDCP SN associated with this PDCP SDU as specified in the subclause 5.7 and 5.6, respectively;

-

-

increment Next_PDCP_TX_SN by one;

if Next_PDCP_TX_SN > Maximum_PDCP_SN:

3GPP

Release 14

13

3GPP TS 36.323 V14.1.0 (2016-12)

-

-

set Next_PDCP_TX_SN to 0;

increment TX_HFN by one;

-

submit the resulting PDCP Data PDU to lower layer.

5.1.2

DL Data Transfer Procedures

5.1.2.1

Procedures for DRBs

5.1.2.1.1

Void

5.1.2.1.2

Procedures for DRBs mapped on RLC AM when the reordering function is not
used

For DRBs mapped on RLC AM, when the reordering function is not used, at reception of a PDCP Data PDU from
lower layers, the UE shall:

-

if received PDCP SN – Last_Submitted_PDCP_RX_SN > Reordering_Window or 0 <=
Last_Submitted_PDCP_RX_SN – received PDCP SN < Reordering_Window:

-

if received PDCP SN > Next_PDCP_RX_SN:

-  decipher the PDCP PDU as specified in the subclause 5.6, using COUNT based on RX_HFN - 1 and the

received PDCP SN;

-  else:

-  decipher the PDCP PDU as specified in the subclause 5.6, using COUNT based on RX_HFN and the

received PDCP SN;

-  perform header decompression (if configured) as specified in the subclause 5.5.5;

-  discard this PDCP SDU;

-  else if Next_PDCP_RX_SN – received PDCP SN > Reordering_Window:

-

increment RX_HFN by one;

-  use COUNT based on RX_HFN and the received PDCP SN for deciphering the PDCP PDU;

-

set Next_PDCP_RX_SN to the received PDCP SN + 1;

-  else if received PDCP SN – Next_PDCP_RX_SN >= Reordering_Window:

-  use COUNT based on RX_HFN – 1 and the received PDCP SN for deciphering the PDCP PDU;

-  else if received PDCP SN >= Next_PDCP_RX_SN:

-  use COUNT based on RX_HFN and the received PDCP SN for deciphering the PDCP PDU;

-

-

set Next_PDCP_RX_SN to the received PDCP SN + 1;

if Next_PDCP_RX_SN is larger than Maximum_PDCP_SN:

-

-

set Next_PDCP_RX_SN to 0;

increment RX_HFN by one;

-  else if received PDCP SN < Next_PDCP_RX_SN:

-  use COUNT based on RX_HFN and the received PDCP SN for deciphering the PDCP PDU;

-

if the PDCP PDU has not been discarded in the above:

3GPP

Release 14

14

3GPP TS 36.323 V14.1.0 (2016-12)

-  perform deciphering and header decompression (if configured) for the PDCP PDU as specified in the

subclauses 5.6 and 5.5.5, respectively;

-

if a PDCP SDU with the same PDCP SN is stored:

-  discard this PDCP SDU;

-  else:

-

store the PDCP SDU;

-

if the PDCP PDU received by PDCP is not due to the re-establishment of lower layers:

-  deliver to upper layers in ascending order of the associated COUNT value:

-  all stored PDCP SDU(s) with an associated COUNT value less than the COUNT value associated

with the received PDCP SDU;

-  all stored PDCP SDU(s) with consecutively associated COUNT value(s) starting from the COUNT

value associated with the received PDCP SDU;

-

set Last_Submitted_PDCP_RX_SN to the PDCP SN of the last PDCP SDU delivered to upper layers;.

-  else if received PDCP SN = Last_Submitted_PDCP_RX_SN + 1 or received PDCP SN =

Last_Submitted_PDCP_RX_SN – Maximum_PDCP_SN:

-  deliver to upper layers in ascending order of the associated COUNT value:

-  all stored PDCP SDU(s) with consecutively associated COUNT value(s) starting from the COUNT

value associated with the received PDCP SDU;

-

set Last_Submitted_PDCP_RX_SN to the PDCP SN of the last PDCP SDU delivered to upper layers.

5.1.2.1.2a

RN procedures for DRBs mapped on RLC AM

For DRBs mapped on RLC AM, at reception of a PDCP Data PDU from lower layers, the RN should follow the
procedures specified for a UE in 5.1.2.1.2 with the addition that for DRBs for which integrity verification is configured,
the RN should, immediately after performing deciphering as specified in 5.6, also perform integrity verification as
specified in 5.7 with the same COUNT value as used for deciphering.

In case of integrity verification failure, the RN should discard the PDCP Data PDU without performing header
decompression and without delivering any stored PDCP SDU(s) to upper layers. The RN should also set the RX_HFN,
Next_PDCP_RX_SN and Last_Submitted_PDCP_RX_SN to the respective values they had before the reception of the
PDCP Data PDU.

5.1.2.1.3

Procedures for DRBs mapped on RLC UM

For DRBs mapped on RLC UM, at reception of a PDCP Data PDU from lower layers, the UE shall:

-

if received PDCP SN < Next_PDCP_RX_SN:

-

increment RX_HFN by one;

-  decipher the PDCP Data PDU using COUNT based on RX_HFN and the received PDCP SN as specified in the

subclause 5.6;

-

-

set Next_PDCP_RX_SN to the received PDCP SN + 1;

if Next_PDCP_RX_SN > Maximum_PDCP_SN:

-

-

set Next_PDCP_RX_SN to 0;

increment RX_HFN by one;

-  perform header decompression (if configured) of the deciphered PDCP Data PDU as specified in the subclause

5.5.5;

3GPP

Release 14

15

3GPP TS 36.323 V14.1.0 (2016-12)

-  deliver the resulting PDCP SDU to upper layer.

5.1.2.1.3a

RN procedures for DRBs mapped on RLC UM

For DRBs mapped on RLC UM, at reception of a PDCP Data PDU from lower layers, the RN should follow the
procedures specified for a UE in 5.1.2.1.3 with the addition that for DRBs for which integrity verification is configured,
the RN should, immediately after performing deciphering as specified in 5.6, also perform integrity verification as
specified in 5.7 with the same COUNT value as used for deciphering.

In case of integrity verification failure, the RN should discard the PDCP Data PDU without performing header
decompression and set the RX_HFN and Next_PDCP_RX_SN to the respective values they had before the reception of
the PDCP Data PDU.

5.1.2.1.4

Procedures for DRBs mapped on RLC AM and for LWA bearers when the
reordering function is used

For DRBs mapped on RLC AM and for LWA bearers, the PDCP entity shall use the reordering function as specified in
this section when:

-

-

-

the PDCP entity is associated with two AM RLC entities; or

the PDCP entity is configured for a LWA bearer; or

the PDCP entity is associated with one AM RLC entity after it was, according to the most recent reconfiguration,
associated with two AM RLC entities or configured for a LWA bearer without performing PDCP re-
establishment.

The PDCP entity shall not use the reordering function in other cases.

5.1.2.1.4.1

Procedures when a PDCP PDU is received from the lower layers

For DRBs mapped on RLC AM, when the reordering function is used, at reception of a PDCP Data PDU from lower
layers, the UE shall:

-

if received PDCP SN – Last_Submitted_PDCP_RX_SN > Reordering_Window or 0 <=
Last_Submitted_PDCP_RX_SN – received PDCP SN < Reordering_Window:

-

if the PDCP PDU was received on WLAN:

-

if received PDCP SN > Next_PDCP_RX_SN:

-

for the purpose of setting the HRW field in the LWA status report, use COUNT based on RX_HFN -
1 and the received PDCP SN;

-  else:

-

for the purpose of setting the HRW field in the LWA status report, use COUNT based on RX_HFN
and the received PDCP SN;

-  discard the PDCP PDU;

-  else if Next_PDCP_RX_SN – received PDCP SN > Reordering_Window:

-

increment RX_HFN by one;

-  use COUNT based on RX_HFN and the received PDCP SN for deciphering the PDCP PDU;

-

set Next_PDCP_RX_SN to the received PDCP SN + 1;

-  else if received PDCP SN – Next_PDCP_RX_SN >= Reordering_Window:

-  use COUNT based on RX_HFN – 1 and the received PDCP SN for deciphering the PDCP PDU;

-  else if received PDCP SN >= Next_PDCP_RX_SN:

3GPP

Release 14

16

3GPP TS 36.323 V14.1.0 (2016-12)

-  use COUNT based on RX_HFN and the received PDCP SN for deciphering the PDCP PDU;

-

-

set Next_PDCP_RX_SN to the received PDCP SN + 1;

if Next_PDCP_RX_SN is larger than Maximum_PDCP_SN:

-

-

set Next_PDCP_RX_SN to 0;

increment RX_HFN by one;

-  else if received PDCP SN < Next_PDCP_RX_SN:

-  use COUNT based on RX_HFN and the received PDCP SN for deciphering the PDCP PDU;

-

if the PDCP PDU has not been discarded in the above:

-

if a PDCP SDU with the same PDCP SN is stored:

-  discard the PDCP PDU;

-  else:

-  perform deciphering of the PDCP PDU and store the resulting PDCP SDU;

-

if received PDCP SN = Last_Submitted_PDCP_RX_SN + 1 or received PDCP SN =
Last_Submitted_PDCP_RX_SN – Maximum_PDCP_SN:

-  deliver to upper layers in ascending order of the associated COUNT value:

-  all stored PDCP SDU(s) with consecutively associated COUNT value(s) starting from the COUNT

value associated with the received PDCP PDU;

-

set Last_Submitted_PDCP_RX_SN to the PDCP SN of the last PDCP SDU delivered to upper layers;

-

if t-Reordering is running:

-

if the PDCP SDU with Reordering_PDCP_RX_COUNT – 1 has been delivered to upper layers:

-

stop and reset t-Reordering;

-

if t-Reordering is not running (includes the case when t-Reordering is stopped due to actions above):

-

if there is at least one stored PDCP SDU:

-

-

start t-Reordering;

set Reordering_PDCP_RX_COUNT to the COUNT value associated to RX_HFN and
Next_PDCP_RX_SN.

5.1.2.1.4.2

Procedures when t-Reordering expires

When t-Reordering expires, the UE shall:

-  deliver to upper layers in ascending order of the associated COUNT value:

-  all stored PDCP SDU(s) with associated COUNT value(s) less than Reordering_PDCP_RX_COUNT;

-  all stored PDCP SDU(s) with consecutively associated COUNT value(s) starting from

Reordering_PDCP_RX_COUNT;

set Last_Submitted_PDCP_RX_SN to the PDCP SN of the last PDCP SDU delivered to upper layers;

if there is at least one stored PDCP SDU:

-

-

-

-

start t-Reordering;

set Reordering_PDCP_RX_COUNT to the COUNT value associated to RX_HFN and Next_PDCP_RX_SN.

3GPP

Release 14

17

3GPP TS 36.323 V14.1.0 (2016-12)

5.1.2.1.4.3

Procedures when the value of t-Reordering is reconfigured

When the value of the t-Reordering is reconfigured by upper layers while the t-Reordering is running, the UE shall:

-

-

stop and restart t-Reordering;

set Reordering_PDCP_RX_COUNT to the COUNT value associated to RX_HFN and Next_PDCP_RX_SN.

5.1.2.2

Procedures for SRBs

For SRBs, at reception of a PDCP Data PDU from lower layers, the UE shall:

-

if received PDCP SN < Next_PDCP_RX_SN:

-  decipher and verify the integrity of the PDU (if applicable) using COUNT based on RX_HFN + 1 and the

received PDCP SN as specified in the subclauses 5.6 and 5.7, respectively;

-  else:

-

-

-  decipher and verify the integrity of the PDU (if applicable) using COUNT based on RX_HFN and the

received PDCP SN as specified in the subclauses 5.6 and 5.7, respectively;

if integrity verification is applicable and the integrity verification is passed successfully; or

if integrity verification is not applicable:

-

if received PDCP SN < Next_PDCP_RX_SN:

-

increment RX_HFN by one;

-

-

set Next_PDCP_RX_SN to the received PDCP SN + 1;

if Next_PDCP_RX_SN > Maximum_PDCP_SN:

-

-

set Next_PDCP_RX_SN to 0;

increment RX_HFN by one;

-  deliver the resulting PDCP SDU to upper layer;

-  else, if integrity verification is applicable and the integrity verification fails:

-  discard the received PDCP Data PDU;

-

indicate the integrity verification failure to upper layer.

5.1.3

SL Data Transmission Procedures

For Sidelink transmission, the UE shall follow the procedures in subclause 5.1.1 with following modifications:

-

the requirements for maintaining Next_PDCP_TX_SN and TX_HFN are not applicable;

-  determine a PDCP SN ensuring that a PDCP SN value is not reused with the same key;

-  perform ciphering (if configured) as specified in subclause 5.6.1 and 5.6.2;

-  perform the header compression (if configured) if SDU Type is set to 000, i.e. IP SDUs.

5.1.4

SL Data Reception Procedures

For Sidelink reception, the UE shall follow the procedures in subclause 5.1.2.1.3 with following modifications:

-

the requirements for maintaining Next_PDCP_RX_SN and RX_HFN are not applicable;

-  perform the deciphering (if configured) as specified in subclause 5.6.1 and 5.6.2;

3GPP

Release 14

18

3GPP TS 36.323 V14.1.0 (2016-12)

-  perform the header decompression (if configured) if SDU Type is set to 000, i.e. IP SDUs.

5.2

Re-establishment procedure

When upper layers request a PDCP re-establishment, the UE shall additionally perform once the procedures described
in this section for the corresponding RLC mode. After performing the procedures in this section, the UE shall follow the
procedures in subclause 5.1.

5.2.1

UL Data Transfer Procedures

5.2.1.1

Procedures for DRBs mapped on RLC AM

When upper layers request a PDCP re-establishment, the UE shall:

-

-

reset the header compression protocol for uplink and start with an IR state in U-mode (if configured) [9] [11],
except if upper layers indicate stored UE AS context is used and drb-ContinueROHC is configured [3];

if connected as an RN, apply the integrity protection algorithm and key provided by upper layers (if configured)
during the re-establishment procedure;

-

if upper layers indicate stored UE AS context is used, set Next_PDCP_TX_SN, and TX_HFN to 0;

-  apply the ciphering algorithm and key provided by upper layers during the re-establishment procedure;

-

from the first PDCP SDU for which the successful delivery of the corresponding PDCP PDU has not been
confirmed by lower layers, perform retransmission or transmission of all the PDCP SDUs already associated
with PDCP SNs in ascending order of the COUNT values associated to the PDCP SDU prior to the PDCP re-
establishment as specified below:

-  perform header compression of the PDCP SDU (if configured) as specified in the subclause 5.5.4;

-

if connected as an RN, perform integrity protection (if configured) of the PDCP SDU using the COUNT
value associated with this PDCP SDU as specified in the subclause 5.7;

-  perform ciphering of the PDCP SDU using the COUNT value associated with this PDCP SDU as specified in

the subclause 5.6;

-

submit the resulting PDCP Data PDU to lower layer.

5.2.1.2

Procedures for DRBs mapped on RLC UM

When upper layers request a PDCP re-establishment, the UE shall:

-

reset the header compression protocol for uplink and start with an IR state in U-mode [9] [11] if the DRB is
configured with the header compression protocol and drb-ContinueROHC is not configured [3];

-

set Next_PDCP_TX_SN, and TX_HFN to 0;

-  apply the ciphering algorithm and key provided by upper layers during the re-establishment procedure;

-

-

if connected as an RN, apply the integrity protection algorithm and key provided by upper layers (if configured)
during the re-establishment procedure;

for each PDCP SDU already associated with a PDCP SN but for which a corresponding PDU has not previously
been submitted to lower layers:

-  consider the PDCP SDUs as received from upper layer;

-  perform transmission of the PDCP SDUs in ascending order of the COUNT value associated to the PDCP

SDU prior to the PDCP re-establishment, as specified in the subclause 5.1.1 without restarting the
discardTimer.

3GPP

Release 14

19

3GPP TS 36.323 V14.1.0 (2016-12)

5.2.1.3

Procedures for SRBs

When upper layers request a PDCP re-establishment, the UE shall:

-

set Next_PDCP_TX_SN, and TX_HFN to 0;

-  discard all stored PDCP SDUs and PDCP PDUs;

-  apply the ciphering and integrity protection algorithms and keys provided by upper layers during the re-

establishment procedure.

5.2.2

DL Data Transfer Procedures

5.2.2.1

Procedures for DRBs mapped on RLC AM while the reordering function is
not used

When upper layers request a PDCP re-establishment while the reordering function is not used, the UE shall:

-  process the PDCP Data PDUs that are received from lower layers due to the re-establishment of the lower layers,

as specified in the subclause 5.1.2.1.2;

-

-

reset the header compression protocol for downlink and start with NC state in U-mode (if configured) [9] [11],
except if upper layers indicate stored UE AS context is used and drb-ContinueROHC is configured [3];

if upper layers indicate stored UE AS context is used, set Next_PDCP_RX_SN, RX_HFN to 0 and
Last_submitted_PDCP_RX_SN to Maximum_PDCP_SN;

-  apply the ciphering algorithm and key provided by upper layers during the re-establishment procedure.

-

if connected as an RN, apply the integrity protection algorithm and key provided by upper layers (if configured)
during the re-establishment procedure.

5.2.2.1a

Procedures for DRBs mapped on RLC AM while the reordering function is
used

When upper layers request a PDCP re-establishment while the reordering function is used, the UE shall:

-  process the PDCP Data PDU(s) that are received from lower layers due to the re-establishment of the lower

layers, as specified in the subclause 5.1.2.1.4;

-

if the PDCP entity is to be associated with one AM RLC entity after PDCP re-establishment:

-

stop and reset t-Reordering;

-  apply the ciphering algorithm and key provided by upper layers during the re-establishment procedure.

5.2.2.2

Procedures for DRBs mapped on RLC UM

When upper layers request a PDCP re-establishment, the UE shall:

-  process the PDCP Data PDUs that are received from lower layers due to the re-establishment of the lower layers,

as specified in the subclause 5.1.2.1.3;

-

reset the header compression protocol for downlink and start with NC state in U-mode [9] [11] if the DRB is
configured with the header compression protocol and drb-ContinueROHC is not configured [3];

-

set Next_PDCP_RX_SN, and RX_HFN to 0;

-  apply the ciphering algorithm and key provided by upper layers during the re-establishment procedure.

-

if connected as an RN, apply the integrity protection algorithm and key provided by upper layers (if configured)
during the re-establishment procedure.

3GPP

Release 14

20

3GPP TS 36.323 V14.1.0 (2016-12)

5.2.2.3

Procedures for SRBs

When upper layers request a PDCP re-establishment, the UE shall:

-  discard the PDCP Data PDUs that are received from lower layers due to the re-establishment of the lower layers;

-

set Next_PDCP_RX_SN, and RX_HFN to 0;

-  discard all stored PDCP SDUs and PDCP PDUs;

-  apply the ciphering and integrity protection algorithms and keys provided by upper layers during the re-

establishment procedure.

5.3

PDCP Status Report

5.3.1

Transmit operation

When upper layers request a PDCP re-establishment or PDCP Data Recovery; or PDCP status report is triggered by
polling or periodic reporting, for radio bearers that are mapped on RLC AM, the UE shall:

-

if the radio bearer is configured by upper layers to send a PDCP status report in the uplink
(statusReportRequired [3]) or the status report is triggered by PDCP status report polling or PDCP periodic
status reporting, compile a status report as indicated below after processing the PDCP Data PDUs that are
received from lower layers due to the re-establishment of the lower layers as specified in the subclause 5.2.2.1,
and submit it to lower layers as the first PDCP PDU for the transmission, by:

-

-

setting the FMS field to the PDCP SN of the first missing PDCP SDU;

if there is at least one out-of-sequence PDCP SDU stored, allocating a Bitmap field of length in bits equal to
the number of PDCP SNs from and not including the first missing PDCP SDU up to and including the last
out-of-sequence PDCP SDUs, rounded up to the next multiple of 8, or up to and including a PDCP SDU for
which the resulting PDCP Control PDU size is equal to 8188 bytes, whichever comes first;

-

setting as ‘0’ in the corresponding position in the bitmap field for all PDCP SDUs that have not been
received as indicated by lower layers, and optionally PDCP SDUs for which decompression have failed;

-

indicating in the bitmap field as ‘1’ for all other PDCP SDUs.

5.3.2

Receive operation

When a PDCP status report is received in the downlink, for radio bearers that are mapped on RLC AM:

-

for each PDCP SDU, if any, with the bit in the bitmap set to '1', or with the associated COUNT value less than
the COUNT value of the PDCP SDU identified by the FMS field, the successful delivery of the corresponding
PDCP SDU is confirmed, and the UE shall process the PDCP SDU as specified in the subclause 5.4.

PDCP status report receive operation is not applicable in NB-IoT.

5.4

PDCP discard

When the discardTimer expires for a PDCP SDU, or the successful delivery of a PDCP SDU is confirmed by PDCP
status report, the UE shall discard the PDCP SDU along with the corresponding PDCP PDU. If the corresponding
PDCP PDU has already been submitted to lower layers the discard is indicated to lower layers.

NOTE:  For UL split bearers, discarding a PDCP SDU already associated with a PDCP SN causes a SN gap in the
transmitted PDCP PDUs, which increases PDCP reordering delay in the receiving PDCP entity. It is up to
UE implementation how to minimize SN gap after SDU discard.

3GPP

Release 14

21

3GPP TS 36.323 V14.1.0 (2016-12)

5.5

Header Compression and Decompression

5.5.1

Supported header compression protocols and profiles

The header compression protocol is based on the Robust Header Compression (ROHC) framework [7]. There are
multiple header compression algorithms, called profiles, defined for the ROHC framework. Each profile is specific to
the particular network layer, transport layer or upper layer protocol combination e.g. TCP/IP and RTP/UDP/IP.

The detailed definition of the ROHC channel is specified as part of the ROHC framework in RFC 4995 [7]. This
includes how to multiplex different flows (header compressed or not) over the ROHC channel, as well as how to
associate a specific IP flow with a specific context state during initialization of the compression algorithm for that flow.

The implementation of the functionality of the ROHC framework and of the functionality of the supported header
compression profiles is not covered in this specification.

In this version of the specification the support of the following profiles is described:

Table 5.5.1.1: Supported header compression protocols and profiles

Profile

Identifier

Usage:

Reference

0x0000

0x0001

0x0002

0x0003

0x0004

0x0006

0x0101

0x0102

0x0103

0x0104

No compression

RFC 4995

RTP/UDP/IP

RFC 3095, RFC 4815

UDP/IP

ESP/IP

IP

RFC 3095, RFC 4815

RFC 3095, RFC 4815

RFC 3843, RFC 4815

TCP/IP

RFC 4996

RTP/UDP/IP

RFC 5225

UDP/IP

ESP/IP

IP

RFC 5225

RFC 5225

RFC 5225

5.5.2

Configuration of header compression

PDCP entities associated with DRBs can be configured by upper layers [3] to use header compression. PDCP entities
associated with SLRBs can be configured to use header compression for IP SDUs.

5.5.3

Protocol parameters

RFC 4995 has configuration parameters that are mandatory and that must be configured by upper layers between
compressor and decompressor peers [7]; these parameters define the ROHC channel. The ROHC channel is a
unidirectional channel, i.e. there is one channel for the downlink, and one for the uplink. There is thus one set of
parameters for each channel, and the same values shall be used for both channels belonging to the same PDCP entity.

These parameters are categorized in two different groups, as defined below:

-  M: Mandatory and configured by upper layers.

-  N/A: Not used in this specification.

The usage and definition of the parameters shall be as specified below.

3GPP

Release 14

22

3GPP TS 36.323 V14.1.0 (2016-12)

-  MAX_CID (M): This is the maximum CID value that can be used. One CID value shall always be reserved for

uncompressed flows. The parameter MAX_CID is configured by upper layers (maxCID [3]).

-  LARGE_CIDS: This value is not configured by upper layers, but rather it is inferred from the configured value

of MAX_CID according to the following rule:

If MAX_CID > 15 then LARGE_CIDS = TRUE else LARGE_CIDS = FALSE.

-  PROFILES (M): Profiles are used to define which profiles are allowed to be used by the UE. The list of

supported profiles is described in section 5.5.1. The parameter PROFILES is configured by upper layers (profiles
for uplink and downlink, rohc-Profiles in SL-Preconfiguration for sidelink [3]).

-  FEEDBACK_FOR (N/A): This is a reference to the channel in the opposite direction between two compression
endpoints and indicates to what channel any feedback sent refers to. Feedback received on one ROHC channel
for this PDCP entity shall always refer to the ROHC channel in the opposite direction for this same PDCP entity.

-  MRRU (N/A): ROHC segmentation is not used.

5.5.4

Header compression

The header compression protocol generates two types of output packets:

-  compressed packets, each associated with one PDCP SDU

-

standalone packets not associated with a PDCP SDU, i.e. interspersed ROHC feedback packets

A compressed packet is associated with the same PDCP SN and COUNT value as the related PDCP SDU.

Interspersed ROHC feedback packets are not associated with a PDCP SDU. They are not associated with a PDCP SN
and are not ciphered.

NOTE:

If the MAX_CID number of ROHC contexts are already established for the compressed flows and a new
IP flow does not match any established ROHC context, the compressor should associate the new IP flow
with one of the ROHC CIDs allocated for the existing compressed flows or send PDCP SDUs belonging
to the IP flow as uncompressed packet.

5.5.5

Header decompression

If header compression is configured by upper layers for PDCP entities associated with u-plane data the PDCP PDUs are
de-compressed by the header compression protocol after performing deciphering as explained in the subclause 5.6.

5.5.6

PDCP Control PDU for interspersed ROHC feedback packet

5.5.6.1

Transmit Operation

When an interspersed ROHC feedback packet is generated by the header compression protocol, the UE shall:

-

submit to lower layers the corresponding PDCP Control PDU as specified in subclause 6.2.5 i.e. without
associating a PDCP SN, nor performing ciphering.

5.5.6.2

Receive Operation

At reception of a PDCP Control PDU for interspersed ROHC feedback packet from lower layers, the UE shall:

-  deliver the corresponding interspersed ROHC feedback packet to the header compression protocol without

performing deciphering.

5.6

Ciphering and Deciphering

The ciphering function includes both ciphering and deciphering and is performed in PDCP. For the control plane, the
data unit that is ciphered is the data part of the PDCP PDU (see subclause 6.3.3) and the MAC-I (see subclause 6.3.4).

3GPP

Release 14

23

3GPP TS 36.323 V14.1.0 (2016-12)

For the user plane, the data unit that is ciphered is the data part of the PDCP PDU (see subclause 6.3.3); ciphering is not
applicable to PDCP Control PDUs.

For RNs, for the user plane, in addition to the data part of the PDCP PDU, the MAC-I (see 6.3.4) is also ciphered if
integrity protection is configured.

The ciphering algorithm and key to be used by the PDCP entity are configured by upper layers [3] and the ciphering
method shall be applied as specified in [6].

The ciphering function is activated/suspended/resumed by upper layers [3]. When security is activated and not
suspended, the ciphering function shall be applied to all PDCP PDUs indicated by upper layers [3] for the downlink and
the uplink, respectively.

NOTE:  Security is suspended upon connection suspension (and resumed upon connection resumption).

For downlink and uplink ciphering and deciphering, the parameters that are required by PDCP for ciphering are defined
in [6] and are input to the ciphering algorithm. The required inputs to the ciphering function include the COUNT value,
and DIRECTION (direction of the transmission: set as specified in [6]).The parameters required by PDCP which are
provided by upper layers [3] are listed below:

-  BEARER (defined as the radio bearer identifier in [6]. It will use the value RB identity –1 as in [3]);

-  KEY (the ciphering keys for the control plane and for the user plane are KRRCenc and KUPenc, respectively).

5.6.1

SL Ciphering and Deciphering for one-to-many communication

For SLRB used for one-to-many communication, the ciphering function includes both ciphering and deciphering and is
performed in PDCP as defined in [13]. The data unit that is ciphered is the data part of the PDCP PDU (see subclause
6.3.3). The ciphering function as specified in [6] is applied with KEY (PEK), COUNT (derived from PTK Identity and
PDCP SN as specified in [13]), BEARER and DIRECTION (set to 0) as input. The ciphering function is configured by
ProSe Function.

If ciphering is configured, the ciphering algorithm and related parameters including PGK, PGK Identity, and Group
Member Identity are configured to the UE by ProSe Key Management Function. The UE shall set PTK Identity based
on PGK, PGK Identity, and PDCP SN as specified in [13]. The UE shall derive PTK from PGK using PTK Identity and
Group Member Identity, and derive PEK from PTK using the ciphering algorithm. The PGK Index, PTK Identity, and
PDCP SN are included in the PDCP PDU header.

If ciphering is not configured, PGK Index, PTK Identity, and PDCP SN shall be set to “0” in the PDCP PDU header.

5.6.2

SL Ciphering and Deciphering for one-to-one communication

For SLRB used for one-to-one communication, the ciphering function includes both ciphering and deciphering and is
performed in PDCP of SLRB that needs ciphering and deciphering as defined in [13]. The data unit that is ciphered is
the data part of the PDCP PDU (see subclause 6.3.3). The ciphering function as specified in [6] is applied with KEY
(PEK), COUNT (derived from KD-sess Identity and PDCP SN as specified in [13]), BEARER and DIRECTION (which
value shall be set is specified in [13]) as input.

For the SLRB that needs ciphering and deciphering, the UE shall derive the KEY (PEK) based on KD-sess and the
algorithms determined by the initiating UE and the receiving UE as specified in [13]. The KD-sess Identity and PDCP SN
are included in the PDCP PDU header.

For the SLRB that does not need ciphering and deciphering, the UE shall set KD-sess Identity and PDCP SN to “0” in the
PDCP PDU header.

5.7

Integrity Protection and Verification

The integrity protection function includes both integrity protection and integrity verification and is performed in PDCP
for PDCP entities associated with SRBs and the SLRB that needs integrity protection. The data unit that is integrity
protected is the PDU header and the data part of the PDU before ciphering.

3GPP

Release 14

24

3GPP TS 36.323 V14.1.0 (2016-12)

For RNs, the integrity protection function is performed also for PDCP entities associated with DRBs if integrity
protection is configured.

The integrity protection algorithm and key to be used by the PDCP entity are configured by upper layers [3] and the
integrity protection method shall be applied as specified in [6].

The integrity protection function is activated/suspended/resumed by upper layers [3]. When security is activated and not
suspended, the integrity protection function shall be applied to all PDUs including and subsequent to the PDU indicated
by upper layers [3] for the downlink and the uplink, respectively.

NOTE:  As the RRC message which activates the integrity protection function is itself integrity protected with the

configuration included in this RRC message, this message needs first be decoded by RRC before the
integrity protection verification could be performed for the PDU in which the message was received.

For downlink and uplink integrity protection and verification, the parameters that are required by PDCP for integrity
protection are defined in [6] and are input to the integrity protection algorithm. The required inputs to the integrity
protection function include the COUNT value, and DIRECTION (direction of the transmission: set as specified in [6]).
The parameters required by PDCP which are provided by upper layers [3] are listed below:

-  BEARER (defined as the radio bearer identifier in [6]. It will use the value RB identity –1 as in [3]);

-  KEY (KRRCint).

-

for RNs, KEY (KUPint)

For the SLRB that needs integrity protection and verification, the parameters that are required by PDCP for integrity
protection are defined in [6] and are input to the integrity protection algorithm. The required inputs to the integrity
protection function include the COUNT value and DIRECTION (which value shall be set is specified in [13]). The
parameters required by PDCP which are provided by upper layers [3] are listed below:

-  BEARER (defined as the radio bearer identifier in [6]);

-  KEY (PIK).

At transmission, the UE computes the value of the MAC-I field and at reception it verifies the integrity of the PDCP
PDU by calculating the X-MAC based on the input parameters as specified above. If the calculated X-MAC
corresponds to the received MAC-I, integrity protection is verified successfully.

5.8

Handling of unknown, unforeseen and erroneous protocol
data

When a PDCP entity receives a PDCP PDU that contains reserved or invalid values, the PDCP entity shall:

-  discard the received PDU.

5.9

PDCP Data Recovery procedure

When upper layers request a PDCP Data Recovery for a radio bearer, the UE shall:

-

if the radio bearer is configured by upper layers to send a PDCP status report in the uplink
(statusReportRequired [3]), compile a status report as described in subclause 5.3.1, and submit it to lower layers
as the first PDCP PDU for the transmission;

-  perform retransmission of all the PDCP PDUs previously submitted to re-established AM RLC entity in

ascending order of the associated COUNT values from the first PDCP PDU for which the successful delivery has
not been confirmed by lower layers.

After performing the above procedures, the UE shall follow the procedures in subclause 5.1.1.

3GPP

Release 14

25

3GPP TS 36.323 V14.1.0 (2016-12)

5.10  Status report for LWA

5.10.1  Transmit operation

When PDCP Data PDU with polling bit P set to 1 is received, the UE shall:

-

if configured to send the PDCP status report in response to polling (statusPDU-TypeForPolling is configured
and set to type1 [3])

-  compile and transmit the PDCP status report as specified in subclause 5.3.1;

-  else if configured to send the LWA status report in response to polling (statusPDU-TypeForPolling is configured

and set to type2 [3])

-  compile and transmit the LWA status report as specified in subclause 5.10.2.

When t-StatusReportType1 expires, the UE shall:

-  compile and transmit the PDCP status report as specified in subclause 5.3.1,

-

start t-StatusReportType1 with value statusPDU-Periodicity-Type1;

When t-StatusReportType2 expires, the UE shall:

-  compile and transmit the LWA status report as specified in subclause 5.10.2,

-

start t-StatusReportType2 with value statusPDU-Periodicity-Type2;

When t-StatusReportType1 is configured or reconfigured by upper layers, the UE shall:

-

-

stop t-StatusReportType1, if running;

start t-StatusReportType1 with value statusPDU-Periodicity-Type1;

When t-StatusReportType2 is configured or reconfigured by upper layers, the UE shall:

-

-

stop t-StatusReportType2, if running;

if statusPDU-Periodicity-Offset is configured by upper layers:

-

start t-StatusReportType2 with value statusPDU-Periodicity-Type2 plus statusPDU-Periodicity-Offset;

-  else:

-

start t-StatusReportType2 with value statusPDU-Periodicity-Type2;

When periodic PDCP status report becomes disabled by upper layers, the UE shall:

-

-

stop t-StatusReportType1, if running;

stop t-StatusReportType2, if running;

5.10.2  LWA status report

When LWA status report is triggered, the UE shall:

-  compile a status report as indicated below, and submit it to lower layers as the first PDCP PDU for the

transmission, by:

-

-

setting the FMS field to the PDCP SN of the first missing PDCP SDU;

setting the HRW field to the PDCP SN of the PDCP SDU received on WLAN with highest PDCP COUNT
value or to FMS if no PDCP SDUs have been received on WLAN;

-

setting the NMP field to the number of missing PDCP SDU(s) as described in 6.3.16.

3GPP

Release 14

26

3GPP TS 36.323 V14.1.0 (2016-12)

6

Protocol data units, formats and parameters

6.1

Protocol data units

6.1.1

PDCP Data PDU

The PDCP Data PDU is used to convey:

-  a PDCP SDU SN; and

-

-

for SLRBs used for one-to-many communication, PGK Index, PTK Identity, and SDU type; or

for SLRBs used for one-to-one communication, KD-sess Identity, and SDU type; and

-  user plane data containing an uncompressed PDCP SDU; or

-  user plane data containing a compressed PDCP SDU; or

-  control plane data; and

-  a MAC-I field for SRBs; or

-

-

for the SLRB that needs integrity protection for one-to-one communication, a MAC-I field; or

for RNs, a MAC-I field for DRB (if integrity protection is configured);

6.1.2

PDCP Control PDU

The PDCP Control PDU is used to convey:

-  a PDCP status report indicating which PDCP SDUs are missing and which are not following a PDCP re-

establishment.

-  header compression control information, e.g. interspersed ROHC feedback.

-  a LWA status report.

6.2

Formats

6.2.1  General

A PDCP PDU is a bit string that is byte aligned (i.e. multiple of 8 bits) in length. In the figures in sub clause 6.2, bit
strings are represented by tables in which the most significant bit is the leftmost bit of the first line of the table, the least
significant bit is the rightmost bit on the last line of the table, and more generally the bit string is to be read from left to
right and then in the reading order of the lines. The bit order of each parameter field within a PDCP PDU is represented
with the first and most significant bit in the leftmost bit and the last and least significant bit in the rightmost bit.

PDCP SDUs are bit strings that are byte aligned (i.e. multiple of 8 bits) in length. A compressed or uncompressed SDU
is included into a PDCP PDU from the first bit onward.

6.2.2

Control plane PDCP Data PDU

Figure 6.2.2.1 shows the format of the PDCP Data PDU carrying data for control plane SRBs.

3GPP

Release 14

27

3GPP TS 36.323 V14.1.0 (2016-12)

R

R

R

PDCP SN

Data

...

MAC-I

MAC-I (cont.)

MAC-I (cont.)

MAC-I (cont.)

Oct 1

Oct 2

Oct N-3

Oct N-2

Oct N-1

Oct N

Figure 6.2.2.1: PDCP Data PDU format for SRBs

6.2.3

User plane PDCP Data PDU with long PDCP SN (12 bits)

Figure 6.2.3.1 shows the format of the PDCP Data PDU when a 12 bit SN length is used. This format is applicable for
PDCP Data PDUs carrying data from DRBs mapped on RLC AM or RLC UM.

D/C

R

R

R

PDCP SN

PDCP SN (cont.)

Data

...

Oct 1

Oct 2

Oct 3

Figure 6.2.3.1: PDCP Data PDU format for DRBs using a 12 bit SN

6.2.4

User plane PDCP Data PDU with short PDCP SN (7 bits)

Figure 6.2.4.1 shows the format of the PDCP Data PDU when a 7 bit SN length is used. This format is applicable for
PDCP Data PDUs carrying data from DRBs mapped on RLC UM or in NB-IoT DRBs mapped on RLC AM.

D/C

PDCP SN

Data

...

Oct 1

Oct 2

Figure 6.2.4.1: PDCP Data PDU format for DRBs using 7 bit SN

3GPP

Release 14

28

3GPP TS 36.323 V14.1.0 (2016-12)

6.2.5

PDCP Control PDU for interspersed ROHC feedback packet

Figure 6.2.5.1 shows the format of the PDCP Control PDU carrying one interspersed ROHC feedback packet. This
format is applicable for DRBs mapped on RLC AM or RLC UM.

D/C

PDU Type

R

R

R

R

Oct 1

Interspersed ROHC feedback packet

Oct 2

...

Figure 6.2.5.1: PDCP Control PDU format for interspersed ROHC feedback packet

6.2.6

PDCP Control PDU for PDCP status report

Figure 6.2.6.1 shows the format of the PDCP Control PDU carrying one PDCP status report when a 12 bit SN length is
used, Figure 6.2.6.2 shows the format of the PDCP Control PDU carrying one PDCP status report when a 15 bit SN
length is used, and Figure 6.2.6.3 shows the format of the PDCP Control PDU carrying one PDCP status report when an
18 bit SN length is used. This format is applicable for DRBs mapped on RLC AM.

D/C

PDU Type

FMS

FMS (cont.)

Bitmap1 (optional)

...

Oct 1

Oct 2

Oct 3

BitmapN (optional)

Oct 2+N

Figure 6.2.6.1: PDCP Control PDU format for PDCP status report using a 12 bit SN

D/C

PDU Type

R

R

R

R

Oct 1

R

FMS

FMS (cont.)

Bitmap1 (optional)

...

Oct 2

Oct 3

Oct 4

BitmapN (optional)

Oct 3+N

Figure 6.2.6.2: PDCP Control PDU format for PDCP status report using a 15 bit SN

3GPP

Release 14

29

3GPP TS 36.323 V14.1.0 (2016-12)

D/C

PDU Type

R

R

FMS

Oct 1

FMS (cont.)

FMS (cont.)

Bitmap1 (optional)

...

Oct 2

Oct 3

Oct 4

BitmapN (optional)

Oct 3+N

Figure 6.2.6.3: PDCP Control PDU format for PDCP status report using an 18 bit SN

6.2.7

Void

6.2.8

RN user plane PDCP Data PDU with integrity protection

Figure 6.2.8.1 shows the format of the PDCP Data PDU for RNs when integrity protection is used. This format is
applicable for PDCP Data PDUs carrying data from DRBs mapped on RLC AM or RLC UM.

D/C

R

R

R

PDCP SN

PDCP SN (cont.)

Data

...

MAC-I

MAC-I (cont.)

MAC-I (cont.)

MAC-I (cont.)

Oct 1

Oct 2

Oct 3

Oct N-3

Oct N-2

Oct N-1

Oct N

Figure 6.2.8.1: PDCP Data PDU format for RN DRBs using integrity protection

6.2.9

User plane PDCP Data PDU with extended PDCP SN (15 bits)

Figure 6.2.9.1 shows the format of the PDCP Data PDU when a 15 bit SN length is used. This format is applicable for
PDCP Data PDUs carrying data from DRBs mapped on RLC AM.

3GPP

Release 14

30

3GPP TS 36.323 V14.1.0 (2016-12)

D/C

PDCP SN

PDCP SN (cont.)

Data

...

Oct 1

Oct 2

Oct 3

Figure 6.2.9.1: PDCP Data PDU format for DRBs using a 15 bit SN

6.2.10  User plane PDCP Data PDU for SLRB

Figure 6.2.10.1 shows the format of the PDCP Data PDU for SLRB used for one-to-many communication where a 16
bit SN length is used.

SDU Type

PGK Index

PTK Identity

PTK Identity (cont.)

PDCP SN

PDCP SN (cont.)

Data

...

Oct 1

Oct 2

Oct 3

Oct 4

Oct 5

Oct 6

Figure 6.2.10.1: PDCP Data PDU format for SLRB used for one-to-many communication

Figure 6.2.10.2 shows the format of the PDCP Data PDU for SLRB used for one-to-one communication where a 16 bit
SN length is used. MAC-I field is used only for the SLRB that needs integrity protection.

3GPP

Release 14

31

3GPP TS 36.323 V14.1.0 (2016-12)

SDU Type

R

R

R

R

R

KD-sess ID

KD-sess ID (cont.)

PDCP SN

PDCP SN (cont.)

Data

...

MAC-I

MAC-I (cont.)

MAC-I (cont.)

Oct 1

Oct 2

Oct 3

Oct 4

Oct 5

Oct 6

Oct N-3 (optional)

Oct N-2 (optional)

Oct N-1 (optional)

MAC-I (cont.)

Oct N (optional)

Figure 6.2.10.2: PDCP Data PDU format for SLRB used for one-to-one communication

6.2.11  User plane PDCP Data PDU with further extended PDCP SN (18

bits)

Figure 6.2.11.1 shows the format of the PDCP Data PDU when an 18 bit SN length is used. This format is applicable
for PDCP Data PDUs carrying data from DRBs mapped on RLC AM. The UE not supporting LWA shall consider the
PDCP Data PDU invalid if the P bit is set to 1.

D/C

P

R

R

R

R

PDCP SN

PDCP SN (cont.)

PDCP SN (cont.)

Data

...

Oct 1

Oct 2

Oct 3

Oct 4

Figure 6.2.11.1: PDCP Data PDU format for DRBs using an 18 bit SN

6.2.12  PDCP Control PDU for LWA status report

Figure 6.2.12.1 shows the format of the PDCP Control PDU carrying one LWA status report when a 12 bit SN length is
used, Figure 6.2.12.2 shows the format of the PDCP Control PDU carrying one LWA status report when a 15 bit SN
length is used, and Figure 6.2.12.3 shows the format of the PDCP Control PDU carrying one LWA status report when
an 18 bit SN length is used. This format is applicable for LWA DRBs.

3GPP

Release 14

32

3GPP TS 36.323 V14.1.0 (2016-12)

D/C

PDU Type

FMS

FMS (cont.)

HRW

HRW (cont.)

NMP

NMP (cont.)

Oct 1

Oct 2

Oct 3

Oct 4

Oct 5

Figure 6.2.12.1: PDCP Control PDU format for LWA status report using a 12 bit SN

D/C

PDU Type

R

R

R

R

Oct 1

R

R

R

FMS

FMS (cont.)

HRW

HRW (cont.)

NMP

NMP (cont.)

Oct 2

Oct 3

Oct 4

Oct 5

Oct 6

Oct 7

Figure 6.2.12.2: PDCP Control PDU format for LWA status report using a 15 bit SN

D/C

PDU Type

R

R

FMS

Oct 1

FMS (cont.)

FMS (cont.)

HRW

HRW (cont.)

HRW
(cont.)

R

R

R

R

NMP

NMP (cont.)

NMP (cont.)

Oct 2

Oct 3

Oct 4

Oct 5

Oct 6

Oct 7

Oct 8

Figure 6.2.12.3: PDCP Control PDU format for LWA status report using an 18 bit SN

3GPP

Release 14

33

3GPP TS 36.323 V14.1.0 (2016-12)

6.3

Parameters

6.3.1  General

If not otherwise mentioned in the definition of each field then the bits in the parameters shall be interpreted as follows:
the left most bit string is the first and most significant and the right most bit is the last and least significant bit.

Unless otherwise mentioned, integers are encoded in standard binary encoding for unsigned integers. In all cases the
bits appear ordered from MSB to LSB when read in the PDU.

6.3.2

PDCP SN

Length: 5, 7, 12, 15, 16, or 18 bits as indicated in table 6.3.2.1 except for NB-IoT which uses 7 bit PDCP SN for DRB.

Table 6.3.2.1: PDCP SN length

Length
5
7
12
15
16
18

Description

SRBs
DRBs, if configured by upper layers (pdcp-SN-Size [3])
DRBs, if configured by upper layers (pdcp-SN-Size [3])
DRBs, if configured by upper layers (pdcp-SN-Size [3])
SLRBs
DRBs, if configured by upper layers (pdcp-SN-Size [3])

6.3.3

Data

Length: Variable

The Data field may include either one of the following:

-  Uncompressed PDCP SDU (user plane data, or control plane data); or

-  Compressed PDCP SDU (user plane data only).

6.3.4  MAC-I

Length: 32 bits

The MAC-I field carries a message authentication code calculated as specified in subclause 5.7.

For control plane data that are not integrity protected, the MAC-I field is still present and should be padded with
padding bits set to 0.

6.3.5

COUNT

Length: 32 bits

For ciphering and integrity a COUNT value is maintained. The COUNT value is composed of a HFN and the PDCP
SN. The length of the PDCP SN is configured by upper layers.

HFN

PDCP SN

Figure 6.3.5.1: Format of COUNT

The size of the HFN part in bits is equal to 32 minus the length of the PDCP SN.

3GPP

Release 14

34

3GPP TS 36.323 V14.1.0 (2016-12)

NOTE:  When performing comparison of values related to COUNT, the UE takes into account that COUNT is a

32-bit value, which may wrap around (e.g., COUNT value of 232 - 1 is less than COUNT value of 0).

6.3.6

R

Length: 1 bit

Reserved. In this version of the specification reserved bits shall be set to 0. Reserved bits shall be ignored by the
receiver.

6.3.7

D/C

Length: 1 bit

Table 6.3.7.1: D/C field

Bit
0
1

Control PDU
Data PDU

Description

6.3.8

PDU type

Length: 3 bits

Table 6.3.8.1: PDU type

Description

PDCP status report
Interspersed ROHC feedback packet
LWA status report
reserved

Bit
000
001
010
011-
111

6.3.9

FMS

Length: 12 bits when a 12 bit SN length is used, 15 bits when a 15 bit SN length is used, and 18 bits when an 18 bit SN
length is used

PDCP SN of the first missing PDCP SDU.

6.3.10  Bitmap

Length: Variable

The length of the bitmap field can be 0.

The MSB of the first octet of the type "Bitmap" indicates whether or not the PDCP SDU with the SN (FMS + 1)
modulo (Maximum_PDCP_SN + 1) has been received and, optionally decompressed correctly. The LSB of the first
octet of the type "Bitmap" indicates whether or not the PDCP SDU with the SN (FMS + 8) modulo
(Maximum_PDCP_SN + 1) has been received and, optionally decompressed correctly.

Table 6.3.10.1 Bitmap

Description

PDCP SDU with PDCP SN = (FMS + bit position)
modulo (Maximum_PDCP_SN + 1) is missing in the
receiver. The bit position of Nth bit in the Bitmap is N,
i.e., the bit position of the first bit in the Bitmap is 1.
PDCP SDU with PDCP SN = (FMS + bit position)
modulo (Maximum_PDCP_SN + 1) does not need to be

Bit
0

1

3GPP

Release 14

35

3GPP TS 36.323 V14.1.0 (2016-12)

retransmitted. The bit position of Nth bit in the Bitmap is
N, i.e., the bit position of the first bit in the Bitmap is 1.

The UE fills the bitmap indicating which SDUs are missing (unset bit - ’0’), i.e. whether an SDU has not been received
or optionally has been received but has not been decompressed correctly, and which SDUs do not need retransmission
(set bit - ’1’), i.e. whether an SDU has been received correctly and may or may not have been decompressed correctly.

6.3.11

Interspersed ROHC feedback packet

Length: Variable

Contains one ROHC packet with only feedback, i.e. a ROHC packet that is not associated with a PDCP SDU as defined
in subclause 5.5.4.

6.3.12  PGK Index

Length: 5 bits

5 LSBs of PGK Identity as specified in [13].

6.3.13  PTK Identity

Length: 16 bits

PTK Identity as specified in [13].

6.3.14  SDU Type

Length: 3 bits

PDCP SDU type, i.e. Layer-3 Protocol Data Unit type as specified in [14]. PDCP entity may handle the SDU differently
per SDU Type, e.g. header compression is applicable to IP SDU but not ARP SDU and Non-IP SDU.

Table 6.3.14.1: SDU Type

Description

Bit
000
001
010
011
100-111

IP
ARP
PC5 Signaling
Non-IP
reserved

6.3.15  KD-sess ID

Length: 16 bits

KD-sess Identity as specified in [13].

6.3.16  NMP

Length: 12 bits when a 12 bit SN length is used, 15 bits when a 15 bit SN length is used, and 18 bits when an 18 bit SN
length is used.

Number of missing PDCP SDU(s) with associated COUNT value below the associated COUNT value corresponding to
HRW, starting from and including the associated COUNT value corresponding to FMS.

6.3.17  HRW

Length: 12 bits when a 12 bit SN length is used, 15 bits when a 15 bit SN length is used and 18 bits when an 18 bit SN
length is used.

3GPP

Release 14

36

3GPP TS 36.323 V14.1.0 (2016-12)

PDCP SN of the PDCP SDU received on WLAN with highest associated PDCP COUNT value.

6.3.18  P

Length: 1 bit

Polling indication. Set to 1 when eNB triggers a PDCP status report or LWA status report for LWA.

7

Variables, constants and timers

7.1

State variables

This sub clause describes the state variables used in PDCP entities in order to specify the PDCP protocol.

All state variables are non-negative integers.

The transmitting side of each PDCP entity shall maintain the following state variables:

a)  Next_PDCP_TX_SN

The variable Next_PDCP_TX_SN indicates the PDCP SN of the next PDCP SDU for a given PDCP entity. At
establishment of the PDCP entity, the UE shall set Next_PDCP_TX_SN to 0.

b)  TX_HFN

The variable TX_HFN indicates the HFN value for the generation of the COUNT value used for PDCP PDUs for a
given PDCP entity. At establishment of the PDCP entity, the UE shall set TX_HFN to 0.

The receiving side of each PDCP entity shall maintain the following state variables:

c)  Next_PDCP_RX_SN

The variable Next_PDCP_RX_SN indicates the next expected PDCP SN by the receiver for a given PDCP entity. At
establishment of the PDCP entity, the UE shall set Next_PDCP_RX_SN to 0.

d)  RX_HFN

The variable RX_HFN indicates the HFN value for the generation of the COUNT value used for the received PDCP
PDUs for a given PDCP entity. At establishment of the PDCP entity, the UE shall set RX_HFN to 0.

e) Last_Submitted_PDCP_RX_SN

For PDCP entities for DRBs mapped on RLC AM the variable Last_Submitted_PDCP_RX_SN indicates the SN of the
last PDCP SDU delivered to the upper layers. At establishment of the PDCP entity, the UE shall set
Last_Submitted_PDCP_RX_SN to Maximum_PDCP_SN.

f) Reordering_PDCP_RX_COUNT

This variable is used only when the reordering function is used. This variable holds the value of the COUNT following
the COUNT value associated with the PDCP PDU which triggered t-Reordering.

7.2

Timers

The transmitting side of each PDCP entity for DRBs shall maintain the following timers:

a) discardTimer

The duration of the timer is configured by upper layers [3]. In the transmitter, a new timer is started upon reception of
an SDU from upper layer.

The receiving side of each PDCP entity shall maintain the following timers only when the reordering function is used:

3GPP

Release 14

b) t-Reordering

37

3GPP TS 36.323 V14.1.0 (2016-12)

The duration of the timer is configured by upper layers [3]. This timer is used to detect loss of PDCP PDUs as specified
in the subclause 5.1.2.1.4. If t-Reordering is running, t-Reordering shall not be started additionally, i.e. only one t-
Reordering per PDCP entity is running at a given time.

The receiving side of each PDCP entity associated with LWA bearers shall maintain the following timers:

c) t-StatusReportType1

The duration of the timer is configured by upper layers (statusPDU-Periodicity-Type1 [3]). This timer is used to trigger
status report transmission for LWA as specified in the subclause 5.10.

d) t-StatusReportType2

The duration of the timer is configured by upper layers (statusPDU-Periodicity-Type2 and statusPDU-Periodicity-
Offset [3]). If statusPDU-Periodicity-Offset is configured and it is the first run of the timer after (re)configuration, the
duration of the timer is the sum of statusPDU-Periodicity-Type2 and statusPDU-Periodicity-Offset [3], otherwise the
duration of the timer is statusPDU-Periodicity-Type2. When configured, this timer is used to trigger status report
transmission for LWA as specified in the subclause 5.10.

7.3

Constants

a) Reordering_Window

Indicates the size of the reordering window. The size equals to 2048 when a 12 bit SN length is used, 16384 when a 15
bit SN length is used, or 131072 when 18 bit SN length is used, i.e. half of the PDCP SN space, for radio bearers that
are mapped on RLC AM.

b) Maximum_PDCP_SN is:

-  262143 if the PDCP entity is configured for the use of 18 bits SNs

-  65535 if the PDCP entity is configured for the use of 16 bits SNs

-  32767 if the PDCP entity is configured for the use of 15 bits SNs

-  4095 if the PDCP entity is configured for the use of 12 bit SNs

-  127 if the PDCP entity is configured for the use of 7 bit SNs

-  31 if the PDCP entity is configured for the use of 5 bit SNs

3GPP

Release 14

38

3GPP TS 36.323 V14.1.0 (2016-12)

Annex A (informative):
Change history

Change history after change control

Date

2007-12  RP-38
2008-03  RP-39
2008-05  RP-40
RP-40
RP-40
RP-40
RP-40
-

TSG #  TSG Doc.  CR  Rev
RP-070919  -
-
RP-080197  0001
-
-
RP-080412  0002
RP-080412  0003  1
RP-080387  0004  3
-
RP-080412  0006
-
RP-080412  0010
-
-

-

2008-09  RP-41
RP-41
RP-41
RP-41
2008-12  RP-42
RP-42
RP-42
RP-42

RP-080692  0013
RP-080692  0016
RP-080692  0023
RP-080692  0033
RP-081020  0038
RP-081020  0039
RP-081020  0040
RP-081020  0041

RP-42
RP-42

RP-081020  0042
RP-081020  0047

RP-42

RP-081020  0048

RP-42
RP-42
RP-42
RP-42
RP-42
RP-42
RP-42

RP-081020  0049
RP-081020  0050
RP-081020  0052
RP-081020  0054
RP-081020  0055
RP-081020  0057
RP-081020  0060

-
-
-
-
-
-
-
-

-
-

-

-
-
-
-
-
-
-

RP-42
2009-03  RP-43
RP-43
RP-43
RP-43
RP-43
RP-43
RP-43

RP-43
RP-43
2009-06  RP-44
RP-44

RP-44
2009-12  RP-46
2010-12  RP-50
2011-03  RP-51
RP-51
2012-03  RP-57
2012-12  RP-58

RP-081020  0061  1
-
RP-090130  0064
-
RP-090130  0065
-
RP-090130  0066
-
RP-090130  0067
-
RP-090130  0068
-
RP-090130  0069
RP-090130  0070  1

-
RP-090130  0071
RP-090130  0077
-
RP-090515  0078  1
RP-090515  0079  1

-
-

RP-090515  0080  2
-
-
-
RP-110280  0086
RP-110291  0087
-
RP-121377  0099  1
-
RP-121959  0100

RP-58
RP-58

RP-121959  0104  1
-
RP-121936  0106

2013-03  RP-59
2014-06  RP-64
RP-64
2014-09  RP-65

RP-130248  0109
RP-140869  0113
RP-140892  0123
RP-141498  0126

-
-
-
-

2014-12  RP-66
2015-03  RP-67
RP-67

RP-142135  0128  1
-
RP-150373  0133
-
RP-150374  0135

Subject/Comment

Approved at TSG-RAN #38 and placed under Change Control
CR to 36.323 with Update of E-UTRAN PDCP specification
Clarification of the BSR calculation
PDCP minor changes
Addition of a duplicate discard window
Reference to ROHCv2 profiles
Bitmap in the DL PDCP status report
Corrections to sections 5.5.1.1, 5.5.1.2.1 and 5.8 to correctly
implement CR0004 Rev 3 (instead of CR0004 Rev 2 of RP-
080412).
Restructuring of PDCP specification
Miscellaneous PDCP corrections
Correction to the PDCP structure
Initial TX_HFN and RX_HFN values
Clarification with regards to the PDCP state variables
CR 0039 to 36.323 on Correction to PDCP functional view
PDCP “in-sequence delivery and duplicate elimination” always on
Proposed CR to 36.323 on Processing of PDCP SDU received
from upper layer
Error in AM receive window behaviour
Proposed CR on the described scope of
Last_Submitted_PDCP_RX_SN
Proposed CR to move DIRECTION from parameters provided by
upper layer
Clarification on COUNT
Correction to PDCP procedure for SRB
Correction to the PDCP re-establishment procedure
Correction to PDCP functional view
Miscellaneous PDCP corrections
Proposed CR for error handling
Proposed CR to 36.323 on Correction to PDCP Control PDU
description
Corrections to PDCP STATUS REPORT
CR to specify maximum PDCP SDU size
CR with correction on PDCP function of maintaining SNs
Miscellaneous corrections to 36.323
Minor issues on PDCP
Security related corrections
CR to 36.323 on RRC Parameters
Corrections on BSR reporting and transmission/ retransmission
after an Handover
Corrections on PDCP services and functions
PDCP Control PDU as Data Available for transmission in PDCP
PDCP Status Report
Correction to PDCP PDU submission condition in lower layer re-
establishment
Minor correction and clarification to 36.323
Upgrade to the Release 9 - no technical change
Upgrade to the Release 10 - no technical change
Clarification on the number of ROHC instances in a PDCP entity
Addition of integrity protection of DRBs in PDCP for RNs
Introduction of Carrier aggregation enhancements
CR to 36.323 on introducing ROHC context continue for intra-ENB
handover
ROHC mode upon handover
Prevention of HFN de-synchronization due to PDCP SN over-
allocation
ROHC mode upon handover in UM DRB
Clarification of CID reuse
ROHC Feedback Handling
Clarification of the decompressor state and mode after PDCP re-
establishment
Introduction of dual connectivity in PDCP
Reconfiguration of PDCP reordering timer
Introduction of ProSe Direct Communication

Old  New

2.0.0  8.0.0
8.0.0  8.1.0
8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.2.0  8.2.1

8.2.1  8.3.0
8.2.1  8.3.0
8.2.1  8.3.0
8.2.1  8.3.0
8.3.0  8.4.0
8.3.0  8.4.0
8.3.0  8.4.0
8.3.0  8.4.0

8.3.0  8.4.0
8.3.0  8.4.0

8.3.0  8.4.0

8.3.0  8.4.0
8.3.0  8.4.0
8.3.0  8.4.0
8.3.0  8.4.0
8.3.0  8.4.0
8.3.0  8.4.0
8.3.0  8.4.0

8.3.0  8.4.0
8.4.0  8.5.0
8.4.0  8.5.0
8.4.0  8.5.0
8.4.0  8.5.0
8.4.0  8.5.0
8.4.0  8.5.0
8.4.0  8.5.0

8.4.0  8.5.0
8.4.0  8.5.0
8.5.0  8.6.0
8.5.0  8.6.0

8.5.0  8.6.0
8.6.0  9.0.0
9.0.0  10.0.0
10.0.0  10.1.0
10.0.0  10.1.0
10.1.0  11.0.0
11.0.0  11.1.0

11.0.0  11.1.0
11.0.0  11.1.0

11.1.0  11.2.0
11.2.0  11.3.0
11.3.0  12.0.0
12.0.0  12.1.0

12.1.0  12.2.0
12.2.0  12.3.0
12.2.0  12.3.0

3GPP

Release 14

39

3GPP TS 36.323 V14.1.0 (2016-12)

2015-06  RP-68
RP-68
RP-68
2015-12  RP-70
RP-70
2015-12  RP-70
RP-70
RP-70
2016-03  RP-71
RP-71
2016-06  RP-72
RP-72
RP-72
RP-72
RP-72
RP-72
RP-72
RP-72
2016-06  RP-72
2016-09  RP-73
RP-73
RP-73
2016-09  RP-73
2016-09  RP-73
2016-09  RP-73
2016-12  RP-74
RP-74

-
RP-150921  0137
-
RP-150921  0138
-
RP-150921  0139
RP-152053  0145
-
RP-152053  0144  1
RP-152074  0146
-
RP-152071  0148  1
RP-152072  0149  2
RP-160454  0155
-
RP-160457  0158  4
RP-161080  0160
-
RP-161078  0162  1
-
RP-161080  0163
RP-161078  0165
-
RP-161080  0166  1
RP-161080  0169
-
RP-161091  0171  4
-
RP-161080  0172
RP-161080  0160
-
RP-161756  0175  1
RP-161756  0177  1
-
RP-161756  0179
-
-
RP-161746  0174  2
-
-
RP-162318  0182
-
RP-162317  0185  1

-

-

COUNT derivation in ProSe
Miscellaneous corrections for DC
BSR Triggering for Split Bearers
Corrections to Sidelink
Update to Services expected from Lower Layers in DC
Introduction of UL split bearer in PDCP
Introduction of enhanced CA in PDCP
Introducing enhanced ProSe
Correction for KD-sess Identity in 36.323
Introduction of LWA into PDCP specification
Clarification on LWA
Data available for transmission due to PDCP data recovery
Correction for sidelink
Corrections on RoHC description
Clarification on Control PDU for LWA
Polling for LWA status report
Introduction of NB-IoT functionality to PDCP protocol
PDCP CR to capture C-IoT optimizations for non-NB-IoT UEs
Missing changes from CR0160 (Clarification on LWA) added
Addition of COUNT determination for the purpose of HRW setting
Clarification on NMP in LWA status report
Corrections to PDCP Status Reporting
MCC cleanup and missing text from v13.2.1 added
Introduction of PC5 V2V for 36.323
MCC cleanup
Correction of security handling upon connection suspension
Corrections to handling of uplink split

12.3.0  12.4.0
12.3.0  12.4.0
12.3.0  12.4.0
12.4.0  12.5.0
12.4.0  12.5.0
12.5.0  13.0.0
12.5.0  13.0.0
12.5.0  13.0.0
13.0.0  13.1.0
13.0.0  13.1.0
13.1.0  13.2.0
13.1.0  13.2.0
13.1.0  13.2.0
13.1.0  13.2.0
13.1.0  13.2.0
13.1.0  13.2.0
13.1.0  13.2.0
13.1.0  13.2.0
13.2.0  13.2.1
13.2.1  13.3.0
13.2.1  13.3.0
13.2.1  13.3.0
13.3.0  13.3.1
13.3.1  14.0.0
14.0.0  14.0.1
14.0.1  14.1.0
14.0.1  14.1.0

3GPP


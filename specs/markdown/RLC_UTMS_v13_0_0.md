3GPP TS 25.322 V13.0.0 (2015-12)

Technical Specification

3rd Generation Partnership Project;
Technical Specification Group Radio Access Network;
Radio Link Control (RLC) protocol specification
(Release 13)

The present document has been developed within the 3rd Generation Partnership Project (3GPP TM) and may be further elaborated for the purposes of 3GPP..
The present document has not been subject to any approval process by the 3GPP Organisational Partners and shall not be implemented.
This Specification is provided for future development work within 3GPP only. The Organisational Partners accept no liability for any use of this Specification.
Specifications and reports for implementation of the 3GPP TM system should be obtained via the 3GPP Organisational Partners' Publications Offices.

Release 13

2

3GPP TS 25.322 V13.0.0 (2015-12)

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

© 2015, 3GPP Organizational Partners (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC).
All rights reserved.

UMTS™ is a Trade Mark of ETSI registered for the benefit of its members
3GPP™ is a Trade Mark of ETSI registered for the benefit of its Members and of the 3GPP Organizational Partners
LTE™ is a Trade Mark of ETSI currently being registered for the benefit of its Members and of the 3GPP Organizational Partners
GSM® and the GSM logo are registered and owned by the GSM Association

3GPP

Release 13

3

3GPP TS 25.322 V13.0.0 (2015-12)

Contents
Foreword............................................................................................................................................................. 7

1

2

3
3.1
3.2

Scope ........................................................................................................................................................ 8

References ................................................................................................................................................ 8

Definitions and abbreviations ................................................................................................................... 8
Definitions ......................................................................................................................................................... 8
Abbreviations ..................................................................................................................................................... 8

4
4.1
4.2
4.2.1
4.2.1.1
4.2.1.1.1
4.2.1.1.2
4.2.1.2
4.2.1.2.1
4.2.1.2.2
4.2.1.3
4.2.1.3.1
4.2.1.3.2

General ..................................................................................................................................................... 9
Objective ............................................................................................................................................................ 9
Overview of the RLC sublayer architecture .................................................................................................... 10
Model of the RLC sublayer ........................................................................................................................ 10
Transparent mode (TM) RLC entities .................................................................................................. 12
Transmitting TM RLC entity .......................................................................................................... 12
Receiving TM RLC entity............................................................................................................... 12
Unacknowledged mode (UM) RLC entities ......................................................................................... 13
Transmitting UM RLC entity .......................................................................................................... 14
Receiving UM RLC entity .............................................................................................................. 15
Acknowledged mode (AM) RLC entity ............................................................................................... 15
Transmitting side ............................................................................................................................ 16
Receiving side ................................................................................................................................. 17

5

6
6.1

7

8
8.1
8.2

Functions ................................................................................................................................................ 17

Services provided to upper layers .......................................................................................................... 18
Mapping of services/functions onto logical channels ...................................................................................... 19

Services expected from MAC ................................................................................................................ 21

Elements for layer-to-layer communication ........................................................................................... 21
Primitives between RLC and upper layers ....................................................................................................... 21
Primitive parameters ........................................................................................................................................ 23

9
9.1
9.1.1
9.1.2
9.2
9.2.1
9.2.1.1
9.2.1.2
9.2.1.3
9.2.1.4
9.2.1.5
9.2.1.6
9.2.1.7
9.2.2
9.2.2.1
9.2.2.2
9.2.2.3
9.2.2.4
9.2.2.5
9.2.2.6
9.2.2.7
9.2.2.8
9.2.2.9
9.2.2.10
9.2.2.11
9.2.2.11.1
9.2.2.11.2

Elements for peer-to-peer communication ............................................................................................. 24
Protocol data units ........................................................................................................................................... 24
Data PDUs .................................................................................................................................................. 24
Control PDUs ............................................................................................................................................. 25
Formats and parameters ................................................................................................................................... 25
Formats ....................................................................................................................................................... 25
General ................................................................................................................................................. 26
TMD PDU ............................................................................................................................................ 26
UMD PDU ............................................................................................................................................ 26
AMD PDU ............................................................................................................................................ 27
STATUS PDU ...................................................................................................................................... 27
Piggybacked STATUS PDU ................................................................................................................ 28
RESET, RESET ACK PDU ................................................................................................................. 28
Parameters .................................................................................................................................................. 28
D/C field ............................................................................................................................................... 29
PDU Type ............................................................................................................................................. 29
Sequence Number (SN) ........................................................................................................................ 29
Polling bit (P) ....................................................................................................................................... 29
Extension bit (E) ................................................................................................................................... 29
Reserved 1 (R1) .................................................................................................................................... 30
Header Extension Type (HE)................................................................................................................ 30
Length Indicator (LI) ............................................................................................................................ 30
Data field .............................................................................................................................................. 34
Padding (PAD) ..................................................................................................................................... 36
SUFI ..................................................................................................................................................... 36
The No More Data super-field ........................................................................................................ 37
The Acknowledgement super-field ................................................................................................. 37

3GPP

Release 13

4

3GPP TS 25.322 V13.0.0 (2015-12)

9.2.2.11.3
9.2.2.11.4
9.2.2.11.5
9.2.2.11.6
9.2.2.11.7
9.2.2.11.8
9.2.2.11.9
9.2.2.12
9.2.2.13
9.2.2.14
9.3
9.3.1
9.3.1.1
9.3.1.2
9.3.2
9.3.2.1
9.3.2.2
9.3.2.3
9.3.3
9.3.3.1
9.3.3.2
9.3.3.3
9.3.3.4
9.3.3.5
9.4
9.5
9.6
9.7
9.7.1
9.7.2
9.7.3
9.7.3.1
9.7.3.2
9.7.3.3
9.7.3.4
9.7.3.5
9.7.4
9.7.5
9.7.6
9.7.7
9.7.8
9.7.9
9.7.10

The Window Size super-field ......................................................................................................... 37
The List super-field ......................................................................................................................... 38
The Bitmap super-field ................................................................................................................... 38
The Relative List super-field ........................................................................................................... 39
The Move Receiving Window Acknowledgement super-field ....................................................... 40
The Move Receiving Window (MRW) super-field ........................................................................ 40
The Poll (POLL) super-field ........................................................................................................... 41
Reserved 2 (R2) .................................................................................................................................... 41
Reset Sequence Number (RSN)............................................................................................................ 41
Hyper Frame Number Indicator (HFNI) ............................................................................................... 42
Protocol states .................................................................................................................................................. 42
State model for transparent mode entities .................................................................................................. 42
NULL State .......................................................................................................................................... 42
DATA_TRANSFER_READY State .................................................................................................... 42
State model for unacknowledged mode entities ......................................................................................... 42
NULL State .......................................................................................................................................... 42
DATA_TRANSFER_READY State .................................................................................................... 43
LOCAL_SUSPEND State .................................................................................................................... 43
State model for acknowledged mode entities ............................................................................................. 44
NULL State .......................................................................................................................................... 44
DATA_TRANSFER_READY State .................................................................................................... 44
RESET_PENDING State ..................................................................................................................... 44
LOCAL_SUSPEND State .................................................................................................................... 46
RESET_AND_SUSPEND State ........................................................................................................... 46
State variables .................................................................................................................................................. 46
Timers .............................................................................................................................................................. 49
Protocol Parameters ......................................................................................................................................... 51
Specific functions ............................................................................................................................................ 52
Polling function for acknowledged mode................................................................................................... 52
STATUS transmission for acknowledged mode ........................................................................................ 54
SDU discard function for acknowledged, unacknowledged, and transparent mode .................................. 55
Timer based discard, with explicit signalling ....................................................................................... 55
Timer based discard, without explicit signalling .................................................................................. 56
SDU discard after MaxDAT number of transmissions ......................................................................... 56
No_discard after MaxDAT number of transmissions ........................................................................... 56
SDU discard not configured ................................................................................................................. 56
Void ............................................................................................................................................................ 57
Local Suspend function for acknowledged and unacknowledged mode .................................................... 57
RLC Stop, RLC Continue function for acknowledged and unacknowledged mode .................................. 57
RLC re-establishment function for acknowledged and unacknowledged mode ........................................ 58
Ciphering for acknowledged and unacknowledged mode .......................................................................... 60
Reconfiguration of RLC parameters by upper layers ................................................................................. 60
Duplicate avoidance and reordering for unacknowledged mode................................................................ 61

10  Handling of unknown, unforeseen and erroneous protocol data ............................................................ 63
Erroneous Sequence Number ........................................................................................................................... 63
10.1
Inconsistent status indication ........................................................................................................................... 63
10.2
Invalid PDU format ......................................................................................................................................... 63
10.3
RLC PDU with CRC error ............................................................................................................................... 63
10.4

11
11.1
11.1.1
11.1.2
11.1.2.1
11.1.2.2
11.1.3
11.1.4
11.1.4.1
11.1.4.2
11.2
11.2.1

Elementary procedures ........................................................................................................................... 63
Transparent mode data transfer procedure ....................................................................................................... 64
General ....................................................................................................................................................... 64
Transmission of TMD PDU ....................................................................................................................... 64
TMD PDU contents to set .................................................................................................................... 64
Submission of TMD PDUs to the lower layer ...................................................................................... 64
Reception of TMD PDU ............................................................................................................................ 65
Abnormal cases .......................................................................................................................................... 65
Void ...................................................................................................................................................... 65
SDU discard without explicit signalling ............................................................................................... 65
Unacknowledged mode data transfer procedure .............................................................................................. 65
General ....................................................................................................................................................... 65

3GPP

Release 13

5

3GPP TS 25.322 V13.0.0 (2015-12)

11.2.2
11.2.2.1
11.2.2.2
11.2.3
11.2.3.1
11.2.3.2
11.2.4
11.2.4.1
11.2.4.2
11.2.4.3
11.2.4.4
11.3
11.3.1
11.3.2
11.3.2.1
11.3.2.1.1
11.3.2.1.2
11.3.2.2
11.3.3
11.3.3a
11.3.4
11.3.4.1
11.3.4.2
11.3.4.3
11.3.4.3.1
11.3.4.4
11.3.4.5
11.3.4.6
11.3.4.7
11.3.4.8
11.3.4.9
11.3.4.10
11.3.5
11.4
11.4.1
11.4.2
11.4.2.1
11.4.3
11.4.3.1
11.4.4
11.4.4a
11.4.5
11.4.5.1
11.4.5.2
11.4.5.3
11.5
11.5.1
11.5.2
11.5.2.1
11.5.2.2
11.5.2.3
11.5.3
11.5.4
11.5.4.1
11.6
11.6.1
11.6.2
11.6.2.1
11.6.2.2
11.6.3
11.6.3.1
11.6.4

Transmission of UMD PDU ....................................................................................................................... 66
UMD PDU contents to set .................................................................................................................... 66
Submission of UMD PDUs to the lower layer ..................................................................................... 66
Reception of UMD PDU ............................................................................................................................ 67
SDU discard and re-assembly ............................................................................................................... 67
Out of sequence SDU delivery ............................................................................................................. 68
Abnormal cases .......................................................................................................................................... 69
Length Indicator value reserved for UMD PDU................................................................................... 69
Invalid length indicator value ............................................................................................................... 69
SDU discard without explicit signalling ............................................................................................... 69
Invalid PDU size ................................................................................................................................... 69
Acknowledged mode data transfer procedure .................................................................................................. 69
General ....................................................................................................................................................... 69
Transmission of AMD PDU ....................................................................................................................... 70
AMD PDU contents to set .................................................................................................................... 71
Setting of the Polling bit ................................................................................................................. 72
Void ................................................................................................................................................ 72
Submission of AMD PDUs to lower layer ........................................................................................... 72
Reception of AMD PDU by the Receiver .................................................................................................. 72
Reached maximum number of attempts ..................................................................................................... 73
Abnormal cases .......................................................................................................................................... 73
Void ...................................................................................................................................................... 73
Receiving an AMD PDU outside the reception window ...................................................................... 73
Timer_Discard timeout ......................................................................................................................... 74
SDU discard with explicit signalling .............................................................................................. 74
Void ...................................................................................................................................................... 74
Invalid length indicator value ............................................................................................................... 74
Length Indicator value reserved for AMD PDU................................................................................... 74
Void ...................................................................................................................................................... 74
Receiving an AMD PDU within the reception window more than once (Handling of Duplicates) ..... 74
Full Buffer Behavior ............................................................................................................................. 74
Invalid PDU size ................................................................................................................................... 75
Transmission of POLL SUFI ..................................................................................................................... 75
RLC reset procedure ........................................................................................................................................ 75
General ....................................................................................................................................................... 75
Initiation ..................................................................................................................................................... 75
RESET PDU contents to set ................................................................................................................. 76
Reception of the RESET PDU by the Receiver ......................................................................................... 76
RESET ACK PDU contents to set ........................................................................................................ 77
Reception of the RESET ACK PDU by the Sender ................................................................................... 77
Reached maximum number of attempts ..................................................................................................... 78
Abnormal cases .......................................................................................................................................... 78
Timer_RST timeout .............................................................................................................................. 78
Void ...................................................................................................................................................... 78
Reception of the RESET PDU by the Sender ....................................................................................... 78
STATUS report transfer procedure .................................................................................................................. 79
General ....................................................................................................................................................... 79
Initiation ..................................................................................................................................................... 79
Piggybacked STATUS PDU ................................................................................................................ 79
STATUS PDU contents to set .............................................................................................................. 79
Submission of STATUS PDUs to the lower layer ................................................................................ 80
Reception of the STATUS PDU by the Sender .......................................................................................... 81
Abnormal cases .......................................................................................................................................... 81
Void ...................................................................................................................................................... 81
SDU discard with explicit signalling procedure .............................................................................................. 81
General ....................................................................................................................................................... 81
Initiation ..................................................................................................................................................... 82
Void ...................................................................................................................................................... 82
STATUS PDU contents to set .............................................................................................................. 83
Reception of the STATUS PDU by the Receiver....................................................................................... 84
STATUS PDU contents to set .............................................................................................................. 84
Termination ................................................................................................................................................ 85

3GPP

Release 13

6

3GPP TS 25.322 V13.0.0 (2015-12)

11.6.5
11.6.6
11.6.6.1
11.6.6.2
11.6.6.3
11.7
11.8

Expiration of timer Timer_MRW ............................................................................................................... 85
Abnormal cases .......................................................................................................................................... 85
Reception of obsolete/corrupted MRW SUFI by the Receiver ............................................................. 85
Void ...................................................................................................................................................... 86
Reception of obsolete/corrupted MRW_ACK SUFI by the Sender ..................................................... 86
Void ................................................................................................................................................................. 86
Void ................................................................................................................................................................. 86

Annex A (informative):

Change history ............................................................................................... 87

3GPP

Release 13

7

3GPP TS 25.322 V13.0.0 (2015-12)

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

8

3GPP TS 25.322 V13.0.0 (2015-12)

1

Scope

The present document specifies the Radio Link Control protocol for the UE-UTRAN radio interface.

Features for the current Release:

-  Transparent mode.

-  Unacknowledged mode.

-  Acknowledged mode.

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

3GPP TS 25.401: "UTRAN Overall Description".

3GPP TR 25.990: "Vocabulary for UTRAN".

3GPP TS 25.301: "Radio Interface Protocol Architecture".

3GPP TS 25.302: "Services provided by the Physical Layer".

3GPP TS 25.303: "Interlayer procedures in Connected Mode".

3GPP TS 25.304: "UE Procedures in Idle Mode and Procedures for Cell Reselection in Connected
Mode".

3GPP TS 25.321: "Medium Access Control (MAC); protocol specification".

3GPP TS 25.331: "Radio Resource Control (RRC); protocol specification".

3GPP TS 33.102: "3G security; Security architecture".

3

Definitions and abbreviations

3.1

Definitions

For the purposes of the present document, the terms and definitions given in [2] apply.

3.2

Abbreviations

For the purposes of the present document, the following abbreviations apply:

AM
AMD
ARQ
BCCH
BCH
C-

Acknowledged Mode
Acknowledged Mode Data
Automatic Repeat Request
Broadcast Control CHannel
Broadcast CHannel
Control-

3GPP

Release 13

9

3GPP TS 25.322 V13.0.0 (2015-12)

CCCH
CCH
CCTrCH
CRC
CTCH
DCCH
DCH
DL
DSCH
DTCH
FACH
FDD
L1
L2
L3
LI
LSB
MAC
MBMS
MCCH
MRW
MSB
MSCH
MTCH
PCCH
PCH
PDU
PHY
PhyCH
RACH
RLC
RRC
SAP
SDU
SHCCH
SN
SUFI
TCH
TDD
TFI
TM
TMD
TTI
U-
UE
UL
UM
UMD
UMTS
UTRA
UTRAN

Common Control CHannel
Control CHannel
Coded Composite Transport CHannel
Cyclic Redundancy Check
Common Traffic CHannel
Dedicated Control CHannel
Dedicated CHannel
DownLink
Downlink Shared CHannel
Dedicated Traffic CHannel
Forward link Access CHannel
Frequency Division Duplex
Layer 1 (physical layer)
Layer 2 (data link layer)
Layer 3 (network layer)
Length Indicator
Least Significant Bit
Medium Access Control
Multmedia Broadcast Multicast Service
MBMS point-to-multipoint Control CHannel
Move Receiving Window
Most Significant Bit
MBMS point-to-multipoint Scheduling CHannel
MBMS point-to-multipoint Traffic CHannel
Paging Control CHannel
Paging CHannel
Protocol Data Unit
PHYsical layer
Physical CHannels
Random Access CHannel
Radio Link Control
Radio Resource Control
Service Access Point
Service Data Unit
SHared channel Control CHannel
Sequence Number
SUper FIeld
Traffic CHannel
Time Division Duplex
Transport Format Indicator
Transparent Mode
Transparent Mode Data
Transmission Time Interval
User-
User Equipment
UpLink
Unacknowledged Mode
Unacknowledged Mode Data
Universal Mobile Telecommunications System
UMTS Terrestrial Radio Access
UMTS Terrestrial Radio Access Network

4

General

4.1

Objective

This subclause describes the architecture of the RLC sublayer.

3GPP

Release 13

10

3GPP TS 25.322 V13.0.0 (2015-12)

4.2

Overview of the RLC sublayer architecture

The model presented in this subclause is intended to support the definition of the RLC sublayer only, and is not meant
to specify or constrain the implementation of the protocol. The RLC sublayer consists of RLC entities, of which there
are three types: Transparent Mode (TM), Unacknowledged Mode (UM), and Acknowledged Mode (AM) RLC entities.

4.2.1  Model of the RLC sublayer

Figure 4.1 illustrates different RLC entities in the RLC model.

An UM and a TM RLC entity can be configured to be a transmitting RLC entity or a receiving RLC entity. The
transmitting RLC entity transmits RLC PDUs and the receiving RLC entity receives RLC PDUs. An AM RLC entity
consists of a transmitting side, and a receiving side, where the transmitting side of the AM RLC entity transmits RLC
PDUs and the receiving side of the AM RLC entity receives RLC PDUs.

Elementary procedures (see clause 11) are defined between a "Sender" and a "Receiver". In UM and TM, the
transmitting RLC entity acts as a Sender and the peer RLC entity acts as a Receiver. An AM RLC entity acts either as a
Sender or as a Receiver depending on the elementary procedure. The Sender is the transmitter of AMD PDUs and the
Receiver is the receiver of AMD PDUs. A Sender or a Receiver can reside at either the UE or the UTRAN.

There is one transmitting and one receiving RLC entity for each transparent mode (TM) and unacknowledged mode
(UM) service. There is one combined, transmitting and receiving entity for the acknowledged mode (AM) service.

In the present document, "transmitted" is equivalent to "submitted to the lower layer" unless otherwise explicitly stated.
Each RLC UM, and TM entity uses one logical channel to send or receive data PDUs. An AM RLC entity can be
configured to use one or two logical channels to send or receive data and control PDUs. If two logical channels are
configured, they are of the same type (DCCH or DTCH). In figure 4.1, the dashed lines between the AM-Entities
illustrate the possibility to send and receive RLC PDUs on separate logical channels, e.g. control PDUs on one and data
PDUs on the other. A more detailed description of the different entities is given in subclauses 4.2.1.1, 4.2.1.2 and
4.2.1.3.

3GPP

Release 13

11

3GPP TS 25.322 V13.0.0 (2015-12)

Upper Layers

RLC

MAC

N
A
R
T
U

e
c
a
f
r
e
t
n
I

o
i
d
a
R

S
M

.
v
i
e
c
e
R

.
v
i
e
c
e
R

y
t
i
t
n
E
-
r
T

y
t
i
t
n
E
-
M
U

y
t
i
t
n
E
-
M
A

.

m
s
n
a
r
T

y
t
i
t
n
E
-
M
U

.

m
s
n
a
r
T

y
t
i
t
n
E
-
r
T

.
v
i
e
c
e
R

.
v
i
e
c
e
R

y
t
i
t
n
E
-
r
T

y
t
i
t
n
E
-
M
U

y
t
i
t
n
E
-
M
A

.

m

s
n
a
r
T

y
t
i
t
n
E
-
M
U

.

m

s
n
a
r
T

y
t
i
t
n
E
-
r
T

e
d
i
s
g
n
i
v
i
e
c
e
R

e
d
i
s

g
n
i
t
t
i

m
s
n
a
r
T

e
d

i
s
g
n

i
v
i
e
c
e
R

e
d
i
s

g
n
i
t
t
i

m
s
n
a
r
T

Figure 4.1: Overview model of the RLC sublayer

3GPP

Release 13

12

3GPP TS 25.322 V13.0.0 (2015-12)

4.2.1.1

Transparent mode (TM) RLC entities

Figure 4.2 below shows the model of two transparent mode peer RLC entities. The logical channels used to
communicate with the lower layer are described in the figure below.

UE/UTRAN

Radio Interface (Uu)

UTRAN/UE

TM- SAP

TM- SAP

Transmitting
TM-   RLC
entity

Receiving
TM-   RLC
entity

Transmission
buffer

Segmentation

Reassembly

Reception
 buffer

CCCH/DTCH/SHCCH  –  UE
BCCH/PCCH/DCCH/DTCH  –  UTRAN

CCCH/DTCH/SHCCH

–  UTRAN

BCCH/PCCH/DCCH/DTCH  – UE

Figure 4.2: Model of two transparent mode peer entities

4.2.1.1.1

Transmitting TM RLC entity

The transmitting TM-RLC entity receives RLC SDUs from upper layers through the TM-SAP.

All received RLC SDUs must be of a length that is a multiple of one of the valid TMD PDU lengths.

If segmentation has been configured by upper layers and a RLC SDU is larger than the TMD PDU size used by the
lower layer for that TTI, the transmitting TM RLC entity segments RLC SDUs to fit the TMD PDUs size without
adding RLC headers. All the TMD PDUs carrying one RLC SDU are sent in the same TTI, and no segment from
another RLC SDU are sent in this TTI.

If segmentation has not been configured by upper layers, then more than one RLC SDU can be sent in one TTI by
placing one RLC SDU in one TMD PDU. All TMD PDUs in one TTI must be of equal length.

When the processing of a RLC SDU is complete, the resulting one or more TMD PDU(s) are/is submitted to the lower
layer through either a BCCH, DCCH, PCCH, CCCH, SHCCH or a DTCH logical channel.

4.2.1.1.2

Receiving TM RLC entity

The receiving TM-RLC entity receives TMD PDUs through the configured logical channels from the lower layer. If
segmentation is configured by upper layers, all TMD PDUs received within one TTI are reassembled to form the RLC
SDU.

If segmentation is not configured by upper layers, each TMD PDU is treated as a RLC SDU.

The receiving TM RLC entity delivers RLC SDUs to upper layers through the TM-SAP.

3GPP

Release 13

13

3GPP TS 25.322 V13.0.0 (2015-12)

4.2.1.2

Unacknowledged mode (UM) RLC entities

Figure 4.3 below shows the model of two unacknowledged mode peer RLC entities when duplicate avoidance and
reordering is not configured. The different functions shown in Figure 4.3 below apply to different logical channel types
as described in subclause 6.1.

UE/UTRAN

Radio Interface (Uu)

UTRAN/UE

UM-SAP

UM-SAP

Transmittin
g
UM RLC
entity

Receiving
UM RLC
entity

Transmission
buffer

Segmentation &
Concatenation

Add RLC header

Ciphering

Reassembly

Remove RLC
header

Reception
buffer

Deciphering

DCCH/DTCH – UE
CCCH/SHCCH/DCCH/DTCH/CTCH/
MCCH/MSCH/MTCH – UTRAN

DCCH/DTCH – UTRAN
CCCH/SHCCH/DCCH/DTCH/CTCH/
MCCH/MSCH/MTCH – UE

Figure 4.3: Model of two unacknowledged mode peer entities configured for use without duplicate
avoidance and reordering

Figure 4.3a below shows the model of two unacknowledged mode peer RLC entities configured for duplicate avoidance
and reordering. Because duplicate avoidance and reordering is only specified for MTCH/CCCH in this release,
ciphering/ deciphering is omitted.

3GPP

Release 13

14

3GPP TS 25.322 V13.0.0 (2015-12)

   UTRAN

Radio Interface (Uu)

UE

UM-SAP

UM-SAP

Transmission
buffer

Transmitting
UM RLC
entity

Receiving
UM RLC
entity

Segmentation &
Concatenation

Add RLC header

Reassembly

Remove RLC
header

Reception
buffer

Duplicate
avoidance and
reordering

 MTCH/CCCH - UTRAN

 MTCH/CCCH - UE

Figure 4.3a: Model of two unacknowledged mode peer entities configured for use with duplicate
avoidance and reordering

4.2.1.2.1

Transmitting UM RLC entity

The transmitting UM-RLC entity receives RLC SDUs from upper layers through the UM-SAP.

The transmitting UM RLC entity segments the RLC SDU into UMD PDUs of appropriate size, if the RLC SDU is
larger than the length of available space in the UMD PDU. The size of the UMD PDUs after segmentation and/or
concatenation shall be smaller than or equal to the largest UL UMD PDU size. If MAC-i/is has been configured and the
RLC PDU size is set to "flexible size", the size of the UMD PDUs after segmentation and/or concatenation shall be
larger than or equal to the Minimum UL RLC PDU size. If data to be transmitted is not enough to create a UMD PDU
of the minimum size, it is allowed to create a UMD PDU including all data to be transmitted, even if the resulting size is
smaller than the Minimum UL RLC PDU size. The UMD PDU may contain segmented and/or concatenated RLC
SDUs. UMD PDU may also contain padding to ensure that it is of a valid length. Length Indicators are used to define
boundaries between RLC SDUs within UMD PDUs unless the "Extension bit" already indicates that a UMD PDU
contains exactly one complete SDU. Length Indicators are also used to define whether Padding is included in the UMD
PDU.

If ciphering is configured and started, an UMD PDU is ciphered (except for the UMD PDU header) before it is
submitted to the lower layer.

The transmitting UM RLC entity submits UMD PDUs to the lower layer through either a CCCH, SHCCH, DCCH,
CTCH, DTCH, MCCH, MSCH or an MTCH logical channel.

3GPP

Release 13

15

3GPP TS 25.322 V13.0.0 (2015-12)

4.2.1.2.2

Receiving UM RLC entity

The receiving UM-RLC entity receives UMD PDUs through the configured logical channels from the lower layer.
When duplicate avoidance and reordering is configured there may be one or more than one input from the lower layer.
Inputs can be added or removed without changing the buffer contents, state variables or timers within the receiving UM
RLC entity. Where duplicate avoidance and reordering is not configured there is only one input from the lower layer
and it is not reconfigured.

When configured, duplicate avoidance and reordering is the first receive function that is applied to the input UMD PDU
streams in the receiving UM RLC entity. It can only be configured in a UE, it is not used in UTRAN. It completes
duplicate detection and re-ordering of the UMD PDUs that are received from the one or more inputs to produce a single
ordered sequence of PDUs that is passed to the next in sequence RLC receiver function.

The receiving UM RLC entity deciphers (if ciphering is configured and started) the received UMD PDUs (except for
the UMD PDU header). It removes RLC headers from received UMD PDUs, and reassembles RLC SDUs (if
segmentation and/or concatenation has been performed by the transmitting UM RLC entity).

If a receiving UM RLC entity is configured for out of sequence SDU delivery, it will reassemble SDUs and transfer
them to the upper layers as soon as all PDUs that contain the SDU have been received even if earlier PDUs have not yet
been received. It will store PDUs pending the retransmission of missing PDUs by the transmitting UM RLC. PDUs are
removed from storage after recovery of all of its associated SDUs, or by a sequence number window function or a
storage timer. Out of sequence SDU delivery is configured only in the UE and is only used with MCCH.

RLC SDUs are delivered by the receiving UM RLC entity to the upper layers through the UM-SAP. If SN_Delivery is
configured, the sequence number of RLC PDU in which RLC SDU is mapped to is also delivered to the upper layers
through the UM-SAP.

4.2.1.3

Acknowledged mode (AM) RLC entity

Figure 4.4 below shows the model of an acknowledged mode RLC entity.

The AM RLC entity can be configured to utilise one or two logical channels. The figure 4.4 shows the model of the AM
RLC entity when one logical channel (shown as a solid line) and when two logical channels (shown as dashed lines) are
used.

If one logical channel is configured, the transmitting side of the AM RLC entity submits AMD and Control PDUs to the
lower layer on that logical channel. If fixed RLC PDU size is configured the RLC PDU size shall be the same for AMD
PDUs and control PDUs. If flexible RLC PDU size is configured the AMD PDU size is variable up to a maximum RLC
PDU size.

In case two logical channels are configured in the uplink, AMD PDUs and control PDUs except acknowledgement
status report, MRW ACK SUFI and WINDOW SUFI shall be transmitted on the first logical channel, and
acknowledgement status reports, MRW ACK SUFI and WINDOW SUFI shall be transmitted on the second logical
channel. In case two logical channels are configured in the downlink, AMD and Control PDUs can be transmitted on
any of the two logical channels.

3GPP

Release 13

16

3GPP TS 25.322 V13.0.0 (2015-12)

Figure 4.4: Model of an acknowledged mode entity

4.2.1.3.1

Transmitting side

The transmitting side of the AM-RLC entity receives RLC SDUs from upper layers through the AM-SAP.

If fixed RLC PDU size is configured, RLC SDUs are segmented and/or concatenated into AMD PDUs of a fixed length.
The segmentation is performed if the received RLC SDU is larger than the length of available space in the AMD PDU.
The uplink AMD PDU size is a semi-static value that is configured by upper layers and can only be changed through re-
establishment of the AM RLC entity by upper layers.

If flexible RLC PDU size is configured, RLC SDUs are segmented and/or concatenated to create RLC PDUs larger than
or equal to the Minimum UL RLC PDU size and smaller than or equal to the largest UL AMD PDU size. If data to be
transmitted is not enough to create an AMD PDU of the minimum size, it is allowed to create an AMD PDU including
all data to be transmitted, even if the resulting size is smaller than the Minimum UL RLC PDU size.

NOTE:

In downlink, if flexible RLC PDU size is configured, RLC SDUs are segmented if the SDU is larger than
the maximum RLC PDU size. Concatenation may be performed up to the maximum RLC PDU size.

The AMD PDU may contain segmented and/or concatenated RLC SDUs. The AMD PDU may also contain Padding to
ensure that it is of a valid size. If fixed RLC PDU size is configured, Length Indicators or a special value of the HE field
can be used to define boundaries between RLC SDUs within AMD PDUs. Length Indicators are also used to define
whether Padding or Piggybacked STATUS PDU is included in the AMD PDU. If flexible RLC PDU size is configured,

3GPP

Release 13

17

3GPP TS 25.322 V13.0.0 (2015-12)

the Length Indicator size is configured by upper layers. The use of the special value of the HE field is configured by
higher layers.

After the segmentation and/or concatenation are performed, the AMD PDUs are placed in the Retransmission buffer
and at the MUX.

AMD PDUs buffered in the Retransmission buffer are deleted or retransmitted based on the status report found within a
STATUS PDU or Piggybacked STATUS PDU sent by the peer AM RLC entity. This status report may contain positive
or negative acknowledgements of individual AMD PDUs received by the peer AM RLC entity.

The MUX multiplexes AMD PDUs from the Retransmission buffer that need to be retransmitted, and the newly
generated AMD PDUs delivered from the Segmentation/Concatenation function.

The PDUs are delivered to the function that completes the AMD PDU header and potentially replaces padding with
piggybacked status information. A Piggybacked STATUS PDUs can be of variable size in order to match the amount of
free space in the AMD PDU. The AMD PDU header is completed based on the input from the RLC Control Unit that
indicates the values to set in various fields (e.g. Polling Bit). The function also multiplexes, if required, Control PDUs
received from the RLC Control Unit (RESET and RESET ACK PDUs), and from the Reception buffer (Piggybacked
STATUS and STATUS PDUs), with AMD PDUs.

The ciphering (if configured) is then applied to the AMD PDUs. The AMD PDU header is not ciphered. Piggybacked
STATUS PDU and Padding in AMD PDU (when present) are ciphered. Control PDUs (i.e. STATUS PDU, RESET
PDU, and RESET ACK PDU) are not ciphered.

The transmitting side of the AM RLC entity submits AMD PDUs to the lower layer through either one or two DCCH or
DTCH logical channels.

4.2.1.3.2

Receiving side

The receiving side of the AM-RLC entity receives AMD and Control PDUs through the configured logical channels
from the lower layer.

If fixed RLC PDU size is configured, the AMD PDU size is a semi-static value that is configured by upper layers and
can only be changed through re-establishment of the AM RLC entity by upper layers. In the case where the AMD PDU
size is not configured, it is determined based on the first PDU received. The downlink and uplink AMD PDU sizes need
not be the same.

If flexible RLC PDU size is configured, the AMD PDU size is variable up to the maximum RLC PDU size, and the
Length Indicator size is configured by upper layers.

AMD PDUs are routed to the Deciphering Unit, where AMD PDUs (minus the AMD PDU header) are deciphered (if
ciphering is configured and started), and then delivered to the Reception buffer.

The AMD PDUs are placed in the Reception buffer until a complete RLC SDU has been received. The Receiver
acknowledges successful reception or requests retransmission of the missing AMD PDUs by sending one or more
STATUS PDUs to the AM RLC peer entity, through its transmitting side. If a Piggybacked STATUS PDU is found in
an AMD PDU, it is delivered to the Retransmission buffer & Management Unit at the transmitting side of the AM RLC
entity, in order to purge the buffer of positively acknowledged AMD PDUs, and to indicate which AMD PDUs need to
be retransmitted.

Once a complete RLC SDU has been received, the associated AMD PDUs are reassembled by the Reassembly Unit and
delivered to upper layers through the AM-SAP.

RESET and RESET ACK PDUs are delivered to the RLC Control Unit for processing. If a response to the peer AM
RLC entity is needed, an appropriate Control PDU is delivered, by the RLC Control Unit to the transmitting side of the
AM RLC entity. The received STATUS PDUs are delivered to the Retransmission buffer and Management Unit at the
transmitting side of the AM RLC entity, in order to purge the buffer of positively acknowledged AMD PDUs, and to
indicate which AMD PDUs need to be retransmitted.

5

Functions

The following functions are supported by RLC sublayer. For an overall description of the following functions see [3]:

-  Segmentation and reassembly.

3GPP

Release 13

18

3GPP TS 25.322 V13.0.0 (2015-12)

-  Concatenation.

-  Padding.

-  Transfer of user data.

-  Error correction.

-

In-sequence delivery of upper layer PDUs.

-  Duplicate detection.

-  Flow control.

-  Sequence number check.

-  Protocol error detection and recovery.

-  Ciphering.

-  SDU discard.

-  Out of sequence SDU delivery.

-  Duplicate avoidance and reordering.

6

Services provided to upper layers

This clause describes the different services provided by RLC sublayer to upper layers. It also includes the mapping of
RLC functions to different RLC services. For a detailed description of the RLC services see [3].

-  Transparent data transfer Service:

  The following functions are needed to support transparent data transfer:

-  Segmentation and reassembly.

-  Transfer of user data.

-  SDU discard.

-  Unacknowledged data transfer Service:

  The following functions are needed to support unacknowledged data transfer:

-  Segmentation and reassembly.

-  Concatenation.

-  Padding.

-  Transfer of user data.

-  Ciphering.

-  Sequence number check.

-  SDU discard.

-  Out of sequence SDU delivery.

-  Duplicate avoidance and reordering.

-  Provisioning of sequence number.

-  Acknowledged data transfer Service:

3GPP

Release 13

19

3GPP TS 25.322 V13.0.0 (2015-12)

  The following functions are needed to support acknowledged data transfer:

-  Segmentation and reassembly.

-  Concatenation.

-  Padding.

-  Transfer of user data.

-  Error correction.

-

In-sequence delivery of upper layer PDUs.

-  Duplicate detection.

-  Flow Control.

-  Protocol error detection and recovery.

-  Ciphering.

-  SDU discard.

-  Maintenance of QoS as defined by upper layers.

-  Notification of unrecoverable errors.

6.1

Mapping of services/functions onto logical channels

The following tables show the applicability of services and functions to the logical channels in UL/DL and
UE/UTRAN. A '+' in a column denotes that the service/function is applicable for the logical channel in question
whereas a '-' denotes that the service/function is not applicable.

Table 6.1: RLC modes and functions in UE uplink side

Service

Functions

CCCH  SHCC

DCCH  DTCH

Transparent
Service

Unacknowledged
Service

Acknowledged
Service

Applicability
Segmentation
Transfer of user data
SDU Discard
Applicability
Segmentation
Concatenation
Padding
Transfer of user data
Ciphering
SDU Discard
Applicability
Segmentation
Concatenation
Padding
Transfer of user data
Flow Control
Error Correction
Protocol error detection
& recovery
Ciphering
SDU Discard

+
-
+
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

H
+
-
+
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

-
-
-
-
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+

+
+

+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+

+
+

3GPP

Release 13

20

3GPP TS 25.322 V13.0.0 (2015-12)

Table 6.2: RLC modes and functions in UE downlink side

Service

Functions

Transparent
Service

Unacknowl
edged
Service

Acknowled
ged
Service

Applicability
Reassembly
Transfer of user
data
Applicability
Reassembly
Deciphering
Sequence number
check
Transfer of user
data
Duplicate avoidance
and reordering
Out of sequence
SDU delivery
Applicability
Reassembly
Error correction
Flow Control
In sequence
delivery
Duplicate detection
Protocol error
detection &
recovery
Deciphering
Transfer of user
data
SDU Discard

BCC
H
+
-
+

PCC
H
+
-
+

SHCC
H
-
-
-

CCC
H
-
-
-

DCC
H
+
+
+

DTC
H
+
+
+

CTC
H
-
-
-

MCC
H
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

-

+
+
-
+

+

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

+
+
-
+

+

+

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

+
+
+
+

+

-

-

+
+
+
+
+

+
+

+
+

+

+
+
+
+

+

-

-

+
+
+
+
+

+
+

+
+

+

+
+
-
+

+

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

+
+
-
+

+

-

+

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

NOTE:  Duplicate avoidance and reordering function is optional in UE.

Table 6.3: RLC modes and functions in UTRAN downlink side

MTCH  MSCH

-
-
-

+
+
-
+

+

+

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

+
+
-
+

+

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

Service

Functions

Transparent
Service

Unacknowle
dged
Service

Acknowled
ged
Service

Applicability
Segmentation
Transfer of user
data
SDU Discard
Applicability
Segmentation
Concatenation
Padding
Ciphering
Transfer of user
data
SDU Discard
Applicability
Segmentation
Concatenation
Padding
Transfer of user
data
Flow Control
Error Correction
Protocol error
detection &
recovery
Ciphering
SDU Discard

BCCH  PCC
H
+
-
+

+
-
+

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

CCCH  SHCC

H
-
-
-

-
+
+
+
+
-
+

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
+
+
+
+
-
+

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

3GPP

DCC
H
+
+
+

DTC
H
+
+
+

CTC
H
-
-
-

MCC
H
-
-
-

+
+
+
+
+
+
+

+
+
+
+
+
+

+
+
+

+
+

+
+
+
+
+
+
+

+
+
+
+
+
+

+
+
+

+
+

-
+
+
+
+
-
+

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
+
+
+
+
-
+

+
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

MTCH  MSCH

-
-
-

-
+
+
+
+
-
+

+
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
+
+
+
+
-
+

+
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

Release 13

21

3GPP TS 25.322 V13.0.0 (2015-12)

Table 6.4: RLC modes and functions in UTRAN uplink side

Service

Functions

CCCH  SHCC

DCCH  DTCH

Transparent
Service

Unacknowledge
d
Service

Acknowledged
Service

Applicability
Reassembly
Transfer of user data
Applicability
Reassembly
Deciphering
Sequence number
check
Transfer of user data
Applicability
Reassembly
Error correction
Flow Control
In sequence delivery
Duplicate detection
Protocol error detection
& recovery
Deciphering
Transfer of user data
SDU Discard

+
-
+
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

H
+
-
+
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
+
+
+
+

+
+
+
+
+
+
+
+

+
+
+

+
+
+
+
+
+
+

+
+
+
+
+
+
+
+

+
+
+

7

Services expected from MAC

For a detailed description of the service provided by the MAC sublayer to upper layers see [3].

-  Data transfer.

8

Elements for layer-to-layer communication

The interaction between the RLC sublayer and other layers are described in terms of primitives where the primitives
represent the logical exchange of information and control between the RLC sublayer and other layers. The primitives
shall not specify or constrain the implementation.

8.1

Primitives between RLC and upper layers

The primitives between RLC and upper layers are shown in table 8.1.

3GPP

Release 13

22

3GPP TS 25.322 V13.0.0 (2015-12)

Table 8.1: Primitives between RLC and upper layers

Parameters

Ind.
Data, DiscardInfo

Resp.
Not Defined

Conf.
Status, MUI

Data,
Sequence_Number

Not Defined

Data, Error_Indicator

Not Defined

MUI

MUI

Not Defined

Not Defined

Not Defined

Req.
Data, CNF,
DiscardReq, MUI, UE-
ID type indicator
Data, UE-ID type
indicator, DiscardReq,
MUI
Data, UE-ID type
indicator, DiscardReq,
MUI
E/R, Stop (UM/AM
only), Continue
(UM/AM only),
Ciphering Elements
(UM/AM only),
TM_parameters (TM
only), UM_parameters
(UM only),
AM_parameters (AM
only) , SN_Delivery
(UM only)
N

Generic Name

RLC-AM-DATA

RLC-UM-DATA

RLC-TM-DATA

CRLC-CONFIG

CRLC-SUSPEND
(UM/AM only)
CRLC-RESUME
(UM/AM only)
CRLC-STATUS

Not Defined

Not Defined

No Parameter

Not Defined

Not Defined

VT(US) (UM only),
VT(S) (AM only)
Not Defined

Not Defined

EVC

Not Defined

Not Defined

Each Primitive is defined as follows:

RLC-AM-DATA-Req/Ind/Conf

-  RLC-AM-DATA-Req is used by upper layers to request transmission of an RLC SDU in acknowledged mode.

-  RLC-AM-DATA-Ind is used by the AM RLC entity to deliver to upper layers an RLC SDU that has been

transmitted in acknowledged mode and to indicate to upper layers of the discarded RLC SDU in the peer RLC
AM entity.

-  RLC-AM-DATA-Conf is used by the AM RLC entity to confirm to upper layers the reception of an RLC SDU

by the peer-RLC AM entity or to inform the upper layers of a discarded SDU.

RLC-UM-DATA-Req/Ind/Conf

-  RLC-UM-DATA-Req is used by upper layers to request transmission of an RLC SDU in unacknowledged mode.

-  RLC-UM-DATA-Ind is used by the UM RLC entity to deliver to upper layers an RLC SDU that has been

transmitted in unacknowledged mode. If SN_Delivery is configured, RLC-UM-DATA-Ind is used by the UM
RLC entity to deliver to upper layers also Sequence_Number.

-  RLC-UM-DATA-Conf is used by the UM RLC entity to inform the upper layers of a discarded SDU.

RLC-TM-DATA-Req/Ind/Conf

-  RLC-TM-DATA-Req is used by upper layers to request transmission of an RLC SDU in transparent mode.

-  RLC-TM-DATA-Ind is used by the TM RLC entity to deliver to upper layers an RLC SDU that has been

transmitted in transparent mode.

-  RLC-TM-DATA-Conf is used by the TM RLC entity to inform the upper layers of a discarded SDU.

CRLC-CONFIG-Req

This primitive is used by upper layers to establish, re-establish, release, stop, continue or modify the RLC. Ciphering
elements are included for UM and AM operation.

3GPP

Release 13

23

3GPP TS 25.322 V13.0.0 (2015-12)

CRLC-SUSPEND-Req/Conf

-  CRLC-SUSPEND-Req is used by upper layers to suspend the UM or AM RLC entity.

-  CRLC-SUSPEND-Conf is used by the UM or AM RLC entity to confirm that the entity is suspended.

CRLC-RESUME-Req

This primitive is used by upper layers to resume the UM or AM RLC entity after the UM or AM RLC entity has been
suspended.

CRLC-STATUS-Ind

It is used by an RLC entity to send status information to upper layers.

8.2

Primitive parameters

Following parameters are used in the primitives:

1)  The parameter Data is the RLC SDU that is mapped onto the Data field in RLC PDUs. When AM or UM RLC
entities are used, the length of the Data parameter is a multiple of 8 bits, otherwise (TM RLC entity) the length
of Data parameter is a bit-string whose length may not be a multiple of 8 bits.

2)  The parameter Confirmation Request (CNF) indicates whether the transmitting side of the AM RLC entity needs
to confirm the reception of the RLC SDU by the peer-RLC AM entity. If required, once all AMD PDUs that
make up the RLC SDU are positively acknowledged by the receiving AM RLC entity, the transmitting AM RLC
entity notifies upper layers.

3)  The parameter Message Unit Identifier (MUI) is an identity of the RLC SDU, which is used to indicate which

RLC SDU that is confirmed with the RLC-AM-DATA-Conf. primitive, or discarded with the RLC-
AM/UM/TM-DATA-Conf. Primitive.

4)  The parameter E/R indicates establishment, re-establishment, release or modification of an RLC entity, where re-
establishment is applicable to AM and UM RLC entities only. If re-establishment is requested, the state variables
and configurable parameters are initialised according to subclause 9.7.7. If release is requested, all protocol
parameters, variables and timers are released and the RLC entity enters the NULL state. If modification is
requested, the protocol parameters indicated by upper layers (e.g. ciphering parameters) are only modified, while
keeping the other protocol parameters, such as the protocol variables, protocol timers and protocol state
unchanged. AM RLC entities are always re-established if any of the uplink or downlink AMD PDU size is
changed. The modification of other protocol parameters does not require a re-establishment.

5)  The parameter Event Code (EVC) indicates the reason for the CRLC-STATUS-Ind e.g., unrecoverable errors

such as data link layer loss or recoverable status events such as reset.

6)  The parameter Ciphering Elements are only applicable for UM and AM operations. These parameters are

Ciphering Mode, Ciphering Key, Transmitting Activation Time (Sequence Number to activate a new ciphering
configuration at the Sender), Receiving Activation Time (Sequence Number to activate a new ciphering
configuration at the Receiver) and HFN (Hyper Frame Number).

7)  The AM_parameters are only applicable for AM operation. These parameters are AMD PDU size, which can be
either a fixed value or set to flexible size, largest UL AMD PDU size (only used when flexible PDU size is
configured by upper layers, see subclause 9.2.2.8), Length Indicator Size, In-sequence Delivery Indication
(indicating that RLC SDUs are delivered to upper layers in sequence or that they can be delivered out of
sequence), Timer values (see subclause 9.5), Use of a special value of the HE field (see subclause 9.2.2.7),
Protocol parameter values (see subclause 9.6), Polling triggers (see subclause 9.7.1), Status triggers (see
subclause 9.7.2), Periodical Status blocking configuration (see subclause 9.7.2), SDU discard mode (see
subclause 9.7.3), Minimum WSN (see subclause 9.2.2.11.3), and Send MRW. The Minimum WSN is always
greater than or equal to the number of transport blocks in the smallest transport block set. The Send MRW
indicates that the information of each discarded RLC SDU is sent to the Receiver, and the MRW SUFI is sent to
the Receiver even if no segments of the RLC SDU to be discarded were submitted to a lower layer.

8)  The parameter DiscardInfo indicates to upper layer the discarded RLC SDU in the peer-RLC AM entity. It is
applicable only when in-sequence delivery is configured and it is to be used when upper layers require the
reliable data transfer.

3GPP

Release 13

24

3GPP TS 25.322 V13.0.0 (2015-12)

9)  The Stop parameter is applicable to AM and UM RLC entities only and indicates to the RLC entity to (see

subclause 9.7.6):

-  not transmit nor receive any RLC PDUs.

10) The Continue parameter is applicable to AM and UM RLC entities only and indicates to the RLC entity to

continue transmission and reception of RLC PDUs.

11) The UM_parameters are only applicable for UM operation. It contains Timer_Discard value (see subclause 9.5),
use Alternative E-bit interpretation (see subclause 9.2.2.5), largest UL UMD PDU size (see subclause 9.2.2.8),
DL RLC UM LI size (see subclause 9.2.2.8) and SN_Delivery. For a receiving UM RLC in a UE, an additional
parameter indicating use/ no use of out of sequence SDU delivery is included (see subclause 11.2.3.2). If out of
sequence SDU delivery is used, the parameters OSD_Window_Size (see subclause 9.6) and the timeout value of
Timer_OSD (see subclause 9.5) are included. For a receiving UM RLC in a UE, an additional parameter
indicating use/ no use of duplicate avoidance and reordering is included (see subclause 9.7.10). If duplicate
avoidance and reordering is used, the parameters DAR_Window_Size (see subclause 9.6) and the timeout value
of Timer_DAR (see subclause 9.5) are included. If out-of-sequence support is configured, the parameter
Configured_Rx_Window_Size is included. If SN_Delivery parameter is configured, the receiving RLC entity
delivers an RLC SDU with Sequence_Number to the upper layers. When SN_Delivery parameter is configured,
the DL transmitting RLC entity should neither concatenate nor segment RLC SDUs, the UL transmitting RLC
entity shall not concatenate RLC SDUs and may segment RLC SDUs.

12) The TM_parameters are only applicable for TM operation. It contains e.g. segmentation indication (see

subclauses 9.2.2.9 and 11.1.2.1), Timer_Discard value (see subclause 9.5) and delivery of erroneous SDU
indication (see subclause 11.1.3).

13) The N parameter indicates that an RLC entity will not send a PDU with "Sequence Number">=VT(S)+N for AM

and "Sequence Number">=VT(US)+N for UM, where N is a non-negative integer.

14) The VT(S) parameter indicates the value of the Send State Variable for the case of the AM.

15) The VT(US) parameter indicates the value of the UM Data State Variable, for the case of the UM.

16) The Error_Indicator parameter indicates that the RLC SDU is erroneous (see subclause 11.1.3).

17) The parameter UE-ID type indicator indicates the RNTI type (U-RNTI or C-RNTI) to be used for the associated

RLC SDU. This parameter is not required at the UE.

18) The parameter DiscardReq indicates whether the transmitting RLC entity needs to inform the upper layers of the
discarded RLC SDU. If required, the transmitting RLC entity notifies upper layers when the SDU is discarded.

19) The parameter Status is only applicable for AM operation. This parameter indicates whether a RLC SDU is

successfully transmitted or discarded.

20) The parameter Sequence_Number is the value that is mapped onto the Sequence Number (SN) field in an RLC

PDU. It is applicable only for UM operation when SN_Delivery is configured for the UMD RLC entity.

21) The parameter Minimum UL PDU size is applicable for AM and UM operation in the uplink. The Minimum UL
PDU size determines the smallest size of the RLC AMD or UMD PDU after segmentation or concatenation (see
section 9.2.2.9). If data to be transmitted is not enough to create a PDU of the minimum size, it is allowed to
create a PDU including all data to be transmitted, even if the resulting size is smaller than the Minimum UL RLC
PDU size.

9

Elements for peer-to-peer communication

9.1

Protocol data units

The structures defined in this subclause are normative.

9.1.1

Data PDUs

a)  TMD PDU (Transparent Mode Data PDU).

3GPP

Release 13

25

3GPP TS 25.322 V13.0.0 (2015-12)

  The TMD PDU is used to convey RLC SDU data without adding any RLC overhead. The TMD PDU is used by

RLC when it is in transparent mode.

b)  UMD PDU (Unacknowledged Mode Data PDU).

  The UMD PDU is used to convey sequentially numbered PDUs containing RLC SDU data. UMD PDUs are

used by RLC when it is configured for unacknowledged data transfer.

c)  AMD PDU (Acknowledged Mode Data PDU).

  The AMD PDU is used to convey sequentially numbered PDUs containing RLC SDU data. AMD PDUs are

used by RLC when it is configured for acknowledged data transfer.

9.1.2

Control PDUs

Control PDUs are only used in acknowledged mode.

a)  STATUS PDU and Piggybacked STATUS PDU.

  The STATUS PDU and the Piggybacked STATUS PDU are used:

-  by the Receiver to inform the Sender about missing and received AMD PDUs in the Receiver;

-  by the Receiver to inform the Sender about the size of the allowed transmission window;

-  by the Sender to request the Receiver to move the reception window; and

-  by the Receiver to acknowledge the Sender about the reception of the request to move the reception window.

b)  RESET PDU.

  The RESET PDU is used to reset all protocol states, protocol variables and protocol timers of the peer RLC

entity in order to synchronise the two peer entities. It is sent by the Sender to the Receiver.

c)  RESET ACK PDU.

  The RESET ACK PDU is an acknowledgement to the RESET PDU. It is sent by the Receiver to the Sender.

Data Transfer Mode
Transparent
Unacknowledged
Acknowledged

Table 9.1: RLC PDU names and descriptions

PDU name

Description

TMD
UMD
AMD
STATUS

Piggybacked
STATUS

RESET
RESET ACK

Transparent mode data
Sequenced unacknowledged mode data
Sequenced acknowledged mode data
Solicited or Unsolicited Status Report, Change
window size command, SDU discard command, or
SDU discard acknowledgement
Piggybacked Solicited or Unsolicited Status Report,
Change window size command, SDU discard
command, or SDU discard acknowledgement
Reset Command
Reset Acknowledgement

9.2

Formats and parameters

The formats of RLC PDUs and their parameters defined in this subclause are normative.

9.2.1

Formats

This subclause specifies the format of the RLC PDUs. The parameters of each RLC PDU are explained in subclause
9.2.2.

3GPP

Release 13

26

3GPP TS 25.322 V13.0.0 (2015-12)

9.2.1.1

General

An RLC PDU is a bit string. In the figures in subclause 9.2, bit strings are represented by tables in which the first bit is
the leftmost one on the first line of the table, the last bit is the rightmost one on the last line of the table, and more
generally the bit string is to be read from left to right and then in the reading order of the lines.

Depending on the provided service, RLC SDUs are bit strings, with any non-null length, or bit strings with a multiple of
8 bits in length. An RLC SDU is included into an RLC PDU from first bit onward.

9.2.1.2

TMD PDU

The TMD PDU is used to transfer user data when RLC is operating in transparent mode. No overhead is added to the
SDU by RLC. The data length is not constrained to be a multiple of 8 bits.

Data

Figure 9.1: TMD PDU

9.2.1.3

UMD PDU

The UMD PDU is used to transfer user data when RLC is operating in unacknowledged mode. The length of the data
part shall be a multiple of 8 bits. The UMD PDU header consists of the first octet, which contains the "Sequence
Number". The RLC header consists of the first octet and all the octets that contain "Length Indicators".

Sequence Number
Length Indicator

.
.
.

Length Indicator

E
E

E

Oct1

(Optional) (1)

(Optional)

Data

PAD

(Optional)

Last Octet

NOTE (1):  The "Length Indicator" may be 15 bits.

Figure 9.2: UMD PDU

3GPP

Release 13

27

3GPP TS 25.322 V13.0.0 (2015-12)

9.2.1.4

AMD PDU

The AMD PDU is used to transfer user data, piggybacked status information and the Polling bit when RLC is operating
in acknowledged mode. The length of the data part shall be a multiple of 8 bits. The AMD PDU header consists of the
first two octets, which contain the "Sequence Number". The RLC header consists of the first two octets and all the
octets that contain "Length Indicators".

D/C

Sequence Number

Sequence Number

P

Length Indicator

HE

E

Oct1
Oct2
Oct3

(Optional) (1)

.
.
.

Length Indicator

E

Data

PAD or a piggybacked STATUS PDU

OctN

Figure 9.3: AMD PDU

NOTE (1):  The "Length Indicator" may be 15 bits.

9.2.1.5

STATUS PDU

The STATUS PDU is used to exchange status information between two RLC AM entities.

The format of the STATUS PDU is given in figure 9.4 below. The length of each super field (SUFI) is dependent on its
type and contents.

D/C   PDU type            SUFI1

SUFI1

…

SUFIK

PAD

Oct 1

Oct2

OctN

Figure 9.4: STATUS PDU

A STATUS PDU can include super-fields of different types. The size of a STATUS PDU is variable and upper bounded
by the maximum RLC PDU size used by the logical channel on which the control PDUs are sent. If fixed RLC PDU
size has been configured by upper layers, padding shall be included to match one of the PDU sizes used by the logical
channel on which the control PDUs are sent. The length of the STATUS PDU shall be a multiple of 8 bits. If flexible
RLC PDU size has been configured by upper layers padding is only included to make the length of the STATUS PDU a
multiple of 8 bits.

3GPP

Release 13

28

3GPP TS 25.322 V13.0.0 (2015-12)

9.2.1.6

Piggybacked STATUS PDU

The format of the piggybacked STATUS PDU is the same as for the STATUS PDU except that the D/C field is
replaced by a reserved bit (R2). This PDU can be piggybacked in an AMD PDU if the data leaves out enough room in
the AMD PDU. The PDU Type field is set to "000" and all other values are invalid for this version of the protocol.

R2  PDU Type

SUFI1

SUFI1

…

SUFIK

PAD

Oct1

Oct2

OctN

Figure 9.5: Piggybacked STATUS PDU

9.2.1.7

RESET, RESET ACK PDU

The RESET PDU includes a one-bit sequence number field (RSN). The value of this bit is carried over in the RESET
ACK PDU sent in response in order to allow the peer entity to identify which RESET PDU it was sent in response to.

D/C

PDU Type  RSN

              R1

Oct1

HFNI

HFNI
HFNI

PAD

Figure 9.6: RESET, RESET ACK PDU

OctN

The size of a RESET or RESET ACK PDU is variable and upper bounded by the maximum RLC PDU size used by the
logical channel on which the control PDUs are sent. If fixed RLC PDU size has been configured by upper layers,
padding shall be included to match one of the PDU sizes used by the logical channel on which the control PDUs are
sent. The length of the RESET or RESET ACK PDU shall be a multiple of 8 bits. If flexible RLC PDU size has been
configured by upper layers padding is only included to make the length of the RESET or RESET ACK PDU a multiple
of 8 bits.

9.2.2

Parameters

If not otherwise mentioned in the definition of each field, the bits in the parameters shall be interpreted as follows: the
left-most bit string is the first and most significant and the right most bit is the last and least significant bit.

Unless otherwise mentioned, integers are encoded in standard binary encoding for unsigned integers. In all cases,
including when a value extends over more than one octet as shown in the tables, the bits appear ordered from MSB to
LSB when read in the RLC PDU.

3GPP

Release 13

29

3GPP TS 25.322 V13.0.0 (2015-12)

9.2.2.1

D/C field

Length: 1bit.

The D/C field indicates the type of an AM PDU. It can be either data or control PDU.

Bit
0
1

Control PDU
Data PDU

Description

9.2.2.2

PDU Type

Length: 3 bit.

The PDU type field indicates the Control PDU type.

Bit
000
001
010
011-111

PDU Type

STATUS
RESET
RESET ACK
Reserved
(PDUs with this
coding will be
discarded by
this version of
the protocol).

9.2.2.3

Sequence Number (SN)

This field indicates the "Sequence Number" of the RLC PDU, encoded in binary.

PDU type
AMD PDU
UMD PDU

12 bits
7 bits

Length

Used for retransmission and reassembly
Used for reassembly

Notes

9.2.2.4

Polling bit (P)

Length: 1bit.

This field is used to request a status report (one or several STATUS PDUs) from the Receiver.

Bit
0
1

Description
Status report not requested
Request a status report

9.2.2.5

Extension bit (E)

Length: 1bit.

The interpretation of this bit depends on RLC mode and higher layer configuration:

-

In the UMD PDU, the "Extension bit" in the first octet has either the normal E-bit interpretation or the alternative
E-bit interpretation depending on higher layer configuration. The "Extension bit" in all the other octets always
has the normal E-bit interpretation.

-

In the AMD PDU, the "Extension bit" always has the normal E-bit interpretation.

Normal E-bit interpretation:

3GPP

Release 13

30

3GPP TS 25.322 V13.0.0 (2015-12)

Alternative E-bit interpretation:

Bit
0

1

Bit
0

1

Description

The next field is data, piggybacked STATUS
PDU or padding
The next field is Length Indicator and E bit

Description

The next field is a complete SDU, which is not
segmented, concatenated or padded.
The next field is Length Indicator and E bit

9.2.2.6

Reserved 1 (R1)

Length: 3 bits.

This field in the RESET PDU and RESET ACK PDU is used to have a multiple of 8 bits in length. Its shall always be
coded to "000". Other values are reserved and will be considered invalid for this version of the protocol.

9.2.2.7

Header Extension Type (HE)

Length: 2 bits.

This two-bit field indicates if the next octet is data or a "Length Indicator" and E bit.

Value
00
01

10

11

Description

The succeeding octet contains data
The succeeding octet contains a length indicator and E
bit
This value is the special value of HE field and indicates
that the succeeding octet contains data and the last
octet of the PDU is the last octet of an SDU.
Reserved (PDUs with this coding will be discarded by
this version of the protocol).

9.2.2.8

Length Indicator (LI)

Unless the "Extension bit" indicates that a UMD PDU contains a complete SDU which is not segmented, concatenated
or padded, or the HE field indicates that an AMD PDU contains the last octet of the RLC SDU, a "Length Indicator" is
used to indicate the last octet of each RLC SDU ending within the PDU. If the "Extension bit" indicates that the UMD
PDU contains a complete SDU which is not segmented, concatenated or padded, or the HE field indicates that an AMD
PDU contains the last octet of the SDU, no LIs are present in this RLC PDU.

Except for the predefined values reserved for special purposes and listed in the tables below, the "Length Indicator"
shall:

-  be set to the number of octets between the end of the RLC header and up to and including the last octet of an

RLC SDU segment;

-  be included in the PDUs that they refer to.

The size of the "Length Indicator" may be either 7 bits or 15 bits. The "Length Indicator" size is determined
independently for uplink and downlink. The value of a "Length Indicator" shall not exceed the values specified in
subclauses 11.2.4.2 and 11.3.4.5 respectively for UMD and AMD PDUs.

The "Length Indicators" which refer to the same PDU shall:

-  not be reordered in case of retransmission;

-  be in the same order as the RLC SDUs that they refer to.

For AM uplink and for AM downlink when "Fixed RLC PDU size" is configured:

3GPP

Release 13

31

3GPP TS 25.322 V13.0.0 (2015-12)

-

if the "AMD PDU size" is ≤ 126 octets:

-  7-bit "Length Indicators" shall be used.

-  else:

-  15-bit "Length Indicators" shall be used.

-

the size of the "Length Indicator" is always the same for all AMD PDUs, for one RLC entity.

For AM downlink and AM uplink when "Flexible RLC PDU size" is configured:

-

if "Length Indicator size" is set to 7 bits:

-  7-bit "Length Indicators" shall be used.

-   else:

-  15-bit "Length Indicators" shall be used.

For UM uplink:

-

if the "largest UL UMD PDU size" is ≤ 125 octets:

-  7-bit "Length Indicators" shall be used.

-  else:

-  15-bit "Length Indicators" shall be used.

For UM downlink:

-

the "Length Indicator" size provided in "DL RLC UM LI size" shall be used.

For UM:

-  between modifications of the "largest UMD PDU size", the size of the "Length Indicator" is the same for all

UMD PDUs;

-

-

-

-

-

-

if the RLC SDU begins in the beginning of the RLC PDU; and

if the RLC PDU is transmitted in uplink; and

if the "Length Indicators" indicating that a RLC SDU ended exactly in the end or one octet short (only when 15-
bit "Length Indicators" is used) of the previous RLC PDU are not present; and

if the "Extension bit" does not indicate that the UMD PDU contains a complete SDU which is not segmented,
concatenated or padded; and

if the "Length Indicator" indicating that the first data octet in this RLC PDU is the first octet of an RLC SDU and
the last octet in this RLC PDU is the last octet of the same RLC SDU is not present; and

if the "Length Indicator" indicating that the first data octet in this RLC PDU is the first octet of an SDU and the
same RLC SDU is one octet short of exactly filling the PDU (only when 15-bit "Length Indicators" is used) is
not present:

-

if 7-bit "Length Indicator" is used:

-

the "Length Indicator" with value "111 1100" shall be used.

-

if 15-bit "Length Indicator" is used:

-

the "Length Indicator" with value "111 1111 1111 1100" shall be used.

-

in downlink:

-

if 7-bit "Length Indicator" is used:

3GPP

Release 13

32

3GPP TS 25.322 V13.0.0 (2015-12)

-

-

the Receiver shall be prepared to receive the "Length Indicator" with value "111 1100";

the Receiver shall follow the discard rules in subclause 11.2.3 both when the "Length Indicator" with
value "111 1100" is present and when it is absent.

-

if 15-bit "Length Indicator" is used:

-

-

the Receiver shall be prepared to receive the "Length Indicator" with value "111 1111 1111 1100";

the Receiver shall follow the discard rules in subclause 11.2.3 both when the "Length Indicator" with
value "111 1111 1111 1100" is present and when it is absent.

In the case where the end of the last segment of an RLC SDU exactly ends at the end of a PDU and there is no "Length
Indicator" that indicates the end of the RLC SDU, and the HE field of the PDU does not indicate that the last octet of
the  AMD PDU is the last octet of an SDU, and the "Extension bit" of the following PDU does not indicate that the
UMD PDU contains a complete SDU which is not segmented, concatenated or padded, and the "Length Indicator" of
the following PDU does not indicate that the first data octet in that PDU is the first octet of an SDU and the last octet in
that PDU is the last octet of the same SDU, and the "Length Indicator" of the following PDU does not indicate that the
first data octet in that RLC PDU is the first octet of an SDU and the same RLC SDU is one octet short of exactly filling
the PDU (only when 15-bit "Length Indicators" is used):

-

if 7-bit "Length Indicator" is used:

-  a "Length Indicator" with value "000 0000" shall be placed as the first "Length Indicator" in the following

PDU;

-

if 15-bit "Length Indicator" is used:

-  a "Length Indicator" with value "000 0000 0000 0000" shall be placed as the first "Length Indicator" in the

following PDU.

In the case where a PDU contains a 15-bit "Length Indicator" indicating that an RLC SDU ends with one octet left in
the PDU, the last octet of this PDU shall:

-  be padded by the Sender and ignored by the Receiver though there is no "Length Indicator" indicating the

existence of Padding; and

-  not be filled with the first octet of the next RLC SDU data.

In the case where 15-bit "Length Indicators" are used in a PDU and the last segment of an RLC SDU is one octet short
of exactly filling the PDU and there is no "Length Indicator" that indicates the end of the RLC SDU:

-

if a 15-bit "Length Indicator" is used for the following PDU:

-

-

the "Length Indicator" with value "111 1111 1111 1011" shall be placed as the first "Length Indicator" in the
following PDU;

the remaining one octet in the current PDU shall be padded by the Sender and ignored at the Receiver though
there is no "Length Indicator" indicating the existence of Padding;

-

if a 7-bit "Length Indicator" size is configured for the following PDU:

-

if RLC is configured for UM mode:

-

if the "Extension bit" of that PDU does not indicate that the UMD PDU contains a complete SDU which
is not segmented, concatenated or padded, and the "Length Indicator" of that PDU does not indicate that
the first data octet in that PDU is the first octet of an SDU and the last octet in that PDU is the last octet of
the same SDU:

-

the "Length Indicator" with value "000 0000" shall be placed as the first "Length indicator" in the
following PDU;

-

the "Sequence Number" shall be incremented by 2 before it is transmitted.

For UM and AM RLC:

3GPP

Release 13

33

3GPP TS 25.322 V13.0.0 (2015-12)

-

if a 7 bit "Length Indicator" is used in a RLC PDU and one or more padding octets are present in the RLC PDU
after the end of the last RLC SDU:

-

indicate the presence of padding by including a "Length Indicator" with value "1111111" as the last "Length
Indicator" in the PDU.

-

if a 15 bit "Length Indicator" is used in a RLC PDU and two or more padding octets are present in the RLC PDU
after the end of the last RLC SDU:

-

indicate the presence of padding by including a "Length Indicator" with value "111 1111 1111 1111" as the
last "Length Indicator" in the PDU.

NOTE:  After the "Length Indicator" indicating the presence of padding has been included in the RLC PDU, the

length of the padding may be zero.

In the case where the "alternative E-bit interpretation" is configured for UM RLC and an RLC PDU contains a segment
of an SDU but neither the first octet nor the last octet of this SDU:

-

if a 7-bit "Length Indicator" is used:

-

the "Length Indicator" with value "111 1110" shall be used.

-

if a 15-bit "Length Indicator" is used:

-

the "Length Indicator" with value "111 1111 1111 1110" shall be used.

In the case where the "alternative E-bit interpretation" is configured for UM RLC and the first data octet in this RLC
PDU is the first octet of an SDU and the last octet in this RLC PDU is the last octet of the same SDU:

-

if a 7-bit "Length Indicator" is used:

-

the "Length Indicator" with value "111 1101" shall be used.

-

if a 15-bit "Length Indicator" is used:

-

the "Length Indicator" with value "111 1111 1111 1101" shall be used.

In the case where the "alternative E-bit interpretation" is configured for UM RLC and the first data octet in this RLC
PDU is the first octet of an SDU and the same RLC SDU is one octet short of exactly filling the PDU and a 15-bit
"Length Indicator" is used:

-

the "Length Indicator" with value "111 1111 1111 1010" shall be used.

If a "Length Indicator" is still awaiting transmission and there is no RLC SDU available, an RLC PDU consisting of this
"Length Indicator", the appropriate padding "Length Indicator" and padding may be transmitted.

Predefined values of the "Length Indicator" are used to indicate padding. The values that are reserved for special
purposes are listed in the tables below depending on the size of the "Length Indicator". Only predefined "Length
Indicator" values can refer to the padding space. These values shall only be placed after all other "Length Indicators" for
a PDU.

STATUS PDUs can be piggybacked on the AMD PDU by using part or all of the padding space. A predefined "Length
Indicator" shall be used to indicate the presence of a piggybacked STATUS PDU. This "Length Indicator" replaces the
padding "Length Indicator". The piggybacked STATUS PDU shall be appended immediately following the PDU data.
When only part of the padding space is used, the end of the piggybacked STATUS PDU is indicated by one of the SUFI
fields NO_MORE or ACK. Thus no additional "Length Indicator" is required to show that there is still padding in the
AMD PDU.

If "SDU discard with explicit signalling" is configured:

-  an AMD PDU can contain a maximum number of 15 "Length Indicators" indicating the end of 15 corresponding

SDUs; and

-

the rest of the AMD PDU space shall be used as padding or as piggybacked STATUS PDU.

Length: 7 bits

3GPP

Release 13

34

3GPP TS 25.322 V13.0.0 (2015-12)

Bit
0000000

1111100

1111101

1111110

1111111

Description
The previous RLC PDU was exactly filled with the last segment of an RLC SDU
and there is no "Length Indicator" that indicates the end of the RLC SDU in the
previous RLC PDU.
UMD PDU: The first data octet in this RLC PDU is the first octet of an RLC
SDU. AMD PDU: Reserved (PDUs with this coding will be discarded by this
version of the protocol).
UMD PDU: The first data octet in this RLC PDU is the first octet of an RLC
SDU and the last octet in this RLC PDU is the last octet of the same RLC SDU.
AMD PDU: Reserved (PDUs with this coding will be discarded by this version
of the protocol).
AMD PDU: The rest of the RLC PDU includes a piggybacked STATUS PDU.
UMD PDU: The RLC PDU contains a segment of an SDU but neither the first
octet nor the last octet of this SDU.
The rest of the RLC PDU is padding. The padding length can be zero.

Length: 15bits

Bit
000000000000000

111111111111010

111111111111011

111111111111100

111111111111101

111111111111110

111111111111111

Description

The previous RLC PDU was exactly filled with the last segment of an
RLC SDU and there is no "Length Indicator" that indicates the end of
the RLC SDU in the previous RLC PDU.
UMD PDU: The first data octet in this RLC PDU is the first octet of an
RLC SDU and the second last octet in this RLC PDU is the last octet of
the same RLC SDU. The remaining one octet in the RLC PDU is
ignored.
The last segment of an RLC SDU was one octet short of exactly filling
the previous RLC PDU and there is no "Length Indicator" that indicates
the end of the RLC SDU in the previous RLC PDU. The remaining one
octet in the previous RLC PDU is ignored.
UMD PDU: The first data octet in this RLC PDU is the first octet of an
RLC SDU. AMD PDU: Reserved (PDUs with this coding will be
discarded by this version of the protocol).
UMD PDU: The first data octet in this RLC PDU is the first octet of an
RLC SDU and the last octet in this RLC PDU is the last octet of the
same RLC SDU. AMD PDU: Reserved (PDUs with this coding will be
discarded by this version of the protocol).
AMD PDU: The rest of the RLC PDU includes a piggybacked STATUS
PDU. UMD PDU: The RLC PDU contains a segment of an SDU but
neither the first octet nor the last octet of this SDU.
The rest of the RLC PDU is padding. The padding length can be zero.

9.2.2.9

Data field

RLC SDUs or segments of RLC SDUs are mapped to this field in transparent, unacknowledged and acknowledged
modes.

Transparent mode data:

-

-

the length of RLC SDUs is not constrained to a multiple of 8 bits;

if "Segmentation" is configured:

-  all the RLC PDUs carrying segments of a RLC SDU shall be sent in one TTI;

-  only RLC PDUs carrying segments from a single RLC SDU shall be sent in one TTI;

-  otherwise (Segmentation is not configured):

-  TMD PDU size is fixed within a single TTI and is equal to the RLC SDU size.

3GPP

Release 13

35

3GPP TS 25.322 V13.0.0 (2015-12)

Unacknowledged mode data and Acknowledged mode data:

-

the length of RLC SDUs is constrained to a multiple of 8 bits;

-

if "Fixed RLC PDU size" is configured:

-

the last segment of an RLC SDU shall be concatenated with the first segment of the next RLC SDU in
order to fill the data field completely and avoid unnecessary padding unless otherwise specified in
subclause 9.2.2.8 or subclause 11.2.2.2. The "Length Indicator" field is used to point the borders between
RLC SDUs (see subclause 9.2.2.8).

-

if "Flexible RLC PDU size" is configured:

-

-

in downlink, the last segment of an RLC SDU may be concatenated with the first segment of the next
RLC SDU in order to fill the data field up to a maximum RLC PDU size. The "Length Indicator" field is
used to point the borders between RLC SDUs (see subclause 9.2.2.8).

in uplink, the last segment of an RLC SDU shall be concatenated with the first segment of the next RLC
SDU in order to fill the data field at least up to the Minimum UL RLC PDU size. It is allowed to
concatenate up to the largest UL AMD PDU size for Acknowledged mode data and largest UMD PDU
size for Unacknowledged mode data. The "Length Indicator" field is used to point the borders between
RLC SDUs (see subclause 9.2.2.8). If data to be transmitted is not enough to create a UMD PDU of the
minimum size, it is allowed to create a UMD PDU including all data to be transmitted, even if the
resulting size is smaller than the Minimum UL RLC PDU size.

-

in uplink, if MAC-i/is has been configured:

-

if the UE pre-generates RLC PDUs for transmission in a later TTI and there is only one activated
uplink frequency:

-  provided that the UE has sufficient amount of data available for transmission, the size of the data
field of the RLC PDU shall be chosen so that each RLC PDU to be multiplexed to the MAC-i/is
PDU matches the maximum amount of data allowed to be transmitted by the applicable current
grant (scheduled or non-scheduled) for the current TTI.

-  RLC PDUs may only be pre-generated if the amount of data in outstanding pre-generated RLC
PDUs for this logical channel is less than or equal to four times the maximum amount of data
allowed to be transmitted by the applicable current grant (scheduled or non-scheduled) for the
current TTI.

-  else if the UE pre-generates RLC PDUs for transmission in a later TTI and there are two activated
uplink frequencies for FDD or more than one scheduled uplink frequencies for 1.28 Mcps TDD:

-  provided that the UE has sufficient amount of data available for transmission, the size of the data
field of the RLC PDU shall be chosen so that each RLC PDU to be multiplexed to the MAC-i/is
PDU matches the minimum of the following:

-  For FDD,

-  maximum amount of data allowed to be transmitted by the applicable current grant
(scheduled or non-scheduled) on the primary uplink frequency for the current TTI.

-  maximum amount of data allowed to be transmitted by the applicable current grant

(scheduled) on the secondary uplink frequency for the current TTI.

-  For 1.28 Mcps TDD,

-  maximum amount of data allowed to be transmitted by the applicable current grant

(scheduled) on the each scheduled uplink frequency for the current TTI.

-  For FDD, RLC PDUs may only be pre-generated if the amount of data in outstanding pre-

generated RLC PDUs for this logical channel is less than or equal to eight times the minimum of
the following:

-  maximum amount of data allowed to be transmitted by the applicable current grant (scheduled

or non-scheduled) on the primary uplink frequency for the current TTI.

3GPP

Release 13

36

3GPP TS 25.322 V13.0.0 (2015-12)

-  maximum amount of data allowed to be transmitted by the applicable current grant (scheduled)

on the secondary uplink frequency for the current TTI.

-  For 1.28 Mcps TDD, RLC PDUs may only be pre-generated if the amount of data in outstanding

pre-generated RLC PDUs for this logical channel is less than or equal to 4N times the minimum of
the following:

-  maximum amount of data allowed to be transmitted by the applicable current grant (scheduled)

of each uplink frequency for the current TTI.

NOTE:  N is the number of configured uplink frequencies.

-  else:

-

the size of the data field of the RLC PDU shall be chosen so that the RLC PDU size matches the
data requested for this logical channel by the current E-TFC selection.

-

if "Flexible RLC PDU size" is configured, the maximum size of the data field of the RLC PDU is 1503
octets.

9.2.2.10

Padding (PAD)

All unused space in a PDU shall be located at the end of the PDU and is referred to as padding. Padding shall have a
length such that the PDU as a whole has one of the predefined total lengths.

Padding may have any value and the Receiver and the Sender shall disregard it.

9.2.2.11

SUFI

Which SUFI fields to use is implementation dependent, but when a STATUS PDU includes information about which
AMD PDUs have been received and which are detected as missing, information shall not be included about AMD
PDUs with "Sequence Number"≥VR(H) or "Sequence Number"≥VR(MR), i.e. AMD PDUs that have not yet reached
the Receiver or are above the receiving window. Information about AMD PDUs with "Sequence Number"<VR(R) shall
not be given except when this is necessary in order to use the BITMAP SUFI, see subclause 9.2.2.11.5.

Length: variable number of bits.

The SUFI can include three sub-fields: type information (type of super-field, e.g. list, bitmap, acknowledgement, etc),
length information (providing the length of a variable length field within the following value field) and a value.

Figure 9.7 shows the structure of the super-field. The size of the type sub-field is non-zero but the size of the other
sub-fields may be zero.

Type
Length
Value

The length of the type field is 4 bits and it may have any of following values.

Figure 9.7: The Structure of a Super-Field

Description

Bit
0000  No More Data (NO_MORE)
0001  Window Size (WINDOW)
0010  Acknowledgement (ACK)
List (LIST)
0011
0100  Bitmap (BITMAP)
0101  Relative list (Rlist)
0110  Move Receiving Window (MRW)
0111  Move Receiving Window Acknowledgement

(MRW_ACK)

1000  Poll (POLL)
1001-
1111

Reserved (PDUs with this encoding are invalid for this
version of the protocol)

3GPP

Release 13

37

3GPP TS 25.322 V13.0.0 (2015-12)

The size and presence of the sub-fields "Length" and "Value" depend on the super-field type and is specified for each
super field separately.

9.2.2.11.1

The No More Data super-field

The 'No More Data' super-field indicates the end of the data part of a STATUS PDU and is shown in Figure 9.8 below.
It shall always be placed as the last SUFI if it is included in a STATUS PDU. All data after this SUFI shall be regarded
as padding and shall be neglected.

Type=NO_MORE

Figure 9.8: NO_MORE field in a STATUS PDU

9.2.2.11.2

The Acknowledgement super-field

The 'Acknowledgement' super-field consists of a type identifier field (ACK) and a sequence number (LSN) as shown in
figure 9.9 below. The acknowledgement super-field is also indicating the end of the data part of a STATUS PDU. Thus,
no 'NO_MORE' super-field is needed in the STATUS PDU when the 'ACK' super-field is present. The ACK SUFI shall
always be placed as the last SUFI if it is included in a STATUS PDU. All data after this SUFI shall be regarded as
padding and shall be neglected.

Type = ACK
LSN

Figure 9.9: The ACK fields in a STATUS PDU

LSN

Length: 12 bits

Acknowledges the reception of all AMD PDUs with "Sequence Number" < LSN (Last Sequence Number) that are not
indicated to be erroneous in earlier parts of the STATUS PDU. This means that if the LSN is set to a value greater than
VR(R), all erroneous AMD PDUs shall be included in the same STATUS PDU and if the LSN is set to VR(R), the
erroneous AMD PDUs can be split into several STATUS PDUs. At the transmitter, if the value of the LSN =< the value
of the first error indicated in the STATUS PDU, VT(A) will be updated according to the LSN, otherwise VT(A) will be
updated according to the first error indicated in the STATUS PDU. VT(A) is only updated based on STATUS PDUs
where ACK SUFI (or MRW_ACK SUFI) is included. The LSN shall not be set to a value > VR(H) nor < VR(R).

9.2.2.11.3

The Window Size super-field

The Window Size super-field consists of a type identifier (WINDOW) and a window size number (WSN) as shown in
Figure 9.10 below. The Receiver is always allowed to change the transmission window size of the peer entity during a
connection, but the minimum and the maximum allowed value is given by upper layers configuration. The reception
window size of the Receiver is not changed.

Type = WINDOW
WSN

Figure 9.10: The WINDOW fields in a STATUS PDU

WSN

Length: 12 bits

The value of VT(WS) to be used by the transmitter. The range of the WSN is [0, 212-1]. The minimum value of
VT(WS) is 1. If WSN is zero the SUFI shall be discarded by this version of the protocol. The variable VT(WS) is set
equal to WSN upon reception of this SUFI. If WSN is greater than Configured_Tx_Window_Size, VT(WS) shall be set
equal to Configured_Tx_Window_Size.

3GPP

Release 13

38

3GPP TS 25.322 V13.0.0 (2015-12)

9.2.2.11.4

The List super-field

The List Super-Field consists of a type identifier field (LIST), a list length field (LENGTH) and a list of LENGTH
number of pairs as shown in figure 9.11 below:

Type = LIST
LENGTH
SN1
L1
SN2
L2
…
SNLENGTH
LLENGTH

Figure 9.11: The List fields in a STATUS PDU

LENGTH

Length: 4 bits

The number of (SNi , Li)-pairs in the super-field of type LIST. The value "0000" is invalid and the STATUS PDU is
discarded.

SNi

Length: 12 bits

"Sequence Number" of AMD PDU, which was not correctly received.

Li

Length: 4 bits

Number of consecutive AMD PDUs not correctly received following AMD PDU with "Sequence Number" SNi.

9.2.2.11.5

The Bitmap super-field

The Bitmap Super-Field consists of a type identifier field (BITMAP), a bitmap length field (LENGTH), a first sequence
number (FSN) and a bitmap as shown in figure 9.12 below:

Type = BITMAP
LENGTH
FSN
Bitmap

Figure 9.12: The Bitmap fields in a STATUS PDU

LENGTH

Length: 4 bits

The size of the bitmap in octets equals LENGTH+1, i.e. LENGTH="0000" means that the size of the bitmap is one
octet and LENGTH="1111" gives the maximum bitmap size of 16 octets.

FSN

Length: 12 bits

The "Sequence Number" for the first bit in the bitmap. FSN shall not be set to a value lower than VR(R)-7 when the
reception window size is less than half the maximum RLC AM "Sequence Number". If the reception window size is
larger, FSN shall not be set to a value lower than VR(R).

Bitmap

3GPP

Release 13

39

3GPP TS 25.322 V13.0.0 (2015-12)

Length: Variable number of octets given by the LENGTH field.

Status of the "Sequence Number" fields in the interval [FSN, FSN + (LENGTH+1)*8 - 1] indicated in the bitmap where
each position (from left to right) can have two different values (0 and 1) with the following meaning
(bit_position∈[0,(LENGTH+1)*8 - 1]):

1: Sequence Number = (FSN + bit_position) has been correctly received.

0: Sequence Number = (FSN + bit_position) has not been correctly received.

The UE may remove AMD PDUs from the transmitter that have been indicated to be correctly received by a BITMAP
SUFI.

NOTE:  The transmission window is not advanced based on BITMAP SUFIs, see subclause 9.4.

9.2.2.11.6

The Relative List super-field

The Relative List super-field consists of a type identifier field (RLIST), a list length field (LENGTH), the first sequence
number (FSN) and a list of LENGTH number of codewords (CW) as shown in figure 9.13 below.

Type = RLIST
LENGTH
FSN
CW1
CW2
…
CWLENGTH

Figure 9.13: The RList fields in a STATUS PDU

LENGTH

Length: 4 bits

The number of codewords (CW) in the super-field of type RLIST.

FSN

Length: 12 bits

The "Sequence Number" for the first erroneous AMD PDU in the RLIST, i.e. LENGTH="0000" means that only FSN
is present in the SUFI.

CW

Length: 4 bits

The CW consists of 4 bits where the three first bits are part of a number and the last bit is a status indicator and it shall
be interpreted as follows:

Code Word
X1X2X3 0

X1X2X3 1

Description
Next 3 bits of the number are X1X2X3 and the number continues in the next
CW. The most significant bit within this CW is X1.
Next 3 bits of the number are X1X2X3 and the number is terminated. The
most significant bit within this CW is X1. This is the most significant CW
within the number.

By default, the number given by the CWs represents a distance between the previous indicated erroneous AMD PDU up
to and including the next erroneous AMD PDU.

One special value of CW is defined:

000 1

'Error burst indicator'.

3GPP

Release 13

40

3GPP TS 25.322 V13.0.0 (2015-12)

The error burst indicator means that the next CWs will represent the number of subsequent erroneous AMD PDUs (not
counting the already indicated error position). After the number of errors in a burst is terminated with XXX 1, the next
codeword will again by default be the least significant bits (LSB) of the distance to the next error.

If the last CW, as indicated by the value of the LENGTH field, does not contain a "1" in its rightmost position, or the
last CW, as indicated by the value of the LENGTH field does contain a "1" in its rightmost position, but is a special
"error burst indicator" CW, the encoding of the RLIST SUFI is invalid, and the STATUS PDU is discarded.

9.2.2.11.7

The Move Receiving Window Acknowledgement super-field

The 'Move Receiving Window Acknowledgement' super-field acknowledges the reception of a MRW SUFI. The format
is given in figure 9.14 below.

Type = MRW_ACK
N
SN_ACK

Figure 9.14: The MRW-ACK fields in a STATUS PDU

N

Length: 4 bits

The N field shall be set equal to the NLENGTH field in the received MRW SUFI if the SN_ACK field is equal to the
SN_MRWLENGTH field. Otherwise N shall be set to 0.

With the aid of this field in combination with the SN_ACK field, it can be determined if the MRW_ACK corresponds
to a previously transmitted MRW SUFI.

SN_ACK

Length: 12 bits

The SN_ACK field indicates the updated value of VR(R) after the reception of the MRW SUFI. With the aid of this
field in combination with the N field, it can be determined if the MRW_ACK corresponds to a previously transmitted
MRW SUFI.

9.2.2.11.8

The Move Receiving Window (MRW) super-field

The 'Move Receiving Window' super-field is used to request the Receiver to move its reception window and optionally
to indicate the set of discarded RLC SDUs, as a result of an RLC SDU discard in the Sender. The format is given in
figure 9.15 below.

Type = MRW
LENGTH
SN_MRW1
SN_MRW2
...
SN_MRWLENGTH
NLENGTH

Figure 9.15: The MRW fields in a STATUS PDU

LENGTH

Length: 4 bits

The number of SN_MRWi fields in the super-field of type MRW.

The values "0001" through "1111" indicate 1 through 15 SN_MRWi respectively. The value "0000" indicates that one
SN_MRWi field is present and that the RLC SDU to be discarded in the Receiver extends above the configured
transmission window in the Sender.

SN_MRWi

3GPP

Release 13

Length: 12 bits

41

3GPP TS 25.322 V13.0.0 (2015-12)

When "Send MRW" is configured, an SN_MRWi shall be used to indicate the end of each discarded RLC SDU, i.e. the
number of SN_MRWi fields shall equal the number of RLC SDUs discarded by that MRW SUFI. When "Send MRW"
is not configured, an SN_MRWi field shall be used to indicate the end of the last RLC SDU to be discarded in the
Receiver and additional ones may optionally be used to indicate the end of other discarded RLC SDUs. SN_MRWi is
the "Sequence Number" of the AMD PDU that contains the "Length Indicator" or the special value of the HE field of
the i:th RLC SDU to be discarded in the Receiver (except for SN_MRWLENGTH when NLENGTH = 0, see definition of
NLENGTH). The order of the SN_MRWi shall be in the same sequential order as the RLC SDUs that they refer to.

Additionally SN_MRWLENGTH requests the Receiver to discard all not yet successfully received SDUs that have
segments or "Length Indicators" indicating the end of the SDUs in the AMD PDUs with "Sequence Number" <
SN_MRWLENGTH, and to move the reception window accordingly. In addition, when NLENGTH > 0, the Receiver has to
discard the not yet successfully received SDUs that have segments or "Length Indicators" indicating the end of the
SDUs in the AMD PDU with sequence number SN_MRWLENGTH up to and including the octet indicated by the
NLENGTH:th "Length Indicator" field of the PDU with sequence number SN_MRWLENGTH.

NLENGTH

Length: 4 bits

NLENGTH is used together with SN_MRWLENGTH to indicate the end of the last RLC SDU to be discarded in the Receiver.

NLENGTH indicates which "Length Indicator" in the AMD PDU with "Sequence Number" SN_MRWLENGTH corresponds
to the last RLC SDU to be discarded in the Receiver. NLENGTH = 0 indicates that the end of the last RLC SDU was
indicated in the AMD PDU with "Sequence Number" SN_MRWLENGTH –1 and that the first data octet in the AMD PDU
with "Sequence Number" SN_MRWLENGTH is the first data octet to be reassembled next.

9.2.2.11.9

The Poll (POLL) super-field

The 'Poll' super-field is used to request a status report (one or several STATUS PDUs) from the receiver. The poll
super-field in downlink can only be used if flexible RLC PDU size is configured in the downlink. The poll super-field
in uplink can only be used if flexible RLC PDU size is configured in the uplink. The format is given in figure 9.15b
below.

Type = POLL
Poll_SN

Figure 9.15b: The POLL fields in a STATUS PDU

Poll_SN

Length: 12 bits

When "Poll" is configured, the Poll_SN field shall be set to VT(S)-1.

9.2.2.12

Reserved 2 (R2)

Length: 1 bit

This bit in the Piggybacked STATUS PDU is used to make the Piggybacked STATUS PDU a multiple of 8 bits in
length and for this purpose it is coded as 0. Otherwise the PDU is treated as invalid and hence shall be discarded by this
version of the protocol.

9.2.2.13

Reset Sequence Number (RSN)

Length: 1 bit

This field is used to indicate the sequence number of the transmitted RESET PDU. If this RESET PDU is a
retransmission of the original RESET PDU then the retransmitted RESET PDU would have the same RSN value as the
original RESET PDU. Otherwise it will have the next RSN value. The initial value of this field is zero. The value of this
field shall be reinitialised when the RLC is re-established. It shall not be reinitialised when the RLC is reset.

3GPP

Release 13

42

3GPP TS 25.322 V13.0.0 (2015-12)

9.2.2.14

Hyper Frame Number Indicator (HFNI)

Length: 20 bit

This field is used to indicate the hyper frame number (HFN) to the peer entity. With the aid of this field the HFN in UE
and UTRAN can be synchronised.

9.3

Protocol states

The content presented in this subclause is intended to support the definition of the RLC protocol states only, and is not
meant to specify or constrain the implementation of the protocol.

9.3.1

State model for transparent mode entities

Figure 9.16 illustrates the state model for transparent mode RLC entities (both transmitting and receiving). A
transparent mode entity can be in one of the following states.

9.3.1.1

NULL State

In the NULL state the RLC entity does not exist and therefore it is not possible to transfer any data through it.

Upon reception of a CRLC-CONFIG-Req from upper layers indicating establishment, the RLC entity:

-

is created; and

-  enters the DATA_TRANSFER_READY state.

9.3.1.2

DATA_TRANSFER_READY State

In the DATA_TRANSFER_READY state, transparent mode data can be exchanged between the entities according to
subclause 11.1.

Upon reception of a CRLC-CONFIG-Req from upper layer indicating release, the RLC entity:

-  enters the NULL state; and

-

is considered as being terminated.

CRLC-CONFIG-Req

1.
NULL

2.
DATA_
TRANSFER
_ READY

CRLC-CONFIG-Req

Received signal
Sent signal

Figure 9.16: The state model for transparent mode entities

9.3.2

State model for unacknowledged mode entities

Figure 9.17 illustrates the state model for unacknowledged mode RLC entities (both transmitting and receiving). An
unacknowledged mode entity can be in one of the following states.

9.3.2.1

NULL State

In the NULL state the RLC entity does not exist and therefore it is not possible to transfer any data through it.

Upon reception of a CRLC-CONFIG-Req from upper layer indicating establishment the RLC entity:

3GPP

Release 13

43

3GPP TS 25.322 V13.0.0 (2015-12)

-

is created; and

-  enters the DATA_TRANSFER_READY state.

9.3.2.2

DATA_TRANSFER_READY State

In the DATA_TRANSFER_READY state, unacknowledged mode data can be exchanged between the entities
according to subclause 11.2.

Upon reception of a CRLC-CONFIG-Req from upper layer indicating release, the RLC entity:

-  enters the NULL state; and

-

is considered as being terminated.

Upon reception of a CRLC-CONFIG-Req from upper layer indicating modification, the RLC entity:

-

stays in the DATA_TRANSFER_READY state;

-  modifies only the protocol parameters and timers as indicated by upper layers.

Upon reception of a CRLC-SUSPEND-Req from upper layers, the RLC entity:

-  enters the LOCAL_SUSPEND state.

9.3.2.3

LOCAL_SUSPEND State

In the LOCAL_SUSPEND state, the RLC entity is suspended, i.e. it does not send UMD PDUs with "Sequence
Number" greater than or equal to a certain specified value (see subclause 9.7.5).

Upon reception of a CRLC-CONFIG-Req from upper layer indicating release, the RLC entity:

-  enters the NULL state; and

-

is considered as being terminated.

Upon reception of a CRLC-RESUME-Req from upper layers, the RLC entity:

-  enters the DATA_TRANSFER_READY state; and

-

resumes the data transmission.

Upon reception of a CRLC-CONFIG-Req from upper layer indicating modification, the RLC entity:

-

stays in the LOCAL_SUSPEND state;

-  modifies only the protocol parameters and timers as indicated by upper layers.

3GPP

Release 13

44

3GPP TS 25.322 V13.0.0 (2015-12)

CRLC-CONFIG-Req

CRLC-CONFIG-Req

1.
NULL

2.
DATA_
TRANSFER_
READY

CRLC-SUSPEND-Req

CRLC-SUSPEND-Conf

CRLC-CONFIG-Req

CRLC-RESUME-Req

CRLC-CONFIG-Req
CRLC-CONFIG-Req

CRLC-CONFIG-Req

3.
LOCAL_
SUSPEND

Received signal
Sent signal

Figure 9.17: The state model for unacknowledged mode entities

9.3.3

State model for acknowledged mode entities

Figure 9.18 illustrates the state model for the acknowledged mode RLC entity (both transmitting and receiving). An
acknowledged mode entity can be in one of the following states.

9.3.3.1

NULL State

In the NULL state the RLC entity does not exist and therefore it is not possible to transfer any data through it.

Upon reception of a CRLC-CONFIG-Req from upper layer indicating establishment, the RLC entity:

-

is created; and

-  enters the DATA_TRANSFER_READY state.

9.3.3.2

DATA_TRANSFER_READY State

In the DATA_TRANSFER_READY state, acknowledged mode data can be exchanged between the entities according
to subclause 11.3.

Upon reception of a CRLC-CONFIG-Req from upper layer indicating release, the RLC entity:

-  enters the NULL state; and

-

is considered as being terminated.

Upon detection of an initiating condition for the RLC reset procedure described in subclause 11.4.2, the RLC entity:

-

initiates the RLC reset procedure (see subclause 11.4); and

-  enters the RESET_PENDING state.

Upon reception of a RESET PDU, the RLC entity responds according to subclause 11.4.3.

Upon reception of a RESET ACK PDU, the RLC entity takes no action.

Upon reception of CRLC-SUSPEND-Req from upper layer, the RLC entity is suspended and enters the
LOCAL_SUSPEND state.

9.3.3.3

RESET_PENDING State

In the RESET_PENDING state the entity waits for a response from its peer entity and no data can be exchanged
between the entities.

3GPP

Release 13

45

3GPP TS 25.322 V13.0.0 (2015-12)

Upon reception of a CRLC-CONFIG-Req from upper layer indicating release, the RLC entity:

-  enters the NULL state; and

-

is considered as being terminated.

Upon reception of a RESET ACK PDU with the same RSN value as in the corresponding RESET PDU, the RLC entity:

-  acts according to subclause 11.4.4; and

-  enters the DATA_TRANSFER_READY state.

Upon reception of a RESET ACK PDU with a different RSN value as in the corresponding RESET PDU, the RLC
entity:

-  discards the RESET ACK PDU (see subclause 11.4.4); and

-

stays in the RESET_PENDING state.

Upon reception of a RESET PDU, the RLC entity:

-

-

responds according to subclause 11.4.3; and

stays in the RESET_PENDING state.

Upon reception of CRLC-SUSPEND-Req from upper layer, the RLC entity:

-  enters the RESET_AND_SUSPEND state.

CRLC-CONFIG-Req

CRLC-CONFIG-Req

RESET
RESET ACK

RESET ACK

1.
NULL

2.
DATA_
TRANSFER_
READY

CRLC-SUSPEND-Req

CRLC-SUSPEND-Conf

CRLC-RESUME-Req

CRLC-CONFIG-Req

RESET ACK

RESET

4.
LOCAL_
SUSPEND

CRLC-CONFIG-Req

RESET ACK

RESET
RESET ACK

RESET

3.
RESET_
PENDING

CRLC-SUSPEND-Req

CRLC-SUSPEND-Conf

CRLC-RESUME-Req

5.
RESET_AND
_SUSPEND

CRLC-CONFIG-Req

Received signal
Sent signal

Figure 9.18: The state model for the acknowledged mode entities

3GPP

Release 13

46

3GPP TS 25.322 V13.0.0 (2015-12)

9.3.3.4

LOCAL_SUSPEND State

In the LOCAL_SUSPEND state, the RLC entity is suspended, i.e. it does not send AMD PDUs with "Sequence
Number" greater than or equal to certain specified value (see subclause 9.7.5).

Upon reception of CRLC-RESUME-Req from upper layers in this state, the RLC entity:

-

resumes the data transmission; and

-  enters the DATA_TRANSFER_READY state.

Upon reception of CRLC-CONFIG-Req from upper layers indicating release, the RLC entity:

-  enters the NULL state; and

-

is considered as being terminated.

Upon detection of an initiating condition for RLC reset procedure described in subclause 11.4.2, the RLC entity:

-

initiates the RLC reset procedure (see subclause 11.4); and

-  enters the RESET_AND_SUSPEND state.

9.3.3.5

RESET_AND_SUSPEND State

In the RESET_ AND_SUSPEND state, the entity waits for a response from its peer entity or a primitive (CRLC-
RESUME-Req) from its upper layer and no data can be exchanged between the entities.

Upon reception of CRLC-CONFIG-Req from upper layer indicating release, the RLC entity:

-  enters the NULL state; and

-

is considered as being terminated.

Upon reception of a RESET ACK PDU with the same RSN value as in the corresponding RESET PDU, the RLC entity:

-  acts according to subclause 11.4.4; and

-  enters the LOCAL_SUSPEND state.

Upon reception of CRLC-RESUME-Req from upper layer in this state, the RLC entity:

-

is resumed, i.e. releases the suspend constraint; and

-  enters the RESET_PENDING state.

9.4

State variables

The state variables defined in this subclause are normative.

This sub-clause describes the state variables used in AM and UM in order to specify the peer-to-peer protocol. All state
variables are non-negative integers. UMD and AMD PDUs are numbered by modulo integer sequence numbers (SN)
cycling through the field: 0 to 212 – 1 for AM and 0 to 27 – 1 for UM. All arithmetic operations contained in the present
document on VT(S), VT(A), VT(MS), VR(R), VR(H) and VR(MR) are affected by the AM modulus. All arithmetic
operations contained in the present document on VT(US), VR(US), VR(UDH), VR(UDR), VR(UOH) and VR(UM) are
affected by the UM modulus. When performing arithmetic comparisons of state variables or Sequence number values a
modulus base shall be used. This modulus base is subtracted (within the appropriate field) from all the values involved
and then an absolute comparison is performed. At the Sender, VT(A) and VT(US) shall be assumed to be the modulus
base in AM and UM respectively. At the Receiver, VR(R) shall be assumed to be the modulus base in AM and VR(US)
shall be assumed to be the modulus base in UM when neither the "out of sequence SDU delivery" nor the "duplicate
avoidance and reordering" function are configured. When "out of sequence SDU delivery" is configured, (VR(UOH) –
OSD_Window_Size + 1) shall be assumed to be the modulus base at the Receiver in UM; when the "duplicate
avoidance and reordering" function is configured, (VR(UDH) – DAR_Window_Size + 1) shall be assumed to be the
modulus base at the Receiver in UM.

The RLC shall maintain the following state variables in the Sender.

3GPP

Release 13

47

3GPP TS 25.322 V13.0.0 (2015-12)

a)  VT(S) - Send state variable.

  This state variable contains the "Sequence Number" of the next AMD PDU to be transmitted for the first time
(i.e. excluding retransmitted PDUs). It shall be updated after the aforementioned AMD PDU is transmitted or
after transmission of a MRW SUFI which includes SN_MRWLENGTH >VT(S) (see subclause 11.6).

The initial value of this variable is 0.

b)  VT(A) - Acknowledge state variable.

  This state variable contains the "Sequence Number" following the "Sequence Number" of the last in-sequence

acknowledged AMD PDU. This forms the lower edge of the transmission window of acceptable
acknowledgements. VT(A) shall be updated based on the receipt of a STATUS PDU including an ACK (see
subclause 9.2.2.11.2) and/or an MRW_ACK SUFI (see subclause 11.6).

  The initial value of this variable is 0. For the purpose of initialising the protocol, this value shall be assumed to

be the first "Sequence Number" following the last in-sequence acknowledged AMD PDU.

c)  VT(DAT).

  This state variable counts the number of times a AMD PDU has been scheduled to be transmitted. There shall be

one VT(DAT) for each PDU and each shall be incremented every time the corresponding AMD PDU is
scheduled to be transmitted or every time a STATUS PDU containing the POLL SUFI is scheduled to be
transmitted and the sequence number of the corresponding AMD PDU is equal to VT(S)-1.

  The initial value of this variable is 0.

d)  VT(MS) - Maximum Send state variable.

  This state variable contains the "Sequence Number" of the first AMD PDU that can be rejected by the peer

Receiver, VT(MS) = VT(A) + VT(WS). This value represents the upper edge of the transmission window. The
transmitter shall not transmit AMD PDUs with "Sequence Number" ≥ VT(MS) unless VT(S) ≥ VT(MS). In that
case, the AMD PDU with "Sequence Number" = VT(S) - 1 can also be transmitted. VT(MS) shall be updated
when VT(A) or VT(WS) is updated.

  The initial value of this variable is Configured_Tx_Window_size.

e)  VT(US) – UM data state variable.

  This state variable contains the "Sequence Number" of the next UMD PDU to be transmitted. It shall be

incremented by 1 each time a UMD PDU is transmitted.

  The initial value of this variable is 0.

NOTE:  For the UTRAN side, the initial value of this variable can be different from 0.

f)  VT(PDU).

  This state variable is used when the "poll every Poll_PDU PDU" polling trigger is configured. It shall be

incremented by 1 for each AMD PDU that is transmitted including both new and retransmitted AMD PDUs.
When it becomes equal to the value Poll_PDU, a new poll shall be transmitted and the state variable shall be set
to zero.

  The initial value of this variable is 0.

g)  VT(SDU).

  This state variable is used when the "poll every Poll_SDU SDU" polling trigger is configured. It shall be

incremented by 1 for a given SDU when the AMD PDU carrying the first segment of this SDU is scheduled to
be transmitted for the first time. When it becomes equal to the value Poll_SDU a new poll shall be transmitted
and the state variable shall be set to zero. The "Polling bit" shall be set to "1" in the first transmission of the
AMD PDU that contains the last segment of an RLC SDU (indicated either by the "Length Indicator" indicating
the end of the SDU or by the special value of the HE field).

  The initial value of this variable is 0.

3GPP

Release 13

48

3GPP TS 25.322 V13.0.0 (2015-12)

h)  VT(RST) - Reset state variable.

  This state variable is used to count the number of times a RESET PDU is scheduled to be transmitted before the
reset procedure is completed. VT(RST) shall be incremented by 1 according to subclauses 11.4.2 and 11.4.5.1.
VT(RST) shall only be reset upon the reception of a RESET ACK PDU ( i.e. VT(RST) shall not be reset when
an RLC reset initiated by the peer RLC entity occurs) unless otherwise specified in subclause 9.7.7.

  The initial value of this variable is 0.

i)  VT(MRW) – MRW command send state variable.

  This state variable is used to count the number of times a MRW command is transmitted. VT(MRW) is

incremented by 1 each time a timer Timer_MRW expires. VT(MRW) shall be reset when the SDU discard with
explicit signalling procedure is terminated.

The initial value of this variable is 0.

j)  VT(WS) – Transmission window size state variable.

  This state variable contains the size that shall be used for the transmission window. VT(WS) shall be set equal to

the WSN field when the transmitter receives a STATUS PDU including a WINDOW SUFI.

  The initial value of this variable is Configured_Tx_Window_size.

The RLC shall maintain the following state variables in the Receiver:

a)  VR(R) - Receive state variable.

  This state variable contains the "Sequence Number" following that of the last in-sequence AMD PDU received.

It shall be updated upon the receipt of the AMD PDU with "Sequence Number" equal to VR(R).

  The initial value of this variable is 0. For the purpose of initialising the protocol, this value shall be assumed to

be the first "Sequence Number" following the last in-sequence received AMD PDU.

b)  VR(H) - Highest expected state variable.

  This state variable contains the "Sequence Number" following the highest "Sequence Number" of any AMD

PDU received or identified to be missing.. When a AMD PDU is received with "Sequence Number" x or a POLL
SUFI is received with POLL_SN=x such that VR(H)≤x<VR(MR), this state variable shall be set equal to x+1.

  The initial value of this variable is 0.

c)  VR(MR) - Maximum acceptable Receive state variable.

  This state variable contains the "Sequence Number" of the first AMD PDU that shall be rejected by the Receiver,

VR(MR) = VR(R) + Configured_Rx_Window_Size.

d)  VR(US) - Receiver Send Sequence state variable.

  This state variable is applicable only when "out of sequence SDU delivery" is not configured. This state variable
contains the "Sequence Number" following that of the last UMD PDU received by the reception buffer (see Fig.
4.3 and 4.3a). When a UMD PDU with "Sequence Number" equal to x is received by the reception buffer, the
state variable shall set equal to x + 1.

  The initial value of this variable is 0.

e)  VR(UOH) –UM out of sequence SDU delivery highest received state variable.

This state variable contains the "Sequence Number" of the highest numbered UMD PDU that has been received.

The initial value of this variable is set according to subclause 11.2.3.2.

f)  VR(UDR) –UM duplicate avoidance and reordering send state variable.

This state variable contains the "Sequence Number" of the next UMD PDU that is expected to be received in
sequence. Its value is set according to subclause 9.7.10.

3GPP

Release 13

49

3GPP TS 25.322 V13.0.0 (2015-12)

The initial value of this variable is set according to subclause 9.7.10.

g)  VR(UDH) – UM duplicate avoidance and reordering highest received state variable.

This state variable contains the "Sequence Number" of the highest numbered UMD PDU that has been received
by the duplicate avoidance and reordering function.

The initial value of this variable is set according to 9.7.10.

h)  VR(UDT) – UM duplicate avoidance and reordering timer state variable.

This state variable contains the sequence number of the UMD PDU associated with Timer_DAR when the timer
is running. Its value is set according to subclause 9.7.10.

i)  VR(UM) - Maximum acceptable Receive state variable.

This state variable contains the "Sequence Number" of the first UMD PDU that shall be rejected by the Receiver,
VR(UM) = VR(US) + Configured_Rx_Window_Size. This state variable is only applicable when out-of-
sequence reception is configured by higher layers.

j)  VR(X) – Timer_Reordering state variable

This state variable holds the value of SN following the SN of the RLC data PDU which triggered
Timer_Reordering.

The initial value of this variable is set according to 11.3.3.

k)  VR(MS) – Maximum STATUS transmit variable

This state variable holds the highest possible value of the SN which can be indicated by LSN when a STATUS
PDU needs to be constructed.

The initial value of this variable is 0.

9.5

Timers

The timers defined in this subclause are normative. The timers shall be considered active from the time they are started
until the time they either expire or are stopped.

a)  Timer_Poll.

  This timer shall only be used when so configured by upper layers. The value of the timer is signalled by upper
layers. In the UE this timer shall be started (or restarted) when the successful or unsuccessful transmission of a
poll is indicated by lower layer. In UTRAN it should be started when a poll is submitted to lower layer. If x is
the value of the state variable VT(S) after the poll was submitted to lower layer, the timer shall be stopped upon
receiving:

-  positive acknowledgements for all the AMD PDUs with "Sequence Number" up to and including x - 1; or

-  a negative acknowledgement for the AMD PDU with "Sequence Number" = x - 1.

If the timer expires and no STATUS PDU fulfilling the criteria above has been received:

-

-

-

the Receiver shall be polled once more;

the timer shall be restarted; and

the new value of VT(S) shall be saved.

If a new poll is sent when the timer is active, the timer shall be restarted at the time specified above, and the
value of VT(S) shall be saved.

b)  Timer_Poll_Prohibit.

  This timer shall only be used when so configured by upper layers. It is used to prohibit transmission of polls

within a certain period. The value of the timer is signalled by upper layers.

3GPP

Release 13

50

3GPP TS 25.322 V13.0.0 (2015-12)

In the UE this timer shall be started (or restarted) when the successful or unsuccessful transmission of a poll is
indicated by lower layer. In UTRAN it should be started when a poll is submitted to lower layer.

From the time a poll is triggered until the timer expires, polling is prohibited. If another poll is triggered while
polling is prohibited, its transmission shall be delayed until the timer expires (see subclause 9.7.1). Only one poll
shall be transmitted when Timer_Poll_Prohibit expires even if several polls were triggered in the meantime. This
timer shall not be affected by the reception of STATUS PDUs.

  When Timer_Poll_Prohibit is not configured by upper layers, polling is never prohibited.

c)  Void

d)  Timer_Discard.

  This timer shall be used when timer-based SDU discard is configured by upper layers. The value of the timer is
signalled by upper layers. In the transmitter, a new timer is started upon reception of an SDU from upper layer.

In UM/TM, if a timer expires before the corresponding SDU is submitted to lower layer, "SDU discard without
explicit signalling" specified in subclauses 11.2.4.3 and 11.1.4.2 shall be initiated. In AM, if a timer expires
before the corresponding SDU is acknowledged, "SDU discard with explicit signalling" specified in subclause
11.6 shall be initiated.

e)  Timer_Poll_Periodic.

  This timer shall only be used when "timer based polling" is configured by upper layers. The value of the timer is
signalled by upper layers. The timer shall be started when the RLC entity is created. When the timer expires, the
RLC entity shall:

-

-

restart the timer;

if AMD PDUs are available for transmission or retransmission (not yet acknowledged):

-

trigger a poll.

f)  Timer_Status_Prohibit.

  This timer shall only be used when so configured by upper layers. It is meant to prohibit the Receiver from

sending consecutive acknowledgement status reports. A status report is an acknowledgement status report if it
contains any of the SUFIs LIST, BITMAP, RLIST or ACK. The value of the timer is signalled by upper layers.

In the UE, this timer shall be started (or restarted) when the successful or unsuccessful transmission of the last
STATUS PDU of an acknowledgement status report is indicated by lower layer. In UTRAN it should be started
when the last STATUS PDU of an acknowledgement status report is submitted to lower layer.

From the time an acknowledgement status report is triggered until the Timer_Status_Prohibit timer expires,
acknowledgement is prohibited. If another such status report is triggered while acknowledgement is prohibited,
its transmission shall be delayed until the timer expires (see subclause 9.7.2). The status report may be updated
during this time. The transmission of SUFIs MRW, MRW_ACK, WINDOW or NO_MORE is not restricted.

  When Timer_Status_Prohibit is not configured by upper layers, acknowledgment is not prohibited.

g)  Timer_Status_Periodic.

  This timer shall only be used when timer based status reporting is configured by upper layers.

  This timer shall be started when the RLC entity is created. When the timer expires the transmission of a status
report shall be triggered and the timer shall be restarted. This timer can be blocked by upper layers. The timer
shall be restarted when upper layers indicate that it is no longer blocked.

3GPP

Release 13

51

3GPP TS 25.322 V13.0.0 (2015-12)

h)  Timer_RST.

  This timer is meant to handle the loss of a RESET PDU by the peer entity, or the loss of a RESET ACK PDU

from the peer entity. The value of the timer is signalled by upper layers.

In the UE this timer shall be started (or restarted) when the successful or unsuccessful transmission of a RESET
PDU is indicated by lower layer. In UTRAN it should be started when a RESET PDU is submitted to lower
layer.

  Timer_RST shall only be stopped upon reception of a RESET ACK PDU (with same RSN as RESET PDU), i.e.
this timer shall not be stopped when an RLC reset initiated by the peer RLC entity occurs. If this timer expires,
the RESET PDU shall be retransmitted.

i)  Timer_MRW.

  This timer is used to trigger the retransmission of a status report containing an MRW SUFI field. The value of

the timer is signalled by upper layers.

In the UE this timer shall be started (or restarted) when the successful or unsuccessful transmission of a
STATUS PDU containing the MRW SUFI is indicated by lower layer. In UTRAN, it should be started when a
STATUS PDU containing the MRW SUFI is submitted to lower layer.

  Each time the timer expires the MRW SUFI is retransmitted. It shall be stopped when one of the termination

criteria for the SDU discard with explicit signalling procedure is fulfilled (see subclause 11.6.4).

j)  Timer_OSD

This timer is used with UM out of sequence SDU delivery. It is used to trigger the deleting of stored PDUs.

The timer is started and stopped according to subclause 11.2.3.2.

k)  Timer_DAR

This timer is used with the UM duplicate avoidance and reordering function. It is used to trigger the transfer of
PDUs to the next in sequence UM RLC receiver function.

The timer is started and stopped according to subclause 9.7.10.

l)  Timer_Reordering

This timer shall only be used when so configured by upper layers.

The timer is started and stopped according to 11.3.3. There is only one Timer_Reordering running at a given
time. While it is running, any positive or negative acknowledgment is prohibited. The status report may be
updated during this time.

9.6

Protocol Parameters

The behaviour defined in this subclause is normative. The values of the protocol parameters defined in this subclause
are signalled by upper layers.

a)  MaxDAT.

  The maximum number of transmissions of an AMD PDU is equal to MaxDAT – 1. This protocol parameter

represents the upper limit for state variable VT(DAT). When VT(DAT) equals the value MaxDAT, either RLC
RESET procedure or SDU discard procedure shall be initiated according to the configuration by upper layers.

b)  Poll_PDU.

  This protocol parameter indicates how often the transmitter shall poll the Receiver in the case where "polling

every Poll_PDU PDU" is configured by upper layers. It represents the upper limit for the state variable
VT(PDU). When VT(PDU) equals the value Poll_PDU a poll shall be transmitted to the peer entity.

c)  Poll_SDU.

3GPP

Release 13

52

3GPP TS 25.322 V13.0.0 (2015-12)

  This protocol parameter indicates how often the transmitter shall poll the Receiver in the case where "polling

every Poll_SDU SDU" is configured by upper layers. It represents the upper limit for state variable VT(SDU).
When VT(SDU) equals the value Poll_SDU a poll shall be transmitted to the peer entity.

d)  Poll_Window.

  This protocol parameter indicates when the transmitter shall poll the Receiver in the case where "window-based
polling" is configured by upper layers. A poll is triggered for each AMD PDU when J ≥ Poll_Window, where J
is the transmission window percentage defined as:

J =

  (4096+VT(S) +1 – VT(A)) mod 4096
VT(WS)

* 100 ,

where the constant 4096 is the modulus for AM described in subclause 9.4 and VT(S) is the value of the variable
before the AMD PDU is submitted to lower layer.

e)  MaxRST.

  The maximum number of transmissions of a RESET PDU is equal to MaxRST – 1. This protocol parameter

represents the upper limit for state variable VT(RST). When VT(RST) equals the value MaxRST, unrecoverable
error shall be indicated to upper layers.

f)  Configured_Tx_Window_Size.

  This protocol parameter indicates both the maximum allowed transmission window size and the value for the

state variable VT(WS).

g)  Configured_Rx_Window_Size.

  This protocol parameter indicates the reception window size. This parameter is applicable both for RLC UM and

AM. This parameter is only configured for RLC-UM in case out-of-sequence reception is supported.

h)  MaxMRW.

  The maximum number of transmissions of an MRW command is equal to MaxMRW. This protocol parameter

represents the upper limit for state variable VT(MRW). When VT(MRW) equals the value MaxMRW, the RLC
RESET procedure shall be initiated.

i)  OSD_Window_Size.

  This protocol parameter indicates the size of the out of sequence SDU delivery storage window.

j)  DAR_Window_Size.

  This protocol parameter indicates the size of the duplicate avoidance and reordering receive window.

9.7

Specific functions

The functions defined in this subclause are normative.

9.7.1

Polling function for acknowledged mode

The Polling function is used by the Sender to request the peer RLC entity for a status report. The "Polling bit" in the
AMD PDU or the POLL SUFI indicate the poll request. There are several triggers for initiating the Polling function.
Which of the triggers shall be used is configured by upper layers for each RLC entity. The following triggers can be
configured:

1)  Last PDU in buffer.

  When an AMD PDU to be transmitted for the first time is submitted to lower layer, the Sender shall:

-

if the AMD PDU is the last AMD PDU scheduled for transmission according to subclause 11.3.2 (i.e. no data
received from upper layer remains to be segmented into AMD PDUs); or

-

if the AMD PDU is the last AMD PDU that is allowed to transmit according to subclause 11.3.2.2:

3GPP

Release 13

53

3GPP TS 25.322 V13.0.0 (2015-12)

-

trigger a poll for this AMD PDU.

2)  Last PDU in Retransmission buffer.

  When a retransmitted AMD PDU is submitted to lower layer, the Sender shall:

-

-

if the AMD PDU is the last AMD PDU scheduled for retransmission according to subclause 11.3.2; or

if the AMD PDU is the last of the AMD PDUs scheduled for retransmission that are allowed to transmit
according to subclause 11.3.2.2:

-

trigger a poll for this AMD PDU.

3)  Poll timer.

  The timer Timer_Poll is started and stopped according to subclause 9.5 a). When the timer Timer_Poll expires

the Sender triggers the Polling function.

4)  Every Poll_PDU PDU.

  The Sender triggers the Polling function for every Poll_PDU PDU. Both retransmitted and new AMD PDUs

shall be counted.

5)  Every Poll_SDU SDU.

  The Sender triggers the Polling function for every Poll_SDU SDU. The poll shall be triggered for the first

transmission of the AMD PDU that contains the last segment of an RLC SDU (indicated either by the "Length
Indicator" indicating the end of the SDU or by the special value of the HE field).

6)  Window based.

  The Sender triggers the Polling function when the condition described in subclause 9.6 d) ("Poll_Window") is

fulfilled.

7)  Timer based.

  The Sender triggers the Polling function periodically.

UTRAN should configure RLC to avoid deadlock situations.

The Poll Prohibit function is used by the Sender to delay the initiation of the Polling function. Usage of the Poll Prohibit
function is configured by upper layers. The Poll Prohibit function consists of starting the timer Timer_Poll_Prohibit
according to subclause 9.5 b) and delaying the Polling function according to the following rules:

When the Polling function is triggered, the Sender shall:

-

-

if polling is not prohibited (see subclause 9.5 b)); and

if there is one or more AMD PDUs to be transmitted or there are AMD PDUs not acknowledged by the
Receiver:

-

initiate the Polling function by setting the polling bit according to subclause 11.3.2.1.1.

-  otherwise (if there is no PDU to be transmitted and all PDUs have already been acknowledged):

-  not initiate the Polling function.

Upon expiry of the timer Timer_Poll_Prohibit, the Sender shall:

-

-

if the Polling function was triggered at least once while the timer Timer_Poll_Prohibit was active; and

if there is one or more AMD PDUs to be transmitted or there are AMD PDUs not acknowledged by the
Receiver:

-

initiate the Polling function once by setting the polling bit according to subclause 11.3.2.1.1.

-  otherwise (if there is no PDU to be transmitted and all PDUs have already been acknowledged):

3GPP

Release 13

54

3GPP TS 25.322 V13.0.0 (2015-12)

-  not initiate the Polling function.

NOTE 1:  In downlink, UTRAN can initiate the Polling function by assembling a POLL SUFI according to

subclause 9.2.2.11.9 when "flexible RLC PDU size" in downlink is configured.

NOTE 2:  In uplink, the UE can initiate the Polling function by assembling a POLL SUFI according to subclause

9.2.2.11.9 when "flexible RLC PDU size" in uplink is configured.

9.7.2

STATUS transmission for acknowledged mode

The Receiver transmits status reports to the Sender in order to inform the Sender about which AMD PDUs have been
received and not received. Each status report consists of one or several STATUS PDUs. The Receiver shall trigger the
transmission of a status report when receiving a poll request. Additionally, the following triggers for transmission of
status reports are configurable by upper layers:

1)  Detection of missing PDU(s).

If the Receiver detects one or several missing AMD PDUs it shall trigger the transmission of a status report to
the Sender.

2)  Timer based status report transfer.

  The Receiver triggers the transmission of a status report to the Sender periodically. The timer

Timer_Status_Periodic controls the time period according to subclause 9.5 g). When "Periodical Status
blocking" is configured by upper layers, the trigger shall not be active.

3)  Void

There are several functions that can prohibit the Receiver from sending a status report containing any of the SUFIs
LIST, BITMAP, RLIST or ACK. Status reports containing other SUFIs are not prohibited. Upper layers control which
functions should be used for each RLC entity. If any of the following functions is used the transmission of the status
report shall be delayed, even if any of the triggering conditions above are fulfilled:

1)  STATUS prohibit.

  The timer Timer_Status_Prohibit is started according to subclause 9.5 f). The Receiver is not allowed to transmit
a status report while acknowledgement is prohibited (see subclause 9.5 f)). If a status report was triggered during
this time, the status report is transmitted after the timer Timer_Status_Prohibit has expired, as described below.

2)  Void

3)  Timer_Reordering

  The timer Timer_Reordering is started according to subclause 11.3.3. The receiver is not allowed to transmit a
status report while the timer is running. If a status report was triggered during this time, the status report is
transmitted after the timer Timer_Reordering has expired, as described below.

When a status report is triggered the Receiver shall:

-

if transmission of status reports is not prohibited by any of the functions "STATUS prohibit" or
"Timer_Reordering":

-  assemble and transmit the status report to the Sender, as specified in subclauses 11.5.2.2 and 11.5.2.3.

-  otherwise (if the status report is prohibited by at least one of the functions "STATUS prohibit"):

-

if MRW, MRW_ACK, WINDOW or POLL SUFIs are required in the status report:

-

send a status report immediately excluding ACK, LIST, BITMAP, and RLIST SUFIs;

-

if ACK, LIST, BITMAP, or RLIST SUFIs are required in the status report:

-  delay sending these SUFIs until the prohibit function terminates.

Upon expiry of the timer Timer_Status_Prohibit, the Receiver shall:

3GPP

Release 13

55

3GPP TS 25.322 V13.0.0 (2015-12)

-

-

if at least one status report was triggered during the time the transmission of a status reports was prohibited that
could not be transmitted due to prohibition; and

if transmission of a status reports is no longer prohibited by any of the functions "STATUS prohibit" or
"Timer_Reordering":

-

transmit one status report to the Sender, using the procedure described in subclause 11.5.2.3.

Upon expiry of the timer Timer_Reordering, the Receiver shall:

-

-

if at least one status report was triggered during the time the transmission of a status reports was prohibited that
could not be transmitted due to prohibition; and

if transmission of a status reports is no longer prohibited by any of the functions "STATUS prohibit" or
"Timer_Reordering":

-  update VR(MS) to the SN of the first AMD PDU with SN >= VR(X) which has not been received;

-

-

transmit one status report to the Sender, using the procedure described in subclause 11.5.2.3.

if VR(H) > VR(MS):

-

-

start Timer_Reordering;

set VR(X) to VR(H).

9.7.3

SDU discard function for acknowledged, unacknowledged, and
transparent mode

The SDU discard function is used by the Sender to discharge RLC PDUs from the RLC PDU buffer, when the
transmission of the RLC PDUs does not succeed for a period of time or for a number of transmissions. The SDU
discard function allows to avoid buffer overflow. There are several alternative operation modes of the RLC SDU
discard function. Upper layers control, which discard function shall be used for each RLC entity.

The following is a list of operation modes for the RLC SDU discard function, which are described in detail in the
subsequent subclauses.

Table 9.2: List of criteria that control when to perform SDU discard

Operation mode

Timer based discard, with explicit signalling
Timer based discard, without explicit signalling
SDU discard after MaxDAT number of transmissions
No_discard after MaxDAT number of transmissions

Presence

Network controlled
Network controlled
Network controlled
Network controlled

9.7.3.1

Timer based discard, with explicit signalling

This alternative is only applicable to RLC entities operating in acknowledged mode. It uses a timer based triggering of
SDU discard (Timer_Discard). This makes the SDU discard function insensitive to variations in the channel rate and
provides means for exact definition of maximum delay. However, the SDU loss rate of the connection is increased as
SDUs are discarded.

For every SDU received from upper layers, the Sender shall:

-

start a timer Timer_Discard.

When the timer Timer_Discard of a SDU expires, the Sender shall:

-  discard the SDU;

-

if "Send MRW" is configured, or one or more segments of the discarded SDU were submitted to the lower layer:

-  utilise explicit signalling to inform the Receiver according to subclause 11.6.

3GPP

Release 13

56

3GPP TS 25.322 V13.0.0 (2015-12)

NOTE:  The support of the configuration "Send MRW" and the functionality connected with this configuration is

implementation dependent.

9.7.3.2

Timer based discard, without explicit signalling

This alternative is only applicable to RLC entities operating in unacknowledged or transparent mode. It uses the same
timer based trigger for SDU discard (Timer_Discard) as the one described in the subclause 9.7.3.1. The difference is
that this discard method does not use any peer-to-peer signalling.

For every SDU received from upper layers, the Sender shall:

-

start timer monitoring of the transmission time of the SDU.

When the transmission time exceeds the configured value for a SDU, the Sender shall:

-  discard the SDU without explicit signalling (for RLC entities operating in unacknowledged mode apply

subclause 11.2.4.3 for updating the state variables).

9.7.3.3

SDU discard after MaxDAT number of transmissions

This alternative uses the number of transmissions as a trigger for SDU discard, and is therefore only applicable for
acknowledged mode RLC. This makes the SDU discard function dependent on the channel rate. Also, this variant of the
SDU discard function strives to keep the SDU loss rate constant for the connection, on the cost of a variable delay.

If the number of times an AMD PDU is scheduled for transmission reaches MaxDAT, the Sender shall:

-  discard all SDUs that have segments or "Length Indicators" indicating the end of the SDUs in the AMD PDU;

and

-  utilise explicit signalling to inform the Receiver according to clause 11.6.

9.7.3.4

No_discard after MaxDAT number of transmissions

This alternative uses the number of transmissions, and is therefore only applicable for acknowledged mode RLC.

If the number of times an AMD PDU is scheduled for transmission reaches MaxDAT, the Sender shall:

-

initiate the RLC Reset procedure (see subclause 11.3.4.4).

9.7.3.5

SDU discard not configured

If SDU discard has not been configured for an unacknowledged mode RLC entity, SDUs in the transmitter shall not be
discarded unless the Transmission buffer is full.

When the Transmission buffer in an unacknowledged mode RLC entity is full, the Sender may:

-

if segments of the SDU to be discarded have been submitted to lower layer:

-  discard the SDU without explicit signalling according to subclause 11.2.4.3.

-  otherwise, if no segments of the SDU to be discarded have been submitted to lower layer:

-

remove the SDU from the Transmission buffer without utilising any of the discard procedures.

If SDU discard has not been configured for a transparent mode RLC entity, the Sender shall upon reception of new
SDUs from upper layer:

-  discard all SDUs received from upper layer in previous TTIs that are not yet submitted to lower layer;

-

submit the new SDUs in the first possible TTI.

For an acknowledged mode RLC entity, an SDU discard mode is always configured.

3GPP

Release 13

57

3GPP TS 25.322 V13.0.0 (2015-12)

9.7.4

Void

9.7.5

Local Suspend function for acknowledged and unacknowledged
mode

The upper layers may suspend an RLC entity.

When an RLC entity operating in unacknowledged mode is suspended by upper layers with the parameter N, the RLC
entity shall:

-  acknowledge the suspend request with a confirmation containing the current value of VT(US);

-  not send UMD PDUs with "Sequence Number" SN≥VT(US)+N.

When an RLC entity operating in acknowledged mode is suspended by upper layers with the parameter N, the RLC
entity shall:

-  acknowledge the suspend request with a confirmation containing the current value of VT(S);

-  not send AMD PDUs with "Sequence Number" SN≥VT(S)+N.

When an RLC entity operating in unacknowledged mode is resumed by upper layers, the RLC entity shall:

-

resume data transfer procedure.

When an RLC entity operating in acknowledged mode is resumed by upper layers, the RLC entity shall:

-

if the RLC entity is suspended and a RLC Reset procedure is not ongoing:

-

resume data transfer procedure.

-  otherwise, if the RLC entity is suspended and a RLC Reset procedure is ongoing:

-

-

remove the suspend constraint;

resume the RLC reset procedure according to subclause 11.4.

9.7.6

RLC Stop, RLC Continue function for acknowledged and
unacknowledged mode

The upper layer may stop an RLC entity.

When an RLC entity is stopped, the RLC timers are not affected.

When a RLC entity is stopped by upper layers, the RLC entity shall:

-  not submit any RLC PDUs to lower layer or receive any RLC PDUs;

-  delay triggered Polling functions or status transmissions until the RLC entity is continued.

NOTE:

If the TFC selection exchange has been initiated by sending the RLC Entity Info parameter to MAC, the
RLC entity may delay the stop function until the end of the next TTI.

When a RLC entity is continued by upper layers, the RLC entity shall:

-

if the RLC entity is stopped:

-  continue the data transmission and reception;

-  process the triggered Polling functions and status transmissions.

-  otherwise, if the RLC is not stopped:

-

take no action.

3GPP

Release 13

9.7.7

58

3GPP TS 25.322 V13.0.0 (2015-12)

RLC re-establishment function for acknowledged and
unacknowledged mode

RLC re-establishment is performed upon request by upper layers.

The RLC re-establishment function is applicable for AM or UM RLC. For UM, the whole RLC entity is re-established.
For AM, upper layers may request re-establishment of the whole RLC entity or only the transmitting or receiving side
of the RLC entity.

When an UM RLC entity is re-established by upper layers, the RLC entity shall:

-

-

-

-

reset the state variables to their initial value;

set the configurable parameters to their configured value;

set the hyper frame number (HFN) to the value configured by upper layers;

if it is a receiving UM RLC entity:

-  discard all UMD PDUs.

-

stop all timers;

-

if it is a transmitting UM RLC entity:

-  discard the RLC SDUs for which one or more segments have been submitted to a lower layer;

-

if requested:

-

inform the upper layers of the discarded SDUs.

-  not stop Timer_Discard if the RLC SDU is not discarded.

When the transmitting and/or receiving side of an AM RLC entity is re-established by upper layers, the RLC entity
shall:

-

if the receiving side of the RLC entity is re-established:

-

-

-

reset the state variables specified for the receiver in subclause 9.4 to their initial values;

set the configurable parameters applicable for the receiving side in subclause 9.6 to their configured values;

set the hyper frame number (HFN) in the receiving side (DL in the UE) to the value configured by upper
layers;

-  discard the AMD PDUs in the receiving side.

-

if only the receiving side of the RLC entity is re-established:

-  discard acknowledgement status report, WINDOW SUFI and MRW_ACK SUFI in all STATUS PDUs
and piggybacked STATUS PDUs, RESET PDU and RESET ACK PDU (i.e. discard all control PDUs
except MRW SUFI and POLL SUFI);

-

if an RLC reset procedure is ongoing (i.e. Timer_RST is running):

-

stop Timer_RST;

-  abort the ongoing RLC reset procedure;

-

-

reset VT(RST);

restart a new RLC reset procedure after the RLC re-establishment terminates.

stop Timer_Status_Prohibit;

for the remaining control PDUs and SUFI that were scheduled for transmission before re-establishment
but were not delivered to lower layer:

-

-

3GPP

Release 13

59

3GPP TS 25.322 V13.0.0 (2015-12)

-  assemble the control PDUs and SUFIs that were not discarded into new control PDUs with the

configured RLC PDU size;

-

schedule the new control PDUs for transmission.

-

if the transmitting side of the RLC entity is re-established:

-

-

-

reset the state variables specified for the sender in subclause 9.4 to their initial values;

set the configurable parameters applicable for the transmitting side in subclause 9.6 to their configured
values;

set the hyper frame number (HFN) in the transmitting side (UL in the UE)  to the value configured by upper
layers;

-  discard SDUs in the transmitting side that have been completely transmitted (the AMD PDUs containing
segments of the SDU and the "Length Indicator" indicating the end of the SDU have been transmitted);

-

the UE may also discard partially transmitted SDUs (at least one AMD PDU containing a segment of the
SDU has been transmitted);

-

segment the SDUs that were not discarded into AMD PDUs with the configured RLC PDU size (that may be
different from the size before the re-establishment);

-

if only the transmitter side of the RLC entity is re-established:

-  discard MRW SUFI and POLL SUFI in all STATUS PDUs and piggybacked STATUS PDUs, RESET
PDU and RESET ACK PDU (i.e. discard all control PDUs except acknowledgement status report,
WINDOW SUFI and MRW_ACK SUFI);

-

for the remaining control PDUs and SUFI that were scheduled for transmission before re-establishment
but were not delivered to lower layer:

-  assemble the control PDUs and SUFIs that were not discarded into new control PDUs with the

configured RLC PDU size;

-

schedule the control PDUs for transmission.

-

if an RLC reset procedure is ongoing (i.e. Timer_RST is running):

-

stop Timer_RST;

-  abort the ongoing RLC reset procedure;

-

restart a new RLC reset procedure after the RLC re-establishment terminates.

-

stop Timer_Poll, Timer_MRW and Timer_Poll_Prohibit.

-

if both the transmitter and receiver side of the RLC entity is re-established:

-  discard the control PDUs in both transmitting and receiving side and the AMD PDUs in the transmitting

side;

-

if an RLC reset procedure is ongoing (i.e. Timer_RST is running):

-  abort the ongoing RLC reset procedure.

-

stop all timers described in subclause 9.5 except Timer_Poll_Periodic and Timer_Status_Periodic, and
Timer_Discard for SDUs that have not been discarded.

-

if requested:

-

inform the upper layers of the discarded SDUs.

NOTE:

If the TFC selection exchange has been initiated by sending the RLC Entity Info parameter to MAC, the
RLC entity may delay the re-establishment function until the end of the next TTI.

3GPP

Release 13

60

3GPP TS 25.322 V13.0.0 (2015-12)

9.7.8

Ciphering for acknowledged and unacknowledged mode

The ciphering function is performed in RLC, according to the following rules if a radio bearer is using a non-transparent
RLC mode (AM or UM). The data unit that is ciphered, depends on the transmission mode as described below.

-  For RLC UM mode, the ciphering unit is the UMD PDU excluding the first octet, i.e. excluding the UMD PDU

header. This is shown below in Figure 9.19.

Sequence Number
Length Indicator

.
.
.

Cipherin g
Un it

Length Indicator

Data

PAD

E
E

E

Oct1

(Optional) (1)

(Optional)

(Optional)

OctN

Figure 9.19: Ciphering unit for a UMD PDU

-  For RLC AM mode, the ciphering unit is the AMD PDU excluding the first two octets, i.e. excluding the AMD

PDU header. This is shown below in Figure 9.20.

D/C

Sequence Number

Sequence Number

P

Length Indicator

HE

E

Oct1
Oct2
Oct3

(Optional)

.
.
.

Cipherin g
Un it

Length Indicator

E

Data

PAD or a piggybacked STATUS PDU

OctN

Figure 9.20: Ciphering unit for an AMD PDU

The ciphering algorithm and key to be used are configured by upper layers [8] and the ciphering method shall be
applied as specified in [9].

The parameters that are required by RLC for ciphering are defined in [9] and are input to the ciphering algorithm. The
parameters required by RLC which are provided by upper layers [8] are listed below:

-  RLC AM HFN (Hyper frame number for radio bearers that are mapped onto RLC AM);

-  RLC UM HFN (Hyper frame number for radio bearers that are mapped onto RLC UM);

-  BEARER (defined as the radio bearer identifier in [9]. It will use the value RB identity –1 as in [8]);

-  CK (Ciphering Key).

9.7.9

Reconfiguration of RLC parameters by upper layers

The RLC parameters for an RLC entity may be reconfigured (modified) by upper layers.

3GPP

Release 13

61

3GPP TS 25.322 V13.0.0 (2015-12)

When an RLC parameter is reconfigured by the upper layer, the UE shall:

-

start using the reconfigured value of the RLC parameter.

If the parameter Configured_Rx_Window_Size is reconfigured:

-

-

-

the UE shall update the state variable VR(UM), (see clause 9.4);

the UE shall update the state variable VR(MR), (see clause 9.4);

for AMD PDUs with "Sequence Number" x such that VR(MR)<=x<VR(H):

- the UE may discard these AMD PDUs; if discarded, the state variable VR(H) should be updated
accordingly;

- consider the discarded AMD PDUs as not having been received.

If the parameter Configured_Tx_Window_Size is reconfigured:

-

-

-

the UE shall set the state variable VT(WS) equal to the Configured_Tx_Window_Size;

the UE shall update the state variable VT(MS), (see subclause 9.4);

for AMD PDUs with "Sequence Number" x such that VT(MS)<=x<VT(S):

- the UE shall not discard any AMD PDUs that are not positively acknowledged;

- the UE may discard AMD PDUs that are positively acknowledged.

When the transmission window size or the reception window size is reconfigured the required buffer memory
may temporarily exceed the size of the configured window and thus exceed the available buffer memory (see
subclause 11.3.4.9).

If the parameter OSD_Window_Size is reconfigured:

-

the UE shall remove from storage any PDUs whose sequence numbers, SN, are outside of the storage window
VR(UOH) >= SN > VR(UOH) – OSD_Window_Size.

If the parameter DAR_Window_Size is reconfigured:

-

-

the UE shall remove from storage any PDUs whose sequence numbers are outside of the storage window and
deliver them to the higher RLC function to perform reassembly specified in subclause 11.2.3 and update the
state variable VR(UDR) as specified in subclause 9.7.10;

the UE shall update the state variables VR(UDT) and operate the timer Timer_DAR if needed (see subclause
9.7.10).

9.7.10  Duplicate avoidance and reordering for unacknowledged mode

The duplicate avoidance and reordering function can be configured for use within a receiving UM RLC entity in the
UE. It combines PDU sequences received from several sources and/or repeat transmissions from a single source to form
a single ordered PDU sequence that is passed to the header removal and reassembly functions. It completes duplicate
detection, discard and re-ordering based on the UM PDU sequence number. Where the UM RLC receives input from
several sources, inputs can be added or removed without changing the buffer contents, state variables and timers
associated with the duplicate avoidance and reordering function or any subsequent UM RLC function.

The duplicate avoidance and reordering function makes use of the state variable VR(UDR) and a receive window whose
span is from VR(UDH) – DAR_Window_Size + 1 to VR(UDH) inclusively. For re-ordering the function uses a buffer
for the temporary storage of PDUs.

For each PDU received, the duplicate avoidance and reordering function shall (in the following SN denotes the
sequence number of each PDU):

Setting initial values of state variables:

If the PDU is the first PDU received by the duplicate avoidance and reordering function after establishment or

-
re-establishment:

3GPP

Release 13

62

3GPP TS 25.322 V13.0.0 (2015-12)

-  VR(UDH) is assigned the value SN;

-  VR(UDR) is assigned the value VR(UDH) – DAR_Window_Size + 1.

Duplicate detection and re-ordering:

-

if SN is within the receive window:

-

 if  SN < VR(UDR) or if a PDU with sequence number SN is already stored in the buffer:

-

 the PDU shall be discarded;

-   else:

-

the PDU shall be stored in the buffer.

-

if SN is outside of the receive window:

-

the PDU shall be stored in the buffer;

-  VR(UDH) shall be assigned the value SN, thereby advancing the receive window;

-

for any stored PDUs with sequence numbers < VR(UDH) – DAR_Window_Size + 1, i.e. outside the receive
window after its position is updated, remove the PDU from the buffer and deliver them to the higher RLC
function to perform the actions specified in subclause 11.2.3;

-

if VR(UDR) < VR(UDH) – DAR_Window_Size + 1, i.e. VR(UDR) is outside the updated receive window;

-  VR(UDR) shall be assigned the value VR(UDH) – DAR_Window_Size + 1.

-

if PDU with sequence number VR(UDR) is stored in the buffer:

-

for this PDU and any sequence of stored PDUs with consecutive sequence numbers starting at VR(UDR) + 1,
remove the PDUs from the buffer and deliver them to the higher RLC function to perform the actions
specified in subclause 11.2.3;

-  VR(UDR) shall be assigned the value of x + 1 where x is the sequence number of the highest numbered PDU

that was delivered to the higher RLC function.

Timer operation:

if Timer_DAR is not active when a PDU is stored with SN > VR(UDR) by the duplicate avoidance and

-
reordering function:

-  Timer_DAR shall be started;

-  VR(UDT) shall be assigned the value of  the sequence number of the PDU.

-  Timer_DAR shall be stopped:

-

if the PDU with sequence number VR(UDT) is removed from the buffer before Timer_DAR expires.

-

if Timer_DAR expires:

-

for all stored PDUs with sequence numbers lower or equal to VR(UDT) and for any sequence of stored PDUs
with consecutive sequence numbers starting at VR(UDT) + 1, remove the PDUs from the buffer and deliver
them to the higher RLC function to perform the actions specified in subclause 11.2.3;

-  VR(UDR) shall be assigned the value x + 1 where x is the sequence number of the highest numbered PDU

that was delivered to the higher RLC function.

-  When Timer_DAR is stopped or expires, and there remain PDUs stored by the duplicate avoidance and

reordering function:

-  Timer_DAR shall be started;

-  VR(UDT) shall be assigned the sequence number of the highest numbered stored PDU.

3GPP

Release 13

63

3GPP TS 25.322 V13.0.0 (2015-12)

10

Handling of unknown, unforeseen and erroneous
protocol data

Errors and the handling of errors defined in this clause are normative.

10.1  Erroneous Sequence Number

A STATUS PDU or Piggybacked STATUS PDU including "erroneous Sequence Number" is a STATUS PDU or
Piggybacked STATUS PDU that contains:

-  a LIST, BITMAP or RLIST SUFI in which the "Sequence Number" of at least one AMD PDU that is negatively

acknowledged is outside the interval VT(A)≤"Sequence Number"< VT(S); or

-  an ACK SUFI in which "LSN" is outside the interval VT(A)≤"LSN"≤ VT(S).

If an AM RLC entity receives a STATUS PDU or a Piggybacked STATUS PDU including "erroneous Sequence
Number", it shall:

-  discard the STATUS PDU or the Piggybacked STATUS PDU;

-

if inter-Node B Multiflow operation is not configured by higher layers, initiate the RLC reset procedure (see
subclause 11.4).

10.2

Inconsistent status indication

If an AM RLC entity receives a STATUS PDU or a Piggybacked STATUS PDU that indicates different status for the
same AMD PDU, it shall:

-  discard the STATUS PDU or the Piggybacked STATUS PDU.

10.3

Invalid PDU format

If an UM or AM RLC entity receives a RLC PDU that contains reserved or invalid values (see subclause 9.2), it shall:

-  discard the RLC PDU.

10.4  RLC PDU with CRC error

If an UM or AM RLC entity receives a RLC PDU with an error indication, it shall:

-  discard the RLC PDU.

If a TM RLC entity receives a RLC PDU with an error indication, it shall:

-

if "Delivery of Erroneous SDUs" is configured:

-  process the RLC PDU according to subclause 11.1.3;

-  otherwise:

-  discard the RLC PDU.

11

Elementary procedures

Procedures defined in this clause are normative.

This description assumes elementary procedures. Interactions between procedures are not described.

3GPP

Release 13

64

3GPP TS 25.322 V13.0.0 (2015-12)

11.1

Transparent mode data transfer procedure

11.1.1  General

The transparent mode data transfer procedure is used for transferring data between two RLC peer entities, which are
operating in transparent mode. Data is transferred from Sender to Receiver. This procedure should only apply to entities
in DATA_TRANSFER_READY state. Figure 11.1 below illustrates the elementary procedure for transparent mode
data transfer.

Channels that can be used are DTCH, CCCH (uplink only), SHCCH (uplink only), BCCH and PCCH. The type of
logical channel depends on if the RLC entity is located in the user plane (DTCH) or in the control plane
(CCCH/BCCH/SHCCH/PCCH).

Sender

Receiver

TMD PDU

Figure 11.1: Transparent mode data transfer procedure

11.1.2  Transmission of TMD PDU

Upon a request of transparent mode data transfer from upper layer, the Sender shall:

-

if no SDU discard configuration has been made by upper layers:

-  discard SDUs received in previous TTIs upon reception of new SDUs from upper layers (see subclause

9.7.3.5);

-  otherwise (if "Timer Based SDU Discard without explicit signalling" is configured):

-

-

-

start a timer Timer_Discard for each SDU received from upper layers (see subclause 9.7.3);

schedule the RLC SDUs that have been received from upper layer for transmission;

if one or more RLC SDUs have been scheduled for transmission:

-  notify the lower layer of reception of data from upper layers;

-  perform the actions specified in subclause 11.1.2.2.

11.1.2.1

TMD PDU contents to set

The Sender shall set the data field of the TMD PDU to all or a subset of the data contained in the SDU as described in
subclause 11.1.2.2.

11.1.2.2

Submission of TMD PDUs to the lower layer

If one or more RLC SDUs have been scheduled for transmission, according to subclause 11.1.2, the Sender shall:

-

if it is configured for segmented operation:

-

-

inform the lower layer of the size of the next SDU to be sent;

segment the SDU according to the PDU size indicated by the lower layer.

-  otherwise (the Sender is configured for non-segmented operation):

-

inform the lower layer of the number and size of SDUs available for transmission;

-

submit to the lower layer, the requested number of TMD PDUs;

3GPP

Release 13

65

3GPP TS 25.322 V13.0.0 (2015-12)

-  buffer the SDUs that are not submitted to the lower layer according to the discard configuration (see subclause

9.7.3).

11.1.3  Reception of TMD PDU

Upon delivery by the lower layer of a set of TMD PDUs (received within one TTI), the Receiver shall:

-

if it is configured for segmented operation:

-

reassemble the TMD PDUs received in one TTI into one RLC SDU.

-  otherwise (it is configured for non-segmented operation):

-

treat each received TMD PDU as a SDU;

-

if "Delivery of Erroneous SDUs" is configured as "no":

-

submit only the RLC SDUs received without error to upper layers through the TM-SAP.

-  else if "Delivery of Erroneous SDUs" is configured as "yes":

-

submit all RLC SDUs to upper layers through the TM-SAP;

-  provide an error indication for each SDU received in error.

-  otherwise if "Delivery of Erroneous SDUs" is configured as "No detect":

-

submit all RLC SDUs to upper layers through the TM-SAP.

If segmentation is performed in transparent mode RLC, an SDU is erroneous if one or more of the TMD PDUs received
in a TTI contains an error. If segmentation is not performed, an SDU is erroneous if the corresponding TMD PDU is
erroneous.

11.1.4  Abnormal cases

11.1.4.1

Void

11.1.4.2

SDU discard without explicit signalling

Upon expiry of the timer Timer_Discard in the Sender, the Sender shall:

-  discard the associated SDU;

-

if requested:

-

inform the upper layers of the discarded SDU.

In the case where the TFC selection exchange has been initiated by sending the RLC Entity Info parameter to MAC, the
UE may wait until after it provides MAC with the requested set of PDUs before discarding the afore-mentioned SDU.

11.2  Unacknowledged mode data transfer procedure

11.2.1  General

The unacknowledged mode data transfer procedure is used for transferring data between two RLC peer entities, which
are operating in unacknowledged mode. Data is transferred from Sender to Receiver. This procedure should only apply
to RLC entities in DATA_TRANSFER_READY state or LOCAL_SUSPEND state. Figure 11.2 below illustrates the
elementary procedure for unacknowledged mode data transfer.

Channels that can be used are DTCH, DCCH, CCCH (downlink only), CTCH, SHCCH (downlink only), MCCH,
MSCH, MTCH. The type of logical channel depends on if the RLC entity is located in the user plane (DTCH, CTCH,
MTCH) or in the control plane (DCCH/CCCH(downlink only)/SHCCH(downlink only)/MCCH/MSCH). One or

3GPP

Release 13

66

3GPP TS 25.322 V13.0.0 (2015-12)

several PDUs may be transmitted in each transmission time interval (TTI). For each TTI, MAC decides which PDU size
shall be used and how many PDUs shall be transmitted.

Sender

UMD PDU

Receiver

Figure 11.2: Unacknowledged mode data transfer procedure

11.2.2  Transmission of UMD PDU

Upon a request of unacknowledged mode data transfer from upper layer, the Sender shall:

-

if no SDU discard configuration has been made by upper layers:

-  only discard SDUs when the Transmission buffer is full (see subclause 9.7.3);

-

if "Timer based SDU Discard without explicit signalling" is configured:

-

start a timer Timer_Discard for each SDU received from upper layer (see subclause 9.7.3);

-

-

schedule the RLC SDUs received from upper layer for transmission;

if one or more RLC SDUs have been scheduled for transmission:

-  notify the lower layer of reception of data from upper layers;

-  perform the actions specified in subclause 11.2.2.2.

A UMD PDU shall be considered to be a padding PDU if it consists only of an RLC Header with one length indicator
(indicating that the rest of the PDU is padding) and padding.

11.2.2.1

UMD PDU contents to set

The Sender shall:

-

-

set the field "Sequence Number" equal to VT(US);

set a "Length Indicator" field for each SDU that ends in the UMD PDU according to subclause 9.2.2.8.

For each "Extension bit" field in the RLC header, the Sender shall:

-

if the next field in the UMD PDU is a "Length Indicator":

-

set the "Extension bit" to "1";

-  otherwise if the next field in the UMD PDU is data:

-

set the "Extension bit" to "0".

11.2.2.2

Submission of UMD PDUs to the lower layer

If one or more SDUs have been scheduled for transmission according to subclause 11.2.2, the Sender shall:

-

-

inform the lower layer of the number and size of SDUs scheduled for transmission;

if "SN_Delivery" is configured:

-

segment, but not concatenate SDUs

-  else:

3GPP

Release 13

67

3GPP TS 25.322 V13.0.0 (2015-12)

-

segment, and if possible concatenate the SDUs according to the PDU sizes indicated by the lower layer (see
subclause 9.2.2.9);

-

submit to the lower layer, the requested number of UMD PDUs;

-  update VT(US) for each UMD PDU submitted to the lower layer (see subclause 9.4);

-  buffer the SDUs that are not submitted to the lower layer according to the discard configuration (see subclause

9.7.3).

11.2.3  Reception of UMD PDU

Upon delivery of a set of UMD PDUs from the lower layer or from the duplicate avoidance and reordering subentity,
the Receiver shall:

-

if "out of sequence SDU delivery" is configured:

-  perform the actions specified in subclause 11.2.3.2;

-  else:

-  perform the actions specified in subclause 11.2.3.1.

11.2.3.1  SDU discard and re-assembly

Upon delivery of a set of UMD PDUs from the lower layer or from the duplicate avoidance and reordering subentity,
the Receiver shall:

-

if out-of-sequence reception is configured and  SN ≥ VR(UM):

-  discard the UMD PDU.

-  else:

-  update VR(US) according to each received UMD PDU (see subclause 9.4);

-

if the updating step of VR(US) is not equal to one (i.e. one or more UMD PDUs are missing):

-  discard the SDUs that could have segments or "Length Indicators" indicating the end of the SDUs in the

missing UMD PDUs according to subclauses 9.2.2.8 and 9.2.2.9.

-

if the special "Length Indicator" "1111 100" or "1111 1111 1111 100" is the first "Length Indicator" of a
UMD PDU received on the downlink:

-  consider the first data octet in this UMD PDU as the first octet of an RLC SDU.

if the "Extension bit" indicates that the UMD PDU contains a complete SDU which is not segmented,

-
concatenated or padded:

-  consider the data part in this UMD PDU as one complete RLC SDU.

-

if the special "Length Indicator" "1111 101" or “1111 1111 1111 101” is the first "Length Indicator" of a UMD
PDU received on the downlink:

-  consider the first data octet in this UMD PDU as the first octet of an RLC SDU and the last data octet as the

last octet of the same RLC SDU.

-

if the special "Length Indicator" "1111 1111 1111 010" is the first "Length Indicator" of a UMD PDU received
on the downlink:

-  consider the first data octet in this UMD PDU as the first octet of an RLC SDU and the second last data octet

as the last octet of the same RLC SDU.

-

-

reassemble the received UMD PDUs into RLC SDUs;

submit the RLC SDUs to upper layers through the UM-SAP.

3GPP

Release 13

68

3GPP TS 25.322 V13.0.0 (2015-12)

11.2.3.2  Out of sequence SDU delivery

To enable the recovery of SDUs from UMD PDUs that are received in different transmissions the receiving function
shall store PDUs until all SDUs that are associated with the PDU can be reconstructed or until they are discarded in
accordance with the procedures described below. SDUs are transferred to the upper layers as soon as all PDUs that
contain the segments of the SDU and the "Length Indicator" indicating the end of the SDU  have been received.

Upon delivery of a set of UMD PDUs from the lower layer, the Receiver shall for each PDU (in the following SN
denotes the sequence number of each PDU):

-

If the PDU is the first PDU received (after the receiving entity is established or re-established or after
Timer_OSD expires):

-  VR(UOH) shall be assigned the value SN-1.

-

if VR(UOH) > SN > VR(UOH) – OSD_Window_Size then:

-

if a PDU with sequence number SN is already stored:

-  discard the PDU;

-  else:

-

store the PDU in sequence number order.

-  else:

-  VR(UOH) shall be assigned the value SN, thereby advancing the storage window;

-

-

store the PDU in sequence number order;

remove from storage any PDUs whose sequence numbers, SN, are outside of the storage window VR(UOH)
> SN > VR(UOH) – OSD_Window_Size;

-

if Timer_OSD is active then Timer_OSD shall be stopped;

-  Timer_OSD shall be started.

-

if a PDU with sequence number SN was stored:

-

if the PDU contains one or more complete SDUs and/or if the PDU contains segments of  SDUs for which all
the remaining segments and length indicators are contained in stored PDUs:

-

-

-

re-assemble the SDUs;

submit the SDUs to upper layers through the UM-SAP;

remove from storage any PDUs which do not contain any segment of a SDU that has not been re-
assembled, and do not contain one of the special length indicators "0000 000", "0000 0000 0000 000" or
"1111 1111 1111 011" that indicate the end of a SDU that has not been re-assembled.

NOTE 0:  If PDUs are removed from storage after SDU recovery then retransmitted PDUs may result in the

duplicate transfer of SDUs to the higher layers.

-

if Timer_OSD expires:

-

remove from storage all stored PDUs.

NOTE 1:  When configured for out of sequence SDU delivery, the transmitter should consider the possibility that a
loss of a number of 128 − OSD_Window_Size consecutively numbered PDUs may result in an
undetected protocol error in the receiver, if the transmit state variable VT(US), at the end of a time
interval equal to the duration of Timer_OSD, is greater than 128 + SN − OSD_Window_Size + 1, where
SN is the lowest sequence number of any PDU transmitted or retransmitted within that time interval.

NOTE 2:  The transmitter should not concatenate within a single PDU, SDUs or fractions of SDUs that contain

MBMS Access Information messages with SDUs or fractions of SDUs that contain other MCCH message
types.

3GPP

Release 13

69

3GPP TS 25.322 V13.0.0 (2015-12)

NOTE 3:  SDUs are contained within consecutively numbered PDUs. To enable SDUs containing MBMS Access
Information messages to be transmitted at their designated times, the transmitter may transmit PDUs out
of sequence order.

NOTE 4:  The transmitter should not transmit within a single PDU, SDUs or fractions of SDUs that contain MBMS

Access Information messages with the special length indicator "0000 000","0000 0000 0000 000", and
"1111 1111 1111 011".

11.2.4  Abnormal cases

11.2.4.1

Length Indicator value reserved for UMD PDU

Upon delivery by the lower layer of an UMD PDU that contains a "Length Indicator" value specified to be reserved for
UMD PDUs in this version of the protocol, the Receiver shall:

-

ignore that UMD PDU.

11.2.4.2

Invalid length indicator value

If the "Length Indicator" of an UMD PDU has a value that is larger than the PDU size – RLC header size and is not one
of the predefined values listed in the table of subclause 9.2.2.8, the Receiver shall:

-

ignore the UMD PDU.

11.2.4.3

SDU discard without explicit signalling

Upon expiry of the timer Timer_Discard in the Sender, the Sender shall:

-  discard the associated SDU;

-

if requested:

-

inform the upper layers of the discarded SDU;

-

for the first UMD PDU to be transmitted after the discard operation, the Sender shall:

-

-

-

increment VT(US) so that the "Sequence Number" field in this UMD PDU is incremented with two
compared with the previous UMD PDU;

fill the first data octet in this UMD PDU with the first octet of an RLC SDU;

if the "Extension bit" does not indicate that the UMD PDU contains a complete SDU which is not segmented,
concatenated or padded:

-

set the first "Length Indicator" in this UMD PDU to indicate that the previous RLC PDU was exactly
filled with the last segment of an RLC SDU (to avoid that the Receiver unnecessarily discards an extra
SDU).

In the case where the TFC selection exchange has been initiated by sending the RLC Entity Info parameter to MAC, the
UE may wait until after it provides MAC with the requested set of UMD PDUs before discarding the afore-mentioned
SDU.

11.2.4.4

Invalid PDU size

In the UE, if the "DL RLC UM LI size" is configured to 7 bits, if a received UMD PDU has a size larger than 125
octets, the Receiver shall:

-

ignore that UMD PDU.

11.3  Acknowledged mode data transfer procedure

11.3.1  General

The acknowledged mode data transfer procedure is used for transferring data between two RLC peer entities, which are
operating in acknowledged mode. Data is transferred from Sender to Receiver. This procedure should only apply to

3GPP

Release 13

70

3GPP TS 25.322 V13.0.0 (2015-12)

RLC entities in DATA_TRANSFER_READY state or LOCAL_SUSPEND state. Figure 11.3 below illustrates the
elementary procedure for acknowledged mode data transfer.

The AMD PDUs shall be transmitted on the DCCH logical channel if the Sender is located in the control plane and on
the DTCH if it is located in the user plane. One or several PDUs may be transmitted in each transmission time interval
(TTI) and MAC decides how many PDUs shall be transmitted in each TTI.

Sender

Receiver

AMD PDU

Figure 11.3: Acknowledged mode data transfer procedure

11.3.2  Transmission of AMD PDU

Upon a request of acknowledged mode data transfer from upper layers or upon retransmission of AMD PDUs, the
Sender shall:

-  when RLC SDUs are received from upper layers:

-

if "fixed RLC PDU size" has been configured:

-

segment, and if possible concatenate the RLC SDUs into AMD PDUs where the fixed PDU size is
configured by upper layer (see subclause 9.2.2.9);

-

if the last octet of the PDU is the last octet of an SDU and there is no SDU concatenation inside the PDU, and
the “use of the special value of the HE field” has been configured by higher layers, set the HE field to
indicate that the last octet of the PDU is the last octet of an SDU (see subclause 9.2.2.7).

-

if "flexible RLC PDU size" has been configured:

-

the last segment of an RLC SDU shall be concatenated with the first segment of the next RLC SDU in
order to fill the data field at least up to the Minimum UL RLC PDU size. If data to be transmitted is not
enough to create an AMD PDU of the minimum size, it is allowed to create an AMD PDU including all
data to be transmitted, even if the resulting size is smaller than the Minimum UL RLC PDU size.

-

set a "Length Indicator" field for each SDU that ends in the AMD PDU according to subclause 9.2.2.8,
except for the SDUs where the end of the SDU has been indicated by the HE field according to subclause
9.2.2.7;

-

if "Timer based SDU Discard with explicit signalling" is configured:

-

start a timer Timer_Discard for each SDU received from upper layer (see subclause 9.7.3);

-

schedule the AMD PDUs for transmission;

-

for each AMD PDU which has been negatively acknowledged (see subclause 11.5.3):

-

if the "Sequence Number" of the AMD PDU is less than VT(MS):

-

schedule the AMD PDU for retransmission;

-

-

-

-

if a poll has been triggered by one of configured polling functions (see subclause 9.7.1); and

if polling is not prohibited (see subclause 9.5); and

if no AMD PDU is scheduled for transmission or retransmission; and

if there is at least one PDU that has been transmitted, has not been discarded and has not yet been acknowledged:

-

if the value of "Configured_Tx_Window_Size" is larger than or equal to "2048":

3GPP

Release 13

71

3GPP TS 25.322 V13.0.0 (2015-12)

-

select the AMD PDU with "Sequence Number" equal to VT(S)-1; or

-  assemble a POLL SUFI according to subclause 9.2.2.11.9 when "flexible RLC PDU size" is configured;

-  otherwise if the "Configured_Tx_Window_Size" is less than "2048":

-

-

select the AMD PDU with "Sequence Number" equal to VT(S)-1; or

select an AMD PDU that has not been discarded and has not yet been acknowledged by the peer entity; or

-  assemble a POLL SUFI according to subclause 9.2.2.11.9 when “flexible RLC PDU size” is configured;

-

if an AMD PDU was selected, schedule the selected AMD PDU for retransmission (in order to transmit a
poll), or if a POLL SUFI was assembled, schedule a STATUS PDU containing the POLL SUFI for
transmission:

-

if the timer Timer_Poll is configured:

-

start the timer Timer_Poll according to subclause 9.5.

NOTE 1:  In downlink, if "flexible RLC PDU size" is configured, the UTRAN should segment, and if possible

concatenate the RLC SDUs into AMD PDUs with a size not larger than the maximum RLC PDU size.

NOTE 2:  In downlink, UTRAN can initiate the Polling function by assembling a POLL SUFI when "flexible RLC

PDU size" in downlink is configured. If a POLL SUFI was assembled, UTRAN should schedule and
submit to lower layer a STATUS PDU containing the POLL SUFI.

NOTE 3:  In uplink, the UE can initiate the Polling function by assembling a POLL SUFI according to subclause
9.2.2.11.9 when "flexible RLC PDU size" in uplink is configured. If a POLL SUFI was assembled, the
UE should schedule and submit to lower layer a STATUS PDU containing the POLL SUFI.

Each time an AMD PDU is scheduled for transmission or retransmission, the Sender shall:

-

-

increment the value of the corresponding VT(DAT);

if VT(DAT) = MaxDAT:

-  perform the actions specified in subclause 11.3.3a;

-  e1se:

-  notify the lower layer that data is available for transmission;

-  perform the actions specified in subclause 11.3.2.2.

In AM, a PDU shall be considered to be a padding PDU if it is:

-  an AMD PDU consisting only of an RLC Header with one "Length Indicator" (indicating that the rest of the

PDU is padding) and padding; or

-  a STATUS PDU consisting only of a NO_MORE SUFI.

11.3.2.1

AMD PDU contents to set

If the AMD PDU is transmitted for the first time, the Sender shall:

-

-

-

set the "Sequence Number" field equal to VT(S);

if the last octet of the PDU is the last octet of an SDU and there is no SDU concatenation inside the PDU, and
the use of the special value of HE field has been configured by higher layers, set the HE field to indicate that the
last octet of the PDU is the last octet of an SDU (see subclause 9.2.2.7)

set a "Length Indicator" field for each SDU that ends in the AMD PDU according to subclause 9.2.2.8, except
for the SDUs where the end of the SDU has been indicated by the HE field according to subclause 9.2.2.7;

-

set the "Polling bit" to the value specified in subclause 11.3.2.1.1.

Otherwise if the AMD PDU is retransmitted:

3GPP

Release 13

72

3GPP TS 25.322 V13.0.0 (2015-12)

-  use the same value of the "Sequence Number" field as in the original transmission of the AMD PDU;

-

if the "Length Indicator" fields needed in the AMD PDU according to subclause 9.2.2.8 has changed due to that
a piggybacked STATUS PDU is included in the AMD PDU or a piggybacked STATUS PDU was included in
the previous transmission of the AMD PDU:

-  update the "Length Indicator" fields according to 9.2.2.8.

-

set the "Polling bit" to the value specified in subclause 11.3.2.1.1.

11.3.2.1.1

Setting of the Polling bit

The Sender shall:

-

if a poll has been triggered by one or several poll triggers (see subclause 9.7.1):

-

if polling is not prohibited, see subclause 9.5:

-

set the "Polling bit" in the AMD PDU header to "1";

-  otherwise:

-

set the "Polling bit" in the AMD PDU header to "0".

11.3.2.1.2

Void

11.3.2.2

Submission of AMD PDUs to lower layer

If one or more AMD PDUs have been scheduled for transmission or retransmission according to subclause 11.3.2, the
Sender shall:

-  not submit any AMD PDUs to lower layer that is not allowed to transmit. AMD PDUs are only allowed to

transmit:

-

if the AMD PDU has a "Sequence Number" < VT(MS) or the AMD PDU has a "Sequence Number" equal to
VT(S)-1; and

-

if the AMD PDU is not restricted to be transmitted by the local suspend function, see subclause 9.7.5.

inform the lower layer of both the numbers of AMD PDUs scheduled and allowed for transmission or
retransmission;

set the AMD PDU contents according to subclause 11.3.2.1;

submit to the lower layer the requested number of AMD PDUs;

treat retransmissions with higher priority than AMD PDUs transmitted for the first time;

-

-

-

-

-  update the state variables in clause 9.4 for each AMD PDU submitted to lower layer except VT(DAT) which has

already been updated, see subclause 11.3.2;

-

-

if the "Polling bit" is set to "1" in any of the AMD PDUs; and

if the timer Timer_Poll is configured;

-

start the timer Timer_Poll according to subclause 9.5;

-  buffer the AMD PDUs that are not submitted to the lower layer according to the discard configuration (see

subclause 9.7.3).

11.3.3  Reception of AMD PDU by the Receiver

Upon reception of an AMD PDU, the Receiver shall:

-

in the UE if "fixed RLC PDU size" has been configured:

3GPP

Release 13

73

3GPP TS 25.322 V13.0.0 (2015-12)

-

if the "downlink AMD PDU size" has not yet been set:

-

set the "downlink AMD PDU size" to the size of the received PDU.

-  update VR(R), VR(H) and VR(MR) state variables for each received AMD PDU (see clause 9.4);

-

if Timer_Reordering is configured:

-

if a received AMD PDU SN = VR(MS)

-  update VR(MS) to SN of the first AMD PDU that has not been received;

-

if Timer_Reordering is running:

-

-

if VR(X) = VR(R); or

if VR(X) falls outside of the receiving window and VR(X) is not equal to VR(MR):

-

stop and reset Timer_Reordering;

-

if Timer_Reordering is not running (includes the case Timer_Reordering is stopped due to actions above):

-

if VR (H) > VR(R):

-

-

start Timer_Reordering;

set VR(X) to VR(H).

-

if a received AMD PDU includes a "Polling bit" set to "1", or "Missing PDU Indicator" is configured and the
Receiver detects that a PDU is missing:

-

initiate the STATUS PDU transfer procedure;

reassemble the received AMD PDUs into RLC SDUs;

if "In-Sequence Delivery" is configured:

-

-

-  deliver the RLC SDUs in-sequence (i.e. in the same order as the RLC SDUs were originally transmitted by

the peer entity) to upper layers through the AM-SAP.

-  otherwise:

-  deliver the RLC SDUs in arbitrary order to upper layers through the AM-SAP.

11.3.3a  Reached maximum number of attempts

If VT(DAT) = MaxDAT, the Sender shall:

-

if "No_discard after MaxDAT number of transmissions" is configured:

-

initiate the RLC reset procedure, see subclause 11.4.

-

if "SDU discard after MaxDAT number of transmissions" is configured:

-

initiate the "SDU discard with explicit signalling" procedure for the corresponding SDU, see subclause 11.6.

11.3.4  Abnormal cases

11.3.4.1

Void

11.3.4.2

Receiving an AMD PDU outside the reception window

Upon reception of an AMD PDU with "Sequence Number" outside the interval VR(R)≤SN<VR(MR), the Receiver
shall:

3GPP

Release 13

74

3GPP TS 25.322 V13.0.0 (2015-12)

-  discard the AMD PDU;

-

if the "polling bit" in the discarded AMD PDU is set to "1":

-

initiate the STATUS PDU transfer procedure.

11.3.4.3

Timer_Discard timeout

11.3.4.3.1

SDU discard with explicit signalling

Upon expiry of the timer Timer_Discard, the Sender shall:

-

initiate the SDU discard with explicit signalling procedure, see subclause 11.6.2.

In the case where the TFC selection exchange has been initiated by sending the RLC Entity Info parameter to MAC, the
UE may wait until after it provides MAC with the requested set of PDUs before discarding the afore-mentioned SDUs.

11.3.4.4

Void

11.3.4.5

Invalid length indicator value

If the "Length Indicator" of an AMD PDU has a value that is larger than the PDU size – RLC header size and is not one
of the predefined values listed in the table of subclause 9.2.2.8, the Receiver shall:

-

ignore that AMD PDU.

11.3.4.6

Length Indicator value reserved for AMD PDU

Upon delivery by the lower layer of an AMD PDU that contains a "Length Indicator" value specified to be reserved for
AMD PDUs in this version of the protocol, the Receiver shall:

-

ignore that AMD PDU.

11.3.4.7

Void

11.3.4.8

Receiving an AMD PDU within the reception window more than once
(Handling of Duplicates)

Upon reception of an AMD PDU with a “Sequence Number” within the interval VR(R)≤SN<VR(MR), for which
"Sequence Number" an AMD PDU has already been received, the Receiver shall:

-  discard the AMD PDU;

-  consider the AMD PDU with this "Sequence Number" as having been correctly received in the next status report

to be transmitted;

-

if the "polling bit" in the discarded AMD PDU is set to "1":

-

initiate the STATUS PDU transfer procedure.

-

if a piggybacked STATUS PDU is included in the AMD PDU:

-  perform the actions specified in subclause 11.5.3.

11.3.4.9

Full Buffer Behavior

It is foreseen that in some conditions, e.g. when the window size is re-configured, the UE may have memory
limitations.

While the buffer memory is full:

-

-

the UE is not required to segment RLC SDUs into AMD PDUs as per Subclause 11.3.2;

the UE shall:

3GPP

Release 13

75

3GPP TS 25.322 V13.0.0 (2015-12)

-  be able to process incoming AMD PDUs (especially to be able to process and store the AMD PDU with

"Sequence Number" = VR(R));

-  operate according to the normal protocol, e.g. process STATUS reports and perform retransmissions;

-

the UE may discard received AMD PDUs with "Sequence Number" within the receiving window and consider
the discarded AMD PDUs as not having been received.

11.3.4.10

Invalid PDU size

In the UE, if "fixed RLC PDU size" has been configured and if a received AMD PDU has a size different from the
configured "downlink AMD PDU size", the Receiver shall:

-

ignore that AMD PDU.

11.3.5  Transmission of POLL SUFI

Each time a STATUS PDU containing the POLL SUFI is scheduled for transmission, the Sender shall:

-

-

increment the value of the corresponding VT(DAT) of the AMD PDU with sequence number equal to VT(S)-1;

if VT(DAT) = MaxDAT:

-  perform the actions specified in subclause 11.3.3a;

-  e1se:

-  notify the lower layer that STATUS PDU is available for transmission.

11.4  RLC reset procedure

11.4.1  General

The RLC reset procedure is used to reset two RLC peer entities, which are operating in acknowledged mode.
Figure 11.4 below illustrates the elementary procedure for an RLC reset. During the reset procedure the hyper frame
numbers (HFN) in UTRAN and UE are synchronised. Two HFNs used for ciphering needs to be synchronised, DL
HFN in downlink and UL HFN in uplink. In the reset procedure, the highest UL HFN and DL HFN used by the RLC
entity in the transmitting sides, i.e. the HFNs associated with AMD PDUs of "Sequence Number"=VT(S)-1 if at least
one AMD PDU had been transmitted or of "Sequence Number"=0 if no AMD PDU had been transmitted, are
exchanged between UE and UTRAN.

The RESET PDUs and the RESET ACK PDUs have higher priority than AMD PDUs.

Sender

RESET

Receiver

RESET ACK

Figure 11.4: RLC reset procedure

11.4.2

Initiation

The Sender shall:

-

if one of the following triggers is detected:

1)  "No_Discard after MaxDAT number of transmissions" is configured and VT(DAT) equals the value MaxDAT

(see subclause 9.7.3.4);

3GPP

Release 13

76

3GPP TS 25.322 V13.0.0 (2015-12)

2)  VT(MRW) equals the value MaxMRW;

3)  A STATUS PDU or a piggybacked STATUS PDU including "erroneous Sequence Number" is received (see

clause 10);

-

-

-

-

stop transmitting any AMD PDU or STATUS PDU;

ignore any incoming AMD PDU, piggybacked STATUS PDU or STATUS PDU;

increment VT(RST) by 1;

if VT(RST) = MaxRST:

-  perform the actions specified in subclause 11.4.4a.

-  else (if VT(RST) < MaxRST):

-

-

submit a RESET PDU to the lower layer;

start the timer Timer_RST according to the description in subclause 9.5.

NOTE:

If the TFC selection exchange has been initiated by sending the RLC Entity Info parameter to MAC, the
RLC entity may delay the RLC reset procedure until the end of the next TTI.

When a reset procedure has been initiated it can only be ended upon reception of a RESET ACK PDU with the same
RSN value as in the corresponding RESET PDU, upon request of re-establishment due to request of re-establishment
(for the whole RLC entity or for only the transmitting or receiving side of the RLC entity), or release from upper layer.
A reset procedure is not interrupted by the reception of a RESET PDU from the peer entity.

11.4.2.1

RESET PDU contents to set

The Sender shall:

-

-

set the HFNI field to the currently highest used HFN (DL HFN when the RESET PDU is sent by UTRAN or UL
HFN when the RESET PDU is sent by the UE);

set the RSN field to the sequence number of the RESET PDU. The sequence number of the first RESET PDU
after the AM entity is established or re-established (for the whole RLC entity or for only the transmitting or
receiving side of the RLC entity) shall be "0". This sequence number is incremented every time a new RESET
PDU is transmitted, but not when a RESET PDU is retransmitted.

11.4.3  Reception of the RESET PDU by the Receiver

Upon reception of a RESET PDU the Receiver shall:

-

-

-

-

if the RESET PDU is not the first RESET PDU received since the entity was established or re-established; and

if the RSN value in the RESET PDU is the same as the RSN value in the last received RESET PDU:

-  only submit a RESET ACK PDU to the lower layer with the contents set exactly as in the last transmitted

RESET ACK PDU (i.e., in this case the RLC entity is not reset).

if the RESET PDU is the first RESET PDU received since the entity was established or re-established; or

if the RSN value is different from the RSN value in the last received RESET PDU:

-

-

-

submit a RESET ACK PDU to the lower layer with the content set as specified in subclause 11.4.3.1;

reset the state variables described in subclause 9.4 except VT(RST) to their initial values;

stop all the timers described in subclause 9.5 except Timer_RST, Timer_Discard, Timer_Poll_Periodic and
Timer_Status_Periodic;

-

reset configurable parameters to their configured values;

-  discard all RLC PDUs in the receiving side of the AM RLC entity;

3GPP

Release 13

77

3GPP TS 25.322 V13.0.0 (2015-12)

-  discard all RLC SDUs that were transmitted before the reset in the transmitting side of the AM RLC entity;

-

if requested for the transmitting side:

-

inform the upper layers of the discarded SDUs.

-

-

set the HFN (DL HFN when the RESET PDU is received in UE or UL HFN when the RESET PDU is
received in UTRAN) equal to the HFNI field in the received RESET PDU;

increase with one the UL HFN and DL HFN, and the updated HFN values shall be used for the first
transmitted and received AMD PDUs after the reset procedure.

NOTE:

If the TFC selection exchange has been initiated by sending the RLC Entity Info parameter to MAC, the
RLC entity may delay the RLC SDUs discard in the transmitting side of the AM RLC entity until the end
of the next TTI.

11.4.3.1

RESET ACK PDU contents to set

The RLC entity shall:

-

set the hyper frame number indicator field (HFNI) to the currently highest used HFN (DL HFN when the RESET
ACK PDU is sent by UTRAN or UL HFN when the RESET ACK PDU is sent by the UE);

-

set the RSN field to the same value as in the corresponding received RESET PDU.

11.4.4  Reception of the RESET ACK PDU by the Sender

Upon reception of a RESET ACK PDU, the Sender shall:

-

if the Sender has already transmitted a RESET PDU which has not been yet acknowledged by a RESET ACK
PDU:

-

if the received RSN value is the same as the one in the corresponding RESET PDU:

-

-

-

set the HFN value (DL HFN when the RESET ACK PDU is received in UE or UL HFN when the RESET
ACK PDU is received in UTRAN) to the HFNI field of the received RESET ACK PDU;

reset the state variables described in subclause 9.4 to their initial values;

stop all the timers described in subclause 9.5 except Timer_Discard, Timer_Poll_Periodic and
Timer_Status_Periodic;

-

reset configurable parameters to their configured values;

-  discard all RLC PDUs in the receiving side of the AM RLC entity;

-  discard all RLC SDUs that were transmitted before the reset in the transmitting side of the AM RLC

entity;

-

if requested for the transmitting side:

-

inform the upper layers of the discarded SDUs.

-

increase with one the UL HFN and DL HFN, and the updated HFN values shall be used for the first
transmitted and received AMD PDUs after the reset procedure;

-  otherwise (if the received RSN value is not the same as the one in the corresponding RESET PDU):

-  discard the RESET ACK PDU;

-  otherwise (if the Sender has not transmitted a RESET PDU which has not been yet acknowledged by a RESET

ACK PDU):

-  discard the RESET ACK PDU.

NOTE:

If the TFC selection exchange has been initiated by sending the RLC Entity Info parameter to MAC, the
RLC entity may delay the RLC SDUs discard in the transmitting side until the end of the next TTI.

3GPP

Release 13

78

3GPP TS 25.322 V13.0.0 (2015-12)

11.4.4a  Reached maximum number of attempts

If VT(RST) = MaxRST, the Sender shall:

-

-

-

terminate the ongoing RLC RESET procedure;

stop the timer Timer_RST if it was started;

indicate unrecoverable error to upper layer.

11.4.5  Abnormal cases

11.4.5.1

Timer_RST timeout

If Timer_RST expires before the reset procedure is terminated, the Sender shall:

-

-

increment VT(RST) by one;

if VT(RST)<MaxRST:

-

-

-

set the RESET PDU as previously transmitted;

transmit the RESET PDU;

restart Timer_RST according to the description in subclause 9.5.

-  else (if VT(RST) = MaxRST):

-  perform the actions specified in subclause 11.4.4a.

11.4.5.2

Void

11.4.5.3

Reception of the RESET PDU by the Sender

Upon reception of a RESET PDU, the Sender shall:

-

-

-

submit a RESET ACK PDU to the lower layer with the content set as specified in subclause 11.4.3.1;

reset the state variables described in subclause 9.4 except VT(RST) to their initial values;

stop all the timers described in subclause 9.5 except Timer_RST, Timer_Discard, Timer_Poll_Periodic and
Timer_Status_Periodic;

-

reset configurable parameters to their configured values;

-  discard all RLC PDUs in the receiving side of the AM RLC entity;

-  discard all RLC SDUs that were transmitted before the reset in the transmitting side of the AM RLC entity;

-

if requested for the transmitting side:

-

inform the upper layers of the discarded SDUs.

-

set the HFN (DL HFN when the RESET PDU is received in UE or UL HFN when the RESET PDU is received
in UTRAN) equal to the HFNI field in the received RESET PDU.

NOTE:

If the TFC selection exchange has been initiated by sending the RLC Entity Info parameter to MAC, the
RLC entity may delay the RLC SDUs discard in the transmitting side until the end of the next TTI.

3GPP

Release 13

79

3GPP TS 25.322 V13.0.0 (2015-12)

11.5  STATUS report transfer procedure

11.5.1  General

The status report transfer procedure is used for transferring of status information between two RLC peer entities, which
are operating in acknowledged mode. Figure 11.5 below illustrates the elementary procedure for status report transfer.
A status report consists of one or several STATUS PDUs.

In case two logical channels are configured in the uplink, only acknowledgement status reports, MRW ACK SUFI and
WINDOW SUFI shall be transmitted on the second logical channel. In case two logical channels are configured in the
downlink, control PDUs can be transmitted on any of the two logical channels.

The STATUS PDUs have higher priority than AMD PDUs.

Sender

Receiver

STATUS PDU

Figure 11.5: Status report transfer procedure

11.5.2

Initiation

The Receiver shall:

-

if one of the following triggers is detected:

1)  The "Polling bit" in a received AMD PDU is set to "1";

2)  "Missing PDU Indicator" is configured and a missing AMD PDU is detected;

3)  The "Timer based STATUS transfer" is configured and the timer Timer_Status_Periodic has expired:

-  act on the trigger as specified in subclause 9.7.2.

4)  Void

5)  If the flexible RLC PDU size is configured and POLL SUFI is received:

-  consider that Poll_SN has been transmitted by the sender as specified in subclause 9.4:

-  act on the trigger as specified in subclause 9.7.2.

11.5.2.1

Piggybacked STATUS PDU

The Receiver may:

-

if STATUS PDU(s) to be sent fit into padding octets in AMD PDU(s) to be sent:

-  piggyback a STATUS PDU on the AMD PDU to be sent.

Submission of a piggybacked STATUS PDU in an AMD PDU to the lower layer follows the same rules as an ordinary
STATUS PDU.

11.5.2.2

STATUS PDU contents to set

On triggering of a status report, the Receiver shall:

-

if the "STATUS prohibit" is not active:

-

If Timer_Reordering is not configured:

3GPP

Release 13

80

3GPP TS 25.322 V13.0.0 (2015-12)

-

-

include negative acknowledgements for all AMD PDUs detected as missing;

include an ACK SUFI positively acknowledging all AMD PDUs received up to at least VR(R);

-

If Timer_Reordering is configured, for all SN such that VR(R) <= SN < VR(MS):

-

-

include negative acknowledgements for all AMD PDUs detected as missing;

include an ACK SUFI positively acknowledging all AMD PDUs received up to at least VR(R);

-

if an MRW SUFI assembled as specified in subclause 11.6.2.2 had not been sent:

-  optionally include the MRW SUFI;

-

if an MRW_ACK SUFI assembled as specified in subclause 11.6.2.2 is awaiting transmission:

-  optionally include the MRW_ACK SUFI;

-

if the Sender's transmission window is to be updated:

-  optionally include the WINDOW SUFI;

-

if all SUFIs can be accommodated in one STATUS PDU:

-  construct the status report using one STATUS PDU, using one of the allowed PDU sizes;

-

if the SUFIs included do not fill the entire STATUS PDU:

-

if the STATUS PDU is not terminated with an ACK SUFI:

-

terminate the STATUS PDU with a NO_MORE SUFI.

-  use padding in the remainder of the STATUS PDU (padding size may be zero);

-  otherwise (the status report is segmented):

-  construct STATUS PDUs including only complete SUFIs using one of the allowed PDU sizes. The set of

STATUS PDUs shall accommodate all the SUFIs to form the complete status report. Indication of the same
AMD PDU shall not be given in more than one STATUS PDU of a status report, but the ACK SUFI can be
present in more than one STATUS PDU of a status report;

-

if any STATUS PDU constructed is not entirely filled with SUFIs:

-

if the STATUS PDU is not terminated with an ACK SUFI:

-

terminate that STATUS PDU with a NO_MORE SUFI.

-  use padding in the remainder of that STATUS PDU (padding size may be zero).

Which SUFI fields to use is implementation dependent. Bitmap SUFI is used to indicate both received and/or missing
AMD PDUs. List SUFI and/or Relative List SUFI are used to indicate missing AMD PDUs only. Acknowledgement
SUFI is used to indicate the received AMD PDUs. (For SUFI details see 9.2.2.11.)

11.5.2.3

Submission of STATUS PDUs to the lower layer

The Receiver shall:

-

-

inform the lower layer of the STATUS PDUs scheduled for transmission;

submit to the lower layer, the requested number of PDUs (STATUS PDUs, piggybacked AMD/STATUS PDUs
and optionally AMD PDUs, see also subclause 11.3.2.2);

-

if "Timer based STATUS transfer" is configured and the timer Timer_Status_Periodic has expired:

-

restart the timer Timer_Status_Periodic according to subclause 9.5 f);

-

if the STATUS PDU includes the MRW SUFI:

3GPP

Release 13

81

3GPP TS 25.322 V13.0.0 (2015-12)

-

start the timer Timer_MRW according to subclause 9.5 i).

11.5.3  Reception of the STATUS PDU by the Sender

Upon reception of the STATUS PDU/piggybacked STATUS PDU, the Sender shall:

-

if an RLC SDU is positively acknowledged by the STATUS PDU:

-

if requested:

-

inform the upper layers of the reception of the RLC SDU by the peer AM RLC entity.

-  update the state variables VT(A) and VT(MS) according to the received STATUS PDU/piggybacked STATUS

PDU;

-

if the STATUS PDU includes negatively acknowledged AMD PDUs:

-

-

initiate the acknowledged data transfer procedure; and

retransmit these AMD PDUs. Retransmitted AMD PDUs shall have higher priority than AMD PDUs to be
transmitted for the first time;

-

if an AMD PDU is negatively acknowledged more than once in a STATUS PDU:

-

retransmit the AMD PDU only once.

-

if the STATUS PDU includes the MRW SUFI:

-

take the actions specified in subclause 11.6.3.

-

if the STATUS PDU includes the MRW_ACK SUFI:

-

take the actions specified in subclause 11.6.4.

-

if the STATUS PDU includes the WINDOW SUFI:

-  update the current transmission window size, VT(WS).

11.5.4  Abnormal cases

11.5.4.1

Void

11.6  SDU discard with explicit signalling procedure

11.6.1  General

The SDU discard with explicit signalling procedure is used for discarding SDUs and transferring the discard
information between two peer entities, which are operating in acknowledged mode. The Sender shall discard an SDU
that has not been successfully transmitted for a period of time or for a number of transmissions, and send a Move
Receiving Window (MRW) SUFI to the Receiver. According to the MRW SUFI, the Receiver shall discard AMD
PDUs carrying that SDU and update the reception window. Figure 11.6 below illustrates the elementary procedure for
SDU discard with explicit signalling.

Sender

Receiver

STATUS PDU (MRW SUFI)

STATUS PDU (MRW_ACK SUFI)

Figure 11.6: SDU discard with explicit signalling

3GPP

Release 13

82

3GPP TS 25.322 V13.0.0 (2015-12)

11.6.2

Initiation

The Sender shall initiate the SDU discard with explicit signalling procedure if one of the following triggers is detected:

-

-

-

"Timer based SDU discard with explicit signalling" is configured, Timer_Discard expires for an SDU, and one
or more segments of the SDU have been submitted to lower layer;

"Timer based SDU discard with explicit signalling" is configured, Timer_Discard expires for an SDU, and "Send
MRW" is configured;

"SDU discard after MaxDAT number of transmissions" is configured, and MaxDAT number of transmissions is
reached (i.e. VT(DAT) ≥ MaxDAT) for an AMD PDU.

Upon initiation of the SDU discard with explicit signalling procedure, the Sender shall:

-

if "Timer based SDU discard with explicit signalling" is configured:

-  discard all SDUs up to and including the SDU for which the timer Timer_Discard expired.

-

if "SDU discard after MaxDAT number of transmissions" is configured:

-  discard all SDUs that have segments or "Length Indicators" indicating the end of the SDUs in AMD PDUs
with "Sequence Number" SN inside the interval VT(A) ≤ SN ≤ X, where X is the value of the "Sequence
Number" of the AMD PDU with VT(DAT) ≥ MaxDAT.

-

if requested:

-

inform the upper layers of the discarded SDUs

-  discard all AMD PDUs including segments of the discarded SDUs or "Length Indicators" indicating the end of

the SDUs, unless they also carry a segment of a SDU which is not discarded;

-

if more than 15 discarded SDUs are to be informed to the Receiver (see subclause 11.6.2.2):

-

if "Send MRW" is not configured:

-  assemble an MRW SUFI with the discard information of the SDUs.

-  otherwise ("Send MRW" is configured):

-  assemble an MRW SUFI with the discard information of the first 15 SDUs; and

-

include the discard information of the rest SDUs in another MRW SUFI which shall be sent by the next
SDU discard with explicit signalling procedure (after the current SDU discard with explicit signalling
procedure is terminated).

-  otherwise (less than or equal to 15 discarded SDUs are to be informed to the Receiver):

-  assemble an MRW SUFI with the discard information of the SDUs.

-

-

schedule and submit to lower layer a STATUS PDU/piggybacked STATUS PDU containing the MRW SUFI;

if SN_MRWLENGTH in the MRW SUFI >VT(S):

-  update VT(S) to SN_MRWLENGTH.

-

start a timer Timer_MRW according to subclause 9.5.

If a new SDU discard with explicit signalling procedure is triggered when the current SDU discard with explicit
signalling procedure is still going on, no new MRW SUFIs shall be sent before the current SDU discard with explicit
signalling procedure is terminated by one of the termination criteria specified in subclause 11.6.4.

11.6.2.1

Void

3GPP

Release 13

83

3GPP TS 25.322 V13.0.0 (2015-12)

11.6.2.2

STATUS PDU contents to set

The Sender shall:

-

if "Send MRW" is configured:

-

if no new SDU is present inside the AMD PDU which contains the "Length Indicator" of the last discarded
SDU or if the AMD PDU contains the special value of the HE field to indicate the end of the last discarded
SDU:

-

set the last SN_MRWi field in the MRW SUFI to 1 + "Sequence Number" of the AMD PDU which
contains the "Length Indicator" of the last discarded SDU or the special value of the HE field to indicate
the end of the last discarded SDU;

-

set the NLENGTH field in the MRW SUFI to "0000".

-  otherwise:

-

-

set the last SN_MRWi field in the MRW SUFI to the "Sequence Number" of the AMD PDU which
contains the "Length Indicator" of the last discarded SDU;

set the NLENGTH field in the MRW SUFI so that the last data octet to be discarded in the Receiver shall be
the octet indicated by the NLENGTH:th "Length Indicator" field of the AMD PDU which contains the
"Length Indicator" of the last discarded SDU;

-

set each of the other SN_MRWi fields in the MRW SUFI to the "Sequence Number" of the AMD PDU which
contains the "Length Indicator" of the i:th discarded SDU or the special value of the HE field to indicate the
end of the i:th discarded SDU.

-  otherwise ("Send MRW" is not configured):

-

if no new SDU is present inside the AMD PDU which contains the "Length Indicator" of the last discarded
SDU or if the AMD PDU contains the special value of the HE field to indicate the end of the last discarded
SDU:

-

set the last SN_MRWi field in the MRW SUFI to 1 + "Sequence Number" of the AMD PDU which
contains the "Length Indicator" of the last SDU to be discarded in the Receiver or the special value of the
HE field to indicate the end of the last discarded SDU;

-

set the NLENGTH field in the MRW SUFI to "0000".

-  otherwise:

-

-

set the last SN_MRWi field in the MRW SUFI to the "Sequence Number" of the AMD PDU which
contains the "Length Indicator" of the last SDU to be discarded in the Receiver;

set the NLENGTH field in the MRW SUFI so that the last data octet to be discarded in the Receiver shall be
the octet indicated by the NLENGTH:th "Length Indicator" field of the AMD PDU which contains the
"Length Indicator" of the last SDU to be discarded in the Receiver;

-  optionally set each of the other SN_MRWi fields in the MRW SUFI to the "Sequence Number" of the AMD
PDU which contains the "Length Indicator" or the special value of the HE field to indicate the end of the i:th
SDU to be discarded in the Receiver;

-

if the MRW SUFI contains only one SN_MRWi field and the value of SN_MRWi field ≥
VT(A)+Configured_Tx_Window_Size:

-

set the LENGTH field in the MRW SUFI to "0000".

-  otherwise:

-

set the LENGTH field in the MRW SUFI to the number of SN_MRWi fields in the same MRW SUFI. In this
case, SN_MRW1 shall be in the interval VT(A) ≤ SN_MRW1 < VT(A)+Configured_Tx_Window_Size.

3GPP

Release 13

84

3GPP TS 25.322 V13.0.0 (2015-12)

11.6.3  Reception of the STATUS PDU by the Receiver

Upon reception of the STATUS PDU/piggybacked STATUS PDU containing an MRW SUFI, the Receiver shall:

-

if the LENGTH field in the received MRW SUFI is "0000":

-  consider SN_MRW1 to be above or equal to VR(R).

-  otherwise:

-  consider SN_MRW1 to be less than VR(MR);

-  consider all the SN_MRWis other than SN_MRW1 to be in sequential order within the list and sequentially

above or equal to SN_MRWi-1;

-  deliver all the successfully received SDUs from the SDU that have segments or "Length Indicators" indicating
the end of the SDUs in AMD PDU with "Sequence Number" of VR(R) up to and including the last SDU that is
indicated by the MRW SUFI;

-  discard AMD PDUs up to and including the PDU with sequence number SN_MRWLENGTH–1;

-

if the NLENGTH field in the received MRW SUFI is "0000":

-

reassemble from the first data octet of the AMD PDU with sequence number SN_MRWLENGTH after the
discard.

-  otherwise:

-  discard further the data octets in the AMD PDU with sequence number SN_MRWLENGTH up to and including

the octet indicated by the NLENGTH:th "Length Indicator" field of the PDU with sequence number
SN_MRWLENGTH;

-

reassemble from the succeeding data octet in the AMD PDU with sequence number SN_MRWLENGTH after
the discard;

-

if "Send MRW" is configured:

-

inform upper layers about all of the discarded SDUs that were not previously delivered to upper layer or
discarded by other MRW SUFIs;

-  update the state variables VR(R), VR(H) and VR(MR) according to the received STATUS PDU/piggybacked

STATUS PDU;

-  assemble a MRW_ACK SUFI according to subclause 11.6.3.1;

-

schedule and submit to lower layer a STATUS PDU/piggybacked STATUS PDU containing the MRW_ACK
SUFI.

11.6.3.1

STATUS PDU contents to set

The Receiver shall:

-

-

set the SN_ACK field in the MRW_ACK SUFI to the new value of VR(R), updated after reception of the MRW
SUFI;

if the SN_ACK field in the MRW_ACK SUFI is set equal to the SN_MRWLENGTH field in the received MRW
SUFI:

-

set the N field in the MRW_ACK SUFI to the NLENGTH field in the received MRW SUFI.

-  otherwise:

-

set the N field in the MRW_ACK SUFI to "0000".

-

include the MRW_ACK SUFI in the next STATUS PDU/piggybacked STATUS PDU to be transmitted,
according to subclause 11.5.2.

3GPP

Release 13

85

3GPP TS 25.322 V13.0.0 (2015-12)

11.6.4  Termination

The Sender shall terminate the SDU discard with explicit signalling procedure if one of the following criteria is
fulfilled:

-  a STATUS PDU/piggybacked STATUS PDU containing an MRW_ACK SUFI is received, and the SN_ACK
field in the received MRW_ACK SUFI > the SN_MRWLENGTH field in the transmitted MRW_SUFI, and the N
field in the received MRW_ACK SUFI is set equal to "0000";

-  a STATUS PDU/piggybacked STATUS PDU containing an MRW_ACK SUFI is received, and the SN_ACK
field in the received MRW_ACK SUFI = the SN_MRWLENGTH field in the transmitted MRW_SUFI, and the N
field in the received MRW_ACK SUFI is set equal to the NLENGTH field in the transmitted MRW SUFI;

-  a STATUS PDU/piggybacked STATUS PDU containing an ACK SUFI is received, and this STATUS

PDU/piggybacked STATUS PDU indicates that all AMD PDUs up to and including the AMD PDU with
"Sequence Number" equal to (SN_MRWLENGTH field in the transmitted MRW SUFI) – 1 has been received or
discarded by the peer entity.

Upon termination of the SDU discard with explicit signalling procedure, the Sender shall:

-

stop the timer Timer_MRW;

-  update VT(A) and VT(MS) according to the received STATUS PDU/piggybacked STATUS PDU;

The Sender shall not confirm to upper layers the SDUs that are requested to be discarded.

11.6.4a  Reached maximum number of attempts

If VT(MRW) = MaxMRW, the Sender shall:

-

-

-

terminate the SDU discard with explicit signalling procedure;

stop the timer Timer_MRW if it was started;

initiate the RLC RESET procedure (see subclause 11.4).

11.6.5  Expiration of timer Timer_MRW

If Timer_MRW expires before the discard procedure is terminated, the Sender shall:

-

-

increment VT(MRW) by one;

if VT(MRW)<MaxMRW:

-

-

-

-

set the MRW SUFI as previously transmitted (even if additional SDUs were discarded in the mean-time);

include the MRW SUFI in a new status report (if other SUFIs are included, their contents shall be updated);

transmit the status report by either including it in a STATUS PDU or piggybacked in an AMD PDU;

restart Timer_MRW for this discard procedure according to the description in subclause 9.5.

-  else (if VT(MRW) = MaxMRW):

-  perform the actions specified in subclause 11.6.4a.

11.6.6  Abnormal cases

11.6.6.1

Reception of obsolete/corrupted MRW SUFI by the Receiver

If the received MRW SUFI contains outdated information about the reception window (reception window already
moved further than MRW SUFI is indicating), the Receiver shall:

-  discard the MRW SUFI;

-

set the SN_ACK field in the MRW_ACK SUFI to the current value of VR(R);

3GPP

Release 13

86

3GPP TS 25.322 V13.0.0 (2015-12)

-

-

set the N field in the MRW_ACK SUFI to "0000";

include the MRW_ACK SUFI in the next STATUS PDU/piggybacked STATUS PDU to be transmitted,
according to subclause 11.5.2.

11.6.6.2

Void

11.6.6.3

Reception of obsolete/corrupted MRW_ACK SUFI by the Sender

The Sender shall discard the received MRW_ACK SUFI if one of the following cases occurs:

-  no ongoing SDU discard with explicit signalling procedure; or

-

-

-

the SN_ACK field in the received MRW_ACK SUFI < the SN_MRWLENGTH field in the transmitted MRW
SUFI; or

the SN_ACK field in the received MRW_ACK SUFI = the SN_MRWLENGTH field in the transmitted MRW
SUFI, and the N field in the received MRW_ACK SUFI is not equal to the NLENGTH field in the transmitted
MRW SUFI; or

the SN_ACK field in the received MRW_ACK SUFI > the SN_MRWLENGTH field in the transmitted MRW
SUFI, and the N field in the received MRW_ACK SUFI is not equal to "0000".

11.7  Void

11.8  Void

3GPP

Release 13

87

3GPP TS 25.322 V13.0.0 (2015-12)

Annex A (informative):
Change history

Change history

Date
TSG #
10/1999  RP-05
12/1999  RP-06
RP-06
RP-06
RP-06
RP-06
RP-06
RP-06
RP-06
RP-06
RP-06
RP-06
RP-06
RP-06
-
-

01/2000

03/2000  RP-07
RP-07
RP-07
RP-07
RP-07
RP-07
RP-07
RP-07

RP-07
RP-07
RP-07
RP-07
06/2000  RP-08
RP-08
RP-08
RP-08
RP-08
RP-08
RP-08
RP-08
RP-08
RP-08
RP-08
RP-08
09/2000  RP-09
RP-09
RP-09
RP-09
RP-09
RP-09
RP-09
RP-09
RP-09
RP-09
RP-09
RP-09
RP-09
12/2000  RP-10
RP-10
RP-10
RP-10
RP-10
RP-10
RP-10
RP-10
RP-10

Approved at TSG-RAN #5 and placed under Change Control
RLC: Editorial corrections
Editorial changes on RLC protocol specification
MRW procedure
SDU Discard Functionality
Change in RLC control PDU format
Editorial corrections regarding CTCH
Updated RLC SDL
RLC Editorial Changes
Editorial Modification on RLC specification
Editorial changes
Change to one PU in a AMD PDU
Introduction of RLC suspend state
RLC editorial corrections
Editorial corrections in title and Annex A (SDL)
Correction of persistent error regarding SDL in Table of Contents
RLC editorial changes
Corrections to RLC
Corrections to RLC
STATUS PDUs
Clarification of RLC AMD Model
Corrections to Timer_discard procedures
Segmentation of RLC SDUs
Modification of SDU discard to support virtual PDCP sequence
numbers
Removal of SCCH
Updated RLC SDL
RLC Editorial Changes
Order of bit transmission for RLC PDUs
Corrections to RLC
Correction to the description of the MRW SUFI fields
Editorial corrections to length indicators and local suspend rate
Clarification of the RESET PDU
Clarification of RLC/MAC interaction
General RLC corrections
Clarification of RLC Transparent Mode operation
Editorial corrections to abbreviations, SCCH, BCCH
Updated RLC SDL
Correction to RLC
RLC Logical Channel mapping
Correction of EPC timer mechanism
State variables after window change
SDU discard
General RLC corrections
Editorial changes to RLC
Correction to RLC window size range

-

TSG Doc.  CR  Rev  Subject/Comment
RP-99465
RP-99641  001
RP-99641  002  1
RP-99643  003  1
RP-99643  004
RP-99643  005  2
RP-99642  006  1
RP-99641  007
RP-99642  011
RP-99642  013
RP-99641  014
RP-99642  015
RP-99643  016  1
RP-99641  017  1
-
-
RP-000040  018  1
RP-000040  021  1
RP-000040  025  2
RP-000040  026  1
RP-000040  027  1
RP-000040  028
RP-000040  029  1
RP-000040  030  2

-
-

RP-000040  031
RP-000040  032
RP-000040  033  1
RP-000040  034
RP-000220  038
RP-000220  039
RP-000220  040  1
RP-000220  041  4
RP-000220  043  1
RP-000220  044  2
RP-000220  045
RP-000220  048
RP-000220  052
RP-000220  053
RP-000220  055
RP-000220  057
RP-000358  059  1
RP-000358  060  4
RP-000358  061  5
RP-000358  066
RP-000358  067  4
RP-000358  068  2  Window based polling
RP-000358  070  2
RP-000358  071
RP-000358  073
RP-000358  076  1
RP-000358  077  1
RP-000358  078
RP-000358  079
RP-000568  080  1
RP-000568  083  3
RP-000568  084  2
RP-000568  085  1
RP-000568  086  1
RP-000568  087  5
RP-000568  088  1
RP-000568  089  1
RP-000568  090  2

General corrections to RLC
State Transition in RLC Acknowledged Mode
Clarification of the Length Indicators
RLC corrections
Corrections to reset procedure and length indicator definitions
RLC Modes for SHCCH
CCCH in UM RLC
Length Indicator and PDU formats
Clarification to the Estimated PDU Counter
Model of UM and AM entities
General RLC corrections
General RLC corrections
RLC timers
Reset procedure
Editorial corrections to RLC
RLC UM protocol

New
Old
-
3.0.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.0.0  3.1.0
3.1.0  3.1.1
3.1.1  3.1.2
3.1.2  3.2.0
3.1.2  3.2.0
3.1.2  3.2.0
3.1.2  3.2.0
3.1.2  3.2.0
3.1.2  3.2.0
3.1.2  3.2.0
3.1.2  3.2.0

3.1.2  3.2.0
3.1.2  3.2.0
3.1.2  3.2.0
3.1.2  3.2.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.2.0  3.3.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.3.0  3.4.0
3.4.0  3.5.0
3.4.0  3.5.0
3.4.0  3.5.0
3.4.0  3.5.0
3.4.0  3.5.0
3.4.0  3.5.0
3.4.0  3.5.0
3.4.0  3.5.0
3.4.0  3.5.0

3GPP

Release 13

88

3GPP TS 25.322 V13.0.0 (2015-12)

Change history

TSG Doc.  CR  Rev  Subject/Comment
RP-000568  092  2

Date

TSG #
RP-10

RP-10
RP-10
RP-10
03/2001  RP-11
RP-11

RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
RP-11
06/2001  RP-12
RP-12
RP-12
RP-12
RP-12
RP-12
RP-12
RP-12
RP-12
RP-12
09/2001  RP-13
RP-13
12/2001  RP-14
RP-14
RP-14
RP-14
RP-14
RP-14
RP-14
RP-14
03/2002  RP-15

RP-15
RP-15
RP-15
06/2002  RP-16
RP-16
RP-16
RP-16
09/2002  RP-17

RP-000568  093  3
RP-000568  094  1
RP-000568  095
RP-010026  097  1
RP-010026  098  1

-

RP-010026  099  1
RP-010026  100  1
RP-010026  101
RP-010026  103
RP-010026  104  1
RP-010026  105  2
RP-010026  106  1
RP-010026  107  1
RP-010026  109  2
RP-010026  110  1
RP-010026  111
RP-010026  112  1
RP-010026  113  1
RP-010026  114  1
RP-010026  116
RP-010026  118  2
-
RP-010309  120
RP-010309  122
RP-010309  124
RP-010309  126
RP-010309  128
RP-010309  130
RP-010309  132
RP-010309  136
RP-010309  138
RP-010309  140
RP-010542  142
RP-010542  150
RP-010761  152
RP-010761  156
RP-010761  158
RP-010761  162
RP-010761  164
RP-010771  160
RP-010771  166
RP-010771  170
RP-020068  172

-

RP-020068  176
RP-020068  180
-
RP-020327  186
RP-020327  189
RP-020327  192  1
RP-020327  195
RP-020539  198

RP-17
RP-17
RP-17

RP-020539  201
RP-020637  204  1
RP-020539  207

RP-17
12/2002  RP-18
RP-18
03/2003  RP-19
RP-19
06/2003  RP-20
RP-20
RP-20
RP-20

RP-020551  209
RP-020719  212
RP-020862  213
RP-030101  216
RP-030116  217
RP-030292  220  2
RP-030292  225
RP-030297  222
RP-030297  227

Clarification to window size parameters, MRW SUFI and window
based polling
General RLC Corrections
RLC Reset handling
Inclusion of stage 3 for ciphering
Clarification on LIST SUFI and RLIST SUFI
Corrections and clarifications for SDU discard without explicit
signalling
Tr mode operation
Timer based discard with explicit signalling
Annex updates
Clarification on MRW SUFI and SDU discard procedure
General clarification on SN arithmetic comparison
General clarification on RLC header and PDU header
Clarification on the primitives between RLC and higher layers
Clarification on the model of AM entity
Clarification on UMD transfer procedure
RLC status transmission in CELL_PCH and URA_PCH
Re-establishment description
Clarifications on the RESET and RESET ACK PDU sizes
Editorial corrections and clarifications
Clarifications on the RLC-AM-DATA-Conf primitive
Removal of the payload unit concept
Padding Blocks and TFC selection pre-empting
Upgrade to Release 4 - no technical change
Clarification on ACK SUFI
MRW SUFI clarification and enhancement
Clarification on AM states
Clarification on HFN update in RESET procedure
Clarification of RLC Discard
Removal of reference to RRC
Clarification in the LI Parameters section
Cleanup of RLC services and functions
Clarification on RLC re-establishment
Corrections and clarifications to the LIST and RLIST SUFI types
General clarifications
Correction to RLC state variables
General clarifications
Send state variable for Timer_Poll and window based polling
Unexpected data interruption during transmission scheduling
UE-ID Type Indicator
Removal of obsolete Send MRW option
Content of retransmitted RESET ACK PDU
Usage of UM RLC Special Length Indicator
Indication of SDU transmission result
Clarification on MRW SUFI and SDU discard with explicit signalling
procedure
SDU discard termination
Initial value of VT(US)
Upgrade to Release 5 - no technical change
Handling abnormal UMD PDUs and AMD PDUs
Clarification of the use of Length Indicators
Correction to MaxDAT, MaxRST and MaxMRW
Clarification on polling functions
Correction to the behaviour after expiration of Timer_MRW during the
SDU discard with explicit signalling procedure
Corrections to RLC retransmissions
Corrections to RLC RESET procedure and Length Indicators
Corrections on handling of timers during a RLC reset or re-
establishment
Corrections on indication of SDU transmission result
RB id in ciphering
Generation of RLC Status Reports to coordinate with MAC-hs reset
Correction to VT(MRW) definition
Enhancement of MRW procedure
Handling of erroneous PDUs
Setting of the “Polling bit” in the “Every Poll_SDU SDU” function
Receiver behaviour when detecting an AMD PDU duplicate
RLC window size reconfigurations

Old
New
3.4.0  3.5.0

3.4.0  3.5.0
3.4.0  3.5.0
3.4.0  3.5.0
3.5.0  3.6.0
3.5.0  3.6.0

3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.5.0  3.6.0
3.6.0  4.0.0
4.0.0  4.1.0
4.0.0  4.1.0
4.0.0  4.1.0
4.0.0  4.1.0
4.0.0  4.1.0
4.0.0  4.1.0
4.0.0  4.1.0
4.0.0  4.1.0
4.0.0  4.1.0
4.0.0  4.1.0
4.1.0  4.2.0
4.1.0  4.2.0
4.2.0  4.3.0
4.2.0  4.3.0
4.2.0  4.3.0
4.2.0  4.3.0
4.2.0  4.3.0
4.2.0  4.3.0
4.2.0  4.3.0
4.2.0  4.3.0
4.3.0  4.4.0

4.3.0  4.4.0
4.3.0  4.4.0
4.4.0  5.0.0
5.0.0  5.1.0
5.0.0  5.1.0
5.0.0  5.1.0
5.0.0  5.1.0
5.1.0  5.2.0

5.1.0  5.2.0
5.1.0  5.2.0
5.1.0  5.2.0

5.1.0  5.2.0
5.2.0  5.3.0
5.2.0  5.3.0
5.3.0  5.4.0
5.3.0  5.4.0
5.4.0  5.5.0
5.4.0  5.5.0
5.4.0  5.5.0
5.4.0  5.5.0

3GPP

Release 13

89

3GPP TS 25.322 V13.0.0 (2015-12)

Change history

TSG Doc.  CR  Rev  Subject/Comment
RP-030483  230
RP-030483  233  1
RP-030483  236  1
RP-030483  239
RP-030478  242
RP-030483  245
RP-030490  247
RP-030616  250
RP-030620  252
-
RP-040224  258
RP-040504  262  1
RP-040504  264  1
RP-040490  265  1
RP-040490  266

-

Date
TSG #
09/2003  RP-21
RP-21
RP-21
RP-21
RP-21
RP-21
RP-21
12-2003  RP-22
RP-22
RP-22
06-2004  RP-24
12-2004  RP-26
RP-26
RP-26
RP-26

03-2005  RP-27
RP-27
RP-27
RP-27
RP-27
RP-27
06-2005  RP-28

RP-050113  260  1
RP-050113  265
RP-050113  267
RP-050113  268
RP-050068  270
RP-050082  271
RP-050319  0272

RP-28
RP-28

RP-050315  0273
RP-050319  0274

RP-28
RP-28
RP-28
RP-28
RP-28
RP-28
RP-28

RP-050302  0276
RP-050319  0277
RP-050319  0278
RP-050315  0279  1
RP-050317  0280
RP-050315  0281
RP-050315  0282

09-2005  RP-29
RP-29
RP-29

RP-050463  0284
RP-050481  0285
RP-050468  0286

RP-29
RP-29

RP-050468  0287
RP-050468  0288

12-2005  RP-30
RP-30
RP-30

RP-050784  0290
RP-050788  0293
RP-050788  0294

RP-30
RP-30
03-2006  RP-31
RP-31
RP-31

RP-050797  0296
RP-050802  0297  1
RP-060090  0292  2
RP-060090  0298
RP-060094  0299

RP-31
06/2006  RP-32
RP-32
09/2006  RP-33
06/2007  RP-36

RP-36
RP-36
RP-36
RP-36
RP-36
09/2007  RP-37
RP-37
12/2007  RP-38

RP-38
03/2008  RP-39
RP-39

-

-
RP-060363  0301  1
RP-060363  0303
RP-060575  0305

RP-070407  0306  1
RP-070407  0307  -
RP-070407  0308  -
RP-070404  0309  2
RP-070416  0311  -
RP-070407  0312  -
RP-070626  0313
RP-070626  0314
RP-070905

0315
RP-070910  0316
RP-080178  0319  -
RP-080191  0321  -

Old

6.3.0  6.4.0
6.3.0  6.4.0

6.2.0  6.3.0
6.2.0  6.3.0
6.2.0  6.3.0
6.2.0  6.3.0
6.2.0  6.3.0
6.2.0  6.3.0
6.3.0  6.4.0

New
SDU Concatenation Exceptions and SDU Concatenation in AM Mode  5.5.0  5.6.0
5.5.0  5.6.0
Decision of Discarded SDUs from Discarded PDUs
5.5.0  5.6.0
RLC Reset Triggering and Update of VT(RST)
5.5.0  5.6.0
correction to the ‘SDU discard with explicit signalling’ procedure
5.5.0  5.6.0
Elimination of EPC mechanism
5.5.0  5.6.0
Correction of MRW and RESET timers in RLC
5.5.0  5.6.0
Reconfiguration of RLC window size
5.6.0  5.7.0
BITMAP and status report content
5.6.0  5.7.0
Indication of discarded SDU in RLC Reset and Re-establishment
5.7.0  6.0.0
Upgrade to Release 6 - no technical change
6.0.0  6.1.0
DL RLC Size handling
6.1.0  6.2.0
Correction of MRW SUFI content setting rule
6.1.0  6.2.0
Correction of Poll Prohibit function
6.1.0  6.2.0
Inclusion of out of sequence SDU delivery
6.1.0  6.2.0
Addition of MBMS Logical Channels and UM functionality for ‘duplicate
avoidance and reordering’
Correction of MRW termination on reception of ACK SUFI
Correction to RLC Re-establishment
CRCLC-Config-Req in LOCAL_SUSPEND State
Protocol error detection and recovery
Removal of the EPC mechanism
Inclusion of transmitter constraints
Correction on actions taken Upon reception of an duplicated AMD
PDU within the reception window
Clarification on a Transmitter Constraint
Reconfiguration of RLC parameters by upper layers may lead to Logic
inconsistency of state variable VrH
Erroneous Sequence Number definition
Selecting a PDU to transmit a poll
Support for out-of-sequence PDUs in RLC-UM
Clarification of the "Out of sequence SDU delivery"
RLC LI Optimization for VoIP
Correction to Out Of Sequence Delivery
Clarification on operations when UE MCCH RLC entity is re-
established and OSD_Window_Size is reconfigured
Single Sided RLC Re-establishment
Removal RLC-SDU alignment capability
Arithmetic comparison for DAR function and VR(US) after MBMS
being included
Clarification on DAR window reconfiguration
Clarification on reception of UMD PDU when OSD function is
configured
Correction on transmission of AMD PDU
Initiation of state variable VR(UOH)
Clarification on reception of UMD PDU when OSD function is
configured
Corrections to RLC re-establishment
RLC UMD header optimisation for RT services over HSDPA/HSUPA
Correction to RLC Re-establishment Procedure
Correction to RLC reset procedure
Introducing missing "and" to the RLC UMD operation with LI
optimisation
Upgrade to the Release 7 - no technical change
Clarification on abortion of RLC Reset procedure
RLC SDU Discard during re-establishment
AMD PDU discard
Removing an incomplete optimization for RLC operations during
HSDPA cell change
7.2.0  7.3.0
Correction to Out of Sequence Reception function
7.2.0  7.3.0
DAR over CCCH
7.2.0  7.3.0
Introduction of Improved L2 support for high data rates
Corrections on modulus base in UM in RLC
7.2.0  7.3.0
Using special value of HE field to indicate end of an SDU for RLC AM  7.2.0  7.3.0
7.3.0  7.4.0
Correction on POLL SUFI
7.3.0  7.4.0
Special HE value setting
7.4.0  7.5.0
Correction to Control Information transmission with two logical
channels
Introduction of CS Voice over HSPA
Correction to Reception of UM RLC
Correction to Control Information transmission

6.3.0  6.4.0
6.3.0  6.4.0
6.3.0  6.4.0
6.3.0  6.4.0
6.3.0  6.4.0
6.3.0  6.4.0
6.3.0  6.4.0

6.5.0  6.6.0
6.5.0  6.6.0
6.6.0  6.7.0
6.6.0  6.7.0
6.6.0  6.7.0

6.7.0  7.0.0
7.0.0  7.1.0
7.0.0  7.1.0
7.1.0  7.2.0
7.2.0  7.3.0

6.4.0  6.5.0
6.4.0  6.5.0
6.4.0  6.5.0

7.4.0  8.0.0
8.0.0  8.1.0
8.0.0  8.1.0

6.5.0  6.6.0
6.5.0  6.6.0
6.5.0  6.6.0

6.4.0  6.5.0
6.4.0  6.5.0

3GPP

Release 13

90

3GPP TS 25.322 V13.0.0 (2015-12)

Change history

Old
New
8.0.0  8.1.0
8.0.0  8.1.0
8.0.0  8.1.0

8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.1.0  8.2.0
8.2.0  8.3.0
8.3.0  8.4.0
8.3.0  8.4.0

8.3.0  8.4.0
8.3.0  8.4.0
8.3.0  8.4.0
8.4.0  8.5.0
8.4.0  8.5.0
8.5.0  8.6.0
8.5.0  8.6.0

8.6.0  8.7.0
8.6.0  9.0.0

9.0.0  9.1.0
9.1.0  9.2.0
9.2.0  10.0.0
10.0.0  10.1.0
10.1.0  11.0.0
11.0.0  11.1.0
11.1.0  11.2.0
11.2.0  12.0.0
12.0.0  13.0.0

TSG Doc.  CR  Rev  Subject/Comment
RP-080191  0323  -
RP-080202  0324  -
RP-080190  0326  -

Date

TSG #
RP-39
RP-39
RP-39

06/2008  RP-40
RP-40
RP-40
RP-40
RP-40
RP-40
RP-40
RP-40
RP-40
09/2008  RP-41
03/2009  RP-43
RP-43

RP-43
RP-43
RP-43
06/2009  RP-44
RP-44
09/2009  RP-45
RP-45

RP-080403  0328  1
RP-080391  0330  1
RP-080405  0331  -
RP-080395  0333  3
RP-080414  0334  -
RP-080414  0335  1
RP-080390  0338  -
RP-080395  0343  -
RP-080414  0344  1
RP-080685  0349
RP-090117  0353  -
RP-090140  0354  -

RP-090138  0356  1
RP-090138  0357  -
RP-090151  0358  -
RP-090519  0359  -
RP-090505  0364  -
RP-090917  0366  -
RP-090909  0368  -

12/2009  RP-46
RP-46

RP-091329  0369  -
RP-091336  0373  -

Poll SUFI and Status Reporting
Introducing flexible RLC PDU size in the uplink
Correction to the RLC RESET and RESET ACK PDU with flexible RLC
PDU size
Correction on UM model depiction
Clarification on DAR Operation
CS-HSPA UL Segmentation
Removal of UTRAN behaviour
Correction to transmitting AM RLC entity
Removal of Redundant Description in Transmitting Side
Non-applicability of ciphering for MCCH, MSCH and MTCH
Maximum RLC PDU size
RLC PDU size adaptation
Correction to definition of N_LENGTH
Correction for VR(UM)
Concatenation/segmentation in case SN_Delivery parameter is
configured
Clarification for the description of transmitting UM RLC entity
Correction to RLC text for MAC i/is
Removal of DCCH logical channel mapped on RLC TM entity
Submission of UMD PDU when SN_Delivery is configured
Removal of references to MAC-hs reset
Clarification on minimum PDU size
Clarification to LI setting after Timer_Discard expiry when alternative
e-bit is used
Introduction of POLL_SUFI in UL data transfer
Partial radio awareness for DC-HSUPA capable UEs

03/2010  RP-47
06/2010  RP-48
12/2010  RP-50
06/2011  RP-52
09/2012  RP-57
12/2012  RP-58
03/2013  RP-59
09/2014  RP-65
12/2015  RP-70

RP-100286  0375  -
RP-100537  0379  2
RP-101365  0388  -
RP-110771  0391  2
RP-121369  0403  -
RP-121943  0404  -
RP-130239  0405  -
-
-
-
-

-
-

RLC recovery with uplink POLL_SUFI(R9)
Correction of Poll SUFI handling for Improved L2 Uplink
Introduction of LCR TDD MC-HSUPA in 25.322
Accept RLC PDUs with special value HE field if it’s supported
Introduction of Multiflow in TS 25.322
Introduction of further Multiflow agreements in TS 25.322
Clarification on RLC Status Report prohibit functions
Upgrade to the Release 12 - no technical change
Upgrade to the Release 13 - no technical change

3GPP


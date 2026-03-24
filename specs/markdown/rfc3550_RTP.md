Network Working Group
Request for Comments: 3550
Obsoletes: 1889
Category: Standards Track

H. Schulzrinne
Columbia University
S. Casner
Packet Design
R. Frederick
Blue Coat Systems Inc.
V. Jacobson
Packet Design
July 2003

RTP: A Transport Protocol for Real-Time Applications

Status of this Memo

This document speci(cid:12)es an Internet standards track protocol for the Internet community, and
requests discussion and suggestions for improvements. Please refer to the current edition of the
\Internet O(cid:14)cial Protocol Standards" (STD 1) for the standardization state and status of this
protocol. Distribution of this memo is unlimited.

Copyright Notice

Copyright (C) The Internet Society (2003). All Rights Reserved.

Abstract

This memorandum describes RTP, the real-time transport protocol. RTP provides end-to-end
network transport functions suitable for applications transmitting real-time data, such as audio,
video or simulation data, over multicast or unicast network services. RTP does not address resource
reservation and does not guarantee quality-of-service for real-time services. The data transport is
augmented by a control protocol (RTCP) to allow monitoring of the data delivery in a manner
scalable to large multicast networks, and to provide minimal control and identi(cid:12)cation functionality.
RTP and RTCP are designed to be independent of the underlying transport and network layers.
The protocol supports the use of RTP-level translators and mixers.

Most of the text in this memorandum is identical to RFC 1889 which it obsoletes. There are no
changes in the packet formats on the wire, only changes to the rules and algorithms governing how
the protocol is used. The biggest change is an enhancement to the scalable timer algorithm for
calculating when to send RTCP packets in order to minimize transmission in excess of the intended
rate when many participants join a session simultaneously.

Schulzrinne, et al.

Standards Track

[Page 1]

RFC 3550

RTP

July 2003

Table of Contents

1.

Introduction

1.1 Terminology . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

2. RTP Use Scenarios

2.1 Simple Multicast Audio Conference . . . . . . . . . . . . . . . . . . . . . . . . . . .

2.2 Audio and Video Conference . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

2.3 Mixers and Translators . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

2.4 Layered Encodings

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

3. Deﬁnitions

4. Byte Order, Alignment, and Time Format

5. RTP Data Transfer Protocol

5

6

6

6

7

7

8

8

11

12

5.1 RTP Fixed Header Fields . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 12

5.2 Multiplexing RTP Sessions . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 15

5.3 Pro(cid:12)le-Speci(cid:12)c Modi(cid:12)cations to the RTP Header

. . . . . . . . . . . . . . . . . . . 15

5.3.1 RTP Header Extension . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 16

6. RTP Control Protocol — RTCP

17

6.1 RTCP Packet Format . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 18

6.2 RTCP Transmission Interval . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 20

6.2.1 Maintaining the Number of Session Members

. . . . . . . . . . . . . . . . . 23

6.3 RTCP Packet Send and Receive Rules

. . . . . . . . . . . . . . . . . . . . . . . . . 24

6.3.1 Computing the RTCP Transmission Interval . . . . . . . . . . . . . . . . . . 25

6.3.2

Initialization . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 25

6.3.3 Receiving an RTP or Non-BYE RTCP Packet . . . . . . . . . . . . . . . . . 26

6.3.4 Receiving an RTCP BYE Packet

. . . . . . . . . . . . . . . . . . . . . . . . 26

6.3.5 Timing Out an SSRC . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 27

6.3.6 Expiration of Transmission Timer . . . . . . . . . . . . . . . . . . . . . . . . 27

6.3.7 Transmitting a BYE Packet . . . . . . . . . . . . . . . . . . . . . . . . . . . 27

6.3.8 Updating we sent . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 28

Schulzrinne, et al.

Standards Track

[Page 2]

RFC 3550

RTP

July 2003

6.3.9 Allocation of Source Description Bandwidth . . . . . . . . . . . . . . . . . . 28

6.4 Sender and Receiver Reports . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 29

6.4.1

SR: Sender Report RTCP Packet . . . . . . . . . . . . . . . . . . . . . . . . 30

6.4.2 RR: Receiver Report RTCP Packet . . . . . . . . . . . . . . . . . . . . . . . 35

6.4.3 Extending the Sender and Receiver Reports . . . . . . . . . . . . . . . . . . 35

6.4.4 Analyzing Sender and Receiver Reports

. . . . . . . . . . . . . . . . . . . . 36

6.5 SDES: Source Description RTCP Packet

. . . . . . . . . . . . . . . . . . . . . . . . 37

6.5.1 CNAME: Canonical End-Point Identi(cid:12)er SDES Item . . . . . . . . . . . . . 38

6.5.2 NAME: User Name SDES Item . . . . . . . . . . . . . . . . . . . . . . . . . 40

6.5.3 EMAIL: Electronic Mail Address SDES Item . . . . . . . . . . . . . . . . . 40

6.5.4 PHONE: Phone Number SDES Item . . . . . . . . . . . . . . . . . . . . . . 40

6.5.5 LOC: Geographic User Location SDES Item . . . . . . . . . . . . . . . . . . 41

6.5.6 TOOL: Application or Tool Name SDES Item . . . . . . . . . . . . . . . . . 41

6.5.7 NOTE: Notice/Status SDES Item . . . . . . . . . . . . . . . . . . . . . . . . 41

6.5.8 PRIV: Private Extensions SDES Item . . . . . . . . . . . . . . . . . . . . . . 42

6.6 BYE: Goodbye RTCP Packet

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 43

6.7 APP: Application-De(cid:12)ned RTCP Packet . . . . . . . . . . . . . . . . . . . . . . . . 44

7. RTP Translators and Mixers

45

7.1 General Description . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 45

7.2 RTCP Processing in Translators . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 46

7.3 RTCP Processing in Mixers

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 48

7.4 Cascaded Mixers

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 49

8. SSRC Identiﬁer Allocation and Use

49

8.1 Probability of Collision . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 49

8.2 Collision Resolution and Loop Detection . . . . . . . . . . . . . . . . . . . . . . . . 50

8.3 Use with Layered Encodings . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 54

9. Security

54

9.1 Con(cid:12)dentiality . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 54

9.2 Authentication and Message Integrity . . . . . . . . . . . . . . . . . . . . . . . . . . 56

10. Congestion Control

56

Schulzrinne, et al.

Standards Track

[Page 3]

RFC 3550

RTP

July 2003

11. RTP over Network and Transport Protocols

12. Summary of Protocol Constants

56

58

12.1 RTCP Packet Types

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 58

12.2 SDES Types . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 58

13. RTP Proﬁles and Payload Format Speciﬁcations

14. Security Considerations

15. IANA Considerations

16. Intellectual Property Rights Statement

17. Acknowledgments

Appendix A. Algorithms

59

60

61

61

61

62

A.1 RTP Data Header Validity Checks . . . . . . . . . . . . . . . . . . . . . . . . . . . . 65

A.2 RTCP Header Validity Checks . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 69

A.3 Determining Number of Packets Expected and Lost . . . . . . . . . . . . . . . . . . 69

A.4 Generating RTCP SDES Packets

. . . . . . . . . . . . . . . . . . . . . . . . . . . . 70

A.5 Parsing RTCP SDES Packets

. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 71

A.6 Generating a Random 32-bit Identi(cid:12)er

. . . . . . . . . . . . . . . . . . . . . . . . . 72

A.7 Computing the RTCP Transmission Interval

. . . . . . . . . . . . . . . . . . . . . . 74

A.8 Estimating the Interarrival Jitter

. . . . . . . . . . . . . . . . . . . . . . . . . . . . 80

Appendix B. Changes from RFC 1889

References

81

85

Normative References . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 85

Informative References . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 85

Authors’ Addresses

Full Copyright Statement

88

89

Schulzrinne, et al.

Standards Track

[Page 4]

RFC 3550

RTP

July 2003

1.

Introduction

This memorandum speci(cid:12)es the real-time transport protocol (RTP), which provides end-to-end
delivery services for data with real-time characteristics, such as interactive audio and video. Those
services include payload type identi(cid:12)cation, sequence numbering, timestamping and delivery mon-
itoring. Applications typically run RTP on top of UDP to make use of its multiplexing and check-
sum services; both protocols contribute parts of the transport protocol functionality. However,
RTP may be used with other suitable underlying network or transport protocols (see Section 11).
RTP supports data transfer to multiple destinations using multicast distribution if provided by the
underlying network.

Note that RTP itself does not provide any mechanism to ensure timely delivery or provide other
It does not guarantee
quality-of-service guarantees, but relies on lower-layer services to do so.
delivery or prevent out-of-order delivery, nor does it assume that the underlying network is reliable
and delivers packets in sequence. The sequence numbers included in RTP allow the receiver to
reconstruct the sender’s packet sequence, but sequence numbers might also be used to determine
the proper location of a packet, for example in video decoding, without necessarily decoding packets
in sequence.

While RTP is primarily designed to satisfy the needs of multi-participant multimedia conferences,
it is not limited to that particular application. Storage of continuous data, interactive distributed
simulation, active badge, and control and measurement applications may also (cid:12)nd RTP applicable.

This document de(cid:12)nes RTP, consisting of two closely-linked parts:

(cid:15) the real-time transport protocol (RTP), to carry data that has real-time properties.

(cid:15) the RTP control protocol (RTCP), to monitor the quality of service and to convey information
about the participants in an on-going session. The latter aspect of RTCP may be su(cid:14)cient for
\loosely controlled" sessions, i.e., where there is no explicit membership control and set-up,
but it is not necessarily intended to support all of an application’s control communication
requirements. This functionality may be fully or partially subsumed by a separate session
control protocol, which is beyond the scope of this document.

RTP represents a new style of protocol following the principles of application level framing and
integrated layer processing proposed by Clark and Tennenhouse [10]. That is, RTP is intended
to be malleable to provide the information required by a particular application and will often
be integrated into the application processing rather than being implemented as a separate layer.
RTP is a protocol framework that is deliberately not complete. This document speci(cid:12)es those
functions expected to be common across all the applications for which RTP would be appropriate.
Unlike conventional protocols in which additional functions might be accommodated by making
the protocol more general or by adding an option mechanism that would require parsing, RTP is
intended to be tailored through modi(cid:12)cations and/or additions to the headers as needed. Examples
are given in Sections 5.3 and 6.4.3.

Therefore, in addition to this document, a complete speci(cid:12)cation of RTP for a particular application
will require one or more companion documents (see Section 13):

Schulzrinne, et al.

Standards Track

[Page 5]

RFC 3550

RTP

July 2003

(cid:15) a proﬁle speci(cid:12)cation document, which de(cid:12)nes a set of payload type codes and their mapping
to payload formats (e.g., media encodings). A pro(cid:12)le may also de(cid:12)ne extensions or modi(cid:12)ca-
tions to RTP that are speci(cid:12)c to a particular class of applications. Typically an application
will operate under only one pro(cid:12)le. A pro(cid:12)le for audio and video data may be found in the
companion RFC 3551 [1].

(cid:15) payload format speci(cid:12)cation documents, which de(cid:12)ne how a particular payload, such as an

audio or video encoding, is to be carried in RTP.

A discussion of real-time services and algorithms for their implementation as well as background
discussion on some of the RTP design decisions can be found in [11].

1.1 Terminology

The key words \must", \must not", \required", \shall", \shall not", \should", \should
not", \recommended", \may", and \optional" in this document are to be interpreted as de-
scribed in BCP 14, RFC 2119 [2] and indicate requirement levels for compliant RTP implementa-
tions.

2. RTP Use Scenarios

The following sections describe some aspects of the use of RTP. The examples were chosen to
illustrate the basic operation of applications using RTP, not to limit what RTP may be used for.
In these examples, RTP is carried on top of IP and UDP, and follows the conventions established
by the pro(cid:12)le for audio and video speci(cid:12)ed in the companion RFC 3551.

2.1 Simple Multicast Audio Conference

A working group of the IETF meets to discuss the latest protocol document, using the IP multicast
services of the Internet for voice communications. Through some allocation mechanism the working
group chair obtains a multicast group address and pair of ports. One port is used for audio data,
and the other is used for control (RTCP) packets. This address and port information is distributed
to the intended participants. If privacy is desired, the data and control packets may be encrypted
as speci(cid:12)ed in Section 9.1, in which case an encryption key must also be generated and distributed.
The exact details of these allocation and distribution mechanisms are beyond the scope of RTP.

The audio conferencing application used by each conference participant sends audio data in small
chunks of, say, 20 ms duration. Each chunk of audio data is preceded by an RTP header; RTP
header and data are in turn contained in a UDP packet. The RTP header indicates what type of
audio encoding (such as PCM, ADPCM or LPC) is contained in each packet so that senders can
change the encoding during a conference, for example, to accommodate a new participant that is
connected through a low-bandwidth link or react to indications of network congestion.

The Internet, like other packet networks, occasionally loses and reorders packets and delays them
by variable amounts of time. To cope with these impairments, the RTP header contains timing

Schulzrinne, et al.

Standards Track

[Page 6]

RFC 3550

RTP

July 2003

information and a sequence number that allow the receivers to reconstruct the timing produced by
the source, so that in this example, chunks of audio are contiguously played out the speaker every
20 ms. This timing reconstruction is performed separately for each source of RTP packets in the
conference. The sequence number can also be used by the receiver to estimate how many packets
are being lost.

Since members of the working group join and leave during the conference, it is useful to know who
is participating at any moment and how well they are receiving the audio data. For that purpose,
each instance of the audio application in the conference periodically multicasts a reception report
plus the name of its user on the RTCP (control) port. The reception report indicates how well the
current speaker is being received and may be used to control adaptive encodings. In addition to
the user name, other identifying information may also be included subject to control bandwidth
limits. A site sends the RTCP BYE packet (Section 6.6) when it leaves the conference.

2.2 Audio and Video Conference

If both audio and video media are used in a conference, they are transmitted as separate RTP
sessions. That is, separate RTP and RTCP packets are transmitted for each medium using two
di(cid:11)erent UDP port pairs and/or multicast addresses. There is no direct coupling at the RTP level
between the audio and video sessions, except that a user participating in both sessions should use
the same distinguished (canonical) name in the RTCP packets for both so that the sessions can be
associated.

One motivation for this separation is to allow some participants in the conference to receive only
one medium if they choose. Further explanation is given in Section 5.2. Despite the separation,
synchronized playback of a source’s audio and video can be achieved using timing information
carried in the RTCP packets for both sessions.

2.3 Mixers and Translators

So far, we have assumed that all sites want to receive media data in the same format. However, this
may not always be appropriate. Consider the case where participants in one area are connected
through a low-speed link to the majority of the conference participants who enjoy high-speed net-
work access. Instead of forcing everyone to use a lower-bandwidth, reduced-quality audio encoding,
an RTP-level relay called a mixer may be placed near the low-bandwidth area. This mixer resyn-
chronizes incoming audio packets to reconstruct the constant 20 ms spacing generated by the sender,
mixes these reconstructed audio streams into a single stream, translates the audio encoding to a
lower-bandwidth one and forwards the lower-bandwidth packet stream across the low-speed link.
These packets might be unicast to a single recipient or multicast on a di(cid:11)erent address to multiple
recipients. The RTP header includes a means for mixers to identify the sources that contributed
to a mixed packet so that correct talker indication can be provided at the receivers.

Some of the intended participants in the audio conference may be connected with high bandwidth
links but might not be directly reachable via IP multicast. For example, they might be behind
an application-level (cid:12)rewall that will not let any IP packets pass. For these sites, mixing may
not be necessary, in which case another type of RTP-level relay called a translator may be used.

Schulzrinne, et al.

Standards Track

[Page 7]

RFC 3550

RTP

July 2003

Two translators are installed, one on either side of the (cid:12)rewall, with the outside one funneling all
multicast packets received through a secure connection to the translator inside the (cid:12)rewall. The
translator inside the (cid:12)rewall sends them again as multicast packets to a multicast group restricted
to the site’s internal network.

Mixers and translators may be designed for a variety of purposes. An example is a video mixer that
scales the images of individual people in separate video streams and composites them into one video
stream to simulate a group scene. Other examples of translation include the connection of a group
of hosts speaking only IP/UDP to a group of hosts that understand only ST-II, or the packet-by-
packet encoding translation of video streams from individual sources without resynchronization or
mixing. Details of the operation of mixers and translators are given in Section 7.

2.4 Layered Encodings

Multimedia applications should be able to adjust the transmission rate to match the capacity of
the receiver or to adapt to network congestion. Many implementations place the responsibility of
rate-adaptivity at the source. This does not work well with multicast transmission because of the
conﬂicting bandwidth requirements of heterogeneous receivers. The result is often a least-common
denominator scenario, where the smallest pipe in the network mesh dictates the quality and (cid:12)delity
of the overall live multimedia \broadcast".

Instead, responsibility for rate-adaptation can be placed at the receivers by combining a layered
encoding with a layered transmission system. In the context of RTP over IP multicast, the source
can stripe the progressive layers of a hierarchically represented signal across multiple RTP sessions
each carried on its own multicast group. Receivers can then adapt to network heterogeneity and
control their reception bandwidth by joining only the appropriate subset of the multicast groups.

Details of the use of RTP with layered encodings are given in Sections 6.3.9, 8.3 and 11.

3. Deﬁnitions

RTP payload: The data transported by RTP in a packet, for example audio samples or com-
pressed video data. The payload format and interpretation are beyond the scope of this
document.

RTP packet: A data packet consisting of the (cid:12)xed RTP header, a possibly empty list of contribut-
ing sources (see below), and the payload data. Some underlying protocols may require an
encapsulation of the RTP packet to be de(cid:12)ned. Typically one packet of the underlying pro-
tocol contains a single RTP packet, but several RTP packets may be contained if permitted
by the encapsulation method (see Section 11).

RTCP packet: A control packet consisting of a (cid:12)xed header part similar to that of RTP data
packets, followed by structured elements that vary depending upon the RTCP packet type.
The formats are de(cid:12)ned in Section 6. Typically, multiple RTCP packets are sent together as
a compound RTCP packet in a single packet of the underlying protocol; this is enabled by
the length (cid:12)eld in the (cid:12)xed header of each RTCP packet.

Schulzrinne, et al.

Standards Track

[Page 8]

RFC 3550

RTP

July 2003

Port: The \abstraction that transport protocols use to distinguish among multiple destinations
within a given host computer. TCP/IP protocols identify ports using small positive integers."
[12] The transport selectors (TSEL) used by the OSI transport layer are equivalent to ports.
RTP depends upon the lower-layer protocol to provide some mechanism such as ports to
multiplex the RTP and RTCP packets of a session.

Transport address: The combination of a network address and port that identi(cid:12)es a transport-
level endpoint, for example an IP address and a UDP port. Packets are transmitted from a
source transport address to a destination transport address.

RTP media type: An RTP media type is the collection of payload types which can be carried
within a single RTP session. The RTP Pro(cid:12)le assigns RTP media types to RTP payload
types.

Multimedia session: A set of concurrent RTP sessions among a common group of participants.
For example, a videoconference (which is a multimedia session) may contain an audio RTP
session and a video RTP session.

RTP session: An association among a set of participants communicating with RTP. A participant
may be involved in multiple RTP sessions at the same time. In a multimedia session, each
medium is typically carried in a separate RTP session with its own RTCP packets unless
the the encoding itself multiplexes multiple media into a single data stream. A participant
distinguishes multiple RTP sessions by reception of di(cid:11)erent sessions using di(cid:11)erent pairs of
destination transport addresses, where a pair of transport addresses comprises one network
address plus a pair of ports for RTP and RTCP. All participants in an RTP session may
share a common destination transport address pair, as in the case of IP multicast, or the pairs
may be di(cid:11)erent for each participant, as in the case of individual unicast network addresses
and port pairs. In the unicast case, a participant may receive from all other participants in
the session using the same pair of ports, or may use a distinct pair of ports for each.

The distinguishing feature of an RTP session is that each maintains a full, separate space of
SSRC identi(cid:12)ers (de(cid:12)ned next). The set of participants included in one RTP session consists
of those that can receive an SSRC identi(cid:12)er transmitted by any one of the participants either
in RTP as the SSRC or a CSRC (also de(cid:12)ned below) or in RTCP. For example, consider a
three-party conference implemented using unicast UDP with each participant receiving from
the other two on separate port pairs. If each participant sends RTCP feedback about data
received from one other participant only back to that participant, then the conference is
composed of three separate point-to-point RTP sessions. If each participant provides RTCP
feedback about its reception of one other participant to both of the other participants, then
the conference is composed of one multi-party RTP session. The latter case simulates the
behavior that would occur with IP multicast communication among the three participants.

The RTP framework allows the variations de(cid:12)ned here, but a particular control protocol or
application design will usually impose constraints on these variations.

Synchronization source (SSRC): The source of a stream of RTP packets, identi(cid:12)ed by a 32-bit
numeric SSRC identi(cid:12)er carried in the RTP header so as not to be dependent upon the network
address. All packets from a synchronization source form part of the same timing and sequence

Schulzrinne, et al.

Standards Track

[Page 9]

RFC 3550

RTP

July 2003

number space, so a receiver groups packets by synchronization source for playback. Examples
of synchronization sources include the sender of a stream of packets derived from a signal
source such as a microphone or a camera, or an RTP mixer (see below). A synchronization
source may change its data format, e.g., audio encoding, over time. The SSRC identi(cid:12)er is
a randomly chosen value meant to be globally unique within a particular RTP session (see
Section 8). A participant need not use the same SSRC identi(cid:12)er for all the RTP sessions
in a multimedia session; the binding of the SSRC identi(cid:12)ers is provided through RTCP (see
Section 6.5.1). If a participant generates multiple streams in one RTP session, for example
from separate video cameras, each must be identi(cid:12)ed as a di(cid:11)erent SSRC.

Contributing source (CSRC): A source of a stream of RTP packets that has contributed to
the combined stream produced by an RTP mixer (see below). The mixer inserts a list of the
SSRC identi(cid:12)ers of the sources that contributed to the generation of a particular packet into
the RTP header of that packet. This list is called the CSRC list. An example application
is audio conferencing where a mixer indicates all the talkers whose speech was combined to
produce the outgoing packet, allowing the receiver to indicate the current talker, even though
all the audio packets contain the same SSRC identi(cid:12)er (that of the mixer).

End system: An application that generates the content to be sent in RTP packets and/or con-
sumes the content of received RTP packets. An end system can act as one or more synchro-
nization sources in a particular RTP session, but typically only one.

Mixer: An intermediate system that receives RTP packets from one or more sources, possibly
changes the data format, combines the packets in some manner and then forwards a new RTP
packet. Since the timing among multiple input sources will not generally be synchronized,
the mixer will make timing adjustments among the streams and generate its own timing for
the combined stream. Thus, all data packets originating from a mixer will be identi(cid:12)ed as
having the mixer as their synchronization source.

Translator: An intermediate system that forwards RTP packets with their synchronization source
identi(cid:12)er intact. Examples of translators include devices that convert encodings without
mixing, replicators from multicast to unicast, and application-level (cid:12)lters in (cid:12)rewalls.

Monitor: An application that receives RTCP packets sent by participants in an RTP session, in
particular the reception reports, and estimates the current quality of service for distribution
monitoring, fault diagnosis and long-term statistics. The monitor function is likely to be built
into the application(s) participating in the session, but may also be a separate application
that does not otherwise participate and does not send or receive the RTP data packets (since
they are on a separate port). These are called third-party monitors. It is also acceptable for a
third-party monitor to receive the RTP data packets but not send RTCP packets or otherwise
be counted in the session.

Non-RTP means: Protocols and mechanisms that may be needed in addition to RTP to provide
a usable service. In particular, for multimedia conferences, a control protocol may distribute
multicast addresses and keys for encryption, negotiate the encryption algorithm to be used,
and de(cid:12)ne dynamic mappings between RTP payload type values and the payload formats they
represent for formats that do not have a prede(cid:12)ned payload type value. Examples of such

Schulzrinne, et al.

Standards Track

[Page 10]

RFC 3550

RTP

July 2003

protocols include the Session Initiation Protocol (SIP) (RFC 3261 [13]), ITU Recommendation
H.323 [14] and applications using SDP (RFC 2327 [15]), such as RTSP (RFC 2326 [16]).
For simple applications, electronic mail or a conference database may also be used. The
speci(cid:12)cation of such protocols and mechanisms is outside the scope of this document.

4. Byte Order, Alignment, and Time Format

All integer (cid:12)elds are carried in network byte order, that is, most signi(cid:12)cant byte (octet) (cid:12)rst. This
byte order is commonly known as big-endian. The transmission order is described in detail in [3,
Appendix A]. Unless otherwise noted, numeric constants are in decimal (base 10).

All header data is aligned to its natural length, i.e., 16-bit (cid:12)elds are aligned on even o(cid:11)sets, 32-bit
(cid:12)elds are aligned at o(cid:11)sets divisible by four, etc. Octets designated as padding have the value zero.

Wallclock time (absolute date and time) is represented using the timestamp format of the Network
Time Protocol (NTP), which is in seconds relative to 0h UTC on 1 January 1900 [4]. The full
resolution NTP timestamp is a 64-bit unsigned (cid:12)xed-point number with the integer part in the
(cid:12)rst 32 bits and the fractional part in the last 32 bits.
In some (cid:12)elds where a more compact
representation is appropriate, only the middle 32 bits are used; that is, the low 16 bits of the
integer part and the high 16 bits of the fractional part. The high 16 bits of the integer part must
be determined independently.

An implementation is not required to run the Network Time Protocol in order to use RTP. Other
time sources, or none at all, may be used (see the description of the NTP timestamp (cid:12)eld in Section
6.4.1). However, running NTP may be useful for synchronizing streams transmitted from separate
hosts.

The NTP timestamp will wrap around to zero some time in the year 2036, but for RTP purposes,
only di(cid:11)erences between pairs of NTP timestamps are used. So long as the pairs of timestamps
can be assumed to be within 68 years of each other, using modular arithmetic for subtractions and
comparisons makes the wraparound irrelevant.

Schulzrinne, et al.

Standards Track

[Page 11]

RFC 3550

RTP

July 2003

5. RTP Data Transfer Protocol

5.1 RTP Fixed Header Fields

The RTP header has the following format:

3

2

1

PT

|M|

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|V=2|P|X| CC
|
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
timestamp
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
synchronization source (SSRC) identifier
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
|
|
contributing source (CSRC) identifiers
|
....
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

sequence number

The (cid:12)rst twelve octets are present in every RTP packet, while the list of CSRC identi(cid:12)ers is present
only when inserted by a mixer. The (cid:12)elds have the following meaning:

version (V): 2 bits

This (cid:12)eld identi(cid:12)es the version of RTP. The version de(cid:12)ned by this speci(cid:12)cation is two (2).
(The value 1 is used by the (cid:12)rst draft version of RTP and the value 0 is used by the protocol
initially implemented in the \vat" audio tool.)

padding (P): 1 bit

If the padding bit is set, the packet contains one or more additional padding octets at the
end which are not part of the payload. The last octet of the padding contains a count of
how many padding octets should be ignored, including itself. Padding may be needed by
some encryption algorithms with (cid:12)xed block sizes or for carrying several RTP packets in a
lower-layer protocol data unit.

extension (X): 1 bit

If the extension bit is set, the (cid:12)xed header must be followed by exactly one header extension,
with a format de(cid:12)ned in Section 5.3.1.

CSRC count (CC): 4 bits

The CSRC count contains the number of CSRC identi(cid:12)ers that follow the (cid:12)xed header.

marker (M): 1 bit

The interpretation of the marker is de(cid:12)ned by a pro(cid:12)le. It is intended to allow signi(cid:12)cant
events such as frame boundaries to be marked in the packet stream. A pro(cid:12)le may de(cid:12)ne
additional marker bits or specify that there is no marker bit by changing the number of bits
in the payload type (cid:12)eld (see Section 5.3).

Schulzrinne, et al.

Standards Track

[Page 12]

RFC 3550

RTP

July 2003

payload type (PT): 7 bits

This (cid:12)eld identi(cid:12)es the format of the RTP payload and determines its interpretation by the
application. A pro(cid:12)le may specify a default static mapping of payload type codes to payload
formats. Additional payload type codes may be de(cid:12)ned dynamically through non-RTP means
(see Section 3). A set of default mappings for audio and video is speci(cid:12)ed in the companion
RFC 3551 [1]. An RTP source may change the payload type during a session, but this (cid:12)eld
should not be used for multiplexing separate media streams (see Section 5.2).
A receiver must ignore packets with payload types that it does not understand.

sequence number: 16 bits

The sequence number increments by one for each RTP data packet sent, and may be used
by the receiver to detect packet loss and to restore packet sequence. The initial value of the
sequence number should be random (unpredictable) to make known-plaintext attacks on
encryption more di(cid:14)cult, even if the source itself does not encrypt according to the method
in Section 9.1, because the packets may ﬂow through a translator that does. Techniques for
choosing unpredictable numbers are discussed in [17].

timestamp: 32 bits

The timestamp reﬂects the sampling instant of the (cid:12)rst octet in the RTP data packet. The
sampling instant must be derived from a clock that increments monotonically and linearly
in time to allow synchronization and jitter calculations (see Section 6.4.1). The resolution
of the clock must be su(cid:14)cient for the desired synchronization accuracy and for measuring
packet arrival jitter (one tick per video frame is typically not su(cid:14)cient). The clock frequency
is dependent on the format of data carried as payload and is speci(cid:12)ed statically in the pro(cid:12)le
or payload format speci(cid:12)cation that de(cid:12)nes the format, or may be speci(cid:12)ed dynamically for
payload formats de(cid:12)ned through non-RTP means. If RTP packets are generated periodically,
the nominal sampling instant as determined from the sampling clock is to be used, not a
reading of the system clock. As an example, for (cid:12)xed-rate audio the timestamp clock would
likely increment by one for each sampling period. If an audio application reads blocks covering
160 sampling periods from the input device, the timestamp would be increased by 160 for
each such block, regardless of whether the block is transmitted in a packet or dropped as
silent.
The initial value of the timestamp should be random, as for the sequence number. Several
consecutive RTP packets will have equal timestamps if they are (logically) generated at once,
e.g., belong to the same video frame. Consecutive RTP packets may contain timestamps that
are not monotonic if the data is not transmitted in the order it was sampled, as in the case
of MPEG interpolated video frames. (The sequence numbers of the packets as transmitted
will still be monotonic.)

RTP timestamps from di(cid:11)erent media streams may advance at di(cid:11)erent rates and usually
have independent, random o(cid:11)sets. Therefore, although these timestamps are su(cid:14)cient to
reconstruct the timing of a single stream, directly comparing RTP timestamps from di(cid:11)erent
Instead, for each medium the RTP timestamp
media is not e(cid:11)ective for synchronization.
is related to the sampling instant by pairing it with a timestamp from a reference clock
(wallclock) that represents the time when the data corresponding to the RTP timestamp was
sampled. The reference clock is shared by all media to be synchronized. The timestamp

Schulzrinne, et al.

Standards Track

[Page 13]

RFC 3550

RTP

July 2003

pairs are not transmitted in every data packet, but at a lower rate in RTCP SR packets as
described in Section 6.4.

The sampling instant is chosen as the point of reference for the RTP timestamp because it is
known to the transmitting endpoint and has a common de(cid:12)nition for all media, independent
of encoding delays or other processing. The purpose is to allow synchronized presentation of
all media sampled at the same time.

Applications transmitting stored data rather than data sampled in real time typically use a
virtual presentation timeline derived from wallclock time to determine when the next frame
or other unit of each medium in the stored data should be presented. In this case, the RTP
timestamp would reﬂect the presentation time for each unit. That is, the RTP timestamp for
each unit would be related to the wallclock time at which the unit becomes current on the
virtual presentation timeline. Actual presentation occurs some time later as determined by
the receiver.

An example describing live audio narration of prerecorded video illustrates the signi(cid:12)cance
of choosing the sampling instant as the reference point. In this scenario, the video would
be presented locally for the narrator to view and would be simultaneously transmitted using
RTP. The \sampling instant" of a video frame transmitted in RTP would be established by
referencing its timestamp to the wallclock time when that video frame was presented to the
narrator. The sampling instant for the audio RTP packets containing the narrator’s speech
would be established by referencing the same wallclock time when the audio was sampled.
The audio and video may even be transmitted by di(cid:11)erent hosts if the reference clocks on
the two hosts are synchronized by some means such as NTP. A receiver can then synchronize
presentation of the audio and video packets by relating their RTP timestamps using the
timestamp pairs in RTCP SR packets.

SSRC: 32 bits

The SSRC (cid:12)eld identi(cid:12)es the synchronization source. This identi(cid:12)er should be
chosen
randomly, with the intent that no two synchronization sources within the same RTP session
will have the same SSRC identi(cid:12)er. An example algorithm for generating a random identi(cid:12)er
is presented in Appendix A.6. Although the probability of multiple sources choosing the same
identi(cid:12)er is low, all RTP implementations must be prepared to detect and resolve collisions.
Section 8 describes the probability of collision along with a mechanism for resolving collisions
and detecting RTP-level forwarding loops based on the uniqueness of the SSRC identi(cid:12)er. If
a source changes its source transport address, it must also choose a new SSRC identi(cid:12)er to
avoid being interpreted as a looped source (see Section 8.2).

CSRC list: 0 to 15 items, 32 bits each

The CSRC list identi(cid:12)es the contributing sources for the payload contained in this packet.
The number of identi(cid:12)ers is given by the CC (cid:12)eld. If there are more than 15 contributing
sources, only 15 can be identi(cid:12)ed. CSRC identi(cid:12)ers are inserted by mixers (see Section 7.1),
using the SSRC identi(cid:12)ers of contributing sources. For example, for audio packets the SSRC
identi(cid:12)ers of all sources that were mixed together to create a packet are listed, allowing correct
talker indication at the receiver.

Schulzrinne, et al.

Standards Track

[Page 14]

RFC 3550

RTP

July 2003

5.2 Multiplexing RTP Sessions

For e(cid:14)cient protocol processing, the number of multiplexing points should be minimized, as de-
scribed in the integrated layer processing design principle [10]. In RTP, multiplexing is provided
by the destination transport address (network address and port number) which is di(cid:11)erent for
each RTP session. For example, in a teleconference composed of audio and video media encoded
separately, each medium should be carried in a separate RTP session with its own destination
transport address.
Separate audio and video streams should not be carried in a single RTP session and demultiplexed
based on the payload type or SSRC (cid:12)elds. Interleaving packets with di(cid:11)erent RTP media types
but using the same SSRC would introduce several problems:

1. If, say, two audio streams shared the same RTP session and the same SSRC value, and one
were to change encodings and thus acquire a di(cid:11)erent RTP payload type, there would be no
general way of identifying which stream had changed encodings.

2. An SSRC is de(cid:12)ned to identify a single timing and sequence number space.

Interleaving
multiple payload types would require di(cid:11)erent timing spaces if the media clock rates di(cid:11)er
and would require di(cid:11)erent sequence number spaces to tell which payload type su(cid:11)ered packet
loss.

3. The RTCP sender and receiver reports (see Section 6.4) can only describe one timing and

sequence number space per SSRC and do not carry a payload type (cid:12)eld.

4. An RTP mixer would not be able to combine interleaved streams of incompatible media into

one stream.

5. Carrying multiple media in one RTP session precludes: the use of di(cid:11)erent network paths or
network resource allocations if appropriate; reception of a subset of the media if desired, for
example just audio if video would exceed the available bandwidth; and receiver implementa-
tions that use separate processes for the di(cid:11)erent media, whereas using separate RTP sessions
permits either single- or multiple-process implementations.

Using a di(cid:11)erent SSRC for each medium but sending them in the same RTP session would avoid
the (cid:12)rst three problems but not the last two.

On the other hand, multiplexing multiple related sources of the same medium in one RTP session
using di(cid:11)erent SSRC values is the norm for multicast sessions. The problems listed above don’t
apply: an RTP mixer can combine multiple audio sources, for example, and the same treatment is
applicable for all of them. It may also be appropriate to multiplex streams of the same medium
using di(cid:11)erent SSRC values in other scenarios where the last two problems do not apply.

5.3 Proﬁle-Speciﬁc Modiﬁcations to the RTP Header

The existing RTP data packet header is believed to be complete for the set of functions required
in common across all the application classes that RTP might support. However, in keeping with
the ALF design principle, the header may be tailored through modi(cid:12)cations or additions de(cid:12)ned

Schulzrinne, et al.

Standards Track

[Page 15]

RFC 3550

RTP

July 2003

in a pro(cid:12)le speci(cid:12)cation while still allowing pro(cid:12)le-independent monitoring and recording tools to
function.

(cid:15) The marker bit and payload type (cid:12)eld carry pro(cid:12)le-speci(cid:12)c information, but they are allocated
in the (cid:12)xed header since many applications are expected to need them and might otherwise
have to add another 32-bit word just to hold them. The octet containing these (cid:12)elds may be
rede(cid:12)ned by a pro(cid:12)le to suit di(cid:11)erent requirements, for example with more or fewer marker
bits. If there are any marker bits, one should be located in the most signi(cid:12)cant bit of the
octet since pro(cid:12)le-independent monitors may be able to observe a correlation between packet
loss patterns and the marker bit.

(cid:15) Additional information that is required for a particular payload format, such as a video
encoding, should be carried in the payload section of the packet. This might be in a header
that is always present at the start of the payload section, or might be indicated by a reserved
value in the data pattern.

(cid:15) If a particular class of applications needs additional functionality independent of payload for-
mat, the pro(cid:12)le under which those applications operate should de(cid:12)ne additional (cid:12)xed (cid:12)elds
to follow immediately after the SSRC (cid:12)eld of the existing (cid:12)xed header. Those applications will
be able to quickly and directly access the additional (cid:12)elds while pro(cid:12)le-independent monitors
or recorders can still process the RTP packets by interpreting only the (cid:12)rst twelve octets.

If it turns out that additional functionality is needed in common across all pro(cid:12)les, then a new
version of RTP should be de(cid:12)ned to make a permanent change to the (cid:12)xed header.

5.3.1 RTP Header Extension

An extension mechanism is provided to allow individual implementations to experiment with new
payload-format-independent functions that require additional information to be carried in the RTP
data packet header. This mechanism is designed so that the header extension may be ignored by
other interoperating implementations that have not been extended.

Note that this header extension is intended only for limited use. Most potential uses of this
mechanism would be better done another way, using the methods described in the previous section.
For example, a pro(cid:12)le-speci(cid:12)c extension to the (cid:12)xed header is less expensive to process because it is
not conditional nor in a variable location. Additional information required for a particular payload
format should not use this header extension, but should be carried in the payload section of
the packet.

2

1

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
header extension
|
|

defined by profile

length

....

3

Schulzrinne, et al.

Standards Track

[Page 16]

RFC 3550

RTP

July 2003

If the X bit in the RTP header is one, a variable-length header extension must be appended to
the RTP header, following the CSRC list if present. The header extension contains a 16-bit length
(cid:12)eld that counts the number of 32-bit words in the extension, excluding the four-octet extension
header (therefore zero is a valid length). Only a single extension can be appended to the RTP data
header. To allow multiple interoperating implementations to each experiment independently with
di(cid:11)erent header extensions, or to allow a particular implementation to experiment with more than
one type of header extension, the (cid:12)rst 16 bits of the header extension are left open for distinguishing
identi(cid:12)ers or parameters. The format of these 16 bits is to be de(cid:12)ned by the pro(cid:12)le speci(cid:12)cation
under which the implementations are operating. This RTP speci(cid:12)cation does not de(cid:12)ne any header
extensions itself.

6. RTP Control Protocol — RTCP

The RTP control protocol (RTCP) is based on the periodic transmission of control packets to
all participants in the session, using the same distribution mechanism as the data packets. The
underlying protocol must provide multiplexing of the data and control packets, for example using
separate port numbers with UDP. RTCP performs four functions:

1. The primary function is to provide feedback on the quality of the data distribution. This
is an integral part of the RTP’s role as a transport protocol and is related to the ﬂow and
congestion control functions of other transport protocols (see Section 10 on the requirement
for congestion control). The feedback may be directly useful for control of adaptive encodings
[18, 19], but experiments with IP multicasting have shown that it is also critical to get feedback
from the receivers to diagnose faults in the distribution. Sending reception feedback reports
to all participants allows one who is observing problems to evaluate whether those problems
are local or global. With a distribution mechanism like IP multicast, it is also possible for
an entity such as a network service provider who is not otherwise involved in the session
to receive the feedback information and act as a third-party monitor to diagnose network
problems. This feedback function is performed by the RTCP sender and receiver reports,
described below in Section 6.4.

2. RTCP carries a persistent transport-level identi(cid:12)er for an RTP source called the canoni-
cal name or CNAME, Section 6.5.1. Since the SSRC identi(cid:12)er may change if a conﬂict is
discovered or a program is restarted, receivers require the CNAME to keep track of each
participant. Receivers may also require the CNAME to associate multiple data streams from
a given participant in a set of related RTP sessions, for example to synchronize audio and
video. Inter-media synchronization also requires the NTP and RTP timestamps included in
RTCP packets by data senders.

3. The (cid:12)rst two functions require that all participants send RTCP packets, therefore the rate
must be controlled in order for RTP to scale up to a large number of participants. By having
each participant send its control packets to all the others, each can independently observe the

Schulzrinne, et al.

Standards Track

[Page 17]

RFC 3550

RTP

July 2003

number of participants. This number is used to calculate the rate at which the packets are
sent, as explained in Section 6.2.

4. A fourth, optional function is to convey minimal session control information, for example
participant identi(cid:12)cation to be displayed in the user interface. This is most likely to be useful
in \loosely controlled" sessions where participants enter and leave without membership control
or parameter negotiation. RTCP serves as a convenient channel to reach all the participants,
but it is not necessarily expected to support all the control communication requirements of
an application. A higher-level session control protocol, which is beyond the scope of this
document, may be needed.

Functions 1-3 should be used in all environments, but particularly in the IP multicast environment.
RTP application designers should avoid mechanisms that can only work in unicast mode and will
not scale to larger numbers. Transmission of RTCP may be controlled separately for senders and
receivers, as described in Section 6.2, for cases such as unidirectional links where feedback from
receivers is not possible.

Non-normative note: In the multicast routing approach called Source-Speci(cid:12)c Mul-
ticast (SSM), there is only one sender per \channel" (a source address, group address
pair), and receivers (except for the channel source) cannot use multicast to communi-
cate directly with other channel members. The recommendations here accommodate
SSM only through Section 6.2’s option of turning o(cid:11) receivers’ RTCP entirely. Future
work will specify adaptation of RTCP for SSM so that feedback from receivers can be
maintained.

6.1 RTCP Packet Format

This speci(cid:12)cation de(cid:12)nes several RTCP packet types to carry a variety of control information:

SR: Sender report, for transmission and reception statistics from participants that are active

senders

RR: Receiver report, for reception statistics from participants that are not active senders and in

combination with SR for active senders reporting on more than 31 sources

SDES: Source description items, including CNAME

BYE: Indicates end of participation

APP: Application-speci(cid:12)c functions

Each RTCP packet begins with a (cid:12)xed part similar to that of RTP data packets, followed by
structured elements that may be of variable length according to the packet type but must end on
a 32-bit boundary. The alignment requirement and a length (cid:12)eld in the (cid:12)xed part of each packet are
included to make RTCP packets \stackable". Multiple RTCP packets can be concatenated without
any intervening separators to form a compound RTCP packet that is sent in a single packet of the

Schulzrinne, et al.

Standards Track

[Page 18]

RFC 3550

RTP

July 2003

lower layer protocol, for example UDP. There is no explicit count of individual RTCP packets in
the compound packet since the lower layer protocols are expected to provide an overall length to
determine the end of the compound packet.

Each individual RTCP packet in the compound packet may be processed independently with no
requirements upon the order or combination of packets. However, in order to perform the functions
of the protocol, the following constraints are imposed:

(cid:15) Reception statistics (in SR or RR) should be sent as often as bandwidth constraints will allow
to maximize the resolution of the statistics, therefore each periodically transmitted compound
RTCP packet must include a report packet.

(cid:15) New receivers need to receive the CNAME for a source as soon as possible to identify the
source and to begin associating media for purposes such as lip-sync, so each compound RTCP
packet must also include the SDES CNAME except when the compound RTCP packet is
split for partial encryption as described in Section 9.1.

(cid:15) The number of packet types that may appear (cid:12)rst in the compound packet needs to be limited
to increase the number of constant bits in the (cid:12)rst word and the probability of successfully
validating RTCP packets against misaddressed RTP data packets or other unrelated packets.

Thus, all RTCP packets must be sent in a compound packet of at least two individual packets,
with the following format:

Encryption preﬁx: If and only if the compound packet is to be encrypted according to the
method in Section 9.1, it must be pre(cid:12)xed by a random 32-bit quantity redrawn for every
compound packet transmitted. If padding is required for the encryption, it must be added
to the last packet of the compound packet.

SR or RR: The (cid:12)rst RTCP packet in the compound packet must always be a report packet to
facilitate header validation as described in Appendix A.2. This is true even if no data has
been sent or received, in which case an empty RR must be sent, and even if the only other
RTCP packet in the compound packet is a BYE.

Additional RRs: If the number of sources for which reception statistics are being reported exceeds
31, the number that will (cid:12)t into one SR or RR packet, then additional RR packets should
follow the initial report packet.

SDES: An SDES packet containing a CNAME item must be included in each compound RTCP
packet, except as noted in Section 9.1. Other source description items may optionally be
included if required by a particular application, subject to bandwidth constraints (see Sec-
tion 6.3.9).

BYE or APP: Other RTCP packet types, including those yet to be de(cid:12)ned, may follow in any
order, except that BYE should be the last packet sent with a given SSRC/CSRC. Packet
types may appear more than once.

Schulzrinne, et al.

Standards Track

[Page 19]

RFC 3550

RTP

July 2003

An individual RTP participant should send only one compound RTCP packet per report interval
in order for the RTCP bandwidth per participant to be estimated correctly (see Section 6.2), except
when the compound RTCP packet is split for partial encryption as described in Section 9.1. If there
are too many sources to (cid:12)t all the necessary RR packets into one compound RTCP packet without
exceeding the maximum transmission unit (MTU) of the network path, then only the subset that
will (cid:12)t into one MTU should be included in each interval. The subsets should be selected
round-robin across multiple intervals so that all sources are reported.
It is recommended that translators and mixers
combine individual RTCP packets from the
multiple sources they are forwarding into one compound packet whenever feasible in order to
amortize the packet overhead (see Section 7). An example RTCP compound packet as might be
produced by a mixer is shown in Fig. 1. If the overall length of a compound packet would exceed
the MTU of the network path, it should be segmented into multiple shorter compound packets
to be transmitted in separate packets of the underlying protocol. This does not impair the RTCP
bandwidth estimation because each compound packet represents at least one distinct participant.
Note that each of the compound packets must begin with an SR or RR packet.
An implementation should ignore incoming RTCP packets with types unknown to it. Additional
RTCP packet types may be registered with the Internet Assigned Numbers Authority (IANA) as
described in Section 15.

if encrypted: random 32-bit integer

packet

packet

packet

receiver reports

item

item

item

item

chunk

chunk

SR

C
R
S
S

sender
report

C
R
S
S

site 1

C
R
S
S

site 2

SDES

C
R
S
S

CNAME PHONE

C
R
S
S

CNAME

LOC

BYE

C
R
S
S

C
R
S
S

reason

compound packet
UDP packet

Figure 1: Example of an RTCP compound packet

6.2 RTCP Transmission Interval

RTP is designed to allow an application to scale automatically over session sizes ranging from a
few participants to thousands. For example, in an audio conference the data tra(cid:14)c is inherently
self-limiting because only one or two people will speak at a time, so with multicast distribution the
data rate on any given link remains relatively constant independent of the number of participants.
However, the control tra(cid:14)c is not self-limiting. If the reception reports from each participant were
sent at a constant rate, the control tra(cid:14)c would grow linearly with the number of participants.
Therefore, the rate must be scaled down by dynamically calculating the interval between RTCP
packet transmissions.

For each session, it is assumed that the data tra(cid:14)c is subject to an aggregate limit called the
\session bandwidth" to be divided among the participants. This bandwidth might be reserved
and the limit enforced by the network. If there is no reservation, there may be other constraints,

Schulzrinne, et al.

Standards Track

[Page 20]

RFC 3550

RTP

July 2003

depending on the environment, that establish the \reasonable" maximum for the session to use, and
that would be the session bandwidth. The session bandwidth may be chosen based on some cost or
a priori knowledge of the available network bandwidth for the session. It is somewhat independent
of the media encoding, but the encoding choice may be limited by the session bandwidth. Often, the
session bandwidth is the sum of the nominal bandwidths of the senders expected to be concurrently
active. For teleconference audio, this number would typically be one sender’s bandwidth. For
layered encodings, each layer is a separate RTP session with its own session bandwidth parameter.

The session bandwidth parameter is expected to be supplied by a session management application
when it invokes a media application, but media applications may set a default based on the single-
sender data bandwidth for the encoding selected for the session. The application may also enforce
bandwidth limits based on multicast scope rules or other criteria. All participants must use the
same value for the session bandwidth so that the same RTCP interval will be calculated.

Bandwidth calculations for control and data tra(cid:14)c include lower-layer transport and network pro-
tocols (e.g., UDP and IP) since that is what the resource reservation system would need to know.
The application can also be expected to know which of these protocols are in use. Link level headers
are not included in the calculation since the packet will be encapsulated with di(cid:11)erent link level
headers as it travels.

The control tra(cid:14)c should be limited to a small and known fraction of the session bandwidth: small
so that the primary function of the transport protocol to carry data is not impaired; known so that
the control tra(cid:14)c can be included in the bandwidth speci(cid:12)cation given to a resource reservation
protocol, and so that each participant can independently calculate its share. The control tra(cid:14)c
bandwidth is in addition to the session bandwidth for the data tra(cid:14)c. It is recommended that the
fraction of the session bandwidth added for RTCP be (cid:12)xed at 5%. It is also recommended that
1/4 of the RTCP bandwidth be dedicated to participants that are sending data so that in sessions
with a large number of receivers but a small number of senders, newly joining participants will
more quickly receive the CNAME for the sending sites. When the proportion of senders is greater
than 1/4 of the participants, the senders get their proportion of the full RTCP bandwidth. While
the values of these and other constants in the interval calculation are not critical, all participants
in the session must use the same values so the same interval will be calculated. Therefore, these
constants should be (cid:12)xed for a particular pro(cid:12)le.
A pro(cid:12)le may specify that the control tra(cid:14)c bandwidth may be a separate parameter of the session
rather than a strict percentage of the session bandwidth. Using a separate parameter allows rate-
adaptive applications to set an RTCP bandwidth consistent with a \typical" data bandwidth that
is lower than the maximum bandwidth speci(cid:12)ed by the session bandwidth parameter.
The pro(cid:12)le may further specify that the control tra(cid:14)c bandwidth may be divided into two separate
session parameters for those participants which are active data senders and those which are not; let
us call the parameters S and R. Following the recommendation that 1/4 of the RTCP bandwidth
be dedicated to data senders, the recommended default values for these two parameters would be
1.25% and 3.75%, respectively. When the proportion of senders is greater than S/(S + R) of the
participants, the senders get their proportion of the sum of these parameters. Using two parameters
allows RTCP reception reports to be turned o(cid:11) entirely for a particular session by setting the RTCP
bandwidth for non-data-senders to zero while keeping the RTCP bandwidth for data senders non-
zero so that sender reports can still be sent for inter-media synchronization. Turning o(cid:11) RTCP

Schulzrinne, et al.

Standards Track

[Page 21]

RFC 3550

RTP

July 2003

reception reports is not recommended because they are needed for the functions listed at the
beginning of Section 6, particularly reception quality feedback and congestion control. However,
doing so may be appropriate for systems operating on unidirectional links or for sessions that don’t
require feedback on the quality of reception or liveness of receivers and that have other means to
avoid congestion.
The calculated interval between transmissions of compound RTCP packets should also have a
lower bound to avoid having bursts of packets exceed the allowed bandwidth when the number of
participants is small and the tra(cid:14)c isn’t smoothed according to the law of large numbers. It also
keeps the report interval from becoming too small during transient outages like a network partition
such that adaptation is delayed when the partition heals. At application startup, a delay should
be imposed before the (cid:12)rst compound RTCP packet is sent to allow time for RTCP packets to
be received from other participants so the report interval will converge to the correct value more
quickly. This delay may be set to half the minimum interval to allow quicker noti(cid:12)cation that the
new participant is present. The recommended value for a (cid:12)xed minimum interval is 5 seconds.
An implementation may scale the minimum RTCP interval to a smaller value inversely proportional
to the session bandwidth parameter with the following limitations:

(cid:15) For multicast sessions, only active data senders may use the reduced minimum value to

calculate the interval for transmission of compound RTCP packets.

(cid:15) For unicast sessions, the reduced value may be used by participants that are not active data
senders as well, and the delay before sending the initial compound RTCP packet may be zero.

(cid:15) For all sessions, the (cid:12)xed minimum should be used when calculating the participant timeout
interval (see Section 6.3.5) so that implementations which do not use the reduced value for
transmitting RTCP packets are not timed out by other participants prematurely.

(cid:15) The recommended value for the reduced minimum in seconds is 360 divided by the session
bandwidth in kilobits/second. This minimum is smaller than 5 seconds for bandwidths greater
than 72 kb/s.

The algorithm described in Section 6.3 and Appendix A.7 was designed to meet the goals outlined
in this section. It calculates the interval between sending compound RTCP packets to divide the
allowed control tra(cid:14)c bandwidth among the participants. This allows an application to provide
fast response for small sessions where, for example, identi(cid:12)cation of all participants is important,
yet automatically adapt to large sessions. The algorithm incorporates the following characteristics:

(cid:15) The calculated interval between RTCP packets scales linearly with the number of members in
the group. It is this linear factor which allows for a constant amount of control tra(cid:14)c when
summed across all members.

(cid:15) The interval between RTCP packets is varied randomly over the range [0.5,1.5] times the
calculated interval to avoid unintended synchronization of all participants [20]. The (cid:12)rst
RTCP packet sent after joining a session is also delayed by a random variation of half the
minimum RTCP interval.

Schulzrinne, et al.

Standards Track

[Page 22]

RFC 3550

RTP

July 2003

(cid:15) A dynamic estimate of the average compound RTCP packet size is calculated, including all
those packets received and sent, to automatically adapt to changes in the amount of control
information carried.

(cid:15) Since the calculated interval is dependent on the number of observed group members, there
may be undesirable startup e(cid:11)ects when a new user joins an existing session, or many users
simultaneously join a new session. These new users will initially have incorrect estimates of
the group membership, and thus their RTCP transmission interval will be too short. This
problem can be signi(cid:12)cant if many users join the session simultaneously. To deal with this,
an algorithm called \timer reconsideration" is employed. This algorithm implements a simple
back-o(cid:11) mechanism which causes users to hold back RTCP packet transmission if the group
sizes are increasing.

(cid:15) When users leave a session, either with a BYE or by timeout, the group membership decreases,
and thus the calculated interval should decrease. A \reverse reconsideration" algorithm is
used to allow members to more quickly reduce their intervals in response to group membership
decreases.

(cid:15) BYE packets are given di(cid:11)erent treatment than other RTCP packets. When a user leaves
a group, and wishes to send a BYE packet, it may do so before its next scheduled RTCP
packet. However, transmission of BYEs follows a back-o(cid:11) algorithm which avoids ﬂoods of
BYE packets should a large number of members simultaneously leave the session.

This algorithm may be used for sessions in which all participants are allowed to send. In that case,
the session bandwidth parameter is the product of the individual sender’s bandwidth times the
number of participants, and the RTCP bandwidth is 5% of that.

Details of the algorithm’s operation are given in the sections that follow. Appendix A.7 gives an
example implementation.

6.2.1 Maintaining the Number of Session Members

Calculation of the RTCP packet interval depends upon an estimate of the number of sites partic-
ipating in the session. New sites are added to the count when they are heard, and an entry for
each should be created in a table indexed by the SSRC or CSRC identi(cid:12)er (see Section 8.2) to
keep track of them. New entries may be considered not valid until multiple packets carrying the
new SSRC have been received (see Appendix A.1), or until an SDES RTCP packet containing a
CNAME for that SSRC has been received. Entries may be deleted from the table when an RTCP
BYE packet with the corresponding SSRC identi(cid:12)er is received, except that some straggler data
packets might arrive after the BYE and cause the entry to be recreated. Instead, the entry should
be marked as having received a BYE and then deleted after an appropriate delay.
A participant may mark another site inactive, or delete it if not yet valid, if no RTP or RTCP
packet has been received for a small number of RTCP report intervals (5 is recommended). This
provides some robustness against packet loss. All sites must have the same value for this multiplier
and must calculate roughly the same value for the RTCP report interval in order for this timeout
to work properly. Therefore, this multiplier should be (cid:12)xed for a particular pro(cid:12)le.

Schulzrinne, et al.

Standards Track

[Page 23]

RFC 3550

RTP

July 2003

For sessions with a very large number of participants, it may be impractical to maintain a table to
store the SSRC identi(cid:12)er and state information for all of them. An implementation may use SSRC
sampling, as described in [21], to reduce the storage requirements. An implementation may use
any other algorithm with similar performance. A key requirement is that any algorithm considered
should not substantially underestimate the group size, although it may overestimate.

6.3 RTCP Packet Send and Receive Rules

The rules for how to send, and what to do when receiving an RTCP packet are outlined here. An
implementation that allows operation in a multicast environment or a multipoint unicast environ-
ment must meet the requirements in Section 6.2. Such an implementation may use the algorithm
de(cid:12)ned in this section to meet those requirements, or may use some other algorithm so long as it
provides equivalent or better performance. An implementation which is constrained to two-party
unicast operation should still use randomization of the RTCP transmission interval to avoid un-
intended synchronization of multiple instances operating in the same environment, but may omit
the \timer reconsideration" and \reverse reconsideration" algorithms in Sections 6.3.3, 6.3.6 and
6.3.7.

To execute these rules, a session participant must maintain several pieces of state:

tp: the last time an RTCP packet was transmitted;

tc: the current time;

tn: the next scheduled transmission time of an RTCP packet;

pmembers: the estimated number of session members at the time tn was last recomputed;

members: the most current estimate for the number of session members;

senders: the most current estimate for the number of senders in the session;

rtcp bw: The target RTCP bandwidth, i.e., the total bandwidth that will be used for RTCP
packets by all members of this session, in octets per second. This will be a speci(cid:12)ed fraction
of the \session bandwidth" parameter supplied to the application at startup.

we sent: Flag that is true if the application has sent data since the 2nd previous RTCP report

was transmitted.

avg rtcp size: The average compound RTCP packet size, in octets, over all RTCP packets sent
and received by this participant. The size includes lower-layer transport and network protocol
headers (e.g., UDP and IP) as explained in Section 6.2.

initial: Flag that is true if the application has not yet sent an RTCP packet.

Many of these rules make use of the \calculated interval" between packet transmissions. This
interval is described in the following section.

Schulzrinne, et al.

Standards Track

[Page 24]

RFC 3550

RTP

July 2003

6.3.1 Computing the RTCP Transmission Interval

To maintain scalability, the average interval between packets from a session participant should scale
with the group size. This interval is called the calculated interval. It is obtained by combining
a number of the pieces of state described above. The calculated interval T is then determined as
follows:

1. If the number of senders is less than or equal to 25% of the membership (members), the interval
depends on whether the participant is a sender or not (based on the value of we sent). If the
participant is a sender (we sent true), the constant C is set to the average RTCP packet size
(avg rtcp size) divided by 25% of the RTCP bandwidth (rtcp bw), and the constant n is set
to the number of senders. If we sent is not true, the constant C is set to the average RTCP
packet size divided by 75% of the RTCP bandwidth. The constant n is set to the number of
receivers (members − senders). If the number of senders is greater than 25%, senders and
receivers are treated together. The constant C is set to the average RTCP packet size divided
by the total RTCP bandwidth and n is set to the total number of members. As stated in
Section 6.2, an RTP pro(cid:12)le may specify that the RTCP bandwidth may be explicitly de(cid:12)ned
by two separate parameters (call them S and R) for those participants which are senders and
those which are not. In that case, the 25% fraction becomes S/(S + R) and the 75% fraction
becomes R/(S + R). Note that if R is zero, the percentage of senders is never greater than
S/(S + R), and the implementation must avoid division by zero.

2. If the participant has not yet sent an RTCP packet (the variable initial is true), the constant

Tmin is set to 2.5 seconds, else it is set to 5 seconds.

3. The deterministic calculated interval Td is set to max(Tmin, n*C).

4. The calculated interval T is set to a number uniformly distributed between 0.5 and 1.5 times

the deterministic calculated interval.

5. The resulting value of T is divided by e − 3/2 = 1.21828 to compensate for the fact that
the timer reconsideration algorithm converges to a value of the RTCP bandwidth below the
intended average.

This procedure results in an interval which is random, but which, on average, gives at least 25% of
the RTCP bandwidth to senders and the rest to receivers. If the senders constitute more than one
quarter of the membership, this procedure splits the bandwidth equally among all participants, on
average.

6.3.2

Initialization

Upon joining the session, the participant initializes tp to 0, tc to 0, senders to 0, pmembers to 1,
members to 1, we sent to false, rtcp bw to the speci(cid:12)ed fraction of the session bandwidth, initial
to true, and avg rtcp size to the probable size of the (cid:12)rst RTCP packet that the application will
later construct. The calculated interval T is then computed, and the (cid:12)rst packet is scheduled for

Schulzrinne, et al.

Standards Track

[Page 25]

RFC 3550

RTP

July 2003

time tn = T. This means that a transmission timer is set which expires at time T. Note that an
application may use any desired approach for implementing this timer.

The participant adds its own SSRC to the member table.

6.3.3 Receiving an RTP or Non-BYE RTCP Packet

When an RTP or RTCP packet is received from a participant whose SSRC is not in the member
table, the SSRC is added to the table, and the value for members is updated once the participant
has been validated as described in Section 6.2.1. The same processing occurs for each CSRC in a
validated RTP packet.

When an RTP packet is received from a participant whose SSRC is not in the sender table, the
SSRC is added to the table, and the value for senders is updated.

For each compound RTCP packet received, the value of avg rtcp size is updated:

avg rtcp size = (1/16) * packet size + (15/16) * avg rtcp size

where packet size is the size of the RTCP packet just received.

6.3.4 Receiving an RTCP BYE Packet

Except as described in Section 6.3.7 for the case when an RTCP BYE is to be transmitted, if the
received packet is an RTCP BYE packet, the SSRC is checked against the member table. If present,
the entry is removed from the table, and the value for members is updated. The SSRC is then
checked against the sender table. If present, the entry is removed from the table, and the value for
senders is updated.

Furthermore, to make the transmission rate of RTCP packets more adaptive to changes in group
membership, the following \reverse reconsideration" algorithm should be executed when a BYE
packet is received that reduces members to a value less than pmembers:

(cid:15) The value for tn is updated according to the following formula:

tn = tc + (members/pmembers) * (tn - tc)

(cid:15) The value for tp is updated according the following formula:

tp = tc - (members/pmembers) * (tc - tp).

(cid:15) The next RTCP packet is rescheduled for transmission at time tn, which is now earlier.

(cid:15) The value of pmembers is set equal to members.

This algorithm does not prevent the group size estimate from incorrectly dropping to zero for a
short time due to premature timeouts when most participants of a large session leave at once but
some remain. The algorithm does make the estimate return to the correct value more rapidly.
This situation is unusual enough and the consequences are su(cid:14)ciently harmless that this problem
is deemed only a secondary concern.

Schulzrinne, et al.

Standards Track

[Page 26]

RFC 3550

RTP

July 2003

6.3.5 Timing Out an SSRC

At occasional intervals, the participant must check to see if any of the other participants time
out. To do this, the participant computes the deterministic (without the randomization factor)
calculated interval Td for a receiver, that is, with we sent false. Any other session member who has
not sent an RTP or RTCP packet since time tc - MTd (M is the timeout multiplier, and defaults
to 5) is timed out. This means that its SSRC is removed from the member list, and members is
updated. A similar check is performed on the sender list. Any member on the sender list who has
not sent an RTP packet since time tc - 2T (within the last two RTCP report intervals) is removed
from the sender list, and senders is updated.
If any members time out, the reverse reconsideration algorithm described in Section 6.3.4 should
be performed.
The participant must perform this check at least once per RTCP transmission interval.

6.3.6 Expiration of Transmission Timer

When the packet transmission timer expires, the participant performs the following operations:

(cid:15) The transmission interval T is computed as described in Section 6.3.1, including the random-

ization factor.

(cid:15) If tp + T is less than or equal to tc, an RTCP packet is transmitted. tp is set to tc, then
another value for T is calculated as in the previous step and tn is set to tc + T. The
transmission timer is set to expire again at time tn. If tp + T is greater than tc, tn is set to
tp + T. No RTCP packet is transmitted. The transmission timer is set to expire at time tn.

(cid:15) pmembers is set to members.

If an RTCP packet is transmitted, the value of initial is set to FALSE. Furthermore, the value of
avg rtcp size is updated:

avg rtcp size = (1/16) * packet size + (15/16) * avg rtcp size

where packet size is the size of the RTCP packet just transmitted.

6.3.7 Transmitting a BYE Packet

When a participant wishes to leave a session, a BYE packet is transmitted to inform the other
participants of the event. In order to avoid a ﬂood of BYE packets when many participants leave
the system, a participant must execute the following algorithm if the number of members is more
than 50 when the participant chooses to leave. This algorithm usurps the normal role of the
members variable to count BYE packets instead:

(cid:15) When the participant decides to leave the system, tp is reset to tc, the current time, members
and pmembers are initialized to 1, initial is set to 1, we sent is set to false, senders is set to

Schulzrinne, et al.

Standards Track

[Page 27]

RFC 3550

RTP

July 2003

0, and avg rtcp size is set to the size of the compound BYE packet. The calculated interval
T is computed. The BYE packet is then scheduled for time tn = tc + T.

(cid:15) Every time a BYE packet from another participant is received, members is incremented
by 1 regardless of whether that participant exists in the member table or not, and when
SSRC sampling is in use, regardless of whether or not the BYE SSRC would be included in
the sample. members is NOT incremented when other RTCP packets or RTP packets are
received, but only for BYE packets. Similarly, avg rtcp size is updated only for received BYE
packets. senders is NOT updated when RTP packets arrive; it remains 0.

(cid:15) Transmission of the BYE packet then follows the rules for transmitting a regular RTCP

packet, as above.

This allows BYE packets to be sent right away, yet controls their total bandwidth usage. In the
worst case, this could cause RTCP control packets to use twice the bandwidth as normal (10%) |
5% for non-BYE RTCP packets and 5% for BYE.

A participant that does not want to wait for the above mechanism to allow transmission of a BYE
packet may leave the group without sending a BYE at all. That participant will eventually be
timed out by the other group members.

If the group size estimate members is less than 50 when the participant decides to leave, the
participant may send a BYE packet immediately. Alternatively, the participant may choose to
execute the above BYE backo(cid:11) algorithm.
In either case, a participant which never sent an RTP or RTCP packet must not send a BYE
packet when they leave the group.

6.3.8 Updating we sent

The variable we sent contains true if the participant has sent an RTP packet recently, false other-
wise. This determination is made by using the same mechanisms as for managing the set of other
participants listed in the senders table. If the participant sends an RTP packet when we sent is
false, it adds itself to the sender table and sets we sent to true. The reverse reconsideration algo-
rithm described in Section 6.3.4 should be performed to possibly reduce the delay before sending
an SR packet. Every time another RTP packet is sent, the time of transmission of that packet is
maintained in the table. The normal sender timeout algorithm is then applied to the participant
| if an RTP packet has not been transmitted since time tc - 2T, the participant removes itself
from the sender table, decrements the sender count, and sets we sent to false.

6.3.9 Allocation of Source Description Bandwidth

This speci(cid:12)cation de(cid:12)nes several source description (SDES) items in addition to the mandatory
CNAME item, such as NAME (personal name) and EMAIL (email address). It also provides a
means to de(cid:12)ne new application-speci(cid:12)c RTCP packet types. Applications should exercise caution
in allocating control bandwidth to this additional information because it will slow down the rate at
which reception reports and CNAME are sent, thus impairing the performance of the protocol. It

Schulzrinne, et al.

Standards Track

[Page 28]

RFC 3550

RTP

July 2003

is recommended that no more than 20% of the RTCP bandwidth allocated to a single participant
be used to carry the additional information. Furthermore, it is not intended that all SDES items
will be included in every application. Those that are included should be assigned a fraction of
the bandwidth according to their utility. Rather than estimate these fractions dynamically, it is
recommended that the percentages be translated statically into report interval counts based on the
typical length of an item.

For example, an application may be designed to send only CNAME, NAME and EMAIL and not
any others. NAME might be given much higher priority than EMAIL because the NAME would be
displayed continuously in the application’s user interface, whereas EMAIL would be displayed only
when requested. At every RTCP interval, an RR packet and an SDES packet with the CNAME
item would be sent. For a small session operating at the minimum interval, that would be every 5
seconds on the average. Every third interval (15 seconds), one extra item would be included in the
SDES packet. Seven out of eight times this would be the NAME item, and every eighth time (2
minutes) it would be the EMAIL item.

When multiple applications operate in concert using cross-application binding through a common
CNAME for each participant, for example in a multimedia conference composed of an RTP session
for each medium, the additional SDES information may be sent in only one RTP session. The
other sessions would carry only the CNAME item. In particular, this approach should be applied
to the multiple sessions of a layered encoding scheme (see Section 2.4).

6.4 Sender and Receiver Reports

RTP receivers provide reception quality feedback using RTCP report packets which may take one
of two forms depending upon whether or not the receiver is also a sender. The only di(cid:11)erence
between the sender report (SR) and receiver report (RR) forms, besides the packet type code, is
that the sender report includes a 20-byte sender information section for use by active senders. The
SR is issued if a site has sent any data packets during the interval since issuing the last report or
the previous one, otherwise the RR is issued.

Both the SR and RR forms include zero or more reception report blocks, one for each of the
synchronization sources from which this receiver has received RTP data packets since the last
report. Reports are not issued for contributing sources listed in the CSRC list. Each reception
report block provides statistics about the data received from the particular source indicated in that
block. Since a maximum of 31 reception report blocks will (cid:12)t in an SR or RR packet, additional RR
packets should be stacked after the initial SR or RR packet as needed to contain the reception
reports for all sources heard during the interval since the last report. If there are too many sources
to (cid:12)t all the necessary RR packets into one compound RTCP packet without exceeding the MTU
of the network path, then only the subset that will (cid:12)t into one MTU should be included in each
interval. The subsets should be selected round-robin across multiple intervals so that all sources
are reported.

The next sections de(cid:12)ne the formats of the two reports, how they may be extended in a pro(cid:12)le-
speci(cid:12)c manner if an application requires additional feedback information, and how the reports
may be used. Details of reception reporting by translators and mixers is given in Section 7.

Schulzrinne, et al.

Standards Track

[Page 29]

RFC 3550

RTP

July 2003

6.4.1 SR: Sender Report RTCP Packet

|

3

1

2

RC

length

PT=SR=200

header |V=2|P|

sender |
info

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
SSRC of sender
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
|
NTP timestamp, most significant word
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
NTP timestamp, least significant word
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
RTP timestamp
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
sender’s packet count
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
sender’s octet count
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
report |
|
SSRC_1 (SSRC of first source)
block +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| fraction lost |
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
extended highest sequence number received
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
interarrival jitter
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
last SR (LSR)
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
delay since last SR (DLSR)
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
report |
|
SSRC_2 (SSRC of second source)
block +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
:
:
...
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
|
profile-specific extensions
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

cumulative number of packets lost

1

2

The sender report packet consists of three sections, possibly followed by a fourth pro(cid:12)le-speci(cid:12)c
extension section if de(cid:12)ned. The (cid:12)rst section, the header, is 8 octets long. The (cid:12)elds have the
following meaning:

version (V): 2 bits

Identi(cid:12)es the version of RTP, which is the same in RTCP packets as in RTP data packets.
The version de(cid:12)ned by this speci(cid:12)cation is two (2).

padding (P): 1 bit

If the padding bit is set, this individual RTCP packet contains some additional padding octets
at the end which are not part of the control information but are included in the length (cid:12)eld.
The last octet of the padding is a count of how many padding octets should be ignored,

Schulzrinne, et al.

Standards Track

[Page 30]

RFC 3550

RTP

July 2003

including itself (it will be a multiple of four). Padding may be needed by some encryption
algorithms with (cid:12)xed block sizes. In a compound RTCP packet, padding is only required on
one individual packet because the compound packet is encrypted as a whole for the method in
Section 9.1. Thus, padding must only be added to the last individual packet, and if padding
is added to that packet, the padding bit must be set only on that packet. This convention
aids the header validity checks described in Appendix A.2 and allows detection of packets
from some early implementations that incorrectly set the padding bit on the (cid:12)rst individual
packet and add padding to the last individual packet.

reception report count (RC): 5 bits

The number of reception report blocks contained in this packet. A value of zero is valid.

packet type (PT): 8 bits

Contains the constant 200 to identify this as an RTCP SR packet.

length: 16 bits

The length of this RTCP packet in 32-bit words minus one, including the header and any
padding. (The o(cid:11)set of one makes zero a valid length and avoids a possible in(cid:12)nite loop in
scanning a compound RTCP packet, while counting 32-bit words avoids a validity check for
a multiple of 4.)

SSRC: 32 bits

The synchronization source identi(cid:12)er for the originator of this SR packet.

The second section, the sender information, is 20 octets long and is present in every sender report
packet.
It summarizes the data transmissions from this sender. The (cid:12)elds have the following
meaning:

NTP timestamp: 64 bits

Indicates the wallclock time (see Section 4) when this report was sent so that it may be used
in combination with timestamps returned in reception reports from other receivers to measure
round-trip propagation to those receivers. Receivers should expect that the measurement ac-
curacy of the timestamp may be limited to far less than the resolution of the NTP timestamp.
The measurement uncertainty of the timestamp is not indicated as it may not be known. On
a system that has no notion of wallclock time but does have some system-speci(cid:12)c clock such
as \system uptime", a sender may use that clock as a reference to calculate relative NTP
timestamps. It is important to choose a commonly used clock so that if separate implementa-
tions are used to produce the individual streams of a multimedia session, all implementations
will use the same clock. Until the year 2036, relative and absolute timestamps will di(cid:11)er in
the high bit so (invalid) comparisons will show a large di(cid:11)erence; by then one hopes relative
timestamps will no longer be needed. A sender that has no notion of wallclock or elapsed
time may set the NTP timestamp to zero.

RTP timestamp: 32 bits

Corresponds to the same time as the NTP timestamp (above), but in the same units and
with the same random o(cid:11)set as the RTP timestamps in data packets. This correspondence
may be used for intra- and inter-media synchronization for sources whose NTP timestamps

Schulzrinne, et al.

Standards Track

[Page 31]

RFC 3550

RTP

July 2003

are synchronized, and may be used by media-independent receivers to estimate the nominal
RTP clock frequency. Note that in most cases this timestamp will not be equal to the RTP
timestamp in any adjacent data packet. Rather, it must be calculated from the corresponding
NTP timestamp using the relationship between the RTP timestamp counter and real time as
maintained by periodically checking the wallclock time at a sampling instant.

sender’s packet count: 32 bits

The total number of RTP data packets transmitted by the sender since starting transmission
up until the time this SR packet was generated. The count should be reset if the sender
changes its SSRC identi(cid:12)er.

sender’s octet count: 32 bits

The total number of payload octets (i.e., not including header or padding) transmitted in
RTP data packets by the sender since starting transmission up until the time this SR packet
was generated. The count should be reset if the sender changes its SSRC identi(cid:12)er. This
(cid:12)eld can be used to estimate the average payload data rate.

The third section contains zero or more reception report blocks depending on the number of other
sources heard by this sender since the last report. Each reception report block conveys statistics on
the reception of RTP packets from a single synchronization source. Receivers should not carry
over statistics when a source changes its SSRC identi(cid:12)er due to a collision. These statistics are:

SSRC n (source identiﬁer): 32 bits

The SSRC identi(cid:12)er of the source to which the information in this reception report block
pertains.

fraction lost: 8 bits

The fraction of RTP data packets from source SSRC n lost since the previous SR or RR packet
was sent, expressed as a (cid:12)xed point number with the binary point at the left edge of the (cid:12)eld.
(That is equivalent to taking the integer part after multiplying the loss fraction by 256.)
This fraction is de(cid:12)ned to be the number of packets lost divided by the number of packets
expected, as de(cid:12)ned in the next paragraph. An implementation is shown in Appendix A.3.
If the loss is negative due to duplicates, the fraction lost is set to zero. Note that a receiver
cannot tell whether any packets were lost after the last one received, and that there will be
no reception report block issued for a source if all packets from that source sent during the
last reporting interval have been lost.

cumulative number of packets lost: 24 bits

The total number of RTP data packets from source SSRC n that have been lost since the
beginning of reception. This number is de(cid:12)ned to be the number of packets expected less
the number of packets actually received, where the number of packets received includes any
which are late or duplicates. Thus, packets that arrive late are not counted as lost, and the
loss may be negative if there are duplicates. The number of packets expected is de(cid:12)ned to be
the extended last sequence number received, as de(cid:12)ned next, less the initial sequence number
received. This may be calculated as shown in Appendix A.3.

Schulzrinne, et al.

Standards Track

[Page 32]

RFC 3550

RTP

July 2003

extended highest sequence number received: 32 bits

The low 16 bits contain the highest sequence number received in an RTP data packet from
source SSRC n, and the most signi(cid:12)cant 16 bits extend that sequence number with the cor-
responding count of sequence number cycles, which may be maintained according to the al-
gorithm in Appendix A.1. Note that di(cid:11)erent receivers within the same session will generate
di(cid:11)erent extensions to the sequence number if their start times di(cid:11)er signi(cid:12)cantly.

interarrival jitter: 32 bits

An estimate of the statistical variance of the RTP data packet interarrival time, measured in
timestamp units and expressed as an unsigned integer. The interarrival jitter J is de(cid:12)ned to
be the mean deviation (smoothed absolute value) of the di(cid:11)erence D in packet spacing at the
receiver compared to the sender for a pair of packets. As shown in the equation below, this
is equivalent to the di(cid:11)erence in the \relative transit time" for the two packets; the relative
transit time is the di(cid:11)erence between a packet’s RTP timestamp and the receiver’s clock at
the time of arrival, measured in the same units.
If Si is the RTP timestamp from packet i, and Ri is the time of arrival in RTP timestamp
units for packet i, then for two packets i and j, D may be expressed as

D(i, j) = (Rj − Ri) − (Sj − Si) = (Rj − Sj) − (Ri − Si)

The interarrival jitter should be calculated continuously as each data packet i is received
from source SSRC n, using this di(cid:11)erence D for that packet and the previous packet i − 1 in
order of arrival (not necessarily in sequence), according to the formula

J(i) = J(i − 1) + (jD(i − 1, i)j − J(i − 1))/16

Whenever a reception report is issued, the current value of J is sampled.
The jitter calculation must conform to the formula speci(cid:12)ed here in order to allow pro(cid:12)le-
independent monitors to make valid interpretations of reports coming from di(cid:11)erent imple-
mentations. This algorithm is the optimal (cid:12)rst-order estimator and the gain parameter 1/16
gives a good noise reduction ratio while maintaining a reasonable rate of convergence [22,
Section 11.5-11.12, Fig. 11.6]. A sample implementation is shown in Appendix A.8. See
Section 6.4.4 for a discussion of the e(cid:11)ects of varying packet duration and delay before trans-
mission.

last SR timestamp (LSR): 32 bits

The middle 32 bits out of 64 in the NTP timestamp (as explained in Section 4) received as
part of the most recent RTCP sender report (SR) packet from source SSRC n. If no SR has
been received yet, the (cid:12)eld is set to zero.

delay since last SR (DLSR): 32 bits

The delay, expressed in units of 1/65536 seconds, between receiving the last SR packet from
source SSRC n and sending this reception report block. If no SR packet has been received
yet from SSRC n, the DLSR (cid:12)eld is set to zero.

Schulzrinne, et al.

Standards Track

[Page 33]

RFC 3550

RTP

July 2003

Let SSRC r denote the receiver issuing this receiver report. Source SSRC n can compute the
round-trip propagation delay to SSRC r by recording the time A when this reception report
block is received. It calculates the total round-trip time A−LSR using the last SR timestamp
(LSR) (cid:12)eld, and then subtracting this (cid:12)eld to leave the round-trip propagation delay as
(A − LSR − DLSR). This is illustrated in Fig. 2. Times are shown in both a hexadecimal
representation of the 32-bit (cid:12)elds and the equivalent ﬂoating-point decimal representation.
Colons indicate a 32-bit (cid:12)eld divided into a 16-bit integer part and 16-bit fraction part.

This may be used as an approximate measure of distance to cluster receivers, although some
links have very asymmetric delays.

[10 Nov 1995 11:33:25.125 UTC] [10 Nov 1995 11:33:36.5 UTC]

n

SR(n)

A=0xb710:8000 (46864.500 s)

ntp_sec =0xb44db705
ntp_frac=0x20000000

(3024992005.125 s)

dlsr=0x0005:4000 (    5.250 s)
lsr =0xb705:2000 (46853.125 s)

r

RR(n)

DLSR
(5.25 s)

A     0xb710:8000 (46864.500 s)
DLSR -0x0005:4000 (    5.250 s)
LSR  -0xb705:2000 (46853.125 s)

delay 0x0006:2000 (    6.125 s)

Figure 2: Example for round-trip time computation

Schulzrinne, et al.

Standards Track

[Page 34]

RFC 3550

RTP

July 2003

6.4.2 RR: Receiver Report RTCP Packet

2

3

1

|

1

RC

length

PT=RR=201

header |V=2|P|

cumulative number of packets lost

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
SSRC of packet sender
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
report |
|
SSRC_1 (SSRC of first source)
block +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| fraction lost |
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
extended highest sequence number received
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
interarrival jitter
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
last SR (LSR)
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
delay since last SR (DLSR)
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
report |
|
SSRC_2 (SSRC of second source)
block +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
:
:
...
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
|
|
profile-specific extensions
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

2

The format of the receiver report (RR) packet is the same as that of the SR packet except that the
packet type (cid:12)eld contains the constant 201 and the (cid:12)ve words of sender information are omitted
(these are the NTP and RTP timestamps and sender’s packet and octet counts). The remaining
(cid:12)elds have the same meaning as for the SR packet.
An empty RR packet (RC = 0) must be put at the head of a compound RTCP packet when there
is no data transmission or reception to report.

6.4.3 Extending the Sender and Receiver Reports

A pro(cid:12)le should de(cid:12)ne pro(cid:12)le-speci(cid:12)c extensions to the sender report and receiver report if there
is additional information that needs to be reported regularly about the sender or receivers. This
method should be used in preference to de(cid:12)ning another RTCP packet type because it requires
less overhead:

(cid:15) fewer octets in the packet (no RTCP header or SSRC (cid:12)eld);

(cid:15) simpler and faster parsing because applications running under that pro(cid:12)le would be pro-
grammed to always expect the extension (cid:12)elds in the directly accessible location after the

Schulzrinne, et al.

Standards Track

[Page 35]

RFC 3550

RTP

July 2003

reception reports.

The extension is a fourth section in the sender- or receiver-report packet which comes at the end
after the reception report blocks, if any. If additional sender information is required, then for sender
reports it would be included (cid:12)rst in the extension section, but for receiver reports it would not be
If information about receivers is to be included, that data should be structured as
present.
an array of blocks parallel to the existing array of reception report blocks; that is, the number of
blocks would be indicated by the RC (cid:12)eld.

6.4.4 Analyzing Sender and Receiver Reports

It is expected that reception quality feedback will be useful not only for the sender but also for other
receivers and third-party monitors. The sender may modify its transmissions based on the feedback;
receivers can determine whether problems are local, regional or global; network managers may use
pro(cid:12)le-independent monitors that receive only the RTCP packets and not the corresponding RTP
data packets to evaluate the performance of their networks for multicast distribution.

Cumulative counts are used in both the sender information and receiver report blocks so that
di(cid:11)erences may be calculated between any two reports to make measurements over both short and
long time periods, and to provide resilience against the loss of a report. The di(cid:11)erence between
the last two reports received can be used to estimate the recent quality of the distribution. The
NTP timestamp is included so that rates may be calculated from these di(cid:11)erences over the interval
between two reports. Since that timestamp is independent of the clock rate for the data encoding,
it is possible to implement encoding- and pro(cid:12)le-independent quality monitors.

An example calculation is the packet loss rate over the interval between two reception reports. The
di(cid:11)erence in the cumulative number of packets lost gives the number lost during that interval. The
di(cid:11)erence in the extended last sequence numbers received gives the number of packets expected
during the interval. The ratio of these two is the packet loss fraction over the interval. This
ratio should equal the fraction lost (cid:12)eld if the two reports are consecutive, but otherwise it may
not. The loss rate per second can be obtained by dividing the loss fraction by the di(cid:11)erence in
NTP timestamps, expressed in seconds. The number of packets received is the number of packets
expected minus the number lost. The number of packets expected may also be used to judge the
statistical validity of any loss estimates. For example, 1 out of 5 packets lost has a lower signi(cid:12)cance
than 200 out of 1000.

From the sender information, a third-party monitor can calculate the average payload data rate
and the average packet rate over an interval without receiving the data. Taking the ratio of the
two gives the average payload size. If it can be assumed that packet loss is independent of packet
size, then the number of packets received by a particular receiver times the average payload size
(or the corresponding packet size) gives the apparent throughput available to that receiver.

In addition to the cumulative counts which allow long-term packet loss measurements using dif-
ferences between reports, the fraction lost (cid:12)eld provides a short-term measurement from a single
report. This becomes more important as the size of a session scales up enough that reception state
information might not be kept for all receivers or the interval between reports becomes long enough
that only one report might have been received from a particular receiver.

Schulzrinne, et al.

Standards Track

[Page 36]

RFC 3550

RTP

July 2003

The interarrival jitter (cid:12)eld provides a second short-term measure of network congestion. Packet
loss tracks persistent congestion while the jitter measure tracks transient congestion. The jitter
measure may indicate congestion before it leads to packet loss. The interarrival jitter (cid:12)eld is only
a snapshot of the jitter at the time of a report and is not intended to be taken quantitatively.
Rather, it is intended for comparison across a number of reports from one receiver over time or
from multiple receivers, e.g., within a single network, at the same time. To allow comparison across
receivers, it is important the the jitter be calculated according to the same formula by all receivers.

Because the jitter calculation is based on the RTP timestamp which represents the instant when
the (cid:12)rst data in the packet was sampled, any variation in the delay between that sampling instant
and the time the packet is transmitted will a(cid:11)ect the resulting jitter that is calculated. Such a
variation in delay would occur for audio packets of varying duration. It will also occur for video
encodings because the timestamp is the same for all the packets of one frame but those packets
are not all transmitted at the same time. The variation in delay until transmission does reduce
the accuracy of the jitter calculation as a measure of the behavior of the network by itself, but
it is appropriate to include considering that the receiver bu(cid:11)er must accommodate it. When the
jitter calculation is used as a comparative measure, the (constant) component due to variation in
delay until transmission subtracts out so that a change in the network jitter component can then be
observed unless it is relatively small. If the change is small, then it is likely to be inconsequential.

6.5 SDES: Source Description RTCP Packet

header |V=2|P|

chunk |

1

2

chunk |

|

3

1

2

SC

length

PT=SDES=202 |

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
|
SSRC/CSRC_1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
SDES items
|
|
|
...
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
|
SSRC/CSRC_2
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
SDES items
|
|
|
...
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

The SDES packet is a three-level structure composed of a header and zero or more chunks, each of
which is composed of items describing the source identi(cid:12)ed in that chunk. The items are described
individually in subsequent sections.

version (V), padding (P), length:

As described for the SR packet (see Section 6.4.1).

packet type (PT): 8 bits

Contains the constant 202 to identify this as an RTCP SDES packet.

Schulzrinne, et al.

Standards Track

[Page 37]

RFC 3550

RTP

July 2003

source count (SC): 5 bits

The number of SSRC/CSRC chunks contained in this SDES packet. A value of zero is valid
but useless.

Each chunk consists of an SSRC/CSRC identi(cid:12)er followed by a list of zero or more items, which
carry information about the SSRC/CSRC. Each chunk starts on a 32-bit boundary. Each item
consists of an 8-bit type (cid:12)eld, an 8-bit octet count describing the length of the text (thus, not
including this two-octet header), and the text itself. Note that the text can be no longer than 255
octets, but this is consistent with the need to limit RTCP bandwidth consumption.

The text is encoded according to the UTF-8 encoding speci(cid:12)ed in RFC 2279 [5]. US-ASCII is a
subset of this encoding and requires no additional encoding. The presence of multi-octet encodings
is indicated by setting the most signi(cid:12)cant bit of a character to a value of one.

Items are contiguous, i.e., items are not individually padded to a 32-bit boundary. Text is not
null terminated because some multi-octet encodings include null octets. The list of items in each
chunk must be terminated by one or more null octets, the (cid:12)rst of which is interpreted as an item
type of zero to denote the end of the list. No length octet follows the null item type octet, but
additional null octets must be included if needed to pad until the next 32-bit boundary. Note that
this padding is separate from that indicated by the P bit in the RTCP header. A chunk with zero
items (four null octets) is valid but useless.

End systems send one SDES packet containing their own source identi(cid:12)er (the same as the SSRC in
the (cid:12)xed RTP header). A mixer sends one SDES packet containing a chunk for each contributing
source from which it is receiving SDES information, or multiple complete SDES packets in the
format above if there are more than 31 such sources (see Section 7).

The SDES items currently de(cid:12)ned are described in the next sections. Only the CNAME item is
mandatory. Some items shown here may be useful only for particular pro(cid:12)les, but the item types
are all assigned from one common space to promote shared use and to simplify pro(cid:12)le-independent
applications. Additional items may be de(cid:12)ned in a pro(cid:12)le by registering the type numbers with
IANA as described in Section 15.

6.5.1 CNAME: Canonical End-Point Identiﬁer SDES Item

1

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

| user and domain name

CNAME=1

length

|

3

2

The CNAME identi(cid:12)er has the following properties:

(cid:15) Because the randomly allocated SSRC identi(cid:12)er may change if a conﬂict is discovered or if a
program is restarted, the CNAME item must be included to provide the binding from the
SSRC identi(cid:12)er to an identi(cid:12)er for the source (sender or receiver) that remains constant.

(cid:15) Like the SSRC identi(cid:12)er, the CNAME identi(cid:12)er should also be unique among all participants

within one RTP session.

Schulzrinne, et al.

Standards Track

[Page 38]

RFC 3550

RTP

July 2003

(cid:15) To provide a binding across multiple media tools used by one participant in a set of related

RTP sessions, the CNAME should be (cid:12)xed for that participant.

(cid:15) To facilitate third-party monitoring, the CNAME should be suitable for either a program

or a person to locate the source.

Therefore, the CNAME should be derived algorithmically and not entered manually, when possi-
ble. To meet these requirements, the following format should be used unless a pro(cid:12)le speci(cid:12)es an
alternate syntax or semantics. The CNAME item should have the format \user@host", or \host"
if a user name is not available as on single-user systems. For both formats, \host" is either the fully
quali(cid:12)ed domain name of the host from which the real-time data originates, formatted according to
the rules speci(cid:12)ed in RFC 1034 [6], RFC 1035 [7] and Section 2.1 of RFC 1123 [8]; or the standard
ASCII representation of the host’s numeric address on the interface used for the RTP communi-
cation. For example, the standard ASCII representation of an IP Version 4 address is \dotted
decimal", also known as dotted quad, and for IP Version 6, addresses are textually represented as
groups of hexadecimal digits separated by colons (with variations as detailed in RFC 3513 [23]).
Other address types are expected to have ASCII representations that are mutually unique. The
fully quali(cid:12)ed domain name is more convenient for a human observer and may avoid the need to
send a NAME item in addition, but it may be di(cid:14)cult or impossible to obtain reliably in some op-
erating environments. Applications that may be run in such environments should use the ASCII
representation of the address instead.

Examples are \doe@sleepy.example.com", \doe@192.0.2.89" or \doe@2201:056D::112E:144A:1E24"
for a multi-user system. On a system with no user name, examples would be \sleepy.example.com",
\192.0.2.89" or \2201:056D::112E:144A:1E24".
The user name should be in a form that a program such as \(cid:12)nger" or \talk" could use, i.e.,
it typically is the login name rather than the personal name. The host name is not necessarily
identical to the one in the participant’s electronic mail address.

This syntax will not provide unique identi(cid:12)ers for each source if an application permits a user to
generate multiple sources from one host. Such an application would have to rely on the SSRC
to further identify the source, or the pro(cid:12)le for that application would have to specify additional
syntax for the CNAME identi(cid:12)er.

If each application creates its CNAME independently, the resulting CNAMEs may not be identical
as would be required to provide a binding across multiple media tools belonging to one participant
in a set of related RTP sessions. If cross-media binding is required, it may be necessary for the
CNAME of each tool to be externally con(cid:12)gured with the same value by a coordination tool.

Application writers should be aware that private network address assignments such as the Net-
10 assignment proposed in RFC 1918 [24] may create network addresses that are not globally
unique. This would lead to non-unique CNAMEs if hosts with private addresses and no direct
IP connectivity to the public Internet have their RTP packets forwarded to the public Internet
through an RTP-level translator. (See also RFC 1627 [25].) To handle this case, applications may
provide a means to con(cid:12)gure a unique CNAME, but the burden is on the translator to translate
CNAMEs from private addresses to public addresses if necessary to keep private addresses from

Schulzrinne, et al.

Standards Track

[Page 39]

RFC 3550

RTP

July 2003

being exposed.

6.5.2 NAME: User Name SDES Item

1

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
...
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

| common name of source

length

NAME=2

|

3

2

This is the real name used to describe the source, e.g., \John Doe, Bit Recycler". It may be in
any form desired by the user. For applications such as conferencing, this form of name may be the
most desirable for display in participant lists, and therefore might be sent most frequently of those
items other than CNAME. Pro(cid:12)les may establish such priorities. The NAME value is expected to
remain constant at least for the duration of a session. It should NOT be relied upon to be unique
among all participants in the session.

6.5.3 EMAIL: Electronic Mail Address SDES Item

1

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

| email address of source

EMAIL=3

length

2

|

3

The email address is formatted according to RFC 2822 [9], for example, \John.Doe@example.com".
The EMAIL value is expected to remain constant for the duration of a session.

6.5.4 PHONE: Phone Number SDES Item

1

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

| phone number of source

PHONE=4

length

|

2

3

The phone number should be formatted with the plus sign replacing the international access code.
For example, \+1 908 555 1212" for a number in the United States.

Schulzrinne, et al.

Standards Track

[Page 40]

RFC 3550

RTP

July 2003

6.5.5 LOC: Geographic User Location SDES Item

1

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| geographic location of site ...
|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

length

LOC=5

|

3

2

Depending on the application, di(cid:11)erent degrees of detail are appropriate for this item. For confer-
ence applications, a string like \Murray Hill, New Jersey" may be su(cid:14)cient, while, for an active
badge system, strings like \Room 2A244, AT&T BL MH" might be appropriate. The degree of
detail is left to the implementation and/or user, but format and content may be prescribed by a
pro(cid:12)le. The LOC value is expected to remain constant for the duration of a session, except for
mobile hosts.

6.5.6 TOOL: Application or Tool Name SDES Item

1

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|name/version of source appl. ...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

length

TOOL=6

3

2

|

A string giving the name and possibly version of the application generating the stream, e.g.,
\videotool 1.2". This information may be useful for debugging purposes and is similar to the
Mailer or Mail-System-Version SMTP headers. The TOOL value is expected to remain constant
for the duration of the session.

6.5.7 NOTE: Notice/Status SDES Item

1

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

| note about the source

length

NOTE=7

|

3

2

The following semantics are suggested for this item, but these or other semantics may be explicitly
de(cid:12)ned by a pro(cid:12)le. The NOTE item is intended for transient messages describing the current
state of the source, e.g., \on the phone, can’t talk". Or, during a seminar, this item might be
used to convey the title of the talk. It should be used only to carry exceptional information and
should NOT be included routinely by all participants because this would slow down the rate at
which reception reports and CNAME are sent, thus impairing the performance of the protocol. In
particular, it should NOT be included as an item in a user’s con(cid:12)guration (cid:12)le nor automatically

Schulzrinne, et al.

Standards Track

[Page 41]

RFC 3550

RTP

July 2003

generated as in a quote-of-the-day.

Since the NOTE item may be important to display while it is active, the rate at which other
non-CNAME items such as NAME are transmitted might be reduced so that the NOTE item can
take that part of the RTCP bandwidth. When the transient message becomes inactive, the NOTE
item should continue to be transmitted a few times at the same repetition rate but with a string
of length zero to signal the receivers. However, receivers should also consider the NOTE item
inactive if it is not received for a small multiple of the repetition rate, or perhaps 20-30 RTCP
intervals.

6.5.8 PRIV: Private Extensions SDES Item

1

2

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
| prefix length |prefix string...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
...
...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

value string

length

PRIV=8

3

|

|

This item is used to de(cid:12)ne experimental or application-speci(cid:12)c SDES extensions. The item contains
a pre(cid:12)x consisting of a length-string pair, followed by the value string (cid:12)lling the remainder of the
item and carrying the desired information. The pre(cid:12)x length (cid:12)eld is 8 bits long. The pre(cid:12)x string
is a name chosen by the person de(cid:12)ning the PRIV item to be unique with respect to other PRIV
items this application might receive. The application creator might choose to use the application
name plus an additional subtype identi(cid:12)cation if needed. Alternatively, it is recommended that
others choose a name based on the entity they represent, then coordinate the use of the name
within that entity.

Note that the pre(cid:12)x consumes some space within the item’s total length of 255 octets, so the pre(cid:12)x
should be kept as short as possible. This facility and the constrained RTCP bandwidth should
NOT be overloaded; it is not intended to satisfy all the control communication requirements of all
applications.

SDES PRIV pre(cid:12)xes will not be registered by IANA. If some form of the PRIV item proves to be
of general utility, it should instead be assigned a regular SDES item type registered with IANA
so that no pre(cid:12)x is required. This simpli(cid:12)es use and increases transmission e(cid:14)ciency.

Schulzrinne, et al.

Standards Track

[Page 42]

RFC 3550

RTP

July 2003

6.6 BYE: Goodbye RTCP Packet

3

1

|

2

SC

PT=BYE=203 |

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|V=2|P|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
SSRC/CSRC
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
:
:
...
+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

reason for leaving

length

length

|

(opt) |

The BYE packet indicates that one or more sources are no longer active.

version (V), padding (P), length:

As described for the SR packet (see Section 6.4.1).

packet type (PT): 8 bits

Contains the constant 203 to identify this as an RTCP BYE packet.

source count (SC): 5 bits

The number of SSRC/CSRC identi(cid:12)ers included in this BYE packet. A count value of zero
is valid, but useless.

The rules for when a BYE packet should be sent are speci(cid:12)ed in Sections 6.3.7 and 8.2.
If a BYE packet is received by a mixer, the mixer should forward the BYE packet with the
SSRC/CSRC identi(cid:12)er(s) unchanged. If a mixer shuts down, it should send a BYE packet listing
all contributing sources it handles, as well as its own SSRC identi(cid:12)er. Optionally, the BYE packet
may include an 8-bit octet count followed by that many octets of text indicating the reason for
leaving, e.g., \camera malfunction" or \RTP loop detected". The string has the same encoding as
that described for SDES. If the string (cid:12)lls the packet to the next 32-bit boundary, the string is
not null terminated. If not, the BYE packet must be padded with null octets to the next 32-bit
boundary. This padding is separate from that indicated by the P bit in the RTCP header.

Schulzrinne, et al.

Standards Track

[Page 43]

RFC 3550

RTP

July 2003

6.7 APP: Application-Deﬁned RTCP Packet

2

3

1

PT=APP=204 |

0
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|V=2|P| subtype |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
SSRC/CSRC
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
|
name (ASCII)
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|
...
application-dependent data
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

length

The APP packet is intended for experimental use as new applications and new features are de-
veloped, without requiring packet type value registration. APP packets with unrecognized names
should be ignored. After testing and if wider use is justi(cid:12)ed, it is recommended that each APP
packet be rede(cid:12)ned without the subtype and name (cid:12)elds and registered with IANA using an RTCP
packet type.

version (V), padding (P), length:

As described for the SR packet (see Section 6.4.1).

subtype: 5 bits

May be used as a subtype to allow a set of APP packets to be de(cid:12)ned under one unique name,
or for any application-dependent data.

packet type (PT): 8 bits

Contains the constant 204 to identify this as an RTCP APP packet.

name: 4 octets

A name chosen by the person de(cid:12)ning the set of APP packets to be unique with respect to
other APP packets this application might receive. The application creator might choose to
use the application name, and then coordinate the allocation of subtype values to others who
want to de(cid:12)ne new packet types for the application. Alternatively, it is recommended that
others choose a name based on the entity they represent, then coordinate the use of the name
within that entity. The name is interpreted as a sequence of four ASCII characters, with
uppercase and lowercase characters treated as distinct.

application-dependent data: variable length

Application-dependent data may or may not appear in an APP packet. It is interpreted by
the application and not RTP itself. It must be a multiple of 32 bits long.

Schulzrinne, et al.

Standards Track

[Page 44]

RFC 3550

RTP

July 2003

7. RTP Translators and Mixers

In addition to end systems, RTP supports the notion of \translators" and \mixers", which could
be considered as \intermediate systems" at the RTP level. Although this support adds some
complexity to the protocol, the need for these functions has been clearly established by experiments
with multicast audio and video applications in the Internet. Example uses of translators and mixers
given in Section 2.3 stem from the presence of (cid:12)rewalls and low bandwidth connections, both of
which are likely to remain.

7.1 General Description

An RTP translator/mixer connects two or more transport-level \clouds". Typically, each cloud is
de(cid:12)ned by a common network and transport protocol (e.g., IP/UDP) plus a multicast address and
transport level destination port or a pair of unicast addresses and ports.
(Network-level protocol
translators, such as IP version 4 to IP version 6, may be present within a cloud invisibly to RTP.)
One system may serve as a translator or mixer for a number of RTP sessions, but each is considered
a logically separate entity.
In order to avoid creating a loop when a translator or mixer is installed, the following rules must
be observed:

(cid:15) Each of the clouds connected by translators and mixers participating in one RTP session
either must be distinct from all the others in at least one of these parameters (protocol,
address, port), or must be isolated at the network level from the others.

(cid:15) A derivative of the (cid:12)rst rule is that there must not be multiple translators or mixers con-
nected in parallel unless by some arrangement they partition the set of sources to be forwarded.

Similarly, all RTP end systems that can communicate through one or more RTP translators or
mixers share the same SSRC space, that is, the SSRC identi(cid:12)ers must be unique among all these
end systems. Section 8.2 describes the collision resolution algorithm by which SSRC identi(cid:12)ers are
kept unique and loops are detected.

There may be many varieties of translators and mixers designed for di(cid:11)erent purposes and appli-
cations. Some examples are to add or remove encryption, change the encoding of the data or the
underlying protocols, or replicate between a multicast address and one or more unicast addresses.
The distinction between translators and mixers is that a translator passes through the data streams
from di(cid:11)erent sources separately, whereas a mixer combines them to form one new stream:

Translator: Forwards RTP packets with their SSRC identi(cid:12)er intact; this makes it possible for
receivers to identify individual sources even though packets from all the sources pass through
the same translator and carry the translator’s network source address. Some kinds of trans-
lators will pass through the data untouched, but others may change the encoding of the data
and thus the RTP data payload type and timestamp. If multiple data packets are re-encoded
into one, or vice versa, a translator must assign new sequence numbers to the outgoing pack-
ets. Losses in the incoming packet stream may induce corresponding gaps in the outgoing

Schulzrinne, et al.

Standards Track

[Page 45]

RFC 3550

RTP

July 2003

sequence numbers. Receivers cannot detect the presence of a translator unless they know by
some other means what payload type or transport address was used by the original source.

Mixer: Receives streams of RTP data packets from one or more sources, possibly changes the data
format, combines the streams in some manner and then forwards the combined stream. Since
the timing among multiple input sources will not generally be synchronized, the mixer will
make timing adjustments among the streams and generate its own timing for the combined
stream, so it is the synchronization source. Thus, all data packets forwarded by a mixer
must be marked with the mixer’s own SSRC identi(cid:12)er. In order to preserve the identity of
the original sources contributing to the mixed packet, the mixer should insert their SSRC
identi(cid:12)ers into the CSRC identi(cid:12)er list following the (cid:12)xed RTP header of the packet. A mixer
that is also itself a contributing source for some packet should explicitly include its own
SSRC identi(cid:12)er in the CSRC list for that packet.
For some applications, it may be acceptable for a mixer not to identify sources in the CSRC
list. However, this introduces the danger that loops involving those sources could not be
detected.

The advantage of a mixer over a translator for applications like audio is that the output bandwidth
is limited to that of one source even when multiple sources are active on the input side. This
may be important for low-bandwidth links. The disadvantage is that receivers on the output side
don’t have any control over which sources are passed through or muted, unless some mechanism is
implemented for remote control of the mixer. The regeneration of synchronization information by
mixers also means that receivers can’t do inter-media synchronization of the original streams. A
multi-media mixer could do it.

A collection of mixers and translators is shown in Fig. 3 to illustrate their e(cid:11)ect on SSRC and
CSRC identi(cid:12)ers. In the (cid:12)gure, end systems are shown as rectangles (named E), translators as
triangles (named T) and mixers as ovals (named M). The notation \M1: 48(1,17)" designates a
packet originating a mixer M1, identi(cid:12)ed by M1’s (random) SSRC value of 48 and two CSRC
identi(cid:12)ers, 1 and 17, copied from the SSRC identi(cid:12)ers of packets from E1 and E2.

7.2 RTCP Processing in Translators

In addition to forwarding data packets, perhaps modi(cid:12)ed, translators and mixers must also process
RTCP packets. In many cases, they will take apart the compound RTCP packets received from
end systems to aggregate SDES information and to modify the SR or RR packets. Retransmission
of this information may be triggered by the packet arrival or by the RTCP interval timer of the
translator or mixer itself.

A translator that does not modify the data packets, for example one that just replicates between a
multicast address and a unicast address, may simply forward RTCP packets unmodi(cid:12)ed as well. A
translator that transforms the payload in some way must make corresponding transformations in
the SR and RR information so that it still reﬂects the characteristics of the data and the reception
quality. These translators must not simply forward RTCP packets.
In general, a translator
should not aggregate SR and RR packets from di(cid:11)erent sources into one packet since that would
reduce the accuracy of the propagation delay measurements based on the LSR and DLSR (cid:12)elds.

Schulzrinne, et al.

Standards Track

[Page 46]

RFC 3550

end system

E1

E1:17

RTP

July 2003

E6

E6:15

translator

M1:48(1,17)

M1

mixer

T1

M1: 48(1,17)
E4:47

T2

E6:15
M1:48(1,17)
E4:47
M3:89(64,45)

E7

E2:1

E4:47

E2

E3

E3:64

E4

M2

M3: 89(64,45)

M2:12(64)

M3

Legend:

source: SSRC (CSRC,...)

E5:45

E5

Figure 3: Sample RTP network with end systems, mixers and translators

SR sender information: A translator does not generate its own sender information, but forwards
the SR packets received from one cloud to the others. The SSRC is left intact but the sender
information must be modi(cid:12)ed if required by the translation. If a translator changes the data
encoding, it must change the \sender’s byte count" (cid:12)eld. If it also combines several data
packets into one output packet, it must change the \sender’s packet count" (cid:12)eld. If it changes
the timestamp frequency, it must change the \RTP timestamp" (cid:12)eld in the SR packet.

SR/RR reception report blocks: A translator forwards reception reports received from one
cloud to the others. Note that these ﬂow in the direction opposite to the data. The SSRC is
left intact. If a translator combines several data packets into one output packet, and therefore
changes the sequence numbers, it must make the inverse manipulation for the packet loss
(cid:12)elds and the \extended last sequence number" (cid:12)eld. This may be complex. In the extreme
case, there may be no meaningful way to translate the reception reports, so the translator
may pass on no reception report at all or a synthetic report based on its own reception. The
general rule is to do what makes sense for a particular translation.
A translator does not require an SSRC identi(cid:12)er of its own, but may choose to allocate one
for the purpose of sending reports about what it has received. These would be sent to all the
connected clouds, each corresponding to the translation of the data stream as sent to that
cloud, since reception reports are normally multicast to all participants.

SDES: Translators typically forward without change the SDES information they receive from one

Schulzrinne, et al.

Standards Track

[Page 47]

RFC 3550

RTP

July 2003

cloud to the others, but may, for example, decide to (cid:12)lter non-CNAME SDES information
if bandwidth is limited. The CNAMEs must be forwarded to allow SSRC identi(cid:12)er collision
detection to work. A translator that generates its own RR packets must send SDES CNAME
information about itself to the same clouds that it sends those RR packets.

BYE: Translators forward BYE packets unchanged. A translator that is about to cease forward-
ing packets should send a BYE packet to each connected cloud containing all the SSRC
identi(cid:12)ers that were previously being forwarded to that cloud, including the translator’s own
SSRC identi(cid:12)er if it sent reports of its own.

APP: Translators forward APP packets unchanged.

7.3 RTCP Processing in Mixers

Since a mixer generates a new data stream of its own, it does not pass through SR or RR packets
at all and instead generates new information for both sides.

SR sender information: A mixer does not pass through sender information from the sources it
mixes because the characteristics of the source streams are lost in the mix. As a synchroniza-
tion source, the mixer should generate its own SR packets with sender information about
the mixed data stream and send them in the same direction as the mixed stream.

SR/RR reception report blocks: A mixer generates its own reception reports for sources in
each cloud and sends them out only to the same cloud. It must not send these reception
reports to the other clouds and must not forward reception reports from one cloud to the
others because the sources would not be SSRCs there (only CSRCs).

SDES: Mixers typically forward without change the SDES information they receive from one
cloud to the others, but may, for example, decide to (cid:12)lter non-CNAME SDES information
if bandwidth is limited. The CNAMEs must be forwarded to allow SSRC identi(cid:12)er collision
detection to work. (An identi(cid:12)er in a CSRC list generated by a mixer might collide with an
SSRC identi(cid:12)er generated by an end system.) A mixer must send SDES CNAME information
about itself to the same clouds that it sends SR or RR packets.

Since mixers do not forward SR or RR packets, they will typically be extracting SDES packets
from a compound RTCP packet. To minimize overhead, chunks from the SDES packets may
be aggregated into a single SDES packet which is then stacked on an SR or RR packet
originating from the mixer. A mixer which aggregates SDES packets will use more RTCP
bandwidth than an individual source because the compound packets will be longer, but that
is appropriate since the mixer represents multiple sources. Similarly, a mixer which passes
through SDES packets as they are received will be transmitting RTCP packets at higher than
the single source rate, but again that is correct since the packets come from multiple sources.
The RTCP packet rate may be di(cid:11)erent on each side of the mixer.
A mixer that does not insert CSRC identi(cid:12)ers may also refrain from forwarding SDES
CNAMEs. In this case, the SSRC identi(cid:12)er spaces in the two clouds are independent. As
mentioned earlier, this mode of operation creates a danger that loops can’t be detected.

Schulzrinne, et al.

Standards Track

[Page 48]

RFC 3550

RTP

July 2003

BYE: Mixers must forward BYE packets. A mixer that is about to cease forwarding packets
should send a BYE packet to each connected cloud containing all the SSRC identi(cid:12)ers that
were previously being forwarded to that cloud, including the mixer’s own SSRC identi(cid:12)er if
it sent reports of its own.

APP: The treatment of APP packets by mixers is application-speci(cid:12)c.

7.4 Cascaded Mixers

An RTP session may involve a collection of mixers and translators as shown in Fig. 3. If two mixers
are cascaded, such as M2 and M3 in the (cid:12)gure, packets received by a mixer may already have been
mixed and may include a CSRC list with multiple identi(cid:12)ers. The second mixer should build the
CSRC list for the outgoing packet using the CSRC identi(cid:12)ers from already-mixed input packets and
the SSRC identi(cid:12)ers from unmixed input packets. This is shown in the output arc from mixer M3
labeled M3:89(64,45) in the (cid:12)gure. As in the case of mixers that are not cascaded, if the resulting
CSRC list has more than 15 identi(cid:12)ers, the remainder cannot be included.

8. SSRC Identiﬁer Allocation and Use

The SSRC identi(cid:12)er carried in the RTP header and in various (cid:12)elds of RTCP packets is a random
32-bit number that is required to be globally unique within an RTP session. It is crucial that the
number be chosen with care in order that participants on the same network or starting at the same
time are not likely to choose the same number.

It is not su(cid:14)cient to use the local network address (such as an IPv4 address) for the identi(cid:12)er
because the address may not be unique. Since RTP translators and mixers enable interoperation
among multiple networks with di(cid:11)erent address spaces, the allocation patterns for addresses within
two spaces might result in a much higher rate of collision than would occur with random allocation.
Multiple sources running on one host would also conﬂict.

It is also not su(cid:14)cient to obtain an SSRC identi(cid:12)er simply by calling random() without care-
fully initializing the state. An example of how to generate a random identi(cid:12)er is presented in
Appendix A.6.

8.1 Probability of Collision

Since the identi(cid:12)ers are chosen randomly, it is possible that two or more sources will choose the same
number. Collision occurs with the highest probability when all sources are started simultaneously,
for example when triggered automatically by some session management event. If N is the number
of sources and L the length of the identi(cid:12)er (here, 32 bits), the probability that two sources
independently pick the same value can be approximated for large N [26, p. 33] as 1 − e−N 2/2L+1
.
For N = 1000, the probability is roughly 10−4.

The typical collision probability is much lower than the worst-case above. When one new source
joins an RTP session in which all the other sources already have unique identi(cid:12)ers, the probability
of collision is just the fraction of numbers used out of the space. Again, if N is the number of

Schulzrinne, et al.

Standards Track

[Page 49]

RFC 3550

RTP

July 2003

sources and L the length of the identi(cid:12)er, the probability of collision is N/2L. For N = 1000, the
probability is roughly 2 (cid:1) 10−7.

The probability of collision is further reduced by the opportunity for a new source to receive packets
from other participants before sending its (cid:12)rst packet (either data or control). If the new source
keeps track of the other participants (by SSRC identi(cid:12)er), then before transmitting its (cid:12)rst packet
the new source can verify that its identi(cid:12)er does not conﬂict with any that have been received, or
else choose again.

8.2 Collision Resolution and Loop Detection

Although the probability of SSRC identi(cid:12)er collision is low, all RTP implementations must be
prepared to detect collisions and take the appropriate actions to resolve them. If a source discovers
at any time that another source is using the same SSRC identi(cid:12)er as its own, it must send an
RTCP BYE packet for the old identi(cid:12)er and choose another random one. (As explained below,
this step is taken only once in case of a loop.)
If a receiver discovers that two other sources are
colliding, it may keep the packets from one and discard the packets from the other when this can
be detected by di(cid:11)erent source transport addresses or CNAMEs. The two sources are expected to
resolve the collision so that the situation doesn’t last.

Because the random SSRC identi(cid:12)ers are kept globally unique for each RTP session, they can also
be used to detect loops that may be introduced by mixers or translators. A loop causes duplication
of data and control information, either unmodi(cid:12)ed or possibly mixed, as in the following examples:

(cid:15) A translator may incorrectly forward a packet to the same multicast group from which it has
received the packet, either directly or through a chain of translators. In that case, the same
packet appears several times, originating from di(cid:11)erent network sources.

(cid:15) Two translators incorrectly set up in parallel, i.e., with the same multicast groups on both
sides, would both forward packets from one multicast group to the other. Unidirectional
translators would produce two copies; bidirectional translators would form a loop.

(cid:15) A mixer can close a loop by sending to the same transport destination upon which it receives
packets, either directly or through another mixer or translator. In this case a source might
show up both as an SSRC on a data packet and a CSRC in a mixed data packet.

A source may discover that its own packets are being looped, or that packets from another source
are being looped (a third-party loop).

Both loops and collisions in the random selection of a source identi(cid:12)er result in packets arriving
with the same SSRC identi(cid:12)er but a di(cid:11)erent source transport address, which may be that of the
end system originating the packet or an intermediate system. Therefore, if a source changes its
source transport address, it may also choose a new SSRC identi(cid:12)er to avoid being interpreted as
a looped source. (This is not must because in some applications of RTP sources may be expected
to change addresses during a session.) Note that if a translator restarts and consequently changes
the source transport address (e.g., changes the UDP source port number) on which it forwards
packets, then all those packets will appear to receivers to be looped because the SSRC identi(cid:12)ers
are applied by the original source and will not change. This problem can be avoided by keeping

Schulzrinne, et al.

Standards Track

[Page 50]

RFC 3550

RTP

July 2003

the source transport address (cid:12)xed across restarts, but in any case will be resolved after a timeout
at the receivers.

Loops or collisions occurring on the far side of a translator or mixer cannot be detected using the
source transport address if all copies of the packets go through the translator or mixer, however,
collisions may still be detected when chunks from two RTCP SDES packets contain the same SSRC
identi(cid:12)er but di(cid:11)erent CNAMEs.
To detect and resolve these conﬂicts, an RTP implementation must include an algorithm similar
to the one described below, though the implementation may choose a di(cid:11)erent policy for which
packets from colliding third-party sources are kept. The algorithm described below ignores packets
from a new source or loop that collide with an established source. It resolves collisions with the
participant’s own SSRC identi(cid:12)er by sending an RTCP BYE for the old identi(cid:12)er and choosing
a new one. However, when the collision was induced by a loop of the participant’s own packets,
the algorithm will choose a new identi(cid:12)er only once and thereafter ignore packets from the looping
source transport address. This is required to avoid a ﬂood of BYE packets.

This algorithm requires keeping a table indexed by the source identi(cid:12)er and containing the source
transport addresses from the (cid:12)rst RTP packet and (cid:12)rst RTCP packet received with that identi(cid:12)er,
along with other state for that source. Two source transport addresses are required since, for
example, the UDP source port numbers may be di(cid:11)erent on RTP and RTCP packets. However, it
may be assumed that the network address is the same in both source transport addresses.

Each SSRC or CSRC identi(cid:12)er received in an RTP or RTCP packet is looked up in the source
identi(cid:12)er table in order to process that data or control information. The source transport address
from the packet is compared to the corresponding source transport address in the table to detect a
loop or collision if they don’t match. For control packets, each element with its own SSRC identi(cid:12)er,
for example an SDES chunk, requires a separate lookup. (The SSRC identi(cid:12)er in a reception report
block is an exception because it identi(cid:12)es a source heard by the reporter, and that SSRC identi(cid:12)er
is unrelated to the source transport address of the RTCP packet sent by the reporter.) If the SSRC
or CSRC is not found, a new entry is created. These table entries are removed when an RTCP
BYE packet is received with the corresponding SSRC identi(cid:12)er and validated by a matching source
transport address, or after no packets have arrived for a relatively long time (see Section 6.2.1).

Note that if two sources on the same host are transmitting with the same source identi(cid:12)er at the
time a receiver begins operation, it would be possible that the (cid:12)rst RTP packet received came from
one of the sources while the (cid:12)rst RTCP packet received came from the other. This would cause
the wrong RTCP information to be associated with the RTP data, but this situation should be
su(cid:14)ciently rare and harmless that it may be disregarded.
In order to track loops of the participant’s own data packets, the implementation must also keep
a separate list of source transport addresses (not identi(cid:12)ers) that have been found to be conﬂicting.
As in the source identi(cid:12)er table, two source transport addresses must be kept to separately track
conﬂicting RTP and RTCP packets. Note that the conﬂicting address list should be short, usually
empty. Each element in this list stores the source addresses plus the time when the most recent
conﬂicting packet was received. An element may be removed from the list when no conﬂicting
packet has arrived from that source for a time on the order of 10 RTCP report intervals (see
Section 6.2).

Schulzrinne, et al.

Standards Track

[Page 51]

RFC 3550

RTP

July 2003

For the algorithm as shown, it is assumed that the participant’s own source identi(cid:12)er and state are
included in the source identi(cid:12)er table. The algorithm could be restructured to (cid:12)rst make a separate
comparison against the participant’s own source identi(cid:12)er.

if (SSRC or CSRC identifier is not found in the source

identifier table) {
create a new entry storing the data or control source

transport address, the SSRC or CSRC and other state;

}

/* Identifier is found in the table */

else if (table entry was created on receipt of a control packet

and this is the first data packet or vice versa) {

store the source transport address from this packet;

}
else if (source transport address from the packet does not match
the one saved in the table entry for this identifier) {

/* An identifier collision or a loop is indicated */

if (source identifier is not the participant’s own) {

/* OPTIONAL error counter step */
if (source identifier is from an RTCP SDES chunk

containing a CNAME item that differs from the CNAME
in the table entry) {
count a third-party collision;

} else {

count a third-party loop;

}
abort processing of data packet or control element;
/* MAY choose a different policy to keep new source */

}

/* A collision or loop of the participant’s own packets */

else if (source transport address is found in the list of

conflicting data or control source transport
addresses) {

/* OPTIONAL error counter step */
if (source identifier is not from an RTCP SDES chunk

containing a CNAME item or CNAME is the
participant’s own) {
count occurrence of own traffic looped;

}

Schulzrinne, et al.

Standards Track

[Page 52]

RFC 3550

RTP

July 2003

mark current time in conflicting address list entry;
abort processing of data packet or control element;

}

/* New collision, change SSRC identifier */

else {

log occurrence of a collision;
create a new entry in the conflicting data or control

source transport address list and mark current time;

send an RTCP BYE packet with the old SSRC identifier;
choose a new SSRC identifier;
create a new entry in the source identifier table with

the old SSRC plus the source transport address from
the data or control packet being processed;

}

}

In this algorithm, packets from a newly conﬂicting source address will be ignored and packets
from the original source address will be kept. If no packets arrive from the original source for an
extended period, the table entry will be timed out and the new source will be able to take over.
This might occur if the original source detects the collision and moves to a new source identi(cid:12)er,
but in the usual case an RTCP BYE packet will be received from the original source to delete the
state without having to wait for a timeout.

If the original source address was received through a mixer (i.e., learned as a CSRC) and later
the same source is received directly, the receiver may be well advised to switch to the new source
address unless other sources in the mix would be lost. Furthermore, for applications such as
telephony in which some sources such as mobile entities may change addresses during the course
of an RTP session, the RTP implementation should modify the collision detection algorithm to
accept packets from the new source transport address. To guard against ﬂip-ﬂopping between
addresses if a genuine collision does occur, the algorithm should include some means to detect
this case and avoid switching.
When a new SSRC identi(cid:12)er is chosen due to a collision, the candidate identi(cid:12)er should (cid:12)rst be
looked up in the source identi(cid:12)er table to see if it was already in use by some other source. If so,
another candidate must be generated and the process repeated.

A loop of data packets to a multicast destination can cause severe network ﬂooding. All mixers
and translators must implement a loop detection algorithm like the one here so that they can
break loops. This should limit the excess tra(cid:14)c to no more than one duplicate copy of the original
tra(cid:14)c, which may allow the session to continue so that the cause of the loop can be found and
(cid:12)xed. However, in extreme cases where a mixer or translator does not properly break the loop and
high tra(cid:14)c levels result, it may be necessary for end systems to cease transmitting data or control
packets entirely. This decision may depend upon the application. An error condition should be
indicated as appropriate. Transmission may be attempted again periodically after a long, random
time (on the order of minutes).

Schulzrinne, et al.

Standards Track

[Page 53]

RFC 3550

RTP

July 2003

8.3 Use with Layered Encodings

For layered encodings transmitted on separate RTP sessions (see Section 2.4), a single SSRC iden-
ti(cid:12)er space should be used across the sessions of all layers and the core (base) layer should be
used for SSRC identi(cid:12)er allocation and collision resolution. When a source discovers that it has
collided, it transmits an RTCP BYE packet on only the base layer but changes the SSRC identi(cid:12)er
to the new value in all layers.

9. Security

Lower layer protocols may eventually provide all the security services that may be desired for
applications of RTP, including authentication, integrity, and con(cid:12)dentiality. These services have
been speci(cid:12)ed for IP in [27]. Since the initial audio and video applications using RTP needed
a con(cid:12)dentiality service before such services were available for the IP layer, the con(cid:12)dentiality
service described in the next section was de(cid:12)ned for use with RTP and RTCP. That description
is included here to codify existing practice. New applications of RTP may implement this RTP-
speci(cid:12)c con(cid:12)dentiality service for backward compatibility, and/or they may implement alternative
security services. The overhead on the RTP protocol for this con(cid:12)dentiality service is low, so the
penalty will be minimal if this service is obsoleted by other services in the future.

Alternatively, other services, other implementations of services and other algorithms may be de(cid:12)ned
for RTP in the future. In particular, an RTP pro(cid:12)le called Secure Real-time Transport Protocol
(SRTP) [28] is being developed to provide con(cid:12)dentiality of the RTP payload while leaving the
It
RTP header in the clear so that link-level header compression algorithms can still operate.
is expected that SRTP will be the correct choice for many applications. SRTP is based on the
Advanced Encryption Standard (AES) and provides stronger security than the service described
here. No claim is made that the methods presented here are appropriate for a particular security
need. A pro(cid:12)le may specify which services and algorithms should be o(cid:11)ered by applications, and
may provide guidance as to their appropriate use.

Key distribution and certi(cid:12)cates are outside the scope of this document.

9.1 Conﬁdentiality

Con(cid:12)dentiality means that only the intended receiver(s) can decode the received packets; for others,
the packet contains no useful information. Con(cid:12)dentiality of the content is achieved by encryption.

When it is desired to encrypt RTP or RTCP according to the method speci(cid:12)ed in this section, all
the octets that will be encapsulated for transmission in a single lower-layer packet are encrypted as
a unit. For RTCP, a 32-bit random number redrawn for each unit must be prepended to the unit
before encryption. For RTP, no pre(cid:12)x is prepended; instead, the sequence number and timestamp
(cid:12)elds are initialized with random o(cid:11)sets. This is considered to be a weak initialization vector (IV)
In addition, if the subsequent (cid:12)eld, the SSRC, can be
because of poor randomness properties.
manipulated by an enemy, there is further weakness of the encryption method.
For RTCP, an implementation may segregate the individual RTCP packets in a compound RTCP

Schulzrinne, et al.

Standards Track

[Page 54]

RFC 3550

RTP

July 2003

packet into two separate compound RTCP packets, one to be encrypted and one to be sent in
the clear. For example, SDES information might be encrypted while reception reports were sent
in the clear to accommodate third-party monitors that are not privy to the encryption key.
In
this example, depicted in Fig. 4, the SDES information must be appended to an RR packet with
no reports (and the random number) to satisfy the requirement that all compound RTCP packets
begin with an SR or RR packet. The SDES CNAME item is required in either the encrypted or
unencrypted packet, but not both. The same SDES information should not be carried in both
packets as this may compromise the encryption.

32-bit
random int.

UDP packet

RR
(empty)

SDES

C
R
S
S
encrypted

UDP packet

CNAME

SR

C
R
S
S

sender
report

C
R
S
S

site 1

C
R
S
S

site 2

not encrypted

fixed RTCP packet header

Figure 4: Encrypted and non-encrypted RTCP packets

The presence of encryption and the use of the correct key are con(cid:12)rmed by the receiver through
header or payload validity checks. Examples of such validity checks for RTP and RTCP headers
are given in Appendices A.1 and A.2.

To be consistent with existing implementations of the initial speci(cid:12)cation of RTP in RFC 1889,
the default encryption algorithm is the Data Encryption Standard (DES) algorithm in cipher block
chaining (CBC) mode, as described in Section 1.1 of RFC 1423 [29], except that padding to a
multiple of 8 octets is indicated as described for the P bit in Section 5.1. The initialization vector is
zero because random values are supplied in the RTP header or by the random pre(cid:12)x for compound
RTCP packets. For details on the use of CBC initialization vectors, see [30].
Implementations that support the encryption method speci(cid:12)ed here should always support the
DES algorithm in CBC mode as the default cipher for this method to maximize interoperability.
This method was chosen because it has been demonstrated to be easy and practical to use in
experimental audio and video tools in operation on the Internet. However, DES has since been
found to be too easily broken. It is recommended that stronger encryption algorithms such as
Triple-DES be used in place of the default algorithm. Furthermore, secure CBC mode requires
that the (cid:12)rst block of each packet be XORed with a random, independent IV of the same size
as the cipher’s block size. For RTCP, this is (partially) achieved by prepending each packet with
a 32-bit random number, independently chosen for each packet. For RTP, the timestamp and
sequence number start from random values, but consecutive packets will not be independently
randomized. It should be noted that the randomness in both cases (RTP and RTCP) is limited.
High-security applications should consider other, more conventional, protection means. Other
encryption algorithms may be speci(cid:12)ed dynamically for a session by non-RTP means. In particular,

Schulzrinne, et al.

Standards Track

[Page 55]

RFC 3550

RTP

July 2003

the SRTP pro(cid:12)le [28] based on AES is being developed to take into account known plaintext and
CBC plaintext manipulation concerns, and will be the correct choice in the future.

As an alternative to encryption at the IP level or at the RTP level as described above, pro(cid:12)les
may de(cid:12)ne additional payload types for encrypted encodings. Those encodings must specify how
padding and other aspects of the encryption are to be handled. This method allows encrypting only
the data while leaving the headers in the clear for applications where that is desired. It may be
particularly useful for hardware devices that will handle both decryption and decoding. It is also
valuable for applications where link-level compression of RTP and lower-layer headers is desired
and con(cid:12)dentiality of the payload (but not addresses) is su(cid:14)cient since encryption of the headers
precludes compression.

9.2 Authentication and Message Integrity

Authentication and message integrity services are not de(cid:12)ned at the RTP level
since these ser-
vices would not be directly feasible without a key management infrastructure. It is expected that
authentication and integrity services will be provided by lower layer protocols.

10. Congestion Control

All transport protocols used on the Internet need to address congestion control in some way [31].
RTP is not an exception, but because the data transported over RTP is often inelastic (generated
at a (cid:12)xed or controlled rate), the means to control congestion in RTP may be quite di(cid:11)erent from
those for other transport protocols such as TCP.
In one sense, inelasticity reduces the risk of
congestion because the RTP stream will not expand to consume all available bandwidth as a TCP
stream can. However, inelasticity also means that the RTP stream cannot arbitrarily reduce its
load on the network to eliminate congestion when it occurs.

Since RTP may be used for a wide variety of applications in many di(cid:11)erent contexts, there is no
single congestion control mechanism that will work for all. Therefore, congestion control should
be de(cid:12)ned in each RTP pro(cid:12)le as appropriate. For some pro(cid:12)les, it may be su(cid:14)cient to include
an applicability statement restricting the use of that pro(cid:12)le to environments where congestion is
avoided by engineering. For other pro(cid:12)les, speci(cid:12)c methods such as data rate adaptation based on
RTCP feedback may be required.

11. RTP over Network and Transport Protocols

This section describes issues speci(cid:12)c to carrying RTP packets within particular network and trans-
port protocols. The following rules apply unless superseded by protocol-speci(cid:12)c de(cid:12)nitions outside
this speci(cid:12)cation.

RTP relies on the underlying protocol(s) to provide demultiplexing of RTP data and RTCP control
streams. For UDP and similar protocols, RTP should use an even destination port number and
the corresponding RTCP stream should use the next higher (odd) destination port number. For
applications that take a single port number as a parameter and derive the RTP and RTCP port

Schulzrinne, et al.

Standards Track

[Page 56]

RFC 3550

RTP

July 2003

pair from that number, if an odd number is supplied then the application should replace that
number with the next lower (even) number to use as the base of the port pair. For applications in
which the RTP and RTCP destination port numbers are speci(cid:12)ed via explicit, separate parameters
(using a signaling protocol or other means), the application may disregard the restrictions that
the port numbers be even/odd and consecutive although the use of an even/odd port pair is still
encouraged. The RTP and RTCP port numbers must not be the same since RTP relies on the
port numbers to demultiplex the RTP data and RTCP control streams.

In a unicast session, both participants need to identify a port pair for receiving RTP and RTCP
packets. Both participants may use the same port pair. A participant must not assume that
the source port of the incoming RTP or RTCP packet can be used as the destination port for
outgoing RTP or RTCP packets. When RTP data packets are being sent in both directions, each
participant’s RTCP SR packets must be sent to the port that the other participant has speci(cid:12)ed
for reception of RTCP. The RTCP SR packets combine sender information for the outgoing data
plus reception report information for the incoming data. If a side is not actively sending data (see
Section 6.4), an RTCP RR packet is sent instead.
It is recommended that layered encoding applications (see Section 2.4) use a set of contiguous
port numbers. The port numbers must be distinct because of a widespread de(cid:12)ciency in existing
operating systems that prevents use of the same port with multiple multicast addresses, and for
unicast, there is only one permissible address. Thus for layer n, the data port is P + 2n, and
the control port is P + 2n + 1. When IP multicast is used, the addresses must also be distinct
because multicast routing and group membership are managed on an address granularity. However,
allocation of contiguous IP multicast addresses cannot be assumed because some groups may require
di(cid:11)erent scopes and may therefore be allocated from di(cid:11)erent address ranges.

The previous paragraph conﬂicts with the SDP speci(cid:12)cation, RFC 2327 [15], which says that it is
illegal for both multiple addresses and multiple ports to be speci(cid:12)ed in the same session description
because the association of addresses with ports could be ambiguous.
It is intended that this
restriction will be relaxed in a revision of RFC 2327 to allow an equal number of addresses and
ports to be speci(cid:12)ed with a one-to-one mapping implied.

RTP data packets contain no length (cid:12)eld or other delineation, therefore RTP relies on the underlying
protocol(s) to provide a length indication. The maximum length of RTP packets is limited only by
the underlying protocols.

If RTP packets are to be carried in an underlying protocol that provides the abstraction of a
continuous octet stream rather than messages (packets), an encapsulation of the RTP packets
must be de(cid:12)ned to provide a framing mechanism. Framing is also needed if the underlying protocol
may contain padding so that the extent of the RTP payload cannot be determined. The framing
mechanism is not de(cid:12)ned here.
A pro(cid:12)le may specify a framing method to be used even when RTP is carried in protocols that do
provide framing in order to allow carrying several RTP packets in one lower-layer protocol data
unit, such as a UDP packet. Carrying several RTP packets in one network or transport packet
reduces header overhead and may simplify synchronization between di(cid:11)erent streams.

Schulzrinne, et al.

Standards Track

[Page 57]

RFC 3550

RTP

July 2003

12. Summary of Protocol Constants

This section contains a summary listing of the constants de(cid:12)ned in this speci(cid:12)cation.

The RTP payload type (PT) constants are de(cid:12)ned in pro(cid:12)les rather than this document. However,
the octet of the RTP header which contains the marker bit(s) and payload type must avoid the
reserved values 200 and 201 (decimal) to distinguish RTP packets from the RTCP SR and RR
packet types for the header validation procedure described in Appendix A.1. For the standard
de(cid:12)nition of one marker bit and a 7-bit payload type (cid:12)eld as shown in this speci(cid:12)cation, this
restriction means that payload types 72 and 73 are reserved.

12.1 RTCP Packet Types

abbrev. name
SR
RR
SDES
BYE
APP

sender report
receiver report
source description
goodbye
application-de(cid:12)ned

value
200
201
202
203
204

These type values were chosen in the range 200-204 for improved header validity checking of RTCP
packets compared to RTP packets or other unrelated packets. When the RTCP packet type (cid:12)eld
is compared to the corresponding octet of the RTP header, this range corresponds to the marker
bit being 1 (which it usually is not in data packets) and to the high bit of the standard payload
type (cid:12)eld being 1 (since the static payload types are typically de(cid:12)ned in the low half). This range
was also chosen to be some distance numerically from 0 and 255 since all-zeros and all-ones are
common data patterns.
Since all compound RTCP packets must begin with SR or RR, these codes were chosen as an
even/odd pair to allow the RTCP validity check to test the maximum number of bits with mask
and value.

Additional RTCP packet types may be registered through IANA (see Section 15).

12.2 SDES Types

name
end of SDES list

user name
user’s electronic mail address

abbrev.
END
CNAME canonical name
NAME
EMAIL
PHONE user’s phone number
LOC
TOOL
NOTE
PRIV

geographic user location
name of application or tool
notice about the source
private extensions

value
0
1
2
3
4
5
6
7
8

Schulzrinne, et al.

Standards Track

[Page 58]

RFC 3550

RTP

July 2003

Additional SDES types may be registered through IANA (see Section 15).

13. RTP Proﬁles and Payload Format Speciﬁcations

A complete speci(cid:12)cation of RTP for a particular application will require one or more companion
documents of two types described here: pro(cid:12)les, and payload format speci(cid:12)cations.

RTP may be used for a variety of applications with somewhat di(cid:11)ering requirements. The ﬂexibil-
ity to adapt to those requirements is provided by allowing multiple choices in the main protocol
speci(cid:12)cation, then selecting the appropriate choices or de(cid:12)ning extensions for a particular environ-
ment and class of applications in a separate proﬁle document. Typically an application will operate
under only one pro(cid:12)le in a particular RTP session, so there is no explicit indication within the RTP
protocol itself as to which pro(cid:12)le is in use. A pro(cid:12)le for audio and video applications may be
found in the companion RFC 3551. Pro(cid:12)les are typically titled \RTP Pro(cid:12)le for . . . ".

The second type of companion document is a payload format speci(cid:12)cation, which de(cid:12)nes how a
particular kind of payload data, such as H.261 encoded video, should be carried in RTP. These
documents are typically titled \RTP Payload Format for XYZ Audio/Video Encoding". Payload
formats may be useful under multiple pro(cid:12)les and may therefore be de(cid:12)ned independently of any
particular pro(cid:12)le. The pro(cid:12)le documents are then responsible for assigning a default mapping of
that format to a payload type value if needed.

Within this speci(cid:12)cation, the following items have been identi(cid:12)ed for possible de(cid:12)nition within a
pro(cid:12)le, but this list is not meant to be exhaustive:

RTP data header: The octet in the RTP data header that contains the marker bit and payload
type (cid:12)eld may be rede(cid:12)ned by a pro(cid:12)le to suit di(cid:11)erent requirements, for example with more
or fewer marker bits (Section 5.3, p. 15).

Payload types: Assuming that a payload type (cid:12)eld is included, the pro(cid:12)le will usually de(cid:12)ne a
set of payload formats (e.g., media encodings) and a default static mapping of those formats
to payload type values. Some of the payload formats may be de(cid:12)ned by reference to separate
payload format speci(cid:12)cations. For each payload type de(cid:12)ned, the pro(cid:12)le must specify the
RTP timestamp clock rate to be used (Section 5.1, p. 13).

RTP data header additions: Additional (cid:12)elds may be appended to the (cid:12)xed RTP data header if
some additional functionality is required across the pro(cid:12)le’s class of applications independent
of payload type (Section 5.3, p. 15).

RTP data header extensions: The contents of the (cid:12)rst 16 bits of the RTP data header extension
structure must be de(cid:12)ned if use of that mechanism is to be allowed under the pro(cid:12)le for
implementation-speci(cid:12)c extensions (Section 5.3.1, p. 16).

RTCP packet types: New application-class-speci(cid:12)c RTCP packet types may be de(cid:12)ned and reg-

istered with IANA.

RTCP report interval: A pro(cid:12)le should specify that the values suggested in Section 6.2 for the
constants employed in the calculation of the RTCP report interval will be used. Those are

Schulzrinne, et al.

Standards Track

[Page 59]

RFC 3550

RTP

July 2003

the RTCP fraction of session bandwidth, the minimum report interval, and the bandwidth
split between senders and receivers. A pro(cid:12)le may specify alternate values if they have been
demonstrated to work in a scalable manner.

SR/RR extension: An extension section may be de(cid:12)ned for the RTCP SR and RR packets if
there is additional information that should be reported regularly about the sender or receivers
(Section 6.4.3, p. 35).

SDES use: The pro(cid:12)le may specify the relative priorities for RTCP SDES items to be transmitted
or excluded entirely (Section 6.3.9); an alternate syntax or semantics for the CNAME item
(Section 6.5.1); the format of the LOC item (Section 6.5.5); the semantics and use of the
NOTE item (Section 6.5.7); or new SDES item types to be registered with IANA.

Security: A pro(cid:12)le may specify which security services and algorithms should be o(cid:11)ered by ap-

plications, and may provide guidance as to their appropriate use (Section 9, p. 54).

String-to-key mapping: A pro(cid:12)le may specify how a user-provided password or pass phrase is

mapped into an encryption key.

Congestion: A pro(cid:12)le should specify the congestion control behavior appropriate for that pro(cid:12)le.

Underlying protocol: Use of a particular underlying network or transport layer protocol to carry

RTP packets may be required.

Transport mapping: A mapping of RTP and RTCP to transport-level addresses, e.g., UDP
ports, other than the standard mapping de(cid:12)ned in Section 11, p. 56 may be speci(cid:12)ed.

Encapsulation: An encapsulation of RTP packets may be de(cid:12)ned to allow multiple RTP data
packets to be carried in one lower-layer packet or to provide framing over underlying protocols
that do not already do so (Section 11, p. 56).

It is not expected that a new pro(cid:12)le will be required for every application. Within one application
class, it would be better to extend an existing pro(cid:12)le rather than make a new one in order to
facilitate interoperation among the applications since each will typically run under only one pro(cid:12)le.
Simple extensions such as the de(cid:12)nition of additional payload type values or RTCP packet types
may be accomplished by registering them through IANA and publishing their descriptions in an
addendum to the pro(cid:12)le or in a payload format speci(cid:12)cation.

14. Security Considerations

RTP su(cid:11)ers from the same security liabilities as the underlying protocols. For example, an impostor
can fake source or destination network addresses, or change the header or payload. Within RTCP,
the CNAME and NAME information may be used to impersonate another participant. In addition,
RTP may be sent via IP multicast, which provides no direct means for a sender to know all the
receivers of the data sent and therefore no measure of privacy. Rightly or not, users may be more
sensitive to privacy concerns with audio and video communication than they have been with more

Schulzrinne, et al.

Standards Track

[Page 60]

RFC 3550

RTP

July 2003

traditional forms of network communication [33]. Therefore, the use of security mechanisms with
RTP is important. These mechanisms are discussed in Section 9.

RTP-level translators or mixers may be used to allow RTP tra(cid:14)c to reach hosts behind (cid:12)rewalls.
Appropriate (cid:12)rewall security principles and practices, which are beyond the scope of this document,
should be followed in the design and installation of these devices and in the admission of RTP
applications for use behind the (cid:12)rewall.

15.

IANA Considerations

Additional RTCP packet types and SDES item types may be registered through the Internet As-
signed Numbers Authority (IANA). Since these number spaces are small, allowing unconstrained
registration of new values would not be prudent. To facilitate review of requests and to promote
shared use of new types among multiple applications, requests for registration of new values must
be documented in an RFC or other permanent and readily available reference such as the product
of another cooperative standards body (e.g., ITU-T). Other requests may also be accepted, under
the advice of a \designated expert." (Contact the IANA for the contact information of the current
expert.)
RTP pro(cid:12)le speci(cid:12)cations should register with IANA a name for the pro(cid:12)le in the form \RTP/xxx",
where xxx is a short abbreviation of the pro(cid:12)le title. These names are for use by higher-level control
protocols, such as the Session Description Protocol (SDP), RFC 2327 [15], to refer to transport
methods.

16.

Intellectual Property Rights Statement

The IETF takes no position regarding the validity or scope of any intellectual property or other
rights that might be claimed to pertain to the implementation or use of the technology described in
this document or the extent to which any license under such rights might or might not be available;
neither does it represent that it has made any e(cid:11)ort to identify any such rights. Information on the
IETF’s procedures with respect to rights in standards-track and standards-related documentation
can be found in BCP-11. Copies of claims of rights made available for publication and any assur-
ances of licenses to be made available, or the result of an attempt made to obtain a general license
or permission for the use of such proprietary rights by implementors or users of this speci(cid:12)cation
can be obtained from the IETF Secretariat.

The IETF invites any interested party to bring to its attention any copyrights, patents or patent
applications, or other proprietary rights which may cover technology that may be required to
practice this standard. Please address the information to the IETF Executive Director.

17. Acknowledgments

This memorandum is based on discussions within the IETF Audio/Video Transport working group
chaired by Stephen Casner and Colin Perkins. The current protocol has its origins in the Network

Schulzrinne, et al.

Standards Track

[Page 61]

RFC 3550

RTP

July 2003

Voice Protocol and the Packet Video Protocol (Danny Cohen and Randy Cole) and the protocol
implemented by the vat application (Van Jacobson and Steve McCanne). Christian Huitema pro-
vided ideas for the random identi(cid:12)er generator. Extensive analysis and simulation of the timer
reconsideration algorithm was done by Jonathan Rosenberg. The additions for layered encodings
were speci(cid:12)ed by Michael Speer and Steve McCanne.

Appendix A. Algorithms

We provide examples of C code for aspects of RTP sender and receiver algorithms. There may be
other implementation methods that are faster in particular operating environments or have other
advantages. These implementation notes are for informational purposes only and are meant to
clarify the RTP speci(cid:12)cation.

The following de(cid:12)nitions are used for all examples; for clarity and brevity, the structure de(cid:12)nitions
are only valid for 32-bit big-endian (most signi(cid:12)cant octet (cid:12)rst) architectures. Bit (cid:12)elds are assumed
to be packed tightly in big-endian bit order, with no additional padding. Modi(cid:12)cations would be
required to construct a portable implementation.

/*

* rtp.h -- RTP header file
*/

#include <sys/types.h>

/*

* The type definitions below are valid for 32-bit architectures and
* may have to be adjusted for 16- or 64-bit architectures.
*/

typedef unsigned char u_int8;
typedef unsigned short u_int16;
typedef unsigned int
u_int32;
typedef

short int16;

/*

* Current protocol version.
*/

#define RTP_VERSION

2

#define RTP_SEQ_MOD (1<<16)
#define RTP_MAX_SDES 255

typedef enum {
= 200,
RTCP_SR
RTCP_RR
= 201,
RTCP_SDES = 202,
RTCP_BYE = 203,

/* maximum text length for SDES */

Schulzrinne, et al.

Standards Track

[Page 62]

RFC 3550

RTP

July 2003

RTCP_APP = 204

} rtcp_type_t;

typedef enum {

RTCP_SDES_END
= 0,
RTCP_SDES_CNAME = 1,
RTCP_SDES_NAME = 2,
RTCP_SDES_EMAIL = 3,
RTCP_SDES_PHONE = 4,
RTCP_SDES_LOC
= 5,
RTCP_SDES_TOOL = 6,
RTCP_SDES_NOTE = 7,
RTCP_SDES_PRIV = 8

} rtcp_sdes_type_t;

/*

* RTP data header
*/

typedef struct {

unsigned int version:2;
unsigned int p:1;
unsigned int x:1;
unsigned int cc:4;
unsigned int m:1;
unsigned int pt:7;
unsigned int seq:16;
u_int32 ts;
u_int32 ssrc;
u_int32 csrc[1];

/* protocol version */
/* padding flag */
/* header extension flag */
/* CSRC count */
/* marker bit */
/* payload type */
/* sequence number */
/* timestamp */
/* synchronization source */
/* optional CSRC list */

} rtp_hdr_t;

/*

* RTCP common header word
*/

typedef struct {

unsigned int version:2;
unsigned int p:1;
unsigned int count:5;
unsigned int pt:8;
u_int16 length;

/* protocol version */
/* padding flag */
/* varies by packet type */
/* RTCP packet type */
/* pkt len in words, w/o this word */

} rtcp_common_t;

/*

* Big-endian mask for version, padding bit and packet type pair
*/

Schulzrinne, et al.

Standards Track

[Page 63]

RFC 3550

RTP

July 2003

#define RTCP_VALID_MASK (0xc000 | 0x2000 | 0xfe)
#define RTCP_VALID_VALUE ((RTP_VERSION << 14) | RTCP_SR)

/*

* Reception report block
*/

typedef struct {

/* data source being reported */

u_int32 ssrc;
unsigned int fraction:8; /* fraction lost since last SR/RR */
/* cumul. no. pkts lost (signed!) */
int lost:24;
/* extended last seq. no. received */
u_int32 last_seq;
/* interarrival jitter */
u_int32 jitter;
/* last SR packet from this source */
u_int32 lsr;
/* delay since last SR packet */
u_int32 dlsr;

} rtcp_rr_t;

/*

* SDES item
*/

typedef struct {
u_int8 type;
u_int8 length;
char data[1];

} rtcp_sdes_item_t;

/*

* One RTCP packet
*/

typedef struct {

/* type of item (rtcp_sdes_type_t) */
/* length of item (in octets) */
/* text, not null-terminated */

rtcp_common_t common;
union {

/* common header */

/* sender report (SR) */
struct {

/* sender generating this report */

u_int32 ssrc;
u_int32 ntp_sec; /* NTP timestamp */
u_int32 ntp_frac;
u_int32 rtp_ts;
u_int32 psent;
u_int32 osent;
rtcp_rr_t rr[1]; /* variable-length list */

/* RTP timestamp */
/* packets sent */
/* octets sent */

} sr;

/* reception report (RR) */
struct {

u_int32 ssrc;

/* receiver generating this report */

Schulzrinne, et al.

Standards Track

[Page 64]

RFC 3550

RTP

July 2003

rtcp_rr_t rr[1]; /* variable-length list */

} rr;

/* source description (SDES) */
struct rtcp_sdes {

u_int32 src;
rtcp_sdes_item_t item[1]; /* list of SDES items */

/* first SSRC/CSRC */

} sdes;

/* BYE */
struct {

u_int32 src[1];
/* can’t express trailing text for reason */

/* list of sources */

} bye;

} r;

} rtcp_t;

typedef struct rtcp_sdes rtcp_sdes_t;

/*

* Per-source state information
*/

typedef struct {

/* highest seq. number seen */
/* shifted count of seq. number cycles */
/* base seq number */
/* last ’bad’ seq number + 1 */
/* sequ. packets till source is valid */
/* packets received */

u_int16 max_seq;
u_int32 cycles;
u_int32 base_seq;
u_int32 bad_seq;
u_int32 probation;
u_int32 received;
u_int32 expected_prior; /* packet expected at last interval */
u_int32 received_prior; /* packet received at last interval */
/* relative trans time for prev pkt */
u_int32 transit;
u_int32 jitter;
/* estimated jitter */
/* ... */

} source;

A.1 RTP Data Header Validity Checks

An RTP receiver should check the validity of the RTP header on incoming packets since they might
be encrypted or might be from a di(cid:11)erent application that happens to be misaddressed. Similarly,
if encryption according to the method described in Section 9 is enabled, the header validity check
is needed to verify that incoming packets have been correctly decrypted, although a failure of the
header validity check (e.g., unknown payload type) may not necessarily indicate decryption failure.

Schulzrinne, et al.

Standards Track

[Page 65]

RFC 3550

RTP

July 2003

Only weak validity checks are possible on an RTP data packet from a source that has not been
heard before:

(cid:15) RTP version (cid:12)eld must equal 2.

(cid:15) The payload type must be known, and in particular it must not be equal to SR or RR.

(cid:15) If the P bit is set, then the last octet of the packet must contain a valid octet count, in

particular, less than the total packet length minus the header size.

(cid:15) The X bit must be zero if the pro(cid:12)le does not specify that the header extension mechanism
may be used. Otherwise, the extension length (cid:12)eld must be less than the total packet size
minus the (cid:12)xed header length and padding.

(cid:15) The length of the packet must be consistent with CC and payload type (if payloads have a

known length).

The last three checks are somewhat complex and not always possible, leaving only the (cid:12)rst two
If the SSRC identi(cid:12)er in the packet is one that has been received
which total just a few bits.
before, then the packet is probably valid and checking if the sequence number is in the expected
range provides further validation.
If the SSRC identi(cid:12)er has not been seen before, then data
packets carrying that identi(cid:12)er may be considered invalid until a small number of them arrive with
consecutive sequence numbers. Those invalid packets may be discarded or they may be stored and
delivered once validation has been achieved if the resulting delay is acceptable.

The routine update_seq shown below ensures that a source is declared valid only after
It also validates the sequence num-
MIN_SEQUENTIAL packets have been received in sequence.
ber seq of a newly received packet and updates the sequence state for the packet’s source in the
structure to which s points.

When a new source is heard for the (cid:12)rst time, that is, its SSRC identi(cid:12)er is not in the table (see
Section 8.2), and the per-source state is allocated for it, s->probation is set to the number of
sequential packets required before declaring a source valid (parameter MIN_SEQUENTIAL) and other
variables are initialized:

init_seq(s, seq);
s->max_seq = seq - 1;
s->probation = MIN_SEQUENTIAL;

A non-zero s->probation marks the source as not yet valid so the state may be discarded after a
short timeout rather than a long one, as discussed in Section 6.2.1.

After a source is considered valid, the sequence number is considered valid if it is no more than
MAX_DROPOUT ahead of s->max_seq nor more than MAX_MISORDER behind.
If the new sequence
number is ahead of max_seq modulo the RTP sequence number range (16 bits), but is smaller than
max_seq, it has wrapped around and the (shifted) count of sequence number cycles is incremented.
A value of one is returned to indicate a valid sequence number.

Otherwise, the value zero is returned to indicate that the validation failed, and the bad sequence
number plus 1 is stored. If the next packet received carries the next higher sequence number, it

Schulzrinne, et al.

Standards Track

[Page 66]

RFC 3550

RTP

July 2003

is considered the valid start of a new packet sequence presumably caused by an extended dropout
or a source restart. Since multiple complete sequence number cycles may have been missed, the
packet loss statistics are reset.

Typical values for the parameters are shown, based on a maximum misordering time of 2 seconds
at 50 packets/second and a maximum dropout of 1 minute. The dropout parameter MAX_DROPOUT
should be a small fraction of the 16-bit sequence number space to give a reasonable probability that
new sequence numbers after a restart will not fall in the acceptable range for sequence numbers
from before the restart.

void init_seq(source *s, u_int16 seq)
{

s->base_seq = seq;
s->max_seq = seq;
s->bad_seq = RTP_SEQ_MOD + 1;
s->cycles = 0;
s->received = 0;
s->received_prior = 0;
s->expected_prior = 0;
/* other initialization */

}

/* so seq == bad_seq is false */

int update_seq(source *s, u_int16 seq)
{

u_int16 udelta = seq - s->max_seq;
const int MAX_DROPOUT = 3000;
const int MAX_MISORDER = 100;
const int MIN_SEQUENTIAL = 2;

/*

* Source is not valid until MIN_SEQUENTIAL packets with
* sequential sequence numbers have been received.
*/

if (s->probation) {

/* packet is in sequence */
if (seq == s->max_seq + 1) {

s->probation--;
s->max_seq = seq;
if (s->probation == 0) {
init_seq(s, seq);
s->received++;
return 1;

}
} else {

s->probation = MIN_SEQUENTIAL - 1;
s->max_seq = seq;

Schulzrinne, et al.

Standards Track

[Page 67]

RFC 3550

RTP

July 2003

}
return 0;

} else if (udelta < MAX_DROPOUT) {

/* in order, with permissible gap */
if (seq < s->max_seq) {

/*

* Sequence number wrapped - count another 64K cycle.
*/

s->cycles += RTP_SEQ_MOD;

}
s->max_seq = seq;

} else if (udelta <= RTP_SEQ_MOD - MAX_MISORDER) {

/* the sequence number made a very large jump */
if (seq == s->bad_seq) {

/*

* Two sequential packets -- assume that the other side
* restarted without telling us so just re-sync
* (i.e., pretend this was the first packet).
*/

init_seq(s, seq);

}
else {

s->bad_seq = (seq + 1) & (RTP_SEQ_MOD-1);
return 0;

}
} else {

/* duplicate or reordered packet */

}
s->received++;
return 1;

}

The validity check can be made stronger requiring more than two packets in sequence. The disad-
vantages are that a larger number of initial packets will be discarded (or delayed in a queue) and
that high packet loss rates could prevent validation. However, because the RTCP header validation
is relatively strong, if an RTCP packet is received from a source before the data packets, the count
could be adjusted so that only two packets are required in sequence. If initial data loss for a few
seconds can be tolerated, an application may choose to discard all data packets from a source until
a valid RTCP packet has been received from that source.

Depending on the application and encoding, algorithms may exploit additional knowledge about
the payload format for further validation. For payload types where the timestamp increment is the
same for all packets, the timestamp values can be predicted from the previous packet received from
the same source using the sequence number di(cid:11)erence (assuming no change in payload type).

A strong \fast-path" check is possible since with high probability the (cid:12)rst four octets in the header

Schulzrinne, et al.

Standards Track

[Page 68]

RFC 3550

RTP

July 2003

of a newly received RTP data packet will be just the same as that of the previous packet from the
same SSRC except that the sequence number will have increased by one. Similarly, a single-entry
cache may be used for faster SSRC lookups in applications where data is typically received from
one source at a time.

A.2 RTCP Header Validity Checks

The following checks should be applied to RTCP packets.

(cid:15) RTP version (cid:12)eld must equal 2.

(cid:15) The payload type (cid:12)eld of the (cid:12)rst RTCP packet in a compound packet must be equal to SR

or RR.

(cid:15) The padding bit (P) should be zero for the (cid:12)rst packet of a compound RTCP packet because

padding should only be applied, if it is needed, to the last packet.

(cid:15) The length (cid:12)elds of the individual RTCP packets must add up to the overall length of the

compound RTCP packet as received. This is a fairly strong check.

The code fragment below performs all of these checks. The packet type is not checked for subsequent
packets since unknown packet types may be present and should be ignored.

u_int32 len;
rtcp_t *r;
rtcp_t *end;

/* length of compound RTCP packet in words */
/* RTCP header */
/* end of compound RTCP packet */

if ((*(u_int16 *)r & RTCP_VALID_MASK) != RTCP_VALID_VALUE) {

/* something wrong with packet format */

}
end = (rtcp_t *)((u_int32 *)r + len);

do r = (rtcp_t *)((u_int32 *)r + r->common.length + 1);
while (r < end && r->common.version == 2);

if (r != end) {

/* something wrong with packet format */

}

A.3 Determining Number of Packets Expected and Lost

In order to compute packet loss rates, the number of RTP packets expected and actually received
from each source needs to be known, using per-source state information de(cid:12)ned in struct source
referenced via pointer s in the code below. The number of packets received is simply the count of
packets as they arrive, including any late or duplicate packets. The number of packets expected

Schulzrinne, et al.

Standards Track

[Page 69]

RFC 3550

RTP

July 2003

can be computed by the receiver as the di(cid:11)erence between the highest sequence number received
(s->max_seq) and the (cid:12)rst sequence number received (s->base_seq). Since the sequence number
is only 16 bits and will wrap around, it is necessary to extend the highest sequence number with
the (shifted) count of sequence number wraparounds (s->cycles). Both the received packet count
and the count of cycles are maintained the RTP header validity check routine in Appendix A.1.

extended_max = s->cycles + s->max_seq;
expected = extended_max - s->base_seq + 1;

The number of packets lost is de(cid:12)ned to be the number of packets expected less the number of
packets actually received:

lost = expected - s->received;

Since this signed number is carried in 24 bits, it should be clamped at 0x7(cid:11)(cid:11)f for positive loss or
0x800000 for negative loss rather than wrapping around.

The fraction of packets lost during the last reporting interval (since the previous SR or RR packet
was sent) is calculated from di(cid:11)erences in the expected and received packet counts across the
interval, where expected_prior and received_prior are the values saved when the previous
reception report was generated:

expected_interval = expected - s->expected_prior;
s->expected_prior = expected;
received_interval = s->received - s->received_prior;
s->received_prior = s->received;
lost_interval = expected_interval - received_interval;
if (expected_interval == 0 || lost_interval <= 0) fraction = 0;
else fraction = (lost_interval << 8) / expected_interval;

The resulting fraction is an 8-bit (cid:12)xed point number with the binary point at the left edge.

A.4 Generating RTCP SDES Packets

This function builds one SDES chunk into bu(cid:11)er b composed of argc items supplied in arrays type,
value and length. It returns a pointer to the next available location within b.

char *rtp_write_sdes(char *b, u_int32 src, int argc,

rtcp_sdes_type_t type[], char *value[],
int length[])

{

rtcp_sdes_t *s = (rtcp_sdes_t *)b;
rtcp_sdes_item_t *rsp;
int i;
int len;
int pad;

Schulzrinne, et al.

Standards Track

[Page 70]

RFC 3550

RTP

July 2003

/* SSRC header */
s->src = src;
rsp = &s->item[0];

/* SDES items */
for (i = 0; i < argc; i++) {
rsp->type = type[i];
len = length[i];
if (len > RTP_MAX_SDES) {

/* invalid length, may want to take other action */
len = RTP_MAX_SDES;

}
rsp->length = len;
memcpy(rsp->data, value[i], len);
rsp = (rtcp_sdes_item_t *)&rsp->data[len];

}

/* terminate with end marker and pad to next 4-octet boundary */
len = ((char *) rsp) - b;
pad = 4 - (len & 0x3);
b = (char *) rsp;
while (pad--) *b++ = RTCP_SDES_END;

return b;

}

A.5 Parsing RTCP SDES Packets

This function parses an SDES packet, calling functions find_member() to (cid:12)nd a pointer to the
information for a session member given the SSRC identi(cid:12)er and member_sdes() to store the new
SDES information for that member. This function expects a pointer to the header of the RTCP
packet.

void rtp_read_sdes(rtcp_t *r)
{

int count = r->common.count;
rtcp_sdes_t *sd = &r->r.sdes;
rtcp_sdes_item_t *rsp, *rspn;
rtcp_sdes_item_t *end = (rtcp_sdes_item_t *)

((u_int32 *)r + r->common.length + 1);

source *s;

while (--count >= 0) {

Schulzrinne, et al.

Standards Track

[Page 71]

RFC 3550

RTP

July 2003

rsp = &sd->item[0];
if (rsp >= end) break;
s = find_member(sd->src);

for (; rsp->type; rsp = rspn ) {

rspn = (rtcp_sdes_item_t *)((char*)rsp+rsp->length+2);
if (rspn >= end) {
rsp = rspn;
break;

}
member_sdes(s, rsp->type, rsp->data, rsp->length);

}
sd = (rtcp_sdes_t *)

((u_int32 *)sd + (((char *)rsp - (char *)sd) >> 2)+1);

}
if (count >= 0) {

/* invalid packet format */

}

}

A.6 Generating a Random 32-bit Identiﬁer

The following subroutine generates a random 32-bit identi(cid:12)er using the MD5 routines published
in RFC 1321 [32]. The system routines may not be present on all operating systems, but they
should serve as hints as to what kinds of information may be used. Other system calls that may
be appropriate include

(cid:15) getdomainname(),

(cid:15) getwd(), or

(cid:15) getrusage().

\Live" video or audio samples are also a good source of random numbers, but care must be taken
to avoid using a turned-o(cid:11) microphone or blinded camera as a source [17].

Use of this or a similar routine is recommended to generate the initial seed for the random number
generator producing the RTCP period (as shown in Appendix A.7), to generate the initial values for
the sequence number and timestamp, and to generate SSRC values. Since this routine is likely to
be CPU-intensive, its direct use to generate RTCP periods is inappropriate because predictability
is not an issue. Note that this routine produces the same result on repeated calls until the value of
the system clock changes unless di(cid:11)erent values are supplied for the type argument.

/*

* Generate a random 32-bit quantity.

Schulzrinne, et al.

Standards Track

[Page 72]

RFC 3550

*/

RTP

July 2003

#include <sys/types.h>
/* u_long */
#include <sys/time.h>
/* gettimeofday() */
#include <unistd.h>
/* get..() */
#include <stdio.h>
/* printf() */
/* clock() */
#include <time.h>
#include <sys/utsname.h> /* uname() */
#include "global.h"
#include "md5.h"

/* from RFC 1321 */
/* from RFC 1321 */

#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final

static u_long md_32(char *string, int length)
{

MD_CTX context;
union {

c[16];

char
u_long x[4];

} digest;
u_long r;
int i;

MDInit (&context);
MDUpdate (&context, string, length);
MDFinal ((unsigned char *)&digest, &context);
r = 0;
for (i = 0; i < 3; i++) {
r ^= digest.x[i];

}
return r;

}

/*

/* md_32 */

* Return random unsigned 32-bit quantity. Use ’type’ argument if
* you need to generate several different values in close succession.
*/

u_int32 random32(int type)
{

struct {

int
struct timeval tv;

type;

Schulzrinne, et al.

Standards Track

[Page 73]

RFC 3550

RTP

July 2003

clock_t cpu;
pid;
pid_t
u_long hid;
uid;
uid_t
gid_t
gid;
struct utsname name;

} s;

gettimeofday(&s.tv, 0);
uname(&s.name);
s.type = type;
s.cpu = clock();
s.pid = getpid();
s.hid = gethostid();
s.uid = getuid();
s.gid = getgid();
/* also: system uptime */

return md_32((char *)&s, sizeof(s));

}

/* random32 */

A.7 Computing the RTCP Transmission Interval

The following functions implement the RTCP transmission and reception rules described in Sec-
tion 6.2. These rules are coded in several functions:

(cid:15) rtcp interval() computes the deterministic calculated interval, measured in seconds. The

parameters are de(cid:12)ned in Section 6.3.

(cid:15) OnExpire() is called when the RTCP transmission timer expires.

(cid:15) OnReceive() is called whenever an RTCP packet is received.

Both OnExpire() and OnReceive() have event e as an argument. This is the next scheduled event
for that participant, either an RTCP report or a BYE packet. It is assumed that the following
functions are available:

(cid:15) Schedule(time t, event e) schedules an event e to occur at time t. When time t arrives,

the function OnExpire is called with e as an argument.

(cid:15) Reschedule(time t, event e) reschedules a previously scheduled event e for time t.

(cid:15) SendRTCPReport(event e) sends an RTCP report.

(cid:15) SendBYEPacket(event e) sends a BYE packet.

Schulzrinne, et al.

Standards Track

[Page 74]

RFC 3550

RTP

July 2003

(cid:15) TypeOfEvent(event e) returns EVENT BYE if the event being processed is for a BYE

packet to be sent, else it returns EVENT REPORT.

(cid:15) PacketType(p) returns PACKET RTCP REPORT if packet p is an RTCP report (not BYE),
PACKET BYE if its a BYE RTCP packet, and PACKET RTP if its a regular RTP data
packet.

(cid:15) ReceivedPacketSize() and SentPacketSize() return the size of the referenced packet in

octets.

(cid:15) NewMember(p) returns a 1 if the participant who sent packet p is not currently in the member
list, 0 otherwise. Note this function is not su(cid:14)cient for a complete implementation because
each CSRC identi(cid:12)er in an RTP packet and each SSRC in a BYE packet should be processed.

(cid:15) NewSender(p) returns a 1 if the participant who sent packet p is not currently in the sender

sublist of the member list, 0 otherwise.

(cid:15) AddMember() and RemoveMember() to add and remove participants from the member list.

(cid:15) AddSender() and RemoveSender() to add and remove participants from the sender sublist

of the member list.

These functions would have to be extended for an implementation that allows the RTCP bandwidth
fractions for senders and non-senders to be speci(cid:12)ed as explict parameters rather than (cid:12)xed values
of 25% and 75%. The extended implementation of rtcp interval() would need to avoid division
by zero if one of the parameters was zero.

double rtcp_interval(int members,
int senders,
double rtcp_bw,
int we_sent,
double avg_rtcp_size,
int initial)

{

/*

* Minimum average time between RTCP packets from this site (in
* seconds). This time prevents the reports from ‘clumping’ when
* sessions are small and the law of large numbers isn’t helping
* to smooth out the traffic. It also keeps the report interval
* from becoming ridiculously small during transient outages like
* a network partition.
*/

double const RTCP_MIN_TIME = 5.;
/*

* Fraction of the RTCP bandwidth to be shared among active
* senders. (This fraction was chosen so that in a typical
* session with one or two active senders, the computed report

Schulzrinne, et al.

Standards Track

[Page 75]

RFC 3550

RTP

July 2003

* time would be roughly equal to the minimum report time so that
* we don’t unnecessarily slow down receiver reports.) The
* receiver fraction must be 1 - the sender fraction.
*/

double const RTCP_SENDER_BW_FRACTION = 0.25;
double const RTCP_RCVR_BW_FRACTION = (1-RTCP_SENDER_BW_FRACTION);
/*
/* To compensate for "timer reconsideration" converging to a

* value below the intended average.
*/

double const COMPENSATION = 2.71828 - 1.5;

double t;
double rtcp_min_time = RTCP_MIN_TIME;
int n;

/* interval */

/* no. of members for computation */

/*

* Very first call at application start-up uses half the min
* delay for quicker notification while still allowing some time
* before reporting for randomization and to learn about other
* sources so the report interval will converge to the correct
* interval more quickly.
*/

if (initial) {

rtcp_min_time /= 2;

}

/*

* Dedicate a fraction of the RTCP bandwidth to senders unless
* the number of senders is large enough that their share is
* more than that fraction.
*/

n = members;
if (senders <= members * RTCP_SENDER_BW_FRACTION) {

if (we_sent) {

rtcp_bw *= RTCP_SENDER_BW_FRACTION;
n = senders;

} else {

rtcp_bw *= RTCP_RCVR_BW_FRACTION;
n -= senders;

}

}

/*

* The effective number of sites times the average packet size is

Schulzrinne, et al.

Standards Track

[Page 76]

RFC 3550

RTP

July 2003

* the total number of octets sent when each site sends a report.
* Dividing this by the effective bandwidth gives the time
* interval over which those packets must be sent in order to
* meet the bandwidth target, with a minimum enforced. In that
* time interval we send one report so this time is also our
* average time between reports.
*/

t = avg_rtcp_size * n / rtcp_bw;
if (t < rtcp_min_time) t = rtcp_min_time;

/*

* To avoid traffic bursts from unintended synchronization with
* other sites, we then pick our actual next report interval as a
* random number uniformly distributed between 0.5*t and 1.5*t.
*/

t = t * (drand48() + 0.5);
t = t / COMPENSATION;
return t;

}

void OnExpire(event e,

members,
int
senders,
int
double rtcp_bw,
int
we_sent,
double *avg_rtcp_size,
*initial,
int
tc,
time_tp
time_tp
*tp,
*pmembers)
int

{

/* This function is responsible for deciding whether to send an

* RTCP report or BYE packet now, or to reschedule transmission.
* It is also responsible for updating the pmembers, initial, tp,
* and avg_rtcp_size state variables. This function should be
* called upon expiration of the event timer used by Schedule().
*/

double t;
double tn;

/* Interval */
/* Next transmit time */

/* In the case of a BYE, we use "timer reconsideration" to
* reschedule the transmission of the BYE if necessary */

Schulzrinne, et al.

Standards Track

[Page 77]

RFC 3550

RTP

July 2003

if (TypeOfEvent(e) == EVENT_BYE) {
t = rtcp_interval(members,
senders,
rtcp_bw,
we_sent,
*avg_rtcp_size,
*initial);

tn = *tp + t;
if (tn <= tc) {

SendBYEPacket(e);
exit(1);

} else {

Schedule(tn, e);

}

} else if (TypeOfEvent(e) == EVENT_REPORT) {

t = rtcp_interval(members,
senders,
rtcp_bw,
we_sent,
*avg_rtcp_size,
*initial);

tn = *tp + t;

if (tn <= tc) {

SendRTCPReport(e);
*avg_rtcp_size = (1./16.)*SentPacketSize(e) +

(15./16.)*(*avg_rtcp_size);

*tp = tc;

/* We must redraw the interval. Don’t reuse the
one computed above, since its not actually
distributed the same, as we are conditioned
on it being small enough to cause a packet to
be sent */

t = rtcp_interval(members,
senders,
rtcp_bw,
we_sent,
*avg_rtcp_size,
*initial);

Schedule(t+tc,e);
*initial = 0;

Schulzrinne, et al.

Standards Track

[Page 78]

RFC 3550

RTP

July 2003

} else {

Schedule(tn, e);

}
*pmembers = members;

}

}

void OnReceive(packet p,

event e,
int *members,
int *pmembers,
int *senders,
double *avg_rtcp_size,
double *tp,
double tc,
double tn)

{

/* What we do depends on whether we have left the group, and are

* waiting to send a BYE (TypeOfEvent(e) == EVENT_BYE) or an RTCP
* report. p represents the packet that was just received. */

if (PacketType(p) == PACKET_RTCP_REPORT) {

if (NewMember(p) && (TypeOfEvent(e) == EVENT_REPORT)) {

AddMember(p);
*members += 1;

}
*avg_rtcp_size = (1./16.)*ReceivedPacketSize(p) +

(15./16.)*(*avg_rtcp_size);

} else if (PacketType(p) == PACKET_RTP) {

if (NewMember(p) && (TypeOfEvent(e) == EVENT_REPORT)) {

AddMember(p);
*members += 1;

}
if (NewSender(p) && (TypeOfEvent(e) == EVENT_REPORT)) {

AddSender(p);
*senders += 1;

}

} else if (PacketType(p) == PACKET_BYE) {

*avg_rtcp_size = (1./16.)*ReceivedPacketSize(p) +

(15./16.)*(*avg_rtcp_size);

if (TypeOfEvent(e) == EVENT_REPORT) {
if (NewSender(p) == FALSE) {

RemoveSender(p);

Schulzrinne, et al.

Standards Track

[Page 79]

RFC 3550

RTP

July 2003

*senders -= 1;

}

if (NewMember(p) == FALSE) {

RemoveMember(p);
*members -= 1;

}

if (*members < *pmembers) {

tn = tc +

(((double) *members)/(*pmembers))*(tn - tc);

*tp = tc -

(((double) *members)/(*pmembers))*(tc - *tp);

/* Reschedule the next report for time tn */

Reschedule(tn, e);
*pmembers = *members;

}

} else if (TypeOfEvent(e) == EVENT_BYE) {

*members += 1;

}

}

}

A.8 Estimating the Interarrival Jitter

The code fragments below implement the algorithm given in Section 6.4.1 for calculating an estimate
of the statistical variance of the RTP data interarrival time to be inserted in the interarrival jitter
(cid:12)eld of reception reports. The inputs are r->ts, the timestamp from the incoming packet, and
arrival, the current time in the same units. Here s points to state for the source; s->transit
holds the relative transit time for the previous packet, and s->jitter holds the estimated jitter.
The jitter (cid:12)eld of the reception report is measured in timestamp units and expressed as an unsigned
integer, but the jitter estimate is kept in a ﬂoating point. As each data packet arrives, the jitter
estimate is updated:

int transit = arrival - r->ts;
int d = transit - s->transit;
s->transit = transit;
if (d < 0) d = -d;
s->jitter += (1./16.) * ((double)d - s->jitter);

Schulzrinne, et al.

Standards Track

[Page 80]

RFC 3550

RTP

July 2003

When a reception report block (to which rr points) is generated for this member, the current jitter
estimate is returned:

rr->jitter = (u_int32) s->jitter;

Alternatively, the jitter estimate can be kept as an integer, but scaled to reduce round-o(cid:11) error.
The calculation is the same except for the last line:

s->jitter += d - ((s->jitter + 8) >> 4);

In this case, the estimate is sampled for the reception report as:

rr->jitter = s->jitter >> 4;

Appendix B. Changes from RFC 1889

Most of this RFC is identical to RFC 1889. There are no changes in the packet formats on the wire,
only changes to the rules and algorithms governing how the protocol is used. The biggest change
is an enhancement to the scalable timer algorithm for calculating when to send RTCP packets:

(cid:15) The algorithm for calculating the RTCP transmission interval speci(cid:12)ed in Sections 6.2 and 6.3
and illustrated in Appendix A.7 is augmented to include \reconsideration" to minimize trans-
mission in excess of the intended rate when many participants join a session simultaneously,
and \reverse reconsideration" to reduce the incidence and duration of false participant time-
outs when the number of participants drops rapidly. Reverse reconsideration is also used to
possibly shorten the delay before sending RTCP SR when transitioning from passive receiver
to active sender mode.

(cid:15) Section 6.3.7 speci(cid:12)es new rules controlling when an RTCP BYE packet should be sent in
order to avoid a ﬂood of packets when many participants leave a session simultaneously.

(cid:15) The requirement to retain state for inactive participants for a period long enough to span
typical network partitions was removed from Section 6.2.1. In a session where many partic-
ipants join for a brief time and fail to send BYE, this requirement would cause a signi(cid:12)cant
overestimate of the number of participants. The reconsideration algorithm added in this re-
vision compensates for the large number of new participants joining simultaneously when a
partition heals.

It should be noted that these enhancements only have a signi(cid:12)cant e(cid:11)ect when the number of ses-
sion participants is large (thousands) and most of the participants join or leave at the same time.
This makes testing in a live network di(cid:14)cult. However, the algorithm was subjected to a thorough
analysis and simulation to verify its performance. Furthermore, the enhanced algorithm was de-
signed to interoperate with the algorithm in RFC 1889 such that the degree of reduction in excess
RTCP bandwidth during a step join is proportional to the fraction of participants that implement
the enhanced algorithm. Interoperation of the two algorithms has been veri(cid:12)ed experimentally on
live networks.

Schulzrinne, et al.

Standards Track

[Page 81]

RFC 3550

RTP

July 2003

Other functional changes were:

(cid:15) Section 6.2.1 speci(cid:12)es that implementations may store only a sampling of the participants’

SSRC identi(cid:12)ers to allow scaling to very large sessions. Algorithms are speci(cid:12)ed in RFC 2762 [21].

(cid:15) In Section 6.2 it is speci(cid:12)ed that RTCP sender and non-sender bandwidths may be set as
separate parameters of the session rather than a strict percentage of the session bandwidth,
and may be set to zero. The requirement that RTCP was mandatory for RTP sessions using
IP multicast was relaxed. However, a clari(cid:12)cation was also added that turning o(cid:11) RTCP is
not recommended.

(cid:15) In Sections 6.2, 6.3.1 and Appendix A.7, it is speci(cid:12)ed that the fraction of participants below
which senders get dedicated RTCP bandwidth changes from the (cid:12)xed 1/4 to a ratio based on
the RTCP sender and non-sender bandwidth parameters when those are given. The condition
that no bandwidth is dedicated to senders when there are no senders was removed since that
is expected to be a transitory state.
It also keeps non-senders from using sender RTCP
bandwidth when that is not intended.

(cid:15) Also in Section 6.2 it is speci(cid:12)ed that the minimum RTCP interval may be scaled to smaller
values for high bandwidth sessions, and that the initial RTCP delay may be set to zero for
unicast sessions.

(cid:15) Timing out a participant is to be based on inactivity for a number of RTCP report intervals

calculated using the receiver RTCP bandwidth fraction even for active senders.

(cid:15) Sections 7.2 and 7.3 specify that translators and mixers should send BYE packets for the

sources they are no longer forwarding.

(cid:15) Rule changes for layered encodings are de(cid:12)ned in Sections 2.4, 6.3.9, 8.3 and 11.

In the
last of these, it is noted that the address and port assignment rule conﬂicts with the SDP
speci(cid:12)cation, RFC 2327 [15], but it is intended that this restriction will be relaxed in a revision
of RFC 2327.

(cid:15) The convention for using even/odd port pairs for RTP and RTCP in Section 11 was clari(cid:12)ed
to refer to destination ports. The requirement to use an even/odd port pair was removed if
the two ports are speci(cid:12)ed explicitly. For unicast RTP sessions, distinct port pairs may be
used for the two ends (Sections 3, 7.1 and 11).

(cid:15) A new Section 10 was added to explain the requirement for congestion control in applications

using RTP.

(cid:15) In Section 8.2, the requirement that a new SSRC identi(cid:12)er must be chosen whenever the
source transport address is changed has been relaxed to say that a new SSRC identi(cid:12)er may
be chosen. Correspondingly, it was clari(cid:12)ed that an implementation may choose to keep
packets from the new source address rather than the existing source address when an SSRC
collision occurs between two other participants, and should do so for applications such as
telephony in which some sources such as mobile entities may change addresses during the
course of an RTP session.

Schulzrinne, et al.

Standards Track

[Page 82]

RFC 3550

RTP

July 2003

(cid:15) An indentation bug in the RFC 1889 printing of the pseudo-code for the collision detection
and resolution algorithm in Section 8.2 has been corrected by translating the syntax to pseudo
C language, and the algorithm has been modi(cid:12)ed to remove the restriction that both RTP
and RTCP must be sent from the same source port number.

(cid:15) The description of the padding mechanism for RTCP packets was clari(cid:12)ed and it is speci(cid:12)ed

that padding must only be applied to the last packet of a compound RTCP packet.

(cid:15) In Section A.1, initialization of base seq was corrected to be seq rather than seq - 1, and the
text was corrected to say the bad sequence number plus 1 is stored. The initialization of
max seq and other variables for the algorithm was separated from the text to make clear that
this initialization must be done in addition to calling the init seq() function (and a few words
lost in RFC 1889 when processing the document from source to output form were restored).

(cid:15) Clamping of number of packets lost in Section A.3 was corrected to use both positive and

negative limits.

(cid:15) The speci(cid:12)cation of \relative" NTP timestamp in the RTCP SR section now de(cid:12)nes these
timestamps to be based on the most common system-speci(cid:12)c clock, such as system uptime,
rather than on session elapsed time which would not be the same for multiple applications
started on the same machine at di(cid:11)erent times.

Non-functional changes:

(cid:15) It is speci(cid:12)ed that a receiver must ignore packets with payload types it does not understand.

(cid:15) In Fig. 2, the ﬂoating point NTP timestamp value was corrected, some missing leading zeros

were added in a hex number, and the UTC timezone was speci(cid:12)ed.

(cid:15) The inconsequence of NTP timestamps wrapping around in the year 2036 is explained.

(cid:15) The policy for registration of RTCP packet types and SDES types was clari(cid:12)ed in a new
Section 15, IANA Considerations. The suggestion that experimenters register the numbers
they need and then unregister those which prove to be unneeded has been removed in favor
of using APP and PRIV. Registration of pro(cid:12)le names was also speci(cid:12)ed.

(cid:15) The reference for the UTF-8 character set was changed from an X/Open Preliminary Speci-

(cid:12)cation to be RFC 2279.

(cid:15) The reference for RFC 1597 was updated to RFC 1918 and the reference for RFC 2543 was

updated to RFC 3261.

(cid:15) The last paragraph of the introduction in RFC 1889, which cautioned implementors to limit

deployment in the Internet, was removed because it was deemed no longer relevant.

(cid:15) A non-normative note regarding the use of RTP with Source-Speci(cid:12)c Multicast (SSM) was

added in Section 6.

Schulzrinne, et al.

Standards Track

[Page 83]

RFC 3550

RTP

July 2003

(cid:15) The de(cid:12)nition of \RTP session" in Section 3 was expanded to acknowledge that a single session
may use multiple destination transport addresses (as was always the case for a translator
or mixer) and to explain that the distinguishing feature of an RTP session is that each
corresponds to a separate SSRC identi(cid:12)er space. A new de(cid:12)nition of \multimedia session"
was added to reduce confusion about the word \session".

(cid:15) The meaning of \sampling instant" was explained in more detail as part of the de(cid:12)nition of

the timestamp (cid:12)eld of the RTP header in Section 5.1.

(cid:15) Small clari(cid:12)cations of the text have been made in several places, some in response to questions

from readers. In particular:

– In RFC 1889, the (cid:12)rst (cid:12)ve words of the second sentence of Section 2.2 were lost in

processing the document from source to output form, but are now restored.

– A de(cid:12)nition for \RTP media type" was added in Section 3 to allow the explanation of
multiplexing RTP sessions in Section 5.2 to be more clear regarding the multiplexing of
multiple media. That section also now explains that multiplexing multiple sources of
the same medium based on SSRC identi(cid:12)ers may be appropriate and is the norm for
multicast sessions.

– The de(cid:12)nition for \non-RTP means" was expanded to include examples of other protocols

constituting non-RTP means.

– The description of the session bandwidth parameter is expanded in Section 6.2, including
a clari(cid:12)cation that the control tra(cid:14)c bandwidth is in addition to the session bandwidth
for the data tra(cid:14)c.

– The e(cid:11)ect of varying packet duration on the jitter calculation was explained in Sec-

tion 6.4.4.

– The method for terminating and padding a sequence of SDES items was clari(cid:12)ed in

Section 6.5.

– IPv6 address examples were added in the description of SDES CNAME in Section 6.5.1,

and \example.com" was used in place of other example domain names.

– The Security section added a formal reference to IPSEC now that it is available, and says
that the con(cid:12)dentiality method de(cid:12)ned in this speci(cid:12)cation is primarily to codify existing
practice. It is recommended that stronger encryption algorithms such as Triple-DES
be used in place of the default algorithm, and noted that the SRTP pro(cid:12)le based on AES
will be the correct choice in the future. A caution about the weakness of the RTP header
as an initialization vector was added. It was also noted that payload-only encryption is
necessary to allow for header compression.

– The method for partial encryption of RTCP was clari(cid:12)ed; in particular, SDES CNAME

is carried in only one part when the compound RTCP packet is split.

– It is clari(cid:12)ed that only one compound RTCP packet should be sent per reporting interval
and that if there are too many active sources for the reports to (cid:12)t in the MTU, then a
subset of the sources should be selected round-robin over multiple intervals.

– A note was added in Appendix A.1 that packets may be saved during RTP header

validation and delivered upon success.

Schulzrinne, et al.

Standards Track

[Page 84]

RFC 3550

RTP

July 2003

– Section 7.3 now explains that a mixer aggregating SDES packets uses more RTCP band-
width due to longer packets, and a mixer passing through RTCP naturally sends packets
at higher than the single source rate, but both behaviors are valid.

– Section 13 clari(cid:12)es that an RTP application may use multiple pro(cid:12)les but typically only

one in a given session.

– The terms must, should, may, etc. are used as de(cid:12)ned in RFC 2119.

– The bibliography was divided into normative and informative references.

References

Normative References

[1] Schulzrinne, H. and S. Casner, \RTP Pro(cid:12)le for Audio and Video Conferences with Minimal

Control", RFC 3551, July 2003.

[2] Bradner, S., \Key Words for Use in RFCs to Indicate Requirement Levels", BCP 14, RFC 2119,

March 1997.

[3] Postel, J., \Internet Protocol", STD 5, RFC 791, September 1981.

[4] Mills, D., \Network Time Protocol (Version 3) Speci(cid:12)cation, Implementation and Analysis",

RFC 1305, March 1992.

[5] Yergeau, F., \UTF-8, a Transformation Format of ISO 10646", RFC 2279, January 1998.

[6] Mockapetris, P., \Domain Names - Concepts and Facilities", STD 13, RFC 1034, November

1987.

[7] Mockapetris, P., \Domain Names - Implementation and Speci(cid:12)cation", STD 13, RFC 1035,

November 1987.

[8] Braden, R., \Requirements for Internet Hosts - Application and Support", STD 3, RFC 1123,

October 1989.

[9] Resnick, P., \Internet Message Format", RFC 2822, April 2001.

Informative References

[10] Clark, D. and D. Tennenhouse, \Architectural Considerations for a New Generation of Proto-
cols," in SIGCOMM Symposium on Communications Architectures and Protocols, (Philadel-
phia, Pennsylvania), pp. 200{208, IEEE Computer Communications Review, Vol. 20(4),
September 1990.

[11] Schulzrinne, H., \Issues in designing a transport protocol for audio and video conferences and

other multiparticipant real-time applications." expired Internet Draft, October 1993.

Schulzrinne, et al.

Standards Track

[Page 85]

RFC 3550

RTP

July 2003

[12] Comer, D., Internetworking with TCP/IP, vol. 1. Englewood Cli(cid:11)s, New Jersey: Prentice Hall,

1991.

[13] Rosenberg, J., Schulzrinne, H., Camarillo, G., Johnston, A., Peterson, J., Sparks, R., Handley,

M. and E. Schooler, \SIP: Session Initiation Protocol", RFC 3261, June 2002.

[14] International Telecommunication Union, \Visual telephone systems and equipment for local
area networks which provide a non-guaranteed quality of service", Recommendation H.323,
Telecommunication Standardization Sector of ITU, Geneva, Switzerland, July 2003.

[15] Handley, M. and V. Jacobson, \SDP: Session Description Protocol", RFC 2327, April 1998.

[16] Schulzrinne, H., Rao, A. and R. Lanphier, \Real Time Streaming Protocol (RTSP)", RFC 2326,

April 1998.

[17] Eastlake 3rd, D., Crocker, S. and J. Schiller, \Randomness Recommendations for Security",

RFC 1750, December 1994.

[18] Bolot, J.-C., Turletti, T. and I. Wakeman, \Scalable Feedback Control for Multicast Video
Distribution in the Internet", in SIGCOMM Symposium on Communications Architectures
and Protocols, (London, England), pp. 58{67, ACM, August 1994.

[19] Busse, I., De(cid:11)ner, B. and H. Schulzrinne, \Dynamic QoS Control of Multimedia Applications

Based on RTP", Computer Communications, vol. 19, pp. 49{58, January 1996.

[20] Floyd, S. and V. Jacobson, \The Synchronization of Periodic Routing Messages", in SIG-
COMM Symposium on Communications Architectures and Protocols (D. P. Sidhu, ed.), (San
Francisco, California), pp. 33{44, ACM, September 1993. Also in [34].

[21] Rosenberg, J. and H. Schulzrinne, \Sampling of the Group Membership in RTP", RFC 2762,

February 2000.

[22] Cadzow, J., Foundations of Digital Signal Processing and Data Analysis. New York, New York:

Macmillan, 1987.

[23] Hinden, R. and S. Deering, \Internet Protocol Version 6 (IPv6) Addressing Architecture",

RFC 3513, April 2003.

[24] Rekhter, Y., Moskowitz, B., Karrenberg, D., de Groot, G. and E. Lear, \Address Allocation

for Private Internets", RFC 1918, February 1996.

[25] Lear, E., Fair, E., Crocker, D. and T. Kessler, \Network 10 Considered Harmful (Some Prac-

tices Shouldn’t be Codi(cid:12)ed)", RFC 1627, July 1994.

[26] Feller, W., An Introduction to Probability Theory and its Applications, vol. 1. New York, New

York: John Wiley and Sons, third ed., 1968.

[27] Kent, S. and R. Atkinson, \Security Architecture for the Internet Protocol", RFC 2401, Novem-

ber 1998.

Schulzrinne, et al.

Standards Track

[Page 86]

RFC 3550

RTP

July 2003

[28] Baugher, M., Blom, R., Carrara, E., McGrew, D., Naslund, M., Norrman, K. and D. Oran,

\Secure Real-time Transport Protocol", Work in Progress, April 2003.

[29] Balenson, D., \Privacy Enhancement for Internet Electronic Mail: Part III", RFC 1423, Febru-

ary 1993.

[30] Voydock, V. and S. Kent, \Security Mechanisms in High-Level Network Protocols", ACM

Computing Surveys, vol. 15, pp. 135{171, June 1983.

[31] Floyd, S., \Congestion Control Principles", BCP 41, RFC 2914, September 2000.

[32] Rivest, R., \The MD5 Message-Digest Algorithm", RFC 1321, April 1992.

[33] Stubblebine, S., \Security Services for Multimedia Conferencing", in 16th National Computer

Security Conference, (Baltimore, Maryland), pp. 391{395, September 1993.

[34] Floyd, S. and V. Jacobson, \The Synchronization of Periodic Routing Messages", IEEE/ACM

Transactions on Networking, vol. 2, pp. 122{136, April 1994.

Schulzrinne, et al.

Standards Track

[Page 87]

RFC 3550

RTP

July 2003

Authors’ Addresses

Henning Schulzrinne
Department of Computer Science
Columbia University
1214 Amsterdam Avenue
New York, NY 10027
United States

EMail: schulzrinne@cs.columbia.edu

Stephen L. Casner
Packet Design
3400 Hillview Avenue, Building 3
Palo Alto, CA 94304
United States

EMail: casner@acm.org

Ron Frederick
Blue Coat Systems Inc.
650 Almanor Avenue
Sunnyvale, CA 94085
United States

EMail: ronf@bluecoat.com

Van Jacobson
Packet Design
3400 Hillview Avenue, Building 3
Palo Alto, CA 94304
United States

EMail: van@packetdesign.com

Schulzrinne, et al.

Standards Track

[Page 88]

RFC 3550

RTP

July 2003

Full Copyright Statement

Copyright (C) The Internet Society (2003). All Rights Reserved.

This document and translations of it may be copied and furnished to others, and derivative works
that comment on or otherwise explain it or assist in its implementation may be prepared, copied,
published and distributed, in whole or in part, without restriction of any kind, provided that the
above copyright notice and this paragraph are included on all such copies and derivative works.
However, this document itself may not be modi(cid:12)ed in any way, such as by removing the copyright
notice or references to the Internet Society or other Internet organizations, except as needed for
the purpose of developing Internet standards in which case the procedures for copyrights de(cid:12)ned
in the Internet Standards process must be followed, or as required to translate it into languages
other than English.

The limited permissions granted above are perpetual and will not be revoked by the Internet Society
or its successors or assigns.

This document and the information contained herein is provided on an \AS IS" basis and THE
INTERNET SOCIETY AND THE INTERNET ENGINEERING TASK FORCE DISCLAIMS
ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY
WARRANTY THAT THE USE OF THE INFORMATION HEREIN WILL NOT INFRINGE
ANY RIGHTS OR ANY IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS
FOR A PARTICULAR PURPOSE.

Acknowledgement

Funding for the RFC Editor function is currently provided by the Internet Society.

Schulzrinne, et al.

Standards Track

[Page 89]


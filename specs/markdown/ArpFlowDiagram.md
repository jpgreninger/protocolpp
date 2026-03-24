ARP - Address Resolution Protocol (ARP within a Subnet)

Subnet 1

Application

Host1
IP Stack

Host3
LAN Driver 1 LAN Driver 2 LAN Driver 3 Router Driver LAN Driver 4

Host2

Intranet
Router

Subnet 2
Host4

EventHelix.com/EventStudio 1.0

03-Feb-02 18:50 (Page 1)

Copyright (c) 2002 EventHelix.com Inc. All Rights Reserved.

LEG: ARP within a subnet

ARP (Address Resolution Protocol) is responsible for mapping from IP addresses to network specific addressing mechanisms. For example, ARP on Ethernet provides
mapping between 32 bit IP addresses and 48 bit MAC addresses. ARP is considered to be a low level protocol and it is generally handled at the device driver level. ARP
implementation is dependent on the underlying network technology. Here we will be describing an ARP implementation for Ethernet

Host 1 transmits first packet after booting up

IP_Packet
source = Host1, destin = Host3

IP Routing Table Lookup

IP_Packet
source = Host1, destin = Host3,
next_hop = Host3

Check ARP Cache for IP Address
to MAC Address translation

Discard Packet

Initiate ARP Processing

ARP_Request
source_protocol_addr = Host1,
source_hw_addr, destin_protocol_addr
= Host3

ARP_Request
source_protocol_addr = Host1, source_hw_addr,
destin_protocol_addr = Host3

Update ARP Cache for source
(Host1)

Discard Packet

Update ARP Cache for source
(Host1)

Application sends an IP message destined for Host 3

IP routing software consults the IP routing table to determine
the IP address of the next hop. In this case the message is being
sent to Host 3 which is directly connected to the same LAN,
thus the destination and next hop are the same address (Host 3)
The IP packet is passed to the LAN driver for transport over the
Ethernet

LAN driver needs to determine the 48 bit MAC address
corresponding to the IP Destination Address (Host3). The ARP
Cache is searched to find the MAC address corresponding to
the IP address.
IP Address to MAC address translation could not be found in
the ARP cache so this packet will be discarded. (Assuming that
higher layers will recover from this lost packet)
The Address Resolution Protocol (ARP) will be used to
determine the MAC address corresponding to the IP address

ARP sends out the ARP Request packet as a ethernet broadcast.
All machines on the ethernet receive the message as the
ethernet frame indicates that this is an ARP packet. (Here, the
broadcast is shown as multiple messages)
Host 2 processes the ARP Request packet. It checks its ARP
cache to determine if it has a mapping between the source
protocol address and the source hardware address (Host1 in this
case). If a mapping is not found, the ARP cache is updated
This ARP request does not target Host 2, so it can now discard
the packet
Host 3 processes the ARP Request packet. It checks its ARP
cache to determine if it has a mapping between the source
protocol address and the source hardware address (Host 1 in
this case)

ARP - Address Resolution Protocol (ARP within a Subnet)

Subnet 1

Application

Host1
IP Stack

Host3
LAN Driver 1 LAN Driver 2 LAN Driver 3 Router Driver LAN Driver 4

Host2

Intranet
Router

Subnet 2
Host4

ARP_Reply
source_prot_addr = Host3,
source_hw_addr, destin_prot_addr =
Host1, destin_hw_addr

ARP_Reply
source_prot_addr = Host3, source_hw_addr,
destin_prot_addr = Host1, destin_hw_addr

EventHelix.com/EventStudio 1.0

03-Feb-02 18:50 (Page 2)

Since the Destination Protocol Address in the ARP Request
matches its own IP Address, it sends back the APR reply
packet, addressing it to Host 1.

Note that even though the packet is addressed to Host 1, it will be received and processed by all nodes as the standard ethernet frame contains a field specifying that this
ethernet frame contains an ARP packet

Update ARP Cache for source
(Host3)

Update ARP Cache for source
(Host3)

IP_Packet
source = Host1, destin = Host3

IP Routing Table Lookup

Host 1 transmits second packet after booting up

IP_Packet
source = Host1, destin = Host3,
next_hop = Host3

Check ARP Cache for IP Address
to MAC Address translation

IP_Packet
source = Host1, destin = Host3

Host 1 now has a mapping from Host 3 IP address to Host 3
MAC address. This entry is updated in the ARP Cache In this
process, Host 2 has obtained the mapping for Host1 and Host 3
for free, without exchanging a single packet! Similarly Host 3
has obtained a mapping for Host 1

Application sends an IP message destined for Host 3

IP routing software consults the IP routing table to determine
the IP address of the next hop. In this case the message is being
sent to Host 3 which is directly connected to the same LAN,
thus the destination and next hop are the same IP Address (Host
3)
The IP packet is passed to the LAN driver for transport over the
Ethernet

LAN driver needs to determine the 48 bit MAC address
corresponding to the IP Destination Address (Host3). The ARP
Cache is searched to find a matching MAC address.
ARP Cache contains the mapping from Host 3 IP Address to
Host 3 MAC address, so the device driver directly sends the
message on the LAN

ARP - Address Resolution Protocol (Proxy ARP)

Subnet 1

Application

Host1
IP Stack

Host3
LAN Driver 1 LAN Driver 2 LAN Driver 3 Router Driver LAN Driver 4

Host2

Intranet
Router

Subnet 2
Host4

EventHelix.com/EventStudio 1.0

03-Feb-02 18:50 (Page 3)

Copyright (c) 2002 EventHelix.com Inc. All Rights Reserved.

LEG: ARP across subnets

Using ARP across subnets: ARP should be used only on a single physical network. ARP can also be used (misused?) to handle hosts that are not aware of subnets. Such a host
would consider a host with the same network id but a different subnet as belonging to the same physical network. Such a host will use ARP to obtain the MAC address
corresponding to the IP address in a different subnet. Implementation of Proxy ARP on the router is designed to handle this situation

In this Scenario, Host1 to Host 3 belong to Subnet 1 while Host4 belongs to Subnet 2. Router connects to both the Subnets and routes packets between them

First packet for Host 4

IP_Packet
source = Host1, destin = Host4

IP_Packet
source = Host1, destin = Host4

ARP_Request
source_protocol_addr = Host1, source_hw_addr, destin_protocol_addr = Host4

ARP_Reply
source_protocol_addr = Host4, source_hw_addr = Router_MAC_Addr,
destin_protocol_addr = Host1, destin_hw_addr

Second packet for Host 4

IP_Packet
source = Host1, destin = Host4

IP_Packet
source = Host1, destin = Host4

IP_Packet
source = Host1, destin = Host4, destin_mac_addr = Router

IP_Packet
source = Host1, destin = Host4,
destin_mac_addr = Host4_mac_addr

An application generates an IP packet for Host4, a machine on
a different subnet
Packet for Host 4 is passed to the LAN Driver

Host1 is not aware that Host4 is on a different subnet, it
assumes that Host4 is on the same physical network. Thus it
sends out an ARP Request for Host4. This broadcast is received
by the Router
Router realizes that Host 1 thinks that Host 4 is on the same
physical network. (That's why it is attempting to use ARP).
Router recognizes the Host 4 machine as connected to Subnet2.
Thus it sends an ARP Reply indicating that its own MAC
address should be used to send packets to Host 4

An application generates another IP packet for Host4

Packet for Host 4 is passed to the LAN Driver

As a result of the ARP reply, the ARP Cache maps Host 4 IP
address to Routers MAC address. Thus the packet is forwarded
to the Router
Router routes the packet to Host 4 on a different subnet


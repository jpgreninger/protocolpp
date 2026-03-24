JEDEC
STANDARD

PMIC50x0 Power Management IC Standard

JPGNetworksLLC

JESD301-1A.02
Rev. 1.8.5
(Editorial Revision of JESD301-1A.01, October 2022)

March 2023

JEDEC SOLID STATE TECHNOLOGY ASSOCIATION

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

NOTICE

JEDEC standards and publications contain material that has been prepared, reviewed, and approved
through the JEDEC Board of Directors level and subsequently reviewed and approved by the JEDEC
legal counsel.

JEDEC standards and publications are designed to serve the public interest through eliminating
misunderstandings between manufacturers and purchasers, facilitating interchangeability and
improvement of products, and assisting the purchaser in selecting and obtaining with minimum delay
the proper product for use by those other than JEDEC members, whether the standard is to be used
either domestically or internationally.

JEDEC standards and publications are adopted without regard to whether or not their adoption may
involve patents or articles, materials, or processes. By such action JEDEC does not assume any
liability to any patent owner, nor does it assume any obligation whatever to parties adopting the
JEDEC standards or publications.

The information included in JEDEC standards and publications represents a sound approach to product
specification and application, principally from the solid state device manufacturer viewpoint. Within
the JEDEC organization there are procedures whereby a JEDEC standard or publication may be
further processed and ultimately become an ANSI standard.

No claims to be in conformance with this standard may be made unless all requirements stated in the
standard are met.

Inquiries, comments, and suggestions relative to the content of this JEDEC standard or publication
should be addressed to JEDEC at the address below, or refer to www.jedec.org under Standards and
Documents for alternative contact information.

JPGNetworksLLC

Published by
©JEDEC Solid State Technology Association 2023
3103 North 10th Street
Suite 240 South
Arlington, VA 22201-2107

JEDEC retains the copyright on this material. By downloading this file the individual agrees not to
charge for or resell the resulting material.

PRICE: Contact JEDEC

Printed in the U.S.A.
All rights reserved

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

DO NOT VIOLATE
THE
LAW!

This document is copyrighted by JEDEC and may not be
reproduced without permission.

Organizations may obtain permission to reproduce a limited
number of copies through entering into a license agreement.
For information, contact:

JPGNetworksLLC

JEDEC Solid State Technology Association
3103 North 10th Street
Suite 240 South
Arlington, VA 22201-2107
https://www.jedec.org/contact

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

This page intentionally left blank

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JEDEC Standard No. 301-1A.02

DEFINITION OF PMIC5000, PMIC5010 VOLTAGE REGULATOR DEVICE FOR
MEMORY MODULE APPLICATIONS

Contents

Pages
Scope  ......................................................................................................................................... 1
1
Device Standard  ....................................................................................................................... 1
2
 Description ................................................................................................................................. 1
2.1
  Common Features Summary  ..................................................................................................... 2
2.1.1
Input Supply and Output Regulator Electrical Characteristics .................................................. 3
2.2
  Input Supply Electrical Characteristics  ..................................................................................... 3
2.2.1
  Switch Regulator Output Electrical Characteristics  .................................................................. 4
2.2.2
  Switch Regulator Efficiency ...................................................................................................... 9
2.2.3
  LDO Output Regulator Characteristics  ................................................................................... 10
2.2.4
  PMIC AC Timing Parameters  ................................................................................................. 11
2.2.5
I2C, I3C Basic and Interface DC and AC Electrical Characteristics  ...................................... 12
2.3
  Thermal Characteristics  ........................................................................................................... 17
2.4
  Absolute Maximum Rating ...................................................................................................... 18
2.5
  Example Schematic  ................................................................................................................. 20
2.6
 Functional Operation  ............................................................................................................... 23
2.7
  PMIC Input Voltage Supplies and Ramp Condition  ............................................................... 23
2.7.1
  Power Up Initialization Sequence  ........................................................................................... 23
2.7.2
  Power Up Sequence ................................................................................................................. 25
2.7.3
  Enabling PMIC Output Switch Voltage Regulators ................................................................ 29
2.7.4
  Power Down Output Regulators .............................................................................................. 30
2.7.5
  Power Down Output Regulators During Power On Sequence  ................................................ 31
2.7.6
  CAMP Signal ........................................................................................................................... 31
2.7.7
2.7.7.1      Register Write Protect Function  ............................................................................................. 32
2.7.7.2      Fail_n Function ....................................................................................................................... 32
2.7.7.3      Status Function  ....................................................................................................................... 32
   GSI_n Signal ........................................................................................................................... 33
2.7.8
   State Transition Diagram ........................................................................................................ 33
2.7.9
 Function Interrupt - CAMP and GSI_n Output Signals  ......................................................... 35
2.7.10
 Input Power Good Status  ........................................................................................................ 38
2.7.11
 Input Over Voltage Protection ................................................................................................ 38
2.7.12
 Output Power Good Status  ..................................................................................................... 39
2.7.13
 Output Over Voltage Protection  ............................................................................................. 40
2.7.14
2.7.14.1       DDR5 RDIMM/LRDIMM Environment - Table 166,

JPGNetworksLLC

“Register 0x4F” [7] = ‘0’: ....................................................................................................... 40

2.7.14.2       DDR5 NVDIMM or other Custom Environment: Table 166,

“Register 0x4F”[7]=‘1’  ........................................................................................................... 40
 Output Under Voltage and VIN_Bulk Under Voltage Lockout Protection  ........................... 41

2.7.15
2.7.15.1       DDR5 RDIMM/LRDIMM Environment - Table 166,

“Register 0x4F” [7] = ‘0’: ....................................................................................................... 41

-i-
Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JEDEC Standard No. 301-1A.02

Contents (cont’d)

2.7.15.2       DDR5 NVDIMM or other Custom Environment - Table 166,

JPGNetworksLLC

“Register 0x4F” [7]=‘1’  .......................................................................................................... 41
 Output Current Limiter Warning Event .................................................................................. 42
2.7.16
 Output High Current Consumption Warning Event  ............................................................... 42
2.7.17
 PMIC LDO Output Failure ..................................................................................................... 43
2.7.18
 PMIC High Temperature Warning and Critical Temperature Protection  .............................. 43
2.7.19
 VIN_Mgmt to VIN_Bulk Input Supply Switchover Event  .................................................... 44
2.7.20
 Valid VIN_Mgmt Supply Detection in Switchover Mode  ..................................................... 44
2.7.21
 Packet Error Code (PEC) and Parity Error Event ................................................................... 44
2.7.22
  Analog to Digital Converter (ADC)  ....................................................................................... 45
2.8
   PMIC Address ID (PID)  ......................................................................................................... 45
2.8.1
   Error Injection ......................................................................................................................... 46
2.8.2
  I2C and I3C Basic Interface Operation  .................................................................................. 46
2.9
    Device Interface - Protocol ..................................................................................................... 46
2.10
 Serial Address of PMIC Device  ............................................................................................. 47
2.10.1
 Switch from I2C Mode to I3C Basic Mode ............................................................................ 47
2.10.2
 Switch from I3C Basic Mode to I2C Mode ............................................................................ 47
2.10.3
2.10.4
 I2C Target Protocol  ................................................................................................................ 48
2.10.4.1       Write Operation - Data Packet ................................................................................................ 48
2.10.4.2       Read Operation - Data Packet ................................................................................................. 48
2.10.4.3       Default Read Address Pointer Mode  ...................................................................................... 49
2.10.5
 I3C Basic Target Protocol  ...................................................................................................... 49
2.10.5.1       Write Operation - Data Packet ................................................................................................ 50
2.10.5.2       Read Operation - Data Packet ................................................................................................. 52
2.10.5.3       Default Read Address Pointer Mode  ...................................................................................... 56
2.10.6          In Band Interrupt (IBI) ............................................................................................................ 62
2.10.6.1       Enabling and Disabling In Band Interrupt Function ............................................................... 62
2.10.6.2       Mechanics of Interrupt Generation ......................................................................................... 63
2.10.6.3       Interrupt Arbitration ................................................................................................................ 65
2.10.6.4       Clearing Device Status and IBI Status Registers .................................................................... 66
 Packet Error Check (PEC) Function ....................................................................................... 67
2.10.7
 Parity Error Check Function ................................................................................................... 67
2.10.8
 Packet Error Check and Parity Error Handling ......................................................................  67
2.10.9
2.10.9.1       Write Command Data Packet Error Handling - PEC Disabled  .............................................. 67
2.10.9.2       Read Command Data Packet Error Handling - PEC Disabled  ............................................... 68
2.10.9.3       Write Command Data Packet Error Handling - PEC Is Enabled  ........................................... 69
2.10.9.4       Read Command Data Packet Error Handling - PEC Is Enabled  ............................................ 70
2.10.10        CCC Packet Error Handling  ................................................................................................... 72
2.10.11        Error Reporting ....................................................................................................................... 72
2.10.12        I3C Basic Common Command Codes (CCC)  ........................................................................ 72
2.10.12.1     ENEC CCC ............................................................................................................................. 73
2.10.12.2     DISEC CCC ............................................................................................................................ 75
2.10.12.3     RSTDAA CCC  ....................................................................................................................... 76

-ii-
Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JEDEC Standard No. 301-1A.02

Contents (cont’d)

2.10.12.4       SETAASA CCC ...................................................................................................................  77
2.10.12.5       GETSTATUS CCC  .............................................................................................................. 77
2.10.12.6       DEVCAP CCC  ..................................................................................................................... 79
2.10.12.7       SETHID CCC  ....................................................................................................................... 80
2.10.12.8       DEVCTRL CCC ................................................................................................................... 80
 IO Operation  ......................................................................................................................... 87
2.10.13
 Bus Clear  .............................................................................................................................. 88
2.10.14
 Bus Reset  .............................................................................................................................. 89
2.10.15
 Command Truth Table .......................................................................................................... 90
2.10.16
  Device Package and Pinout  .................................................................................................. 91
2.11
   Package Pinout ...................................................................................................................... 91
2.11.1
   PMIC Package Pin List ......................................................................................................... 93
2.11.2
   Package Mechanical Drawing  .............................................................................................. 95
2.11.3
  Inductor Specification ........................................................................................................... 99
2.12
   Mechanical Specification ...................................................................................................... 99
2.12.1
   Electrical Specification ....................................................................................................... 100
2.12.2
  Application Notes  ............................................................................................................... 100
2.13
   Method to Identify and Map Out DIMM with a PMIC Fault in Shared CAMP
2.13.1
  Topology  ............................................................................................................................. 100
   Registers Space..................................................................................................................  102
    Register Attribute Definition  .............................................................................................. 102
    Register Map Breakdown  ................................................................................................... 103
Register Memory Protection ............................................................................................... 103
 Steps to Access DIMM Vendor Region Registers  ............................................................. 103
 Steps to Change DIMM Vendor Region Password  ............................................................ 104
 Steps to Burn or Program DIMM Vendor Region Registers .............................................. 104
 Host Region Register Map .................................................................................................. 105
 Host Region Registers  ........................................................................................................ 110
  Status Registers ................................................................................................................... 110
  Clear Registers .................................................................................................................... 123
  Mask Registers .................................................................................................................... 128
  Threshold and Configuration Registers  .............................................................................. 134
  DIMM Vendor Region Registers ....................................................................................... 166
  (Informative) - Differences between Revisions  .............................................................. 191
Differences between JESD301-1A and JESD301-1 (June 2020) ....................................... 191
Differences between JESD301-1A.01 and JESD301-1A (August 2021) ........................... 193
Differences between JESD301-1A.02 and JESD301-1A.01 (October 2022)  .................... 193

JPGNetworksLLC

3
3.1
3.2
3.3
3.3.1
3.3.2
3.3.3
3.3.4
3.3.5
3.3.5.1
3.3.5.2
3.3.5.3
3.3.5.4
3.3.6
Annex A
A.1
A.2
A.3

-iii-
Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JEDEC Standard No. 301-1A.02

List of Figures

Contents (cont’d)

Figure 1 — I2C or I3C Basic Bus AC Input Timing Parameter Definition  ............................................... 14
Figure 2 — I3C Basic Bus AC Data Output Timing Parameter Definition  ............................................... 15
Figure 3 — I2C Bus AC Data Output Timing Parameter Definition  ......................................................... 15
Figure 4 — Output Slew Rate and Output Timing Reference Load  .......................................................... 15
Figure 5 — Output Slew Rate Measurement Points ................................................................................... 16
Figure 6 — Rise and Fall Timing Parameter Definition  ............................................................................ 16
Figure 7 — AC Measurement Waveform  .................................................................................................. 17
Figure 8 — Impulse Waveform for EOS Test (IEC 61000-4-5)  ................................................................ 19
Figure 9 — Dual Phase Regulator Example Schematic  ............................................................................. 20
Figure 10 — Single Phase Regulator Example Schematic ......................................................................... 21
Figure 11 — PMIC Power Up Sequence; VIN_Mgmt Followed by VIN_Bulk ........................................ 25
Figure 12 — PMIC Power Up Sequence; VIN_Bulk Followed by VIN_Mgmt ........................................ 26
Figure 13 — VIN_Mgmt Input Supply to VIN_Bulk Input Supply Switchover Function  ........................ 27
Figure 14 — VIN_Bulk Transition ............................................................................................................. 28
Figure 15 — PMIC Power On Timing  ....................................................................................................... 29
Figure 16 — PMIC Power Off Timing Due to Internal Fault Condition  ................................................... 31
Figure 17 — High Level State Transitions ................................................................................................. 34
Figure 18 — Target Open Drain to Controller Push Pull Hand Off Operation .......................................... 58
Figure 19 — Controller Open Drain (ACK) to Target Push Pull Hand Off Operation .............................. 59
Figure 20 — Controller Push Pull to Target Open Drain Hand Off Operation .......................................... 60
Figure 21 — T=1; Controller Ends Read with Repeated START and STOP Waveform  .......................... 61
Figure 22 — T=0; Target Ends Read; Controller Generates STOP  ........................................................... 62
Figure 23 — PMIC Requests Interrupt, Host Ack Followed by PMIC Device IBI Payload  ..................... 64
Figure 24 — PMIC Requests Interrupt; Host NACK Followed by STOP ................................................. 64
Figure 25 — I2C or I3C Basic Bus Reset - PMIC Device  ......................................................................... 89
Figure 26 — PMIC Pinout - TOP View  ..................................................................................................... 91
Figure 27 — PMIC Pinout - BOTTOM View ............................................................................................ 92
Figure 28 — Package Mechanical Outline ................................................................................................. 95
Figure 29 — Detail A Drawing  .................................................................................................................. 96
Figure 30 — Detail B Drawing  .................................................................................................................. 97
Figure 31 — Reference PCB Land Pattern ................................................................................................. 98
Figure 32 — Reference Drawing and Recommended Land Pattern  .......................................................... 99
Figure 33 — Error Log (R05 to R07) Registers Behavior with Power Cycle .......................................... 111

JPGNetworksLLC

List of Tables

Table 1 — PMIC Device Type Summary  .................................................................................................... 2
Table 2 — Input Supply DC + AC Specification  ......................................................................................... 3
Table 3 — SWA, SWB1 - Single Phase Regulator; PMIC5000; DC + AC Specification  .......................... 4
Table 4 — SWA + SWB1 - Dual Phase Regulator; PMIC5000; DC + AC Specification ........................... 5
Table 5 — SWA, SWB1 - Single Phase Regulator; PMIC5010; DC + AC Specification  .......................... 5

-iv-
Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JEDEC Standard No. 301-1A.02

Contents (cont’d)

Table 6 — SWA + SWB1 - Dual Phase Regulator; PMIC5010; DC + AC Specification ........................... 6
Table 7 — SWC1 - Single Phase Regulator; PMIC5000; DC + AC Specification  ..................................... 6
Table 8 — SWC1 -  Single Phase Regulator; PMIC5010; DC + AC Specification  .................................... 7
Table 9 — SWD1 - Single Phase Regulator; PMIC5000; DC + AC Specification  ..................................... 7
Table 10 — SWD1 - Single Phase Regulator; PMIC5010; DC + AC Specification  ................................... 8
Table 11 — Efficiency Characteristics; PMIC5000 ..................................................................................... 9
Table 12 — Efficiency Characteristics; PMIC5010 ..................................................................................... 9
Table 13 — LDO Output Regulator DC + AC Specification ..................................................................... 10
Table 14 — PMIC AC Timing Parameters  ................................................................................................ 11
Table 15 — I2C, I3C, and Interface DC Electrical Specification  .............................................................. 12
Table 16 — Input Capacitance Spec  .......................................................................................................... 12
Table 17 — Input Spike Filter Spec  ........................................................................................................... 12
Table 18 — Output Ron  ............................................................................................................................. 12
Table 19 — I2C and I3C Interface AC Characteristics .............................................................................. 13
Table 20 — AC Measurement Conditions1  ............................................................................................... 17
Table 21 — Thermal Characteristics .......................................................................................................... 17
Table 22 — Absolute Maximum Rating  .................................................................................................... 18
Table 23 — ESD Requirement  ................................................................................................................... 18
Table 24 — EOS Requirement  ................................................................................................................... 18
Table 25 — Input Source Condition ........................................................................................................... 19
Table 26 — PMIC Schematic Values ......................................................................................................... 22
Table 27 — Events Interrupt Summary ...................................................................................................... 35
Table 28 — PMIC Response for Clear Command by Host - 1  .................................................................. 36
Table 29 — PMIC Response for Clear Command by Host - 2  .................................................................. 37
Table 30 — PMIC ID  ................................................................................................................................. 45
Table 31 — 7-bit Address of PMIC Device  ............................................................................................... 47
Table 32 — Write Command Data Packet  ................................................................................................. 48
Table 33 — Read Command Data Packet  .................................................................................................. 48
Table 34 — Read Command Data Packet with Default Address Pointer Mode  ........................................ 49
Table 35 — Write Command Data Packet; PEC Disabled ......................................................................... 50
Table 36 — Write Command Data Packet; PEC Enabled .......................................................................... 50
Table 37 — Write Command Data Packet with IBI Header; No Pending IBI, PEC Disabled  .................. 51
Table 38 — Write Command Data Packet with IBI Header; No Pending IBI, PEC Enabled  ................... 51
Table 39 — Read Command Data Packet; PEC Disabled  ......................................................................... 52
Table 40 — Read Command Data Packet; PEC Enabled ........................................................................... 53
Table 41 — Read Command Data Packet with IBI Header; No Pending IBI, PEC Disabled  ................... 54
Table 42 — Read Command Data Packet with IBI Header; No Pending IBI, PEC Enabled  .................... 55
Table 43 — Read Command Data Packet with Read Address Pointer Mode; PEC Disabled  ................... 56
Table 44 — Read Command Data Packet with Read Address Pointer Mode; PEC Enabled  .................... 56
Table 45 — Read Command Data Packet with Read Address Pointer and IBI Header; No Pending

JPGNetworksLLC

IBI; PEC Disabled ................................................................................................................... 57

Table 46 — Read Command Data Packet with Read Address Pointer and IBI Header; No Pending

IBI; PEC Enabled .................................................................................................................... 57

-v-
Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JEDEC Standard No. 301-1A.02

Contents (cont’d)

Table 47 — Target Device IBI Payload Packet; PEC is Disabled  ............................................................. 63
Table 48 — Target Device IBI Payload Packet; PEC is Enabled  .............................................................. 64
Table 49 — Interrupt Arbitration - Among All Devices  ............................................................................ 65
Table 50 — Write Command Data Packet; PEC Disabled ......................................................................... 68
Table 51 — Read Command Data Packet; PEC Disabled  ......................................................................... 69
Table 52 — Write Command Data Packet; PEC Enabled .......................................................................... 70
Table 53 — Read Command Data Packet; PEC Enabled ........................................................................... 71
Table 54 — PMIC CCC Support Requirement  .......................................................................................... 73
Table 55 — ENEC CCC - Broadcast  ......................................................................................................... 73
Table 56 — ENEC CCC - Broadcast with PEC  ......................................................................................... 74
Table 57 — ENEC CCC - Direct  ............................................................................................................... 74
Table 58 — ENEC CCC - Direct with PEC  ............................................................................................... 74
Table 59 — ENEC CCC Byte Encoding .................................................................................................... 75
Table 60 — DISEC CCC - Broadcast  ........................................................................................................ 75
Table 61 — DISEC CCC - Broadcast with PEC ........................................................................................ 75
Table 62 — DISEC CCC - Direct  .............................................................................................................. 76
Table 63 — DISEC CCC - Direct with PEC .............................................................................................. 76
Table 64 — DISEC CCC Byte Encoding ................................................................................................... 76
Table 65 — RSTDAA CCC - Broadcast .................................................................................................... 77
Table 66 — RSTDAA CCC - Broadcast with PEC  ................................................................................... 77
Table 67 — SETAASA CCC - Broadcast .................................................................................................. 77
Table 68 — GETSTATUS CCC - Direct  ................................................................................................... 78
Table 69 — GETSTATUS CCC - Direct with PEC ................................................................................... 78
Table 70 — GETSTATUS CCC Byte Encoding  ....................................................................................... 78
Table 71 — DEVCAP CCC - Direct .......................................................................................................... 79
Table 72 — DEVCAP CCC - Direct with PEC  ......................................................................................... 79
Table 73 — DEVCAP CCC Byte Encoding  .............................................................................................. 80
Table 74 — SETHID CCC - Broadcast ...................................................................................................... 80
Table 75 — DEVCTRL CCC - Broadcast  ................................................................................................. 81
Table 76 — DEVCTRL CCC - Broadcast with PEC1  ............................................................................... 82
Table 77 — DEVCTRL CCC Command Definition .................................................................................. 83
Table 78 — DEVCTRL CCC Data Payload Definition ............................................................................. 84
Table 79 — DEVCTRL CCC Example - Multicast Command to ‘1001’ and ‘0110’ Devices  ................. 85
Table 80 — DEVCTRL CCC Example - Broadcast Command to all Devices .......................................... 85
Table 81 — DEVCTRL CCC Example - Unicast Command to PMIC on DIMM5  .................................. 86
Table 82 — DEVCTRL CCC Example - Multicast Command to ‘0010’ and ‘1001’ Devices  ................. 86
Table 83 — DEVCTRL CCC Example - Multicast Command to ‘1001’ Devices .................................... 87
Table 84 — PMIC Device Dynamic IO Operation Mode Switching ......................................................... 88
Table 85 — For I3C Mode Only with PEC Enabled - Command Truth Table .......................................... 90
Table 86 — PMIC Pin Description  ............................................................................................................ 93
Table 87 — Inductor Mechanical Specification ......................................................................................... 99
Table 88 — Inductor Electrical Specification1  ........................................................................................ 100
Table 89 — Register Base Attributes  ....................................................................................................... 102

JPGNetworksLLC

-vi-
Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JEDEC Standard No. 301-1A.02

Contents (cont’d)

Table 90 — Register Attribute Modifier  .................................................................................................. 102
Table 91 — Register Map Breakdown  ..................................................................................................... 103
Table 92 — Register Color Coding Scheme  ............................................................................................ 105
Table 93 — Host Region - Register Map  ................................................................................................. 105
Table 94 — Register 0x04 ........................................................................................................................ 112
Table 95 — Register 0x05 ........................................................................................................................ 113
Table 96 — Register 0x06 ........................................................................................................................ 114
Table 97 — Register 0x07 ........................................................................................................................ 115
Table 98 — Register 0x08 ........................................................................................................................ 116
Table 99 — Register 0x09 ........................................................................................................................ 117
Table 100 — Register 0x0A  ..................................................................................................................... 118
Table 101 — Register 0x0B  ..................................................................................................................... 119
Table 102 — Register 0x0C  ..................................................................................................................... 120
Table 103 — Register 0x0D  ..................................................................................................................... 121
Table 104 — Register 0x0E  ..................................................................................................................... 122
Table 105 — Register 0x0F ...................................................................................................................... 123
Table 106 — Register 0x10 ...................................................................................................................... 124
Table 107 — Register 0x11 ...................................................................................................................... 125
Table 108 — Register 0x12 ...................................................................................................................... 126
Table 109 — Register 0x13 ...................................................................................................................... 127
Table 110 — Register 0x14 ...................................................................................................................... 128
Table 111 — Register 0x15 ...................................................................................................................... 129
Table 112 — Register 0x16 ...................................................................................................................... 130
Table 113 — Register 0x17 ...................................................................................................................... 131
Table 114 — Register 0x18 ...................................................................................................................... 132
Table 115 — Register 0x19 ...................................................................................................................... 133
Table 116 — Register 0x1A  ..................................................................................................................... 134
Table 117 — Register 0x1B  ..................................................................................................................... 135
Table 118 — Register 0x1C  ..................................................................................................................... 136
Table 119 — Register 0x1D  ..................................................................................................................... 137
Table 120 — Register 0x1E  ..................................................................................................................... 138
Table 121 — Register 0x1F ...................................................................................................................... 139
Table 122 — Register 0x20 ...................................................................................................................... 140
Table 123 — Register 0x21 ...................................................................................................................... 142
Table 124 — Register 0x22 ...................................................................................................................... 143
Table 125 — Register 0x23 ...................................................................................................................... 144
Table 126 — Register 0x24 ...................................................................................................................... 145
Table 127 — Register 0x25 ...................................................................................................................... 146
Table 128 — Register 0x26 ...................................................................................................................... 147
Table 129 — Register 0x27 ...................................................................................................................... 148
Table 130 — Register 0x28 ...................................................................................................................... 149
Table 131 — Register 0x29 ...................................................................................................................... 150
Table 132 — Register 0x2A  ..................................................................................................................... 151

JPGNetworksLLC

-vii-
Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JEDEC Standard No. 301-1A.02

Contents (cont’d)

Table 133 — Register 0x2B  ..................................................................................................................... 152
Table 134 — Register 0x2C  ..................................................................................................................... 153
Table 135 — Register 0x2D  ..................................................................................................................... 154
Table 136 — Register 0x2E  ..................................................................................................................... 154
Table 137 — Register 0x2F ...................................................................................................................... 155
Table 138 — Register 0x30 ...................................................................................................................... 157
Table 139 — Register 0x31 ...................................................................................................................... 158
Table 140 — Register 0x32 ...................................................................................................................... 159
Table 141 — Register 0x33 ...................................................................................................................... 160
Table 142 — Register 0x34 ...................................................................................................................... 161
Table 143 — Register 0x35 ...................................................................................................................... 162
Table 144 — Register 0x37 ...................................................................................................................... 163
Table 145 — Register 0x38 ...................................................................................................................... 163
Table 146 — Register 0x39 ...................................................................................................................... 163
Table 147 — Register 0x3A  ..................................................................................................................... 164
Table 148 — Register 0x3B  ..................................................................................................................... 165
Table 149 — Register 0x3C  ..................................................................................................................... 165
Table 150 — Register 0x3D  ..................................................................................................................... 165
Table 151 — DIMM Vendor Region - Register Map  .............................................................................. 166
Table 152 — Register 0x40 ...................................................................................................................... 168
Table 153 — Register 0x41 ...................................................................................................................... 169
Table 154 — Register 0x42 ...................................................................................................................... 170
Table 155 — Register 0x43....................................................................................................................... 171
Table 156 — Register 0x45 ...................................................................................................................... 172
Table 157 — Register 0x46 ...................................................................................................................... 173
Table 158 — Register 0x47 ...................................................................................................................... 174
Table 159 — Register 0x48 ...................................................................................................................... 175
Table 160 — Register 0x49 ...................................................................................................................... 176
Table 161 — Register 0x4A  ..................................................................................................................... 177
Table 162 — Register 0x4B  ..................................................................................................................... 178
Table 163 — Register 0x4C  ..................................................................................................................... 179
Table 164 — Register 0x4D  ..................................................................................................................... 180
Table 165 — Register 0x4E  ..................................................................................................................... 181
Table 166 — Register 0x4F ...................................................................................................................... 182
Table 167 — Register 0x50 ...................................................................................................................... 183
Table 168 — Register 0x51 ...................................................................................................................... 185
Table 169 — Register 0x58 ...................................................................................................................... 186
Table 170 — Register 0x59 ...................................................................................................................... 187
Table 171 — Register 0x5A ...................................................................................................................... 188
Table 172 — Register 0x5B ...................................................................................................................... 189
Table 173 — Register 0x5D  ..................................................................................................................... 190
Table 174 — Register 0x5E  ..................................................................................................................... 190

JPGNetworksLLC

-viii-
Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

DEFINITION of PMIC5000, PMIC5010 VOLTAGE REGULATOR DEVICE for
MEMORY MODULE APPLICATIONS

JEDEC Standard No. 301-1A.02
Page 1

From JEDEC Board Ballot JCB-22-06, formulated under the cognizance of the JC-40.1 Subcommittee on Digital

Logic Families and Applications, item 325.29D.

1

Scope

This standard defines the specifications of interface parameters, signaling protocols, and features for PMIC device as
used for memory module applications. The designation PMIC5000, PMIC5010 refers to the device specified by this
document.

The purpose is to provide a standard for the PMIC5000, PMIC5010 device for uniformity, multiplicity of sources,
elimination of confusion, ease of device specification, and ease of use.

Unless otherwise noted in the document, any illegal operation is not allowed and device operation is not guaranteed.

NOTE:  The  designation  PMIC5000,  PMIC5010  refers  to  a  portion  of  the  part  number  designation  of  a  series  of
commercial logic devices common in the industry. This number is normally preceded by a series of manufacturer
specific characters to make up a complete part designation.

JPGNetworksLLC

The PMIC5000 and PMIC5010 is designed for typical DDR5 RDIMM, DDR5 LRDIMM as well as various types of
DDR5 NVDIMM application. The PMIC features four step down switching regulators and three LDO regulators.

The PMIC is designed to support approximately 15 Watts of power. The PMIC is powered from VIN_Bulk input for
switching regulators and VIN_Mgmt input for the rest of the PMIC. The PMIC supports selectable interface (I2C or
I3C Basic) to fit various application environment. The PMIC device is intended to operate up to 12.5 MHz on a 1.0 V
I3C Basic bus or up to 1 MHz on a 1.0 V to 3.3 V I2C bus.

2

Device Standard

2.1   Description

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 2

2.1.1   Common Features Summary

Table 1 — PMIC Device Type Summary

Device Type
PMIC5000 - Current Capability per Phase
PMIC5010 - Current Capability per Phase

SWA
5
3

SWB
5
3

SWC
5
3

SWD
5
3

Unit
A
A

•  VIN_Bulk input supply range: 4.25 V to 15.0 V
•  VIN_Mgmt input supply range: 3.0 V to 3.6 V
•  Four step down switching regulators: SWA, SWB, SWC and SWD
•  Programmable dual phase and single phase regulator for SWA and SWB
•  3 LDO regulators: VBias, VOUT_1.8V, VOUT_1.0V
•  Automatic switchover from VIN_Mgmt input supply to VIN_Bulk input supply
•  Error injection capability
•  Persistent Error log registers
•  Write protect mode and programmable of operation
•  Independently programmable output voltages, power up and power down sequence for switch regulators
•  Input and output power good status reporting mechanism
•  VIN_Bulk input supply protection feature: Input over voltage
•  Output switch regulators protection feature: Output over voltage, output under voltage, output current

JPGNetworksLLC

•  Output current and power measurement, output current threshold mechanism
•  Temperature measurement, temperature warning threshold, critical temperature shutdown
•  Multi Time Programmable Non-Volatile Memory
•  Programmable and DIMM specific registers for customization
•  General Status Interrupt Function
•  Flexible Open Drain IO (I2C) and Push Pull (I3C Basic) IO Support

limiter

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 3

2.2   Input Supply and Output Regulator Electrical Characteristics

2.2.1   Input Supply Electrical Characteristics

Table 2 — Input Supply DC + AC Specification

Parameter

Symbol
VIN_Bulk
VIN_Bulk_AC

Min
4.25
-

Typ Max
15
12
18
-

Unit
V
V

Notes

1,2

VIN_Bulk_Ramp_Up

VIN_Bulk_OS_Startup

Bulk Input Supply Voltage DC Voltage
Bulk Input Supply Maximum AC Voltage
Bulk Input Supply Maximum Voltage Start
up Overshoot
Bulk Input Supply Voltage Ramp Up Rate
Bulk Input Supply Voltage Ramp Down
Rate
Management Input Supply Voltage
Management Input Supply Ramp Up and
Down Rate
Minimum Management Input Supply
Current
IVIN_Bulk
Bulk Input Supply Current
NOTE 1 During first power on, the input voltage supply must reach minimum value based on default from register Table 116, “Register 0x1A”

VIN_Bulk_Ramp_Down

IVIN_Mgmt

VIN_Mgmt

V/ms

V/ms

V/ms

V*μs

mA

0.1

3.0

3.0

1.0

3.3

3.6

2.5

33

V

A

3

3

4

5

6

7

8

-

-

-

-

-

-

NOTE 2 The PMIC efficiency is optimized for nominal input supply of 12 V or lower. The PMIC efficiency above 13.8 V is degraded and

thermal impact must be considered. The PMIC operation above 14.2V should not be greater than 20% duty cycle at any time and should
be limited to a maximum contiguous period of 10 minutes.

NOTE 3 The area under the curve above VIN_Bulk = 15V. VIN_Bulk_AC spec must also be satisfied.
NOTE 4 The ramp up rate between 300 mV and 8.0 V.
NOTE 5 The ramp down rate between 8.0 V and 300 mV.
NOTE 6 During first power on, the input voltage supply must reach minimum value of 2.8 V for PMIC to detect valid input supply.
NOTE 7 This is a platform spec. The minimum input current delivered by the platform through the DIMM gold finger to deliver the maximum
load on LDO outputs (1.8V LDO output + 1.0V LDO output = 25 mA + 20 mA) plus the current required by the PMIC for its own
usage.

NOTE 8 This is a platform spec. The maximum input current delivered by the platform through the DIMM gold finger.

-

-

110

0.15

VIN_Mgmt_Ramp

JPGNetworksLLC

[7:5] + 1.0V for PMIC to detect valid input supply.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 4

2.2.2   Switch Regulator Output Electrical Characteristics

Table 3 — SWA, SWB1 - Single Phase Regulator; PMIC5000; DC + AC Specification

Parameter

Symbol

Min

Max

Unit

Notes

Output Voltage
Maximum Continuous DC Current Load

Maximum Peak Instantaneous Current

Vout
Itdc
Ipeakmax
dI/dt

Typ

1.1
-

-
-

0

-
-
-2.5%
-0.75%

2
3

4

V
A

5

A
A/μs

6
5
2.5%
0.75%

Maximum Load Transient
Regulator Output DC + AC Voltage Tolerance Reg_DC_AC_Tol
Regulator Feedback Set Point Accuracy
NOTE 1 Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.
NOTE 2 Typical voltage configured in the register Table 123, “Register 0x21” [7:1] for SWA and Table 125, “Register 0x23” [7:1] for SWB.
NOTE 3 Measured over long period of time. Typically 1 second.
NOTE 4 Measured over short period of time. Typically > 20 μs but less than 50 μs.
NOTE 5 The percentage applies to typical voltage configured in the register. Applies across entire PMIC operating temperature range. The
PMIC bulk input supply voltage VIN_Bulk can vary from minimum to maximum value specified in Table 2, “Input Supply DC + AC
Specification”. The regulator output current load can vary maximum dI/dt value. The output ripple is inclusive in this parameter and
not to exceed TBD mV.

FB_Set_Point

5
6

NOTE 6 The percentage applies to typical voltage configured in the register and at a given temperature within operating temperature range.

The PMIC bulk input supply voltage VIN_Bulk is fixed at nominal voltage of 12.0 V. The regulator output current load Itdc = 0 A.

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

2
3

4

2
3

4

Table 5 — SWA, SWB1 - Single Phase Regulator; PMIC5010; DC + AC Specification

JEDEC Standard No. 301-1A.02
Page 5

 2.2.2 Switch Regulator Output Electrical Characteristics (cont’d)

Table 4 — SWA + SWB1 - Dual Phase Regulator; PMIC5000; DC + AC Specification

Parameter

Symbol

Min

Max

Unit

Notes

Output Voltage
Maximum Continuous DC Current Load

Maximum Peak Instantaneous Current

Vout
Itdc
Ipeakmax
dI/dt

Typ

1.1
-

-
-

0

-
-
-2.5%
-0.75%

V
A

10

A
A/μs

12
10
2.5%
0.75%

Maximum Load Transient
Regulator Output DC + AC Voltage Tolerance Reg_DC_AC_Tol
Regulator Feedback Set Point Accuracy
NOTE 1 Only applicable if Table 166, “Register 0x4F” [0], = ‘1’.
NOTE 2 Typical voltage configured in the register Table 123, “Register 0x21” [7:1].
NOTE 3 Measured over long period of time. Typically 1 second.
NOTE 4 Measured over short period of time. Typically > 20 μs but less than 50 μs.
NOTE 5 The percentage applies to typical voltage configured in the register. Applies across entire PMIC operating temperature range. The
PMIC bulk input supply voltage VIN_Bulk can vary from minimum to maximum value specified in Table 2, “Input Supply DC + AC
Specification”. The regulator output current load can vary maximum dI/dt value. The output ripple is inclusive in this parameter and
not to exceed TBD mV.

FB_Set_Point

5
6

NOTE 6 The percentage applies to typical voltage configured in the register and at a given temperature within operating temperature range.

The PMIC bulk input supply voltage VIN_Bulk is fixed at nominal voltage of 12.0 V. The regulator output current load Itdc = 0 A.

JPGNetworksLLC

Vout
Itdc
Ipeakmax
dI/dt

-
-
-2.5%
-0.75%

Symbol

1.1
-

Min

Typ

-
-

0

Max

Unit

Notes

V
A

3

A
A/μs

3.5
5
2.5%
0.75%

Maximum Load Transient
Regulator Output DC + AC Voltage Tolerance Reg_DC_AC_Tol
Regulator Feedback Set Point Accuracy
NOTE 1 Only applicable if Table 166, “Register 0x4F” [0], = ‘1’.
NOTE 2 Typical voltage configured in the register Table 123, “Register 0x21” [7:1] for SWA and Table 125, “Register 0x23” [7:1] for SWB.
NOTE 3 Measured over long period of time. Typically 1 second.
NOTE 4 Measured over short period of time. Typically > 20 μs but less than 50 μs.
NOTE 5 The percentage applies to typical voltage configured in the register. Applies across entire PMIC operating temperature range. The
PMIC bulk input supply voltage VIN_Bulk can vary from minimum to maximum value specified in Table 2, “Input Supply DC + AC
Specification”. The regulator output current load can vary maximum dI/dt value. The output ripple is inclusive in this parameter and
not to exceed TBD mV.

FB_Set_Point

5
6

NOTE 6 The percentage applies to typical voltage configured in the register and at a given temperature within operating temperature range.

The PMIC bulk input supply voltage VIN_Bulk is fixed at nominal voltage of 12.0 V. The regulator output current load Itdc = 0 A.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

Parameter

Output Voltage
Maximum Continuous DC Current Load

Maximum Peak Instantaneous Current

2
3

4

2
3

4

Table 7 — SWC1 - Single Phase Regulator; PMIC5000; DC + AC Specification

JEDEC Standard No. 301-1A.02
Page 6

2.2.2 Switch Regulator Output Electrical Characteristics (cont’d)

Table 6 — SWA + SWB1 - Dual Phase Regulator; PMIC5010; DC + AC Specification

Parameter

Symbol

Min

Max

Unit

Notes

Output Voltage
Maximum Continuous DC Current Load

Maximum Peak Instantaneous Current

Vout
Itdc
Ipeakmax
dI/dt

Typ

1.1
-

-
-

0

-
-
-2.5%
-0.75%

V
A

6

A
A/μs

7
10
2.5%
0.75%

Maximum Load Transient
Regulator Output DC + AC Voltage Tolerance Reg_DC_AC_Tol
Regulator Feedback Set Point Accuracy
NOTE 1 Only applicable if Table 166, “Register 0x4F” [0], = ‘1’.
NOTE 2 Typical voltage configured in the register Table 123, “Register 0x21” [7:1].
NOTE 3 Measured over long period of time. Typically 1 second.
NOTE 4 Measured over short period of time. Typically > 20 μs but less than 50 μs.
NOTE 5 The percentage applies to typical voltage configured in the register. Applies across entire PMIC operating temperature range. The
PMIC bulk input supply voltage VIN_Bulk can vary from minimum to maximum value specified in Table 2, “Input Supply DC + AC
Specification”. The regulator output current load can vary maximum dI/dt value. The output ripple is inclusive in this parameter and
not to exceed TBD mV.

FB_Set_Point

5
6

NOTE 6 The percentage applies to typical voltage configured in the register and at a given temperature within operating temperature range.

The PMIC bulk input supply voltage VIN_Bulk is fixed at nominal voltage of 12.0 V. The regulator output current load Itdc = 0 A.

JPGNetworksLLC

Vout
Itdc
Ipeakmax
dI/dt

-
-
-2.5%
-0.75%

Symbol

1.1
-

Min

Typ

-
-

0

Max

Unit

Notes

V
A

5

A
A/μs

6
5
2.5%
0.75%

Maximum Load Transient
Regulator Output DC + AC Voltage Tolerance Reg_DC_AC_Tol
Regulator Feedback Set Point Accuracy
NOTE 1 There is no note. This is intentional.
NOTE 2 Typical voltage configured in the register Table 127, “Register 0x25” [7:1].
NOTE 3 Measured over long period of time. Typically 1 second.
NOTE 4 Measured over short period of time. Typically > 20 μs but less than 50 μs.
NOTE 5 The percentage applies to typical voltage configured in the register. Applies across entire PMIC operating temperature range. The
PMIC bulk input supply voltage VIN_Bulk can vary from minimum to maximum value specified in Table 2, “Input Supply DC + AC
Specification”. The regulator output current load can vary maximum dI/dt value. The output ripple is inclusive in this parameter and
not to exceed TBD mV.

FB_Set_Point

5
6

NOTE 6 The percentage applies to typical voltage configured in the register and at a given temperature within operating temperature range.

The PMIC bulk input supply voltage VIN_Bulk is fixed at nominal voltage of 12.0 V. The regulator output current load Itdc = 0 A.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

Parameter

Output Voltage
Maximum Continuous DC Current Load

Maximum Peak Instantaneous Current

Table 9 — SWD1 - Single Phase Regulator; PMIC5000; DC + AC Specification

JEDEC Standard No. 301-1A.02
Page 7

2.2.2 Switch Regulator Output Electrical Characteristics (cont’d)

Table 8 — SWC1 -  Single Phase Regulator; PMIC5010; DC + AC Specification

Vout
Itdc
Ipeakmax
dI/dt

Parameter

Symbol

Min

Output Voltage
Maximum Continuous DC Current Load

Typ

1.1
-

Max

Unit

Notes

V
A

2
3

3

0

-
-

Maximum Peak Instantaneous Current
Maximum Load Transient
Regulator Output DC + AC Voltage Tolerance Reg_DC_AC_Tol
Regulator Feedback Set Point Accuracy
NOTE 1 There is no note. This is intentional.
NOTE 2 Typical voltage configured in the register Table 127, “Register 0x25” [7:1].
NOTE 3 Measured over long period of time. Typically 1 second.
NOTE 4 Measured over short period of time. Typically > 20 μs but less than 50 μs.
NOTE 5 The percentage applies to typical voltage configured in the register. Applies across entire PMIC operating temperature range. The
PMIC bulk input supply voltage VIN_Bulk can vary from minimum to maximum value specified in Table 2, “Input Supply DC + AC
Specification”. The regulator output current load can vary maximum dI/dt value. The output ripple is inclusive in this parameter and
not to exceed TBD mV.

-
-
-2.5%
-0.75%

3.5
5
2.5%
0.75%

FB_Set_Point

A
A/μs

5
6

4

NOTE 6 The percentage applies to typical voltage configured in the register and at a given temperature within operating temperature range.

The PMIC bulk input supply voltage VIN_Bulk is fixed at nominal voltage of 12.0 V. The regulator output current load Itdc = 0 A.

JPGNetworksLLC

Vout
Itdc
Ipeakmax
dI/dt

-
-
-2.5%
-0.75%

Symbol

1.8
-

Min

Typ

-
-

0

Max

Unit

Notes

2
3

4

V
A

5

A
A/μs

6
5
2.5%
0.75%

Maximum Load Transient
Regulator Output DC + AC Voltage Tolerance Reg_DC_AC_Tol
Regulator Feedback Set Point Accuracy
NOTE 1 There is no note. This is intentional.
NOTE 2 Typical voltage configured in the register Table 129, “Register 0x27” [7:1].
NOTE 3 Measured over long period of time. Typically 1 second.
NOTE 4 Measured over short period of time. Typically > 20 μs but less than 50 μs.
NOTE 5 The percentage applies to typical voltage configured in the register. Applies across entire PMIC operating temperature range. The
PMIC bulk input supply voltage VIN_Bulk can vary from minimum to maximum value specified in Table 2, “Input Supply DC + AC
Specification”. The regulator output current load can vary maximum dI/dt value. The output ripple is inclusive in this parameter and
not to exceed TBD mV.

FB_Set_Point

5
6

NOTE 6 The percentage applies to typical voltage configured in the register and at a given temperature within operating temperature range.

The PMIC bulk input supply voltage VIN_Bulk is fixed at nominal voltage of 12.0 V. The regulator output current load Itdc = 0 A.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

Parameter

Output Voltage
Maximum Continuous DC Current Load

Maximum Peak Instantaneous Current

JEDEC Standard No. 301-1A.02
Page 8

2.2.2 Switch Regulator Output Electrical Characteristics (cont’d)

Table 10 — SWD1 - Single Phase Regulator; PMIC5010; DC + AC Specification

Parameter

Symbol

Min

Max

Unit

Notes

Output Voltage
Maximum Continuous DC Current Load

Maximum Peak Instantaneous Current

Vout
Itdc
Ipeakmax
dI/dt

Typ

1.8
-

-
-

0

-
-
-2.5%
-0.75%

2
3

4

V
A

3

A
A/μs

3.5
5
2.5%
0.75%

Maximum Load Transient
Regulator Output DC + AC Voltage Tolerance Reg_DC_AC_Tol
Regulator Feedback Set Point Accuracy
NOTE 1 There is no note. This is intentional.
NOTE 2 Typical voltage configured in the register Table 129, “Register 0x27” [7:1].
NOTE 3 Measured over long period of time. Typically 1 second.
NOTE 4 Measured over short period of time. Typically > 20 μs but less than 50 μs.
NOTE 5 The percentage applies to typical voltage configured in the register. Applies across entire PMIC operating temperature range. The
PMIC bulk input supply voltage VIN_Bulk can vary from minimum to maximum value specified in Table 2, “Input Supply DC + AC
Specification”. The regulator output current load can vary maximum dI/dt value. The output ripple is inclusive in this parameter and
not to exceed TBD mV.

FB_Set_Point

5
6

NOTE 6 The percentage applies to typical voltage configured in the register and at a given temperature within operating temperature range.

The PMIC bulk input supply voltage VIN_Bulk is fixed at nominal voltage of 12.0 V. The regulator output current load Itdc = 0 A.

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 9

2.2.3   Switch Regulator Efficiency

Table 11 — Efficiency Characteristics; PMIC5000

Efficiency (% of Max Itdc Load) Unit

Notes

Switch Node Output

SWA or SWB (Single Phase Regulator Mode)
SWA + SWB (Dual Phase Regulator Mode)
SWC
SWD
NOTE 1 VIN_Bulk = 12 V; VIN_Mgmt = 3.3 V
NOTE 2 The maximum Itdc as specified in appropriate Tables above.
NOTE 3 When the efficiency of any given output regulator is being measured, all other switching output regulators are disabled.
NOTE 4 No external load on VOUT_1.8V, VOUT_1.0V LDO is applied.
NOTE 5 I2C/I3C Basic bus is pulled High and held static. CAMP and GSI_n signals are pulled High and held static.
NOTE 6 The efficiency includes the buck regulator loss, the PCB loss (< 2.5 mΩ) and see clause 2.12 for inductor specification assumption

1,2,3,4,5,
6,7,8,9,10

%
%
%
%

25%
> 87
> 87
> 87
> 87

50%
> 92
> 92
> 92
> 92

100%
> 89
> 89
> 89
> 89

for DCR and ACR.

NOTE 7 Efficiency calculation equation: (VOUT * IOUT) / [(VIN_Bulk * IVIN_Bulk) + (VIN_Mgmt * IIN_Mgmt)]; where VOUT, IOUT, VIN_Mgmt,

IIN_Mgmt, VIN_Bulk, IVIN_Bulk parameters are actual measured values.

NOTE 8 Applies at maximum ambient temperature of 65 0C (PMIC Junction temperature of 105 0C). The inductor characteristics noted

above applies inductor temperature of 105 0C.

NOTE 9 The output buck regulator switching frequency can be set to anywhere within 500 KHz to 1000 KHz. For all efficiency qualification
testing, the device under test (DUT) must also comply with all PMIC’s electrical characteristics (DC+AC) specifications.
NOTE 10 For input supply rails, probing is done at the input high frequency filter cap (0.1uF) to PMIC pin. For output rail, probing is done

at the output cap location at the inductor load side.

JPGNetworksLLC

Table 12 — Efficiency Characteristics; PMIC5010

100%
> 87
> 87
> 87
> 87

25%
> 85
> 85
> 85
> 85

50%
> 90
> 90
> 90
> 90

Switch Node Output

Efficiency (% of Max Itdc Load) Unit

Notes

SWA or SWB (Single Phase Regulator Mode)
SWA + SWB (Dual Phase Regulator Mode)
SWC
SWD
NOTE 1 VIN_Bulk = 12 V; VIN_Mgmt = 3.3 V
NOTE 2 The maximum Itdc as specified in appropriate Tables above.
NOTE 3 When the efficiency of any given output regulator is being measured, all other switching output regulators are disabled.

%
%
%
%

1,2,3,4,5,
6,7,8,9,10

NOTE 4 No external load on VOUT_1.8 V, VOUT_1.0 V LDO is applied.
NOTE 5 I2C/I3C Basic bus is pulled High and held static. CAMP and GSI_n signals are pulled High and held static.
NOTE 6 The efficiency includes the buck regulator loss, the PCB loss (< 2.5 mΩ) and see clause 2.12 for inductor specification.assumption

for DCR and ACR.

NOTE 7 Efficiency calculation equation: (VOUT * IOUT) / [(VIN_Bulk * IVIN_Bulk) + (VIN_Mgmt * IIN_Mgmt)]; where VOUT, IOUT, VIN_Mgmt,

IIN_Mgmt, VIN_Bulk, IVIN_Bulk parameters are actual measured values.

NOTE 8 Applies at maximum ambient temperature of 65 0C (PMIC Junction temperature of 105 0C). The inductor characteristics noted

above applies inductor temperature of 105 0C.

NOTE 9 The output buck regulator switching frequency can be set to anywhere within 500 KHz to 1000 KHz. For all efficiency qualification

testing, the device under test (DUT) must also comply with all PMIC’s electrical characteristics (DC+AC) specifications.

NOTE 10 For input supply rails, probing is done at the input high frequency filter cap (0.1 uF) to PMIC pin. For output rail, probing is done

at the output cap location at the inductor load side.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 10

2.2.4   LDO Output Regulator Characteristics

Table 13 — LDO Output Regulator DC + AC Specification

Parameter

1.8 V LDO Output Voltage
1.8 V LDO Output - Maximum Output Current
1.0 V LDO Output Voltage
1.0 V LDO Output - Maximum Output Current
NOTE 1 Typical voltage is configured in register Table 133, “Register 0x2B” [7:6]. The min and max values are guaranteed to be within + 100

25

-

-

Typ Max
1.8
-
1.0
-

20

Unit
V
mA
V
mA

Notes
1
2
3
4

Symbol
VOUT_1.8V
Itdc_VOUT_1.8V
VOUT_1.0V
Itdc_VOUT_1.0V

Min

mV of programmed value.

NOTE 2 The maximum output current represents the external load and excludes PMIC’s own internal current consumption. The specified

maximum output current is only applicable after PMIC’s 1.8V LDO Power Good status is good (i.e., t1.8V_Ready timing parameter
is satisfied). Prior to PMIC’s 1.8V LDO Power Good status (i.e., while PMIC is still ramping up the 1.8 V LDO, the maximum output
current load shall be limited to maximum of 10 mA.

NOTE 3 Typical voltage is configured in register Table 133, “Register 0x2B” [2:1]. The min and max values are guaranteed to be within + 50

mV of programmed value.

NOTE  4 The  maximum  output  current  represents  the  external  load  and  excludes  PMIC’s  own  internal  current  consumption.  The  specified
maximum output current is only applicable after PMIC’s 1.0V LDO Power Good status is good (i.e., t1.0V_Ready timing parameter
is satisfied). Prior to PMIC’s 1.0V LDO Power Good status (i.e., while PMIC is still ramping up the 1.0V LDO), the maximum output
current load shall be limited to maximum of 5 mA.

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 11

2.2.5   PMIC AC Timing Parameters

Table 14 — PMIC AC Timing Parameters

Parameter

Input Supply to GSI_n assertion

Symbol
tInput_PWR_GOOD_GSI_
Assertion

Min

Typ Max

Unit

Notes

10

μs

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

μs

μs

μs

μs

μs

μs

20

10

10

10

20

20

10

tShut_Down_Temp

tHigh_Temp_Warning

tInput_OV_VR_Disable

tOutput_Current_Limiter

tOutput_UV_VR_Disable

tOutput_OV_VR_Disable

tInput_OV_GSI_Assertion

tOutput_PWR_GOOD_GSI_
Assertion

Input over voltage condition to
GSI_n assertion
Input over voltage condition to
automatic PMIC VR Disable
Output Voltage Tolerance to GSI_n
assertion
Output over voltage condition to
automatic PMIC VR Disable
Output under voltage lockout
condition to automatic PMIC VR
Disable
Output current limiter Warning to
GSI_n assertion
High Temperature Warning to
GSI_n assertion
Critical Temperature condition to
automatic PMIC shut down
VIN_Mgmt input supply stable to
VR Enable Command
VIN_Bulk input supply stable to
VR Enable Command
VIN_Mgmt input supply stable to
VOUT_1.8V output stable
VOUT_1.8V output supply stable
to VOUT_1.0V output stable
VOUT_1.8V output supply to
PMIC Management Ready
VR Enable Command to PMIC
output regulator ready
VR Disable Command to PMIC
Output Regulators Off
CAMP Input Low Pulse Width
CAMP Input Low Pulse Width
Input Filter
Output Voltage Adjustment in non
write protect mode
NOTE 1 This time is added to t_1.8V_Ready parameter to get total time from VIN_Mgmt input supply.
NOTE 2 See footnote 4 for registers Table 123, “Register 0x21” [7:1], Table 125, “Register 0x23” [7:1], Table 127, “Register 0x25” [7:1],

JPGNetworksLLC

tCAMP_Low_Pulse_Width
tCAMP_Low_Pulse_Width_
Filter

tPMIC_PWR_Good_Out

tVIN_Mgmt_to_Enable

tVIN_Bulk_to_Enable

tManagement_Ready

tPMIC_Output_Off

t1.8V_Ready

t1.0V_Ready

Figure 15

Figure 16

mV/μs

Δv/Δt

0.35

6.5

6.5

3.5

1.0

ms

ms

ms

ms

ms

ms

ms

10

μs

μs

μs

μs

1

3

2

1

2

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

and Table 129, “Register 0x27” [7:1]. The accuracy is + 10%

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 12

2.3   I2C, I3C Basic and Interface DC and AC Electrical Characteristics

Table 15 — I2C, I3C, and Interface DC Electrical Specification

Min

Max

Parameter

Input Low Voltage (CAMP, SDA, SCL)
Input High Voltage (SDA, SCL)
Input High Voltage (CAMP)
Output Low Voltage (SDA, GSI_n)
Output High Voltage (SDA)
Output Low Current (SDA, GSI_n, CAMP)
Output High Current (SDA)
Output Low Voltage (CAMP)
Rising Output Slew Rate (SDA)
Falling Output Slew Rate (SDA)
ILI
Input Leakage Current
ILO
Output Leakage Current
NOTE 1 The pullup resistor for GSI_n signal may vary and is typically 1K Ohm.

Symbol
VIL
VIH
VIH
VOL
VOH
IOL
IOH
VOL_CAMP

Slew_Rate

-0.3
0.7
1.26
-
0.75
3
-
-
0.1
0.1
-
-

Notes

1

2

3

Unit

V
V
V
V
V
mA
mA
V
V/ns
V/ns
μA
μA

0.3
3.6
3.6
0.3
-
-
3
0.3
1
3
+ 5
+ 5

NOTE 2  CAMP output is Open Drain output. There is an external pullup resistor to 3.3 V motherboard for standard DDR5 RDIMM/LRDIMM.

For other DIMM environment, the external pullup resistor may be pulled to either 1.8 V or 2.5 V or 3.3 V on either on DIMM or on

the motherboard.

NOTE 3 Output slew rate is guaranteed by design and/or characterization. The output slew rate reference load is shown in Figure 4 and Figure 5

shows the timing measurement points. For slew rate measurement, the VOH level shown in Figure 5 is a function of Ron value;
VOH = {1.0/(Ron + 50)} * 50.

JPGNetworksLLC

Table 16 — Input Capacitance Spec

Table 17 — Input Spike Filter Spec

Symbol
CIN

Min

-

Input Capacitance (CAMP, SCL, SDA)

Parameter

Max

5

Unit

Notes

pF

Parameter

Symbol

Test Condition

Min

Max

Unit

Notes

Pulse width of spikes which must
be suppressed by the input filter in
I2C mode
NOTE 1 TA = 25 0C; f = 400 KHz. Verified by design and characterization only.

tSP

Single glitch, f > 100 KHz

Single glitch, f < 100 KHz

-

0

-

50

ns

ns

1

Table 18 — Output Ron

Parameter

Symbol

SDA Output Pullup and Pulldown Driver Impedance
GSI_n, CAMP Output Pulldown Driver Impedance
NOTE 1 Pulldown Ron = Vout/Iout. Pullup Ron = (VOUT_1.0V - Vout)/Iout.

RON

Min
20
40

Max
100
100

Unit

Notes

Ω

Ω

1

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 13

2.3 I2C, I3C Basic and Interface DC and AC Electrical Characteristics (cont’d)

Table 19 — I2C and I3C Interface AC Characteristics

I2C Mode -
Open Drain

I3C Basic Mode
Push-Pull¹
Min Max Min Max

Unit Notes

Symbol
fSCL
tHigh
tLow
tTIMEOUT
tR
tF
tSU:DAT
tHD:DI
tSU:STA
tHD:STA
tSU:STO

0.01
260
500
10
-
-
50
0
260
260
260

1

50
120
120
-
-
-
-
-

0.01
35
35
10
-
0
8
3
12
30
12

-

0.5

350

500

500

N/A

tBUF

tDOUT

tHD:DAT

JPGNetworksLLC

tCL_r_DAT_f

tIBI_ISSUE

tDOFFC

tDOFFT

tAVAL

N/A

N/A

N/A

N/A

N/A

N/A

N/A

N/A

N/A

N/A

N/A

N/A

0.5

0.5

0.5

40

1

-

Parameter

Clock Frequency
Clock High Pulse Width Time
Clock Low Pulse Width Time
Detect Clock Input Low Time
Rise Time
Fall time
Data in Setup Time
Data in Hold Time
Start Condition Setup Time
Start Condition Hold Time
Stop Condition Setup Time
Time between Stop Condition and next Start
Condition
SDA Data Out Hold Time
SCL Falling Clock In to Valid SDA Data Out
Time
SCL Rising Clock In to Target SDA Output
Off
SCL Rising Clock In to Controller SDA
Output Off
SCL Rising Clock In to Controller Driving
Data Signal Low
Bus Available Time (no edges seen on SCL
and SDA)
Time to issue IBI after an event is detected
when Bus is available
Time from Clear Register Status to any I3C
Basic operation with Start condition to avoid
false IBI generation; PEC disabled
Time from Clear Register Status to any I3C
Basic operation with Start condition to avoid
false IBI generation; PEC enabled
DEVCTRL CCC Followed by DEVCTRL
CCC or Register Read/Write Command
Delay

tCLR_I3C_CMD_
Delay

N/A

N/A

4

N/A

N/A

15

tDEVCTRLCCC_
DELAY_PEC_DIS

3

-

3

12.5 MHz

2,3
2,3
2,4
2,4
2
2
2

2,5

6

7,8

7,8,9

7,8,10

11

ns
ns
ms
ns
ns
ns
ns
ns
ns
ns

ns

ns

ns

ns

ns

ns

μs

μs

μs

μs

μs

12,13,14

50
5
5
-
-
-
-
-

-

N/A

12

12

30

-

-

15

-

-

-

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 14

Table 19 — I2C and I3C Interface AC Characteristics (cont’d)

Parameter

Symbol

I2C Mode -
Open Drain

I3C Basic Mode
Push-Pull¹
Min Max Min Max

N/A

N/A

tWR_RD_DELAY
_PEC_EN

Register Write Command Followed by
Register Read Command Delay in PEC
Enabled Mode
SETHID CCC or SETAASA CCC followed
by any other CCC or Read/Write Command
Delay
RSTDAA CCC or ENEC CCC or DISEC
CCC to any other CCC or Read/Write
Command Delay
Any CCC followed by RSTDAA CCC delay
NOTE 1  I3C mode with Open Drain operation follows timing values as shown in I2C Mode - Open Drain column.
NOTE 2  See Figure 1 for PMIC’s input timing definition.

tI3C_CCC_Update
_Delay

tI2C_CCC_Update
_Delay

tCCC_Delay

N/A

N/A

2.5

2.5

2.5

8

-

-

-

-

-

-

-

-

NOTE 3  See Figure 6 for voltage threshold definition for rise and fall times.

Unit Notes

μs

15,16,17

μs

μs

μs

NOTE 4  The input setup time is referenced from SDA VIL or VIH threshold as shown in Figure 1 to SCL VIH threshold as shown in Figure 1.

The input hold time is referenced from SCL VIL threshold as shown in Figure 1 to SDA VIL or VIH threshold as shown in Figure 1.

NOTE 5  If PEC is enabled, tWR_RD_DELAY_PEC_EN timing parameter applies.
NOTE 6  The PMIC device guarantees tHD:DAT value in I2C mode of operation. See Figure 3 for PMIC’s output timing definitions as well as

SCL clock input threshold level and SDA data output threshold levels.

NOTE 7  The PMIC device must be configured in I3C Basic mode to guarantee tDOUT or tDOFFT or tDOFFC value. See Figure 2 for PMIC’s

output timing definition as well as SCL clock input threshold level and SDA data output threshold levels.

NOTE 8  This timing parameter is guaranteed into output timing reference load as shown in Figure 4.
NOTE 9  The PMIC device must be configured in I3C Basic mode to guarantee tDOFFT value. See Figure 18.
NOTE 10 The PMIC device must be configured in I3C Basic mode to guarantee tDOFFC value. See Figure 19.
NOTE 11  See Figure 21.

JPGNetworksLLC

NOTE 12 From STOP condition of DEVCTRL CCC to START condition for Register Read or Register Write Command Data Packet delay.
NOTE 13 The PMIC sends NACK if Host does not satisfy tDEVCTRLCCC_DELAY_PEC_DIS timing parameter.
NOTE 14 This timing parameter restriction is only applicable when PEC function is disabled in PMIC. If PEC is enabled, this timing parameter

NOTE 15 From STOP condition for Register Write Command Data Packet to START condition for Register Read Command Data Packet delay.

NOTE 16 This timing parameter restriction is only applicable when PEC function is enabled in PMIC. If PEC is disabled, this timing parameter

does not apply.

does not apply.

NOTE 17 The PMIC sends NACK if Host does not satisfy tWR_RD_DELAY_PEC_EN timing parameter.

The PMIC device follow the I2C or I3C Basic bus timing requirements. Figure 1, Figure 2, and Figure 3 show the
timing diagram for Data bus Input and Data Output parameters.

SCL

VIHmin
VILmax

VIHmin
VILmax
SDA

P

S

tR

tLOW

tHD:DI

tHIGH

Sr

P

tHD:STA

tBUF

tSU:DAT

tF

tSU:DAT

tSU:STA

tSU:STO

Figure 1 — I2C or I3C Basic Bus AC Input Timing Parameter Definition

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

2.3 I2C, I3C Basic and Interface DC and AC Electrical Characteristics (cont’d)

JEDEC Standard No. 301-1A.02
Page 15

tDOUT

tDOUT

SCL

SDA

SCL

SDA

VIHmin

VILmax

VOHmin

VOLmax

VIHmin

VILmax

VOHmin

VOLmax

ACK

Figure 2 — I3C Basic Bus AC Data Output Timing Parameter Definition

tHD:DAT

tHD:DAT

JPGNetworksLLC

ACK

Figure 3 — I2C Bus AC Data Output Timing Parameter Definition

50 Ohm

SDA

5 mm

Figure 4 — Output Slew Rate and Output Timing Reference Load

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 16

2.3 I2C, I3C Basic and Interface DC and AC Electrical Characteristics (cont’d)

Delta tF

Delta tR

SDA

VOL

I3C

tF

I2C
tF

SCL,
SDA

Figure 5 — Output Slew Rate Measurement Points

JPGNetworksLLC

0.7 V

0.3 V

I2C

I3C

tR

tR

0.7 V

0.3 V

SCL,
SDA

Figure 6 — Rise and Fall Timing Parameter Definition

SCL,
SDA

SCL,
SDA

VOH

70%*VOH

30%*VOH

0.7 V

0.3 V

0.7 V

0.3 V

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 17

2.3 I2C, I3C Basic and Interface DC and AC Electrical Characteristics (cont’d)

Table 20 — AC Measurement Conditions1

Symbol

CL

Parameter

Load capacitance

Input rise and Fall times - Open Drain

Input rise and fall times - Push Pull

Input signal swing levels

Input and Output timing reference levels

Min

-

-

Max

40

TBD

TBD

0.2 to 0.8

0.3 to 0.7

Units

pF

ns

ns

V

V

NOTE 1  This AC measurement condition (Table 20 and Figure 7) is only for the test purpose in lab.

Input Signal
Swing levels

             0.8 V

             0.2 V

2.4   Thermal Characteristics

Input Levels for
timing reference

0.7 V

0.3 V

Figure 7 — AC Measurement Waveform

JPGNetworksLLC

Table 21 — Thermal Characteristics

Symbol Maximum Rating

Parameter

Case operating temperature

Junction operating temperature

Thermal resistance junction to case

ΘJC
TJ
TC
TSTG3
TLEAD
NOTE 1  The maximum power dissipation is PD(MAX) = (TJMAX - TC)/ ΘJC. Exceeding the maximum allowable power

Lead temperature (soldering, 10s)

Storage temperature

-10 to TBD

-10 to 125

-55 to 150

TBD

300

4

4

Notes
Unit
0C/W 1,2,3
0C
0C
0C
0C

4

dissipation results in excessive die temperature and the device will enter thermal shutdown.

NOTE 2  This thermal rating was calculated on JEDEC 51 standard 4 layer board with dimensions 3” x 4.5” in still air

conditions. Actual thermal resistance is affected by PCB size, solder joint quality, layer count, copper
thickness, air flow, altitude and other unlisted variables.

NOTE 3  This specification is compliant with JESD402-1 Temperature Grade and Measurement Specification for

Components and Modules, operating temperature range MT, storage temperature TSTG3. See JESD402-1 for
details, including measurement point.

NOTE 4  Soldering temperature, 10 s.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 18

2.5   Absolute Maximum Rating

The  absolute  maximum  ratings  are  stress  ratings  only.  Stresses  greater  than  those  listed  in  Table 22,  “Absolute
Maximum Rating”, Table 23, “ESD Requirement”, and Table 24, “EOS Requirement” may cause permanent damage
to the device. Functional operation of the PMIC at absolute maximum ratings is not implied. Exposure to absolute
maximum rating condition for extended periods may affect long term reliability.

Table 22 — Absolute Maximum Rating

Maximum Rating

Pin

Unit

V

TBD

V
V
V
V

-0.3 to 6.0

-0.3 to 2.2

-0.3 to 21.0

DC
-0.3 to 16.2
-0.3 to 6.0
-0.3 to 2.2
-0.3 to 16.2

AC
TBD (Duration < 25 ns)
-
-
-4.5 to 20 (Duration < 25 ns)

-0.3 to 24 (Duration < 25 ns)

VIN_BULK
VIN_Mgmt, VBIAS
VOUT_1.8V, VOUT_1.0V
SWA, SWB, SWC, SWD
SWA_BOOT, SWB_BOOT, SWC_BOOT,
SWD_BOOT (to GND)
SWA_BOOT, SWB_BOOT, SWC_BOOT,
SWD_BOOT (to SWx)
SWAB_FB_P, SWB_FB_P, SWC_FB_P,
SWD_FB_P (to AGND)
SWAB_FB_N, SWC_FB_N, SWD_FB_N/PID
CAMP1, GSI_n
SCL, SDA; I2C Mode only
SCL, SDA; I3C Mode only
AGND, PGND
NOTE 1  CAMP pins shall withstand the stress when connected to maximum of 15V DC source through 250 Ohm series resistor for 10

JPGNetworksLLC

Maximum Rating
+ 2000
+ 500

-0.3 to 5.0
-0.3 to 2.1
-0.3 to 0.3

Table 23 — ESD Requirement

-0.3 to 2.2
-0.3 to 5.0

TBD
TBD
-

Unit
V
V

Pin
All
All

HBM
CDM

Test Model

V
V
V

seconds.

V
V

-
-

V

V

-

Table 24 — EOS Requirement

Pin
VIN_BULK
VIN_Mgmt

Maximum Rating
37
10

Unit
V
V

Notes

1,2,3,4

NOTE 1  The test is performed on DDR5 DIMM module without any input capacitor on VIN_BULK and VIN_Mgmt
NOTE 2  The input source needs to follow the waveform and condition as shown in Figure 8 and Table 25.
NOTE 3  Probing is performed at the VIN_BULK and VIN_Mgmt pin of PMIC.
NOTE 4  Each net test is performed individually.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 19

2.5 Absolute Maximum Rating (cont’d)

Table 25 — Input Source Condition

Item
T (rise from 30% to 90% of peak)
T1 (rise time)
T2 (duration time to half value)
Output Impedance
VUNDERSHOOT Voltage

Value
0.72 μs (+ 30%)
1.2 μs (+ 30%)
50 μs (+ 20%)
2 Ω
30% Max

Notes

T1 = 1.67*T

Figure 8 — Impulse Waveform for EOS Test (IEC 61000-4-5)

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 20

2.6   Example Schematic

Figure 9  shows  an  example  schematic  when  PMIC  is  configured  in  dual  phase  regulator  mode.  Table 26,  “PMIC
Schematic Values” shows all component details shown in the schematics. Note that capacitors C25, C26, C27, C29,
C30, and C31 represent the lump sum of distributed capacitance across the entire DIMM.

VIN_Mgmt

C24

C14

VIN_Mgmt

VIN_Bulk

C1

C17

SWA

SWA_BOOT

SWB

L1

L2

C2

C5

VDD_OUT

C3

C4

C27

C31

VOUT_1.8V

C23

C15

SCL

SDA

SWB_FB_P

RFU1/RFU2

DIMM
Connector

GSI_n

CAMP

VOUT_1.0V

C22

C16

VBias

C21

C13

C18

SWB_BOOT

C6

VIN_Bulk

VIN_Bulk

SWAB_FB_P

SWAB_FB_N

JPGNetworksLLC

SWC_BOOT

SWC_FB_N

SWC_FB_P

VIN_Bulk

SWC

C10

C8

C9

C7

L3

L4

VDDQ_OUT

C19

C20

DIMM Gold Finger

C25

C29

AGND

PGND (2x)

SWD

SWD_BOOT

SWD_FB_P

SWD_FB_N/PID

C12

C11

VPP_OUT

C26

C30

Figure 9 — Dual Phase Regulator Example Schematic

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 21

2.6 Example Schematic (cont’d)

Figure 10 shows an example schematic when PMIC is configured in single phase regulator mode. Table 26, “PMIC
Schematic Values” shows all component details shown in the schematics. Note that capacitors C25, C26, C27, C28,
C29, C30, C31, and C32 represent the lump sum of distributed capacitance across the entire DIMM.

VIN_Mgmt

C24

C14

VIN_Mgmt

VIN_Bulk

C1

C17

VOUT_1.8V

C23

C15

SCL

SDA

SWA

SWA_BOOT

SWB

SWB_BOOT

L1

L2

C2

C5

C3

C4

RFU1/RFU2

DIMM
Connector

GSI_n

CAMP

VOUT_1.0V

C22

C16

VBias

C21

C13

C6

VIN_Bulk

VIN_Bulk

SWB_FB_P

SWAB_FB_P

SWAB_FB_N

JPGNetworksLLC

SWC_BOOT

SWC_FB_N

SWC_FB_P

VIN_Bulk

SWC

C10

C8

C9

C7

L3

L4

VDDQ_OUT

VDD_OUT

C27

C31

VXX_OUT

C28

C32

DIMM Gold Finger

C18

C19

C25

C29

C20

C12

C11

VPP_OUT

C26

C30

AGND

PGND (2x)

SWD

SWD_BOOT

SWD_FB_P

SWD_FB_N/PID

Figure 10 — Single Phase Regulator Example Schematic

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 22

2.6 Example Schematic (cont’d)

Table 26 — PMIC Schematic Values

Component

Dual Phase Regulator Mode

Single Phase Regulator Mode

Value

Physical Size/Rating

Value

Physical Size/Rating

Unit Comment

L1
L2
L3
L4
C1
C2
C3
C4
C5
C6
C7
C8
C9
C10
C11
C12
C13
C14
C15
C16
C17
C18
C19
C20
C21
C22
C23
C24
C25
C26
C27
C28
C29
C30
C31
C32

0.47 - 0.68
0.47 - 0.68
0.47 - 0.68
0.68 - 1.2
2x; 22
0.1
3x; 47
3x; 47
0.1
2x; 22
2x; 22
3x; 47
0.1
2x; 22
3x; 47
0.1
4.7
4.7
4.7
4.7
0.1
0.1
0.1
0.1
0.1
0.1
0.1
0.1
175
175
350
N/A
175
175
350
N/A

4.0 x 4.0 x 2.0
4.0 x 4.0 x 2.0
4.0 x 4.0 x 2.0
4.0 x 4.0 x 2.0
25V
16V; 0201
6.3V; 0805
6.3V; 0805
16V; 0201
25V
25V
6.3V; 0805
16V; 0201
25V
6.3V; 0805
16V; 0201
6.3V; 0402
6.3V; 0402
6.3V; 0402
6.3V; 0402
25V, X6S; 0201
25V, X6S; 0201
25V, X6S; 0201
25V, X6S; 0201
6.3V; 0201
6.3V; 0201
6.3V; 0201
6.3V; 0201
6.3V
6.3V
6.3V
N/A
6.3V
6.3V
6.3V

JPGNetworksLLC

0.47 - 0.68
0.47 - 0.68
0.47 - 0.68
0.68 - 1.2
2x; 22
0.1
3x; 47
3x; 47
0.1
2x; 22
2x; 22
3x; 47
0.1
2x; 22
3x; 47
0.1
4.7
4.7
4.7
4.7
0.1
0.1
0.1
0.1
0.1
0.1
0.1
0.1
175
175
175
175
175
175
175
175

4.0 x 4.0 x 2.0
4.0 x 4.0 x 2.0
4.0 x 4.0 x 2.0
4.0 x 4.0 x 2.0
25V
16V; 0201
6.3V; 0805
6.3V; 0805
16V; 0201
25V
25V
6.3V; 0805
16V; 0201
25V
6.3V; 0805
16V; 0201
6.3V; 0402
6.3V; 0402
6.3V; 0402
6.3V; 0402
25V, X6S; 0201
25V, X6S; 0201
25V, X6S; 0201
25V, X6S; 0201
6.3V; 0201
6.3V; 0201
6.3V; 0201
6.3V; 0201
6.3V
6.3V
6.3V
6.3V
6.3V
6.3V
6.3V
6.3V

μH
μH
μH
μH
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF
μF

1

1

NOTE 1  These capacitor values represent the distributed capacitance for the entire DIMM assuming max Itdc and Ipeakmax defined in
Electrical characteristics for each SWx. For a given DIMM design, the distributed capacitance for each SWx varies and is a
function of Itdc and Ipeakmax current requirement for that DIMM design. See actual DIMM design for total distributed
capacitance.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 23

2.7   Functional Operation

2.7.1   PMIC Input Voltage Supplies and Ramp Condition

The DDR5 PMIC has two input supplies from the platform: VIN_Bulk and VIN_Mgmt.

The VIN_Bulk supply is used by the PMIC for all output regulators except for the VOUT_1.8V and VOUT_1.0V
LDO outputs regulators when not in switchover mode. The VIN_Bulk input supply may also be used to generate the
internal bias voltage. Note that the VOUT_1.8V LDO output is separate and independent from SWD output, which is
for the DRAM VPP rail. The VOUT_1.0V LDO output is separate and independent from SWA, SWB, or SWC.

The PMIC internally generates on its own bias voltage (VBias). At first power on, the VIN_Bulk input supply shall
reach a minimum threshold voltage value per register Table 116, “Register 0x1A” [7:5] plus 1.0V offset before it can
be detected as a valid input supply to the PMIC. The PMIC filters any non-monotonic noise after this threshold. After
power on, with valid VIN_Mgmt input supply while PMIC is operating in non write protect mode of operation, if
VIN_Bulk  input  supply  is  removed  and  re-applied,  it  must  reach  the  same  threshold  voltage  value  per  Table 116,
“Register 0x1A” [7:5] plus 1.0 V offset.

The VIN_Mgmt supply is used to read out its internal non-volatile memory content and to supply VOUT_1.8V and
VOUT_1.0V to other devices such as SPD, TS and RCD on the DIMM. At first power on, the VIN_Mgmt supply
shall reach a minimum of 2.8V before it can be detected as a valid input supply to the PMIC. At power on, the PMIC
floats CAMP signal and then drives CAMP output signal low only when VIN_Mgmt input supply reaches minimum
of 2.8 V and PMIC VOUT_1.8V and VOUT_1.0V LDO outputs are valid. VIN_Bulk input supply does not trigger
PMIC to drive CAMP output signal low at power on. The VIN_Mgmt supply is strictly a voltage input.

The CAMP output is pulled up to either 1.8 V or 3.3 V on the platform or on the host controller. The CAMP pullup
voltage (either 1.8 V or 3.3 V) can be available before or after either VIN_Bulk or VIN_Mgmt is valid and stable. If
CAMP pullup voltage is available before VIN_Mgmt or VIN_Bulk is applied, the CAMP signal is high and remains
High with no leakage path or damage to the PMIC. When VIN_Mgmt is applied to the PMIC and after VOUT_1.8V
and VOUT_1.0V LDO outputs are valid, the PMIC asserts CAMP output low.

JPGNetworksLLC

Figure 11 and  Figure 12 show  PMIC power up sequence  when  power  is  first applied. The  platform  can  power  up
VIN_Bulk  and  VIN_Mgmt  supply  in  any  sequence.  Figure 11  shows  VIN_Mgmt  supply  ramps  up  first  prior  to
VIN_Bulk supply. Figure 12 shows VIN_Bulk supply ramps up first prior to VIN_Mgmt supply. The PMIC does not
mandate any specific timing relationship between VIN_Bulk and VIN_Mgmt supply.

The PMIC updates register Table 98, “Register 0x08” [7] when VIN_Bulk input supply status is valid.

2.7.2   Power Up Initialization Sequence

During power on, the host shall:

1.   Ramp up VIN_Mgmt supply; Ramp up VIN_Bulk supply; (No timing relationship between two supplies)
2.   Hold VIN_Mgmt supply stable for a minimum of tVIN_Mgmt_to_Enable time
3.   Hold VIN_Bulk supply stable for a minimum of tVIN_Bulk_to_Enable time
4.   Query the status of the PMIC status register to determine if it is safe to enable VR.
5.   If it is safe to enable, send VR Enable command by setting register Table 140, “Register 0x32” [7] = ‘1’ or by

issuing DEVCTRL CCC.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 24

2.7.2 Power Up Initialization Sequence (cont’d)

Once the VIN_Mgmt supply is valid and stable, the PMIC shall drive VOUT_1.8V and VOUT_1.0V supply within
t1.8  _Ready  and  t1.0V_Ready  time.  The  PMIC  shall  enable  I2C/I3C  Basic  bus  interface  function  within
tManagement_Ready. The host shall not attempt to access the PMIC’s memory registers until tManagement_Ready
timing  requirement  is  satisfied.  Further  the  host  shall  not  attempt  to  issue  VR  Enable  command  until
tVIN_Mgmt_to_Enable  and  tVIN_Bulk_to_Enable  timing  requirement  is  satisfied.  In  Figure 11,  the  PMIC  allows
access to its memory registers for indefinite period of time as long as VIN_Mgmt input supply is valid and PMIC
does not require VIN_Bulk input supply.

The host may read PMIC's own internal memory content prior to ramping VIN_Bulk supply.

The host, prior to issuing VR Enable command, must keep VIN_Mgmt input supply valid as long as VOUT_1.8V
and VOUT_1.0V LDO output are required. If VIN_Mgmt input supply is removed or drops below 2.8 V, the PMIC
does not guarantee any operation including VOUT_1.8V and VOUT_1.0V LDO output as well as access to its I2C/
I3C Basic interface regardless of VIN_Bulk input supply status.

After  host  issues  VR  Enable  command  to  the  PMIC,  the  PMIC  offers  the  input  supply  switchover  function.  The
PMIC has an automatic internal input supply switchover function from VIN_Mgmt input supply to VIN_Bulk input
supply. The PMIC triggers the switchover to VIN_Bulk input supply when VIN_Mgmt input supply drops below the
threshold  set  in  register  Table 137,  “Register  0x2F”  [7].  The  internal  input  supply  switchover  is  for  PMIC’s
VOUT_1.8V and  VOUT_1.0V LDO output. The PMIC’s I2C/I3C Basic interfaces (SCL/SDA) are kept alive when
PMIC  switches  over  to  VIN_Bulk  input  supply.  Figure 13  shows  automatic  internal  switchover  function  when
VIN_Mgmt  input  supply  drops  below  the  threshold  while  maintaining  its  LDO  outputs  as  well  as  I2C/I3C  Basic
interfaces. Under the switchover conditions VIN_Mgmt back-feed voltage shall be less than 0.2 V. While PMIC is in
switchover mode to VIN_Bulk, the VIN_Mgmt input supply can re-power backup at any time and PMIC switches
back to VIN_Mgmt input supply for its LDO outputs and I2C/I3C interface continues to operate as normal.

JPGNetworksLLC

the  PMIC  shall  complete

registered,

the

is

1.   Check VIN_Bulk, VIN_Mgmt and VBias Power Good status is valid.
2.   Power up itself - PMIC executes Power On Sequence Config 0 to Power On Sequence Config 3 registers and

configures PMIC internal registers as programmed in DIMM vendor memory space registers.

3.   Power up all enabled output switch regulators and ready for normal operation
4.   Update status registers Table 98, “Register 0x08” [5:2] and floats CAMP signal.

The PMIC shall power up its output switch regulators when it registers VR Enable command.

After  VR  Enable  command
tPMIC_PWR_GOOD_OUT:

following  steps  within

If  PMIC  CAMP  signal  is  not  pulled  High  within  tPMIC_PWR_GOOD_OUT  time,  the  host  can  access  the  PMIC
status registers for detailed information after tPMIC_PWR_GOOD_OUT time. The PMIC may NACK for any host
request on I2C or I3C bus after VR Enable command until tPMIC_PWR_GOOD_OUT time expires.

Note that in Figure 11 and Figure 12 the specific sequence of ramping the output regulators (VOUT_A, VOUT_B,
VOUT_C, and VOUT_D) is for example purpose only. The specific ramp up sequence is configurable through the
registers.

Once PMIC’s output regulators are running, the PMIC allows VIN_Bulk input supply to vary. Figure 14 shows that
VIN_Bulk can go as low as VIN_Bulk Min value (4.25 V) and PMIC output regulators will continue to operate as
normal. The VIN_Mgmt input supply can drop and may re-power back up at any time.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 25

2.7.3   Power Up Sequence

Figure 11 shows the power up initialization sequence.

After VIN_Bulk supply is valid and stable, the PMIC powers up its output regulators when the system host sends VR
Enable command. The PMIC generates its bias voltage (VBias) on its own using VIN_Bulk input supply. Further it
executes Power On Sequence Config0 to Config3 as configured in register Table 152, “Register 0x40” to Table 155,
“Register 0x43” to enable its output regulators in the sequence as specified. The PMIC also follows the settings as
specified in register 0x44 to register 0x6F for each of the enabled output. The PMIC ensures CAMP signal is floated
within maximum of tPMIC_PWR_GOOD_OUT after registering VR Enable command.

VIN_MGMT

VOUT_1.8V

VOUT_1.0V

VIN_BULK

I2C/I3C

SWD

SWC

SWAB

CAMP

tVIN_MGMT_Ramp

tVIN_MGMT_to_Enable

tManagement_Ready

t1.8V_Ready

tPMIC_PWR_GOOD_OUT

tVPP_Ramp

t1.0V_Ready

VR Enable

tVIN_BULK_Ramp

tVIN_BULK_to_Enable

JPGNetworksLLC

Hi‐Z

tVDDQ_Ramp

tVDD_Ramp

Figure 11 — PMIC Power Up Sequence; VIN_Mgmt Followed by VIN_Bulk

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 26

2.7.3 Power Up Sequence (cont’d)

VIN_MGMT

VOUT_1.8V

tVIN_MGMT_Ramp

tVIN_MGMT_to_Enable

tManagement_Ready

t1.8V_Ready

VOUT_1.0V

t1.0V_Ready

VIN_BULK

tVIN_BULK_Ramp

tVIN_BULK_to_Enable

tPMIC_PWR_GOOD_OUT

I2C/I3C

SWD

SWC

SWAB

CAMP

VR Enable

tVPP_Ramp

tVDDQ_Ramp

Hi‐Z

JPGNetworksLLC

tVDD_Ramp

Figure 12 — PMIC Power Up Sequence; VIN_Bulk Followed by VIN_Mgmt

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

2.7.3 Power Up Sequence (cont’d)

JEDEC Standard No. 301-1A.02
Page 27

tVIN_Mgmt_Ramp

tVIN_Mgmt_Ramp

valid

valid

valid

valid

valid

valid

VIN_Mgmt

VOUT_1.8V
(Valid)

VOUT_1.0V
(Valid)

VIN_Bulk
(Valid)

I2C/I3C

SWD

SWC

SWAB

CAMP

VR
Enable

tVPP_Ramp

tVDD_Ramp

tVDDQ_Ramp

JPGNetworksLLC

Figure 13 — VIN_Mgmt Input Supply to VIN_Bulk Input Supply Switchover Function

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 28

2.7.3 Power Up Sequence (cont’d)

VIN_Mgmt

VOUT_1.8V
(Valid)

VOUT_1.0V
(Valid)

VIN_Bulk
(Valid)

I2C/I3C

SWD

SWC

SWAB

CAMP

tVIN_Mgmt_Ramp

tVIN_Mgmt_Ramp

valid

valid

VIN_Bulk can reach
as low as 4.25 V

VR
Enable

valid

valid

valid

valid

tVPP_Ramp

tVDD_Ramp

tVDDQ_Ramp

JPGNetworksLLC

Figure 14 — VIN_Bulk Transition

The timing  waveform  example  in  Figure 14 assumes VIN_Bulk  threshold is  set to 4.25 V  in  Table 116,  “Register
0x1A” [7:5] and hence CAMP signal remains at valid High level.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 29

2.7.4   Enabling PMIC Output Switch Voltage Regulators

After  first  power  on,  the  PMIC  automatically  enables  VOUT_1.8V  and  VOUT_1.0V  LDO  output  regulators  and
primary I2C/I3C Basic port based on valid VIN_Mgmt input.

Figure 15  shows  the  timing  relationship  once  the  PMIC  receives VR  Enable  command  and  when  it  floats  CAMP
output signal;  timing parameter  tPMIC_PWR_GOOD_OUT applies. This  timing parameter  is  a sum of maximum
soft start time and configured delay for each power on sequence config registers that are executed plus additional 5
ms timing margin error. The waveform shows each buck regulator output soft start time and delay time once the soft
start time expires for each power on sequence config0 to power on sequence config3 registers. Note that if more than
one regulators are enabled in a power on sequence config register and if those regulators have different soft start time
programmed, then the larger value of that soft start time is used as a reference for delay timer to start. Each regulator
will still follow different soft start time to turn on the buck regulator.

The specific example in Figure 15 uses only three power on sequence config0 to config2 registers and only one buck
regulator is enabled in power on sequence config 0 register and power on sequence config 1 register. The power on
sequence config 2 register enables dual phase regulator for SWA and SWB.

tPMIC_PWR_GOOD_OUT

SWD_Soft_Start
R2D [3:1]

JPGNetworksLLC

Power_On
Config0_Delay
R40 [2:0]

Power_On
Config1_Delay
R41 [2:0]

SWC_Soft_Start
R2D [7:5]

SWAB_Soft_Start
R2C [7:5]

VR Enable

SWD

SWC

SWAB

CAMP

Power On Sequence
Config0

Power On Sequence
Config1

Power On Sequence
Config2

Figure 15 — PMIC Power On Timing

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 30

2.7.5   Power Down Output Regulators

Regardless  of  how  PMIC’s  output  regulators  are  turned  on,  the  PMIC’s  output  regulators  are  powered  down  as
described below depending on mode of operation.

In non write protect mode of operation, the PMIC allows host to power down any or all output regulators in non write
protect mode. The host can disable PMIC’s any or all output regulators by any of the three methods below.

1.   The VR Disable command (Table 140, “Register 0x32” [7] = ‘0’).The PMIC executes power off sequence

config0 (Table 169, “Register 0x58”) to power off sequence config3
(Table 172, “Register 0x5B”) to preserve the appropriate voltage relationship as configured by the DIMM
vendors. The  PMIC  keeps  the  CAMP  signal  floating  (i.e.,  it  remains  High)  because  this  is  an  intentional
command from the host and not a fault condition. Note that host can re-enable the PMIC’s output regulator
by issuing VR Enable command. The PMIC executes power on sequence config 0 to config 3 registers and
keeps the CAMP signal floating (i.e it remains High).

2.      Configuring  one  or  more  bits  in  Table 137,  “Register  0x2F”  [6:3]  to  ‘0’  in  any  specific  sequence  that  is
desired by the host.The PMIC does not execute power off sequence config0 (Table 169, “Register 0x58”) to
power off sequence config3 (Table 172, “Register 0x5B”) on its own. The PMIC keeps the CAMP signal
floating (i.e it remains High) because this is intentional command from the host and not a fault condition.
Note that host can re-enable any of disabled output regulators by configuring one or more bits in Table 137,
“Register 0x2F” [6:3] to ‘1’ in any specific sequence that is desired by the host. The PMIC keeps the CAMP
signal floating (i.e., it remains High).

3.    By driving CAMP input low. The PMIC executes power off sequence config0

(Table 169, “Register 0x58”) to power off sequence config3 (Table 172, “Register 0x5B”) to preserve the
appropriate voltage relationship as configured by the DIMM vendors.

JPGNetworksLLC

In  write  protect  mode  of  operation,  the  host  can  disable  PMIC’s  all  enabled  output  regulators  by  any  of  the  two
methods below.

1.   Power cycle the PMIC.
2.    By driving CAMP input low. The PMIC executes power off sequence config0 (Table 169, “Register 0x58”)
to power off sequence config3 (Table 172, “Register 0x5B”) to preserve the appropriate voltage relationship
as configured by the DIMM vendors.

Regardless of the either mode of the operation, the PMIC, on its own, can generate VR Disable command at any time
due  to  one  or  more  events  listed  in  Table 27  under  column  “Trigger VR  Disable”.  The  PMIC  executes  power  off
sequence  config0  (Table 169,  “Register  0x58”)  to  power  off  sequence  config3  (Table 172,  “Register  0x5B”)  to
preserve the appropriate voltage relationship as configured by the DIMM vendors. The PMIC may also reset its Vbias
LDO regulator.

Figure 16 shows the timing relationship once the PMIC registers VR Disable command internally due to fault. The
waveform shows each buck regulator output soft stop time and delay time once the soft stop time expires from each
power  off  sequence  config0  to  power  off  sequence  config3  registers.  Note  that  if  more  than  one  regulators  are
disabled in a power off sequence config register and if those regulators have different soft stop time programmed,
then the  larger  value  of that  soft  stop  time  is  used as  a  reference  for  delay  timer  to  start.  Each  regulator  will  still
follow different soft stop time to turn off the buck regulator.

The specific example in Figure 16 uses only three power off sequence config0 to config2 registers and only one buck
regulator is disabled in power off sequence config 1 register and power off sequence config 2 register. The power off
sequence config 0 register disables dual phase regulator for SWA and SWB.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

2.7.5 Power Down Output Regulators (cont’d)

JEDEC Standard No. 301-1A.02
Page 31

SWAB_Soft_Stop
R22 [1:0]

Power_Off
Config0_Delay
R58 [2:0]

SWC_Soft_Stop
R26 [1:0]

VR Disable

SWAB

SWC

SWD

CAMP

Power_Off
Config1_Delay
R59 [2:0]

Power Off Sequence
Config2

SWD_Soft_Stop
R28 [1:0]

Power Off Sequence
Config1

Power Off Sequence
Config0

JPGNetworksLLC

2.7.6   Power Down Output Regulators During Power On Sequence

During power on, as described in clause 2.7.2, it is possible that PMIC can trigger VR Disable command on its own
as described in Table 27, “Events Interrupt Summary” when one or more regulators are already turned on even while
other  remaining  output  regulators  are  not  yet  turned  on  because  PMIC  has  not  completed  the  power  on  sequence
config registers. For these type of cases, the PMIC will not execute the remaining power on sequence config registers
and will immediately jump to executing the power off sequence config0 to power off sequence config3 registers. The
PMIC will update the status registers and error log registers appropriately as normal because it generated VR Disable
command on its own. The CAMP output signal would remain low.

Figure 16 — PMIC Power Off Timing Due to Internal Fault Condition

2.7.7   CAMP Signal

The CAMP (Control AND Monitor Port) signal provides three different functions.

1.   Register write protect function
2.   Fail_n function
3.   Status function

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 32

2.7.7.1  Register Write Protect Function

By default, PMIC register write protect function is enabled (i.e., Table 137, “Register 0x2F” [2] = ‘0’). The CAMP
input signal level determines when PMIC enters or exits the write protect mode. The PMIC enters the write protect
mode  when  CAMP  signal  is  at  logic  level  High  and  Table 137,  “Register  0x2F”  [2]  =  ‘0’.  PMIC  exits  the  write
protect mode when CAMP signal is at logic level Low. When PMIC is in write protect mode, the PMIC does not
allow to modify registers Table 111, “Register 0x15” to Table 137, “Register 0x2F”, Table 140, “Register 0x32”, and
Table 143, “Register 0x35” in the host region as well as Table 152, “Register 0x40” to Register 0x6F in the DIMM
vendor region. These registers are write protected marked with RED color cells in “Register” column in Table 93,
“Host Region - Register Map”. The PMIC simply ignores the host request for write operation in write protect mode.
PMIC allows all register read access in write protect mode.

Once PMIC is in write protect mode, there are 3 ways PMIC can exit write protect mode:

1.   PMIC sees CAMP input signal Low (clause 2.7.7.2)
2.   PMIC triggers internal fault event (VIN_Bulk OV, VIN_Bulk UV, SWx_OV, SWx_UV) and asserts CAMP

signal low.

3.   PMIC goes through power cycle or power down cycle (i.e., simultaneous removal of VIN_Bulk and

VIN_Mgmt input supplies)

If Table 137, “Register 0x2F” [2] = ‘1’, the PMIC does not enter write protect mode. The PMIC CAMP input signal
has  no  effect  on  write  protect  function.  The  PMIC  allows  write  and  read  access  to  all  registers.  Caution:  The
operation  of  non-write  protect  mode  should  be  limited  to  lab  and  debug  environment  instead  of  normal  system
operation.

JPGNetworksLLC

By default, PMIC Fail_n function is enabled (Table 140, “Register 0x32” [4] = ‘0’). When PMIC CAMP input signal
transitions from High to Low, the PMIC executes VR Disable command (i.e., execute power off sequence config0 to
config3 registers), asserts CAMP signal low (if Table 140, “Register 0x32” [3] = ‘0’), exits the write protect mode
and clears Table 140, “Register 0x32” [7] to ‘0’.

If Table 140, “Register 0x32” [4] = ‘1’, the PMIC Fail_n function is disabled. When CAMP signal transition from
High to Low, The PMIC does not execute VR Disable command (i.e., does not execute power off sequence config0 to
config3  registers),  does  not  assert  CAMP  signal  low,  exits  the  write  protect  mode  and  does  not  clear  Table 140,
“Register 0x32” [7] to ‘0’.

The Fail_n function is independent of PMIC’s write protect function.

2.7.7.2   Fail_n Function

2.7.7.3   Status Function

The PMIC CAMP PWR_GOOD output signal indicates status of VIN_Bulk input supply and all output regulators
(VOUT_A, VOUT_B, VOUT_C, VOUT_D, VOUT_1.8V, VOUT_1.0V, VBias).  Once  PMIC  receives VR  Enable
command,  the  PMIC  floats  CAMP  pin  when  VIN_Bulk  input  supply  is  valid  and  all  enabled  output  regulator’s
(VOUT_A,  VOUT_B,  VOUT_C,  VOUT_D,  VOUT_1.8V,  VOUT_1.0V,  VBias)  tolerances  are  maintained  as
configured in the appropriate register space. Note that CAMP pin is not affected based on VIN_Mgmt input supply.

At  first  power  up,  with  stable  and  valid  input  supply VIN_Mgmt  as  well  as VOUT_1.8V  and VOUT_1.0V  LDO
outputs, the PMIC asserts CAMP pin low however PMIC updates corresponding status register. Once PMIC receives
VR Enable command from the host, the PMIC enables all appropriate output regulators and updates corresponding
status registers and enters state called as “Regulation”. At this point, PMIC floats CAMP PWR_GOOD output and
the external board pullup resistor pulls the CAMP pin high. Once the CAMP pin is pulled high (i.e., no other PMIC is
driving the CAMP pin low), the PMIC enters state stated called as “online” state.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 33

2.7.7.3 Status Function (cont’d)

Once the CAMP pin is high, if PMIC detects any condition either on VIN_Bulk input supply or any of the output
regulators (VOUT_A, VOUT_B, VOUT_C, VOUT_D, VOUT_1.8V, VOUT_1.0V, VBias) that causes the PMIC to
update  it  status  registers  to  indicate  the  power  status  is  not  good,  then  PMIC  asserts  CAMP  pin  low  and  keeps  it
asserted until the host explicitly takes a specific action corresponding to it. The PMIC does not automatically let the
CAMP  pin  float  even  if  the  condition  that  triggered  the  PMIC  to  assert  the  CAMP  pin  no  longer  exists.  In  other
words, the PMIC’s CAMP pin is latched and once latched, it must be explicitly addressed by the host.

Regardless of whether PMIC is operating in write protect mode or not, the PMIC always asserts CAMP signal low to
indicate the status if there is a fault event.

2.7.8   GSI_n Signal

General Status Interrupt (GSI_n) is an Open Drain output signal. By default at power on, GSI_n output is disabled.
The host can enable the GSI_n output by setting Table 117, “Register 0x1B” [3] = ‘1’. Typically, GSI_n output is
pulled up to 1 KΩ resistor to 1.8 V or 3.3 V. The PMIC asserts GSI_n output for the events as described in Table 27,
“Events Interrupt Summary”.

2.7.9   State Transition Diagram

Following is a summary of high level description of basic PMIC states.

Offline State:

•  VIN_Mgmt is invalid and VIN_Bulk = X (valid or invalid); LDOs are invalid
•  All registers are reset to specified default values
•  CAMP is Hi-Z

JPGNetworksLLC

Configuration (non write protect) state:

•  At initial configuration state, all registers follow the register attributes as defined and read/write accessible.
•  The I2C/I3C bus interface is alive and running.
•  LDOs are valid; switch regulators are off
•  CAMP is low

Regulation (non write protect) state:

•  All registers are read/write accessible.
•  All enabled output rails are active
•  Internal power good is floated; external CAMP is low

Online (write protect) state:

•  All registers are readable. All non protect registers are writable.
•  All enabled output rails are active,i.e., PMIC has registered VR Enable command with Table 137, “Register

0x2F” = ‘0’.
•  CAMP is high
•  Note: Prior to PMIC registering VR Enable command, PMIC may be configured to not execute VR Enable
command and float its CAMP PWR_GOOD output signal (Table 140, “Register 0x32” = 0x08) with default
configuration of Table 137, “Register 0x2F” = ‘0’. In this configuration, PMIC also enters write protect state
when CAMP signal is pulled high.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 34

2.7.9 State Transition Diagram (cont’d)

Figure 17 shows high level simplified state diagram. Specific transition details are function of PMIC’s configuration
register  settings  (e.g.,  R2F,  R32,  etc.,  as  well  as  CAMP  signal  and  input/output  supplies).  Please  refer  to  detail
functional  description  and  configuration  register  definition  for  PMIC  operation.  Consider  an  example  of  a  valid
PMIC operation: When the PMIC first powers up from an offline state, the PMIC register Table 137, “Register 0x2F”
[2] can be configured to ‘1’ followed by VR Enable command. After PMIC turns on all regulators and floats CAMP
signal such that it is pulled up High, PMIC is in online state but allows all register write/read access as PMIC is not in
write protect state. In this state, the PMIC does allow to clear Table 137, “Register 0x2F” [2] to ‘0’ which will cause
PMIC to enter in write protect state as the CAMP signal was already pulled up High and the PMIC was in regulation.

Offline

Invalid LDO or invalid
VIN_Bulk & VIN_Mgmt

Valid VIN_Mgmt;
Valid 1.8V & 1.0V LDOs

Invalid 1.8V or 1.0V LDOs

JPGNetworksLLC

Configuration
Non Write
Protect

VR Disable

VR Enable

Regulation
Non Write
Protect

PMIC isolation with
CAMP @ logic high

VIN_Bulk invalid or CAMP
@ logic low & R32[4] = 0

CAMP @ logic
low & R32[4] = 1

CAMP @
logic high

Online
Write
Protect

Figure 17 — High Level State Transitions

Revision 1.8.5

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JEDEC Standard No. 301-1A.02
Page 35

2.7.10   Function Interrupt - CAMP and GSI_n Output Signals

This clause defines the output functionality of GSI_n pin and CAMP pin.

When  mask  register  bits  are  not  set,  the  PMIC  asserts  its  GSI_n  output  and  CAMP  output  signals  as  shown  in
Table 27  when  any  event  occurs. The  table  also  highlights  11  events  that  causes  PMIC  to  generate  internally VR
Disable command. For remaining events that does not trigger internal VR Disable command, the PMIC continues to
operate as normal.

Table 27 — Events Interrupt Summary

Event

VIN_Bulk Power Good
VIN_Bulk Over Voltage
VIN_Mgmt Over Voltage
SWA Output Power Good
SWB Output Power Good
SWC Output Power Good
SWD Output Power Good
1.8 V LDO Power Good
1.0 V LDO Power Good
VBias LDO Power Good
SWA Output Over Voltage
SWB Output Over Voltage
SWC Output Over Voltage
SWD Output Over Voltage
SWA Output Under Voltage
SWB Output Under Voltage
SWC Output Under Voltage
SWD Output Under Voltage
VBias LDO Output or VIN_Bulk Input
Under Voltage
SWA Output Current Limit
SWB Output Current Limit
SWC Output Current Limit
SWD Output Current Limit
SWA Output High Current/Power
SWB Output High Current/Power
SWC Output High Current/Power
SWD Output High Current/Power
High Temperature Warning
Critical Temperature
VIN_Mgmt to VIN_Bulk Switchover
Valid VIN_Mgmt in Switchover State
PEC Error
Parity Error

Threshold Bits

R1A [7:5]
R1B [7]
R1B [5]
R21 [0]; R22 [7:6]
R23 [0]’ R24 [7:6]
R25 [0]; R26 [7:6]
R27 [0]; R28 [7:6]
R1A [2]
R1A [0]
R1A [3]
R22 [5:4]
R24 [5:4]
R26 [5:4]
R28 [5:4]
R22 [3:2]
R24 [3:2]
R26 [3:2]
R28 [3:2]

Trigger VR
Disable?
No
Yes
No
No
No
No
No
No
No
No
Yes
Yes
Yes
Yes
Yes
Yes
Yes
Yes

JPGNetworksLLC

Vendor Specific

R33 [3]

R14 [3]

R19 [3]

Yes

Status
Bit
R08 [7]
R08 [0]
R08 [1]
R08 [5]
R08 [4]
R08 [3]
R08 [2]
R09 [5]
R33 [2]
R09 [6]
R0A [7]
R0A [6]
R0A [5]
R0A [4]
R0B [3]
R0B [2]
R0B [1]
R0B [0]

R0B [7]
R0B [6]
R0B [5]
R0B [4]
R09 [3]
R09 [2]
R09 [1]
R09 [0]
R09 [7]
R08[6]
R09 [4]
R33 [4]
R0A [3]
R0A [2]

Mask
Bit
R15 [7]
R15 [0]
R15 [1]
R15 [5]
R15 [4]
R15 [3]
R15 [2]
R16 [5]
R19 [2]
R16 [6]
R17 [7]
R17 [6]
R17 [5]
R17 [4]
R18 [3]
R18 [2]
R18 [1]
R18 [0]

R18 [7]
R18 [6]
R18 [5]
R18 [4]
R16 [3]
R16 [2]
R16 [1]
R16 [0]
R16 [7]
N/A
R16 [4]
R19 [4]
R17 [3]
R17 [2]

Clear
Bit
R10 [7]
R10 [0]
R10 [1]
R10 [5]
R10 [4]
R10 [3]
R10 [2]
R11 [5]
R14 [2]
R11 [6]
R12 [7]
R12 [6]
R12 [5]
R12 [4]
R13 [3]
R13 [2]
R13 [1]
R13 [0]

R13 [7]
R13 [6]
R13 [5]
R13 [4]
R11 [3]
R11 [2]
R11 [1]
R11 [0]
R11 [7]
N/A
R11 [4]
R14 [4]
R12 [3]
R12 [2]

R20 [7:6]
R20 [5:4]
R20 [3:2]
R20 [1:0]
R1C [7:2]
R1D [7:2]
R1E [7:2]
R1F [7:2]
R1B [2:0]
R2E [2:0]
R2F [7]
N/A
N/A
N/A

No
No
No
No
No
No
No
No
No
Yes
No
No
No
No

CAMP
Output
Low
Low
High
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low

Low

High
High
High
High
High
High
High
High
High
Low
High
High
High
High

GSI_n
Output
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low

Low

Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low

The host is expected to read appropriate status registers to determine and isolate the cause of the GSI_n signal
assertion or CAMP signal assertion. The host may attempt to clear or mask the appropriate corresponding interrupt
event. The PMIC keeps the GSI_n signal asserted or CAMP signal asserted until the appropriate corresponding
registers are explicitly cleared or masked by the host. Table 28 and Table 29 show the PMIC’s response of GSI_n
signal and CAMP output signal for each event before and after host issues the Clear command. Table 28 and Table 29
assume that all mask bits are either ‘0’ or ‘1’ for simplicity.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 36

 2.7.10 Function Interrupt - CAMP and GSI_n Output Signals (cont’d)

Table 28 — PMIC Response for Clear Command by Host - 1

Event Occurred; All
Mask Bits = ‘0’

Clear Command;
Event Not Present;
All Mask Bits = ‘0’

R2F [1:0] = ‘00’ or
‘01’ or ‘10’

Event Occurred; All
Mask Bits = ‘1’

Clear Command;
Event Not Present;
All Mask Bits = ‘1’

R2F [1:0] = ‘00’

R2F [1:0] = ‘00’

Event

VIN_Bulk Power Good
VIN_Bulk Over Voltage
VIN_Mgmt Over Voltage
SWA Output Power Good
SWB Output Power Good
SWC Output Power Good
SWD Output Power Good
1.8 V LDO Power Good
1.0 V LDO Power Good
VBias LDO Power Good
SWA Output Over Voltage
SWB Output Over Voltage
SWC Output Over Voltage
SWD Output Over Voltage
SWA Output Under Voltage
SWB Output Under Voltage
SWC Output Under Voltage
SWD Output Under Voltage
VBias LDO Output or VIN_Bulk
Input Under Voltage
SWA Output Current Limit
SWB Output Current Limit
SWC Output Current Limit
SWD Output Current Limit
SWA Output High Current/Power
SWB Output High Current/Power
SWC Output High Current/Power
SWD Output High Current/Power
High Temperature Warning
Critical Temperature
VIN_Mgmt to VIN_Bulk Switchover
Valid VIN_Mgmt in Switchover
PEC Error
Parity Error

CAMP
Output
Low
Low
High
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low

High
High
High
High
High
High
High
High
High
Low
High
High
High
High

CAMP
Output
High
Low
High
High
High
High
High
High
High
High
Low
Low
Low
Low
Low
Low
Low
Low

High
High
High
High
High
High
High
High
High
P/C
High
High
High
High

GSI_n
Output
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High

High
High
High
High
High
High
High
High
High
P/C
High
High
High
High

JPGNetworksLLC

High

Low

Low

Low

Low

CAMP
Output
Low
Low
High
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low

High
High
High
High
High
High
High
High
High
Low
High
High
High
High

GSI_n
Output
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low

Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low

GSI_n
Output
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High

High

High
High
High
High
High
High
High
High
High
Low
High
High
High
High

CAMP
Output
High
Low
High
High
High
High
High
High
High
High
Low
Low
Low
Low
Low
Low
Low
Low

Low

High
High
High
High
High
High
High
High
High
P/C
High
High
High
High

GSI_n
Output
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High

High

High
High
High
High
High
High
High
High
High
P/C
High
High
High
High

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

 2.7.10 Function Interrupt - CAMP and GSI_n Output Signals (cont’d)

JEDEC Standard No. 301-1A.02
Page 37

Table 29 — PMIC Response for Clear Command by Host - 2

Event Occurred; All
Mask Bits = ‘1’

Clear Command;
Event Not Present;
All Mask Bits = ‘1’

Event Occurred; All
Mask Bits = ‘1’

Clear Command;
Event Not Present;
All Mask Bits = ‘1’

R2F [1:0] = ‘01’

R2F [1:0] = ‘01’

R2F [1:0] = ‘10’

R2F [1:0] = ‘10’

Event

VIN_Bulk Power Good
VIN_Bulk Over Voltage
VIN_Mgmt Over Voltage
SWA Output Power Good
SWB Output Power Good
SWC Output Power Good
SWD Output Power Good
1.8 V LDO Power Good
1.0 V LDO Power Good
VBias LDO Power Good
SWA Output Over Voltage
SWB Output Over Voltage
SWC Output Over Voltage
SWD Output Over Voltage
SWA Output Under Voltage
SWB Output Under Voltage
SWC Output Under Voltage
SWD Output Under Voltage
VBias LDO Output or VIN_Bulk Input
Under Voltage
SWA Output Current Limit
SWB Output Current Limit
SWC Output Current Limit
SWD Output Current Limit
SWA Output High Current/Power
SWB Output High Current/Power
SWC Output High Current/Power
SWD Output High Current/Power
High Temperature Warning
Critical Temperature
VIN_Mgmt to VIN_Bulk Switchover
Valid VIN_Mgmt in Switchover
PEC Error
Parity Error

CAMP
Output
High
Low
High
High
High
High
High
High
High
High
Low
Low
Low
Low
Low
Low
Low
Low

High
High
High
High
High
High
High
High
High
Low
High
High
High
High

GSI_n
Output
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low

Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low
Low

CAMP
Output
High
Low
High
High
High
High
High
High
High
High
Low
Low
Low
Low
Low
Low
Low
Low

High
High
High
High
High
High
High
High
High
P/C
High
High
High
High

Low

JPGNetworksLLC

High

Low

Low

Low

CAMP
Output
High
Low
High
High
High
High
High
High
High
High
Low
Low
Low
Low
Low
Low
Low
Low

High
High
High
High
High
High
High
High
High
Low
High
High
High
High

GSI_n
Output
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High

High
High
High
High
High
High
High
High
High
P/C
High
High
High
High

GSI_n
Output
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High

High

High
High
High
High
High
High
High
High
High
Low
High
High
High
High

CAMP
Output
High
Low
High
High
High
High
High
High
High
High
Low
Low
Low
Low
Low
Low
Low
Low

Low

High
High
High
High
High
High
High
High
High
P/C
High
High
High
High

GSI_n
Output
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High
High

High

High
High
High
High
High
High
High
High
High
P/C
High
High
High
High

Note that when host masks any of the event in appropriate register, it only masks the assertion of GSI_n output signal
or assertion of CAMP output signal. The PMIC functional behavior remains the same as noted for each event other
than assertion of GSI_n output signal and assertion of CAMP output signal.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 38

2.7.11   Input Power Good Status

There is one possibility where PMIC recognizes the input supply fail.

1.   VIN_Bulk goes below the threshold set in register Table 116, “Register 0x1A” [7:5].

When this event occurs for a period longer than tInput_PWR_GOOD_GSI_Assertion time then PMIC sets the
register Table 98, “Register 0x08” [7] and drives GSI_n and CAMP output signal as shown in Table 27 at the same
time. The PMIC allows access to all registers and PMIC continues to operate as normal as long as VIN_Bulk input
remains above 4.25 V. See also clause 2.7.15. The host is responsible for taking any specific action. The host may
clear the VIN_Bulk input power good status register by writing ‘1’ to register Table 98, “Register 0x08” [7] or by
writing ‘1’ to global status clear register Table 110, “Register 0x14” [0]. If the input power not good condition is still
present  then  PMIC  will  continue  to  drive  GSI_n  and  CAMP  output  signal  as  in  Table 27  and  the  status  register
Table 98, “Register 0x08” [7] will remain at ‘1’. If the input power not good condition persists, the host may set the
appropriate mask register to remove GSI_n or CAMP output signal as shown in Table 28 and Table 29.

2.7.12   Input Over Voltage Protection

There are two possibilities where PMIC recognizes the input over voltage event.

Note  that  after  VR  enable  command,  when  VIN_Mgmt  input  goes  below  the  threshold  set  in  register  Table 137,
“Register 0x2F” [7], it is reported as switchover event as described in clause 2.7.20. Prior to VR Enable command,
the VIN_Mgmt is always required to be above 2.8 V to guarantee PMIC’s functionality as described in clause 2.7.2.

1.   VIN_Mgmt input goes above the threshold set in register Table 117, “Register 0x1B” [5].
2.   VIN_Bulk input goes above the threshold set in register Table 117, “Register 0x1B” [7].

An input over voltage protection mechanism is implemented to limit the voltages to the PMIC. The PMIC actively
monitors the input voltage VIN_Bulk and VIN_Mgmt rail.

JPGNetworksLLC

When either one or both event occurs for a period longer than tInput_OV_GSI_Assertion time then PMIC sets the
register Table 98, “Register 0x08” [1:0] accordingly and drives GSI_n output signal as shown in Table 27 at the same
time. Note that at this point, the PMIC does not assert CAMP output signal. The PMIC allows access to all registers
and PMIC continues to operate as normal. The host is responsible for taking any specific action. The host may clear
the VIN_Mgmt or VIN_Bulk input over voltage status register by writing ‘1’ to register Table 106, “Register 0x10”
[1:0] appropriately or by writing ‘1’ to global status clear register Table 110, “Register 0x14” [0]. If the input over
voltage  condition  is  still  present  then  PMIC  will  continue  to  assert  GSI_n  output  signal  and  the  status  register
Table 98, “Register 0x08” [1:0] will remain at ‘1’.
In non write protect mode, if VIN_Bulk input supply over voltage condition persists greater than tInput_OV_VR_-
Disable time then PMIC internally generates VR Disable command and disables all of its switching output regulators
and  asserts  CAMP  signal. The  PMIC  keeps  its VOUT_1.8V  and VOUT_1.0V  LDO  output  regulators  active. The
PMIC allows access to all registers. The host is responsible for taking any specific action. The host may query the
PMIC  register  space  to  determine  the  cause  of  the  CAMP  signal  assertion  and  GSI_n  signal  assertion.  Once  host
determines the cause, the host must first clear the VIN_Bulk input over voltage status register as well as any other
relevant status registers individually or by writing ‘1’ to global status clear register Table 110, “Register 0x14” [0]
which triggers the GSI_n signal to be de-asserted. If the input over voltage condition is still present then PMIC will
continue to assert GSI_n output signal and the status register Table 98, “Register 0x08” [0] will remain at ‘1’. Once
the status register is cleared and GSI_n output signal is de-asserted, the host may re-enable the PMIC’s output
switching  regulator  by  issuing VR  Enable  command.  The  PMIC  enables  output  switching  regulators  and  ensures
CAMP signal is floated when all of its output regulators are normal and input over voltage condition is no longer
present.

In write protect mode, if VIN_Bulk input supply over voltage condition persists greater than tInput_OV_VR_Disable
time then PMIC internally generates VR Disable command and disables all of its switching output regulators by
executing Power Off Sequence configuration registers, asserts CAMP signal low and returns to configuration mode.
The PMIC keeps its VOUT_1.8V and VOUT_1.0V LDO output regulators active.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 39

2.7.13   Output Power Good Status

The PMIC provides the voltage tolerance information to host that its output regulator may have crossed the desired
voltage tolerance from its nominal programmed setting. The nominal programmed setting for output regulator SWA,
SWB, SWC and SWD is programmed in register Table 123, “Register 0x21” [7:1], Table 125, “Register 0x23” [7:1],
Table 127, “Register 0x25” [7:1], and Table 129, “Register 0x27” [7:1], respectively. The PMIC offers the CAMP
condition to be set independently for low side and high side.

In addition, PMIC has three LDO regulators: VBias, VOUT_1.8V, and VOUT_1.0V

There are five possibilities where PMIC recognizes the output power good event for any output regulator.

1.   Output voltage goes below the threshold set in register Table 123, “Register 0x21” [0] for SWA or Table 125,
“Register 0x23” [0] for SWB or Table 127, “Register 0x25” [0] for SWC, or Table 129, “Register 0x27” [0]
for SWD.

2.      Output  voltage  goes  above  the  threshold  set  in  register  Table 124,  “Register  0x22”  [7:6]  for  SWA  or

Table 126, “Register 0x24” [7:6] for SWB or Table 128, “Register 0x26” [7:6] for SWC, or
Table 130, “Register 0x28” [7:6] for SWD.

3.   LDO output VBias goes below the threshold set in register Table 116, “Register 0x1A” [3].

5.   LDO output VOUT_1.0V goes below the threshold set in register Table 116, “Register 0x1A” [0].

4.   LDO output VOUT_1.8V goes below the threshold set in register Table 116, “Register 0x1A” [2].

When either event occurs for a period longer than Output_PWR_GOOD_GSI_Assertion time then PMIC sets the
register Table 98, “Register 0x08” [5:2] or Table 99, “Register 0x09” [6:5] or Table 141, “Register 0x33” [2]
appropriately and drives CAMP and GSI_n output signal as shown in Table 27 at the same time. The PMIC may
continue to operate but DDR5 DIMM functionality may not be guaranteed. The PMIC allows access to all registers.
The host is responsible for taking any specific action. The host may query the PMIC register space to determine and
identify the cause of the CAMP signal assertion and GSI_n signal assertion. Once host determines the cause, the host
may clear the appropriate status register individually or by writing ‘1’ to global status clear register
Table 110, “Register 0x14” [0] which triggers the GSI_n signal to be de-asserted and CAMP signal to be de-asserted.
If the output power not good condition is still present then PMIC will continue to assert GSI_n output signal and
assert CAMP signal and the appropriate status register Table 98, “Register 0x08” [5:2] or Table 99, “Register 0x09”
[6:5] or Table 141, “Register 0x33” [2] will remain at ‘1’. If the output power not good condition persists, the host
may set the appropriate mask register to remove GSI_n or CAMP output signal as shown in Table 28 and Table 29.

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 40

2.7.14   Output Over Voltage Protection

An output over voltage protection mechanism is implemented to limit the voltages on the PMIC output regulators.
The PMIC actively monitors the output voltage on each enabled regulators.

There are four possibilities where PMIC recognizes the over voltage event.

1.   SWA output regulator goes above the threshold set in register Table 124, “Register 0x22” [5:4].
2.   SWB output regulator goes above the threshold set in register Table 126, “Register 0x24” [5:4].
3.   SWC output regulator goes above the threshold set in register Table 128, “Register 0x26” [5:4].
4.   SWD output regulator goes above the threshold set in register Table 130, “Register 0x28” [5:4].

2.7.14.1  DDR5 RDIMM/LRDIMM Environment - Table 166, “Register 0x4F” [7] = ‘0’:

In non write protect mode, if any output over voltage condition persists greater than tOutput_OV_VR_Disable time
then PMIC internally generates VR Disable command and disables all of its switching output regulators, sets register
Table 100, “Register 0x0A” [7:4] appropriately, asserts CAMP and asserts GSI_n output signal. The PMIC keeps its
VOUT_1.8V and VOUT_1.0V LDO output regulators active. The PMIC allows access to all registers. The host is
responsible for taking any specific action. The host may query the PMIC register space to determine the cause of the
CAMP  signal  assertion  and  GSI_n  signal  assertion.  Once  host  determines  the  cause,  the  host  must  first  clear  the
appropriate output over voltage status register as well as any other relevant status registers individually or by writing
‘1’ to global status clear register Table 110, “Register 0x14” [0] which triggers the GSI_n signal to be de-asserted.
Once the status register is cleared and GSI_n output signal is de-asserted, the host may re-enable the PMIC’s output
switching  regulator  by  issuing VR  Enable  command.  The  PMIC  enables  output  switching  regulators  and  ensures
CAMP signal is floated when all of its output regulators are normal.

In write protect mode, if any output over voltage condition persists greater than tOutput_OV_VR_Disable time then
PMIC  internally  generates VR  Disable  command  and  disables  all  of  its  switching  output  regulators  by  executing
Power Off Sequence configuration registers, asserts CAMP signal low and returns to configuration mode. The PMIC
keeps its VOUT_1.8V and VOUT_1.0V LDO output regulators active.

JPGNetworksLLC

In non write protect mode, if any output over voltage condition persists greater than tOutput_OV_VR_Disable time
then PMIC internally generates VR Disable command to disable only the affected switching output regulator, sets
register Table 100, “Register 0x0A” [7:4] appropriately, asserts CAMP and asserts GSI_n output signal and continues
to operate normal on other output regulators. The PMIC keeps its VOUT_1.8V and VOUT_1.0V LDO output
regulators active. The PMIC allows access to all registers. The host is responsible for taking any specific action. The
host may query the PMIC register space to determine the cause of the CAMP signal assertion and GSI_n signal
assertion. Once host determines the cause, the host must first clear the appropriate output over voltage status register
as well as any other relevant status registers individually or by writing ‘1’ to global status clear register Table 110,
“Register 0x14” [0] which triggers the GSI_n signal to be de-asserted. Once the status register is cleared and GSI_n
output  signal  is  de-asserted,  the  host  may  re-enable  the  PMIC’s  output  switching  regulator  by  issuing VR  Enable
command. The PMIC enables output switching regulator and floats CAMP signal when all of its output regulators are
normal. Note that in this case, though Host issues VR Enable command, it only turns on the only affected regulator
that was disabled.

2.7.14.2  DDR5 NVDIMM or other Custom Environment: Table 166, “Register

0x4F”[7]=‘1’

The write protect mode is not allowed when Table 166, “Register 0x4F” [7] = ‘1’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 41

2.7.15   Output Under Voltage and VIN_Bulk Under Voltage Lockout Protection

An  output  under  voltage  lockout  protection  mechanism  is  implemented  to  limit  the  voltages  on  the  PMIC  output
regulators. The PMIC actively monitors the output voltage on each enabled regulators.

There are five possibilities where PMIC recognizes the under voltage lockout event.

1.   SWA output regulator goes below the threshold set in register Table 124, “Register 0x22” [3:2].
2.   SWB output regulator goes below the threshold set in register Table 126, “Register 0x24” [3:2].
3.   SWC output regulator goes below the threshold set in register Table 128, “Register 0x26” [3:2].
4.   SWD output regulator goes below the threshold set in register Table 130, “Register 0x28” [3:2].
5.   VBias LDO output regulator goes below the vendor specific threshold or VIN_Bulk Input Voltage goes

below vendor specific threshold.

2.7.15.1  DDR5 RDIMM/LRDIMM Environment - Table 166, “Register 0x4F” [7] = ‘0’:

2.7.15.2  DDR5 NVDIMM or other Custom Environment - Table 166, “Register 0x4F”

In non write protect mode, if any output under voltage condition (among five possibilities listed above) or VIN_Bulk
input voltage condition as listed above persists greater than tOutput_UV_VR_Disable time then PMIC internally
generates VR Disable command and disables all of its switching output regulators, sets register Table 101, “Register
0x0B” [3:0], Table 141, “Register 0x33” [3] appropriately, asserts CAMP and asserts GSI_n output signal. The PMIC
keeps its VOUT_1.8V and VOUT_1.0V LDO output regulators active. The PMIC allows access to all registers. The
host is responsible for taking any specific action. The host may query the PMIC register space to determine the cause
of the CAMP signal assertion and GSI_n signal assertion. Once host determines the cause, the host must first clear the
appropriate output under voltage status register as well as any other relevant status registers individually or by writing
‘1’ to global status clear register Table 110, “Register 0x14” [0] which triggers the GSI_n signal to be de-asserted.
Once the status register is cleared and GSI_n output signal is de-asserted, the host may re-enable the PMIC’s output
switching regulator by issuing VR Enable command assuming valid VIN_Bulk input voltage. The PMIC enables
output switching regulators and floats CAMP signal when all of its output regulators are normal.

JPGNetworksLLC

In  write  protect  mode,  if  any  output  under  voltage  condition  (among  five  possibilities  listed  above)  or VIN_Bulk
input voltage condition as listed above persists greater than tOutput_UV_VR_Disable time then PMIC internally
generates VR Disable command and disables all of its switching output regulators by executing Power Off Sequence
configuration  registers,  asserts  CAMP  signal  low  and  returns  to  configuration  mode.  The  PMIC  keeps  its
VOUT_1.8V and VOUT_1.0V LDO output regulators active.

In non write protect mode, if any output under voltage condition (First four possibilities listed above) as listed above
persists greater than tOutput_UV_VR_Disable time then PMIC internally generates VR Disable command to disable
only  the  affected  switching  output  regulator,  sets  register  Table 101,  “Register  0x0B”  [3:0]  appropriately,  asserts
CAMP and asserts GSI_n output signal and continues to operate normal on other output regulators. Note that if the
fifth condition (VBias LDO output goes below vendor specific threshold or VIN_Bulk input goes below vendor
specific threshold) listed above persists greater than tOutput_UV_VR_Disable time, then the PMIC internally
generates VR Disable command and disables all of its switching output regulators, sets register Table 101, “Register
0x0B” [3:0] and Table 141, “Register 0x33” [3] appropriately, asserts CAMP and asserts GSI_n output signal. The
PMIC keeps its VOUT_1.8V and VOUT_1.0V LDO output regulators active. The PMIC allows access to all
registers. The host is responsible for taking any specific action. The host may query the PMIC register space to
determine the cause of the CAMP signal assertion and GSI_n signal assertion. Once host determines the cause, the
host must first clear the appropriate output under voltage status register as well as any other relevant status registers
individually or by writing ‘1’ to global status clear register Table 110, “Register 0x14” [0] which triggers the GSI_n
signal to be de-asserted. Once the status register is cleared and GSI_n output signal is de-asserted, the host may
re-enable the PMIC’s output switching regulator by issuing VR Enable command. The PMIC enables output
switching regulator and ensures CAMP signal is floated when all of its output regulators are normal. Note that in this
case, though Host issues VR Enable command, it only turns on the only affected regulator that was disabled.

[7]=‘1’

The write protect mode is not allowed when Table 166, “Register 0x4F” [7] = ‘1’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 42

2.7.16   Output Current Limiter Warning Event

The PMIC has output current limiter mechanism to limit the current on the PMIC output voltage regulators.

There are four possibilities where PMIC recognizes the current limiter event.

1.   SWA output regulator current goes above the threshold set in register Table 122, “Register 0x20” [7:6].

2.   SWB output regulator current goes above the threshold set in register Table 122, “Register 0x20” [5:4].

3.   SWC output regulator current goes above the threshold set in register Table 122, “Register 0x20” [3:2].

4.   SWD output regulator current goes above the threshold set in register Table 122, “Register 0x20” [1:0].

When  either  event  occurs  for  a  period  longer  than  tOutput_Current_Limiter  time  then  PMIC  sets  the  register
Table 101, “Register 0x0B” [7:4] appropriately, drives GSI_n output signal as shown in Table 27 at the same time.
The PMIC continues to operate as normal. The PMIC allows access to all registers. The host is responsible for taking
any specific action. The host may query the PMIC register space to determine the cause of the GSI_n signal assertion.
Once host determine the cause, the host may clear the appropriate output current limiter status register as well as any
other status registers individually or by writing ‘1’ to global status clear register in Table 110, “Register 0x14” [0]
which triggers the GSI_n signal to be de-asserted. If the output current limiter condition is still present then PMIC
will continue to assert GSI_n output signal and the appropriate status register in Table 101, “Register 0x0B” [7:4] will
remain at ‘1’. If the output current limiter condition persists, the host may set the appropriate mask register to remove
the GSI_n output signal as shown in Table 28 and Table 29.

2.7.17   Output High Current Consumption Warning Event

The PMIC supports high output current consumption warning mechanism for each of its regulator output. If enabled,
the PMIC actively monitors the average output current of the regulator.

There are four possibilities where PMIC recognizes the high output current consumption.

1.   SWA output regulator average current goes above the threshold set in register Table 118, “Register 0x1C”

JPGNetworksLLC

2.   SWB output regulator average current goes above the threshold set in register Table 119, “Register 0x1D”

3.   SWC output regulator average current goes above the threshold set in register Table 120, “Register 0x1E”

4.   SWD output regulator average current goes above the threshold set in register Table 121, “Register 0x1F”

[7:2].

[7:2].

[7:2].

[7:2].

When either event occurs then PMIC sets the register Table 99, “Register 0x09” [3:0] appropriately, drives GSI_n
output signal as shown in Table 27 at the same time. The PMIC continues to operate as normal. The PMIC allows
access to all registers. The host is responsible for taking any specific action. The host may query the PMIC register
space to determine the cause of the GSI_n signal assertion. Once host determines the cause, the host may clear the
appropriate output current consumption warning status register as well as any other status registers individually or by
writing ‘1’ to global status clear register in Table 110, “Register 0x14” [0] which triggers the GSI_n signal to be
de-asserted. If the output current consumption warning condition is still present then PMIC will continue to assert
GSI_n output signal and the appropriate status register in Table 99, “Register 0x09” [3:0] will remain at ‘1’. If the
output  current  consumption  warning  condition  persists,  the  host  may  set  the  appropriate  mask  register  to  remove
GSI_n output signal as shown in Table 28 and Table 29.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 43

2.7.18   PMIC LDO Output Failure

In the event where PMIC LDO outputs (VOUT_1.8V or VOUT_1.0V) failure occurs and PMIC cannot reliably
support external communication, the PMIC has no control of CAMP signal and it is floated. The PMIC returns to
“offline” state.

Note that the PMIC operation itself may not be guaranteed as PMIC internally may use the LDO output voltages for
its own internal operation.

2.7.19   PMIC High Temperature Warning and Critical Temperature Protection

The PMIC provides a high temperature warning mechanism as well as critical temperature shutdown. There are two
registers associated with PMIC temperature: The high temperature warning threshold register Table 117, “Register
0x1B” [2:0] and shutdown temperature threshold register Table 136, “Register 0x2E” [2:0]. The value programmed
in the shutdown temperature register must be equal or greater than value programmed in a warning threshold register.

There is one possibility where PMIC recognizes the high temperature event.

1.   The PMIC temperature goes above the threshold set in register Table 117, “Register 0x1B” [2:0].

When  the  above  event  occurs  for  a  period  longer  than  tHigh_Temp_Warning  time,  the  PMIC  sets  the  register
Table 99, “Register 0x09” [7] and drives GSI_n output signal as shown in Table 27 at the same time. The PMIC
continues to operate as normal. The PMIC allows access to all registers. The host is responsible for taking any
specific action. The host is responsible for taking any specific action. The host may query the PMIC register space to
determine the cause of the GSI_n signal assertion. Once host determines the cause, the host may clear the temperature
warning status register as well as any other status registers individually or by writing ‘1’ to global status clear register
in Table 110, “Register 0x14” [0] which triggers the GSI_n signal to be de-asserted. If the high temperature warning
condition is still present then PMIC will continue to assert GSI_n output signal and the appropriate status register in
Table 99, “Register 0x09” [7] will remain at ‘1’. If the high temperature warning condition persists, the host may set
the appropriate mask register to remove GSI_n output signal as shown in Table 28 and Table 29.

JPGNetworksLLC

If the PMIC temperature goes above the threshold set in register Table 136, “Register 0x2E” [2:0] for a period longer
than tShut_Down_Temp time, the PMIC internally generates VR Disable command and disables all of its switching
output regulators as well as Vbias voltage regulator (optional), sets the code in register Table 95, “Register 0x05”
[2:0], updates Table 98, “Register 0x08” [6], drives GSI_n and CAMP output signal as shown in Table 27 at the same
time.  The  PMIC  keeps  its  VOUT_1.8V  LDO  and  VOUT_1.0V  LDO  output  regulator  active.  The  PMIC  allows
access to all registers. The host is responsible for taking any specific action. The host is expected to monitor the
temperature status registers. When the  temperature drops below the threshold, the host  must re-start the PMIC  by
going through the power cycle of the VIN_Mgmt and VIN_Bulk input supply. If the PMIC is in VIN_Bulk input
supply switchover state, the host must re-start the PMIC by going through the power cycle of the VIN_Bulk input
supply.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 44

2.7.20   VIN_Mgmt to VIN_Bulk Input Supply Switchover Event

After VR Enable command is registered, the PMIC automatically switches over from VIN_Mgmt to VIN_Bulk input
supply under following condition.

1.   VIN_Mgmt goes below the threshold set in register Table 137, “Register 0x2F” [7].

When the above event occurs for a period longer than tInput_PWR_GOOD_GSI_Assertion time then PMIC sets the
register Table 99, “Register 0x09” [4] and drives GSI_n output signal as shown in Table 27 at the same time. The
PMIC continues to operate as normal. The PMIC allows access to all registers. The host is responsible for taking any
specific action. The host may query the PMIC register space to determine the cause of the GSI_n signal assertion.
Once host determines the cause, the host may clear the status register individually or by writing ‘1’ to global status
clear register in Table 110, “Register 0x14” [0] which triggers the GSI_n signal to be de-asserted. No further action is
needed by the host or the PMIC at this point.

Note that this event is treated differently by the PMIC. When host clears this event, the PMIC must remove the GSI_n
signal assertion even though PMIC does not see valid VIN_Mgmt. This is to simplify host because host knows that
there is no VIN_Mgmt and yet host expects the PMIC (as well as system) to continue to run normal and host should
not have to worry about masking this event in PMIC. It is assumed that at some point VIN_Mgmt supply will come
back up again, PMIC will detect it and assert GSI_n output signal as described in clause 2.7.21. At this point, PMIC
will be ready to assert GSI_n output signal again if VIN_Mgmt input supply goes below the threshold set in register
Table 137, “Register 0x2F” [7].

JPGNetworksLLC

When PMIC is in switchover mode as described in clause 2.7.20, the VIN_Mgmt input supply may power back up at
any time. When VIN_Mgmt input supply re-powers backup, the PMIC sets the register Table 141, “Register 0x33”
[4] and drives GSI_n output signal as shown in Table 27 at the same time. The PMIC continues to operate as normal
and automatically switches back to VIN_Mgmt input supply. The PMIC allows access to all registers. The host is
responsible for taking any specific action.The host may query the PMIC register space to determine the cause of the
GSI_n  signal  assertion.  Once  host  determines  the  cause,  the  host  may  clear  the  status  register  individually  or  by
writing ‘1’ to global status clear register in Table 110, “Register 0x14” [0] which triggers the GSI_n signal to be
de-asserted. No further action is needed by the host or the PMIC at this point.

Note that this event is treated differently by the PMIC. When host clears this event, the PMIC must remove the GSI_n
signal  assertion  even  though  PMIC  still  sees  valid  VIN_Mgmt.  This  is  to  simplify  host  because  host  knows  that
VIN_Mgmt input supply is back and so host expects the PMIC (as well as system) to continue to run normal and host
should not have to worry about masking this event in PMIC. It is assumed that if at some point VIN_Mgmt supply
goes below the threshold again, PMIC will detect it and assert GSI_n output signal as described in clause 2.7.20. At
this point, PMIC will be ready to assert GSI_n output signal again if VIN_Mgmt input supply re-powers back up
again.

2.7.21   Valid VIN_Mgmt Supply Detection in Switchover Mode

2.7.22   Packet Error Code (PEC) and Parity Error Event

In I3C Basic mode, on PMIC’s primary management interface, PEC function and Parity function can be enabled. If
enabled, when PMIC detects either PEC error or Parity Error, the PMIC sets the register Table 100, “Register 0x0A”
[3:2] appropriately, drives GSI_n output signal as shown in Table 27 and it continues to operate as normal and allows
access to all registers. See clause 2.10.8 to 2.10.9 for additional details. The host is responsible for taking any specific
action. The host may query the PMIC register space to determine the cause of the GSI_n signal assertion. Once host
determines the cause, the host may clear the status register individually or by writing ‘1’ to global status clear register
in Table 110, “Register 0x14” [0] which triggers the GSI_n signal to be de-asserted. No further action is needed by
the host from this point on.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 45

2.8   Analog to Digital Converter (ADC)

The PMIC supports analog to digital converter (ADC) to monitor input supply voltages (VIN_Bulk and VIN_Mgmt)
as well as output voltage regulator voltage (SWA, SWB, SWC, SWD, VBias, VOUT_1.8V and VOUT_1.0V). The
register  Table 138,  “Register  0x30”  [7:3]  allows  to  enable  the ADC  and  select  the  desire  input  supply  voltage  or
output supply voltage. The register Table 139, “Register 0x31” [7:0] provides the actual voltage measurement. The
accuracy of the voltage measurement is as following:

•  Switch Output Voltage Regulator SWA, SWB, SWC (Output Voltage Range: 1050 mV to 1160 mV): + 1 LSB
•  Switch Output Voltage Regulator SWA, SWB, SWC (Output Voltage Range outside of 1050 mV to 1160 mV):

+ 3 LSB

•  Switch Output Voltage Regulator SWD (Output Voltage Range: 1750 mV to 1850 mV): + 1 LSB
•  Switch Output Voltage Regulator SWD (Output Voltage Range outside of 1750 mV to 1850 mV): + 3 LSB
•  VOUT_1.8V, VOUT_1.0V: + 3 LSB
•  VBias Output Voltage, VIN_Bulk, VIN_Mgmt Input Voltage: + 6 LSB

The  PMIC  also  monitors  output  voltage  regulator  current  or  power  (SWA,  SWB,  SWC  and  SWD)  and  updates
registers Table 102, “Register 0x0C” [7:0] for SWA, Table 103, “Register 0x0D” [5:0] for SWB, Table 104, “Register
0x0E” [5:0] for SWC and Table 105, “Register 0x0F” [5:0] for SWD. The register Table 117, “Register 0x1B” [6]
allows  host  to  select  whether  PMIC  should  report  current  measurements  or  power  measurements.  The  current  or
power  measurement  reported  in  this  registers  are  an  average  measurement  over  time  period  defined  in  register
Table 138, “Register 0x30” [1:0]. If Table 117, “Register 0x1B” [6] = ‘1’, the register Table 116, “Register 0x1A” [1]
allows host to select whether PMIC should report individual rail power or total power in Table 102, “Register 0x0C”
[7:0]. The register update frequency of this register is configured in Table 138, “Register 0x30” [1:0]. The internal
sampling  rate  of  the  PMIC  is  vendor  specific.  The  accuracy  of  the  current  (>  0.5  A)  or  corresponding  power
measurement is + 3 LSB or + 6 LSB respectively. The accuracy of the current measurement (< 0.5 A) is + 4 LSB or
corresponding power measurement is + 7 LSB, respectively.

JPGNetworksLLC

The PMIC has PID input pin which allows to assign up to three different unique ID for I2C and I3C Basic protocol.
The PID input pin is shared with SWD_FB_N pin.

If register Table 116, “Register 0x1A” [1] = ‘1’, the accuracy of total power reported in register Table 102, “Register
0x0C” = + 12 LSB.

At first power on, when VIN_Mgmt input is applied, the PMIC automatically senses its ID. The PMIC also checks
the configuration register Table 166, “Register 0x4F” [1].

2.8.1   PMIC Address ID (PID)

If SWD output regulator is enabled and intended to operate in a single ended remote sensing mode, the PMIC offers
three different ID as shown in Table 30. If SWD output regulator is not enabled, the PMIC still offers three different
ID as shown in Table 30.

If SWD output regulator is enabled and intended to operate in a differential remote sensing mode, there is only one
default ID for the PMIC as shown in Table 30. This means, there can be only one PMIC on the DIMM (or I2C and
I3C Basic bus).

Table 30 — PMIC ID

R4F [1] =

PID Pin Connection on DIMM Board

‘0’

‘1’

short to GND

Floating

short to 1.8

Connect to Differential Sensing GND

PMIC ID

PID = 1001

PID = 1000

PID = 1100

PID = 1001

Comment

PMIC can be configured

Connected to PMIC’s VOUT_1.8V Rail

SWD differential sensing

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 46

2.8.2   Error Injection

The PMIC offers error injection function for the purpose of debug, test and validation at various stages.

Error Injection Function Usage prior to VR Enable:

•  Prior to VR Enable command, the Error injection function may be invoked by setting error injection enable bit
Table 143, “Register 0x35” [7] = ‘1’ during the configuration state. If any of either VIN_Bulk UV/OV or SWx
OV/UV or Critical Temp Shutdown error is injected prior to VR Enable command, the PMIC shall not execute
power on sequence and shall not enable PMIC output regulators when PMIC receives VR Enable command.
The PMIC shall not update error log registers (Table 94, “Register 0x04” to Table 96, “Register 0x06”). The
PMIC shall update appropriate status registers accordingly when error is injected.

Error Injection Function Usage after VR Enable:

•  After PMIC output regulators are enabled with VR Enable command and PMIC is in non write protect mode,
the error injection function may be invoked by setting error injection enable bit Table 143, “Register 0x35” [7]
=  ‘1’.  If  any  of  either VIN_Bulk  UV/OV  or  SWx  OV/UV  or  Critical Temp  Shutdown  error  is  injected  the
PMIC shall execute Power Off Sequence to disable PMIC output regulators and shall update the error log
registers (Table 94, “Register 0x04” to Table 96, “Register 0x06”) as well as status registers accordingly. Note
that  if  any  of  the  output  rails  are  not  enabled  through  power  on  sequence  configuration  registers,  the  error
injection on that output rail does not apply.

•  After PMIC output regulators are enabled with VR Enable command and PMIC is in write protect mode, the
error  injection  enabling  Table 143,  “Register  0x35”  [7]  =  ‘1’  is  disallowed.  The  PMIC  shall  ignore  any
attempts to inject any error and shall not execute Power Off Sequence to disable PMIC output regulators and
shall not update any error log or status registers.

To exit the error injection function, the host shall power cycle VIN_Bulk and VIN_Mgmt input supply.

JPGNetworksLLC

2.9   I2C and I3C Basic Interface Operation

At power on, by default, the PMIC device comes up in legacy I2C mode of operation. Following applies in I2C mode:

1.   The max operation speed is limited to 1 MHz
2.   In-band interrupts are not supported
3.   Bus reset is supported.
4.   Parity check is not supported except for supported CCCs.
5.   Packet Error check is not supported.

The PMIC device shall operate in the legacy I2C mode until put into I3C Basic mode via command.

The host may put the PMIC device in I3C Basic mode by issuing SETAASA CCC.

Following applies in I3C Basic mode.

1.   The max operation speed is up to 12.5 MHz
2.   In-band interrupts are supported
3.   Bus reset is supported.
4.   Parity check is always enabled by default.
5.   Packet error check is supported and by default is disabled.

2.10   Device Interface - Protocol

The 7-bit serial address of the PMIC device applies to both I2C and I3C Basic mode of operation identically.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 47

2.10.1   Serial Address of PMIC Device

The PMIC device 4-bit binary value (LID) is:

•  If PID pin is connected to GND on PCB: ‘1001’
•  If PID pin is tied to 1.8 V on PCB: ‘1100’
•  If PID pin is floating on PCB: ‘1000’

The PMIC device samples the status of the PID pin on power up. The sampled status of the PID pin is used to select
one of the three possible unique LID code for the device. The selected LID code either ‘1001’ or ‘1100’ or ‘1000’ is
merged with a 3 bit HID code Table 142, “Register 0x34” [3:1] to establish the 7-bit address code the device. For
example, with the default setting in Table 142, “Register 0x34” [3:1] = ‘111’; if the PID pin is connected to GND, the
device address shall be ‘1001 111’.

Table 31 — 7-bit Address of PMIC Device

Bit 0

R/W

Read/
Write

2.10.2   Switch from I2C Mode to I3C Basic Mode

Bit 7

1

PMIC Device Type ID (LID)

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

x

1

1

1

x

0

Host ID (HID)

JPGNetworksLLC

By default when PMIC first powers on, it operates in legacy I2C mode. The PMIC device shall operate in I2C mode
until put into I3C Basic mode via command.

In I2C mode, the host is allowed to issued only 3 CCCs (DEVCTRL, SETHID, SETAASA). All other CCCs are not
supported and the PMIC device may simply ignore it. The Host must issue DEVCTRL and SETHID CCC first (if
required) followed by SETAASA CCC.

The Host puts the PMIC device in I3C Basic mode by issuing SETAASA CCC.

When SETAASA CCC is registered by the PMIC device, it updates the Table 140, “Register 0x32” [6] to ‘1’.

When SETHID CCC is registered by the PMIC device, it updates the Table 142, “Register 0x34” [3:1].

2.10.3   Switch from I3C Basic Mode to I2C Mode

The Host can put the PMIC device back in I2C mode from I3C Basic mode at any time by issuing RSTDAA CCC.

When RSTDAA CCC is registered by the PMIC device, it updates the Table 140, “Register 0x32” [6] to ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 48

2.10.4   I2C Target Protocol

The  PMIC  device  operate  on  a  standard  I2C  serial  interface.  Transactions  where  the  PMIC  device  is  the  targeted
target device begin with the Host issuing a START condition followed by a 7-bit PMIC device address then a read or
write bit, RW. All data are transmitted with the most significant bit MSB first. During the address followed by R/W
bit transmission, the PMIC device typically replies with an ACK unless there are exceptional conditions when it may
passively assert a NACK.

The PMIC device host region registers that are write protected in write protect mode of operation, the PMIC ACKs
the host request but the PMIC does not execute the operation internally.

Similarly, regardless of write protect mode or non write protect mode of operation, without the correct password, all
DIMM  vendor  and  vendor  specific  region  registers  are  write  protected  and  PMIC ACKs  the  host  request  but  the
PMIC does not execute the operation internally.

The PMIC device accepts 1 byte of address which covers 256 bytes of registers. The PMIC device register space does
not require page selection process as all registers are within first 256 bytes.

2.10.4.1   Write Operation - Data Packet

Start
S or Sr1

Bit 7
1

Stop

Bit 1

Bit 3

Bit 0
W=0

Bit 2
HID

Bit 4
X

Bit 5
0

Bit 6
X

Table 32 — Write Command Data Packet

Address [7:0]
Data
...
Data

JPGNetworksLLC

Table 33 — Read Command Data Packet

P
NOTE 1  In I2C mode, Start or Repeat Start operation followed by 7’h7E with W=0 is only allowed for the purpose of
issuing CCCs that are allowed in I2C mode. Any other operation including another Repeat Start is considered
an illegal operation.

2.10.4.2   Read Operation - Data Packet

Start
S or Sr1

Bit 7
1

Bit 6
X

Bit 5
0

Bit 4
X

Bit 3

Address [7:0]

Sr

1

X

0

X

Bit 1

Bit 2
HID

HID

Bit 0
W=0

R=1

Stop

Data
...
Data

P
NOTE 1  In I2C mode, Start or Repeat Start operation followed by 7’h7E with W=0 is only allowed for the purpose of

issuing CCCs that are allowed in I2C mode. Any other operation including another Repeat Start is considered an
illegal operation.

NOTE 2  If target device NACKs during Repeat Start for any reason, the host my re-try Repeat Start again. The host can

do the Repeat Start as many times it may desire. The PMIC may eventually ACK.

NOTE 3  When PMIC device reaches last byte within the region (either Host region or DIMM vendor region), it will

continue to return data but returned data will be 0x00 if there is no valid password for DIMM vendor region or
Vendor specific region. Once the address counter reaches R255, it will reset to address R00 and it will continue
to return the data. Only Host can perform STOP operation.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

A/N
A
A
A
A
A

A/N
A
A
A2
A
A
N3

JEDEC Standard No. 301-1A.02
Page 49

2.10.4.3   Default Read Address Pointer Mode

During  normal  operation  of  the  DDR5  DIMM,  the  host  periodically  may  poll  critical  information  from  the  same
location. An example may be the PMIC device’s status registers or current or power measurement register readout. To
help  improve  the  efficiency  of  the  I2C  bus  protocol,  the  PMIC  offers  a  default  read  address  pointer  mode  so  that
whenever  the  PMIC  device  sees  the  STOP  operation  on  its  SCL  and  SDA  bus,  its  read  address  pointer  is  always
resets  to  default  address.  The  default  read  pointer  address  mode  is  enabled  through  register  Table 147,  “Register
0x3A” [6] and default starting address for read operation is selectable through register Table 147, “Register 0x3A”
[5:4]. This allows host to read the read command data packet as shown in Table 34. The default read address pointer
reduces the packet overhead by 2 bytes. The host typically enables this mode at last after VR Enable command when
the normal operation of the DDR5 DIMM begins.

Table 34 — Read Command Data Packet with Default Address Pointer Mode

A/N

Stop

A

A

A

N1

P

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

S or Sr

1

X

0

X

Bit 1

Bit 2

HID

Bit 0

R=1

2.10.5   I3C Basic Target Protocol

NOTE 1  When PMIC device reaches last byte within the region (either Host region or DIMM vendor region), it will

continue to return data but returned data will be 0x00 if there is no valid password for DIMM vendor region or
Vendor specific region. Once the address counter reaches R255, it will reset to address R00 and it will continue
to return the data. Only Host can perform STOP operation.

...

Data

Data

JPGNetworksLLC

The  PMIC  device  operate  on  a  standard  I3C  Basic  serial  interface.  Transactions  where  the  PMIC  device  is  the
targeted target device begin with the Host issuing a START condition followed by a 7-bit PMIC device address then
a read or write bit, RW. All data are transmitted with the most significant bit MSB first. During the address followed
by  R/W  bit  transmission,  the  PMIC  device  typically  replies  with  an  ACK  unless  there  are  exceptional  conditions
when it may passively assert a NACK. See Table 35. The “T” bit carries Parity information from the Host for each
byte.

The PMIC device host region registers that are write protected in write protect mode of operation, the PMIC does not
execute the operation internally.

Similarly, regardless of write protect mode or non write protect mode of operation, without the correct password, all
DIMM  vendor  and  vendor  specific  region  registers  are  write  protected  and  PMIC  does  not  execute  the  operation
internally.

The Packet Error Code (PEC) function is disabled by default when the PMIC device is put in I3C Basic mode. The
host may optionally enable this function through Table 142, “Register 0x34” [7] or DEVCTRL CCC. If enabled, the
PEC is appended at the end of all transactions. If PEC is enabled, the host must complete the burst length as indicated
in CMD field. In other words, the host must not interrupt the burst length pre-maturely for Write operation.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 50

2.10.5.1  Write Operation - Data Packet

Table 35 — Write Command Data Packet; PEC Disabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S or Sr

1

X

0

X

HID

Address [7:0]

Data

...

Stop

Bit 0

W=0

A/N/T
A1,2,3
T

T

T

Sr4 or P
NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit

Data

T

of Addr, bit [7]).

NOTE 2  The PMIC device NACKs if there is a parity error in a previous transaction when host performs consecutive

transactions with Repeat Start.

NOTE 3  The PMIC device does not check for parity error in subsequent bytes when it determines the 7-bit device select code
issued by the host does not match with its own device code. The PMIC device ignores the entire packet until STOP
or next Repeat Start operation.

NOTE 4  Repeat Start or Repeat Start with 7’h7E.

Bit 6

X

Bit 3

Bit 4

Bit 5

Table 36 — Write Command Data Packet; PEC Enabled

JPGNetworksLLC

Address [7:0]

Bit 2

Bit 1

Bit 0

W=0

W=0

0000

Data

Data

HID

...

X

0

CMD

Stop

A/N/T
A1,2,3
T

T

T

T

T

Start

Bit 7

S or Sr

1

Sr4 or P
NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit

PEC

T

of Addr, bit [7]).

NOTE 2  The PMIC device NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive

transactions with Repeat Start.

NOTE 3  The PMIC device does not check for parity or PEC error in subsequent bytes when it determines the 7-bit device

select code issued by the host does not match with its own device code. The PMIC device ignores the entire packet
until STOP or next Repeat Start operation.

NOTE 4  Repeat Start or Repeat Start with 7’h7E.

The host may optionally allow PMIC device to request IBI. For this case, the transactions to the PMIC device begin
with the I3C host issuing a START condition followed by 7’h7E and then write bit. If PMIC device has a pending IBI,
it transmits its 7-bit device select code followed by R=1. If PMIC device has no pending IBI, there is no action taken
by PMIC. The Table 37 and Table 38 shows the I3C Basic bus write command data packet with optional IBI header
for PEC disabled and PEC enabled case respectively. Note that in Table 38, PEC calculation does not include IBI
header byte (7’h7E followed by W=0).

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 51

2.10.5.1 Write Operation - Data Packet (cont’d)

Table 37 — Write Command Data Packet with IBI Header; No Pending IBI, PEC Disabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S

Sr

1

1

1

X

1

0

1

X

1

0

1

HID

Bit 0

W=0

W=0

Address [7:0]

Data

...

Data

A/N/T
A1,2

A2,3,4
T

T

T

T

Stop

Sr5 or P

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation

(Repeat Start)

NOTE 2  The PMIC device NACKs if there is a parity error in a previous transaction when host performs consecutive

transactions with Repeat Start.

NOTE 3  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK) and
See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st
bit of Addr, bit [7]).

NOTE 4  The PMIC device does not check for parity error in subsequent bytes when it determines the 7-bit device select

code issued by the host does not match with its own device code. The PMIC device ignores the entire packet until
STOP or next Repeat Start operation.

NOTE 5  Repeat Start or Repeat Start with 7’h7E.

JPGNetworksLLC

Address [7:0]

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

Bit 0

W=0

W=0

W=0

0000

HID

X

1

1

1

1

1

0

0

X

Bit 6

CMD

Table 38 — Write Command Data Packet with IBI Header; No Pending IBI, PEC Enabled

Start

Bit 7

S

Sr

1

1

A/N/T
A1,2

A2,3,4
T

T

T

T

T

T

Stop

Sr5 or P

Data

...

Data

PEC

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation

(Repeat Start)

NOTE 2  The PMIC device NACKs if there is a parity or PEC error in a previous transaction when host performs

consecutive transactions with Repeat Start.

NOTE 3  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK) and
See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st
bit of Addr, bit [7]).

NOTE 4  The PMIC device does not check for parity or PEC error in subsequent bytes when it determines the 7-bit device

select code issued by the host does not match with its own device code. The PMIC device ignores the entire
packet until STOP or next Repeat Start operation.

NOTE 5  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 52

2.10.5.2  Read Operation - Data Packet

The  PMIC  device  operate  on  a  standard  I3C  Basic  serial  interface.  Transactions  where  the  PMIC  device  is  the
targeted target device begin with the Host issuing a START condition followed by a 7-bit PMIC device address then
a read or write bit, RW. All data are transmitted with the most significant bit MSB first. During the address followed
by  R/W  bit  transmission,  the  PMIC  device  typically  replies  with  an  ACK  unless  there  are  exceptional  conditions
when it may passively assert a NACK. See Table 39. The “T” bit carries Parity information from the Host for each
byte prior to Repeat START. After Repeat START, “T” bit carries information from PMIC device to Host indicating
Continuous (‘1’) or Stop (‘0’) whether it is transmitting the last byte or not.

The Packet Error Code (PEC) function is disabled by default when the PMIC device is put in I3C Basic mode. The
host may optionally enable this function through Table 142, “Register 0x34” [7] or DEVCTRL CCC. If enabled, the
PEC is appended as shown in Table 39. If PEC is enabled, the host must complete the burst length as indicated in
CMD field. In other words, the host must not interrupt the burst length pre-maturely for Read operation

Table 39 — Read Command Data Packet; PEC Disabled

Start

Bit 7

S or Sr

Sr

1

1

Stop

A/N/T
A1,2,3
T

A/N4,5
T=1

T=1

Bit 6

0

0

X

X

X

X

...

R=1

HID

HID

Data

W=0

Bit 0

Bit 1

Bit 2

Bit 3

Bit 4

Bit 5

Address [7:0]

JPGNetworksLLC

Data

Sr8 or P
NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit of

T=16,7

NOTE 2  The PMIC device NACKs if there is a parity error in a previous transaction when host performs consecutive

Addr, bit [7]).

transactions with Repeat Start.

NOTE 3  The PMIC device does not check for parity error in subsequent bytes when it determines the 7-bit device select code
issued by the host does not match with its own device code. The PMIC device ignores the entire packet until STOP
or next Repeat Start operation.

NOTE 4  If target device NACKs during Repeat Start for any reason, the host my re-try Repeat Start again. The host can do the
Repeat Start as many times it may desire. If target device NACKs due to parity error in previous bytes, it will always
NACK regardless of how many times the Host tries Repeat Start. If there were no parity errors, the PMIC may
eventually ACK.

NOTE 5  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK).

NOTE 6  See Figure 21 to see how Host ends target device operation.

NOTE 7  When PMIC device reaches last byte within the region (either Host region or DIMM vendor region), it will continue
to return data but returned data will be 0x00 if there is no valid password for DIMM vendor region or Vendor specific
region. Once the address counter reaches R255, it will reset to address R00 and it will continue to return the data.
Only Host can perform STOP operation.

NOTE 8  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 53

2.10.5.2 Read Operation - Data Packet (cont’d)

Table 40 — Read Command Data Packet; PEC Enabled

Start

S or Sr

Sr

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

1

1

X

CMD

X

0

0

X

Address [7:0]

R=1

PEC

X

Data

...

Data

Bit 2

HID

Bit 1

Bit 0

W=0

0000

HID

R=1

Stop

A/N/T
A1,2,3
T

T

T

A/N4,5
T=1

T=1

T=1

T=06

Sr7 or P

[7]).

with Repeat Start.

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit of Addr, bit

NOTE 2  The PMIC device NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions

NOTE 3  The PMIC device does not check for parity or PEC error in subsequent bytes when it determines the 7-bit device select code

issued by the host does not match with its own device code. The PMIC device ignores the entire packet until STOP or next Repeat
Start operation.

NOTE 4  If target device NACKs during Repeat Start for any reason, the host my re-try Repeat Start again. The host can do the Repeat Start

as many times it may desire. If target device NACKs due to PEC error or parity error in previous bytes, it will always NACK
regardless of how many times the Host tries Repeat Start. If there were no parity or PEC errors, the PMIC may eventually ACK.
The PEC calculation by the target device only includes device select code of the ACK response of the Repeat start operation. In
other words, if there are more than one Repeat Start operation, the target device includes device select of only the last Repeat Start
from the Host when it ACKs in PEC calculation and all other NACK responses of the device select code of the Repeat Start are
not included in PEC calculation.

NOTE 5  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK).

NOTE 6  See Figure 22 to see how target device ends the operation followed by Host STOP operation.

PEC

JPGNetworksLLC

NOTE 7  Repeat Start or Repeat Start with 7’h7E.

The host may optionally allow PMIC device to request IBI. For this case, the transactions to the PMIC device begin
with  the  I3C  Basic  host  issuing  a  START  condition  followed  by  7’h7E  and  then  write  bit.  If  PMIC  device  has  a
pending IBI, it transmits its 7-bit device select code followed by R=1. If PMIC device has no pending IBI, there is no
action taken by PMIC. The Table 41 and Table 42 shows the I3C Basic bus read command data packet with optional
IBI  header  for  PEC  disabled  and  PEC  enabled  case  respectively.  Note  that  in  Table 42,  PEC  calculation  does  not
include IBI header byte (7’h7E followed by W=0).

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 54

2.10.5.2 Read Operation - Data Packet (cont’d)

Table 41 — Read Command Data Packet with IBI Header; No Pending IBI, PEC Disabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S

Sr

Sr

1

1

1

1

X

X

1

0

0

0

1

HID

HID

1

1

X

Address [7:0]

X

Data

...

Stop

A/N/T

Bit 0
W=0 A1,2

W=0 A2,3,4
T

R=1 A/N5,6
T=1

T=1

Sr9 or P
NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit

T=17,8

Data

of Addr, bit [7]).

transactions with Repeat Start.

NOTE 2  The PMIC device NACKs if there is a parity error in a previous transaction when host performs consecutive

NOTE 3  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK) and

See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit
of Addr, bit [7]).

NOTE 4  The PMIC device does not check for parity error in subsequent bytes when it determines the 7-bit device select

code issued by the host does not match with its own device code. The PMIC device ignores the entire packet until
STOP or next Repeat Start operation.

NOTE 5  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK).

NOTE 6  If target device NACKs during Repeat Start for any reason, the host my re-try Repeat Start again. The host can do
the Repeat Start as many times it may desire. If target device NACKs due to parity error in previous bytes, it will
always NACK regardless of how many times the Host tries Repeat Start.

JPGNetworksLLC

continue to return data but returned data will be 0x00 if there is no valid password for DIMM vendor region or
Vendor specific region. Once the address counter reaches R255, it will reset to address R00 and it will continue to
return the data. Only Host can perform STOP operation.

NOTE 8  When PMIC device reaches last byte within the region (either Host region or DIMM vendor region), it will

NOTE 7  See Figure 21 to see how Host ends target device operation.

NOTE 9  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 55

2.10.5.2 Read Operation - Data Packet (cont’d)

Table 42 — Read Command Data Packet with IBI Header; No Pending IBI, PEC Enabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S

Sr

Sr

1

1

1

1

X

CMD

X

1

0

0

1

1

X

Address [7:0]

R=1

PEC

X

Data

...

Bit 0

W=0

W=0

0

1

HID

0000

HID

R=1

Stop

A/N/T
A1,2

A2,3,4
T

T

T

A/N5,6
T=1

T=1

T=1

with Repeat Start.

Sr8 or P
NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit of Addr, bit [7]).

T=07

NOTE 2  The PMIC device NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions

PEC

Data

JPGNetworksLLC

NOTE 3  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK) and See Figure 18 to see

how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit of Addr, bit [7]).

NOTE 4  The PMIC device does not check for parity or PEC error in subsequent bytes when it determines the 7-bit device select code issued

by the host does not match with its own device code. The PMIC device ignores the entire packet until STOP or next Repeat Start
operation.

NOTE 5  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK).

NOTE 6  If target device NACKs during Repeat Start for any reason, the host my re-try Repeat Start again. The host can do the Repeat Start

as many times it may desire. If target device NACKs due to PEC error or parity error in previous bytes, it will always NACK
regardless of how many times the Host tries Repeat Start. If there were no parity or PEC errors, the PMIC may eventually ACK. The
PEC calculation by the target device only includes device select code of the ACK response of the Repeat start operation. In other
words, if there are more than one Repeat Start operation, the target device includes device select of only the last Repeat Start from
the Host when it ACKs in PEC calculation and all other NACK responses of the device select code of the Repeat Start are not
included in PEC calculation.

NOTE 7  See Figure 22 to see how target device ends the operation followed by Host STOP operation.

NOTE 8  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 56

2.10.5.3  Default Read Address Pointer Mode

This mode works the same exact way as explained in clause 2.10.4.3. Table 43 and Table 44 show the read command
data packet for PEC function disabled and enabled respectively. When PEC function is enabled, Table 147, “Register
0x3A” [3:2] sets the number of bytes that PMIC device sends out followed by the PEC calculation. If PEC is enabled,
the host must complete the burst length as indicated in Table 147, “Register 0x3A” [3:2] register. In other words, the
host must not interrupt the burst length pre-maturely for default address pointer read operation.

Table 43 — Read Command Data Packet with Read Address Pointer Mode; PEC Disabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

S or Sr

1

X

0

X

Bit 2

HID

Bit 1

Bit 0

R=1

Data

...

Stop

A/N/T
A1
T=1

T=1

Sr4 or P
NOTE 1  The PMIC device NACKs if there is a parity error in a previous transaction when host performs consecutive transactions

T=12,3

Data

with Repeat Start.

NOTE 2  See Figure 21 to see how Host ends target device operation.

NOTE 3  When PMIC device reaches last byte within the region (either Host region or DIMM vendor region), it will continue to

return data but returned data will be 0x00 if there is no valid password for DIMM vendor region or Vendor specific region.
Once the address counter reaches R255, it will reset to address R00 and it will continue to return the data. Only Host can
perform STOP operation.

NOTE 4  Repeat Start or Repeat Start with 7’h7E.

JPGNetworksLLC

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

Data

Data

HID

R=1

...

X

0

Bit 0

PEC

Stop

A/N/T
A1
T=1

T=1

T=1

T=02

Sr3 or P

Table 44 — Read Command Data Packet with Read Address Pointer Mode; PEC Enabled

Start

Bit 7

S or Sr

1

Bit 6

X

NOTE 1  The PMIC device NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive

transactions with Repeat Start.

NOTE 2  See Figure 22 to see how target device ends the operation followed by STOP operation

NOTE 3  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 57

2.10.5.3 Default Read Address Pointer Mode (cont’d)

Table 45 — Read Command Data Packet with Read Address Pointer and IBI Header;
No Pending IBI; PEC Disabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S

Sr

1

1

1

X

1

0

1

X

0

1

HID

1

Data

...

Data

Stop

Bit 0

W=0

R=1

A/N/T
A1,2

A/N2,3
T=1

T=1

T=14,5

Sr6 or P

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (Repeat

Start).

NOTE 2  The PMIC device NACKs if there is a parity error in a previous transaction when host performs consecutive

transactions with Repeat Start.

NOTE 3  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK).

NOTE 4  See Figure 21 to see how Host ends target device operation.

NOTE 5  When PMIC device reaches last byte within the region (either Host region or DIMM vendor region), it will continue to

return data but returned data will be 0x00 if there is no valid password for DIMM vendor region or Vendor specific
region. Once the address counter reaches R255, it will reset to address R00 and it will continue to return the data. Only
Host can perform STOP operation.

NOTE 6  Repeat Start or Repeat Start with 7’h7E.

JPGNetworksLLC

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

Bit 0

W=0

Data

HID

R=1

...

X

1

1

1

1

0

0

Data

PEC

Stop

A/N/T
A1,2

A/N2,3
T=1

T=1

T=1

T=04

Sr5 or P

Table 46 — Read Command Data Packet with Read Address Pointer and IBI Header;
No Pending IBI; PEC Enabled

Start

Bit 7

S

Sr

1

1

Bit 6

1

X

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (Repeat

Start).

NOTE 2  The PMIC device NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive

transactions with Repeat Start.

NOTE 3  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK).

NOTE 4  See Figure 22 to see how target device ends the operation followed by STOP operation

NOTE 5  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 58

2.10.5.3 Default Read Address Pointer Mode (cont’d)

tDOUT

tDOFFT

HSCL

VIHmin

VILmax

HSDA

ACK

Bit 7

Bit 6

Controller Drives SDA Bus
– Open Drain

Controller Drives SDA Bus – Push Pull

Target Drives SDA Bus
– Open Drain

JPGNetworksLLC

Both Controller & Slave Drives SDA Bus
Overlap – Open Drain

Figure 18 — Target Open Drain to Controller Push Pull Hand Off Operation

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 59

2.10.5.3 Default Read Address Pointer Mode (cont’d)

tDOUT

tDOFFC

HSCL

VIHmin

VILmax

HSDA

ACK

Bit 7

Bit 6

Target  Drives SDA Bus
– Open Drain

Target Drives SDA Bus – Push Pull

Controller Drives SDA Bus
– Open Drain

JPGNetworksLLC

Both Controller & Target Drives SDA Bus
Overlap – Open Drain

Figure 19 — Controller Open Drain (ACK) to Target Push Pull Hand Off Operation

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 60

2.10.5.3 Default Read Address Pointer Mode (cont’d)

tDOFFC

tDOFFT

HSCL

VIHmin

VILmax

HSDA

Bit 1

Bit 0; W=0

ACK

Bit 7

Bit 6

Controller Drives SDA Bus
– Push Pull

Controller Drives SDA Bus – Push Pull

Target drives SDA Bus
Open Drain

Both Controller & Target
Drives SDA Bus

JPGNetworksLLC

Both Controller & Target Drives SDA Bus
Overlap – Open Drain

tHIGH_OD

tLOW_OD

tDOFFC

HSCL

VIHmin

VILmax

HSDA

Bit 1

Bit 0; R=1

ACK

Bit 7

Bit 6

Controller Drives SDA Bus
– Push Pull

Target drives SDA Bus
Push Pull

Both Controller & Target
Drives SDA Bus

Figure 20 — Controller Push Pull to Target Open Drain Hand Off Operation

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

2.10.5.3 Default Read Address Pointer Mode (cont’d)

JEDEC Standard No. 301-1A.02
Page 61

tDOUT

tDOFFT

Repeat
Start

STOP

HSCL

VIHmin

VILmax

HSDA

Target Drives SDA Bus

Controller Drives SDA Bus

tCL_r_Dat_f

T = 1

JPGNetworksLLC

Controller Pullup Resistor
Keeps SDA Bus High

Figure 21 — T=1; Controller Ends Read with Repeated START and STOP Waveform

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 62

2.10.5.3 Default Read Address Pointer Mode (cont’d)

tDOUT

tDOFFT

STOP

HSCL
VIHmin

VILmax

HSDA

T = 0

Target Drives SDA Bus

Controller Drives SDA Bus

JPGNetworksLLC

Both Controller & Target Drives SDA Bus
Overlap

Figure 22 — T=0; Target Ends Read; Controller Generates STOP

2.10.6   In Band Interrupt (IBI)

In I2C mode, in band interrupt function is not supported. Only I3C Basic mode supports in band interrupt function.

2.10.6.1  Enabling and Disabling In Band Interrupt Function

By default, IBI function is disabled. The PMIC device enables the IBI when it registers ENEC CCC. Once enabled,
the PMIC device sends an IBI when an event occurs.

•  When Table 142, “Register 0x34” [6] = ‘1’, the device sends the IBI at next available opportunity when any of
the  register  bits  in  Table 98,  “Register  0x08”  [7:0],  Table 99,  “Register  0x09”  [7:0],  Table 100,  “Register
0x0A” [7:2], Table 101, “Register 0x0B” [7:0], and Table 141, “Register 0x33” [4:2] is set to ‘1’. The device
also sets Table 100, “Register 0x0A” [1] to ‘1’ and updates Pending Interrupt Bits [3:0] = ‘0001’ for
GETSTATUS CCC.

•  When Table 142, “Register 0x34” [6] = ‘0’, the device does not send the IBI regardless of the register bits in
Table 98, “Register 0x08” [7:0], Table 99, “Register 0x09” [7:0], Table 100, “Register 0x0A” [7:2], Table 101,
“Register  0x0B”  [7:0],  and  Table 141,  “Register  0x33”  [4:2].  However,  the  device  set  Table 100,  “Register
0x0A” [1] to ‘1’ and updates Pending Interrupt Bits [3:0] = ‘0001’ for GETSTATUS CCC.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 63

2.10.6.2  Mechanics of Interrupt Generation

Event  interrupts  may  be  generated  by  the  local  device  if  IBI  is  enabled.  When  there  is  a  pending  interrupt  (i.e.,
Table 100, “Register 0x0A” [1] =  ‘1’)  and  if  IBI is  enabled (i.e.,  Table 142, “Register  0x34” [6]  = ‘1’) the  PMIC
device  requests  an  interrupt  after  detecting  START  condition  by  transmitting  its  7-bit  binary  address  (LID  bits
followed by HID bits) followed by R/W = ‘1’ on the SDA bus serially (synchronized by SCL falling transitions).

If PMIC device detects no START condition but if the I3C bus (SDA and SCL) has been inactive (no edges seen) for
tAVAL  period,  then  PMIC  device  may  assert  SDA  low  by  tIBI_ISSUE  time  to  request  an  interrupt. When  the  PMIC
device requests an interrupt, the Host toggles the SCL. The PMIC device transmits its 7-bit binary address (LID bits
followed by HID bits) followed by R/W bit = ‘1’ to the Host.

When the PMIC device requests an interrupt, the host may take one of the two actions below.

•  The Host sends ACK on 9th bit to accept the interrupt request. At this point, if the PMIC device confirms that
it has won the arbitration, the PMIC device transmits the IBI payload as shown in Table 47 and Table 48 for
PEC disabled and PEC enabled configuration respectively. See Figure . Figure  just shows only first two data
bits of the MDB byte to illustrate the timing. The interrupt payload contains MDB followed by
Table 98,  “Register  0x08”,  Table 99,  “Register  0x09”,  Table 100,  “Register  0x0A”,  Table 101,  “Register
0x0B” and Table 141, “Register 0x33” bytes. The host then issues the STOP command. Note the timing
waveform in Figure . The host then accepts the IBI payload if it sends an ACK on 9th bit to accept the interrupt
request. The host can interrupt the IBI payload at T bit. If host stops the IBI payload at T bit in the middle of
payload, the PMIC retains the IBI status flag (Table 100, “Register 0x0A” [1]) and Pending Interrupt Bits [3:0]
internally and waits for the next opportunity to request an interrupt. If the PMIC device successfully transmits
the entire IBI payload, it then clears IBI status flag (Table 100, “Register 0x0A” [1] = ‘0’) and Pending
Interrupt Bits [3:0] = ‘0000’ on its own and does not request for an IBI again unless there is another different
event occurs; for another same event, the device does not request for an IBI.

JPGNetworksLLC

•  The Host sends NACK on the 9th bit as shown in  Figure  followed by a STOP command. In this case, the
PMIC device does not transmit the IBI payload and waits for the next opportunity to request an interrupt. At
this point, though Host sent an NACK, it does have a knowledge of which PMIC device sent the IBI request.
The PMIC device retains the IBI status flag (Table 100, “Register 0x0A” [1] = ‘1’) and Pending Interrupt Bits
[3:0] = ‘0001’

Table 47 — Target Device IBI Payload Packet; PEC is Disabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

Bit 0

S

1

X

0

X

HID

R=1

MDB = 0x00

R08 [7:0]

R09 [7:0]

R0A [7:0]

R0B [7:0]

R33 [7:0]

Stop

A/T
A1
T=1

T=1

T=1

T=1

T=1

T=02

P

NOTE 1  See Figure 19 to see how the transition occurs from Host Open Drain (ACK) to Target Push Pull Operation (1st bit of

MDB Byte bit [7]).

NOTE 2  See Figure 22 to see how target device ends the operation followed by Host STOP operation.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 64

2.10.6.2 Mechanics of Interrupt Generation (cont’d)

Table 48 — Target Device IBI Payload Packet; PEC is Enabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

Bit 0

S

1

X

0

X

HID

R=1

MDB 0x00

R08 [7:0]

R09 [7:0]

R0A [7:0]

R0B [7:0]

R33 [7:0]

PEC

Stop

A/T
A1
T=1

T=1

T=1

T=1

T=1

T=1

T=02

P

NOTE 1  See Figure 19 to see how the transition occurs from Host Open Drain (ACK) to Target Push Pull Operation (1st bit of

MDB Byte bit [7]).

NOTE 2  See Figure 22 to see how target device ends the operation followed by Host STOP operation.

Idle

R/W=1

Interrupt

PMIC HID Code

PMIC LID Address

JPGNetworksLLC

HID

HID

HID

Ack

D0

D1

X

X

1

0

1

D2

LSDA

LSCL

Figure 23 — PMIC Requests Interrupt, Host Ack Followed by PMIC Device IBI Payload

PMIC LID Address

PMIC HID Code

R/W=1

Idle

Interrupt

NACK

Stop

1

X

0

X

HID

HID

HID

1

LSDA

LSCL

Figure 24 — PMIC Requests Interrupt; Host NACK Followed by STOP

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 65

2.10.6.3  Interrupt Arbitration

As there are multiple devices I3C Basic bus, multiple device may request an interrupt when the Host I3C Basic bus is
inactive for tAVAL period. Arbitration process is required.

For DDR5 DIMM application environment, there could be up to total of 13 difference devices including the PMIC on
I3C bus.

On a typical DDR5 DIMM application environment, all devices have the same 3-bit HID code. Hence the arbitration
is always won  by  the  lowest 4-bit LID code. For  example, if  one  target  device  has LID code of  ‘0010’  and  other
device (PMIC) has a LID code of ‘1001’, through the arbitration process, the target device LID code of ‘0010’ wins.
The  PMIC  device  with  a  LID  code  of  ‘1001’  must  release  the  bus  and  wait  for  next  opportunity  to  request  an
interrupt.  Table 49  shows  the  arbitration  priority  based  on  the  LID  code  for  all  devices. The  Green  color  cells  in
Table 49 are the likely devices that will be on a standard DDR5 RDIMM or DDR5 LRDIMM. The Olive color cells
in Table 49 do not apply.

Table 49 — Interrupt Arbitration - Among All Devices

2

1

111

111

111

N/A

TS0

N/A

N/A

RFU

RFU

RFU

0011

0010

0001

0000

Device

LID Code

Arbitration
Priority

HID Code
= ‘111’

JPGNetworksLLC

SPD Hub

PMIC0

PMIC2

PMIC1

RCD

1001

1010

0100

0101

1000

1011

1100

0110

RFU

RFU

0111

N/A

TS1

N/A

111

111

111

111

111

111

111

111

10

11

8

9

3

4

5

6

7

RFU

RFU

N/A

1101

1110

1111

111

111

N/A

12

13

N/A

In an uncommon but possible scenario would be that at the exact same time as when the Hub or local target devices
(i.e.,  PMIC)  are  requesting  an  interrupt,  the  host  is  starting  an  operation  to  the  Hub  or  local  target  devices  (i.e.,
PMIC). When this happens, Host also gets involved in the arbitration process along with the Hub or the local target
devices (PMIC). During the arbitration phase, there will be always only one winning device and it could be either
Hub or the local target device (i.e., PMIC) or the Host.

If the host wins during the arbitration phase, it continues with normal operation. The losing Hub or local target device
(i.e., PMIC) waits for next opportunity to send an interrupt.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 66

2.10.6.3 Interrupt Arbitration (cont’d)

If the host loses during the arbitration phase, it must let go of the bus. When Host loses during the arbitration, the host
must let the Hub or local target device (i.e., PMIC) finish sending their 4-bit LID code followed by 3-bit HID code
followed by R/W = ‘1’. At this point, during the 9th bit, the host has two options to take the action as noted below:

•  Host sends an ACK to accept the interrupt and hence accepts the IBI payload from the winning Hub or local

target device (i.e., PMIC). After the IBI payload, the host issues STOP operation.

•  Host sends an NACK followed by STOP operation.

In a rare but still possible scenario would be that at the exact same time as when the PMIC is requesting an interrupt,
the host is starting an operation to the same PMIC. When this happens, neither Host or nor the PMIC knows it is a
winner until the 8th bit and Host always wins. This is because, the PMIC sends R=1 (8th bit) during the interrupt. The
host sets W=0 (8th bit) during the operation. As a result, the host wins and the PMIC must let go of the bus and wait
for the next opportunity to send an interrupt.

2.10.6.4  Clearing Device Status and IBI Status Registers

In an extreme rare but still possible scenario would be that at the same exact time as when PMIC device is requesting
an interrupt, the host is requesting a read operation with the default read address pointer mode to the PMIC device.
When this happens, there is no winning device. This is the only time there is no winning device. This is because, the
PMIC  device  sends  R=1  (8th  bit)  during  the  interrupt  and  Host  also  sends  R=1  for  read  request  with  default  read
address pointer mode. As a result, there is no winner because Host is waiting for PMIC to ACK and PMIC is waiting
for  Host  to ACK.  In  this  case,  neither  Host  nor  PMIC  will ACK.  Since  there  is  no ACK  (i.e.,  NACK)  by  either
device, the Host must time out and repeat the read request with Repeat Start. When Host repeats the read request with
Repeat Start, the PMIC does not send an interrupt because of Repeat Start.

JPGNetworksLLC

The PMIC device provides the IBI status in Table 100, “Register 0x0A” [1] by setting it to ‘1’. The PMIC device
clears  the  IBI  status  register  Table 100,  “Register  0x0A”  [1]  to  ‘0’  automatically  when  it  sends  a  complete  IBI
(including payload and without interruption) and it also clears Pending Interrupt Bits [3:0] to ‘0000’. Once IBI status
register is cleared, the PMIC does not request for an IBI again unless an another event occurs.

The  PMIC  device  provides  the  device  status  in  Table 98,  “Register  0x08”  [7:0],  Table 99,  “Register  0x09”  [7:0],
Table 100, “Register 0x0A” [7:2], Table 101, “Register 0x0B” [7:0] and Table 141, “Register 0x33” [4:2] registers.
The  status  information  in  Table 98,  “Register  0x08”  [7:0],  Table 99,  “Register  0x09”  [7:0],  Table 100,  “Register
0x0A” [7:2], Table 101, “Register 0x0B” [7:0] and Table 141, “Register 0x33” [4:2] registers are latched and remains
set even after the PMIC device sends IBI payload and clears the IBI status register Table 100, “Register 0x0A” [1] to
‘0’. The host must explicitly clear the status register through Clear command by writing ‘1’ for appropriate status or
by issuing a Global clear command.

After Host issues clear command, if the condition is no longer present, the PMIC device clears the appropriate status
register, clears the IBI status register to ‘0’ and Pending Interrupt Bits [3:0] to ‘0000’ even if the PMIC device has not
sent the IBI. After Host issues clear command, if the condition is still present, the device will again set the appropriate
status  register,  sets  the  IBI  status  register  to  ‘1’  and  Pending  Interrupt  Bits  [3:0]  to  ‘0001’  even  if  the  device  has
already sent the IBI and entire IBI payload.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 67

2.10.7   Packet Error Check (PEC) Function

In I2C mode, packet error checking is not supported. Only I3C Basic mode supports packet error checking.

The PMIC device implement an 8-bit Packet Error Code (PEC) which is appended at the end of all transactions if
PECs is enabled through DEVCTRL CCC or by directly writing ‘1’ to Table 142, “Register 0x34” [7]. The PEC is a
CRC-8 value calculated on all the messages bytes except for START, STOP, REPEATED START conditions or
T-bits, ACK and NACK and IBI header (7’h7E followed W=0) bits.

The polynomial for CRC-8 calculations is:

•  C(X) = X8 + X2 + X1 + 1

The seed value for PEC function is all zero.

When Host calculates PEC for PMIC device, it includes LID and HID bits followed by R/W bit.

2.10.8   Parity Error Check Function

In I2C mode, parity error checking is not supported except for supported CCCs. Only I3C Basic mode supports parity
error checking.

By  default,  when  PMIC  device  is  put  in  I3C  Basic  mode,  parity  function  is  automatically  enabled. The  host  can
disable the function after it is enabled. Host can also disable the parity function with DEVCTRL CCC or by directly
writing ‘1’ to Table 142, “Register 0x34” [5]. When parity function is disabled, the PMIC device simply ignores the
“T” bit information from the Host. The host may actually choose to compute the parity and send that information
during “T” bit or simply drive static low or high in “T” bit.

The PMIC device implements ODD parity. If an odd number of bits in the byte are ‘1’, the parity bit value is ‘0’. If
even number of bits in the byte are ‘1’, the parity bit value is ‘1’. The host computes the parity and sends during “T”
bit.

JPGNetworksLLC

There are two types of error checking done by the PMIC device. Parity error checking and Packet Error checking. By
default, the parity error checking is always enabled and packet error checking is disabled. The host may enable the
packet error checking at any time. The parity error is checked for each byte in a packet except for the device select
code byte from the host. The host sends parity error information in “T” bit.

I3C Basic defines TE0, TE1, TE2, TE3, TE4, TE5, TE6 error detection for target devices. Only TE1 and TE2 error
detection is supported by the PMIC for parity checking. All other errors are not supported and not applicable.

2.10.9   Packet Error Check and Parity Error Handling

2.10.9.1  Write Command Data Packet Error Handling - PEC Disabled

The PMIC device checks for the parity error for each byte in a packet that it receives from the host except for the
device select code byte that it receives from the host as shown in Table 50.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 68

2.10.9.1 Write Command Data Packet Error Handling - PEC Disabled (cont’d)

Table 50 — Write Command Data Packet; PEC Disabled

Start

S or Sr

Bit 7

1

Bit 6

X

Bit 5

Bit 4

Bit 3

0

X

Address [7:0]

Data

...

Bit 2

HID

Bit 1

Bit 0

W=0

Stop

A/N/T
A1,2,3
T

T

T

Sr4 or P
NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit of Addr, bit [7]).

Data

T

NOTE 2  The PMIC NACKs if there is a parity error in a previous transaction when host performs consecutive transactions with Repeat

Start.

NOTE 3  The PMIC does not check for parity error in subsequent bytes when it determines the 7-bit device select code issues by the host

does not match with its own device code. The PMIC ignores the entire packet until STOP or next Repeat Start operation.

Write command - if parity error:

NOTE 4  Repeat Start or Repeat Start with 7’h7E.

Write command - if no parity error:

•  The PMIC device executes the command.

JPGNetworksLLC

•  The PMIC device discards the byte in the packet that had a parity error.
•  The PMIC device discards all subsequent bytes in that packet until the STOP operation. The PMIC device may

or may not check parity for all sub-sequent bytes in that packet.

•  Note that as the packet contains more than one byte, if first byte had no parity error but the second byte had a

parity error, the PMIC device may or may not execute the first byte operation but second byte and all
subsequent bytes operations are discarded.

•    The  PMIC  device  sets  the  Table 100,  “Register  0x0A”  [2:1]  to  ‘11’;  P_Err  in  GETSTATUS  CCC  to  ‘1’;
updates Pending Interrupt Bits [3:0] in GETSTATUS CCC to ‘0001’; asserts GSI_n pin if enabled and waits
for the next opportunity to send an in band interrupt if IBI is enabled.

2.10.9.2  Read Command Data Packet Error Handling - PEC Disabled

The  PMIC  device  checks  for  parity  error  for  each  byte  in  a  packet  except  for  the  device  select  code  byte  that  it
receives from the host prior to Repeat Start as shown in Table 51.

The PMIC device does not compute the parity when it sends the data to the Host. The does not check for parity error
for the bytes shown in Table 51. The device sends Continuous (‘1’) or Stop (‘0’) information during “T” bit when
PMIC device is sending the read data.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 69

2.10.9.2 Read Command Data Packet Error Handling - PEC Disabled (cont’d)

Table 51 — Read Command Data Packet; PEC Disabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

S or Sr

Sr

1

1

X

X

0

0

X

Address [7:0]

X

Data

...

Bit 2

HID

HID

Bit 1

Bit 0

W=0

R=1

Stop

A/N/T
A1,2,3
T
A/N4,5
T=1

T=1

Sr8 or P
NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit of Addr, bit [7]).
NOTE 2  The PMIC NACKs if there is a parity error in a previous transaction when host performs consecutive transactions with Repeat

T=16,7

Data

Start.

Read Command - If parity error:

Read Command - If no parity error:

•  The PMIC sends ACK back to the host when Host perform Start Repeat operation.
•  The PMIC device executes the command and sends the data as shown in Table 51.

NOTE 3  The PMIC does not check for parity error in subsequent bytes when it determines the 7-bit device select code issues by the host

does not match with its own device code. The PMIC ignores the entire packet until STOP or next Repeat Start operation.
NOTE 4  If target device NACKs during Repeat Start for any reason, the host my re-try Repeat Start again. The host can do the Repeat Start
as many times it may desire. If target device NACKs due to parity error in previous bytes, it will always NACK regardless of how
many times the Host tries Repeat Start. If there were no parity errors, the PMIC may eventually ACK.

NOTE 5  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK).
NOTE 6  See Figure 21 to see how Host ends target device operation.
NOTE 7  When PMIC device reaches last byte within the region (either Host region or DIMM vendor region), it will continue to return data
but returned data will be 0x00 if there is no valid password for DIMM vendor region or Vendor specific region. Once the address
counter reaches R255, it will reset to address R00 and it will continue to return the data. Only Host can perform STOP operation.

NOTE 8  Repeat Start or Repeat Start with 7’h7E.

JPGNetworksLLC

•  The PMIC device discards the byte in the packet that had a parity error.
•  The PMIC device sends NACK back to the host when Host performs a Start Repeat operation. This is shown in
the RED colored cell in Table 51. The NACK represents either a parity error in one of the two bytes or that
PMIC  is  not  able  to  start  the  read  operation. The  host  may  re-try  Repeat  Start  again. The  host  may  do  the
Repeat Start as many times as it may desire. If the PMIC target device NACKs due to parity error in a previous
byte from the host, it will always NACK regardless of how many times Host tries Repeat Start.

•  The PMIC does not send the data shown in Table 51 and instead expects Host to perform STOP operation.
•  The PMIC device sets Table 100, “Register 0x0A” [2:1] to ‘11’; P_Err in GETSTATUS CCC to ‘1’; updates
Pending Interrupt Bits [3:0] in GETSTATUS CCC to ‘0001’; asserts GSI_n pin if enabled and waits for the
next opportunity to send an in band interrupt if IBI is enabled.

2.10.9.3  Write Command Data Packet Error Handling - PEC Is Enabled

The PMIC device checks for the parity error for each byte in a packet that it receives from the host except for the
device select code byte that it receives from the host as shown in Table 52. Further, the PMIC device checks for the
packet error for the entire packet (from Start condition until last byte of Data) that it receives from the host as shown
in Table 52.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 70

2.10.9.3 Write Command Data Packet Error Handling - PEC Is Enabled (cont’d)

Table 52 — Write Command Data Packet; PEC Enabled

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

S or Sr

1

X

0

X

Bit 2

HID

Bit 1

Bit 0

W=0

Address [7:0]

CMD

W=0

0

0

0

0

Data

...

Data

Stop

A/N/T
A1,2,3
T

T

T

T

T

Sr4 or P
NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit of Addr, bit

PEC

T

[7]).

NOTE 2  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

NOTE 3  The PMIC does not check for parity or PEC error in subsequent bytes when it determines the 7-bit device select code issues by
the host does not match with its own device code. The PMIC ignores the entire packet until STOP or next Repeat Start operation.

NOTE 4  Repeat Start or Repeat Start with 7’h7E.

JPGNetworksLLC

Write command - if no parity error:

•  The PMIC device waits for the entire packet. If no error in packet, the PMIC device executes the command. If
there is an error in the packet, the PMIC device discards the entire packet and does not execute the packet and
waits  for  STOP;  sets  the  Table 100,  “Register  0x0A”  [3,1]  to  ‘11’;  PEC_Err  in  GETSTATUS  CCC  to  ‘1’;
updates Pending Interrupt Bits [3:0] in GETSTATUS CCC to ‘0001’; asserts GSI_n pin if enabled and waits
for the next opportunity to send an in band interrupt if IBI is enabled.

Write command - if parity error:

•  The PMIC device discards that byte and the entire packet until STOP operation.
•    The  PMIC  device  sets  the  Table 100,  “Register  0x0A”  [2:1]  to  ‘11’;  P_Err  in  GETSTATUS  CCC  to  ‘1’;
updates Pending Interrupt Bits [3:0] in GETSTATUS CCC to ‘0001’; asserts GSI_n pin if enabled and waits
for the next opportunity to send an in band interrupt if IBI is enabled.

•  The PMIC device may or may not check the error for the packet. If the PMIC device checks for the packet
error, likely it will detect an error in the packet and the device may also set Table 100, “Register 0x0A” [3] and
PEC_Err in GETSTATUS CCC as well.

2.10.9.4  Read Command Data Packet Error Handling - PEC Is Enabled

The  PMIC  device  checks  for  parity  error  for  each  byte  in  a  packet  except  for  the  device  select  code  byte  that  it
receives from the host prior to Repeat Start as shown in Table 53.

The PMIC device does not compute the parity when it sends the data to the Host. The does not check for parity error
for the bytes shown in Table 53. The device sends Continuous (‘1’) or Stop (‘0’) information during “T” bit when
PMIC device is sending the read data.

The PMIC device checks for the PEC error in a packet that it receives from Host from Start condition to Repeat Start
(from first device select code followed by the address offset and CMD byte).

The PMIC device computes the packet error code for the entire packet starting with Repeat Start (device select code
and the data PMIC device transmits back to Host).

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

2.10.9.4 Read Command Data Packet Error Handling - PEC Is Enabled (cont’d)

Table 53 — Read Command Data Packet; PEC Enabled

JEDEC Standard No. 301-1A.02
Page 71

Start

S or Sr

Sr

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

1

1

X

CMD

X

0

0

X

Address [7:0]

R=1

0

PEC

X

Data

...

Data

Bit 2

HID

Bit 1

Bit 0

W=0

0

0

0

HID

R=1

Stop

A/N/T
A1,2,3
T

T

T
A/N4,5
T=1

T=1

T=1
T=06

Repeat Start.

Sr7 or P
NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation (1st bit of Addr, bit [7]).
NOTE 2  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

PEC

NOTE 3  The PMIC does not check for parity or PEC error in subsequent bytes when it determines the 7-bit device select code issues by the

host does not match with its own device code. The PMIC ignores the entire packet until STOP or next Repeat Start operation.

NOTE 4  If target device NACKs during Repeat Start for any reason, the host my re-try Repeat Start again. The host can do the Repeat Start

as many times it may desire. If target device NACKs due to PEC error or parity error in previous bytes, it will always NACK
regardless of how many times the Host tries Repeat Start. If there were no parity or PEC errors, the PMIC may eventually ACK.
The PEC calculation by the target device only includes device select code of the ACK response of the Repeat start operation. In
other words, if there are more than one Repeat Start operation, the target device includes device select of only the last Repeat Start
from the Host when it ACKs in PEC calculation and all other NACK responses of the device select code of the Repeat Start are not
included in PEC calculation.

NOTE 5  See Figure 20 to see how the transition occurs from Host Push Pull Operation to Target Open Drain (ACK).
NOTE 6  See Figure 22 to see how target device ends the operation followed by Host STOP operation.
NOTE 7  Repeat Start or Repeat Start with 7’h7E.

JPGNetworksLLC

•  The PMIC device sends ACK back to the host when Host perform a Start Repeat operation.
•  The PMIC device executes the command and sends the data as shown in Table 53.
•  The PMIC computes PEC for the bytes (from Start condition to PEC byte prior to Repeat Start) shown in the

Read command - If no parity error and no PEC error

cells in Table 53.

Read command - if parity error or PEC error

•  The PMIC device discards the byte in the packet that had a parity error.
•  The PMIC device discards second byte in that packet if a parity error occurred in first byte. The PMIC device

may or may not check parity for the second byte in that packet.

•  The PMIC device discards the packet if there is a PEC error.
•  The PMIC sends NACK back to the host when Host perform Start Repeat operation. This is shown in the RED
colored cell in Table 53. The NACK represents either PEC error or a parity error in one of the three bytes or
that PMIC is not able to start the read operation. The host may re-try Repeat Start again. The host may do the
Repeat Start as many times it may desire. The PEC calculation by PMIC device only includes device select
code of the ACK responses of the Repeat Start operation. In other words, if there are more than one Repeat
Start operation, the PMIC device includes the device select of only the last Repeat Start from the Host when it
ACKs in PEC calculation and other NACK responses of the device select codes of the Repeat Start are not
included in PEC calculation. If the PMIC target device NACKs due to PEC error or a parity error in a
previous bytes from Host, it will always NACK regardless of how many times Host tries Repeat Start.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 72

2.10.9.4 Read Command Data Packet Error Handling - PEC Is Enabled (cont’d)

•  The PMIC device does not send any data shown in Table 53 and instead expects Host to perform STOP

operation.

•  The PMIC device sets Table 100, “Register 0x0A” [3:2] accordingly and Table 100, “Register 0x0A” [1] to

‘1’; P_Err, PEC_Err in GETSTATUS CCC to ‘1’ accordingly; updates Pending Interrupt Bits [3:0] in
GETSTATUS CCC to ‘0001’; asserts GSI_n pin if enabled and waits for the next opportunity to send an in
band interrupt if IBI is enabled.

2.10.10   CCC Packet Error Handling

Parity error and PEC error detected in a CCC packet are handled the same way as described for normal Read/Write
operations.

2.10.11   Error Reporting

All  error  conditions  detected  by  the  PMIC  devices  are  captured  in  Table 98,  “Register  0x08”  [7:0],  Table 99,
“Register 0x09” [7:0], Table 100, “Register 0x0A” [7:1] Table 101, “Register 0x0B” [7:0], and Table 141, “Register
0x33” [4:2] registers.

There are four different possible ways error information can be communicated to the host.

1.   The host makes the read request to Table 98, “Register 0x08”, Table 99, “Register 0x09”,

Table 100, “Register 0x0A”, Table 101, “Register 0x0B” and Table 141, “Register 0x33” registers.

2.   The host starts any transactions with Start condition followed by 7’h7E IBI header (Only applicable in I3C

Basic mode).

JPGNetworksLLC

The  I3C  Basic  spec  lists  large  number  of  Common  Command  Codes  (CCC).  Not  all  CCC  are  required  to  be
supported. The PMIC device NACKs for all unsupported CCC. The PMIC supports CCC as listed in Table 54.

The PMIC device requires STOP operation in between when switching from CCC operation to private device specific
Write or Read or Default Read Address Pointer mode operation and vice versa. In other words, any CCC operation
must be followed by STOP operation before continuing to any device specific Write or Read or Default Read Address
Pointer  mode  operation.  Similarly,  any  device  specific  Write  or  Read  or  Default  Read  Address  Pointer  mode
operation  must  be  followed  by  STOP  operation  before  continuing  to  any  CCC  operation.  The  PMIC  device  also
requires STOP operation between any direct CCC to broadcast CCC.

The PMIC device does allow Repeat Start operation between any direct CCC to any other direct CCC or between any
broadcast CCC to any other broadcast CCC or between any private Write or Read or Default Read Address Pointer
mode operation to any other private Write or Read or Default Read Address Pointer mode operation.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

3.   The PMIC device sends in band interrupt if enabled, when its SCL and SDA input has been idle for tAVAL

time (Only applicable in I3C Basic mode).
4.   The PMIC device asserts GSI_n pin if enabled.

2.10.12   I3C Basic Common Command Codes (CCC)

JEDEC Standard No. 301-1A.02
Page 73

2.10.12 I3C Basic Common Command Codes (CCC) (cont’d)

Table 54 — PMIC CCC Support Requirement

CCC

Mode

Code

Description

Note

ENEC

DISEC

Broadcast

Direct

Broadcast

Direct

0x00

0x80

0x01

0x81

RSTDAA

Broadcast

0x06

SETAASA

Broadcast

0x29

Enable Event Interrupts

Disable Event Interrupts

Put the device in I2C Mode (aka: Reset Dynamic
Address Assignment)

Put the device in I3C Basic Mode (aka: Set All
Addresses to Static Address)

GETSTATUS

Direct

0x90

Get Device Status

DEVCAP

SETHID

DEVCTRL

Direct

Broadcast

Broadcast

NOTE 1  JEDEC specific CCC.

2.10.12.1  ENEC CCC

1

1

1

Configure SPD Hub and all devices behind Hub

0x62

0x61

0xE0

Get Device Capability

PMIC updates 3-bit HID field

JPGNetworksLLC

Table 55 — ENEC CCC - Broadcast

The ENEC CCC is only supported after device is put in I3C Basic mode. In I2C mode, it is illegal for host to issue this
CCC. When ENEC CCC is registered by the PMIC, it updates Table 142, “Register 0x34” [6] = ‘1’ and it takes in
effect at the next Start operation (i.e., after STOP operation). Table 55 to Table 58 show an example of a single ENEC
CCC. Table 59 shows the encoding definition for ENEC CCC.

If PEC function is enabled, the PEC calculation starts with Start or Repeat Start operation but does not include 7’h7E
with W=0 byte in PEC calculation.

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S or Sr

1

1

1

1

1

1

0

0x00 (Broadcast)

0x00

Stop

Bit 0

W=0

A/N/T
A1
T

ENINT

T

Sr2 or P

NOTE 1  The PMIC NACKs if there is a parity error in a previous transaction when host performs consecutive transactions with Repeat

Start.

NOTE 2  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 74

2.10.12.1 ENEC CCC (cont’d)

Table 56 — ENEC CCC - Broadcast with PEC

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S or Sr

1

1

1

1

1

1

0

0x00 (Broadcast)

0x00

PEC

Bit 0

W=0

ENINT

A/N/T
A1
T

T

T

Stop

Sr2 or P

NOTE 1  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

NOTE 2  Repeat Start or Repeat Start with 7’h7E.

Start

Bit 7

Bit 6

S or Sr

1

1

Sr

Bit 0

W=0

W=0

ENINT

A/N/T
A1
T

A1,2

T

Stop

Sr3 or P

0

1

1

1

1

0x00

Bit 1

Bit 5

Bit 2

Bit 3

Bit 4

DevID[6:0]

0x80 (Direct)

Table 57 — ENEC CCC - Direct

JPGNetworksLLC

Table 58 — ENEC CCC - Direct with PEC

NOTE 1  The PMIC NACKs if there is a parity error in a previous transaction when host performs consecutive transactions with Repeat

Start.

NOTE 2  The PMIC device does not check for parity error in subsequent bytes when it determines 7-bit device select code issued by the
Host does not match with its own device code. The PMIC device ignores the entire packet until STOP operation or next Repeat
Start operation.

NOTE 3  Repeat Start or Repeat Start with 7’h7E.

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

Bit 0

S or Sr

1

1

1

1

1

1

0

W=0

Sr

0x80 (Direct)

PEC

DevID[6:0]

0x00

PEC

W=0

ENINT

A/N/
T
A1
T

T

A1,2
T

T

Stop

Sr3 or P

NOTE 1  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

NOTE 2  The PMIC device does not check for parity error in subsequent bytes when it determines 7-bit device select code issued by the
Host does not match with its own device code. The PMIC device ignores the entire packet until STOP operation or next Repeat
Start operation.

NOTE 3  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 75

2.10.12.1 ENEC CCC (cont’d)

Table 59 — ENEC CCC Byte Encoding

Bit

ENINT

Encoding

Notes

0 = No Action
1 = Enable IBI Interrupt

It is illegal for Host to issue ENEC CCC
with ENINT bit = ‘0’

2.10.12.2  DISEC CCC

The DISEC CCC is only supported after device is put in I3C Basic mode. In I2C mode, it is illegal for host to issue
this CCC. When DISEC CCC is registered by the PMIC, it updates Table 142, “Register 0x34” [6] = ‘0’and it takes in
effect  at  the  next  Start  operation  (i.e.,  after  STOP  operation).  Table 60  to  Table 63  shows  an  example  of  a  single
DISEC CCC. Table 64 shows the encoding definition for DISEC CCC.

If PEC function is enabled, the PEC calculation starts with Start or Repeat Start operation but does not include 7’h7E
with W=0 byte in PEC calculation.

Start

Bit 7

Bit 6

S or Sr

1

1

Bit 0

W=0

Stop

A/N/T
A1
T

Sr2 or P
NOTE 1  The PMIC NACKs if there is a parity error in a previous transaction when host performs consecutive transactions with Repeat Start.

DISINT

7’h00

T

NOTE 2  Repeat Start or Repeat Start with 7’h7E.

1

1

1

1

Bit 1

Bit 2

Bit 3

Bit 4

Bit 5

Table 60 — DISEC CCC - Broadcast

JPGNetworksLLC

Table 61 — DISEC CCC - Broadcast with PEC

0x01 (Broadcast)

Bit 5

Bit 3

Bit 2

Bit 4

Bit 1

0

1

1

1

0

Start

Bit 7

Bit 6

S or Sr

1

1

1

0x01 (Broadcast)

7’h00

PEC

DISINT

Bit 0

W=0

A/N/T
A1
T

T

T

Stop

Sr2 or P

NOTE 1  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

NOTE 2  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 76

2.10.12.2 DISEC CCC (cont’d)

Table 62 — DISEC CCC - Direct

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S or Sr

1

1

1

1

1

1

0

Sr

0x81 (Direct)

DevID[6:0]

Stop

Bit 0

W=0

W=0

A/N/T
A1
T

A1,2

Sr3 or P
NOTE 1  The PMIC NACKs if there is a parity error in a previous transaction when host performs consecutive transactions with Repeat Start.
NOTE 2  The PMIC device does not check for parity error in subsequent bytes when it determines 7-bit device select code issued by the Host

DISINT

0x00

T

does not match with its own device code. The PMIC device ignores the entire packet until STOP operation or next Repeat Start
operation.

NOTE 3  Repeat Start or Repeat Start with 7’h7E.

Start

Bit 7

Bit 6

S or Sr

1

1

Sr

0

1

1

1

1

PEC

Bit 1

Bit 2

Bit 3

Bit 4

Bit 5

0x81 (Direct)

Table 63 — DISEC CCC - Direct with PEC

JPGNetworksLLC

DevID[6:0]

0x00

PEC

Bit 0

W=0

W=0

DISINT

A/N/T
A1
T

T

A1,2
T

T

Stop

Sr3 or P

NOTE 1  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

NOTE 2  The PMIC device does not check for parity error in subsequent bytes when it determines 7-bit device select code issued by the Host

does not match with its own device code. The PMIC device ignores the entire packet until STOP operation or next Repeat Start
operation.

NOTE 3  Repeat Start or Repeat Start with 7’h7E.

Table 64 — DISEC CCC Byte Encoding

Bit

DISINT

Encoding

Notes

0 = No Action
1 = Disable IBI Interrupt

It is illegal for Host to issue DISEC CCC
with DISINT bit = ‘0’

2.10.12.3  RSTDAA CCC

The RSTDAA CCC is only supported after device is put in I3C Basic mode. In I2C mode, this CCC is ignored. When
RSTDAA CCC is registered by the PMIC, it updates Table 140, “Register 0x32” [6] = ‘0’ and it takes in effect at the
next Start operation (i.e., after STOP operation). Further it disables IBI and PEC function (Table 142, “Register 0x34”
[7:6] = ‘00’) and clears parity function Table 142, “Register 0x34” [5] = ‘0’).

Table 65 to Table 66 show an example of a single RSTDAA CCC.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 77

2.10.12.3 RSTDAA CCC (cont’d)

If PEC function is enabled, the PEC calculation starts with Start or Repeat Start operation but does not include 7’h7E
with W=0 byte in PEC calculation.

Table 65 — RSTDAA CCC - Broadcast

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S or Sr

1

1

1

1

1

1

0

0x06 (Broadcast)

Bit 0

W=0

A/N/T
A1
T

Stop

P

NOTE 1  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

Start

Bit 7

Bit 6

S or Sr

1

1

Bit 0

W=0

Stop

A/N/T
A1
T

T

P

NOTE 1  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

0

1

1

1

1

PEC

Bit 1

Bit 2

Bit 3

Bit 5

Bit 4

Table 66 — RSTDAA CCC - Broadcast with PEC

0x06 (Broadcast)

JPGNetworksLLC

2.10.12.4  SETAASA CCC

The SETAASA  CCC  is only supported when  device is  in  I2C mode.  In  I2C  mode,  when host issues  this CCC,  to
guarantee  that  this  CCC  is  registered  by  the  device  without  any  error,  the  host  shall  limit  the  maximum  speed
operation for this CCC to 1 MHz. In I3C Basic mode, this CCC is ignored. When SETAASA CCC is registered by the
PMIC, it updates Table 140, “Register 0x32” [6] = ‘1’and it takes in effect at the next Start operation (i.e., after STOP
operation). Table 67 shows an example of a single SETAASA CCC.

SETAASA CCC does not support PEC function as device is in I2C mode and there is no PEC function in I2C mode.

Table 67 — SETAASA CCC - Broadcast

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S or Sr

1

1

1

1

1

1

0

0x29 (Broadcast)

Bit 0

W=0

A/N/T

Stop

A

T

P

2.10.12.5  GETSTATUS CCC

The GETSTATUS CCC is supported in I3C Basic mode. In I2C mode, this CCC is ignored (i.e., it is not executed
internally and the Repeat Start byte arriving after the 0x90 GETSTATUS CCC code is not acknowledged and host
must do STOP operation. Table 68 to Table 69 show an example of a single GETSTATUS CCC.

If PEC function is enabled, the PEC calculation starts with Start or Repeat Start operation but does not include 7’h7E
with W=0 byte in PEC calculation.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 78

2.10.12.5 GETSTATUS CCC (cont’d)

Table 68 — GETSTATUS CCC - Direct

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S or Sr

1

Sr

PEC_Err

1

0

1

0

1

1

0x90 (Direct)

DevID[6:0]

0

0

1

0

0

0

Stop

Bit 0

W=0

R=1

0

A/N/T
A1
T

A

T

0

Sr2 or P
NOTE 1  The PMIC NACKs if there is a parity error in a previous transaction when host performs consecutive transactions with Repeat Start.
NOTE 2  Repeat Start or Repeat Start with 7’h7E.

Pending Interrupt

R32[3]

P_Err

T

0

Start

Bit 7

Bit 6

S

1

Sr

PEC_Err

0

1

0

0

Bit 0

W=0

R=1

0

0

0

1

1

1

1

PEC

Bit 1

Bit 2

Bit 3

Bit 4

Bit 5

DevID[6:0]

0x90 (Direct)

Table 69 — GETSTATUS CCC - Direct with PEC

JPGNetworksLLC

Table 70 — GETSTATUS CCC Byte Encoding

Pending Interrupt

R32[3]

P_Err

PEC

0

0

0

0

Stop

A/N/T
A1
T

T

A

T

T

T

Sr2 or P

NOTE 1  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

NOTE 2  Repeat Start or Repeat Start with 7’h7E.

Bit

PEC_Err

Encoding

0 = No Error
1 = PEC Error Occurred

P_Err

R32[3]

Pending
Interrupt

0 = No Error
1 = Protocol Error; Parity Error
occurred

See Table 140, “Register 0x32”
for encoding.

0000 = No Pending Interrupt or
No New Global Status Event
0001 = Pending Interrupt or New
Global Status Event
All other encodings are reserved

Notes

This register is cleared when Host issues clear command
to Table 108, “Register 0x12” [3] for PEC error

This register is cleared when Host issues clear command
to Table 108, “Register 0x12” [2] for Parity error.

PMIC reflects the register status of R32[3] in this bit.

This register is cleared when Host issues clear command
to any appropriate device status register that causes IBI
status register to get cleared.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 79

2.10.12.5 GETSTATUS CCC (cont’d)

When the  PMIC device  responds to GETSTATUS  CCC, after it completes the response, the  PEC_Err,  P_Err,  and
Pending Interrupt Bits [3:0] do not automatically get cleared. The host must explicitly clear the appropriate status
register through Clear command by writing ‘1’ to corresponding register or by issuing Global Clear command. Once
the PMIC device clears the appropriate status register, only then PEC_Err, P_err and Pending Interrupt Bits [3:0] gets
cleared.

After  host  issues  clear  command,  if  the  condition  is  still  present,  the  device  will  again  set  the  appropriate  status
register, sets the IBI status register to ‘1’ and Pending Interrupt Bits [3:0] to ‘0001’.

2.10.12.6  DEVCAP CCC

The DEVCAP CCC is only supported after device is put in I3C Basic mode. In I2C mode, it is illegal for host to issue
this  CCC.  Table 71  to  Table 72  show  an  example  of  a  single  DEVCAP  CCC.  Table 73  defines  the  encoding  for
DEVCAP CCC.

If PEC function is enabled, the PEC calculation starts with Start or Repeat Start operation but does not include 7’h7E
with W=0 byte in PEC calculation.

Start

Bit 7

Bit 6

S or Sr

1

1

Sr

1

1

1

Bit 1

Bit 2

Bit 3

Bit 4

Bit 5

Table 71 — DEVCAP CCC - Direct

JPGNetworksLLC

Table 72 — DEVCAP CCC - Direct with PEC

MSB (Each bit defines capability)

0xE0 (Direct)

DevID[6:0]

1

0

Bit 0

W=0

R=1

Stop

A/N/T
A1
T

A1
T

Sr2 or P
NOTE 1  The PMIC NACKs if there is a parity error in a previous transaction when host performs consecutive transactions with Repeat Start.
NOTE 2  Repeat Start or Repeat Start with 7’h7E.

LSB (Each bit defines capability)

T

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S or Sr

1

1

1

1

1

1

0

Sr

0xE0 (Direct)

PEC

DevID[6:0]

MSB (Each bit defines capability)

LSB (Each bit defines capability)

PEC

Bit 0

W=0

R=1

A/N/T
A1
T

T

A1
T

T

T

Stop

Sr2 or P

NOTE 1  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

NOTE 2  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 80

2.10.12.6 DEVCAP CCC (cont’d)

Table 73 — DEVCAP CCC Byte Encoding

Encoding

Notes

Bit

MSB [7]

MSB[6]

MSB[5]

MSB[4]

MSB[3]

MSB[2]

RFU

RFU

RFU

RFU

RFU

0 = No Support for Timer based Reset
1 = Supports Timer based Reset

MSB[1:0]

LSB[7:0]

RFU

RFU

Coded as ‘0’

Coded as ‘0’

Coded as ‘0’

Coded as ‘0’

Coded as ‘0’

Coded as ‘1’

Coded as ‘00’

Coded as ‘0x00’

2.10.12.7  SETHID CCC

The  SETHID  CCC  is  supported  only  when  device  is  in  I2C  mode.  In  I2C  mode,  when  host  issues  this  CCC,  to
guarantee  that  this  CCC  is  registered  by  the  device  without  any  error,  the  host  shall  limit  the  maximum  speed
operation for this CCC to 1 MHz. In I3C Basic mode, it is illegal for host to issue this CCC. When SETHID CCC is
registered by the PMIC, it updates Table 142, “Register 0x34” [3:1] with the HID code received by the PMIC and it
takes in effect at the next Start operation (i.e., after STOP operation). Table 74 shows an example of a single SETHID
CCC. As the device is in I2C mode when SETHID CCC is issued, the PEC function is not supported.

Once  PMIC  receives  SETHID  CCC  and  updates  its  3-bit  HID  code,  after  the  Stop  operation,  PMIC  device  only
responds to updated 7-bit address. The 4-bit LID code of the PMIC device remains as is.

JPGNetworksLLC

Table 74 — SETHID CCC - Broadcast

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

Start

Bit 7

Bit 6

S or Sr

1

0

1

0

1

0

1

1

1

0

0x61 (Broadcast)

0

HID[2:0]

Bit 0

W=0

0

A/N/T

Stop

A

T

T

P

The Host may issue SETHID CCC more than one time.

2.10.12.8  DEVCTRL CCC

On a typical I3C Basic bus there can be up to 120 devices. For DDR5 DIMM application environment, there are up to
8 SPD5 Hub devices and behind each SPD5 Hub devices, there are 4 local target devices totaling up to 40 or more
devices on I3C Basic bus. For certain operation such as enable or disable functions that are common to all devices
(i.e., Packet Error Check), the host must go through one device at a time which takes significant amount of time at
initial  power  up.  Further,  it  requires  additional  complexity  on  the  host  because  it  must  speak  different  protocol
depending on how it may access the device until all devices are configured identically.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 81

2.10.12.8 DEVCTRL CCC (cont’d)

To help expedite this configuration operation and to simplify the host complexity, the device supports the SPDCTRL
CCC. The DEVCTRL CCC is supported either in I2C mode or I3C Basic mode of operation. In I2C mode, when host
issues  this  CCC,  to  guarantee  that  this  CCC  is  registered  by  the  device  without  any  error,  the  host  shall  limit  the
maximum speed operation for this CCC to 1 MHz. Table 75 to Table 76 show an example of a single DEVCTRL
CCC.

In I3C mode only, if PEC function is enabled, the PEC calculation starts with Start or Repeat Start operation but does
not include 7’h7E with W=0 byte in PEC calculation.

The host shall pay attention to DEVCTRL CCC. If DEVCTRL CCC is used to access device specific registers (e.g.,
RegMod  =  ‘1’),  the  host  shall  still  follow  any  device  specific  register  restriction.  For  example,  if  device  specific
register requires STOP operation for device to take in the effect of the setting, the host must also use STOP operation
when using DEVCTRL CCC to access device specific register.

Start

Bit 7

Bit 6

S or Sr

1

1

AddrMask[2:0]

Bit 0

W=0

RegMod

0

0

1

1

1

1

Bit 3

Bit 1

Bit 2

Bit 4

Bit 5

DevID[6:0]

PEC BL[1:0]

StartOffset[1:0]

0x62 (Broadcast)

Table 75 — DEVCTRL CCC - Broadcast

JPGNetworksLLC

Byte 1 Data Payload

Byte 0 Data Payload

Byte 2 Data Payload

Byte 3 Data Payload

Stop

A/N/T
A1
T

T

T2
T

T

T

T

Sr3 or P

NOTE 1  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with

Repeat Start.

NOTE 2  An exception is made for DEVCTRL CCC. The PMIC does not report parity error when it determines 7-bit device select code

issues by the host does not match with its own device code. If 7-bit device select code does not match but if parity is still valid, the
device does not check for parity error in subsequent bytes; ignores the entire packet and waits until STOP or Repeat Start operation.

NOTE 3  Repeat Start or Repeat Start with 7’h7E.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 82

2.10.12.8  DEVCTRL CCC (cont’d)

Table 76 — DEVCTRL CCC - Broadcast with PEC1

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S or Sr

1

1

1

1

1

1

0

0x62 (Broadcast)

Stop

Bit 0

W=0

A/N/T
A2
T

AddrMask[2:0]

StartOffset[1:0]

PEC BL[1:0]

RegMod

0

DevID[6:0]

Byte 0 Data Payload

Byte 1 Data Payload

Byte 2 Data Payload

Byte 3 Data Payload

T

T3
T

T

T

T

T

Sr4 or P

NOTE 1  DEVCTRL CCC with PEC check is only supported in I3C mode.

NOTE 2  The PMIC NACKs if there is a parity or PEC error in a previous transaction when host performs consecutive transactions with Repeat

Start.

NOTE 3  An exception is made for DEVCTRL CCC. The PMIC does not report parity error when it determines 7-bit device select code issues
by the host does not match with its own device code. The device does not check for PEC as all subsequent bytes are discarded due to
parity error. If 7-bit device select code does not match but if parity is still valid, the device does not check for parity error in
subsequent bytes; ignores the entire packet and waits until STOP or Repeat Start operation.

NOTE 4  Repeat Start or Repeat Start with 7’h7E.

PEC

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 83

2.10.12.8 DEVCTRL CCC (cont’d)

Table 77 — DEVCTRL CCC Command Definition

Parameter

Definition

Broadcast, Unicast or Multicast Command Selection

AddrMask[2:0]

000 = Unicast Command; PMIC device responds if DevID[6:0] field matches with
PMIC device’s own 7-bit address (4-bit LID + 3-bit HID)
011 = Multicast Command; PMIC device and possible other device responds if
DevID[6:3] field matches with PMIC device’s own 4-bit LID address
111 = Broadcast Command; All devices responds to this command
All other encodings are reserved

StartOffset[1:0]

PEC BL[1:0]

RegMod

DevID[6:0]

Only applicable if RegMod = ‘0’
Identifies the starting Byte (Byte 0 or Byte 1 or Byte 2 or Byte 3) for DEVCTRL
CCC. Host can start at any Byte (from Byte 0 to Byte 3) and has continuous access to
next byte until STOP operation. If Byte 3 is reached, the host is responsible for
applying STOP operation.

Only applicable if RegMod = ‘0’ and PEC function is enabled.
Identifies the burst length just for this DEVCTRL CCC. The device uses the setting in
this field to know when the PEC byte is expected after the data bytes.

00 = Byte 0
01 = Byte 1
10 = Byte 2
11 = Byte 3

JPGNetworksLLC

00 = 1 Byte
01 = 2 Byte
10 = 3 Byte
11 = 4 Byte

Identifies if DEVCTRL is going to be used for General Registers as identified in Byte
0 to Byte 3 or device specific address offset register.

0 = Access to General Registers in Byte 0 to Byte 3 (i.e., StartOffset[1:0] = Valid)
1 = Device Specific Offset Address (i.e., StartOffset[1:0] and PECBL[1:0] is a don’t
care and does not apply). The Host shall NOT use RegMod = ‘1’ with Broadcast
Command if there are different types of devices on the I3C Basic bus.

Identifies 7-bit device address. Device responds to DEVCTRL CCC data packet
depending on AddrMask[2:0].

If AddrMask[2:0] = ‘111’, DevID[6:0] is a don’t care and device always responds.
If AddrMask[2:0] = ‘000’, DevID[6:0] must match for device to respond
If AddrMask[2:0] = ‘011’, DevID[6:3] must match for device to respond. DevID[2:0]
is don’t care.
For any other codes for AddrMask[2:0], the device always NACKs.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 84

2.10.12.8 DEVCTRL CCC (cont’d)

Table 78 — DEVCTRL CCC Data Payload Definition

Byte #

Bit #

Function

Definition

Comment

 Table 142, “Register 0x34” [7] is
updated

 Table 142, “Register 0x34” [5] is
updated

Table 140, “Register 0x32” [7] is
updated.

[7]

[6]

PEC
Enable
Parity Dis-
able

0 = Disable
1 = Enable

0 = Enable
1 = Disable

Byte 0

[5:2]

RFU

RFU

VR Enable

0 = VR Disable
1 = VR Enable

RFU

RFU

RFU

RFU

[1]

[0]

[7:4]

[3]

[2:0]

[7:0]

[7:0]

Byte 1

Byte 2

Byte 3

Table 110, “Register 0x14” [0] is
updated.

NOTE 1  After target device clears the event, the device can still have certain registers set to ‘1’ if the event is still present in which case,

the device will generate an IBI again at the next opportunity.

Global and
IBI Clear

RFU

RFU

RFU

RFU

RFU

0 = No Action
1 = Clear All Event and pending IBI1
RFU

JPGNetworksLLC

Table 79 shows an example of DEVCTRL CCC data packet. It assumes that all devices on the bus are already in I3C
Basic mode with PEC function disabled and parity function enabled. In this example, the Host uses DEVCTRL CCC
as Multicast command. Host sends Multicast command to all devices with 4-bit LID code of ‘1001’ on I3C Basic bus
to do VR Enable followed by all devices with 4-bit LID code of ‘0110’ to disable parity function. The host sends
AddrMask = ‘011’ to indicate Multicast command with DevID[6:3] match; StartOffset = ‘00’ to indicate starting Byte
0 and RegMod = ‘0’ to indicates general register. Upon receiving this command, all devices with DevID[6:3] that
matches to ‘1001’ will do the VR Enable command and DevID[6:3] that matches to ‘0110’ with disable the parity
function.

2.10.12.8.1  DEVCTRL CCC Examples - RegMod = ‘0’

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 85

2.10.12.8.1 DEVCTRL CCC Examples - RegMod = ‘0’ (cont’d)

Table 79 — DEVCTRL CCC Example - Multicast Command to ‘1001’ and ‘0110’ Devices

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

0

S

1

1

011

Sr

1

1

1

1

1

1

0x62 (Broadcast)

00

1001 000

0000 0010

1

1

0x62 (Broadcast)

011

00

1

1

00

00

0

W=0

Bit 0

W=0

0

0

0

0

Stop

A/N/T
A1
T

T

T

T

A1
T

T

T

T

P

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation.

Table 80 shows an example of DEVCTRL CCC data packet. It assumes that all devices on the bus are already in I3C
Basic mode with PEC function disabled and parity function enabled. In this example, the Host uses DEVCTRL CCC
as Broadcast command to enable PEC function. The host sends AddrMask = ‘111’ to indicate Broadcast command;
StartOffset = ‘00’ to indicate starting Byte 0 and RegMod = ‘0’ to indicates general register. Upon receiving this
command, all devices will enable PEC function.

0110 000

0100 0000

JPGNetworksLLC

0x62 (Broadcast)

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

1

1

1

1

0

00

00

0000 000

1000 0000

Bit 0

W=0

0

0

A/N/T
A1
T

T

T

T

Stop

P

Start

Bit 7

Bit 6

S

1

1

111

Table 80 — DEVCTRL CCC Example - Broadcast Command to all Devices

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation.

Table 81 shows an example of DEVCTRL CCC data packet. It assumes that all devices on the bus are already in I3C
Basic mode with PEC function disabled and parity function enabled. In this example, the Host uses DEVCTRL CCC
as Unitcast command to enable VR on DIMM5. The host sends AddrMask = ‘000’ to indicate Unicast command;
StartOffset = ‘00’ to indicate starting Byte 0 and RegMod = ‘0’ to indicates general register. Upon receiving this
command, PMIC on DIMM5 will enable its regulator.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 86

2.10.12.8.1 DEVCTRL CCC Examples - RegMod = ‘0’ (cont’d)

Table 81 — DEVCTRL CCC Example - Unicast Command to PMIC on DIMM5

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S

1

1

1

1

1

1

0

000

0x62 (Broadcast)

00

1001 101

0000 0010

00

Bit 0

W=0

0

0

A/N/T
A1
T

T

T

T

Stop

P

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation.

2.10.12.8.2  DEVCTRL CCC Examples - RegMod = ‘1’

Table 82 shows an example of DEVCTRL CCC data packet for the purpose of configuring device specific address
offset register. It assumes that all devices on the bus are already in I3C Basic mode with PEC function enabled and
parity function enabled. In this example, the Host sends Multicast command to all devices with 4-bit LID code of
‘0010’ on the I3C Basic bus to write to address offset of 0x1C and 0x1D with data 0xFF and 0x55 respectively
followed by all devices with 4-bit LID of ‘1001’ on the I3C Basic bus to write to address offset of 0x15 with data
0x78.

The PEC calculation starts with Start or Repeat Start operation but does not include 7’h7E with W=0 byte in PEC
calculation.

JPGNetworksLLC

0001 1100 (address offset 0x1C)

0010 0000 (CMD field = 2 bytes of data)

0x62 (Broadcast)

0010 000

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

00

00

1

1

1

1

0

Bit 0

W=0

1

0

Start

Bit 7

Bit 6

S

1

1

011

Table 82 — DEVCTRL CCC Example - Multicast Command to ‘0010’ and ‘1001’ Devices

1111 1111 (data)

0101 0101 (data)

PEC

Sr

1

1

1

1

1

1

0

W=0

011

0x62 (Broadcast)

00

1001 000

00

1

0

0001 0101 (address offset 0x15)

0000 0000 (CMD field = 1 byte of data)

0111 1000 (data)

PEC

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation.

Stop

A/N/T
A1
T

T

T

T

T

T

T

T
A1
T

T

T

T

T

T

T

P

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 87

2.10.12.8.2 DEVCTRL CCC Examples - RegMod = ‘1’ (cont’d)

Table 83 shows an example of DEVCTRL CCC data packet for the purpose of configuring device specific address
offset register. It assumes that all devices on the bus are already in I3C Basic mode with PEC function disabled and
parity function enabled. In this example, the Host sends Multicast command to all devices with 4-bit LID code of
‘1001’ on the I3C Basic bus to write to address offset of 0x13 with data 0xFF and it continues to write data 0x01 to
the next address.

Table 83 — DEVCTRL CCC Example - Multicast Command to ‘1001’ Devices

Stop

Bit 0

W=0

A/N/T
A1
T

1

0

T

T

T

T

T

P

Start

Bit 7

Bit 6

Bit 5

Bit 4

Bit 3

Bit 2

Bit 1

S

1

1

1

1

1

1

0

0x62 (Broadcast)

011

00

00

2.10.13   IO Operation

NOTE 1  See Figure 18 to see how the transition occurs from Target Open Drain (ACK) to Host Push Pull Operation.

1001 000

1111 1111 (data)

0000 0001 (data)

0001 0011 (address offset 0x13)

JPGNetworksLLC

At power on, by default, the PMIC device comes up in legacy I2C mode of operation with Open Drain IO for its
interface. The maximum speed is limited to 1 MHz and supported IO voltage levels are from 1.0 V to 3.3 V.

After power on, the host may put the PMIC device in I3C Basic mode of operation.

In I3C Basic mode, the host may drive the SCL clock input of the PMIC device using either Push-Pull output driver
or  using  the  open-drain  output  driver.  It  is  expected  that  for  all  DDR5  DIMM  family  environment,  the  host  may
always drive the SCL clock input using a Push-Pull output driver.

To support in band interrupt, the PMIC device supports dynamic switching between Open Drain mode and Push Pull
mode on its SCL and SDA bus for various event. The Table 84 below describes the different mode of operation by the
PMIC device for each cycle.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 88

2.10.13 IO Operation (cont’d)

Table 84 — PMIC Device Dynamic IO Operation Mode Switching

Open Drain Mode

Push Pull Mode

START + Device Select Code

START + 7’h7E IBI Header Byte

REPEAT START + Device Select Code

REPEAT START + 7’h7E Header Byte

CCC Bytes (i.e., after 7’h7E+W=0+ACK)

STOP

ACK/NACK Responses

Command, Block Address, Address Operation

Yes

Yes

No

No

No

No

Yes

No

Interrupt Request by Target + Device Select Code

Yes

2.10.14   Bus Clear

Write Data, T-bit sequence

Read Data, T-bit sequence

PEC, T-bit sequence

No

No

No

No

IBI Payload

JPGNetworksLLC

The PMIC device supports the following described Bus Clear feature in I2C mode only. Any attempt by host to
perform I2C Bus clear on a target device in I3C mode may result in an active drive bus contention on the SDA data
line.

There may be abnormal circumstances when the host abruptly stops clocking SCL while the target device is in the
middle of outputting data for read operation. For these type of events, the SDA data line may appear as stuck low as
the device is expecting to receive more clock pulses from the host. Eventually when the host has control of the SCL
clock, the host may optionally clear the device that is stuck low on the SDA data line by sending continuous 18 clock
pulses  without  driving  the  SDA  data  line  followed  by  STOP  operation. The  device  floats  the  SDA  line  within  18
clock pulses and returns to the Idle state. The device is ready for normal new transaction with Start condition.

No

No

Yes

Yes

Yes

Yes

No

Yes

No

Yes

Yes

Yes

Yes

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 89

2.10.15   Bus Reset

To prevent a malfunctioning device from locking up the I2C bus or I3C Basic bus, a bus reset mechanism is defined.
It uses a timeout mechanism on SCL as shown in Figure 25 to force a device bus reset. All devices on a I2C or I3C
Basic bus reset simultaneously. Bus reset operation works same way regardless of whether device is operating in I2C
or I3C Basic mode.

To guarantee the device resets I2C bus or I3C Basic bus, the SCL clock input Low time has to be greater than or equal
to tTIMEOUT(Max).

The PMIC device does not reset I2C bus or I3C Basic bus if the SCL clock input Low time is less than tTIMEOUT(Min).

If the SCL clock input Low time is between tTIMEOUT(Min) and tTIMEOUT(Max), the PMIC device does not guarantee
and it may or may not reset the I2C bus or I3C Basic bus.

When RESET, the PMIC device takes following action.

1.   Interface and any pending command or transactions are cleared
2.   All internal register values are preserved unless noted otherwise in item # 3 below.
3.   Device returns to I2C mode of operation; Table 142, “Register 0x34” [3:1] resets to ‘111’;
Table 142, “Register 0x34” [7:5] resets to ‘000’; Table 140, “Register 0x32” [6] to ‘0’;
Table 100, “Register 0x0A” [3:2] to ‘00’.

4.   Device does not re-sample PID pin.
5.   Device floats the SDA pin such that it gets pulled High by external/other device pullup.
6.   Device treats bus reset as STOP operation.

JPGNetworksLLC

tTIMEOUT(Max)

tTIMEOUT(Min)

SCL

SCL

SCL

VIL

VIL

VIL

Resets I2C/I3C Interface

Does Not Reset I2C/I3C Interface

May or May Not Reset I2C/I3C Interface

Figure 25 — I2C or I3C Basic Bus Reset - PMIC Device

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 90

2.10.16   Command Truth Table

The command truth table as shown in Table 85 only applies in I3C Basic mode with PEC enabled. In I2C mode and
I3C Basic mode with PEC disabled, the command truth table does not apply.

Table 85 — For I3C Mode only with PEC Enabled - Command Truth Table

CMD Code

RW

Address

TS5 Command
Write 1 Byte to Register
Read 1 Byte from Register
Write 2 Byte to Register
Read 2 Byte from Register
Write 4 Byte to Register
Read 4 Byte from Register
Write 16 Byte to Register
Read 16 Byte from Register
Reserved

Command
Name
W1R
R1R
W2R
R2R
W4R
R4R
W16R
R16R
RSVD

2nd Byte
Bits [7:5]

000

001

010

2nd Byte
Bit [4]
0
1
0
1
0
1
0
1
RSVD

1st Byte
Bits [7:0]
V
V
V
V
V
V
V
V
RSVD

011

100 to 111

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 91

2.11   Device Package and Pinout

The PMIC device is packaged in 5 mm x 5 mm FCQFN.

2.11.1   Package Pinout

The PMIC pinout is shown in Figure 26 and Figure 27 for TOP view and BOTTOM view, respectively.

C
A
M
P

N
C

S
W
A
B
_
F
B
_
N

S
W
A
B
_
F
B
_
P

S
W
C
_
F
B
_
P

S
W
C
_
F
B
_
N

G
S
I
_
n

S
D
A

S
C
L

R
F
U
2

1

3
5

3
4

3
3

3
2

3
1

3
0

2
9

2
8

2
7

N
C

2
6

SWA_BOOT

2

VIN_Bulk

3

SWA

4

PGND

SWB

5

6

VIN_Bulk

7

SWB_BOOT

8

Top View

JPGNetworksLLC

DDR5 PMIC
5 mm x 5 mm
FCQFN

A
G
N
D

V
b
a
s

R
F
U
1

1
1

1
0

1
3

1
2

1
8

1
7

1
6

1
5

1
4

V
O
U
T
_
1

V
O
U
T
_
1

i

9

N
C

S
W
B
_
F
B
_
P

I

V
N
_
M
g
m

t

S
W
D
_
F
B
_
P

S
W
D
_
F
B
_
N
/
P
D

I

.

8
V

.

0
V

25

SWC_BOOT

24

VIN_Bulk

23

SWC

PGND

22

SWD

21

VIN_Bulk

20

SWD_BOOT

1
9

N
C

Figure 26 — PMIC Pinout - TOP View

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 92

2.11.1 Package Pinout (cont’d)

N
C

R
F
U
2

S
C
L

S
D
A

S
W
C
_
F
B
_
N

S
W
C
_
F
B
_
P

G
S
I
_
n

S
W
A
B
_
F
B
_
P

S
W
A
B
_
F
B
_
N

C
A
M
P

2
6

2
7

2
8

2
9

3
0

3
1

3
2

3
3

3
4

3
5

N
C

1

SWC_BOOT

25

VIN_Bulk

24

SWC

23

PGND

SWD

22

VIN_Bulk

21

SWD_BOOT

20

1
9

N
C

2

3

4

5

6

7

SWA_BOOT

VIN_Bulk

SWA

PGND

SWB

VIN_Bulk

8

SWB_BOOT

Bottom View

DDR5 PMIC
5 mm x 5 mm
FCQFN

JPGNetworksLLC

Figure 27 — PMIC Pinout - BOTTOM View

S
W
D
_
F
B
_
N
/
P
D

V
O
U
T
_
1
8
V

S
W
D
_
F
B
_
P

S
W
B
_
F
B
_
P

V
N
_
M
g
m

V
O
U
T
_
1

A
G
N
D

V
b
a
s

R
F
U
1

0
V

1
7

1
8

1
0

1
1

1
2

1
3

1
4

1
5

1
6

t

.

.

I

I

i

9

N
C

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 93

2.11.2   PMIC Package Pin List

.

Pin Name

Type

Description

Table 86 — PMIC Pin Description

VIN_Bulk (4x)

VIN_Mgmt

I

I

CAMP

IO

GSI_n

O

VBias

SCL

SDA

SWA

SWA_BOOT

SWAB_FB_P

SWAB_FB_N

12 V power input supply pin to the PMIC. All four VIN_Bulk input pins must be
connected to the 12V input supply even if one or more output regulators are not intended
to be used.

3.3 V power input supply pin to the PMIC for VOUT_1.8V and VOUT_1.0V LDO
output, side band management access, internal memory read operation. Vendor usage of
3.3V input supply may vary.

Control and Monitor Port. Open drain output. The PMIC floats this pin when VIN_Bulk
input supply, as well as all enabled output buck regulators and all LDO regulators
tolerance threshold is maintained as configured in the appropriate register. The PMIC
drives this pin low when VIN_Bulk input goes below the threshold or when any of the
enabled output buck regulator exceeds the thresholds configured in the appropriate
register or when any LDO output regulator exceeds the threshold configured in the
appropriate register.

Input: The PMIC disables its output regulator when this pin transitions from high to low.
The LDO outputs shall remain on.

Input: The PMIC enters write protect mode when it is high and configuration mode when
it is low.

JPGNetworksLLC

high quality capacitor.

General Status Interrupt. Open drain output. The PMIC asserts this pin low to
communicate any one or more critical event to host. This pin stays asserted until the
appropriate registers are explicitly cleared.

In single phase regulator mode of operation, the SWA output must not be connected to
either SWB or SWC output even if they are configured as same exact output voltage.

I

IO

O

I2C/I3C Basic Clock Input for management bus.
I2C/I3C Basic Data Input/Output for management bus.
Output switch node A buck regulator. This pin connects to L1 power inductor.

PWR Bootstrap node for SWA high side NMOS driver. This pin connects to SWA through a

PWR Vbias Voltage generated by PMIC.

I

I

In single phase regulator mode or dual phase regulator mode of operation, this pin
connects to DIMM power plane load.

In single phase regulator mode or dual phase regulator mode of operation, this pin
connects to DIMM ground plane.

SWB

O

Output switch node B buck regulator. This pin connects to L2 power inductor.

In single phase regulator mode of operation, the SWB output must not be connected to
either SWA or SWC output even if they are configured as same exact output voltage.

SWB_BOOT

PWR Bootstrap node for SWB high side NMOS driver. This pin connects to SWB through a

high quality capacitor.

SWB_FB_P

I

In single phase regulator mode of operation, this pin connects to DIMM power plane load.
If not used, this pin must be connected to GND.

SWC

O

In dual phase regulator mode of operation, this pin must be connected to GND.

Output switch node C buck regulator. This pin connects to L3 power inductor. The output
of SWC must not be connected to the output of either SWA or SWB or SWA+SWB even
if they are configured as same exact output voltage.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 94

Pin Name

Type

Description

Table 86 — PMIC Pin Description (cont’d)

SWC_BOOT

PWR Bootstrap node for SWC high NMOS driver. This pin connects to SWC through a high

SWC_FB_P

SWC_FB_N

SWD

I

I

O

quality capacitor.

This pin connects to DIMM power plane load.

This pin connects to DIMM ground plane.

Output switch node D buck regulator. This pin connects to L4 power inductor.

SWD_BOOT

PWR Bootstrap node for SWD high side NMOS driver. This pin connects to SWD through a

high quality capacitor.

This pin connects to DIMM power plane load.

This pin connects to DIMM ground plane when PMIC is used in differential remote
sensing mode of operation.

This pin connects to DIMM ground plane or VOUT_1.8V rail or left floating when PMIC
is used in a single ended remote sensing mode of operation.

No Connect. This pin is not connected internally in the package to the die. Typical
application connects this pin to GND on PCB for better thermal performance.

PWR Analog Ground. Connects to DIMM ground plane.

PWR Power Ground. Connects to DIMM ground plane.

1.8V LDO Output.

1.0 V LDO Output.

This pins must be connected to GND.

JPGNetworksLLC

I

I

O

O

SWD_FB_P

SWD_FB_N/
PID

VOUT_1.8V

VOUT_1.0V

AGND

PGND

RFU1, RFU2

NC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

2.11.3   Package Mechanical Drawing

JEDEC Standard No. 301-1A.02
Page 95

JPGNetworksLLC

Figure 28 — Package Mechanical Outline

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 96

2.11.3 Package Mechanical Drawing (cont’d)

Figure 29 — Detail A Drawing

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

2.11.3 Package Mechanical Drawing (cont’d)

JEDEC Standard No. 301-1A.02
Page 97

JPGNetworksLLC

Figure 30 — Detail B Drawing

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 98

2.11.3 Package Mechanical Drawing (cont’d)

JPGNetworksLLC

Figure 31 — Reference PCB Land Pattern

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 99

2.12   Inductor Specification

2.12.1   Mechanical Specification

The inductor package dimensions and its recommended land patterns are defined in Table 87.

Table 87 — Inductor Mechanical Specification

Package Size

Reference Drawing

Recommended Land Pattern

L (mm)

4.3 Max

W (mm)

4.3 Max

H (mm)

2.0 Max

Figure 32
(Left Picture)

Figure 32
(Right Picture)

JPGNetworksLLC

Figure 32 — Reference Drawing and Recommended Land Pattern

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

2.13   Application Notes

Table 10.

Topology

JEDEC Standard No. 301-1A.02
Page 100

2.12.2   Electrical Specification

The inductor electrical specifications are defined in Table 88.

Table 88 — Inductor Electrical Specification1

Package
Height
(mm)

L @ 0.5-1 MHz; 0
Bias
+ 20%
(μH)

Max DCR
(mΩ)

Max ACR @ 1
MHz2,3(mΩ)

2.0 Max

0.47
0.68
1.0
1.2

6.9
8.4
15.5
16.5

90
145
250
300

Min L @ 3.5 A
(Ipeakmax of
PMIC5010)4
(μH)
0.30
0.38
0.56
0.67

Min L @ 6 A
(Ipeakmax of
PMIC5000)5
(μH)
0.30
0.38
0.56
0.67

NOTE 1  Test condition: Ambient Temperature = 20 + 2 0C; Ambient Humidity = 65 + 5% Rh
NOTE 2  ACR definition: ACR = Rs @ 1 MHz - DCR. Measured current (1 MHz/sinusoidal): 0.52A rms for 0.47 μH, 0.36A rms for 0.68

μH, 0.25 A rms for 1.0 μH, and 0.2 A rms for 1.2 μH; with no DC Bias for all cases.

NOTE 3  For Rs measurement, it is recommended to measure by Iwatsu SY-8218 (BH Analyzer, with NF IE-1125B), its upper compatible

instruments or other instruments which is guaranteed on the measurement accuracy by inductor vendors.

NOTE 4  Minimum inductance is defined at DC bias current given by definition in Ipeakmax of PMIC5010; Table 5, Table 8, and

NOTE 5  Minimum inductance is defined at DC bias current given by definition in Ipeakmax of PMIC5000; Table 3, Table 7, and Table 9.

JPGNetworksLLC

2.13.1   Method to Identify and Map Out DIMM with a PMIC Fault in Shared CAMP

Typical DDR5 server platform may have up to 32 DDR5 DIMM sockets. Server platform implementation may vary
however it is possible to have up to 8 DDR5 DIMMs may share CAMP signal. The exact number of DDR5 DIMMs
that share CAMP  signal is beyond the scope of this application note. It is assumed that CAMP  signal is pulled up on
the platform or on the controller via 1K Ohm pullup resistor to either 3.3 V or 1.8 V.

In a DDR5 server platform, it is possible that one or more DDR5 DIMM may have encountered a PMIC fault, as
listed below, that has generated VR Disable event. Also refer to Table 27.

•  SWx Over Voltage
•  SWx Under Votlage
•  VIN_Bulk Over Voltage
•  VIN_Bulk Under Voltage
•  Critical Temperature

In this environment, it is desired to let the platform continue to power up and that faulty PMIC does not interfere with
the platform operation. This application note describes a BIOS or appropriate software method to identify the faulty
PMIC/DDR5  DIMM  and  then  to  map  out  the  faulty  PMIC/DDR5  DIMM  from  the  memory  subsystem. The  fault
scenario noted here is one example of fault scenario. Note that initial failure may occur during operation, hence BIOS
needs to determine and log fault condition and then execute the map out routine.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 101

2.13.1 Method to Identify and Map Out DIMM with PMIC Fault in Shared CAMP (cont’d)

Faulty PMIC Identification:

1.   Power up the platform (i.e., DDR5 DIMMs) by applying VIN_Bulk and VIN_Mgmt input supplies.

2.   Broadcast VR Enable command to all PMICs.

3.   If all PMICs power up the their regulators successfully, all PMICs float the CAMP signal and the pullup
resistor pulls the CAMP signal high indicating that all PMICs (i.e., DDR5 DIMMs) have powered up
successfully.

4.   However, if one or more PMIC fails to power up their regulators then that PMIC continues to hold the CAMP
signal low while other PMICs that do power up their regulators successfully floats the CAMP signal. The net
effect is CAMP signal remains low.

5.   BIOS eventually times out as the CAMP signal is not pulled up high and interrogates all PMIC’s status

registers one at a time. The interrogation process of PMIC status registers allows BIOS to identify which
PMICs regulators are successfully powered up and which PMICs are faulty.

Once BIOS identifies faulty PMIC, BIOS stores the faulty PMIC (DDR5 DIMM) identification in its non-volatile
memory.Isolating and Securing Faulted PMIC:

1.   Once the faulty PMIC is identified, the platform may re-cycle the power by simultaneously removing

VIN_Bulk and VIN_Mgmt input supply and then re-applying VIN_Bulk and VIN_Mgmt input supplies.
This puts PMIC in configuration mode,

a. The BIOS reads PMIC error log registers to determine ‘bad’ PMIC. The BIOS also has a prior

knowledge of a faulty PMIC.

2.   BIOS performs following steps to the faulty PMIC.

a. Write R32 = 0x08 (Floats CAMP signal;  prevents PMIC interference)

b. Ensure R2F[2] = ‘0’.

3.   Broadcast VR Enable command to all PMICs.

JPGNetworksLLC

4.   All good PMIC executes Power On Sequence and floats the CAMP signal. The faulty PMIC is already

floating the CAMP signal and does not execute Power On Sequence.

5.   At this point, BIOS sees CAMP signal is pulled High and moves to the next operation.

6.   By the above process, the faulty PMIC is mapped out of the memory system in a secure state and it does not
interfere with platform operation. The good PMICs allow server system to power up normally and operate in
a secure state.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 102

3

Registers Space

3.1   Register Attribute Definition

All volatile registers have Base Attributes as defined in Table 89. Some register attributes are further modified with
Attribute Modifiers, as defined in Table 90.

Table 89 — Register Base Attributes

Attribute

Abbreviation

Description

Read Only

Read/Write

RO

RW

Write Only W

Reserved

RV

This bit can be read by software. Writes have no effect.

This bit can be read or written by host.

This bit can only be written by host. Read from this bit returns ‘0’.

This bit is reserved for future expansion and its value must not be
modified by host. The bit will return ‘0’ when read. Write has no effect.

Abbreviation

Attribute

Write ‘1’
Only

Protected

Persistent

1O

P

E

This bit can only be set (i.e., write ‘1’) but not reset (i.e., write ‘0’). Write
‘0’ has no effect.

This bit is protected by the password registers. This bit cannot be written
to unless the password code has been written into the password registers.

Description

Table 90 — Register Attribute Modifier

JPGNetworksLLC

This bit is persistent during power cycle.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

3.2   Register Map Breakdown

JEDEC Standard No. 301-1A.02
Page 103

Register Range
0x00 - 0x3F

Region
Host Region

0x40 - 0x6F

DIMM Vendor
Region

Table 91 — Register Map Breakdown

Comments

Host Accessible Registers
DIMM Vendor Registers - Non Volatile Memory
Allows DIMM vendors to program the PMIC for a given DRAM/DIMM
vendor designs.
These are password protected registers and password is selected by
DIMM vendor. Under normal operation, these registers are not used by
any host.
These registers require password for read access. Access to these
registers without correct password will return all data as ‘0’.
These registers require complete power cycle before it takes in effect.
Changing these registers under normal operation is considered an illegal
operation.
Vendor Specific Registers - Non Volatile Memory
These are vendor specific password protected registers. Under normal
operation these registers are not used by any host.
These registers require password for read access. Access to these
registers without correct password will return all data as ‘0’.

0x70 - 0xFF

Vendor Specific
Region

JPGNetworksLLC

3.3.1   Steps to Access DIMM Vendor Region Registers

The steps to access the DIMM vendor registers are as following:

1.   Write to register Table 144, “Register 0x37” = 8 bit password LSB code.

2.   Write to register Table 145, “Register 0x38” = 8 bit password MSB code.

3.3   Register Memory Protection

The PMIC DIMM vendors registers (0x40 - 0x6F) are password protected registers. Both Read and Write access to
DIMM vendor registers are blocked unless it is unlocked by providing the correct password. The default password for
DIMM vendor registers is 0x9473. The PMIC offers DIMM vendors to select their own password for DIMM vendor
registers.

3.   Write to register Table 146, “Register 0x39” = 0x40.

4.   Perform Read operations to DIMM vendor registers as desired.

5.   Write to register Table 146, “Register 0x39” = 0x00.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 104

3.3.2   Steps to Change DIMM Vendor Region Password

By default, the DIMM vendor region register password is 0x9473. The steps to change the password from default
password are as following:

1.   Write to register Table 144, “Register 0x37” = 0x73.

2.   Write to register Table 145, “Register 0x38” = 0x94.

3.   Write to register Table 146, “Register 0x39” = 0x40.

4.   Write to register Table 144, “Register 0x37” = New 8 bit password LSB code as desired by DIMM vendor.

5.   Write to register Table 145, “Register 0x38” = New 8 bit password MSB code as desired by DIMM vendor.

6.   Write to register Table 146, “Register 0x39” = 0x80.

7.   Wait 200 ms.

8.   Write to register Table 146, “Register 0x39” = 0x00.

9.   Power cycle the PMIC. (Remove VIN_Bulk and VIN_Mgmt supply from the PMIC. The new password is in

effect after the power cycle.

To change the password again from this point on, repeat steps 1 to 8 but note that in steps 1 and 2 current password is
required.

3.3.3   Steps to Burn or Program DIMM Vendor Region Registers

The steps to burn or to program the DIMM vendor registers are as following:

1.   Write to register Table 144, “Register 0x37” = 8 bit password LSB code.

2.   Write to register Table 145, “Register 0x38” = 8 bit password MSB code.

3.   Write to register Table 146, “Register 0x39” = 0x40.

JPGNetworksLLC

4.   Programming DIMM vendor registers are done at block level. Block 40 addresses: 0x40 - 0x4F; Block 50
addresses: 0x50 - 0x5F; Block 60 addresses: 0x60 - 0x6F. Perform write operation to each block as desired.

5.   Burn each block one at a time: Block 40 addresses: Write register Table 146, “Register 0x39” = 0x81. Block
50  addresses:  Write  register  Table 146,  “Register  0x39”  =  0x82.  Block  60  addresses:  Write  register
Table 146, “Register 0x39” = 0x85.

7.      To  check  if  programming  is  complete:  Perform  read  from  register  Table 146,  “Register  0x39”. The  code

0x5A indicates it is complete. It takes 200 ms per page to program.

6.   Wait time 200 ms.

8.   To verify if programming is done correctly: Perform read operation from appropriate block addresses.

9.   Write to register Table 146, “Register 0x39” = 0x00.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 105

3.3.4   Host Region Register Map

Table 92 — Register Color Coding Scheme

Region

Register Range

Restriction

Host Region + DIMM
Vendor Region + Vendor
specific Region

Table 111, “Register 0x15” to Table 137, “Register 0x2F”
Table 140, “Register 0x32” [7,5:0],
Table 143, “Register 0x35”
Table 152, “Register 0x40” to Register 0x6F
Register 0x70 to Register 0xFF

Host Region

Table 122, “Register 0x20” to
Table 135, “Register 0x2D”

Register Modification is
NOT allowed in write
protect mode

Registers are copied from
DIMM Vendor Region
Setting at power on

.

Register
0x00 to 0x03

Table 94, “Register 0x04”

Table 95, “Register 0x05”

Table 96, “Register 0x06”

Table 97, “Register 0x07”

Table 98, “Register 0x08”

Table 99, “Register 0x09”

RO

Table 100, “Register 0x0A”

RO

Table 101, “Register 0x0B”

RO

Table 102, “Register 0x0C”

RO

RO

ROE

ROE

ROE

ROE

Description

Table 93 — Host Region - Register Map

Attribute
RV

JPGNetworksLLC

R00 [7:0] to R03 [7:0] - Reserved
R04 [7] Global Error Count
R04 [6:4] Global Error History Log
R04 [3:0] Reserved
R05 [7] Reserved
R05 [6:3] Power On Reset - SWA, SWB, SWC and SWD Power Not
Good
R05 [2:0] Power On Reset - High Level Status Code
R06 [7:4] Power On Reset - SWA, SWB, SWC and SWD Under Voltage
Lockout
R06 [3:0] Power On Reset - SWA, SWB, SWC and SWD Over Voltage
R07 [7:0] Reserved
R08 [7] VIN_Bulk Input Power Good Status
R08[6] Critical Temperature Shutdown Status
R08 [5:2] SWA, SWB, SWC, SWD Output Power Good Status
R08 [1] VIN_Mgmt Input Over Voltage Status
R08 [0] VIN_Bulk Input Over Voltage Status
R09 [7] PMIC High Temperature Warning Status
R09 [6] VBias Power Good Status
R09 [5] VOUT_1.8V Output Power Good Status
R09 [4] VIN_Mgmt to VIN_Bulk Input Supply Switchover Status
R09 [3:0] SWA, SWB, SWC and SWD High Output Current
Consumption Warning Status
R0A [7:4] SWA, SWB, SWC, SWD Output Over Voltage Status
R0A [3] PEC Error Status
R0A [2] Parity Error Status
R0A [1] IBI Status
R0A [0] Reserved
R0B [7:4] SWA, SWB, SWC and SWD Output Current Limiter Warning
Status
R0B [3:0] SWA, SWB, SWC and SWD Output Under Voltage Lockout
Status
R0C [7:0] SWA Output Current or Power or Total Output Power
Measurement

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 106

Table 93 — Host Region - Register Map (cont’d)

Register

Attribute

Description

Table 103, “Register 0x0D”

RO

Table 104, “Register 0x0E”

Table 105, “Register 0x0F”

RO

RO

Table 106, “Register 0x10”

1O

Table 107, “Register 0x11”

1O

Table 108, “Register 0x12”

Table 109, “Register 0x13”

Table 110, “Register 0x14”

Table 111, “Register 0x15”

1O

1O

JPGNetworksLLC

R0D [7:6] Reserved
R0D [5:0] SWB Output Current or Power Measurement
R0E [7:6] Reserved
R0E [5:0] SWC Output Current or Power Measurement
R0F [7:6] Reserved
R0F [5:0] SWD Output Current or Power Measurement
R10 [7] Clear VIN_Bulk Input Power Good Status
R10 [6] Reserved
R10 [5:2] Clear SWA, SWB, SWC and SWD Output Power Good Status
R10 [1] Clear VIN_Mgmt Input Over Voltage Status
R10 [0] Clear VIN_Bulk Input Over Voltage Status
R11 [7] Clear PMIC High Temperature Warning Status
R11 [6] Clear VBias Power Good Status
R11 [5] Clear VOUT_1.8V Output Power Good Status
R11 [4] Clear VIN_Mgmt to VIN_Bulk Input Supply Switchover Status
R11 [3:0] Clear SWA, SWB, SWC and SWD High Output Current
Consumption Warning Status
R12 [7:4] Clear SWA, SWB, SWC, SWD Output Over Voltage Status
R12 [3] Clear PEC Error
R12 [2] Clear Parity Error
R12 [1:0] Reserved
R13 [7:4] Clear SWA, SWB, SWC and SWD Output Current Limiter
Warning Status
R13 [3:0] Clear SWA, SWB, SWC and SWD Output Under Voltage
Lockout Status
R14 [7:5] Reserved
R14 [4] Clear VIN_Mgmt Power Good Status in Switchover Mode
R14 [3] Clear VBias Output or VIN_Bulk InputUnder Voltage Lockout
Status
R14 [2] Clear VOUT_1.0V Output Power Good Status
R14 [1] Reserved
R14 [0] Clear Global Status
R15 [7] Mask VIN_Bulk Input Power Good Status
R15 [6] Reserved
R15 [5:2] Mask SWA, SWB,SWC and SWD Output Power Good Status
R15 [1] Mask VIN_Mgmt Input Over Voltage Status
R15 [0] Mask VIN_Bulk Input Over Voltage Status
R16 [7] Mask PMIC High Temperature Warning Status
R16 [6] Mask VBias Power Good Status
R16 [5] Mask VOUT_1.8V Output Power Good Status
R16 [4] Mask VIN_Mgmt to VIN_Bulk Input Supply Switchover Status
R16 [3:0] Mask SWA, SWB, SWC and SWD High Output Current
Consumption Warning Status
R17 [7:4] Mask SWA, SWB, SWC, SWD Output Over Voltage
R17 [3] Mask PEC Error Status
R17 [2] Mask Parity Error Status
R17 [1:0] Reserved
R18 [7:4] Mask SWA, SWB, SWC and SWD Output Current Limiter
Warning Status
R18 [3:0] Mask SWA, SWB, SWC and SWD Output Under Voltage
Lockout Status

RW

1O

Table 112, “Register 0x16”

RW

Table 113, “Register 0x17”

RW

Table 114, “Register 0x18”

RW

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

Table 93 — Host Region - Register Map (cont’d)

Register

Attribute

Description

JEDEC Standard No. 301-1A.02
Page 107

Table 115, “Register 0x19”

RW

Table 116, “Register 0x1A”

RW

RW

RW

RW

RW

JPGNetworksLLC

R19 [7:5] Reserved
R19 [4] Mask VIN_Mgmt Power Good Status Switchover Mode
R19 [3] Mask Vbias Output or VIN_Bulk InputUnder Voltage Lockout
Status
R19 [2] Mask VOUT_1.0V Output Power Good Status
R19 [1:0] Reserved
R1A [7:5] VIN_Bulk Input Power Good Threshold Voltage
R1A [4] Reserved
R1A [3] VBias Power Good Threshold Voltage
R1A [2] VOUT_1.8 V Power Good Threshold Voltage
R1A [1] Output Power Measurement Select
R1A [0] VOUT_1.0 V Power Good Threshold Voltage
R1B [7] VIN_Bulk Input Over Voltage Threshold
R1B [6] Current or Power Meter Select
R1B [5] VIN_Mgmt Input Over Voltage Threshold
R1B [4] Global Mask Control for PWR_GOOD Output Pin
R1B [3] GSI_n Pin Enable
R1B [2:0] PMIC High Temperature Warning Threshold
R1C [7:2] SWA Output High Current Threshold
R1C [1:0] Reserved
R1D [7:2] SWB Output High Current Threshold
R1D [1:0] Reserved
R1E [7:2] SWC Output High Current Threshold
R1E [1:0] Reserved
R1F [7:2] SWD Output High Current Threshold
R1F [1:0] Reserved
R20 [7:6] SWA Output Current Limiter Warning Threshold
R20 [5:4] SWB Output Current Limiter Warning Threshold
R20 [3:2] SWC Output Current Limiter Warning Threshold
R20 [1:0] SWD Output Current Limiter Warning Threshold
R21 [7:1] SWA Voltage Setting
R21 [0] SWA Power Good Low Side Threshold
R22 [7:6] SWA Power Good High Side Threshold
R22 [5:4] SWA Over Voltage Threshold
R22 [3:2] SWA Under Voltage Lockout Threshold
R22 [1:0] SWA Soft Stop Time
R23 [7:1] SWB Voltage Setting
R23 [0] SWB Power Good Low Side Threshold
R24 [7:6] SWB Power Good High Side Threshold
R24 [5:4] SWB Over Voltage Threshold
R24 [3:2] SWB Under Voltage Lockout Threshold
R24 [1:0] SWB Soft Stop Time
R25 [7:1] SWC Voltage Setting
R25 [0] SWC Power Good Low Side Threshold
R26 [7:6] SWC Power Good High Side Threshold
R26 [5:4] SWC Over Voltage Threshold
R26 [3:2] SWC Under Voltage Lockout Threshold
R26 [1:0] SWC Soft Stop Time
R27 [7:1] SWD Voltage Setting
R27 [0] SWD Power Good Low Side Threshold

RW

RW

RW

RW

Table 117, “Register 0x1B”

Table 118, “Register 0x1C”

Table 119, “Register 0x1D”

Table 120, “Register 0x1E”

Table 121, “Register 0x1F”

Table 122, “Register 0x20”

Table 123, “Register 0x21”

Table 124, “Register 0x22”

Table 125, “Register 0x23”

RW

Table 126, “Register 0x24”

RW

Table 127, “Register 0x25”

RW

Table 128, “Register 0x26”

RW

Table 129, “Register 0x27”

RW

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 108

Table 93 — Host Region - Register Map (cont’d)

Register

Attribute

Description

Table 130, “Register 0x28”

RW

Table 131, “Register 0x29”

RW

Table 132, “Register 0x2A”

RW

Table 133, “Register 0x2B”

RW

Table 134, “Register 0x2C”

Table 135, “Register 0x2D”

Table 136, “Register 0x2E”

Table 137, “Register 0x2F”

Table 138, “Register 0x30”

Table 139, “Register 0x31”

Table 140, “Register 0x32” RW, RO

Table 141, “Register 0x33”

RO

Table 142, “Register 0x34” RW, RO

RW

RW

RW

JPGNetworksLLC

R28 [7:6] SWD Power Good High Side Threshold
R28 [5:4] SWD Over Voltage Threshold
R28 [3:2] SWD Under Voltage Lockout Threshold
R28 [1:0] SWD Soft Stop Time
R29 [7:6] SWA Mode Select
R29 [5:4] SWA Switching Frequency
R29 [3:2] SWB Mode Select
R29 [1:0] SWB Switching Frequency
R2A [7:6] SWC Mode Select
R2A [5:4] SWC Switching Frequency
R2A [3:2] SWD Mode Select
R2A [1:0] SWD Switching Frequency
R2B [7:6] VOUT_1.8V LDO Setting
R2B [5:3] Voltage Range Selection for SWA, SWB and SWC
R2B [2:1] VOUT_1.0V LDO Setting
R2B [0] Voltage Range Selection for SWD
R2C [7:5] SWA Soft Start Time
R2C [4] Reserved
R2C [3:1] SWB Soft Start Time
R2C [0] Reserved
R2D [7:5] SWC Soft Start Time
R2D [4] Reserved
R2D [3:1] SWD Soft Start Time
R2D [0] Reserved
R2E [7:3] Reserved
R2E [2:0] PMIC Shutdown temperature threshold
R2F [7] VIN_Mgmt Input Supply Switchover Threshold Voltage
R2F [6:3] SWA, SWB, SWC and SWD Enable
R2F [2] Write Protect Function Control
R2F [1:0] Mask Bits Register Control
R30 [7] ADC Enable
R30 [6:3] ADC Select
R30 [2] Reserved
R30 [1:0] ADC Register Update Frequency
R31 [7:0] ADC Read Out
R32 [7] VR Enable
R32 [6] Management Interface Selection
R32 [5] Execute VR Enable Control
R32 [4] Execute CAMP Fail_n Function Control
R32 [3] PMIC CAMP Power Good Output Signal Control
R32 [2:0] Reserved
R33 [7:5] Temperature Measurement
R33 [4] VIN_Mgmt Power Good Status in Switchover Mode Only
R33 [3] VBias Output or VIN_Bulk Input Under Voltage Lockout Status
R33 [2] VOUT_1.0V Output Power Good Status
R33 [1:0] Reserved
R34 [7] PEC Enable
R34 [6] IBI Enable
R34 [5] Parity Disable
R34 [4] Reserved
R34 [3:1] HID_CODE
R34 [0] Reserved

RW

RW

RO

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

Table 93 — Host Region - Register Map (cont’d)

Register

Attribute

Description

JEDEC Standard No. 301-1A.02
Page 109

Table 143, “Register 0x35”

RW

0x36
Table 144, “Register 0x37”
Table 145, “Register 0x38”
Table 146, “Register 0x39”

RV
WO
WO
RW

Table 147, “Register 0x3A”

RW

Table 148, “Register 0x3B”

Table 149, “Register 0x3C”
Table 150, “Register 0x3D”
0x3E to 0x3F

R35 [7] Error Injection Enable
R35 [6:4] Output Rail Selection
R35 [3] Over and Under Voltage Select
R35 [2:0] Misc. Error Injection Type
R36 [7:0] Reserved
R37 [7:0] Password Lower Byte 0
R38 [7:0] Password Upper Byte 1
R39 [7:0] Command Codes
R3A [7] Reserved
R3A [6] Default Read Address Pointer Enable
R3A [5:4] Default Read Address Pointer Selection
R3A [3:2] Burst Length for Default Read Address Pointer Mode in PEC
Enabled Mode
R3A [1:0] Reserved
R3B [7:6] Reserved
R3B [5:4] Major Revision ID
R3B [3:1] Minor Revision ID
R3B [0] PMIC Current Capability
R3C [7:0] VENDOR_ID_BYTE0
R3D [7:0] VENDOR_ID_BYTE1
R3E [7:0] to 0x3F Reserved

ROE

ROE
ROE
RV

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 110

3.3.5   Host Region Registers

3.3.5.1  Status Registers

The PMIC offers status registers that are grouped into four different categories.

1.   Global History of Error Log Register (Table 94, “Register 0x04” [7:4])

2.   Error Log Registers (Table 95, “Register 0x05” [6:0], Table 96, “Register 0x06”[7:0], Table 97, “Register

0x07” [7:0]; Table 97, “Register 0x07” [7:0] is currently defined as Reserved)

3.      Real  time  Status  Registers  (Table 98,  “Register  0x08”  [7:0],  Table 99,  “Register  0x09”  [7:0],  Table 100,

“Register 0x0A” [7:1], Table 101, “Register 0x0B” [7:0], Table 141, “Register 0x33” [4:2])

4.   Periodic Status Registers (Table 102, “Register 0x0C” [7:0], Table 103, “Register 0x0D” [5:0], Table 104,

“Register 0x0E” [5:0], Table 105, “Register 0x0F” [5:0], Table 141, “Register 0x33” [7:5])

Global History of Error Log Registers (Table 94, “Register 0x04” [7:4]) - This register records the PMIC state at each
abnormal power down cycle. This register reports the cumulative error of each abnormal power down sequence. The
PMIC writes this register on its own when it internally generates VR Disable command on its own due to failure. The
host  can  erase  this  register  in  MTP  memory  and  clear  the  status  register  by  writing  the  code  0x74  in  Table 146,
“Register 0x39”.

Error Log Registers (Table 95, “Register 0x05” [6:0], Table 96, “Register 0x06” [7:0] to Table 97, “Register 0x07”
[7:0]) - These registers record the PMIC state at each power down sequence. The PMIC may report abnormal power
down  sequence  or  normal  power  down  sequence.  The  PMIC  writes  this  register  on  its  own  when  it  internally
generates VR Disable command on its own due to failure. These registers are updated at power down cycle, if update
is  needed  by  the  PMIC  on  its  own. The  host  can  clear  the  status  register  by  writing  the  code  0x74  in  Table 146,
“Register 0x39”. See Figure 33 for illustration. The top waveform illustrates how PMIC captures Error Log Registers
(R05 to R07) when there is a fault or a no fault and how PMIC reports error log registers when PMIC goes through
power cycle. The bottom waveform illustrates same as top waveform with one exception. It shows no fault condition
when CAMP is asserted to turn off switch regulator outputs with power down sequence.

Note that word Power Cycle is used  interchangeably with Power  Down Cycle  as  illustrated in both figures and it
means  both VIN_Bulk  and VIN_Mgmt  input  supplies  are  removed  and  re-applied.  Power  Down  Sequence  means
execution of Power Off Sequence configuration registers (Table 169, “Register 0x58” to Table 172, “Register 0x5B”.

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

3.3.5.1 Status Registers (cont’d)

JEDEC Standard No. 301-1A.02
Page 111

Figure 33 — Error Log (R05 to R07) Registers Behavior with Power Cycle

JPGNetworksLLC

Real Time Status Registers (Table 98, “Register 0x08” [7:0], Table 99, “Register 0x09” [7:0], Table 100, “Register
0x0A” [7:1], to Table 101, “Register 0x0B” [7:0], Table 141, “Register 0x33” [4:2]): These registers are updated to
‘1’ any time based on any event that occurs. The status registers will remain at ‘1’ even if the failing condition is no
longer  present  until  the  Clear  Register  command  is  received  by  the  PMIC.  Note  that  any  switch  regulator  related
status registers are only applicable after VR Enable command is registered by the PMIC. The PMIC updates switch
regulators related status registers after VR Enable command is registered within tPMIC_PWR_GOOD_OUT time if
there  is  any  issue  and  host  shall  check  these  status  registers  after  tPMIC_PWR_GOOD_OUT  time.  The  PMIC
updates  these  status  registers  if  there  is  any  event  related  to  switch  regulators  in  future.  The  GSI_n  interrupt  or
PWR_GOOD  interrupt  may  be  generated  by  the  PMIC  at  the  same  time,  depending  on  the  type  of  event.  The
interrupts  are  only  generated  if  they  are  not  masked. The  status  registers  Table 98,  “Register  0x08”  [7],  Table 99,
“Register 0x09” [5], and Table 141, “Register 0x33” [2] is only valid once valid VIN_Bulk and VIN_Mgmt input
supply  is  valid  at  the  PMIC  input  pin.  The  remaining  status  registers  are  valid  after  VR  Enable  command  is
registered.

Periodic Status Registers (Table 102, “Register 0x0C” [7:0], Table 103, “Register 0x0D” [5:0], Table 104, “Register
0x0E”  [5:0],  Table 105,  “Register  0x0F”  [5:0],  Table 141,  “Register  0x33”  [7:5])  -  These  registers  are  updated
periodically. These registers are only valid after VR Enable command is registered.

All  Read  Only  (RO)  registers  except  for  registers  Table 102,  “Register  0x0C”  [7:0],  Table 103,  “Register  0x0D”
[5:0], Table 104, “Register 0x0E” [5:0] and Table 105, “Register 0x0F” [5:0] are one time latched registers. In other
words, once PMIC sets those register flag, the host must explicitly clear those registers appropriately. The PMIC does
not automatically update the registers on its own even if the event that triggered the status is no longer present. The
registers Table 102, “Register 0x0C” [7:0], Table 103, “Register 0x0D” [5:0], Table 104, “Register 0x0E” [5:0], and
Table 105, “Register 0x0F” [5:0] are dynamically updated by the PMIC at certain frequency and they represent the
status at that point.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 112

3.3.5.1 Status Registers (cont’d)

R04

Table 94 — Register 0x04

Bits

Attribute Default

Description1,2

7

6

5

4

ROE

ROE

ROE

ROE

3:0

RV

0

0

0

R04 [7]: GLOBAL_ERROR_COUNT
Global Error Count Since Last Erase Operation3
0 = No Error or Only 1 Error since last Erase operation
1 = > 1 Error Count since last Erase operation
R04 [6]: GLOBAL_ERROR_LOG_BUCK_OV_OR_UV
Global Error Log History for Buck Regulator Output Over or Under Voltage4
0 = No Error Occurred
1 = Error Occurred
R04 [5]: GLOBAL_ERROR_LOG_VIN_BULK_OVER_VOLTAGE
Global Error Log History for VIN_Bulk Over Voltage4
0 = No Error Occurred
1 = Error Occurred
R04 [4]: GLOBAL_ERROR_LOG_CRITICAL_TEMPERATURE
Global Error Log History for Critical Temperature4
0 = No Error Occurred
1 = Error Occurred
R04 [3:0]: Reserved

JPGNetworksLLC

0

0

NOTE 1  The PMIC always attempts to write this register into its non-volatile memory. However, it may not be guaranteed depending on

how fast the host may shut off the input power to the PMIC. The PMIC needs minimum of 5.0 V for VIN_Bulk voltage and 200 ms
duration from PWR_GOOD signal assertion to guarantee the write operation into non-volatile memory.

NOTE 2  Host must explicitly perform Erase operation to erase this entire register Table 94, “Register 0x04” [7:0] via Table 146, “Register

0x39”. The PMIC needs minimum of 200 ms for Erase operation.

NOTE 3  PMIC counts the error since last erase operation and if more than one error occurs, it sets this bit to ‘1’. Host must explicitly

perform Erase operation to erase this entire register Table 94, “Register 0x04” [7:0].

NOTE 4  PMIC sets the bit when error occurs.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 113

3.3.5.1 Status Registers (cont’d)

R05

Table 95 — Register 0x05

Bits

Attribute Default

Description1,2

7

6

5

4

3

RV

ROE

ROE

ROE

ROE

2:0

ROE

0

0

0

0

R05 [7]: Reserved
R05 [6]: SWA_POWER_GOOD
PMIC Power On - SWA Power Not Good3
0 = Normal Power On
1 = SWA Power Not Good
R05 [5]: SWB_POWER_GOOD
PMIC Power On - SWB Power Not Good3,4
0 = Normal Power On
1 = SWB Power Not Good
R05 [4]: SWC_POWER_GOOD
PMIC Power On - SWC Power Not Good3
0 = Normal Power On
1 = SWC Power Not Good
R05 [3]: SWD_POWER_GOOD
PMIC Power On - SWD Power Not Good3
0 = Normal Power On
1 = SWD Power Not Good
R05 [2:0]: PMIC_ERROR_LOG
PMIC Power On - High Level Status Bit to Previous Last Known Power
Cycle
000 = Normal Power On
001 = Reserved
010 = Buck Regulator Output Over or Under Voltage5
011 = Critical Temperature
100 = VIN_Bulk Input Over Voltage
101 = Reserved
110 = Reserved
111 = Reserved

JPGNetworksLLC

0

0

NOTE 1  The PMIC always attempts to write this register into its non-volatile memory. However, it may not be guaranteed depending on

how fast the host may shut off the input power to the PMIC. The PMIC needs minimum of 5.0 V for VIN_Bulk voltage and 200 ms
duration from PWR_GOOD signal assertion to guarantee the write operation into non-volatile memory.

NOTE 2  This entire register status reflects previous power down cycle of the PMIC and is updated by the PMIC on its own at each power
cycle, if update is needed. Because this register is updated only if there is an update needed, there is no NVM life time impact. This
register is cleared when host issues the erase command via Table 146, “Register 0x39”. The PMIC needs minimum of 200 ms for
Erase operation.

NOTE 3  This register is set only if PMIC generates internal VR Disable command due to fault condition.

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 5  This code is a logical OR function of Table 96, “Register 0x06” [7:0] register bits.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 114

3.3.5.1 Status Registers (cont’d)

R06

Bits

Attribute Default

Description1,2

Table 96 — Register 0x06

7

6

5

4

3

2

1

0

ROE

ROE

ROE

ROE

ROE

ROE

ROE

0

0

0

0

R06 [7]: SWA_UNDER_VOLTAGE_LOCKOUT
PMIC Power On - SWA Under Voltage Lockout
0 = Normal Power On
1 = SWA Under Voltage Lockout
R06 [6]: SWB_UNDER_VOLTAGE_LOCKOUT
PMIC Power On - SWB Under Voltage Lockout3
0 = Normal Power On
1 = SWB Under Voltage Lockout
R06 [5]: SWC_UNDER_VOLTAGE_LOCKOUT
PMIC Power On - SWC Under Voltage Lockout
0 = Normal Power On
1 = SWC Under Voltage Lockout
R06 [4]: SWD_UNDER_VOLTAGE_LOCKOUT
PMIC Power On - SWD Under Voltage Lockout
0 = Normal Power On
1 = SWD Under Voltage Lockout
R06 [3]: SWA_OVER_VOLTAGE
PMIC Power On - SWA Over Voltage
0 = Normal Power On
1 = SWA Over Voltage
R06 [2]: SWB_OVER_VOLTAGE
PMIC Power On - SWB Over Voltage3
0 = Normal Power On
1 = SWB Over Voltage
R06 [1]: SWC_OVER_VOLTAGE
PMIC Power On - SWC Over Voltage
0 = Normal Power On
1 = SWC Over Voltage
R06 [0]: SWD_OVER_VOLTAGE
PMIC Power On - SWD Over Voltage
0 = Normal Power On
1 = SWD Over Voltage

JPGNetworksLLC

0

0

0

ROE

0

NOTE 1  The PMIC always attempts to write this register into its non-volatile memory. However, it may not be guaranteed depending on how

fast the host may shut off the input power to the PMIC. The PMIC needs minimum of 5.0 V for VIN_Bulk voltage and 200 ms
duration from PWR_GOOD signal assertion to guarantee the write operation into non-volatile memory.

NOTE 2  This entire register status reflects previous power down cycle of the PMIC and is updated by the PMIC on its own at each power

cycle, if update is needed. Because this register is updated only if there is an update needed, there is no NVM life time impact. This
register is cleared when host issues the erase command via Table 146, “Register 0x39”. The PMIC needs minimum of 200 ms for
Erase operation.

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 115

3.3.5.1 Status Registers (cont’d)

Table 97 — Register 0x07

R07

Attribute Default

ROE

0

R07 [7:0]: Reserved

Bits

7:0

Description1,2

NOTE 1  The PMIC always attempts to write this register into its non-volatile memory. However, it may not be guaranteed depending on

how fast the host may shut off the input power to the PMIC. The PMIC needs minimum of 5.0V for VIN_Bulk voltage and 200 ms
duration from PWR_GOOD signal assertion to guarantee the write operation into non-volatile memory.

NOTE 2  This entire register status reflects previous power down cycle of the PMIC and is updated by the PMIC on its own at each power
cycle, if update is needed. Because this register is updated only if there is an update needed, there is no NVM life time impact. This
register is cleared when host issues the erase command via Table 146, “Register 0x39”. The PMIC needs minimum of 200 ms for
Erase operation.

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 116

3.3.5.1 Status Registers (cont’d)

R08

Table 98 — Register 0x08

Bits

Attribute Default

Description

7

6

5

4

3

2

1

0

RO

RO

RO

RO

RO

RO

RO

0

0

0

0

R08 [7]: VIN_BULK_INPUT_POWER_GOOD_STATUS
VIN_Bulk Input Power Good Status1
0 = Power Good
1 = Power Not Good
R08 [6]: CRITICAL_TEMP_SHUTDOWN_STATUS
Critical Temperature Shutdown Status2
0 = No Critical Temperature Shutdown
1 = Critical Temperature Shutdown
R08 [5]: SWA_OUTPUT_POWER_GOOD_STATUS
Switch Node A Output Power Good Status3
0 = Power Good
1 = Power Not Good
R08 [4]: SWB_OUTPUT_POWER_GOOD_STATUS
Switch Node B Output Power Good Status4
0 = Power Good
1 = Power Not Good
R08 [3]: SWC_OUTPUT_POWER_GOOD_STATUS
Switch Node C Output Power Good Status5
0 = Power Good
1 = Power Not Good
R08 [2]: SWD_OUTPUT_POWER_GOOD_STATUS
Switch Node D Output Power Good Status6
0 = Power Good
1 = Power Not Good
R08 [1]: VIN_MGMT_INPUT_OVER_VOLTAGE_STATUS
VIN_Mgmt Input Supply Over Voltage Status7
0 = No Over Voltage
1 = Over Voltage
R08 [0]: VIN_BULK_INPUT_OVER_VOLTAGE_STATUS
VIN_Bulk Input Supply Over Voltage Status8
0 = No Over Voltage
1 = Over Voltage

JPGNetworksLLC

0

0

0

RO

0

NOTE 1  This register is set when VIN_Bulk input goes below the threshold setting in register Table 116, “Register 0x1A” [7:5].
NOTE 2  This register is set when PMIC temperature goes above the threshold setting in register Table 136, “Register 0x2E” [2:0].
NOTE 3  This register is set when SWA output voltage goes either below the threshold setting in register Table 123, “Register 0x21”[1:0] or

above the threshold setting in register Table 124, “Register 0x22” [7:6].

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’. This register is set when SWB output goes either below the threshold
setting in register Table 125, “Register 0x23”[1:0] or above the threshold setting in register Table 126, “Register 0x24” [7:6].

NOTE 5  This register is set when SWC output goes either below the threshold setting in register Table 127, “Register 0x25”[1:0] or above

the threshold setting in register Table 128, “Register 0x26” [7:6].

NOTE 6  This register is set when SWD output goes either below the threshold setting in register Table 129, “Register 0x27”[1:0] or above

the threshold setting in register Table 130, “Register 0x28” [7:6].

NOTE 7  This register is set when VIN_Mgmt input voltage goes above the threshold setting in register Table 117, “Register 0x1B” [5].
NOTE 8  This register is set when VIN_Bulk input voltage goes above the threshold setting in register Table 117, “Register 0x1B” [7].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 117

3.3.5.1 Status Registers (cont’d)

R09

Table 99 — Register 0x09

Bits

Attribute Default

Description

7

6

5

4

3

2

1

0

RO

RO

RO

RO

RO

RO

RO

RO

0

0

0

0

0

0

0

0

R09 [7]: PMIC_HIGH_TEMP_WARNING_STATUS
PMIC High Temperature Warning Status1
0 = Temperature Below the Warning Threshold
1 = Temperature Exceeded the Warning Threshold
R09 [6]: VBIAS_POWER_GOOD_STATUS
VBias Power Good Status2
0 = Power Good
1 = Power Not Good
R09 [5]: VOUT_1.8V_OUTPUT_POWER_GOOD_STATUS
VOUT_1.8V LDO Output Power Good Status3
0 = Power Good
1 = Power Not Good
R09 [4]:
VIN_MGMT_TO_VIN_BULK_INPUT_SUPPLY_SWITCHOVER_STATUS
VIN_Mgmt to VIN_Bulk Input Supply Automatic Switchover Status4
0 = VIN_Mgmt Input Supply is Present
1 = VIN_Mgmt Input Supply is Removed (i.e., using VIN_Bulk Input Supply)
R09 [3]:
SWA_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING_STATUS
Switch Node A High Output Current Consumption Warning Status5
0 = No High Current Consumption Warning
1 = High Current Consumption Warning
R09 [2]:
SWB_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING_STATUS
Switch Node B High Output Current Consumption Warning Status6,7
0 = No High Current Consumption Warning
1 = High Current Consumption Warning
R09 [1]:
SWC_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING_STATUS
Switch Node C High Output Current Consumption Warning Status8
0 = No High Current Consumption Warning
1 = High Current Consumption Warning
R09 [0]:
SWD_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING_STATUS
Switch Node D High Output Current Consumption Warning Status9
0 = No High Current Consumption Warning
1 = High Current Consumption Warning

JPGNetworksLLC

NOTE 1  This register is set when PMIC temperature goes above the threshold setting in Table 117, “Register 0x1B” [2:0].

NOTE 2  This register is set when VBias voltage goes below the threshold setting in register Table 116, “Register 0x1A” [3].

NOTE 3  This register is set when VOUT_1.8V output goes below the threshold setting in register Table 116, “Register 0x1A” [2].

NOTE 4  This register is set when VIN_Mgmt input supply goes below the threshold setting in register Table 137, “Register 0x2F” [7].

NOTE 5  This register is set when SWA output current consumption goes above the threshold setting in Table 118, “Register 0x1C” [7:2].

NOTE 6  This register is set when SWB output current consumption goes above the threshold setting in Table 119, “Register 0x1D” [7:2]. If

Table 166, “Register 0x4F” [0] = ‘1’, the setting in Table 119, “Register 0x1D” [7:2] must be identical as Table 118, “Register 0x1C”
[7:2].

NOTE 7  This register is applicable regardless of the setting in Table 166, “Register 0x4F” [0]

NOTE 8  This register is set when SWC output current consumption goes above the threshold setting in Table 120, “Register 0x1E” [7:2].

NOTE 9  This register is set when SWD output current consumption goes above the threshold setting in Table 121, “Register 0x1F” [7:2].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 118

3.3.5.1 Status Registers (cont’d)

R0A

Table 100 — Register 0x0A

Bits

Attribute Default

Description

7

6

5

4

3

2

1

0

RO

RO

RO

RO

RO

RO

RO

RV

0

0

0

0

R0A [7]: SWA_OUTPUT_OVER_VOLTAGE_STATUS
Switch Node A Output Over Voltage Status1
0 = No Over Voltage
1 = Over Voltage
R0A [6]: SWB_OUTPUT_OVER_VOLTAGE_STATUS
Switch Node B Output Over Voltage Status2
0 = No Over Voltage
1 = Over Voltage
R0A [5]: SWC_OUTPUT_OVER_VOLTAGE_STATUS
Switch Node C Output Over Voltage Status3
0 = No Over Voltage
1 = Over Voltage
R0A [4]: SWD_OUTPUT_OVER_VOLTAGE_STATUS
Switch Node D Output Over Voltage Status4
0 = No Over Voltage
1 = Over Voltage
R0A [3]: PEC_ERROR_STATUS
Packet Error Code Status5,6
0 = No PEC Error
1 = PEC Error
R0A [2]: PARITY_ERROR_STATUS
T Bit Parity Error Status6,7
0 = No Parity Error
1 = Parity Error
R0A [1]: IBI_AND_GLOBAL_STATUS
In Band Interrupt and Global Status8
0 = No Pending IBI or Outstanding Status
1 = Pending IBI or Outstanding Status
R0A [0]: Reserved

JPGNetworksLLC

0

0

0

0

NOTE 1  This register is set when SWA output voltage goes above the threshold setting in Table 124, “Register 0x22” [5:4].

NOTE 2  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’. This register is set when SWB output voltage goes above the threshold

setting in Table 126, “Register 0x24” [5:4]. If Table 166, “Register 0x4F” [0] = ‘1’, the setting in Table 126, “Register 0x24” [5:4]
must be identical to Table 124, “Register 0x22” [5:4].

NOTE 3  This register is set when SWC output voltage goes above the threshold setting in Table 128, “Register 0x26” [5:4]

NOTE 4  This register is set when SWD output voltage goes above the threshold setting in Table 130, “Register 0x28” [5:4]

NOTE 5  Applicable in I3C Basic Mode Only and if enabled in register Table 142, “Register 0x34” [7].

NOTE 6  This register is updated when PMIC device goes through bus reset as described in clause 2.10.15.
NOTE 7  Applicable in I3C Basic Mode and if enabled in register Table 142, “Register 0x34” [5]. Also applicable in I2C mode for supported

CCC.

NOTE 8  This register can be used as Global Status in addition to IBI status. When IBI function is enabled, this register is automatically

cleared when PMIC transmits IBI payload; however individual status registers still require an explicit clear command from host.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 119

3.3.5.1 Status Registers (cont’d)

R0B

Table 101 — Register 0x0B

Bits

Attribute Default

Description

0

4

0

5

0

6

0

7

RO

RO

RO

RO

R0B [7]: SWA_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Switch Node A Output Current Limiter Warning Status1
0 = No Current Limiter Event
1 = Current Limiter Event
R0B [6]: SWB_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Switch Node B Output Current Limiter Warning Status2
0 = No Current Limiter Event
1 = Current Limiter Event
R0B [5]: SWC_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Switch Node C Output Current Limiter Warning Status3
0 = No Current Limiter Event
1 = Current Limiter Event
R0B [4]: SWD_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Switch Node D Output Current Limiter Warning Status4
0 = No Current Limiter Event
1 = Current Limiter Event
R0B [3]: SWA_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Switch Node A Output Under Voltage Lockout Status5
0 = No Under Voltage Lockout
1 = Under Voltage Lockout
R0B [2]: SWB_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Switch Node B Output Under Voltage Lockout Status6
0 = No Under Voltage Lockout
1 = Under Voltage Lockout
R0B [1]: SWC_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Switch Node C Output Under Voltage Lockout Status7
0 = No Under Voltage Lockout
1 = Under Voltage Lockout
R0B [0]: SWD_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Switch Node D Output Under Voltage Lockout Status8
0 = No Under Voltage Lockout
1 = Under Voltage Lockout
NOTE 1  This register is set when SWA output current goes above the threshold setting in Table 122, “Register 0x20” [7:6].
NOTE 2  This register is applicable regardless of the setting in Table 166, “Register 0x4F” [0]. This register is set when SWB output current

JPGNetworksLLC

RO

RO

RO

RO

3

0

2

0

1

0

0

0

goes above the threshold setting in Table 123, “Register 0x21” [5:4]. If Table 166, “Register 0x4F” [0] = ‘1’, the setting in
Table 122, “Register 0x20” [5:4] must be identical as Table 122, “Register 0x20” [7:6].

NOTE 3  This register is set when SWC output current goes above the threshold setting in Table 122, “Register 0x20” [3:2].
NOTE 4  This register is set when SWD output current goes above the threshold setting in Table 122, “Register 0x20” [1:0].
NOTE 5  This register is set when SWA output voltage goes below the threshold setting in Table 122, “Register 0x20” [3:2].
NOTE 6  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’. This register is set when SWB output voltage goes below the threshold

setting in Table 126, “Register 0x24” [3:2]. If Table 166, “Register 0x4F” [0] = ‘1’, the setting in Table 126, “Register 0x24” [3:2]
must be identical as Table 124, “Register 0x22” [3:2].

NOTE 7  This register is set when SWC output voltage goes below the threshold setting in Table 128, “Register 0x26” [3:2].
NOTE 8  This register is set when SWD output voltage goes below the threshold setting in Table 130, “Register 0x28” [3:2].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 120

3.3.5.1 Status Registers (cont’d)

R0C

Bits

Attribute Default

Table 102 — Register 0x0C

Description1

7:0

RO

R0C [7:0]: SWA_OUTPUT_CURRENT_POWER_MEASUREMENT
If Table 116, “Register 0x1A”[1] = ‘0’: Switch Node A Output Current or
Output Power2 Measurement3
0000 0000 = Un-defined
0000 0001 = 0.125 A or 125 mW
0000 0010 = 0.25 A or 250 mW
0000 0011 = 0.375 A or 375 mW
0000 0100 = 0.5 A or 500 mW
0000 0101 = 0.625 A or 625 mW
0000 0110 = 0.75 A or 750 mW
0000 0111 = 0.875 A or 875 mW
0000 1000 = 1.0 A or 1000 mW
0000 1001 = 1.125 A or 1125 mW
..
0011 0111 = 6.875 A or 6875 mW
0011 1000 = 7.0 A or 7000 mW
0011 1001 = 7.125 A or 7125 mW
0011 1010 = 7.25 A or 7250 mW
0011 1011 = 7.375 A or 7375 mW
0011 1100 = 7.5 A or 7500 mW
0011 1101 = 7.625 A or 7625 mW
0011 1110 = 7.75 A or 7750 mW
0011 1111 > = 7.875 A or 7875 mW
All other encodings are reserved

JPGNetworksLLC

If Table 116, “Register 0x1A”[1] = ‘1’: Sum of SWA, SWB, SWC and SWD
Output Power4
0000 0000 = Undefined
0000 0001 = 125 mW
0000 0010 = 250 mW
0000 0011 = 375 mW
0000 0100 = 500 mW
...
1111 1100 = 31500 mW
1111 1101 = 31625 mW
1111 1110 = 31750 mW
1111 1111 > = 31875 mW

0

NOTE 1  The PMIC reports current or power measurement as long as there is no output over voltage or output under voltage lockout event
that triggers the VR Disable command. If PMIC triggers VR Disable command, PMIC does not report current or power
measurement and register content may have stale data. For all other events that causes PMIC’s power good status as Not Good, the
PMIC continues to provide current or power measurement.

NOTE 2  If Table 117, “Register 0x1B” [6] = ‘0’, the PMIC reports current measurement. If Table 117, “Register 0x1B” [6] = ‘1’, the PMIC

reports power measurement.

NOTE 3  If Table 166, “Register 0x4F” [0] = ‘1’, host adds the current or power reported in Table 102, “Register 0x0C” [7:0] and Table 103,

“Register 0x0D” [5:0] for total current or power consumption.

NOTE 4  Register Table 117, “Register 0x1B” [6] must be configured as ‘1’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

3.3.5.1 Status Registers (cont’d)

JEDEC Standard No. 301-1A.02
Page 121

R0D

Bits

7:6

Attribute Default

RV

0

Table 103 — Register 0x0D

Description1

5:0

RO

0

R0D [7:6]: Reserved
R0D [5:0]: SWB_OUTPUT_CURRENT_POWER_MEASUREMENT
Switch Node B Output Current or Output Power2 Measurement3
000000 = Un-defined
000001 = 0.125 A or 125 mW
000010 = 0.25 A or 250 mW
000011 = 0.375 A or 375 mW
000100 = 0.5 A or 500 mW
000101 = 0.625 A or 625 mW
000110 = 0.75 A or 750 mW
000111 = 0.875 A or 875 mW
001000 = 1.0 A or 1000 mW
001001 = 1.125 A or 1125 mW
...
110111 = 6.875 A or 6875 mW
111000 = 7.0 A or 7000 mW
111001 = 7.125 A or 7125 mW
111010 = 7.25 A or 7250 mW
111011 = 7.375 A or 7375 mW
111100 = 7.5 A or 7500 mW
111101 = 7.625 A or 7625 mW
111110 = 7.75 A or 7750 mW
111111 > = 7.875 A or 7875 mW

JPGNetworksLLC

NOTE 1  The PMIC reports current or power measurement as long as there is no output over voltage or output under voltage lockout event
that triggers the VR Disable command. If PMIC triggers VR Disable command, PMIC does not report current or power
measurement and register content may have stale data. For all other events that causes PMIC’s power good status as Not Good, the
PMIC continues to provide current or power measurement.

NOTE 2  If Table 117, “Register 0x1B” [6] = ‘0’, the PMIC reports current measurement. If Table 117, “Register 0x1B” [6] = ‘1’, the PMIC

reports power measurement.

NOTE 3  If Table 166, “Register 0x4F” [0] = ‘1’, host adds the current or power reported in Table 102, “Register 0x0C” [7:0] and Table 103,

“Register 0x0D” [5:0] for total current or power consumption.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 122

3.3.5.1 Status Registers (cont’d)

R0E

Bits

7:6

Attribute Default

RV

0

Table 104 — Register 0x0E

Description1

5:0

RO

0

R0E [7:6]: Reserved
R0E [5:0]: SWC_OUTPUT_CURRENT_POWER_MEASUREMENT
Switch Node C Output Current or Output Power2 Measurement
000000 = Un-defined
000001 = 0.125 A or 125 mW
000010 = 0.25 A or 250 mW
000011 = 0.375 A or 375 mW
000100 = 0.5 A or 500 mW
000101 = 0.625 A or 625 mW
000110 = 0.75 A or 750 mW
000111 = 0.875 A or 875 mW
001000 = 1.0 A or 1000 mW
001001 = 1.125 A or 1125 mW
001010 = 1.25 A or 1250 mW
...
110111 = 6.875 A or 6875 mW
111000 = 7.0 A or 7000 mW
111001 = 7.125 A or 7125 mW
111010 = 7.25 A or 7250 mW
111011 = 7.375 A or 7375 mW
111100 = 7.5 A or 7500 mW
111101 = 7.625 A or 7625 mW
111110 = 7.75 A or 7750 mW
111111 > = 7.875 A or 7875 mW

JPGNetworksLLC

NOTE 1  The PMIC reports current or power measurement as long as there is no output over voltage or output under voltage lockout event
that triggers the VR Disable command. If PMIC triggers VR Disable command, PMIC does not report current or power
measurement and register content may have stale data. For all other events that causes PMIC’s power good status as Not Good, the
PMIC continues to provide current or power measurement.

NOTE 2  If Table 117, “Register 0x1B” [6] = ‘0’, the PMIC reports current measurement. If Table 117, “Register 0x1B” [6] = ‘1’, the PMIC

reports power measurement.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

5:0

RO

3.3.5.1 Status Registers (cont’d)

JEDEC Standard No. 301-1A.02
Page 123

R0F

Bits

7:6

Attribute Default

RV

0

Table 105 — Register 0x0F

Description1

0

R0F [7:6]: Reserved
R0F [5:0]: SWD_OUTPUT_CURRENT_POWER_MEASUREMENT
Switch Node D Output Current or Output Power2 Measurement
000000 = Un-defined
000001 = 0.125 A or 125 mW
000010 = 0.25 A or 250 mW
000011 = 0.375 A or 375 mW
000100 = 0.5 A or 500 mW
000101 = 0.625 A or 625 mW
000110 = 0.75 A or 750 mW
000111 = 0.875 A or 875 mW
001000 = 1.0 A or 1000 mW
001001 = 1.125 A or 1125 mW
...
...
110111 = 6.875 A or 6875 mW
111000 = 7.0 A or 7000 mW
111001 = 7.125 A or 7125 mW
111010 = 7.25 A or 7250 mW
111011 = 7.375 A or 7375 mW
111100 = 7.5 A or 7500 mW
111101 = 7.625 A or 7625 mW
111110 = 7.75 A or 7750 mW
111111 > = 7.875 A or 7875 mW

JPGNetworksLLC

NOTE 1  The PMIC reports current or power measurement as long as there is no output over voltage or output under voltage lockout event
that triggers the VR Disable command. If PMIC triggers VR Disable command, PMIC does not report current or power
measurement and register content may have stale data. For all other events that causes PMIC’s power good status as Not Good, the
PMIC continues to provide current or power measurement.

NOTE 2  If Table 117, “Register 0x1B” [6] = ‘0’, the PMIC reports current measurement. If Table 117, “Register 0x1B” [6] = ‘1’, the PMIC

reports power measurement.

3.3.5.2  Clear Registers

For each Real Time Status Registers (Table 98, “Register 0x08” [7:0], Table 99, “Register 0x09” [7:0], Table 100,
“Register 0x0A” [7:1], Table 101, “Register 0x0B” [7:0] and Table 141, “Register 0x33” [4:2]), the PMIC offers a
way to clear the status of each event. The clear registers are Table 106, “Register 0x10” [7,5:0], Table 107, “Register
0x11” [7:0], Table 108, “Register 0x12” [7:2], Table 109, “Register 0x13” [7:0] and to Table 110, “Register 0x14”
[4:2,0], respectively. All clear registers are Write ‘1’ only registers. When ‘1’ is written to any of the clear registers,
the PMIC updates the status registers to default state and removes the interrupt condition on GSI_n and PWR_GOOD
output signal assuming that event is no longer present. If the failing condition is still present, the status register will
still remain at ‘1’. Note that GSI_n and PWR_GOOD interrupt is only applicable if that event is not masked. GSI_n
output signal can be disabled.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 124

3.3.5.2 Clear Registers (cont’d)

When ‘1’ is written to any of the clear registers, there are three categories of response by the PMIC.

1.      PMIC  removes  GSI_n  interrupt  (PWR_GOOD  interrupt  is  not  applicable.  Related  status  registers  are:
Table 106,  “Register  0x10”  [1],  Table 107,  “Register  0x11”  [7,4:0],  Table 109,  “Register  0x13”  [7:4],
Table 110, “Register 0x14” [4].

2.   PMIC removes GSI_n and PWR_GOOD interrupt. Related status registers are: Table 106, “Register 0x10”

[7,5:2], Table 107, “Register 0x11” [6:5], Table 110, “Register 0x14” [2].

3.   PMIC only removes GSI_n interrupt and does not remove PWR_GOOD interrupt. Related status registers
are:  Table 106,  “Register  0x10”  [0],  Table 108,  “Register  0x12”  [7:4],  Table 109,  “Register  0x13”  [3:0],
Table 110, “Register 0x14” [3]. The host is expected to either power cycle the PMIC or re-issue the
VR Enable command if PMIC is in non write protect mode.

The PMIC offers a Global Clear command by writing ‘1’ to registers Table 110, “Register 0x14” [0]. This command
works same way as individual clear command. This command can alternatively be used by the host if more than one
clear command is required to different registers.

R10

Attribute Default

Bits

7

6

5

4

3

2

1

0

1O

RV

1O

1O

1O

1O

1O

1O

0

0

0

Description1

Table 106 — Register 0x10

JPGNetworksLLC

R10 [7]: CLEAR_VIN_BULK_INPUT_POWER_GOOD_STATUS
Clear VIN_Bulk Input Power Good Status.
1 = Clear Register Table 98, “Register 0x08” [7]2
R10 [6]: Reserved
R10 [5]: CLEAR_SWA_OUTPUT_POWER_GOOD_STATUS
Clear SWA Output Power Good Status.
1 = Clear Register Table 98, “Register 0x08” [5]2
R10 [4]: CLEAR_SWB_OUTPUT_POWER_GOOD_STATUS
Clear SWB Output Power Good Status.3
1 = Clear Register Table 98, “Register 0x08” [4]2
R10 [3]: CLEAR_SWC_OUTPUT_POWER_GOOD_STATUS
Clear SWC Output Power Good Status.
1 = Clear Register Table 98, “Register 0x08” [3]2
R10 [2]: CLEAR_SWD_OUTPUT_POWER_GOOD_STATUS
Clear SWD Output Power Good Status.
1 = Clear Register Table 98, “Register 0x08” [2]2
R10 [1]: CLEAR_VIN_MGMT_INPUT_OVER_VOLTAGE_STATUS
Clear VIN_Mgmt Input Supply Over Voltage Status.
1 = Clear Register Table 98, “Register 0x08” [1]2
R10 [0]: CLEAR_VIN_BULK_INPUT_OVER_VOLTAGE_STATUS
Clear VIN_Bulk Input Supply Over Voltage Status.
1 = Clear Register Table 98, “Register 0x08” [0]2

0

0

0

0

0

NOTE 1  Table 106, “Register 0x10” [7:0] are self clearing bits.

NOTE 2  See Table 28 and Table 29 for GSI_n and POWER_GOOD output signal status change.

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 125

3.3.5.2 Clear Registers (cont’d)

R11

Bits

Attribute Default

Table 107 — Register 0x11

Description1

7

6

5

4

3

2

1

0

1O

1O

1O

1O

1O

1O

1O

0

0

0

0

0

R11 [7]: CLEAR_PMIC_HIGH_TEMP_WARNING_STATUS
Clear PMIC High Temperature Warning Status.
1 = Clear Register Table 99, “Register 0x09” [7]2
R11 [6]: CLEAR_VBIAS_POWER_GOOD_STATUS
Clear VBias Power Good Status.
1 = Clear Register Table 99, “Register 0x09” [6]2
R11 [5]: CLEAR_VOUT_1.8V_OUTPUT_POWER_GOOD_STATUS
Clear VOUT_1.8V Output Power Good Status.
1 = Clear Register Table 99, “Register 0x09” [5]2
R11 [4]:
CLEAR_VIN_MGMT_TO_VIN_BULK_INPUT_SWITCHOVER_STATUS
Clear VIN_Mgmt to VIN_Bulk Input Supply Switchover Status.
1 = Clear Register Table 99, “Register 0x09” [4]2
R11 [3]:
CLEAR_SWA_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING
_STATUS
Clear Switch Node A High Output Current Consumption Warning Status.
1 = Clear Register Table 99, “Register 0x09” [3]2
R11 [2]:
CLEAR_SWB_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING
_STATUS
Clear Switch Node B High Output Current Consumption Warning Status.3
Clear Register Table 99, “Register 0x09” [2]2
R11 [1]:
CLEAR_SWC_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING
_STATUS
Clear Switch Node C High Output Current Consumption Warning Status.
1 = Clear Register Table 99, “Register 0x09” [1]2
R11 [0]:
CLEAR_SWD_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING
_STATUS
Clear Switch Node D High Output Current Consumption Warning Status.
1 = Clear Register Table 99, “Register 0x09” [0]2

JPGNetworksLLC

0

0

1O

0

NOTE 1  Table 107, “Register 0x11” [7:0] are self clearing bits.

NOTE 2  See Table 28 and Table 29 for GSI_n and POWER_GOOD output signal status change.

NOTE 3  This register is applicable regardless of the setting in Table 166, “Register 0x4F” [0].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 126

3.3.5.2 Clear Registers (cont’d)

Table 108 — Register 0x12

R12

Bits

Attribute Default

Description1

7

6

5

4

3

2

1:0

1O

1O

1O

1O

1O

1O

RV

0

0

0

0

0

R12 [7]: CLEAR_SWA_OUTPUT_OVER_VOLTAGE_STATUS
Clear Switch Node A Output Over Voltage Status.
1 = Clear Register Table 100, “Register 0x0A” [7]2
R12 [6]: CLEAR_SWB_OUTPUT_OVER_VOLTAGE_STATUS
Clear Switch Node B Output Over Voltage Status.3
1 = Clear Register Table 100, “Register 0x0A” [6]2
R12 [5]: CLEAR_SWC_OUTPUT_OVER_VOLTAGE_STATUS
Clear Switch Node C Output Over Voltage Status.
1 = Clear Register Table 100, “Register 0x0A” [5]2
R12 [4]: CLEAR_SWD_OUTPUT_OVER_VOLTAGE_STATUS
Clear Switch Node D Output Over Voltage Status.
1 = Clear Register Table 100, “Register 0x0A” [4]2
R12 [3]: CLEAR_PER_ERROR_STATUS
Clear PEC Error Status.
1 = Clear Register Table 100, “Register 0x0A” [3]
R12 [2]: CLEAR_PARITY_ERROR_STATUS
Clear Parity Error Status.
1 = Clear Register Table 100, “Register 0x0A” [2]
R12 [1:0]: Reserved

JPGNetworksLLC

0

0

NOTE 1  Table 108, “Register 0x12” [7:0] are self clearing bits.

NOTE 2  See Table 28 and Table 29 for GSI_n and POWER_GOOD output signal status change.

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 127

3.3.5.2 Clear Registers (cont’d)

Table 109 — Register 0x13

R13

Bits

Attribute Default

Description1

7

6

5

4

3

2

1

0

1O

1O

1O

1O

1O

1O

1O

0

0

0

0

R13 [7]:
CLEAR_SWA_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Clear Switch Node A Output Current Limiter Warning Status.
1 = Clear Register Table 101, “Register 0x0B” [7]2
R13 [6]:
CLEAR_SWB_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Clear Switch Node B Output Current Limiter Warning Status.3
1 = Clear Register Table 101, “Register 0x0B” [6]2
R13 [5]:
CLEAR_SWC_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Clear Switch Node C Output Current Limiter Warning Status.
1 = Clear Register Table 101, “Register 0x0B” [5]2
R13 [4]:
CLEAR_SWD_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Clear Switch Node D Output Current Limiter Warning Status.
1 = Clear Register Table 101, “Register 0x0B” [4]2
R13 [3]:
CLEAR_SWA_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Clear Switch Node A Output Under Voltage Lockout Status.
1 = Clear Register Table 101, “Register 0x0B” [3]2
R13 [2]:
CLEAR_SWB_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Clear Switch Node B Output Under Voltage Lockout Status.4
1 = Clear Register Table 101, “Register 0x0B” [2]2
R13 [1]:
CLEAR_SWC_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Clear Switch Node C Output Under Voltage Lockout Status.
1 = Clear Register Table 101, “Register 0x0B” [1]2
R13 [0]:
CLEAR_SWD_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Clear Switch Node D Output Under Voltage Lockout Status.
1 = Clear Register Table 101, “Register 0x0B” [0]2

JPGNetworksLLC

0

0

0

1O

0

NOTE 1  Table 109, “Register 0x13” [7:0] are self clearing bits.

NOTE 2  See Table 28 and Table 29 for GSI_n and POWER_GOOD output signal status change.

NOTE 3  This register is applicable regardless of the setting in Table 166, “Register 0x4F” [0]

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 128

3.3.5.2 Clear Registers (cont’d)

Table 110 — Register 0x14

R14

Attribute Default

Description1

Bits

7:5

4

3

2

1

0

RV

1O

1O

1O

RV

1O

0

0

0

0

0

R14 [7:5]: Reserved
R14 [4]:
CLEAR_VIN_MGMT_POWER_GOOD_STATUS_SWITCHOVER_MODE
Clear Valid VIN_Mgmt Power Good Status in Switchover Mode.
1 = Clear Register Table 141, “Register 0x33” [4]2
R14 [3]:
CLEAR_VBIAS_OUTPUT_OR_VIN_BULK_UNDER_VOLTAGE_
LOCKOUT_STATUS
Clear VBias Output or VIN_Bulk Input Under Voltage Lockout Status.
1 = Clear Register Table 141, “Register 0x33” [3]2
R14 [2]: CLEAR_VOUT_1.0V_OUTPUT_POWER_GOOD_STATUS
Clear VOUT_1.0V Output Power Good Status.
1 = Clear Register Table 141, “Register 0x33” [2]2
R14 [1]: Reserved
R14 [0]: GLOBAL_CLEAR_STATUS
Clear all3 status bits.
1 = Clear all status bits4

JPGNetworksLLC

0

NOTE 1  Table 110, “Register 0x14” [4:2, 0] are self clearing bits.
NOTE 2  See Table 28 and Table 29 for GSI_n and POWER_GOOD output signal status change.
NOTE 3  All status bits in register Table 106, “Register 0x10” [7,5:0], Table 107, “Register 0x11” [7:0], Table 108, “Register 0x12” [7:2],

Table 109, “Register 0x13” [7:0] and Table 110, “Register 0x14” [4:2].

NOTE 4  See Table 28 and Table 29 for GSI_n and POWER_GOOD output signal status change.

3.3.5.3  Mask Registers

For each Real Time Status Registers (Table 98, “Register 0x08” [7:0], Table 99, “Register 0x09” [7:0], Table 100,
“Register 0x0A” [7:1], Table 101, “Register 0x0B” [7:0], Table 141, “Register 0x33” [4:2]), the PMIC offers a way
to  mask  the  status  of  each  event  interrupt.  The  mask  registers  are  Table 111,  “Register  0x15”  [7,5:0],  Table 112,
“Register 0x16” [7:0], Table 113, “Register 0x17” [7:2], Table 114, “Register 0x18” [7:0], and Table 115, “Register
0x19” [4:2] respectively. The mask registers only masks the event interrupt on GSI_n and PWR_GOOD signal.

There  is  also  a  global  mask  bits  register  control  Table 137,  “Register  0x2F”  [1:0]  to  control  the  GSI_n  and
PWR_GOOD  output  signal. When  all  mask  registers  are  Table 111,  “Register  0x15”  [7,5:0],  Table 112,  “Register
0x16” [7:0], Table 113, “Register 0x17” [7:2], Table 114, “Register 0x18” [7:0], and Table 115, “Register 0x19” [4:2]
configured as ‘0’, the setting in Table 137, “Register 0x2F” [1:0] does not matter. The setting in Table 137, “Register
0x2F” [1:0] only matters when one or more mask registers Table 111, “Register 0x15” [7,5:0], Table 112, “Register
0x16” [7:0], Table 113, “Register 0x17” [7:2], Table 114, “Register 0x18” [7:0], and Table 115, “Register 0x19” [4:2]
are configured to ‘1’.

For  any  failure  events  that  causes  the  PMIC  to  generate VR  Disable  command  on  its  own,  the  mask  register  bits
(Table 111,  “Register  0x15”  [0],  Table 113,  “Register  0x17”  [7:4],  Table 114,  “Register  0x18”  [3:0],  Table 115,
“Register 0x19” [3], Table 137, “Register 0x2F” [1:0]) do not apply and PMIC will assert PWR_GOOD output signal
regardless of the setting in mask registers. The PMIC still updates the status registers appropriately when any event
occurs. When masked, the host is expected to read the status registers periodically to learn if any of the event has
occurred or not. The host can mask or un-mask each event individually. The host can mask or un-mask at any time in
non write protect mode. In write protect mode of operation, the mask registers are locked.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 129

3.3.5.3 Mask Registers (cont’d)

R15

Table 111 — Register 0x15

Bits

Attribute Default

Description

7

6

5

4

3

2

1

0

RW

RV

RW

RW

RW

RW

RW

RW

1

1

0

1

R15 [7]: MASK_VIN_BULK_INPUT_POWER_GOOD_STATUS
Mask VIN_Bulk Input Power Good Status Event.
0 = Do Not Mask VIN_Bulk Input Power Good Status Event
1 = Mask VIN_Bulk Input Power Good Status Event1
R15 [6]: Reserved
R15 [5]: MASK_SWA_OUTPUT_POWER_GOOD_STATUS
Mask SWA Output Power Good Status Event.
0 = Do Not Mask SWA Output Power Good Status Event
1 = Mask SWA Output Power Good Status Event1
R15 [4]: MASK_SWB_OUTPUT_POWER_GOOD_STATUS
Mask SWB Output Power Good Status Event.2
0 = Do Not Mask SWB Output Power Good Status Event
1 = Mask SWB Output Power Good Status Event1
R15 [3]: MASK_SWC_OUTPUT_POWER_GOOD_STATUS
Mask SWC Output Power Good Status Event.
0 = Do Not Mask SWC Output Power Good Status Event
1 = Mask SWC Output Power Good Status Event1
R15 [2]: MASK_SWD_OUTPUT_POWER_GOOD_STATUS
Mask SWD Output Power Good Status Event.
0 = Do Not Mask SWD Output Power Good Status Event
1 = Mask SWD Output Power Good Status Event1
R15 [1]: MASK_VIN_MGMT_INPUT_OVER_VOLTAGE_STATUS
Mask VIN_Mgmt Input Supply Over Voltage Status Event.
0 = Do Not Mask VIN_Mgmt Input Supply Over Voltage Status Event
1 = Mask VIN_Mgmt Input Supply Over Voltage Status Event3
R15 [0]: MASK_VIN_BULK_INPUT_OVER_VOLTAGE_STATUS
Mask VIN_Bulk Input Supply Over Voltage Status Event.
0 = Do Not Mask VIN_Bulk Input Supply Over Voltage Status Event
1 = Mask VIN_Bulk Input Supply Over Voltage Status Event3

JPGNetworksLLC

1

1

0

0

NOTE 1  Not assert GSI_n or assert POWER_GOOD output signal.

NOTE 2  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 3  Not assert GSI_n output signal.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 130

3.3.5.3 Mask Registers (cont’d)

R16

Table 112 — Register 0x16

Bits

Attribute Default

Description

7

6

5

4

3

2

1

0

RW

RW

RW

RW

RW

RW

RW

0

RW

0

1

0

0

0

0

JPGNetworksLLC

R16 [7]: MASK_PMIC_HIGH_TEMP_WARNING_STATUS
Mask PMIC High Temperature Warning Status Event.
0 = Do Not Mask PMIC High Temperature Warning Status Event
1 = Mask PMIC High Temperature Warning Status Event1
R16 [6]: MASK_VBIAS_POWER_GOOD_STATUS
Mask VBias Power Good Status Event.
0 = Do Not Mask VBias Power Good Status Event
1 = Mask VBias Power Good Status Event2
R16 [5]: MASK_VOUT_1.8V_OUTPUT_POWER_GOOD_STATUS
Mask VOUT_1.8V Output Power Good Status Event.
0 = Do Not Mask 1.8V Output Power Good Status Event
1 = Mask 1.8V Output Power Good Status Event2
R16 [4]: MASK_VIN_MGMT_TO_VIN_BULK_SWITCHOVER_STATUS
Mask VIN_Mgmt to VIN_Bulk Input Supply Switchover Status Event.
0 = Do Not Mask VIN_Mgmt to VIN_Bulk Input Supply Switchover Status
Event
1 = Mask VIN_Mgmt to VIN_Bulk Input Supply Switchover Status Event1
R16 [3]:
MASK_SWA_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING_S
TATUS
Mask SWA High Output Current Consumption Warning Status Event.
0 = Do Not Mask SWA Output Current Consumption Warning Status Event
1 = Mask SWA Output Current Consumption Warning Status Event1
R16 [2]:
MASK_SWB_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING_S
TATUS
Mask SWB High Output Current Consumption Warning Status Event.3
0 = Do Not Mask SWB Output Current Consumption Warning Status Event
1 = Mask SWB Output Current Consumption Warning Status Event1
R16 [1]:
MASK_SWC_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING_S
TATUS
Mask SWC High Output Current Consumption Warning Status Event.
0 = Do Not Mask SWC Output Current Consumption Warning Status Event
1 = Mask SWC Output Current Consumption Warning Status Event1
R16 [0]:
MASK_SWD_HIGH_OUTPUT_CURRENT_CONSUMPTION_WARNING_S
TATUS
Mask SWD High Output Current Consumption Warning Status Event.
0 = Do Not Mask SWD Output Current Consumption Warning Status Event
1 = Mask SWD Output Current Consumption Warning Status Event1

0

NOTE 1  Not assert GSI_n output signal.

NOTE 2  Not assert GSI_n or assert POWER_GOOD output signal

NOTE 3  This register is applicable regardless of the setting in Table 166, “Register 0x4F” [0].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 131

3.3.5.3 Mask Registers (cont’d)

R17

Table 113 — Register 0x17

Bits

Attribute Default

Description

7

6

5

4

3

2

RW

RW

RW

RW

RW

RW

0

0

0

0

R17 [7]: MASK_SWA_OUTPUT_OVER_VOLTAGE_STATUS
Mask SWA Output Over Voltage Status Event.
0 = Do Not Mask SWA Output Over Voltage Status Event
1 = Mask SWA Output Over Voltage Status Event1
R17 [6]: MASK_SWB_OUTPUT_OVER_VOLTAGE_STATUS
Mask SWB Output Over Voltage Status Event.2
0 = Do Not Mask SWB Output Over Voltage Status Event
1 = Mask SWB Output Over Voltage Status Event1
R17 [5]: MASK_SWC_OUTPUT_OVER_VOLTAGE_STATUS
Mask SWC Output Over Voltage Status Event.
0 = Do Not Mask SWC Output Over Voltage Status Event
1 = Mask SWC Output Over Voltage Status Event1
R17 [4]: MASK_SWD_OUTPUT_OVER_VOLTAGE_STATUS
Mask SWD Output Over Voltage Status Event.
0 = Do Not Mask SWD Output Over Voltage Status Event
1 = Mask SWD Output Over Voltage Status Event1
R17 [3]: MASK_PEC_ERROR_STATUS
Mask PEC Error Event for GSI_n output Only3
0 = Do Not Mask PEC Error Status Event
1 = Mask PEC Error Status
R17 [2]: MASK_PARITY_ERROR_STATUS
Mask Parity Error Event for GSI_n output Only3
0 = Do Not Mask Parity Error Status Event
1 = Mask Parity Error Status
R17 [1:0]: Reserved

JPGNetworksLLC

0

0

1:0

RV
NOTE 1  Not assert GSI_n output signal.

0

NOTE 2  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 3  Only applicable when PMIC is in I3C Basic Mode. This Mask register only masks the GSI_n output. Does not apply to IBI.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 132

3.3.5.3 Mask Registers (cont’d)

R18

Table 114 — Register 0x18

Bits

Attribute Default

Description

7

6

5

4

3

2

1

0

RW

RW

RW

RW

RW

RW

RW

RW

0

0

0

0

JPGNetworksLLC

R18 [7]:
MASK_SWA_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Mask SWA Output Current Limiter Warning Status Event.
0 = Do Not Mask SWA Output Current Limiter Warning Status Event
1 = Mask SWA Output Current Limiter Warning Status Event1
R18 [6]:
MASK_SWB_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Mask SWB Output Current Limiter Warning Status Event.2
0 = Do Not Mask SWB Output Current Limiter Warning Status Event
1 = Mask SWB Output Current Limiter Warning Status Event1
R18 [5]:
MASK_SWC_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Mask SWC Output Current Limiter Warning Status Event.
0 = Do Not Mask SWC Output Current Limiter Warning Status Event
1 = Mask SWC Output Current Limiter Warning Status Event1
R18 [4]:
MASK_SWD_OUTPUT_CURRENT_LIMITER_WARNING_STATUS
Mask SWD Output Current Limiter Warning Status Event.
0 = Do Not Mask SWD Output Current Limiter Warning Status Event
1 = Mask SWD Output Current Limiter Warning Status Event1
R18 [3]:
MASK_SWA_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Mask SWA Output Under Voltage Lockout Status Event.
0 = Do Not Mask SWA Output Under Voltage Lockout Status Event
1 = Mask SWA Output Under Voltage Lockout Status Event1
R18 [2]:
MASK_SWB_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Mask SWB Output Under Voltage Lockout Status Event.3
0 = Do Not Mask SWB Output Under Voltage Lockout Status Event
1 = Mask SWB Output Under Voltage Lockout Status Event1
R18 [1]:
MASK_SWC_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Mask SWC Output Under Voltage Lockout Status Event.
0 = Do Not Mask SWC Output Under Voltage Lockout Status Event
1 = Mask SWC Output Under Voltage Lockout Status Event1
R18 [0]:
MASK_SWD_OUTPUT_UNDER_VOLTAGE_LOCKOUT_STATUS
Mask SWD Output Under Voltage Lockout Status Event.
0 = Do Not Mask SWD Output Under Voltage Lockout Status Event
1 = Mask SWD Output Under Voltage Lockout Status Event1

0

0

0

0

NOTE 1  Not assert GSI_n output signal.
NOTE 2  This register is applicable regardless of the setting in Table 166, “Register 0x4F” [0]

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

3.3.5.3 Mask Registers (cont’d)

JEDEC Standard No. 301-1A.02
Page 133

Table 115 — Register 0x19

R19

Attribute Default

Description

Bits
7:5

RV

4

RW

3

2

RW

RW

0

0

0

R19 [7:5]: Reserved
R19 [4]:
MASK_VIN_MGMT_POWER_GOOD_STATUS_SWITCHOVER_MODE
Mask VIN_Mgmt Input Supply Power Good Status in Switchover Mode Only
0 = Do Not Mask VIN_Mgmt Input Power Supply Power Good Status Event
in Switchover Mode
1 = Mask VIN_Mgmt Input Power Supply Power Good Status Event in
Switchover Mode1
R19 [3]:
MASK_VBIAS_OUTPUT_OR_VIN_BULK_UNDER_VOLTAGE_LOCK
OUT_STATUS
Mask VBias Output or VIN_Bulk Input Under Voltage Lockout Event
0 = Do Not Mask Vbias Output or VIN_Bulk Input Under Voltage Lockout
Event
1 = Mask Vbias Output or VIN_Bulk InputUnder Voltage Lockout Event1
R19 [2]: MASK_VOUT_1.0V_OUTPUT_POWER_GOOD_STATUS
Mask VOUT_1.0V Output Power Good Status Event.
0 = Do Not Mask VOUT_1.0V Output Power Good Status Event
1 = Mask VOUT_1.0V Output Power Good Status Event2
R19 [1:0]: Reserved

JPGNetworksLLC

1

1:0

RV
NOTE 1  Not assert GSI_n output signal.

0

NOTE 2  Not assert GSI_n or POWER_GOOD output signal.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 134

3.3.5.4   Threshold and Configuration Registers

R1A

Table 116 — Register 0x1A

Bits

Attribute Default

Description

7:5

RW

110

4

3

2

1

0

RV

RW

RW

RW

RW

0

0

R1A [7:5]: VIN_BULK_POWER_GOOD_THRESHOLD_VOLTAGE
VIN Bulk Input Threshold Voltage for Input Power Good Status for input
supply
000 = Reserved
001 = 9.5 V
010 = 8.5 V
011 = 7.5 V
100 = 6.5 V
101 = 5.5 V
110 = 4.25 V1,2,3
111 = Reserved
R1A [4]: Reserved
R1A [3]: VBIAS_POWER_GOOD_THRESHOLD_VOLTAGE
VBias LDO Output Threshold Voltage for Power Good Status
0 = Vendor Specific
1 = Reserved
R1A [2]: VOUT_1.8V_POWER_GOOD_THRESHOLD_VOLTAGE
VOUT 1.8V LDO Output Threshold Voltage for Power Good Status
0 = 1.6 V
1 = Reserved
R1A [1]: OUTPUT_POWER_SELECT
Switch Regulator Output Power Select4
0 = Report individual power for each rail in R0C, R0D, R0E, and R0F
1 = Report total power of each rail in R0C5
R1A [0]: VOUT_1.0V_POWER_GOOD_THRESHOLD_VOLTAGE
VOUT 1.0V LDO Output Threshold Voltage for Power Good Status
0 = -10% from the setting in Table 133, “Register 0x2B” [2:1]
1 = -15% from the setting in Table 133, “Register 0x2B” [2:1]

JPGNetworksLLC

0

0

0

NOTE 1  If VIN_Bulk input voltage falls below this threshold, the PMIC may not guarantee the operation.

NOTE 2  If VIN_Bulk voltage continues to fall below vendor specific UVLO, the PMIC triggers a VR Disable command and executes

power down sequence.

NOTE 3  If VIN_Bulk voltage threshold is higher than default setting of this register, the PMIC continues to operate but updates its
PWR_GOOD status register and GSI_n/PWR_GOOD signal is asserted when VIN_Bulk falls below the threshold setting.

NOTE 4  This register is only applicable if Table 117, “Register 0x1B” [6] = ‘1’.

NOTE 5  Host should only read Table 102, “Register 0x0C” [7:0] for total power. The register contents of Table 103, “Register 0x0D”,

Table 104, “Register 0x0E”, and Table 105, “Register 0x0F” may not be valid.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 135

3.3.5.4 Threshold and Configuration Registers (cont’d)

R1B

Table 117 — Register 0x1B

Bits

Attribute Default

Description

7

6

5

4

3

RW

RW

RW

RW

RW

2:0

RW

0

0

0

0

R1B [7]: VIN_BULK_OVER_VOLTAGE_THRESHOLD
VIN_Bulk Input Over Voltage Threshold Setting
0 = 14.5 V
1 = 16.0 V
R1B [6]: CURRENT_OR_POWER_METER_SELECT
PMIC Output Regulator Measurement - Current or Power Meter
0 = Report Current Measurements in registers:1
1 = Report Power Measurements in registers1
R1B [5]: VIN_MGMT_OVER_VOLTAGE_THRESHOLD
VIN_Mgmt Input Over Voltage Threshold
0 = 3.8 V
1 = 3.7 V
R1B [4]: GLOBAL_PWR_GOOD_PIN_STATUS_MASK
Global Mask PWR_GOOD Output Pin2
0 = Not Masked
1 = Masked
R1B [3]: GSI_N_PIN_ENABLE
Enable GSI_n Pin3
0 = Disable GSI_n Pin
1 = Enable GSI_n Pin
R1B [2:0]: PMIC_HIGH_TEMPERATURE_WARNING_THRESHOLD
PMIC High Temperature Warning Threshold4
000 = Reserved
001 = PMIC temperature > 850 C
010 = PMIC temperature > 950 C
011 = PMIC temperature > 1050 C
100 = PMIC temperature > 1150 C
101 = PMIC temperature > 1250 C
110 = PMIC temperature > 1350 C
111 = Reserved

JPGNetworksLLC

0

101

NOTE 1  Table 102, “Register 0x0C” [7:0], Table 103, “Register 0x0D” [5:0], Table 104, “Register 0x0E” [5:0], Table 105, “Register

0x0F”[5:0].

NOTE 2  Mask POWER_GOOD output signal for all appropriate register bits in Table 111, “Register 0x15” [7,5:0], Table 112, “Register

0x16” [7:0], Table 113, “Register 0x17” [7:4], Table 114, “Register 0x18” [7:0] and Table 115, “Register 0x19” [4:2]. Mask
Register Control Table 137, “Register 0x2F” [1:0] still applies when Global PWR_GOOD output Mask register is set to ‘1’.

NOTE 3  This register can be used as Global Mask Function for GSI_n pin. If disabled, this masks GSI_n output signal for all register bits in

Table 111, “Register 0x15” [7, 5:0], Table 112, “Register 0x16” [7:0], Table 113, “Register 0x17” [7:2], Table 114, “Register
0x18” [7:0], and Table 115, “Register 0x19” [4:2].

NOTE 4  The tolerance of the temperature warning threshold is + 5 0C from the selected setting.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 136

3.3.5.4 Threshold and Configuration Registers (cont’d)

R1C

Table 118 — Register 0x1C

Bits

Attribute Default

Description

R1C [7:2]:
SWA_OUTPUT_HIGH_CURRENT_CONSUMPTION_WARNING_THRE
SHOLD
SWA Output High Current Consumption Warning Threshold
000000 = Un-defined
000001 = > 0.125 A
000010 = > 0.25 A
000011 = > 0.375 A
000100 = > 0.5 A or
000101 = > 0.625 A
000110 = > 0.75 A
000111 = > 0.875 A
001000 = > 1.0 A
001001 = > 1.125 A
...
010111 = > 2.875 A
011000 = > 3.0 A
011001 = > 3.125 A
...
110111 = > 6.875 A
111000 = > 7.0 A
111001 = > 7.125 A
111010 = > 7.25 A
111011 = > 7.375 A
111100 = > 7.5 A
111101 = > 7.625 A
111110 = > 7.75 A
111111 = > 7.875 A
R1C [1:0]: Reserved

JPGNetworksLLC

0

7:2

RW 011000

1:0

RV

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 137

3.3.5.4 Threshold and Configuration Registers (cont’d)

R1D

Table 119 — Register 0x1D

Bits

Attribute Default

Description

7:2

RW 011000

R1D [7:2]:
SWB_OUTPUT_HIGH_CURRENT_CONSUMPTION_WARNING_THRE
SHOLD
SWB Output High Current Consumption Warning Threshold1
000000 = Un-defined
000001 = > 0.125 A
000010 = > 0.25 A
000011 = > 0.375 A
000100 = > 0.5 A or
000101 = > 0.625 A
000110 = > 0.75 A
000111 = > 0.875 A
001000 = > 1.0 A
001001 = > 1.125 A
...
010111 = > 2.875 A
011000 = > 3.0 A
...
110111 = > 6.875 A
111000 = > 7.0 A
111001 = > 7.125 A
111010 = > 7.25 A
111011 = > 7.375 A
111100 = > 7.5 A
111101 = > 7.625 A
111110 = > 7.75 A
111111 = > 7.875 A
R1D [1:0]: Reserved

JPGNetworksLLC

0

1:0

RV

NOTE 1  This register is applicable regardless of the setting in Table 166, “Register 0x4F” [0]. For dual phase operation, this register should

be configured identically as Table 118, “Register 0x1C” [7:2].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 138

3.3.5.4 Threshold and Configuration Registers (cont’d)

R1E

Table 120 — Register 0x1E

Bits

Attribute Default

Description

R1E [7:2]:
SWC_OUTPUT_HIGH_CURRENT_CONSUMPTION_WARNING_THRE
SHOLD
SWC Output High Current Consumption Warning Threshold
000000 = Un-defined
000001 = > 0.125 A
000010 = > 0.25 A
000011 = > 0.375 A
000100 = > 0.5 A or
000101 = > 0.625 A
000110 = > 0.75 A
000111 = > 0.875 A
001000 = > 1.0 A
001001 = > 1.125 A
...
010111 = > 2.875 A
011000 = > 3.0 A
011001 = > 3.125 A
...
110111 = > 6.875 A
111000 = > 7.0 A
111001 = > 7.125 A
111010 = > 7.25 A
111011 = > 7.375 A
111100 = > 7.5 A
111101 = > 7.625 A
111110 = > 7.75 A
111111 = > 7.875 A
R1E [1:0]: Reserved

JPGNetworksLLC

0

7:2

RW 011000

1:0

RV

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 139

3.3.5.4 Threshold and Configuration Registers (cont’d)

R1F

Table 121 — Register 0x1F

Bits

Attribute Default

Description

R1F [7:2]:
SWD_OUTPUT_HIGH_CURRENT_CONSUMPTION_WARNING_
THRESHOLD
SWD Output High Current Consumption Warning Threshold
000000 = Un-defined
000001 = > 0.125 A
000010 = > 0.25 A
000011 = > 0.375 A
000100 = > 0.5 A or
000101 = > 0.625 A
000110 = > 0.75 A
000111 = > 0.875 A
001000 = > 1.0 A
001001 = > 1.125 A
...
010111 = > 2.875 A
011000 = > 3.0 A
011001 = > 3.125 A
...
110111 = > 6.875 A
111000 = > 7.0 A
111001 = > 7.125 A
111010 = > 7.25 A
111011 = > 7.375 A
111100 = > 7.5 A
111101 = > 7.625 A
111110 = > 7.75 A
111111 = > 7.875 A
R1F [1:0]: Reserved

JPGNetworksLLC

0

7:2

RW 011000

1:0

RV

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 140

3.3.5.4 Threshold and Configuration Registers (cont’d)

R20 1

Bits

Attribute Default

Description

Table 122 — Register 0x20

R20 [7:6]:
SWA_OUTPUT_CURRENT_LIMITER_WARNING_THRESHOLD_
SETTING
PMIC5000, COT Ivalley_limit
00 = 4.0 A
01 = 4.5 A
10 = 5.0 A
11 = 5.5 A

7:6

RW

0

5:4

RW

0

PMIC5010, COT Ivalley_limit
00 = 2.0 A
01 = 2.5 A
10 = 3.0 A
11 = 3.5 A
R20 [5:4]:
SWB_OUTPUT_CURRENT_LIMITER_WARNING_THRESHOLD_
SETTING
PMIC5000, COT Ivalley_limit:2
00 = 4.0 A
01 = 4.5 A
10 = 5.0 A
11 = 5.5 A

JPGNetworksLLC

PMIC5010, COT Ivalley_limit
00 = 2.0 A
01 = 2.5 A
10 = 3.0 A
11 = 3.5 A
R20 [3:2]:
SWC_OUTPUT_CURRENT_LIMITER_WARNING_THRESHOLD_
SETTING
PMIC5000, COT Ivalley_limit:
00 = 4.0 A
01 = 4.5 A
10 = 5.0 A
11 = 5.5 A

3:2

RW

0

PMIC5010, COT Ivalley_limit
00 = 2.0 A
01 = 2.5 A
10 = 3.0 A
11 = 3.5 A

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 141

3.3.5.4 Threshold and Configuration Registers (cont’d)

Table 122 — Register 0x20 (cont’d)

R20 1

Bits

Attribute Default

Description

R20 [1:0]:
SWD_OUTPUT_CURRENT_LIMITER_WARNING_THRESHOLD_
SETTING
PMIC5000, COT Ivalley_limit:
00 = 4.0 A
01 = 4.5 A
10 = 5.0 A
11 = 5.5 A

1:0

RW

0

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 167, “Register 0x50””.

NOTE 2  This register is applicable regardless of the setting in Table 166, “Register 0x4F” [0]. If Table 166, “Register 0x4F” [0] = ‘1’, this

register must be configured identically as bits [7:6].

PMIC5010, COT Ivalley_limit
00 = 2.0 A
01 = 2.5 A
10 = 3.0 A
11 = 3.5 A

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 142

3.3.5.4 Threshold and Configuration Registers (cont’d)

R21 1,2

Bits

Attribute Default

Description

Table 123 — Register 0x21

0

RW

7:1

RW

011
1100

R21 [7:1]: SWA_VOLTAGE_SETTING
SWA Output Regulator Voltage Setting3,4
000 0000 = 800 mV5 or 600 mV6
000 0001 = 805 mV or 605 mV
000 0010 = 810 mV or 610 mV
...
011 1100 = 1100 mV or 900 mV
...
111 1101 = 1425 mV or 1225 mV
111 1110 = 1430 mV or 1230 mV
111 1111 = 1435 mV or 1235 mV
R21 [0]:
SWA_POWER_GOOD_THRESHOLD_LOW_SIDE_VOLTAGE_SETTING
SWA Output Threshold Low Side Voltage For Power Good Status
0 = -5% from the setting in Table 123, “Register 0x21” [7:1]
1 = -7.5% from the setting in Table 123, “Register 0x21” [7:1]

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 156, “Register 0x45”.

NOTE 2  If required, the host must update the settings in register Table 123, “Register 0x21” [0], Table 124, “Register 0x22” [7:2] and
Table 122, “Register 0x20” [7:6] first prior to updating the settings in the register Table 123, “Register 0x21” [7:1].

NOTE 3  PMIC guarantees efficiency spec and all electrical characteristics spec within a range of 1050 mV to 1160 mV.

NOTE 4  After VR is enabled, the host may update this register to any new setting that it may desire. However to prevent false error trigger, the

PMIC internally will increment the SWA output voltage setting by 5 mV at a time. The time it takes for PMIC to adjust the output
voltage is 5 μs for each 5 mV increment. The host must wait sufficient time for PMIC to adjust to final value. As an example, if host
adjusts the output voltage by 50 mV from the original value, the host must wait minimum of 50 μs before PMIC can guarantee the
new output voltage. During this time, PMIC masks the PWR_GOOD output signal assertion to prevent any artificial error due to the
crossing of the output voltage threshold setting. However, PMIC does assert PWR_GOOD output signal if there is any abnormal
issues that triggers VR Disable command as described in Table 27, “Events Interrupt Summary”. Further, PMIC does monitor
PWR_GOOD input signal and executes power off config sequence registers if it is registered low when Table 140, “Register 0x32”
[5] = ‘1’.

0

JPGNetworksLLC

NOTE 5  Table 133, “Register 0x2B” [5] = ‘0’; 5 mV step size.

NOTE 6  Table 133, “Register 0x2B” [5] = ‘1’; 5 mV step size

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 143

3.3.5.4 Threshold and Configuration Registers (cont’d)

R22 1,2

Bits

Attribute Default

Description

Table 124 — Register 0x22

7:6

RW

01

5:4

RW

3:2

RW

1:0

RW

10

R22 [7:6]:
SWA_POWER_GOOD_THRESHOLD_HIGH_SIDE_VOLTAGE_SETTING
SWA Output Threshold High Side Voltage For Power Good Status
00 = +5% from the setting in Table 123, “Register 0x21” [7:1]
01 = +7.5% from the setting in Table 123, “Register 0x21” [7:1]
10 = +10% from the setting in Table 123, “Register 0x21” [7:1]
11 = Reserved
R22 [5:4]: SWA_OVER_VOLTAGE_THRESHOLD_SETTING
SWA Output Regulator Threshold For Over Voltage Status3
00 = +7.5% from the setting in Table 123, “Register 0x21” [7:1]
01 = +10% from the setting in Table 123, “Register 0x21” [7:1]
10 =+12.5% from the setting in Table 123, “Register 0x21” [7:1]
11 = Reserved
R22 [3:2]: SWA_UNDER_VOLTAGE_LOCKOUT_THRESHOLD_SETTING
SWA Output Regulator Threshold For Under Voltage Lockout Status
00 = -10% from the setting in Table 123, “Register 0x21” [7:1]
01 = -12.5% from the setting in Table 123, “Register 0x21” [7:1]
10 = Reserved
11 = Reserved
R22 [1:0]: SWA_OUTPUT_SOFT_STOP_TIME
SWA Output Regulator Soft Stop Time After VR Disable4
00 = 0.5 ms
01 = 1 ms
10 = 2 ms
11 = 4 ms

JPGNetworksLLC

00

00

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 157, “Register 0x46”.

NOTE 2  If required, the host must update the setting in register Table 123, “Register 0x21” [0], Table 124, “Register 0x22” [7:2] and
Table 122, “Register 0x20” [7:6] first prior to updating the settings in the register Table 123, “Register 0x21” [7:1].

NOTE 3  The setting for the Over Voltage must be higher than Power Good High Side Voltage threshold in Table 124, “Register 0x22”[7:6].

NOTE 4  This is the time it takes for buck regulator to go from steady state voltage to 0 V.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 144

3.3.5.4 Threshold and Configuration Registers (cont’d)

R23 1,2,3

Bits

Attribute Default

Description

Table 125 — Register 0x23

0

RW

7:1

RW

011
1100

R23 [7:1]: SWB_VOLTAGE_SETTING
SWB Output Regulator Voltage Setting4,5
000 0000 = 800 mV6 or 600 mV7
000 0001 = 805 mV or 605 mV
000 0010 = 810 mV or 610 mV
...
011 1100 = 1100 mV or 900 mV
...
111 1101 = 1425 mV or 1225 mV
111 1110 = 1430 mV or 1230 mV
111 1111 = 1435 mV or 1235 mV
R23 [0]:
SWB_POWER_GOOD_THRESHOLD_LOW_SIDE_VOLTAGE_SETTING
SWB Output Threshold Low Side Voltage For Power Good Status
0 = -5% from the setting in Table 125, “Register 0x23” [7:1]
1 = -7.5% from the setting in Table 125, “Register 0x23” [7:1]

0

JPGNetworksLLC

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 158, “Register 0x47”.

NOTE 2  If required, the host must update the settings in register Table 125, “Register 0x23” [0], Table 126, “Register 0x24” [7:2], and
Table 122, “Register 0x20” [5:4] first prior to updating the settings in the register Table 125, “Register 0x23” [7:1].

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 4  PMIC guarantees efficiency spec and all electrical characteristics spec within a range of 1050 mV to 1160 mV.

NOTE 5  After VR is enabled, the host may update this register to any new setting that it may desire. However to prevent false error trigger, the

PMIC internally will increment the SWB output voltage setting by 5 mV at a time. The time it takes for PMIC to adjust the output
voltage is 5 μs for each 5 mV increment. The host must wait sufficient time for PMIC to adjust to final value. As an example, if host
adjusts the output voltage by 50 mV from the original value, the host must wait minimum of 50 μs before PMIC can guarantee the
new output voltage. During this time, PMIC masks the PWR_GOOD output signal assertion to prevent any artificial error due to the
crossing of the output voltage threshold setting. However, PMIC does assert PWR_GOOD output signal if there is any abnormal
issues that triggers VR Disable command as described in Table 27. Further, PMIC does monitor PWR_GOOD input signal and
executes power off config sequence registers if it is registered low when Table 140, “Register 0x32” [5] = ‘1’.

NOTE 6  Table 133, “Register 0x2B” [4] = ‘0’; 5 mV step size.

NOTE 7  Table 133, “Register 0x2B” [4] = ‘1’; 5 mV step size

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 145

3.3.5.4 Threshold and Configuration Registers (cont’d)

R24 1,2,3

Bits

Attribute Default

Description

Table 126 — Register 0x24

7:6

RW

01

5:4

RW

3:2

RW

1:0

RW

10

00

R24 [7:6]:
SWB_POWER_GOOD_THRESHOLD_HIGH_SIDE_VOLTAGE_SETTING
SWB Output Threshold High Side Voltage For Power Good Status
00 = +5% from the setting in Table 125, “Register 0x23” [7:1]
01 = +7.5% from the setting in Table 125, “Register 0x23” [7:1]
10 = +10% from the setting in Table 125, “Register 0x23” [7:1]
11 = Reserved
R24 [5:4]: SWB_OVER_VOLTAGE_THRESHOLD_SETTING
SWB Output Regulator Threshold For Over Voltage Status4
00 = +7.5% from the setting in Table 125, “Register 0x23” [7:1]
01 = +10% from the setting in Table 125, “Register 0x23” [7:1]
10 =+12.5% from the setting in Table 125, “Register 0x23” [7:1]
11 = Reserved
R24 [3:2]:
SWB_UNDER_VOLTAGE_LOCKOUT_THRESHOLD_SETTING
SWB Output Regulator Threshold For Under Voltage Lockout Status
00 = -10% from the setting in Table 125, “Register 0x23” [7:1]
01 = -12.5% from the setting in Table 125, “Register 0x23” [7:1]
10 = Reserved
11 = Reserved
R24 [1:0]: SWB_OUTPUT_SOFT_STOP_TIME
SWB Output Regulator Soft Stop Time After VR Disable5
00 = 0.5 ms
01 = 1 ms
10 = 2 ms
11 = 4 ms

JPGNetworksLLC

00

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 159, “Register 0x48”.

NOTE 2  If required, the host must update the settings in register Table 125, “Register 0x23” [0], Table 126, “Register 0x24” [7:2] and
Table 122, “Register 0x20” [5:4] first prior to updating the settings in the register Table 125, “Register 0x23” [7:1].

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 4  The setting for the Over Voltage must be higher than Power Good High Side Voltage threshold in Table 126, “Register 0x24”[7:6].

NOTE 5  This is the time it takes for buck regulator to go from steady state voltage to 0 V.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 146

3.3.5.4 Threshold and Configuration Registers (cont’d)

R25 1,2

Bits

Attribute Default

Description

Table 127 — Register 0x25

0

RW

7:1

RW

011
1100

R25 [7:1]: SWC_VOLTAGE_SETTING
SWC Output Regulator Voltage Setting3,4
000 0000 = 800 mV5 or 600 mV6
000 0001 = 805 mV or 605 mV
000 0010 = 810 mV or 610 mV
...
011 1100 = 1100 mV or 900 mV
...
111 1101 = 1425 mV or 1225 mV
111 1110 = 1430 mV or 1230 mV
111 1111 = 1435 mV or 1235 mV
R25 [0]:
SWC_POWER_GOOD_THRESHOLD_LOW_SIDE_VOLTAGE_SETTING
SWC Output Threshold Low Side Voltage For Power Good Status
0 = -5% from the setting in Table 127, “Register 0x25” [7:1]
1 = -7.5% from the setting in Table 127, “Register 0x25” [7:1]

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 160, “Register 0x49”.

NOTE 2  If required, the host must update the settings in register Table 127, “Register 0x25” [0], Table 128, “Register 0x26” [7:2] and
Table 122, “Register 0x20” [3:2] first prior to updating the settings in the register Table 127, “Register 0x25” [7:1].

NOTE 3  PMIC guarantees efficiency spec and all electrical characteristics spec within a range of 1050 mV to 1160 mV.

NOTE 4  After VR is enabled, the host may update this register to any new setting that it may desire. However to prevent false error trigger, the

PMIC internally will increment the SWC output voltage setting by 5 mV at a time. The time it takes for PMIC to adjust the output
voltage is 5 μs for each 5 mV increment. The host must wait sufficient time for PMIC to adjust to final value. As an example, if host
adjusts the output voltage by 50 mV from the original value, the host must wait minimum of 50 μs before PMIC can guarantee the
new output voltage. During this time, PMIC masks the PWR_GOOD output signal assertion to prevent any artificial error due to the
crossing of the output voltage threshold setting. However, PMIC does assert PWR_GOOD output signal if there is any abnormal
issues that triggers VR Disable command as described in Table 27, “Events Interrupt Summary”. Further, PMIC does monitor
PWR_GOOD input signal and executes power off config sequence registers if it is registered low when Table 140, “Register 0x32”
[5] = ‘1’.

0

JPGNetworksLLC

NOTE 5  Table 133, “Register 0x2B” [3] = ‘0’; 5 mV step size.

NOTE 6  Table 133, “Register 0x2B” [3] = ‘1’; 5 mV step size

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 147

3.3.5.4 Threshold and Configuration Registers (cont’d)

R26 1,2

Table 128 — Register 0x26

Bits

Attribute Default

Description

7:6

RW

01

5:4

RW

3:2

RW

1:0

RW

10

00

R26 [7:6]:
SWC_POWER_GOOD_THRESHOLD_HIGH_SIDE_VOLTAGE_SETTING
SWC Output Threshold High Side Voltage For Power Good Status
00 = +5% from the setting in Table 127, “Register 0x25” [7:1]
01 = +7.5% from the setting in Table 127, “Register 0x25” [7:1]
10 = +10% from the setting in Table 127, “Register 0x25” [7:1]
11 = Reserved
R26 [5:4]: SWC_OVER_VOLTAGE_THRESHOLD_SETTING
SWC Output Regulator Threshold For Over Voltage Status3
00 = +7.5% from the setting in Table 127, “Register 0x25” [7:1]
01 = +10% from the setting in Table 127, “Register 0x25” [7:1]
10 =+12.5% from the setting in Table 127, “Register 0x25” [7:1]
11 = Reserved
R26 [3:2]:
SWC_UNDER_VOLTAGE_LOCKOUT_THRESHOLD_SETTING
SWC Output Regulator Threshold For Under Voltage Lockout Status
00 = -10% from the setting in Table 127, “Register 0x25” [7:1]
01 = -12.5% from the setting in Table 127, “Register 0x25” [7:1]
10 = Reserved
11 = Reserved
R26 [1:0]: SWC_OUTPUT_SOFT_STOP_TIME
SWC Output Regulator Soft Stop Time After VR Disable4
00 = 0.5 ms
01 = 1 ms
10 = 2 ms
11 = 4 ms

JPGNetworksLLC

00

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 161, “Register 0x4A”.

NOTE 2  If required, the host must update the settings in register Table 127, “Register 0x25” [0], Table 128, “Register 0x26” [7:2], and
Table 122, “Register 0x20” [3:2] first prior to updating the settings in the register Table 127, “Register 0x25” [7:1].

NOTE 3  The setting for the Over Voltage must be higher than Power Good High Side Voltage threshold in Table 128, “Register 0x26”[7:6].

NOTE 4  This is the time it takes for buck regulator to go from steady state voltage to 0 V.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 148

3.3.5.4 Threshold and Configuration Registers (cont’d)

R27 1,2

Bits

Attribute Default

Description

Table 129 — Register 0x27

0

RW

7:1

RW

011
1100

R27 [7:1]: SWD_VOLTAGE_SETTING
SWD Output Regulator Voltage Setting3,4
000 0000 = 1500 mV5 or 2200 mV6
000 0001 = 1505 mV or 2205 mV
000 0010 = 1510 mV or 2210 mV
...
011 1100 = 1800 mV or 2500 mV
...
111 1101 = 2125 mV or 2825 mV
111 1110 = 2130 mV or 2830 mV
111 1111 = 2135 mV or 2835 mV
R27 [0]:
SWD_POWER_GOOD_THRESHOLD_LOW_SIDE_VOLTAGE_SETTING
SWD Output Threshold Low Side Voltage For Power Good Status
0 = -5% from the setting in Table 129, “Register 0x27” [7:1]
1 = -7.5% from the setting in Table 129, “Register 0x27” [7:1]

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 162, “Register 0x4B”.

NOTE 2  If required, the host must update the settings in register Table 129, “Register 0x27” [0], Table 130, “Register 0x28” [7:2], and
Table 122, “Register 0x20” [1:0] first prior to updating the settings in the register Table 129, “Register 0x27” [7:1].

NOTE 3  PMIC guarantees efficiency spec and all electrical characteristics spec within a range of 1750 mV to 1850 mV.

NOTE 4  After VR is enabled, the host may update this register to any new setting that it may desire. However to prevent false error trigger, the

PMIC internally will increment the SWD output voltage setting by 5 mV at a time. The time it takes for PMIC to adjust the output
voltage is 5 μs for each 5 mV increment. The host must wait sufficient time for PMIC to adjust to final value. As an example, if host
adjusts the output voltage by 50 mV from the original value, the host must wait minimum of 50 μs before PMIC can guarantee the
new output voltage. During this time, PMIC masks the PWR_GOOD output signal assertion to prevent any artificial error due to the
crossing of the output voltage threshold setting. However, PMIC does assert PWR_GOOD output signal if there is any abnormal
issues that triggers VR Disable command as described in Table 27, “Events Interrupt Summary”. Further, PMIC does monitor
PWR_GOOD input signal and executes power off config sequence registers if it is registered low when Table 140, “Register 0x32”
[5] = ‘1’.

0

JPGNetworksLLC

NOTE 5  Table 133, “Register 0x2B” [0] = ‘0’; 5 mV step size.

NOTE 6  Table 133, “Register 0x2B” [0] = ‘1’; 5 mV step size.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 149

3.3.5.4 Threshold and Configuration Registers (cont’d)

R28 1,2

Bits

Attribute Default

Description

Table 130 — Register 0x28

7:6

RW

01

5:4

RW

3:2

RW

1:0

RW

10

00

R28 [7:6]:
SWD_POWER_GOOD_THRESHOLD_HIGH_SIDE_VOLTAGE_SETTING
SWD Output Threshold High Side Voltage For Power Good Status
00 = +5% from the setting in Table 129, “Register 0x27” [7:1]
01 = +7.5% from the setting in Table 129, “Register 0x27” [7:1]
10 = +10% from the setting in Table 129, “Register 0x27” [7:1]
11 = Reserved
R28 [5:4]: SWD_OVER_VOLTAGE_THRESHOLD_SETTING
SWD Output Regulator Threshold For Over Voltage Status3
00 = +7.5% from the setting in Table 129, “Register 0x27” [7:1]
01 = +10% from the setting in Table 129, “Register 0x27” [7:1]
10 =+12.5% from the setting in Table 129, “Register 0x27” [7:1]
11 = Reserved
R28 [3:2]:
SWD_UNDER_VOLTAGE_LOCKOUT_THRESHOLD_SETTING
SWD Output Regulator Threshold For Under Voltage Lockout Status
00 = -10% from the setting in Table 129, “Register 0x27” [7:1]
01 = -12.5% from the setting in Table 129, “Register 0x27” [7:1]
10 = Reserved
11 = Reserved
R28 [1:0]: SWD_OUTPUT_SOFT_STOP_TIME
SWD Output Regulator Soft Stop Time After VR Disable4
00 = 1 ms
01 = 2 ms
10 = 4 ms
11 = 8 ms

JPGNetworksLLC

00

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 163, “Register 0x4C”.

NOTE 2  If required, the host must update the settings in register Table 129, “Register 0x27” [0], Table 130, “Register 0x28” [7:2] and
Table 122, “Register 0x20” [1:0] first prior to updating the settings in the register Table 129, “Register 0x27” [7:1].

NOTE 3  The setting for the Over Voltage must be higher than Power Good High Side Voltage threshold in Table 130, “Register 0x28”[7:6].

NOTE 4  This is the time it takes for buck regulator to go from steady state voltage to 0 V.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 150

3.3.5.4 Threshold and Configuration Registers (cont’d)

R29 1,2

Table 131 — Register 0x29

Bits

Attribute Default

Description

7:6

RW

10

5:4

RW

01

3:2

RW

1:0

RW

10

R29 [7:6]: SWA_MODE_SELECT
SWA Output Regulator Mode Selection
00 = Reserved
01 = Reserved
10 = COT; DCM (Constant on Time; Discontinuous Current Mode)
11 = COT; Forced CCM (Constant on Time; Continuous Current Mode)
R29 [5:4]: SWA_SWITCHING_FREQ
SWA Output Regulator Switching Frequency
00 = 500 KHz
01 = 750 KHz
10 = 1000 KHz
11 = 1250 KHz
R29 [1:0]: SWB_MODE_SELECT
SWB Output Regulator Mode Selection3
00 = Reserved
01 = Reserved
10 = COT; DCM (Constant on Time; Discontinuous Current Mode)
11 = COT; Forced CCM (Constant on Time; Continuous Current Mode)
R29 [1:0]: SWB_SWITCHING_FREQ
SWB Output Regulator Switching Frequency3
00 = 500 KHz
01 = 750 KHz
10 = 1000 KHz
11 = 1250 KHz

JPGNetworksLLC

01

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 164, “Register 0x4D”.

NOTE 2  If required, the host must adjust this register first before issuing VR Enable command in Table 140, “Register 0x32” [7].

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 151

3.3.5.4 Threshold and Configuration Registers (cont’d)

R2A 1,2

Table 132 — Register 0x2A

Bits

Attribute Default

Description

7:6

RW

10

5:4

RW

01

3:2

RW

1:0

RW

10

R2A [7:6]: SWC_MODE_SELECT
Switch Node C Output Regulator Mode Selection
00 = Reserved
01 = Reserved
10 = COT; DCM (Constant on Time; Discontinuous Current Mode)
11 = COT; Forced CCM (Constant on Time; Continuous Current Mode)
R2A [5:4]: SWC_SWITCHING_FREQ
Switch Node C Output Regulator Switching Frequency
00 = 500 KHz
01 = 750 KHz
10 = 1000 KHz
11 = 1250 KHz
R2A [3:2]: SWD_MODE_SELECT
Switch Node D Output Regulator Mode Selection
00 = Reserved
01 = Reserved
10 = COT; DCM (Constant on Time; Discontinuous Current Mode)
11 = COT; Forced CCM (Constant on Time; Continuous Current Mode)
R2A [1:0]: SWD_SWITCHING_FREQ
Switch Node D Output Regulator Switching Frequency
00 = 500 KHz
01 = 750 KHz
10 = 1000 KHz
11 = 1250 KHz

JPGNetworksLLC

01

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 165, “Register 0x4E”.

NOTE 2  If required, the host must adjust this register first before issuing VR Enable command in Table 140, “Register 0x32” [7].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 152

3.3.5.4 Threshold and Configuration Registers (cont’d)

R2B 1,2

Table 133 — Register 0x2B

Bits

Attribute Default

Description

7:6

RW

01

5

4

3

RW

0

RW

RW

2:1

RW

0

RW

0

R2B [7:6]: VOUT_1.8V_VOLTAGE_SETTING
VOUT 1.8 V LDO Output Voltage Setting3
00 = 1.7 V
01 = 1.8 V
10 = 1.9 V
11 = Reserved
R2B [5]: SWA_VOLTAGE_RANGE
SWA Output Voltage Range Selection4
0 = Range: 800 mV to 1435 mV for SWA; 5 mV step size
1 = Range: 600 mV to 1235 mV for SWA; 5 mV step size
R2B [4]: SWB_VOLTAGE_RANGE
SWB Output Voltage Range Selection5,6
0 = Range: 800 mV to 1435 mV for SWB; 5 mV step size
1 = Range: 600 mV to 1235 mV for SWB; 5 mV step size
R2B [3]: SWC_VOLTAGE_RANGE
SWC Output Voltage Range Selection7
0 = Range: 800 mV to 1435 mV for SWC; 5 mV step size
1 = Range: 600 mV to 1235 mV for SWC; 5 mV step size
R2B [2:1]: VOUT_1.0V_VOLTAGE_SETTING
VOUT 1.0 V LDO Voltage Setting8
00 = 0.9 V
01 = 1.0 V
10 = 1.1 V
11 = 1.2 V
R2B [0]: SWD_VOLTAGE_RANGE
SWD Output Voltage Range Selection9
0 = Range: 1500 mV to 2135 mV for SWD; 5 mV step size
1 = Range: 2200 mV to 2835 mV for SWD; 5 mV step size

JPGNetworksLLC

0

0

01

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 168, “Register 0x51”.

NOTE 2  If required, the host must adjust this register first before issuing VR Enable command in Table 140, “Register 0x32” [7]. The host

must also wait minimum of 5 μs after the adjustment before issuing VR Enable command.

NOTE 3  The VOUT_1.8V Power Good threshold in register Table 116, “Register 0x1A” [2] is always fixed regardless of the setting in this

register.

NOTE 4  Range and resolution selection applies to register Table 123, “Register 0x21” [7:1].

NOTE 5  Range and resolution selection applies to register Table 125, “Register 0x23” [7:1].

NOTE 6  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 7  Range and resolution selection applies to register Table 127, “Register 0x25” [7:1].

NOTE 8  If required, the host must adjust this register one step at a time (0.1 V increment or decrement) to prevent false trigger of power

good status and PWR_GOOD pin assertion. In other words, host should not increment or decrement 0.2 V or 0.3 V from its current
setting.

NOTE 9  Range and resolution selection applies to register Table 129, “Register 0x27” [7:1].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 153

3.3.5.4 Threshold and Configuration Registers (cont’d)

Table 134 — Register 0x2C

R2C 1,2

Bits

Attribute Default

Description

7:5

RW

001

4

RV

0

3:1

RW

0

RV

001

R2C [7:5]: SWA_OUTPUT_SOFT_START_TIME
SWA Output Regulator Soft Start Time After VR Enable3
000 = 1 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
...
111 = 14 ms
R2C [4]: Reserved
R2C [3:1]: SWB_OUTPUT_SOFT_START_TIME
SWB Output Regulator Soft Start Time After VR Enable3,4
000 = 1 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
...
111 = 14 ms
R2C [0]: Reserved

JPGNetworksLLC

0

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 173, “Register 0x5D”.

NOTE 2  If required, the host must adjust this register first before issuing VR Enable command in Table 140, “Register 0x32” [7].

NOTE 3  This is the time it takes for buck regulator to go from 0 V to steady state voltage (the actual voltage varies based on

pre-programmed voltage).

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 154

3.3.5.4 Threshold and Configuration Registers (cont’d)

R2D 1,2

Table 135 — Register 0x2D

Bits

Attribute Default

Description

NOTE 1  At first power on, this register is automatically configured identically by PMIC on its own as Table 174, “Register 0x5E”.

NOTE 2  If required, the host must adjust this register first before issuing VR Enable command in Table 140, “Register 0x32” [7].

NOTE 3  This is the time it takes for buck regulator to go from 0 V to steady state voltage (the actual voltage varies based on pre-

001

R2D [7:5]: SWC_OUTPUT_SOFT_START_TIME
SWC Output Regulator Soft Start Time After VR Enable3
000 = 1 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
...
111 = 14 ms
R2D [4]: Reserved
R2D [3:1]: SWD_OUTPUT_SOFT_START_TIME
SWD Output Regulator Soft Start Time After VR Enable3
000 = 1 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
...
111 = 14 ms
R2D [0]: Reserved

JPGNetworksLLC

Table 136 — Register 0x2E

Description

0

0

7:5

RW

001

4

RV

0

3:1

RW

0

RV

programmed voltage)

R2E

Bits
7:3

Attribute Default

RV

2:0

RW

100

R2E [7:3]: Reserved
R2E [2:0]: PMIC_SHUTDOWN_TEMPERATURE_THRESHOLD
PMIC Shutdown Temperature Threshold
000 = PMIC Temperature > 1050 C
001 = PMIC Temperature > 1150 C
010 = PMIC Temperature > 1250 C
011 = PMIC Temperature > 1350 C
100 = PMIC Temperature > 1450 C
101 = Reserved
110 = Reserved
111 = Reserved

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

3.3.5.4 Threshold and Configuration Registers (cont’d)

Table 137 — Register 0x2F

JEDEC Standard No. 301-1A.02
Page 155

R2F

Bits

Attribute Default

0

0

7

6

5

RW

RW

RW

Description
R2F [7]: VIN_MGMT_INPUT_SUPPLY_SWITCHOVER_THRESHOLD
VIN_Mgmt Input Supply Switchover Voltage Threshold to VIN_Bulk Input
Supply
0 = Vendor Specific1
1 = Reserved
R2F [6]: SWA_REGULATOR_CONTROL
Disable SWA Regulator Output2,3
0 = Disable Switch Node A Output Regulator
1 = Enable Switch Node A Output Regulator
R2F [5]: SWB_REGULATOR_CONTROL
Disable SWB Regulator Output2,3,4
0 = Disable Switch Node B Output Regulator
1 = Enable Switch Node B Output Regulator

0

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 156

Table 137 — Register 0x2F (cont’d)

R2F

Bits

Attribute Default

4

3

2

RW

RW

RW

0

0

0

Description
R2F [4]: SWC_REGULATOR_CONTROL
Disable SWC Regulator Output2,3
0 = Disable Switch Node C Output Regulator
1 = Enable Switch Node C Output Regulator
R2F [3]: SWD_REGULATOR_CONTROL
Disable SWD Regulator Output2,3
0 = Disable Switch Node D Output Regulator
1 = Enable Switch Node D Output Regulator
R2F [2]: WRITE_PROTECT_FUNCTION_CONTROL
 PMIC Write Protect Function Control
0 = CAMP input signal determines the Write Protect Function as noted in
clause 2.7.7.1
1 = Write Protect Function is disabled; All register write access is allowed
independent of CAMP input signal as noted in clause 2.7.7.1.
R2F [1:0]: MASK_BITS_REGISTER_CONTROL
Mask Bits Register Control5
00 = Mask GSI_n Signal Only (PWR_GOOD Signal will assert)
01 = Mask PWR_GOOD Signal Only (GSI_n Signal will assert)
10 = Mask GSI_n and PWR_GOOD Signals (neither PWR_GOOD assert or
GSI_n signal will assert)
11 = Reserved

10

JPGNetworksLLC

the status of this register to ‘1’ after VR Enable command. When VR Enable command is registered, the PMIC updates this
register based on Power On Sequence Configuration (0 to 3) setting. If enabled in Power On Sequence Configuration 0 to 3
registers, only then, under non write protect mode of operation, the PMIC’s output regulator can be disabled by clearing this bit and
they can be re-enabled again by setting this bit. The PMIC does not alter its Power Good output signal and keeps it asserted High.
If any regulator is not enabled in Power on Sequence Configuration 0 to 3, it cannot be enabled using this register. For example, if
only SWA is enabled and SWB, SWC and SWD is not enabled in Table 152, “Register 0x40” [7:0] to Table 155, “Register 0x43”
[7:0] then only SWA can be disabled and then re-enabled again but SWB, SWC and SWD cannot be enabled using Table 137,
“Register 0x2F” [6:3].

NOTE 3  In non write protect mode, after VR enable command, if any output regulators are disabled by clearing Table 137, “Register 0x2F”
[6:3] and then if host issues VR Disable command or PMIC internally triggers VR Disable command, the PMIC keeps the disabled
output regulator in Table 137, “Register 0x2F”[6:3] off and remaining output regulators are disabled by following the Power Off
Sequence Configuration 0 to 3 settings.

NOTE 2  This bit must be used only after power up sequence (after VR Enable command). At first power up, PMIC automatically updates

NOTE 1  The VIN_Mgmt input switchover voltage threshold range is vendor specific and can vary between 2.6 V to 2.9 V max.

1:0

RW

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.
NOTE 5  Applies to Mask Registers Table 111, “Register 0x15” [7,5:0], Table 112, “Register 0x16” [7:0], Table 113, “Register 0x17” [7:2],
Table 114, “Register 0x18” [7:0], Table 115, “Register 0x19” [4:2] when any one or more Mask registers are set to ‘1’. If all Mask
registers are configured as ‘0’, the setting in this register (Table 137, “Register 0x2F” [1:0]) does not matter.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 157

3.3.5.4 Threshold and Configuration Registers (cont’d)

R30

Table 138 — Register 0x30

Bits

Attribute Default

Description

7

RW

0

6:3

RW

2

RV

1:0

RW

0

R30 [7]: ADC_ENABLE
Enable ADC (Analog to Digital Conversion)
0 = Disable1
1 = Enable
R30 [6:3]: ADC_SELECT
Input Selection for ADC Readout2
0000 = SWA Output Voltage
0001 = SWB Output Voltage3
0010 = SWC Output Voltage
0011 = SWD Output Voltage
0100 = Reserved
0101 = VIN_Bulk Input Voltage
0110 = VIN_Mgmt Input Voltage
0111 = VBias Output Voltage
1000 = VOUT_1.8V Output Voltage
1001 = VOUT_1.0V Output Voltage
All other encodings are reserved.
R30 [2]: Reserved
R30 [1:0]: ADC_REGISTER_UPDATE_FREQUENCY
ADC Current or Power Measurement Update Frequency4,5
00 = 1 ms
01 = 2 ms
10 = 4 ms
11 = 8 ms

JPGNetworksLLC

0

0

NOTE 1  Disables the ADC function completely. Applies to voltage readout in Table 139, “Register 0x31” [7:0] as well as current or power

readout in Table 102, “Register 0x0C” [7:0], Table 103, “Register 0x0D” [5:0], Table 104, “Register 0x0E” [5:0] and Table 105,
“Register 0x0F” [5:0]. Does not apply to thermal sensor temperature readout in Table 141, “Register 0x33” [7:5] as well as high
temperature warning and critical temperature shutdown.

NOTE 2  The host shall wait minimum of 9 ms delay after the input selection for ADC readout and the actual readout from Table 139,

“Register 0x31” to get the latest reading

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’

NOTE 4  For average output current or power measurement in registers Table 102, “Register 0x0C” [7:0], Table 103, “Register 0x0D” [5:0],

Table 104, “Register 0x0E” [5:0] and Table 105, “Register 0x0F” [5:0].

NOTE 5  This register represents how often the registers are updated. The internal sampling rate is vendor specific.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 158

3.3.5.4 Threshold and Configuration Registers (cont’d)

R31

Table 139 — Register 0x31

Bits

Attribute Default

Description

R31 [7:0]: ADC_READ
ADC Output Voltage Reading1(Applies to SW[A:D], VOUT_1.8V,
VOUT_1.0V, VIN_Mgmt)
0000 0000 = Undefined
0000 0001 = 15 mV
0000 0010 = 30 mV
..
1111 1111 > = 3825 mV

7:0

RO

0

ADC Output Voltage Reading2 (Applies to VIN_Bulk Input Voltage)
0000 0000 = Undefined
0000 0001 = 70 mV
0000 0010 = 140 mV
..
1111 1111 > = 17850 mV

ADC Output Voltage Reading3 (Applies to VBias Output Voltage)
0000 0000 = Undefined
0000 0001 = 25 mV
0000 0010 = 50 mV
..
1111 1111 > = 6375 mV

JPGNetworksLLC

NOTE 1  Only valid when Table 138, “Register 0x30” [6:3] = ‘0000’ or ‘0001’ or ‘0010’ or ‘0011’ or ‘0110’ or ‘1000’ or ‘1001’.

NOTE 2  Only valid when Table 138, “Register 0x30” [6:3] = ‘0101’.

NOTE 3  Only valid when Table 138, “Register 0x30” [6:3] = ‘0111’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 159

3.3.5.4 Threshold and Configuration Registers (cont’d)

R32

Table 140 — Register 0x32

Bits

Attribute Default

Description

7

6

5

4

3

RW

RO

RW

RW

RW

2:0

RV

1

0

0

R32 [7]: VR_ENABLE
PMIC Enable1,2,3,4
0 = PMIC Disable
1 = PMIC Enable
R32 [6]: MANAGEMENT_INTERFACE_SELECTION
PMIC Management Bus Interface Protocol Selection5
0 = I2C Protocol (Max speed 1 MHz)
1 = I3C Basic Protocol
R32 [5]: EXECUTE_VR_ENABLE_CONTROL_
PMIC VR Enable Command Execution Control over I2C/I3C Bus4
0 = Do Not Execute VR Enable Command; i.e., ignore bit [7] = ‘1’ and keep it
as ‘0’.
1 = Execute VR Enable Command
R32 [4]: EXECUTE_CAMP_FAIL_N_FUNCTION_CONTROL
PMIC CAMP Fail_n function (Transition from High to Low) Control
0 = Execute VR Disable Command
1 = Do Not Execute VR Disable Command
R32 [3]: CAMP_PWR_GOOD_OUTPUT_SIGNAL_CONTROL
PMIC CAMP PWR_GOOD Output Signal Control
0 = PMIC controls PWR_GOOD output on its own based on internal status
1 = PWR_GOOD Output Float6
R32 [2:0]: Reserved

JPGNetworksLLC

0

0

00

NOTE 1  Host sets this bit at first power on. After this bit is set, the PMIC executes Power On Sequence configuration 0 (Table 152,

“Register 0x40”) to Power On Sequence configuration 3 (Table 155, “Register 0x43”) registers. At least one bit in Table 152,
“Register 0x40” [6:3] must be set to ‘1’ to issue VR Enable command.

NOTE 2  The host shall ensure that prior to issuing VR Enable command, there is no pending IBI interrupt (i.e., Table 100, “Register 0x0A”
[1] = ‘1’) status. After host issues VR Enable command, the PMIC may NACK any I2C or I3C Basic bus transaction by host until
tPMIC_PWR_GOOD_OUT timing parameter is satisfied. The host shall not access any device specific registers or issue any
CCCs until tPMIC_PWR_GOOD_OUT parameter is satisfied. The PMIC device may request for an IBI during power up sequence
(i.e., during tPMIC_PWR_GOOD_OUT time) if there is any event.

NOTE 3  After host issues VR Enable command, the PMIC may NACK any I2C or I3C Basic bus transactions by host until

tPMIC_PWR_GOOD_OUT timing parameter is satisfied.

NOTE 4  Once Table 140, “Register 0x32” [7] is set to ‘1’ via VR Enable command, the subsequent write to register Table 140, “Register

0x32” [5] = ‘0’ is ignored by the PMIC. If there is a simultaneous write to register Table 140, “Register 0x32” [7,5] = ‘10’, the
PMIC prioritizes bit [5] and does not execute VR Enable command.

NOTE 5  This register is automatically updated when SETAASA CCC or RSTDAA CCC is registered by the PMIC device or when PMIC

device goes through bus reset as described in clause 2.10.15 regardless of whether PMIC is in write protect mode or non write
protect mode of operation. This register can be read by the Host through normal Read operation but it cannot be written with
normal write operation either in I2C mode or I3C Basic mode of operation. When this register is updated, it takes in effect where
there is a next START operation (i.e., after STOP operation).

NOTE 6  When this encoding is set, the PMIC always floats the PWR_GOOD output signal even when there is an internal VR Disable

command due to fault condition.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 160

3.3.5.4 Threshold and Configuration Registers (cont’d)

R33

Table 141 — Register 0x33

Bits

Attribute Default

Description

7:5

RO

0

4

3

2

RO

RO

RO

0

R33 [7:5]: TEMPERATURE_MEASUREMENT
PMIC Temperature1
000 = < 850 C
001 = 850 C
010 = 950 C
011 = 1050 C
100 = 1150 C
101 = 1250 C
110 = 1350 C
111 = > 1400 C
R33 [4]: VIN_MGMT_POWER_GOOD_STATUS_SWITCHOVER_MODE
VIN_Mgmt Input Supply Power Good Status in Switchover Mode Only2
0 = Power Not Good
1 = Power Good
R33 [3]:
VBIAS_OR_VIN_BULK_UNDER_VOLTAGE_LOCKOUT_STATUS
VBias or VIN_Bulk Under Voltage Lockout Status3
0 = No Under Voltage Lockout
1 = Under Voltage Lockout
R33 [2]: VOUT_1.0V_OUTPUT_POWER_GOOD_STATUS
VOUT_1.0V LDO Output Power Good Status4
0 = Power Good
1 = Power Not Good
R33 [1:0]: Reserved

JPGNetworksLLC

0

0

1:0

RV

0
NOTE 1  The accuracy of the temperature readout code is + 50 C.
NOTE 2  This register has no meaning when PMIC is NOT in switchover mode. In switchover mode only, when PMIC detects VIN_Mgmt
input supply from the platform, this bit is set to indicate that PMIC now recognizes valid VIN_Mgmt input power supply.

NOTE 3  This register is set when VBias LDO output goes below vendor specific threshold or VIN_Bulk input goes below vendor-specific

threshold.

NOTE 4  This register is set when VOUT_1.0V output drops below the threshold setting in register Table 116, “Register 0x1A” [0].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 161

3.3.5.4 Threshold and Configuration Registers (cont’d)

R34

Bits

Attribute Default

Table 142 — Register 0x34

Description1

7

6

5

4

RO

RO

RO

RV

3:1

RO

0

RV

setting.

0

0

0

0

R34 [7]: PEC_ENABLE
Packet Error Code Enable2 (Applicable Only if R32 [6] = ‘1’)
0 = Disable
1 = Enable
R34 [6]: IBI_ENABLE
In Band Interrupt Enable3 (Applicable Only if R32 [6] = ‘1’)
0 = Disable
1 = Enable
R34 [5]: PARITY_DISABLE
T Bit Parity Code Disable2 (Applicable Only if R32 [6] = ‘1’.)
0 = Enable
1 = Disable4
R34 [4]: Reserved
R34 [3:1]: HID_CODE
PMIC’s 3-bit HID Code5
000
001
010
011
100
101
110
111
R34 [0]: Reserved

JPGNetworksLLC

0

111

NOTE 1  The write (or update) transaction to this register must be followed by STOP operation to allow the PMIC device to update the

NOTE 2  This register is automatically updated when RSTDAA CCC is registered by the PMIC device or when PMIC device goes through
bus reset as described in clause 2.10.15. This register cannot  be written  by the Host through normal write operation either in I2C
mode or I3C mode of operation. This register is updated with DEVCTRL CCC with RegMod=’0’ only. This register cannot be
written with DEVCTRL CCC with RegMod=’1’.

NOTE 3  This register is automatically updated when ENEC CCC or DISEC CCC or RSTDAA CCC is registered by the PMIC device or
when PMIC device goes through bus reset as described in clause 2.10.15. This register can be read by the Host through normal
Read operation but it cannot be written with normal write operation either in I2C mode or I3C mode of operation. This register
cannot be written with DEVCTRL CCC with RegMod=’1’.

NOTE 4  When Parity function is disabled, the PMIC simply ignores the “T” bit information from the Host. The host may actually choose to

compute the parity and send that information in “T” bit or simply drive static low or high in “T” bit.

NOTE 5  This register is updated when PMIC device receives SETHID CCC or when PMIC device goes through bus reset as described in

clause 2.10.15. This register cannot be written with DEVCTRL CCC with RegMod=’1’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 162

3.3.5.4 Threshold and Configuration Registers (cont’d)

R35

Bits

Attribute Default

7

RW

0

6:4

RW

0

3

RW

2:0

RW

Table 143 — Register 0x35

Description1,2

R35 [7]: ERROR_INJECTION_ENABLE
Error Injection Enable3
0 = Disable
1 = Enable
R35 [6:4]: ERROR_INJECTION_RAIL_SELECTION
Error Injection - Input Rail and Output Rail Selection4,5
000 = Undefined
001 = SWA Output Only
010 = SWB Output Only
011 = SWC Output Only
100 = SWD Output Only
101 = VIN_Bulk Input Only
110 = VIN_Mgmt Input Only
111 = Do Not Use
R35 [3]: OVER_VOLTAGE_UNDER_VOLTAGE_SELECT
Over Voltage or Under Voltage Selection for Bits [6:4]6
0 = Over Voltage
1 = Under Voltage7
R35[2:0]: MISC_ERROR_INJECTION_TYPE
Miscellaneous Error Injection Type8
000 = Undefined
001 = VIN_Mgmt to VIN_Bulk Switchover
010 = Critical Temperature Shutdown
011 = High Temperature Warning Threshold
100= VOUT_1.8V LDO Power Good
101 = High Current Consumption Warning9
110 = Reserved
111 = Current Limiter Warning9

JPGNetworksLLC

0

0

NOTE 1  Refer to clause 2.8.2 for error function usage model. The host can erase the error log registers (Table 94, “Register 0x04” to

Table 94, “Register 0x04”) by writing 0x74 to Table 146, “Register 0x39”.

NOTE 2  To exit from Error Injection Mode, the PMIC must go through power cycle of both VIN_Bulk and VIN_Mgmt input supply.

NOTE 3  When error function is invoked by setting bit [7] = ‘1’, the setting of bits [6:4, 2:0] = ‘000 000’ is considered an illegal setting.

NOTE 4  This register Table 143, “Register 0x35” [6:4] is only applicable if Table 143, “Register 0x35” [2:0] is ‘000’. Any value other than

‘000’ in both Table 143, “Register 0x35” [6:4] and Table 143, “Register 0x35” [2:0] is considered an illegal setting and PMIC
operation is not guaranteed.

NOTE 5  If dual phase regulator is selected, use SWA encoding to inject the error. Register bit [3] selects either over voltage or under voltage

condition for the setting selected in this register.

NOTE 6  This register Table 143, “Register 0x35” [3] is only applicable if bits [6:4] is anything other than ‘000’.

NOTE 7  The under voltage selection only applies to SWx output rails and VIN_Bulk input. Does not apply to VIN_Mgmt input.

NOTE 8  This register Table 143, “Register 0x35” [2:0] is only applicable if Table 143, “Register 0x35” [6:3] is ‘0000’. Any value other

than ‘000’ in both Table 143, “Register 0x35” [6:4] and Table 143, “Register 0x35” [2:0] is considered an illegal setting and PMIC
operation is not guaranteed.

NOTE 9  Applies to all enabled SWx output regulators at the same time.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 163

3.3.5.4 Threshold and Configuration Registers (cont’d)

R37

Table 144 — Register 0x37

Bits

Attribute Default

Description

7:0

WO

-

R37 [7:0]:
DIMM_VENDOR_MEMORY_REGION_PASSWORD_LOWER_BYTE
DIMM Vendor Memory Region (0x40 - 0x6F) Password - Lower Byte
[7:0] = Code

R38

Table 145 — Register 0x38

Bits

Attribute Default

Description

7:0

WO

R39

Bits

Attribute Default

7:0

RW

0x00

R38 [7:0]:
DIMM_VENDOR_MEMORY_REGION_PASSWORD_UPPER_BYTE
DIMM Vendor Memory Region (0x40 - 0x6F) Password - Upper Byte
[7:0] = Code

-

Table 146 — Register 0x39

JPGNetworksLLC

Description

DIMM Vendor Region (0x40 to 0x6F) Write Codes:
0x40: Unlock DIMM Vendor Region. Password needs to be present in R37
and R38 registers.
0x00: Lock DIMM Vendor Region.
0x80: Burn DIMM Vendor Region Password. New password needs to be
present in R37 and R38.
0x81: Burn DIMM Vendor Region - 0x40 to 0x4F
0x82: Burn DIMM Vendor Region - 0x50 to 0x5F
0x85: Burn DIMM Vendor Region - 0x60 to 0x6F

R39 Codes:
Host Region Codes:
0x74: Clear Registers R04 to R07, Erase MTP memory for R04 Register.

DIMM Vendor Region (0x40 to 0x6F) Read Codes:
0x5A: Burning is complete in DIMM Vendor region.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 164

3.3.5.4 Threshold and Configuration Registers (cont’d)

R3A

Bits

Attribute Default

7

6

RV

RW

5:4

RW

0

0

0

3:2

RW

1:0

RV

setting.

Table 147 — Register 0x3A

Description1

R3A [7]: Reserved
R3A [6]: DEFAULT_READ_ADDRESS_POINTER_ENABLE
Enable Default Address Read Pointer when PMIC sees STOP operation
0 = Disable Default Address Pointer (address pointer is set by Host)2
1 = Enable Default Address Pointer; Address selected by register bits [5:4]3
R3A [5:4]: DEFAULT_READ_STARTING_ADDRESS
Default Read Address Pointer Selection when PMIC sees STOP operation4
00 = R08
01 = R0C
10 = Reserved
11 = Reserved
R3A [3:2]: BURST_LENGTH_FOR_READ_DEFAULT_ADDR_POINTER
Burst Length (# of Bytes) to be transferred for Read Default Address Pointer
Mode5
00 = 2 Bytes
01 = 4 Bytes
10 = Reserved
11 = 16 Bytes
R3A [1:0]: Reserved

JPGNetworksLLC

0

0

NOTE 1  The write (or update) transaction to this register must be followed by STOP operation to allow the PMIC device to update the

NOTE 2  The register setting in R3A [5:4] is a don’t care.

NOTE 3  This mode is only allowed when PEC function is disabled (i.e., register R34 [7] = ‘0’).

NOTE 4  This register is only applicable if R3A [6] = ‘1’.

NOTE 5  This register is only applicable if R3A [6] = ‘1’ and R34 [7] = ‘1’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 165

3.3.5.4 Threshold and Configuration Registers (cont’d)

R3B

Table 148 — Register 0x3B

Bits

Attribute Default

Description

7:6

ROE

0

5:4

ROE

-

3:1

ROE

0

ROE

R3C

R3B [7:6]: PMIC_PART_CAPABILITY_EXT
PMIC Current Capability Extension. This register bits [7:6] and bit [0]
provides 3 bit encoding as following:
000 = Small PMIC (Low Current)
001 = Big PMIC (High Current)
01x = Extreme PMIC (Highest Current)
All other encodings are reserved.
R3B [5:4]: REVISION_ID_MAJOR_STEPPING
Major Revision Stepping
00 = Revision 1
01 = Revision 2
10 = Revision 3
11 = Revision 4
R3B [3:1]: REVISION_ID_MINOR_STEPPING
Minor Revision Stepping
000 = Revision 0
001 = Revision 1
010 = Revision 2
011 = Revision 3
All other encodings are reserved.
R3B [0]: PMIC_PART_CAPABILITY
PMIC Current Capability. See also bits [7:6] definition.
0 = Small PMIC (Low Current)
1 = Big PMIC (High Current)

JPGNetworksLLC

Table 149 — Register 0x3C

Description

-

-

R3C [7:0]: VENDOR_ID_BYTE0
Vendor Identification Register Byte 0.

Attribute Default

ROE

-

Bits

7:0

.

Table 150 — Register 0x3D

R3D

Bits

Attribute Default

7:0

ROE

-

R3D [7:0]: VENDOR_ID_BYTE1
Vendor Identification Register Byte 1.

Description

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 166

3.3.6   DIMM Vendor Region Registers

Table 151 — DIMM Vendor Region - Register Map

Register
Table 152, “Register 0x40”
Table 153, “Register 0x41”
Table 154, “Register 0x42”
Table 155, “Register 0x43”
0x44

Attribute
RWPE
RWPE
RWPE
RWPE
RV

Table 156, “Register 0x45”

RWPE

Table 157, “Register 0x46”

RWPE

Table 158, “Register 0x47”

Table 159, “Register 0x48”

Table 160, “Register 0x49”

Table 161, “Register 0x4A”

Table 162, “Register 0x4B”

Table 163, “Register 0x4C”

Table 164, “Register 0x4D”

RWPE

RWPE

RWPE

RWPE

JPGNetworksLLC

Description
R40 [7:0] Power On Sequence Config 0
R41 [7:0] Power On Sequence Config 1
R42 [7:0] Power On Sequence Config 2
R43 [7:0] Power On Sequence Config 3
R44 [7:0] Reserved
R45 [7:1] SWA Voltage Setting
R45 [0] SWA Power Good Low Side Threshold
R46 [7:6] SWA Power Good High Side Threshold
R46 [5:4] SWA Over Voltage Threshold
R46 [3:2] SWA Under Voltage Lockout Threshold
R46 [1:0] SWA Soft Stop Time
R47 [7:1] SWB Voltage Setting
R47 [0] SWB Power Good Low Side Threshold
R48 [7:6] SWB Power Good High Side Threshold
R48 [5:4] SWB Over Voltage Threshold
R48 [3:2] SWB Under Voltage Lockout Threshold
R48 [1:0] SWB Soft Stop Time
R49 [7:1] SWC Voltage Setting
R49 [0] SWC Power Good Low Side Threshold
R4A [7:6] SWC Power Good High Side Threshold
R4A [5:4] SWC Over Voltage Threshold
R4A [3:2] SWC Under Voltage Lockout Threshold
R4A [1:0] SWC Soft Stop Time
R4B [7:1] SWD Voltage Setting
R4B [0] SWD Power Good Low Side Threshold
R4C [7:6] SWD Power Good High Side Threshold
R4C [5:4] SWD Over Voltage Threshold
R4C [3:2] SWD Under Voltage Lockout Threshold
R4C [1:0] SWD Soft Stop Time
R4D [7:6] SWA Mode Select
R4D [5:4] SWA Switching Frequency
R4D [3:2] SWB Mode Select
R4D [1:0] SWB Switching Frequency
R4E [7:6] SWC Mode Select
R4E [5:4] SWC Switching Frequency
R4E [3:2] SWD Mode Select
R4E [1:0] SWD Switching Frequency
R4F [7] Output Regulator Disable Contro
R4F [6:5] Reserved
R4F [4] SWA Remote Sensing Scheme
R4F [3] Reserved
R4F [2] SWC Remote Sensing Scheme
R4F [1] SWD Remote Sensing Scheme
R4F [0] SWA, SWB Single or Dual Phase Regulator Select
R50 [7:6] SWA Current Limit Warning Threshold
R50 [5:4] SWB Current Limit Warning Threshold
R50 [3:2] SWC Current Limit Warning Threshold
R50 [1:0] SWD Current Limit Warning Threshold

RWPE

RWPE

RWPE

Table 165, “Register 0x4E”

RWPE

Table 166, “Register 0x4F”

RWPE

Table 167, “Register 0x50”

RWPE

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

Table 151 — DIMM Vendor Region - Register Map (cont’d)

Register

Attribute

Description

JEDEC Standard No. 301-1A.02
Page 167

Table 168, “Register 0x51”

RWPE

0x52 to 0x57
Table 169, “Register 0x58”
Table 170, “Register 0x59”
Table 171, “Register 0x5A”
Table 172, “Register 0x5B”
0x5C

RV
RWPE
RWPE
RWPE
RWPE
RV

Table 173, “Register 0x5D”

RWPE

Table 174, “Register 0x5E”

0x5F to 0x6F

R51 [7:6] VOUT_1.8V LDO Setting
R51 [5:3] Voltage Range Selection for SWA, SWB and SWC
R51 [2:1] VOUT_1.0V LDO Setting
R51 [0] Voltage Range Selection for SWD
R52 [7:0] to R57 [7:0] Reserved
R58 [7:0] Power Off Sequence Config 0
R59 [7:0] Power Off Sequence Config 1
R5A [7:0] Power Off Sequence Config 2
R5B [7:0] Power Off Sequence Config 3
R5C [7:0] Reserved
R5D [7:5] SWA Soft Start Time
R5D [4] Reserved
R5D [3:1] SWB Soft Start Time
R5D [0] Reserved
R5E [7:5] SWC Soft Start Time
R5E [4] Reserved
R5E [3:1] SWD Soft Start Time
R5E [0] Reserved
R5F [7:0] to R6F [7:0] Reserved

RV

RWPE

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 168

3.3.6 DIMM Vendor Region Registers (cont’d)

R40 1

Table 152 — Register 0x40

Bits

Attribute Default

Description

7

6

5

4

3

RWPE

RWPE

RWPE

RWPE

RWPE

2:0

RWPE

0

0

0

0

R40 [7]: POWER_ON_SEQUENCE_CONFIG0
PMIC Power On Sequence Config 02
0 = Do Not Execute Config 0
1 = Execute Config 0
R40 [6]: POWER_ON_SEQUENCE_CONFIG0_SWA_ENABLE
Enable SWA Output Regulator.
0 = Disable SWA Output Regulator
1 = Enable SWA Output Regulator
R40 [5]: POWER_ON_SEQUENCE_CONFIG0_SWB_ENABLE
Enable SWB Output Regulator.3
0 = Disable SWB Output Regulator
1 = Enable SWB Output Regulator
R40 [4]: POWER_ON_SEQUENCE_CONFIG0_SWC_ENABLE
Enable SWC Output Regulator.
0 = Disable SWC Output Regulator
1 = Enable SWC Output Regulator
R40 [3]: POWER_ON_SEQUENCE_CONFIG0_SWD_ENABLE
Enable SWD Output Regulator.
0 = Disable SWD Output Regulator
1 = Enable SWD Output Regulator
R40 [2:0]: POWER_ON_SEQUENCE_CONFIG0_IDLE
Idle time after Power On Sequence Config 04
000 = 0 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
100 = 8 ms
101 = 10 ms
110 = 12 ms
111 = 24 ms

JPGNetworksLLC

0

001

NOTE 1  If more than one configuration register is used for power on sequence, first register must start at Table 152, “Register 0x40” and it

must go in sequential order to Table 155, “Register 0x43” to turn on all desired regulators. In other words, there must not be any
gap of the register that is used for power on sequence.

NOTE 2  If bit [7] = ‘0’, bits [6:3] must be programmed as ‘0000’. If bit [7] = ‘1’, at least one of the bits [6:3] must be programmed as ‘1’.

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’. This bit is a don’t care when Table 166, “Register 0x4F” [0] = ‘1’.

NOTE 4  Idle time is the additional time after soft-start time expires. The PMIC waits sum of Soft Start time and Idle time before it executes
the next power on sequence configuration register. If more than one regulators are enabled, the PMIC uses the largest value of the
soft start time among the regulators that are enabled in this configuration register.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 169

3.3.6 DIMM Vendor Region Registers (cont’d)

R41 1,2

Table 153 — Register 0x41

Bits

Attribute Default

Description

7

6

5

4

3

RWPE

RWPE

RWPE

RWPE

RWPE

2:0

RWPE

0

0

0

0

R41 [7]: POWER_ON_SEQUENCE_CONFIG1
PMIC Power On Sequence Config 1
0 = Do Not Execute Config13
1 = Execute Config 1
R41 [6]: POWER_ON_SEQUENCE_CONFIG1_SWA_ENABLE
Enable SWA Output Regulator.
0 = Disable SWA Output Regulator
1 = Enable SWA Output Regulator
R41 [5]: POWER_ON_SEQUENCE_CONFIG1_SWB_ENABLE
Enable SWB Output Regulator.4
0 = Disable SWB Output Regulator
1 = Enable SWB Output Regulator
R41 [4]: POWER_ON_SEQUENCE_CONFIG1_SWC_ENABLE
Enable Switch Node C Output Regulator.
0 = Disable SWC Output Regulator
1 = Enable SWC Output Regulator
R41 [3]: POWER_ON_SEQUENCE_CONFIG1_SWD_ENABLE
Enable Switch Node D Output Regulator.
0 = Disable SWD Output Regulator
1 = Enable SWD Output Regulator
R41 [2:0]: POWER_ON_SEQUENCE_CONFIG1_IDLE
Idle time after Power On Sequence Config 15
000 = 0 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
100 = 8 ms
101 = 10 ms
110 = 12 ms
111 = 24 ms

JPGNetworksLLC

0

001

NOTE 1  If any regulators are enabled in Table 152, “Register 0x40” [6:3], those regulators must be configured as ‘1’ in this sequence.

NOTE 2  If more than one configuration register is used for power on sequence, first register must start at Table 152, “Register 0x40” and it

must go in sequential order to Table 155, “Register 0x43” to turn on all desired regulators. In other words, there must not be any
gap of the register that is used for power on sequence.

NOTE 3  If bit [7] = ‘0’, bits [6:3] must be programmed as ‘0000’. If bit [7] = ‘1’, at least one of the bits [6:3] must be programmed as ‘1’.

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’. This bit is a don’t care when Table 166, “Register 0x4F” [0] = ‘1’

NOTE 5  Idle time is the additional time after soft-start time expires. The PMIC waits sum of Soft Start time and Idle time before it executes
the next power on sequence configuration register. If more than one regulators are enabled, the PMIC uses the largest value of the
soft start time among the regulators that are enabled in this configuration register.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 170

3.3.6 DIMM Vendor Region Registers (cont’d)

R42 1,2

Table 154 — Register 0x42

Bits

Attribute Default

Description

7

6

5

4

3

RWPE

RWPE

RWPE

RWPE

RWPE

2:0

RWPE

0

0

0

0

R42 [7]: POWER_ON_SEQUENCE_CONFIG2
PMIC Power On Sequence Config 23
0 = Do Not Execute Config 2
1 = Execute Config 2
R42 [6]: POWER_ON_SEQUENCE_CONFIG2_SWA_ENABLE
Enable Switch Node A Output Regulator.
0 = Disable Switch Node A Output Regulator
1 = Enable Switch Node A Output Regulator
R42 [5]: POWER_ON_SEQUENCE_CONFIG2_SWB_ENABLE
Enable Switch Node B Output Regulator.4
0 = Disable Switch Node B Output Regulator
1 = Enable Switch Node B Output Regulator
R42 [4]: POWER_ON_SEQUENCE_CONFIG2_SWC_ENABLE
Enable Switch Node C Output Regulator.
0 = Disable Switch Node C Output Regulator
1 = Enable Switch Node C Output Regulator
R42 [3]: POWER_ON_SEQUENCE_CONFIG2_SWD_ENABLE
Enable Switch Node D Output Regulator.
0 = Disable Switch Node D Output Regulator
1 = Enable Switch Node D Output Regulator
R42 [2:0]: POWER_ON_SEQUENCE_CONFIG2_IDLE
Idle time after Power On Sequence Config 25
000 = 0 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
100 = 8 ms
101 = 10 ms
110 = 12 ms
111 = 24 ms

JPGNetworksLLC

0

001

NOTE 1  If any regulators are enabled in Table 152, “Register 0x40” [6:3] and Table 153, “Register 0x41” [6:3], those regulators must be

configured as ‘1’ in this sequence.

NOTE 2  If more than one configuration register is used for power on sequence, first register must start at Table 152, “Register 0x40” and it

must go in sequential order to Table 155, “Register 0x43” to turn on all desired regulators. In other words, there must not be any
gap of the register that is used for power on sequence.

NOTE 3  If bit [7] = ‘0’, bits [6:3] must be programmed as ‘0000’. If bit [7] = ‘1’, at least one of the bits [6:3] must be programmed as ‘1’.

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’. This bit is a don’t care when Table 166, “Register 0x4F” [0] = ‘1’

NOTE 5  Idle time is the additional time after soft-start time expires. The PMIC waits sum of Soft Start time and Idle time before it executes
the next power on sequence configuration register. If more than one regulators are enabled, the PMIC uses the largest value of the
soft start time among the regulators that are enabled in this configuration register.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 171

3.3.6 DIMM Vendor Region Registers (cont’d)

R43 1,2

Table 155 — Register 0x43

Bits

Attribute Default

Description

7

6

5

4

3

RWPE

RWPE

RWPE

RWPE

RWPE

2:0

RWPE

0

0

0

0

R43 [7]: POWER_ON_SEQUENCE_CONFIG3
PMIC Power On Sequence Config 3
0 = Do Not Execute Config 33
1 = Execute Config 3
R43 [6]: POWER_ON_SEQUENCE_CONFIG3_SWA_ENABLE
Enable Switch Node A Output Regulator.
0 = Disable Switch Node A Output Regulator
1 = Enable Switch Node A Output Regulator
R43 [5]: POWER_ON_SEQUENCE_CONFIG3_SWB_ENABLE
Enable Switch Node B Output Regulator.4
0 = Disable Switch Node B Output Regulator
1 = Enable Switch Node B Output Regulator
R43 [4]: POWER_ON_SEQUENCE_CONFIG3_SWC_ENABLE
Enable Switch Node C Output Regulator.
0 = Disable Switch Node C Output Regulator
1 = Enable Switch Node C Output Regulator
R43 [3]: POWER_ON_SEQUENCE_CONFIG3_SWD_ENABLE
Enable Switch Node D Output Regulator.
0 = Disable Switch Node D Output Regulator
1 = Enable Switch Node D Output Regulator
R43 [2:0]: POWER_ON_SEQUENCE_CONFIG3_IDLE
Idle time after Power On Sequence Config 35
000 = 0 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
100 = 8 ms
101 = 10 ms
110 = 12 ms
111 = 24 ms

JPGNetworksLLC

0

001

NOTE 1  If any regulators are enabled in Table 152, “Register 0x40” [6:3], Table 153, “Register 0x41” [6:3] and Table 154, “Register 0x42”

[6:3], those regulators must be configured as ‘1’ in this sequence.

NOTE 2  If more than one configuration register is used for power on sequence, first register must start at Table 152, “Register 0x40” and it

must go in sequential order to Table 155, “Register 0x43” to turn on all desired regulators. In other words, there must not be any
gap of the register that is used for power on sequence.

NOTE 3  If bit [7] = ‘0’, bits [6:3] must be programmed as ‘0000’. If bit [7] = ‘1’, at least one of the bits [6:3] must be programmed as ‘1’.

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’. This bit is a don’t care when Table 166, “Register 0x4F” [0] = ‘1’

NOTE 5  Idle time is the additional time after soft-start time expires. The PMIC waits sum of Soft Start time and Idle time before it executes
the next event. If more than one regulators are enabled, the PMIC uses the largest value of the soft start time among the regulators
that are enabled in this configuration register..

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 172

3.3.6 DIMM Vendor Region Registers (cont’d)

R45

Table 156 — Register 0x45

Bits

Attribute Default

Description

7:1

RWPE

011
1100

0

RWPE

0

R45 [7:1]: SWA_VOLTAGE_SETTING
SWA Output Regulator Voltage Setting1
000 0000 = 800 mV2 or 600 mV3
000 0001 = 805 mV or 605 mV
000 0010 = 810 mV or 610 mV
...
011 1100 = 1100 mV or 900 mV
...
111 1101 = 1425 mV or 1225 mV
111 1110 = 1430 mV or 1230 mV
111 1111 = 1435 mV or 1235 mV
R45 [1:0]:
SWA_POWER_GOOD_THRESHOLD_LOW_SIDE_VOLTAGE_SETTING
SWA Output Threshold Low Side Voltage For Power Good Status
0 = - 5% from the setting in Table 156, “Register 0x45” [7:1]
1 = - 7.5% from the setting in Table 156, “Register 0x45” [7:1]

JPGNetworksLLC

NOTE 1  PMIC guarantees efficiency spec and all electrical characteristics spec within a range of 1050 mV to 1160 mV.

NOTE 2  Table 168, “Register 0x51” [5] = ‘0’; 5 mV step size.

NOTE 3  Table 168, “Register 0x51” [5] = ‘1’; 5 mV step size.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 173

3.3.6 DIMM Vendor Region Registers (cont’d)

R46

Table 157 — Register 0x46

Bits

Attribute Default

Description

7:6

RWPE

01

5:4

RWPE

10

3:2

RWPE

1:0

RWPE

R46 [7:6]:
SWA_POWER_GOOD_THRESHOLD_HIGH_SIDE_VOLTAGE_SETTING
Switch Node A Output Threshold High Side Voltage For Power Good Status
00 = +5% from the setting in Table 156, “Register 0x45” [7:1]
01 = +7.5% from the setting in Table 156, “Register 0x45” [7:1]
10 = +10% from the setting in Table 156, “Register 0x45” [7:1]
11 = Reserved
R46 [5:4]: SWA_OVER_VOLTAGE_THRESHOLD_SETTING
Switch Node A Output Regulator Threshold For Over Voltage Status1
00 = +7.5% from the setting in Table 156, “Register 0x45” [7:1]
01 = +10% from the setting in Table 156, “Register 0x45” [7:1]
10 = +12.5% from the setting in Table 156, “Register 0x45” [7:1]
11 = Reserved
R46 [3:2]: SWA_UNDER_VOLTAGE_LOCKOUT_THRESHOLD_SETTING
Switch Node A Output Regulator Threshold For Under Voltage Lockout Status
00 = -10% from the setting in Table 156, “Register 0x45” [7:1]
01 = -12.5% from the setting in Table 156, “Register 0x45” [7:1]
10 = Reserved
11 = Reserved
R46 [1:0]: SWA_OUTPUT_SOFT_STOP_TIME
SWA Output Regulator Soft Stop Time After VR Disable2
00 = 0.5 ms
01 = 1 ms
10 = 2 ms
11 = 4 ms

JPGNetworksLLC

00

00

NOTE 1  The setting for the Over Voltage must be higher than Power Good High Side Voltage threshold in Table 157, “Register 0x46”[7:6].

NOTE 2  This is the time it takes for buck regulator to go from steady state voltage to 0 V.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 174

3.3.6 DIMM Vendor Region Registers (cont’d)

R47

Bits

Attribute Default

Table 158 — Register 0x47

Description1

7:1

RWPE

011
1100

0

RWPE

0

R47 [7:1]: SWB_VOLTAGE_SETTING
SWB Output Regulator Voltage Setting2
000 0000 = 800 mV3 or 600 mV4
000 0001 = 805 mV or 605 mV
000 0010 = 810 mV or 610 mV
...
011 1100 = 1100 mV or 900 mV
...
111 1101 = 1425 mV or 1225 mV
111 1110 = 1430 mV or 1230 mV
111 1111 = 1435 mV or 1235 mV
R47 [1]:
SWB_POWER_GOOD_THRESHOLD_LOW_SIDE_VOLTAGE_SETTING
SWB Output Threshold Low Side Voltage For Power Good Status
0 = -5% from the setting in Table 158, “Register 0x47” [7:1]
1 = -7.5% from the setting in Table 158, “Register 0x47” [7:1]

JPGNetworksLLC

NOTE 1  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 2  PMIC guarantees efficiency spec and all electrical characteristics spec within a range of 1050 mV to 1160 mV.

NOTE 3  Table 168, “Register 0x51” [4] = ‘0’; 5 mV step size.

NOTE 4  Table 168, “Register 0x51” [4] = ‘1’; 5 mV step size.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

3.3.6 DIMM Vendor Region Registers (cont’d)

JEDEC Standard No. 301-1A.02
Page 175

R48

Bits

Attribute Default

7:6

RWPE

01

5:4

RWPE

3:2

RWPE

1:0

RWPE

Table 159 — Register 0x48

Description1

10

00

R48 [7:6]:
SWB_POWER_GOOD_THRESHOLD_HIGH_SIDE_VOLTAGE_SETTING
SWB Output Threshold High Side Voltage For Power Good Status
00 = +5% from the setting in Table 158, “Register 0x47” [7:1]
01 = +7.5% from the setting in Table 158, “Register 0x47” [7:1]
10 = +10% from the setting in Table 158, “Register 0x47” [7:1]
11 = Reserved
R48 [5:4]: SWB_OVER_VOLTAGE_THRESHOLD_SETTING
SWB Output Regulator Threshold For Over Voltage Status2
00 = +7.5% from the setting in Table 158, “Register 0x47” [7:1]
01 = +10% from the setting in Table 158, “Register 0x47” [7:1]
10 = +12.5% from the setting in Table 158, “Register 0x47” [7:1]
11 = Reserved
R48 [3:2]:
SWB_UNDER_VOLTAGE_LOCKOUT_THRESHOLD_SETTING
SWB Output Regulator Threshold For Under Voltage Lockout Status
00 = -10% from the setting in Table 158, “Register 0x47” [7:1]
01 = -12.5% from the setting in Table 158, “Register 0x47” [7:1]
10 = Reserved
11 = Reserved
R48 [1:0]: SWB_OUTPUT_SOFT_STOP_TIME
SWB Output Regulator Soft Stop Time After VR Disable3
00 = 0.5 ms
01 = 1 ms
10 = 2 ms
11 = 4 ms

JPGNetworksLLC

00

NOTE 1  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 2  The setting for the Over Voltage must be higher than Power Good High Side Voltage threshold in Table 159, “Register 0x48”[7:6].

NOTE 3  This is the time it takes for buck regulator to go from steady state voltage to 0 V.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 176

3.3.6 DIMM Vendor Region Registers (cont’d)

R49

Table 160 — Register 0x49

Bits

Attribute Default

Description

7:1

RWPE

011
1100

R49 [7:1]: SWC_VOLTAGE_SETTING
SWC Output Regulator Voltage Setting1
000 0000 = 800 mV2 or 600 mV3
000 0001 = 805 mV or 605 mV
000 0010 = 810 mV or 610 mV
...
011 1100 = 1100 mV or 900 mV
...
111 1101 = 1425 mV or 1225 mV
111 1110 = 1430 mV or 1230 mV
111 1111 = 1435 mV or 1235 mV
R49 [0]:
SWC_POWER_GOOD_THRESHOLD_LOW_SIDE_VOLTAGE_SETTING
Switch Node C Output Threshold Low Side Voltage For Power Good Status
0 = -5% from the setting in Table 160, “Register 0x49” [7:1]
1 = -7.5 from the setting in Table 160, “Register 0x49” [7:1]
NOTE 1  PMIC guarantees efficiency spec and all electrical characteristics spec within a range of 1050 mV to 1160 mV.

RWPE

0

0

NOTE 2  Table 168, “Register 0x51” [3] = ‘0’; 5 mV step size.

NOTE 3  Table 168, “Register 0x51” [3] = ‘1’; 5 mV step size.

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 177

3.3.6 DIMM Vendor Region Registers (cont’d)

R4A

Table 161 — Register 0x4A

Bits

Attribute Default

Description

7:6

RWPE

01

5:4

RWPE

10

3:2

RWPE

1:0

RWPE

R4A [7:6]:
SWC_POWER_GOOD_THRESHOLD_HIGH_SIDE_VOLTAGE_SETTING
SWC Output Threshold High Side Voltage For Power Good Status
00 = +5% from the setting in Table 160, “Register 0x49” [7:1]
01 = +7.5% from the setting in Table 160, “Register 0x49” [7:1]
10 = +10% from the setting in Table 160, “Register 0x49” [7:1]
11 = Reserved
R4A [5:4]: SWC_OVER_VOLTAGE_THRESHOLD_SETTING
SWC Output Regulator Threshold For Over Voltage Status1
00 = +7.5% from the setting in Table 160, “Register 0x49” [7:1]
01 = +10% from the setting in Table 160, “Register 0x49” [7:1]
10 = +12.5% from the setting in Table 160, “Register 0x49” [7:1]
11 = Reserved
R4A [3:2]:
SWC_UNDER_VOLTAGE_LOCKOUT_THRESHOLD_SETTING
SWC Output Regulator Threshold For Under Voltage Lockout Status
00 = -10% from the setting in Table 160, “Register 0x49” [7:1]
01 = -12.5% from the setting in Table 160, “Register 0x49” [7:1]
10 = Reserved
11 = Reserved
R4A [1:0]: SWC_OUTPUT_SOFT_STOP_TIME
SWC Output Regulator Soft Stop Time After VR Disable2
00 = 0.5 ms
01 = 1 ms
10 = 2 ms
11 = 4 ms

JPGNetworksLLC

00

00

NOTE 1  The setting for the Over Voltage must be higher than Power Good High Side Voltage threshold in Table 161, “Register 0x4A”[7:6].

NOTE 2  This is the time it takes for buck regulator to go from steady state voltage to 0 V.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 178

3.3.6 DIMM Vendor Region Registers (cont’d)

R4B

Table 162 — Register 0x4B

Bits

Attribute Default

Description

7:1

RWPE

011
1100

R4B [7:1]: SWD_VOLTAGE_SETTING
SWD Output Regulator Voltage Setting1
000 0000 = 1500 mV2 or 2200 mV3
000 0001 = 1505 mV or 2205 mV
000 0010 = 1510 mV or 2210 mV
...
011 1100 = 1800 mV or 2500 mV
...
111 1101 = 2125 mV or 2825 mV
111 1110 = 2130 mV or 2830 mV
111 1111 = 2135 mV or 2835 mV
R4B [0]:
SWD_POWER_GOOD_THRESHOLD_LOW_SIDE_VOLTAGE_SETTING
SWD Output Threshold Low Side Voltage For Power Good Status
0 = -5% from the setting in Table 162, “Register 0x4B” [7:1]
1 = -7.5% from the setting in Table 162, “Register 0x4B” [7:1]
NOTE 1  PMIC guarantees efficiency spec and all electrical characteristics spec within a range of 1750 mV to 1850 mV.

RWPE

0

0

NOTE 2  Table 168, “Register 0x51” [0] = ‘0’; 5 mV step size.

NOTE 3  Table 168, “Register 0x51” [0] = ‘1’; 5 mV step size.

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 179

3.3.6 DIMM Vendor Region Registers (cont’d)

R4C

Table 163 — Register 0x4C

Bits

Attribute Default

Description

7:6

RWPE

01

5:4

RWPE

3:2

RWPE

1:0

RWPE

10

00

R4C [7:6]:
SWD_POWER_GOOD_THRESHOLD_HIGH_SIDE_VOLTAGE_SETTING
SWD Output Threshold High Side Voltage For Power Good Status
00 = +5% from the setting in Table 162, “Register 0x4B” [7:1]
01 = +7.5% from the setting in Table 162, “Register 0x4B” [7:1]
10 = Reserved
11 = Reserved
R4C [5:4]: SWD_OVER_VOLTAGE_THRESHOLD_SETTING
SWD Output Regulator Threshold For Over Voltage Status1
00 =+7.5% from the setting in Table 162, “Register 0x4B” [7:1]
01 = +10% from the setting in Table 162, “Register 0x4B” [7:1]
10 = +12.5% from the setting in Table 162, “Register 0x4B” [7:1]
11 = Reserved
R4C [3:2]:
SWD_UNDER_VOLTAGE_LOCKOUT_THRESHOLD_SETTING
SWD Output Regulator Threshold For Under Voltage Lockout Status
00 = -10% from the setting in Table 162, “Register 0x4B” [7:1]
01 = -12.5% from the setting in Table 162, “Register 0x4B” [7:1]
10 = Reserved
11 = Reserved
R4C [1:0]: SWD_OUTPUT_SOFT_STOP_TIME
SWD Output Regulator Soft Stop Time After VR Disable2
00 = 1 ms
01 = 2 ms
10 = 4 ms
11 = 8 ms

JPGNetworksLLC

00

NOTE 1  The setting for the Over Voltage must be higher than Power Good High Side Voltage threshold in Table 163, “Register 0x4C”[7:6].

NOTE 2  This is the time it takes for buck regulator to go from steady state voltage to 0 V.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 180

3.3.6 DIMM Vendor Region Registers (cont’d)

R4D

Table 164 — Register 0x4D

Bits

Attribute Default

Description

7:6

RWPE

10

5:4

RWPE

01

3:2

RWPE

1:0

RWPE

10

R4D [7:6]: SWA_MODE_SELECT
Switch Node A Output Regulator Mode Selection
00 = Reserved
01 = Reserved
10 = COT; DCM (Constant on Time; Discontinuous Current Mode)
11 = COT; CCM (Constant on Time; Continuous Current Mode)
R4D [5:4]: SWA_SWITCHING_FREQ
Switch Node A Output Regulator Switching Frequency
00 = 500 KHz
01 = 750 KHz
10 = 1000 KHz
11 = 1250 KHz
R4D [1:0]: SWB_MODE_SELECT
Switch Node B Output Regulator Mode Selection1
00 = Reserved
01 = Reserved
10 = COT; DCM (Constant on Time; Discontinuous Current Mode)
11 = COT; CCM (Constant on Time; Continuous Current Mode)
R4D [1:0]: SWB_SWITCHING_FREQ
Switch Node B Output Regulator Switching Frequency1
00 = 500 KHz
01 = 750 KHz
10 = 1000 KHz
11 = 1250 KHz

JPGNetworksLLC

01

NOTE 1  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 181

3.3.6 DIMM Vendor Region Registers (cont’d)

R4E

Table 165 — Register 0x4E

Bits

Attribute Default

Description

7:6

RWPE

10

5:4

RWPE

01

3:2

RWPE

1:0

RWPE

10

R4E [7:6]: SWC_MODE_SELECT
Switch Node C Output Regulator Mode Selection
00 = Reserved
01 = Reserved
10 = COT; DCM (Constant on Time; Discontinuous Current Mode)
11 = COT; CCM (Constant on Time; Continuous Current Mode)
R4E [5:4]: SWC_SWITCHING_FREQ
Switch Node C Output Regulator Switching Frequency
00 = 500 KHz
01 = 750 KHz
10 = 1000 KHz
11 = 1250 KHz
R4E [3:2]: SWD_MODE_SELECT
Switch Node D Output Regulator Mode Selection
00 = Reserved
01 = Reserved
10 = COT; DCM (Constant on Time; Discontinuous Current Mode)
11 = COT; CCM (Constant on Time; Continuous Current Mode)
R4E [1:0]: SWD_SWITCHING_FREQ
Switch Node D Output Regulator Switching Frequency
00 = 500 KHz
01 = 750 KHz
10 = 1000 KHz
11 = 1250 KHz

JPGNetworksLLC

01

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 182

3.3.6 DIMM Vendor Region Registers (cont’d)

R4F

Table 166 — Register 0x4F

Bits

Attribute Default

Description

7

RWPE

6:5

RWPE

4

3

2

1

0

RWPE

RV

RWPE

RWPE

RWPE

0

0

0

0

0

R4F [7]: OUTPUT_REGULAOTRS_DISABLE_CONTROL1
Output Regulator SWA, SWB, SWC and SWD Disable Control for OV and
UV.
0 = Disable all switching regulators of PMIC2
1 = Disable only the affected switching output regulator; Rest of the PMIC’s
switching regulators remains operations3
R4F [6:5]: Reserved
R4F [4]: SWA_OUTPUT_REGULATOR_REMOTE_SENSING
SWA Output Regulator Remote Sensing Scheme on DIMM
0 = Single Ended Remote Sensing on DIMM.1 = Differential Remote Sensing
on DIMM
R4F [3]: Reserved
R4F [2]: SWC_OUTPUT_REGULATOR_REMOTE_SENSING
SWC Output Regulator Remote Sensing Scheme on DIMM
0 = Single Ended Remote Sensing on DIMM.
1 = Differential Remote Sensing on DIMM
R4F [1]: SWD_OUTPUT_REGULATOR_REMOTE_SENSING
SWD Output Regulator Remote Sensing Scheme on DIMM
0 = Single Ended Remote Sensing on DIMM; Use SWD_FB_N pin as PID
input pin to determine the PMIC’s ID4
1 = Differential Remote Sensing on DIMM5
R4F [0]: SWA_SWB_PHASE_MODE_SELECT
Switch Node A and Switch Node B Phase Regulator Mode Selection.
0 = Single Phase Regulator Mode
1 = Dual Phase Regulator Mode

JPGNetworksLLC

0

0

NOTE 1  Applicable to Output Over Voltage and Output Under Voltage. For VIN_Bulk input over voltage or VBIAS under voltage or

VIN_Bulk Input under voltage, this bit does not apply and the PMIC always disables all switching regulators.

NOTE 2  For standard DDR5 RDIMM and DDR5 LRDIMM, this bit must be always configured to ‘0’.

NOTE 3  For DDR5 NVDIMM or any other custom DIMM, this bit can be configured to either ‘0’ or ‘1’ as desired. This is applicable only

after VR_ENABLE bit is set to ‘1’. Prior to VR_ENABLE bit is set to ‘1’, PMIC keeps all buck regulator off.

NOTE 4  Up to three different PMIC can be placed on DIMM module.
NOTE 5  Only one PMIC can be placed on DIMM module.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 183

3.3.6 DIMM Vendor Region Registers (cont’d)

R50

Table 167 — Register 0x50

Bits

Attribute Default

Description

R50 [7:6]:
SWA_OUTPUT_CURRENT_LIMITER_WARNING_THRESHOLD_
SETTING

7:6

RWPE

0

PMIC5000 COT Mode, Ivalley_limit:
00 = 4.0 A
01 = 4.5 A
10 = 5.0 A
11 = 5.5 A

5:4

RWPE

PMIC5010 COT Mode, Ivalley_limit:
00 = 2.0 A
01 = 2.5 A
10 = 3.0 A
11 = 3.5 A
R50 [5:4]:
SWB_OUTPUT_CURRENT_LIMITER_WARNING_THRESHOLD_
SETTING

JPGNetworksLLC

PMIC5000 COT Mode, Ivalley_limit1:
00 = 4.0 A
01 = 4.5 A
10 = 5.0 A
11 = 5.5 A

PMIC5010 COT Mode, Ivalley_limit:
00 = 2.0 A
01 = 2.5 A
10 = 3.0 A
11 = 3.5 A
R50 [3:2]:
SWC_OUTPUT_CURRENT_LIMITER_WARNING_THRESHOLD_
SETTING

0

3:2

RWPE

0

PMIC5000 COT Mode, Ivalley_limit:
00 = 4.0 A
01 = 4.5 A
10 = 5.0 A
11 = 5.5 A

PMIC5010 COT Mode, Ivalley_limit:
00 = 2.0 A
01 = 2.5 A
10 = 3.0 A
11 = 3.5 A

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 184

3.3.6 DIMM Vendor Region Registers (cont’d)

Table 167 — Register 0x50 (cont’d)

R50

Bits

Attribute Default

Description

R50 [1:0]:
SWD_OUTPUT_CURRENT_LIMITER_WARNING_THRESHOLD_
SETTING

1:0

RWPE

0

PMIC5000 COT Mode, Ivalley_limit:
00 = 4.0 A
01 = 4.5 A
10 = 5.0 A
11 = 5.5 A

NOTE 1  This register is applicable regardless of the setting in Table 166, “Register 0x4F” [0].

PMIC5010 COT Mode, Ivalley_limit:
00 = 2.0 A
01 = 2.5 A
10 = 3.0 A
11 = 3.5 A

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 185

3.3.6 DIMM Vendor Region Registers (cont’d)

R51

Table 168 — Register 0x51

Bits

Attribute Default

Description

0

R51 [7:6]: VOUT_1.8V_VOLTAGE_SETTING
VOUT 1.8 V LDO Output Voltage Setting1
00 = 1.7 V
01 = 1.8 V
10 = 1.9 V
11 = Reserved
R51 [5]: SWA_VOLTAGE_RANGE
SWA Output Voltage Range Selection2
0 = Range: 800 mV to 1435 mV for SWA; 5 mV step size.
1 = Range: 600 mV to 1235 mV for SWA; 5 mV step size
R51 [4]: SWB_VOLTAGE_RANGE
SWB Output Voltage Range Selection3,4
0 = Range: 800 mV to 1435 mV for SWB; 5 mV step size
1 = Range: 600 mV to 1235 mV for SWB; 5 mV step size
R51 [3]: SWC_VOLTAGE_RANGE
SWC Output Voltage Range Selection5
0 = Range: 800 mV to 1435 mV for SWC; 5 mV step size
1 = Range: 600 mV to 1235 mV for SWC; 5 mV step size
R51 [2:1]: VOUT_1.0V_VOLTAGE_SETTING
VOUT 1.0 V LDO Voltage Setting
00 = 0.9 V
01 = 1.0 V
10 = 1.1 V
11 = 1.2 V
R51 [0]: SWD_VOLTAGE_RANGE
SWD Output Voltage Range Selection6
0 = Range: 1500 mV to 2135 mV for SWD; 5 mV step size
1 = Range: 2200 mV to 2835 mV for SWD; 5 mV step size

JPGNetworksLLC

0

0

01

7:6

RWPE

01

5

4

3

RWPE

0

RWPE

RWPE

2:1

RWPE

0

RWPE

register.

NOTE 1  The VOUT_1.8V Power Good threshold in register Table 116, “Register 0x1A” [2] is always fixed regardless of the setting in this

NOTE 2  Range and resolution selection applies to registers Table 156, “Register 0x45” [7:1].

NOTE 3  Range and resolution selection applies to registers Table 158, “Register 0x47” [7:1].

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 5  Range and resolution selection applies to registers Table 160, “Register 0x49” [7:1].

NOTE 6  Range and resolution selection applies to registers Table 162, “Register 0x4B” [7:1].

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 186

3.3.6 DIMM Vendor Region Registers (cont’d)

R58 1

Table 169 — Register 0x58

Bits

Attribute Default

Description

7

6

5

4

3

RWPE

RWPE

RWPE

RWPE

RWPE

2:0

RWPE

0

0

0

0

R58 [7]: POWER_OFF_SEQUENCE_CONFIG0
PMIC Power Off Sequence Config 0
0 = Do Not Execute Config 02
1 = Execute Config 0
R58 [6]: POWER_OFF_SEQUENCE_CONFIG0_SWA_DISABLE
Disable SWA Output Regulator.
0 = Do Not Disable SWA Output Regulator
1 = Disable SWA Output Regulator
R58 [5]: POWER_OFF_SEQUENCE_CONFIG0_SWB_DISABLE
Disable Switch Node B Output Regulator.3
0 = Do Not Disable SWB Output Regulator
1 = Disable SWB Output Regulator
R58 [4]: POWER_OFF_SEQUENCE_CONFIG0_SWC_DISABLE
Disable Switch Node C Output Regulator.
0 = Do Not Disable SWC Output Regulator
1 = Disable SWC Output Regulator
R58 [3]: POWER_OFF_SEQUENCE_CONFIG0_SWD_DISABLE
Disable SWD Output Regulator.
0 = Do Not Disable SWD Output Regulator
1 = Disable SWD Output Regulator
R58 [2:0]: POWER_OFF_SEQUENCE_CONFIG0_IDLE
Idle time after Power Off Sequence Config 04
000 = 0 ms
001 = 1 ms
010 = 2 ms
011 = 3 ms
100 = 4 ms
101 = 5 ms
110 = 6 ms
111 = 7 ms

JPGNetworksLLC

0

0

NOTE 1  If more than one configuration register is used for power off sequence, first register must start at Table 169, “Register 0x58” and it
must go in sequential order to Table 172, “Register 0x5B” to turn off all regulators. In other words, there must not be any gap of the
register that is used for power off sequence.

NOTE 2  If bit [7] = ‘0’, bits [6:3] must be programmed as ‘0000’.If bit [7] = ‘1’, at least one of the bits [6:3] must be programmed as ‘1’.

NOTE 3  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 4  Idle time is the additional time after soft-stop time expires. The PMIC waits sum of soft stop time and idle time before it executes
the next power off sequence configuration register. If more than one regulators are disabled, the PMIC uses the largest value of the
soft stop time among the regulators that are disabled in this configuration register.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 187

3.3.6 DIMM Vendor Region Registers (cont’d)

Table 170 — Register 0x59

R59 1,2

Bits

Attribute Default

Description

7

6

5

4

3

RWPE

RWPE

RWPE

RWPE

RWPE

2:0

RWPE

0

0

0

0

R59 [7]: POWER_OFF_SEQUENCE_CONFIG1
PMIC Power Off Sequence Config13
0 = Do Not Execute Config 1
1 = Execute Config 1
R59 [6]: POWER_OFF_SEQUENCE_CONFIG1_SWA_DISABLE
Disable SWA Output Regulator.
0 = Do Not Disable SWA Output Regulator
1 = Disable SWA Output Regulator
R59 [5]: POWER_OFF_SEQUENCE_CONFIG1_SWB_DISABLE
Disable Switch Node B Output Regulator.4
0 = Do Not Disable SWB Output Regulator
1 = Disable SWB Output Regulator
R59 [4]: POWER_OFF_SEQUENCE_CONFIG1_SWC_DISABLE
Disable Switch Node C Output Regulator.
0 = Do Not Disable SWC Output Regulator
1 = Disable SWC Output Regulator
R59 [3]: POWER_OFF_SEQUENCE_CONFIG1_SWD_DISABLE
Disable Switch Node D Output Regulator.
0 = Do Not Disable SWD Output Regulator
1 = Disable SWD Output Regulator
R59 [2:0]: POWER_OFF_SEQUENCE_CONFIG1_IDLE
Idle time after Power Off Sequence Config 15
000 = 0 ms
001 = 1 ms
010 = 2 ms
011 = 3 ms
100 = 4 ms
101 = 5 ms
110 = 6 ms
111 = 7 ms

JPGNetworksLLC

0

0

NOTE 1  If any regulators are disabled in Table 169, “Register 0x58” [6:3], those regulators must be configured as ‘1’ in this sequence.

NOTE 2  If more than one configuration register is used for power off sequence, first register must start at Table 169, “Register 0x58” and it
must go in sequential order to Table 172, “Register 0x5B” to turn off all regulators. In other words, there must not be any gap of the
register that is used for power off sequence.

NOTE 3  If bit [7] = ‘0’, bits [6:3] must be programmed as ‘0000’.If bit [7] = ‘1’, at least one of the bits [6:3] must be programmed as ‘1’.

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 5  Idle time is the additional time after soft-stop time expires. The PMIC waits sum of soft stop time and idle time before it executes
the next power off sequence configuration register. If more than one regulators are disabled, the PMIC uses the largest value of the
soft stop time among the regulators that are disabled in this configuration register.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 188

3.3.6 DIMM Vendor Region Registers (cont’d)

R5A 1,2

Table 171 — Register 0x5A

Bits

Attribute Default

Description

7

6

5

4

3

RWPE

RWPE

RWPE

RWPE

RWPE

2:0

RWPE

0

0

0

0

R5A [7]: POWER_OFF_SEQUENCE_CONFIG2
PMIC Power Off Sequence Config 23
0 = Do Not Execute Config 2
1 = Execute Config 2
R5A [6]: POWER_OFF_SEQUENCE_CONFIG2_SWA_DISABLE
Disable SWA Output Regulator.
0 = Do Not Disable SWA Output Regulator
1 = Disable SWA Output Regulator
R5A [5]: POWER_OFF_SEQUENCE_CONFIG2_SWB_DISABLE
Disable Switch Node B Output Regulator.4
0 = Do Not Disable SWB Output Regulator
1 = Disable SWB Output Regulator
R5A [4]: POWER_OFF_SEQUENCE_CONFIG2_SWC_DISABLE
Disable Switch Node C Output Regulator.
0 = Do Not Disable SWC Output Regulator
1 = Disable SWC Output Regulator
R5A [3]: POWER_OFF_SEQUENCE_CONFIG2_SWD_DISABLE
Disable Switch Node D Output Regulator.
0 = Do Not Disable SWD Output Regulator
1 = Disable SWD Output Regulator
R5A [2:0]: POWER_OFF_SEQUENCE_CONFIG2_IDLE
Idle time after Power Off Sequence Config 25
000 = 0 ms
001 = 1 ms
010 = 2 ms
011 = 3 ms
100 = 4 ms
101 = 5 ms
110 = 6 ms
111 = 7 ms

JPGNetworksLLC

0

0

NOTE 1  If any regulators are disabled in Table 169, “Register 0x58” [6:3], and Table 170, “Register 0x59” [6:3] those regulators must be

configured as ‘1’ in this sequence.

NOTE 2  If more than one configuration register is used for power off sequence, first register must start at Table 169, “Register 0x58” and it
must go in sequential order to Table 172, “Register 0x5B” to turn off all regulators. In other words, there must not be any gap of the
register that is used for power off sequence.

NOTE 3  If bit [7] = ‘0’, bits [6:3] must be programmed as ‘0000’.If bit [7] = ‘1’, at least one of the bits [6:3] must be programmed as ‘1’.

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

NOTE 5  Idle time is the additional time after soft-stop time expires. The PMIC waits sum of soft stop time and idle time before it executes
the next power off sequence configuration register. If more than one regulators are disabled, the PMIC uses the largest value of the
soft stop time among the regulators that are disabled in this configuration register.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 189

3.3.6 DIMM Vendor Region Registers (cont’d)

R5B 1,2

Table 172 — Register 0x5B

Bits

Attribute Default

Description

7

6

5

4

3

RWPE

RWPE

RWPE

RWPE

RWPE

2:0

RV

0

0

0

0

R5B [7]: POWER_OFF_SEQUENCE_CONFIG3
PMIC Power Off Sequence Config 33
0 = Do Not Execute Config 3
1 = Execute Config 3
R5B [6]: POWER_OFF_SEQUENCE_CONFIG3_SWA_DISABLE
Disable SWA Output Regulator.
0 = Do Not Disable SWA Output Regulator
1 = Disable SWA Output Regulator
R5B [5]: POWER_OFF_SEQUENCE_CONFIG3_SWB_DISABLE
Disable SWB Output Regulator.4
0 = Do Not Disable SWB Output Regulator
1 = Disable SWB Output Regulator
R5B [4]: POWER_OFF_SEQUENCE_CONFIG3_SWC_DISABLE
Disable Switch Node C Output Regulator.
0 = Do Not Disable SWC Output Regulator
1 = Disable SWC Output Regulator
R5B [3]: POWER_OFF_SEQUENCE_CONFIG3_SWD_DISABLE
Disable Switch Node D Output Regulator.
0 = Do Not Disable SWD Output Regulator
1 = Disable SWD Output Regulator
R5B [2:0]: Reserved

JPGNetworksLLC

0

0

NOTE 1  If any regulators are disabled in Table 169, “Register 0x58” [6:3], Table 170, “Register 0x59” [6:3] and Table 171, “Register

0x5A” [6:3], those regulators must be configured as ‘1’ in this sequence.

NOTE 2  If more than one configuration register is used for power off sequence, first register must start at Table 169, “Register 0x58” and it
must go in sequential order to Table 172, “Register 0x5B” to turn off all regulators. In other words, there must not be any gap of the
register that is used for power off sequence.

NOTE 3  If bit [7] = ‘0’, bits [6:3] must be programmed as ‘0000’.If bit [7] = ‘1’, at least one of the bits [6:3] must be programmed as ‘1’.

NOTE 4  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 190

3.3.6 DIMM Vendor Region Registers (cont’d)

R5D

Table 173 — Register 0x5D

Bits

Attribute Default

Description

NOTE 1  This is the time it takes for buck regulator to go from 0 V to steady state voltage (the actual voltage varies based on

pre-programmed voltage).

NOTE 2  Only applicable if Table 166, “Register 0x4F” [0] = ‘0’.

001

0

R5D [7:5]: SWA_OUTPUT_SOFT_START_TIME
SWA Output Regulator Soft Start Time After VR Enable1
000 = 1 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
...
111 = 14 ms
R5D [4]: Reserved
R5D [3:1]: SWB_OUTPUT_SOFT_START_TIME
SWB Output Regulator Soft Start Time After VR Enable1,2
000 = 1 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
...
111 = 14 ms
R5D [0]: Reserved

JPGNetworksLLC

R5E [7:5]: SWC_OUTPUT_SOFT_START_TIME
SWC Output Regulator Soft Start Time After VR Enable1
000 = 1 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
...
111 = 14 ms
R5E [4]: Reserved
R5E [3:1]: SWD_OUTPUT_SOFT_START_TIME
SWD Output Regulator Soft Start Time After VR Enable1
000 = 1 ms
001 = 2 ms
010 = 4 ms
011 = 6 ms
...
111 = 14 ms
R5E [0]: Reserved

Table 174 — Register 0x5E

Description

7:5

RWPE

001

4

RV

0

3:1

RWPE

0

RV

R5E

Bits

Attribute Default

7:5

RWPE

001

4

RV

0

3:1

RWPE

001

0

RV

0

NOTE 1  This is the time it takes for buck regulator to go from 0 V to steady state voltage (the actual voltage varies based on

pre-programmed voltage)

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 191

Annex A (Informative) - Differences between Revisions

A.1   Differences between JESD301-1A and JESD301-1 (June 2020)

Version

Rev 1.3

Release
Date

August 20
2020

Rev 1.4

October 1
2020

Changes

Clause 1.9.2: Wording clarification.
Table 94 to Table 97: Updated program and erase time values.
Table 143: Deleted first statement in footnote 5 for clarification.
Table 18: Updated Ron min value.
Clause B.3.5.1: Added clarification.
Table 100, Table 70: Added
clarification. clause 1.8.8: Added
description.
Clause 1.8.5, 1.8.9, 1.8.10, 1.8.12, 1.8.14, 1.8.15: Updated with new definition.
Table 22: Added note 1.

JPGNetworksLLC

Table 54. Table 72, Table 73: Deleted RSTDAA direct CCC.
Table 21: Updated temperature spec to be compliant with JESD402-1.
Table 15: Separated output slew rate value.
Table 137: Updated bit [2] definition and associated footnote.
Table 140: Updated bit [5:3] definition and associated footnotes.
Table 93: Updated functional description.
Clause 1.8.5: Deleted entire clause.
Clause 1.8.7: Updated definition.
Clause 1.8.9: Updated definition.
Clause 1.8.1: Added clarification.
Table 86: Updated CAMP pin description.
Figure 11, Figure 12: Updated drawing for clarification.
Clause 1.14.1: Updated definition.
Global update: Re-labeled PWR_GOOD pin w/ CAMP; secure mode with write protect
mode; programmable mode with non write protect mode

Rev 1.5

October 3
2020

  Corrected typo.

  Clause : Corrected typo.

  Added clarification.

  Added cross reference.

  Added Hi-Z clarification.

  Clause: Editorial cleanup.
  Added missing transition

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 192

A.1 Differences between JESD301-1A and JESD301-1 (June 2020) (cont’d)

Version

Release Date

Changes

Rev 1.6

Oct. 15, 2020

Rev 1.7

Oct. 17, 2020

Rev 1.7a

Dec. 10, 2020

  Section
  Corrected typo
  Section
  Updated label
  Section
  Added cross reference; added cautionary statement.
  Added clarification
  Updated pin numbers to align with
  Updated figure
  Section
  Added clarification
  Marked write protect register
  Section
  Added section about defective LDO failure behavior
  Added filter parameter for LDO outputs
  Added R32[5] definition.
  Updated mapping from R32[5] to R32[3]
  Section
  Fixed typo
  Section
  Added clarification statement.
 Table 65, Table 66: Deleted Repeat Start condition.
 Table 100: Added additional clarification.
 Table 138: Added footnote 2 for clarification.
 Section 1.2.2: Editorial correction.
 Table 13: Editorial correction.
 Table 14: Editorial correction; deleted row
 Table 15: Editorial correction
  Section 1.8.1: Editorial correction.
  Section 1.8.2: Editorial correction.
  Section 1.8.10: Editorial correction.
  Section 1.8.7.3: Editorial correction.
  Section 1.8.11: Editorial correction.
  Table 166: Editorial correction.
  Table 26: Editorial correction in footnote.
  Table 117: Editorial correction.
  Table 142: Changed the register attribute definition and added notes.
  Figure 17: Added clarification.

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 193

A.1 Differences between JESD301-1A and JESD301-1 (June 2020) (cont’d)

Version

Release Date

Changes

Rev 1.8

Dec. 18, 2020   Table 138: Updated footnote 2 delay value to 9 ms.

Rev 1.8a

Feb. 2, 2021

  Inclusive terminology updated throughout the document.
  Figure 18: Added inclusive terminology.
  Figure 19: Added inclusive terminology.
  Figure 20: Added inclusive terminology.
  Figure 21: Added inclusive terminology.
  Figure 22: Added inclusive terminology.
  Table 19 and notes 7,9,10: Added inclusive terminology.
  Clause 1.11.9: Added inclusive terminology.

A.3 Differences between JESD301-1A.02 and JESD301-1A.01 (October 2022)

A.2   Differences between JESD301-1A.01 and JESD301-1A (August 2021)

1.   Table 2: Updated Footnote 2

2.   Table 86: Added NC pin definition

JPGNetworksLLC

Description

 Table 2:   Updated VIN_Bulk Ramp Down minimum value

 Table 15:   Corrected IOL/IOH minimum and maximum values, respectively

 Clause 2.7.7.1:   Added clarification

Page

3

12

32

Editorial corrections as outlined in the following summary.

33/34

 Clause 2.7.9:   Added clarification

35

105

110

111

117

128

134

135

 Table 27:   Corrected typographical error

 Table 92:   Added missing register to the list

 Clause 3.3.5:   Added editorial explanation

 Figure 33:   Added

 Table 99:   Editorial re-wording of Footnote #3

 Clause 3.3.5.3:   Added missing register reference

 Table 116:   Editorial correction of the cross reference pointer

 Table 117:   Corrected typographical error in Footnote #3

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

JEDEC Standard No. 301-1A.02
Page 194

JPGNetworksLLC

This page intentionally left blank

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

Revision 1.8.5

Standard Improvement Form

JEDEC Standard JESD301-1A.02

The purpose of this form is to provide the Technical Committees of JEDEC with input from the industry
regarding usage of the subject standard. Individuals or companies are invited to submit comments to
JEDEC. All comments will be collected and dispersed to the appropriate committee(s).

If you can provide input, please complete this form and return to:

JEDEC
Attn: Publications Department
3103 North 10th Street
Suite 240 South
Arlington, VA  22201-2107

Fax: 703.907.7583

1.

I recommend changes to the following:
Requirement, clause number

Test method number

The referenced clause number has proven to be:
In Error

Too Rigid

Unclear

Other

Clause number

JPGNetworksLLC

2.   Recommendations for correction:

3.   Other suggestions for document improvement:

Submitted by
Name:
Company:
Address:
City/State/Zip:

Phone:
E-mail:

Date:

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST

JPGNetworksLLC

Downloaded by John Greninger (admin@protocolpp.com) on Mar 8, 2024, 7:24 pm PST


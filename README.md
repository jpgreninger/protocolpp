# Protocolpp(Protocol++) 3.0.0
Networking and Encryption Library, Testbench, and Drivers

Only www.protocolpp.com has the rights to update, modify,
license, distribute, sell, or make copies of Protocolpp(Protocol++).

Evaluation licenses that last 60-days are available from the website free
of charge

Full licenses last a year and include support and updates

Protocol++ has several different interfaces and can be configured
in different ways. Preview the Makefile to see the target. Descriptions
of the different targets are found below. Contrary to some people's opinion,
ProtocolPP(Protocol++) is not a "WORK IN PROGRESS". The core library has
remained unchanged for several years. Changes have only been added when
updating to new versions of tinyxml2 parser or the Crypto++ library. NEW
items have been added (drivers, IKEv2, Security Associations) that sit
on top of the core library of protocols, ciphers, and authentication
algorithms with randomizers, parsers, anti-replay, and structures
necessary for complete functionality

Issued copyrights

* Protocol++(Protocolpp) 1.0.0 - TXu002059872
* Protocol++(Protocolpp) 1.2.7 - TXu002066632
* Protocol++(Protocolpp) 1.4.0 - TXu002082674
* Protocol++(Protocolpp) 2.0.0 - TXu002097880
* JPGNetworks - VAu001334497

Trademarks

* JPGNetworks - 87708008

protocolpp - Executable of the full set of protocols, ciphers, testbench,
             and responders to provide a command line interface for
             connecting and testing a device under test (DUT). A user
             can opt to use the jresponder (default) or use QorIQ and
             Layerscape compatible testbench by setting PLATFORM to
             SECPLAT. If using the SEC platform, the testbench only
             reads and writes to the software rings as it is expected
             that the SEC connected to the other side of the software
             rings. See the file jbuilder.cpp

libprotocolpp.a - Static library of the protocolpp.h interface, wasp.h, and ciphers.h

libprotocolpp.so.3.0.0 - Shared library of the protocolpp.h interface, wasp.h, and ciphers.h

winprot++.lib - Static library for Windows compiled under VC++ 19

rdriver - Ring driver that for UDP, TCP, TLS, or SRTP. Underlying protocols include
          ICMP, IP, IPsec, MACsec, Ethernet, LTE, RLC, Wifi, WiGig, WiMax with separate
          threads that run both the send and receive functions from the rings

ddriver - Same as the ring driver except the input and output are queues rather than
          rings and have push and pop routines to send and receive packets

driver  - Unlike the two previous drivers, the calling program must feed the driver
          with single packets that are driven onto the socket. The calling program
          must also poll the receive method continually to obtain packets from the
          receive socket

ikev2   - Support for Internet Key Exchange (IKE) version 2 for IPsec ESP with CHACHA20
          AES-GCM, AES-CCM, AES-CBC, AES-CTR, and Camellia. All Diffie-Hellman curves
          supported including 448 and 25519. Suppoort for all authentication methods
          now supported (RSA, PSK, ECDSA, DSA)

test - Runs the CPPUNIT tests for Protocol++. Message outputs are for negative testing

Supported Platforms

* RedHat Enterprise 7.2 GCC5.3.1 x64, i686
* Ubuntu 18.04 GCC5.5.0 x64, i686
* Fedora GCC7.2 x64, i686
* SUSE Enterprise GCC8.2 x64, i686
* openSUSE 15.1 GCC8.2 x64, i686
* Windows 10 VC++19 x64, i686
* ARM (Coming Soon)

USE CASES

Protocol++(ProtocolPP) can be used for several different use cases in development,
software, hardware development, stacks, and testbenches.

  * TESTBENCHES - Protocolpp comes with a testbench to allow the interface to be connected
    to a Device Under Test (DUT) through software rings for test of protocols, encryption,
    and authentication algroithms, replay windows, randomization, Diffie-Hellman
    routines, and other items. In addition, Protocol++ can be used to generate XML output
    for all of the above items that can be read back in to drive Verilog or software
    drivers for development of hardware accelerators and software

  * STACKS - The drivers in ProtocolPP show examples of how to write software stacks that
    support all levels of the OSI model to allow full manipulation of all features and
    methodologies of the protocol stack. Want to try out a new retry routine for TCP? 
    Change the code in level 4 of your software stack to try it out. Want to try a new
    algorithm for IPsec? Add it to level 3 of the stack. Developing a driver for 
    extended packet numbers in Macsec? Run your software against the Protocol++ testbench
    to ensure conformance. Additional protocols that do not need need the stack and
    require direct access to level 3 (IP/IPsec) such as Real Time Protocol (RTP) or its
    secure version (SRTP)? Disable TCP/UDP and TLS to drive IP/IPsec directly

  * HARDWARE DEVELOPMENT - Protocol++ can be used for testing hardware accelerators that
    support encryption and authentication algorithms. Developing an AES-GCM engine for
    your hard drive controller? Instantiate AES-GCM using the "ciphers" interface of 
    ProtocolPP in your SystemC testbench to driver your Verilog or VHDL through your UVM
    driver. Received your silicon back from manufacting and need to verify there are no
    defects? Read back in the XML files generated during pre-silicon testing that achieves
    100% coverage, and execute them through ProtocolPP's driver (or your own driver) and
    compare to the expected value. Have some conformance vectors from the specification?
    Enter the conformance data into the XML format specified by Protocol++'s XML schema,
    read the data into the testbench or driver, and test the silicon and or RTL

  * SOFTWARE - The elements of ProtocolPP can be incorporated into larger software projects
    to encrypt data, authenticate, generate CRC32 values, create Signatures, verify
    signatures, create PRF material, generate random data over ranges as bytes, words, or
    double words, enable SMFT mode and generate millions of random bytes from hardware
    is little or no time

These are the use cases currently being used. Development continues for Internet Key
Exchange (IKEv2), additional driver features (ICMP message generation and return), offline
key protection, key ring use, etc.

Please see the documentation found above and www.protocolpp.com for all options

INSTALLATION

To install Protocol++, the cryptopp library must first be compiled and installed

www.cryptopp.com

USAGE: protocolpp [options]

Options:

  --help, -h   Print usage and exit
  
  --in, -i     Input file (either *.ppp or *.protopp)
  
  --out, -o    Output file (*.protpp)
  
  --seed, -s   Seed for reproducibility
  
  --log, -l    Path to output simulation log
  
  --size, -z   Size of the rings in entries
  
  --resp, -r   Number of responders
  
  --thread, -t Number of threads per responder
  
  --plat, -p   Platform to run (WASPLAT or SECPLAT)
  
  --endian, -e Endiness of the platform (BIG or LITTLE)
  
  --ptr, -q    Size of address pointers in bytes (4 or 8 default=8)
  
  --sgt, -g    Size of SG entries in bytes (8 or 16 default=16)
  
  --irg, -n    Address of the input ring
  
  --org, -z    Address of the output ring

Examples:

  protocolpp --in file1.ppp
  protocolpp -i file1.protpp
  protocolpp --in file1.ppp --out file2.protpp
  protocolpp --seed 1234567890 -i file1.protpp
  protocolpp --seed 1234567890 -i file1.ppp
  protocolpp -i file1.ppp -l filelog -z 50
  protocolpp --in file2.protpp --log filelog -r 2 -z 40
  protocolpp --seed 1234567890 --in file2.protpp --log filelog --resp 2
  protocolpp --seed 1234567890 --plat SECPLAT --in file2.protpp --log filelog
  protocolpp --seed 1234567890 -i file1.ppp -l filelog

For W.A.S.P usage, see the doxygen section

* See www.protocolpp.com for further updates, information and licensing

* New in 2.5.5

  * Moved to Crypto++ 8.2.0

* New in 2.5.4

  * Moved to Crypto++ 8.1.0

* New in 2.5.3 (Sun Feb 10 23:37:22 2019 -0700)

  * Split out signature classes as separate functions
  * Used new classes in IKEv2 to streamline code
  * Updated documentation to fix math symbols and equations using LaTeX math
  * Removed obsolete ciphers, authentication, dh curves from IKEv2
  * Generated PDF from all documentation (1007 pages)
  * Updated schema to include restrictions

* New in 2.5.2 (Sun Jan 20 21:30:58 2019 -0700)

  * New class jdsa
  * New class jecdsa
  * New class jrsa
  * Updated copyright to 2019

* New in 2.5.1 (Sun Jan 6 12:45:27 2019 -0700)

  * Moved to Crypto++ v8.0.0
  * Moved to tinyxml2 v7.0.1

* New in 2.5.0 (Mon Dec 31 21:15:03 2018 -0700)

  * Separated IKEv2 functions into separate classes
  * New class jikeparse
  * New class jikev2dh
  * New class jikencrypt
  * New class jikeprf

* New in 2.4.3 (Sat Dec 23 21:39:15 2018 -0700)

  * All encryption schemes for IKEv2 working (CBC, CTR, GCM, CCM, DES, 3DES, CHACHA)
  * All integrity schemes for IKEv2 working (MD5, SHA, SHA2-256, SHA2-384, SHA2-512, AES-CMAC, AES-GMAC, POLY1305)
  * All PRF schemes for IKEv2 working (MD5, SHA, SHA2-256, SHA2-384, SHA2-512, AES-CMAC, AES-XCBC-MAC)
  * 80% of Key exchange schemes working (MODP, ECP, missing curve25514 and curve448)
  * All encryption, integrity, Diffie-Hellman, and Signatures tested against StrongSwan IKEv2 (www.strongswan.org)
  * Added all conformance vectors for CCM, CMAC, XCBC-MAC, GCM, CHACHA20, POLY1305, SM3, SM4, ARIA to cppunit tests
  * Fixed small bug in jrand
  * Added Appendix A from employment agreement to clarify ownership
  * Crypto++ support for curve25519 and curve448 not quite ready https://stackoverflow.com/questions/50408019/crypto-ed448-unknown-oid

* New in 2.4.2 (Sun Dec 24 15:22:38 2018 -0700)

  * GIT log for all time

* New in 2.4.1 (Sun Dec 24 17:58:22 2018 -0700)

  * Working IKEv2 for AES-CBC, SHA256, MODP1024 (see log files)

* New in 2.4.0 (Mon Nov 26 22:13:39 2018 -0700)

  * Added delete_sa() to IKEv2
  * Fixed SKEYSEED and KEYMAT generation
  * Fixed AUTH payload generation
  * Fixed preshared key authentication
  * Fixed key ring issues
  * Added key ring to drivers
  * Added ability to daemonize IKEv2

* New in 2.3.3 (Tue Oct 30 19:02:06 2018 -0700)

  * Moved from pthread to std::thread
  * Moved to CryptoPP 7.0.0 for SM3, SM4, Poly1305, ARIA encryption engines
  * Documentation updates

* New in 2.3.2 (Sun Oct 21 19:02:35 2018 -0700)

  * Support for all IKEv2 encryption algorithms (CHACHA20, AEAD, Camellia)
  * Support for all IKEv2 Diffie-Hellman curves (including 22855 and 485)
  * Support for multiple IPsec connections

* New in 2.3.0 (Sun Oct 7 17:59:27 2018 -0700)

  * IKE configuration parser working
  * Updated DH parameters with all RFC value except group 31 and 32
  * Fixed gateway lookup of HWADDR
  * Updated to include Ethernet
  * Discard of packet not for this interface

* New in 2.2.0 (Fri Sep 14 22:36:21 2018 -0700)

  * Split SKEYSEED and Key material generation for IPsec and IKEv2
  * IKEv2 initial checkin
  * Valgrind clean ring and direct drivers
  * https://docs.wixstatic.com/ugd/9bb785_d197a030c2f3416b8b834825f29d8858.pdf
  * https://docs.wixstatic.com/ugd/9bb785_5faf3e543d4b466b91bd858b23807524.pdf

* New in 2.1.0 (Fri Aug 31 22:38:31 2018 -0700)

  * Added ring driver
  * Added direct driver
  * Added driver
  * Added function to interpret status word as a string for printing
  * Fixed several testbench bugs
  * Logging levels now configuration from command line with --loglvl
  * Valgrind is completely clean, fixed the remaining issue that left 168 bytes of data in use at simulation end
  * https://docs.wixstatic.com/ugd/9bb785_3a1738aaab814c1390473476f38390aa.pdf

* New in 2.0.0 (Tue May 15 01:41:28 2018 -0700)

  * Fixed support for SEC/CAAM with new security associations
  * Added new classes and base clase jsecass for security associations
  * Moved to tinyxml2 v6.2.0
  * Removed memory leaks
  * Updated all files and testbenches to use new security associations
  * Fedora28 libraries
  * Re-qualified code

* New in 1.5.0 (Sat Mar 31 20:57:46 2018 -0700)

  * Added namespaces for ProtocolPP, InterfacePP, DriverPP, and PlatformPP

* New in 1.4.2 (Wed Mar 14 19:18:10 2018 -0700)

  * Updated driver
  * Static link of libgcc and libstdc++ in libraries

* New in 1.4.1 (Mon Feb 12 00:52:10 2018 -0700)

  * Moved to Crypto++ 6.0
  * Stripped out dead code
  * Added in template specialization

* New in 1.4.0 (Sun Jan 28 21:12:41 2018 -0700)

  * Fixed several parser and randomization issues
  * Fixed overrun issue in responder
  * updated copyright for 2018 and second copyright
  * added outlen to ringin API
  * Fixed RLC control plane bug
  * Fixes for Windows compile to configuration files VC++
  * Added Phanton colorization theme

* New in 1.3.1 (Sat Dec 23 11:10:19 2017 -0700)

  * Updated copyright with newly granted copyright reference number
  * Added mudsums for all files

* New in 1.3.0 (Thu Nov 30 00:08:31 2017 -0700)

  * Fixed next header processing for IPv6 in IP and IPsec
  * Fixed some randomization issues that were affecting reproduction of simulations
  * Generation of random extension headers for IPv6 when respective NH is selected (IPv6_Frag, IPv6_Route, IPv6_Opts, Jumbogram)
  * Found and fixed segmentation faults related to next header generation and processing
  * Fixed issue with status not being updated when generating descriptors
  * Fixed <data> nodes

* New in 1.2.7 (Fri Oct 20:38:49 2017 -0700)

  * Removed --native compile option, re-enabled SFMT randomizer
  * Fixed memory leaks in the library, still looking in testbench
  * Fixed parser bug when reading *.protpp files for SRTP

* New in 1.2.6 (Sat Sep 16 19:56:44 2017 -0700)

  * Fixed PRF generation issues for AES-CCM
  * Remove shared objects

* New in 1.2.5 (Thu Sep 14 22:28:19 2017 -0700)

  * Added #define for SFMT_MODE to enable use of SFMT Mersenne Twister otherwise uses previous randomizer

* New in 1.2.4 (Thu Sep 14 20:51:00 2017 -0700)

  * fixed makefile to build correctly with given repository structure

* New in 1.2.3 (Sat Aug 29 11:49:09 2017 -0700)

  * fixed formulas in doxygen
  * added back PRF usage for TLS and IPsec in W.A.S.P

* New in 1.2.2 (Sat Jul 29 16:15:55 2017 -0700)

  * Port to Windows VC++ 15
  * Updated header files
  * Linux debug for Windows port

* New in 1.2.1 (Tue Jul 25 19:25:10 2017 -0700)

  * Changed RDSEED to RDRAND in hardware random number generation

* New in 1.2.0 (Sun Jul 23 17:37:04 2017 -0700)

  * Support for IKEPRFv1, IKEPRFv2, TLSPRF1.0, TLSPRF1.2 as static functions in the jipsec and jtls classes
  * Added try/catch blocks in jmodes when calling encryption engines
  * Added generation and usage of PRF material for IPsec and TLS in the W.A.S.P randomizer

* New in 1.1.1 (Sat Jul 22 03:12:49 2017 -0700)

  * updated jrand for SFMT usage

* New in 1.1.0 (Sat Jul 22 03:12:49 2017 -0700)

  * SIMD based random number generation using SFMT
  * New build system to support versioning

* New in 1.0.0 (Sat Jul 15 11:43:00 2017 -0700)

  * First production release of Protocolpp(Protocol++)

* New in beta-2.5 (SUn Jul  2 22:38:00 2017 -0700)

  * Added SEC updates
  * Doxygen Updates

* New in beta-2.3 (Wed Jun 28 20:55:27 2017 -0700)

  * Updates for the SEC platform
  * Updated examples

* New in beta-2.1 (Mon Jun 19 23:14:25 2017 -0700)

  * Doxygen updates
  * Removed submodules

* New in beta-2.0 (Wed Jun 14 11:12:30 2017 -0700)

  * Print packet name when there's an error
  * Fixed randomizer to randomize on each pass
  * Fixed IP/IPSec decap with extension headers

* New in beta-1.0 (Sat Jun 10 12:30:08 2017 -0700)

  * GitHub site secured
  * First working release for Protocolpp(Protocol++) with testbench, all protocols, all cipher, all algorithms present and working on GitHub
  * Previously for sale on www.protocopp.com

* Intel interview (Fri May 19 15:00:00 2017 -0700)

* www.protocolpp.com goes LIVE! (Sat May 6 10:47:35 2017 -0700)

  * <B>Source code for sale</B>
  * Documentation Available
  * Examples Available
  * Testbench Available
  * <B>Able to run regressions with parser, testbench, responders</B>
  * Documented above

* Working testbench (Mon Apr 23 04:02:03 2017 -0700)

  * <B>Fully working testbench</B>
  * Screenshots taken with date and time
  * Documented above
  * https://www.protocolpp.com/demonstration-videos/MyChannel/18?wix-vod-video-id=95316505fa0e4afc9b1d18e311105d84&wix-vod-comp-id=comp-j2ddnt1i#
  * https://www.protocolpp.com/demonstration-videos/MyChannel/18?wix-vod-video-id=0758d7253d8f4a58b68d14a9e03d043a&wix-vod-comp-id=comp-j2ddnt1i#

* Protocol++ genesis (Sun Feb 8 2015 -0700)

  * jrand.h first file created with the IDE (hence the date, see file above)
  * Documented above

* Additions

  * Added CPPUNIT tests as examples of usage
  * Added test executable to run CPPUNIT tests
  * QorIQ and Layerscape support has been added
  * Enabled input and output ring address pass in
  * removed responder for SEC to allow connection to device/testbench

* Fixes

  * dynamic memory tracking in the testbench
  * Fixed TLS random IV postprocessing
  * minor code clean up
  * Fixed randomization when <protocol> is present to randomize prot and dir with each pass
  * Fixed testbench to print packet name when an error occurs
  * Doxygen updates
  * Added CYGWIN compiled libraries
  * Fixed "free" bug

* Outstanding Issues

  * Arbitration of threads in execution units
  * Realignment of packets in execution units when finished out-of-order
  * See "Upcoming Features" on www.protocolpp.com for additional information
    * AES-XTS mode
    * Reordering of output from jexec
    * Multiple jexec units per responder
    * Support for KEK protection for sensitive information (Keys, IV, Salt)

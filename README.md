# Protocolpp®(Protocol++®) 5.4.3 Released July 1, 2023!
https://www.youtube.com/watch?v=zs5Edbf4MiI

Only www.protocolpp.com has the rights to update, modify,
license, distribute, sell, or make copies of Protocolpp®(Protocol++®).

Evaluation licenses that last 30-days are available from the website free
of charge at https://www.protocolpp.com/protocolpp-trial-versions

Documentation can be found at

https://jpgreninger.github.io/protocolpp/html/index.html

Full licenses last a year and include support and updates. Latest documentation found only in licensed products

Protocol++® has several different interfaces and can be configured
in different ways. Preview the Makefile to see the target. Descriptions
of the different targets are found below. Contrary to some people's opinion,
ProtocolPP®(Protocol++®) is not a "WORK IN PROGRESS". The core library has
remained unchanged for several years. Changes have only been added when
updating to new versions of tinyxml2 parser or the Crypto++ library. NEW
items have been added (drivers, IKEv2, Security Associations) that sit
on top of the core library of protocols, ciphers, and authentication
algorithms with randomizers, parsers, anti-replay, and structures
necessary for complete functionality

Issued copyrights

* Protocol++®(Protocolpp®) 1.0.0 - TXu002059872
* Protocol++®(Protocolpp®) 1.2.7 - TXu002066632
* Protocol++®(Protocolpp®) 1.4.0 - TXu002082674
* Protocol++®(Protocolpp®) 2.0.0 - TXu002097880
* Protocol++®(Protocolpp®) 3.0.1 - TXu002169236
* Protocol++®(Protocolpp®) 4.0.0 - TXu002182417
* Protocol++®(Protocolpp®) 5.0.0 - TXu002219402
* Protocol++®(Protocolpp®) 5.2.1 - TXu002272076
* JPGNetworks - VAu001334497
* Protocol++®(Protocolpp®) 4.0.0 (Canada) - 1168370
* Protocolpp®(Protocol++®) 5.0.0 (Canada) - 1174890
* Protocolpp®(Protocol++®) 5.2.1 (Canada) - 1185641

Trademarks

* JPGNetworks - 87708008
* protocolpp® - 90634294
* protocol++® - 90634339

protocolpp® - Executable of the full set of protocols, ciphers, testbench,
             and responders to provide a command line interface for
             connecting and testing a device under test (DUT). A user
             can opt to use the jresponder (default) or use QorIQ and
             Layerscape compatible testbench by setting PLATFORM to
             SECPLAT. If using the SEC platform, the testbench only
             reads and writes to the software rings as it is expected
             that the SEC connected to the other side of the software
             rings. See the file jbuilder.cpp

libprotocolpp.a - Static library of the protocolpp.h interface, wasp.h, and ciphers.h

libprotocolpp.so.5.4.3 - Shared library of the protocolpp.h interface, wasp.h, and ciphers.h

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

test - Runs the CPPUNIT tests for Protocol++®. Message outputs are for negative testing

Supported Platforms

* RedHat Enterprise 7.2 GCC5.3.1 x64, i686
* Ubuntu 18.04 GCC5.5.0 x64, i686
* Fedora GCC7.2 x64, i686
* SUSE Enterprise GCC8.2 x64, i686
* openSUSE 15.1 GCC8.2 x64, i686
* Windows 10 VC++19 x64, i686
* ARM (Coming Soon)

USE CASES

Protocol++®(ProtocolPP®) can be used for several different use cases in development,
software, hardware development, stacks, and testbenches.

  * TESTBENCHES - Protocolpp® comes with a testbench to allow the interface to be connected
    to a Device Under Test (DUT) through software rings for test of protocols, encryption,
    and authentication algroithms, replay windows, randomization, Diffie-Hellman
    routines, and other items. In addition, Protocol++® can be used to generate XML output
    for all of the above items that can be read back in to drive Verilog or software
    drivers for development of hardware accelerators and software

  * STACKS - The drivers in ProtocolPP® show examples of how to write software stacks that
    support all levels of the OSI model to allow full manipulation of all features and
    methodologies of the protocol stack. Want to try out a new retry routine for TCP? 
    Change the code in level 4 of your software stack to try it out. Want to try a new
    algorithm for IPsec? Add it to level 3 of the stack. Developing a driver for 
    extended packet numbers in Macsec? Run your software against the Protocol++ testbench
    to ensure conformance. Additional protocols that do not need need the stack and
    require direct access to level 3 (IP/IPsec) such as Real Time Protocol (RTP) or its
    secure version (SRTP)? Disable TCP/UDP and TLS to drive IP/IPsec directly

  * HARDWARE DEVELOPMENT - Protocol++® can be used for testing hardware accelerators that
    support encryption and authentication algorithms. Developing an AES-GCM engine for
    your hard drive controller? Instantiate AES-GCM using the "ciphers" interface of 
    ProtocolPP® in your SystemC testbench to driver your Verilog or VHDL through your UVM
    driver. Received your silicon back from manufacting and need to verify there are no
    defects? Read back in the XML files generated during pre-silicon testing that achieves
    100% coverage, and execute them through ProtocolPP's® driver (or your own driver) and
    compare to the expected value. Have some conformance vectors from the specification?
    Enter the conformance data into the XML format specified by Protocol++'s® XML schema,
    read the data into the testbench or driver, and test the silicon and or RTL

  * SOFTWARE - The elements of ProtocolPP® can be incorporated into larger software projects
    to encrypt data, authenticate, generate CRC32 values, create Signatures, verify
    signatures, create PRF material, generate random data over ranges as bytes, words, or
    double words, enable SMFT mode and generate millions of random bytes from hardware
    is little or no time

These are the use cases currently being used. Development continues for Internet Key
Exchange (IKEv2), additional driver features (ICMP message generation and return), offline
key protection, key ring use, etc.

Please see the documentation found above and www.protocolpp.com for all options

INSTALLATION

```
[jgreninger@localhost protocol++]$ ./protocolpp --help
******************************************************
** Welcome to JPGNetworks, LLC Copyright 2017-2021  **
**                                                  **
** Thank You for purchasing Protocol++(ProtocolPP)  **
** the encryption, authentication, and protocol     **
** library with documentation, drivers, and         **
** testbench                                        **
******************************************************

USAGE: protocolpp [options]

Options:
  --help, -h Print usage and exit
  --cfg, -c  Configuration file (*.testpp)
  --log, -l  Path to output simulation log
  --seed, -s Seed for reproducibility
  --out, -o  Output directory (default: ./debug)

Examples:
  protocolpp --cfg myconfig.testpp
  protocolpp --seed 1234567890 --cfg myconfig.testpp --log filelog
  protocolpp --cfg myconfig.testpp --log filelog
  protocolpp --seed 2435678456 --cfg myconfig.testpp --log filelog --out ./output
  protocolpp --cfg myconfig.testpp --log filelog --out ./output
```

For W.A.S.P usage, see the doxygen section

* See www.protocolpp.com for more updates, information and licensing

* Protocol++® (Protocolpp®) - 5.4.3 upcoming July 1, 2023
  * See encrypted release notes in paid version
  * Documentation Updates
  * See www.protocolpp.com for further information
  
* Protocol++® (Protocolpp®) - 5.4.2 released March 15, 2023
  * Maintainence release
  * All updates documented in the paid version RELEASE file
  * All releases now encrypted, if yours isn't, it's a fake
  * Added DTLSv1.3 Anti-Replay support
  * Many edits to make the code more efficient
  * Documentation Updates
  * See the release video https://www.youtube.com/watch?v=zs5Edbf4MiI

* Protocol++® (Protocolpp®) - 5.4.1 released January 1, 2023
  * All updates documented in the paid version RELEASE file
  * All releases now encrypted, if yours isn't, it's a fake
  * Added AES-XTS
  * Added JSON support to the SEC testbench
  * Many edits to make the code more efficient
  * Documentation Updates
  * See the release video https://www.youtube.com/watch?v=zs5Edbf4MiI
  
* Protocol++® (Protocolpp®) - 5.4.0 released December 15, 2022
  * All updates documented in the paid version RELEASE file
  * All releases now encrypted, if yours isn't, it's a fake
  * Added the following protocols
    * Extended GRE
    * NVGRE
    * VXLAN
    * DTLS v1.3 (RFC 9147) with SM support (RFC8998)
    * Added SM support to TLS v1.3 (RFC8998)
  * Many edits to make the code more efficient
  * Documentation Updates
  * See the release video https://www.protocolpp.com/protocolpp-demonstration-videos?wix-vod-video-id=b476cddf732040089759683c20c4b926&wix-vod-comp-id=comp-j2ddnt1i
  
* Protocol++® (Protocolpp®) - 5.3.2 released August 8, 2022
  * All updates documented in the paid version RELEASE file
  * All releases now encrypted, if yours isn't, it's a fake
  * JSON support
    * XML -> JSON
    * XML -> XML
    * JSON -> XML
    * JSON -> JSON
  * Bumped version
  * See the release video https://www.protocolpp.com/protocolpp-demonstration-videos?wix-vod-video-id=dfe709cd0329410d8bebb7ae75aab9ac&wix-vod-comp-id=comp-j2ddnt1i
  
* Protocol++® (Protocolpp®) - 5.3.1 released June 28, 2022
  * All updates documented in the paid version RELEASE file
  * All releases now encrypted, if yours isn't, it's a fake
  * Bumped version
  * See the release video https://www.protocolpp.com/protocolpp-demonstration-videos?wix-vod-video-id=1ad7e49827904441969410ae2d6cfaea&wix-vod-comp-id=comp-j2ddnt1i
  
* Protocol++® (Protocolpp®) - 5.3.0 released February 27, 2022
  * Added support for ZUC256 with 16-byte IV (as well as 25-byte IV) in LTE, standalone, confident, integrity
  * Updated SNOWV interface
  * Bumped version

* Protocol++® (Protocolpp®) - 5.2.4 released January 29, 2022
  * Many changes for -pedantic-errors -Wall -Wextra compile
  * Bumped version

* Protocol++® (Protocolpp®) - 5.2.3 released January 24, 2022
  * Added initilizer list constructor and append() to jarray
  * Many additional CLangTidy updates
  * changed all seeds to UINT64_T from unsigned long
  * Bumped version

* New in 5.2.2 - Release January 1, 2022
  * Bumped version
  * Exposed support for non-keyed hashes (SHA2/SHA3/SHAKE) stand alone, jmodes, jintegrity, and W.A.S.P/Testbench
    * MD5
    * SHA1
    * SHA2_224
    * SHA2_256
    * SHA2_384
    * SHA2_512
    * SHAKE128
    * SHAKE256
    * SHA3_224
    * SHA3_256
    * SHA3_384
    * SHA3_512
  * Renamed previous keyed-hashes to included HMAC
    * MD5 -> HMAC_MD5
    * SHA1 -> HMAC_SHA1
    * SHA_224 -> HMAC_SHA2_224
    * SHA_256 -> HMAC_SHA2_256
    * SHA_384 -> HMAC_SHA2_384
    * SHA_512 -> HMAC_SHA2_256
    * SHA3_224 -> HMAC_SHA3_224
    * SHA3_256 -> HMAC_SHA3_256
    * SHA3_384 -> HMAC_SHA3_284
    * SHA3_512 -> HMAC_SHA3_512
  * Support for SNOW-V, SNOW-V-AEAD (GCM), SNOW-V-GHASH (new class jsnowv) stand alone, jmodes, ciphers factory method, jconfident, jintegrity, and W.A.S.P/Testbench
  * Support for ZUC-256, ZUC-256-MAC (use 32-byte key and 25-bytes IV constructor) stand alone, jmodes, ciphers factory method, jconfident, jintegrity, and W.A.S.P/Testbench
  * Support for connection of Device-Under-Test (DUT) to W.A.S.P testbench through software rings
    * Pass location and size of rings to testbench in configuration file
    * Testbench generates packets
    * Testbench loads packets and flows to rings
    * Testbench processes packets in output ring from DUT
    * If no DUT connected, testbench will continually issue "waiting for ring" warning to screen because input ring is full
  * Updated documentation and source code with ® symbol for trademarks on 'protocolpp' and 'protocol++'
  * As always, valgrind leak free testbench and libraries
  * Many more static code analysis updates from CLang-Tidy and CPPcheck in header and CPP files
  * See the release video https://www.protocolpp.com/protocolpp-demonstration-videos?wix-vod-video-id=139948e590064090a8594348915f441a&wix-vod-comp-id=comp-j2ddnt1i
  
* New in 5.2.1 - Released September 24, 2021
  * Bumped version
  * Added new utilities
  * Separated TLSv13 from legacy
  * Updated LMS and XMSS to run in testbench
  * Testbench now runs at WARN level rather than INFO
  * Added unit tests for ECDSA, DSA, EdDSA
  * Fixed BER decoding issues for PKI keys
  * Key validation added for signature methods
  * Fixed some initialization lists that had missing variables
  * Fixed W.A.S.P for cases where <security> or <protocol> are not found
  * Many fixes from CLang-Tidy code analysis
  * Added feature to crypto scrub IVs, Keys, and Salt in real time
  * Added jumbogram unit tests for IPsec
  * Added scrub feature for sensitive data
  * Removed PLAT from WASPPLAT and SECPLAT
  * Removed all shared pointers from jmodes
  * Fixed stream and protocol with no children to randomly generate replay packets
  * Moved to TinyXML2 v9.0.0
  * Added X25519 support for Diffie-Hellman
  * Added Ed25519 Signature Scheme
  * Added ZUC256 support
  * Coverage work (coverage is > 90%)
  * Debugged for CLang compiler
  * Fixed TLSv13 nonce to remove SALT and use a 12-byte IV XORd with padded SEQNUM
  * Fixed ECDSA key save and load to use point and private element
  * Expanded testbench to run up to 100,0000 independent flows at once (1,000, 10,000, and 100,000 tested)
  * Expanded testbench to have continuous mode (run continuously, filling rings with new packets)
  * Separated SEC and W.A.S.P testbenches
  * Updated documentation
  * see the release video https://www.protocolpp.com/protocolpp-demonstration-videos?wix-vod-video-id=74c77d3dd5d6401db4d363bec657d255&wix-vod-comp-id=comp-j2ddnt1i

* See the original video April 27, 2017 1.5 months before Intel ever called
  * https://www.protocolpp.com/protocolpp-demonstration-videos?wix-vod-video-id=9ae26d2c476d48bc854100acb4f8b447&wix-vod-comp-id=comp-j2ddnt1i
  
* See the Beta 2.0.0 video May 7, 2017 before Intel interview on May 19, 2017
  * https://www.protocolpp.com/protocolpp-demonstration-videos?wix-vod-video-id=e5551d0b1134404699de66194c12608b&wix-vod-comp-id=comp-j2ddnt1i

* See the README in the released version for the full release path from the beginning

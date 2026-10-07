///
/// <center>Protocol++&reg; (ProtocolPP&reg;) modified by : John Peter Greninger &bull; &copy; John Peter Greninger 2015-2024 &bull; All Rights Reserved</center>
/// <center><sub>All copyrights and trademarks are the property of their respective owners</sub></center>
///
/// The source code contained or described herein and all documents related to the source code 
/// (herein called "Material") are owned by John Peter Greninger and Sheila Rocha Greninger. Title
/// to the Material remains with John Peter Greninger and Sheila Rocha Greninger. The Material contains
/// trade secrets and proprietary and confidential information of John Peter Greninger and Sheila Rocha
/// Greninger. The Material is protected by worldwide copyright and trade secret laws and treaty
/// provisions. No part of the Material may be used, copied, reproduced, modified, published, uploaded,
/// posted, transmitted, distributed, or disclosed in any way without prior express written consent of
/// John Peter Greninger and Sheila Rocha Greninger (both are required)
/// 
/// No license under any patent, copyright, trade secret, or other intellectual property right is granted
/// to or conferred upon you by disclosure or delivery of the Materials, either expressly, by implication,
/// inducement, estoppel, or otherwise. Any license under such intellectual property rights must be express
/// and approved by John Peter Greninger and Sheila Rocha Greninger in writing
///
/// Redistribution and use in source and binary forms, with or without modification, are
/// permitted provided that the following conditions are met:
///
/// * Redistributions of source code must retain the above copyright notice, this list of
///   conditions and the following disclaimer
///
/// * Redistributions in binary form must reproduce the above copyright notice, this list
///   of conditions and the following disclaimer in the documentation and/or other materials
///   provided with the distribution
///
/// * Any and all modifications must be returned to John Peter Greninger at GitHub.com
///   https://github.com/jpgreninger/protocolpp for evaluation. Inclusion of modifications
///   in the source code shall be determined solely by John Peter Greninger. Failure to
///   provide modifications shall render this license NULL and VOID and revoke any rights
///   to use of Protocol++&reg;
///
/// * Commercial use requires a fee-based license obtainable at www.protocolpp.com
///
/// * Academic use requires written and notarized permission from John Peter and Sheila
///   Rocha Greninger
///
/// * <B>US Copyrights at https://www.copyright.gov/</B>
///   * <B>TXu002059872 (Version 1.0.0)</B>
///   * <B>TXu002066632 (Version 1.2.7)</B>
///   * <B>TXu002082674 (Version 1.4.0)</B>
///   * <B>TXu002097880 (Version 2.0.0)</B>
///   * <B>TXu002169236 (Version 3.0.1)</B>
///   * <B>TXu002182417 (Version 4.0.0)</B>
///   * <B>TXu002219402 (Version 5.0.0)</B>
///   * <B>TXu002272076 (Version 5.2.1)</B>
///   * <B>TXu002383571 (Version 5.4.3)</B>
///
/// The names of its contributors may not be used to endorse or promote products derived
/// from this software without specific prior written permission
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
/// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
/// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
/// SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
/// OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
/// TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
/// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
///

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <stdlib.h>
#include <string.h>
#include "wasp.h"
#include "jring.h"
#include "jexec.h"

using namespace CppUnit;

///#define HAS_SIZEOF_INT128_64BIT (defined(__SIZEOF_INT128__) && defined(__LP64__))
///#define HAS_MSVC_64BIT false (defined(_MSC_VER) && defined(_M_X64))
///#define HAS_GCC_4_4_64BIT false (defined(__GNUC__) && defined(__LP64__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 4))))

/* auto detect between 32bit / 64bit */
#if _WIN32 || _WIN64
    #if _WIN64
        #ifndef HAS_SIZEOF_INT128_64BIT
            #define HAS_SIZEOF_INT128_64BIT
        #endif
        #ifndef HAS_SIZEOF_INT128_64BIT
            #define HAS_MSVC_64BIT
        #endif
        #ifndef HAS_SIZEOF_INT128_64BIT
            #define HAS_GCC_4_4_64BIT
        #endif
    #endif
#endif

#if __GNUC__
    #if __x86_64__ || __ppc64__
        #ifndef HAS_SIZEOF_INT128_64BIT
            #define HAS_SIZEOF_INT128_64BIT
        #endif
        #ifndef HAS_SIZEOF_INT128_64BIT
            #define HAS_MSVC_64BIT
        #endif
        #ifndef HAS_SIZEOF_INT128_64BIT
            #define HAS_GCC_4_4_64BIT
        #endif
    #endif
#endif

// folded function printer
template<typename ...Args>
void printer(InterfacePP::jlogger::severity_t loglvl, Args&&... args) {
    if (loglvl == InterfacePP::jlogger::severity_t::info) {
        std::cout << "\033[1m\033[33m ";
    }

    (std::cout << ... << args);
    std::cout << std::endl;
}

class ppUnitTest : public TestCase {
    CPPUNIT_TEST_SUITE(ppUnitTest);
        CPPUNIT_TEST(testendian);
        CPPUNIT_TEST(testarray);
        //CPPUNIT_TEST(testbuffer);
        CPPUNIT_TEST(testbuffs);
        CPPUNIT_TEST(testconv);
        CPPUNIT_TEST(testrand);
        CPPUNIT_TEST(testreplay);
        CPPUNIT_TEST(testenum);
        CPPUNIT_TEST(testwasp);
        CPPUNIT_TEST(testcfg);
        CPPUNIT_TEST(testmodes);
        //CPPUNIT_TEST(testcrc);
        CPPUNIT_TEST(testgcm);
        CPPUNIT_TEST(testxts);
        CPPUNIT_TEST(testccm);
        CPPUNIT_TEST(testsm4);
        CPPUNIT_TEST(testsnow);
        CPPUNIT_TEST(testsnowv);
        CPPUNIT_TEST(testcmac);
        CPPUNIT_TEST(testxcbcmac);
        CPPUNIT_TEST(testchacha);
        CPPUNIT_TEST(testpoly1305);
        CPPUNIT_TEST(testsm3);
        //CPPUNIT_TEST(testlms);
        CPPUNIT_TEST(testzuckeystream);
        //CPPUNIT_TEST(testzuce);
        CPPUNIT_TEST(testzuca);
        CPPUNIT_TEST(testzuc256);
        CPPUNIT_TEST(testzuc256_128);
        //CPPUNIT_TEST(testzuca256);
        //CPPUNIT_TEST(testxmss);
        CPPUNIT_TEST(testshake);
        CPPUNIT_TEST(testppcov);
        CPPUNIT_TEST(testdhcov);
        CPPUNIT_TEST(testudpcov);
        CPPUNIT_TEST(testgrecov);
        CPPUNIT_TEST(testtcpcov);
        CPPUNIT_TEST(testicmpcov);
        CPPUNIT_TEST(testip4cov);
        CPPUNIT_TEST(testipseccov);
        CPPUNIT_TEST(testmaccov);
        CPPUNIT_TEST(testtlscov);
        CPPUNIT_TEST(testtls13cov);
        CPPUNIT_TEST(testdtls13cov);
        CPPUNIT_TEST(testsrtpcov);
        CPPUNIT_TEST(testwificov);
        CPPUNIT_TEST(testwifiprf);
        CPPUNIT_TEST(testwifikdf);
        CPPUNIT_TEST(testwifipbkdf);
        CPPUNIT_TEST(testwigigcov);
        CPPUNIT_TEST(testwimaxcov);
        CPPUNIT_TEST(testltecov);
        CPPUNIT_TEST(testrlccov);
        CPPUNIT_TEST(testblobcov);
        CPPUNIT_TEST(testconfsacov);
        CPPUNIT_TEST(testconfcov);
        CPPUNIT_TEST(testintegsacov);
        CPPUNIT_TEST(testintegcov);
        CPPUNIT_TEST(testrsasacov);
        CPPUNIT_TEST(testrsacov);
        CPPUNIT_TEST(testdsasacov);
        CPPUNIT_TEST(testdsacov);
        CPPUNIT_TEST(testecdsaedcov);
        CPPUNIT_TEST(testecdsafpcov);
        CPPUNIT_TEST(testecdsaf2mcov);
        CPPUNIT_TEST(testdatacov);
        CPPUNIT_TEST(testexecov);
        CPPUNIT_TEST(testudp);
        CPPUNIT_TEST(testudpvxlan);
        CPPUNIT_TEST(testudpfile);
        CPPUNIT_TEST(testtcp);
        CPPUNIT_TEST(testtcpfile);
        CPPUNIT_TEST(testudpip);
        CPPUNIT_TEST(testudpip6);
        CPPUNIT_TEST(testpgre);
        CPPUNIT_TEST(testnvgre);
        CPPUNIT_TEST(testip6);
        CPPUNIT_TEST(testip6file);
        CPPUNIT_TEST(testtcpip);
        CPPUNIT_TEST(testtcpip6);
        //CPPUNIT_TEST(testipsec);
        CPPUNIT_TEST(testipsecgcm);
        CPPUNIT_TEST(testipsecccm);
        CPPUNIT_TEST(testipsecchacha);
        //CPPUNIT_TEST(testipsecctr);
        //CPPUNIT_TEST(testipsecxcbc);
        CPPUNIT_TEST(testmsec);
        CPPUNIT_TEST(testmsecxpn);
        CPPUNIT_TEST(testtls);
        CPPUNIT_TEST(testtlsfile);
        CPPUNIT_TEST(testtlschacha);
        CPPUNIT_TEST(testtlsgcm);
        CPPUNIT_TEST(testtlsccm);
        CPPUNIT_TEST(testtlsencmac);
        //CPPUNIT_TEST(testtls13);
        //CPPUNIT_TEST(testtls13file);
        CPPUNIT_TEST(testdtls13);
        CPPUNIT_TEST(testsrtpctr);
        CPPUNIT_TEST(testsrtpgcm);
        CPPUNIT_TEST(testsrtpccm);
        CPPUNIT_TEST(testwificcmp);
        CPPUNIT_TEST(testwifigcmp);
        CPPUNIT_TEST(testwifism4ccmp);
        CPPUNIT_TEST(testwifism4gcmp);
        CPPUNIT_TEST(testwimax);
        CPPUNIT_TEST(testltesnow);
        CPPUNIT_TEST(testltesnowv);
        CPPUNIT_TEST(testltesnowvgcm);
        CPPUNIT_TEST(testltezuc);
        CPPUNIT_TEST(testlteaes);
        CPPUNIT_TEST(testrlcsnow);
        CPPUNIT_TEST(testrlczuc);
        CPPUNIT_TEST(testrlcaes);
        CPPUNIT_TEST(testlogger);
    CPPUNIT_TEST_SUITE_END();

public:

    unsigned int mystatus = 0;
    unsigned long seed = static_cast<unsigned long>(time(NULL));
    std::string myreplay = std::string("NORMAL");
    std::shared_ptr<ProtocolPP::jrand> myrand = std::make_shared<ProtocolPP::jrand>(seed);
    std::string log = "./mypp.log";
    std::shared_ptr<InterfacePP::jlogger> logger = std::make_shared<InterfacePP::jlogger>(log,
                                                                                          true,
                                                                                          InterfacePP::jlogger::severity_t::info,
                                                                                          InterfacePP::jlogger::asciicolor::MAGENTA,
                                                                                          InterfacePP::jlogger::asciicolor::CYAN,
                                                                                          InterfacePP::jlogger::asciicolor::YELLOW,
                                                                                          InterfacePP::jlogger::asciicolor::RED,
                                                                                          InterfacePP::jlogger::asciicolor::RED,
                                                                                          InterfacePP::jlogger::asciicolor::GREEN);
    void testendian() {
        short int word = 0x0001;
        char *byte = (char *) &word;
        //return(byte[0] ? LITTLE_ENDIAN : BIG_ENDIAN);

        if (byte[0]) {
            std::cout << "Platform is LITTLE_ENDIAN" << std::endl;
        }
        else {
            std::cout << "Platform is LITTLE_ENDIAN" << std::endl;
        }

        printer(InterfacePP::jlogger::severity_t::info, "Answer is: ", 1, ", then is: ", 2);
        //INFO("Answer is: ", 1, ", then is: ", 2);
    }

    void testarray() {
        // constructors, to_sting, and size
        unsigned int zero=0;
        unsigned int fifty=50;
        ProtocolPP::jarray<uint8_t> jempty=ProtocolPP::jarray<uint8_t>();
        ProtocolPP::jarray<uint8_t> mysize(50);
        ProtocolPP::jarray<uint8_t> myfill(10, 0xAC);
        ProtocolPP::jarray<uint8_t> myinit {0xAC, 0xBB, 0xEF, 0x01, 0x02};
        myinit.append({0xAA, 0xCD, 0xBF});
        std::string chk("1023456789ABCDEF");
        std::string chkrev("EFCDAB8967452310");
        ProtocolPP::jarray<uint8_t> mystring(chk);
        ProtocolPP::jarray<uint8_t> myrev(chk);
        std::vector<uint8_t> myvec(10, 0xAA);
        ProtocolPP::jarray<uint8_t> myjvec(myvec);
        ProtocolPP::jarray<uint32_t> myword(mystring);
        std::string fillstr("ACACACACACACACACACAC");
        std::string stringstr("1023456789ABCDEF");
        std::string vecstr("AAAAAAAAAAAAAAAAAAAA");
        std::string upperstr("AAAABBBBCCCCDDDDEEEEFFFF11112222");
        std::string lowerstr("aaaabbbbccccddddeeeeffff11112222");
        std::string nonstr("aaaabbbbccccddddeeeefffz11112222");
        std::string nonstr2("aaaabbbbccccddddeeeeffzf11112222");
        ProtocolPP::jarray<uint8_t> tstupper(upperstr);
        ProtocolPP::jarray<uint8_t> tstlower(lowerstr);
        ProtocolPP::jarray<uint8_t> nonnon(nonstr);
        ProtocolPP::jarray<uint8_t> nonnon2(nonstr2);
        ProtocolPP::jarray<uint8_t> nonhex("ABCDEF0123456789O");
        bool tstme = tstupper.empty();
        myrev.reverse();
        CPPUNIT_ASSERT_EQUAL(chkrev, myrev.to_string());
        CPPUNIT_ASSERT_EQUAL(false, tstme);
        CPPUNIT_ASSERT_EQUAL(zero, jempty.get_size());
        CPPUNIT_ASSERT_EQUAL(true, jempty.empty());
        CPPUNIT_ASSERT_EQUAL(fifty, mysize.get_size());
        CPPUNIT_ASSERT_EQUAL(fillstr, myfill.to_string());
        CPPUNIT_ASSERT_EQUAL(stringstr, mystring.to_string());
        CPPUNIT_ASSERT_EQUAL(vecstr, myjvec.to_string());
        CPPUNIT_ASSERT_EQUAL(stringstr, myword.to_string());
        CPPUNIT_ASSERT_EQUAL(tstupper.to_string(), tstlower.to_string());
        tstlower.resize(20);
        tstlower.extract(16, 8);
        tstlower.erase(16, 4);
        ProtocolPP::endian_t end = tstlower.get_format();

        uint8_t* ptr1 = tstupper.get_ptr();
        const uint8_t* ptr2 = tstlower.get_ptr();
        memcpy(ptr1, ptr2, tstlower.get_size());

        // range constructors
        ProtocolPP::jarray<char>     charme = myrand->getchar(10);
        ProtocolPP::jarray<uint16_t> shortme = myrand->getu16("5..16");
        ProtocolPP::jarray<uint32_t> normme  = myrand->getword("5..16");
        ProtocolPP::jarray<uint64_t> longme  = myrand->getdouble("5..16");
        ProtocolPP::jarray<uint8_t>  cryptme = myrand->get_crypto(5);
        //unsigned long myseeds[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        //myrand->seed(&myseeds[0], 10);

        // manipulators
        std::string mysplt("AAAAAAAA");
        ProtocolPP::jarray<uint8_t> mysplit = myjvec.split(4);
        CPPUNIT_ASSERT_EQUAL(mysplt, mysplit.to_string());

        ProtocolPP::jarray<uint8_t> myex(1,0xAC);
        ProtocolPP::jarray<uint8_t> myxtract = myfill.extract(0,1);
        CPPUNIT_ASSERT_EQUAL(myex.to_string(), myxtract.to_string());

        uint8_t back = 0xFF;
        myfill.push_back(back);
        std::string fillback("ACACACACACACACACACACFF");
        CPPUNIT_ASSERT_EQUAL(fillback, myfill.to_string());
        int size = (int) myfill.get_size();
        CPPUNIT_ASSERT_EQUAL(11, size);

        myfill.pop_back();
        CPPUNIT_ASSERT_EQUAL(fillstr, myfill.to_string());
        size = (int) myfill.get_size();
        CPPUNIT_ASSERT_EQUAL(10, size);

        ProtocolPP::jarray<uint8_t> myapp(10, 0xFF);
        myfill.append(myapp);
        std::string fillapp("ACACACACACACACACACACFFFFFFFFFFFFFFFFFFFF");
        CPPUNIT_ASSERT_EQUAL(fillapp, myfill.to_string());
        size = (int) myfill.get_size();
        CPPUNIT_ASSERT_EQUAL(20, size);

        ProtocolPP::jarray<uint8_t> myin(5, 0xCE);
        myfill.insert(10, myin);
        std::string fillin("ACACACACACACACACACACCECECECECEFFFFFFFFFFFFFFFFFFFF");
        CPPUNIT_ASSERT_EQUAL(fillin, myfill.to_string());
        size = (int) myfill.get_size();
        CPPUNIT_ASSERT_EQUAL(25, size);

        ProtocolPP::jarray<uint8_t> myup(5, 0xBB);
        myfill.update(10, myup);
        std::string fillup("ACACACACACACACACACACBBBBBBBBBBFFFFFFFFFFFFFFFFFFFF");
        CPPUNIT_ASSERT_EQUAL(fillup, myfill.to_string());
        size = (int) myfill.get_size();
        CPPUNIT_ASSERT_EQUAL(25, size);

        myfill.erase(10, 5);
        std::string filler("ACACACACACACACACACACFFFFFFFFFFFFFFFFFFFF");
        CPPUNIT_ASSERT_EQUAL(filler, myfill.to_string());
        size = (int) myfill.get_size();
        CPPUNIT_ASSERT_EQUAL(20, size);

        CPPUNIT_ASSERT_EQUAL(ProtocolPP::BIG, myfill.get_format());

        // operators
        ProtocolPP::jarray<uint32_t> myequal(5, 0xABCDEF01);
        ProtocolPP::jarray<uint32_t> little(myequal, ProtocolPP::LITTLE);
        ProtocolPP::jarray<uint32_t> myequal2(5, 0xABCDEF01);
        ProtocolPP::jarray<uint32_t> myequal3(5, 0xAB9DEF01);
        ProtocolPP::jarray<uint32_t> myequal4(5, 0);
        ProtocolPP::jarray<uint32_t> myequal5(5, 0x579BDE02);
        ProtocolPP::jarray<uint32_t> myequal6(5, 0x00000003);
        ProtocolPP::jarray<uint32_t> myequal7(5, 0x0369CD03);
        ProtocolPP::jarray<uint32_t> myequal8(5, 0x01EFCDAB);
        ProtocolPP::jarray<uint32_t> xorme(myequal);
        xorme ^= myequal2;
        ProtocolPP::jarray<uint32_t> orme(myequal);
        orme |= myequal2;
        ProtocolPP::jarray<uint32_t> andme(myequal);
        andme &= myequal2;
        ProtocolPP::jarray<uint32_t> multme(myequal);
        multme *= myequal6;
        ProtocolPP::jarray<uint32_t> addme(myequal);
        addme += myequal2;
        CPPUNIT_ASSERT_EQUAL(true, myequal==myequal2);
        CPPUNIT_ASSERT_EQUAL(false, myequal==myequal3);
        CPPUNIT_ASSERT_EQUAL(true, myequal!=myequal3);
        CPPUNIT_ASSERT_EQUAL(false, myequal!=myequal2);
        CPPUNIT_ASSERT_EQUAL(true, myequal8==little);
        CPPUNIT_ASSERT_EQUAL(xorme.to_string(), myequal4.to_string());
        CPPUNIT_ASSERT_EQUAL(orme.to_string(), myequal.to_string());
        CPPUNIT_ASSERT_EQUAL(andme.to_string(), myequal.to_string());
        CPPUNIT_ASSERT_EQUAL(multme.to_string(), myequal7.to_string());
        CPPUNIT_ASSERT_EQUAL(addme.to_string(), myequal5.to_string());
        myequal2.debug(myequal3);
        myequal2.debug(myequal);
        myequal.to_string(true);

        // serial errors
        ProtocolPP::jarray<uint8_t> xorerr1(myrand->getbyte(50));
        ProtocolPP::jarray<uint8_t> xorerr2(myrand->getbyte(54));
        xorerr1 ^= xorerr2;

        ProtocolPP::jarray<uint8_t> orerr1(myrand->getbyte(55));
        ProtocolPP::jarray<uint8_t> orerr2(myrand->getbyte(45));
        orerr1 |= orerr2;

        ProtocolPP::jarray<uint8_t> anderr1(myrand->getbyte(50));
        ProtocolPP::jarray<uint8_t> anderr2(myrand->getbyte(49));
        anderr1 &= anderr2;

        ProtocolPP::jarray<uint8_t> multerr1(myrand->getbyte(25));
        ProtocolPP::jarray<uint8_t> multerr2(myrand->getbyte(28));
        multerr1 *= multerr2;

        ProtocolPP::jarray<uint8_t> adderr1(myrand->getbyte(25));
        ProtocolPP::jarray<uint8_t> adderr2(myrand->getbyte(28));
        adderr1 += adderr2;

        // conversion routines 
        // word to others
        ProtocolPP::jarray<uint32_t> myconv(5, 0xABCDEF01);
        ProtocolPP::jarray<uint32_t> littleconv(myconv, ProtocolPP::LITTLE);
        ProtocolPP::jarray<uint8_t> mycbyte(littleconv, ProtocolPP::LITTLE);
        ProtocolPP::jarray<uint16_t> mycshort(littleconv, ProtocolPP::LITTLE);
        ProtocolPP::jarray<uint64_t> mycdbl(littleconv, ProtocolPP::LITTLE);

        // byte to others
        ProtocolPP::jarray<uint8_t> mymybyte(mycbyte);
        ProtocolPP::jarray<uint16_t> mymyshort(mycbyte);
        ProtocolPP::jarray<uint32_t> mymyword(mycbyte);
        ProtocolPP::jarray<uint64_t> mymydbl(mycbyte);

        // short to others
        ProtocolPP::jarray<uint8_t> my3byte(mycshort);
        ProtocolPP::jarray<uint16_t> my3short(mycshort);
        ProtocolPP::jarray<uint32_t> my3word(mycshort);
        ProtocolPP::jarray<uint64_t> my3dbl(mycshort);

        // double to others
        ProtocolPP::jarray<uint8_t> my4byte(mycdbl);
        ProtocolPP::jarray<uint16_t> my4short(mycdbl);
        ProtocolPP::jarray<uint32_t> my4word(mycdbl);
        ProtocolPP::jarray<uint64_t> my4dbl(mycdbl);

        std::cout << "Size of UINT8_T is: " << sizeof(uint8_t) << std::endl;
        std::cout << "Size of UINT16_T is: " << sizeof(uint16_t) << std::endl;
        std::cout << "Size of UINT32_T is: " << sizeof(uint32_t) << std::endl;
        std::cout << "Size of UINT64_T is: " << sizeof(uint64_t) << std::endl;

        // test secure erase
        cryptme.serase();
        shortme.serase();
        normme.serase();
        longme.serase();
    }

    void testbuffer() {
        ProtocolPP::jbuffer<uint8_t, 256> bigtmp(logger);
        ProtocolPP::jbuffer<uint8_t, 256> tmp(200, logger);
        ProtocolPP::jbuffer<uint8_t, 256> tmp5(tmp, logger);

        auto bufptr = tmp.dequeue(100);
        auto bufptr2 = tmp.dequeue(10);
        ProtocolPP::jarray<uint8_t> tmp3(25600, 0xA5);
        ProtocolPP::jarray<uint8_t> tmp4(25600, 0);
        tmp.write(bufptr.second, tmp3.get_ptr(), tmp3.get_size(), 258);
        tmp.read(bufptr.second, tmp4.get_ptr(), tmp4.get_size(), 257);
        tmp.write(bufptr.second, tmp3, 258);
        tmp.read(bufptr.second, tmp4, 257);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> tmp6 = std::make_shared<ProtocolPP::jarray<uint8_t>>(tmp3);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> tmp7 = std::make_shared<ProtocolPP::jarray<uint8_t>>(25600, 0);
        tmp.write(bufptr.second, tmp6, 258);
        tmp.read(bufptr.second, tmp7, 257);
        tmp.enqueue(bufptr2.second);
        tmp.enqueue(bufptr.second);
    }

    void testbuffs() {
        ProtocolPP::jbuffman<uint8_t, 256> bigtmp;
        ProtocolPP::jbuffman<uint8_t, 256> tmp(200);
        ProtocolPP::jbuffman<uint8_t, 256> tmp5(tmp);

        std::list<std::array<uint8_t, 256>> get = tmp.deque(100);
        std::list<std::array<uint8_t, 256>> getme = tmp.deque(400);
        tmp5.enque(get);
        tmp.enque(get);

        get = tmp.deque(100);
        ProtocolPP::jbuffacc<uint8_t, 256> tmp2(get);
        ProtocolPP::jarray<uint8_t> tmp3(25600, 0xA5);
        ProtocolPP::jarray<uint8_t> tmp4(25600, 0);
        tmp2.write(0, tmp3.get_size(), tmp3.get_ptr());
        tmp2.read(0, tmp4.get_size(), tmp4.get_ptr());
        tmp3 = tmp3.split(25500);
        tmp4 = tmp4.split(25500);
        tmp2.write(0, tmp3.get_size(), tmp3.get_ptr());
        tmp2.read(0, tmp4.get_size(), tmp4.get_ptr());
        tmp3 = tmp3.split(100);
        tmp4 = tmp4.split(100);
        int mysize = tmp2.size();
        tmp2.write(64, tmp3.get_size(), tmp3.get_ptr());
        tmp2.read(0, tmp4.get_size(), tmp4.get_ptr());
        tmp2.read(1000, tmp4.get_size(), tmp4.get_ptr());
        tmp2.read(25550, tmp4.get_size(), tmp4.get_ptr());

        std::shared_ptr<std::list<std::array<uint8_t, 256>>> tmp10;
        tmp.deque(100, tmp10);
        tmp5.enque(tmp10);
        tmp.enque(tmp10);
        tmp.deque(400, tmp10);

        std::shared_ptr<ProtocolPP::jbuffacc<uint8_t, 256>> tmp20;
        tmp.dequea(100, tmp20);
        tmp5.enque(tmp20);
        tmp.enque(tmp20);

        ProtocolPP::jbuffacc<uint8_t, 256> tmp30 = tmp.dequea(100);
        tmp5.enque(tmp30);
        tmp.enque(tmp30);

        ProtocolPP::jbuffacc<uint8_t, 256> tmp40 = tmp.dequea(600);
        tmp.dequea(600, tmp20);
    }

    void testconv() {
        uint64_t tmp1 = 0xAABBCCDDEEFF0011;
        uint32_t tmp2 = 0xEEFF0011;
        uint16_t tmp3 = 0xAABB;

        ProtocolPP::jarray<uint64_t> reg1(1,tmp1);
        ProtocolPP::jarray<uint8_t>  reg11(reg1, ProtocolPP::endian_t::BIG);
        ProtocolPP::jarray<uint32_t> reg2(1,tmp2);
        ProtocolPP::jarray<uint8_t>  reg22(reg2, ProtocolPP::endian_t::BIG);
        ProtocolPP::jarray<uint16_t> reg3(1,tmp3);
        ProtocolPP::jarray<uint8_t>  reg33(reg3, ProtocolPP::endian_t::BIG);
        ProtocolPP::jarray<uint64_t> reg4(10,0xFE);
        ProtocolPP::jarray<uint8_t>  reg44(reg4, ProtocolPP::endian_t::BIG);

        ProtocolPP::jarray<uint8_t> ary1(1,0xAA);
        ary1.push_back(0xBB);
        ary1.push_back(0xCC);
        ary1.push_back(0xDD);
        ary1.push_back(0xEE);
        ary1.push_back(0xFF);
        ary1.push_back(0x00);
        ary1.push_back(0x11);

        ProtocolPP::jarray<uint8_t> ary2(1,0xEE);
        ary2.push_back(0xFF);
        ary2.push_back(0x00);
        ary2.push_back(0x11);

        ProtocolPP::jarray<uint8_t> ary3(1,0xAA);
        ary3.push_back(0xBB);

        uint64_t chk1 = ProtocolPP::jprotocol::to_u64(reg11);
        uint32_t chk2 = ProtocolPP::jprotocol::to_u32(reg22);
        uint16_t chk3 = ProtocolPP::jprotocol::to_u16(reg33);
        uint64_t chk4 = ProtocolPP::jprotocol::to_u64(reg44);

        CPPUNIT_ASSERT_EQUAL(tmp1, chk1);
        CPPUNIT_ASSERT_EQUAL(tmp2, chk2);
        CPPUNIT_ASSERT_EQUAL(tmp3, chk3);

        if (ary1 != reg11) {
            std::cerr << "ARRAY64 conversion did not match\n"
                      << ary1.debug(reg11) << std::endl;
        }
        if (ary2 != reg22) {
            std::cerr << "ARRAY32 conversion did not match\n"
                      << ary2.debug(reg22) << std::endl;
        }
        if (ary3 != reg33) {
            std::cerr << "ARRAY16 conversion did not match\n"
                      << ary3.debug(reg33) << std::endl;
        }
    }

    void testrand() {
        unsigned long newseed = 0x443399AA;
        ProtocolPP::jrand chkrand;

        int size = (int) sizeof(chkrand.get_u8());
        CPPUNIT_ASSERT_EQUAL(1, size);
        size = (int) sizeof(chkrand.get_u16());
        CPPUNIT_ASSERT_EQUAL(2, size);
        size = (int) sizeof(chkrand.get_u32());
        CPPUNIT_ASSERT_EQUAL(4, size);
        size = (int) sizeof(chkrand.get_u64());
        CPPUNIT_ASSERT_EQUAL(8, size);

        ProtocolPP::jarray<uint8_t> chk8 = chkrand.getbyte(15);
        size = (int) chk8.get_size();
        int width = (int) sizeof(chk8[0]);
        CPPUNIT_ASSERT_EQUAL(15, size);
        CPPUNIT_ASSERT_EQUAL(1, width);

        ProtocolPP::jarray<uint16_t> chk16 = chkrand.getu16(30);
        size = (int) chk16.get_size();
        width = (int) sizeof(chk16[29]);
        CPPUNIT_ASSERT_EQUAL(30, size);
        CPPUNIT_ASSERT_EQUAL(2, width);

        chkrand.seed(newseed);

        ProtocolPP::jarray<uint32_t> chk32 = chkrand.getword(45);
        size = (int) chk32.get_size();
        width = (int) sizeof(chk32[29]);
        CPPUNIT_ASSERT_EQUAL(45, size);
        CPPUNIT_ASSERT_EQUAL(4, width);

        ProtocolPP::jarray<uint64_t> chk64 = chkrand.getdouble(12);
        size = (int) chk64.get_size();
        width = (int) sizeof(chk64[3]);
        CPPUNIT_ASSERT_EQUAL(12, size);
        CPPUNIT_ASSERT_EQUAL(8, width);

        std::vector<std::string> tokens = chkrand.tokenizer("one:two:three:four", ":");

        unsigned int tokensize = 0x04;

        //CPPUNIT_ASSERT_EQUAL(tokensize, tokens.size());
        CPPUNIT_ASSERT_EQUAL(std::string("one"), tokens[0]);
        CPPUNIT_ASSERT_EQUAL(std::string("two"), tokens[1]);
        CPPUNIT_ASSERT_EQUAL(std::string("three"), tokens[2]);
        CPPUNIT_ASSERT_EQUAL(std::string("four"), tokens[3]);
        std::vector<std::string> tokens2 = chkrand.tokenizer("1..200", "..");
        tokensize = 0x02;
        //CPPUNIT_ASSERT_EQUAL(tokensize, tokens2.size());
        CPPUNIT_ASSERT_EQUAL(std::string("1"), tokens2[0]);
        CPPUNIT_ASSERT_EQUAL(std::string("200"), tokens2[1]);

        ProtocolPP::jarray<uint16_t> my161 = chkrand.getu16("5");
        ProtocolPP::jarray<uint16_t> my162 = chkrand.getu16("10:20");

        ProtocolPP::jarray<uint32_t> my321 = chkrand.getword("4");
        ProtocolPP::jarray<uint32_t> my322 = chkrand.getword("12:25");

        ProtocolPP::jarray<uint64_t> my641 = chkrand.getdouble("3");
        ProtocolPP::jarray<uint64_t> my642 = chkrand.getdouble("14:21");

        int myint = chkrand.get_int();

        ProtocolPP::jarray<uint8_t> mycrypto = chkrand.get_crypto(3);
    }

    void testreplay() {
        uint32_t xseq = 0;
        uint32_t seqnum = 0x00000001;

        // construct using empty window
        ProtocolPP::jreplay<uint32_t, uint32_t> chkreplay(myrand, ProtocolPP::IPSEC, seqnum, xseq, false, 20);
        int size = (int) chkreplay.size();
        CPPUNIT_ASSERT_EQUAL(20, size);
        std::string replay0("00000000000000000001");
        chkreplay.print(true);
        CPPUNIT_ASSERT_EQUAL(replay0, chkreplay.print(false, 0));

        seqnum += 5;
        std::string replay1("00000000000000100001");
        chkreplay.antireplay(seqnum, xseq);
        CPPUNIT_ASSERT_EQUAL(replay1, chkreplay.print(false, 0));

        seqnum += 15;
        std::string replay2("00001000000000000001");
        chkreplay.antireplay(seqnum, xseq);
        CPPUNIT_ASSERT_EQUAL(replay2, chkreplay.print(false, 0));

        seqnum += 10;
        std::string replay3("00000000010000000001");
        chkreplay.antireplay(seqnum, xseq);
        CPPUNIT_ASSERT_EQUAL(replay3, chkreplay.print(false, 0));

        seqnum -= 5;
        std::string replay33("00000000010000100001");
        chkreplay.antireplay(seqnum, xseq);
        CPPUNIT_ASSERT_EQUAL(replay33, chkreplay.print(false, 0));

        seqnum -= 5;
        uint32_t status = ProtocolPP::ERR_REPLAY;
        CPPUNIT_ASSERT_EQUAL(status, chkreplay.antireplay(seqnum, xseq));

        seqnum -= 11;
        status = ProtocolPP::ERR_LATE;
        CPPUNIT_ASSERT_EQUAL(status, chkreplay.antireplay(seqnum, xseq));

        seqnum -= 10;
        status = ProtocolPP::ERR_ROLLUNDER;
        CPPUNIT_ASSERT_EQUAL(status, chkreplay.antireplay(seqnum, xseq));

        // construct too large
        xseq = 0;
        seqnum = 0x00000001;
        std::vector<uint8_t> myvec3 = {0x0C, 0x71};
        ProtocolPP::jarray<uint8_t> mywin2(myvec3);

        ProtocolPP::jreplay<uint32_t, uint32_t> chkreplay1(myrand, ProtocolPP::IPSEC, seqnum, xseq, false, 9, mywin2);
        unsigned int rsize = chkreplay1.size();
        uint32_t rseqnum  = chkreplay1.get_seqnum();
        uint32_t rxseqnum = chkreplay1.get_extseq();

        // construct too large
        xseq = 0;
        seqnum = 0x00000001;
        std::vector<uint8_t> myvec4 = {0x0E, 0x0C, 0x71};
        ProtocolPP::jarray<uint8_t> mywin3(myvec4);

        ProtocolPP::jreplay<uint32_t, uint32_t> chkreplay3(myrand, ProtocolPP::IPSEC, seqnum, xseq, false, 30, mywin3);
        rsize = chkreplay3.size();
        rseqnum  = chkreplay3.get_seqnum();
        rxseqnum = chkreplay3.get_extseq();

        // construct too large
        xseq = 0;
        seqnum = 0x00000001;
        std::vector<uint8_t> myvec6 = {0x0E, 0x0C, 0x71, 0xFF, 0x11};
        ProtocolPP::jarray<uint8_t> mywin6(myvec6);

        ProtocolPP::jreplay<uint32_t, uint32_t> chkreplay6(myrand, ProtocolPP::IPSEC, seqnum, xseq, false, 40, mywin6);
        chkreplay6.print(false,0);
        chkreplay6.print(true,0);

        // construct using a predefined window
        xseq = 0;
        seqnum = 0x00000001;
        std::vector<uint8_t> myvec2 = {0x0E, 0x0C, 0x71};
        ProtocolPP::jarray<uint8_t> mywin(myvec2);

        ProtocolPP::jreplay<uint32_t, uint32_t> chkreplay2(myrand, ProtocolPP::IPSEC, seqnum, xseq, false, 20, mywin);
        size = (int) chkreplay2.size();
        CPPUNIT_ASSERT_EQUAL(20, size);
        std::string replay4("11100000110001110001");
        CPPUNIT_ASSERT_EQUAL(replay4, chkreplay2.print(false, 0));
        chkreplay2.print();
        chkreplay2.print(true);

        seqnum += 5;
        std::string replay5("00011000111000100001");
        chkreplay2.antireplay(seqnum, xseq);
        CPPUNIT_ASSERT_EQUAL(replay5, chkreplay2.print(false, 0));

        seqnum += 10;
        std::string replay6("10001000010000000001");
        chkreplay2.antireplay(seqnum, xseq);
        CPPUNIT_ASSERT_EQUAL(replay6, chkreplay2.print(false, 0));

        seqnum += 10;
        size = (int) chkreplay2.size();
        CPPUNIT_ASSERT_EQUAL(20, size);
        std::string replay7("00000000010000000001");
        chkreplay2.antireplay(seqnum, xseq);
        CPPUNIT_ASSERT_EQUAL(replay7, chkreplay2.print(false, 0));

        seqnum -= 10;
        status = ProtocolPP::ERR_REPLAY;
        CPPUNIT_ASSERT_EQUAL(status, chkreplay2.antireplay(seqnum, xseq));

        seqnum -= 11;
        status = ProtocolPP::ERR_LATE;
        CPPUNIT_ASSERT_EQUAL(status, chkreplay2.antireplay(seqnum, xseq));

        seqnum -= 10;
        status = ProtocolPP::ERR_ROLLUNDER;
        CPPUNIT_ASSERT_EQUAL(status, chkreplay2.antireplay(seqnum, xseq));

        uint64_t seqz1 = 0;
        uint64_t seqz2 = 1;

        ProtocolPP::jreplay<uint64_t, uint64_t> chkreplayz1(myrand, ProtocolPP::IPSEC, seqz1, seqz2, true, 40, mywin6);
        chkreplayz1.antireplay(seqz1,seqz2);
        rsize = chkreplayz1.size();
        uint64_t rseqnum64  = chkreplayz1.get_seqnum();
        uint64_t rxseqnum64 = chkreplayz1.get_extseq();

        uint32_t seqzz1 = 0;
        uint32_t seqzz5 = 1;
        uint16_t seqzz2 = 0xFFFF;
        uint32_t seqzz3 = 0;
        uint16_t seqzz4 = 0;

        ProtocolPP::jreplay<uint16_t, uint32_t> chkreplayz2(myrand, ProtocolPP::SRTP, seqzz2, seqzz1, true, 20, mywin);
        chkreplayz2.antireplay(seqzz4,seqzz3);
        rsize = chkreplayz2.size();
        uint16_t rseqnum16  = chkreplayz2.get_seqnum();
        uint32_t rxseqnum32 = chkreplayz2.get_extseq();

        uint32_t seqzzz1 = 0;
        uint16_t seqzzz2 = 0;

        ProtocolPP::jreplay<uint16_t, uint32_t> chkreplayz4(myrand, ProtocolPP::SRTP, seqzzz2, seqzzz1, true, 20, mywin);
        chkreplayz4.antireplay(seqzz2,seqzzz1);

        ProtocolPP::jreplay<uint32_t, uint32_t> chkreplayz3(myrand, ProtocolPP::IPSEC, seqzz1, seqzz1, false, 10, mywin);
        chkreplayz3.antireplay(seqzz5,seqzz1);

        uint32_t seqzz6 = 1;
        ProtocolPP::jreplay<uint32_t, uint32_t> chkreplayz5(myrand, ProtocolPP::WIMAX, seqzz6, seqzz6, false, 10, mywin);
        chkreplayz5.antireplay(seqzz6,seqzz6);
    }

    void testenum() {
        std::string mychk = "ERR_PROGRAM";
        std::string mynum = ProtocolPP::EnumString<ProtocolPP::err_t>::From(ProtocolPP::ERR_PROGRAM);
        CPPUNIT_ASSERT_EQUAL(mychk, mynum);

        ProtocolPP::protocol_t prot;
        ProtocolPP::EnumString<ProtocolPP::protocol_t>::To(prot, "WIMAX");
        CPPUNIT_ASSERT_EQUAL(ProtocolPP::WIMAX, prot);
    }

    void testwasp() {
        ProtocolPP::wasp myparse(logger, "<?xml version='1.0' encoding='UTF-8'?>\n<protocolpp ver='4.1.0' format='ppp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/protocolpp.xsd'>\n<general/>\n<stream number='100..200' packets='3..5' datalen='64:390:1500'>\n<protocol prot='IP' file=''>\n<security name='ipsa' ver='IPV6:IPV4'/>\n</protocol>\n</stream>\n</protocolpp>");

        ProtocolPP::wasp myparse1(logger, "<?xml version='1.0' encoding='UTF-8'?>\n<protocolpp ver='4.1.0' format='ppp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/protocolpp.xsd'>\n<general/>\n<stream number='100..200' packets='3..5' datalen='64:390:1500'>\n<protocol prot='IP' file=''>\n<security name='ipsa' ver='IPV6:IPV4'/>\n</protocol>\n</stream>\n</protocolpp>","./myout2.protpp");

        ProtocolPP::wasp myparse2(logger, "<?xml version='1.0' encoding='UTF-8'?>\n<protocolpp ver='4.1.0' format='ppp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/protocolpp.xsd'>\n<general/>\n<stream number='100..200' packets='3..5' datalen='64:390:1500'>\n<protocol prot='IP' file=''>\n<security name='ipsa' ver='IPV6:IPV4'/>\n</protocol>\n</stream>\n</protocolpp>");

        ProtocolPP::wasp myparse13(logger, "<?xml version='1.0' encoding='UTF-8'?>\n<protocolpp ver='4.1.0' format='ppp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/protocolpp.xsd'>\n<general/>\n<stream number='100..200' packets='3..5' datalen='64:390:1500'>\n<protocol prot='IP' file=''>\n<security name='ipsa' ver='IPV6:IPV4'/>\n</protocol>\n</stream>\n</protocolpp>","./myout3.protpp");

        std::string myfile("./tests/ip.ppp");
        ProtocolPP::wasp myparse4(logger, myfile);
        ProtocolPP::wasp myparse5(logger, myfile, "./myout.protpp");

//        std::string myfile2("./tests/icmp_enc.protpp");
//        ProtocolPP::wasp myparse6(logger, myfile2, "./myout4.protpp");

        std::string waspStr = myparse.to_str();
        waspStr = myparse1.to_str();
        waspStr = myparse2.to_str();
        waspStr = myparse13.to_str();
        waspStr = myparse4.to_str();
        waspStr = myparse5.to_str();
//        waspStr = myparse6.to_str();
    }

    void testcfg() {
        ProtocolPP::jtestcfg cfg("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='WASP' endian='BIG' sgtsize='8' ptrsize='4'/>\n<flowring name='flow0' index='0' addr='0' size='50'/>\n<inring name='in0' index='0' addr='0' size='50' flow='flow0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' addr='0' size='50'/>\n<responder name='resp0' index='0' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n<inring name='in1' index='1' size='50' input='./tests/debug.ppp'/>\n<outring name='out1' index='1' size='50'/>\n<responder name='resp1' index='1' units='ms' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg4("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='WASP' endian='BIG' sgtsize='8' ptrsize='4'/>\n<flowring name='flow0' index='0' size='50'/>\n<inring name='in0' index='0' size='50' input='./tests/debug.ppp'/>\n<outring name='out0' index='0' size='50'/>\n<responder name='resp0' index='0' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n<inring name='in1' index='1' size='50' input='./tests/debug.ppp'/>\n<outring name='out1' index='1' size='50'/>\n<responder name='resp1' index='1' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg5("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='5.3.1' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/protocolpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='WASP' endian='BIG' sgtsize='8' ptrsize='4' out='myself.txt'/>\n<flowring name='flow0' index='0' size='50' out='myself.txt'/>\n<inring name='in0' index='0' size='50' input='./tests/debug.ppp' out='myout.txt'/>\n<outring name='out0' index='0' size='50' out='myself.txt'/>\n<responder name='resp0' index='0' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n<inring name='in1' index='1' size='50' input='./tests/debug.ppp'/>\n<outring name='out1' index='1' size='50'/>\n<responder name='resp1' index='1' writelatency='50..200' readlatency='200..500' complatency='1000..2500' out='myself.txt'/>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg6("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' out='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='WASP' endian='BIG' sgtsize='8' ptrsize='4'/>\n<flowring name='flow0' index='0' size='50'/>\n<inring name='in0' index='0' size='50' flow='flow0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' size='50'/>\n<responder name='resp0' index='0' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n<inring name='in1' index='1' size='50' input='./tests/debug.ppp'/>\n<outring name='out1' index='1' size='50'/>\n<responder name='resp1' index='1' units='ms' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg7("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/protocolpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='WASP' endian='BIG' sgtsize='8' ptrsize='4'/>\n<flowring name='flow0' index='0' size='50'/>\n<inring name='in0' index='0' size='50' flow='flow0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' size='50'/>\n<responder name='resp0' index='0' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n<inring name='in1' index='1' size='50' input='./tests/debug.ppp'/>\n<outring name='out1' index='1' size='50'/>\n<responder name='resp1' index='1' units='ms' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg8("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='WASP' endian='BIG' sgtsize='8' ptrsize='4'/>\n<flowring name='flow0' index='0' size='50' out='myout.txt'/>\n<inring name='in0' index='0' size='50' flow='flow0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' size='50'/>\n<responder name='resp0' index='0' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n<inring name='in1' index='1' size='50' input='./tests/debug.ppp'/>\n<outring name='out1' index='1' size='50'/>\n<responder name='resp1' index='1' units='ms' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg9("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='WASP' endian='BIG' sgtsize='8' ptrsize='4'/>\n<flowring name='flow0' index='0' size='50' out='myout.txt'/>\n<inring name='in0' index='0' size='50' flow='flow0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' size='50'/>\n<responder name='resp0' index='0' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n<inring name='in1' index='1' size='50' input='./tests/debug.ppp'/>\n<outring name='out1' index='1' size='50'/>\n<responder name='resp1' index='1' units='ms' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg10("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='WASP' endian='BIG' sgtsize='8' ptrsize='4'/>\n<flowring name='flow0' index='0' size='50'/>\n<inring name='in0' index='0' size='50' flow='flow0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' size='50'/>\n<responder name='resp0' index='0' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n<inring name='in1' index='1' size='50' input='./tests/debug.ppp'/>\n<outring name='out1' index='1' size='50'/>\n<responder name='resp1' index='1' units='ms' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n</testpp>", "no_output");
        
        ProtocolPP::jtestcfg cfg11("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='WASP' endian='BIG' sgtsize='8' ptrsize='4'/>\n<flowring name='flow0' index='0' size='50'/>\n<inring name='in0' index='0' size='50' flow='flow0' addr='0' input='./tests/debug.ppp' out='myout.txt'/>\n<outring name='out0' flow='flow0' index='0' size='50'/>\n<responder name='resp0' index='0' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n<inring name='in1' index='1' size='50' input='./tests/debug.ppp'/>\n<outring name='out1' index='1' size='50'/>\n<responder name='resp1' index='1' units='ms' writelatency='50..200' readlatency='200..500' complatency='1000..2500'/>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg12("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='SECPLAT' endian='LITTLE' sgtsize='16' ptrsize='8' debugclr='CYAN' infoclr='RED' warnclr='GREEN' errclr='MAGENTA' fatalclr='BRIGHTWHITE' passclr='BLACK'/>\n<flowring name='flow0' addr='0' index='0' size='50'>\n<inring name='in0' index='0' size='50' flow='flow0' addr='0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' addr='0' size='50'/>\n<responder name='resp0' index='0' units='ms' writelatency='50..200' readlatency='200..500' computelatency='1000..2500'/>\n</flowring>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg13("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='SECPLAT' endian='LITTLE' sgtsize='16' ptrsize='8' debugclr='CYAN' infoclr='RED' warnclr='GREEN' errclr='MAGENTA' fatalclr='BRIGHTWHITE' passclr='BLACK'/>\n<flowring name='flow0' addr='0' index='0' size='50'>\n<inring name='in0' index='0' size='50' flow='flow0' addr='0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' addr='0' size='50'/>\n<responder name='resp0' index='0' units='ms' writelatency='50..200' readlatency='200..500' computelatency='1000..2500' out='myout.txt'/>\n</flowring>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg14("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='SECPLAT' endian='LITTLE' sgtsize='16' ptrsize='8' debugclr='CYAN' infoclr='RED' warnclr='GREEN' errclr='MAGENTA' fatalclr='BRIGHTWHITE' passclr='BLACK'/>\n<flowring name='flow0' addr='0' index='0' size='50'>\n<inring name='in0' index='0' size='50' flow='flow0' addr='0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' addr='0' size='50' out='myout.txt'/>\n<responder name='resp0' index='0' units='ms' writelatency='50..200' readlatency='200..500' computelatency='1000..2500'/>\n</flowring>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg15("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='SECPLAT' endian='LITTLE' sgtsize='16' ptrsize='8' debugclr='CYAN' infoclr='RED' warnclr='GREEN' errclr='MAGENTA' fatalclr='BRIGHTWHITE' passclr='BLACK'/>\n<flowring name='flow0' addr='0' index='0' size='50'>\n<inring name='in0' index='0' size='50' flow='flow0' addr='0' out='myout.txt' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' addr='0' size='50' out='myout.txt'/>\n<responder name='resp0' index='0' units='ms' writelatency='50..200' readlatency='200..500' computelatency='1000..2500'/>\n</flowring>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg16("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='SECPLAT' endian='LITTLE' sgtsize='16' ptrsize='8' debugclr='CYAN' infoclr='RED' warnclr='GREEN' errclr='MAGENTA' fatalclr='BRIGHTWHITE' passclr='BLACK' out='myout.txt'/>\n<flowring name='flow0' addr='0' index='0' size='50'>\n<inring name='in0' index='0' size='50' flow='flow0' addr='0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' addr='0' size='50'/>\n<responder name='resp0' index='0' units='ms' writelatency='50..200' readlatency='200..500' computelatency='1000..2500'/>\n</flowring>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg17("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd'>\n<general seed='' loglvl='4' stdout='true' platform='SECPLAT' endian='LITTLE' sgtsize='16' ptrsize='8' debugclr='CYAN' infoclr='RED' warnclr='GREEN' errclr='MAGENTA' fatalclr='BRIGHTWHITE' passclr='BLACK'/>\n<flowring name='flow0' addr='0' index='0' size='50'>\n<inring name='in0' index='0' size='50' flow='flow0' addr='0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' addr='0' size='50'/>\n<responder name='resp0' index='0' units='ms' writelatency='50..200' readlatency='200..500' computelatency='1000..2500'/>\n<myelement/>\n</flowring>\n</testpp>", "no_output");

        ProtocolPP::jtestcfg cfg19("<?xml version='1.0' encoding='UTF-8'?>\n<testpp ver='4.1.0' format='testpp' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xsi:noNamespaceSchemaLocation='../schema/testpp.xsd' out='myout.txt'>\n<general seed='' loglvl='4' stdout='true' platform='SECPLAT' endian='LITTLE' sgtsize='16' ptrsize='8' debugclr='CYAN' infoclr='RED' warnclr='GREEN' errclr='MAGENTA' fatalclr='BRIGHTWHITE' passclr='BLACK'/>\n<flowring name='flow0' addr='0' index='0' size='50'>\n<inring name='in0' index='0' size='50' flow='flow0' addr='0' input='./tests/debug.ppp'/>\n<outring name='out0' flow='flow0' index='0' addr='0' size='50'/>\n<responder name='resp0' index='0' units='ms' writelatency='50..200' readlatency='200..500' computelatency='1000..2500'/>\n</flowring>\n</testpp>", "no_output");

        std::string cfg2("./tests/ipsec.testpp");
        ProtocolPP::jtestcfg cfg3(cfg2, "no_output");

        std::shared_ptr<tinyxml2::XMLDocument> mydoc = std::make_shared<tinyxml2::XMLDocument>();
        mydoc->LoadFile(cfg2.c_str());
        ProtocolPP::jtestcfg cfg18(mydoc, "no_output");

        uint64_t seed = cfg.get_field<uint64_t>(ProtocolPP::SEED);
        seed = cfg.get_field<uint64_t>(ProtocolPP::SGTSIZE);
        cfg.set_field<uint64_t>(ProtocolPP::SGTSIZE, 1234567890);
        cfg.set_field<uint64_t>(ProtocolPP::LENGTH, 1234567890);
        uint32_t sgsize = cfg.get_field<uint32_t>(ProtocolPP::SGTSIZE);
        uint32_t ptrsize = cfg.get_field<uint32_t>(ProtocolPP::PTRSIZE);
        uint32_t loglvl = cfg.get_field<uint32_t>(ProtocolPP::LOGLVL);
        loglvl = cfg.get_field<uint32_t>(ProtocolPP::STDOUT);
        cfg.set_field<uint32_t>(ProtocolPP::SGTSIZE, sgsize);
        cfg.set_field<uint32_t>(ProtocolPP::PTRSIZE, ptrsize);
        cfg.set_field<uint32_t>(ProtocolPP::LOGLVL, loglvl);
        cfg.set_field<uint32_t>(ProtocolPP::NH, loglvl);
        bool stdoutput = cfg.get_field<bool>(ProtocolPP::STDOUT);
        stdoutput = cfg.get_field<bool>(ProtocolPP::NH);
        cfg.set_field<bool>(ProtocolPP::STDOUT, true);
        cfg.set_field<bool>(ProtocolPP::NH, true);
        ProtocolPP::platform_t myplat = cfg.get_field<ProtocolPP::platform_t>(ProtocolPP::PLATFORM);
        cfg.set_field<ProtocolPP::platform_t>(ProtocolPP::PLATFORM, myplat);
        cfg.set_field<ProtocolPP::platform_t>(ProtocolPP::ENDIAN, myplat);
        ProtocolPP::endian_t myendian = cfg.get_field<ProtocolPP::endian_t>(ProtocolPP::ENDIAN);
        InterfacePP::jlogger::asciicolor colorme = cfg.get_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::NH);
        colorme = cfg.get_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::DEBUGCLR);
        colorme = cfg.get_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::INFOCLR);
        colorme = cfg.get_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::WARNCLR);
        colorme = cfg.get_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::ERRCLR);
        colorme = cfg.get_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::FATALCLR);
        colorme = cfg.get_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::PASSCLR);
        ProtocolPP::endian_t endme = cfg.get_field<ProtocolPP::endian_t>(ProtocolPP::NH);
        cfg.set_field<ProtocolPP::endian_t>(ProtocolPP::ENDIAN, ProtocolPP::endian_t::BIG);
        cfg.set_field<ProtocolPP::endian_t>(ProtocolPP::DIRECTION, ProtocolPP::endian_t::BIG);
        cfg.set_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::DEBUGCLR, InterfacePP::jlogger::asciicolor::MAGENTA);
        cfg.set_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::INFOCLR, InterfacePP::jlogger::asciicolor::RED);
        cfg.set_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::WARNCLR, InterfacePP::jlogger::asciicolor::BLACK);
        cfg.set_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::ERRCLR, InterfacePP::jlogger::asciicolor::GREEN);
        cfg.set_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::FATALCLR, InterfacePP::jlogger::asciicolor::CYAN);
        cfg.set_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::PASSCLR, InterfacePP::jlogger::asciicolor::WHITE);
        cfg.set_field<InterfacePP::jlogger::asciicolor>(ProtocolPP::NH, InterfacePP::jlogger::asciicolor::WHITE);
        cfg12.set_field<uint64_t>(ProtocolPP::SEED, seed);
        cfg12.set_field<ProtocolPP::platform_t>(ProtocolPP::SEED, ProtocolPP::WASP);
        cfg12.get_field<ProtocolPP::platform_t>(ProtocolPP::SEED);
    }

    void testmodes() {
        // Key (K)       :
        ProtocolPP::jarray<uint8_t> key("00000000000000000000000000000000");
        
        //Message (M)    : <empty string>
        ProtocolPP::jarray<uint8_t> aad(0);
        ProtocolPP::jarray<uint8_t> message(0);
        ProtocolPP::jarray<uint8_t> iv("000000000000000000000000");
        ProtocolPP::jarray<uint8_t> expect(0);
        ProtocolPP::jarray<uint8_t> output(message.get_size());
        ProtocolPP::jarray<uint8_t> ricv("58e2fccefa7e3061367f1d57a4e7455a");
        ProtocolPP::jarray<uint8_t> icv(16);
    
        std::shared_ptr<ProtocolPP::jmodes> engine;

        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - key size
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::DES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::ARIA,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::XCBC_MAC,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::ARIA,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::CMAC,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::ARIA,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::AEAD,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::ARIA,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::STREAM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::Serpent,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::CBC,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::DES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::CBC,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::Serpent,
                                                 ProtocolPP::jmodes::DEC,
                                                 ProtocolPP::jmodes::CBC,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::DES,
                                                 ProtocolPP::jmodes::DEC,
                                                 ProtocolPP::jmodes::CBC,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::CHACHA20,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::STREAM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());

        ProtocolPP::jarray<uint8_t> idat(myrand->getbyte(50));
        ProtocolPP::jarray<uint8_t> odat(50);
        engine->ProcessData(idat.get_ptr(), odat.get_ptr(), idat.get_size());

        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::ARC4,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::STREAM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());

        engine->ProcessData(idat.get_ptr(), odat.get_ptr(), idat.get_size());

        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c");
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::POLY1305,
                                               key.get_ptr(),
                                               key.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::POLY1305,
                                               key.get_ptr(),
                                               key.get_size());

        ProtocolPP::jarray<uint8_t> myicv(16);
        engine->ProcessData(idat.get_ptr(), idat.get_size());
        engine->result(myicv.get_ptr(), 16);

        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>(0);
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SM3);
    
        engine->ProcessData(idat.get_ptr(), idat.get_size());
        engine->result(myicv.get_ptr(), 16);

        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SHA224,
                                               key.get_ptr(),
                                               key.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - illegal modes
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>(0);
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::CRC32_IEEE,
                                               key.get_ptr(),
                                               key.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - engine construction
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c");
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::MD5,
                                               key.get_ptr(),
                                               key.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - engine construction
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SHA3_224,
                                               key.get_ptr(),
                                               key.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - engine construction
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SHA3_256,
                                               key.get_ptr(),
                                               key.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - engine construction
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SHA3_384,
                                               key.get_ptr(),
                                               key.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - engine construction
        ///////////////////////////////////////////////////////////////////////
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SHA3_512,
                                               key.get_ptr(),
                                               key.get_size());
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - constructor
        ///////////////////////////////////////////////////////////////////////
        uint32_t poly = 0xfeffe992;
        engine = ProtocolPP::ciphers::get_crc(ProtocolPP::CRC_POLY,
                                              poly,
                                              0);
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - constructor 
        ///////////////////////////////////////////////////////////////////////
        poly = 0xfeffe992;
        engine = ProtocolPP::ciphers::get_crc(ProtocolPP::CRC_POLY,
                                              poly,
                                              32);
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - constructor
        ///////////////////////////////////////////////////////////////////////
        poly = 0xffe992;
        engine = ProtocolPP::ciphers::get_crc(ProtocolPP::CRC8_LTE);
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - constructor
        ///////////////////////////////////////////////////////////////////////
        poly = 0xe992;
        engine = ProtocolPP::ciphers::get_crc(ProtocolPP::CRC16_IBM);
        engine = ProtocolPP::ciphers::get_crc(ProtocolPP::CRC12_UTMS);
    
        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - constructor
        ///////////////////////////////////////////////////////////////////////
        poly = 0x92;
        engine = ProtocolPP::ciphers::get_crc(ProtocolPP::CRC24_LTE_A);
        engine->ProcessData(idat.get_ptr(), idat.get_size());

        engine = ProtocolPP::ciphers::get_crc(ProtocolPP::CRC_POLY,
                                              poly,
                                              8,
                                              false,
                                              true,
                                              false,
                                              true);
        engine->ProcessData(idat.get_ptr(), idat.get_size());
    }

    void testcrc() {
        ProtocolPP::jarray<uint8_t> input(myrand->getbyte(50));
        ProtocolPP::jarray<uint8_t> result(4);
        ProtocolPP::jarray<uint8_t> expect(4);

        std::shared_ptr<ProtocolPP::jmodes> mycrc5 = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC5_USB);
        std::shared_ptr<ProtocolPP::jmodes> mycrc7 = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC7_UTMS);
        std::shared_ptr<ProtocolPP::jmodes> mycrc8 = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC8_LTE);
        std::shared_ptr<ProtocolPP::jmodes> mycrc11 = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC11_UTMS);
        std::shared_ptr<ProtocolPP::jmodes> mycrc12 = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC12_UTMS);
        std::shared_ptr<ProtocolPP::jmodes> mycrc16 = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC16_IBM);
        std::shared_ptr<ProtocolPP::jmodes> mycrc16C = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC16_CCITT);
        std::shared_ptr<ProtocolPP::jmodes> mycrc24A = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC24_LTE_A);
        std::shared_ptr<ProtocolPP::jmodes> mycrc24B = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC24_LTE_B);
        std::shared_ptr<ProtocolPP::jmodes> mycrc31 = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC32_IETF);
        std::shared_ptr<ProtocolPP::jmodes> mycrc32 = ProtocolPP::ciphers::get_crc(ProtocolPP::auth_t::CRC32_IEEE);
        
        mycrc32->ProcessData(input.get_ptr(), input.get_size());
        mycrc32->result(expect.get_ptr(), expect.get_size());

        ProtocolPP::jcrc crcengine(ProtocolPP::auth_t::CRC32_IEEE,
                                   0,
                                   0,
                                   false,
                                   true,
                                   true,
                                   true);

//        crcengine.ProcessData(input.get_ptr(), input.get_size());
//        crcengine.result(result.get_ptr());
//
//        if (result != expect) {
//            std::cerr << "In testcrc() data mismatch" << std::endl;
//            std::cerr << result.debug(expect);
//        }
    }

    void testgcm() {
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #1
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        ProtocolPP::jarray<uint8_t> key("00000000000000000000000000000000");
        
        //Message (M)    : <empty string>
        ProtocolPP::jarray<uint8_t> aad(0);
        ProtocolPP::jarray<uint8_t> message(0);
        ProtocolPP::jarray<uint8_t> iv("000000000000000000000000");
        ProtocolPP::jarray<uint8_t> expect(0);
        ProtocolPP::jarray<uint8_t> output(message.get_size());
        ProtocolPP::jarray<uint8_t> ricv("58e2fccefa7e3061367f1d57a4e7455a");
        ProtocolPP::jarray<uint8_t> icv(16);
    
        std::shared_ptr<ProtocolPP::jmodes> engine;

        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());
    
        if (output != expect) {
            std::cerr << "In testgcm() conformance #1 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #1 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #2
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("00000000000000000000000000000000");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>(0);
        message=ProtocolPP::jarray<uint8_t>("00000000000000000000000000000000");
        iv=ProtocolPP::jarray<uint8_t>("000000000000000000000000");
        expect=ProtocolPP::jarray<uint8_t>("0388dace60b6a392f328c2b971b2fe78");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("ab6e47d42cec13bdf53a67b21257bddf");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());
    
        if (output != expect) {
            std::cerr << "In testgcm() conformance #2 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #2 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #3
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>(0);
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b391aafd255");
        iv=ProtocolPP::jarray<uint8_t>("cafebabefacedbaddecaf888");
        expect=ProtocolPP::jarray<uint8_t>("42831ec2217774244b7221b784d0d49ce3aa212f2c02a4e035c17e2329aca12e21d514b25466931c7d8f6a5aac84aa051ba30b396a0aac973d58e091473f5985");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("4d5c2af327cd64a62cf35abd2ba6fab4");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #3 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #3 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #4
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("feedfacedeadbeeffeedfacedeadbeefabaddad2");
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39");
        iv=ProtocolPP::jarray<uint8_t>("cafebabefacedbaddecaf888");
        expect=ProtocolPP::jarray<uint8_t>("42831ec2217774244b7221b784d0d49ce3aa212f2c02a4e035c17e2329aca12e21d514b25466931c7d8f6a5aac84aa051ba30b396a0aac973d58e091");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("5bc94fbc3221a5db94fae95ae7121a47");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #4 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #4 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #5
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("feedfacedeadbeeffeedfacedeadbeefabaddad2");
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39");
        iv=ProtocolPP::jarray<uint8_t>("cafebabefacedbad");
        expect=ProtocolPP::jarray<uint8_t>("61353b4c2806934a777ff51fa22a4755699b2a714fcdc6f83766e5f97b6c742373806900e49f24b22b097544d4896b424989b5e1ebac0f07c23f4598");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("3612d2e79e3b0785561be14aaca2fccb");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #5 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #5 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #6
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("feedfacedeadbeeffeedfacedeadbeefabaddad2");
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39");
        iv=ProtocolPP::jarray<uint8_t>("9313225df88406e555909c5aff5269aa6a7a9538534f7da1e4c303d2a318a728c3c0c95156809539fcf0e2429a6b525416aedbf5a0de6a57a637b39b");
        expect=ProtocolPP::jarray<uint8_t>("8ce24998625615b603a033aca13fb894be9112a5c3a211a8ba262a3cca7e2ca701e4a9a4fba43c90ccdcb281d48c7c6fd62875d2aca417034c34aee5");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("619cc5aefffe0bfa462af43c1699d050");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #6 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #6 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #7
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("000000000000000000000000000000000000000000000000");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>(0);
        message=ProtocolPP::jarray<uint8_t>(0);
        iv=ProtocolPP::jarray<uint8_t>("000000000000000000000000");
        expect=ProtocolPP::jarray<uint8_t>(0);
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("cd33b28ac773f74ba00ed1f312572435");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #7 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #7 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #8
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("000000000000000000000000000000000000000000000000");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>(0);
        message=ProtocolPP::jarray<uint8_t>("00000000000000000000000000000000");
        iv=ProtocolPP::jarray<uint8_t>("000000000000000000000000");
        expect=ProtocolPP::jarray<uint8_t>("98e7247c07f0fe411c267e4384b0f600");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("2ff58d80033927ab8ef4d4587514f0fb");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #8 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #8 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #9
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>(0);
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b391aafd255");
        iv=ProtocolPP::jarray<uint8_t>("cafebabefacedbaddecaf888");
        expect=ProtocolPP::jarray<uint8_t>("3980ca0b3c00e841eb06fac4872a2757859e1ceaa6efd984628593b40ca1e19c7d773d00c144c525ac619d18c84a3f4718e2448b2fe324d9ccda2710acade256");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("9924a7c8587336bfb118024db8674a14");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #9 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #9 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #10
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("feedfacedeadbeeffeedfacedeadbeefabaddad2");
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39");
        iv=ProtocolPP::jarray<uint8_t>("cafebabefacedbaddecaf888");
        expect=ProtocolPP::jarray<uint8_t>("3980ca0b3c00e841eb06fac4872a2757859e1ceaa6efd984628593b40ca1e19c7d773d00c144c525ac619d18c84a3f4718e2448b2fe324d9ccda2710");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("2519498e80f1478f37ba55bd6d27618c");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #10 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #10 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #11
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("feedfacedeadbeeffeedfacedeadbeefabaddad2");
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39");
        iv=ProtocolPP::jarray<uint8_t>("cafebabefacedbad");
        expect=ProtocolPP::jarray<uint8_t>("0f10f599ae14a154ed24b36e25324db8c566632ef2bbb34f8347280fc4507057fddc29df9a471f75c66541d4d4dad1c9e93a19a58e8b473fa0f062f7");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("65dcc57fcf623a24094fcca40d3533f8");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #11 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #11 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #12
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("feedfacedeadbeeffeedfacedeadbeefabaddad2");
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39");
        iv=ProtocolPP::jarray<uint8_t>("9313225df88406e555909c5aff5269aa6a7a9538534f7da1e4c303d2a318a728c3c0c95156809539fcf0e2429a6b525416aedbf5a0de6a57a637b39b");
        expect=ProtocolPP::jarray<uint8_t>("d27e88681ce3243c4830165a8fdcf9ff1de9a1d8e6b447ef6ef7b79828666e4581e79012af34ddd9e2f037589b292db3e67c036745fa22e7e9b7373b");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("dcf566ff291c25bbb8568fc3d376a6d9");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #12 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #12 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #13
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("0000000000000000000000000000000000000000000000000000000000000000");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>(0);
        message=ProtocolPP::jarray<uint8_t>(0);
        iv=ProtocolPP::jarray<uint8_t>("000000000000000000000000");
        expect=ProtocolPP::jarray<uint8_t>(0);
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("530f8afbc74536b9a963b4f1c4cb738b");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #13 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #13 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #14
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("0000000000000000000000000000000000000000000000000000000000000000");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>(0);
        message=ProtocolPP::jarray<uint8_t>("00000000000000000000000000000000");
        iv=ProtocolPP::jarray<uint8_t>("000000000000000000000000");
        expect=ProtocolPP::jarray<uint8_t>("cea7403d4d606b6e074ec5d3baf39d18");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("d0d1c8a799996bf0265b98b5d48ab919");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #14 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #14 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #15
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>(0);
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b391aafd255");
        iv=ProtocolPP::jarray<uint8_t>("cafebabefacedbaddecaf888");
        expect=ProtocolPP::jarray<uint8_t>("522dc1f099567d07f47f37a32a84427d643a8cdcbfe5c0c97598a2bd2555d1aa8cb08e48590dbb3da7b08b1056828838c5f61e6393ba7a0abcc9f662898015ad");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("b094dac5d93471bdec1a502270e3cc6c");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #15 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #15 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #16
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("feedfacedeadbeeffeedfacedeadbeefabaddad2");
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39");
        iv=ProtocolPP::jarray<uint8_t>("cafebabefacedbaddecaf888");
        expect=ProtocolPP::jarray<uint8_t>("522dc1f099567d07f47f37a32a84427d643a8cdcbfe5c0c97598a2bd2555d1aa8cb08e48590dbb3da7b08b1056828838c5f61e6393ba7a0abcc9f662");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("76fc6ece0f4e1768cddf8853bb2d551b");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #16 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #16 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #17
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("feedfacedeadbeeffeedfacedeadbeefabaddad2");
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39");
        iv=ProtocolPP::jarray<uint8_t>("cafebabefacedbad");
        expect=ProtocolPP::jarray<uint8_t>("c3762df1ca787d32ae47c13bf19844cbaf1ae14d0b976afac52ff7d79bba9de0feb582d33934a4f0954cc2363bc73f7862ac430e64abe499f47c9b1f");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("3a337dbf46a792c45e454913fe2ea8f2");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #17 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #17 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From gcm-nist-6 Appendix B Test Case #18
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("feffe9928665731c6d6a8f9467308308feffe9928665731c6d6a8f9467308308");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("feedfacedeadbeeffeedfacedeadbeefabaddad2");
        message=ProtocolPP::jarray<uint8_t>("d9313225f88406e5a55909c5aff5269a86a7a9531534f7da2e4c303d8a318a721c3c0c95956809532fcf0e2449a6b525b16aedf5aa0de657ba637b39");
        iv=ProtocolPP::jarray<uint8_t>("9313225df88406e555909c5aff5269aa6a7a9538534f7da1e4c303d2a318a728c3c0c95156809539fcf0e2429a6b525416aedbf5a0de6a57a637b39b");
        expect=ProtocolPP::jarray<uint8_t>("5a8def2f0c9e53f1f75d7853659e2a20eeb2b22aafde6419a058ab4f6f746bf40fc0c3b780f244452da3ebf1c5d82cdea2418997200ef82e44ae7e3f");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("a44a8266ee1c8eb0c8b5d4cf5ae9f19a");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::GCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (output != expect) {
            std::cerr << "In testgcm() conformance #18 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testgcm() conformance #18 icv mismatch" << std::endl;
            std::cerr << ricv.debug(icv);
        }

    }

    void testxts() {
        // Key (K)       :
        ProtocolPP::jarray<uint8_t> key = myrand->getbyte(64);
        
        //Message (M)    :
        ProtocolPP::jarray<uint8_t> iv = myrand->getbyte(16);
    
        std::shared_ptr<ProtocolPP::jmodes> engine;
        std::shared_ptr<ProtocolPP::jmodes> engined;

        ///////////////////////////////////////////////////////////////////////
        /// boundary checking - key size
        ///////////////////////////////////////////////////////////////////////
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::XTS,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size());

        engined = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                  ProtocolPP::jmodes::DEC,
                                                  ProtocolPP::jmodes::XTS,
                                                  key.get_ptr(),
                                                  key.get_size(),
                                                  iv.get_ptr(),
                                                  iv.get_size());

        for(int j=0; j<10; j++) {
            ProtocolPP::jarray<uint8_t> input = myrand->getbyte(1024);
            ProtocolPP::jarray<uint8_t> output(input.get_size(), 0);
            ProtocolPP::jarray<uint8_t> expect(input.get_size(), 0);

            engine->ProcessData(input.get_ptr(), output.get_ptr(), input.get_size());
            engined->ProcessData(output.get_ptr(), expect.get_ptr(), output.get_size());
        
            if (input != expect) {
                std::cerr << "In testxts() data mismatch" << std::endl;
                std::cerr << expect.debug(input);
            }
        }
    }

    void testccm() {
        ///////////////////////////////////////////////////////////////////////
        /// From NIST800-38c Appendix C Example Vector #1
        ///////////////////////////////////////////////////////////////////////
        
        // Key (K)       :
        ProtocolPP::jarray<uint8_t> key("404142434445464748494a4b4c4d4e4f");
        
        //Message (M)    : <empty string>
        ProtocolPP::jarray<uint8_t> aad("0001020304050607");
        ProtocolPP::jarray<uint8_t> message("20212223");
        ProtocolPP::jarray<uint8_t> iv("10111213141516");
        ProtocolPP::jarray<uint8_t> expect("7162015b");
        ProtocolPP::jarray<uint8_t> output(message.get_size());
        ProtocolPP::jarray<uint8_t> ricv("4dac255d");
        ProtocolPP::jarray<uint8_t> icv(4);
    
        std::shared_ptr<ProtocolPP::jmodes> engine;
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                     ProtocolPP::jmodes::ENC,
                                     ProtocolPP::jmodes::CCM,
                                     key.get_ptr(),
                                     key.get_size(),
                                     iv.get_ptr(),
                                     iv.get_size(),
                                     icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());
    
        if (output != expect) {
            std::cerr << "In testccm() conformance #1 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testccm() conformance #1 icv mismatch" << std::endl;
            std::cerr << icv.debug(ricv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From NIST800-38c Appendix C Example Vector #2
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("404142434445464748494a4b4c4d4e4f");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("000102030405060708090a0b0c0d0e0f");
        message=ProtocolPP::jarray<uint8_t>("202122232425262728292a2b2c2d2e2f");
        iv=ProtocolPP::jarray<uint8_t>("1011121314151617");
        expect=ProtocolPP::jarray<uint8_t>("d2a1f0e051ea5f62081a7792073d593d");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("1fc64fbfaccd");
        icv=ProtocolPP::jarray<uint8_t>(6);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                     ProtocolPP::jmodes::ENC,
                                     ProtocolPP::jmodes::CCM,
                                     key.get_ptr(),
                                     key.get_size(),
                                     iv.get_ptr(),
                                     iv.get_size(),
                                     icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());
    
        if (output != expect) {
            std::cerr << "In testccm() conformance #2 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testccm() conformance #2 icv mismatch" << std::endl;
            std::cerr << icv.debug(ricv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From NIST800-38c Appendix C Example Vector #3
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("404142434445464748494a4b4c4d4e4f");
        
        //Message (M)    : <empty string>
        aad=ProtocolPP::jarray<uint8_t>("000102030405060708090a0b0c0d0e0f10111213");
        message=ProtocolPP::jarray<uint8_t>("202122232425262728292a2b2c2d2e2f3031323334353637");
        iv=ProtocolPP::jarray<uint8_t>("101112131415161718191a1b");
        expect=ProtocolPP::jarray<uint8_t>("e3b201a9f5b71a7a9b1ceaeccd97e70b6176aad9a4428aa5");
        output=ProtocolPP::jarray<uint8_t>(message.get_size());
        ricv=ProtocolPP::jarray<uint8_t>("484392fbc1b09951");
        icv=ProtocolPP::jarray<uint8_t>(8);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::CCM,
                                                 key.get_ptr(),
                                                 key.get_size(),
                                                 iv.get_ptr(),
                                                 iv.get_size(),
                                                 icv.get_size());
    
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());
    
        if (output != expect) {
            std::cerr << "In testccm() conformance #3 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
        else if (ricv != icv) {
            std::cerr << "In testccm() conformance #3 icv mismatch" << std::endl;
            std::cerr << icv.debug(ricv);
        }

        ///////////////////////////////////////////////////////////////////////
        /// large AAD
        ///////////////////////////////////////////////////////////////////////
        aad=myrand->getbyte(1024);
        engine->ProcessData(message.get_ptr(),
                            output.get_ptr(),
                            message.get_size(),
                            aad.get_ptr(),
                            aad.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());
    }

    void testsm4() {
        // seed the random number generator
        unsigned long seed = static_cast<unsigned long>(time(NULL));
        std::shared_ptr<ProtocolPP::jrand> myrand = std::make_shared<ProtocolPP::jrand>(seed);
    
        ///////////////////////////////////////////////////////////////////////
        /// From SMS4 Encryption Algorithm ver 1.03 Example #1
        ///////////////////////////////////////////////////////////////////////
        
        // Key (K)       :
        ProtocolPP::jarray<uint8_t> key("0123456789ABCDEFFEDCBA9876543210");
        
        //Message (M)    : <empty string>
        ProtocolPP::jarray<uint8_t> message("0123456789ABCDEFFEDCBA9876543210");
        ProtocolPP::jarray<uint8_t> expect("681EDF34D206965E86B3E94F536E4246");
        ProtocolPP::jarray<uint8_t> output(message.get_size());
    
        std::shared_ptr<ProtocolPP::jmodes> engine;
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::SM4,
                                                 ProtocolPP::jmodes::DEC,
                                                 ProtocolPP::jmodes::ECB,
                                                 key.get_ptr(),
                                                 key.get_size());
        engine->ProcessData(expect.get_ptr(),
                            output.get_ptr(),
                            expect.get_size());
    
        if (output != message) {
            std::cerr << "In testsm4() conformance #1 data mismatch" << std::endl;
            std::cerr << output.debug(message);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From SMS4 Encryption Algorithm ver 1.03 Example #2
        ///////////////////////////////////////////////////////////////////////
    
        // Key (K)       :
        key=ProtocolPP::jarray<uint8_t>("0123456789ABCDEFFEDCBA9876543210");
        
        //Message (M)    : <empty string>
        message=ProtocolPP::jarray<uint8_t>("0123456789ABCDEFFEDCBA9876543210");
        expect=ProtocolPP::jarray<uint8_t>("595298C7C6FD271F0402F804C33D3F66");
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::SM4,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::ECB,
                                                 key.get_ptr(),
                                                 key.get_size());
    
        for(int i=0; i<1000000; i++) {
            output=ProtocolPP::jarray<uint8_t>(message.get_size());
            engine->ProcessData(message.get_ptr(),
                                output.get_ptr(),
                                message.get_size());
            message = output;
        }
    
        if (output != expect) {
            std::cerr << "In testsm4() conformance #2 data mismatch" << std::endl;
            std::cerr << output.debug(expect);
        }
    }

    void testsnow() {
        ProtocolPP::jsnow3g::dir_t mydir = ProtocolPP::jsnow3g::dir_t::SNOW3G_UPLINK;
        ProtocolPP::jarray<uint8_t> mykey = myrand->getbyte(16);
        ProtocolPP::jarray<uint32_t> myctx(19,0,ProtocolPP::endian_t::BIG);
        uint32_t mycount = myrand->get_u32();
        uint8_t mybear = myrand->get_u8();

        ProtocolPP::jsnow3g mysnow(mydir,
                                   mykey.get_ptr(),
                                   mykey.get_size(),
                                   mycount,
                                   mybear);

        mysnow.context(myctx.get_ptr());
    }

    void testsnowv() {
        std::shared_ptr<ProtocolPP::jmodes> enginec;

        //////////////////////////////////////////
        // SNOW-V test vectors #1:
        //////////////////////////////////////////
        
        ProtocolPP::jarray<uint8_t> key1("0000000000000000000000000000000000000000000000000000000000000000");
        ProtocolPP::jarray<uint8_t>  iv1("00000000000000000000000000000000");
       
        // Initialization phase
        std::vector<uint8_t> zi1 = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                    0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,
                                    0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,0xa5,
                                    0xea,0xea,0xea,0xea,0xeb,0xeb,0xeb,0xeb,0xeb,0xeb,0xeb,0xeb,0xeb,0xeb,0xeb,0xeb,
                                    0x55,0xf7,0xf7,0xc2,0xe8,0xe8,0xdd,0x4a,0xe8,0xdd,0x4a,0xe8,0xdd,0x4a,0xe8,0xe8,
                                    0xc7,0x2a,0x23,0xbf,0xe8,0x93,0x73,0x30,0x23,0xbc,0x66,0xec,0x94,0xd2,0xeb,0xb2,
                                    0xa7,0xdd,0xca,0xf3,0x13,0x87,0x61,0x02,0x6e,0xad,0xf4,0x2b,0x54,0xe3,0xef,0xcf,
                                    0x6a,0x67,0x62,0x3e,0x6f,0x8a,0xf9,0x79,0x1e,0xcd,0x81,0x83,0xc5,0x86,0x8e,0x3a,
                                    0x45,0x10,0x1e,0x83,0xa2,0xc6,0xdd,0xeb,0x40,0x86,0x38,0x2d,0xac,0xfb,0x3b,0x65,
                                    0x3c,0xc4,0xdf,0x56,0xec,0xbf,0xc1,0x06,0x6d,0xac,0x02,0xc5,0x0a,0x68,0x3c,0xfe,
                                    0x0c,0xcb,0xe1,0xde,0x2e,0x41,0xaf,0xda,0x70,0x98,0xd5,0x60,0x19,0x20,0x06,0x98,
                                    0x53,0xcd,0x98,0x69,0xc7,0x78,0xca,0xde,0xd7,0xdb,0x45,0x9b,0x6f,0x45,0x8b,0x10,
                                    0x8d,0x94,0x0b,0xe5,0x9f,0xbd,0xb1,0x61,0xc1,0x21,0xfc,0x29,0x7a,0x3d,0x0a,0x15,
                                    0x26,0x13,0x2c,0x14,0x9e,0xaf,0x12,0xcc,0xd3,0x2f,0x35,0x76,0xf6,0x43,0x68,0x94,
                                    0x0e,0x75,0xbe,0x09,0x54,0x18,0x1e,0xf5,0x8a,0x60,0xa9,0xa9,0x54,0x3a,0x05,0xff,
                                    0xdc,0x77,0xa4,0x97,0x23,0xeb,0x65,0x6a,0xe1,0x8f,0x28,0x2c,0xf1,0xde,0x1d,0x00};
        
        //Keystream phase
        std::vector<uint8_t> zk1 = {0x69,0xca,0x6d,0xaf,0x9a,0xe3,0xb7,0x2d,0xb1,0x34,0xa8,0x5a,0x83,0x7e,0x41,0x9d,
                                    0xec,0x08,0xaa,0xd3,0x9d,0x7b,0x0f,0x00,0x9b,0x60,0xb2,0x8c,0x53,0x43,0x00,0xed,
                                    0x84,0xab,0xf5,0x94,0xfb,0x08,0xa7,0xf1,0xf3,0xa2,0xdf,0x18,0xe6,0x17,0x68,0x3b,
                                    0x48,0x1f,0xa3,0x78,0x07,0x9d,0xcf,0x04,0xdb,0x53,0xb5,0xd6,0x29,0xa9,0xeb,0x9d,
                                    0x03,0x1c,0x15,0x9d,0xcc,0xd0,0xa5,0x0c,0x4d,0x5d,0xbf,0x51,0x15,0xd8,0x70,0x39,
                                    0xc0,0xd0,0x3c,0xa1,0x37,0x0c,0x19,0x40,0x03,0x47,0xa0,0xb4,0xd2,0xe9,0xdb,0xe5,
                                    0xcb,0xca,0x60,0x82,0x14,0xa2,0x65,0x82,0xcf,0x68,0x09,0x16,0xb3,0x45,0x13,0x21,
                                    0x95,0x4f,0xdf,0x30,0x84,0xaf,0x02,0xf6,0xa8,0xe2,0x48,0x1d,0xe6,0xbf,0x82,0x79};
        
        ProtocolPP::jsnowv engine0(ProtocolPP::jsnowv::dir_t::SNOWV_DEC,
                                   ProtocolPP::jsnowv::mode_t::SNOWV,
                                   key1.get_ptr(),
                                   key1.get_size(),
                                   iv1.get_ptr(),
                                   iv1.get_size());
        
        //////////////////////////////////////////
        // SNOW-V test vectors #2:
        //////////////////////////////////////////
        
        ProtocolPP::jarray<uint8_t> key2("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        ProtocolPP::jarray<uint8_t>  iv2("ffffffffffffffffffffffffffffffff");
        
        // Initialization phase
        std::vector<uint8_t> zi2 = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
                                    0xd3,0x07,0xd2,0x07,0xd3,0x07,0xd2,0x07,0xd3,0x07,0x2d,0xf8,0x2e,0xf8,0x2d,0xf8,
                                    0x65,0xf6,0x62,0xf6,0x65,0xf6,0x62,0xf6,0x65,0xf6,0x62,0xf6,0x65,0xf6,0x62,0xf6,
                                    0xfe,0x86,0xfe,0x86,0xf5,0x2d,0xf2,0x2d,0x31,0x96,0xd7,0x54,0x6a,0xe8,0x6a,0xe8,
                                    0x8b,0xd8,0x8a,0xa5,0xc8,0x29,0xc6,0x26,0x7c,0x51,0x37,0x97,0xbf,0x9a,0xc8,0x7c,
                                    0x21,0xc0,0x4a,0x14,0xe4,0x1c,0x34,0x95,0xd0,0x9c,0x96,0xe5,0x48,0x60,0x89,0x81,
                                    0x7c,0xce,0x64,0x29,0x1a,0xcf,0x8f,0x4a,0x06,0xca,0x55,0x65,0x3f,0xc4,0x93,0x97,
                                    0x0a,0xf9,0x1c,0x75,0x0f,0xd3,0x80,0xe3,0x48,0x6b,0xff,0xe5,0xc7,0xbb,0xe3,0xd4,
                                    0x89,0x60,0x89,0xa2,0xe6,0xf0,0x7c,0x2c,0x92,0xed,0x62,0xed,0x9d,0x43,0x61,0x98,
                                    0xff,0x04,0xbf,0x72,0x41,0xc0,0x7f,0x6b,0x17,0xfd,0x90,0xc8,0x8a,0x61,0xbf,0xca,
                                    0x97,0x88,0x78,0x33,0x20,0x08,0x2f,0xf6,0xf9,0x34,0x45,0x18,0x6e,0x71,0xbc,0xbc,
                                    0x7e,0x17,0xb4,0xff,0x42,0x3a,0x2e,0x2c,0xc7,0xc5,0x0f,0x84,0x5d,0x9b,0xb3,0xee,
                                    0x32,0x40,0x8c,0x85,0x58,0xe0,0xd2,0x7e,0xf5,0xa3,0xa8,0xd7,0x63,0x32,0x25,0xdc,
                                    0xa2,0x93,0x73,0xc3,0x48,0x2b,0x3f,0x1a,0xd3,0x3b,0xb4,0x57,0xa3,0x0d,0x7f,0xe4,
                                    0x72,0xe0,0x95,0x5b,0x9a,0x83,0x3a,0x3f,0xdb,0x98,0x68,0x56,0x35,0x80,0xb4,0xb0,
                                    0x94,0x9f,0xbe,0x85,0xa4,0xe5,0x35,0x7f,0xbf,0x75,0xe9,0x86,0x4d,0x2c,0x7b,0xa1};
        
        // Keystream phase
        std::vector<uint8_t> zk2 = {0x30,0x76,0x09,0xfb,0x10,0x10,0x12,0x54,0x4b,0xc1,0x75,0xe3,0x17,0xfb,0x25,0xff,
                                    0x33,0x0d,0x0d,0xe2,0x5a,0xf6,0xaa,0xd1,0x05,0x05,0xb8,0x9b,0x1e,0x09,0xa8,0xec,
                                    0xdd,0x46,0x72,0xcc,0xbb,0x98,0xc7,0xf2,0xc4,0xe2,0x4a,0xf5,0x27,0x28,0x36,0xc8,
                                    0x7c,0xc7,0x3a,0x81,0x76,0xb3,0x9c,0xe9,0x30,0x3b,0x3e,0x76,0x4e,0x9b,0xe3,0xe7,
                                    0x48,0xf7,0x65,0x1a,0x7c,0x7e,0x81,0x3f,0xd5,0x24,0x90,0x23,0x1e,0x56,0xf7,0xc1,
                                    0x44,0xe4,0x38,0xe7,0x77,0x11,0xa6,0xb0,0xba,0xfb,0x60,0x45,0x0c,0x62,0xd7,0xd9,
                                    0xb9,0x24,0x1d,0x12,0x44,0xfc,0xb4,0x9d,0xa1,0xe5,0x2b,0x80,0x13,0xde,0xcd,0xd4,
                                    0x86,0x04,0xff,0xfc,0x62,0x67,0x6e,0x70,0x3b,0x3a,0xb8,0x49,0xcb,0xa6,0xea,0x09};
        
        ProtocolPP::jsnowv engine02(ProtocolPP::jsnowv::dir_t::SNOWV_DEC,
                                    ProtocolPP::jsnowv::mode_t::SNOWV,
                                    key2.get_ptr(),
                                    key2.get_size(),
                                    iv2.get_ptr(),
                                    iv2.get_size());
        
        //////////////////////////////////////////
        // SNOW-V test vectors #3:
        //////////////////////////////////////////
        
        ProtocolPP::jarray<uint8_t> key3("505152535455565758595a5b5c5d5e5f0a1a2a3a4a5a6a7a8a9aaabacadaeafa");
        ProtocolPP::jarray<uint8_t>  iv3("0123456789abcdeffedcba9876543210");
        
        // Initialization phase
        std::vector<uint8_t> zi3 = {0x0a,0x1a,0x2a,0x3a,0x4a,0x5a,0x6a,0x7a,0x8a,0x9a,0xaa,0xba,0xca,0xda,0xea,0xfa,
                                    0x66,0xd4,0x2d,0x92,0xac,0x52,0xb6,0x44,0x63,0x3c,0xc3,0x71,0xc3,0x91,0xc6,0x24,
                                    0xa2,0xd7,0xea,0xbe,0x3f,0x04,0x8e,0x50,0x00,0xb1,0x7b,0x74,0x2f,0x34,0x5e,0x49,
                                    0x96,0xa7,0x34,0xed,0xfd,0x07,0x46,0x9d,0xc8,0xf9,0xa2,0x91,0xfc,0x13,0x76,0x73,
                                    0x58,0xc8,0x70,0x73,0xd8,0xa2,0xa1,0xbd,0x03,0xe7,0xa1,0x4c,0xc7,0xb7,0xdb,0x89,
                                    0x7e,0x86,0xeb,0x71,0xd6,0xdc,0x00,0x99,0xd1,0x31,0xe3,0x1b,0x54,0xc5,0x3e,0xf8,
                                    0xa8,0xca,0xff,0x06,0x0d,0xc0,0x9e,0x67,0xcc,0x95,0x62,0x16,0x17,0x19,0x8c,0xf2,
                                    0xc0,0x99,0x3a,0x55,0xf3,0xe2,0xd7,0x8d,0x6a,0xf7,0xe1,0x57,0x0f,0xa1,0x63,0x02,
                                    0x39,0x8f,0xa0,0x7e,0xab,0xa2,0x73,0x89,0x94,0xf9,0xac,0x3e,0x8e,0xb1,0xff,0x64,
                                    0x15,0x32,0x31,0x6a,0x42,0x5c,0x12,0xa6,0x39,0xce,0x79,0xcb,0x30,0x43,0x47,0x1e,
                                    0x2e,0x7a,0x44,0xfd,0xad,0x23,0x77,0x5a,0xf1,0x61,0x1c,0xca,0x5b,0xb2,0x1e,0x95,
                                    0x93,0x69,0xc8,0x20,0xa9,0x37,0xd5,0xc8,0xb6,0x7a,0xdf,0x84,0x45,0x5e,0x13,0xc3,
                                    0xc1,0x0f,0x8d,0xb5,0xfb,0x37,0x08,0x31,0x11,0xd1,0xc8,0x44,0x6e,0xa2,0xac,0x9e,
                                    0x13,0xac,0x34,0x20,0x7b,0x01,0xb7,0xab,0xd3,0x57,0x02,0xa1,0xed,0x98,0x9b,0xdc,
                                    0x0b,0x15,0x43,0xa4,0x74,0x26,0x2c,0x76,0xa3,0xe2,0x73,0x57,0x28,0x4b,0xdc,0x67,
                                    0x7b,0x79,0x91,0x96,0xcf,0x6b,0x76,0x27,0xf8,0xdd,0xa1,0x89,0xbb,0xaf,0xdc,0x93};
        
        // Keystream phase
        std::vector<uint8_t> zk3 = {0xaa,0x81,0xea,0xfb,0x8b,0x86,0x16,0xce,0x3e,0x5c,0xe2,0x22,0x24,0x61,0xc5,0x0a,
                                    0x6a,0xb4,0x48,0x77,0x56,0xde,0x4b,0xd3,0x1c,0x90,0x4f,0x3d,0x97,0x8a,0xfe,0x56,
                                    0x33,0x4f,0x10,0xdd,0xdf,0x2b,0x95,0x31,0x76,0x9a,0x71,0x05,0x0b,0xe4,0x38,0x5f,
                                    0xc2,0xb6,0x19,0x2c,0x7a,0x85,0x7b,0xe8,0xb4,0xfc,0x28,0xb7,0x09,0xf0,0x8f,0x11,
                                    0xf2,0x06,0x49,0xe2,0xee,0xf2,0x49,0x80,0xf8,0x6c,0x4c,0x11,0x36,0x41,0xfe,0xd2,
                                    0xf3,0xf6,0xfa,0x2b,0x91,0x95,0x12,0x06,0xb8,0x01,0xdb,0x15,0x46,0x65,0x17,0xa6,
                                    0x33,0x0a,0xdd,0xa6,0xb3,0x5b,0x26,0x5e,0xfd,0x72,0x2e,0x86,0x77,0xb4,0x8b,0xfc,
                                    0x15,0xb4,0x41,0x18,0xde,0x52,0xd0,0x73,0xb0,0xad,0x0f,0xe7,0x59,0x4d,0x62,0x91};
        
        ProtocolPP::jsnowv engine03(ProtocolPP::jsnowv::dir_t::SNOWV_DEC,
                                    ProtocolPP::jsnowv::mode_t::SNOWV,
                                    key3.get_ptr(),
                                    key3.get_size(),
                                    iv3.get_ptr(),
                                    iv3.get_size());
        
        //////////////////////////////////////////
        // SNOW-V-GCM test vectors #1:
        //////////////////////////////////////////
        
        ProtocolPP::jarray<uint8_t> keygcm1("0000000000000000000000000000000000000000000000000000000000000000");
        ProtocolPP::jarray<uint8_t> ivgcm1("00000000000000000000000000000000");
        ProtocolPP::jarray<uint8_t> aadgcm1("");
        ProtocolPP::jarray<uint8_t> plaingcm1("");
        ProtocolPP::jarray<uint8_t> keygcm1H("e9c0d9300799d4f670230878cd4965d5");
        ProtocolPP::jarray<uint8_t> endpadgcm1("029a624cdaa4d46cb9a0ef4046956c9f");
        ProtocolPP::jarray<uint8_t> ciphergcm1("");
        ProtocolPP::jarray<uint8_t> authgcm1("029a624cdaa4d46cb9a0ef4046956c9f");
        ProtocolPP::jarray<uint8_t> expectgcm1("");
        ProtocolPP::jarray<uint8_t> icvgcm1(16, 0);
        
        // test direct interface
        ProtocolPP::jsnowv engine1(ProtocolPP::jsnowv::dir_t::SNOWV_ENC,
                                   ProtocolPP::jsnowv::mode_t::SNOWV_GCM,
                                   keygcm1.get_ptr(),
                                   keygcm1.get_size(),
                                   ivgcm1.get_ptr(),
                                   ivgcm1.get_size());
        
        engine1.ProcessData(plaingcm1.get_ptr(),
                            expectgcm1.get_ptr(),
                            plaingcm1.get_size(),
                            aadgcm1.get_ptr(),
                            aadgcm1.get_size());
        
        engine1.result(icvgcm1.get_ptr(), 16);
        
        CPPUNIT_ASSERT_EQUAL(authgcm1.to_string(), icvgcm1.to_string());
                            
        // test ciphers interface
        expectgcm1 = ProtocolPP::jarray<uint8_t>(plaingcm1.get_size(), 0);
        icvgcm1 = ProtocolPP::jarray<uint8_t>(16, 0);

        enginec = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::SNOWV_GCM,
                                                  ProtocolPP::jmodes::ENC,
                                                  ProtocolPP::jmodes::AEAD,
                                                  keygcm1.get_ptr(),
                                                  keygcm1.get_size(),
                                                  ivgcm1.get_ptr(),
                                                  ivgcm1.get_size());

        enginec->ProcessData(plaingcm1.get_ptr(),
                             expectgcm1.get_ptr(),
                             plaingcm1.get_size(),
                             aadgcm1.get_ptr(),
                             aadgcm1.get_size());

        enginec->result(icvgcm1.get_ptr(),
                        icvgcm1.get_size());

        CPPUNIT_ASSERT_EQUAL(authgcm1.to_string(), icvgcm1.to_string());

        //////////////////////////////////////////
        // SNOW-V-GCMtestvectors#2:
        //////////////////////////////////////////
        
        ProtocolPP::jarray<uint8_t> keygcm2("505152535455565758595a5b5c5d5e5f0a1a2a3a4a5a6a7a8a9aaabacadaeafa");
        ProtocolPP::jarray<uint8_t> ivgcm2("0123456789abcdeffedcba9876543210");
        ProtocolPP::jarray<uint8_t> aadgcm2("");
        ProtocolPP::jarray<uint8_t> plaingcm2("");
        ProtocolPP::jarray<uint8_t> keyHgcm2("a578c7e6c9dde77fafb7ae37fa56954a");
        ProtocolPP::jarray<uint8_t> endpadgcm2("fc7cac574c49feae6150315b9685424c");
        ProtocolPP::jarray<uint8_t> ciphergcm2("");
        ProtocolPP::jarray<uint8_t> authgcm2("fc7cac574c49feae6150315b9685424c");
        ProtocolPP::jarray<uint8_t> expectgcm2("");
        ProtocolPP::jarray<uint8_t> icvgcm2(16, 0);
        
        // test direct inferface
        ProtocolPP::jsnowv engine2(ProtocolPP::jsnowv::dir_t::SNOWV_ENC,
                                   ProtocolPP::jsnowv::mode_t::SNOWV_GCM,
                                   keygcm2.get_ptr(),
                                   keygcm2.get_size(),
                                   ivgcm2.get_ptr(),
                                   ivgcm2.get_size());
        
        engine2.ProcessData(plaingcm2.get_ptr(),
                            expectgcm2.get_ptr(),
                            plaingcm2.get_size(),
                            aadgcm2.get_ptr(),
                            aadgcm2.get_size());
        
        engine2.result(icvgcm2.get_ptr(), 16);
        
        CPPUNIT_ASSERT_EQUAL(authgcm2.to_string(), icvgcm2.to_string());
                           
        // test ciphers interface
        expectgcm2 = ProtocolPP::jarray<uint8_t>(plaingcm2.get_size(), 0);
        icvgcm2 = ProtocolPP::jarray<uint8_t>(16, 0);

        enginec = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::SNOWV_GCM,
                                                  ProtocolPP::jmodes::ENC,
                                                  ProtocolPP::jmodes::AEAD,
                                                  keygcm2.get_ptr(),
                                                  keygcm2.get_size(),
                                                  ivgcm2.get_ptr(),
                                                  ivgcm2.get_size());

        enginec->ProcessData(plaingcm2.get_ptr(),
                             expectgcm2.get_ptr(),
                             plaingcm2.get_size(),
                             aadgcm2.get_ptr(),
                             aadgcm2.get_size());

        enginec->result(icvgcm2.get_ptr(),
                        icvgcm2.get_size());

        CPPUNIT_ASSERT_EQUAL(authgcm2.to_string(), icvgcm2.to_string());

        //////////////////////////////////////////
        // SNOW-V-GCMtestvectors#3:
        //////////////////////////////////////////
        
        ProtocolPP::jarray<uint8_t> keygcm3("0000000000000000000000000000000000000000000000000000000000000000");
        ProtocolPP::jarray<uint8_t> ivgcm3("00000000000000000000000000000000");
        ProtocolPP::jarray<uint8_t> aadgcm3("30313233343536373839616263646566");
        ProtocolPP::jarray<uint8_t> plaingcm3("");
        ProtocolPP::jarray<uint8_t> keyHgcm3("e9c0d9300799d4f670230878cd4965d5");
        ProtocolPP::jarray<uint8_t> endpadgcm3("029a624cdaa4d46cb9a0ef4046956c9f");
        ProtocolPP::jarray<uint8_t> ciphergcm3("");
        ProtocolPP::jarray<uint8_t> authgcm3("5a5aa5fbd635ef1ae129614203e10384");
        ProtocolPP::jarray<uint8_t> expectgcm3("");
        
        // test direct interface
        ProtocolPP::jsnowv engine3(ProtocolPP::jsnowv::dir_t::SNOWV_ENC,
                                   ProtocolPP::jsnowv::mode_t::SNOWV_GCM,
                                   keygcm3.get_ptr(),
                                   keygcm3.get_size(),
                                   ivgcm3.get_ptr(),
                                   ivgcm3.get_size());
        
        engine3.ProcessData(plaingcm3.get_ptr(),
                            expectgcm3.get_ptr(),
                            plaingcm3.get_size(),
                            aadgcm3.get_ptr(),
                            aadgcm3.get_size());
        
        ProtocolPP::jarray<uint8_t> icvgcm3(engine3.result_size(), 0);
        engine3.result(icvgcm3.get_ptr(), 16);
        
        CPPUNIT_ASSERT_EQUAL(authgcm3.to_string(), icvgcm3.to_string());

        ProtocolPP::jarray<uint16_t> ctx3(44,0);
        engine3.context(ctx3.get_ptr());
                     
        // test ciphers interface
        expectgcm3 = ProtocolPP::jarray<uint8_t>(plaingcm3.get_size(), 0);
        icvgcm3 = ProtocolPP::jarray<uint8_t>(16, 0);

        enginec = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::SNOWV_GCM,
                                                  ProtocolPP::jmodes::ENC,
                                                  ProtocolPP::jmodes::AEAD,
                                                  keygcm3.get_ptr(),
                                                  keygcm3.get_size(),
                                                  ivgcm3.get_ptr(),
                                                  ivgcm3.get_size());

        enginec->ProcessData(plaingcm3.get_ptr(),
                             expectgcm3.get_ptr(),
                             plaingcm3.get_size(),
                             aadgcm3.get_ptr(),
                             aadgcm3.get_size());

        enginec->result(icvgcm3.get_ptr(),
                        icvgcm3.get_size());

        CPPUNIT_ASSERT_EQUAL(authgcm3.to_string(), icvgcm3.to_string());

        //////////////////////////////////////////
        // SNOW-V-GCMtestvectors#4:
        //////////////////////////////////////////
        
        ProtocolPP::jarray<uint8_t> keygcm4("505152535455565758595a5b5c5d5e5f0a1a2a3a4a5a6a7a8a9aaabacadaeafa");
        ProtocolPP::jarray<uint8_t> ivgcm4("0123456789abcdeffedcba9876543210");
        ProtocolPP::jarray<uint8_t> aadgcm4("30313233343536373839616263646566");
        ProtocolPP::jarray<uint8_t> plaingcm4("");
        ProtocolPP::jarray<uint8_t> keyHgcm4("a578c7e6c9dde77fafb7ae37fa56954a");
        ProtocolPP::jarray<uint8_t> endpadgcm4("fc7cac574c49feae6150315b9685424c");
        ProtocolPP::jarray<uint8_t> ciphergcm4("");
        ProtocolPP::jarray<uint8_t> authgcm4("250ec8d77a022c087adf08b65adcbb1a");
        ProtocolPP::jarray<uint8_t> expectgcm4("");
        ProtocolPP::jarray<uint8_t> icvgcm4(16, 0);
       
        // test direct interface
        ProtocolPP::jsnowv engine4(ProtocolPP::jsnowv::dir_t::SNOWV_ENC,
                                   ProtocolPP::jsnowv::mode_t::SNOWV_GCM,
                                   keygcm4.get_ptr(),
                                   keygcm4.get_size(),
                                   ivgcm4.get_ptr(),
                                   ivgcm4.get_size());
        
        engine4.ProcessData(plaingcm4.get_ptr(),
                            expectgcm4.get_ptr(),
                            plaingcm4.get_size(),
                            aadgcm4.get_ptr(),
                            aadgcm4.get_size());
        
        engine4.result(icvgcm4.get_ptr(), 16);
        
        CPPUNIT_ASSERT_EQUAL(authgcm4.to_string(), icvgcm4.to_string());
                           
        // test ciphers interface
        expectgcm4 = ProtocolPP::jarray<uint8_t>(plaingcm4.get_size(), 0);
        icvgcm4 = ProtocolPP::jarray<uint8_t>(16, 0);

        enginec = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::SNOWV_GCM,
                                                  ProtocolPP::jmodes::ENC,
                                                  ProtocolPP::jmodes::AEAD,
                                                  keygcm4.get_ptr(),
                                                  keygcm4.get_size(),
                                                  ivgcm4.get_ptr(),
                                                  ivgcm4.get_size());

        enginec->ProcessData(plaingcm4.get_ptr(),
                             expectgcm4.get_ptr(),
                             plaingcm4.get_size(),
                             aadgcm4.get_ptr(),
                             aadgcm4.get_size());

        enginec->result(icvgcm4.get_ptr(),
                        icvgcm4.get_size());

        CPPUNIT_ASSERT_EQUAL(authgcm4.to_string(), icvgcm4.to_string());

        //////////////////////////////////////////
        // SNOW-V-GCMtestvectors#5:
        //////////////////////////////////////////
        
        ProtocolPP::jarray<uint8_t> keygcm5("505152535455565758595a5b5c5d5e5f0a1a2a3a4a5a6a7a8a9aaabacadaeafa");
        ProtocolPP::jarray<uint8_t> ivgcm5("0123456789abcdeffedcba9876543210");
        ProtocolPP::jarray<uint8_t> aadgcm5("");
        ProtocolPP::jarray<uint8_t> plaingcm5("30313233343536373839");
        ProtocolPP::jarray<uint8_t> keyHgcm5("a578c7e6c9dde77fafb7ae37fa56954a");
        ProtocolPP::jarray<uint8_t> endpadgcm5("fc7cac574c49feae6150315b9685424c");
        ProtocolPP::jarray<uint8_t> ciphergcm5("dd7e01b2b424a2ef8250");
        ProtocolPP::jarray<uint8_t> authgcm5("ddfe4e31e7bfe6902331ec5ce319d90d");
        ProtocolPP::jarray<uint8_t> expectgcm5(plaingcm5.get_size(), 0);
        ProtocolPP::jarray<uint8_t> icvgcm5(16, 0);
        
        // test direct interface
        ProtocolPP::jsnowv engine5(ProtocolPP::jsnowv::dir_t::SNOWV_ENC,
                                   ProtocolPP::jsnowv::mode_t::SNOWV_GCM,
                                   keygcm5.get_ptr(),
                                   keygcm5.get_size(),
                                   ivgcm5.get_ptr(),
                                   ivgcm5.get_size());
        
        engine5.ProcessData(plaingcm5.get_ptr(),
                            expectgcm5.get_ptr(),
                            plaingcm5.get_size(),
                            aadgcm5.get_ptr(),
                            aadgcm5.get_size());
        
        engine5.result(icvgcm5.get_ptr(), 16);
        
        CPPUNIT_ASSERT_EQUAL(expectgcm5.to_string(), ciphergcm5.to_string());
        CPPUNIT_ASSERT_EQUAL(authgcm5.to_string(), icvgcm5.to_string());
                         
        // test ciphers interface
        expectgcm5 = ProtocolPP::jarray<uint8_t>(plaingcm5.get_size(), 0);
        icvgcm5 = ProtocolPP::jarray<uint8_t>(16, 0);

        enginec = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::SNOWV_GCM,
                                                  ProtocolPP::jmodes::ENC,
                                                  ProtocolPP::jmodes::AEAD,
                                                  keygcm5.get_ptr(),
                                                  keygcm5.get_size(),
                                                  ivgcm5.get_ptr(),
                                                  ivgcm5.get_size());

        enginec->ProcessData(plaingcm5.get_ptr(),
                             expectgcm5.get_ptr(),
                             plaingcm5.get_size(),
                             aadgcm5.get_ptr(),
                             aadgcm5.get_size());

        enginec->result(icvgcm5.get_ptr(),
                        icvgcm5.get_size());

        CPPUNIT_ASSERT_EQUAL(expectgcm5.to_string(), ciphergcm5.to_string());
        CPPUNIT_ASSERT_EQUAL(authgcm5.to_string(), icvgcm5.to_string());

        //////////////////////////////////////////
        // SNOW-V-GCMtestvectors#6:
        //////////////////////////////////////////
        
        ProtocolPP::jarray<uint8_t> keygcm6("505152535455565758595a5b5c5d5e5f0a1a2a3a4a5a6a7a8a9aaabacadaeafa");
        ProtocolPP::jarray<uint8_t> ivgcm6("0123456789abcdeffedcba9876543210");
        ProtocolPP::jarray<uint8_t> aadgcm6("41414420746573742076616c756521");
        ProtocolPP::jarray<uint8_t> plaingcm6("3031323334353637383961626364656620536e6f77562d41454144206d6f646521");
        ProtocolPP::jarray<uint8_t> keyHgcm6("a578c7e6c9dde77fafb7ae37fa56954a");
        ProtocolPP::jarray<uint8_t> endpadgcm6("fc7cac574c49feae6150315b9685424c");
        ProtocolPP::jarray<uint8_t> ciphergcm6("dd7e01b2b424a2ef82502707e87a32c152b0d01818fd7f12243eb5a15659e91b4c");
        ProtocolPP::jarray<uint8_t> authgcm6("907ea6a5b73a51de747c3e9ad9ee029b");
        ProtocolPP::jarray<uint8_t> expectgcm6(plaingcm6.get_size(), 0);
        ProtocolPP::jarray<uint8_t> icvgcm6(16, 0);
        
        // test direct interface
        ProtocolPP::jsnowv engine6(ProtocolPP::jsnowv::dir_t::SNOWV_ENC,
                                   ProtocolPP::jsnowv::mode_t::SNOWV_GCM,
                                   keygcm6.get_ptr(),
                                   keygcm6.get_size(),
                                   ivgcm6.get_ptr(),
                                   ivgcm6.get_size());
        
        engine6.ProcessData(plaingcm6.get_ptr(),
                            expectgcm6.get_ptr(),
                            plaingcm6.get_size(),
                            aadgcm6.get_ptr(),
                            aadgcm6.get_size());
        
        engine6.result(icvgcm6.get_ptr(), 16);
        
        CPPUNIT_ASSERT_EQUAL(expectgcm6.to_string(), ciphergcm6.to_string());
        CPPUNIT_ASSERT_EQUAL(authgcm6.to_string(), icvgcm6.to_string());

        // test ciphers interface
        expectgcm6 = ProtocolPP::jarray<uint8_t>(plaingcm6.get_size(), 0);
        icvgcm6 = ProtocolPP::jarray<uint8_t>(16, 0);

        enginec = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::SNOWV_GCM,
                                                  ProtocolPP::jmodes::ENC,
                                                  ProtocolPP::jmodes::AEAD,
                                                  keygcm6.get_ptr(),
                                                  keygcm6.get_size(),
                                                  ivgcm6.get_ptr(),
                                                  ivgcm6.get_size());

        enginec->ProcessData(plaingcm6.get_ptr(),
                             expectgcm6.get_ptr(),
                             plaingcm6.get_size(),
                             aadgcm6.get_ptr(),
                             aadgcm6.get_size());

        enginec->result(icvgcm6.get_ptr(),
                        icvgcm6.get_size());

        CPPUNIT_ASSERT_EQUAL(expectgcm6.to_string(), ciphergcm6.to_string());
        CPPUNIT_ASSERT_EQUAL(authgcm6.to_string(), icvgcm6.to_string());
    }
    
    void testcmac() {
    
        ///////////////////////////////////////////////////////////////////////
        /// From RFC4494 Section 5 Test Vector #1
        ///////////////////////////////////////////////////////////////////////

        //Test Case #1
        // Key (K)       :
        ProtocolPP::jarray<uint8_t> key("2b7e151628aed2a6abf7158809cf4f3c");
        
        //Message (M)    : <empty string>
        ProtocolPP::jarray<uint8_t> message(0);
        ProtocolPP::jarray<uint8_t> ricv("bb1d6929e95937287fa37d129b756746");
        ProtocolPP::jarray<uint8_t> icv(16);
    
        std::shared_ptr<ProtocolPP::jmodes> engine;

        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::CMAC,
                                                 key.get_ptr(),
                                                 key.get_size());

        engine->ProcessData(message.get_ptr(),
                            icv.get_ptr(),
                            message.get_size());

        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (ricv != icv) {
            std::cerr << "In testcmac() test vector #1 icv mismatch" << std::endl;
            std::cerr << icv.debug(ricv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From RFC4494 Section 5 Test Vector #2
        ///////////////////////////////////////////////////////////////////////

        //Message (M)    : <empty string>
        message = ProtocolPP::jarray<uint8_t>("6bc1bee22e409f96e93d7e117393172a");
        ricv=ProtocolPP::jarray<uint8_t>("070a16b46b4d4144f79bdd9dd04a287c");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine->ProcessData(message.get_ptr(),
                            icv.get_ptr(),
                            message.get_size());

        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (ricv != icv) {
            std::cerr << "In testcmac() test vector #2 icv mismatch" << std::endl;
            std::cerr << icv.debug(ricv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From RFC4494 Section 5 Test Vector #3
        ///////////////////////////////////////////////////////////////////////

        //Message (M)    : <empty string>
        message = ProtocolPP::jarray<uint8_t>("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411");
        ricv=ProtocolPP::jarray<uint8_t>("dfa66747de9ae63030ca32611497c827");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine->ProcessData(message.get_ptr(),
                            icv.get_ptr(),
                            message.get_size());

        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (ricv != icv) {
            std::cerr << "In testcmac() test vector #3 icv mismatch" << std::endl;
            std::cerr << icv.debug(ricv);
        }
    
        ///////////////////////////////////////////////////////////////////////
        /// From RFC4494 Section 5 Test Vector #4
        ///////////////////////////////////////////////////////////////////////

        //Message (M)    : <empty string>
        message = ProtocolPP::jarray<uint8_t>("6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411e5fbc1191a0a52eff69f2445df4f9b17ad2b417be66c3710");
        ricv=ProtocolPP::jarray<uint8_t>("51f0bebf7e3b9d92fc49741779363cfe");
        icv=ProtocolPP::jarray<uint8_t>(16);
    
        engine->ProcessData(message.get_ptr(),
                            icv.get_ptr(),
                            message.get_size());

        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (ricv != icv) {
            std::cerr << "In testcmac() test vector #4 icv mismatch" << std::endl;
            std::cerr << icv.debug(ricv);
        }
    }

    void testxcbcmac() {
        ///////////////////////////////////////////////////////////////////////
        /// From RFC3566 Section 4.6 Test Vector #1   : AES-XCBC-MAC-96 with 0-byte input
        ///////////////////////////////////////////////////////////////////////

        // Key (K)       :
        ProtocolPP::jarray<uint8_t> key("000102030405060708090a0b0c0d0e0f");
        
        //Message (M)    : <empty string>
        ProtocolPP::jarray<uint8_t> message1(0);
    
        //AES-XCBC-MAC   :
        //AES-XCBC-MAC-96: 75f0251d528ac01c4573dfd5
        ProtocolPP::jarray<uint8_t> mac1("75f0251d528ac01c4573dfd584d79f29");
        ProtocolPP::jarray<uint8_t> icv1(16);
    
        std::shared_ptr<ProtocolPP::jmodes> engine;
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::XCBC_MAC,
                                                 key.get_ptr(),
                                                 key.get_size());

        engine->ProcessData(message1.get_ptr(),
                            icv1.get_ptr(),
                            message1.get_size());
    
        engine->result(icv1.get_ptr(),
                       icv1.get_size());

        if (mac1 != icv1) {
            std::cerr << "In testxcbcmac() test vector #1 icv mismatch : " << std::endl;
            std::cerr << icv1.debug(mac1);
        }
    
        ///////////////////////////////////////////////////////////////////////
        // From RFC3566 Section 4.6 Test Vector #2   : AES-XCBC-MAC-96 with 3-byte input
        ///////////////////////////////////////////////////////////////////////

        // Key (K)        :
        // Message (M)    :
        ProtocolPP::jarray<uint8_t> message2("000102");
        
        // AES-XCBC-MAC   :
        // AES-XCBC-MAC-96: 5b376580ae2f19afe7219cee
        ProtocolPP::jarray<uint8_t> mac2("5b376580ae2f19afe7219ceef172756f");
        ProtocolPP::jarray<uint8_t> icv2(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::XCBC_MAC,
                                                 key.get_ptr(),
                                                 key.get_size());

        engine->ProcessData(message2.get_ptr(),
                            icv2.get_ptr(),
                            message2.get_size());
    
        engine->result(icv2.get_ptr(),
                       icv2.get_size());

        if (mac2 != icv2) {
            std::cerr << "In testxcbcmac() test vector #2 icv mismatch : " << std::endl;
            std::cerr << icv2.debug(mac2);
        }
    
        ///////////////////////////////////////////////////////////////////////
        // From RFC3566 Section 4.6 Test Vector #3   : AES-XCBC-MAC-96 with 16-byte input
        ///////////////////////////////////////////////////////////////////////

        // Key (K)        :
        // Message (M)    :
        ProtocolPP::jarray<uint8_t> message3("000102030405060708090a0b0c0d0e0f");
        
        // AES-XCBC-MAC   :
        // AES-XCBC-MAC-96: d2a246fa349b68a79998a439
        ProtocolPP::jarray<uint8_t> mac3("d2a246fa349b68a79998a4394ff7a263");
        ProtocolPP::jarray<uint8_t> icv3(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::XCBC_MAC,
                                                 key.get_ptr(),
                                                 key.get_size());

        engine->ProcessData(message3.get_ptr(),
                            icv3.get_ptr(),
                            message3.get_size());
    
        engine->result(icv3.get_ptr(),
                       icv3.get_size());

        if (mac3 != icv3) {
            std::cerr << "In testxcbcmac() test vector #3 icv mismatch : " << std::endl;
            std::cerr << icv3.debug(mac3);
        }
    
        ///////////////////////////////////////////////////////////////////////
        // From RFC3566 Section 4.6 Test Vector #4   : AES-XCBC-MAC-96 with 20-byte input
        ///////////////////////////////////////////////////////////////////////

        // Key (K)        :
        // Message (M)    :
        ProtocolPP::jarray<uint8_t> message4("000102030405060708090a0b0c0d0e0f10111213");
        
        // AES-XCBC-MAC   :
        // AES-XCBC-MAC-96: 47f51b4564966215b8985c63
        ProtocolPP::jarray<uint8_t> mac4("47f51b4564966215b8985c63055ed308");
        ProtocolPP::jarray<uint8_t> icv4(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::XCBC_MAC,
                                                 key.get_ptr(),
                                                 key.get_size());

        engine->ProcessData(message4.get_ptr(),
                            icv4.get_ptr(),
                            message4.get_size());
    
        engine->result(icv4.get_ptr(),
                       icv4.get_size());

        if (mac4 != icv4) {
            std::cerr << "In testxcbcmac() test vector #4 icv mismatch : " << std::endl;
            std::cerr << icv4.debug(mac4);
        }
    
        ///////////////////////////////////////////////////////////////////////
        // From RFC3566 Section 4.6 Test Vector #5   : AES-XCBC-MAC-96 with 32-byte input
        ///////////////////////////////////////////////////////////////////////

        // Key (K)        :
        // Message (M)    :
        ProtocolPP::jarray<uint8_t> message5("000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f");
        
        // AES-XCBC-MAC   :
        // AES-XCBC-MAC-96: f54f0ec8d2b9f3d36807734b
        ProtocolPP::jarray<uint8_t> mac5("f54f0ec8d2b9f3d36807734bd5283fd4");
        ProtocolPP::jarray<uint8_t> icv5(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::XCBC_MAC,
                                                 key.get_ptr(),
                                                 key.get_size());

        engine->ProcessData(message5.get_ptr(),
                            icv5.get_ptr(),
                            message5.get_size());
    
        engine->result(icv5.get_ptr(),
                       icv5.get_size());

        if (mac5 != icv5) {
            std::cerr << "In testxcbcmac() test vector #5 icv mismatch : " << std::endl;
            std::cerr << icv5.debug(mac5);
        }
    
        ///////////////////////////////////////////////////////////////////////
        // From RFC3566 Section 4.6 Test Vector #6   : AES-XCBC-MAC-96 with 34-byte input
        ///////////////////////////////////////////////////////////////////////

        // Key (K)        : 000102030405060708090a0b0c0d0e0f
        // Message (M)    :
        ProtocolPP::jarray<uint8_t> message6("000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f2021");
        
        // AES-XCBC-MAC   :
        // AES-XCBC-MAC-96: becbb3bccdb518a30677d548
        ProtocolPP::jarray<uint8_t> mac6("becbb3bccdb518a30677d5481fb6b4d8");
        ProtocolPP::jarray<uint8_t> icv6(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::XCBC_MAC,
                                                 key.get_ptr(),
                                                 key.get_size());

        engine->ProcessData(message6.get_ptr(),
                            icv6.get_ptr(),
                            message6.get_size());
    
        engine->result(icv6.get_ptr(),
                       icv6.get_size());

        if (mac6 != icv6) {
            std::cerr << "In testxcbcmac() test vector #6 icv mismatch : " << std::endl;
            std::cerr << icv6.debug(mac6);
        }
    
        ///////////////////////////////////////////////////////////////////////
        // From RFC3566 Section 4.6 Test Vector #7   : AES-XCBC-MAC-96 with 1000-byte input
        ///////////////////////////////////////////////////////////////////////

        // Key (K)        : 000102030405060708090a0b0c0d0e0f
        // Message (M)    :
        ProtocolPP::jarray<uint8_t> message7(1000, 0x00);
    
        // AES-XCBC-MAC   :
        // AES-XCBC-MAC-96: f0dafee895db30253761103b
        ProtocolPP::jarray<uint8_t> mac7("f0dafee895db30253761103b5d84528f");
        ProtocolPP::jarray<uint8_t> icv7(16);
    
        engine = ProtocolPP::ciphers::get_cipher(ProtocolPP::jmodes::AES,
                                                 ProtocolPP::jmodes::ENC,
                                                 ProtocolPP::jmodes::XCBC_MAC,
                                                 key.get_ptr(),
                                                 key.get_size());

        engine->ProcessData(message7.get_ptr(),
                            icv7.get_ptr(),
                            message7.get_size());
    
        engine->result(icv7.get_ptr(),
                       icv7.get_size());

        if (mac7 != icv7) {
            std::cerr << "In testxcbcmac() test vector #7 icv mismatch : " << std::endl;
            std::cerr << icv7.debug(mac7);
        }
    }

    void testchacha() {
        for(int j=0; j<2; j++) {
            ProtocolPP::jarray<uint8_t> tmpkey = myrand->getbyte(16);
            ProtocolPP::jarray<uint8_t> nonce = myrand->getbyte(12);
            ProtocolPP::jarray<uint8_t> input = myrand->getbyte(125);
            ProtocolPP::jarray<uint8_t> output(input.get_size(), 0);
            uint64_t counter = myrand->get_u64();

            ProtocolPP::jarray<uint8_t> roundkeys(64);
            ProtocolPP::jarray<uint8_t> roundkeys2(32);
            ProtocolPP::chacha20 tmp(tmpkey.get_ptr(), nonce.get_ptr(), counter);
            tmp.ProcessData(input.get_ptr(), output.get_ptr(), input.get_size());
            tmp.context(roundkeys.get_ptr(), roundkeys.get_size());
            ProtocolPP::chacha20 tmp2(roundkeys.get_ptr(), roundkeys.get_size());
            tmp2.ProcessData(input.get_ptr(), output.get_ptr(), input.get_size());
            tmp2.context(roundkeys2.get_ptr(), roundkeys2.get_size());
        }
    }

    void testpoly1305() {
        for(int j=0; j<2; j++) {
            ProtocolPP::jarray<uint8_t> tmpkey = myrand->getbyte(32);
            ProtocolPP::jarray<uint8_t> icv(16);
            ProtocolPP::jarray<uint8_t> input = myrand->getbyte(125);
            ProtocolPP::jarray<uint8_t> roundkeys(144);
            ProtocolPP::jpoly1305 tmp(tmpkey.get_ptr(), tmpkey.get_size());
            tmp.context(roundkeys.get_ptr(), roundkeys.get_size());
            ProtocolPP::jpoly1305 tmp2(roundkeys.get_ptr());
            tmp2.ProcessData(input.get_ptr(), input.get_size());
            tmp2.result(icv.get_ptr(), icv.get_size());
        }
    }

    void testsm3() {
        ///////////////////////////////////////////////////////////////////////
        // From draft-shen-sm3-hash-01 Appendix A Test Vector #1
        ///////////////////////////////////////////////////////////////////////

        // Message (M)    :
        std::shared_ptr<ProtocolPP::jmodes> engine;
        ProtocolPP::jarray<uint8_t> input("abc", ProtocolPP::BIG, true);
        ProtocolPP::jarray<uint8_t> mac("66c7f0f462eeedd9d1f2d46bdc10e4e24167c4875cf2f7a2297da02b8f4ba8e0");
        ProtocolPP::jarray<uint8_t> icv(32,0);

        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SM3);

        engine->ProcessData(input.get_ptr(),
                            input.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (mac != icv) {
            std::cerr << "In testsm3() test vector #1 icv mismatch : " << std::endl;
            std::cerr << icv.debug(mac);
        }

        ///////////////////////////////////////////////////////////////////////
        // From draft-shen-sm3-hash-01 Appendix A Test Vector #2
        ///////////////////////////////////////////////////////////////////////

        // Message (M)    :
        input=ProtocolPP::jarray<uint8_t>("61626364616263646162636461626364616263646162636461626364616263646162636461626364616263646162636461626364616263646162636461626364");
        mac=ProtocolPP::jarray<uint8_t>("debe9ff92275b8a138604889c18e5a4d6fdb70e5387e5765293dcba39c0c5732");
        icv=ProtocolPP::jarray<uint8_t>(32,0);

        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SM3);

        engine->ProcessData(input.get_ptr(),
                            input.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        if (mac != icv) {
            std::cerr << "In testsm3() test vector #2 icv mismatch : " << std::endl;
            std::cerr << icv.debug(mac);
        }
    }

    void testlms() {

        ///////////////////////////////////////////////////////////////////////
        // From RFC8554 Appendix F Test Vector #1
        ///////////////////////////////////////////////////////////////////////
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> msg1 = std::make_shared<ProtocolPP::jarray<uint8_t>>("54686520706f77657273206e6f742064656c65676174656420746f2074686520556e69746564205374617465732062792074686520436f6e737469747574696f6e2c206e6f722070726f6869626974656420627920697420746f20746865205374617465732c2061726520726573657276656420746f207468652053746174657320726573706563746976656c792c206f7220746f207468652070656f706c652e0a");

        ProtocolPP::jarray<uint8_t> ident1("61a5d57d37f5e46bfb7520806b07a1b8");
        ProtocolPP::jarray<uint8_t> inK1("50650e3b31fe4a773ea29a07f09cf2ea30e579f0df58ef8e298da0434cb2b878");
        ProtocolPP::jarray<uint8_t> carray1("d32b56671d7eb98833c49b433c272586bc4a1c8a8970528ffa04b966f9426eb9");
        ProtocolPP::jarray<uint8_t> otssig1("00000004d32b56671d7eb98833c49b433c272586bc4a1c8a8970528ffa04b966f9426eb9965a25bfd37f196b9073f3d4a232feb69128ec45146f86292f9dff9610a7bf95a64c7f60f6261a62043f86c70324b7707f5b4a8a6e19c114c7be866d488778a0e05fd5c6509a6e61d559cf1a77a970de927d60c70d3de31a7fa0100994e162a2582e8ff1b10cd99d4e8e413ef469559f7d7ed12c838342f9b9c96b83a4943d1681d84b15357ff48ca579f19f5e71f18466f2bbef4bf660c2518eb20de2f66e3b14784269d7d876f5d35d3fbfc7039a462c716bb9f6891a7f41ad133e9e1f6d9560b960e7777c52f060492f2d7c660e1471e07e72655562035abc9a701b473ecbc3943c6b9c4f2405a3cb8bf8a691ca51d3f6ad2f428bab6f3a30f55dd9625563f0a75ee390e385e3ae0b906961ecf41ae073a0590c2eb6204f44831c26dd768c35b167b28ce8dc988a3748255230cef99ebf14e730632f27414489808afab1d1e783ed04516de012498682212b07810579b250365941bcc98142da13609e9768aaf65de7620dabec29eb82a17fde35af15ad238c73f81bdb8dec2fc0e7f932701099762b37f43c4a3c20010a3d72e2f606be108d310e639f09ce7286800d9ef8a1a40281cc5a7ea98d2adc7c7400c2fe5a101552df4e3cccfd0cbf2ddf5dc6779cbbc68fee0c3efe4ec22b83a2caa3e48e0809a0a750b73ccdcf3c79e6580c154f8a58f7f24335eec5c5eb5e0cf01dcf4439424095fceb077f66ded5bec73b27c5b9f64a2a9af2f07c05e99e5cf80f00252e39db32f6c19674f190c9fbc506d826857713afd2ca6bb85cd8c107347552f30575a5417816ab4db3f603f2df56fbc413e7d0acd8bdd81352b2471fc1bc4f1ef296fea1220403466b1afe78b94f7ecf7cc62fb92be14f18c2192384ebceaf8801afdf947f698ce9c6ceb696ed70e9e87b0144417e8d7baf25eb5f70f09f016fc925b4db048ab8d8cb2a661ce3b57ada67571f5dd546fc22cb1f97e0ebd1a65926b1234fd04f171cf469c76b884cf3115cce6f792cc84e36da58960c5f1d760f32c12faef477e94c92eb75625b6a371efc72d60ca5e908b3a7dd69fef0249150e3eebdfed39cbdc3ce9704882a2072c75e13527b7a581a556168783dc1e97545e31865ddc46b3c957835da252bb7328d3ee2062445dfb85ef8c35f8e1f3371af34023cef626e0af1e0bc017351aae2ab8f5c612ead0b729a1d059d02bfe18efa971b7300e882360a93b025ff97e9e0eec0f3f3f13039a17f88b0cf808f488431606cb13f9241f40f44e537d302c64a4f1f4ab949b9feefadcb71ab50ef27d6d6ca8510f150c85fb525bf25703df7209b6066f09c37280d59128d2f0f637c7d7d7fad4ed1c1ea04e628d221e3d8db77b7c878c9411cafc5071a34a00f4cf07738912753dfce48f07576f0d4f94f42c6d76f7ce973e9367095ba7e9a3649b7f461d9f9ac1332a4d1044c96aefee67676401b64457c54d65fef6500c59cdfb69af7b6dddfcb0f086278dd8ad0686078dfb0f3f79cd893d314168648499898fbc0ced5f95b74e8ff14d735cdea968bee7400000005d8b8112f9200a5e50c4a262165bd342cd800b8496810bc716277435ac376728d129ac6eda839a6f357b5a04387c5ce97382a78f2a4372917eefcbf93f63bb59112f5dbe400bd49e4501e859f885bf0736e90a509b30a26bfac8c17b5991c157eb5971115aa39efd8d564a6b90282c3168af2d30ef89d51bf14654510a12b8a144cca1848cf7da59cc2b3d9d0692dd2a20ba3863480e25b1b85ee860c62bf5136");

        // LMOTS engine
        ProtocolPP::jlmots lmots(myrand,
                                 0x00000005,
                                 false,
                                 ProtocolPP::PLMOTS_SHA256_N32_W8);

        // initial values for (normally) random values
        lmots.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::LMOTSI, ident1);
        lmots.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::LMOTSC, carray1);

        // generate private key
        ProtocolPP::jarray<uint8_t> lmotsk  = lmots.gensk();

        // generate public key
        ProtocolPP::jarray<uint8_t> lmotpk  = lmots.genpk(lmotsk);

        // sign the message
        ProtocolPP::jarray<uint8_t> lmotsig = lmots.sign(*msg1, lmotsk);

        // verify the signature
        ProtocolPP::jarray<uint8_t> tmppk = lmots.verify(*msg1, lmotsig, lmotpk);

        // extract the y[i] from the public key
        ProtocolPP::jarray<uint8_t> pktmp = lmotpk.extract(24,lmotpk.get_size()-24);

        // temp public key should match the public key
        if (tmppk != pktmp) {
            std::cerr << "In testlms() vector 1, OTS signature does not match" << std::endl
                      << pktmp.debug(tmppk) << std::endl;

            CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE( "testlms() vector1 OTS signature 1 fail", CPPUNIT_ASSERT( 1 == 2 ) );
        }

        ///////////////////////////////////////////////////////////////////////
        // From RFC8554 Appendix F Test Vector #2
        ///////////////////////////////////////////////////////////////////////
        // LMS tree level 1
        ProtocolPP::jarray<uint8_t> seed1("558b8966c48ae9cb898b423c83443aae014a72f1b1ab5cc85cf1d892903b5439");
        ProtocolPP::jarray<uint8_t> I1("d08fabd4a2091ff0a8cb4ed834e74534");

        // LMS tree level 2
        ProtocolPP::jarray<uint8_t> seed2("a1c4696e2608035a886100d05cd99945eb3370731884a8235e2fb3d4d71f2547");
        ProtocolPP::jarray<uint8_t> I2("215f83b7ccb9acbcd08db97b0d04dc2b");

        // HSS public key levels
        ProtocolPP::jarray<uint8_t> hsslevel("00000002");

        // LMS key 1
        ProtocolPP::jarray<uint8_t> lmstype("00000006");
        ProtocolPP::jarray<uint8_t> lmotstype("00000003");
        ProtocolPP::jarray<uint8_t> hssi("d08fabd4a2091ff0a8cb4ed834e74534");
        ProtocolPP::jarray<uint8_t> hssk("32a58885cd9ba0431235466bff9651c6c92124404d45fa53cf161c28f1ad5a8e");

        // LMS key 2
        ProtocolPP::jarray<uint8_t> lmstype2("00000005");
        ProtocolPP::jarray<uint8_t> lmotstype2("00000004");
        ProtocolPP::jarray<uint8_t> hssi2("215f83b7ccb9acbcd08db97b0d04dc2b");
        ProtocolPP::jarray<uint8_t> hssk2("a1cd035833e0e90059603f26e07ad2aad152338e7a5e5984bcd5f7bb4eba40b7");

        // message 2
        ProtocolPP::jarray<uint8_t> msg2("54686520656e756d65726174696f6e20696e2074686520436f6e737469747574696f6e2c206f66206365727461696e207269676874732c207368616c6c206e6f7420626520636f6e73747275656420746f2064656e79206f7220646973706172616765206f7468657273207265746169 6e6564206279207468652070656f706c652e0a");

        // OTS signature 2
        ProtocolPP::jarray<uint8_t> sigots2("000000033d46bee8660f8f215d3f96408a7a64cf1c4da02b63a55f62c666ef5707a914ce0674e8cb7a55f0c48d484f31f3aa4af9719a74f22cf823b94431d01c926e2a76bb71226d279700ec81c9e95fb11a0d10d065279a5796e265ae17737c44eb8c594508e126a9a7870bf4360820bdeb9a01d9693779e416828e75bddd7d8c70d50a0ac8ba39810909d445f44cb5bb58de737e60cb4345302786ef2c6b14af212ca19edeaa3bfcfe8baa6621ce88480df2371dd37add732c9de4ea2ce0dffa53c92649a18d39a50788f4652987f226a1d48168205df6ae7c58e049a25d4907edc1aa90da8aa5e5f7671773e941d8055360215c6b60dd35463cf2240a9c06d694e9cb54e7b1e1bf494d0d1a28c0d31acc75161f4f485dfd3cb9578e836ec2dc722f37ed30872e07f2b8bd0374eb57d22c614e09150f6c0d8774a39a6e168211035dc52988ab46eaca9ec597fb18b4936e66ef2f0df26e8d1e34da28cbb3af752313720c7b345434f72d65314328bbb030d0f0f6d5e47b28ea91008fb11b05017705a8be3b2adb83c60a54f9d1d1b2f476f9e393eb5695203d2ba6ad815e6a111ea293dcc21033f9453d49c8e5a6387f588b1ea4f706217c151e05f55a6eb7997be09d56a326a32f9cba1fbe1c07bb49fa04cecf9df1a1b815483c75d7a27cc88ad1b1238e5ea986b53e087045723ce16187eda22e33b2c70709e53251025abde8939645fc8c0693e97763928f00b2e3c75af3942d8ddaee81b59a6f1f67efda0ef81d11873b59137f67800b35e81b01563d187c4a1575a1acb92d087b517a8833383f05d357ef4678de0c57ff9f1b2da61dfde5d88318bcdde4d9061cc75c2de3cd4740dd7739ca3ef66f1930026f47d9ebaa713b07176f76f953e1c2e7f8f271a6ca375dbfb83d719b1635a7d8a13891957944b1c29bb101913e166e11bd5f34186fa6c0a555c9026b256a6860f4866bd6d0b5bf90627086c6149133f8282ce6c9b3622442443d5eca959d6c14ca8389d12c4068b503e4e3c39b635bea245d9d05a2558f249c9661c0427d2e489ca5b5dde220a90333f4862aec793223c781997da98266c12c50ea28b2c438e7a379eb106eca0c7fd6006e9bf612f3ea0a454ba3bdb76e8027992e60de01e9094fddeb3349883914fb17a9621ab929d970d101e45f8278c14b032bcab02bd15692d21b6c5c204abbf077d465553bd6eda645e6c3065d33b10d518a61e15ed0f092c32226281a29c8a0f50cde0a8c66236e29c2f310a375cebda1dc6bb9a1a01dae6c7aba8ebedc6371a7d52aacb955f83bd6e4f84d2949dcc198fb77c7e5cdf6040b0f84faf82808bf985577f0a2acf2ec7ed7c0b0ae8a270e951743ff23e0b2dd12e9c3c828fb5598a22461af94d568f29240ba2820c4591f71c088f96e095dd98beae456579ebbba36f6d9ca2613d1c26eee4d8c73217ac5962b5f3147b492e8831597fd89b64aa7fde82e1974d2f6779504dc21435eb3109350756b9fdabe1c6f368081bd40b27ebcb9819a75d7df8bb07bb05db1bab705a4b7e37125186339464ad8faaa4f052cc1272919fde3e025bb64aa8e0eb1fcbfcc25acb5f718ce4f7c2182fb393a1814b0e942490e52d3bca817b2b26e90d4c9b0cc38608a6cef5eb153af0858acc867c9922aed43bb67d7b33acc519313d28d41a5c6fe6cf3595dd5ee63f0a4c4065a083590b275788bee7ad875a7f88dd73720708c6c6c0ecf1f43bbaadae6f208557fdc07bd4ed91f88ce4c0de842761c70c186bfdafafc444834bd3418be4253a71eaf41d718753ad07754ca3effd5960b0336981795721426803599ed5b2b7516920efcbe32ada4bcf6c73bd29e3fa152d9adeca36020fdeeee1b739521d3ea8c0da497003df1513897b0f54794a873670b8d93bcca2ae47e64424b7423e1f078d9554bb5232cc6de8aae9b83fa5b9510beb39ccf4b4e1d9c0f19d5e17f58e5b8705d9a6837a7d9bf99cd13387af256a8491671f1f2f22af253bcff54b673199bdb7d05d81064ef05f80f0153d0be7919684b23da8d42ff3effdb7ca0985033f389181f47659138003d712b5ec0a614d31cc7487f52de8664916af79c98456b2c94a8038083db55391e3475862250274a1de2584fec975fb09536792cfbfcf6192856cc76eb5b13dc4709e2f7301ddff26ec1b23de2d188c999166c74e1e14bbc15f457cf4e471ae13dcbdd9c50f4d646fc6278e8fe7eb6cb5c94100fa870187380b777ed19d7868fd8ca7ceb7fa7d5cc861c5bdac98e7495eb0a2ceec1924ae979f44c5390ebedddc65d6ec11287d978b8df064219bc5679f7d7b264a76ff272b2ac9f2f7cfc9fdcfb6a51428240027afd9d52a79b647c90c2709e060ed70f87299dd798d68f4fadd3da6c51d839f851f98f67840b964ebe73f8cec41572538ec6bc131034ca2894eb736b3bda93d9f5f6fa6f6c0f03ce43362b8414940355fb54d3dfdd03633ae108f3de3ebc85a3ff51efeea3bc2cf27e1658f1789ee612c83d0f5fd56f7cd071930e2946beeecaa04dccea9f97786001475e0294bc2852f62eb5d39bb9fbeef75916efe44a662ecae37ede27e9d6eadfdeb8f8b2b2dbccbf96fa6dbaf7321fb0e701f4d429c2f4dcd153a2742574126e5eaccc77686acf6e3ee48f423766e0fc466810a905ff5453ec99897b56bc55dd49b991142f65043f2d744eeb935ba7f4ef23cf80cc5a8a335d3619d781e7454826df720eec82e06034c44699b5f0c44a8787752e057fa3419b5bb0e25d30981e41cb1361322dba8f69931cf42fad3f3bce6ded5b8bfc3d20a2148861b2afc14562ddd27f12897abf0685288dcc5c4982f826026846a24bf77e383c7aacab1ab692b29ed8c018a65f3dc2b87ff619a633c41b4fadb1c78725c1f8f922f6009787b1964247df0136b1bc614ab575c59a16d089917bd4a8b6f04d95c581279a139be09fcf6e98a470a0bceca191fce476f9370021cbc05518a7efd35d89d8577c990a5e19961ba16203c959c91829ba7497cffcbb4b294546454fa5388a23a22e805a5ca35f956598848bda678615fec28afd5da61a");

        // LMS signature 2
        ProtocolPP::jarray<uint8_t> siglms2("00000003000000033d46bee8660f8f215d3f96408a7a64cf1c4da02b63a55f62c666ef5707a914ce0674e8cb7a55f0c48d484f31f3aa4af9719a74f22cf823b94431d01c926e2a76bb71226d279700ec81c9e95fb11a0d10d065279a5796e265ae17737c44eb8c594508e126a9a7870bf4360820bdeb9a01d9693779e416828e75bddd7d8c70d50a0ac8ba39810909d445f44cb5bb58de737e60cb4345302786ef2c6b14af212ca19edeaa3bfcfe8baa6621ce88480df2371dd37add732c9de4ea2ce0dffa53c92649a18d39a50788f4652987f226a1d48168205df6ae7c58e049a25d4907edc1aa90da8aa5e5f7671773e941d8055360215c6b60dd35463cf2240a9c06d694e9cb54e7b1e1bf494d0d1a28c0d31acc75161f4f485dfd3cb9578e836ec2dc722f37ed30872e07f2b8bd0374eb57d22c614e09150f6c0d8774a39a6e168211035dc52988ab46eaca9ec597fb18b4936e66ef2f0df26e8d1e34da28cbb3af752313720c7b345434f72d65314328bbb030d0f0f6d5e47b28ea91008fb11b05017705a8be3b2adb83c60a54f9d1d1b2f476f9e393eb5695203d2ba6ad815e6a111ea293dcc21033f9453d49c8e5a6387f588b1ea4f706217c151e05f55a6eb7997be09d56a326a32f9cba1fbe1c07bb49fa04cecf9df1a1b815483c75d7a27cc88ad1b1238e5ea986b53e087045723ce16187eda22e33b2c70709e53251025abde8939645fc8c0693e97763928f00b2e3c75af3942d8ddaee81b59a6f1f67efda0ef81d11873b59137f67800b35e81b01563d187c4a1575a1acb92d087b517a8833383f05d357ef4678de0c57ff9f1b2da61dfde5d88318bcdde4d9061cc75c2de3cd4740dd7739ca3ef66f1930026f47d9ebaa713b07176f76f953e1c2e7f8f271a6ca375dbfb83d719b1635a7d8a13891957944b1c29bb101913e166e11bd5f34186fa6c0a555c9026b256a6860f4866bd6d0b5bf90627086c6149133f8282ce6c9b3622442443d5eca959d6c14ca8389d12c4068b503e4e3c39b635bea245d9d05a2558f249c9661c0427d2e489ca5b5dde220a90333f4862aec793223c781997da98266c12c50ea28b2c438e7a379eb106eca0c7fd6006e9bf612f3ea0a454ba3bdb76e8027992e60de01e9094fddeb3349883914fb17a9621ab929d970d101e45f8278c14b032bcab02bd15692d21b6c5c204abbf077d465553bd6eda645e6c3065d33b10d518a61e15ed0f092c32226281a29c8a0f50cde0a8c66236e29c2f310a375cebda1dc6bb9a1a01dae6c7aba8ebedc6371a7d52aacb955f83bd6e4f84d2949dcc198fb77c7e5cdf6040b0f84faf82808bf985577f0a2acf2ec7ed7c0b0ae8a270e951743ff23e0b2dd12e9c3c828fb5598a22461af94d568f29240ba2820c4591f71c088f96e095dd98beae456579ebbba36f6d9ca2613d1c26eee4d8c73217ac5962b5f3147b492e8831597fd89b64aa7fde82e1974d2f6779504dc21435eb3109350756b9fdabe1c6f368081bd40b27ebcb9819a75d7df8bb07bb05db1bab705a4b7e37125186339464ad8faaa4f052cc1272919fde3e025bb64aa8e0eb1fcbfcc25acb5f718ce4f7c2182fb393a1814b0e942490e52d3bca817b2b26e90d4c9b0cc38608a6cef5eb153af0858acc867c9922aed43bb67d7b33acc519313d28d41a5c6fe6cf3595dd5ee63f0a4c4065a083590b275788bee7ad875a7f88dd73720708c6c6c0ecf1f43bbaadae6f208557fdc07bd4ed91f88ce4c0de842761c70c186bfdafafc444834bd3418be4253a71eaf41d718753ad07754ca3effd5960b0336981795721426803599ed5b2b7516920efcbe32ada4bcf6c73bd29e3fa152d9adeca36020fdeeee1b739521d3ea8c0da497003df1513897b0f54794a873670b8d93bcca2ae47e64424b7423e1f078d9554bb5232cc6de8aae9b83fa5b9510beb39ccf4b4e1d9c0f19d5e17f58e5b8705d9a6837a7d9bf99cd13387af256a8491671f1f2f22af253bcff54b673199bdb7d05d81064ef05f80f0153d0be7919684b23da8d42ff3effdb7ca0985033f389181f47659138003d712b5ec0a614d31cc7487f52de8664916af79c98456b2c94a8038083db55391e3475862250274a1de2584fec975fb09536792cfbfcf6192856cc76eb5b13dc4709e2f7301ddff26ec1b23de2d188c999166c74e1e14bbc15f457cf4e471ae13dcbdd9c50f4d646fc6278e8fe7eb6cb5c94100fa870187380b777ed19d7868fd8ca7ceb7fa7d5cc861c5bdac98e7495eb0a2ceec1924ae979f44c5390ebedddc65d6ec11287d978b8df064219bc5679f7d7b264a76ff272b2ac9f2f7cfc9fdcfb6a51428240027afd9d52a79b647c90c2709e060ed70f87299dd798d68f4fadd3da6c51d839f851f98f67840b964ebe73f8cec41572538ec6bc131034ca2894eb736b3bda93d9f5f6fa6f6c0f03ce43362b8414940355fb54d3dfdd03633ae108f3de3ebc85a3ff51efeea3bc2cf27e1658f1789ee612c83d0f5fd56f7cd071930e2946beeecaa04dccea9f97786001475e0294bc2852f62eb5d39bb9fbeef75916efe44a662ecae37ede27e9d6eadfdeb8f8b2b2dbccbf96fa6dbaf7321fb0e701f4d429c2f4dcd153a2742574126e5eaccc77686acf6e3ee48f423766e0fc466810a905ff5453ec99897b56bc55dd49b991142f65043f2d744eeb935ba7f4ef23cf80cc5a8a335d3619d781e7454826df720eec82e06034c44699b5f0c44a8787752e057fa3419b5bb0e25d30981e41cb1361322dba8f69931cf42fad3f3bce6ded5b8bfc3d20a2148861b2afc14562ddd27f12897abf0685288dcc5c4982f826026846a24bf77e383c7aacab1ab692b29ed8c018a65f3dc2b87ff619a633c41b4fadb1c78725c1f8f922f6009787b1964247df0136b1bc614ab575c59a16d089917bd4a8b6f04d95c581279a139be09fcf6e98a470a0bceca191fce476f9370021cbc05518a7efd35d89d8577c990a5e19961ba16203c959c91829ba7497cffcbb4b294546454fa5388a23a22e805a5ca35f956598848bda678615fec28afd5da61a00000006b326493313053ced3876db9d237148181b7173bc7d042cefb4dbe94d2e58cd21a769db4657a103279ba8ef3a629ca84ee836172a9c50e51f45581741cf8083150b491cb4ecbbabec128e7c81a46e62a67b57640a0a78be1cbf7dd9d419a10cd8686d16621a80816bfdb5bdc56211d72ca70b81f1117d129529a7570cf79cf52a7028a48538ecdd3b38d3d5d62d26246595c4fb73a525a5ed2c30524ebb1d8cc82e0c19bc4977c6898ff95fd3d310b0bae71696cef93c6a552456bf96e9d075e383bb7543c675842bafbfc7cdb88483b3276c29d4f0a341c2d406e40d4653b7e4d045851acf6a0a0ea9c710b805cced4635ee8c107362f0fc8d80c14d0ac49c516703d26d14752f34c1c0d2c4247581c18c2cf4de48e9ce949be7c888e9caebe4a415e291fd107d21dc1f084b1158208249f28f4f7c7e931ba7b3bd0d824a4570");

        ProtocolPP::jarray<uint8_t> sigotsfinal2("000000040eb1ed54a2460d512388cad533138d240534e97b1e82d33bd927d201dfc24ebb11b3649023696f85150b189e50c00e98850ac343a77b3638319c347d7310269d3b7714fa406b8c35b021d54d4fdada7b9ce5d4ba5b06719e72aaf58c5aae7aca057aa0e2e74e7dcfd17a0823429db62965b7d563c57b4cec942cc865e29c1dad83cac8b4d61aacc457f336e6a10b66323f5887bf3523dfcadee158503bfaa89dc6bf59daa82afd2b5ebb2a9ca6572a6067cee7c327e9039b3b6ea6a1edc7fdc3df927aade10c1c9f2d5ff446450d2a3998d0f9f6202b5e07c3f97d2458c69d3c8190643978d7a7f4d64e97e3f1c4a08a7c5bc03fd55682c017e2907eab07e5bb2f190143475a6043d5e6d5263471f4eecf6e2575fbc6ff37edfa249d6cda1a09f797fd5a3cd53a066700f45863f04b6c8a58cfd341241e002d0d2c0217472bf18b636ae547c1771368d9f317835c9b0ef430b3df4034f6af00d0da44f4af7800bc7a5cf8a5abdb12dc718b559b74cab9090e33cc58a955300981c420c4da8ffd67df540890a062fe40dba8b2c1c548ced22473219c534911d48ccaabfb71bc71862f4a24ebd376d288fd4e6fb06ed8705787c5fedc813cd2697e5b1aac1ced45767b14ce88409eaebb601a93559aae893e143d1c395bc326da821d79a9ed41dcfbe549147f71c092f4f3ac522b5cc57290706650487bae9bb5671ecc9ccc2ce51ead87ac01985268521222fb9057df7ed41810b5ef0d4f7cc67368c90f573b1ac2ce956c365ed38e893ce7b2fae15d3685a3df2fa3d4cc098fa57dd60d2c9754a8ade980ad0f93f6787075c3f680a2ba1936a8c61d1af52ab7e21f416be09d2a8d64c3d3d8582968c2839902229f85aee297e717c094c8df4a23bb5db658dd377bf0f4ff3ffd8fba5e383a48574802ed545bbe7a6b4753533353d73706067640135a7ce517279cd683039747d218647c86e097b0daa2872d54b8f3e5085987629547b830d8118161b65079fe7bc59a99e9c3c7380e3e70b7138fe5d9be2551502b698d09ae193972f27d40f38dea264a0126e637d74ae4c92a6249fa103436d3eb0d4029ac712bfc7a5eacbdd7518d6d4fe903a5ae65527cd65bb0d4e9925ca24fd7214dc617c150544e423f450c99ce51ac8005d33acd74f1bed3b17b7266a4a3bb86da7eba80b101e15cb79de9a207852cf91249ef480619ff2af8cabca83125d1faa94cbb0a03a906f683b3f47a97c871fd513e510a7a25f283b196075778496152a91c2bf9da76ebe089f4654877f2d586ae7149c406e663eadeb2b5c7e82429b9e8cb4834c83464f079995332e4b3c8f5a72bb4b8c6f74b0d45dc6c1f79952c0b7420df525e37c15377b5f0984319c3993921e5ccd97e097592064530d33de3afad5733cbe7703c5296263f77342efbf5a04755b0b3c997c4328463e84caa2de3ffdcd297baaaacd7ae646e44b5c0f16044df38fabd296a47b3a838a913982fb2e370c078edb042c84db34ce36b46ccb76460a690cc86c302457dd1cde197ec8075e82b393d542075134e2a17ee70a5e187075d03ae3c853cff60729ba4");

        ProtocolPP::jarray<uint8_t> siglmsfinal2("00000004000000040eb1ed54a2460d512388cad533138d240534e97b1e82d33bd927d201dfc24ebb11b3649023696f85150b189e50c00e98850ac343a77b3638319c347d7310269d3b7714fa406b8c35b021d54d4fdada7b9ce5d4ba5b06719e72aaf58c5aae7aca057aa0e2e74e7dcfd17a0823429db62965b7d563c57b4cec942cc865e29c1dad83cac8b4d61aacc457f336e6a10b66323f5887bf3523dfcadee158503bfaa89dc6bf59daa82afd2b5ebb2a9ca6572a6067cee7c327e9039b3b6ea6a1edc7fdc3df927aade10c1c9f2d5ff446450d2a3998d0f9f6202b5e07c3f97d2458c69d3c8190643978d7a7f4d64e97e3f1c4a08a7c5bc03fd55682c017e2907eab07e5bb2f190143475a6043d5e6d5263471f4eecf6e2575fbc6ff37edfa249d6cda1a09f797fd5a3cd53a066700f45863f04b6c8a58cfd341241e002d0d2c0217472bf18b636ae547c1771368d9f317835c9b0ef430b3df4034f6af00d0da44f4af7800bc7a5cf8a5abdb12dc718b559b74cab9090e33cc58a955300981c420c4da8ffd67df540890a062fe40dba8b2c1c548ced22473219c534911d48ccaabfb71bc71862f4a24ebd376d288fd4e6fb06ed8705787c5fedc813cd2697e5b1aac1ced45767b14ce88409eaebb601a93559aae893e143d1c395bc326da821d79a9ed41dcfbe549147f71c092f4f3ac522b5cc57290706650487bae9bb5671ecc9ccc2ce51ead87ac01985268521222fb9057df7ed41810b5ef0d4f7cc67368c90f573b1ac2ce956c365ed38e893ce7b2fae15d3685a3df2fa3d4cc098fa57dd60d2c9754a8ade980ad0f93f6787075c3f680a2ba1936a8c61d1af52ab7e21f416be09d2a8d64c3d3d8582968c2839902229f85aee297e717c094c8df4a23bb5db658dd377bf0f4ff3ffd8fba5e383a48574802ed545bbe7a6b4753533353d73706067640135a7ce517279cd683039747d218647c86e097b0daa2872d54b8f3e5085987629547b830d8118161b65079fe7bc59a99e9c3c7380e3e70b7138fe5d9be2551502b698d09ae193972f27d40f38dea264a0126e637d74ae4c92a6249fa103436d3eb0d4029ac712bfc7a5eacbdd7518d6d4fe903a5ae65527cd65bb0d4e9925ca24fd7214dc617c150544e423f450c99ce51ac8005d33acd74f1bed3b17b7266a4a3bb86da7eba80b101e15cb79de9a207852cf91249ef480619ff2af8cabca83125d1faa94cbb0a03a906f683b3f47a97c871fd513e510a7a25f283b196075778496152a91c2bf9da76ebe089f4654877f2d586ae7149c406e663eadeb2b5c7e82429b9e8cb4834c83464f079995332e4b3c8f5a72bb4b8c6f74b0d45dc6c1f79952c0b7420df525e37c15377b5f0984319c3993921e5ccd97e097592064530d33de3afad5733cbe7703c5296263f77342efbf5a04755b0b3c997c4328463e84caa2de3ffdcd297baaaacd7ae646e44b5c0f16044df38fabd296a47b3a838a913982fb2e370c078edb042c84db34ce36b46ccb76460a690cc86c302457dd1cde197ec8075e82b393d542075134e2a17ee70a5e187075d03ae3c853cff60729ba4000000054de1f6965bdabc676c5a4dc7c35f97f82cb0e31c68d04f1dad96314ff09e6b3de96aeee300d1f68bf1bca9fc58e4032336cd819aaf578744e50d1357a0e4286704d341aa0a337b19fe4bc43c2e79964d4f351089f2e0e41c7c43ae0d49e7f404b0f75be80ea3af098c9752420a8ac0ea2bbb1f4eeba05238aef0d8ce63f0c6e5e4041d95398a6f7f3e0ee97cc1591849d4ed236338b147abde9f51ef9fd4e1c1");

        // LMOTS engine
        ProtocolPP::jlmots lmots2(myrand,
                                  0x00000003,
                                  true,
                                  ProtocolPP::PLMOTS_SHA256_N32_W4);

        // initial values for (normally) random values
        lmots2.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::LMOTSI, I1);
        lmots2.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::LMOTSEED, seed1);

        // generate private key
        ProtocolPP::jarray<uint8_t> lmotsk2  = lmots2.gensk();

        // generate public key
        ProtocolPP::jarray<uint8_t> lmotpk2  = lmots2.genpk(lmotsk2);

        // sign the message
        ProtocolPP::jarray<uint8_t> lmotsig2 = lmots2.sign(*msg1, lmotsk2);

        // verify the signature
        ProtocolPP::jarray<uint8_t> tmppk2 = lmots2.verify(*msg1, lmotsig2, lmotpk2);

        // extract the y[i] from the public key
        ProtocolPP::jarray<uint8_t> pktmp2 = lmotpk2.extract(24,lmotpk2.get_size()-24);

        // temp public key should match the public key
        if (tmppk2 != pktmp2) {
            std::cerr << "In testlms() vector 1, OTS signature does not match" << std::endl
                      << pktmp2.debug(tmppk2) << std::endl;

            CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE( "testlms() vector2 OTS signature 2 fail", CPPUNIT_ASSERT( 1 == 2 ) );
        }

        // create the security association
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> tmpsk3 = std::make_shared<ProtocolPP::jarray<uint8_t>>(lmotsk2);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> tmppk3 = std::make_shared<ProtocolPP::jarray<uint8_t>>(lmotpk2);

        std::shared_ptr<ProtocolPP::jlmsa> sec = std::make_shared<ProtocolPP::jlmsa>(ProtocolPP::GENKEYPAIR,
                                                                                     "LMS_SHA256_M32_H10",
                                                                                     "PLMOTS_SHA256_N32_W8",
                                                                                     1,
                                                                                     tmpsk3,
                                                                                     tmppk3);

        // create the engine with the security association
        std::shared_ptr<ProtocolPP::jlms> lmseng = ProtocolPP::jprotocolpp::get_lms(myrand,
                                                                                    sec);
    }

    void testshake() {
        // test SHAKE128
        std::shared_ptr<ProtocolPP::jmodes> engine;
        ProtocolPP::jarray<uint8_t> input;
        ProtocolPP::jarray<uint8_t> icv(16,0);
        ProtocolPP::jarray<uint8_t> expect128("7f9c2ba4e88f827d616045507605853e");

        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SHAKE128);

        engine->ProcessData(input.get_ptr(),
                            input.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        CPPUNIT_ASSERT_EQUAL(expect128.to_string(), icv.to_string());

        // test SHAKE256
        icv = ProtocolPP::jarray<uint8_t>(32,0);
        ProtocolPP::jarray<uint8_t> expect256("46b9dd2b0ba88d13233b3feb743eeb243fcd52ea62b81b82b50c27646ed5762f");

        engine = ProtocolPP::ciphers::get_auth(ProtocolPP::SHAKE256);

        engine->ProcessData(input.get_ptr(),
                            input.get_size());
    
        engine->result(icv.get_ptr(),
                       icv.get_size());

        CPPUNIT_ASSERT_EQUAL(expect256.to_string(), icv.to_string());
    }

    void testxmss() {
        // standard constructor
        ProtocolPP::jxmss xmss0(myrand);

        // XMSS engine
        ProtocolPP::jxmss xmss(myrand,
                               ProtocolPP::XMSS_SHA2_20_256,
                               ProtocolPP::XMSSMT_NO_TYPE);
        // generate key pair
        xmss.gen_keypair();

        // sign the message
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> msg = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(1000));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> xmssig = std::make_shared<ProtocolPP::jarray<uint8_t>>(xmss.get_field(ProtocolPP::SIGLEN), 0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> msgout = std::make_shared<ProtocolPP::jarray<uint8_t>>();

        // sign the message
        xmss.sign(msg, xmssig);

        // verify the message
        msg->append(*xmssig);
        xmss.verify(msg, msgout);

        // get the status of the sigature
        if (xmss.get_status() != 0) {
            std::cerr << "In testxmss() vector 1, signature did not verify" << std::endl;
            CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE( "testxmss() signature 1 fail", CPPUNIT_ASSERT( 1 == 2 ) );
        }

        std::shared_ptr<ProtocolPP::jxmssa> tmpsec;
        xmss.get_security(tmpsec);

        // security association constructor
        ProtocolPP::jxmss xmss2(myrand,
                                tmpsec);

        // get top level key
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mtkey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(xmss2.get_field(ProtocolPP::SIGLEN)));

        // generate key pair
        xmss2.gen_keypair();

        // sign the message
        msg = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(2000));
        xmssig = std::make_shared<ProtocolPP::jarray<uint8_t>>(xmss.get_field(ProtocolPP::SIGLEN), 0);
        msgout = std::make_shared<ProtocolPP::jarray<uint8_t>>();

        // sign the message
        xmss2.sign(msg, xmssig);

        // verify the message
        msg->append(*xmssig);
        xmss2.verify(msg, msgout);

        // get the status of the sigature
        if (xmss2.get_status() != 0) {
            std::cerr << "In testxmss() vector 2, signature did not verify" << std::endl;
            CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE( "testxmss() signature 2 fail", CPPUNIT_ASSERT( 1 == 2 ) );
        }
    }

    void testzuckeystream() {
        //////////////////////////////////////////
        // ZUC keystream test vectors #1:
        //////////////////////////////////////////
        uint32_t count1 = 0;
        uint8_t bearer1 = 0;
        ProtocolPP::jarray<uint8_t> key1("00000000000000000000000000000000");
        ProtocolPP::jarray<uint8_t>  iv1("00000000000000000000000000000000");
        ProtocolPP::jarray<uint8_t> plain1("0000000000000000");
        ProtocolPP::jarray<uint8_t> output1(plain1.get_size(), 0);
        ProtocolPP::jarray<uint8_t> expect1("27bede74018082da");
        ProtocolPP::jzuc::dir_t dir1=ProtocolPP::jzuc::dir_t::ZUC_UPLINK;
        
        ProtocolPP::jzuc engine1(dir1,
                                 key1.get_ptr(),
                                 key1.get_size(),
                                 count1,
                                 bearer1);
        
        engine1.ProcessData(plain1.get_ptr(),
                            output1.get_ptr(),
                            64);

        CPPUNIT_ASSERT_EQUAL(expect1.to_string(), output1.to_string());
        
        // NOTE: these other three tests can't be run directly without modifying
        // how the IV is constructed in the source code. Protocolpp implementation
        // of ZUC is for 128-EEA3 and 128-EIA3 not pure ZUC so there is no way to
        // pass in the IV or to make bytes 5-7,13-15 of the IV any other value
        // beside zero or byte 4,12 of the IV to NOT zero out the lower two bits
        // They have been verified to ensure that keystream generation is correct
        
        //////////////////////////////////////////
        // ZUC keystream test vectors #2:
        //////////////////////////////////////////
//        uint32_t count2 = 0xFFFFFFFF;
//        uint8_t bearer2 = 0x1F;
//        ProtocolPP::jarray<uint8_t> key2("ffffffffffffffffffffffffffffffff");
//        ProtocolPP::jarray<uint8_t>  iv2("ffffffffffffffffffffffffffffffff");
//        ProtocolPP::jarray<uint8_t> plain2("0000000000000000");
//        ProtocolPP::jarray<uint8_t> output2(plain2.get_size(), 0);
//        ProtocolPP::jarray<uint8_t> expect2("0657cfa07096398b");
//        ProtocolPP::jzuc::dir_t dir2=ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK;
//        
//        ProtocolPP::jzuc engine2(dir2,
//                                 key2.get_ptr(),
//                                 key2.get_size(),
//                                 count2,
//                                 bearer2);
//        
//        engine2.ProcessData(plain2.get_ptr(),
//                            output2.get_ptr(),
//                            64);
//
//        CPPUNIT_ASSERT_EQUAL(expect2.to_string(), output2.to_string());
//        
//        //////////////////////////////////////////
//        // ZUC keystream test vectors #3:
//        //////////////////////////////////////////
//        uint32_t count3 = 0xFFFFFFFF;
//        uint8_t bearer3 = 0x1F;
//        ProtocolPP::jarray<uint8_t> key3("3d4c4be96a82fdaeb58f641db17b455b");
//        ProtocolPP::jarray<uint8_t>  iv3("84319aa8de6915ca1f6bda6bfbd8c766");
//        ProtocolPP::jarray<uint8_t> plain3("0000000000000000");
//        ProtocolPP::jarray<uint8_t> output3(plain3.get_size(), 0);
//        ProtocolPP::jarray<uint8_t> expect3("14f1c2723279c419");
//        ProtocolPP::jzuc::dir_t dir3=ProtocolPP::jzuc::dir_t::ZUC_UPLINK;
//       
//        ProtocolPP::jzuc engine3(dir3,
//                                 key3.get_ptr(),
//                                 key3.get_size(),
//                                 count3,
//                                 bearer3);
//        
//        engine3.ProcessData(plain3.get_ptr(),
//                            output3.get_ptr(),
//                            64);
//
//        CPPUNIT_ASSERT_EQUAL(expect3.to_string(), output3.to_string());
//        
//        //////////////////////////////////////////
//        // ZUC keystream test vectors #4:
//        //////////////////////////////////////////
//        uint32_t count4 = 0xFFFFFFFF;
//        uint8_t bearer4 = 0x1F;
//        ProtocolPP::jarray<uint8_t> key4("4d320bfad4c285bfd6b8bd00f39d8b41");
//        ProtocolPP::jarray<uint8_t>  iv4("52959daba0bf176ece2dc315049eb574");
//        ProtocolPP::jarray<uint8_t> plain4("0000000000000000");
//        ProtocolPP::jarray<uint8_t> output4(plain4.get_size(), 0);
//        ProtocolPP::jarray<uint8_t> expect4("ed4400e70633e5c5");
//        ProtocolPP::jzuc::dir_t dir4=ProtocolPP::jzuc::dir_t::ZUC_UPLINK;
//        
//        ProtocolPP::jzuc engine4(dir4,
//                                 key4.get_ptr(),
//                                 key4.get_size(),
//                                 count4,
//                                 bearer4);
//        
//        engine4.ProcessData(plain4.get_ptr(),
//                            output4.get_ptr(),
//                            64);
//
//        CPPUNIT_ASSERT_EQUAL(expect4.to_string(), output4.to_string());
    }

    void testzuce() {
        // 128-EEA3 ZUCE Test Data #1
        ProtocolPP::jarray<uint8_t> key1("173d14ba5003731d7a60049470f00a29");
        uint32_t count1 = 0x66035492;
        uint8_t bearer1 = 0xf;
        ProtocolPP::jarray<uint8_t> plain1("6cf65340735552ab0c9752fa6f9025fe0bd675d9005875b200");
        ProtocolPP::jarray<uint8_t> output1(plain1.get_size(), 0);
        ProtocolPP::jarray<uint8_t> expect1("a6c85fc66afb8533aafc2518dfe784940ee1e4b030238cc800");
        ProtocolPP::jzuc::dir_t dir1=ProtocolPP::jzuc::dir_t::ZUC_UPLINK;
        
        ProtocolPP::jzuc engine1(dir1,
                                 key1.get_ptr(),
                                 key1.get_size(),
                                 count1,
                                 bearer1);
        
        engine1.ProcessData(plain1.get_ptr(),
                            output1.get_ptr(),
                            193);
        
        CPPUNIT_ASSERT_EQUAL(expect1.to_string(), output1.to_string());
        
        // 128-EEA3 ZUCE Test Data #2
        ProtocolPP::jarray<uint8_t> key2("e5bd3ea0eb55ade866c6ac58bd54302a");
        uint32_t count2 = 0x00056823;
        uint8_t bearer2 = 0x18;
        ProtocolPP::jarray<uint8_t> plain2("14a8ef693d678507bbe7270a7f67ff5006c3525b9807e467c4e56000ba338f5d429559036751822246c80d3b38f07f4be2d8ff5805f5132229bde93bbbdcaf382bf1ee972fbf9977bada8945847a2a6c9ad34a667554e04d1f7fa2c33241bd8f01ba220d");
        
        ProtocolPP::jarray<uint8_t> output2(plain2.get_size(), 0);
        
        ProtocolPP::jarray<uint8_t> expect2("131d43e0dea1be5c5a1bfd971d852cbf712d7b4f57961fea3208afa8bca433f456ad09c7417e58bc69cf8866d1353f74865e80781d202dfb3ecff7fcbc3b190fe82a204ed0e350fc0f6f2613b2f2bca6df5a473a57a4a00d985ebad880d6f23864a07b01");
        
        ProtocolPP::jzuc::dir_t dir2=ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK;
        
        ProtocolPP::jzuc engine2(dir2,
                                 key2.get_ptr(),
                                 key2.get_size(),
                                 count2,
                                 bearer2);
        
        engine2.ProcessData(plain2.get_ptr(),
                            output2.get_ptr(),
                            800);
        
        CPPUNIT_ASSERT_EQUAL(expect2.to_string(), output2.to_string());
        
        // 128-EEA3 ZUCE Test Data #3
        ProtocolPP::jarray<uint8_t> key3("d4552a8fd6e61cc81a2009141a29c10b");
        uint32_t count3 = 0x76452ec1;
        uint8_t bearer3 = 0x02;
        ProtocolPP::jarray<uint8_t> plain3("38f07f4be2d8ff5805f5132229bde93bbbdcaf382bf1ee972fbf9977bada8945847a2a6c9ad34a667554e04d1f7fa2c33241bd8f01ba220d3ca4ec41e074595f54ae2b454fd971432043601965cca85c2417ed6cbec3bada84fc8a579aea7837b0271177242a64dc0a9de71a8edee86ca3d47d033d6bf539804eca86c584a9052de46ad3fced65543bd90207372b27afb79234f5ff43ea870820e2c2b78a8aae61cce52a0515e348d196664a3456b182a07c406e4a20791271cfeda165d535ec5ea2d4df40");
        
        ProtocolPP::jarray<uint8_t> output3(plain3.get_size(), 0);
        
        ProtocolPP::jarray<uint8_t> expect3("8383b0229fcc0b9d2295ec41c977e9c2bb72e220378141f9c8318f3a270dfbcdee6411c2b3044f176dc6e00f8960f97afacd131ad6a3b49b16b7babcf2a509ebb16a75dcab14ff275dbeeea1a2b155f9d52c26452d0187c310a4ee55beaa78ab4024615ba9f5d5adc7728f73560671f013e5e550085d3291df7d5fecedded559641b6c2f585233bc71e9602bd2305855bbd25ffa7f17ecbc042daae38c1f57ad8e8ebd37346f71befdbb7432e0e0bb2cfc09bcd96570cb0c0c39df5e29294e82703a637f80");
        
        ProtocolPP::jzuc::dir_t dir3=ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK;
        
        ProtocolPP::jzuc engine3(dir3,
                                 key3.get_ptr(),
                                 key3.get_size(),
                                 count3,
                                 bearer3);
        
        engine3.ProcessData(plain3.get_ptr(),
                            output3.get_ptr(),
                            1576);
        
        CPPUNIT_ASSERT_EQUAL(expect3.to_string(), output3.to_string());
        
        // 128-EEA3 ZUCE Test Data #4
        ProtocolPP::jarray<uint8_t> key4("db84b4fbccda563b66227bfe456f0f77");
        uint32_t count4 = 0xe4850fe1;
        uint8_t bearer4 = 0x10;
        ProtocolPP::jarray<uint8_t> plain4("e539f3b8973240da03f2b8aa05ee0a00dbafc0e182055dfe3d7383d92cef40e92928605d52d05f4f9018a1f189ae3997ce19155fb1221db8bb0951a853ad852ce16cff07382c93a157de00ddb125c7539fd85045e4ee07e0c43f9e9d6f414fc4d1c62917813f74c00fc83f3e2ed7c45ba5835264b43e0b20afda6b3053bfb6423b7fce25479ff5f139dd9b5b995558e2a56be18dd581cd017c735e6f0d0d97c4ddc1d1da70c6db4a12cc92778e2fbbd6f3ba52af91c9c6b64e8da4f7a2c266d02d001753df08960393c5d56888bf49eb5c16d9a80427a416bcb597df5bfe6f13890a07ee1340e6476b0d9aa8f822ab0fd1ab0d204f40b7ce6f2e136eb67485e507804d504588ad37ffd816568b2dc40311dfb654cdead47e2385c3436203dd836f9c64d97462ad5dfa63b5cfe08acb9532866f5ca787566fca93e6b1693ee15cf6f7a2d689d9741798dc1c238e1be650733b18fb34ff880e16bbd21b47ac");
        
        ProtocolPP::jarray<uint8_t> output4(plain4.get_size(), 0);
        
        ProtocolPP::jarray<uint8_t> expect4("4bbfa91ba25d47db9a9f190d962a19ab323926b351fbd39e351e05da8b8925e30b1cce0d1221101095815cc7cb6319509ec0d67940491987e13f0affac332aa6aa64626d3e9a1917519e0b97b655c6a165e44ca9feac0790d2a321ad3d86b79c5138739fa38d887ec7def449ce8abdd3e7f8dc4ca9e7b73314ad310f9025e61946b3a56dc649ec0da0d63943dff592cf962a7efb2c8524e35a2a6e7879d62604ef268695fa4003027e22e6083077522064bd4a5b906b5f531274f235ed506cff0154c754928a0ce5476f2cb1020a1222d32c1455ecaef1e368fb344d1735bfbedeb71d0a33a2a54b1da5a294e679144ddf11eb1a3de8cf0cc061917974f35c1d9ca0ac81807f8fcce6199a6c7712da865021b04ce0439516f1a526ccda9fd9abbd53c3a684f9ae1e7ee6b11da138ea826c5516b5aadf1abbe36fa7fff92e3a1176064e8d95f2e4882b5500b93228b2194a475c1a27f63f9ffd264989a1bc");
        
        ProtocolPP::jzuc::dir_t dir4=ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK;
        
        ProtocolPP::jzuc engine4(dir4,
                                 key4.get_ptr(),
                                 key4.get_size(),
                                 count4,
                                 bearer4);
        
        engine4.ProcessData(plain4.get_ptr(),
                            output4.get_ptr(),
                            2800);
        
        CPPUNIT_ASSERT_EQUAL(expect4.to_string(), output4.to_string());
        
        // 128-EEA3 ZUCE Test Data #5
        ProtocolPP::jarray<uint8_t> key5("e13fed21b46e4e7ec31253b2bb17b3e0");
        uint32_t count5 = 0x2738cdaa;
        uint8_t bearer5 = 0x1a;
        ProtocolPP::jarray<uint8_t> plain5("8d74e20d54894e06d3cb13cb3933065e8674be62adb1c72b3a646965ab63cb7b7854dfdc27e84929f49c64b872a490b13f957b64827e71f41fbd4269a42c97f824537027f86e9f4ad82d1df451690fdd98b6d03f3a0ebe3a312d6b840ba5a1820b2a2c9709c090d245ed267cf845ae41fa975d3333ac3009fd40eba9eb5b885714b768b697138baf21380eca49f644d48689e4215760b906739f0d2b3f091133ca15d981cbe401baf72d05ace05cccb2d297f4ef6a5f58d91246cfa77215b892ab441d5278452795ccb7f5d79057a1c4f77f80d46db2033cb79bedf8e60551ce10c667f62a97abafabbcd6772018df96a282ea737ce2cb331211f60d5354ce78f9918d9c206ca042c9b62387dd709604a50af16d8d35a8906be484cf2e74a9289940364353249b27b4c9ae29eddfc7da6418791a4e7baa0660fa64511f2d685cc3a5ff70e0d2b74292e3b8a0cd6b04b1c790b8ead2703708540dea2fc09c3da770f65449e84d817a4f551055e19ab85018a0028b71a144d96791e9a3577933504eee0060340c69d274e1bf9d805dcbcc1a6faa976800b6ff2b671dc463652fa8a33ee50974c1c21be01eabb2167430269d72ee511c9dde30797c9a25d86ce74f5b961be5fdfb6807814039e7137636bd1d7fa9e09efd2007505906a5ac45dfdeed7757bbee745749c29633350bee0ea6f409df45801600");
        
        ProtocolPP::jarray<uint8_t> output5(plain5.get_size(), 0);
        
        ProtocolPP::jarray<uint8_t> expect5("94eaa4aa30a57137ddf09b97b25618a20a13e2f10fa5bf8161a879cc2ae797a6b4cf2d9df31debb9905ccfec97de605d21c61ab8531b7f3c9da5f03931f8a0642de48211f5f52ffea10f392a047669985da454a28f080961a6c2b62daa17f33cd60a4971f48d2d909394a55f48117ace43d708e6b77d3dc46d8bc017d4d1abb77b7428c042b06f2f99d8d07c9879d99600127a31985f1099bbd7d6c1519ede8f5eeb4a610b349ac01ea2350691756bd105c974a53eddb35d1d4100b012e522ab41f4c5f2fde76b59cb8b96d885cfe4080d1328a0d636cc0edc05800b76acca8fef672084d1f52a8bbd8e0993320992c7ffbae17c408441e0ee883fc8a8b05e22f5ff7f8d1b48c74c468c467a028f09fd7ce91109a570a2d5c4d5f4fa18c5dd3e4562afe24ef771901f59af645898acef088abae07e92d52eb2de55045bb1b7c4164ef2d7a6cac15eeb926d7ea2f08b66e1f759f3aee44614725aa3c7482b30844c143ff85b53f1e583c501257dddd096b81268daa303f17234c2333541f0bb8e190648c5807c866d7193228609adb948686f7de294a802cc38f7fe5208f5ea3196d0167b9bdd02f0d2a5221ca508f893af5c4b4bb9f4f520fd84289b3dbe7e61497a7e2a584037ea637b6981127174af57b471df4b2768fd79c1540fb3edf2ea22cb69bec0cf8d933d9c6fdd645e850591cca3d62c0cc0");
        
        ProtocolPP::jzuc::dir_t dir5=ProtocolPP::jzuc::dir_t::ZUC_UPLINK;
        
        ProtocolPP::jzuc engine5(dir5,
                                 key5.get_ptr(),
                                 key5.get_size(),
                                 count5,
                                 bearer5);
        
        engine5.ProcessData(plain5.get_ptr(),
                            output5.get_ptr(),
                            4024);

        CPPUNIT_ASSERT_EQUAL(expect5.to_string(), output5.to_string());
    }

    void testzuca() {
        // 128-EIA3 ZUCA Test Data #1
        ProtocolPP::jarray<uint8_t> key1(16,0);
        uint32_t count1 = 0;
        uint32_t bearer1 = 0;
        ProtocolPP::jarray<uint8_t> plain1(1,0);
        ProtocolPP::jarray<uint8_t> ricv1(4,0);
        ProtocolPP::jarray<uint8_t> icv1("c8a9595e");
        ProtocolPP::jzuc::dir_t dir1=ProtocolPP::jzuc::dir_t::ZUC_UPLINK;
        
        ProtocolPP::jzuc engine1(dir1,
                                 key1.get_ptr(),
                                 key1.get_size(),
                                 count1,
                                 bearer1);
        
        engine1.ProcessData(plain1.get_ptr(),
                            1);
        
        engine1.result(ricv1.get_ptr());
        
        CPPUNIT_ASSERT_EQUAL(icv1.to_string(), ricv1.to_string());

        // 128-EIA3 ZUCA Test Data #2
        ProtocolPP::jarray<uint8_t> key2("47054125561eb2dda94059da05097850");
        uint32_t count2 = 0x561eb2dd;
        uint32_t bearer2 = 0x00000014;
        ProtocolPP::jarray<uint8_t> plain2(12,0);
        ProtocolPP::jarray<uint8_t> ricv2(4,0);
        ProtocolPP::jarray<uint8_t> icv2("6719a088");
        ProtocolPP::jzuc::dir_t dir2=ProtocolPP::jzuc::dir_t::ZUC_UPLINK;
        
        ProtocolPP::jzuc engine2(dir2,
                                 key2.get_ptr(),
                                 key2.get_size(),
                                 count2,
                                 bearer2);
        
        engine2.ProcessData(plain2.get_ptr(),
                            90);
        
        engine2.result(ricv2.get_ptr());
        
        CPPUNIT_ASSERT_EQUAL(icv2.to_string(), ricv2.to_string());
        
        // 128-EIA3 ZUCA Test Data #3
        ProtocolPP::jarray<uint8_t> key3("c9e6cec4607c72db000aefa88385ab0a");
        uint32_t count3 = 0xa94059da;
        uint32_t bearer3 = 0x0000000a;
        ProtocolPP::jarray<uint8_t> plain3("983b41d47d780c9e1ad11d7eb70391b1de0b35da2dc62f83e7b78d6306ca0ea07e941b7be91348f9fcb170e2217fecd97f9f68adb16e5d7d21e569d280ed775cebde3f4093c5388100000000");
        
        ProtocolPP::jarray<uint8_t> ricv3(4,0);
        ProtocolPP::jarray<uint8_t> icv3("fae8ff0b");
        ProtocolPP::jzuc::dir_t dir3=ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK;
        
        ProtocolPP::jzuc engine3(dir3,
                                 key3.get_ptr(),
                                 key3.get_size(),
                                 count3,
                                 bearer3);
        
        engine3.ProcessData(plain3.get_ptr(),
                            577);
        
        engine3.result(ricv3.get_ptr());
        
        CPPUNIT_ASSERT_EQUAL(icv3.to_string(), ricv3.to_string());
        
        // 128-EIA3 ZUCA Test Data #4
        ProtocolPP::jarray<uint8_t> key4("c8a48262d0c2e2bac4b96ef77e80ca59");
        uint32_t count4 = 0x05097850;
        uint32_t bearer4 = 0x00000010;
        ProtocolPP::jarray<uint8_t> plain4("b546430bf87b4f1ee834704cd6951c36e26f108cf731788f48dc34f1678c05221c8fa7ff2f39f477e7e49ef60a4ec2c3de24312a96aa26e1cfba57563838b297f47e8510c779fd6654b143386fa639d31edbd6c06e47d159d94362f26aeeedee0e4f49d9bf8412995415bfad56ee82d1ca7463abf085b082b09904d6d990d43cf2e062f40839d93248b1eb92cdfed5300bc148280430b6d0caa094b6ec8911ab7dc36824b824dc0af6682b0935fde7b492a14dc2f43648038da2cf79170d2d50133fd49416cb6e33bea90b8bf4559b03732a01ea290e6d074f79bb83c10e580015cc1a85b36b5501046e9c4bdcae5135690b8666bd54b7a703ea7b6f220a5469a568027e");
        
        ProtocolPP::jarray<uint8_t> ricv4(4,0);
        ProtocolPP::jarray<uint8_t> icv4("004ac4d6");
        ProtocolPP::jzuc::dir_t dir4=ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK;
        
        ProtocolPP::jzuc engine4(dir4,
                                 key4.get_ptr(),
                                 key4.get_size(),
                                 count4,
                                 bearer4);
        
        engine4.ProcessData(plain4.get_ptr(),
                            2079);
        
        engine4.result(ricv4.get_ptr());
        
        CPPUNIT_ASSERT_EQUAL(icv4.to_string(), ricv4.to_string());
        
        // 128-EIA3 ZUCA Test Data #5
        ProtocolPP::jarray<uint8_t> key5("6b8b08ee79e0b5982d6d128ea9f220cb");
        uint32_t count5 = 0x561eb2dd;
        uint32_t bearer5 = 0x0000001c;
        ProtocolPP::jarray<uint8_t> plain5("5bad724710ba1c56d5a315f8d40f6e093780be8e8de07b6992432018e08ed96a5734af8bad8a575d3a1f162f85045cc770925571d9f5b94e454a77c16e72936bf016ae157499f0543b5d52caa6dbeab697d2bb73e41b8075dce79b4b86044f661d4485a543dd78606e0419e8059859d3cb2b67ce0977603f81ff839e331859544cfbc8d00fef1a4c8510fb547d6b06c611ef44f1bce107cfa45a06aab360152b28dc1ebe6f7fe09b0516f9a5b02a1bd84bb0181e2e89e19bd8125930d178682f3862dc51b636f04e720c47c3ce51ad70d94b9b2255fbae906549f499f8c6d39947ed5e5df8e2def113253e7b08d0a76b6bfc68c812f375c79b8fe5fd85976aa6d46b4a2339d8ae5147f680fbe70f978b38effd7b2f7866a22554e193a94e98a68b74bd25bb2b3f5fb0a5fd59887f9ab68159b7178d5b7b677cb546bf41eadca216fc10850128f8bdef5c8d89f96afa4fa8b54885565ed838a950fee5f1c3b0a4f6fb71e54dfd169e82cecc7266c850e67c5ef0ba960f5214060e71eb172a75fc1486835cbea6534465b055c96a72e4105224182325d830414b40214daa8091d2e0fb010ae15c6de90850973bdf1e423be148a237b87a0c9f34d4b47605b803d743a86a90399a4af396d3a1200a62f3d9507962e8e5bee6d3da2bb3f7237664ac7a292823900bc63503b29e80d63f6067bf8e1716ac25beba350deb62a99fe03185eb4f69937ecd387941fda544ba67db0911774938b01827bcc69c92b3f772a9d2859ef003398b1f6bbad7b574f7989a1d10b2df798e0dbf30d6587464d24878cd00c0eaee8a1a0cc753a27979e11b41db1de3d5038afaf49f5c682c3748d8a3a9ec54e6a371275f1683510f8e4f90938f9ab6e134c2cfdf4841cba88e0cff2b0bcc8e6adcb71109b5198fecf1bb7e5c531aca50a56a8a3b6de59862d41fa113d9cd957808f08571d9a4bb792af271f6cc6dbb8dc7ec36e36be1ed308164c31c7c0afc541c000000");
        
        ProtocolPP::jarray<uint8_t> ricv5(4,0);
        ProtocolPP::jarray<uint8_t> icv5("0ca12792");
        ProtocolPP::jzuc::dir_t dir5=ProtocolPP::jzuc::dir_t::ZUC_UPLINK;
        
        ProtocolPP::jzuc engine5(dir5,
                                 key5.get_ptr(),
                                 key5.get_size(),
                                 count5,
                                 bearer5);
        
        engine5.ProcessData(plain5.get_ptr(),
                            5670);
        
        engine5.result(ricv5.get_ptr());
        
        CPPUNIT_ASSERT_EQUAL(icv5.to_string(), ricv5.to_string());
    }

    void testzuc256() {
        // test case keystream 1 from The ZUC-256 Stream Cipher
        ProtocolPP::jarray<uint8_t> key(32,0);
        ProtocolPP::jarray<uint8_t> iv(25,0);
        ProtocolPP::jarray<uint8_t> msg(80,0x00);
        ProtocolPP::jarray<uint8_t> out(80,0x00);
        ProtocolPP::jarray<uint8_t> exp("58D03AD62E032CE2DAFC683A39BDCB0352A2BC67F1B7DE74163CE3A101EF55589639D75B95FA681B7F090DF756391CCC903B7612744D544C17BC3FAD8B163B0821787C0B97775BB84943C6BBE8AD8AFD");

        ProtocolPP::jzuc tmpk1(ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK,
                               key.get_ptr(),
                               key.get_size(),
                               iv.get_ptr(),
                               iv.get_size());

        tmpk1.ProcessData(msg.get_ptr(),
                          out.get_ptr(),
                          msg.get_size()*8);

        CPPUNIT_ASSERT_EQUAL(exp.to_string(), out.to_string());

        // test case keystream 2 from The ZUC-256 Stream Cipher
        key = ProtocolPP::jarray<uint8_t>(32,0xFF);
        iv  = ProtocolPP::jarray<uint8_t>(8,0x3F);
        iv.append(ProtocolPP::jarray<uint8_t>(17, 0xFF));

        msg = ProtocolPP::jarray<uint8_t>(80,0x00);
        out = ProtocolPP::jarray<uint8_t>(80,0x00);
        exp = ProtocolPP::jarray<uint8_t>("3356CBAED1A1C18B6BAA4FFE343F777C9E15128F251AB65B949F7B26EF7157F296DD2FA9DF95E3EE7A5BE02EC32BA585505AF316C2F9DED27CDBD935e441CE1115FD0A80BB7AEF6768989416B8FAC8C2");

        ProtocolPP::jzuc tmpk2(ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK,
                               key.get_ptr(),
                               key.get_size(),
                               iv.get_ptr(),
                               iv.get_size());

        tmpk2.ProcessData(msg.get_ptr(),
                          out.get_ptr(),
                          msg.get_size()*8);

        CPPUNIT_ASSERT_EQUAL(exp.to_string(), out.to_string());
    }

    void testzuc256_128() {
        // test case keystream 1 from The ZUC-256 Stream Cipher
        ProtocolPP::jarray<uint8_t> key(32,0);
        ProtocolPP::jarray<uint8_t> iv(16,0);
        ProtocolPP::jarray<uint8_t> msg(80,0x00);
        ProtocolPP::jarray<uint8_t> out(80,0x00);
        ProtocolPP::jarray<uint8_t> exp("e457e206cee79e167da20fd03bbb22cca2ec34f0e4e12c0b0ad0fb236051348af9779552454c3dbb397d19b32839033211b9ae546094770b5016e134620ebf4a302c9be3b65db1422b564caa9caeca83");

        ProtocolPP::jzuc tmpk1(ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK,
                               key.get_ptr(),
                               key.get_size(),
                               iv.get_ptr(),
                               iv.get_size());

        tmpk1.ProcessData(msg.get_ptr(),
                          out.get_ptr(),
                          msg.get_size()*8);

        CPPUNIT_ASSERT_EQUAL(exp.to_string(), out.to_string());

        // test case keystream 2 from The ZUC-256 Stream Cipher
        key = ProtocolPP::jarray<uint8_t>(32,0xFF);
        iv  = ProtocolPP::jarray<uint8_t>(16,0xFF);

        msg = ProtocolPP::jarray<uint8_t>(80,0x00);
        out = ProtocolPP::jarray<uint8_t>(80,0x00);
        exp = ProtocolPP::jarray<uint8_t>("7f8605429c82e2634ad9a83ae7d711f64eba1791dfa2108978d9af94124a3eee31feb686be91bfd5148b5e719ce309ec21238b2dec2acee4df3470522c5ac5c33dc68a2705c09c6f2396a67b091ca2e0");

        ProtocolPP::jzuc tmpk2(ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK,
                               key.get_ptr(),
                               key.get_size(),
                               iv.get_ptr(),
                               iv.get_size());

        tmpk2.ProcessData(msg.get_ptr(),
                          out.get_ptr(),
                          msg.get_size()*8);

        CPPUNIT_ASSERT_EQUAL(exp.to_string(), out.to_string());
    }

    void testzuca256() {
        // test case keystream 1 from The ZUC-256 Stream Cipher
        ProtocolPP::jarray<uint8_t> key(32,0);
        ProtocolPP::jarray<uint8_t> iv(25,0);
        ProtocolPP::jarray<uint8_t> msg(50,0x00);
        ProtocolPP::jarray<uint8_t> out(50,0x00);
        ProtocolPP::jarray<uint8_t> ricv("9B972A74");
        ProtocolPP::jarray<uint8_t> icv(4,0);

        ProtocolPP::jzuc tmp (ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK,
                              key.get_ptr(),
                              key.get_size(),
                              iv.get_ptr(),
                              iv.get_size(),
                              4);

        tmp.ProcessData(msg.get_ptr(),
                        400);

        tmp.result(icv.get_ptr());

        CPPUNIT_ASSERT_EQUAL(ricv.to_string(), icv.to_string());

        // test case 2 from The ZUC-256 Stream Cipher
        msg = ProtocolPP::jarray<uint8_t>(500,0xFF);
        out = ProtocolPP::jarray<uint8_t>(500,0x00);
        ricv = ProtocolPP::jarray<uint8_t>("8754F5CF");
        icv = ProtocolPP::jarray<uint8_t>(4,0);

        ProtocolPP::jzuc tmp2 (ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK,
                               key.get_ptr(),
                               key.get_size(),
                               iv.get_ptr(),
                               iv.get_size(),
                               4);

        tmp2.ProcessData(msg.get_ptr(),
                         4000);

        tmp2.result(icv.get_ptr());

        CPPUNIT_ASSERT_EQUAL(ricv.to_string(), icv.to_string());

        // test case 3 from The ZUC-256 Stream Cipher
        key = ProtocolPP::jarray<uint8_t>(32,0xFF);
        iv  = ProtocolPP::jarray<uint8_t>(9,0x3F);
        iv.append(ProtocolPP::jarray<uint8_t>(16, 0xFF));
        ricv = ProtocolPP::jarray<uint8_t>("1F3079B4");
        icv = ProtocolPP::jarray<uint8_t>(4,0);

        msg = ProtocolPP::jarray<uint8_t>(50,0x00);
        out = ProtocolPP::jarray<uint8_t>(50,0x00);

        ProtocolPP::jzuc tmp3 (ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK,
                               key.get_ptr(),
                               key.get_size(),
                               iv.get_ptr(),
                               iv.get_size(),
                               4);

        tmp3.ProcessData(msg.get_ptr(),
                         400);

        tmp3.result(icv.get_ptr());

        CPPUNIT_ASSERT_EQUAL(ricv.to_string(), icv.to_string());

        // test case 4 from The ZUC-256 Stream Cipher
        msg = ProtocolPP::jarray<uint8_t>(500,0xFF);
        out = ProtocolPP::jarray<uint8_t>(500,0x00);
        ricv = ProtocolPP::jarray<uint8_t>("5C7C8B88");
        icv = ProtocolPP::jarray<uint8_t>(4,0);

        ProtocolPP::jzuc tmp4 (ProtocolPP::jzuc::dir_t::ZUC_DOWNLINK,
                               key.get_ptr(),
                               key.get_size(),
                               iv.get_ptr(),
                               iv.get_size(),
                               4);

        tmp4.ProcessData(msg.get_ptr(),
                         4000);

        tmp4.result(icv.get_ptr());

        CPPUNIT_ASSERT_EQUAL(ricv.to_string(), icv.to_string());
    }

    void testppcov() {
        ProtocolPP::jarray<uint8_t> mytmp = ProtocolPP::jprotocol::to_array((uint8_t)0xAA);
        ProtocolPP::jarray<uint8_t> mytmp2 = ProtocolPP::jprotocol::to_array((uint16_t)0xAABB);
        ProtocolPP::jarray<uint8_t> mytmp3 = ProtocolPP::jprotocol::to_array((uint32_t)0xAABBCCDD);
        ProtocolPP::jarray<uint8_t> mytmp4 = ProtocolPP::jprotocol::to_array((uint64_t)0x22334455AABBCCDD);
        ProtocolPP::jarray<uint8_t> mytmp93(3,0xA5);
        ProtocolPP::jarray<uint8_t> mytmp95(5,0xA5);
        ProtocolPP::jarray<uint8_t> mytmp96(6,0xA5);
        ProtocolPP::jarray<uint8_t> mytmp97(7,0xA5);

        uint8_t  mytmp5 = ProtocolPP::jprotocol::to_u8(mytmp);
                 mytmp5 = ProtocolPP::jprotocol::to_u8(mytmp93);
        uint16_t mytmp6 = ProtocolPP::jprotocol::to_u16(mytmp);
                 mytmp6 = ProtocolPP::jprotocol::to_u16(mytmp2);
                 mytmp6 = ProtocolPP::jprotocol::to_u16(mytmp4);
        uint32_t mytmp7 = ProtocolPP::jprotocol::to_u32(mytmp);
                 mytmp7 = ProtocolPP::jprotocol::to_u32(mytmp2);
                 mytmp7 = ProtocolPP::jprotocol::to_u32(mytmp3);
                 mytmp7 = ProtocolPP::jprotocol::to_u32(mytmp93);
                 mytmp7 = ProtocolPP::jprotocol::to_u32(mytmp4);
        uint64_t mytmp8 = ProtocolPP::jprotocol::to_u64(mytmp);
                 mytmp8 = ProtocolPP::jprotocol::to_u64(mytmp2);
                 mytmp8 = ProtocolPP::jprotocol::to_u64(mytmp3);
                 mytmp8 = ProtocolPP::jprotocol::to_u64(mytmp4);
                 mytmp8 = ProtocolPP::jprotocol::to_u64(mytmp93);
                 mytmp8 = ProtocolPP::jprotocol::to_u64(mytmp95);
                 mytmp8 = ProtocolPP::jprotocol::to_u64(mytmp96);
                 mytmp8 = ProtocolPP::jprotocol::to_u64(mytmp97);
    }

    void testdhcov() {
        // test Ed25519 curve for Diffie-Hellman
        ProtocolPP::jikev2dh tmp(logger);
        ProtocolPP::jikev2dh tmp2(logger);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> sharedsec;
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> pubkey;
        std::shared_ptr<CryptoPP::SecByteBlock> prvkey;
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> pubkey2;
        std::shared_ptr<CryptoPP::SecByteBlock> prvkey2;

        tmp.get_pubkey(ProtocolPP::DH_CURVE_25519,
                       pubkey,
                       prvkey);

        tmp2.get_pubkey(ProtocolPP::DH_CURVE_25519,
                        pubkey2,
                        prvkey2);

        sharedsec = std::make_shared<ProtocolPP::jarray<uint8_t>>(pubkey->get_size(), 0);
        bool result = tmp.verify(ProtocolPP::DH_CURVE_25519,
                                 pubkey2,
                                 prvkey,
                                 sharedsec);

        CPPUNIT_ASSERT_EQUAL(true, result);
    }

    void testudpcov() {
        ProtocolPP::judpsa tmp;

        ProtocolPP::judpsa tmp2(tmp);

        std::shared_ptr<ProtocolPP::judpsa> tmp3 = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::ENCAP,
                                                                                        ProtocolPP::NOPROTO,
                                                                                        (uint16_t)0xFFAA,
                                                                                        (uint16_t)0xAAFF,
                                                                                        0,
                                                                                        1500);
        std::shared_ptr<ProtocolPP::judpsa> tmp4(tmp3);

        // set fields (includes incorrect values for coverage)
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::SOURCE, ProtocolPP::ENCAP);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::SOURCE, 0xFFFF);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::DESTINATION, 0xAAAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::RCVWINDOW, 0xAAAA);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::MTU, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::VNI, 0x3C3A5A5C);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::TCPTIMEOUT, 0xC3C3A5A5);

        // get fields (includes incorrect values for coverage)
        ProtocolPP::direction_t mytmp = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION);
        mytmp = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::SOURCE);
        uint16_t mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::SOURCE);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::DESTINATION);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::RCVWINDOW);
        uint32_t mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::MTU);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::VNI);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::OFFSET);

        std::shared_ptr<ProtocolPP::judp> myudp = std::make_shared<ProtocolPP::judp>(tmp4);
        myudp->set_field(ProtocolPP::SOURCE, 0);
        myudp->set_field(ProtocolPP::DESTINATION, 0);
        myudp->set_field(ProtocolPP::LENGTH, 0);
        myudp->set_field(ProtocolPP::CHECKSUM, 0);
        myudp->set_field(ProtocolPP::MTU, 0);
        myudp->set_field(ProtocolPP::VNI, 1);
        
        ProtocolPP::jarray<uint8_t> newhdr(4, 0xFF);
        uint64_t myfield = myudp->get_field(ProtocolPP::SOURCE, newhdr);
        myfield = myudp->get_field(ProtocolPP::DESTINATION, newhdr);
        myfield = myudp->get_field(ProtocolPP::LENGTH, newhdr);
        myfield = myudp->get_field(ProtocolPP::CHECKSUM, newhdr);
        myfield = myudp->get_field(ProtocolPP::MTU, newhdr);
        myfield = myudp->get_field(ProtocolPP::SOURCE);
        myfield = myudp->get_field(ProtocolPP::DESTINATION);
        myfield = myudp->get_field(ProtocolPP::LENGTH);
        myfield = myudp->get_field(ProtocolPP::CHECKSUM);
        myfield = myudp->get_field(ProtocolPP::MTU);
        myfield = myudp->get_field(ProtocolPP::VNI);

        myudp->set_hdr(newhdr);
        newhdr = myudp->get_hdr();
    }

    void testgrecov() {
        ProtocolPP::jgresa tmp;

        ProtocolPP::jgresa tmp2(tmp);

        std::shared_ptr<ProtocolPP::jgresa> tmp3 = std::make_shared<ProtocolPP::jgresa>(ProtocolPP::ENCAP,
                                                                                        ProtocolPP::EGRE,
                                                                                        false,
                                                                                        false,
                                                                                        false,
                                                                                        0,
                                                                                        0,
                                                                                        0,
                                                                                        0);
        std::shared_ptr<ProtocolPP::jgresa> tmp4(tmp3);

        // set fields (includes incorrect values for coverage)
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::SOURCE, ProtocolPP::ENCAP);

        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::MODE, ProtocolPP::NVGRE);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::SOURCE, ProtocolPP::NVGRE);

        tmp4->set_field<bool>(ProtocolPP::field_t::CBIT, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::KBIT, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::SBIT, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::SOURCE, true);

        tmp4->set_field<uint8_t>(ProtocolPP::field_t::VERSION, 0xFF);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::FLOWID, 0xFF);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::PROTYPE, 0xFF);

        tmp4->set_field<uint16_t>(ProtocolPP::field_t::PROTYPE, 0x0800);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::DESTINATION, 0xAAAA);

        tmp4->set_field<uint32_t>(ProtocolPP::field_t::KEY, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, 0x3C3A5A5C);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::MODE, 0xC3C3A5A5);

        // get fields (includes incorrect values for coverage)
        ProtocolPP::direction_t mytmp = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION);
        mytmp = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::SOURCE);

        ProtocolPP::protocol_t mymode = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::MODE);
        mymode = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::SOURCE);

        bool mytmp20 = tmp4->get_field<bool>(ProtocolPP::field_t::CBIT);
        mytmp20 = tmp4->get_field<bool>(ProtocolPP::field_t::KBIT);
        mytmp20 = tmp4->get_field<bool>(ProtocolPP::field_t::SBIT);
        mytmp20 = tmp4->get_field<bool>(ProtocolPP::field_t::SOURCE);

        uint8_t mytmp8 = tmp4->get_field<uint8_t>(ProtocolPP::field_t::VERSION);
        mytmp8 = tmp4->get_field<uint8_t>(ProtocolPP::field_t::FLOWID);
        mytmp8 = tmp4->get_field<uint8_t>(ProtocolPP::field_t::MODE);

        uint16_t mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::PROTYPE);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::DESTINATION);

        uint32_t mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::KEY);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::SEQNUM);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::MODE);

        std::shared_ptr<ProtocolPP::jgre> mygre = std::make_shared<ProtocolPP::jgre>(tmp4);
        mygre->set_field(ProtocolPP::CBIT, 1);
        mygre->set_field(ProtocolPP::KBIT, 1);
        mygre->set_field(ProtocolPP::SBIT, 1);
        mygre->set_field(ProtocolPP::VERSION, 0x02);
        mygre->set_field(ProtocolPP::PROTYPE, 0x1234);
        mygre->set_field(ProtocolPP::KEY, 0x12345678);
        mygre->set_field(ProtocolPP::SEQNUM, 0x23456781);
        mygre->set_field(ProtocolPP::DIRECTION, 0x90AABBCC);
        
        uint64_t tmp15 = mygre->get_field(ProtocolPP::CBIT);
        tmp15 = mygre->get_field(ProtocolPP::KBIT);
        tmp15 = mygre->get_field(ProtocolPP::SBIT);
        tmp15 = mygre->get_field(ProtocolPP::VERSION);
        tmp15 = mygre->get_field(ProtocolPP::PROTYPE);
        tmp15 = mygre->get_field(ProtocolPP::KEY);
        tmp15 = mygre->get_field(ProtocolPP::SEQNUM);
        tmp15 = mygre->get_field(ProtocolPP::DIRECTION);
        
        ProtocolPP::jarray<uint8_t> newhdr(16, 0xFF);
        uint64_t myfield = mygre->get_field(ProtocolPP::CBIT, newhdr);
        myfield = mygre->get_field(ProtocolPP::KBIT, newhdr);
        myfield = mygre->get_field(ProtocolPP::SBIT, newhdr);
        myfield = mygre->get_field(ProtocolPP::VERSION, newhdr);
        myfield = mygre->get_field(ProtocolPP::PROTYPE, newhdr);
        myfield = mygre->get_field(ProtocolPP::CHECKSUM, newhdr);
        myfield = mygre->get_field(ProtocolPP::KEY, newhdr);
        myfield = mygre->get_field(ProtocolPP::SEQNUM, newhdr);
        myfield = mygre->get_field(ProtocolPP::FLOWID, newhdr);
        myfield = mygre->get_field(ProtocolPP::DESTINATION, newhdr);

        mygre->set_hdr(newhdr);
        newhdr = mygre->get_hdr();
    }

    void testtcpcov() {
        ProtocolPP::jtcpsa tmp6;

        ProtocolPP::jtcpsa tmp2(tmp6);

        std::shared_ptr<ProtocolPP::jtcpsa> tmp3 = std::make_shared<ProtocolPP::jtcpsa>(ProtocolPP::ENCAP,
                                                                                        1500,
                                                                                        (uint16_t)0xFFAA,
                                                                                        (uint16_t)0xAAFF,
                                                                                        (uint32_t)0x00112233,
                                                                                        (uint32_t)0x00332211,
                                                                                        (uint8_t)0,
                                                                                        (uint8_t)0xA5,
                                                                                        (uint16_t)0x000F,
                                                                                        (uint16_t)0,
                                                                                        0xFFFFFFFF);

        std::shared_ptr<ProtocolPP::jtcpsa> tmp4(tmp3);

        // set fields (includes incorrect values for coverage)
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::SOURCE, ProtocolPP::ENCAP);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::OFFSET, 0xFF);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::FLAGS, 0xFF);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::DESTINATION, 0xFF);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::SOURCE, 0xFFFF);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::DESTINATION, 0xAAAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::RCVWINDOW, 0xAAAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::URGENT, 0xAAAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::PRECEDENCE, 0xAAAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::SNDWND, 0xAAAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::SNDUP, 0xAAAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::RCVWND, 0xAAAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::RCVUP, 0xAAAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::OFFSET, 0xAAAA);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::ACKNUM, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::SEGLEN, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::SNDUNA, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::SNDNXT, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::SNDW1, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::SNDW2, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::ISS, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::RCVNXT, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::IRS, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::MTU, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::TCPTIMEOUT, 0xC3C3A5A5);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::OFFSET, 0xC3C3A5A5);

        // get fields (includes incorrect values for coverage)
        ProtocolPP::direction_t mytmp = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION);
        mytmp = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::SOURCE);
        uint8_t mytmp2 = tmp4->get_field<uint8_t>(ProtocolPP::field_t::OFFSET);
        mytmp2 = tmp4->get_field<uint8_t>(ProtocolPP::field_t::FLAGS);
        mytmp2 = tmp4->get_field<uint8_t>(ProtocolPP::field_t::DESTINATION);
        uint16_t mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::SOURCE);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::DESTINATION);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::RCVWINDOW);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::URGENT);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::PRECEDENCE);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::SNDWND);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::SNDUP);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::RCVWND);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::RCVUP);
        mytmp3 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::OFFSET);
        uint32_t mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::SEQNUM);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::ACKNUM);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::SEGLEN);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::SNDUNA);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::SNDNXT);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::SNDW1);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::SNDW2);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::ISS);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::RCVNXT);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::IRS);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::MTU);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::TCPTIMEOUT);
        mytmp4 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::OFFSET);

        std::shared_ptr<ProtocolPP::jtcp> mytcp = std::make_shared<ProtocolPP::jtcp>(ProtocolPP::jtcp::tcpstate_t::ESTABLISHED, tmp4);
        ProtocolPP::jarray<uint8_t> tmphdr(24,0xAA);
        mytcp->set_hdr(tmphdr);
        tmphdr = mytcp->get_hdr();

        // set field
        mytcp->set_field(ProtocolPP::SOURCE, 0x0011);
        mytcp->set_field(ProtocolPP::DESTINATION, 0x1100);
        mytcp->set_field(ProtocolPP::SEQNUM, 0x1100);
        mytcp->set_field(ProtocolPP::ACKNUM, 0x1100);
        mytcp->set_field(ProtocolPP::OFFSET, 0x1100);
        mytcp->set_field(ProtocolPP::FLAGS, 0x1100);
        mytcp->set_field(ProtocolPP::RCVWINDOW, 0x1100);
        mytcp->set_field(ProtocolPP::CHECKSUM, 0x1100);
        mytcp->set_field(ProtocolPP::URGENT, 0x1100);
        mytcp->set_field(ProtocolPP::SNDUNA, 0x1100);
        mytcp->set_field(ProtocolPP::SNDNXT, 0x1100);
        mytcp->set_field(ProtocolPP::SNDWND, 0x1100);
        mytcp->set_field(ProtocolPP::SNDUP, 0x1100);
        mytcp->set_field(ProtocolPP::SNDW1, 0x1100);
        mytcp->set_field(ProtocolPP::SNDW2, 0x1100);
        mytcp->set_field(ProtocolPP::ISS, 0x1100);
        mytcp->set_field(ProtocolPP::RCVNXT, 0x1100);
        mytcp->set_field(ProtocolPP::RCVWND, 0x1100);
        mytcp->set_field(ProtocolPP::RCVUP, 0x1100);
        mytcp->set_field(ProtocolPP::IRS, 0x1100);
        mytcp->set_field(ProtocolPP::STATE, 0);
        mytcp->set_field(ProtocolPP::STATE, 1);
        mytcp->set_field(ProtocolPP::STATE, 2);
        mytcp->set_field(ProtocolPP::STATE, 3);
        mytcp->set_field(ProtocolPP::STATE, 4);
        mytcp->set_field(ProtocolPP::STATE, 5);
        mytcp->set_field(ProtocolPP::STATE, 6);
        mytcp->set_field(ProtocolPP::STATE, 7);
        mytcp->set_field(ProtocolPP::STATE, 8);
        mytcp->set_field(ProtocolPP::STATE, 9);

        // set field
        uint64_t tmp = mytcp->get_field(ProtocolPP::SOURCE, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::DESTINATION, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::SEQNUM, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::ACKNUM, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::OFFSET, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::FLAGS, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::RCVWINDOW, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::CHECKSUM, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::URGENT, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::STATE, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::SNDUNA, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::SNDNXT, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::SNDWND, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::SNDUP, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::SNDW1, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::SNDW2, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::ISS, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::RCVNXT, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::RCVWND, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::RCVUP, tmphdr);
        tmp = mytcp->get_field(ProtocolPP::IRS, tmphdr);

        // get field
        tmp = mytcp->get_field(ProtocolPP::SOURCE);
        tmp = mytcp->get_field(ProtocolPP::DESTINATION);
        tmp = mytcp->get_field(ProtocolPP::SEQNUM);
        tmp = mytcp->get_field(ProtocolPP::ACKNUM);
        tmp = mytcp->get_field(ProtocolPP::OFFSET);
        tmp = mytcp->get_field(ProtocolPP::FLAGS);
        tmp = mytcp->get_field(ProtocolPP::RCVWINDOW);
        tmp = mytcp->get_field(ProtocolPP::CHECKSUM);
        tmp = mytcp->get_field(ProtocolPP::URGENT);
        tmp = mytcp->get_field(ProtocolPP::STATE);
        tmp = mytcp->get_field(ProtocolPP::SNDUNA);
        tmp = mytcp->get_field(ProtocolPP::SNDNXT);
        tmp = mytcp->get_field(ProtocolPP::SNDWND);
        tmp = mytcp->get_field(ProtocolPP::SNDUP);
        tmp = mytcp->get_field(ProtocolPP::SNDW1);
        tmp = mytcp->get_field(ProtocolPP::SNDW2);
        tmp = mytcp->get_field(ProtocolPP::ISS);
        tmp = mytcp->get_field(ProtocolPP::RCVNXT);
        tmp = mytcp->get_field(ProtocolPP::RCVWND);
        tmp = mytcp->get_field(ProtocolPP::RCVUP);
        tmp = mytcp->get_field(ProtocolPP::IRS);

        // add options
        mytcp->add_option(ProtocolPP::jtcp::tcpopt_t::END, tmphdr);
        mytcp->add_option(ProtocolPP::jtcp::tcpopt_t::NOP, tmphdr);
        mytcp->add_option(ProtocolPP::jtcp::tcpopt_t::MSS, tmphdr);
        mytcp->add_option(ProtocolPP::jtcp::tcpopt_t::WINSCALE, tmphdr);
        mytcp->add_option(ProtocolPP::jtcp::tcpopt_t::SELACK, tmphdr);
        mytcp->add_option(ProtocolPP::jtcp::tcpopt_t::SACK, tmphdr);
        mytcp->add_option(ProtocolPP::jtcp::tcpopt_t::TIMESTAMP, tmphdr);
    }

    void testicmpcov() {
        ProtocolPP::jicmpsa tmp;

        ProtocolPP::jicmpsa tmp2(tmp);

        std::shared_ptr<ProtocolPP::jicmpsa> tmp3 = std::make_shared<ProtocolPP::jicmpsa>(ProtocolPP::ENCAP,
                                                                                          ProtocolPP::ICMP,
                                                                                          ProtocolPP::TIMEXCEED,
                                                                                          ProtocolPP::TTLEXPIRE,
                                                                                          0xFF,
                                                                                          0xFF,
                                                                                          0x00,
                                                                                          0x0000,
                                                                                          0x0000,
                                                                                          0xA5A5A5A5,
                                                                                          ProtocolPP::jarray<uint8_t>(4,0xAA),
                                                                                          ProtocolPP::jarray<uint8_t>(4,0xCC));

        std::shared_ptr<ProtocolPP::jicmpsa> tmp4 = std::make_shared<ProtocolPP::jicmpsa>(ProtocolPP::ENCAP,
                                                                                          ProtocolPP::ICMPV6,
                                                                                          ProtocolPP::TIMEXCEED,
                                                                                          ProtocolPP::TTLEXPIRE,
                                                                                          0xFF,
                                                                                          0xFF,
                                                                                          0x00,
                                                                                          0x0000,
                                                                                          0x0000,
                                                                                          0xA5A5A5A5,
                                                                                          ProtocolPP::jarray<uint8_t>(4,0xAA),
                                                                                          ProtocolPP::jarray<uint8_t>(4,0xCC));

        ProtocolPP::jicmpsa tmp50(tmp3);

        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::NH, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::iana_t>(ProtocolPP::field_t::VERSION, ProtocolPP::ICMPV6);
        tmp4->set_field<ProtocolPP::iana_t>(ProtocolPP::field_t::NH, ProtocolPP::ICMPV6);
        tmp4->set_field<ProtocolPP::icmpmsg_t>(ProtocolPP::field_t::MESSAGE, ProtocolPP::TIMEXCEED);
        tmp4->set_field<ProtocolPP::icmpmsg_t>(ProtocolPP::field_t::NH, ProtocolPP::TIMEXCEED);
        tmp4->set_field<ProtocolPP::icmpcode_t>(ProtocolPP::field_t::CODE, ProtocolPP::TTLEXPIRE);
        tmp4->set_field<ProtocolPP::icmpcode_t>(ProtocolPP::field_t::NH, ProtocolPP::TTLEXPIRE);
        tmp4->set_field<ProtocolPP::icmpcode_t>(ProtocolPP::field_t::ICMPCODE, ProtocolPP::TTLEXPIRE);
        tmp4->set_field<ProtocolPP::icmpcode_t>(ProtocolPP::field_t::NH, ProtocolPP::TTLEXPIRE);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::DSECN, 0xFF);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::TTLHOP, 0xAA);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::FLAGS, 0xCC);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::NH, 0xAA);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::FRAGOFFSET, 0x001E);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::ID, 0x01CC);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::NH, 0x01CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::LABEL, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::NH, 0xA1CC);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SOURCE, ProtocolPP::jarray<uint8_t>("0xAABBCCDDAAAAAAAAAAAAAAAAAAAAAAAA"));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::DESTINATION, ProtocolPP::jarray<uint8_t>("0xEE11AABBFFFFFFFFFFFFFFFFFFFFFFFF"));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::NH, ProtocolPP::jarray<uint8_t>("0xEE11AABBFFFFFFFFFFFFFFFFFFFFFFFF"));

        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::NH);
        ProtocolPP::iana_t myver = tmp4->get_field<ProtocolPP::iana_t>(ProtocolPP::field_t::VERSION);
        myver = tmp4->get_field<ProtocolPP::iana_t>(ProtocolPP::field_t::NH);
        ProtocolPP::icmpmsg_t mymsg = tmp4->get_field<ProtocolPP::icmpmsg_t>(ProtocolPP::field_t::MESSAGE);
        mymsg = tmp4->get_field<ProtocolPP::icmpmsg_t>(ProtocolPP::field_t::NH);
        ProtocolPP::icmpcode_t mycode = tmp4->get_field<ProtocolPP::icmpcode_t>(ProtocolPP::field_t::CODE);
        mycode = tmp4->get_field<ProtocolPP::icmpcode_t>(ProtocolPP::field_t::NH);
        uint8_t mydsecn = tmp4->get_field<uint8_t>(ProtocolPP::field_t::DSECN);
        uint8_t myttl = tmp4->get_field<uint8_t>(ProtocolPP::field_t::TTLHOP);
        uint8_t myflags = tmp4->get_field<uint8_t>(ProtocolPP::field_t::FLAGS);
        myflags = tmp4->get_field<uint8_t>(ProtocolPP::field_t::NH);
        uint16_t myfragoff = tmp4->get_field<uint16_t>(ProtocolPP::field_t::FRAGOFFSET);
        uint16_t myid = tmp4->get_field<uint16_t>(ProtocolPP::field_t::ID);
        myid = tmp4->get_field<uint16_t>(ProtocolPP::field_t::NH);
        uint32_t mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::LABEL);
        mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::NH);
        ProtocolPP::jarray<uint8_t> mysrc = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SOURCE);
        ProtocolPP::jarray<uint8_t> mydst = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::DESTINATION);
        mydst = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::NH);

        ProtocolPP::jicmp tmp5(tmp3);
        ProtocolPP::jicmp tmp6(tmp4);

        // set header
        ProtocolPP::jarray<uint8_t> tmphdr(20,0);
        tmp5.set_hdr(tmphdr);

        // set fields
        tmp5.set_field(ProtocolPP::TYPE, 0xFF);
        tmp5.set_field(ProtocolPP::CODE, 0xFF);
        tmp5.set_field(ProtocolPP::CHECKSUM, 0xF0F0);
        tmp5.set_field(ProtocolPP::POINTER, 0xF0);
        tmp6.set_field(ProtocolPP::POINTER, 0xF0);
        tmp5.set_field(ProtocolPP::IDENTIFIER, 0xF0F0);
        tmp5.set_field(ProtocolPP::SEQNUM, 0xF0F0);
        tmp5.set_field(ProtocolPP::GATEWAY, 0xA5A5C3C3);
        tmp6.set_field(ProtocolPP::MTU, 0xA5A5C3C3);
        tmp5.set_field(ProtocolPP::ORIGTIMESTAMP, 0xA5A5C3C3);
        tmp5.set_field(ProtocolPP::RXTIMESTAMP, 0xA5A5C3C3);
        tmp5.set_field(ProtocolPP::TXTIMESTAMP, 0xA5A5C3C3);
        tmp5.set_field(ProtocolPP::MESSAGE, 0xA5);
        tmp6.set_field(ProtocolPP::MESSAGE, 0xA5);
        tmp5.set_field(ProtocolPP::ICMPCODE, 0xA5);
        tmp6.set_field(ProtocolPP::ICMPCODE, 0xA5);

        // get header
        tmphdr = tmp5.get_hdr();

        // get fields
        uint64_t myfield = 0;
        myfield = tmp6.get_field(ProtocolPP::VERSION, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::TYPE, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::CODE, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::CHECKSUM, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::POINTER, tmphdr);
        myfield = tmp6.get_field(ProtocolPP::POINTER, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::IDENTIFIER, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::SEQNUM, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::GATEWAY, tmphdr);
        myfield = tmp6.get_field(ProtocolPP::MTU, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::ORIGTIMESTAMP, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::RXTIMESTAMP, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::TXTIMESTAMP, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::SOURCE, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::DESTINATION, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::MESSAGE, tmphdr);
        myfield = tmp6.get_field(ProtocolPP::MESSAGE, tmphdr);
        myfield = tmp5.get_field(ProtocolPP::ICMPCODE, tmphdr);
        myfield = tmp6.get_field(ProtocolPP::ICMPCODE, tmphdr);

        // convert message
        uint8_t msg = 0;
        msg = tmp5.convmsg(ProtocolPP::DESTUNRCH);
        msg = tmp5.convmsg(ProtocolPP::SRCQNCH);
        msg = tmp5.convmsg(ProtocolPP::RDIRMSG);
        msg = tmp5.convmsg(ProtocolPP::ALTHOST);
        msg = tmp5.convmsg(ProtocolPP::ECHORQST);
        msg = tmp5.convmsg(ProtocolPP::RTRADVERT);
        msg = tmp5.convmsg(ProtocolPP::RTRSOLCIT);
        msg = tmp5.convmsg(ProtocolPP::TIMEXCEED);
        msg = tmp5.convmsg(ProtocolPP::BADIPHDR);
        msg = tmp5.convmsg(ProtocolPP::TIMESTMP);
        msg = tmp5.convmsg(ProtocolPP::TIMERPLY);
        msg = tmp5.convmsg(ProtocolPP::INFORQST);
        msg = tmp5.convmsg(ProtocolPP::INFORPLY);
        msg = tmp5.convmsg(ProtocolPP::ADMSKRQST);
        msg = tmp5.convmsg(ProtocolPP::ADMSKRPLY);
        msg = tmp5.convmsg(ProtocolPP::TRACERTE);
        msg = tmp5.convmsg(ProtocolPP::NODEST);
        msg = tmp5.convmsg(ProtocolPP::PKTBIG);
        msg = tmp5.convmsg(ProtocolPP::TIMEOUT);
        msg = tmp5.convmsg(ProtocolPP::PARAM);
        msg = tmp5.convmsg(ProtocolPP::PRVTE1);
        msg = tmp5.convmsg(ProtocolPP::PRVTE2);
        msg = tmp5.convmsg(ProtocolPP::RSVDE);
        msg = tmp5.convmsg(ProtocolPP::ECHORQSTV6);
        msg = tmp5.convmsg(ProtocolPP::ECHORPLYV6);
        msg = tmp5.convmsg(ProtocolPP::PRVTI1);
        msg = tmp5.convmsg(ProtocolPP::PRVTI2);
        msg = tmp5.convmsg(ProtocolPP::RSVDI);

        // convert code
        uint8_t code = 0;
        code = tmp5.convcode(ProtocolPP::ECHORPLY);
        code = tmp5.convcode(ProtocolPP::NONETWRK);
        code = tmp5.convcode(ProtocolPP::REDIRNETWK);
        code = tmp5.convcode(ProtocolPP::TTLEXPIRE);
        code = tmp5.convcode(ProtocolPP::PTRINDERR);
        code = tmp5.convcode(ProtocolPP::NOROUTE);
        code = tmp5.convcode(ProtocolPP::HOPLMTEXCD);
        code = tmp5.convcode(ProtocolPP::ERRHDRFIELD);
        code = tmp5.convcode(ProtocolPP::NOHOST);
        code = tmp5.convcode(ProtocolPP::REDIRHOST);
        code = tmp5.convcode(ProtocolPP::FRAGEXPIRE);
        code = tmp5.convcode(ProtocolPP::OPTERR);
        code = tmp5.convcode(ProtocolPP::COMMPROHIBV6);
        code = tmp5.convcode(ProtocolPP::FRAGTIME);
        code = tmp5.convcode(ProtocolPP::NXTHDRERR);
        code = tmp5.convcode(ProtocolPP::NOPROT);
        code = tmp5.convcode(ProtocolPP::REDIRTOSN);
        code = tmp5.convcode(ProtocolPP::BADLENGTH);
        code = tmp5.convcode(ProtocolPP::BYNDSRCADDR);
        code = tmp5.convcode(ProtocolPP::IPV6OPTERR);
        code = tmp5.convcode(ProtocolPP::NOPROT);
        code = tmp5.convcode(ProtocolPP::REDIRTOSH);
        code = tmp5.convcode(ProtocolPP::ADDRUNREACH);
        code = tmp5.convcode(ProtocolPP::FRAGRQD);
        code = tmp5.convcode(ProtocolPP::PORTUNREACH);
        code = tmp5.convcode(ProtocolPP::SRCADDRPLCY);
        code = tmp5.convcode(ProtocolPP::RTEFAIL);
        code = tmp5.convcode(ProtocolPP::DSTUNKNWN);
        code = tmp5.convcode(ProtocolPP::REJECTDST);
        code = tmp5.convcode(ProtocolPP::DSTHSTUNKNWN);
        code = tmp5.convcode(ProtocolPP::SRCHSTISOLT);
        code = tmp5.convcode(ProtocolPP::NETWKPROHIB);
        code = tmp5.convcode(ProtocolPP::HOSTPROHIB);
        code = tmp5.convcode(ProtocolPP::NETWKNOTOS);
        code = tmp5.convcode(ProtocolPP::HOSTNOTOS);
        code = tmp5.convcode(ProtocolPP::COMMPROHIB);
        code = tmp5.convcode(ProtocolPP::HOSTVILATE);
        code = tmp5.convcode(ProtocolPP::CUTOFF);
        code = tmp5.convcode(ProtocolPP::SEQNUMRST);
    }

    void testip4cov() {
        ProtocolPP::jipsa tmp;

        ProtocolPP::jipsa tmp2(tmp);

        std::shared_ptr<ProtocolPP::jipsa> tmp3 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV4,
                                                                                      ProtocolPP::TCP,
                                                                                      ProtocolPP::jarray<uint8_t>(4,0xAA),
                                                                                      ProtocolPP::jarray<uint8_t>(4,0xCC),
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> tmp4 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV6,
                                                                                      ProtocolPP::TCP,
                                                                                      ProtocolPP::jarray<uint8_t>(4,0xAA),
                                                                                      ProtocolPP::jarray<uint8_t>(4,0xCC),
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        ProtocolPP::jipsa tmp51(tmp3);

        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::NH, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::iana_t>(ProtocolPP::field_t::VERSION, ProtocolPP::IPV6);
        tmp4->set_field<ProtocolPP::iana_t>(ProtocolPP::field_t::NH, ProtocolPP::RSVP);
        tmp4->set_field<ProtocolPP::iana_t>(ProtocolPP::field_t::CODE, ProtocolPP::IPV6);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::DSECN, 0xFF);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::TTLHOP, 0xAA);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::FLAGS, 0xCC);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::NH, 0xCC);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::FRAGOFFSET, 0x001E);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::ID, 0x01CC);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::NH, 0x01CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::LABEL, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::MTU, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::NH, 0xA1CC);
        tmp4->set_field<bool>(ProtocolPP::field_t::NODEJUMBO, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::NH, true);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SOURCE, ProtocolPP::jarray<uint8_t>("0xAABBCCDDAAAAAAAAAAAAAAAAAAAAAAAA"));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::DESTINATION, ProtocolPP::jarray<uint8_t>("0xEE11AABBFFFFFFFFFFFFFFFFFFFFFFFF"));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::EXTHDR, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::NH, ProtocolPP::jarray<uint8_t>(0));

        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION);
        ProtocolPP::direction_t mydir2 = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::NH);
        ProtocolPP::iana_t myver = tmp4->get_field<ProtocolPP::iana_t>(ProtocolPP::field_t::VERSION);
        ProtocolPP::iana_t mymsg = tmp4->get_field<ProtocolPP::iana_t>(ProtocolPP::field_t::NH);
        ProtocolPP::iana_t mycode = tmp4->get_field<ProtocolPP::iana_t>(ProtocolPP::field_t::CODE);
        uint8_t mydsecn = tmp4->get_field<uint8_t>(ProtocolPP::field_t::DSECN);
        uint8_t myttl = tmp4->get_field<uint8_t>(ProtocolPP::field_t::TTLHOP);
        uint8_t myflags = tmp4->get_field<uint8_t>(ProtocolPP::field_t::FLAGS);
        uint8_t mymy = tmp4->get_field<uint8_t>(ProtocolPP::field_t::NH);
        uint16_t myfragoff = tmp4->get_field<uint16_t>(ProtocolPP::field_t::FRAGOFFSET);
        uint16_t myid = tmp4->get_field<uint16_t>(ProtocolPP::field_t::ID);
        uint16_t myid2 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::NH);
        uint32_t mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::LABEL);
        uint32_t mylabel3 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::MTU);
        uint32_t mylabel2 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::NH);
        bool myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::NODEJUMBO);
        bool myjumbo2 = tmp4->get_field<bool>(ProtocolPP::field_t::NH);
        ProtocolPP::jarray<uint8_t> mysrc = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SOURCE);
        ProtocolPP::jarray<uint8_t> mydst = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::DESTINATION);
        ProtocolPP::jarray<uint8_t> myext = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::EXTHDR);
        ProtocolPP::jarray<uint8_t> myext2 = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::NH);

        std::string mystr("./mylog.log");
        ProtocolPP::jip engine(tmp3);
        ProtocolPP::jip engine2(tmp4);
        ProtocolPP::jip engine3(tmp4, mystr);
        ProtocolPP::jip engine4(tmp3, mystr);

        ProtocolPP::jarray<uint8_t> newhdr(20, 0x11);
        engine.set_hdr(newhdr);
        engine.set_exthdr(newhdr);

        // set field
        engine.set_field(ProtocolPP::VERSION, 4);
        engine.set_field(ProtocolPP::DSECN, 32);
        engine2.set_field(ProtocolPP::DSECN, 32);
        engine.set_field(ProtocolPP::ID, 123456);
        engine2.set_field(ProtocolPP::ID, 123456);
        engine.set_field(ProtocolPP::LABEL, 125);
        engine2.set_field(ProtocolPP::LABEL, 125);
        engine.set_field(ProtocolPP::NH, 54);
        engine2.set_field(ProtocolPP::NH, 54);
        engine.set_field(ProtocolPP::LENGTH, 128);
        engine2.set_field(ProtocolPP::LENGTH, 128);
        engine.set_field(ProtocolPP::CHECKSUM, 100);
        engine2.set_field(ProtocolPP::CHECKSUM, 100);

        // get extension header
        ProtocolPP::jarray<uint8_t> rtehdr(32,0xFF);
        rtehdr = engine2.format_exthdr(ProtocolPP::IPV6_ROUTE,
                                        ProtocolPP::ESP,
                                        rtehdr,
                                        0xFFEE,
                                        1);

        rtehdr = ProtocolPP::jarray<uint8_t>(4,0xFF);
        rtehdr = engine2.format_exthdr(ProtocolPP::IPV6_FRAG,
                                        ProtocolPP::ESP,
                                        rtehdr,
                                        0xFFEE,
                                        1);

        rtehdr = ProtocolPP::jarray<uint8_t>(8,0xFF);
        rtehdr = engine2.format_exthdr(ProtocolPP::IPV6_OPTS,
                                        ProtocolPP::ESP,
                                        rtehdr,
                                        0xFFEE,
                                        1);

        // get hdr
        ProtocolPP::jarray<uint8_t> myhdr = engine.get_hdr();
        myhdr = engine.get_exthdr();

        // get fields
        uint64_t field = engine.get_field(ProtocolPP::VERSION, myhdr);
        field = engine2.get_field(ProtocolPP::VERSION, myhdr);
        field = engine.get_field(ProtocolPP::DSECN, myhdr);
        field = engine2.get_field(ProtocolPP::DSECN, myhdr);
        field = engine.get_field(ProtocolPP::ID, myhdr);
        field = engine2.get_field(ProtocolPP::ID, myhdr);
        field = engine.get_field(ProtocolPP::LABEL, myhdr);
        field = engine2.get_field(ProtocolPP::LABEL, myhdr);
        field = engine.get_field(ProtocolPP::NH, myhdr);
        field = engine2.get_field(ProtocolPP::NH, myhdr);
        field = engine.get_field(ProtocolPP::LENGTH, myhdr);
        field = engine2.get_field(ProtocolPP::LENGTH, myhdr);
        field = engine.get_field(ProtocolPP::CHECKSUM, myhdr);
        field = engine2.get_field(ProtocolPP::CHECKSUM, myhdr);
        field = engine.get_field(ProtocolPP::TTLHOP, myhdr);
        field = engine2.get_field(ProtocolPP::TTLHOP, myhdr);
        field = engine.get_field(ProtocolPP::FRAGOFFSET, myhdr);
        field = engine.get_field(ProtocolPP::FLAGS, myhdr);
        field = engine2.get_field(ProtocolPP::FRAGOFFSET, myhdr);

        // get fields
        uint64_t field2 = engine.get_field(ProtocolPP::VERSION);
        field2 = engine.get_field(ProtocolPP::DSECN);
        field2 = engine2.get_field(ProtocolPP::DSECN);
        field2 = engine.get_field(ProtocolPP::ID);
        field2 = engine2.get_field(ProtocolPP::ID);
        field2 = engine.get_field(ProtocolPP::LABEL);
        field2 = engine2.get_field(ProtocolPP::LABEL);
        field2 = engine.get_field(ProtocolPP::NH);
        field2 = engine2.get_field(ProtocolPP::NH);
        field2 = engine.get_field(ProtocolPP::LENGTH);
        field2 = engine2.get_field(ProtocolPP::LENGTH);
        field2 = engine.get_field(ProtocolPP::CHECKSUM);
        field2 = engine2.get_field(ProtocolPP::CHECKSUM);
        field2 = engine.get_field(ProtocolPP::TTLHOP);
        field2 = engine.get_field(ProtocolPP::FLAGS);
        field2 = engine.get_field(ProtocolPP::FRAGOFFSET);
        field2 = engine2.get_field(ProtocolPP::FRAGOFFSET);
    }

    void testipseccov() {
        ProtocolPP::jipsecsa tmp;

        ProtocolPP::jipsecsa tmp2(tmp);

        uint32_t ipspi = myrand->get_u32();
        
        std::shared_ptr<ProtocolPP::jipsecsa> tmp3 = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::ENCAP,
                                                                                            ProtocolPP::IPV4,
                                                                                            ProtocolPP::TUNNEL,
                                                                                            ipspi,
                                                                                            1,
                                                                                            1,
                                                                                            128,
                                                                                            ProtocolPP::jarray<uint8_t>(0),
                                                                                            ProtocolPP::AES_CBC,
                                                                                            16,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xEE),
                                                                                            ProtocolPP::SHA256,
                                                                                            32,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(32,0xCC),
                                                                                            16,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16)),
                                                                                            0,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                            0,
                                                                                            0xFFFFFFFF,
                                                                                            false,
                                                                                            false,
                                                                                            false,
                                                                                            false,
                                                                                            false,
                                                                                            false,
                                                                                            0,
                                                                                            0xFF,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            false,
                                                                                            0,
                                                                                            1500,
                                                                                            ProtocolPP::jarray<uint8_t>(4,0xAA),
                                                                                            ProtocolPP::jarray<uint8_t>(4,0xCC),
                                                                                            ProtocolPP::jarray<uint8_t>(0),
                                                                                            ProtocolPP::IPV4,
                                                                                            32,
                                                                                            20,
                                                                                            0,
                                                                                            true,
                                                                                            false,
                                                                                            true,
                                                                                            true,
                                                                                            std::string("./myaudit.log"));

        std::shared_ptr<ProtocolPP::jipsecsa> tmp4 = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::DECAP,
                                                                                            ProtocolPP::IPV6,
                                                                                            ProtocolPP::TUNNEL,
                                                                                            ipspi,
                                                                                            1,
                                                                                            1,
                                                                                            128,
                                                                                            ProtocolPP::jarray<uint8_t>(myrand->getbyte(16)),
                                                                                            ProtocolPP::AES_CBC,
                                                                                            16,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xEE),
                                                                                            ProtocolPP::SHA256,
                                                                                            32,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(32,0xCC),
                                                                                            16,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16)),
                                                                                            0,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                            0,
                                                                                            0xFFFFFFFF,
                                                                                            false,
                                                                                            false,
                                                                                            false,
                                                                                            false,
                                                                                            false,
                                                                                            false,
                                                                                            0,
                                                                                            0xFF,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            false,
                                                                                            0,
                                                                                            1500,
                                                                                            ProtocolPP::jarray<uint8_t>(16,0xAA),
                                                                                            ProtocolPP::jarray<uint8_t>(16,0xCC),
                                                                                            ProtocolPP::jarray<uint8_t>(0),
                                                                                            ProtocolPP::IPV4,
                                                                                            32,
                                                                                            20,
                                                                                            0,
                                                                                            true,
                                                                                            false,
                                                                                            true,
                                                                                            true,
                                                                                            std::string("./myaudit6.log"));

        ProtocolPP::jipsecsa tmp52(tmp3);

        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::NH, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::iana_t>(ProtocolPP::field_t::VERSION, ProtocolPP::IPV6);
        tmp4->set_field<ProtocolPP::iana_t>(ProtocolPP::field_t::NH, ProtocolPP::RSVP);
        tmp4->set_field<ProtocolPP::iana_t>(ProtocolPP::field_t::CODE, ProtocolPP::IPV6);
        tmp4->set_field<ProtocolPP::ipmode_t>(ProtocolPP::field_t::MODE, ProtocolPP::TRANSPORT);
        tmp4->set_field<ProtocolPP::ipmode_t>(ProtocolPP::field_t::NH, ProtocolPP::TRANSPORT);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::ARIA_CBC);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::NH, ProtocolPP::ARIA_CBC);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH, ProtocolPP::SHA512);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::NH, ProtocolPP::SHA512);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::DSECN, 0xFF);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::TTLHOP, 0xAA);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::FLAGS, 0xCC);
        tmp4->set_field<uint8_t>(ProtocolPP::field_t::NH, 0xCC);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::NATSRC, 0x001E);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::NATDST, 0x001E);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::FRAGOFFSET, 0x001E);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::ID, 0x01CC);
        tmp4->set_field<uint16_t>(ProtocolPP::field_t::NH, 0x01CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::SPI, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::FRAGID, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::CKEYLEN, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::AKEYLEN, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::SALTLEN, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::HDRLEN, 40);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::TFCLEN, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::LABEL, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::MTU, 0xA1CC);
        tmp4->set_field<uint32_t>(ProtocolPP::field_t::NH, 0xA1CC);
        tmp4->set_field<uint64_t>(ProtocolPP::field_t::BYTECNT, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::field_t::LIFETIME, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::field_t::NH, 0);
        tmp4->set_field<bool>(ProtocolPP::field_t::SEQNUMOVRFLW, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::STATEFULFRAG, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::BYPASSDF, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::BYPASSDSCP, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::NAT, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::NCHK, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::USEXT, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::RANDIV, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::NODEJUMBO, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::AUDIT, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::MOREFRAG, true);
        tmp4->set_field<bool>(ProtocolPP::field_t::NH, true);
        tmp4->set_field<std::string>(ProtocolPP::field_t::AUDITLOG, std::string("./myauditlog6.log"));
        tmp4->set_field<std::string>(ProtocolPP::field_t::DIRECTION, std::string("./mylog.log"));
        ProtocolPP::jarray<uint8_t> src2("0xAABBCCDDAAAAAAAAAAAAAAAAAAAAAAAA");
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SOURCE, src2);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::DESTINATION, ProtocolPP::jarray<uint8_t>("0xEE11AABBFFFFFFFFFFFFFFFFFFFFFFFF"));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::EXTHDR, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::NH, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>("0xAABBCCDDAAAAAAAAAAAAAAAAAAAAAAAA"));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>("0xAABBCCDDAAAAAAAAAAAAAAAAAAAAAAAA"));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, std::make_shared<ProtocolPP::jarray<uint8_t>>("0xAABBCCDDAAAAAAAAAAAAAAAAAAAAAAAA"));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::NH, std::make_shared<ProtocolPP::jarray<uint8_t>>("0xAABBCCDDAAAAAAAAAAAAAAAAAAAAAAAA"));

        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION);
        ProtocolPP::direction_t mydir2 = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::NH);
        ProtocolPP::iana_t myver = tmp4->get_field<ProtocolPP::iana_t>(ProtocolPP::field_t::VERSION);
        ProtocolPP::iana_t mymsg = tmp4->get_field<ProtocolPP::iana_t>(ProtocolPP::field_t::NH);
        ProtocolPP::iana_t mycode = tmp4->get_field<ProtocolPP::iana_t>(ProtocolPP::field_t::CODE);
        ProtocolPP::ipmode_t mymode = tmp4->get_field<ProtocolPP::ipmode_t>(ProtocolPP::field_t::MODE);
        mymode = tmp4->get_field<ProtocolPP::ipmode_t>(ProtocolPP::field_t::NH);
        ProtocolPP::cipher_t mycipher = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER);
        mycipher = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::NH);
        ProtocolPP::auth_t myauth = tmp4->get_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH);
        myauth = tmp4->get_field<ProtocolPP::auth_t>(ProtocolPP::field_t::NH);
        uint8_t mydsecn = tmp4->get_field<uint8_t>(ProtocolPP::field_t::DSECN);
        uint8_t myttl = tmp4->get_field<uint8_t>(ProtocolPP::field_t::TTLHOP);
        uint8_t myflags = tmp4->get_field<uint8_t>(ProtocolPP::field_t::FLAGS);
        uint8_t mymy = tmp4->get_field<uint8_t>(ProtocolPP::field_t::NH);
        uint16_t myfragoff = tmp4->get_field<uint16_t>(ProtocolPP::field_t::FRAGOFFSET);
        myfragoff = tmp4->get_field<uint16_t>(ProtocolPP::field_t::NATSRC);
        myfragoff = tmp4->get_field<uint16_t>(ProtocolPP::field_t::NATDST);
        uint16_t myid = tmp4->get_field<uint16_t>(ProtocolPP::field_t::ID);
        uint16_t myid2 = tmp4->get_field<uint16_t>(ProtocolPP::field_t::NH);
        uint32_t mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::LABEL);
        mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::SPI);
        mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::FRAGID);
        mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::CKEYLEN);
        mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::AKEYLEN);
        mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::SALTLEN);
        mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::HDRLEN);
        mylabel = tmp4->get_field<uint32_t>(ProtocolPP::field_t::TFCLEN);
        uint32_t mylabel3 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::MTU);
        uint32_t mylabel2 = tmp4->get_field<uint32_t>(ProtocolPP::field_t::NH);
        uint64_t mybyte = tmp4->get_field<uint64_t>(ProtocolPP::field_t::BYTECNT);
        mybyte = tmp4->get_field<uint64_t>(ProtocolPP::field_t::LIFETIME);
        mybyte = tmp4->get_field<uint64_t>(ProtocolPP::field_t::NH);
        bool myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::NODEJUMBO);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::SEQNUMOVRFLW);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::STATEFULFRAG);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::BYPASSDF);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::BYPASSDSCP);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::NAT);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::NCHK);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::USEXT);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::RANDIV);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::NODEJUMBO);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::AUDIT);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::MOREFRAG);
        myjumbo = tmp4->get_field<bool>(ProtocolPP::field_t::NH);
        std::string mystr = tmp4->get_field<std::string>(ProtocolPP::field_t::AUDITLOG);
        mystr = tmp4->get_field<std::string>(ProtocolPP::field_t::AUDIT);
        ProtocolPP::jarray<uint8_t> mysrc = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SOURCE);
        ProtocolPP::jarray<uint8_t> mydst = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::DESTINATION);
        ProtocolPP::jarray<uint8_t> myext = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::EXTHDR);
        ProtocolPP::jarray<uint8_t> myext2 = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::NH);

        std::shared_ptr<ProtocolPP::jrand> myrand = std::make_shared<ProtocolPP::jrand>(0x1122334455667788);
        ProtocolPP::jipsec engine(myrand,tmp3,myreplay);
        ProtocolPP::jipsec engine2(myrand,tmp4,myreplay);

        ProtocolPP::jarray<uint8_t> newhdr(20, 0x11);
        engine.set_hdr(newhdr);

        // set field
        engine.set_field(ProtocolPP::VERSION, 4);
        engine.set_field(ProtocolPP::DSECN, 0);
        engine2.set_field(ProtocolPP::DSECN, 0);
        engine.set_field(ProtocolPP::ID, 0);
        engine2.set_field(ProtocolPP::ID, 0);
        engine.set_field(ProtocolPP::LABEL, 0);
        engine2.set_field(ProtocolPP::LABEL, 0);
        engine.set_field(ProtocolPP::NH, 0);
        engine2.set_field(ProtocolPP::NH, 0);
        engine.set_field(ProtocolPP::LENGTH, 0);
        engine2.set_field(ProtocolPP::LENGTH, 0);
        engine.set_field(ProtocolPP::CHECKSUM, 0);
        engine2.set_field(ProtocolPP::CHECKSUM, 0);

        // get extension header
        ProtocolPP::jarray<uint8_t> rtehdr(4,0xFF);
        rtehdr = engine2.get_exthdr(ProtocolPP::JUMBOGRAM,
                                    ProtocolPP::ESP,
                                    rtehdr,
                                    0xFFEE,
                                    1);

        rtehdr = ProtocolPP::jarray<uint8_t>(32,0xFF);
        rtehdr = engine2.get_exthdr(ProtocolPP::IPV6_ROUTE,
                                    ProtocolPP::ESP,
                                    rtehdr,
                                    0xFFEE,
                                    1);

        rtehdr = ProtocolPP::jarray<uint8_t>(4,0xFF);
        rtehdr = engine2.get_exthdr(ProtocolPP::IPV6_FRAG,
                                    ProtocolPP::ESP,
                                    rtehdr,
                                    0xFFEE,
                                    1);

        rtehdr = ProtocolPP::jarray<uint8_t>(8,0xFF);
        rtehdr = engine2.get_exthdr(ProtocolPP::IPV6_OPTS,
                                    ProtocolPP::ESP,
                                    rtehdr,
                                    0xFFEE,
                                    1);

        // get hdr
        ProtocolPP::jarray<uint8_t> myhdr = engine.get_hdr();
        ProtocolPP::jarray<uint8_t> myhdr6 = engine2.get_hdr();

        // get fields
        uint64_t field = engine.get_field(ProtocolPP::VERSION, myhdr);
        field = engine.get_field(ProtocolPP::DSECN, myhdr);
        field = engine2.get_field(ProtocolPP::DSECN, myhdr);
        field = engine.get_field(ProtocolPP::ID, myhdr);
        field = engine2.get_field(ProtocolPP::ID, myhdr);
        field = engine.get_field(ProtocolPP::LABEL, myhdr);
        field = engine2.get_field(ProtocolPP::LABEL, myhdr);
        field = engine.get_field(ProtocolPP::NH, myhdr);
        field = engine2.get_field(ProtocolPP::NH, myhdr);
        field = engine.get_field(ProtocolPP::LENGTH, myhdr);
        field = engine2.get_field(ProtocolPP::LENGTH, myhdr);
        field = engine.get_field(ProtocolPP::CHECKSUM, myhdr);
        field = engine2.get_field(ProtocolPP::CHECKSUM, myhdr);
        field = engine.get_field(ProtocolPP::TTLHOP, myhdr);
        field = engine2.get_field(ProtocolPP::TTLHOP, myhdr);
        field = engine.get_field(ProtocolPP::FRAGOFFSET, myhdr);
        field = engine2.get_field(ProtocolPP::FRAGOFFSET, myhdr);
        field = engine.get_field(ProtocolPP::SEQNUM, myhdr);
        field = engine.get_field(ProtocolPP::EXTSEQNUM, myhdr);

        // get fields
        uint64_t field2 = engine.get_field(ProtocolPP::VERSION);
        field2 = engine.get_field(ProtocolPP::DSECN);
        field2 = engine2.get_field(ProtocolPP::DSECN);
        field2 = engine.get_field(ProtocolPP::ID);
        field2 = engine2.get_field(ProtocolPP::ID);
        field2 = engine.get_field(ProtocolPP::LABEL);
        field2 = engine2.get_field(ProtocolPP::LABEL);
        field2 = engine.get_field(ProtocolPP::NH);
        field2 = engine2.get_field(ProtocolPP::NH);
        field2 = engine.get_field(ProtocolPP::LENGTH);
        field2 = engine2.get_field(ProtocolPP::LENGTH);
        field2 = engine.get_field(ProtocolPP::CHECKSUM);
        field2 = engine2.get_field(ProtocolPP::CHECKSUM);
        field2 = engine.get_field(ProtocolPP::TTLHOP);
        field2 = engine.get_field(ProtocolPP::FLAGS);
        field2 = engine.get_field(ProtocolPP::SEQNUM);
        field2 = engine.get_field(ProtocolPP::EXTSEQNUM);
        field2 = engine2.get_field(ProtocolPP::SEQNUM);
        field2 = engine2.get_field(ProtocolPP::EXTSEQNUM);
        field2 = engine.get_field(ProtocolPP::FRAGOFFSET);
        field2 = engine2.get_field(ProtocolPP::FRAGOFFSET);

        // audit types
        engine.audit(ProtocolPP::jipsec::audit_t::AUDIT_INVALIDSA, myhdr);
        engine2.audit(ProtocolPP::jipsec::audit_t::AUDIT_FRAGMENT, myhdr6);
        engine.audit(ProtocolPP::jipsec::audit_t::AUDIT_ROLLOVER, myhdr);
        engine2.audit(ProtocolPP::jipsec::audit_t::AUDIT_REPLAY, myhdr6);
        engine.audit(ProtocolPP::jipsec::audit_t::AUDIT_ICV, myhdr);
        engine2.audit(ProtocolPP::jipsec::audit_t::AUDIT_FORMAT, myhdr6);
        engine.audit(ProtocolPP::jipsec::audit_t::AUDIT_DUMMY, myhdr);

        // check padding types
        ProtocolPP::jarray<uint8_t> pad = engine.pad(ProtocolPP::ZERO, 20);
        pad = engine.pad(ProtocolPP::INCREMENT, 20);
        pad = engine.pad(ProtocolPP::SIZE, 20);
        pad = engine.pad(ProtocolPP::RANDOM, 20);
        pad = engine.pad(ProtocolPP::UNKNWN, 20);

        // check string status
        std::string strstat;
        strstat = engine.str_status(0x000F0000);
        strstat = engine.str_status(0x010E0001);
        strstat = engine.str_status(0x020D0002);
        strstat = engine.str_status(0x030C0003);
        strstat = engine.str_status(0x040B0004);
        strstat = engine.str_status(0x050A0005);
        strstat = engine.str_status(0x06090006);
        strstat = engine.str_status(0x07080007);
        strstat = engine.str_status(0x08070008);
        strstat = engine.str_status(0x09060009);
        strstat = engine.str_status(0x0A05000A);
        strstat = engine.str_status(0x0B04000B);
        strstat = engine.str_status(0x0C03000C);
        strstat = engine.str_status(0x0D02000D);
        strstat = engine.str_status(0x0E01000E);
        strstat = engine.str_status(0x0F00000F);
        strstat = engine.str_status(0x101F0010);
        strstat = engine.str_status(0x112F0011);
        strstat = engine.str_status(0x123F0012);
        strstat = engine.str_status(0x134F0013);
        strstat = engine.str_status(0x145F0014);
        strstat = engine.str_status(0x156F0015);
        strstat = engine.str_status(0x167F0016);
        strstat = engine.str_status(0x178F0017);
        strstat = engine.str_status(0x189F0018);
        strstat = engine.str_status(0x19AF0019);
        strstat = engine.str_status(0x1ABF001A);
        strstat = engine.str_status(0x1BCF001B);
        strstat = engine.str_status(0x1CDF001C);
        strstat = engine.str_status(0x1DEF001D);
        strstat = engine.str_status(0x1EFF001E);
        strstat = engine.str_status(0x1F10001F);
        strstat = engine.str_status(0x1F110020);
        strstat = engine.str_status(0x1F120021);
        strstat = engine.str_status(0x1F130022);
        strstat = engine.str_status(0x1F140023);
        strstat = engine.str_status(0x1F150024);
        strstat = engine.str_status(0x1F160025);
        strstat = engine.str_status(0x1F170026);
        strstat = engine.str_status(0x1F180027);
        strstat = engine.str_status(0x1F190028);
        strstat = engine.str_status(0x1F1A0029);
        strstat = engine.str_status(0x1F1B002A);
        strstat = engine.str_status(0x1F1C002B);
        strstat = engine.str_status(0x1F1D002C);
        strstat = engine.str_status(0x1F1E002D);
        strstat = engine.str_status(0x1F1F002E);
        strstat = engine.str_status(0x1F20002E);
        strstat = engine.str_status(0x1F21002E);
        strstat = engine.str_status(0x1F22002E);
        strstat = engine.str_status(0x1F23002E);
        strstat = engine.str_status(0x1F24002E);
        strstat = engine.str_status(0x1F25002E);
        strstat = engine.str_status(0x1F26002E);
        strstat = engine.str_status(0x1F27002E);
        strstat = engine.str_status(0x1F28002E);
        strstat = engine.str_status(0x1F29002E);
        strstat = engine.str_status(0x1F2A002E);
        strstat = engine.str_status(0x1F2B002E);
        strstat = engine.str_status(0x1F2C002E);
        strstat = engine.str_status(0x1F2D002E);
        strstat = engine.str_status(0x1F2E002E);
        strstat = engine.str_status(0x1F2F002E);
        strstat = engine.str_status(0x1F30002E);
    }

    void testmaccov() {
        ProtocolPP::jmacsecsa tmp;
        ProtocolPP::jmacsecsa tmp2(tmp);
        std::shared_ptr<ProtocolPP::jmacsecsa> tmp3 = std::make_shared<ProtocolPP::jmacsecsa>(ProtocolPP::DECAP,
                                                                                              ProtocolPP::AES_GCM_256,
                                                                                              true,
                                                                                              true,
                                                                                              true,
                                                                                              false,
                                                                                              true,
                                                                                              0,
                                                                                              0,
                                                                                              0,
                                                                                              0,
                                                                                              0,
                                                                                              1,
                                                                                              1,
                                                                                              0,
                                                                                              0,
                                                                                              8,
                                                                                              32,
                                                                                              2,
                                                                                              3,
                                                                                              4,
                                                                                              ProtocolPP::jarray<uint8_t>(0),
                                                                                              std::make_shared<ProtocolPP::jarray<uint8_t>>(32,0),
                                                                                              std::make_shared<ProtocolPP::jarray<uint8_t>>(4,0));

        std::shared_ptr<ProtocolPP::jmacsecsa> tmp4 = std::make_shared<ProtocolPP::jmacsecsa>(ProtocolPP::ENCAP,
                                                                                              ProtocolPP::AES_GCM_256,
                                                                                              true,
                                                                                              true,
                                                                                              false,
                                                                                              true,
                                                                                              true,
                                                                                              0,
                                                                                              0,
                                                                                              0,
                                                                                              0,
                                                                                              0,
                                                                                              1,
                                                                                              1,
                                                                                              0,
                                                                                              0,
                                                                                              8,
                                                                                              32,
                                                                                              2,
                                                                                              3,
                                                                                              4,
                                                                                              ProtocolPP::jarray<uint8_t>(0),
                                                                                              std::make_shared<ProtocolPP::jarray<uint8_t>>(32,0),
                                                                                              std::make_shared<ProtocolPP::jarray<uint8_t>>(4,0));

        std::shared_ptr<ProtocolPP::jmacsecsa> tmp104(tmp3);

        // set field
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::macsecmode_t>(ProtocolPP::MODE, ProtocolPP::AES_GCM_256);
        tmp4->set_field<ProtocolPP::macsecmode_t>(ProtocolPP::NH, ProtocolPP::AES_GCM_256);
        tmp4->set_field<std::string>(ProtocolPP::CREATETIME, std::string("CREATEME"));
        tmp4->set_field<std::string>(ProtocolPP::STARTTIME, std::string("STARTME"));
        tmp4->set_field<std::string>(ProtocolPP::STOPTIME, std::string("STOPME"));
        tmp4->set_field<std::string>(ProtocolPP::CIPHER, std::string("CREATEME"));
        tmp4->set_field<bool>(ProtocolPP::USEXT, false);
        tmp4->set_field<bool>(ProtocolPP::ENTRANSMIT, false);
        tmp3->set_field<bool>(ProtocolPP::ENRECEIVE, false);
        tmp3->set_field<bool>(ProtocolPP::PROTECTFRAMES, false);
        tmp4->set_field<bool>(ProtocolPP::NH, false);
        tmp4->set_field<uint8_t>(ProtocolPP::TCIAN, 0xFF);
        tmp4->set_field<uint8_t>(ProtocolPP::SL, 0xFF);
        tmp4->set_field<uint8_t>(ProtocolPP::NH, 0xFF);
        tmp4->set_field<uint16_t>(ProtocolPP::ETHERTYPE, 0x88FF);
        tmp4->set_field<uint16_t>(ProtocolPP::NH, 0x88FF);
        tmp4->set_field<uint32_t>(ProtocolPP::PN, 1);
        tmp4->set_field<uint32_t>(ProtocolPP::XPN, 1);
        tmp4->set_field<uint32_t>(ProtocolPP::SSCI, 1);
        tmp4->set_field<uint32_t>(ProtocolPP::ARLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::ICVLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::SOURCE, 0xAAAA);
        tmp4->set_field<uint64_t>(ProtocolPP::DESTINATION, 0xFFFF);
        tmp4->set_field<uint64_t>(ProtocolPP::SCI, 0xFFFF);
        tmp4->set_field<uint64_t>(ProtocolPP::NH, 0xFFFF);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SAKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SALT, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));

        // get field
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::macsecmode_t mymode = tmp4->get_field<ProtocolPP::macsecmode_t>(ProtocolPP::MODE);
        mymode = tmp4->get_field<ProtocolPP::macsecmode_t>(ProtocolPP::NH);
        bool mybool = tmp4->get_field<bool>(ProtocolPP::USEXT);
        mybool = tmp4->get_field<bool>(ProtocolPP::ENTRANSMIT);
        mybool = tmp3->get_field<bool>(ProtocolPP::ENRECEIVE);
        mybool = tmp3->get_field<bool>(ProtocolPP::PROTECTFRAMES);
        mybool = tmp3->get_field<bool>(ProtocolPP::INUSE);
        mybool = tmp4->get_field<bool>(ProtocolPP::NH);
        uint8_t my8 = tmp4->get_field<uint8_t>(ProtocolPP::TCIAN);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::SL);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::NH);
        uint16_t my16 = tmp4->get_field<uint16_t>(ProtocolPP::ETHERTYPE);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::NH);
        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::PN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::XPN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::SSCI);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ARLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ICVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::VLANTAG1);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::VLANTAG2);
        uint64_t my64 = tmp4->get_field<uint64_t>(ProtocolPP::SOURCE);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::DESTINATION);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::SCI);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SAKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SALT);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);

        ProtocolPP::jarray<uint8_t> tmphdr(20,0x33);
        std::shared_ptr<ProtocolPP::jrand> myrand = std::make_shared<ProtocolPP::jrand>(0x1122334455667788);
        std::shared_ptr<ProtocolPP::jmacsec> myms = std::make_shared<ProtocolPP::jmacsec>(myrand, tmp4, myreplay);
        std::shared_ptr<ProtocolPP::jmacsec> mymd = std::make_shared<ProtocolPP::jmacsec>(myrand, tmp3, myreplay);
        myms->set_hdr(tmphdr);
        tmphdr = myms->get_hdr();
        my64 = myms->get_field(ProtocolPP::SOURCE, tmphdr);
        my64 = myms->get_field(ProtocolPP::DESTINATION, tmphdr);
        my64 = myms->get_field(ProtocolPP::BYTECNT, tmphdr);

        my64 = myms->get_field(ProtocolPP::SOURCE);
        my64 = myms->get_field(ProtocolPP::DESTINATION);
        my64 = myms->get_field(ProtocolPP::MODE);
        my64 = myms->get_field(ProtocolPP::DIRECTION);
        my64 = myms->get_field(ProtocolPP::ARLEN);
        my64 = myms->get_field(ProtocolPP::ICVLEN);
        my64 = myms->get_field(ProtocolPP::USEXT);
        my64 = myms->get_field(ProtocolPP::AKEYLEN);
        my64 = myms->get_field(ProtocolPP::CKEYLEN);
        my64 = myms->get_field(ProtocolPP::ENTRANSMIT);
        my64 = mymd->get_field(ProtocolPP::ENRECEIVE);
        my64 = mymd->get_field(ProtocolPP::INUSE);
        my64 = mymd->get_field(ProtocolPP::PROTECTFRAMES);
        my64 = mymd->get_field(ProtocolPP::CREATETIME);
        my64 = mymd->get_field(ProtocolPP::STARTTIME);
        my64 = mymd->get_field(ProtocolPP::STOPTIME);
        my64 = mymd->get_field(ProtocolPP::CIPHER);

        // set field
        myms->set_field(ProtocolPP::ETHERTYPE, 0);
        myms->set_field(ProtocolPP::TCIAN, 0);
        myms->set_field(ProtocolPP::SL, 0);
        myms->set_field(ProtocolPP::PN, 0);
        myms->set_field(ProtocolPP::XPN, 0);
        myms->set_field(ProtocolPP::SCI, 0);
        myms->set_field(ProtocolPP::SSCI, 0);
        myms->set_field(ProtocolPP::ENTRANSMIT, 1);
        mymd->set_field(ProtocolPP::ENRECEIVE, 1);
        myms->set_field(ProtocolPP::ENTRANSMIT, 0);
        mymd->set_field(ProtocolPP::ENRECEIVE, 0);
        mymd->set_field(ProtocolPP::PROTECTFRAMES, 0);
        mymd->set_field(ProtocolPP::PROTECTFRAMES, 1);

        std::shared_ptr<ProtocolPP::jmacsecsa> tmp444(tmp4);
        tmp444->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::DECAP);
        tmp444->set_field(ProtocolPP::INUSE, false);
        std::shared_ptr<ProtocolPP::jmacsec> myms2 = std::make_shared<ProtocolPP::jmacsec>(myrand, tmp444, myreplay);
        myms2->set_field(ProtocolPP::ENRECEIVE, 1);
        myms2->set_field(ProtocolPP::ENRECEIVE, 0);

        std::shared_ptr<ProtocolPP::jmacsecsa> tmp544(tmp4);
        tmp544->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        tmp544->set_field(ProtocolPP::INUSE, false);
        std::shared_ptr<ProtocolPP::jmacsec> myms3 = std::make_shared<ProtocolPP::jmacsec>(myrand, tmp544, myreplay);
        myms3->set_field(ProtocolPP::ENTRANSMIT, 1);
        myms3->set_field(ProtocolPP::ENTRANSMIT, 0);

        // get field
        uint64_t myfield = 0;
        myfield = myms->get_field(ProtocolPP::ETHERTYPE, tmphdr);
        myfield = myms->get_field(ProtocolPP::TCIAN, tmphdr);
        myfield = myms->get_field(ProtocolPP::SL, tmphdr);
        myfield = myms->get_field(ProtocolPP::PN, tmphdr);
        myfield = myms->get_field(ProtocolPP::XPN, tmphdr);
        myfield = myms->get_field(ProtocolPP::SCI, tmphdr);
        myfield = myms->get_field(ProtocolPP::SSCI, tmphdr);
        myfield = myms->get_field(ProtocolPP::ETHERTYPE);
        myfield = myms->get_field(ProtocolPP::TCIAN);
        myfield = myms->get_field(ProtocolPP::SL);
        myfield = myms->get_field(ProtocolPP::PN);
        myfield = myms->get_field(ProtocolPP::XPN);
        myfield = myms->get_field(ProtocolPP::SCI);
        myfield = myms->get_field(ProtocolPP::SSCI);
    }

    void testtlscov() {
        ProtocolPP::jtlsa tmp;
        ProtocolPP::jtlsa tmp2(tmp);
        std::shared_ptr<ProtocolPP::jtlsa> tmp3 = std::make_shared<ProtocolPP::jtlsa>(ProtocolPP::DECAP,
                                                                                      ProtocolPP::TLS_PSK_WITH_AES_256_CBC_SHA384,
                                                                                      ProtocolPP::tlsver_t::DTLS,
                                                                                      ProtocolPP::tlstype_t::APPLICATION,
                                                                                      0,
                                                                                      1,
                                                                                      12,
                                                                                      32,
                                                                                      std::make_shared<ProtocolPP::jarray<uint8_t>>(32,0xCC),
                                                                                      16,
                                                                                      std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                      16,
                                                                                      std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                      0,
                                                                                      std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                      0,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      1500,
                                                                                      true,
                                                                                      true,
                                                                                      false);

        std::shared_ptr<ProtocolPP::jtlsa> tmp4 = std::make_shared<ProtocolPP::jtlsa>(ProtocolPP::DECAP,
                                                                                      ProtocolPP::TLS_PSK_WITH_AES_256_CBC_SHA384,
                                                                                      ProtocolPP::tlsver_t::DTLS,
                                                                                      ProtocolPP::tlstype_t::APPLICATION,
                                                                                      0,
                                                                                      1,
                                                                                      12,
                                                                                      32,
                                                                                      std::make_shared<ProtocolPP::jarray<uint8_t>>(32,0xCC),
                                                                                      16,
                                                                                      std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                      16,
                                                                                      std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                      0,
                                                                                      std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                      0,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      1500,
                                                                                      true,
                                                                                      true,
                                                                                      false);

        std::shared_ptr<ProtocolPP::jtlsa> tmp555(tmp3);

        // set field
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::DECAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::DECAP);
        tmp4->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::CIPHERSUITE, ProtocolPP::TLS_RSA_WITH_AES_256_GCM_SHA384);
        tmp4->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::NH, ProtocolPP::TLS_RSA_WITH_AES_256_GCM_SHA384);
        tmp4->set_field<ProtocolPP::tlsver_t>(ProtocolPP::VERSION, ProtocolPP::tlsver_t::DTLS);
        tmp4->set_field<ProtocolPP::tlsver_t>(ProtocolPP::NH, ProtocolPP::tlsver_t::DTLS);
        tmp4->set_field<ProtocolPP::tlstype_t>(ProtocolPP::TYPE, ProtocolPP::tlstype_t::ALERT);
        tmp4->set_field<ProtocolPP::tlstype_t>(ProtocolPP::NH, ProtocolPP::tlstype_t::ALERT);
        tmp4->set_field<bool>(ProtocolPP::RANDIV, true);
        tmp4->set_field<bool>(ProtocolPP::IVEX, true);
        tmp4->set_field<bool>(ProtocolPP::ENCTHENMAC, true);
        tmp4->set_field<bool>(ProtocolPP::NH, true);
        tmp4->set_field<uint16_t>(ProtocolPP::EPOCH, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::ICVLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::IVLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 32);
        tmp4->set_field<uint32_t>(ProtocolPP::AKEYLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::SALTLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::MTU, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::ARLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::SEQNUM, 1);
        tmp4->set_field<uint64_t>(ProtocolPP::NH, 1);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::IV, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::AUTHKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SALT, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));

        // get field
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::tls_ciphersuite_t mycs = tmp4->get_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::CIPHERSUITE);
        mycs = tmp4->get_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::NH);
        ProtocolPP::tlsver_t myver = tmp4->get_field<ProtocolPP::tlsver_t>(ProtocolPP::VERSION);
        myver = tmp4->get_field<ProtocolPP::tlsver_t>(ProtocolPP::NH);
        ProtocolPP::tlstype_t mytt = tmp4->get_field<ProtocolPP::tlstype_t>(ProtocolPP::TYPE);
        mytt = tmp4->get_field<ProtocolPP::tlstype_t>(ProtocolPP::NH);
        bool mybool = tmp4->get_field<bool>(ProtocolPP::RANDIV);
        mybool = tmp4->get_field<bool>(ProtocolPP::IVEX);
        mybool = tmp4->get_field<bool>(ProtocolPP::ENCTHENMAC);
        mybool = tmp4->get_field<bool>(ProtocolPP::NH);
        uint16_t my16 = tmp4->get_field<uint16_t>(ProtocolPP::EPOCH);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::NH);
        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::ICVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::IVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::AKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::SALTLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::MTU);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ARLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);
        uint64_t my64 = tmp4->get_field<uint64_t>(ProtocolPP::SEQNUM);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> mywin = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN);
        mywin = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::IV);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::AUTHKEY);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SALT);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> myhdr(20,0xFF);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::TYPE);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::VERSION);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::MTU);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::SEQNUM);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::SEQNUM);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::EPOCH);

        ProtocolPP::jarray<uint8_t> tmphdr(5,0x44);
        std::shared_ptr<ProtocolPP::jrand> myrand = std::make_shared<ProtocolPP::jrand>(0x1122334455667788);
        std::shared_ptr<ProtocolPP::jtls> mytls = std::make_shared<ProtocolPP::jtls>(myrand, tmp4, myreplay);
        mytls->set_hdr(tmphdr);
        tmphdr = mytls->get_hdr();
        my64  = mytls->get_field(ProtocolPP::LENGTH,myhdr);

        // set field
        mytls->set_field(ProtocolPP::TYPE, 0);
        mytls->set_field(ProtocolPP::VERSION, 0x0300);
        mytls->set_field(ProtocolPP::VERSION, 0x0301);
        mytls->set_field(ProtocolPP::VERSION, 0x0302);
        mytls->set_field(ProtocolPP::VERSION, 0x0303);
        mytls->set_field(ProtocolPP::VERSION, 0xFFFE);
        mytls->set_field(ProtocolPP::SEQNUM, 0);
        mytls->set_field(ProtocolPP::EPOCH, 0);
        mytls->set_field(ProtocolPP::LENGTH, 0);
        mytls->set_field(ProtocolPP::MTU, 0);

        // get field
        uint64_t myf = mytls->get_field(ProtocolPP::TYPE, tmphdr);
        myf = mytls->get_field(ProtocolPP::VERSION, tmphdr);
        myf = mytls->get_field(ProtocolPP::LENGTH, tmphdr);
        myf = mytls->get_field(ProtocolPP::MTU, tmphdr);
        myf = mytls->get_field(ProtocolPP::SEQNUM, tmphdr);
        myf = mytls->get_field(ProtocolPP::EPOCH, tmphdr);
        myf = mytls->get_field(ProtocolPP::TYPE);
        myf = mytls->get_field(ProtocolPP::VERSION);
        myf = mytls->get_field(ProtocolPP::MTU);
        myf = mytls->get_field(ProtocolPP::SEQNUM);
        myf = mytls->get_field(ProtocolPP::EPOCH);
        myf = mytls->get_field(ProtocolPP::CIPHER);
    }

    void testtls13cov() {
        ProtocolPP::jtlsa13 tmp;
        ProtocolPP::jtlsa13 tmp2(tmp);

        std::shared_ptr<ProtocolPP::jtlsa13> tmp3 = std::make_shared<ProtocolPP::jtlsa13>(ProtocolPP::DECAP,
                                                                                          ProtocolPP::TLS_AES_256_GCM_SHA384,
                                                                                          ProtocolPP::tlstype_t::APPLICATION,
                                                                                          0,
                                                                                          12,
                                                                                          32,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(32,0xCC),
                                                                                          16,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                          0,
                                                                                          1500);

        std::shared_ptr<ProtocolPP::jtlsa13> tmp4 = std::make_shared<ProtocolPP::jtlsa13>(ProtocolPP::DECAP,
                                                                                          ProtocolPP::TLS_AES_256_GCM_SHA384,
                                                                                          ProtocolPP::tlstype_t::APPLICATION,
                                                                                          0,
                                                                                          12,
                                                                                          32,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(32,0xCC),
                                                                                          16,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                          0,
                                                                                          1500);
        // copy constructor from shared pointer
        std::shared_ptr<ProtocolPP::jtlsa13> tmp555(tmp3);

        // set field
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::DECAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::DECAP);
        tmp4->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::CIPHERSUITE, ProtocolPP::TLS_AES_256_GCM_SHA384);
        tmp4->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::NH, ProtocolPP::TLS_AES_256_GCM_SHA384);
        tmp4->set_field<ProtocolPP::tlstype_t>(ProtocolPP::TYPE, ProtocolPP::tlstype_t::ALERT);
        tmp4->set_field<ProtocolPP::tlstype_t>(ProtocolPP::NH, ProtocolPP::tlstype_t::ALERT);
        tmp4->set_field<uint32_t>(ProtocolPP::ICVLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::IVLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::SALTLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::MTU, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::ARLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::SEQNUM, 1);
        tmp4->set_field<uint64_t>(ProtocolPP::NH, 1);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::IV, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SALT, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));

        // get field
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::tls_ciphersuite_t mycs = tmp4->get_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::CIPHERSUITE);
        mycs = tmp4->get_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::NH);
        ProtocolPP::tlstype_t mytt = tmp4->get_field<ProtocolPP::tlstype_t>(ProtocolPP::TYPE);
        mytt = tmp4->get_field<ProtocolPP::tlstype_t>(ProtocolPP::NH);
        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::ICVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::IVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::AKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::SALTLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::MTU);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ARLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);
        uint64_t my64 = tmp4->get_field<uint64_t>(ProtocolPP::SEQNUM);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::IV);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SALT);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> myhdr(20,0xFF);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::TYPE);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::MTU);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::SEQNUM);

        ProtocolPP::jarray<uint8_t> tmphdr(5,0x44);
        std::string mypath("./test_outudp.dat");
        std::shared_ptr<ProtocolPP::jrand> myrand = std::make_shared<ProtocolPP::jrand>(0x1122334455667788);
        std::shared_ptr<ProtocolPP::jtls13> mytls = std::make_shared<ProtocolPP::jtls13>(myrand, tmp4);
        std::shared_ptr<ProtocolPP::jtls13> mytls2 = std::make_shared<ProtocolPP::jtls13>(myrand, tmp4, mypath);
        mytls->set_hdr(tmphdr);
        tmphdr = mytls->get_hdr();
        my64  = mytls->get_field(ProtocolPP::LENGTH,myhdr);

        // set field
        mytls->set_field(ProtocolPP::TYPE, 0);
        mytls->set_field(ProtocolPP::SEQNUM, 0);
        mytls->set_field(ProtocolPP::LENGTH, 0);
        mytls->set_field(ProtocolPP::MTU, 0);

        // get field
        uint64_t myf = mytls->get_field(ProtocolPP::TYPE, tmphdr);
        myf = mytls->get_field(ProtocolPP::VERSION, tmphdr);
        myf = mytls->get_field(ProtocolPP::LENGTH, tmphdr);
        myf = mytls->get_field(ProtocolPP::MTU, tmphdr);
        myf = mytls->get_field(ProtocolPP::SEQNUM, tmphdr);
        myf = mytls->get_field(ProtocolPP::TYPE);
        myf = mytls->get_field(ProtocolPP::VERSION);
        myf = mytls->get_field(ProtocolPP::MTU);
        myf = mytls->get_field(ProtocolPP::SEQNUM);
        myf = mytls->get_field(ProtocolPP::CIPHER);

        // retrieve the security association
        mytls->get_security(tmp4);
    }

    void testdtls13cov() {
        ProtocolPP::jdtlsa13 tmp;
        ProtocolPP::jdtlsa13 tmp2(tmp);

        std::shared_ptr<ProtocolPP::jdtlsa13> tmp3 = std::make_shared<ProtocolPP::jdtlsa13>(ProtocolPP::DECAP,
                                                                                            ProtocolPP::TLS_AES_256_GCM_SHA384,
                                                                                            ProtocolPP::tlstype_t::APPLICATION,
                                                                                            10,
                                                                                            1,
                                                                                            1,
                                                                                            0,
                                                                                            true,
                                                                                            true,
                                                                                            true,
                                                                                            12,
                                                                                            16,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                            16,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                            0,
                                                                                            ProtocolPP::jarray<uint8_t>(0),
                                                                                            1500);

        std::shared_ptr<ProtocolPP::jdtlsa13> tmp4 = std::make_shared<ProtocolPP::jdtlsa13>(ProtocolPP::DECAP,
                                                                                            ProtocolPP::TLS_AES_256_GCM_SHA384,
                                                                                            ProtocolPP::tlstype_t::APPLICATION,
                                                                                            20,
                                                                                            1,
                                                                                            1,
                                                                                            0,
                                                                                            false,
                                                                                            false,
                                                                                            false,
                                                                                            12,
                                                                                            16,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                            16,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0xCC),
                                                                                            0,
                                                                                            ProtocolPP::jarray<uint8_t>(0),
                                                                                            1500);
        // copy constructor from shared pointer
        std::shared_ptr<ProtocolPP::jdtlsa13> tmp555(tmp3);

        // set field
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::DECAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::DECAP);
        tmp4->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::CIPHERSUITE, ProtocolPP::TLS_AES_256_GCM_SHA384);
        tmp4->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::NH, ProtocolPP::TLS_AES_256_GCM_SHA384);
        tmp4->set_field<ProtocolPP::tlstype_t>(ProtocolPP::TYPE, ProtocolPP::tlstype_t::ALERT);
        tmp4->set_field<ProtocolPP::tlstype_t>(ProtocolPP::NH, ProtocolPP::tlstype_t::ALERT);

        tmp4->set_field<uint32_t>(ProtocolPP::ICVLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::IVLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::MTU, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::ARLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 0);

        tmp4->set_field<uint64_t>(ProtocolPP::EPOCH, 1);
        tmp4->set_field<uint64_t>(ProtocolPP::SEQNUM, 1);
        tmp4->set_field<uint64_t>(ProtocolPP::AUTHFAIL, 1);
        tmp4->set_field<uint64_t>(ProtocolPP::NH, 1);

        tmp4->set_field<uint8_t>(ProtocolPP::CID, 1);
        tmp4->set_field<uint8_t>(ProtocolPP::NH, 1);

        tmp4->set_field<bool>(ProtocolPP::CBIT, true);
        tmp4->set_field<bool>(ProtocolPP::SBIT, false);
        tmp4->set_field<bool>(ProtocolPP::LBIT, true);
        tmp4->set_field<bool>(ProtocolPP::NH, true);

        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::IV, ProtocolPP::jarray<uint8_t>(12, 0xAA));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHERKEY, ProtocolPP::jarray<uint8_t>(32, 0xA5));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::APP_TRAFFIC_SECRET, ProtocolPP::jarray<uint8_t>(32, 0xA5));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, ProtocolPP::jarray<uint8_t>(32, 0xA5));

        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::IV, std::make_shared<ProtocolPP::jarray<uint8_t>>(12, 0xAA));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(32, 0xA5));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::APP_TRAFFIC_SECRET, std::make_shared<ProtocolPP::jarray<uint8_t>>(32, 0xA5));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, std::make_shared<ProtocolPP::jarray<uint8_t>>(32, 0xA5));

        // get field
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::tls_ciphersuite_t mycs = tmp4->get_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::CIPHERSUITE);
        mycs = tmp4->get_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::NH);
        ProtocolPP::tlstype_t mytt = tmp4->get_field<ProtocolPP::tlstype_t>(ProtocolPP::TYPE);
        mytt = tmp4->get_field<ProtocolPP::tlstype_t>(ProtocolPP::NH);

        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::ICVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::IVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::AKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::MTU);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ARLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);

        uint64_t my64 = tmp4->get_field<uint64_t>(ProtocolPP::SEQNUM);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::NH);

        ProtocolPP::jarray<uint8_t> mywin = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN);
        mywin = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::IV);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        mykey = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);

        ProtocolPP::jarray<uint8_t> myhdr(20,0xFF);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::TYPE);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::MTU);
        my64  = tmp4->get_field<uint64_t>(ProtocolPP::SEQNUM);

        uint8_t mycid = tmp4->get_field<uint8_t>(ProtocolPP::CID);
        mycid = tmp4->get_field<uint8_t>(ProtocolPP::NH);

        bool bits = tmp4->get_field<bool>(ProtocolPP::CBIT);
        bits = tmp4->get_field<bool>(ProtocolPP::SBIT);
        bits = tmp4->get_field<bool>(ProtocolPP::LBIT);
        bits = tmp4->get_field<bool>(ProtocolPP::NH);

        ProtocolPP::jarray<uint8_t> tmphdr(13, 0x44);
        std::string mypath("./test_outudp.dat");
        std::shared_ptr<ProtocolPP::jrand> myrand = std::make_shared<ProtocolPP::jrand>(0x1122334455667788);
        std::shared_ptr<ProtocolPP::jdtls13> mytls = std::make_shared<ProtocolPP::jdtls13>(myrand, tmp4, myreplay);
        std::shared_ptr<ProtocolPP::jdtls13> mytls2 = std::make_shared<ProtocolPP::jdtls13>(myrand, tmp4, mypath, myreplay);
        mytls->set_hdr(tmphdr);
        tmphdr = mytls->get_hdr();
        my64  = mytls->get_field(ProtocolPP::LENGTH,myhdr);

        // set field
        mytls->set_field(ProtocolPP::TYPE, 0);
        mytls->set_field(ProtocolPP::SEQNUM, 0);
        mytls->set_field(ProtocolPP::LENGTH, 0);
        mytls->set_field(ProtocolPP::EPOCH, 0);
        mytls->set_field(ProtocolPP::MTU, 0);

        // get field
        uint64_t myf = mytls->get_field(ProtocolPP::TYPE, tmphdr);
        myf = mytls->get_field(ProtocolPP::VERSION, tmphdr);
        myf = mytls->get_field(ProtocolPP::LENGTH, tmphdr);
        myf = mytls->get_field(ProtocolPP::MTU, tmphdr);
        myf = mytls->get_field(ProtocolPP::SEQNUM, tmphdr);
        myf = mytls->get_field(ProtocolPP::TYPE);
        myf = mytls->get_field(ProtocolPP::VERSION);
        myf = mytls->get_field(ProtocolPP::MTU);
        myf = mytls->get_field(ProtocolPP::EPOCH);
        myf = mytls->get_field(ProtocolPP::SEQNUM);
        myf = mytls->get_field(ProtocolPP::CIPHER);

        // retrieve the security association
        mytls->get_security(tmp4);
    }

    void testsrtpcov() {
        ProtocolPP::jsrtpsa tmp;
        ProtocolPP::jsrtpsa tmp2(tmp);
        std::shared_ptr<ProtocolPP::jsrtpsa> tmp3 = std::make_shared<ProtocolPP::jsrtpsa>(ProtocolPP::DECAP,
                                                                                          ProtocolPP::SRTP,
                                                                                          ProtocolPP::AEAD_AES_256_GCM,
                                                                                          16,
                                                                                          16,
                                                                                          1,
                                                                                          1,
                                                                                          1,
                                                                                          2,
                                                                                          0,
                                                                                          true,
                                                                                          true,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(4,0),
                                                                                          false,
                                                                                          false,
                                                                                          32,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(32,0),
                                                                                          0,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                          4,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(4,0),
                                                                                          0,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                          0,
                                                                                          std::make_shared<ProtocolPP::jarray<uint32_t>>(0),
                                                                                          0,
                                                                                          ProtocolPP::jarray<uint8_t>(0));

        std::shared_ptr<ProtocolPP::jsrtpsa> tmp4(tmp3);

        // set field
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::MODE, ProtocolPP::SRTP);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::NH, ProtocolPP::SRTP);
        tmp4->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::CIPHER, ProtocolPP::AEAD_AES_256_GCM);
        tmp4->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::NH, ProtocolPP::AEAD_AES_256_GCM);
        tmp4->set_field<bool>(ProtocolPP::PADDING, false);
        tmp4->set_field<bool>(ProtocolPP::EXTENSION, false);
        tmp4->set_field<bool>(ProtocolPP::MARKER, false);
        tmp4->set_field<bool>(ProtocolPP::MKI, false);
        tmp4->set_field<bool>(ProtocolPP::NH, false);
        tmp4->set_field<uint8_t>(ProtocolPP::VERSION, 1);
        tmp4->set_field<uint8_t>(ProtocolPP::TYPE, 1);
        tmp4->set_field<uint8_t>(ProtocolPP::NH, 1);
        tmp4->set_field<uint16_t>(ProtocolPP::SEQNUM, 1);
        tmp4->set_field<uint16_t>(ProtocolPP::NH, 1);
        tmp4->set_field<uint32_t>(ProtocolPP::ICVLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::BLKSIZE, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::ROC, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::SSRC, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::AKEYLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::SALTLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::MKILEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::CC, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::ARLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 16);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::EXTHDR, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHERKEY, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::AUTHKEY, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::SALT, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::MKIDATA, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHER, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<ProtocolPP::jarray<uint32_t>>(ProtocolPP::CSRC, ProtocolPP::jarray<uint32_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint32_t>>(ProtocolPP::AUTH, ProtocolPP::jarray<uint32_t>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::EXTHDR, std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::AUTHKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SALT, std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::MKIDATA, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint32_t>>>(ProtocolPP::CSRC, std::make_shared<ProtocolPP::jarray<uint32_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint32_t>>>(ProtocolPP::NH, std::make_shared<ProtocolPP::jarray<uint32_t>>(0));

        // get field
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::protocol_t myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::MODE);
        myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::NH);
        ProtocolPP::srtpcipher_t mycipher = tmp4->get_field<ProtocolPP::srtpcipher_t>(ProtocolPP::CIPHER);
        mycipher = tmp4->get_field<ProtocolPP::srtpcipher_t>(ProtocolPP::NH);
        bool mybool = tmp4->get_field<bool>(ProtocolPP::PADDING);
        mybool = tmp4->get_field<bool>(ProtocolPP::EXTENSION);
        mybool = tmp4->get_field<bool>(ProtocolPP::MARKER);
        mybool = tmp4->get_field<bool>(ProtocolPP::MKI);
        mybool = tmp4->get_field<bool>(ProtocolPP::NH);
        uint8_t my8 = tmp4->get_field<uint8_t>(ProtocolPP::VERSION);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::TYPE);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::NH);
        uint16_t my16 = tmp4->get_field<uint16_t>(ProtocolPP::SEQNUM);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::NH);
        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::ICVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::BLKSIZE);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ROC);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::SSRC);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::AKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::SALTLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::MKILEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CC);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ARLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::EXTHDR);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHERKEY);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::AUTHKEY);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::SALT);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::MKIDATA);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHER);
        ProtocolPP::jarray<uint32_t> myar2 = tmp4->get_field<ProtocolPP::jarray<uint32_t>>(ProtocolPP::CSRC);
        myar2 = tmp4->get_field<ProtocolPP::jarray<uint32_t>>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::EXTHDR);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::AUTHKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::SALT);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::MKIDATA);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint32_t>> myptr2 = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint32_t>>>(ProtocolPP::CSRC);
        myptr2 = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint32_t>>>(ProtocolPP::NH);

        ProtocolPP::jarray<uint8_t> tmphdr(5,0x44);
        std::shared_ptr<ProtocolPP::jrand> myrand = std::make_shared<ProtocolPP::jrand>(0x1122334455667788);
        std::shared_ptr<ProtocolPP::jsrtp> mysrtp = std::make_shared<ProtocolPP::jsrtp>(myrand, tmp4, myreplay);
        mysrtp->set_hdr(tmphdr);
        tmphdr = mysrtp->get_hdr();
        mysrtp->set_exthdr(tmphdr);
        tmphdr = mysrtp->get_exthdr();

        // set field
        mysrtp->set_field(ProtocolPP::VERSION, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::PADDING, 0, 0);
        mysrtp->set_field(ProtocolPP::EXTENSION, 0, 0);
        mysrtp->set_field(ProtocolPP::CC, 0, 0);
        mysrtp->set_field(ProtocolPP::MARKER, 0, 0);
        mysrtp->set_field(ProtocolPP::PT, 0, 0);
        mysrtp->set_field(ProtocolPP::SEQNUM, 0, 0);
        mysrtp->set_field(ProtocolPP::ROC, 0, 0);
        mysrtp->set_field(ProtocolPP::TIMESTAMP, 0, 0);
        mysrtp->set_field(ProtocolPP::SSRC, 0, 0);
        mysrtp->set_field(ProtocolPP::CSRC, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);
        mysrtp->set_field(ProtocolPP::VERSION, 0, 0);

        // get field
        uint64_t myfield = 0;
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::PADDING, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::EXTENSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::CC, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::MARKER, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::PT, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::SEQNUM, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::ROC, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::TIMESTAMP, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::SSRC, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::CSRC, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
        myfield = mysrtp->get_field(ProtocolPP::VERSION, tmphdr, 0);
    }

    void testwificov() {
        ProtocolPP::jwifisa tmp;
        ProtocolPP::jwifisa tmp2(tmp);
        std::shared_ptr<ProtocolPP::jwifisa> tmp3 = std::make_shared<ProtocolPP::jwifisa>(ProtocolPP::DECAP,
                                                                                          ProtocolPP::WIFI,
                                                                                          ProtocolPP::AES_CTR,
                                                                                          ProtocolPP::NULL_AUTH,
                                                                                          ProtocolPP::SHA256,
                                                                                          1,
                                                                                          2,
                                                                                          3,
                                                                                          4,
                                                                                          1,
                                                                                          0xFF33,
                                                                                          ProtocolPP::SSW,
                                                                                          0xAA11,
                                                                                          0x1122,
                                                                                          0x3355,
                                                                                          0x22446688,
                                                                                          0x13,
                                                                                          0x11,
                                                                                          16,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0x33),
                                                                                          0,
                                                                                          ProtocolPP::jarray<uint8_t>(0),
                                                                                          false,
                                                                                          true,
                                                                                          false);

        std::shared_ptr<ProtocolPP::jwifisa> tmp4 = std::make_shared<ProtocolPP::jwifisa>(ProtocolPP::DECAP,
                                                                                          ProtocolPP::WIFI,
                                                                                          ProtocolPP::AES_CTR,
                                                                                          ProtocolPP::NULL_AUTH,
                                                                                          ProtocolPP::SHA256,
                                                                                          1,
                                                                                          2,
                                                                                          3,
                                                                                          4,
                                                                                          1,
                                                                                          0xFF33,
                                                                                          ProtocolPP::SSW,
                                                                                          0xAA11,
                                                                                          0x1122,
                                                                                          0x3355,
                                                                                          0x22446688,
                                                                                          0x13,
                                                                                          0x11,
                                                                                          16,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0x33),
                                                                                          0,
                                                                                          ProtocolPP::jarray<uint8_t>(0),
                                                                                          false,
                                                                                          true,
                                                                                          false);
        ProtocolPP::jwifisa tmp54(tmp3);

        // set fields
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::CIPHER, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::MODE, ProtocolPP::WIGIG);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::NH, ProtocolPP::WIGIG);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER, ProtocolPP::AES_GCM);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::NH, ProtocolPP::AES_GCM);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::KDFALG, ProtocolPP::AES_CMAC);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::SHA1);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::CIPHER, ProtocolPP::SHA1);
        tmp4->set_field<ProtocolPP::wifictlext_t>(ProtocolPP::CTLEXT, ProtocolPP::SSW);
        tmp4->set_field<ProtocolPP::wifictlext_t>(ProtocolPP::NH, ProtocolPP::SSW);
        tmp4->set_field<bool>(ProtocolPP::EXTIV, true);
        tmp4->set_field<bool>(ProtocolPP::FCS, true);
        tmp4->set_field<bool>(ProtocolPP::SPPCAP, false);
        tmp4->set_field<bool>(ProtocolPP::NH, true);
        tmp4->set_field<uint8_t>(ProtocolPP::KEYID, 0x00);
        tmp4->set_field<uint8_t>(ProtocolPP::NH, 0x00);
        tmp4->set_field<uint16_t>(ProtocolPP::FRAMECTL, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::ID, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::SEQCTL, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::QOSCTL, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::HTCTL, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::ICVLEN, 12);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::ARLEN, 128);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 128);
        tmp4->set_field<uint64_t>(ProtocolPP::ADDR1, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::ADDR2, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::ADDR3, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::ADDR4, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::PN, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::NH, 0);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));

        // get fields
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::protocol_t myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::MODE);
        myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::NH);
        ProtocolPP::cipher_t myciph = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER);
        ProtocolPP::auth_t myauth = tmp4->get_field<ProtocolPP::auth_t>(ProtocolPP::KDFALG);
        myauth = tmp4->get_field<ProtocolPP::auth_t>(ProtocolPP::CIPHER);
        myciph = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::NH);
        ProtocolPP::wifictlext_t myctl = tmp4->get_field<ProtocolPP::wifictlext_t>(ProtocolPP::CTLEXT);
        myctl = tmp4->get_field<ProtocolPP::wifictlext_t>(ProtocolPP::NH);
        bool mybool = tmp4->get_field<bool>(ProtocolPP::EXTIV);
        mybool = tmp4->get_field<bool>(ProtocolPP::FCS);
        mybool = tmp4->get_field<bool>(ProtocolPP::SPPCAP);
        mybool = tmp4->get_field<bool>(ProtocolPP::NH);
        uint8_t my8 = tmp4->get_field<uint8_t>(ProtocolPP::KEYID);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::NH);
        uint16_t my16 = tmp4->get_field<uint16_t>(ProtocolPP::FRAMECTL);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::ID);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::SEQCTL);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::QOSCTL);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::NH);
        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::HTCTL);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ICVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ARLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);
        uint64_t my64 = tmp4->get_field<uint64_t>(ProtocolPP::ADDR1);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::ADDR2);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::ADDR3);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::ADDR4);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::PN);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);
                                     
        // jwifi coverage
        std::shared_ptr<ProtocolPP::jwifi> mywifi = std::make_shared<ProtocolPP::jwifi>(myrand, tmp4, myreplay);
        mywifi->set_field(ProtocolPP::FRAMECTL, 0x10C0);
        mywifi->set_field(ProtocolPP::PROTVER, 0);
        mywifi->set_field(ProtocolPP::TYPE, 0);
        mywifi->set_field(ProtocolPP::SUBTYPE, 0);
        mywifi->set_field(ProtocolPP::CTLEXT, 0);
        mywifi->set_field(ProtocolPP::TDS, 0);
        mywifi->set_field(ProtocolPP::FDS, 0);
        mywifi->set_field(ProtocolPP::MFRAG, 0);
        mywifi->set_field(ProtocolPP::RETRY, 0);
        mywifi->set_field(ProtocolPP::PWRMGMT, 0);
        mywifi->set_field(ProtocolPP::MDATA, 0);
        mywifi->set_field(ProtocolPP::WEP, 0);
        mywifi->set_field(ProtocolPP::ORDER, 0);
        mywifi->set_field(ProtocolPP::ID, 0);
        mywifi->set_field(ProtocolPP::ADDR1, 0);
        mywifi->set_field(ProtocolPP::ADDR2, 0);
        mywifi->set_field(ProtocolPP::ADDR3, 0);
        mywifi->set_field(ProtocolPP::ADDR4, 0);
        mywifi->set_field(ProtocolPP::SEQCTL, 0);
        mywifi->set_field(ProtocolPP::QOSCTL, 0);
        mywifi->set_field(ProtocolPP::HTCTL, 0);
        mywifi->set_field(ProtocolPP::PN, 0);
        mywifi->set_field(ProtocolPP::EXTIV, 0);
        mywifi->set_field(ProtocolPP::KEYID, 0);

        // get field
        uint64_t fc = mywifi->get_field(ProtocolPP::FRAMECTL);
        fc = mywifi->get_field(ProtocolPP::PROTVER);
        fc = mywifi->get_field(ProtocolPP::TYPE);
        fc = mywifi->get_field(ProtocolPP::SUBTYPE);
        fc = mywifi->get_field(ProtocolPP::CTLEXT);
        fc = mywifi->get_field(ProtocolPP::TDS);
        fc = mywifi->get_field(ProtocolPP::FDS);
        fc = mywifi->get_field(ProtocolPP::MFRAG);
        fc = mywifi->get_field(ProtocolPP::RETRY);
        fc = mywifi->get_field(ProtocolPP::PWRMGMT);
        fc = mywifi->get_field(ProtocolPP::MDATA);
        fc = mywifi->get_field(ProtocolPP::WEP);
        fc = mywifi->get_field(ProtocolPP::ORDER);
        fc = mywifi->get_field(ProtocolPP::ID);
        fc = mywifi->get_field(ProtocolPP::ADDR1);
        fc = mywifi->get_field(ProtocolPP::ADDR2);
        fc = mywifi->get_field(ProtocolPP::ADDR3);
        fc = mywifi->get_field(ProtocolPP::ADDR4);
        fc = mywifi->get_field(ProtocolPP::SEQCTL);
        fc = mywifi->get_field(ProtocolPP::QOSCTL);
        fc = mywifi->get_field(ProtocolPP::HTCTL);
        fc = mywifi->get_field(ProtocolPP::PN);
        fc = mywifi->get_field(ProtocolPP::EXTIV);
        fc = mywifi->get_field(ProtocolPP::KEYID);
        fc = mywifi->get_field(ProtocolPP::HDRLEN);

        // get header
        ProtocolPP::jarray<uint8_t> myhdr(24,0);
        mywifi->set_hdr(myhdr);
        myhdr = mywifi->get_hdr();

        myhdr[0] = 0x20;
        myhdr[1] = 0x06;
        mywifi->set_hdr(myhdr);
        mywifi->set_field(ProtocolPP::CTLEXT, 0xE0);
        mywifi->set_field(ProtocolPP::ADDR4, 0xAABBCCDDEEFF);
        mywifi->set_field(ProtocolPP::QOSCTL, 0xAABB);
        mywifi->set_field(ProtocolPP::HTCTL, 0xAABB);
        mywifi->set_field(ProtocolPP::EXTIV, 0xAABB);
        mywifi->set_field(ProtocolPP::KEYID, 0xAABB);

        myhdr[0] = 0x10;
        mywifi->set_hdr(myhdr);
        fc = mywifi->get_field(ProtocolPP::TDS, myhdr);
        fc = mywifi->get_field(ProtocolPP::FDS, myhdr);
        fc = mywifi->get_field(ProtocolPP::MFRAG, myhdr);
        fc = mywifi->get_field(ProtocolPP::RETRY, myhdr);
        fc = mywifi->get_field(ProtocolPP::CTLEXT, myhdr);

        // get field with header
        fc = mywifi->get_field(ProtocolPP::FRAMECTL, myhdr);
        fc = mywifi->get_field(ProtocolPP::PROTVER, myhdr);
        fc = mywifi->get_field(ProtocolPP::TYPE, myhdr);
        fc = mywifi->get_field(ProtocolPP::SUBTYPE, myhdr);
        fc = mywifi->get_field(ProtocolPP::CTLEXT, myhdr);
        fc = mywifi->get_field(ProtocolPP::TDS, myhdr);
        fc = mywifi->get_field(ProtocolPP::FDS, myhdr);
        fc = mywifi->get_field(ProtocolPP::MFRAG, myhdr);
        fc = mywifi->get_field(ProtocolPP::RETRY, myhdr);
        fc = mywifi->get_field(ProtocolPP::PWRMGMT, myhdr);
        fc = mywifi->get_field(ProtocolPP::MDATA, myhdr);
        fc = mywifi->get_field(ProtocolPP::WEP, myhdr);
        fc = mywifi->get_field(ProtocolPP::ORDER, myhdr);
        fc = mywifi->get_field(ProtocolPP::ID, myhdr);
        fc = mywifi->get_field(ProtocolPP::ADDR1, myhdr);
        fc = mywifi->get_field(ProtocolPP::ADDR2, myhdr);
        fc = mywifi->get_field(ProtocolPP::ADDR3, myhdr);
        fc = mywifi->get_field(ProtocolPP::ADDR4, myhdr);
        fc = mywifi->get_field(ProtocolPP::SEQCTL, myhdr);
        fc = mywifi->get_field(ProtocolPP::QOSCTL, myhdr);
        fc = mywifi->get_field(ProtocolPP::HTCTL, myhdr);
        fc = mywifi->get_field(ProtocolPP::PN, myhdr);
        fc = mywifi->get_field(ProtocolPP::EXTIV, myhdr);
        fc = mywifi->get_field(ProtocolPP::KEYID, myhdr);
        fc = mywifi->get_field(ProtocolPP::HDRLEN, myhdr);

        tmp4->set_field<uint16_t>(ProtocolPP::FRAMECTL, 0x11C0);
        std::shared_ptr<ProtocolPP::jwifi> mywifi2 = std::make_shared<ProtocolPP::jwifi>(myrand, tmp4, myreplay);
        mywifi2->set_field(ProtocolPP::ADDR4, 0xAABBCCDDEEFF);
        mywifi2->set_field(ProtocolPP::QOSCTL, 0xAABB);
        mywifi2->set_field(ProtocolPP::HTCTL, 0xAABB);
        fc = mywifi2->get_field(ProtocolPP::ADDR4);
        fc = mywifi2->get_field(ProtocolPP::ADDR4, myhdr);
        fc = mywifi2->get_field(ProtocolPP::QOSCTL);
        fc = mywifi2->get_field(ProtocolPP::QOSCTL, myhdr);
        fc = mywifi2->get_field(ProtocolPP::HTCTL);
        fc = mywifi2->get_field(ProtocolPP::HTCTL, myhdr);
        fc = mywifi2->get_field(ProtocolPP::HDRLEN);

        tmp4->set_field<uint16_t>(ProtocolPP::FRAMECTL, 0x1101);
        std::shared_ptr<ProtocolPP::jwifi> mywifi3 = std::make_shared<ProtocolPP::jwifi>(myrand, tmp4, myreplay);
        mywifi3->set_field(ProtocolPP::HTCTL, 0xAABB);
    }

    void testwifiprf() {
        // test case 1 M.3.2 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> key = std::make_shared<ProtocolPP::jarray<uint8_t>>(20,0x0b);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> label = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> context = std::make_shared<ProtocolPP::jarray<uint8_t>>("Hi There",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>("bcd4c650b30b9684951829e0d75f9d54b862175ed9f00606e17d8da35402ffee75df78c3d31e0f889f012120c0862beb67753e7439ae242edb8373698356cf5a");

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA1,
                               key,
                               label,
                               context,
                               prfout,
                               512);

        if (*prfout != *expect) {
            std::cerr << "For WIFI PRF M.3.2 test case #1 expected and PRFOUT do not match"
                      << prfout->debug(*expect) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout->to_string(), expect->to_string());
        }

        // test case 2 M.3.2 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> key2 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Jefe", ProtocolPP::endian_t::BIG, true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> label2 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix", ProtocolPP::endian_t::BIG, true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> context2 = std::make_shared<ProtocolPP::jarray<uint8_t>>("what do ya want for nothing?", ProtocolPP::endian_t::BIG, true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect2 = std::make_shared<ProtocolPP::jarray<uint8_t>>("51f4de5b33f249adf81aeb713a3c20f4fe631446fabdfa58244759ae58ef9009a99abf4eac2ca5fa87e692c440eb40023e7babb206d61de7b92f41529092b8fc");

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA1,
                               key2,
                               label2,
                               context2,
                               prfout2,
                               512);

        if (*prfout2 != *expect2) {
            std::cerr << "For WIFI PRF M.3.2 test case #2 expected and PRFOUT do not match"
                      << prfout2->debug(*expect2) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout2->to_string(), expect2->to_string());
        }

        // test case 3 M.3.2 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> key3 = std::make_shared<ProtocolPP::jarray<uint8_t>>(20,0xaa);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> label3 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> context3 = std::make_shared<ProtocolPP::jarray<uint8_t>>(50,0xDD);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout3 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect3 = std::make_shared<ProtocolPP::jarray<uint8_t>>("e1ac546ec4cb636f9976487be5c86be17a0252ca5d8d8df12cfb0473525249ce9dd8d177ead710bc9b590547239107aef7b4abd43d87f0a68f1cbd9e2b6f7607");

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA1,
                               key3,
                               label3,
                               context3,
                               prfout3,
                               512);

        if (*prfout3 != *expect3) {
            std::cerr << "For WIFI PRF M.3.2 test case #3 expected and PRFOUT do not match"
                      << prfout3->debug(*expect3) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout3->to_string(), expect3->to_string());
        }

        // test case 1 M.6.5 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> key4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(20,0x0b);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> label4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> context4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Hi There",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("bcd4c650b30b9684951829e0d75f9d54b862175ed9f00606");

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA1,
                               key4,
                               label4,
                               context4,
                               prfout4,
                               192);

        if (*prfout4 != *expect4) {
            std::cerr << "For WIFI PRF M.6.5 test case #1 expected and PRFOUT do not match"
                      << prfout4->debug(*expect4) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout4->to_string(), expect4->to_string());
        }

        // test case 2 M.6.5 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> key5 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Jefe",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> label5 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix-2",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> context5 = std::make_shared<ProtocolPP::jarray<uint8_t>>("what do ya want for nothing?",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout5 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect5 = std::make_shared<ProtocolPP::jarray<uint8_t>>("47c4908e30c947521ad20be9053450ecbea23d3aa604b77326d8b3825ff7475c");

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA1,
                               key5,
                               label5,
                               context5,
                               prfout5,
                               256);

        if (*prfout5 != *expect5) {
            std::cerr << "For WIFI PRF M.6.5 test case #2 expected and PRFOUT do not match"
                      << prfout5->debug(*expect5) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout5->to_string(), expect5->to_string());
        }

        // test case 3 M.6.5 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> key6 = std::make_shared<ProtocolPP::jarray<uint8_t>>(80,0xaa);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> label6 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix-3",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> context6 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Test Using Larger Than Block-Size Key - Hash Key First",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout6 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect6 = std::make_shared<ProtocolPP::jarray<uint8_t>>("0ab6c33ccf70d0d736f4b04c8a7373255511abc5073713163bd0b8c9eeb7e1956fa066820a73ddee3f6d3bd407e0682a");

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA1,
                               key6,
                               label6,
                               context6,
                               prfout6,
                               384);

        if (*prfout6 != *expect6) {
            std::cerr << "For WIFI PRF M.6.5 test case #3 expected and PRFOUT do not match"
                      << prfout6->debug(*expect6) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout6->to_string(), expect6->to_string());
        }

        // test case 4 M.6.5 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> key7 = std::make_shared<ProtocolPP::jarray<uint8_t>>(20,0x0b);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> label7 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix-4",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> context7 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Hi There Again",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout7 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect7 = std::make_shared<ProtocolPP::jarray<uint8_t>>("248cfbc532ab38ffa483c8a2e40bf170eb542a2e0916d7bf6d97da2c4c5ca877736c53a65b03fa4b3745ce7613f6ad68e0e4a798b7cf691c96176fd634a59a49");

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA1,
                               key7,
                               label7,
                               context7,
                               prfout7,
                               512);

        if (*prfout7 != *expect7) {
            std::cerr << "For WIFI PRF M.6.5 test case #4 expected and PRFOUT do not match"
                      << prfout7->debug(*expect7) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout7->to_string(), expect7->to_string());
        }

        // additional algorithms - SHA256
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> key8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(64));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> label8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix-4",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> context8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Hi There Again",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA2_256,
                               key8,
                               label8,
                               context8,
                               prfout8,
                               512);

        key8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(128));
        label8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix-4",ProtocolPP::endian_t::BIG,true);
        context8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Hi There Again",ProtocolPP::endian_t::BIG,true);
        prfout8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA2_256,
                               key8,
                               label8,
                               context8,
                               prfout8,
                               512);

        // additional algorithms - SHA384
        key8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(128));
        label8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix-4",ProtocolPP::endian_t::BIG,true);
        context8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Hi There Again",ProtocolPP::endian_t::BIG,true);
        prfout8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA2_384,
                               key8,
                               label8,
                               context8,
                               prfout8,
                               1024);

        key8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(750));
        label8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix-4",ProtocolPP::endian_t::BIG,true);
        context8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Hi There Again",ProtocolPP::endian_t::BIG,true);
        prfout8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA2_384,
                               key8,
                               label8,
                               context8,
                               prfout8,
                               1024);

        // additional algorithms - SHA512
        key8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(128));
        label8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix-4",ProtocolPP::endian_t::BIG,true);
        context8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Hi There Again",ProtocolPP::endian_t::BIG,true);
        prfout8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA2_512,
                               key8,
                               label8,
                               context8,
                               prfout8,
                               1024);

        key8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(750));
        label8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("prefix-4",ProtocolPP::endian_t::BIG,true);
        context8 = std::make_shared<ProtocolPP::jarray<uint8_t>>("Hi There Again",ProtocolPP::endian_t::BIG,true);
        prfout8 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA2_512,
                               key8,
                               label8,
                               context8,
                               prfout8,
                               1024);

        // unsupported hash algorithm
        ProtocolPP::jwifi::prf(ProtocolPP::HMAC_SHA3_256,
                               key8,
                               label8,
                               context8,
                               prfout8,
                               1024);
    }

    void testwifikdf() {
        // SHA1 KDF
        ProtocolPP::auth_t kdfalg = ProtocolPP::HMAC_SHA1;            

        unsigned int akeylen = 75;
    
        // pointers to KDF data
        unsigned int myckeylen = 16;
        std::string mylabel = myrand->getname(16);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> label = std::make_shared<ProtocolPP::jarray<uint8_t>>(mylabel, ProtocolPP::endian_t::BIG, true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> context = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(myckeylen));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> authkey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(akeylen));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mycipherkey = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        // generate key material
        ProtocolPP::jwifi::kdf(kdfalg,
                               authkey,
                               label,
                               context,
                               mycipherkey,
                               myckeylen*8);

        // SHA256 KDF
        kdfalg = ProtocolPP::HMAC_SHA2_256;            

        akeylen = 90;
    
        // pointers to KDF data
        mylabel = myrand->getname(16);
        label = std::make_shared<ProtocolPP::jarray<uint8_t>>(mylabel, ProtocolPP::endian_t::BIG, true);
        context = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(myckeylen));
        authkey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(akeylen));
        mycipherkey = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        // generate key material
        ProtocolPP::jwifi::kdf(kdfalg,
                               authkey,
                               label,
                               context,
                               mycipherkey,
                               myckeylen*8);

        // SHA384 KDF
        kdfalg = ProtocolPP::HMAC_SHA2_384;            

        akeylen = 200;
    
        // pointers to KDF data
        mylabel = myrand->getname(16);
        label = std::make_shared<ProtocolPP::jarray<uint8_t>>(mylabel, ProtocolPP::endian_t::BIG, true);
        context = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(myckeylen));
        authkey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(akeylen));
        mycipherkey = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        // generate key material
        ProtocolPP::jwifi::kdf(kdfalg,
                               authkey,
                               label,
                               context,
                               mycipherkey,
                               myckeylen*8);

        // SHA512 KDF
        kdfalg = ProtocolPP::HMAC_SHA2_512;            

        akeylen = 150;
    
        // pointers to KDF data
        mylabel = myrand->getname(16);
        label = std::make_shared<ProtocolPP::jarray<uint8_t>>(mylabel, ProtocolPP::endian_t::BIG, true);
        context = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(myckeylen));
        authkey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(akeylen));
        mycipherkey = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);

        // generate key material
        ProtocolPP::jwifi::kdf(kdfalg,
                               authkey,
                               label,
                               context,
                               mycipherkey,
                               myckeylen*8);

        // unsupported hash algorithm
        ProtocolPP::jwifi::kdf(ProtocolPP::HMAC_SHA3_512,
                               authkey,
                               label,
                               context,
                               mycipherkey,
                               myckeylen*8);
    }

    void testwifipbkdf() {
        // test case 1 M.4.3 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> passphrase = std::make_shared<ProtocolPP::jarray<uint8_t>>("password",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ssid = std::make_shared<ProtocolPP::jarray<uint8_t>>("IEEE",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>("f42c6fc52df0ebef9ebb4b90b38a5f902e83fe1b135a70e23aed762e9710a12e");
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA1,
                                  passphrase, 
                                  ssid, 
                                  prfout,
                                  32,
                                  4096); 

        if (*prfout != *expect) {
            std::cerr << "For WIFI PBKDF2 M.4.3 test case #1 expected and PRFOUT do not match"
                      << prfout->debug(*expect) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout->to_string(), expect->to_string());
        }

        // test case 2 M.4.3 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> passphrase2 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ThisIsAPassword",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ssid2 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ThisIsASSID",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect2 = std::make_shared<ProtocolPP::jarray<uint8_t>>("0dc0d6eb90555ed6419756b9a15ec3e3209b63df707dd508d14581f8982721af");
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA1,
                                  passphrase2, 
                                  ssid2, 
                                  prfout2,
                                  32,
                                  4096); 

        if (*prfout2 != *expect2) {
            std::cerr << "For WIFI PBKDF2 M.4.3 test case #2 expected and PRFOUT do not match"
                      << prfout2->debug(*expect2) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout2->to_string(), expect2->to_string());
        }

        // test case 1 M.4.3 IEEE802.11-2012
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> passphrase3 = std::make_shared<ProtocolPP::jarray<uint8_t>>("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ssid3 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout3 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect3 = std::make_shared<ProtocolPP::jarray<uint8_t>>("becb93866bb8c3832cb777c2f559807c8c59afcb6eae734885001300a981cc62");
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA1,
                                  passphrase3, 
                                  ssid3, 
                                  prfout3,
                                  32,
                                  4096); 

        if (*prfout3 != *expect3) {
            std::cerr << "For WIFI PBKDF2 M.4.3 test case #3 expected and PRFOUT do not match"
                      << prfout3->debug(*expect3) << std::endl;
            CPPUNIT_ASSERT_EQUAL(prfout3->to_string(), expect3->to_string());
        }

        // additional algorithms - SHA1 large key
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> passphrase4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(80));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ssid4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",ProtocolPP::endian_t::BIG,true);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> prfout4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA1,
                                  passphrase4, 
                                  ssid4, 
                                  prfout4,
                                  32,
                                  4096); 

        // additional algorithms - SHA256
        passphrase4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(64));
        ssid4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",ProtocolPP::endian_t::BIG,true);
        prfout4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA2_256,
                                  passphrase4, 
                                  ssid4, 
                                  prfout4,
                                  32,
                                  4096); 

        passphrase4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(85));
        ssid4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",ProtocolPP::endian_t::BIG,true);
        prfout4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA2_256,
                                  passphrase4, 
                                  ssid4, 
                                  prfout4,
                                  32,
                                  4096); 

        // additional algorithms - SHA384
        passphrase4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(128));
        ssid4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",ProtocolPP::endian_t::BIG,true);
        prfout4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA2_384,
                                  passphrase4, 
                                  ssid4, 
                                  prfout4,
                                  64,
                                  4096); 

        passphrase4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(400));
        ssid4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",ProtocolPP::endian_t::BIG,true);
        prfout4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA2_384,
                                  passphrase4, 
                                  ssid4, 
                                  prfout4,
                                  64,
                                  4096); 

        // additional algorithms - SHA512
        passphrase4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(128));
        ssid4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",ProtocolPP::endian_t::BIG,true);
        prfout4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA2_512,
                                  passphrase4, 
                                  ssid4, 
                                  prfout4,
                                  64,
                                  4096); 

        passphrase4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(512));
        ssid4 = std::make_shared<ProtocolPP::jarray<uint8_t>>("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",ProtocolPP::endian_t::BIG,true);
        prfout4 = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA2_512,
                                  passphrase4, 
                                  ssid4, 
                                  prfout4,
                                  64,
                                  4096); 

        // unsupported hash algorithm
        ProtocolPP::jwifi::pbkdf2(ProtocolPP::HMAC_SHA3_512,
                                  passphrase4, 
                                  ssid4, 
                                  prfout4,
                                  64,
                                  4096); 
    }

    void testwigigcov() {
        ProtocolPP::jwifisa tmp;
        ProtocolPP::jwifisa tmp2(tmp);
        std::shared_ptr<ProtocolPP::jwifisa> tmp3 = std::make_shared<ProtocolPP::jwifisa>(ProtocolPP::DECAP,
                                                                                          ProtocolPP::WIGIG,
                                                                                          ProtocolPP::AES_CTR,
                                                                                          ProtocolPP::NULL_AUTH,
                                                                                          ProtocolPP::SHA256,
                                                                                          1,
                                                                                          2,
                                                                                          3,
                                                                                          4,
                                                                                          1,
                                                                                          0xFF33,
                                                                                          ProtocolPP::SSW,
                                                                                          0xAA11,
                                                                                          0x1122,
                                                                                          0x3355,
                                                                                          0x22446688,
                                                                                          0x13,
                                                                                          0x11,
                                                                                          16,
                                                                                          std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0x33),
                                                                                          0,
                                                                                          ProtocolPP::jarray<uint8_t>(0),
                                                                                          false,
                                                                                          true,
                                                                                          false);
        
        std::shared_ptr<ProtocolPP::jwifisa> tmp4(tmp3);

        // set fields
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::MODE, ProtocolPP::WIGIG);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::NH, ProtocolPP::WIGIG);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER, ProtocolPP::AES_GCM);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::KDFALG, ProtocolPP::SHA384);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::NH, ProtocolPP::AES_GCM);
        tmp4->set_field<ProtocolPP::wifictlext_t>(ProtocolPP::CTLEXT, ProtocolPP::SSW);
        tmp4->set_field<ProtocolPP::wifictlext_t>(ProtocolPP::NH, ProtocolPP::SSW);
        tmp4->set_field<bool>(ProtocolPP::EXTIV, true);
        tmp4->set_field<bool>(ProtocolPP::FCS, true);
        tmp4->set_field<bool>(ProtocolPP::SPPCAP, false);
        tmp4->set_field<bool>(ProtocolPP::NH, true);
        tmp4->set_field<uint8_t>(ProtocolPP::KEYID, 0x00);
        tmp4->set_field<uint8_t>(ProtocolPP::NH, 0x00);
        tmp4->set_field<uint16_t>(ProtocolPP::FRAMECTL, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::ID, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::SEQCTL, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::QOSCTL, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::HTCTL, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::ICVLEN, 12);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 16);
        tmp4->set_field<uint32_t>(ProtocolPP::ARLEN, 128);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 128);
        tmp4->set_field<uint64_t>(ProtocolPP::ADDR1, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::ADDR2, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::ADDR3, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::ADDR4, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::PN, 0);
        tmp4->set_field<uint64_t>(ProtocolPP::NH, 0);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, ProtocolPP::jarray<uint8_t>(16,0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));

        // get fields
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::protocol_t myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::MODE);
        myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::NH);
        ProtocolPP::cipher_t myciph = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER);
        ProtocolPP::auth_t myauth = tmp4->get_field<ProtocolPP::auth_t>(ProtocolPP::KDFALG);
        myciph = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::NH);
        ProtocolPP::wifictlext_t myctl = tmp4->get_field<ProtocolPP::wifictlext_t>(ProtocolPP::CTLEXT);
        myctl = tmp4->get_field<ProtocolPP::wifictlext_t>(ProtocolPP::NH);
        bool mybool = tmp4->get_field<bool>(ProtocolPP::EXTIV);
        mybool = tmp4->get_field<bool>(ProtocolPP::FCS);
        mybool = tmp4->get_field<bool>(ProtocolPP::SPPCAP);
        mybool = tmp4->get_field<bool>(ProtocolPP::NH);
        uint8_t my8 = tmp4->get_field<uint8_t>(ProtocolPP::KEYID);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::NH);
        uint16_t my16 = tmp4->get_field<uint16_t>(ProtocolPP::FRAMECTL);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::ID);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::SEQCTL);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::QOSCTL);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::NH);
        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::HTCTL);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ICVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ARLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);
        uint64_t my64 = tmp4->get_field<uint64_t>(ProtocolPP::ADDR1);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::ADDR2);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::ADDR3);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::ADDR4);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::PN);
        my64 = tmp4->get_field<uint64_t>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);
                                     
        // jwifi coverage
        std::shared_ptr<ProtocolPP::jwifi> mywifi = std::make_shared<ProtocolPP::jwifi>(myrand, tmp4, myreplay);
        mywifi->set_field(ProtocolPP::FRAMECTL, 0);
        mywifi->set_field(ProtocolPP::PROTVER, 0);
        mywifi->set_field(ProtocolPP::TYPE, 0);
        mywifi->set_field(ProtocolPP::SUBTYPE, 0);
        mywifi->set_field(ProtocolPP::CTLEXT, 0);
        mywifi->set_field(ProtocolPP::TDS, 0);
        mywifi->set_field(ProtocolPP::FDS, 0);
        mywifi->set_field(ProtocolPP::MFRAG, 0);
        mywifi->set_field(ProtocolPP::RETRY, 0);
        mywifi->set_field(ProtocolPP::PWRMGMT, 0);
        mywifi->set_field(ProtocolPP::MDATA, 0);
        mywifi->set_field(ProtocolPP::WEP, 0);
        mywifi->set_field(ProtocolPP::ORDER, 0);
        mywifi->set_field(ProtocolPP::ID, 0);
        mywifi->set_field(ProtocolPP::ADDR1, 0);
        mywifi->set_field(ProtocolPP::ADDR2, 0);
        mywifi->set_field(ProtocolPP::ADDR3, 0);
        mywifi->set_field(ProtocolPP::ADDR4, 0);
        mywifi->set_field(ProtocolPP::SEQCTL, 0);
        mywifi->set_field(ProtocolPP::QOSCTL, 0);
        mywifi->set_field(ProtocolPP::HTCTL, 0);
        mywifi->set_field(ProtocolPP::PN, 0);
        mywifi->set_field(ProtocolPP::EXTIV, 0);
        mywifi->set_field(ProtocolPP::KEYID, 0);

        // get field
        uint64_t fc = mywifi->get_field(ProtocolPP::FRAMECTL);
        fc = mywifi->get_field(ProtocolPP::PROTVER);
        fc = mywifi->get_field(ProtocolPP::TYPE);
        fc = mywifi->get_field(ProtocolPP::SUBTYPE);
        fc = mywifi->get_field(ProtocolPP::CTLEXT);
        fc = mywifi->get_field(ProtocolPP::TDS);
        fc = mywifi->get_field(ProtocolPP::FDS);
        fc = mywifi->get_field(ProtocolPP::MFRAG);
        fc = mywifi->get_field(ProtocolPP::RETRY);
        fc = mywifi->get_field(ProtocolPP::PWRMGMT);
        fc = mywifi->get_field(ProtocolPP::MDATA);
        fc = mywifi->get_field(ProtocolPP::WEP);
        fc = mywifi->get_field(ProtocolPP::ORDER);
        fc = mywifi->get_field(ProtocolPP::ID);
        fc = mywifi->get_field(ProtocolPP::ADDR1);
        fc = mywifi->get_field(ProtocolPP::ADDR2);
        fc = mywifi->get_field(ProtocolPP::ADDR3);
        fc = mywifi->get_field(ProtocolPP::ADDR4);
        fc = mywifi->get_field(ProtocolPP::SEQCTL);
        fc = mywifi->get_field(ProtocolPP::QOSCTL);
        fc = mywifi->get_field(ProtocolPP::HTCTL);
        fc = mywifi->get_field(ProtocolPP::PN);
        fc = mywifi->get_field(ProtocolPP::EXTIV);
        fc = mywifi->get_field(ProtocolPP::KEYID);

        // get header
        ProtocolPP::jarray<uint8_t> myhdr(24,0);
        mywifi->set_hdr(myhdr);
        myhdr = mywifi->get_hdr();

        // get field with header
        fc = mywifi->get_field(ProtocolPP::FRAMECTL, myhdr);
        fc = mywifi->get_field(ProtocolPP::PROTVER, myhdr);
        fc = mywifi->get_field(ProtocolPP::TYPE, myhdr);
        fc = mywifi->get_field(ProtocolPP::SUBTYPE, myhdr);
        fc = mywifi->get_field(ProtocolPP::CTLEXT, myhdr);
        fc = mywifi->get_field(ProtocolPP::TDS, myhdr);
        fc = mywifi->get_field(ProtocolPP::FDS, myhdr);
        fc = mywifi->get_field(ProtocolPP::MFRAG, myhdr);
        fc = mywifi->get_field(ProtocolPP::RETRY, myhdr);
        fc = mywifi->get_field(ProtocolPP::PWRMGMT, myhdr);
        fc = mywifi->get_field(ProtocolPP::MDATA, myhdr);
        fc = mywifi->get_field(ProtocolPP::WEP, myhdr);
        fc = mywifi->get_field(ProtocolPP::ORDER, myhdr);
        fc = mywifi->get_field(ProtocolPP::ID, myhdr);
        fc = mywifi->get_field(ProtocolPP::ADDR1, myhdr);
        fc = mywifi->get_field(ProtocolPP::ADDR2, myhdr);
        fc = mywifi->get_field(ProtocolPP::ADDR3, myhdr);
        fc = mywifi->get_field(ProtocolPP::ADDR4, myhdr);
        fc = mywifi->get_field(ProtocolPP::SEQCTL, myhdr);
        fc = mywifi->get_field(ProtocolPP::QOSCTL, myhdr);
        fc = mywifi->get_field(ProtocolPP::HTCTL, myhdr);
        fc = mywifi->get_field(ProtocolPP::PN, myhdr);
        fc = mywifi->get_field(ProtocolPP::EXTIV, myhdr);
        fc = mywifi->get_field(ProtocolPP::KEYID, myhdr);

        // additional init fields
        tmp4->set_field<uint16_t>(ProtocolPP::FRAMECTL, 0x2600);
        std::shared_ptr<ProtocolPP::jwifi> mywifi2 = std::make_shared<ProtocolPP::jwifi>(myrand, tmp4, myreplay);
        
    }

    void testwimaxcov() {
        ProtocolPP::jwimaxsa tmp;
        ProtocolPP::jwimaxsa tmp2(tmp);
        std::shared_ptr<ProtocolPP::jwimaxsa> tmp3 = std::make_shared<ProtocolPP::jwimaxsa>(ProtocolPP::ENCAP,
                                                                                            ProtocolPP::OFDM,
                                                                                            ProtocolPP::AES_CCM,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            0,
                                                                                            1,
                                                                                            16,
                                                                                            std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0),
                                                                                            0,
                                                                                            ProtocolPP::jarray<uint8_t>(0),
                                                                                            false,
                                                                                            false,
                                                                                            true,
                                                                                            false,
                                                                                            false);
        std::shared_ptr<ProtocolPP::jwimaxsa> tmp4(tmp3);
        
        // set field
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::ENCAP);
        tmp4->set_field<ProtocolPP::wimaxmode_t>(ProtocolPP::MODE, ProtocolPP::OFDMA);
        tmp4->set_field<ProtocolPP::wimaxmode_t>(ProtocolPP::NH, ProtocolPP::OFDMA);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER, ProtocolPP::SEED_CBC);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::NH, ProtocolPP::ARIA_GCM);
        tmp4->set_field<bool>(ProtocolPP::EH, true);
        tmp4->set_field<bool>(ProtocolPP::HT, true);
        tmp4->set_field<bool>(ProtocolPP::EC, true);
        tmp4->set_field<bool>(ProtocolPP::ESF, true);
        tmp4->set_field<bool>(ProtocolPP::CI, true);
        tmp4->set_field<bool>(ProtocolPP::NH, true);
        tmp4->set_field<uint8_t>(ProtocolPP::TYPE, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::EKS, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::FID, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::CID, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::PN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::ARLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 0);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));

        // get field
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::wimaxmode_t mymode = tmp4->get_field<ProtocolPP::wimaxmode_t>(ProtocolPP::MODE);
        mymode = tmp4->get_field<ProtocolPP::wimaxmode_t>(ProtocolPP::NH);
        ProtocolPP::cipher_t mycipher = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::MODE);
        mycipher = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::NH);
        bool mybool = tmp4->get_field<bool>(ProtocolPP::EH);
        mybool = tmp4->get_field<bool>(ProtocolPP::HT);
        mybool = tmp4->get_field<bool>(ProtocolPP::EC);
        mybool = tmp4->get_field<bool>(ProtocolPP::ESF);
        mybool = tmp4->get_field<bool>(ProtocolPP::CI);
        mybool = tmp4->get_field<bool>(ProtocolPP::NH);
        uint8_t my8 = tmp4->get_field<uint8_t>(ProtocolPP::TYPE);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::EKS);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::FID);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::NH);
        uint16_t my16 = tmp4->get_field<uint16_t>(ProtocolPP::CID);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::NH);
        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::PN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ARLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::ARWIN);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);

        ProtocolPP::jarray<uint8_t> tmphdr(16,0);
        std::shared_ptr<ProtocolPP::jwimax> mywimax = std::make_shared<ProtocolPP::jwimax>(myrand, tmp4, myreplay);
        mywimax->set_hdr(tmphdr);
        tmphdr = mywimax->get_hdr();

        // set field
        mywimax->set_field(ProtocolPP::HT, 0);
        mywimax->set_field(ProtocolPP::EC, 0);
        mywimax->set_field(ProtocolPP::TYPE, 0);
        mywimax->set_field(ProtocolPP::ESF, 0);
        mywimax->set_field(ProtocolPP::CI, 0);
        mywimax->set_field(ProtocolPP::EKS, 0);
        mywimax->set_field(ProtocolPP::FID, 0);
        mywimax->set_field(ProtocolPP::EH, 0);
        mywimax->set_field(ProtocolPP::LENGTH, 0);
        mywimax->set_field(ProtocolPP::CID, 0);
        mywimax->set_field(ProtocolPP::HCS, 0);
        mywimax->set_field(ProtocolPP::PN, 0);

        // get field
        uint64_t myfield = 0;
        myfield = mywimax->get_field(ProtocolPP::HT, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::EC, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::TYPE, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::ESF, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::CI, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::EKS, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::FID, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::EH, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::LENGTH, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::CID, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::HCS, tmphdr);
        myfield = mywimax->get_field(ProtocolPP::PN, tmphdr);
    }

    void testltecov() {
        ProtocolPP::jltesa tmp;
        ProtocolPP::jltesa tmp2(tmp);
        std::shared_ptr<ProtocolPP::jltesa> tmp3 = std::make_shared<ProtocolPP::jltesa>(ProtocolPP::UPLINK,
                                                                                        ProtocolPP::LTE,
                                                                                        ProtocolPP::SNOWE,
                                                                                        ProtocolPP::SNOWA,
                                                                                        7,
                                                                                        true,
                                                                                        false,
                                                                                        false,
                                                                                        false,
                                                                                        0,
                                                                                        0,
                                                                                        0,
                                                                                        0,
                                                                                        5,
                                                                                        0,
                                                                                        0,
                                                                                        0,
                                                                                        1,
                                                                                        1,
                                                                                        1,
                                                                                        1,
                                                                                        1,
                                                                                        1,
                                                                                        4,
                                                                                        16,
                                                                                        16,
                                                                                        100,
                                                                                        ProtocolPP::jarray<uint8_t>(16,0),
                                                                                        ProtocolPP::jarray<uint8_t>(0),
                                                                                        std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0),
                                                                                        std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));
        std::shared_ptr<ProtocolPP::jltesa> tmp4(tmp3);

        // set field
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::DOWNLINK);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::DOWNLINK);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::TYPE, ProtocolPP::RLC);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::NH, ProtocolPP::RLC);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER, ProtocolPP::ZUCE);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::NH, ProtocolPP::ZUCE);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::ZUCA);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::NH, ProtocolPP::ZUCA);
        tmp4->set_field<int>(ProtocolPP::SNLEN, 12);
        tmp4->set_field<int>(ProtocolPP::NH, 12);
        tmp4->set_field<bool>(ProtocolPP::DATACTRL, true);
        tmp4->set_field<bool>(ProtocolPP::POLLBIT, true);
        tmp4->set_field<bool>(ProtocolPP::EXTENSION, true);
        tmp4->set_field<bool>(ProtocolPP::RSN, true);
        tmp4->set_field<bool>(ProtocolPP::NH, true);
        tmp4->set_field<uint8_t>(ProtocolPP::PDUTYPE, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::HDREXT, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::PGKINDEX, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::SDUTYPE, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::BEARER, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::LENGTHIND, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::PTKINDENT, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::KDID, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::HFNI, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::FMS, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::NMP, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::HRW, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::FRESH, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::ICVLEN, 4);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::AKEYLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::BITMAPLEN, 100);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 0);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::SUFI, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::BITMAP, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHERKEY, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::AUTHKEY, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHER, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::AUTHKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHER, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));

        // get field
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::protocol_t myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::TYPE);
        myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::NH);
        ProtocolPP::cipher_t myciph = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER);
        myciph = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::NH);
        ProtocolPP::auth_t myauth = tmp4->get_field<ProtocolPP::auth_t>(ProtocolPP::AUTH);
        myauth = tmp4->get_field<ProtocolPP::auth_t>(ProtocolPP::NH);
        int myint = tmp4->get_field<int>(ProtocolPP::SNLEN);
        myint = tmp4->get_field<int>(ProtocolPP::NH);
        bool mybool = tmp4->get_field<bool>(ProtocolPP::DATACTRL);
        mybool = tmp4->get_field<bool>(ProtocolPP::POLLBIT);
        mybool = tmp4->get_field<bool>(ProtocolPP::EXTENSION);
        mybool = tmp4->get_field<bool>(ProtocolPP::RSN);
        mybool = tmp4->get_field<bool>(ProtocolPP::NH);
        uint8_t my8 = tmp4->get_field<uint8_t>(ProtocolPP::PDUTYPE);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::HDREXT);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::PGKINDEX);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::SDUTYPE);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::BEARER);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::NH);
        uint16_t my16 = tmp4->get_field<uint16_t>(ProtocolPP::LENGTHIND);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::PTKINDENT);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::KDID);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::NH);
        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::SEQNUM);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::HFNI);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::FMS);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NMP);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::HRW);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::FRESH);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ICVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::AKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::BITMAPLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::SUFI);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::BITMAP);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHER);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::AUTHKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::AUTH);

        ProtocolPP::jarray<uint8_t> tmphdr(4,0);
        std::shared_ptr<ProtocolPP::jlte> mylte = std::make_shared<ProtocolPP::jlte>(myrand, tmp4, myreplay);
        mylte->set_hdr(tmphdr);
        tmphdr = mylte->get_hdr();

        uint64_t my64 = mylte->get_field(ProtocolPP::CKEYLEN);
        my64 = mylte->get_field(ProtocolPP::AKEYLEN);
        my64 = mylte->get_field(ProtocolPP::FRESH);
        my64 = mylte->get_field(ProtocolPP::SEQNUM,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 5);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 7);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 12);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 15);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 16);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 18);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);

        // set field
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::PDUTYPE, 1);
        mylte->set_field(ProtocolPP::POLLBIT, 1);
        mylte->set_field(ProtocolPP::EXTENSION, 1);
        mylte->set_field(ProtocolPP::SNLEN, 1);
        mylte->set_field(ProtocolPP::HDREXT, 1);
        mylte->set_field(ProtocolPP::LENGTHIND, 1);
        mylte->set_field(ProtocolPP::SEQNUM, 1);
        mylte->set_field(ProtocolPP::HFNI, 1);
        mylte->set_field(ProtocolPP::SUFI, 1);
        mylte->set_field(ProtocolPP::FMS, 1);
        mylte->set_field(ProtocolPP::PGKINDEX, 1);
        mylte->set_field(ProtocolPP::PTKINDENT, 1);
        mylte->set_field(ProtocolPP::SDUTYPE, 1);
        mylte->set_field(ProtocolPP::RSN, 1);
        mylte->set_field(ProtocolPP::KDID, 1);
        mylte->set_field(ProtocolPP::NMP, 1);
        mylte->set_field(ProtocolPP::HRW, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);

        // get field
        uint64_t myfield = 0;
        myfield = mylte->get_field(ProtocolPP::DATACTRL, tmphdr);
        myfield = mylte->get_field(ProtocolPP::PDUTYPE, tmphdr);
        myfield = mylte->get_field(ProtocolPP::POLLBIT, tmphdr);
        myfield = mylte->get_field(ProtocolPP::EXTENSION, tmphdr);
        myfield = mylte->get_field(ProtocolPP::SNLEN, tmphdr);
        myfield = mylte->get_field(ProtocolPP::HDREXT, tmphdr);
        myfield = mylte->get_field(ProtocolPP::LENGTHIND, tmphdr);
        myfield = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        myfield = mylte->get_field(ProtocolPP::HFNI, tmphdr);
        myfield = mylte->get_field(ProtocolPP::SUFI, tmphdr);
        myfield = mylte->get_field(ProtocolPP::FMS, tmphdr);
        myfield = mylte->get_field(ProtocolPP::PGKINDEX, tmphdr);
        myfield = mylte->get_field(ProtocolPP::PTKINDENT, tmphdr);
        myfield = mylte->get_field(ProtocolPP::SDUTYPE, tmphdr);
        myfield = mylte->get_field(ProtocolPP::RSN, tmphdr);
        myfield = mylte->get_field(ProtocolPP::KDID, tmphdr);
        myfield = mylte->get_field(ProtocolPP::NMP, tmphdr);
        myfield = mylte->get_field(ProtocolPP::HRW, tmphdr);
        myfield = mylte->get_field(ProtocolPP::BITMAPLEN, tmphdr);

        myfield = mylte->get_field(ProtocolPP::DATACTRL);
        myfield = mylte->get_field(ProtocolPP::PDUTYPE);
        myfield = mylte->get_field(ProtocolPP::POLLBIT);
        myfield = mylte->get_field(ProtocolPP::EXTENSION);
        myfield = mylte->get_field(ProtocolPP::SNLEN);
        myfield = mylte->get_field(ProtocolPP::HDREXT);
        myfield = mylte->get_field(ProtocolPP::LENGTHIND);
        myfield = mylte->get_field(ProtocolPP::SEQNUM);
        myfield = mylte->get_field(ProtocolPP::HFNI);
        myfield = mylte->get_field(ProtocolPP::SUFI);
        myfield = mylte->get_field(ProtocolPP::FMS);
        myfield = mylte->get_field(ProtocolPP::PGKINDEX);
        myfield = mylte->get_field(ProtocolPP::PTKINDENT);
        myfield = mylte->get_field(ProtocolPP::SDUTYPE);
        myfield = mylte->get_field(ProtocolPP::RSN);
        myfield = mylte->get_field(ProtocolPP::KDID);
        myfield = mylte->get_field(ProtocolPP::NMP);
        myfield = mylte->get_field(ProtocolPP::HRW);
        myfield = mylte->get_field(ProtocolPP::BITMAPLEN);
    }

    void testrlccov() {
        ProtocolPP::jltesa tmp;
        ProtocolPP::jltesa tmp2(tmp);
        std::shared_ptr<ProtocolPP::jltesa> tmp3 = std::make_shared<ProtocolPP::jltesa>(ProtocolPP::UPLINK,
                                                                                        ProtocolPP::RLC,
                                                                                        ProtocolPP::SNOWE,
                                                                                        ProtocolPP::SNOWA,
                                                                                        7,
                                                                                        true,
                                                                                        false,
                                                                                        false,
                                                                                        false,
                                                                                        0,
                                                                                        0,
                                                                                        0,
                                                                                        0,
                                                                                        5,
                                                                                        0,
                                                                                        0,
                                                                                        0,
                                                                                        1,
                                                                                        1,
                                                                                        1,
                                                                                        1,
                                                                                        1,
                                                                                        1,
                                                                                        4,
                                                                                        16,
                                                                                        16,
                                                                                        0,
                                                                                        ProtocolPP::jarray<uint8_t>(16,0),
                                                                                        ProtocolPP::jarray<uint8_t>(0),
                                                                                        std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0),
                                                                                        std::make_shared<ProtocolPP::jarray<uint8_t>>(16,0));
        std::shared_ptr<ProtocolPP::jltesa> tmp4(tmp3);

        // set field
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::DOWNLINK);
        tmp4->set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::DOWNLINK);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::TYPE, ProtocolPP::RLC);
        tmp4->set_field<ProtocolPP::protocol_t>(ProtocolPP::NH, ProtocolPP::RLC);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER, ProtocolPP::ZUCE);
        tmp4->set_field<ProtocolPP::cipher_t>(ProtocolPP::NH, ProtocolPP::ZUCE);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::ZUCA);
        tmp4->set_field<ProtocolPP::auth_t>(ProtocolPP::NH, ProtocolPP::ZUCA);
        tmp4->set_field<int>(ProtocolPP::SNLEN, 12);
        tmp4->set_field<int>(ProtocolPP::NH, 12);
        tmp4->set_field<bool>(ProtocolPP::DATACTRL, true);
        tmp4->set_field<bool>(ProtocolPP::POLLBIT, true);
        tmp4->set_field<bool>(ProtocolPP::EXTENSION, true);
        tmp4->set_field<bool>(ProtocolPP::RSN, true);
        tmp4->set_field<bool>(ProtocolPP::NH, true);
        tmp4->set_field<uint8_t>(ProtocolPP::PDUTYPE, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::HDREXT, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::PGKINDEX, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::SDUTYPE, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::BEARER, 0);
        tmp4->set_field<uint8_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::LENGTHIND, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::PTKINDENT, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::KDID, 0);
        tmp4->set_field<uint16_t>(ProtocolPP::NH, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::HFNI, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::FMS, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::NMP, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::HRW, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::FRESH, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::ICVLEN, 4);
        tmp4->set_field<uint32_t>(ProtocolPP::CKEYLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::AKEYLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::BITMAPLEN, 0);
        tmp4->set_field<uint32_t>(ProtocolPP::NH, 0);
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::SUFI, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::BITMAP, ProtocolPP::jarray<uint8_t>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
        tmp4->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, std::make_shared<ProtocolPP::jarray<uint8_t>>(0));

        // get field
        ProtocolPP::direction_t mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = tmp4->get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        ProtocolPP::protocol_t myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::TYPE);
        myprot = tmp4->get_field<ProtocolPP::protocol_t>(ProtocolPP::NH);
        ProtocolPP::cipher_t myciph = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER);
        myciph = tmp4->get_field<ProtocolPP::cipher_t>(ProtocolPP::NH);
        ProtocolPP::auth_t myauth = tmp4->get_field<ProtocolPP::auth_t>(ProtocolPP::AUTH);
        myauth = tmp4->get_field<ProtocolPP::auth_t>(ProtocolPP::NH);
        int myint = tmp4->get_field<int>(ProtocolPP::SNLEN);
        myint = tmp4->get_field<int>(ProtocolPP::NH);
        bool mybool = tmp4->get_field<bool>(ProtocolPP::DATACTRL);
        mybool = tmp4->get_field<bool>(ProtocolPP::POLLBIT);
        mybool = tmp4->get_field<bool>(ProtocolPP::EXTENSION);
        mybool = tmp4->get_field<bool>(ProtocolPP::RSN);
        mybool = tmp4->get_field<bool>(ProtocolPP::NH);
        uint8_t my8 = tmp4->get_field<uint8_t>(ProtocolPP::PDUTYPE);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::HDREXT);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::PGKINDEX);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::SDUTYPE);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::BEARER);
        my8 = tmp4->get_field<uint8_t>(ProtocolPP::NH);
        uint16_t my16 = tmp4->get_field<uint16_t>(ProtocolPP::LENGTHIND);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::PTKINDENT);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::KDID);
        my16 = tmp4->get_field<uint16_t>(ProtocolPP::NH);
        uint32_t my32 = tmp4->get_field<uint32_t>(ProtocolPP::SEQNUM);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::HFNI);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::FMS);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NMP);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::HRW);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::FRESH);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::ICVLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::CKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::AKEYLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::BITMAPLEN);
        my32 = tmp4->get_field<uint32_t>(ProtocolPP::NH);
        ProtocolPP::jarray<uint8_t> myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::SUFI);
        myar = tmp4->get_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::BITMAP);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);
        myptr = tmp4->get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY);

        ProtocolPP::jarray<uint8_t> tmphdr(4,0);
        std::shared_ptr<ProtocolPP::jlte> mylte = std::make_shared<ProtocolPP::jlte>(myrand, tmp4, myreplay);
        mylte->set_hdr(tmphdr);
        tmphdr = mylte->get_hdr();

        uint64_t my64 = mylte->get_field(ProtocolPP::CKEYLEN);
        my64 = mylte->get_field(ProtocolPP::AKEYLEN);
        my64 = mylte->get_field(ProtocolPP::FRESH);
        my64 = mylte->get_field(ProtocolPP::ICVLEN);
        my64 = mylte->get_field(ProtocolPP::SEQNUM,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 5);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 7);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 12);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 15);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 16);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);
        mylte->set_field(ProtocolPP::SNLEN, 18);
        my64 = mylte->get_field(ProtocolPP::HFNI,tmphdr);
        my64 = mylte->get_field(ProtocolPP::FMS,tmphdr);
        my64 = mylte->get_field(ProtocolPP::RSN,tmphdr);
        my64 = mylte->get_field(ProtocolPP::NMP,tmphdr);
        my64 = mylte->get_field(ProtocolPP::HRW,tmphdr);
        my64 = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        my64 = mylte->get_field(ProtocolPP::BITMAPLEN,tmphdr);

        // set field
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::PDUTYPE, 1);
        mylte->set_field(ProtocolPP::POLLBIT, 1);
        mylte->set_field(ProtocolPP::EXTENSION, 1);
        mylte->set_field(ProtocolPP::SNLEN, 1);
        mylte->set_field(ProtocolPP::HDREXT, 1);
        mylte->set_field(ProtocolPP::LENGTHIND, 1);
        mylte->set_field(ProtocolPP::SEQNUM, 1);
        mylte->set_field(ProtocolPP::HFNI, 1);
        mylte->set_field(ProtocolPP::SUFI, 1);
        mylte->set_field(ProtocolPP::FMS, 1);
        mylte->set_field(ProtocolPP::PGKINDEX, 1);
        mylte->set_field(ProtocolPP::PTKINDENT, 1);
        mylte->set_field(ProtocolPP::SDUTYPE, 1);
        mylte->set_field(ProtocolPP::RSN, 1);
        mylte->set_field(ProtocolPP::KDID, 1);
        mylte->set_field(ProtocolPP::NMP, 1);
        mylte->set_field(ProtocolPP::HRW, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);
        mylte->set_field(ProtocolPP::DATACTRL, 1);

        // get field
        uint64_t myfield = 0;
        myfield = mylte->get_field(ProtocolPP::DATACTRL, tmphdr);
        myfield = mylte->get_field(ProtocolPP::PDUTYPE, tmphdr);
        myfield = mylte->get_field(ProtocolPP::POLLBIT, tmphdr);
        myfield = mylte->get_field(ProtocolPP::EXTENSION, tmphdr);
        myfield = mylte->get_field(ProtocolPP::SNLEN, tmphdr);
        myfield = mylte->get_field(ProtocolPP::HDREXT, tmphdr);
        myfield = mylte->get_field(ProtocolPP::LENGTHIND, tmphdr);
        myfield = mylte->get_field(ProtocolPP::SEQNUM, tmphdr);
        myfield = mylte->get_field(ProtocolPP::HFNI, tmphdr);
        myfield = mylte->get_field(ProtocolPP::SUFI, tmphdr);
        myfield = mylte->get_field(ProtocolPP::FMS, tmphdr);
        myfield = mylte->get_field(ProtocolPP::PGKINDEX, tmphdr);
        myfield = mylte->get_field(ProtocolPP::PTKINDENT, tmphdr);
        myfield = mylte->get_field(ProtocolPP::SDUTYPE, tmphdr);
        myfield = mylte->get_field(ProtocolPP::RSN, tmphdr);
        myfield = mylte->get_field(ProtocolPP::KDID, tmphdr);
        myfield = mylte->get_field(ProtocolPP::NMP, tmphdr);
        myfield = mylte->get_field(ProtocolPP::HRW, tmphdr);
        myfield = mylte->get_field(ProtocolPP::BITMAPLEN, tmphdr);

        myfield = mylte->get_field(ProtocolPP::DATACTRL);
        myfield = mylte->get_field(ProtocolPP::PDUTYPE);
        myfield = mylte->get_field(ProtocolPP::POLLBIT);
        myfield = mylte->get_field(ProtocolPP::EXTENSION);
        myfield = mylte->get_field(ProtocolPP::SNLEN);
        myfield = mylte->get_field(ProtocolPP::HDREXT);
        myfield = mylte->get_field(ProtocolPP::LENGTHIND);
        myfield = mylte->get_field(ProtocolPP::SEQNUM);
        myfield = mylte->get_field(ProtocolPP::HFNI);
        myfield = mylte->get_field(ProtocolPP::SUFI);
        myfield = mylte->get_field(ProtocolPP::FMS);
        myfield = mylte->get_field(ProtocolPP::PGKINDEX);
        myfield = mylte->get_field(ProtocolPP::PTKINDENT);
        myfield = mylte->get_field(ProtocolPP::SDUTYPE);
        myfield = mylte->get_field(ProtocolPP::RSN);
        myfield = mylte->get_field(ProtocolPP::KDID);
        myfield = mylte->get_field(ProtocolPP::NMP);
        myfield = mylte->get_field(ProtocolPP::HRW);
        myfield = mylte->get_field(ProtocolPP::BITMAPLEN);
    }

    void testblobcov() {
        uint64_t mydir = myrand->get_u64();
        uint32_t keylen = 32;
        ProtocolPP::jarray<uint8_t> bkek = myrand->getbyte(32);
        ProtocolPP::jarray<uint8_t> blobkey = myrand->getbyte(32);
        ProtocolPP::jarray<uint8_t> mydat = myrand->getbyte(32);
        ProtocolPP::jarray<uint8_t> myicv = myrand->getbyte(16);
        ProtocolPP::jarray<uint8_t> myiv = myrand->getbyte(8);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> blobdat = std::make_shared<ProtocolPP::jarray<uint8_t>>(blobkey);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> outdat = std::make_shared<ProtocolPP::jarray<uint8_t>>(0, blobdat->get_size());
        blobdat->append(mydat);
        blobdat->append(myicv);

        ProtocolPP::jmemblob myblob(myrand,
                                    bkek.get_ptr(),
                                    bkek.get_size(),
                                    blobkey.get_ptr(),
                                    blobkey.get_size());
        
        ProtocolPP::jarray<uint8_t> mypad = myblob.pad(ProtocolPP::pad_t::INCREMENT, 8);
        blobdat->append(mypad);
        blobdat->append(myiv);
        blobdat->append(bkek);
        myblob.set_hdr(bkek);
        myblob.set_field(ProtocolPP::DIRECTION, mydir);
        myblob.get_field(ProtocolPP::DIRECTION, bkek);
        myblob.decap_packet(blobdat,
                            outdat);
        ProtocolPP::jarray<uint8_t> hdr = myblob.get_hdr();

        ProtocolPP::jmemblobsa blob2;
        blob2.set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::ENCAP);
        blob2.set_field<uint32_t>(ProtocolPP::BKEKLEN, keylen);
        blob2.set_field<uint32_t>(ProtocolPP::BLOBKEYLEN, keylen);
        blob2.set_field<uint32_t>(ProtocolPP::DIRECTION, keylen);
        blob2.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::BKEK, bkek);
        blob2.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::BLOBKEY, blobkey);
        blob2.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHERKEY, blobkey);
        blob2.set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::BKEK, blobdat);
        blob2.set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::BLOBKEY, blobdat);
        blob2.set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, blobdat);

        ProtocolPP::direction_t blobdir = blob2.get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        uint8_t* myarray = blob2.get_field<uint8_t*>(ProtocolPP::NH);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = blob2.get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::BKEK);
        myptr = blob2.get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::BLOBKEY);
        myptr = blob2.get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);
        keylen = blob2.get_field<uint32_t>(ProtocolPP::BKEKLEN);
        keylen = blob2.get_field<uint32_t>(ProtocolPP::BLOBKEYLEN);
        keylen = blob2.get_field<uint32_t>(ProtocolPP::DIRECTION);
        ProtocolPP::jmemblobsa myblob2(blob2);
        ProtocolPP::jmemblob(myrand, myblob2);
    }

    void testconfsacov() {
        // confident security association tests
        uint8_t mylen2 = 32;
        uint32_t mylen = 32;
        ProtocolPP::cipher_t mycipher;
        ProtocolPP::direction_t mydir;
        ProtocolPP::jconfidentsa myconf;

        ProtocolPP::jarray<uint8_t> myhdr = myrand->getbyte(16);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
        myconf.set_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER, ProtocolPP::AES_CCM);
        myconf.set_field<ProtocolPP::cipher_t>(ProtocolPP::NH, ProtocolPP::AES_CCM);

        myconf.set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        myconf.set_field<ProtocolPP::direction_t>(ProtocolPP::CIPHER, ProtocolPP::ENCAP);

        myconf.set_field<uint32_t>(ProtocolPP::ICVLEN, mylen);
        myconf.set_field<uint32_t>(ProtocolPP::AADLEN, mylen);
        myconf.set_field<uint32_t>(ProtocolPP::COUNT, mylen);
        myconf.set_field<uint32_t>(ProtocolPP::BLOCKSIZE, mylen);
        myconf.set_field<uint32_t>(ProtocolPP::AUTH, mylen);

        myconf.set_field<uint8_t>(ProtocolPP::BEARER, mylen2);
        myconf.set_field<uint8_t>(ProtocolPP::CIPHER, mylen2);

        myconf.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::CIPHERKEY, myhdr);
        myconf.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::IV, myhdr);
        myconf.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, myhdr);

        myconf.set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::CIPHERKEY, myptr);
        myconf.set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::IV, myptr);
        myconf.set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, myptr);

        mycipher = myconf.get_field<ProtocolPP::cipher_t>(ProtocolPP::NH);
        mydir    = myconf.get_field<ProtocolPP::direction_t>(ProtocolPP::CIPHER);
        mylen2   = myconf.get_field<uint32_t>(ProtocolPP::AUTH);
        mylen2   = myconf.get_field<uint8_t>(ProtocolPP::AUTH);

        uint8_t* myhdr2 = myconf.get_field<uint8_t*>(ProtocolPP::NH);
        myptr = myconf.get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);

        ProtocolPP::jconfidentsa myconf2(myconf);
    }

    void testconfcov() {
        // confident tests
        std::shared_ptr<ProtocolPP::jconfidentsa> myconf = std::make_shared<ProtocolPP::jconfidentsa>();
        ProtocolPP::jconfident myconfig(myconf);

        uint32_t mylen = 32;
        uint8_t mybearer = 127;
        ProtocolPP::jarray<uint8_t> myhdr = myconfig.get_hdr();
        uint64_t nh = myconfig.get_field(ProtocolPP::DIRECTION, myhdr);
        myconfig.set_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER, ProtocolPP::AES_GCM);
        myconfig.set_field<ProtocolPP::cipher_t>(ProtocolPP::NH, ProtocolPP::AES_GCM);
        myconfig.set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENC);
        myconfig.set_field<ProtocolPP::direction_t>(ProtocolPP::NH, ProtocolPP::ENC);
        myconfig.set_field<uint32_t>(ProtocolPP::ICVLEN, mylen);
        myconfig.set_field<uint32_t>(ProtocolPP::AADLEN, mylen);
        myconfig.set_field<uint32_t>(ProtocolPP::COUNT, mylen);
        myconfig.set_field<uint32_t>(ProtocolPP::BLOCKSIZE, mylen);
        myconfig.set_field<uint32_t>(ProtocolPP::NH, mylen);
        myconfig.set_field<uint8_t>(ProtocolPP::BEARER, mybearer);
        myconfig.set_field<uint8_t>(ProtocolPP::NH, mybearer);
        myconfig.set_field(ProtocolPP::NH, nh);
        myconfig.set_hdr(myhdr);
        ProtocolPP::cipher_t mycipher = myconfig.get_field<ProtocolPP::cipher_t>(ProtocolPP::CIPHER);
        mycipher = myconfig.get_field<ProtocolPP::cipher_t>(ProtocolPP::DIRECTION);
        ProtocolPP::direction_t mydir = myconfig.get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = myconfig.get_field<ProtocolPP::direction_t>(ProtocolPP::NH);
        mylen = myconfig.get_field<uint32_t>(ProtocolPP::CKEYLEN);
        mylen = myconfig.get_field<uint32_t>(ProtocolPP::IVLEN);
        mylen = myconfig.get_field<uint32_t>(ProtocolPP::ICVLEN);
        mylen = myconfig.get_field<uint32_t>(ProtocolPP::AADLEN);
        mylen = myconfig.get_field<uint32_t>(ProtocolPP::COUNT);
        mylen = myconfig.get_field<uint32_t>(ProtocolPP::BLOCKSIZE);
        mylen = myconfig.get_field<uint32_t>(ProtocolPP::NH);
        mybearer = myconfig.get_field<uint8_t>(ProtocolPP::BEARER);
        mybearer = myconfig.get_field<uint8_t>(ProtocolPP::CIPHER);
    }

    void testintegsacov() {
        bool myflag = false;
        uint32_t mylen = 32;
        ProtocolPP::auth_t myauth;
        ProtocolPP::direction_t mydir;
        ProtocolPP::jintegritysa myconf;
        ProtocolPP::jarray<uint8_t> myhdr = myrand->getbyte(16);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myptr = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));

        myconf.set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::SHA256);
        myconf.set_field<ProtocolPP::auth_t>(ProtocolPP::NH, ProtocolPP::SHA256);

        myconf.set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        myconf.set_field<ProtocolPP::direction_t>(ProtocolPP::CIPHER, ProtocolPP::ENCAP);

        myconf.set_field<bool>(ProtocolPP::ZEROINIT, true);
        myconf.set_field<bool>(ProtocolPP::SWAPIN, false);
        myconf.set_field<bool>(ProtocolPP::SWAPOUT, true);
        myconf.set_field<bool>(ProtocolPP::COMPOUT, false);
        myconf.set_field<bool>(ProtocolPP::DIRECTION, true);

        myconf.set_field<uint32_t>(ProtocolPP::COUNT, mylen);
        myconf.set_field<uint32_t>(ProtocolPP::FRESH, mylen);
        myconf.set_field<uint32_t>(ProtocolPP::ICVLEN, mylen);
        myconf.set_field<uint32_t>(ProtocolPP::POLYNOMIAL, mylen);
        myconf.set_field<uint32_t>(ProtocolPP::AUTH, mylen);

        myconf.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::AUTHKEY, myhdr);
        myconf.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::IV, myhdr);
        myconf.set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::NH, myhdr);

        myconf.set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::AUTHKEY, myptr);
        myconf.set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::IV, myptr);
        myconf.set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH, myptr);

        myauth = myconf.get_field<ProtocolPP::auth_t>(ProtocolPP::CIPHER);
        mydir  = myconf.get_field<ProtocolPP::direction_t>(ProtocolPP::CIPHER);
        myflag = myconf.get_field<bool>(ProtocolPP::AUTH);
        mylen  = myconf.get_field<uint32_t>(ProtocolPP::AUTH);

        uint8_t* myptr2 = myconf.get_field<uint8_t*>(ProtocolPP::NH);
        myptr = myconf.get_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::NH);

        ProtocolPP::jintegritysa myconf2(myconf);
        ProtocolPP::jintegritysa myconf3(ProtocolPP::auth_t::CRC5_USB);
        ProtocolPP::jintegritysa myconf4(ProtocolPP::auth_t::CRC7_UTMS);
        ProtocolPP::jintegritysa myconf5(ProtocolPP::auth_t::CRC8_LTE);
        ProtocolPP::jintegritysa myconf6(ProtocolPP::auth_t::CRC11_UTMS);
        ProtocolPP::jintegritysa myconf7(ProtocolPP::auth_t::CRC12_UTMS);
        ProtocolPP::jintegritysa myconf8(ProtocolPP::auth_t::CRC16_IBM);
        ProtocolPP::jintegritysa myconf9(ProtocolPP::auth_t::CRC16_CCITT);
        ProtocolPP::jintegritysa myconf10(ProtocolPP::auth_t::CRC24_LTE_A);
        ProtocolPP::jintegritysa myconf100(ProtocolPP::auth_t::CRC24_LTE_B);
        ProtocolPP::jintegritysa myconf101(ProtocolPP::auth_t::CRC64_ISO);
        ProtocolPP::jintegritysa myconf102(ProtocolPP::auth_t::CRC64_ECMA);
        ProtocolPP::jintegritysa myconf11(ProtocolPP::auth_t::POLY1305);

        ProtocolPP::jintegritysa myconf12(ProtocolPP::auth_t::CRC5_USB,
                                          0x00000005,
                                          5,
                                          true,
                                          false,
                                          false,
                                          true);

        ProtocolPP::jintegritysa myconf13(ProtocolPP::auth_t::CRC7_UTMS,
                                          0x00000035,
                                          7,
                                          true,
                                          false,
                                          false,
                                          true);

        ProtocolPP::jintegritysa myconf14(ProtocolPP::auth_t::CRC8_LTE,
                                          0x00000075,
                                          8,
                                          true,
                                          false,
                                          false,
                                          true);

        ProtocolPP::jintegritysa myconf15(ProtocolPP::auth_t::CRC11_UTMS,
                                          0x00000335,
                                          11,
                                          true,
                                          true,
                                          true,
                                          true);

        ProtocolPP::jintegritysa myconf16(ProtocolPP::auth_t::CRC12_UTMS,
                                          0x00000735,
                                          12,
                                          false,
                                          false,
                                          false,
                                          true);

        ProtocolPP::jintegritysa myconf17(ProtocolPP::auth_t::CRC16_IBM,
                                          0x00007F35,
                                          16,
                                          true,
                                          false,
                                          false,
                                          true);

        ProtocolPP::jintegritysa myconf18(ProtocolPP::auth_t::CRC16_CCITT,
                                          0x00007735,
                                          16,
                                          true,
                                          false,
                                          false,
                                          true);

        ProtocolPP::jintegritysa myconf19(ProtocolPP::auth_t::CRC24_LTE_A,
                                          0x00717735,
                                          24,
                                          true,
                                          false,
                                          false,
                                          true);

        ProtocolPP::jintegritysa myconf20(ProtocolPP::auth_t::CRC32_IETF,
                                          0x12345678,
                                          32,
                                          true,
                                          false,
                                          false,
                                          true);

        ProtocolPP::jintegritysa myconf21(ProtocolPP::auth_t::CRC32_IEEE,
                                          0x1F345678,
                                          32,
                                          true,
                                          false,
                                          false,
                                          true);

        ProtocolPP::jintegritysa myconf22(ProtocolPP::auth_t::CRC_POLY,
                                          0x1F345678,
                                          32,
                                          true,
                                          false,
                                          false,
                                          true);
    }

    void testintegcov() {
        std::shared_ptr<ProtocolPP::jintegritysa> myconf = std::make_shared<ProtocolPP::jintegritysa>();
        ProtocolPP::jintegrity myinteg(myconf);
        
        ProtocolPP::jarray<uint8_t> myhdr = myinteg.get_hdr();
        myinteg.set_hdr(myhdr);

        ProtocolPP::direction_t mydir = ProtocolPP::ENCAP;
        ProtocolPP::auth_t myauth = ProtocolPP::SHA256;
        uint32_t mycnt   = myrand->get_u32();
        uint32_t myfresh = myrand->get_u32();

        uint64_t mydbl = myinteg.get_field(ProtocolPP::CIPHER, myhdr);
        myinteg.set_field(ProtocolPP::AUTH, mydbl);

        myinteg.set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, mydir);
        myinteg.set_field<ProtocolPP::direction_t>(ProtocolPP::CIPHER, mydir);

        myinteg.set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, myauth);
        myinteg.set_field<ProtocolPP::auth_t>(ProtocolPP::CIPHER, myauth);

        myinteg.set_field<uint32_t>(ProtocolPP::ICVLEN, 16);
        myinteg.set_field<uint32_t>(ProtocolPP::IVLEN, 12);
        myinteg.set_field<uint32_t>(ProtocolPP::COUNT, mycnt);
        myinteg.set_field<uint32_t>(ProtocolPP::FRESH, myfresh);
        myinteg.set_field<uint32_t>(ProtocolPP::CIPHER, 16);

        mydir = myinteg.get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        mydir = myinteg.get_field<ProtocolPP::direction_t>(ProtocolPP::CIPHER);

        myauth = myinteg.get_field<ProtocolPP::auth_t>(ProtocolPP::AUTH);
        myauth = myinteg.get_field<ProtocolPP::auth_t>(ProtocolPP::CIPHER);

        mycnt = myinteg.get_field<uint32_t>(ProtocolPP::ICVLEN);
        mycnt = myinteg.get_field<uint32_t>(ProtocolPP::IVLEN);
        mycnt = myinteg.get_field<uint32_t>(ProtocolPP::AKEYLEN);
        myfresh = myinteg.get_field<uint32_t>(ProtocolPP::COUNT);
        mycnt = myinteg.get_field<uint32_t>(ProtocolPP::FRESH);
        mycnt = myinteg.get_field<uint32_t>(ProtocolPP::CIPHER);
    }

    void testrsasacov() {
        int bitsize = 8192;
        ProtocolPP::jrsasa myrsasa;
        ProtocolPP::rsaenc_t myenc;
        ProtocolPP::keymode_t mymode;
        ProtocolPP::rsapadtype_t mypad;
        CryptoPP::RSA::PrivateKey prvKey;
        CryptoPP::RSA::PublicKey pubKey;
        CryptoPP::AutoSeededRandomPool m_rng;
        std::shared_ptr<ProtocolPP::jrsasa> myrsasaptr = std::make_shared<ProtocolPP::jrsasa>();

        prvKey.GenerateRandomWithKeySize(m_rng, 4096);
        pubKey = CryptoPP::RSA::PublicKey(prvKey);

        ProtocolPP::jrsasa myrsasa2(4096,
                                    ProtocolPP::keymode_t::GENKEYPAIR,
                                    ProtocolPP::rsapadtype_t::PKCS15,
                                    ProtocolPP::rsaenc_t::PKCS);

        ProtocolPP::jrsasa myrsasa3(4096,
                                    ProtocolPP::keymode_t::GENKEYPAIR,
                                    ProtocolPP::rsapadtype_t::PKCS15,
                                    ProtocolPP::rsaenc_t::PKCS,
                                    prvKey,
                                    pubKey);

        ProtocolPP::jrsasa myrsasa4(myrsasa3);
        ProtocolPP::jrsasa myrsasa5(myrsasaptr);

        myrsasa.set_field<int>(ProtocolPP::BITSIZE, bitsize);
        myrsasa.set_field<int>(ProtocolPP::CIPHER, bitsize);
        myrsasa.set_field<CryptoPP::RSA::PrivateKey>(ProtocolPP::PRVKEY, prvKey);
        myrsasa.set_field<CryptoPP::RSA::PrivateKey>(ProtocolPP::CIPHER, prvKey);
        myrsasa.set_field<CryptoPP::RSA::PublicKey>(ProtocolPP::PUBKEY, pubKey);
        myrsasa.set_field<CryptoPP::RSA::PublicKey>(ProtocolPP::AUTH, pubKey);

        myrsasa.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::keymode_t::PKISIGN);
        myrsasa.set_field<ProtocolPP::keymode_t>(ProtocolPP::CIPHER, ProtocolPP::keymode_t::PKISIGN);

        myrsasa.set_field<ProtocolPP::rsapadtype_t>(ProtocolPP::RSAPAD, ProtocolPP::rsapadtype_t::PSS);
        myrsasa.set_field<ProtocolPP::rsapadtype_t>(ProtocolPP::CIPHER, ProtocolPP::rsapadtype_t::PKCS15);

        myrsasa.set_field<ProtocolPP::rsaenc_t>(ProtocolPP::RSAENC, ProtocolPP::rsaenc_t::OAEP_SHA);
        myrsasa.set_field<ProtocolPP::rsaenc_t>(ProtocolPP::CIPHER, ProtocolPP::rsaenc_t::PKCS);

        bitsize = myrsasa.get_field<int>(ProtocolPP::BITSIZE);
        bitsize = myrsasa.get_field<int>(ProtocolPP::AUTH);

        CryptoPP::RSA::PrivateKey prvKey2 = myrsasa.get_field<CryptoPP::RSA::PrivateKey>(ProtocolPP::PRVKEY);
        prvKey2 = myrsasa.get_field<CryptoPP::RSA::PrivateKey>(ProtocolPP::DIRECTION);

        CryptoPP::RSA::PublicKey pubKey2 = myrsasa.get_field<CryptoPP::RSA::PublicKey>(ProtocolPP::PUBKEY);
        pubKey2 = myrsasa.get_field<CryptoPP::RSA::PublicKey>(ProtocolPP::DIRECTION);

        mymode = myrsasa.get_field<ProtocolPP::keymode_t>(ProtocolPP::MODE);
        mymode = myrsasa.get_field<ProtocolPP::keymode_t>(ProtocolPP::CIPHER);

        mypad = myrsasa.get_field<ProtocolPP::rsapadtype_t>(ProtocolPP::RSAPAD);
        mypad = myrsasa.get_field<ProtocolPP::rsapadtype_t>(ProtocolPP::CIPHER);

        myenc = myrsasa.get_field<ProtocolPP::rsaenc_t>(ProtocolPP::RSAENC);
        myenc = myrsasa.get_field<ProtocolPP::rsaenc_t>(ProtocolPP::CIPHER);
    }

    void testrsacov() {
        int bitsize = 3072;
        uint64_t mydata = 0;
        ProtocolPP::jrsasa myrsasa;
        ProtocolPP::rsaenc_t myenc;
        ProtocolPP::keymode_t mymode;
        ProtocolPP::rsapadtype_t mypad;
        CryptoPP::RSA::PrivateKey prvKey;
        CryptoPP::RSA::PublicKey pubKey;
        CryptoPP::AutoSeededRandomPool m_rng;
        ProtocolPP::jarray<uint8_t> myhdr = myrand->getbyte(16);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mymsg = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(256));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mydec = std::make_shared<ProtocolPP::jarray<uint8_t>>(512,0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myexp = std::make_shared<ProtocolPP::jarray<uint8_t>>(256,0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mysig = std::make_shared<ProtocolPP::jarray<uint8_t>>(501,0);

        prvKey.GenerateRandomWithKeySize(m_rng, 4096);
        pubKey = CryptoPP::RSA::PublicKey(prvKey);

        std::shared_ptr<ProtocolPP::jrsasa> myrsasaptr = std::make_shared<ProtocolPP::jrsasa>();
        std::pair<CryptoPP::RSA::PrivateKey,CryptoPP::RSA::PublicKey> keypair(prvKey,pubKey);

        ProtocolPP::jrsa myrsa;

        ProtocolPP::jrsa myrsa2(4096,
                                ProtocolPP::rsapadtype_t::PKCS15);

        ProtocolPP::jrsa myrsa3(4096,
                                ProtocolPP::rsapadtype_t::PKCS15,
                                prvKey,
                                pubKey);

        ProtocolPP::jrsa myrsa6(4096,
                                ProtocolPP::rsapadtype_t::PSS,
                                prvKey,
                                pubKey);

        ProtocolPP::jrsa myrsa4(myrsasaptr);

        myrsa3.encrypt(mymsg, mydec);
        myrsa3.decrypt(mydec, myexp);

        myrsa3.sign(mymsg, mysig);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myveri = std::make_shared<ProtocolPP::jarray<uint8_t>>(*mymsg);
        myveri->append(*mysig);
        myrsa3.verify(myveri);

        myrsa6.encrypt(mymsg, mydec);
        myrsa6.decrypt(mydec, myexp);

        myrsa6.sign(mymsg, mysig);
        myveri = std::make_shared<ProtocolPP::jarray<uint8_t>>(*mymsg);
        myveri->append(*mysig);
        myrsa6.verify(myveri);

        myrsa2.gen_keypair();
        myrsa2.set_field<int>(ProtocolPP::BITSIZE, bitsize);
        myrsa2.set_field<int>(ProtocolPP::CIPHER, bitsize);

        myrsa2.set_field<ProtocolPP::rsapadtype_t>(ProtocolPP::RSAPAD, ProtocolPP::PSS);
        myrsa2.set_field<ProtocolPP::rsapadtype_t>(ProtocolPP::BITSIZE, ProtocolPP::PSS);

        myrsa2.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::RSAENCRYPT);
        myrsa2.set_field<ProtocolPP::keymode_t>(ProtocolPP::NH, ProtocolPP::RSAENCRYPT);

        myrsa2.set_field<ProtocolPP::rsaenc_t>(ProtocolPP::RSAENC, ProtocolPP::PKCS);
        myrsa2.set_field<ProtocolPP::rsaenc_t>(ProtocolPP::BITSIZE, ProtocolPP::PKCS);

        bitsize = myrsa2.get_field<int>(ProtocolPP::BITSIZE);
        bitsize = myrsa2.get_field<int>(ProtocolPP::CIPHER);

        mypad = myrsa2.get_field<ProtocolPP::rsapadtype_t>(ProtocolPP::RSAPAD);
        mypad = myrsa2.get_field<ProtocolPP::rsapadtype_t>(ProtocolPP::BITSIZE);

        mymode = myrsa2.get_field<ProtocolPP::keymode_t>(ProtocolPP::MODE);
        mymode = myrsa2.get_field<ProtocolPP::keymode_t>(ProtocolPP::NH);

        myenc = myrsa2.get_field<ProtocolPP::rsaenc_t>(ProtocolPP::RSAENC);
        myenc = myrsa2.get_field<ProtocolPP::rsaenc_t>(ProtocolPP::BITSIZE);

        myrsa2.get_security(myrsasaptr);

        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myout = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        myrsa2.set_hdr(myhdr);
        myhdr = myrsa2.get_hdr();
        mydata = myrsa2.get_field(ProtocolPP::BITSIZE, myhdr);
        myrsa2.set_field(ProtocolPP::DIRECTION, mydata);
        myrsa2.encap_packet(myveri, myout);
        myrsa2.decap_packet(myout, myveri);
        myrsa3.encap_packet(myveri, myout);
        myrsa3.decap_packet(myout, myveri);
        myrsa6.encap_packet(myveri, myout);
        myrsa6.decap_packet(myout, myveri);

        prvKey = myrsa2.get_field<CryptoPP::RSA::PrivateKey>(ProtocolPP::PRVKEY);
        prvKey = myrsa2.get_field<CryptoPP::RSA::PrivateKey>(ProtocolPP::AUTH);

        pubKey = myrsa2.get_field<CryptoPP::RSA::PublicKey>(ProtocolPP::PUBKEY);
        pubKey = myrsa2.get_field<CryptoPP::RSA::PublicKey>(ProtocolPP::AUTH);

        keypair = myrsa2.get_field<std::pair<CryptoPP::RSA::PrivateKey,CryptoPP::RSA::PublicKey>>(ProtocolPP::KEYPAIR);
        keypair = myrsa2.get_field<std::pair<CryptoPP::RSA::PrivateKey,CryptoPP::RSA::PublicKey>>(ProtocolPP::CIPHER);

        std::shared_ptr<ProtocolPP::jrsa> rsa10 = ProtocolPP::jprotocolpp::get_rsa(myrsasaptr);
    }

    void testdsasacov() {
        int bitsize = 8192;
        ProtocolPP::jdsasa mydsasa;
        ProtocolPP::keymode_t mymode;
        CryptoPP::DSA::PrivateKey prvKey;
        CryptoPP::DSA::PublicKey pubKey;
        CryptoPP::AutoSeededRandomPool m_rng;
        CryptoPP::Integer prime = myrand->get_u64();
        CryptoPP::Integer subprime = myrand->get_u64();
        CryptoPP::Integer generator = myrand->get_u64();
        std::shared_ptr<ProtocolPP::jdsasa> mydsasaptr = std::make_shared<ProtocolPP::jdsasa>();

        prime     |= 0x0000000000000001ull;
        subprime  |= 0x0000000000000001ull;
        generator |= 0x0000000000000001ull;

        prvKey.Initialize(m_rng, 3072);
        pubKey.AssignFrom(prvKey);

        ProtocolPP::jdsasa mydsasa2(3072,
                                    ProtocolPP::keymode_t::GENKEYPAIR);

        ProtocolPP::jdsasa mydsasa3(3072,
                                    ProtocolPP::keymode_t::GENKEYPAIR,
                                    prvKey,
                                    pubKey);

        ProtocolPP::jdsasa mydsasa6(4096,
                                    ProtocolPP::keymode_t::GENKEYPAIR,
                                    prime,
                                    subprime,
                                    generator);

        ProtocolPP::jdsasa mydsasa4(mydsasa3);
        ProtocolPP::jdsasa mydsasa5(mydsasaptr);

        mydsasa.set_field<int>(ProtocolPP::BITSIZE, bitsize);
        mydsasa.set_field<int>(ProtocolPP::AUTH, bitsize);

        mydsasa.set_field<CryptoPP::DSA::PrivateKey>(ProtocolPP::PRVKEY, prvKey);
        mydsasa.set_field<CryptoPP::DSA::PrivateKey>(ProtocolPP::CIPHER, prvKey);

        mydsasa.set_field<CryptoPP::DSA::PublicKey>(ProtocolPP::PUBKEY, pubKey);
        mydsasa.set_field<CryptoPP::DSA::PublicKey>(ProtocolPP::AUTH, pubKey);

        mydsasa.set_field<CryptoPP::Integer>(ProtocolPP::PRIME, prime);
        mydsasa.set_field<CryptoPP::Integer>(ProtocolPP::SUBPRIME, subprime);
        mydsasa.set_field<CryptoPP::Integer>(ProtocolPP::GENERATOR, generator);
        mydsasa.set_field<CryptoPP::Integer>(ProtocolPP::CIPHER, generator);

        mydsasa.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::keymode_t::PKISIGN);
        mydsasa.set_field<ProtocolPP::keymode_t>(ProtocolPP::CIPHER, ProtocolPP::keymode_t::PKISIGN);

        bitsize = mydsasa.get_field<int>(ProtocolPP::BITSIZE);
        bitsize = mydsasa.get_field<int>(ProtocolPP::AUTH);

        CryptoPP::DSA::PrivateKey prvKey2 = mydsasa.get_field<CryptoPP::DSA::PrivateKey>(ProtocolPP::PRVKEY);
        prvKey2 = mydsasa.get_field<CryptoPP::DSA::PrivateKey>(ProtocolPP::DIRECTION);

        CryptoPP::DSA::PublicKey pubKey2 = mydsasa.get_field<CryptoPP::DSA::PublicKey>(ProtocolPP::PUBKEY);
        pubKey2 = mydsasa.get_field<CryptoPP::DSA::PublicKey>(ProtocolPP::DIRECTION);

        mymode = mydsasa.get_field<ProtocolPP::keymode_t>(ProtocolPP::MODE);
        mymode = mydsasa.get_field<ProtocolPP::keymode_t>(ProtocolPP::CIPHER);
        prime  = mydsasa.get_field<CryptoPP::Integer>(ProtocolPP::CIPHER);
    }

    void testdsacov() {
        int bitsize = 4096;
        uint64_t mydata = 0;
        ProtocolPP::jdsasa mydsasa;
        ProtocolPP::keymode_t mymode;
        CryptoPP::DSA::PrivateKey prvKey;
        CryptoPP::DSA::PublicKey pubKey;
        CryptoPP::AutoSeededRandomPool m_rng;
        CryptoPP::Integer prime = myrand->get_u64();
        CryptoPP::Integer subprime = myrand->get_u64();
        CryptoPP::Integer generator = myrand->get_u64();
        ProtocolPP::jarray<uint8_t> myhdr = myrand->getbyte(16);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mymsg = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(500));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mysig = std::make_shared<ProtocolPP::jarray<uint8_t>>(500,0);

        prime     |= 0x0000000000000001ull;
        subprime  |= 0x0000000000000001ull;
        generator |= 0x0000000000000001ull;

        prvKey.Initialize(m_rng, 3072);
        pubKey.AssignFrom(prvKey);
        std::pair<CryptoPP::DSA::PrivateKey,CryptoPP::DSA::PublicKey> keypair(prvKey,pubKey);

        std::string log = "./mypp.log";
        std::shared_ptr<ProtocolPP::jdsasa> mydsasaptr = std::make_shared<ProtocolPP::jdsasa>();

        ProtocolPP::jdsa mydsa2(3072);

        ProtocolPP::jdsa mydsa3(3072,
                                prvKey,
                                pubKey);

        ProtocolPP::jdsa mydsa5(3072,
                                keypair);

        ProtocolPP::jdsa mydsa7(3072,
                                prime,
                                subprime,
                                generator);

        ProtocolPP::jdsa mydsa4(mydsasaptr);

        mydsa3.sign(mymsg, mysig);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myveri = std::make_shared<ProtocolPP::jarray<uint8_t>>(*mymsg);
        myveri->append(*mysig);
        mydsa3.verify(myveri);

        mydsa5.sign(mymsg, mysig);
        myveri = std::make_shared<ProtocolPP::jarray<uint8_t>>(*mymsg);
        myveri->append(*mysig);
        mydsa5.verify(myveri);

        mydsa2.gen_keypair();
        mydsa2.set_field<int>(ProtocolPP::BITSIZE, bitsize);
        mydsa2.set_field<int>(ProtocolPP::CIPHER, bitsize);

        mydsa2.set_field<CryptoPP::DSA::PrivateKey>(ProtocolPP::PRVKEY, prvKey);
        mydsa2.set_field<CryptoPP::DSA::PrivateKey>(ProtocolPP::CIPHER, prvKey);

        mydsa2.set_field<CryptoPP::DSA::PublicKey>(ProtocolPP::PUBKEY, pubKey);
        mydsa2.set_field<CryptoPP::DSA::PublicKey>(ProtocolPP::AUTH, pubKey);

        mydsa2.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::PKISIGN);
        mydsa2.set_field<ProtocolPP::keymode_t>(ProtocolPP::NH, ProtocolPP::RSAENCRYPT);

        mydsa2.set_field<CryptoPP::Integer>(ProtocolPP::PRIME, prime);
        mydsa2.set_field<CryptoPP::Integer>(ProtocolPP::SUBPRIME, subprime);
        mydsa2.set_field<CryptoPP::Integer>(ProtocolPP::GENERATOR, generator);
        mydsa2.set_field<CryptoPP::Integer>(ProtocolPP::CIPHER, generator);

        bitsize = mydsa2.get_field<int>(ProtocolPP::BITSIZE);
        bitsize = mydsa2.get_field<int>(ProtocolPP::CIPHER);

        mymode = mydsa2.get_field<ProtocolPP::keymode_t>(ProtocolPP::MODE);
        mymode = mydsa2.get_field<ProtocolPP::keymode_t>(ProtocolPP::NH);

        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myout = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        mydsa2.get_security(mydsasaptr);
        mydsa2.encap_packet(myveri, myout);
        mydsa2.decap_packet(myout, myveri);
        mydsa3.encap_packet(myveri, myout);
        mydsa3.decap_packet(myout, myveri);
        mydsa5.encap_packet(myveri, myout);
        mydsa5.decap_packet(myout, myveri);

        mydsa2.set_hdr(myhdr);
        myhdr  = mydsa2.get_hdr();
        mydata = mydsa2.get_field(ProtocolPP::BITSIZE, myhdr);
        mydsa2.set_field(ProtocolPP::DIRECTION, mydata);

        prvKey = mydsa2.get_field<CryptoPP::DSA::PrivateKey>(ProtocolPP::PRVKEY);
        prvKey = mydsa2.get_field<CryptoPP::DSA::PrivateKey>(ProtocolPP::AUTH);

        pubKey = mydsa2.get_field<CryptoPP::DSA::PublicKey>(ProtocolPP::PUBKEY);
        pubKey = mydsa2.get_field<CryptoPP::DSA::PublicKey>(ProtocolPP::AUTH);

        prime     = mydsa2.get_field<CryptoPP::Integer>(ProtocolPP::PRIME);
        subprime  = mydsa2.get_field<CryptoPP::Integer>(ProtocolPP::SUBPRIME);
        generator = mydsa2.get_field<CryptoPP::Integer>(ProtocolPP::GENERATOR);
        prime     = mydsa2.get_field<CryptoPP::Integer>(ProtocolPP::CIPHER);

        std::shared_ptr<ProtocolPP::jdsa> dsa10 = ProtocolPP::jprotocolpp::get_dsa(mydsasaptr);
    }

    void testecdsaedcov() {
        ProtocolPP::ike_hash_t myhash = ProtocolPP::ike_hash_t::HASH_SHA2_512;
        ProtocolPP::keymode_t mymode = ProtocolPP::keymode_t::GENKEYPAIR;
        CryptoPP::OID curve = CryptoPP::ASN1::curve25519();

        // constructors
        ProtocolPP::jecdsaedsa mydsasa(mymode,
                                       myhash,
                                       curve);

        ProtocolPP::jecdsaedsa noptrsa;
        std::shared_ptr<ProtocolPP::jecdsaedsa> ptrsa;

        ProtocolPP::jecdsaed tmp(myhash,
                                 curve);
    
        uint64_t myval = 0;
        ProtocolPP::jarray<uint8_t> myhdr(20,0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> in = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte("50"));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> out = std::make_shared<ProtocolPP::jarray<uint8_t>>(50, 0x00);

        // unused functions
        tmp.set_hdr(myhdr);
        tmp.set_field(ProtocolPP::DIRECTION, myval);
        myval = tmp.get_field(ProtocolPP::DIRECTION, myhdr);
        myhdr = tmp.get_hdr();
        tmp.encap_packet(in, out);
        tmp.decap_packet(out, in);

        // private key container
        CryptoPP::ed25519PrivateKey prvKey;

        // public key container
        CryptoPP::ed25519PublicKey pubKey;

        // create signing object
        CryptoPP::AutoSeededRandomPool rng;
        CryptoPP::ed25519::Signer signer;
        signer.AccessPrivateKey().GenerateRandom(rng);
        CryptoPP::ed25519::Verifier verifier(signer);

        // set and get methods
        prvKey = tmp.get_field<CryptoPP::ed25519PrivateKey>(ProtocolPP::PRVKEY);
        tmp.set_field<CryptoPP::ed25519PrivateKey>(ProtocolPP::PRVKEY, prvKey);

        pubKey = tmp.get_field<CryptoPP::ed25519PublicKey>(ProtocolPP::PUBKEY);
        tmp.set_field<CryptoPP::ed25519PublicKey>(ProtocolPP::PUBKEY, pubKey);

        CryptoPP::OID mycur = tmp.get_field<CryptoPP::OID>(ProtocolPP::CURVE);
        mycur = tmp.get_field<CryptoPP::OID>(ProtocolPP::NH);

        tmp.set_field<CryptoPP::OID>(ProtocolPP::CURVE, CryptoPP::ASN1::curve25519());
        tmp.set_field<CryptoPP::OID>(ProtocolPP::NH, CryptoPP::ASN1::curve25519());

        ProtocolPP::ike_hash_t hashme = tmp.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH);
        tmp.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH, hashme);
        hashme = tmp.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::AUTH);

        tmp.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::AUTH, ProtocolPP::ike_hash_t::HASH_SHA2_512);
        tmp.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::AUTH, ProtocolPP::ike_hash_t::HASH_SHA2_512);

        ProtocolPP::keymode_t modeme = tmp.get_field<ProtocolPP::keymode_t>(ProtocolPP::MODE);
        modeme = tmp.get_field<ProtocolPP::keymode_t>(ProtocolPP::ECHASH);

        tmp.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::PKISIGN);
        tmp.set_field<ProtocolPP::keymode_t>(ProtocolPP::ECHASH, ProtocolPP::PKIVERIFY);

        ProtocolPP::jecdsaedsa mydsaed3(noptrsa);

        mydsaed3.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::PKISIGN);
        mydsaed3.set_field<ProtocolPP::keymode_t>(ProtocolPP::ECHASH, ProtocolPP::PKIVERIFY);

        mydsaed3.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH, ProtocolPP::ike_hash_t::HASH_SHA2_512);
        mydsaed3.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::AUTH, ProtocolPP::ike_hash_t::HASH_SHA2_512);

        mydsaed3.set_field<CryptoPP::OID>(ProtocolPP::CURVE, CryptoPP::ASN1::curve25519());
        mydsaed3.set_field<CryptoPP::OID>(ProtocolPP::NH, CryptoPP::ASN1::curve25519());

        mydsaed3.set_field<CryptoPP::ed25519PrivateKey>(ProtocolPP::PRVKEY, prvKey);
        mydsaed3.set_field<CryptoPP::ed25519PrivateKey>(ProtocolPP::PUBKEY, prvKey);

        mydsaed3.set_field<CryptoPP::ed25519PublicKey>(ProtocolPP::PUBKEY, pubKey);
        mydsaed3.set_field<CryptoPP::ed25519PublicKey>(ProtocolPP::PRVKEY, pubKey);

        mydsaed3.set_field<CryptoPP::ed25519::Signer>(ProtocolPP::SIGNER, signer);
        mydsaed3.set_field<CryptoPP::ed25519::Signer>(ProtocolPP::VERIFIER, signer);

        mydsaed3.set_field<CryptoPP::ed25519::Verifier>(ProtocolPP::VERIFIER, verifier);
        mydsaed3.set_field<CryptoPP::ed25519::Verifier>(ProtocolPP::SIGNER, verifier);

        mydsaed3.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::PKISIGN);
        mydsaed3.set_field<ProtocolPP::keymode_t>(ProtocolPP::ECHASH, ProtocolPP::PKIVERIFY);

        modeme = mydsaed3.get_field<ProtocolPP::keymode_t>(ProtocolPP::MODE);
        modeme = mydsaed3.get_field<ProtocolPP::keymode_t>(ProtocolPP::ECHASH);

        hashme = mydsaed3.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH);
        hashme = mydsaed3.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::AUTH);

        mycur = mydsaed3.get_field<CryptoPP::OID>(ProtocolPP::CURVE);
        mycur = mydsaed3.get_field<CryptoPP::OID>(ProtocolPP::NH);

        prvKey = mydsaed3.get_field<CryptoPP::ed25519PrivateKey>(ProtocolPP::PRVKEY);
        prvKey = mydsaed3.get_field<CryptoPP::ed25519PrivateKey>(ProtocolPP::PUBKEY);

        pubKey = mydsaed3.get_field<CryptoPP::ed25519PublicKey>(ProtocolPP::PUBKEY);
        pubKey = mydsaed3.get_field<CryptoPP::ed25519PublicKey>(ProtocolPP::PRVKEY);

        signer = mydsaed3.get_field<CryptoPP::ed25519::Signer>(ProtocolPP::SIGNER);
        signer = mydsaed3.get_field<CryptoPP::ed25519::Signer>(ProtocolPP::VERIFIER);

        verifier = mydsaed3.get_field<CryptoPP::ed25519::Verifier>(ProtocolPP::VERIFIER);
        verifier = mydsaed3.get_field<CryptoPP::ed25519::Verifier>(ProtocolPP::SIGNER);

        // get security association
        tmp.get_security(ptrsa);
        ProtocolPP::jecdsaedsa mydsaed4(ptrsa);
    }

    void testecdsafpcov() {
        int bitsize = 8192;
        ProtocolPP::jecdsafpsa mydsasa;
        ProtocolPP::keymode_t mymode;
        CryptoPP::OID curve = CryptoPP::ASN1::secp256r1();
        CryptoPP::OID curve4 = CryptoPP::ASN1::secp384r1();
        CryptoPP::OID curve5 = CryptoPP::ASN1::secp521r1();

        uint64_t myval = 0;
        ProtocolPP::jarray<uint8_t> myhdr(20,0);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> in = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte("50"));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> out = std::make_shared<ProtocolPP::jarray<uint8_t>>(50, 0x00);

        // private key container
        CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey prvKey;
        CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA384>::PrivateKey prvKey4;
        CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA512>::PrivateKey prvKey5;

        // public key container
        CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey pubKey;
        CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA384>::PublicKey pubKey4;
        CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA512>::PublicKey pubKey5;

        CryptoPP::AutoSeededRandomPool m_rng;
        std::shared_ptr<ProtocolPP::jecdsafpsa> mydsasaptr = std::make_shared<ProtocolPP::jecdsafpsa>();

        prvKey.Initialize(m_rng, curve);
        prvKey.MakePublicKey(pubKey);

        mydsasa.set_prvkey256(prvKey);
        mydsasa.set_pubkey256(pubKey);

        mydsasaptr->set_prvkey256(prvKey);
        mydsasaptr->set_pubkey256(pubKey);

        mydsasaptr->set_prvkey384(prvKey);
        mydsasaptr->set_pubkey384(pubKey);

        mydsasaptr->set_prvkey512(prvKey);
        mydsasaptr->set_pubkey512(pubKey);

        ProtocolPP::jecdsafpsa mydsasa2;

        ProtocolPP::jecdsafpsa mydsasa3(ProtocolPP::keymode_t::GENKEYPAIR,
                                        ProtocolPP::ike_hash_t::HASH_SHA2_256,
                                        curve);

        ProtocolPP::jecdsafpsa mydsasa384(ProtocolPP::keymode_t::GENKEYPAIR,
                                          ProtocolPP::ike_hash_t::HASH_SHA2_384,
                                          curve);

        ProtocolPP::jecdsafpsa mydsasa512(ProtocolPP::keymode_t::GENKEYPAIR,
                                          ProtocolPP::ike_hash_t::HASH_SHA2_512,
                                          curve);

        ProtocolPP::jecdsafpsa mydsasa4(mydsasa3);
        ProtocolPP::jecdsafpsa mydsasa40(mydsasa384);
        ProtocolPP::jecdsafpsa mydsasa400(mydsasa512);
        ProtocolPP::jecdsafpsa mydsasa5(mydsasaptr);

        std::shared_ptr<ProtocolPP::jecdsafpsa> mydsasaptr40 = std::make_shared<ProtocolPP::jecdsafpsa>(mydsasa40);
        std::shared_ptr<ProtocolPP::jecdsafpsa> mydsasaptr400 = std::make_shared<ProtocolPP::jecdsafpsa>(mydsasa400);
        ProtocolPP::jecdsafpsa mydsasa50(mydsasaptr40);
        ProtocolPP::jecdsafpsa mydsasa500(mydsasaptr400);

        mydsasa.set_field<int>(ProtocolPP::BITSIZE, bitsize);
        mydsasa.set_field<int>(ProtocolPP::AUTH, bitsize);

        mydsasa.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH, ProtocolPP::ike_hash_t::HASH_SHA2_384);
        mydsasa.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::AUTH, ProtocolPP::ike_hash_t::HASH_SHA2_384);

        mydsasa.set_field<CryptoPP::OID>(ProtocolPP::CURVE, CryptoPP::ASN1::secp384r1());
        mydsasa.set_field<CryptoPP::OID>(ProtocolPP::AUTH, CryptoPP::ASN1::secp384r1());

        mydsasa.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::keymode_t::PKISIGN);
        mydsasa.set_field<ProtocolPP::keymode_t>(ProtocolPP::CIPHER, ProtocolPP::keymode_t::PKISIGN);

        bitsize = mydsasa.get_field<int>(ProtocolPP::BITSIZE);
        bitsize = mydsasa.get_field<int>(ProtocolPP::AUTH);

        prvKey = mydsasaptr->get_prvkey384();
        prvKey = mydsasaptr->get_prvkey512();
        prvKey = mydsasaptr->get_prvkey256();
        prvKey = mydsasa40.get_prvkey256();
        mydsasa40.set_prvkey256(prvKey);

        pubKey = mydsasaptr->get_pubkey384();
        pubKey = mydsasaptr->get_pubkey512();
        pubKey = mydsasaptr->get_pubkey256();
        pubKey = mydsasa40.get_pubkey256();
        mydsasa40.set_pubkey256(pubKey);

        mymode = mydsasa.get_field<ProtocolPP::keymode_t>(ProtocolPP::MODE);
        mymode = mydsasa.get_field<ProtocolPP::keymode_t>(ProtocolPP::CIPHER);

        ProtocolPP::ike_hash_t hme = mydsasa.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH);
        hme = mydsasa.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::CIPHER);

        CryptoPP::OID mc = mydsasa.get_field<CryptoPP::OID>(ProtocolPP::CURVE);
        mc = mydsasa.get_field<CryptoPP::OID>(ProtocolPP::CIPHER);

        ProtocolPP::jecdsafp tmp(ProtocolPP::ike_hash_t::HASH_SHA2_256,
                                 curve);

        tmp.set_field<int>(ProtocolPP::BITSIZE, bitsize);
        tmp.set_field<int>(ProtocolPP::AUTH, bitsize);

        tmp.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::keymode_t::PKISIGN);
        tmp.set_field<ProtocolPP::keymode_t>(ProtocolPP::CIPHER, ProtocolPP::keymode_t::PKISIGN);

        tmp.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH, ProtocolPP::ike_hash_t::HASH_SHA2_256);
        tmp.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::CIPHER, ProtocolPP::ike_hash_t::HASH_SHA2_256);

        tmp.set_field<CryptoPP::OID>(ProtocolPP::CURVE, CryptoPP::ASN1::secp256r1());
        tmp.set_field<CryptoPP::OID>(ProtocolPP::CIPHER, CryptoPP::ASN1::secp256r1());

        bitsize = tmp.get_field<int>(ProtocolPP::BITSIZE);
        bitsize = tmp.get_field<int>(ProtocolPP::AUTH);

        tmp.set_prvkey256(prvKey);
        tmp.set_pubkey256(pubKey);

        tmp.set_prvkey384(prvKey4);
        tmp.set_pubkey384(pubKey4);

        tmp.set_prvkey512(prvKey5);
        tmp.set_pubkey512(pubKey5);

        prvKey = tmp.get_prvkey384();
        prvKey = tmp.get_prvkey512();

        pubKey = tmp.get_pubkey384();
        pubKey = tmp.get_pubkey512();

        mymode = tmp.get_field<ProtocolPP::keymode_t>(ProtocolPP::MODE);
        mymode = tmp.get_field<ProtocolPP::keymode_t>(ProtocolPP::CIPHER);

        tmp.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH, ProtocolPP::ike_hash_t::HASH_SHA2_384);
        tmp.set_field<CryptoPP::OID>(ProtocolPP::CURVE, CryptoPP::ASN1::secp384r1());

        hme = tmp.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH);
        hme = tmp.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::CIPHER);

        mc = tmp.get_field<CryptoPP::OID>(ProtocolPP::CURVE);
        mc = tmp.get_field<CryptoPP::OID>(ProtocolPP::CIPHER);

        tmp.set_prvkey256(prvKey);
        tmp.set_pubkey256(pubKey);

        tmp.set_prvkey384(prvKey4);
        tmp.set_pubkey384(pubKey4);

        tmp.set_prvkey512(prvKey5);
        tmp.set_pubkey512(pubKey5);

        tmp.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH, ProtocolPP::ike_hash_t::HASH_SHA2_512);
        tmp.set_field<CryptoPP::OID>(ProtocolPP::CURVE, CryptoPP::ASN1::secp521r1());

        tmp.set_prvkey256(prvKey);
        tmp.set_pubkey256(pubKey);

        tmp.set_prvkey384(prvKey4);
        tmp.set_pubkey384(pubKey4);

        tmp.set_prvkey512(prvKey5);
        tmp.set_pubkey512(pubKey5);

        tmp.set_hdr(myhdr);
        tmp.set_field(ProtocolPP::NH, myval);
        myhdr = tmp.get_hdr();
        myval = tmp.get_field(ProtocolPP::NH, myhdr);
        tmp.encap_packet(in, out);
        tmp.decap_packet(out, in);
    }

    void testecdsaf2mcov() {
        int bitsize = 4096;
        uint64_t mydata = 0;
        ProtocolPP::keymode_t mymode;
        ProtocolPP::jecdsaf2msa mydsasa;
        CryptoPP::AutoSeededRandomPool m_rng;
        CryptoPP::OID curve = CryptoPP::ASN1::sect283r1();
        CryptoPP::OID curve3 = CryptoPP::ASN1::sect409r1();
        CryptoPP::OID curve4 = CryptoPP::ASN1::sect571r1();

        ProtocolPP::jecdsaf2msa mydsasa384(ProtocolPP::PKISIGN,
                                           ProtocolPP::ike_hash_t::HASH_SHA2_384,
                                           curve3);

        ProtocolPP::jecdsaf2msa mydsasa512(ProtocolPP::PKISIGN,
                                           ProtocolPP::ike_hash_t::HASH_SHA2_512,
                                           curve4);
        // private key container
        CryptoPP::ECDSA<CryptoPP::EC2N, CryptoPP::SHA256>::PrivateKey prvKey;
        CryptoPP::ECDSA<CryptoPP::EC2N, CryptoPP::SHA256>::PublicKey pubKey;

        CryptoPP::ECDSA<CryptoPP::EC2N, CryptoPP::SHA384>::PrivateKey prvKey3;
        CryptoPP::ECDSA<CryptoPP::EC2N, CryptoPP::SHA384>::PublicKey pubKey3;

        CryptoPP::ECDSA<CryptoPP::EC2N, CryptoPP::SHA512>::PrivateKey prvKey4;
        CryptoPP::ECDSA<CryptoPP::EC2N, CryptoPP::SHA512>::PublicKey pubKey4;

        prvKey3.Initialize(m_rng, curve3);
        prvKey3.MakePublicKey(pubKey3);

        prvKey4.Initialize(m_rng, curve4);
        prvKey4.MakePublicKey(pubKey4);

        ProtocolPP::jarray<uint8_t> myhdr = myrand->getbyte(16);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mymsg = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(500));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> mysig = std::make_shared<ProtocolPP::jarray<uint8_t>>(500,0);

        prvKey.Initialize(m_rng, curve);
        prvKey.MakePublicKey(pubKey);

        std::string log = "./mypp.log";
        std::shared_ptr<ProtocolPP::jecdsaf2msa> mydsasaptr = std::make_shared<ProtocolPP::jecdsaf2msa>(ProtocolPP::PKISIGN,
                                                                                                        ProtocolPP::ike_hash_t::HASH_SHA2_256,
                                                                                                        curve);

        std::shared_ptr<ProtocolPP::jecdsaf2msa> mydsasa384ptr = std::make_shared<ProtocolPP::jecdsaf2msa>(ProtocolPP::PKISIGN,
                                                                                                           ProtocolPP::ike_hash_t::HASH_SHA2_384,
                                                                                                           curve3);

        std::shared_ptr<ProtocolPP::jecdsaf2msa> mydsasa512ptr = std::make_shared<ProtocolPP::jecdsaf2msa>(ProtocolPP::PKISIGN,
                                                                                                           ProtocolPP::ike_hash_t::HASH_SHA2_512,
                                                                                                           curve4);

        mydsasaptr->set_prvkey256(prvKey);
        mydsasaptr->set_pubkey256(pubKey);

        prvKey = mydsasaptr->get_prvkey512();
        pubKey = mydsasaptr->get_pubkey512();

        mydsasa512ptr->set_prvkey256(prvKey4);
        mydsasa512ptr->set_pubkey256(pubKey4);

        prvKey4 = mydsasa512ptr->get_prvkey256();
        pubKey4 = mydsasa512ptr->get_pubkey256();

        prvKey4 = mydsasa512ptr->get_prvkey384();
        pubKey4 = mydsasa512ptr->get_pubkey384();

        ProtocolPP::jecdsaf2m mydsa3(ProtocolPP::ike_hash_t::HASH_SHA2_256,
                                     curve);

        ProtocolPP::jecdsaf2m mydsa4(mydsasaptr);
        ProtocolPP::jecdsaf2msa mydsa4_2(mydsasaptr);
        ProtocolPP::jecdsaf2msa mydsa384(mydsasa384ptr);
        ProtocolPP::jecdsaf2msa mydsa512(mydsasa512ptr);

        ProtocolPP::jecdsaf2msa mydsa5(mydsasa);
        ProtocolPP::jecdsaf2msa mydsa384_2(mydsasa384);
        ProtocolPP::jecdsaf2msa mydsa512_2(mydsasa512);

        mydsa4.sign(mymsg, mysig);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myveri = std::make_shared<ProtocolPP::jarray<uint8_t>>(*mymsg);
        myveri->append(*mysig);
        mydsa4.verify(myveri);

        mydsa3.gen_keypair();
        mydsa3.set_field<int>(ProtocolPP::BITSIZE, bitsize);
        mydsa3.set_field<int>(ProtocolPP::CIPHER, bitsize);

        mydsa3.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::PKISIGN);
        mydsa3.set_field<ProtocolPP::keymode_t>(ProtocolPP::NH, ProtocolPP::RSAENCRYPT);

        ProtocolPP::ike_hash_t hashme = mydsa3.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::IKEHASH);
        mydsa3.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::IKEHASH, hashme);
        mydsa3.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::NH, hashme);

        CryptoPP::OID mycur = mydsa3.get_field<CryptoPP::OID>(ProtocolPP::CURVE);
        mydsa3.set_field<CryptoPP::OID>(ProtocolPP::CURVE, mycur);
        mydsa3.set_field<CryptoPP::OID>(ProtocolPP::NH, mycur);

        bitsize = mydsa3.get_field<int>(ProtocolPP::BITSIZE);
        bitsize = mydsa3.get_field<int>(ProtocolPP::CIPHER);

        mymode = mydsa3.get_field<ProtocolPP::keymode_t>(ProtocolPP::MODE);
        mymode = mydsa3.get_field<ProtocolPP::keymode_t>(ProtocolPP::NH);

        std::shared_ptr<ProtocolPP::jarray<uint8_t>> myout = std::make_shared<ProtocolPP::jarray<uint8_t>>(0);
        mydsa3.get_security(mydsasaptr);
        mydsa3.encap_packet(myveri, myout);
        mydsa3.decap_packet(myout, myveri);

        mydsa3.set_hdr(myhdr);
        myhdr  = mydsa3.get_hdr();
        mydata = mydsa3.get_field(ProtocolPP::BITSIZE, myhdr);
        mydsa3.set_field(ProtocolPP::DIRECTION, mydata);

        mydsa4.set_prvkey256(prvKey);
        mydsa4.set_prvkey384(prvKey3);
        mydsa4.set_prvkey512(prvKey4);

        prvKey = mydsa4.get_prvkey256();
        prvKey3 = mydsa4.get_prvkey384();
        prvKey4 = mydsa4.get_prvkey512();

        mydsa4.set_pubkey256(pubKey);
        mydsa4.set_pubkey384(pubKey3);
        mydsa4.set_pubkey512(pubKey4);

        pubKey = mydsa4.get_pubkey256();
        pubKey3 = mydsa4.get_pubkey384();
        pubKey4 = mydsa4.get_pubkey512();

        mydsa4.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH, ProtocolPP::HASH_SHA2_384);
        mydsa4.set_field<CryptoPP::OID>(ProtocolPP::CURVE, curve3);

        mydsa4.set_pubkey256(pubKey);
        pubKey = mydsa4.get_pubkey256();

        mydsa4.set_pubkey384(pubKey3);
        pubKey3 = mydsa4.get_pubkey384();

        mydsa4.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH, ProtocolPP::HASH_SHA2_512);
        mydsa4.set_field<CryptoPP::OID>(ProtocolPP::CURVE, curve4);

        mydsa4.set_pubkey512(pubKey4);
        pubKey4 = mydsa4.get_pubkey512();

        mydsasa.set_field<int>(ProtocolPP::NH, bitsize);
        mydsasa.set_field<ProtocolPP::keymode_t>(ProtocolPP::MODE, ProtocolPP::PKISIGN);
        mydsasa.set_field<ProtocolPP::keymode_t>(ProtocolPP::NH, ProtocolPP::PKISIGN);
        mydsasa.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::ECHASH, ProtocolPP::HASH_SHA2_256);
        mydsasa.set_field<ProtocolPP::ike_hash_t>(ProtocolPP::NH, ProtocolPP::HASH_SHA2_256);
        mydsasa.set_field<CryptoPP::OID>(ProtocolPP::CURVE, CryptoPP::ASN1::sect233r1());
        mydsasa.set_field<CryptoPP::OID>(ProtocolPP::NH, CryptoPP::ASN1::sect233r1());

        int ime = mydsasa.get_field<int>(ProtocolPP::NH);
        ProtocolPP::keymode_t kme = mydsasa.get_field<ProtocolPP::keymode_t>(ProtocolPP::NH);
        ProtocolPP::ike_hash_t hme = mydsasa.get_field<ProtocolPP::ike_hash_t>(ProtocolPP::NH);
        CryptoPP::OID curme = mydsasa.get_field<CryptoPP::OID>(ProtocolPP::NH);

        // private key container
        mydsasa.set_prvkey384(prvKey3);
        mydsasa.set_pubkey384(pubKey3);

        // private key container
        mydsasa.set_prvkey512(prvKey4);
        mydsasa.set_pubkey512(pubKey4);

        std::shared_ptr<ProtocolPP::jecdsaf2m> dsa10 = ProtocolPP::jprotocolpp::get_ecdsaf2m(mydsasaptr);
    }

    void testdatacov() {
        ProtocolPP::jdata mydat;

        uint64_t myaddr = myrand->get_u64();
        uint32_t mylen = 32;
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(50));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(50));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(50));
        std::string name = myrand->getname(12);
        ProtocolPP::direction_t dir(ProtocolPP::ENCAP);
        ProtocolPP::protocol_t type(ProtocolPP::WIFI);
        std::shared_ptr<ProtocolPP::jwifisa> mysec = std::make_shared<ProtocolPP::jwifisa>();
        std::shared_ptr<ProtocolPP::jstream> mystrm = std::make_shared<ProtocolPP::jstream>(name,
                                                                                            dir,
                                                                                            type,
                                                                                            false,
                                                                                            mysec);

        std::shared_ptr<ProtocolPP::jpacket> mypkt = std::make_shared<ProtocolPP::jpacket>(name,
                                                                                           name,
                                                                                           name,
                                                                                           input);

        std::shared_ptr<ProtocolPP::jpacket> mypkt2 = std::make_shared<ProtocolPP::jpacket>(name,
                                                                                            name,
                                                                                            name,
                                                                                            input,
                                                                                            expect,
                                                                                            myaddr,
                                                                                            mylen,
                                                                                            mylen);
        mydat.set_flow(mystrm);
        mydat.set_packet(name, mypkt);
        mydat.get_flow(name, mystrm);
        mydat.get_packet(name, mypkt);

        mystrm->set_field<std::string>(ProtocolPP::NAME, name);
        mystrm->set_field<std::string>(ProtocolPP::CIPHER, name);

        mystrm->set_field<unsigned int>(ProtocolPP::STREAMSIZE, 32);
        mystrm->set_field<unsigned int>(ProtocolPP::CIPHER, 32);

        mystrm->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::ENCAP);
        mystrm->set_field<ProtocolPP::direction_t>(ProtocolPP::CIPHER, ProtocolPP::DECAP);

        mystrm->set_field<ProtocolPP::protocol_t>(ProtocolPP::TYPE, ProtocolPP::IPSEC);
        mystrm->set_field<ProtocolPP::protocol_t>(ProtocolPP::CIPHER, ProtocolPP::WIFI);

        mystrm->set_field<bool>(ProtocolPP::POSTPROCESS, true);
        mystrm->set_field<bool>(ProtocolPP::CIPHER, false);

        name = mystrm->get_field<std::string>(ProtocolPP::CIPHER);

        unsigned int mysize = mystrm->get_field<unsigned int>(ProtocolPP::STREAMSIZE);
        mysize = mystrm->get_field<unsigned int>(ProtocolPP::AUTH);

        dir = mystrm->get_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION);
        dir = mystrm->get_field<ProtocolPP::direction_t>(ProtocolPP::CIPHER);

        type = mystrm->get_field<ProtocolPP::protocol_t>(ProtocolPP::TYPE);
        type = mystrm->get_field<ProtocolPP::protocol_t>(ProtocolPP::CIPHER);

        bool mytrue = mystrm->get_field<bool>(ProtocolPP::CIPHER);

        mypkt->set_field<uint64_t>(ProtocolPP::CIPHER, myaddr);
        mypkt->set_field<uint32_t>(ProtocolPP::CIPHER, 32);

        mypkt->set_field<std::string>(ProtocolPP::STREAM, name);
        mypkt->set_field<std::string>(ProtocolPP::NAME, name);
        mypkt->set_field<std::string>(ProtocolPP::PREVIOUS, name);
        mypkt->set_field<std::string>(ProtocolPP::CIPHER, name);

        mypkt->set_data(ProtocolPP::CIPHER, input);

        std::string myprev = mypkt->get_field<std::string>(ProtocolPP::PREVIOUS);
        myprev = mypkt->get_field<std::string>(ProtocolPP::AUTH);
        
        myaddr = mypkt->get_field<uint64_t>(ProtocolPP::CIPHER);

        mysize = mypkt->get_field<uint32_t>(ProtocolPP::INLEN);
        mysize = mypkt->get_field<uint32_t>(ProtocolPP::OUTPUTLEN);
        mypkt->set_field<uint32_t>(ProtocolPP::OUTPUTLEN,0);
        mysize = mypkt->get_field<uint32_t>(ProtocolPP::OUTPUTLEN);
        mysize = mypkt->get_field<uint32_t>(ProtocolPP::EXPLEN);
        mypkt->set_field<uint32_t>(ProtocolPP::EXPLEN,0);
        mysize = mypkt->get_field<uint32_t>(ProtocolPP::EXPLEN);
        mysize = mypkt->get_field<uint32_t>(ProtocolPP::CIPHER);

        mypkt->get_data(ProtocolPP::CIPHER, input);
    }

    void testexecov() {
        auto oaddr = (uintptr_t)0x1234567890;
        std::shared_ptr<InterfacePP::jring<InterfacePP::ringout>> oring = std::make_shared<InterfacePP::jring<InterfacePP::ringout>>(oaddr, 50);
        //std::shared_ptr<std::map<std::string, std::shared_ptr<ProtocolPP::jstream>>> flows = std::make_shared<std::map<std::string, std::shared_ptr<ProtocolPP::jstream>>>();

        InterfacePP::jexec myex(seed,
                                false,
                                logger,
                                //flows,
                                oring,
                                "us",
                                "50..150",
                                "50..150",
                                "50..150");

        myex.set_readlat("100..250");
        myex.set_computlat("200..350");
        myex.set_writelat("300..450");
        std::string myreadlat  = myex.get_readlat();
        std::string mycomplat  = myex.get_complat();
        std::string mywritelat = myex.get_writelat();
        bool mybusy = myex.get_busy();
    }

    void testudp() {

        uint16_t src = myrand->get_u16();
        uint16_t dst = myrand->get_u16();
        unsigned int mtu = 50; //myrand->get_u16() & 0x0FFF;
        std::shared_ptr<ProtocolPP::judpsa> myudp = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::direction_t::ENCAP,
                                                                                         ProtocolPP::NOPROTO,
                                                                                         src,
                                                                                         dst,
                                                                                         0,
                                                                                         mtu);

        std::shared_ptr<ProtocolPP::judpsa> myudp2 = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::NOPROTO,
                                                                                          src,
                                                                                          dst,
                                                                                          0,
                                                                                          mtu);

        std::shared_ptr<ProtocolPP::jprotocol> eudp = ProtocolPP::jprotocolpp::get_udp(myudp);
        std::shared_ptr<ProtocolPP::jprotocol> dudp = ProtocolPP::jprotocolpp::get_udp(myudp2);
      
        for (int i = 0; i < 50; i++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
          
            // encapsulate the UDP packet
            eudp->encap_packet(input, output);
            dudp->decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dudp->get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTUDP Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testudpvxlan() {

        uint16_t src = myrand->get_u16();
        uint16_t dst = myrand->get_u16();
        unsigned int mtu = 50; //myrand->get_u16() & 0x0FFF;
        std::shared_ptr<ProtocolPP::judpsa> myudp = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::direction_t::ENCAP,
                                                                                         ProtocolPP::VXLAN,
                                                                                         src,
                                                                                         dst,
                                                                                         0,
                                                                                         mtu);

        std::shared_ptr<ProtocolPP::judpsa> myudp2 = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::VXLAN,
                                                                                          src,
                                                                                          dst,
                                                                                          0,
                                                                                          mtu);

        std::shared_ptr<ProtocolPP::jprotocol> eudp = ProtocolPP::jprotocolpp::get_udp(myudp);
        std::shared_ptr<ProtocolPP::jprotocol> dudp = ProtocolPP::jprotocolpp::get_udp(myudp2);
      
        for (int i = 0; i < 50; i++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
          
            // encapsulate the UDP packet
            eudp->encap_packet(input, output);
            dudp->decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dudp->get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTUDP Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testudpfile() {

        uint16_t src = myrand->get_u16();
        uint16_t dst = myrand->get_u16();

        unsigned int mtu = 1500;
        std::string myfile("./test.dat");
        std::shared_ptr<ProtocolPP::judpsa> myudp = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::ENCAP,
                                                                                         ProtocolPP::NOPROTO,
                                                                                         src,
                                                                                         dst,
                                                                                         0,
                                                                                         mtu);

        std::string myfile2("./test_outudp.dat");
        std::shared_ptr<ProtocolPP::judpsa> myudp2 = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::DECAP,
                                                                                          ProtocolPP::NOPROTO,
                                                                                          src,
                                                                                          dst,
                                                                                          0,
                                                                                          mtu);

        std::shared_ptr<ProtocolPP::jprotocol> eudp = ProtocolPP::jprotocolpp::get_udp(myudp, myfile);
        std::shared_ptr<ProtocolPP::jprotocol> dudp = ProtocolPP::jprotocolpp::get_udp(myudp2, myfile2);
      
        for (int i = 0; i < 50; i++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
          
            // encapsulate the UDP packet
            eudp->encap_packet(output);
            dudp->decap_packet(output);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dudp->get_status());
        }
    }

    void testtcp() {

        uint16_t src = myrand->get_u16();
        uint16_t dst = myrand->get_u16();
        unsigned int mtu = 50; //myrand->get_u16() & 0x0FFF;
        uint32_t seqnum = myrand->get_u32();
        uint32_t acknum = seqnum + 1;
        std::shared_ptr<ProtocolPP::jtcpsa> mytcp = std::make_shared<ProtocolPP::jtcpsa>(ProtocolPP::ENCAP,
                                                                                         mtu,
                                                                                         src,
                                                                                         dst,
                                                                                         seqnum,
                                                                                         acknum,
                                                                                         5,
                                                                                         0,
                                                                                         mtu,
                                                                                         0,
                                                                                         0xFFFFFFFF);

        std::shared_ptr<ProtocolPP::jtcpsa> mytcp2 = std::make_shared<ProtocolPP::jtcpsa>(ProtocolPP::DECAP,
                                                                                          mtu,
                                                                                          src,
                                                                                          dst,
                                                                                          acknum,
                                                                                          seqnum,
                                                                                          5,
                                                                                          0,
                                                                                          mtu,
                                                                                          0,
                                                                                          0xFFFFFFFF);

        std::shared_ptr<ProtocolPP::jprotocol> etcp = ProtocolPP::jprotocolpp::get_tcp(ProtocolPP::jtcp::ESTABLISHED, mytcp);
        std::shared_ptr<ProtocolPP::jprotocol> dtcp = ProtocolPP::jprotocolpp::get_tcp(ProtocolPP::jtcp::ESTABLISHED, mytcp2);
    
        for (int i = 0; i < 50; i++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
        
            // encapsulate the TCP packet
            etcp->encap_packet(input, output);
            dtcp->decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dtcp->get_status());

            // check data
            if (*input != *expect) {
                std::cerr << "TESTCP Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testtcpfile() {

        uint16_t src = myrand->get_u16();
        uint16_t dst = myrand->get_u16();
        unsigned int mtu = 1500;
        uint32_t seqnum = myrand->get_u32();
        uint32_t acknum = seqnum + 1;
        
        std::string myfile("./test.dat");
        std::shared_ptr<ProtocolPP::jtcpsa> mytcp = std::make_shared<ProtocolPP::jtcpsa>(ProtocolPP::ENCAP,
                                                                                         mtu,
                                                                                         src,
                                                                                         dst,
                                                                                         seqnum,
                                                                                         acknum,
                                                                                         5,
                                                                                         0,
                                                                                         mtu,
                                                                                         0,
                                                                                         0xFFFFFFFF);
  
        std::string myfile2("./test_outtcp.dat");
        std::shared_ptr<ProtocolPP::jtcpsa> mytcp2 = std::make_shared<ProtocolPP::jtcpsa>(ProtocolPP::DECAP,
                                                                                         mtu,
                                                                                         src,
                                                                                         dst,
                                                                                         acknum,
                                                                                         seqnum,
                                                                                         5,
                                                                                         0,
                                                                                         mtu,
                                                                                         0,
                                                                                         0xFFFFFFFF);

        std::shared_ptr<ProtocolPP::jprotocol> etcp = ProtocolPP::jprotocolpp::get_tcp(ProtocolPP::jtcp::ESTABLISHED, mytcp, myfile);
        std::shared_ptr<ProtocolPP::jprotocol> dtcp = ProtocolPP::jprotocolpp::get_tcp(ProtocolPP::jtcp::ESTABLISHED, mytcp2, myfile2);
    
        for (int i = 0; i < 1; i++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
        
            // encapsulate the TCP packet
            etcp->encap_packet(output);
            dtcp->decap_packet(output);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dtcp->get_status());
        }
    }

    void testudpip() {

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(4);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV4,
                                                                                      ProtocolPP::UDP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV4,
                                                                                       ProtocolPP::UDP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        uint16_t usrc = myrand->get_u16();
        uint16_t udst = myrand->get_u16();

        std::shared_ptr<ProtocolPP::judpsa> myudp = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::ENCAP,
                                                                                         ProtocolPP::NOPROTO,
                                                                                         usrc,
                                                                                         udst,
                                                                                         0,
                                                                                         1500);

        std::shared_ptr<ProtocolPP::judpsa> myudp2 = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::DECAP,
                                                                                          ProtocolPP::NOPROTO,
                                                                                          usrc,
                                                                                          udst,
                                                                                          0,
                                                                                          1500);

        std::shared_ptr<ProtocolPP::jprotocol> eudp = ProtocolPP::jprotocolpp::get_udp(myudp);
        std::shared_ptr<ProtocolPP::jprotocol> dudp = ProtocolPP::jprotocolpp::get_udp(myudp2);
      
        for (int i = 0; i < 50; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input_udp = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output_udp = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect_udp = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
        
            // encapsulate the UDP packet
            eudp->encap_packet(input_udp, output_udp);

            // encapsulate the IP packet
            eip->encap_packet(output_udp, output);

            // decapsulate the IP packet
            dip->decap_packet(output, expect);

            // decapsulate the UDP packet
            dudp->decap_packet(expect, expect_udp);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dudp->get_status());

            // check the data
            if (*input_udp != *expect_udp) {
                std::cerr << "TESTIP Data MISMATCH!" << std::endl;
                expect_udp->debug(*input_udp);
            }
        }
    }

    void testudpip6() {

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(16);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(16);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV6,
                                                                                      ProtocolPP::UDP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV6,
                                                                                       ProtocolPP::UDP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        uint16_t usrc = myrand->get_u16();
        uint16_t udst = myrand->get_u16();

        std::shared_ptr<ProtocolPP::judpsa> myudp = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::ENCAP,
                                                                                         ProtocolPP::NOPROTO,
                                                                                         usrc,
                                                                                         udst,
                                                                                         0,
                                                                                         1500);

        std::shared_ptr<ProtocolPP::judpsa> myudp2 = std::make_shared<ProtocolPP::judpsa>(ProtocolPP::DECAP,
                                                                                          ProtocolPP::NOPROTO,
                                                                                          usrc,
                                                                                          udst,
                                                                                          0,
                                                                                          1500);

        std::shared_ptr<ProtocolPP::jprotocol> eudp = ProtocolPP::jprotocolpp::get_udp(myudp);
        std::shared_ptr<ProtocolPP::jprotocol> dudp = ProtocolPP::jprotocolpp::get_udp(myudp2);
      
        for (int i = 0; i < 50; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input_udp = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output_udp = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect_udp = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
        
            // encapsulate the UDP packet
            eudp->encap_packet(input_udp, output_udp);

            // encapsulate the IP packet
            eip->encap_packet(output_udp, output);

            // decapsulate the IP packet
            dip->decap_packet(output, expect);

            // decapsulate the UDP packet
            dudp->decap_packet(expect, expect_udp);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dudp->get_status());

            // check data
            if (*input_udp != *expect_udp) {
                std::cerr << "TESTUDPIP6 Data MISMATCH!" << std::endl;
                expect_udp->debug(*input_udp);
            }
        }
    }

    void testpgre() {
        ProtocolPP::jarray<uint8_t> payload = myrand->getbyte("256..1024");
        std::shared_ptr<ProtocolPP::jgresa> gresa = std::make_shared<ProtocolPP::jgresa>();
        ProtocolPP::jgresa gresa2(ProtocolPP::direction_t::ENCAP,
                                  ProtocolPP::protocol_t::EGRE,
                                  false,
                                  true,
                                  false,
                                  1,
                                  0x6658,
                                  0x12345678,
                                  0);

        std::shared_ptr<ProtocolPP::jgresa> gresa5 = std::make_shared<ProtocolPP::jgresa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::protocol_t::EGRE,
                                                                                          true,
                                                                                          true,
                                                                                          true,
                                                                                          0,
                                                                                          0x6658,
                                                                                          0x12345678,
                                                                                          0);

        std::shared_ptr<ProtocolPP::jgresa> gresa3 = std::make_shared<ProtocolPP::jgresa>(gresa5);
        gresa3->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::direction_t::ENCAP);
        gresa3->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);
        ProtocolPP::jgresa gresa4(gresa);

        ProtocolPP::jgre grei(gresa3);
        ProtocolPP::jgre greo(gresa5);

        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>();
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(mtu,0);

            grei.encap_packet(input, output);
            greo.decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, greo.get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTGRE Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }

        std::shared_ptr<ProtocolPP::jgresa> gresa6 = std::make_shared<ProtocolPP::jgresa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::protocol_t::EGRE,
                                                                                          false,
                                                                                          true,
                                                                                          true,
                                                                                          0,
                                                                                          0x6658,
                                                                                          0x12345678,
                                                                                          0);

        std::shared_ptr<ProtocolPP::jgresa> gresa7 = std::make_shared<ProtocolPP::jgresa>(gresa6);
        gresa7->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::direction_t::ENCAP);
        gresa7->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);

        ProtocolPP::jgre greii(gresa6);
        ProtocolPP::jgre greoo(gresa7);

        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>();
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(mtu,0);

            greii.encap_packet(input, output);
            greoo.decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, greoo.get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTGRE Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }

        std::shared_ptr<ProtocolPP::jgresa> gresa8 = std::make_shared<ProtocolPP::jgresa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::protocol_t::EGRE,
                                                                                          true,
                                                                                          false,
                                                                                          true,
                                                                                          0,
                                                                                          0x6658,
                                                                                          0x12345678,
                                                                                          0);

        std::shared_ptr<ProtocolPP::jgresa> gresa9 = std::make_shared<ProtocolPP::jgresa>(gresa8);
        gresa9->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::direction_t::ENCAP);
        gresa9->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);

        ProtocolPP::jgre greiii(gresa8);
        ProtocolPP::jgre greooo(gresa9);

        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>();
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(mtu,0);

            greiii.encap_packet(input, output);
            greooo.decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, greooo.get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTGRE Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }

        std::shared_ptr<ProtocolPP::jgresa> gresa10 = std::make_shared<ProtocolPP::jgresa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::protocol_t::EGRE,
                                                                                          false,
                                                                                          false,
                                                                                          true,
                                                                                          0,
                                                                                          0x6658,
                                                                                          0x12345678,
                                                                                          0);

        std::shared_ptr<ProtocolPP::jgresa> gresa11 = std::make_shared<ProtocolPP::jgresa>(gresa10);
        gresa11->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::direction_t::ENCAP);
        gresa11->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);

        ProtocolPP::jgre greiiii(gresa10);
        ProtocolPP::jgre greoooo(gresa11);

        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>();
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(mtu,0);

            greiiii.encap_packet(input, output);
            greoooo.decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, greoooo.get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTGRE Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }

        std::shared_ptr<ProtocolPP::jgresa> gresa12 = std::make_shared<ProtocolPP::jgresa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::protocol_t::EGRE,
                                                                                          false,
                                                                                          false,
                                                                                          false,
                                                                                          0,
                                                                                          0x6658,
                                                                                          0x12345678,
                                                                                          0);

        std::shared_ptr<ProtocolPP::jgresa> gresa13 = std::make_shared<ProtocolPP::jgresa>(gresa12);
        gresa13->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::direction_t::ENCAP);
        gresa13->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);

        ProtocolPP::jgre greiiiii(gresa12);
        ProtocolPP::jgre greooooo(gresa13);

        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>();
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(mtu,0);

            greiiiii.encap_packet(input, output);
            greooooo.decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, greooooo.get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTGRE Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }

        std::shared_ptr<ProtocolPP::jgresa> gresa14 = std::make_shared<ProtocolPP::jgresa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::protocol_t::EGRE,
                                                                                          true,
                                                                                          true,
                                                                                          false,
                                                                                          0,
                                                                                          0x6658,
                                                                                          0x12345678,
                                                                                          0);

        std::shared_ptr<ProtocolPP::jgresa> gresa15 = std::make_shared<ProtocolPP::jgresa>(gresa14);
        gresa15->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::direction_t::ENCAP);
        gresa15->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);

        ProtocolPP::jgre greiiiiii(gresa14);
        ProtocolPP::jgre greoooooo(gresa15);

        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>();
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(mtu,0);

            greiiiiii.encap_packet(input, output);
            greoooooo.decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, greoooooo.get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTGRE Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }

        std::shared_ptr<ProtocolPP::jgresa> gresa16 = std::make_shared<ProtocolPP::jgresa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::protocol_t::EGRE,
                                                                                          false,
                                                                                          true,
                                                                                          false,
                                                                                          0,
                                                                                          0x6658,
                                                                                          0x12345678,
                                                                                          0);

        std::shared_ptr<ProtocolPP::jgresa> gresa17 = std::make_shared<ProtocolPP::jgresa>(gresa16);
        gresa17->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::direction_t::ENCAP);
        gresa17->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);

        ProtocolPP::jgre greiiiiiii(gresa16);
        ProtocolPP::jgre greooooooo(gresa17);

        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>();
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(mtu,0);

            greiiiiiii.encap_packet(input, output);
            greooooooo.decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, greooooooo.get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTGRE Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testnvgre() {
        ProtocolPP::jarray<uint8_t> payload = myrand->getbyte("256..1024");
        std::shared_ptr<ProtocolPP::jgresa> gresa = std::make_shared<ProtocolPP::jgresa>();
        ProtocolPP::jgresa gresa2(ProtocolPP::direction_t::ENCAP,
                                  ProtocolPP::protocol_t::NVGRE,
                                  false,
                                  true,
                                  false,
                                  1,
                                  0x6658,
                                  0x12345678,
                                  0);

        std::shared_ptr<ProtocolPP::jgresa> gresa5 = std::make_shared<ProtocolPP::jgresa>(ProtocolPP::direction_t::DECAP,
                                                                                          ProtocolPP::protocol_t::NVGRE,
                                                                                          false,
                                                                                          true,
                                                                                          false,
                                                                                          1,
                                                                                          0x6658,
                                                                                          0x345678,
                                                                                          0x12);

        std::shared_ptr<ProtocolPP::jgresa> gresa3 = std::make_shared<ProtocolPP::jgresa>(gresa5);
        gresa3->set_field<ProtocolPP::direction_t>(ProtocolPP::DIRECTION, ProtocolPP::direction_t::ENCAP);
        gresa3->set_field<uint32_t>(ProtocolPP::SEQNUM, 0);
        ProtocolPP::jgresa gresa4(gresa);

        ProtocolPP::jgre grei(gresa3);
        ProtocolPP::jgre greo(gresa5);

        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>();
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(mtu,0);

            grei.encap_packet(input, output);
            greo.decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, greo.get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTGRE Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testip6() {

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(16);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(16);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV6,
                                                                                      ProtocolPP::CHAOS,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV6,
                                                                                       ProtocolPP::CHAOS,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(80000));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(80000));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(80000));
        
            // encapsulate the IP packet
            eip->encap_packet(input, output);

            // decapsulate the IP packet
            dip->decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dip->get_status());

            // check the data
            if (*input != *expect) {
                std::cerr << "TESTIP6 Data MISMATCH!" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testip6file() {

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(16);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(16);

        std::string myfile("./test.dat");
        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV6,
                                                                                      ProtocolPP::CHAOS,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::string myfile2("./test_outip.dat");
        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV6,
                                                                                       ProtocolPP::CHAOS,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip, myfile);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2, myfile2);
    
        for (int i = 0; i < 5; i++) {
            unsigned int mtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(80000));
        
            // encapsulate the IP packet
            eip->encap_packet(output);

            // decapsulate the IP packet
            dip->decap_packet(output);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dip->get_status());
        }
    }

    void testtcpip() {

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(4);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV4,
                                                                                      ProtocolPP::TCP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV4,
                                                                                       ProtocolPP::TCP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        uint16_t srct = myrand->get_u16();
        uint16_t dstt = myrand->get_u16();
        unsigned int mtu = myrand->get_u16() & 0x0FFF;
        uint32_t seqnum = myrand->get_u32();
        uint32_t acknum = seqnum + 1;

        std::shared_ptr<ProtocolPP::jtcpsa> mytcp = std::make_shared<ProtocolPP::jtcpsa>(ProtocolPP::ENCAP,
                                                                                         mtu,
                                                                                         srct,
                                                                                         dstt,
                                                                                         seqnum,
                                                                                         acknum,
                                                                                         5,
                                                                                         0,
                                                                                         mtu,
                                                                                         0,
                                                                                         0xFFFFFFFF);

        std::shared_ptr<ProtocolPP::jtcpsa> mytcp2 = std::make_shared<ProtocolPP::jtcpsa>(ProtocolPP::DECAP,
                                                                                          mtu,
                                                                                          dstt,
                                                                                          srct,
                                                                                          acknum,
                                                                                          seqnum,
                                                                                          5,
                                                                                          0,
                                                                                          mtu,
                                                                                          0,
                                                                                          0xFFFFFFFF);

        std::shared_ptr<ProtocolPP::jprotocol> etcp = ProtocolPP::jprotocolpp::get_tcp(ProtocolPP::jtcp::ESTABLISHED, mytcp);
        std::shared_ptr<ProtocolPP::jprotocol> dtcp = ProtocolPP::jprotocolpp::get_tcp(ProtocolPP::jtcp::ESTABLISHED, mytcp2);
    
        for (int i = 0; i < 50; i++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input_tcp = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output_tcp = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect_tcp = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
        
            // encapsulate the TCP packet
            etcp->encap_packet(input_tcp, output_tcp);

            // encapsulate the IP packet
            eip->encap_packet(output_tcp, output);

            // decapsulate the IP packet
            dip->decap_packet(output, expect);

            // decapsulate the TCP packet
            dtcp->decap_packet(expect, expect_tcp);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dtcp->get_status());

            // check data
            if (*input_tcp != *expect_tcp) {
                std::cerr << "TESTIP Data MISMATCH!" << std::endl;
                expect_tcp->debug(*input_tcp);
            }
        }
    }

    void testtcpip6() {

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(16);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(16);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV6,
                                                                                      ProtocolPP::TCP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV6,
                                                                                       ProtocolPP::TCP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);


        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        uint16_t srct = myrand->get_u16();
        uint16_t dstt = myrand->get_u16();
        unsigned int mtu = myrand->get_u16() & 0x0FFF;
        uint32_t seqnum = myrand->get_u32();
        uint32_t acknum = seqnum + 1;

        std::shared_ptr<ProtocolPP::jtcpsa> mytcp = std::make_shared<ProtocolPP::jtcpsa>(ProtocolPP::ENCAP,
                                                                                         mtu,
                                                                                         srct,
                                                                                         dstt,
                                                                                         seqnum,
                                                                                         acknum,
                                                                                         5,
                                                                                         0,
                                                                                         mtu,
                                                                                         0,
                                                                                         0xFFFFFFFF);

        std::shared_ptr<ProtocolPP::jtcpsa> mytcp2 = std::make_shared<ProtocolPP::jtcpsa>(ProtocolPP::DECAP,
                                                                                          mtu,
                                                                                          dstt,
                                                                                          srct,
                                                                                          acknum,
                                                                                          seqnum,
                                                                                          5,
                                                                                          0,
                                                                                          mtu,
                                                                                          0,
                                                                                          0xFFFFFFFF);

        std::shared_ptr<ProtocolPP::jprotocol> etcp = ProtocolPP::jprotocolpp::get_tcp(ProtocolPP::jtcp::ESTABLISHED, mytcp);
        std::shared_ptr<ProtocolPP::jprotocol> dtcp = ProtocolPP::jprotocolpp::get_tcp(ProtocolPP::jtcp::ESTABLISHED, mytcp2);
    
        for (int i = 0; i < 50; i++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input_tcp = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output_tcp = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect_tcp = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(mtu));
        
            // encapsulate the TCP packet
            etcp->encap_packet(input_tcp, output_tcp);

            // encapsulate the IP packet
            eip->encap_packet(output_tcp, output);

            // decapsulate the IP packet
            dip->decap_packet(output, expect);

            // decapsulate the TCP packet
            dtcp->decap_packet(expect, expect_tcp);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dtcp->get_status());

            // check data
            if (*input_tcp != *expect_tcp) {
                std::cerr << "TESTIP Data MISMATCH!" << std::endl;
                expect_tcp->debug(*input_tcp);
            }
        }
    }

    void testipsec() {

        // IPsec setup
        ProtocolPP::jarray<uint8_t> ipsrc = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> ipdst = myrand->getbyte(4);
        uint32_t ipspi = myrand->get_u32();

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(4);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV4,
                                                                                      ProtocolPP::RSVP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV4,
                                                                                       ProtocolPP::RSVP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));

        for (unsigned int j=0; j<3; j++) {
            // populate the security association
            std::shared_ptr<ProtocolPP::jipsecsa> myipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::ENCAP,
                                                                                                   ProtocolPP::IPV4,
                                                                                                   ProtocolPP::TUNNEL,
                                                                                                   ipspi,
                                                                                                   1,
                                                                                                   1,
                                                                                                   0,
                                                                                                   ProtocolPP::jarray<uint8_t>(0),
                                                                                                   ProtocolPP::AES_CBC,
                                                                                                   32,
                                                                                                   ckey,
                                                                                                   ProtocolPP::HMAC_SHA2_256,
                                                                                                   32,
                                                                                                   akey,
                                                                                                   16,
                                                                                                   std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16)),
                                                                                                   0,
                                                                                                   std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                                   0,
                                                                                                   0xFFFFFFFF,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   0,
                                                                                                   0xFF,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   false,
                                                                                                   0,
                                                                                                   1500,
                                                                                                   ipsrc,
                                                                                                   ipdst,
                                                                                                   ProtocolPP::jarray<uint8_t>(0),
                                                                                                   ProtocolPP::IPV4,
                                                                                                   32,
                                                                                                   20,
                                                                                                   0,
                                                                                                   true,
                                                                                                   false,
                                                                                                   true,
                                                                                                   false,
                                                                                                   std::string("./myaudit.log"));

            std::shared_ptr<ProtocolPP::jipsecsa> mydipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::DECAP,
                                                                                                    ProtocolPP::IPV4,
                                                                                                    ProtocolPP::TUNNEL,
                                                                                                    ipspi,
                                                                                                    1,
                                                                                                    1,
                                                                                                    0,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::AES_CBC,
                                                                                                    32,
                                                                                                    ckey,
                                                                                                    ProtocolPP::HMAC_SHA2_256,
                                                                                                    32,
                                                                                                    akey,
                                                                                                    16,
                                                                                                    std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16)),
                                                                                                    0,
                                                                                                    std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                                    0,
                                                                                                    0xFFFFFFFF,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    0,
                                                                                                    0xFF,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    false,
                                                                                                    0,
                                                                                                    1500,
                                                                                                    ipsrc,
                                                                                                    ipdst,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::IPV4,
                                                                                                    32,
                                                                                                    20,
                                                                                                    0,
                                                                                                    true,
                                                                                                    false,
                                                                                                    true,
                                                                                                    false,
                                                                                                    std::string("./myaudit.log"));

            if (j == 0) {
                myipsec->set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::HMAC_SHA2_256);
                myipsec->set_field<uint32_t>(ProtocolPP::ICVLEN, 32);
                mydipsec->set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::HMAC_SHA2_256);
                mydipsec->set_field<uint32_t>(ProtocolPP::ICVLEN, 32);
            }
            else if (j == 1) {
                myipsec->set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::HMAC_SHA2_384);
                myipsec->set_field<uint32_t>(ProtocolPP::ICVLEN, 48);
                mydipsec->set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::HMAC_SHA2_384);
                mydipsec->set_field<uint32_t>(ProtocolPP::ICVLEN, 48);
            }
            else {
                myipsec->set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::HMAC_SHA2_512);
                myipsec->set_field<uint32_t>(ProtocolPP::ICVLEN, 64);
                mydipsec->set_field<ProtocolPP::auth_t>(ProtocolPP::AUTH, ProtocolPP::HMAC_SHA2_512);
                mydipsec->set_field<uint32_t>(ProtocolPP::ICVLEN, 64);
            }
    
            // create encap and decap IPsec
            std::shared_ptr<ProtocolPP::jprotocol> eipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, myipsec, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, mydipsec, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FF0;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> outputip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expectip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the IP packet
                eip->encap_packet(input, outputip);

                // encapsulate the IP packet
                eipsec->encap_packet(outputip, output);

                // encapsulate the IP packet
                dipsec->decap_packet(output, expectip);

                // encapsulate the IP packet
                dip->decap_packet(expectip, expect);

                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dipsec->get_status());
                
                // check data
                if (*input != *expect) {
                    std::cerr << "IPsec AES-CBC Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testipsecgcm() {

        // IPsec setup
        ProtocolPP::jarray<uint8_t> ipsrc = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> ipdst = myrand->getbyte(4);
        uint32_t ipspi = myrand->get_u32();

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(4);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV4,
                                                                                      ProtocolPP::RSVP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV4,
                                                                                       ProtocolPP::RSVP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        for (unsigned int j=0; j<1; j++) {
            unsigned int keylen = ((j == 0) ? 16 : ((j == 1) ? 24 : 32));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(4));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*salt);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jipsecsa> myipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::ENCAP,
                                                                                                   ProtocolPP::IPV4,
                                                                                                   ProtocolPP::TUNNEL,
                                                                                                   ipspi,
                                                                                                   1,
                                                                                                   1,
                                                                                                   0,
                                                                                                   ProtocolPP::jarray<uint8_t>(0),
                                                                                                   ProtocolPP::AES_GCM,
                                                                                                   16,
                                                                                                   ckey,
                                                                                                   ProtocolPP::HMAC_SHA2_256,
                                                                                                   16,
                                                                                                   std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16)),
                                                                                                   8,
                                                                                                   std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8)),
                                                                                                   4,
                                                                                                   salt,
                                                                                                   0,
                                                                                                   0xFFFFFFFF,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   0,
                                                                                                   0xFF,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   false,
                                                                                                   0,
                                                                                                   1500,
                                                                                                   ipsrc,
                                                                                                   ipdst,
                                                                                                   ProtocolPP::jarray<uint8_t>(0),
                                                                                                   ProtocolPP::IPV4,
                                                                                                   16,
                                                                                                   20,
                                                                                                   0,
                                                                                                   true,
                                                                                                   false,
                                                                                                   true,
                                                                                                   false,
                                                                                                   std::string("./myaudit.log"));

            std::shared_ptr<ProtocolPP::jipsecsa> mydipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::DECAP,
                                                                                                    ProtocolPP::IPV4,
                                                                                                    ProtocolPP::TUNNEL,
                                                                                                    ipspi,
                                                                                                    1,
                                                                                                    1,
                                                                                                    0,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::AES_GCM,
                                                                                                    16,
                                                                                                    ckey2,
                                                                                                    ProtocolPP::HMAC_SHA2_256,
                                                                                                    16,
                                                                                                    std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16)),
                                                                                                    8,
                                                                                                    std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8)),
                                                                                                    4,
                                                                                                    salt2,
                                                                                                    0,
                                                                                                    0xFFFFFFFF,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    0,
                                                                                                    0xFF,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    false,
                                                                                                    0,
                                                                                                    1500,
                                                                                                    ipsrc,
                                                                                                    ipdst,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::IPV4,
                                                                                                    16,
                                                                                                    20,
                                                                                                    0,
                                                                                                    true,
                                                                                                    false,
                                                                                                    true,
                                                                                                    false,
                                                                                                    std::string("./myaudit.log"));

            // create encap and decap IPsec
            std::shared_ptr<ProtocolPP::jprotocol> eipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, myipsec, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, mydipsec, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> outputip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expectip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the IP packet
                eip->encap_packet(input, outputip);
                eipsec->encap_packet(outputip, output);
                dipsec->decap_packet(output, expectip);
                dip->decap_packet(expectip, expect);

                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dipsec->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "IPsec AES-GCM Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testipsecccm() {
        // IPsec setup
        ProtocolPP::jarray<uint8_t> ipsrc = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> ipdst = myrand->getbyte(4);
        uint32_t ipspi = myrand->get_u32();

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(4);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV4,
                                                                                      ProtocolPP::RSVP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV4,
                                                                                       ProtocolPP::RSVP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        for (unsigned int j=0; j<1; j++) {
            unsigned int keylen = ((j == 0) ? 16 : ((j == 1) ? 24 : 32));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(3));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*salt);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jipsecsa> myipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::ENCAP,
                                                                                                   ProtocolPP::IPV4,
                                                                                                   ProtocolPP::TUNNEL,
                                                                                                   ipspi,
                                                                                                   1,
                                                                                                   1,
                                                                                                   0,
                                                                                                   ProtocolPP::jarray<uint8_t>(0),
                                                                                                   ProtocolPP::AES_CCM,
                                                                                                   16,
                                                                                                   ckey,
                                                                                                   ProtocolPP::HMAC_SHA2_256,
                                                                                                   16,
                                                                                                   std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16)),
                                                                                                   8,
                                                                                                   std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8)),
                                                                                                   3,
                                                                                                   salt,
                                                                                                   0,
                                                                                                   0xFFFFFFFF,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   0,
                                                                                                   0xFF,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   false,
                                                                                                   0,
                                                                                                   1500,
                                                                                                   ipsrc,
                                                                                                   ipdst,
                                                                                                   ProtocolPP::jarray<uint8_t>(0),
                                                                                                   ProtocolPP::IPV4,
                                                                                                   16,
                                                                                                   20,
                                                                                                   0,
                                                                                                   true,
                                                                                                   false,
                                                                                                   true,
                                                                                                   false,
                                                                                                   std::string("./myaudit.log"));

            std::shared_ptr<ProtocolPP::jipsecsa> mydipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::DECAP,
                                                                                                    ProtocolPP::IPV4,
                                                                                                    ProtocolPP::TUNNEL,
                                                                                                    ipspi,
                                                                                                    1,
                                                                                                    1,
                                                                                                    0,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::AES_CCM,
                                                                                                    16,
                                                                                                    ckey2,
                                                                                                    ProtocolPP::HMAC_SHA2_256,
                                                                                                    16,
                                                                                                    std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16)),
                                                                                                    8,
                                                                                                    std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8)),
                                                                                                    3,
                                                                                                    salt2,
                                                                                                    0,
                                                                                                    0xFFFFFFFF,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    0,
                                                                                                    0xFF,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    false,
                                                                                                    0,
                                                                                                    1500,
                                                                                                    ipsrc,
                                                                                                    ipdst,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::IPV4,
                                                                                                    16,
                                                                                                    20,
                                                                                                    0,
                                                                                                    true,
                                                                                                    false,
                                                                                                    true,
                                                                                                    false,
                                                                                                    std::string("./myaudit.log"));

            // create encap and decap IPsec
            std::shared_ptr<ProtocolPP::jprotocol> eipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, myipsec, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, mydipsec, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> outputip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expectip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the IP packet
                eip->encap_packet(input, outputip);
                eipsec->encap_packet(outputip, output);
                dipsec->decap_packet(output, expectip);
                dip->decap_packet(expectip, expect);

                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dipsec->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "IPsec AES-GCM Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }


    void testipsecchacha() {
        // IPsec setup
        ProtocolPP::jarray<uint8_t> ipsrc = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> ipdst = myrand->getbyte(4);
        uint32_t ipspi = myrand->get_u32();

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(4);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV4,
                                                                                      ProtocolPP::RSVP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV4,
                                                                                       ProtocolPP::RSVP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);


        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(4));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*salt);

            // populate the security association
            std::shared_ptr<ProtocolPP::jipsecsa> myipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::ENCAP,
                                                                                                   ProtocolPP::IPV4,
                                                                                                   ProtocolPP::TUNNEL,
                                                                                                   ipspi,
                                                                                                   1,
                                                                                                   1,
                                                                                                   0,
                                                                                                   ProtocolPP::jarray<uint8_t>(0),
                                                                                                   ProtocolPP::CHACHA20_POLY1305,
                                                                                                   32,
                                                                                                   ckey,
                                                                                                   ProtocolPP::HMAC_SHA2_256,
                                                                                                   32,
                                                                                                   std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32)),
                                                                                                   0,
                                                                                                   std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                                   4,
                                                                                                   salt,
                                                                                                   0,
                                                                                                   0xFFFFFFFF,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   0,
                                                                                                   0xFF,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   false,
                                                                                                   0,
                                                                                                   1500,
                                                                                                   ipsrc,
                                                                                                   ipdst,
                                                                                                   ProtocolPP::jarray<uint8_t>(0),
                                                                                                   ProtocolPP::IPV4,
                                                                                                   16,
                                                                                                   20,
                                                                                                   0,
                                                                                                   true,
                                                                                                   true,
                                                                                                   true,
                                                                                                   false,
                                                                                                   std::string("./myaudit.log"));

            std::shared_ptr<ProtocolPP::jipsecsa> myipsec2 = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::DECAP,
                                                                                                    ProtocolPP::IPV4,
                                                                                                    ProtocolPP::TUNNEL,
                                                                                                    ipspi,
                                                                                                    1,
                                                                                                    1,
                                                                                                    0,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::CHACHA20_POLY1305,
                                                                                                    32,
                                                                                                    ckey2,
                                                                                                    ProtocolPP::HMAC_SHA2_256,
                                                                                                    32,
                                                                                                    std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32)),
                                                                                                    0,
                                                                                                    std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                                    4,
                                                                                                    salt2,
                                                                                                    0,
                                                                                                    0xFFFFFFFF,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    0,
                                                                                                    0xFF,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    false,
                                                                                                    0,
                                                                                                    1500,
                                                                                                    ipsrc,
                                                                                                    ipdst,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::IPV4,
                                                                                                    16,
                                                                                                    20,
                                                                                                    0,
                                                                                                    true,
                                                                                                    true,
                                                                                                    true,
                                                                                                    false,
                                                                                                    std::string("./myaudit.log"));
 
        // create encap and decap IPsec
        std::shared_ptr<ProtocolPP::jprotocol> eipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, myipsec, myreplay);
        std::shared_ptr<ProtocolPP::jprotocol> dipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, myipsec2, myreplay);

        for (int i = 0; i<50; i++) {
            unsigned int nmtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> outputip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expectip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
        
            // encapsulate the IP packet
            eip->encap_packet(input, outputip);
            eipsec->encap_packet(outputip, output);
            dipsec->decap_packet(output, expectip);
            dip->decap_packet(expectip, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dipsec->get_status());

            // check data
            if (*input != *expect) {
                std::cerr << "IPsec CHACHA20 Data MISMATCH" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testipsecctr() {
        // IPsec setup
        ProtocolPP::jarray<uint8_t> ipsrc = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> ipdst = myrand->getbyte(4);
        uint32_t ipspi = myrand->get_u32();

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(4);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV4,
                                                                                      ProtocolPP::RSVP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0xFFFF,
                                                                                      0xFFFFFFFF,
                                                                                      true,
                                                                                      0);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV4,
                                                                                       ProtocolPP::RSVP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0xFFFF,
                                                                                       0xFFFFFFFF,
                                                                                       true,
                                                                                       0);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*iv);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*akey);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(4));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*salt);

        // populate the security association
            std::shared_ptr<ProtocolPP::jipsecsa> myipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::ENCAP,
                                                                                                   ProtocolPP::IPV4,
                                                                                                   ProtocolPP::TUNNEL,
                                                                                                   ipspi,
                                                                                                   1,
                                                                                                   1,
                                                                                                   0,
                                                                                                   ProtocolPP::jarray<uint8_t>(3,0),
                                                                                                   ProtocolPP::AES_CTR,
                                                                                                   32,
                                                                                                   ckey,
                                                                                                   ProtocolPP::HMAC_SHA2_256,
                                                                                                   32,
                                                                                                   akey,
                                                                                                   8,
                                                                                                   iv,
                                                                                                   4,
                                                                                                   salt,
                                                                                                   0,
                                                                                                   0xFFFFFFFF,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   false,
                                                                                                   0,
                                                                                                   0xFF,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   0,
                                                                                                   false,
                                                                                                   0,
                                                                                                   1500,
                                                                                                   ipsrc,
                                                                                                   ipdst,
                                                                                                   ProtocolPP::jarray<uint8_t>(0),
                                                                                                   ProtocolPP::IPV4,
                                                                                                   32,
                                                                                                   20,
                                                                                                   0,
                                                                                                   false,
                                                                                                   true,
                                                                                                   true,
                                                                                                   false,
                                                                                                   std::string("./myaudit.log"));

        std::shared_ptr<ProtocolPP::jipsecsa> myipsec2 = std::make_shared<ProtocolPP::jipsecsa>(myipsec);
        myipsec2->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);

        // create encap and decap IPsec
        std::shared_ptr<ProtocolPP::jprotocol> eipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, myipsec, myreplay);
        std::shared_ptr<ProtocolPP::jprotocol> dipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, myipsec2, myreplay);

        for (int i = 0; i<50; i++) {
            unsigned int nmtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> outputip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expectip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
        
            // encapsulate the IP packet
            eip->encap_packet(input, outputip);
            eipsec->encap_packet(outputip, output);
            dipsec->decap_packet(output, expectip);
            dip->decap_packet(expectip, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dipsec->get_status());

            // check data
            if (*input != *expect) {
                std::cerr << "IPsec AES-CTR Data MISMATCH" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testipsecxcbc() {
        // IPsec setup
        ProtocolPP::jarray<uint8_t> ipsrc = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> ipdst = myrand->getbyte(4);
        uint32_t ipspi = myrand->get_u32();

        ProtocolPP::jarray<uint8_t> src = myrand->getbyte(4);
        ProtocolPP::jarray<uint8_t> dst = myrand->getbyte(4);

        std::shared_ptr<ProtocolPP::jipsa> myip = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::ENCAP,
                                                                                      ProtocolPP::IPV4,
                                                                                      ProtocolPP::RSVP,
                                                                                      src,
                                                                                      dst,
                                                                                      ProtocolPP::jarray<uint8_t>(0),
                                                                                      0,
                                                                                      0xFF,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      0,
                                                                                      true,
                                                                                      1500);

        std::shared_ptr<ProtocolPP::jipsa> myip2 = std::make_shared<ProtocolPP::jipsa>(ProtocolPP::DECAP,
                                                                                       ProtocolPP::IPV4,
                                                                                       ProtocolPP::RSVP,
                                                                                       src,
                                                                                       dst,
                                                                                       ProtocolPP::jarray<uint8_t>(0),
                                                                                       0,
                                                                                       0xFF,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       0,
                                                                                       true,
                                                                                       1500);

        std::shared_ptr<ProtocolPP::jprotocol> eip = ProtocolPP::jprotocolpp::get_ip(myip);
        std::shared_ptr<ProtocolPP::jprotocol> dip = ProtocolPP::jprotocolpp::get_ip(myip2);
    
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*iv);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*akey);

        // populate the security association
        std::shared_ptr<ProtocolPP::jipsecsa> myipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::ENCAP,
                                                                                               ProtocolPP::IPV4,
                                                                                               ProtocolPP::TUNNEL,
                                                                                               ipspi,
                                                                                               1,
                                                                                               1,
                                                                                               0,
                                                                                               ProtocolPP::jarray<uint8_t>(0),
                                                                                               ProtocolPP::AES_CBC,
                                                                                               32,
                                                                                               ckey,
                                                                                               ProtocolPP::AES_XCBC_MAC,
                                                                                               16,
                                                                                               akey,
                                                                                               16,
                                                                                               iv,
                                                                                               0,
                                                                                               std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                               0,
                                                                                               0xFFFFFFFF,
                                                                                               false,
                                                                                               false,
                                                                                               false,
                                                                                               false,
                                                                                               false,
                                                                                               false,
                                                                                               0,
                                                                                               0xFF,
                                                                                               0,
                                                                                               0,
                                                                                               0,
                                                                                               0,
                                                                                               0,
                                                                                               0,
                                                                                               false,
                                                                                               0,
                                                                                               1500,
                                                                                               ipsrc,
                                                                                               ipdst,
                                                                                               ProtocolPP::jarray<uint8_t>(0),
                                                                                               ProtocolPP::IPV4,
                                                                                               8,
                                                                                               20,
                                                                                               0,
                                                                                               true,
                                                                                               false,
                                                                                               true,
                                                                                               false,
                                                                                               std::string("./myaudit.log"));

            std::shared_ptr<ProtocolPP::jipsecsa> mydipsec = std::make_shared<ProtocolPP::jipsecsa>(ProtocolPP::DECAP,
                                                                                                    ProtocolPP::IPV4,
                                                                                                    ProtocolPP::TUNNEL,
                                                                                                    ipspi,
                                                                                                    1,
                                                                                                    1,
                                                                                                    0,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::AES_CBC,
                                                                                                    32,
                                                                                                    ckey2,
                                                                                                    ProtocolPP::AES_XCBC_MAC,
                                                                                                    16,
                                                                                                    akey2,
                                                                                                    16,
                                                                                                    iv2,
                                                                                                    0,
                                                                                                    std::make_shared<ProtocolPP::jarray<uint8_t>>(0),
                                                                                                    0,
                                                                                                    0xFFFFFFFF,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    false,
                                                                                                    0,
                                                                                                    0xFF,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    0,
                                                                                                    false,
                                                                                                    0,
                                                                                                    1500,
                                                                                                    ipsrc,
                                                                                                    ipdst,
                                                                                                    ProtocolPP::jarray<uint8_t>(0),
                                                                                                    ProtocolPP::IPV4,
                                                                                                    8,
                                                                                                    20,
                                                                                                    0,
                                                                                                    true,
                                                                                                    false,
                                                                                                    true,
                                                                                                    false,
                                                                                                    std::string("./myaudit.log"));

        // create encap and decap IPsec
        std::shared_ptr<ProtocolPP::jprotocol> eipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, myipsec, myreplay);
        std::shared_ptr<ProtocolPP::jprotocol> dipsec = ProtocolPP::jprotocolpp::get_ipsec(myrand, mydipsec, myreplay);

        for (int i = 0; i<50; i++) {
            unsigned int nmtu = myrand->get_u16() & 0x0FF0;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> outputip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expectip = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
        
            // encapsulate the IP packet
            eip->encap_packet(input, outputip);
            eipsec->encap_packet(outputip, output);
            dipsec->decap_packet(output, expectip);
            dip->decap_packet(expectip, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dipsec->get_status());

            // check data
            if (*input != *expect) {
                std::cerr << "IPsec AES-XCBC Data MISMATCH" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testmsec() {
        // MACSEC setup
        uint64_t nmsource = myrand->get_u64();
        uint64_t nmdest = myrand->get_u64();
        uint64_t nsci = myrand->get_u64();
        uint32_t mypn = myrand->get_u32();
        uint32_t vlantag1 = 0x81000FAA;
        uint32_t vlantag2 = 0x81000EBB;
        uint16_t ntype = myrand->get_u16();
        uint8_t  nsl = 0;

        std::shared_ptr<ProtocolPP::jarray<uint8_t>> nckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> nckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*nckey);
    
        // MACSEC security association
        std::shared_ptr<ProtocolPP::jmacsecsa> nmysec = std::make_shared<ProtocolPP::jmacsecsa>(ProtocolPP::ENCAP,
                                                                                                ProtocolPP::AES_GCM_256,
                                                                                                false,
                                                                                                false,
                                                                                                false,
                                                                                                true,
                                                                                                true,
                                                                                                0x0C,
                                                                                                nsl,
                                                                                                ntype,
                                                                                                vlantag1,
                                                                                                vlantag2,
                                                                                                mypn,
                                                                                                1,
                                                                                                0,
                                                                                                20,
                                                                                                16,
                                                                                                32,
                                                                                                nmsource,
                                                                                                nmdest,
                                                                                                nsci,
                                                                                                ProtocolPP::jarray<uint8_t>(3,0),
                                                                                                nckey,
                                                                                                std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
       
        std::shared_ptr<ProtocolPP::jmacsecsa> dmysec = std::make_shared<ProtocolPP::jmacsecsa>(ProtocolPP::DECAP,
                                                                                                ProtocolPP::AES_GCM_256,
                                                                                                false,
                                                                                                false,
                                                                                                false,
                                                                                                true,
                                                                                                true,
                                                                                                0x0C,
                                                                                                nsl,
                                                                                                ntype,
                                                                                                vlantag1,
                                                                                                vlantag2,
                                                                                                mypn,
                                                                                                1,
                                                                                                0,
                                                                                                20,
                                                                                                16,
                                                                                                32,
                                                                                                nmsource,
                                                                                                nmdest,
                                                                                                nsci,
                                                                                                ProtocolPP::jarray<uint8_t>(3,0),
                                                                                                nckey2,
                                                                                                std::make_shared<ProtocolPP::jarray<uint8_t>>(0));
   
        // instantiate both ends of the connection
        std::shared_ptr<ProtocolPP::jprotocol> me = ProtocolPP::jprotocolpp::get_macsec(myrand, nmysec, myreplay);
        std::shared_ptr<ProtocolPP::jprotocol> md = ProtocolPP::jprotocolpp::get_macsec(myrand, dmysec, myreplay);

        for (int i = 0; i<50; i++) {
            unsigned int nmtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
        
            // encapsulate the packet
            me->encap_packet(input, output);
            md->decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, md->get_status());

            // check data
            if (*input != *expect) {
                std::cerr << "MacSec Data MISMATCH" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testmsecxpn() {
        // MACSEC setup
        uint64_t nmsource = myrand->get_u64();
        uint64_t nmdest = myrand->get_u64();
        uint64_t nsci = myrand->get_u64();
        uint32_t myssci = myrand->get_u32();
        uint32_t mypn = myrand->get_u32();
        uint32_t vlantag1 = 0;
        uint32_t vlantag2 = 0;
        uint16_t ntype = myrand->get_u16();
        uint8_t  nsl = 0;

        std::shared_ptr<ProtocolPP::jarray<uint8_t>> nckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> nckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*nckey);
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt   = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(12));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt2  = std::make_shared<ProtocolPP::jarray<uint8_t>>(*salt);
    
        // MACSEC security association
        std::shared_ptr<ProtocolPP::jmacsecsa> nmysec = std::make_shared<ProtocolPP::jmacsecsa>(ProtocolPP::ENCAP,
                                                                                                ProtocolPP::AES_GCM_XPN_256,
                                                                                                false,
                                                                                                true,
                                                                                                false,
                                                                                                true,
                                                                                                true,
                                                                                                0x0C,
                                                                                                nsl,
                                                                                                ntype,
                                                                                                vlantag1,
                                                                                                vlantag2,
                                                                                                mypn,
                                                                                                1,
                                                                                                myssci,
                                                                                                20,
                                                                                                16,
                                                                                                32,
                                                                                                nmsource,
                                                                                                nmdest,
                                                                                                nsci,
                                                                                                ProtocolPP::jarray<uint8_t>(3,0),
                                                                                                nckey,
                                                                                                salt);
       
        std::shared_ptr<ProtocolPP::jmacsecsa> dmysec = std::make_shared<ProtocolPP::jmacsecsa>(ProtocolPP::DECAP,
                                                                                                ProtocolPP::AES_GCM_XPN_256,
                                                                                                false,
                                                                                                true,
                                                                                                true,
                                                                                                false,
                                                                                                true,
                                                                                                0x0C,
                                                                                                nsl,
                                                                                                ntype,
                                                                                                vlantag1,
                                                                                                vlantag2,
                                                                                                mypn,
                                                                                                1,
                                                                                                myssci,
                                                                                                20,
                                                                                                16,
                                                                                                32,
                                                                                                nmsource,
                                                                                                nmdest,
                                                                                                nsci,
                                                                                                ProtocolPP::jarray<uint8_t>(3,0),
                                                                                                nckey2,
                                                                                                salt2);
   
        // instantiate both ends of the connection
        std::shared_ptr<ProtocolPP::jprotocol> me = ProtocolPP::jprotocolpp::get_macsec(myrand, nmysec, myreplay);
        std::shared_ptr<ProtocolPP::jprotocol> md = ProtocolPP::jprotocolpp::get_macsec(myrand, dmysec, myreplay);

        for (int i = 0; i<50; i++) {
            unsigned int nmtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
        
            // encapsulate the packet
            me->encap_packet(input, output);
            md->decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, md->get_status());

            // check data
            if (*input != *expect) {
                std::cerr << "MacSec Data MISMATCH" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testtls() {
        // TLS setup
        uint64_t seqnum = (0x0000FFFFFFFFFFFF & myrand->get_u64());
    
        for (int j=0; j<1; j++) {
            // TLS security association
            std::shared_ptr<ProtocolPP::jtlsa> mytls = std::make_shared<ProtocolPP::jtlsa>();
            std::shared_ptr<ProtocolPP::jtlsa> mydtls = std::make_shared<ProtocolPP::jtlsa>();

            if (j == 0) {
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(48));

                mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_PSK_WITH_AES_256_CBC_SHA384);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 16);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 32);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);

                mydtls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_PSK_WITH_AES_256_CBC_SHA384);
                mydtls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 16);
                mydtls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 32);
                mydtls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mydtls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mydtls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            }
            ProtocolPP::jarray<uint8_t> arwin = ProtocolPP::jarray<uint8_t>(3,0);
            mytls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mytls->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::DTLS);
            mytls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, arwin);
            mytls->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls->set_field<bool>(ProtocolPP::field_t::IVEX, true);
       
            mydtls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mydtls->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::DTLS);
            mydtls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mydtls->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mydtls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum-1);
            mydtls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mydtls->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, arwin);
            mydtls->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mydtls->set_field<bool>(ProtocolPP::field_t::IVEX, true);
       
            // instantiate both ends of the connection
            std::shared_ptr<ProtocolPP::jprotocol> etls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dtls = ProtocolPP::jprotocolpp::get_tls(myrand, mydtls, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FF0;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the packet
                etls->encap_packet(input, output);
                dtls->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dtls->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "TLS AES-CBC Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testtlsfile() {
        // TLS setup
        uint64_t seqnum = (0x0000FFFFFFFFFFFF & myrand->get_u64());
    
        std::string myfile("./test.dat");
        std::string myfile2("./test_outtls.dat");
        unsigned int nmtu = 1500;

        for (int j=0; j<1; j++) {
            // TLS security association
            std::shared_ptr<ProtocolPP::jtlsa> mytls = std::make_shared<ProtocolPP::jtlsa>();
            std::shared_ptr<ProtocolPP::jtlsa> mydtls = std::make_shared<ProtocolPP::jtlsa>();

            if (j == 0) {
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));

                mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_PSK_WITH_AES_256_CBC_SHA384);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 16);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 32);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);

                mydtls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_PSK_WITH_AES_256_CBC_SHA384);
                mydtls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 16);
                mydtls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 32);
                mydtls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mydtls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mydtls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            }
            ProtocolPP::jarray<uint8_t> arwin = ProtocolPP::jarray<uint8_t>(3,0);
            mytls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mytls->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::DTLS);
            mytls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, arwin);
            mytls->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls->set_field<bool>(ProtocolPP::field_t::IVEX, true);
       
            mydtls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mydtls->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::DTLS);
            mydtls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mydtls->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mydtls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum-1);
            mydtls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mydtls->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, arwin);
            mydtls->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mydtls->set_field<bool>(ProtocolPP::field_t::IVEX, true);
       
            // instantiate both ends of the connection
            std::shared_ptr<ProtocolPP::jprotocol> etls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls, myfile, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dtls = ProtocolPP::jprotocolpp::get_tls(myrand, mydtls, myfile2, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FF0;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the packet
                etls->encap_packet(output);
                dtls->decap_packet(output);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dtls->get_status());
            }
        }
    }

    void testtlschacha() {
        // TLS setup
        uint64_t seqnum = myrand->get_u64();
    
        for (int j=0; j<2; j++) {
            // TLS security association
            ProtocolPP::jtlsa mytls1;
            std::shared_ptr<ProtocolPP::jtlsa> mytls = std::make_shared<ProtocolPP::jtlsa>(mytls1);
            std::shared_ptr<ProtocolPP::jtlsa> mytls2 = std::make_shared<ProtocolPP::jtlsa>();
            if (j == 0) {
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(12));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);

                mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_ECDHE_PSK_WITH_CHACHA20_POLY1305_SHA256);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);

                mytls2->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_ECDHE_PSK_WITH_CHACHA20_POLY1305_SHA256);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            }
            else if (j == 1) {
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(12));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);

                mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_ECDHE_PSK_WITH_CHACHA20_POLY1305_SHA256);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);

                mytls2->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_ECDHE_PSK_WITH_CHACHA20_POLY1305_SHA256);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            }
       
            mytls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mytls->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::TLS12);
            mytls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mytls->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls->set_field<bool>(ProtocolPP::field_t::IVEX, true);

            mytls2->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mytls2->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::TLS12);
            mytls2->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls2->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls2->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls2->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls2->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mytls2->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls2->set_field<bool>(ProtocolPP::field_t::IVEX, true);

            // instantiate both ends of the connection
            std::shared_ptr<ProtocolPP::jprotocol> etls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dtls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls2, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the packet
                etls->encap_packet(input, output);
                dtls->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dtls->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "TLS CHACHA20 Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testtlsgcm() {
        // TLS setup
        uint64_t seqnum = myrand->get_u64();
    
        for (int j=0; j<2; j++) {
            // TLS security association
            std::shared_ptr<ProtocolPP::jtlsa> mytls = std::make_shared<ProtocolPP::jtlsa>();
            std::shared_ptr<ProtocolPP::jtlsa> mytls2 = std::make_shared<ProtocolPP::jtlsa>();
            if (j == 0) {
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(12));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(4));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*salt);

                mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_RSA_WITH_AES_256_GCM_SHA384);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);

                mytls2->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_RSA_WITH_AES_256_GCM_SHA384);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt2);
            }
            else if (j == 1) {
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(12));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(4));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*salt);

                mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_RSA_WITH_AES_256_GCM_SHA384);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);

                mytls2->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_RSA_WITH_AES_256_GCM_SHA384);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt2);
            }
       
            mytls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mytls->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::TLS12);
            mytls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mytls->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls->set_field<bool>(ProtocolPP::field_t::IVEX, true);

            mytls2->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mytls2->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::TLS12);
            mytls2->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls2->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls2->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls2->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls2->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mytls2->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls2->set_field<bool>(ProtocolPP::field_t::IVEX, true);

            // instantiate both ends of the connection
            std::shared_ptr<ProtocolPP::jprotocol> etls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dtls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls2, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the packet
                etls->encap_packet(input, output);
                dtls->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dtls->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "TLS AES-GCM Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testtlsccm() {
        // TLS setup
        uint64_t seqnum = myrand->get_u64();
    
        for (int j=0; j<2; j++) {
            // TLS security association
            std::shared_ptr<ProtocolPP::jtlsa> mytls = std::make_shared<ProtocolPP::jtlsa>();
            std::shared_ptr<ProtocolPP::jtlsa> mytls2 = std::make_shared<ProtocolPP::jtlsa>();
            if (j == 0) {
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(3));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*salt);

                mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_RSA_WITH_AES_256_CCM);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 8);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);

                mytls2->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_RSA_WITH_AES_256_CCM);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 8);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt2);
            }
            else if (j == 1) {
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(3));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*salt);

                mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_RSA_WITH_AES_256_CCM);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 8);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);

                mytls2->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_RSA_WITH_AES_256_CCM);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 8);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt2);
            }
       
            mytls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mytls->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::TLS12);
            mytls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mytls->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls->set_field<bool>(ProtocolPP::field_t::IVEX, true);

            mytls2->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mytls2->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::TLS12);
            mytls2->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls2->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls2->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls2->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls2->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mytls2->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls2->set_field<bool>(ProtocolPP::field_t::IVEX, true);

            // instantiate both ends of the connection
            std::shared_ptr<ProtocolPP::jprotocol> etls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dtls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls2, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the packet
                etls->encap_packet(input, output);
                dtls->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dtls->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "TLS AES-GCM Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testtlsencmac() {
        // TLS setup
        uint64_t seqnum = myrand->get_u64();
    
        for (int j=0; j<1; j++) {
            // TLS security association
            std::shared_ptr<ProtocolPP::jtlsa> mytls = std::make_shared<ProtocolPP::jtlsa>();
            std::shared_ptr<ProtocolPP::jtlsa> mytls2 = std::make_shared<ProtocolPP::jtlsa>();
            if (j == 0) {
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(12));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(32));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(4));

                mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_DH_RSA_WITH_AES_256_GCM_SHA384);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);

                mytls2->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_DH_RSA_WITH_AES_256_GCM_SHA384);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
                mytls2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
                mytls2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);
            }
            mytls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mytls->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::TLS12);
            mytls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mytls->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls->set_field<bool>(ProtocolPP::field_t::IVEX, true);
            mytls->set_field<bool>(ProtocolPP::field_t::ENCTHENMAC, true);

            mytls2->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mytls2->set_field<ProtocolPP::tlsver_t>(ProtocolPP::field_t::VERSION, ProtocolPP::TLS12);
            mytls2->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls2->set_field<uint16_t>(ProtocolPP::field_t::EPOCH, 0);
            mytls2->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls2->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mytls2->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mytls2->set_field<bool>(ProtocolPP::field_t::RANDIV, false);
            mytls2->set_field<bool>(ProtocolPP::field_t::IVEX, true);
            mytls2->set_field<bool>(ProtocolPP::field_t::ENCTHENMAC, true);

            // instantiate both ends of the connection
            std::shared_ptr<ProtocolPP::jprotocol> etls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dtls = ProtocolPP::jprotocolpp::get_tls(myrand, mytls2, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FF0;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the packet
                etls->encap_packet(input, output);
                dtls->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dtls->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "TLS Camellia CBC Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testdtls13() {
        // TLS setup
        uint64_t seqnum = (0x0000FFFFFFFFFFFF & myrand->get_u64());

        //for (int j=1; j<2; j++) {
            // TLS security association
            std::shared_ptr<ProtocolPP::jdtlsa13> mytls = std::make_shared<ProtocolPP::jdtlsa13>();
            std::shared_ptr<ProtocolPP::jdtlsa13> mydtls = std::make_shared<ProtocolPP::jdtlsa13>();

            std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(12));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> app = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));

            mytls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_AES_256_GCM_SHA384);
            mytls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
            mytls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
            mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
            mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mytls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::APP_TRAFFIC_SECRET, app);

            mydtls->set_field<ProtocolPP::tls_ciphersuite_t>(ProtocolPP::field_t::CIPHERSUITE, ProtocolPP::TLS_AES_256_GCM_SHA384);
            mydtls->set_field<uint32_t>(ProtocolPP::field_t::IVLEN, 12);
            mydtls->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
            mydtls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::IV, iv);
            mydtls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mydtls->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::APP_TRAFFIC_SECRET, app);

            ProtocolPP::jarray<uint8_t> arwin = ProtocolPP::jarray<uint8_t>(3,0);
            mytls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mytls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mytls->set_field<uint64_t>(ProtocolPP::field_t::EPOCH, 4);
            mytls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mytls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 0);
       
            mydtls->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mydtls->set_field<ProtocolPP::tlstype_t>(ProtocolPP::field_t::TYPE, ProtocolPP::APPLICATION);
            mydtls->set_field<uint64_t>(ProtocolPP::field_t::EPOCH, 4);
            mydtls->set_field<uint64_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mydtls->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 0);
       
            // instantiate both ends of the connection
            std::shared_ptr<ProtocolPP::jprotocol> etls = ProtocolPP::jprotocolpp::get_dtls13(myrand, mytls, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dtls = ProtocolPP::jprotocolpp::get_dtls13(myrand, mydtls, myreplay);
    
            for (int i = 0; i<1; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FF0;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the packet
                etls->encap_packet(input, output);
                dtls->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dtls->get_status());
            }
        //}
    }


    void testsrtpctr() {
        // SRTP setup
        uint16_t seqnum = myrand->get_u16();
        uint32_t ssrc = myrand->get_u32();
        std::shared_ptr<ProtocolPP::jarray<uint32_t>> csrc = std::make_shared<ProtocolPP::jarray<uint32_t>>(myrand->getword(2));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(14));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
    
        // SRTP security association
        std::shared_ptr<ProtocolPP::jsrtpsa> mysrtp = std::make_shared<ProtocolPP::jsrtpsa>();
        mysrtp->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_GCM);
        mysrtp->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::MODE, ProtocolPP::SRTP);
        mysrtp->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
        mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ROC, 0);
        mysrtp->set_field<uint16_t>(ProtocolPP::field_t::SEQNUM, seqnum);
        mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);
        mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
        mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
        mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
        mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
        mysrtp->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
        mysrtp->set_field<bool>(ProtocolPP::field_t::MKI, false);
        mysrtp->set_field<uint32_t>(ProtocolPP::field_t::SSRC, ssrc);
        mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint32_t>>>(ProtocolPP::field_t::CSRC, csrc);
       
        // SRTP security association
        std::shared_ptr<ProtocolPP::jsrtpsa> mysrtp2 = std::make_shared<ProtocolPP::jsrtpsa>(mysrtp);
        mysrtp2->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
   
        // instantiate both ends of the connection
        std::shared_ptr<ProtocolPP::jprotocol> esrtp = ProtocolPP::jprotocolpp::get_srtp(myrand, mysrtp, myreplay);
        std::shared_ptr<ProtocolPP::jprotocol> dsrtp = ProtocolPP::jprotocolpp::get_srtp(myrand, mysrtp2, myreplay);

        for (int i = 0; i<50; i++) {
            unsigned int nmtu = myrand->get_u16() & 0x0FFF;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
        
            // encapsulate the packet
            esrtp->encap_packet(input, output);
            dsrtp->decap_packet(output, expect);

            // check the status
            CPPUNIT_ASSERT_EQUAL(mystatus, dsrtp->get_status());

            // check data
            if (*input != *expect) {
                std::cerr << "SRTP CTR Data MISMATCH" << std::endl;
                expect->debug(*input);
            }
        }
    }

    void testsrtpgcm() {
        // SRTP setup
        uint16_t seqnum = myrand->get_u16();
        uint32_t ssrc = myrand->get_u32();
        std::shared_ptr<ProtocolPP::jarray<uint32_t>> csrc = std::make_shared<ProtocolPP::jarray<uint32_t>>(myrand->getword(5));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
    
        for (int j=0; j<3; j++) {
        
            unsigned int keylen = ((j>2) ? 16 : 32);
            
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(12));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));

            // SRTP security association
            std::shared_ptr<ProtocolPP::jsrtpsa> mysrtp = std::make_shared<ProtocolPP::jsrtpsa>();
            mysrtp->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::MODE, ProtocolPP::SRTP);
            mysrtp->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ROC, 0);
            mysrtp->set_field<uint16_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);
            mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mysrtp->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mysrtp->set_field<bool>(ProtocolPP::MKI, false);
            mysrtp->set_field<uint32_t>(ProtocolPP::field_t::SSRC, ssrc);
            mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint32_t>>>(ProtocolPP::field_t::CSRC, csrc);
       
            std::shared_ptr<ProtocolPP::jsrtpsa> mysrtp2 = std::make_shared<ProtocolPP::jsrtpsa>();
            mysrtp2->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::MODE, ProtocolPP::SRTP);
            mysrtp2->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ROC, 0);
            mysrtp2->set_field<uint16_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mysrtp2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);
            mysrtp2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mysrtp2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mysrtp2->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mysrtp2->set_field<bool>(ProtocolPP::MKI, false);
            mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::SSRC, ssrc);
            mysrtp2->set_field<std::shared_ptr<ProtocolPP::jarray<uint32_t>>>(ProtocolPP::field_t::CSRC, csrc);
       
            if (j == 0) {
                mysrtp->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_GCM_8);
                mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 8);
                mysrtp2->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_GCM_8);
                mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 8);
            }
            else if (j == 1) {
                mysrtp->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_GCM_12);
                mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 12);
                mysrtp2->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_GCM_12);
                mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 12);
            }
            else if (j == 2) {
                mysrtp->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_GCM);
                mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mysrtp2->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_GCM);
                mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
            }

            // instantiate both ends of the connection
            std::shared_ptr<ProtocolPP::jprotocol> esrtp = ProtocolPP::jprotocolpp::get_srtp(myrand, mysrtp, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dsrtp = ProtocolPP::jprotocolpp::get_srtp(myrand, mysrtp2, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x01FF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the packet
                esrtp->encap_packet(input, output);
                dsrtp->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dsrtp->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "SRTP GCM DATA MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testsrtpccm() {
        // SRTP setup
        uint16_t seqnum = myrand->get_u16();
        uint32_t ssrc = myrand->get_u32();
        std::shared_ptr<ProtocolPP::jarray<uint32_t>> csrc = std::make_shared<ProtocolPP::jarray<uint32_t>>(myrand->getword(10));
        std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(16));
    
        for (int j=0; j<3; j++) {
        
            unsigned int keylen = ((j>2) ? 16 : 32);
            
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> salt = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(12));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));

            // SRTP security association
            std::shared_ptr<ProtocolPP::jsrtpsa> mysrtp = std::make_shared<ProtocolPP::jsrtpsa>();
            mysrtp->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::MODE, ProtocolPP::SRTP);
            mysrtp->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ROC, 0);
            mysrtp->set_field<uint16_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);
            mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mysrtp->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mysrtp->set_field<bool>(ProtocolPP::MKI, false);
            mysrtp->set_field<uint32_t>(ProtocolPP::field_t::SSRC, ssrc);
            mysrtp->set_field<std::shared_ptr<ProtocolPP::jarray<uint32_t>>>(ProtocolPP::field_t::CSRC, csrc);
       
            std::shared_ptr<ProtocolPP::jsrtpsa> mysrtp2 = std::make_shared<ProtocolPP::jsrtpsa>();
            mysrtp2->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::MODE, ProtocolPP::SRTP);
            mysrtp2->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ROC, 0);
            mysrtp2->set_field<uint16_t>(ProtocolPP::field_t::SEQNUM, seqnum);
            mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ARLEN, 20);
            mysrtp2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::SALT, salt);
            mysrtp2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mysrtp2->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mysrtp2->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(3,0));
            mysrtp2->set_field<bool>(ProtocolPP::MKI, false);
            mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::SSRC, ssrc);
            mysrtp2->set_field<std::shared_ptr<ProtocolPP::jarray<uint32_t>>>(ProtocolPP::field_t::CSRC, csrc);
       
            if (j == 0) {
                mysrtp->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_CCM_8);
                mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 8);
                mysrtp2->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_CCM_8);
                mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 8);
            }
            else if (j == 1) {
                mysrtp->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_CCM_12);
                mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 12);
                mysrtp2->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_CCM_12);
                mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 12);
            }
            else if (j == 2) {
                mysrtp->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_CCM);
                mysrtp->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
                mysrtp2->set_field<ProtocolPP::srtpcipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AEAD_AES_256_CCM);
                mysrtp2->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
            }

            // instantiate both ends of the connection
            std::shared_ptr<ProtocolPP::jprotocol> esrtp = ProtocolPP::jprotocolpp::get_srtp(myrand, mysrtp, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dsrtp = ProtocolPP::jprotocolpp::get_srtp(myrand, mysrtp2, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x01FF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
            
                // encapsulate the packet
                esrtp->encap_packet(input, output);
                dsrtp->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dsrtp->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "SRTP CCM DATA MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testwificcmp() {
        // Wifi setup
        for (unsigned int j=0; j<1; j++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8));
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
    
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
    
            // populate the security association
            ProtocolPP::jwifisa mywifi1;
            std::shared_ptr<ProtocolPP::jwifisa> mywifi = std::make_shared<ProtocolPP::jwifisa>(mywifi1);
            mywifi->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mywifi->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AES_CCM);
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR1, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR2, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR3, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR4, myrand->get_u64());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::QOSCTL, myrand->get_u16());
            mywifi->set_field<uint32_t>(ProtocolPP::field_t::HTCTL, myrand->get_u16());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::PN, (myrand->get_u64() & 0x0000FFFFFFFFFFFF));
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::FRAMECTL, myrand->get_u16());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::ID, myrand->get_u16());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::SEQCTL, myrand->get_u16());
            mywifi->set_field<uint8_t>(ProtocolPP::field_t::KEYID, myrand->get_u8());
            mywifi->set_field<bool>(ProtocolPP::field_t::EXTIV, true);
            mywifi->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 8);
            mywifi->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mywifi->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, mywin);

            std::shared_ptr<ProtocolPP::jwifisa> mywifid = std::make_shared<ProtocolPP::jwifisa>(mywifi);
            mywifid->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mywifid->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);

            // create encap and decap Wifi 
            std::shared_ptr<ProtocolPP::jprotocol> ewifi = ProtocolPP::jprotocolpp::get_wifi(myrand, mywifi, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dwifi = ProtocolPP::jprotocolpp::get_wifi(myrand, mywifid, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                ewifi->encap_packet(input, output);
                dwifi->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dwifi->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "Wifi CCM Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testwifigcmp() {
        // Wifi setup
        for (unsigned int j=0; j<1; j++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8));
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
    
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
    
            // populate the security association
            ProtocolPP::jwifisa mywifi1;
            std::shared_ptr<ProtocolPP::jwifisa> mywifi = std::make_shared<ProtocolPP::jwifisa>(mywifi1);
            mywifi->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mywifi->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AES_GCM);
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR1, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR2, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR3, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR4, myrand->get_u64());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::QOSCTL, myrand->get_u16());
            mywifi->set_field<uint32_t>(ProtocolPP::field_t::HTCTL, myrand->get_u16());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::PN, (myrand->get_u64() & 0x0000FFFFFFFFFFFF));
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::FRAMECTL, myrand->get_u16());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::ID, myrand->get_u16());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::SEQCTL, myrand->get_u16());
            mywifi->set_field<uint8_t>(ProtocolPP::field_t::KEYID, myrand->get_u8());
            mywifi->set_field<bool>(ProtocolPP::field_t::EXTIV, true);
            mywifi->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
            mywifi->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mywifi->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, mywin);

            std::shared_ptr<ProtocolPP::jwifisa> mywifid = std::make_shared<ProtocolPP::jwifisa>(mywifi);
            mywifid->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mywifid->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);

            // create encap and decap Wifi 
            std::shared_ptr<ProtocolPP::jprotocol> ewifi = ProtocolPP::jprotocolpp::get_wifi(myrand, mywifi, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dwifi = ProtocolPP::jprotocolpp::get_wifi(myrand, mywifid, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                ewifi->encap_packet(input, output);
                dwifi->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dwifi->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "Wifi CCM Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testwifism4ccmp() {
        // Wifi setup
        for (unsigned int j=0; j<1; j++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8));
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
    
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
    
            // populate the security association
            ProtocolPP::jwifisa mywifi1;
            std::shared_ptr<ProtocolPP::jwifisa> mywifi = std::make_shared<ProtocolPP::jwifisa>(mywifi1);
            mywifi->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mywifi->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::SM4_CCM);
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR1, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR2, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR3, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR4, myrand->get_u64());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::QOSCTL, myrand->get_u16());
            mywifi->set_field<uint32_t>(ProtocolPP::field_t::HTCTL, myrand->get_u16());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::PN, (myrand->get_u64() & 0x0000FFFFFFFFFFFF));
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::FRAMECTL, myrand->get_u16());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::ID, myrand->get_u16());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::SEQCTL, myrand->get_u16());
            mywifi->set_field<uint8_t>(ProtocolPP::field_t::KEYID, myrand->get_u8());
            mywifi->set_field<bool>(ProtocolPP::field_t::EXTIV, true);
            mywifi->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 8);
            mywifi->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mywifi->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, mywin);

            std::shared_ptr<ProtocolPP::jwifisa> mywifid = std::make_shared<ProtocolPP::jwifisa>(mywifi);
            mywifid->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mywifid->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);

            // create encap and decap Wifi 
            std::shared_ptr<ProtocolPP::jprotocol> ewifi = ProtocolPP::jprotocolpp::get_wifi(myrand, mywifi, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dwifi = ProtocolPP::jprotocolpp::get_wifi(myrand, mywifid, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                ewifi->encap_packet(input, output);
                dwifi->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dwifi->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "Wifi CCM Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testwifism4gcmp() {
        // Wifi setup
        for (unsigned int j=0; j<1; j++) {
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> iv = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(8));
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
    
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
    
            // populate the security association
            ProtocolPP::jwifisa mywifi1;
            std::shared_ptr<ProtocolPP::jwifisa> mywifi = std::make_shared<ProtocolPP::jwifisa>(mywifi1);
            mywifi->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mywifi->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::SM4_GCM);
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR1, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR2, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR3, myrand->get_u64());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::ADDR4, myrand->get_u64());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::QOSCTL, myrand->get_u16());
            mywifi->set_field<uint32_t>(ProtocolPP::field_t::HTCTL, myrand->get_u16());
            mywifi->set_field<uint64_t>(ProtocolPP::field_t::PN, (myrand->get_u64() & 0x0000FFFFFFFFFFFF));
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::FRAMECTL, myrand->get_u16());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::ID, myrand->get_u16());
            mywifi->set_field<uint16_t>(ProtocolPP::field_t::SEQCTL, myrand->get_u16());
            mywifi->set_field<uint8_t>(ProtocolPP::field_t::KEYID, myrand->get_u8());
            mywifi->set_field<bool>(ProtocolPP::field_t::EXTIV, true);
            mywifi->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 16);
            mywifi->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mywifi->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, mywin);

            std::shared_ptr<ProtocolPP::jwifisa> mywifid = std::make_shared<ProtocolPP::jwifisa>(mywifi);
            mywifid->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mywifid->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);

            // create encap and decap Wifi 
            std::shared_ptr<ProtocolPP::jprotocol> ewifi = ProtocolPP::jprotocolpp::get_wifi(myrand, mywifi, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dwifi = ProtocolPP::jprotocolpp::get_wifi(myrand, mywifid, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                ewifi->encap_packet(input, output);
                dwifi->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dwifi->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "Wifi CCM Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testwimax() {
        // WiMax setup
        for (unsigned int j=0; j<1; j++) {
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
            ProtocolPP::jarray<uint8_t> blank = ProtocolPP::jarray<uint8_t>(0);
    
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jwimaxsa> mywimax = std::make_shared<ProtocolPP::jwimaxsa>();
            mywimax->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::ENCAP);
            mywimax->set_field<ProtocolPP::wimaxmode_t>(ProtocolPP::field_t::MODE, ProtocolPP::OFDM);
            mywimax->set_field<uint8_t>(ProtocolPP::field_t::TYPE, myrand->get_u8());
            mywimax->set_field<uint8_t>(ProtocolPP::field_t::EKS, myrand->get_u8());
            mywimax->set_field<uint16_t>(ProtocolPP::field_t::CID, myrand->get_u32());
            mywimax->set_field<uint32_t>(ProtocolPP::field_t::PN, myrand->get_u32());
            mywimax->set_field<bool>(ProtocolPP::field_t::HT, false);
            mywimax->set_field<bool>(ProtocolPP::field_t::EC, true);
            mywimax->set_field<bool>(ProtocolPP::field_t::ESF, false);
            mywimax->set_field<bool>(ProtocolPP::field_t::CI, false);
            mywimax->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mywimax->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, blank);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jwimaxsa> mywimaxd = std::make_shared<ProtocolPP::jwimaxsa>(mywimax);
            mywimaxd->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DECAP);
            mywimaxd->set_field<uint32_t>(ProtocolPP::field_t::PN, mywimax->get_field<uint32_t>(ProtocolPP::field_t::PN)-1);
            mywimaxd->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            mywimaxd->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::ARWIN, ProtocolPP::jarray<uint8_t>(28,0));
    
            // create encap and decap wimax 
            std::shared_ptr<ProtocolPP::jprotocol> ewimax = ProtocolPP::jprotocolpp::get_wimax(myrand, mywimax, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dwimax = ProtocolPP::jprotocolpp::get_wimax(myrand, mywimaxd, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = myrand->get_u16() & 0x03FF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                ewimax->encap_packet(input, output);
                dwimax->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dwimax->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "WiMax Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testltesnow() {
        // LTE setup
        for (unsigned int j=0; j<4; j++) {
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
            ProtocolPP::jarray<uint8_t> blank = ProtocolPP::jarray<uint8_t>(0);
    
            uint32_t bearer = myrand->get_uint("0..31");
            uint32_t fresh = myrand->get_u32();
            uint32_t seqnum = myrand->get_u32();
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*akey);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylte = std::make_shared<ProtocolPP::jltesa>();
            mylte->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::TYPE, ProtocolPP::LTE);
            mylte->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylte->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::SNOWE);
            mylte->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH, ProtocolPP::SNOWA);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::CKEYLEN, ckey->get_size());
            mylte->set_field<uint32_t>(ProtocolPP::field_t::AKEYLEN, akey->get_size());
            mylte->set_field<bool>(ProtocolPP::field_t::DATACTRL, true);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PDUTYPE, 0);
            mylte->set_field<bool>(ProtocolPP::field_t::POLLBIT, false);
            mylte->set_field<bool>(ProtocolPP::field_t::EXTENSION, false);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::HDREXT, 0);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::LENGTHIND, 0);
            mylte->set_field<int>(ProtocolPP::field_t::SNLEN, ((j==0) ? 7 : ((j==1) ? 12 : 18)));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, ((j==0) ? (seqnum & 0x7F) : ((j==1) ? (seqnum & 0xFFF) : ((j==2) ? (seqnum & 0x7FFF) : (seqnum & 0x3FFFF)))));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HFNI, ((j==0) ? (seqnum & 0x1FFFFFF) : ((j==1) ? (seqnum & 0xFFFFF) : ((j==2) ? (seqnum & 0x1FFFF) : (seqnum & 0x3FFF)))));
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SUFI, blank);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FMS, 0);
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::BITMAP, blank);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PGKINDEX, 1);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::PTKINDENT, 0xAAC1);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::SDUTYPE, ProtocolPP::IP);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::KDID, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::NMP, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HRW, 0);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::BEARER, bearer);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FRESH, fresh);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 4);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylted = std::make_shared<ProtocolPP::jltesa>(mylte);
            mylted->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey2);
    
            // create encap and decap wimax 
            std::shared_ptr<ProtocolPP::jprotocol> elte = ProtocolPP::jprotocolpp::get_lte(myrand, mylte, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dlte = ProtocolPP::jprotocolpp::get_lte(myrand, mylted, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                elte->encap_packet(input, output);
                dlte->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dlte->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "LTESNOW Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testltesnowv() {
        // LTE setup
        for (unsigned int j=0; j<4; j++) {
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
            ProtocolPP::jarray<uint8_t> blank = ProtocolPP::jarray<uint8_t>(0);
    
            uint32_t bearer = myrand->get_uint("0..31");
            uint32_t fresh = myrand->get_u32();
            uint32_t seqnum = myrand->get_u32();
            unsigned int keylen = 32;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*akey);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylte = std::make_shared<ProtocolPP::jltesa>();
            mylte->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::TYPE, ProtocolPP::LTE);
            mylte->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylte->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::SNOWV);
            mylte->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH, ProtocolPP::SNOWVA);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::CKEYLEN, ckey->get_size());
            mylte->set_field<uint32_t>(ProtocolPP::field_t::AKEYLEN, akey->get_size());
            mylte->set_field<bool>(ProtocolPP::field_t::DATACTRL, true);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PDUTYPE, 0);
            mylte->set_field<bool>(ProtocolPP::field_t::POLLBIT, false);
            mylte->set_field<bool>(ProtocolPP::field_t::EXTENSION, false);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::HDREXT, 0);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::LENGTHIND, 0);
            mylte->set_field<int>(ProtocolPP::field_t::SNLEN, ((j==0) ? 7 : ((j==1) ? 12 : 18)));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, ((j==0) ? (seqnum & 0x7F) : ((j==1) ? (seqnum & 0xFFF) : ((j==2) ? (seqnum & 0x7FFF) : (seqnum & 0x3FFFF)))));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HFNI, ((j==0) ? (seqnum & 0x1FFFFFF) : ((j==1) ? (seqnum & 0xFFFFF) : ((j==2) ? (seqnum & 0x1FFFF) : (seqnum & 0x3FFF)))));
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SUFI, blank);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FMS, 0);
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::BITMAP, blank);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PGKINDEX, 1);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::PTKINDENT, 0xAAC1);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::SDUTYPE, ProtocolPP::IP);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::KDID, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::NMP, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HRW, 0);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::BEARER, bearer);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FRESH, fresh);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 4);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylted = std::make_shared<ProtocolPP::jltesa>(mylte);
            mylted->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey2);
    
            // create encap and decap wimax 
            std::shared_ptr<ProtocolPP::jprotocol> elte = ProtocolPP::jprotocolpp::get_lte(myrand, mylte, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dlte = ProtocolPP::jprotocolpp::get_lte(myrand, mylted, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                elte->encap_packet(input, output);
                dlte->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dlte->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "LTESNOWV Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testltesnowvgcm() {
        // LTE setup
        for (unsigned int j=0; j<4; j++) {
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
            ProtocolPP::jarray<uint8_t> blank = ProtocolPP::jarray<uint8_t>(0);
    
            uint32_t bearer = myrand->get_uint("0..31");
            uint32_t fresh = myrand->get_u32();
            uint32_t seqnum = myrand->get_u32();
            unsigned int keylen = 32;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylte = std::make_shared<ProtocolPP::jltesa>();
            mylte->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::TYPE, ProtocolPP::LTE);
            mylte->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylte->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::SNOWV_GCM);
            mylte->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH, ProtocolPP::NULL_AUTH);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::CKEYLEN, ckey->get_size());
            mylte->set_field<bool>(ProtocolPP::field_t::DATACTRL, true);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PDUTYPE, 0);
            mylte->set_field<bool>(ProtocolPP::field_t::POLLBIT, false);
            mylte->set_field<bool>(ProtocolPP::field_t::EXTENSION, false);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::HDREXT, 0);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::LENGTHIND, 0);
            mylte->set_field<int>(ProtocolPP::field_t::SNLEN, ((j==0) ? 7 : ((j==1) ? 12 : 18)));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, ((j==0) ? (seqnum & 0x7F) : ((j==1) ? (seqnum & 0xFFF) : ((j==2) ? (seqnum & 0x7FFF) : (seqnum & 0x3FFFF)))));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HFNI, ((j==0) ? (seqnum & 0x1FFFFFF) : ((j==1) ? (seqnum & 0xFFFFF) : ((j==2) ? (seqnum & 0x1FFFF) : (seqnum & 0x3FFF)))));
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SUFI, blank);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FMS, 0);
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::BITMAP, blank);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PGKINDEX, 1);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::PTKINDENT, 0xAAC1);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::SDUTYPE, ProtocolPP::IP);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::KDID, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::NMP, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HRW, 0);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::BEARER, bearer);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FRESH, fresh);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 4);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylted = std::make_shared<ProtocolPP::jltesa>(mylte);
            mylted->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
    
            // create encap and decap lte
            std::shared_ptr<ProtocolPP::jprotocol> elte = ProtocolPP::jprotocolpp::get_lte(myrand, mylte, myreplay);
            std::shared_ptr<ProtocolPP::jprotocol> dlte = ProtocolPP::jprotocolpp::get_lte(myrand, mylted, myreplay);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                elte->encap_packet(input, output);
                dlte->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dlte->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "LTESNOWV_GCM Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testltezuc() {
        // LTE setup
        for (unsigned int j=0; j<4; j++) {
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
            ProtocolPP::jarray<uint8_t> blank = ProtocolPP::jarray<uint8_t>(0);
    
            uint32_t bearer = myrand->get_uint("0..31");
            uint32_t fresh = myrand->get_u32();
            uint32_t seqnum = myrand->get_u32();
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*akey);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylte = std::make_shared<ProtocolPP::jltesa>();
            mylte->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::TYPE, ProtocolPP::LTE);
            mylte->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DOWNLINK);
            mylte->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::ZUCE);
            mylte->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH, ProtocolPP::ZUCA);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::CKEYLEN, ckey->get_size());
            mylte->set_field<uint32_t>(ProtocolPP::field_t::AKEYLEN, akey->get_size());
            mylte->set_field<bool>(ProtocolPP::field_t::DATACTRL, true);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PDUTYPE, 0);
            mylte->set_field<bool>(ProtocolPP::field_t::POLLBIT, false);
            mylte->set_field<bool>(ProtocolPP::field_t::EXTENSION, false);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::HDREXT, 0);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::LENGTHIND, 0);
            mylte->set_field<int>(ProtocolPP::field_t::SNLEN, ((j==0) ? 7 : ((j==1) ? 12 : 18)));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, ((j==0) ? (seqnum & 0x7F) : ((j==1) ? (seqnum & 0xFFF) : ((j==2) ? (seqnum & 0x7FFF) : (seqnum & 0x3FFFF)))));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HFNI, ((j==0) ? (seqnum & 0x1FFFFFF) : ((j==1) ? (seqnum & 0xFFFFF) : ((j==2) ? (seqnum & 0x1FFFF) : (seqnum & 0x3FFF)))));
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SUFI, blank);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FMS, 0);
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::BITMAP, blank);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PGKINDEX, 1);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::PTKINDENT, 0xAAC1);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::SDUTYPE, ProtocolPP::IP);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::KDID, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::NMP, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HRW, 0);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::BEARER, bearer);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FRESH, fresh);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 4);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylted = std::make_shared<ProtocolPP::jltesa>(mylte);
            mylted->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DOWNLINK);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey2);
    
            // create encap and decap wimax 
            std::shared_ptr<ProtocolPP::jprotocol> elte = ProtocolPP::jprotocolpp::get_lte(myrand, mylte);
            std::shared_ptr<ProtocolPP::jprotocol> dlte = ProtocolPP::jprotocolpp::get_lte(myrand, mylted);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                elte->encap_packet(input, output);
                dlte->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dlte->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "LTEZUC Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testlteaes() {
        // LTE setup
        for (unsigned int j=0; j<4; j++) {
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
            ProtocolPP::jarray<uint8_t> blank = ProtocolPP::jarray<uint8_t>(0);
    
            uint32_t bearer = myrand->get_uint("0..31");
            uint32_t fresh = myrand->get_u32();
            uint32_t seqnum = myrand->get_u32();
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*akey);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylte = std::make_shared<ProtocolPP::jltesa>();
            mylte->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::TYPE, ProtocolPP::LTE);
            mylte->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylte->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AES_CTR);
            mylte->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH, ProtocolPP::AES_CMAC);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::CKEYLEN, ckey->get_size());
            mylte->set_field<uint32_t>(ProtocolPP::field_t::AKEYLEN, akey->get_size());
            mylte->set_field<bool>(ProtocolPP::field_t::DATACTRL, true);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PDUTYPE, 0);
            mylte->set_field<bool>(ProtocolPP::field_t::POLLBIT, false);
            mylte->set_field<bool>(ProtocolPP::field_t::EXTENSION, false);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::HDREXT, 0);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::LENGTHIND, 0);
            mylte->set_field<int>(ProtocolPP::field_t::SNLEN, ((j==0) ? 7 : ((j==1) ? 12 : 18)));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, ((j==0) ? (seqnum & 0x7F) : ((j==1) ? (seqnum & 0xFFF) : ((j==2) ? (seqnum & 0x7FFF) : (seqnum & 0x3FFFF)))));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HFNI, ((j==0) ? (seqnum & 0x1FFFFFF) : ((j==1) ? (seqnum & 0xFFFFF) : ((j==2) ? (seqnum & 0x1FFFF) : (seqnum & 0x3FFF)))));
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SUFI, blank);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FMS, 0);
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::BITMAP, blank);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PGKINDEX, 1);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::PTKINDENT, 0xAAC1);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::SDUTYPE, ProtocolPP::IP);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::KDID, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::NMP, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HRW, 0);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::BEARER, bearer);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FRESH, fresh);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 4);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylted = std::make_shared<ProtocolPP::jltesa>(mylte);
            mylted->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey2);
    
            // create encap and decap wimax 
            std::shared_ptr<ProtocolPP::jprotocol> elte = ProtocolPP::jprotocolpp::get_lte(myrand, mylte);
            std::shared_ptr<ProtocolPP::jprotocol> dlte = ProtocolPP::jprotocolpp::get_lte(myrand, mylted);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                elte->encap_packet(input, output);
                dlte->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dlte->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "LTEZUC Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testrlcsnow() {
        // LTE setup
        for (unsigned int j=0; j<4; j++) {
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
            ProtocolPP::jarray<uint8_t> blank = ProtocolPP::jarray<uint8_t>(0);
    
            uint32_t bearer = myrand->get_uint("0..31");
            uint32_t fresh = myrand->get_u32();
            uint32_t seqnum = myrand->get_u32();
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*akey);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylte = std::make_shared<ProtocolPP::jltesa>();
            mylte->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::TYPE, ProtocolPP::RLC);
            mylte->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylte->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::SNOWE);
            mylte->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH, ProtocolPP::SNOWA);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::CKEYLEN, ckey->get_size());
            mylte->set_field<uint32_t>(ProtocolPP::field_t::AKEYLEN, akey->get_size());
            mylte->set_field<bool>(ProtocolPP::field_t::DATACTRL, true);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PDUTYPE, 0);
            mylte->set_field<bool>(ProtocolPP::field_t::POLLBIT, false);
            mylte->set_field<bool>(ProtocolPP::field_t::EXTENSION, false);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::HDREXT, 0);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::LENGTHIND, 0);
            mylte->set_field<int>(ProtocolPP::field_t::SNLEN, ((j==0) ? 7 : 12));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, ((j==0) ? (seqnum & 0x7F) : (seqnum & 0xFFF)));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HFNI, ((j==0) ? (seqnum & 0x1FFFFFF) : (seqnum & 0xFFFFF)));
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SUFI, blank);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FMS, 0);
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::BITMAP, blank);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PGKINDEX, 1);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::PTKINDENT, 0xAAC1);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::SDUTYPE, ProtocolPP::IP);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::KDID, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::NMP, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HRW, 0);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::BEARER, bearer);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FRESH, fresh);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 4);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylted = std::make_shared<ProtocolPP::jltesa>(mylte);
            mylted->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey2);
    
            // create encap and decap wimax 
            std::shared_ptr<ProtocolPP::jprotocol> elte = ProtocolPP::jprotocolpp::get_lte(myrand, mylte);
            std::shared_ptr<ProtocolPP::jprotocol> dlte = ProtocolPP::jprotocolpp::get_lte(myrand, mylted);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                elte->encap_packet(input, output);
                dlte->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dlte->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "LTESNOW Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testrlczuc() {
        // LTE setup
        for (unsigned int j=0; j<4; j++) {
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
            ProtocolPP::jarray<uint8_t> blank = ProtocolPP::jarray<uint8_t>(0);
    
            uint32_t bearer = myrand->get_uint("0..31");
            uint32_t fresh = myrand->get_u32();
            uint32_t seqnum = myrand->get_u32();
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*akey);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylte = std::make_shared<ProtocolPP::jltesa>();
            mylte->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::TYPE, ProtocolPP::RLC);
            mylte->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DOWNLINK);
            mylte->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::ZUCE);
            mylte->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH, ProtocolPP::ZUCA);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::CKEYLEN, ckey->get_size());
            mylte->set_field<uint32_t>(ProtocolPP::field_t::AKEYLEN, akey->get_size());
            mylte->set_field<bool>(ProtocolPP::field_t::DATACTRL, true);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PDUTYPE, 0);
            mylte->set_field<bool>(ProtocolPP::field_t::POLLBIT, false);
            mylte->set_field<bool>(ProtocolPP::field_t::EXTENSION, false);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::HDREXT, 0);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::LENGTHIND, 0);
            mylte->set_field<int>(ProtocolPP::field_t::SNLEN, ((j==0) ? 7 : 12));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, ((j==0) ? (seqnum & 0x7F) : (seqnum & 0xFFF)));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HFNI, ((j==0) ? (seqnum & 0x1FFFFFF) : (seqnum & 0xFFFFF)));
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SUFI, blank);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FMS, 0);
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::BITMAP, blank);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PGKINDEX, 1);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::PTKINDENT, 0xAAC1);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::SDUTYPE, ProtocolPP::IP);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::KDID, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::NMP, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HRW, 0);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::BEARER, bearer);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FRESH, fresh);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 4);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylted = std::make_shared<ProtocolPP::jltesa>(mylte);
            mylted->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::DOWNLINK);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey2);
    
            // create encap and decap wimax 
            std::shared_ptr<ProtocolPP::jprotocol> elte = ProtocolPP::jprotocolpp::get_lte(myrand, mylte);
            std::shared_ptr<ProtocolPP::jprotocol> dlte = ProtocolPP::jprotocolpp::get_lte(myrand, mylted);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                elte->encap_packet(input, output);
                dlte->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dlte->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "LTEZUC Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testrlcaes() {
        // LTE setup
        for (unsigned int j=0; j<4; j++) {
            ProtocolPP::jarray<uint8_t> mywin = ProtocolPP::jarray<uint8_t>(28, 0);
            ProtocolPP::jarray<uint8_t> blank = ProtocolPP::jarray<uint8_t>(0);
    
            uint32_t bearer = myrand->get_uint("0..31");
            uint32_t fresh = myrand->get_u32();
            uint32_t seqnum = myrand->get_u32();
            unsigned int keylen = 16;
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(keylen));
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> ckey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*ckey);
            std::shared_ptr<ProtocolPP::jarray<uint8_t>> akey2 = std::make_shared<ProtocolPP::jarray<uint8_t>>(*akey);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylte = std::make_shared<ProtocolPP::jltesa>();
            mylte->set_field<ProtocolPP::protocol_t>(ProtocolPP::field_t::TYPE, ProtocolPP::RLC);
            mylte->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylte->set_field<ProtocolPP::cipher_t>(ProtocolPP::field_t::CIPHER, ProtocolPP::AES_CTR);
            mylte->set_field<ProtocolPP::auth_t>(ProtocolPP::field_t::AUTH, ProtocolPP::AES_CMAC);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey);
            mylte->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::CKEYLEN, ckey->get_size());
            mylte->set_field<uint32_t>(ProtocolPP::field_t::AKEYLEN, akey->get_size());
            mylte->set_field<bool>(ProtocolPP::field_t::DATACTRL, true);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PDUTYPE, 0);
            mylte->set_field<bool>(ProtocolPP::field_t::POLLBIT, false);
            mylte->set_field<bool>(ProtocolPP::field_t::EXTENSION, false);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::HDREXT, 0);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::LENGTHIND, 0);
            mylte->set_field<int>(ProtocolPP::field_t::SNLEN, ((j==0) ? 7 : 12));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::SEQNUM, ((j==0) ? (seqnum & 0x7F) : (seqnum & 0xFFF)));
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HFNI, ((j==0) ? (seqnum & 0x1FFFFFF) : (seqnum & 0xFFFFF)));
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::SUFI, blank);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FMS, 0);
            mylte->set_field<ProtocolPP::jarray<uint8_t>>(ProtocolPP::field_t::BITMAP, blank);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::PGKINDEX, 1);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::PTKINDENT, 0xAAC1);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::SDUTYPE, ProtocolPP::IP);
            mylte->set_field<uint16_t>(ProtocolPP::field_t::KDID, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::NMP, 0);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::HRW, 0);
            mylte->set_field<uint8_t>(ProtocolPP::field_t::BEARER, bearer);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::FRESH, fresh);
            mylte->set_field<uint32_t>(ProtocolPP::field_t::ICVLEN, 4);
    
            // populate the security association
            std::shared_ptr<ProtocolPP::jltesa> mylted = std::make_shared<ProtocolPP::jltesa>(mylte);
            mylted->set_field<ProtocolPP::direction_t>(ProtocolPP::field_t::DIRECTION, ProtocolPP::UPLINK);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::CIPHERKEY, ckey2);
            mylted->set_field<std::shared_ptr<ProtocolPP::jarray<uint8_t>>>(ProtocolPP::field_t::AUTHKEY, akey2);
    
            // create encap and decap wimax 
            std::shared_ptr<ProtocolPP::jprotocol> elte = ProtocolPP::jprotocolpp::get_lte(myrand, mylte);
            std::shared_ptr<ProtocolPP::jprotocol> dlte = ProtocolPP::jprotocolpp::get_lte(myrand, mylted);
    
            for (int i = 0; i<50; i++) {
                unsigned int nmtu = 50; //myrand->get_u16() & 0x0FFF;
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> input  = std::make_shared<ProtocolPP::jarray<uint8_t>>(myrand->getbyte(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> output = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
                std::shared_ptr<ProtocolPP::jarray<uint8_t>> expect = std::make_shared<ProtocolPP::jarray<uint8_t>>(ProtocolPP::jarray<uint8_t>(nmtu));
    
                // encapsulate the IP packet
                elte->encap_packet(input, output);
                dlte->decap_packet(output, expect);
    
                // check the status
                CPPUNIT_ASSERT_EQUAL(mystatus, dlte->get_status());

                // check data
                if (*input != *expect) {
                    std::cerr << "LTEZUC Data MISMATCH" << std::endl;
                    expect->debug(*input);
                }
            }
        }
    }

    void testlogger() {
        // get the ENUM for the color string
        InterfacePP::jlogger::asciicolor colorme = logger->get_color("DEBUGCLR");
        logger->set_color("DEBUGCLR", colorme);

        colorme = logger->get_color("INFOCLR");
        logger->set_color("INFOCLR", colorme);

        colorme = logger->get_color("WARNCLR");
        logger->set_color("WARNCLR", colorme);

        colorme = logger->get_color("ERRCLR");
        logger->set_color("ERRCLR", colorme);

        colorme = logger->get_color("FATALCLR");
        logger->set_color("FATALCLR", colorme);

        colorme = logger->get_color("PASSCLR");
        logger->set_color("PASSCLR", colorme);

        colorme = logger->get_color("FISHCLR");
        logger->set_color("FISHCLR", colorme);

        // get the loglvl and set it
        InterfacePP::jlogger::severity_t logLvl = logger->get_loglvl();
        logger->set_loglvl(logLvl);

        // retrieve the color names
        std::string clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BLACK);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BLACK"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::RED);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("RED"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::GREEN);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("GREEN"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::YELLOW);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("YELLOW"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BLUE);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BLUE"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::MAGENTA);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("MAGENTA"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::CYAN);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("CYAN"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::WHITE);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("WHITE"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BRIGHTBLACK);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BRIGHTBLACK"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BRIGHTRED);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BRIGHTRED"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BRIGHTGREEN);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BRIGHTGREEN"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BRIGHTYELLOW);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BRIGHTYELLOW"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BRIGHTBLUE);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BRIGHTBLUE"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BRIGHTMAGENTA);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BRIGHTMAGENTA"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BRIGHTCYAN);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BRIGHTCYAN"));

        clrStr = InterfacePP::jlogger::toStr(InterfacePP::jlogger::asciicolor::BRIGHTWHITE);
        CPPUNIT_ASSERT_EQUAL(clrStr, std::string("BRIGHTWHITE"));

        // retrieve the color codes
        std::string clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BLACK);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::RED);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::GREEN);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::YELLOW);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BLUE);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::MAGENTA);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::CYAN);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::WHITE);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BRIGHTBLACK);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BRIGHTRED);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BRIGHTGREEN);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BRIGHTYELLOW);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BRIGHTBLUE);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BRIGHTMAGENTA);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BRIGHTCYAN);
        clrCode = InterfacePP::jlogger::toCode(InterfacePP::jlogger::asciicolor::BRIGHTWHITE);

        InterfacePP::jlogger::asciicolor myEnum = InterfacePP::jlogger::toEnum("BLACK");
        myEnum = InterfacePP::jlogger::toEnum("RED");
        myEnum = InterfacePP::jlogger::toEnum("GREEN");
        myEnum = InterfacePP::jlogger::toEnum("YELLOW");
        myEnum = InterfacePP::jlogger::toEnum("BLUE");
        myEnum = InterfacePP::jlogger::toEnum("MAGENTA");
        myEnum = InterfacePP::jlogger::toEnum("CYAN");
        myEnum = InterfacePP::jlogger::toEnum("WHITE");

        myEnum = InterfacePP::jlogger::toEnum("BRIGHTBLACK");
        myEnum = InterfacePP::jlogger::toEnum("BRIGHTRED");
        myEnum = InterfacePP::jlogger::toEnum("BRIGHTGREEN");
        myEnum = InterfacePP::jlogger::toEnum("BRIGHTYELLOW");
        myEnum = InterfacePP::jlogger::toEnum("BRIGHTBLUE");
        myEnum = InterfacePP::jlogger::toEnum("BRIGHTMAGENTA");
        myEnum = InterfacePP::jlogger::toEnum("BRIGHTCYAN");
        myEnum = InterfacePP::jlogger::toEnum("BRIGHTWHITE");

        myEnum = InterfacePP::jlogger::toEnum("BRIGHTFISH");
    }
};

int main(int argc, char **argv) {

    CPPUNIT_TEST_SUITE_REGISTRATION(ppUnitTest);

    CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);
    runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
    runner.run();

    return 0;
}


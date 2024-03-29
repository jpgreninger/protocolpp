///
/// <center>Protocol++ written by : John Peter Greninger &bull; &copy; John Peter Greninger 2015-2023 &bull; All Rights Reserved</center>
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
/// Licensing information can be found at <B>www.protocolpp.com/license</B> with use of the binary forms
/// permitted provided that the following conditions are met:
///
/// * Redistributions in binary form must reproduce the above copyright notice, this list
///   of conditions and the following disclaimer in the documentation and/or other materials
///   provided with the distribution
///
/// * Any and all modifications must be returned to John Peter Greninger at GitHub.com
///   https://github.com/jpgreninger/protocolpp for evaluation. Inclusion of modifications
///   in the source code shall be determined solely by John Peter Greninger. Failure to
///   provide modifications shall render this license NULL and VOID and revoke any rights
///   to use of Protocol++
///
/// * Commercial use (incidental or not) requires a fee-based license obtainable at <B>www.protocolpp.com/shop</B>
///
/// * Academic or research use requires prior written and notarized permission from John Peter
///   and Sheila Rocha Greninger
///
/// Use of the source code requires purchase of the source code. Source code can be purchased
/// at <B>www.protocolpp.com/shop</B>
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
/// The name of its contributor may not be used to endorse or promote products derived
/// from this software without specific prior written permission and licensing
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTOR "AS IS" AND ANY
/// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
/// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
/// SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
/// OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
/// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
/// TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
/// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
///

#include "jlogger.h"

namespace InterfacePP {

void file_log_policy::open_ostream(const std::string& name)
{
	out_stream.open( name.c_str(), std::ios_base::binary|std::ios_base::out );
	if( !out_stream.is_open() ) 
	{
		throw(std::runtime_error("LOGGER: Unable to open an output stream"));
	}
}

void file_log_policy::close_ostream()
{
	if( out_stream )
	{
		out_stream.close();
	}
}

void file_log_policy::write(const std::string& msg)
{
	out_stream<<msg<<std::endl;
}

file_log_policy::~file_log_policy()
{
	if( out_stream )
	{
		close_ostream();
	}
}

void file_stdout_log_policy::open_ostream(const std::string& name)
{
	out_stream.open( name.c_str(), std::ios_base::binary|std::ios_base::out );
	if( !out_stream.is_open() ) 
	{
		throw(std::runtime_error("LOGGER: Unable to open an output stream"));
	}
}

void file_stdout_log_policy::close_ostream()
{
	if( out_stream )
	{
		out_stream.close();
	}
}

void file_stdout_log_policy::write(const std::string& msg)
{
	out_stream<<msg<<std::endl;
    std::cout << msg << std::endl;
}

file_stdout_log_policy::~file_stdout_log_policy()
{
	if( out_stream )
	{
		close_ostream();
	}
}

jlogger::jlogger(const std::string& name,
                 bool logstdout,
                 int loglvl,
                 jlogger::asciicolor debugclr,
                 jlogger::asciicolor infoclr,
                 jlogger::asciicolor warningclr,
                 jlogger::asciicolor errorclr,
                 jlogger::asciicolor fatalclr,
                 jlogger::asciicolor passclr) : m_loglvl(loglvl),
                                                m_debugclr(debugclr),
                                                m_infoclr(infoclr),
                                                m_warnclr(warningclr),
                                                m_errclr(errorclr),
                                                m_fatalclr(fatalclr),
                                                m_passclr(passclr),
                                                m_timer(),
                                                m_logstream(),
                                                m_policy(nullptr),
                                                m_writemutex()
{
    m_first = true;
	m_linenum = 0;

    if (logstdout) {
	    m_policy = new file_stdout_log_policy();
    }
    else {
	    m_policy = new file_log_policy();
    }

    if(m_policy == nullptr) {
		throw std::runtime_error("LOGGER: Unable to create the logger instance"); 
	}
    else {
	    m_policy->open_ostream( name );
    }
}

jlogger::~jlogger()
{
	if(m_policy != nullptr)
	{
#ifdef COLORIZE
        m_policy->write("\033[1;36m");

#endif
		m_policy->close_ostream();
		delete m_policy;
	}
}

std::string jlogger::get_datetime()
{
    if (m_first) {
        m_timer = get_time();
        m_first = false;
    }

	std::string time_str;
	time_t raw_time;
		
	time( &raw_time );
	time_str = ctime( &raw_time );

	//without the newline character
	return time_str.substr( 0 , time_str.size() - 1 );
}

std::chrono::system_clock::time_point jlogger::get_time()
{
    return std::chrono::system_clock::now();
}

std::string jlogger::get_header()
{
	std::stringstream header;

	header.str("");
	header.fill('0');
	header.width(7);
	header << m_linenum++ <<" < "<<get_datetime()<<" - ";

	header.fill('0');
	header.width(7);
	header << std::chrono::nanoseconds(get_time()-m_timer).count()/1000000 <<"ms > ~ ";

	return header.str();
}

void jlogger::print_impl()
{
    std::string line = get_header();
    line += m_logstream.str();

#ifdef COLORIZE
    if (line.find("<INFO>") != std::string::npos) {
        switch(m_infoclr) {
            case jlogger::asciicolor::BLACK:
                line.insert(0, "\033[1;30m ");
                break;
            case jlogger::asciicolor::RED:
                line.insert(0, "\033[1;31m ");
                break;
            case jlogger::asciicolor::GREEN:
                line.insert(0, "\033[1;32m ");
                break;
            case jlogger::asciicolor::YELLOW:
                line.insert(0, "\033[1;33m ");
                break;
            case jlogger::asciicolor::BLUE:
                line.insert(0, "\033[1;34m ");
                break;
            case jlogger::asciicolor::MAGENTA:
                line.insert(0, "\033[1;35m ");
                break;
            case jlogger::asciicolor::CYAN:
                line.insert(0, "\033[1;36m ");
                break;
            case jlogger::asciicolor::WHITE:
                line.insert(0, "\033[1;37m ");
                break;
            case jlogger::asciicolor::BRIGHTBLACK:
                line.insert(0, "\033[1;90m ");
                break;
            case jlogger::asciicolor::BRIGHTRED:
                line.insert(0, "\033[1;91m ");
                break;
            case jlogger::asciicolor::BRIGHTGREEN:
                line.insert(0, "\033[1;92m ");
                break;
            case jlogger::asciicolor::BRIGHTYELLOW:
                line.insert(0, "\033[1;93m ");
                break;
            case jlogger::asciicolor::BRIGHTBLUE:
                line.insert(0, "\033[1;94m ");
                break;
            case jlogger::asciicolor::BRIGHTMAGENTA:
                line.insert(0, "\033[1;95m ");
                break;
            case jlogger::asciicolor::BRIGHTCYAN:
                line.insert(0, "\033[1;96m ");
                break;
            case jlogger::asciicolor::BRIGHTWHITE:
                line.insert(0, "\033[1;97m ");
                break;
            default:
                std::cerr << "In jlogger::print_impl(), unknown INFO color" << std::endl;
        }
    }
    else if (line.find("<DEBUG>") != std::string::npos) {
        switch(m_debugclr) {
            case jlogger::asciicolor::BLACK:
                line.insert(0, "\033[1;30m ");
                break;
            case jlogger::asciicolor::RED:
                line.insert(0, "\033[1;31m ");
                break;
            case jlogger::asciicolor::GREEN:
                line.insert(0, "\033[1;32m ");
                break;
            case jlogger::asciicolor::YELLOW:
                line.insert(0, "\033[1;33m ");
                break;
            case jlogger::asciicolor::BLUE:
                line.insert(0, "\033[1;34m ");
                break;
            case jlogger::asciicolor::MAGENTA:
                line.insert(0, "\033[1;35m ");
                break;
            case jlogger::asciicolor::CYAN:
                line.insert(0, "\033[1;36m ");
                break;
            case jlogger::asciicolor::WHITE:
                line.insert(0, "\033[1;37m ");
                break;
            case jlogger::asciicolor::BRIGHTBLACK:
                line.insert(0, "\033[1;90m ");
                break;
            case jlogger::asciicolor::BRIGHTRED:
                line.insert(0, "\033[1;91m ");
                break;
            case jlogger::asciicolor::BRIGHTGREEN:
                line.insert(0, "\033[1;92m ");
                break;
            case jlogger::asciicolor::BRIGHTYELLOW:
                line.insert(0, "\033[1;93m ");
                break;
            case jlogger::asciicolor::BRIGHTBLUE:
                line.insert(0, "\033[1;94m ");
                break;
            case jlogger::asciicolor::BRIGHTMAGENTA:
                line.insert(0, "\033[1;95m ");
                break;
            case jlogger::asciicolor::BRIGHTCYAN:
                line.insert(0, "\033[1;96m ");
                break;
            case jlogger::asciicolor::BRIGHTWHITE:
                line.insert(0, "\033[1;97m ");
                break;
            default:
                std::cerr << "In jlogger::print_impl(), unknown DEBUG color" << std::endl;
        }
    }
    else if (line.find("<WARN>") != std::string::npos) {
        switch(m_warnclr) {
            case jlogger::asciicolor::BLACK:
                line.insert(0, "\033[1;30m ");
                break;
            case jlogger::asciicolor::RED:
                line.insert(0, "\033[1;31m ");
                break;
            case jlogger::asciicolor::GREEN:
                line.insert(0, "\033[1;32m ");
                break;
            case jlogger::asciicolor::YELLOW:
                line.insert(0, "\033[1;33m ");
                break;
            case jlogger::asciicolor::BLUE:
                line.insert(0, "\033[1;34m ");
                break;
            case jlogger::asciicolor::MAGENTA:
                line.insert(0, "\033[1;35m ");
                break;
            case jlogger::asciicolor::CYAN:
                line.insert(0, "\033[1;36m ");
                break;
            case jlogger::asciicolor::WHITE:
                line.insert(0, "\033[1;37m ");
                break;
            case jlogger::asciicolor::BRIGHTBLACK:
                line.insert(0, "\033[1;90m ");
                break;
            case jlogger::asciicolor::BRIGHTRED:
                line.insert(0, "\033[1;91m ");
                break;
            case jlogger::asciicolor::BRIGHTGREEN:
                line.insert(0, "\033[1;92m ");
                break;
            case jlogger::asciicolor::BRIGHTYELLOW:
                line.insert(0, "\033[1;93m ");
                break;
            case jlogger::asciicolor::BRIGHTBLUE:
                line.insert(0, "\033[1;94m ");
                break;
            case jlogger::asciicolor::BRIGHTMAGENTA:
                line.insert(0, "\033[1;95m ");
                break;
            case jlogger::asciicolor::BRIGHTCYAN:
                line.insert(0, "\033[1;96m ");
                break;
            case jlogger::asciicolor::BRIGHTWHITE:
                line.insert(0, "\033[1;97m ");
                break;
            default:
                std::cerr << "In jlogger::print_impl(), unknown WARN color" << std::endl;
        }
    }
    else if (line.find("<ERROR>") != std::string::npos) {
        switch(m_errclr) {
            case jlogger::asciicolor::BLACK:
                line.insert(0, "\033[1;30m ");
                break;
            case jlogger::asciicolor::RED:
                line.insert(0, "\033[1;31m ");
                break;
            case jlogger::asciicolor::GREEN:
                line.insert(0, "\033[1;32m ");
                break;
            case jlogger::asciicolor::YELLOW:
                line.insert(0, "\033[1;33m ");
                break;
            case jlogger::asciicolor::BLUE:
                line.insert(0, "\033[1;34m ");
                break;
            case jlogger::asciicolor::MAGENTA:
                line.insert(0, "\033[1;35m ");
                break;
            case jlogger::asciicolor::CYAN:
                line.insert(0, "\033[1;36m ");
                break;
            case jlogger::asciicolor::WHITE:
                line.insert(0, "\033[1;37m ");
                break;
            case jlogger::asciicolor::BRIGHTBLACK:
                line.insert(0, "\033[1;90m ");
                break;
            case jlogger::asciicolor::BRIGHTRED:
                line.insert(0, "\033[1;91m ");
                break;
            case jlogger::asciicolor::BRIGHTGREEN:
                line.insert(0, "\033[1;92m ");
                break;
            case jlogger::asciicolor::BRIGHTYELLOW:
                line.insert(0, "\033[1;93m ");
                break;
            case jlogger::asciicolor::BRIGHTBLUE:
                line.insert(0, "\033[1;94m ");
                break;
            case jlogger::asciicolor::BRIGHTMAGENTA:
                line.insert(0, "\033[1;95m ");
                break;
            case jlogger::asciicolor::BRIGHTCYAN:
                line.insert(0, "\033[1;96m ");
                break;
            case jlogger::asciicolor::BRIGHTWHITE:
                line.insert(0, "\033[1;97m ");
                break;
            default:
                std::cerr << "In jlogger::print_impl(), unknown ERROR color" << std::endl;
        }
    }
    else if (line.find("<FATAL>") != std::string::npos) {
        switch(m_fatalclr) {
            case jlogger::asciicolor::BLACK:
                line.insert(0, "\033[1;30m ");
                break;
            case jlogger::asciicolor::RED:
                line.insert(0, "\033[1;31m ");
                break;
            case jlogger::asciicolor::GREEN:
                line.insert(0, "\033[1;32m ");
                break;
            case jlogger::asciicolor::YELLOW:
                line.insert(0, "\033[1;33m ");
                break;
            case jlogger::asciicolor::BLUE:
                line.insert(0, "\033[1;34m ");
                break;
            case jlogger::asciicolor::MAGENTA:
                line.insert(0, "\033[1;35m ");
                break;
            case jlogger::asciicolor::CYAN:
                line.insert(0, "\033[1;36m ");
                break;
            case jlogger::asciicolor::WHITE:
                line.insert(0, "\033[1;37m ");
                break;
            case jlogger::asciicolor::BRIGHTBLACK:
                line.insert(0, "\033[1;90m ");
                break;
            case jlogger::asciicolor::BRIGHTRED:
                line.insert(0, "\033[1;91m ");
                break;
            case jlogger::asciicolor::BRIGHTGREEN:
                line.insert(0, "\033[1;92m ");
                break;
            case jlogger::asciicolor::BRIGHTYELLOW:
                line.insert(0, "\033[1;93m ");
                break;
            case jlogger::asciicolor::BRIGHTBLUE:
                line.insert(0, "\033[1;94m ");
                break;
            case jlogger::asciicolor::BRIGHTMAGENTA:
                line.insert(0, "\033[1;95m ");
                break;
            case jlogger::asciicolor::BRIGHTCYAN:
                line.insert(0, "\033[1;96m ");
                break;
            case jlogger::asciicolor::BRIGHTWHITE:
                line.insert(0, "\033[1;97m ");
                break;
            default:
                std::cerr << "In jlogger::print_impl(), unknown FATAL color" << std::endl;
        }
    }
    else if (line.find("<PASS>") != std::string::npos) {
        switch(m_passclr) {
            case jlogger::asciicolor::BLACK:
                line.insert(0, "\033[1;30m ");
                break;
            case jlogger::asciicolor::RED:
                line.insert(0, "\033[1;31m ");
                break;
            case jlogger::asciicolor::GREEN:
                line.insert(0, "\033[1;32m ");
                break;
            case jlogger::asciicolor::YELLOW:
                line.insert(0, "\033[1;33m ");
                break;
            case jlogger::asciicolor::BLUE:
                line.insert(0, "\033[1;34m ");
                break;
            case jlogger::asciicolor::MAGENTA:
                line.insert(0, "\033[1;35m ");
                break;
            case jlogger::asciicolor::CYAN:
                line.insert(0, "\033[1;36m ");
                break;
            case jlogger::asciicolor::WHITE:
                line.insert(0, "\033[1;37m ");
                break;
            case jlogger::asciicolor::BRIGHTBLACK:
                line.insert(0, "\033[1;90m ");
                break;
            case jlogger::asciicolor::BRIGHTRED:
                line.insert(0, "\033[1;91m ");
                break;
            case jlogger::asciicolor::BRIGHTGREEN:
                line.insert(0, "\033[1;92m ");
                break;
            case jlogger::asciicolor::BRIGHTYELLOW:
                line.insert(0, "\033[1;93m ");
                break;
            case jlogger::asciicolor::BRIGHTBLUE:
                line.insert(0, "\033[1;94m ");
                break;
            case jlogger::asciicolor::BRIGHTMAGENTA:
                line.insert(0, "\033[1;95m ");
                break;
            case jlogger::asciicolor::BRIGHTCYAN:
                line.insert(0, "\033[1;96m ");
                break;
            case jlogger::asciicolor::BRIGHTWHITE:
                line.insert(0, "\033[1;97m ");
                break;
            default:
                std::cerr << "In jlogger::print_impl(), unknown PASS color" << std::endl;
        }
    }
    else {
        line.insert(0, "\033[1;36m ");
    }
#endif

    // only log what the level allows LVL3 allows DEBUG, INFO, WARN, ERROR, FATAL, and PASS
    if (m_loglvl > 3) {
        m_policy->write( line );
        m_logstream.str("");
    }
    else if ((m_loglvl == 3) && ((line.find("<INFO>") != std::string::npos) ||
                                 (line.find("<WARN>") != std::string::npos) ||
                                 (line.find("<ERROR>") != std::string::npos) ||
                                 (line.find("<FATAL>") != std::string::npos) ||
                                 (line.find("<PASS>") != std::string::npos))) {
        m_policy->write( line );
        m_logstream.str("");
    }
    else if ((m_loglvl == 2) && ((line.find("<WARN>") != std::string::npos) ||
                                 (line.find("<ERROR>") != std::string::npos) ||
                                 (line.find("<FATAL>") != std::string::npos) ||
                                 (line.find("<PASS>") != std::string::npos))) {
        m_policy->write( line );
        m_logstream.str("");
    }
    else if ((m_loglvl == 1) && ((line.find("<ERROR>") != std::string::npos) ||
                                 (line.find("<FATAL>") != std::string::npos) ||
                                 (line.find("<PASS>") != std::string::npos))) {
        m_policy->write( line );
        m_logstream.str("");
    }
    else {
        m_logstream.str("");
    }
}

// set the logging level
void jlogger::set_loglvl(int newlvl) {
    m_loglvl = newlvl;
}

// @param Args...args - variable number of arguments to print
void jlogger::set_color(std::string color, jlogger::asciicolor jcolor) {
    if (color == "DEBUGCLR") {
        m_debugclr = jcolor;
    }
    else if (color == "INFOCLR") {
        m_infoclr = jcolor;
    }
    else if (color == "WARNCLR") {
        m_warnclr = jcolor;
    }
    else if (color == "ERRCLR") {
        m_errclr = jcolor;
    }
    else if (color == "FATALCLR") {
        m_fatalclr = jcolor;
    }
    else if (color == "PASSCLR") {
        m_passclr = jcolor;
    }
    else {
        std::cerr << "In jlogger::set_color(), unknown field requested: " << color << std::endl;
    }
}

// set the logging level
int jlogger::get_loglvl() {
    return m_loglvl;
}

// @param Args...args - variable number of arguments to print
jlogger::asciicolor jlogger::get_color(std::string color) {
    if (color == "DEBUGCLR") {
        return m_debugclr;
    }
    else if (color == "INFOCLR") {
        return m_infoclr;
    }
    else if (color == "WARNCLR") {
        return m_warnclr;
    }
    else if (color == "ERRCLR") {
        return m_errclr;
    }
    else if (color == "FATALCLR") {
        return m_fatalclr;
    }
    else if (color == "PASSCLR") {
        return m_passclr;
    }
    else {
        std::cerr << "In jlogger::get_color(), unknown field requested: " << color << std::endl;
        return jlogger::asciicolor::WHITE;
    }
}

// convert from jlogger::asciicolor enum to std::string
std::string jlogger::toStr(jlogger::asciicolor jcolor) {
    std::string result;
    switch (jcolor) {
        case jlogger::asciicolor::BLACK: result = std::string("BLACK"); break;
        case jlogger::asciicolor::RED: result = std::string("RED"); break;
        case jlogger::asciicolor::GREEN: result = std::string("GREEN"); break;
        case jlogger::asciicolor::YELLOW: result = std::string("YELLOW"); break;
        case jlogger::asciicolor::BLUE: result = std::string("BLUE"); break;
        case jlogger::asciicolor::MAGENTA: result = std::string("MAGENTA"); break;
        case jlogger::asciicolor::CYAN: result = std::string("CYAN"); break;
        case jlogger::asciicolor::WHITE: result = std::string("WHITE"); break;
        case jlogger::asciicolor::BRIGHTBLACK: result = std::string("BRIGHTBLACK"); break;
        case jlogger::asciicolor::BRIGHTRED: result = std::string("BRIGHTRED"); break;
        case jlogger::asciicolor::BRIGHTGREEN: result = std::string("BRIGHTGREEN"); break;
        case jlogger::asciicolor::BRIGHTYELLOW: result = std::string("BRIGHTYELLOW"); break;
        case jlogger::asciicolor::BRIGHTBLUE: result = std::string("BRIGHTBLUE"); break;
        case jlogger::asciicolor::BRIGHTMAGENTA: result = std::string("BRIGHTMAGENTA"); break;
        case jlogger::asciicolor::BRIGHTCYAN: result = std::string("BRIGHTCYAN"); break;
        case jlogger::asciicolor::BRIGHTWHITE: result = std::string("BRIGHTWHITE"); break;
        default : {
            std::cerr << "In jlogger::toStr(), unknown color requested" << std::endl;
            result = std::string("BLACK");
        }
    }

    return result;
}

// convert from jlogger::asciicolor enum to std::string
std::string jlogger::toCode(jlogger::asciicolor jcolor) {
    std::string result;
    switch (jcolor) {
        case jlogger::asciicolor::BLACK: result = std::string("\033[1;30m"); break;
        case jlogger::asciicolor::RED: result = std::string("\033[1;31m"); break;
        case jlogger::asciicolor::GREEN: result = std::string("\033[1;32m"); break;
        case jlogger::asciicolor::YELLOW: result = std::string("\033[1;33m"); break;
        case jlogger::asciicolor::BLUE: result = std::string("\033[1;34m"); break;
        case jlogger::asciicolor::MAGENTA: result = std::string("\033[1;35m"); break;
        case jlogger::asciicolor::CYAN: result = std::string("\033[1;36m"); break;
        case jlogger::asciicolor::WHITE: result = std::string("\033[1;37m"); break;
        case jlogger::asciicolor::BRIGHTBLACK: result = std::string("\033[1;90m"); break;
        case jlogger::asciicolor::BRIGHTRED: result = std::string("\033[1;91m"); break;
        case jlogger::asciicolor::BRIGHTGREEN: result = std::string("\033[1;92m"); break;
        case jlogger::asciicolor::BRIGHTYELLOW: result = std::string("\033[1;93m"); break;
        case jlogger::asciicolor::BRIGHTBLUE: result = std::string("\033[1;94m"); break;
        case jlogger::asciicolor::BRIGHTMAGENTA: result = std::string("\033[1;95m"); break;
        case jlogger::asciicolor::BRIGHTCYAN: result = std::string("\033[1;96m"); break;
        case jlogger::asciicolor::BRIGHTWHITE: result = std::string("\033[1;97m"); break;
        default : {
            std::cerr << "In jlogger::toCode(), unknown color requested" << std::endl;
            result = std::string("\033[1;30m"); break;
        }
    }

    return result;
}

// convert string to jlogger::asciicolor enum
jlogger::asciicolor jlogger::toEnum(std::string jcolor) {
    if (jcolor == "BLACK") {
        return jlogger::asciicolor::BLACK;
    }
    else if (jcolor == "RED") {
        return jlogger::asciicolor::RED;
    }
    else if (jcolor == "GREEN") {
        return jlogger::asciicolor::GREEN;
    }
    else if (jcolor == "YELLOW") {
        return jlogger::asciicolor::YELLOW;
    }
    else if (jcolor == "BLUE") {
        return jlogger::asciicolor::BLUE;
    }
    else if (jcolor == "MAGENTA") {
        return jlogger::asciicolor::MAGENTA;
    }
    else if (jcolor == "CYAN") {
        return jlogger::asciicolor::CYAN;
    }
    else if (jcolor == "WHITE") {
        return jlogger::asciicolor::WHITE;
    }
    else if (jcolor == "BRIGHTBLACK") {
        return jlogger::asciicolor::BRIGHTBLACK;
    }
    else if (jcolor == "BRIGHTRED") {
        return jlogger::asciicolor::BRIGHTRED;
    }
    else if (jcolor == "BRIGHTGREEN") {
        return jlogger::asciicolor::BRIGHTGREEN;
    }
    else if (jcolor == "BRIGHTYELLOW") {
        return jlogger::asciicolor::BRIGHTYELLOW;
    }
    else if (jcolor == "BRIGHTBLUE") {
        return jlogger::asciicolor::BRIGHTBLUE;
    }
    else if (jcolor == "BRIGHTMAGENTA") {
        return jlogger::asciicolor::BRIGHTMAGENTA;
    }
    else if (jcolor == "BRIGHTCYAN") {
        return jlogger::asciicolor::BRIGHTCYAN;
    }
    else if (jcolor == "BRIGHTWHITE") {
        return jlogger::asciicolor::BRIGHTWHITE;
    }
    else {
        std::cerr << "In jlogger::toEnum(), unknown color requested: " << jcolor << std::endl;
        return jlogger::asciicolor::BLACK;
    }
}

}

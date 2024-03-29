#ifndef JLOGGER_H_
#define JLOGGER_H_

///
///\class log_policy_interface log_policy_interface "include/jlogger.h"
///
///\section JLOGGERC Central logger class for Protocol++&reg; (ProtocolPP&reg;)
///
/// Supports logging levels for INFO, DEBUG, WARN, ERROR, and FATAL. The constructor allows colors to
/// be defined at construction. Colors can also be updated at any time using the accessor functions
/// The constructor requires the log file name and path, output can be sent to std::cout if requested
/// (disabled by default), and the loglvl by default includes everything but DEBUG. The default color
/// scheme is what I call the "phantom" color sceeen as it looks like charcoal grey on a black background
/// See the constructor below:
///
///\code
///
/// jlogger(const std::string& name,
///         bool logstdout=false,
///         int loglvl=3,
///         jlogger::asciicolor debugclr=jlogger::asciicolor::MAGENTA,
///         jlogger::asciicolor infoclr=jlogger::asciicolor::BLACK,
///         jlogger::asciicolor warningclr=jlogger::asciicolor::YELLOW,
///         jlogger::asciicolor errorclr=jlogger::asciicolor::RED,
///         jlogger::asciicolor fatalclr=jlogger::asciicolor::RED,
///         jlogger::asciicolor passclr=jlogger::asciicolor::GREEN);
///\endcode
///
/// Additional methods are as follows
///\code
///
/// // set a new color for a type (DEBUGCLR, INFOCLR, WARNCLR, ERRCLR, FATALCLR, PASSCLR)
/// void set_color(std::string color, jlogger::asciicolor jcolor);
///
/// // return the corrent color for the give logging type
/// jlogger::asciicolor get_color(std::string color);
///
/// // Convert jlogger::asciicolor Enum to a string representation
/// std::string colorString = jlogger::toStr(jlogger::asciicolor jcolor);
///
/// // Convert string to jlogger::asciicolor Enum
/// jlogger::asciicolor colorEnum = jlogger::toEnum(std::string color);
///\endcode
///
/// Severity codes are typical for logging and are as follows
///\code
///
/// enum severity_type {/// information level of logging
///     info=1,         /// debug level of logging
///     debug,          /// warning level of logging
///     warning,        /// error level of logging
///     error,          /// fatal level of logging
///     fatal,          /// PASS banner
///     pass
/// };
///\endcode
/// Possible color codes are the ASCII escape codes as follows
///\code
///
/// enum asciicolor {    /// Standard black
///     BLACK=30,        /// Standard red
///     RED=31,          /// Standard green
///     GREEN=32,        /// Standard yellow
///     YELLOW=33,       /// Standard blue
///     BLUE=34,         /// Standard magenta
///     MAGENTA=35,      /// Standard cyan
///     CYAN=36,         /// Standard white
///     WHITE=37,        /// Bold black
///     BRIGHTBLACK=90,  /// Bold red
///     BRIGHTRED=91,    /// Bold green
///     BRIGHTGREEN=92,  /// Bold yellow
///     BRIGHTYELLOW=93, /// Bold blue
///     BRIGHTBLUE=94,   /// Bold magenta
///     BRIGHTMAGENTA=95,/// Bold cyan
///     BRIGHTCYAN=96,   /// Bold white
///     BRIGHTWHITE=97
/// };
///\endcode
///
/// Color schemes that work well on a dark backgroud (DARK_THEME, PHANTOM_THEME) and light background
/// (LIGHT_THEME), are shown below for the user
///
/// DARK_THEME
///
/// * INFO - Light blue (cyan)
/// * DEBUG - Dark blue
/// * WARN - Yellow
/// * ERROR - Red
/// * FATAL - Magenta
///
/// LIGHT_THEME
///
/// * INFO - Black
/// * DEBUG - Dark blue
/// * WARN - Blue 
/// * ERROR - Red
/// * FATAL - Magenta
///
/// PHANTOM_THEME
///
/// * INFO - Black
/// * DEBUG - Magenta
/// * WARN - Yellow
/// * ERROR - Red
/// * FATAL - Red
///
///\image html darkThemePass.png
///\image latex darkThemePass.eps
///
///\image html darkThemeWarn.png
///\image latex darkThemeWarn.eps
///
///\image html darkThemeError.png
///\image latex darkThemeError.eps
///
///\image html darkThemeFail.png
///\image latex darkThemeFail.eps
///
/// <center>Protocol++&reg; (ProtocolPP&reg;) modified by : John Peter Greninger &bull; &copy; John Peter Greninger 2015-2023 &bull; All Rights Reserved</center>
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
///   to use of Protocol++&reg;
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

#include <mutex>
#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>
#include <fstream>
#include <sstream>

#define COLORIZE
#undef DARK_THEME
#undef LIGHT_THEME
#undef PHANTOM_THEME

namespace InterfacePP {

///
///\class log_policy_interface log_policy_interface "include/jlogger.h"
///

class log_policy_interface
{
public:
    /////////////////////////////////////////////////////
    /// standard deconstructor
    /////////////////////////////////////////////////////
    log_policy_interface() : out_stream() {}

    /////////////////////////////////////////////////////
    /// standard deconstructor
    /////////////////////////////////////////////////////
    virtual ~log_policy_interface() = default;

    /////////////////////////////////////////////////////
    /// open_ostream - pure virtual function to override in your testbench
    /////////////////////////////////////////////////////
    virtual void open_ostream(const std::string& name) = 0;

    /////////////////////////////////////////////////////
    /// close_ostream - pure virtual function to override in your testbench
    /////////////////////////////////////////////////////
    virtual void close_ostream() = 0;

    /////////////////////////////////////////////////////
    /// write - pure virtual function to override in your testbench
    /////////////////////////////////////////////////////
    virtual void write(const std::string& msg) = 0;

protected:

    /////////////////////////////////////////////////////
    /// Output file stream object
    /////////////////////////////////////////////////////
    std::ofstream out_stream;
};

///
///\class file_log_policy file_log_policy "include/jlogger.h"
///

class file_log_policy : public log_policy_interface
{

public:

    /////////////////////////////////////////////////////
    /// file_log_policy constructor
    /////////////////////////////////////////////////////
    file_log_policy() : log_policy_interface() {}

    /////////////////////////////////////////////////////
    /// open_ostream
    /// @param name - name of the log output file
    /////////////////////////////////////////////////////
    void open_ostream(const std::string& name);

    /////////////////////////////////////////////////////
    /// close_ostream - close the log file
    /////////////////////////////////////////////////////
    void close_ostream();

    /////////////////////////////////////////////////////
    /// write - write msg to log file
    /// @param msg - message to write to log file
    /////////////////////////////////////////////////////
    void write(const std::string& msg);

    /////////////////////////////////////////////////////
    /// standard deconstructor
    /////////////////////////////////////////////////////
    ~file_log_policy();
};

///
///\class file_stdout_log_policy file_log_policy "include/jlogger.h"
///

class file_stdout_log_policy : public log_policy_interface
{

public:

    /////////////////////////////////////////////////////
    /// file_log_policy constructor
    /////////////////////////////////////////////////////
    file_stdout_log_policy() : log_policy_interface() {}

    /////////////////////////////////////////////////////
    /// open_ostream
    /// @param name - name of the log output file
    /////////////////////////////////////////////////////
    void open_ostream(const std::string& name);

    /////////////////////////////////////////////////////
    /// close_ostream - close the log file
    /////////////////////////////////////////////////////
    void close_ostream();

    /////////////////////////////////////////////////////
    /// write - write msg to log file
    /// @param msg - message to write to log file
    /////////////////////////////////////////////////////
    void write(const std::string& msg);

    /////////////////////////////////////////////////////
    /// standard deconstructor
    /////////////////////////////////////////////////////
    ~file_stdout_log_policy();
};

///
///\class jlogger jlogger.h "include/jlogger.h"
///
/// #ifdef DARK_THEME
///         line.insert(0, "\033[1;34m ");
/// #else
///         line.insert(0, "\033[1;30m ");
/// #endif
///     }
///     else if (line.find("<DEBUG>") != std::string::npos) {
/// #ifdef DARK_THEME
///         line.insert(0, "\033[1;35m ");
/// #else
///         line.insert(0, "\033[1;34m ");
/// #endif
///     }
///     else if (line.find("<WARN>") != std::string::npos) {
/// #ifdef LIGHT_THEME
///         line.insert(0, "\033[0;34m ");
/// #else
///         line.insert(0, "\033[1;33m ");
/// #endif
///     }
///     else if (line.find("<ERROR>") != std::string::npos) {
/// #ifdef LIGHT_THEME
///         line.insert(0, "\033[1;31m ");
/// #else
///         line.insert(0, "\033[1;31m ");
/// #endif
///     }
///     else if (line.find("<FATAL>") != std::string::npos) {
/// #ifdef DARK_THEME
///         line.insert(0, "\033[1;35m ");
/// #else
///         line.insert(0, "\033[1;35m ");
/// #endif
///     }
///     else if (line.find("<PASS>") != std::string::npos) {
/// #ifdef DARK_THEME
///         line.insert(0, "\033[1;32m ");
/// #else
///         line.insert(0, "\033[1;32m ");
/// #endif
///     }
///     else {
/// #ifdef DARK_THEME
///         line.insert(0, "\033[1;34m ");
/// #else
///         line.insert(0, "\033[1;34m ");
/// #endif
///


class jlogger {
    
public:

    //////////////////////////////////////////////////////////////////////
    /// Color enums
    /// @param BLACK - Standard black
    /// @param RED - Standard red
    /// @param GREEN - Standard green
    /// @param YELLOW - Standard yellow
    /// @param BLUE - Standard blue
    /// @param MAGENTA - Standard magenta
    /// @param CYAN - Standard cyan 
    /// @param WHITE - Standard white
    /// @param BRIGHTBLACK - Bold black
    /// @param BRIGHTRED - Bold red 
    /// @param BRIGHTGREEN - Bold green
    /// @param BRIGHTYELLOW - Bold yellow
    /// @param BRIGHTBLUE - Bold blue
    /// @param BRIGHTMAGENTA - Bold magenta
    /// @param BRIGHTCYAN - Bold cyan
    /// @param BRIGHTWHITE - Bold white 
    //////////////////////////////////////////////////////////////////////
    enum asciicolor {    /// Standard black
        BLACK=30,        /// Standard red
        RED=31,          /// Standard green
        GREEN=32,        /// Standard yellow
        YELLOW=33,       /// Standard blue
        BLUE=34,         /// Standard magenta
        MAGENTA=35,      /// Standard cyan
        CYAN=36,         /// Standard white
        WHITE=37,        /// Bold black
        BRIGHTBLACK=90,  /// Bold red
        BRIGHTRED=91,    /// Bold green
        BRIGHTGREEN=92,  /// Bold yellow
        BRIGHTYELLOW=93, /// Bold blue
        BRIGHTBLUE=94,   /// Bold magenta
        BRIGHTMAGENTA=95,/// Bold cyan
        BRIGHTCYAN=96,   /// Bold white
        BRIGHTWHITE=97
    };

    /////////////////////////////////////////////////////
    /// severity type
    /// @param info - information level of logging
    /// @param debug - debug level of logging
    /// @param warning - warning level of logging
    /// @param error - error level of logging
    /// @param fatal - fatal level of logging
    /// @param pass - PASS banner level of logging
    /////////////////////////////////////////////////////
    enum severity_type {/// information level of logging
        info=1,         /// debug level of logging
        debug,          /// warning level of logging
        warning,        /// error level of logging
        error,          /// fatal level of logging
        fatal,          /// PASS banner
        pass
    };

    /////////////////////////////////////////////////////
    /// logger class
    /// @param name - name of the output log file 
    /// @param logstdout - print logging to stdout as well as file
    /// @param loglvl - Level of logging (4-<DEBUG, INFO, WARN, ERROR, FATAL, PASS>, 3[default]-<INFO, WARN, ERROR, FATAL, PASS>, 2-<WARN, ERROR, FATAL, PASS>, 1-<ERROR, FATAL, PASS>, 0-NO LOGGING)
    /// @param debugclr - Color for the DEBUG messages (default: MAGENTA)
    /// @param infoclr - Color for the INFO messages (default: BLACK)
    /// @param warningclr - Color for the WARN messages (default: YELLOW)
    /// @param errorclr - Color for the ERROR messages (default:RED)
    /// @param fatalclr - Color for the FATAL messages (default:RED)
    /// @param passclr - Color for the PASS messages (default:GREEN)
    /////////////////////////////////////////////////////
    explicit jlogger(const std::string& name,
                     bool logstdout=false,
                     int loglvl=3,
                     jlogger::asciicolor debugclr=jlogger::asciicolor::MAGENTA,
                     jlogger::asciicolor infoclr=jlogger::asciicolor::CYAN,
                     jlogger::asciicolor warningclr=jlogger::asciicolor::YELLOW,
                     jlogger::asciicolor errorclr=jlogger::asciicolor::RED,
                     jlogger::asciicolor fatalclr=jlogger::asciicolor::RED,
                     jlogger::asciicolor passclr=jlogger::asciicolor::GREEN);

    /////////////////////////////////////////////////////
    /// print function for logger
    /// @param Args...args - variable number of arguments to print
    /////////////////////////////////////////////////////
    template< typename jlogger::severity_type, typename...Args >
    void print(Args...args );

    /////////////////////////////////////////////////////
    /// standard deconstructor
    /////////////////////////////////////////////////////
    ~jlogger();

    /////////////////////////////////////////////////////
    /// set the loggging level
    /// @param newlvl - new logging level
    /////////////////////////////////////////////////////
    void set_loglvl(int newlvl);

    /////////////////////////////////////////////////////
    /// Change colors for the logging output
    /// @param color - Color to set values are DEBUGCLR,
    ///                INFOCLR, WARNCLR, ERRCLR, FATALCLR,
    ///                PASSCLR
    /// @param jcolor - Enum value of new color
    /////////////////////////////////////////////////////
    void set_color(std::string color, jlogger::asciicolor jcolor);

    /////////////////////////////////////////////////////
    /// get the loggging level
    /// @return Returns the logging level
    /////////////////////////////////////////////////////
    int get_loglvl();

    /////////////////////////////////////////////////////
    /// Obtain current color for logging field
    /// @param color - Color to set values are DEBUGCLR,
    ///                INFOCLR, WARNCLR, ERRCLR, FATALCLR,
    ///                PASSCLR
    /// @return Returns the jlogger::asciicolor Enum value of the color
    /////////////////////////////////////////////////////
    jlogger::asciicolor get_color(std::string color);

    /////////////////////////////////////////////////////
    /// Convert jlogger::asciicolor Enum to a string representation
    /// @param jcolor - Enum to convert
    /// @return Returns the string name of the color
    /////////////////////////////////////////////////////
    static std::string toStr(jlogger::asciicolor jcolor);

    /////////////////////////////////////////////////////
    /// Convert jlogger::asciicolor Enum to a ASCII color code string
    /// @param jcolor - Enum to convert
    /// @return ASCII color code string
    /////////////////////////////////////////////////////
    static std::string toCode(jlogger::asciicolor jcolor);

    /////////////////////////////////////////////////////
    /// Convert string to jlogger::asciicolor Enum
    /// @param color - Color to convert
    /// @return Returns the jlogger::asciicolor Enum value of the color
    /////////////////////////////////////////////////////
    static jlogger::asciicolor toEnum(std::string color);

private:

    // variables
    bool m_first;
    int m_loglvl;
    jlogger::asciicolor m_debugclr;
    jlogger::asciicolor m_infoclr;
    jlogger::asciicolor m_warnclr;
    jlogger::asciicolor m_errclr;
    jlogger::asciicolor m_fatalclr;
    jlogger::asciicolor m_passclr;
    std::chrono::system_clock::time_point m_timer;
    unsigned m_linenum;
    std::stringstream m_logstream;
    log_policy_interface* m_policy;
    std::mutex m_writemutex;

    // time functions
    std::string get_datetime();
    std::chrono::system_clock::time_point get_time();
    std::string get_header();

    //Core printing functionality
    void print_impl();

    // viradic function
    template<typename First, typename...Rest>
    void print_impl(First parm1, Rest...parm);
};

template< jlogger::severity_type severity , typename...Args >
void jlogger::print(Args...args )
{
    m_writemutex.lock();
    switch( severity )
    {
        case severity_type::info:
            m_logstream<<"<INFO>  :";
            break;
        case severity_type::debug:
            m_logstream<<"<DEBUG> :";
            break;
        case severity_type::warning:
            m_logstream<<"<WARN>  :";
            break;
        case severity_type::error:
            m_logstream<<"<ERROR> :";
            break;
        case severity_type::fatal:
            m_logstream<<"<FATAL> :";
            break;
        case severity_type::pass:
            m_logstream<<"<PASS>  :";
            break;
        default:
            m_logstream<<"<INFO>  :";
            break;
    }
    print_impl( args... );
    m_writemutex.unlock();
}

template<typename First, typename...Rest>
void jlogger::print_impl(First parm1, Rest...parm)
{
    m_logstream<<parm1;
    print_impl(parm...);    
}

}

#endif // JLOGGER_H_

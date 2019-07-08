#ifndef __COMMANDLINEARGUMENT_H_
#define __COMMANDLINEARGUMENT_H_

#include <string>

/** √¸¡Ó––Ω‚Œˆ
*/
class CommandLineArguments 
{
public:
    CommandLineArguments();
    CommandLineArguments(const wchar_t* lpCmdLine);
    ~CommandLineArguments();

    int argc() { return argc_; }
    char **argv() { return argv_; }

private:    
    std::string _W2A(const wchar_t* src);

    int  argc_;
    char **argv_;
};

#endif

#ifndef ENGINELOGGER_H
#define ENGINELOGGER_H

#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

class ELogger
{
private:
public:
    static std::shared_ptr<spdlog::logger> log_inst;
    static void InitLog()
    {
        try
        {
            ELogger::log_inst = spdlog::basic_logger_mt( "Main", getExePath() + "/_log_" );
            SPDLOG_LOGGER_INFO( ELogger::log_inst, "----------- Life 2 --------------" );
        }
        catch( const spdlog::spdlog_ex& ex )
        {
            std::cout << "ERROR! Log initialization failed: " << ex.what() << std::endl;
        }
    }
private:
    static std::string getExePath()
    {
        char pBuf[PATH_MAX];
        int bytes = readlink( "/proc/self/exe", pBuf, PATH_MAX );
        if( bytes >= 0 )
        {
            pBuf[bytes] = '\0';
        }
        else
        {
            std::cout << "EPIC FAIL!!!  Cannot get current directory!" << std::endl;
        }
        std::filesystem::path p{std::string( pBuf,  bytes > 0  ? bytes : 0 )};
        return  p.parent_path();
    }

};

#endif

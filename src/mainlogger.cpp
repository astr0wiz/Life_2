#include "mainlogger.h"

MainLogger::MainLogger()
{
    log_inst = spdlog::basic_logger_mt( "Main", this->getExePath() + "/_log_" );
}

MainLogger::~MainLogger()
{
    //dtor
}

MainLogger& MainLogger::Instance()
{
    static MainLogger theInstance;
    return theInstance;
}

void MainLogger::Log(std::string message)
{
    SPDLOG_LOGGER_INFO( log_inst, message );
}

std::string MainLogger::getExePath()
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


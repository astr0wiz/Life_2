#ifndef MAINLOGGER_H
#define MAINLOGGER_H

#include "limits.h"
#include <unistd.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <memory>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

class MainLogger
{
public:
    static MainLogger& Instance();
    MainLogger( MainLogger const& ) = delete;
    void operator=( MainLogger const& ) = delete;
    void Log(std::string message);

protected:
    ~MainLogger();

private:
    MainLogger();
    std::shared_ptr<spdlog::logger> log_inst{nullptr};
    std::string getExePath();
};

#endif // MAINLOGGER_H

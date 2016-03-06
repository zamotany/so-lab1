#pragma once

#include <string>
#include <fstream>
#include <queue>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <filesystem>
#include <thread>
#include <mutex>
#include <condition_variable>

// \brief Asynchronous debug printing and loggig tool.
// \author Paweł Trysła aka zamotany.
class Logger
{
public:
	// \brief Default constructor.
	// \param path Path to output folder.
	// \param depth Active depth. Only messgages with lower depth will be printed.
	// \note Name of file containging debug output will be set to default: DebugOut.%t.txt.
	Logger(const std::string& path, unsigned int depth = 0);

	// \brief Default constructor.
	// \param path Path to output folder.
	// \param depth Active depth. Only messgages with lower depth will be printed.
	// \param filename Name of file to which output will be written.
	Logger(const std::string& path, const std::string& filename, unsigned int depth = 0);

	// \brief Default destructor.
	~Logger();

	// \brief Operator =.
	Logger& operator=(const Logger&) = delete;

	// \brief Copy constructor.
	Logger(const Logger&) = delete;
	
	// \brief Set current depth.
	// \param depth Current depth.
	// \note If message has grater depth and current/active depth it will not be printed.
	void setDepth(unsigned int depth);

	// \brief Write message into debug file.
	// \param message Message to be written.
	// \param depth Depth of this message.
	//        If active depth is grater or equal, message will be printed.
	// \note Availe macros:
	//       %y - year,
	//       %m - month,
	//       %d - day,
	//       %h - hour,
	//       %i - minutes,
	//       %s - seconds,
	//       %a - abnormal termination (ABORT),
	//       %t - shortcut for %y-%m-%d %h-%i-%s.
	// \return Itself.
	Logger& out(const std::string& message, unsigned int depth = 0);

	// \brief Abort program and write message to file.
	// \param message Message to write.
	// \note Availe macros:
	//       %y - year,
	//       %m - month,
	//       %d - day,
	//       %h - hour,
	//       %i - minutes,
	//       %s - seconds,
	//       %a - abnormal termination (ABORT),
	//       %t - shortcut for %y-%m-%d %h-%i-%s.
	void abort(const std::string& message);
private:
	// \brief Resolve macro.
	// \param macro Macro to be resolved.
	// \return Resolved string.
	std::string resolveMacro(std::string macro);

	// \brief Resolve message.
	// \param Message to be resolved.
	// \return Resolved message.
	std::string resolveMessage(std::string message);

	// \brief Make directory if needed.
	// \param path Path to directory.
	void makeDir(std::string path);

	// \brief Resolve path.
	// \param path Path to be resolved.
	// \return Resolved path.
	std::string resolvePath(std::string path);

	// \brief Worker entry function.
	void backgroundLogging();

	bool Exit_;
	unsigned int Depth_;
	std::string Path_;
	std::string FilenamePattern_;
	std::queue<std::string> Logs_;
	std::thread Worker_;
	std::mutex Mutex_;
	std::condition_variable BreakCond_;
};


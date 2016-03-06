#include "Logger.h"

Logger::Logger(const std::string& path, unsigned int depth) :
	Exit_(false), Depth_(depth),
	Path_(path), FilenamePattern_("DebugOut.%t.txt"),
	Worker_(&Logger::backgroundLogging, this)
{
}

Logger::Logger(const std::string& path, const std::string& filename, unsigned int depth) :
	Exit_(false), Depth_(depth),
	Path_(path), FilenamePattern_(filename),
	Worker_(&Logger::backgroundLogging, this)
{
}

Logger::~Logger()
{
	{
		std::lock_guard<std::mutex> lk(Mutex_);
		Exit_ = true;
	}
	BreakCond_.notify_one();
	if (Worker_.joinable())
		Worker_.join();
}

std::string Logger::resolveMacro(std::string macro)
{
	std::string output;

	if (macro.length() != 2 || (macro.length() > 1 && macro[0] != '%'))
		return output;

	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buffer[4];
	tm time;
#ifdef __GNUC__
	localtime_r(&now, &time); 
#else
	localtime_s(&time, &now);
#endif

	switch (macro[1])
	{
	case 'y':
		//strftime(buffer, sizeof(buffer), "%Y", &time); // do not work for some reason
		//output.append(buffer);
		output = std::to_string(time.tm_year + 1900);
		break;
	case 'm':
		strftime(buffer, sizeof(buffer), "%m", &time);
		output.append(buffer);
		break;
	case 'd':
		strftime(buffer, sizeof(buffer), "%d", &time);
		output.append(buffer);
		break;
	case 'h':
		strftime(buffer, sizeof(buffer), "%H", &time);
		output.append(buffer);
		break;
	case 'i':
		strftime(buffer, sizeof(buffer), "%M", &time);
		output.append(buffer);
		break;
	case 's':
		strftime(buffer, sizeof(buffer), "%S", &time);
		output.append(buffer);
		break;
	case 'a':
		output = "ABORT";
		break;
	case 't':
		output = resolveMacro("%y") + '-' + resolveMacro("%m") + '-' + resolveMacro("%d") + ' ' +
			resolveMacro("%h") + '-' + resolveMacro("%i") + '-' + resolveMacro("%s");
		break;
	default:
		break;
	}

	return output;
}

std::string Logger::resolveMessage(std::string message)
{
	if (message.empty())
		return "";

	auto pos = message.find('%');
	while (pos != std::string::npos)
	{
		std::string p1 = message.substr(0, pos);
		std::string p2 = message.substr(pos + 2);
		std::string macro = resolveMacro(message.substr(pos, 2));
		message = p1 + macro + p2;
		pos = message.find('%');
	}

	return message;
}

void Logger::makeDir(std::string path)
{
	auto dir = std::tr2::sys::path(path);

	if (!std::tr2::sys::exists(dir))
		std::tr2::sys::create_directory(dir);
}

std::string Logger::resolvePath(std::string path)
{
	if (path[0] == '/')
		path = path.substr(1);

	if (path[path.length() - 1] == '/')
		path = path.substr(0, path.length() - 1);

	return path;
}

void Logger::setDepth(unsigned int depth)
{
	Depth_ = depth;
}

Logger& Logger::out(const std::string& message, unsigned int depth)
{
	if(Depth_ < depth)
		return *this;
	
	{
		std::lock_guard<std::mutex> lk(Mutex_);
		Logs_.push(message);
	}
	return *this;
}

void Logger::abort(const std::string& message)
{
	out(message, 0);
	{
		std::lock_guard<std::mutex> lk(Mutex_);
		Exit_ = true;
	}
	BreakCond_.notify_one();
	if (Worker_.joinable())
		Worker_.join();
	std::abort();
}

void Logger::backgroundLogging()
{
	if (FilenamePattern_.empty())
		FilenamePattern_ = "DebugOut.%t.txt";

	std::string filename = resolvePath(Path_) + '/' + resolveMessage(FilenamePattern_);
	makeDir(resolvePath(Path_));

	std::fstream file;

	std::string top;
	bool exit = false;
	size_t logsCount = 0;

	while (!exit || (exit && logsCount != 0))
	{
		{
			std::lock_guard<std::mutex> lk(Mutex_);
			logsCount = Logs_.size();
			if (logsCount > 0)
			{
				top = Logs_.front();
				Logs_.pop();
			}
			else top.clear();
		}

		if (!top.empty() && !file.is_open())
			file.open(filename, std::ios_base::out | std::ios_base::app);
		if (!top.empty() && file.good())
		{
			file << resolveMessage(top) + '\n';
			std::lock_guard<std::mutex> lk(Mutex_);
			if (Logs_.size() == 0)
				file.close();
			else continue;
		}

		{
			std::unique_lock<std::mutex> lk(Mutex_);
			if (BreakCond_.wait_for(lk, std::chrono::milliseconds(100), [this](){ return Exit_; }))
			{
				exit = true;
				logsCount = Logs_.size();
			}
		}
	}

	if (file.is_open())
		file.close();
}
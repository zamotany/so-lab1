#include "INIParser.h"

INIParser::INIParser(const std::string& filename) : LastIndex_(0), Error_(false), Ready_(loadAndParse(filename))
{
}

INIParser::~INIParser()
{
}

bool INIParser::loadAndParse(const std::string& filename)
{
	Sections_.clear();
	LastIndex_ = 0;

	if (filename.empty())
	{
		Error_ = true;
		return false;
	}

	FileName_ = filename;

	std::string temp;
	std::string section = "__global__";
	std::fstream file;

	file.open(FileName_, std::ios_base::in);

	//if file do not exists is_open() returns false
	if (!file.is_open())
		return true;

	while (getline(file, temp, '\n'))
	{
		bool isString = false;

		//check if it is empty line
		if (temp.empty())
		{
			Sections_[section].push_back(OrderedKeyValue(LastIndex_++, "newline", ""));
			continue;
		}

		//check if line is a comment
		if (temp[0] == ';' || temp[0] == '#')
		{
			Sections_[section].push_back(OrderedKeyValue(LastIndex_++, "comment", temp));
			continue;
		}

		//check if line is section declaration
		if (temp.find('[') != std::string::npos && temp.find(']') != std::string::npos)
		{
			section = temp.substr(1, temp.length() - 2);
			Sections_[section].push_back(OrderedKeyValue(LastIndex_++, "section", section));
			continue;
		}
		else if ((temp.find('[') != std::string::npos && temp.find(']') == std::string::npos) ||
			(temp.find('[') == std::string::npos && temp.find(']') != std::string::npos))
			continue;

		//check if line has string
		auto open = temp.find("\"");
		auto close = temp.rfind("\"");

		if ((open == std::string::npos && close != std::string::npos) ||
			(open != std::string::npos && close == std::string::npos) ||
			(open != std::string::npos && close != std::string::npos && open == close))
			continue;
		else if (open == std::string::npos && close == std::string::npos)
		{
			while (temp.find(' ') != std::string::npos || temp.find('\t') != std::string::npos)
			{
				if (temp.find(' ') != std::string::npos)
					temp.erase(temp.find(' '), 1);
				if (temp.find('\t') != std::string::npos)
					temp.erase(temp.find('\t'), 1);
			}
		}
		else if (open != std::string::npos && close != std::string::npos)
		{
			//divide line into key and string, so the string will remaind unchanged
			std::string str = temp.substr(open + 1, close - open - 1);
			temp = temp.substr(0, temp.find('=') + 1);

			while (temp.find(' ') != std::string::npos || temp.find('\t') != std::string::npos)
			{
				if (temp.find(' ') != std::string::npos)
					temp.erase(temp.find(' '), 1);
				if (temp.find('\t') != std::string::npos)
					temp.erase(temp.find('\t'), 1);
			}

			temp += str;
			isString = true;
		}

		if (!temp.empty())
		{
			Sections_[section].push_back(OrderedKeyValue(
				LastIndex_++,
				temp.substr(0, temp.find('=')),
				temp.substr(temp.find('=') + 1),
				isString
				));
		}

	}

	return true;
}

bool INIParser::sectionExist(const std::string& section) const
{
	if (Error_)
		return false;

	return Sections_.find((section.empty() ? "__global__" : section)) != Sections_.end();
}

bool INIParser::keyExist(const std::string& section, const std::string& key) const
{
	if (Error_ || !sectionExist(section))
		return false;

	for (auto it = Sections_.at((section.empty() ? "__global__" : section)).begin();
		it != Sections_.at((section.empty() ? "__global__" : section)).end(); it++)
	{
		if (it->Key == key)
			return true;
	}

	return false;
}

std::string INIParser::get(const std::string& section, const std::string& key, const std::string& defaultValue) const
{
	if (!Ready_ || !sectionExist(section))
		return defaultValue;

	for (auto it = Sections_.at((section.empty() ? "__global__" : section)).begin();
		it != Sections_.at((section.empty() ? "__global__" : section)).end(); it++)
	{
		if (it->Key == key)
			return it->Value;
	}

	return defaultValue;
}

long INIParser::getInt(const std::string& section, const std::string& key, long defaultValue) const
{
	return std::stol(get(section, key, std::to_string(defaultValue)));
}

bool INIParser::getBool(const std::string& section, const std::string& key, bool defaultValue) const
{
	return std::stoi(get(section, key, std::to_string(defaultValue))) == 0 ? false : true;
}

double INIParser::getFloat(const std::string& section, const std::string& key, double defaultValue) const
{
	return (double)std::stod(get(section, key, std::to_string(defaultValue)));
}

void INIParser::set(const std::string& section, const std::string& key, const std::string& value)
{
	if (!Ready_)
		return;

	bool foundKey = false;
	int appendInIndex = -1;

	std::string str = section.empty() ? "__global__" : section;

	if (!sectionExist(str))
	{
		Sections_[str].push_back(OrderedKeyValue(LastIndex_++, "section", str));
		Sections_.at(str).push_back(OrderedKeyValue(LastIndex_++, key, value));
		return;
	}

	for (auto it = Sections_.at(str).begin(); it != Sections_.at(str).end(); it++)
	{
		if (it->Key == key)
		{
			it->Value = value;
			foundKey = true;
			break;
		}

		appendInIndex = it->Index;
	}
	
	if (!foundKey)
		Sections_.at(str).push_back(OrderedKeyValue(appendInIndex, key, value));
}

void INIParser::setInt(const std::string& section, const std::string& key, long value)
{
	set(section, key, std::to_string(value));
}

void INIParser::setBool(const std::string& section, const std::string& key, bool value)
{
	set(section, key, std::to_string(value));
}

void INIParser::setFloat(const std::string& section, const std::string& key, double value)
{
	set(section, key, std::to_string(value));
}

bool INIParser::save()
{
	if (Error_)
		return false;

	File_.open(FileName_, std::ios_base::out);
	if (!File_.is_open())
		return false;

	for (size_t i = 0; i < LastIndex_; i++)
	{
		bool inserted = false;

		for (auto sec = Sections_.begin(); !inserted && sec != Sections_.end(); sec++)
		{
			for (auto it = sec->second.begin(); it != sec->second.end(); it++)
			{
				if (it->Index == i)
				{
					if (it->Key == "newline")
						File_ << '\n';
					else if (it->Key == "comment")
						File_ << it->Value + '\n';
					else if (it->Key == "section")
						File_ << '[' + it->Value + "]\n";
					else
					{
						if (it->IsString)
							File_ << it->Key + "=\"" + it->Value + "\"\n";
						else File_ << it->Key + '=' + it->Value + '\n';
					}

					inserted = true;
				}
			}
		}
	}
	File_.close();

	return true;
}

std::vector<std::string> INIParser::getKeysVector(const std::string& section) const
{
	std::vector<std::string> output;

	if (!sectionExist(section))
		return output;

	auto keys = Sections_.at(section);
	for (auto it = keys.begin(); it != keys.end(); it++)
	{
		if (it->Key != "newline" && it->Key != "comment" && it->Key != "section")
			output.push_back(it->Key);
	}
	return output;
}
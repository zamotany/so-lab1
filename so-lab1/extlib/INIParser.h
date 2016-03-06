#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

namespace sfe
{
	class INIParser;
}

// \brief Custom INI file parser.
// \author Pawe³ Trys³a aka zamotany.
// \detail Parser supports keys without specified section (aka global), however
//         they must be placed at the beginig of the file.
//         Parser supports RGBA color, however the must be placed in rgba()
//         wrapper: myColor=rgba(255, 0, 0, 255).
//         WIP: HSLA colors support.
//         WIP: Hex w/ Alpha colors support.
// \note Comments must be placed in separate lines begining with # or ; without
//       any other character before them.
// \note Strings must be placed inside double quotes: myString="value".
// \note Multiple identical keys are allowed, but get methods will return the
//       first one found.
// \attention Parser DOES NOT support multi-line values.
class sfe::INIParser
{
public:
	// \brief Default constructor.
	// \param filename Full file name with path.
	// \note If file exists, it is read.
	INIParser(const std::string& filename);

	// \brief Default destructor.
	~INIParser();

	// \brief Operator =.
	INIParser& operator=(const INIParser&) = delete;

	// \brief Copy constructor.
	INIParser(const INIParser&) = delete;

	// \bierf Load file into memory and parse it's content.
	// \param filename Full file name with path.
	// \note Overrides any prevously stored data.
	// \return False if filename is empty or could not open file, true otherwise.
	bool loadAndParse(const std::string& filename);

	// \bierf Check if given section exists.
	// \param section Name of section to check.
	// \return True if section exists, false otherwise.
	bool sectionExist(const std::string& section) const;

	// \bierf Check if given key exists in given section.
	// \param section Name of section.
	// \param key Name of key to check.
	// \return True if section exists, false otherwise.
	bool keyExist(const std::string& section, const std::string& key) const;

	// \brieg Get value assigned to given key in given section.
	// \param section Name of section.
	// \param key Name of key.
	// \param defaultValue Optional value returned if key was not found or error occured.
	// \note If multiple values with the same keys exist in the same section, the first found one is returned.
	// \return Value assigned to given key in given section.
	std::string get(const std::string& section, const std::string& key, const std::string& defaultValue = "") const;
	long getInt(const std::string& section, const std::string& key, long defaultValue = 0) const;
	bool getBool(const std::string& section, const std::string& key, bool defaultValue = false) const;
	double getFloat(const std::string& section, const std::string& key, double defaultValue = 0.f) const;
	sf::Color getColor(const std::string& section, const std::string& key, sf::Color defaultValue = sf::Color::Black) const;

	// \brief Add or set value of given key in given section.
	// \param section Name of section.
	// \param key Name of key.
	// \param value New value of given key.
	void set(const std::string& section, const std::string& key, const std::string& value);
	void setInt(const std::string& section, const std::string& key, long value);
	void setBool(const std::string& section, const std::string& key, bool value);
	void setFloat(const std::string& section, const std::string& key, double value);
	void setColor(const std::string& section, const std::string& key, sf::Color value);

	// \brief Save data back into file.
	// \note New keys are placed at the end of the section in the same order there were set.
	// \note New sections are placed at the end of the file in the same order there were set.
	// \note Comments and newlines are preserved.
	// \returns False if file there are no associated file, filename is empty or could not open file, true otherwise.
	bool save();

	// \brief Get vector of keys in given section.
	// \param section Section from which keys will be retrived.
	// \return Vector of keys.
	std::vector<std::string> getKeysVector(const std::string& section) const;
private:
	struct OrderedKeyValue
	{
		size_t Index;
		std::string Key;
		std::string Value;
		bool IsString;
		OrderedKeyValue(size_t index, const std::string& key, const std::string& value, bool isString = false)
			: Index(index), Key(key), Value(value), IsString(isString) {}
	};
	std::map<std::string, std::vector<OrderedKeyValue>> Sections_;
	std::fstream File_;
	std::string FileName_;
	size_t LastIndex_;
	bool Error_;
	bool Ready_;
};


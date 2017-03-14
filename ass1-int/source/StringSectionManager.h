#pragma once
#include <map>
#include <string>

class StringSectionManager
{
	StringSectionManager(){}
	std::map<std::string, std::string> m_strings;
public:
	static StringSectionManager& get()
	{
		static StringSectionManager instance; // Guaranteed to be destroyed. Instantiated on first use.
		return instance;
	}

	StringSectionManager(StringSectionManager const&) = delete;
	void operator=(StringSectionManager const&) = delete;

	void addString(std::string name, std::string str) {
		m_strings[name] = str;
	}

	std::string to_asm() {
		std::stringstream output;
		output << "\".data\"" << std::endl;
		for (auto pair : m_strings) {
			output << "\"" << pair.first << ": " << pair.second << "\"" << std::endl;
		}
		return "";
	}
};


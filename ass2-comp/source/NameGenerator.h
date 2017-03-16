#pragma once
#include <map>
#include <string>

class NameGenerator
{
	NameGenerator(){}
	std::map<std::string, int> m_count;
public:
	static NameGenerator& get()
	{
		static NameGenerator instance; // Guaranteed to be destroyed. Instantiated on first use.
		return instance;
	}

	NameGenerator(NameGenerator const&) = delete;
	void operator=(NameGenerator const&) = delete;

	std::string nextName(std::string prefix) {
		if (!m_count.count(prefix))
			m_count[prefix] = 0;
		return prefix + std::to_string(m_count[prefix]++);
	}

	std::string nextTemp() {
		return nextName("t");
	}

	std::string nextTable() {
		return nextName("table");
	}

	std::string nextStr() {
		return nextName("str");
	}
	
	std::string nextBlk() {
		return nextName("blk");
	}
};


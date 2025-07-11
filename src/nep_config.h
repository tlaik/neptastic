#pragma once

#include <string>
#include <vector>

#define NEP_CONFIG_PATH "nep.ini"

enum NepCfgOptType {
	NEP_INT,
	NEP_FLOAT,
	NEP_BOOL,
	NEP_STRING,
	NEP_TYPE_MAX
};
extern const char* nepCfgOptFmt[(int)NEP_TYPE_MAX];

union NepVal {
	int iVal;
	float fVal;
	bool bVal;
	const char* sVal;
};

struct NepCfgOption {
	NepCfgOptType type;
	const char* name;
	const char* desc;
	NepVal val;
};

class NepConfig {
	std::vector<NepCfgOption> opt;
	std::string txt;

public:
	NepConfig();
	void loadDefault();
	void loadConfig();
	int geti(const char* name);
	float getf(const char* name);
	bool getb(const char* name);
	const char* gets(const char* name);

private:
	void writeConfig();
	const NepCfgOption* getOption(const char* name);
	void updateTxt();
	const char* getTxt();

	template <typename T = int, NepCfgOptType NepType = NEP_INT>
	void setOption(const char*, const char*, T);
};

extern NepConfig nepCfg;
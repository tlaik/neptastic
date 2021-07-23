// Security is for the insecure; The strength of spirit is earned through battling the buffer overflow in hand-to-hand combat.
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include "nep_main.h"
#include "nep_config.h"

#define NEP_CFG_TRUE	"Yes"
#define NEP_CFG_FALSE	"No"

const char* nepCfgOptFmt[(int)NEP_TYPE_MAX] = { "%d", "%f", "%3s" };

template <class T, NepCfgOptType NepType>
void NepConfig::setOption(const char* name, const char* desc, T val) {
	NepCfgOption tmp { NepType, name, desc, *((int*)&val) };
	auto found = std::find_if(opt.begin(), opt.end(), [&tmp](const NepCfgOption& o){ return o.name == tmp.name; });
	if(found != opt.end())
		*found = tmp;
	else
		opt.push_back(tmp);
}

const NepCfgOption* NepConfig::getOption(const char* name) {
	for (auto i = opt.begin(); i != opt.end(); i++)
		if (_stricmp(i->name, name) == 0)
			return &(*i);
	return NULL;
}

int NepConfig::geti(const char* name) {
	const NepCfgOption* tmp = getOption(name);
	if (tmp->type == NEP_INT)
		return tmp->val.iVal;
	return 0;
};

float NepConfig::getf(const char* name) {
	const NepCfgOption* tmp = getOption(name);
	if (tmp->type == NEP_FLOAT)
		return tmp->val.fVal;
	return 0.0f;
};

bool NepConfig::getb(const char* name) {
	const NepCfgOption* tmp = getOption(name);
	if (tmp->type == NEP_BOOL)
		return tmp->val.bVal;
	return false;
};

void NepConfig::updateTxt() {
	txt.clear();
	std::ostringstream sstream;
	sstream << std::setprecision(1) << std::fixed;
	for (auto i = opt.begin(); i != opt.end(); i++) {
		if(i->desc) {
			if(i != opt.begin()) sstream << std::endl;
			sstream << "// " << i->desc << std::endl;
		}
		sstream << i->name << ": ";
		switch(i->type) {
			case NEP_INT: sstream << i->val.iVal; break;
			case NEP_FLOAT: sstream << i->val.fVal; break;
			case NEP_BOOL: sstream << (i->val.bVal ? NEP_CFG_TRUE : NEP_CFG_FALSE);
		}
		sstream << std::endl;
	}
	txt = sstream.str();
}

const char* NepConfig::getTxt() { return txt.c_str(); }

void NepConfig::loadDefault() {
	setOption<float, NEP_FLOAT>("Resolution scaling", "1.0 = Render at window/screen size. Higher numbers produce smoother image, but values above 2.0 are not recommended", 2.0f);
	setOption<bool, NEP_BOOL>("FPS Unlock", "Only for RB2 || Yes = Unlimited FPS, No = Default 60 FPS cap", true);
	setOption("VSync type", "1 = No VSync, 2 = VSync, 3 = Adaptive VSync (Recommended)", 3);
	setOption<bool, NEP_BOOL>("Simple outlines", "Yes = Simple gray outlines, No = Default textured outlines", false);
	setOption<float, NEP_FLOAT>("Outlines intensity", NULL, 0.2f);
	setOption<float, NEP_FLOAT>("Shadow resolution", "1.0 = 1024x1024, 2.0 = 2048x2048, etc.", 4.0f);
	setOption<float, NEP_FLOAT>("Shadow blur", NULL, 1.0f);
	setOption<float, NEP_FLOAT>("Bloom intensity", "Bloom intensity has the most effect, reasonable values are up to ~1.2", 0.6f);
	setOption<float, NEP_FLOAT>("Bloom contrast", NULL, 2.0f);
	setOption<float, NEP_FLOAT>("Bloom softness", NULL, 10.0f);
	setOption("Bloom samples", NULL, 5);
	updateTxt();
}

void NepConfig::writeConfig() {
	FILE* f = fopen(NEP_PATH(NEP_CONFIG_PATH), "w");
	fprintf(f, getTxt());
	fclose(f);
}

NepConfig::NepConfig() { }

NepConfig nepCfg;

void NepConfig::loadConfig() {
	loadDefault();
	char buf[8192];
	FILE* f = fopen(NEP_PATH(NEP_CONFIG_PATH), "r");
	if(!f) {
		sprintf(buf, "Couldn't open " NEP_CONFIG_PATH "\nUsing default values & creating new config:\n\n%s", getTxt());
		MessageBoxA(NULL, buf, "Nepu!", MB_OK | MB_ICONINFORMATION);
		writeConfig();
		return;
	}

	while(fgets(buf, sizeof(buf), f)) {
		int len = strlen(buf);
		if(len < 2 || buf[0] == '/' && buf[1] == '/')
			continue;
		strtok(buf, "\r\n");

		char scanTmp[128];
		bool unknown = true;
		for(auto i  = opt.begin(); i != opt.end(); i++) {
			if(sscanf(buf, "%[A-Za-z ]", scanTmp) == 0 || strcmp(scanTmp, i->name) != 0) continue;
			unknown = false;
			sprintf(scanTmp, "%s: %s", i->name, nepCfgOptFmt[i->type]);
			NepVal tmp = {0};
			if(i->type == NEP_INT || i->type == NEP_FLOAT)
				sscanf(buf, scanTmp, &tmp);
			else if(i->type == NEP_BOOL) {
				char boolVal[4];
				sscanf(buf, scanTmp, boolVal);
				tmp.bVal = strcmp(boolVal, NEP_CFG_TRUE) == 0;
			}
			switch(i->type) {
				case NEP_INT: setOption(i->name, i->desc, tmp.iVal); break;
				case NEP_FLOAT: setOption<float, NEP_FLOAT>(i->name, i->desc, tmp.fVal); break;
				case NEP_BOOL: setOption<bool, NEP_BOOL>(i->name, i->desc, tmp.bVal); break;
			}
		}

		if(unknown)
			NEP_LOG("Unknown option: [%s]\n", buf)
	}

	updateTxt();

	fclose(f);
}
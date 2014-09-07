#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include "Utilities/Utilities.h"
#include "Variable System/VariableSystem.h"
#include "Launcher/ArgumentParser.h"
#include "Launcher/LauncherMode.h"
#include "Launcher/GameType.h"

class SettingsManager {
public:
	SettingsManager();
	SettingsManager(const SettingsManager & s);
	SettingsManager & operator = (const SettingsManager & s);
	~SettingsManager();

	static SettingsManager * getInstance();
	void updateInstance();
	
	void reset();
	
	bool load(const ArgumentParser * args = NULL);
	bool save(const ArgumentParser * args = NULL) const;
	bool loadFrom(const char * fileName);
	bool loadFrom(const QString & fileName);
	bool saveTo(const char * fileName) const;
	bool saveTo(const QString & fileName) const;

public:
	const static char * defaultSettingsFileName;
	const static char * defaultDataDirectoryName;
	const static char * defaultGameFileName;
	const static char * defaultGamePath;
	const static char * defaultSetupSoundFileName;
	const static char * defaultSetupVideoFileName;
	const static char * defaultCDISOFileName;
	const static char * defaultCDISOPath;
	const static char * defaultDOSBoxFileName;
	const static char * defaultDOSBoxPath;
	const static char * defaultDOSBoxArgs;
	const static char * defaultDOSBoxGameScriptFileName;
	const static char * defaultDOSBoxSetupSoundScriptFileName;
	const static char * defaultDOSBoxSetupVideoScriptFileName;
	const static char * defaultDOSBoxClientScriptFileName;
	const static char * defaultDOSBoxServerScriptFileName;
	const static char * defaultWindowsGameScriptFileName;
	const static char * defaultWindowsSetupSoundScriptFileName;
	const static char * defaultWindowsSetupVideoScriptFileName;
	const static LauncherModes::LauncherMode defaultLauncherMode;
	const static GameTypes::GameType defaultGameType;
	const static char * defaultServerIPAddress;
	
	char * dataDirectoryName;
	char * gameFileName;
	char * gamePath;
	char * setupSoundFileName;
	char * setupVideoFileName;
	char * CDISOFileName;
	char * CDISOPath;
	char * DOSBoxFileName;
	char * DOSBoxPath;
	char * DOSBoxArgs;
	char * DOSBoxGameScriptFileName;
	char * DOSBoxSetupSoundScriptFileName;
	char * DOSBoxSetupVideoScriptFileName;
	char * DOSBoxClientScriptFileName;
	char * DOSBoxServerScriptFileName;
	char * windowsGameScriptFileName;
	char * windowsSetupSoundScriptFileName;
	char * windowsSetupVideoScriptFileName;
	LauncherModes::LauncherMode launcherMode;
	GameTypes::GameType gameType;
	char * serverIPAddress;

private:
	static SettingsManager * instance;
	VariableSystem * m_variables;
};

#endif // SETTINGS_MANAGER_H

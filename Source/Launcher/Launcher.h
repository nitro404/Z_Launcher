#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QString.h>
#include <QTextStream.h>
#include <QRegExp.h>
#include <QXmlStream.h>
#include "Launcher/MenuOptions.h"
#include "Launcher/LauncherMode.h"
#include "Launcher/GameType.h"
#include "Script/Script.h"

class Launcher {
public:
	Launcher();
	~Launcher();

	bool init(int argc, char * argv[], bool start = true);
	bool init(const ArgumentParser * args = NULL, bool start = true);
	bool uninit();

	void run();

	LauncherModes::LauncherMode getMode() const;
	const char * getModeName() const;
	bool setMode(const char * modeName);
	bool setMode(const QString & modeName);
	bool setMode(int mode);
	bool setMode(LauncherModes::LauncherMode mode);

	GameTypes::GameType getGameType() const;
	const char * getGameTypeName() const;
	bool setGameType(const char * gameTypeName);
	bool setGameType(const QString & gameTypeName);
	bool setGameType(int gameType);
	bool setGameType(GameTypes::GameType gameType);

	const char * getServerIPAddress() const;
	void setServerIPAddress(const char * ipAddress);
	void setServerIPAddress(const QString & ipAddress);

	void runMenu();
	void runGameTypePrompt(const QString & args = QString());
	void runModePrompt(const QString & args = QString());
	void runIPAddressPrompt(const QString & args = QString());
	void runPortPrompt(const QString & args = QString());
	bool runGame(const ArgumentParser * args = NULL);
	bool updateScriptArgs();

	bool handleArguments(const ArgumentParser * args, bool start);

	static int checkForMissingExecutables();

	static void displayArgumentHelp();

	static const char * VERSION;
	
private:
	bool m_initialized;
	ArgumentParser * m_arguments;
	SettingsManager m_settings;
	LauncherModes::LauncherMode m_mode;
	GameTypes::GameType m_gameType;
	ScriptArguments m_scriptArgs;
};

#endif // LAUNCHER_H

#include "Settings Manager/SettingsManager.h"

SettingsManager * SettingsManager::instance = NULL;

const char * SettingsManager::defaultSettingsFileName = "Z Launcher.ini";
const char * SettingsManager::defaultDataDirectoryName = "Data";
const char * SettingsManager::defaultGameFileName = "ZED.EXE";
const char * SettingsManager::defaultGamePath = ".";
const char * SettingsManager::defaultSetupSoundFileName = "SETSOUND.EXE";
const char * SettingsManager::defaultSetupVideoFileName = "SETVIDEO.EXE";
const char * SettingsManager::defaultCDISOFileName = "Z.ISO";
const char * SettingsManager::defaultCDISOPath = ".";
const char * SettingsManager::defaultDOSBoxFileName = "dosbox.exe";
const char * SettingsManager::defaultDOSBoxPath = "DOSBox";
const char * SettingsManager::defaultDOSBoxArgs = "-noconsole";
const char * SettingsManager::defaultDOSBoxGameScriptFileName = "z.conf";
const char * SettingsManager::defaultDOSBoxSetupSoundScriptFileName = "z_setsound.conf";
const char * SettingsManager::defaultDOSBoxSetupVideoScriptFileName = "z_setvideo.conf";
const char * SettingsManager::defaultDOSBoxClientScriptFileName = "z_client.conf";
const char * SettingsManager::defaultDOSBoxServerScriptFileName = "z_server.conf";
const char * SettingsManager::defaultWindowsGameScriptFileName = "z.bat";
const char * SettingsManager::defaultWindowsSetupSoundScriptFileName = "z_setsound.bat";
const char * SettingsManager::defaultWindowsSetupVideoScriptFileName = "z_setvideo.bat";
const LauncherModes::LauncherMode SettingsManager::defaultLauncherMode = LauncherModes::defaultMode;
const GameTypes::GameType SettingsManager::defaultGameType = GameTypes::defaultGameType;
const char * SettingsManager::defaultServerIPAddress = "127.0.0.1";

SettingsManager::SettingsManager()
	: m_variables(new VariableCollection())
	, dataDirectoryName(NULL)
	, gameFileName(NULL)
	, gamePath(NULL)
	, setupSoundFileName(NULL)
	, setupVideoFileName(NULL)
	, CDISOFileName(NULL)
	, CDISOPath(NULL)
	, DOSBoxFileName(NULL)
	, DOSBoxPath(NULL)
	, DOSBoxArgs(NULL)
	, DOSBoxGameScriptFileName(NULL)
	, DOSBoxSetupSoundScriptFileName(NULL)
	, DOSBoxSetupVideoScriptFileName(NULL)
	, DOSBoxClientScriptFileName(NULL)
	, DOSBoxServerScriptFileName(NULL)
	, windowsGameScriptFileName(NULL)
	, windowsSetupSoundScriptFileName(NULL)
	, windowsSetupVideoScriptFileName(NULL)
	, launcherMode(defaultLauncherMode)
	, gameType(defaultGameType)
	, serverIPAddress(NULL) {
	if(instance == NULL) {
		instance = this;
	}
	reset();
}

SettingsManager::SettingsManager(const SettingsManager & s)
	: m_variables(new VariableCollection(*s.m_variables))
	, dataDirectoryName(NULL)
	, gameFileName(NULL)
	, gamePath(NULL)
	, setupSoundFileName(NULL)
	, setupVideoFileName(NULL)
	, CDISOFileName(NULL)
	, CDISOPath(NULL)
	, DOSBoxFileName(NULL)
	, DOSBoxPath(NULL)
	, DOSBoxArgs(NULL)
	, DOSBoxGameScriptFileName(NULL)
	, DOSBoxSetupSoundScriptFileName(NULL)
	, DOSBoxSetupVideoScriptFileName(NULL)
	, DOSBoxClientScriptFileName(NULL)
	, DOSBoxServerScriptFileName(NULL)
	, windowsGameScriptFileName(NULL)
	, windowsSetupSoundScriptFileName(NULL)
	, windowsSetupVideoScriptFileName(NULL)
	, launcherMode(s.launcherMode)
	, gameType(s.gameType)
	, serverIPAddress(NULL) {
	if(instance == NULL) {
		instance = this;
	}

	dataDirectoryName = Utilities::copyString(s.dataDirectoryName);
	gameFileName = Utilities::copyString(s.gameFileName);
	gamePath = Utilities::copyString(s.gamePath);
	setupSoundFileName = Utilities::copyString(s.setupSoundFileName);
	setupVideoFileName = Utilities::copyString(s.setupVideoFileName);
	CDISOFileName = Utilities::copyString(s.CDISOFileName);
	CDISOPath = Utilities::copyString(s.CDISOPath);
	DOSBoxFileName = Utilities::copyString(s.DOSBoxFileName);
	DOSBoxPath = Utilities::copyString(s.DOSBoxPath);
	DOSBoxArgs = Utilities::copyString(s.DOSBoxArgs);
	DOSBoxGameScriptFileName = Utilities::copyString(s.DOSBoxGameScriptFileName);
	DOSBoxSetupSoundScriptFileName = Utilities::copyString(s.DOSBoxSetupSoundScriptFileName);
	DOSBoxSetupVideoScriptFileName = Utilities::copyString(s.DOSBoxSetupVideoScriptFileName);
	DOSBoxClientScriptFileName = Utilities::copyString(s.DOSBoxClientScriptFileName);
	DOSBoxServerScriptFileName = Utilities::copyString(s.DOSBoxServerScriptFileName);
	windowsGameScriptFileName = Utilities::copyString(s.windowsGameScriptFileName);
	windowsSetupSoundScriptFileName = Utilities::copyString(s.windowsSetupSoundScriptFileName);
	windowsSetupVideoScriptFileName = Utilities::copyString(s.windowsSetupVideoScriptFileName);
	serverIPAddress = Utilities::copyString(s.serverIPAddress);
}

SettingsManager & SettingsManager::operator = (const SettingsManager & s) {
	if(instance == NULL) {
		instance = this;
	}

	if(dataDirectoryName != NULL)				{ delete [] dataDirectoryName; }
	if(gameFileName != NULL)					{ delete [] gameFileName; }
	if(gamePath != NULL)						{ delete [] gamePath; }
	if(setupSoundFileName != NULL)				{ delete [] setupSoundFileName; }
	if(setupVideoFileName != NULL)				{ delete [] setupVideoFileName; }
	if(CDISOFileName != NULL)					{ delete [] CDISOFileName; }
	if(CDISOPath != NULL)						{ delete [] CDISOPath; }
	if(DOSBoxFileName != NULL)					{ delete [] DOSBoxFileName; }
	if(DOSBoxPath != NULL)						{ delete [] DOSBoxPath; }
	if(DOSBoxArgs != NULL)						{ delete [] DOSBoxArgs; }
	if(DOSBoxGameScriptFileName != NULL)		{ delete [] DOSBoxGameScriptFileName; }
	if(DOSBoxSetupSoundScriptFileName != NULL)	{ delete [] DOSBoxSetupSoundScriptFileName; }
	if(DOSBoxSetupVideoScriptFileName != NULL)	{ delete [] DOSBoxSetupVideoScriptFileName; }
	if(DOSBoxClientScriptFileName != NULL)		{ delete [] DOSBoxClientScriptFileName; }
	if(DOSBoxServerScriptFileName != NULL)		{ delete [] DOSBoxServerScriptFileName; }
	if(windowsGameScriptFileName != NULL)		{ delete [] windowsGameScriptFileName; }
	if(windowsSetupSoundScriptFileName != NULL)	{ delete [] windowsSetupSoundScriptFileName; }
	if(windowsSetupVideoScriptFileName != NULL)	{ delete [] windowsSetupVideoScriptFileName; }
	if(serverIPAddress != NULL)					{ delete [] serverIPAddress; }

	delete m_variables;

	m_variables = new VariableCollection(*s.m_variables);

	launcherMode = s.launcherMode;
	gameType = s.gameType;

	dataDirectoryName = Utilities::copyString(s.dataDirectoryName);
	gameFileName = Utilities::copyString(s.gameFileName);
	gamePath = Utilities::copyString(s.gamePath);
	setupSoundFileName = Utilities::copyString(s.setupSoundFileName);
	setupVideoFileName = Utilities::copyString(s.setupVideoFileName);
	CDISOFileName = Utilities::copyString(s.CDISOFileName);
	CDISOPath = Utilities::copyString(s.CDISOPath);
	DOSBoxFileName = Utilities::copyString(s.DOSBoxFileName);
	DOSBoxPath = Utilities::copyString(s.DOSBoxPath);
	DOSBoxArgs = Utilities::copyString(s.DOSBoxArgs);
	DOSBoxGameScriptFileName = Utilities::copyString(s.DOSBoxGameScriptFileName);
	DOSBoxSetupSoundScriptFileName = Utilities::copyString(s.DOSBoxSetupSoundScriptFileName);
	DOSBoxSetupVideoScriptFileName = Utilities::copyString(s.DOSBoxSetupVideoScriptFileName);
	DOSBoxClientScriptFileName = Utilities::copyString(s.DOSBoxClientScriptFileName);
	DOSBoxServerScriptFileName = Utilities::copyString(s.DOSBoxServerScriptFileName);
	windowsGameScriptFileName = Utilities::copyString(s.windowsGameScriptFileName);
	windowsSetupSoundScriptFileName = Utilities::copyString(s.windowsSetupSoundScriptFileName);
	windowsSetupVideoScriptFileName = Utilities::copyString(s.windowsSetupVideoScriptFileName);
	serverIPAddress = Utilities::copyString(s.serverIPAddress);

	return *this;
}

SettingsManager::~SettingsManager() {
	if(dataDirectoryName != NULL)				{ delete [] dataDirectoryName; }
	if(gameFileName != NULL)					{ delete [] gameFileName; }
	if(gamePath != NULL)						{ delete [] gamePath; }
	if(setupSoundFileName != NULL)				{ delete [] setupSoundFileName; }
	if(setupVideoFileName != NULL)				{ delete [] setupVideoFileName; }
	if(CDISOFileName != NULL)					{ delete [] CDISOFileName; }
	if(CDISOPath != NULL)						{ delete [] CDISOPath; }
	if(DOSBoxFileName != NULL)					{ delete [] DOSBoxFileName; }
	if(DOSBoxPath != NULL)						{ delete [] DOSBoxPath; }
	if(DOSBoxArgs != NULL)						{ delete [] DOSBoxArgs; }
	if(DOSBoxGameScriptFileName != NULL)		{ delete [] DOSBoxGameScriptFileName; }
	if(DOSBoxSetupSoundScriptFileName != NULL)	{ delete [] DOSBoxSetupSoundScriptFileName; }
	if(DOSBoxSetupVideoScriptFileName != NULL)	{ delete [] DOSBoxSetupVideoScriptFileName; }
	if(DOSBoxClientScriptFileName != NULL)		{ delete [] DOSBoxClientScriptFileName; }
	if(DOSBoxServerScriptFileName != NULL)		{ delete [] DOSBoxServerScriptFileName; }
	if(windowsGameScriptFileName != NULL)		{ delete [] windowsGameScriptFileName; }
	if(windowsSetupSoundScriptFileName != NULL)	{ delete [] windowsSetupSoundScriptFileName; }
	if(windowsSetupVideoScriptFileName != NULL)	{ delete [] windowsSetupVideoScriptFileName; }
	if(serverIPAddress != NULL)					{ delete [] serverIPAddress; }

	delete m_variables;
}

SettingsManager * SettingsManager::getInstance() {
	return instance;
}

void SettingsManager::updateInstance() {
	instance = this;
}

void SettingsManager::reset() {
	if(dataDirectoryName != NULL)				{ delete [] dataDirectoryName; }
	if(gameFileName != NULL)					{ delete [] gameFileName; }
	if(gamePath != NULL)						{ delete [] gamePath; }
	if(setupSoundFileName != NULL)				{ delete [] setupSoundFileName; }
	if(setupVideoFileName != NULL)				{ delete [] setupVideoFileName; }
	if(CDISOFileName != NULL)					{ delete [] CDISOFileName; }
	if(CDISOPath != NULL)						{ delete [] CDISOPath; }
	if(DOSBoxFileName != NULL)					{ delete [] DOSBoxFileName; }
	if(DOSBoxPath != NULL)						{ delete [] DOSBoxPath; }
	if(DOSBoxArgs != NULL)						{ delete [] DOSBoxArgs; }
	if(DOSBoxGameScriptFileName != NULL)		{ delete [] DOSBoxGameScriptFileName; }
	if(DOSBoxSetupSoundScriptFileName != NULL)	{ delete [] DOSBoxSetupSoundScriptFileName; }
	if(DOSBoxSetupVideoScriptFileName != NULL)	{ delete [] DOSBoxSetupVideoScriptFileName; }
	if(DOSBoxClientScriptFileName != NULL)		{ delete [] DOSBoxClientScriptFileName; }
	if(DOSBoxServerScriptFileName != NULL)		{ delete [] DOSBoxServerScriptFileName; }
	if(windowsGameScriptFileName != NULL)		{ delete [] windowsGameScriptFileName; }
	if(windowsSetupSoundScriptFileName != NULL)	{ delete [] windowsSetupSoundScriptFileName; }
	if(windowsSetupVideoScriptFileName != NULL)	{ delete [] windowsSetupVideoScriptFileName; }
	if(serverIPAddress != NULL)					{ delete [] serverIPAddress; }

	dataDirectoryName = Utilities::copyString(defaultDataDirectoryName);
	gameFileName = Utilities::copyString(defaultGameFileName);
	gamePath = Utilities::copyString(defaultGamePath);
	setupSoundFileName = Utilities::copyString(defaultSetupSoundFileName);
	setupVideoFileName = Utilities::copyString(defaultSetupVideoFileName);
	CDISOFileName = Utilities::copyString(defaultCDISOFileName);
	CDISOPath = Utilities::copyString(defaultCDISOPath);
	DOSBoxFileName = Utilities::copyString(defaultDOSBoxFileName);
	DOSBoxPath = Utilities::copyString(defaultDOSBoxPath);
	DOSBoxArgs = Utilities::copyString(defaultDOSBoxArgs);
	DOSBoxGameScriptFileName = Utilities::copyString(defaultDOSBoxGameScriptFileName);
	DOSBoxSetupSoundScriptFileName = Utilities::copyString(defaultDOSBoxSetupSoundScriptFileName);
	DOSBoxSetupVideoScriptFileName = Utilities::copyString(defaultDOSBoxSetupVideoScriptFileName);
	DOSBoxClientScriptFileName = Utilities::copyString(defaultDOSBoxClientScriptFileName);
	DOSBoxServerScriptFileName = Utilities::copyString(defaultDOSBoxServerScriptFileName);
	windowsGameScriptFileName = Utilities::copyString(defaultWindowsGameScriptFileName);
	windowsSetupSoundScriptFileName = Utilities::copyString(defaultWindowsSetupSoundScriptFileName);
	windowsSetupVideoScriptFileName = Utilities::copyString(defaultWindowsSetupVideoScriptFileName);
	serverIPAddress = Utilities::copyString(defaultServerIPAddress);

	launcherMode = defaultLauncherMode;
	gameType = defaultGameType;
}

bool SettingsManager::load(const ArgumentParser * args) {
	if(args != NULL) {
		QString altSettingsFileName = args->getValue("f");
		if(altSettingsFileName.length() > 0) {
			QByteArray fileNameBytes = altSettingsFileName.toLocal8Bit();

			printf("Loading settings from alternate file: %s\n", fileNameBytes.data());

			bool loadedSettings = loadFrom(altSettingsFileName);
			if(!loadedSettings) {
				printf("Failed to load settings from alt settings file: %s\n", fileNameBytes.data());
			}
			return loadedSettings;
		}
	}

	return loadFrom(defaultSettingsFileName);
}

bool SettingsManager::save(const ArgumentParser * args) const {
	if(args != NULL) {
		QString altSettingsFileName = args->getValue("f");
		if(altSettingsFileName.length() > 0) {
			QByteArray fileNameBytes = altSettingsFileName.toLocal8Bit();

			printf("Saving settings to alternate file: %s\n", fileNameBytes.data());

			bool savedSettings = saveTo(altSettingsFileName);
			if(!savedSettings) {
				printf("Failed to save settings to alternate file: %s\n", fileNameBytes.data());
			}
			return savedSettings;
		}
	}

	return saveTo(defaultSettingsFileName);
}

bool SettingsManager::loadFrom(const QString & fileName) {
	QByteArray fileNameBytes = fileName.toLocal8Bit();

	return loadFrom(fileNameBytes.data());
}

bool SettingsManager::loadFrom(const char * fileName) {
	VariableCollection * newVariables = VariableCollection::readFrom(fileName);
	if(newVariables == NULL) { return false; }

	delete m_variables;
	m_variables = newVariables;

	const char * data = NULL;
	
	data = m_variables->getValue("Data Directory Name", "Paths");
	if(data != NULL) {
		if(dataDirectoryName != NULL) { delete [] dataDirectoryName; }
		dataDirectoryName = Utilities::copyString(data);
	}

	data = m_variables->getValue("Game File Name", "Paths");
	if(data != NULL) {
		if(gameFileName != NULL) { delete [] gameFileName; }
		gameFileName = Utilities::copyString(data);
	}

	data = m_variables->getValue("Game Path", "Paths");
	if(data != NULL) {
		if(gamePath != NULL) { delete [] gamePath; }
		gamePath = Utilities::copyString(data);
	}

	data = m_variables->getValue("Setup Sound File Name", "Paths");
	if(data != NULL) {
		if(setupSoundFileName != NULL) { delete [] setupSoundFileName; }
		setupSoundFileName = Utilities::copyString(data);
	}

	data = m_variables->getValue("Setup Video File Name", "Paths");
	if(data != NULL) {
		if(setupVideoFileName != NULL) { delete [] setupVideoFileName; }
		setupVideoFileName = Utilities::copyString(data);
	}

	data = m_variables->getValue("CD ISO File Name", "Paths");
	if(data != NULL) {
		if(CDISOFileName != NULL) { delete [] CDISOFileName; }
		CDISOFileName = Utilities::copyString(data);
	}

	data = m_variables->getValue("CD ISO Path", "Paths");
	if(data != NULL) {
		if(CDISOPath != NULL) { delete [] CDISOPath; }
		CDISOPath = Utilities::copyString(data);
	}

	data = m_variables->getValue("DOSBox File Name", "Paths");
	if(data != NULL) {
		if(DOSBoxFileName != NULL) { delete [] DOSBoxFileName; }
		DOSBoxFileName = Utilities::copyString(data);
	}
	
	data = m_variables->getValue("DOSBox Path", "Paths");
	if(data != NULL) {
		if(DOSBoxPath != NULL) { delete [] DOSBoxPath; }
		DOSBoxPath = Utilities::copyString(data);
	}

	data = m_variables->getValue("DOSBox Arguments", "Arguments");
	if(data != NULL) {
		if(DOSBoxArgs != NULL) { delete [] DOSBoxArgs; }
		DOSBoxArgs = Utilities::copyString(data);
	}
	
	data = m_variables->getValue("DOSBox Game Script File Name", "Scripts");
	if(data != NULL) {
		if(DOSBoxGameScriptFileName != NULL) { delete [] DOSBoxGameScriptFileName; }
		DOSBoxGameScriptFileName = Utilities::copyString(data);
	}
	
	data = m_variables->getValue("DOSBox Setup Sound Script File Name", "Scripts");
	if(data != NULL) {
		if(DOSBoxSetupSoundScriptFileName != NULL) { delete [] DOSBoxSetupSoundScriptFileName; }
		DOSBoxSetupSoundScriptFileName = Utilities::copyString(data);
	}

	data = m_variables->getValue("DOSBox Setup Video Script File Name", "Scripts");
	if(data != NULL) {
		if(DOSBoxSetupVideoScriptFileName != NULL) { delete [] DOSBoxSetupVideoScriptFileName; }
		DOSBoxSetupVideoScriptFileName = Utilities::copyString(data);
	}
	
	data = m_variables->getValue("DOSBox Client Script File Name", "Scripts");
	if(data != NULL) {
		if(DOSBoxClientScriptFileName != NULL) { delete [] DOSBoxClientScriptFileName; }
		DOSBoxClientScriptFileName = Utilities::copyString(data);
	}
	
	data = m_variables->getValue("DOSBox Server Script File Name", "Scripts");
	if(data != NULL) {
		if(DOSBoxServerScriptFileName != NULL) { delete [] DOSBoxServerScriptFileName; }
		DOSBoxServerScriptFileName = Utilities::copyString(data);
	}

	data = m_variables->getValue("Windows Game Script File Name", "Scripts");
	if(data != NULL) {
		if(windowsGameScriptFileName != NULL) { delete [] windowsGameScriptFileName; }
		windowsGameScriptFileName = Utilities::copyString(data);
	}
	
	data = m_variables->getValue("Windows Setup Sound Script File Name", "Scripts");
	if(data != NULL) {
		if(windowsSetupSoundScriptFileName != NULL) { delete [] windowsSetupSoundScriptFileName; }
		windowsSetupSoundScriptFileName = Utilities::copyString(data);
	}

	data = m_variables->getValue("Windows Setup Video Script File Name", "Scripts");
	if(data != NULL) {
		if(windowsSetupVideoScriptFileName != NULL) { delete [] windowsSetupVideoScriptFileName; }
		windowsSetupVideoScriptFileName = Utilities::copyString(data);
	}

	data = m_variables->getValue("Launcher Mode", "Options");
	if(data != NULL) {
		LauncherModes::LauncherMode newLauncherMode = LauncherModes::parseFrom(data);
		if(LauncherModes::isValid(newLauncherMode)) {
			launcherMode = newLauncherMode;
		}
	}

	data = m_variables->getValue("Game Type", "Options");
	if(data != NULL) {
		GameTypes::GameType newGameType = GameTypes::parseFrom(data);
		if(GameTypes::isValid(newGameType)) {
			gameType = newGameType;
		}
	}

	data = m_variables->getValue("Server IP Address", "Options");
	if(data != NULL) {
		if(serverIPAddress != NULL) { delete [] serverIPAddress; }
		serverIPAddress = Utilities::copyString(data);
	}
	
	return true;
}

bool SettingsManager::saveTo(const QString & fileName) const {
	QByteArray fileNameBytes = fileName.toLocal8Bit();

	return saveTo(fileNameBytes.data());
}

bool SettingsManager::saveTo(const char * fileName) const {
	m_variables->setValue("Data Directory Name", dataDirectoryName, "Paths");
	m_variables->setValue("Game File Name", gameFileName, "Paths");
	m_variables->setValue("Game Path", Utilities::stringLength(gamePath) == 0 ? defaultGamePath : gamePath, "Paths");
	m_variables->setValue("Setup Sound File Name", setupSoundFileName, "Paths");
	m_variables->setValue("Setup Video File Name", setupVideoFileName, "Paths");
	m_variables->setValue("CD ISO File Name", CDISOFileName, "Paths");
	m_variables->setValue("CD ISO Path", CDISOPath, "Paths");
	m_variables->setValue("DOSBox File Name", DOSBoxFileName, "Paths");
	m_variables->setValue("DOSBox Path", DOSBoxPath, "Paths");
	m_variables->setValue("DOSBox Arguments", DOSBoxArgs, "Arguments");
	m_variables->setValue("DOSBox Game Script File Name", DOSBoxGameScriptFileName, "Scripts");
	m_variables->setValue("DOSBox Setup Sound Script File Name", DOSBoxSetupSoundScriptFileName, "Scripts");
	m_variables->setValue("DOSBox Setup Video Script File Name", DOSBoxSetupVideoScriptFileName, "Scripts");
	m_variables->setValue("DOSBox Client Script File Name", DOSBoxClientScriptFileName, "Scripts");
	m_variables->setValue("DOSBox Server Script File Name", DOSBoxServerScriptFileName, "Scripts");
	m_variables->setValue("Windows Game Script File Name", windowsGameScriptFileName, "Scripts");
	m_variables->setValue("Windows Setup Sound Script File Name", windowsSetupSoundScriptFileName, "Scripts");
	m_variables->setValue("Windows Setup Video Script File Name", windowsSetupVideoScriptFileName, "Scripts");
	m_variables->setValue("Launcher Mode", LauncherModes::toString(launcherMode), "Options");
	m_variables->setValue("Game Type", GameTypes::toString(gameType), "Options");
	m_variables->setValue("Server IP Address", serverIPAddress, "Options");

	// group the variables by categories
	m_variables->sortVariables();

	// update the settings file with the changes
	return m_variables->writeTo(fileName);
}

#include "Launcher/Launcher.h"

Launcher::Launcher()
	: m_initialized(false)
	, m_arguments(NULL)
	, m_mode(LauncherModes::defaultMode)
	, m_gameType(GameTypes::defaultGameType) {
	
}

Launcher::~Launcher() {
	if(m_arguments != NULL) {
		delete m_arguments;
	}
}

bool Launcher::init(int argc, char * argv[], bool start) {
	return init(&ArgumentParser(argc, argv), start);
}

bool Launcher::init(const ArgumentParser * args, bool start) {
	if(m_initialized) { return true; }

	if(args != NULL) {
		m_arguments = new ArgumentParser(*args);
	}

	if(m_arguments != NULL && m_arguments->hasArgument("?")) {
		displayArgumentHelp();
		return false;
	}

	m_settings.load(m_arguments);

	m_mode = SettingsManager::getInstance()->launcherMode;
	m_gameType = SettingsManager::getInstance()->gameType;

	m_initialized = true;

	int numberOfMissingExecutables = checkForMissingExecutables();

	if(numberOfMissingExecutables > 0) {
		printf("\n");

		Utilities::pause();
		Utilities::clear();
	}

	if(!handleArguments(m_arguments, start)) {
		return false;
	}

	return true;
}

bool Launcher::uninit() {
	if(!m_initialized) { return false; }

	m_scriptArgs.clear();

	if(m_arguments != NULL) {
		delete m_arguments;
		m_arguments = NULL;
	}

	m_settings.save(m_arguments);

	m_initialized = false;

	return true;
}

void Launcher::run() {
	if(!m_initialized) { return; }

	runMenu();
}

LauncherModes::LauncherMode Launcher::getMode() const {
	return m_mode;
}

const char * Launcher::getModeName() const {
	return LauncherModes::toString(m_mode);
}

bool Launcher::setMode(const char * modeName) {
	if(modeName == NULL) { return false; }

	return setMode(LauncherModes::parseFrom(modeName));
}

bool Launcher::setMode(const QString & modeName) {
	return setMode(LauncherModes::parseFrom(modeName));
}

bool Launcher::setMode(int mode) {
	if(!LauncherModes::isValid(mode)) { return false; }

	m_mode = static_cast<LauncherModes::LauncherMode>(mode);

	SettingsManager::getInstance()->launcherMode = m_mode;

	return true;
}

bool Launcher::setMode(LauncherModes::LauncherMode mode) {
	if(!LauncherModes::isValid(mode)) { return false; }

	m_mode = mode;

	SettingsManager::getInstance()->launcherMode = m_mode;

	return true;
}

GameTypes::GameType Launcher::getGameType() const {
	return m_gameType;
}

const char * Launcher::getGameTypeName() const {
	return GameTypes::toString(m_mode);
}

bool Launcher::setGameType(const char * gameTypeName) {
	if(gameTypeName == NULL) { return false; }

	return setGameType(GameTypes::parseFrom(gameTypeName));
}

bool Launcher::setGameType(const QString & gameTypeName) {
	return setGameType(GameTypes::parseFrom(gameTypeName));
}

bool Launcher::setGameType(int gameType) {
	if(!GameTypes::isValid(gameType)) { return false; }

	m_gameType = static_cast<GameTypes::GameType>(gameType);

	SettingsManager::getInstance()->gameType = m_gameType;

	return true;
}

bool Launcher::setGameType(GameTypes::GameType gameType) {
	if(!GameTypes::isValid(gameType)) { return false; }

	m_gameType = gameType;

	SettingsManager::getInstance()->gameType = m_gameType;

	return true;
}

const char * Launcher::getServerIPAddress() const {
	return SettingsManager::getInstance()->serverIPAddress;
}

void Launcher::setServerIPAddress(const char * ipAddress) {
	if(SettingsManager::getInstance()->serverIPAddress != NULL) {
		delete [] SettingsManager::getInstance()->serverIPAddress;
	}
	
	if(ipAddress == NULL || Utilities::stringLength(ipAddress) == 0) {
		SettingsManager::getInstance()->serverIPAddress = new char[1];
		SettingsManager::getInstance()->serverIPAddress[0] = '\0';
	}
	else {
		SettingsManager::getInstance()->serverIPAddress = Utilities::trimCopyString(ipAddress);
	}
}

void Launcher::setServerIPAddress(const QString & ipAddress) {
	if(SettingsManager::getInstance()->serverIPAddress != NULL) {
		delete [] SettingsManager::getInstance()->serverIPAddress;
	}

	if(ipAddress.length() == 0) {
		SettingsManager::getInstance()->serverIPAddress = new char[1];
		SettingsManager::getInstance()->serverIPAddress[0] = '\0';
	}
	else {
		QByteArray ipAddressBytes = ipAddress.toLocal8Bit();
		SettingsManager::getInstance()->serverIPAddress = Utilities::trimCopyString(ipAddressBytes.data());
	}
}

void Launcher::runMenu() {
	if(!m_initialized) { return; }

	int selectedIndex = -1;
	bool valid = false;
	QTextStream in(stdin);
	QString input, data, formattedData;
	QByteArray dateBytes;

	static const QRegExp       gameRegExp("^(z|r(un)?|g(o)?|l(aunch)?|start)$");
	static const QRegExp     clientRegExp("^(c(lient)?)$");
	static const QRegExp     serverRegExp("^(s(server)?)$");
	static const QRegExp soundSetupRegExp("^(a(udio)?|sound)$");
	static const QRegExp videoSetupRegExp("^(v(ideo)?)$");
	static const QRegExp         ipRegExp("^(ip|connect)([ ]+.*)?");
	static const QRegExp   gameTypeRegExp("^(t(ype)?)([ ]+.*)?");
	static const QRegExp       modeRegExp("^(m(ode)?)([ ]+.*)?");
	static const QRegExp       helpRegExp("^(\\?|h(elp)?)$");
	static const QRegExp       backRegExp("^(b(ack)?)$");
	static const QRegExp       exitRegExp("^(x|exit|q(uit)?)$");

	while(true) {
		Utilities::clear();

		printf("======================\n");
		printf(" Z Launcher Main Menu\n");
		printf("======================\n");

		printf("\n");

		for(int i=static_cast<int>(MenuOptions::Invalid)+1;i<static_cast<int>(MenuOptions::NumberOfOptions);i++) {
			printf("%d. %s\n", i, MenuOptions::toString(i));
		}
		printf("> ");

		input = in.readLine();
		data = input.trimmed();
		formattedData = data.toLower();

		if(gameRegExp.exactMatch(formattedData)) {
			setGameType(GameTypes::Game);
			runGame();
			break;
		}
		else if(clientRegExp.exactMatch(formattedData)) {
			setGameType(GameTypes::Client);
			runGame();
			break;
		}
		else if(serverRegExp.exactMatch(formattedData)) {
			setGameType(GameTypes::Server);
			runGame();
			break;
		}
		else if(soundSetupRegExp.exactMatch(formattedData)) {
			GameTypes::GameType lastGameType = m_gameType;
			setGameType(GameTypes::SetupSound);
			runGame();
			setGameType(lastGameType);
			continue;
		}
		else if(videoSetupRegExp.exactMatch(formattedData)) {
			GameTypes::GameType lastGameType = m_gameType;
			setGameType(GameTypes::SetupVideo);
			runGame();
			setGameType(lastGameType);
			continue;
		}
		else if(ipRegExp.exactMatch(formattedData)) {
			runIPAddressPrompt(Utilities::getArguments(data));
			continue;
		}
		else if(gameTypeRegExp.exactMatch(formattedData)) {
			runGameTypePrompt(Utilities::getArguments(data));
			continue;
		}
		else if(modeRegExp.exactMatch(formattedData)) {
			runModePrompt(Utilities::getArguments(data));
			continue;
		}
		else if(backRegExp.exactMatch(formattedData)) {
			Utilities::clear();
			continue;
		}
		else if(helpRegExp.exactMatch(formattedData)) {
			Utilities::clear();

			printf("Command information:\n");
			printf("       z -------- start Z in single player mode.\n");
			printf("   [r]un -------- start Z in single player mode.\n");
			printf("    [g]o -------- start Z in single player mode.\n");
			printf("[l]aunch -------- start Z in single player mode.\n");
			printf("   start -------- start Z in single player mode.\n");
			printf("[c]lient -------- start Z in multiplayer client mode.\n");
			printf("[s]erver -------- start Z in multiplayer server mode.\n");
			printf(" [a]udio -------- run sound setup.\n");
			printf("   sound -------- run sound setup.\n");
			printf(" [v]ideo -------- run video setup.\n");
			printf(" connect <args> - obtains the ip address of the host server.\n");
			printf("      ip <args> - obtains the ip address of the host server.\n");
			printf("  [t]ype <args> - change game type (single / multi player).\n");
			printf("  [m]ode <args> - change mod manager launch mode (regular / dosbox).\n");
			printf("  [b]ack -------- returns to the previous menu (if applicable).\n");
			printf("  [h]elp -------- displays this help message.\n");
			printf("       ? -------- displays this help message.\n");
			printf("  [q]uit -------- closes the program.\n");
			printf("  e[x]it -------- closes the program.\n");
			printf("\n");

			Utilities::pause();

			continue;
		}
		else if(exitRegExp.exactMatch(formattedData)) {
			Utilities::clear();

			printf("Goodbye!\n");
			printf("\n");

			return;
		}

		selectedIndex = data.toInt(&valid, 10);

		if(valid) {
			valid = false;

			if(selectedIndex >= 1 && selectedIndex < static_cast<int>(MenuOptions::NumberOfOptions)) {
				valid = true;

				if(selectedIndex == MenuOptions::LaunchGame) {
					setGameType(GameTypes::Game);
					runGame();
					break;
				}
				else if(selectedIndex == MenuOptions::LaunchClient) {
					setGameType(GameTypes::Client);
					runGame();
					break;
				}
				else if(selectedIndex == MenuOptions::LaunchServer) {
					setGameType(GameTypes::Server);
					runGame();
					break;
				}
				else if(selectedIndex == MenuOptions::SoundSetup) {
					GameTypes::GameType lastGameType = m_gameType;
					setGameType(GameTypes::SetupSound);
					runGame();
					setGameType(lastGameType);
					continue;
				}
				else if(selectedIndex == MenuOptions::VideoSetup) {
					GameTypes::GameType lastGameType = m_gameType;
					setGameType(GameTypes::SetupVideo);
					runGame();
					setGameType(lastGameType);
					continue;
				}
				else if(selectedIndex == MenuOptions::ChangeGameType) {
					runGameTypePrompt();
					continue;
				}
				else if(selectedIndex == MenuOptions::ChangeLauncherMode) {
					runModePrompt();
					continue;
				}
				else if(selectedIndex == MenuOptions::ChangeHostIPAddress) {
					runIPAddressPrompt();
					continue;
				}
				else if(selectedIndex == MenuOptions::Quit) {
					Utilities::clear();

					printf("Goodbye!\n");
					printf("\n");

					return;
				}
			}
		}

		if(!valid) {
			Utilities::clear();
			printf("Invalid selection!\n\n");
			Utilities::pause();
		}
	}
}

void Launcher::runGameTypePrompt(const QString & args) {
	if(!m_initialized) { return; }

	bool valid = false;
	QTextStream in(stdin);
	QString input, data, formattedData;
	int value = -1;
	int cancel = -1;
	QString trimmedArgs = args.trimmed();
	bool skipInput = !trimmedArgs.isEmpty();
	GameTypes::GameType gameType = GameTypes::Invalid;

	static const QRegExp integerRegExp("^[0-9]+$");
	static const QRegExp  cancelRegExp("^(a(bort)?)|(b(ack)?)|(c(ancel)?)$");
	static const QRegExp    helpRegExp("^(\\?|h(elp)?)$");

	while(true) {
		Utilities::clear();

		if(skipInput) {
			data = trimmedArgs;
			skipInput = false;
		}
		else {
			printf("Current game type is set to: \"%s\" (default: \"%s\")\n\n", GameTypes::toString(SettingsManager::getInstance()->gameType), GameTypes::toString(SettingsManager::getInstance()->defaultGameType));
			printf("Choose a game type:\n");

			for(int i=static_cast<int>(GameTypes::Invalid) + 1;i<static_cast<int>(GameTypes::NumberOfGameTypes);i++) {
				printf("%d: %s\n", i, GameTypes::gameTypeStrings[i]);

				cancel = i + 1;
			}

			printf("%d: Cancel\n", cancel);

			printf("> ");

			input = in.readLine();
			data = input.trimmed();
			formattedData = data.toLower();

			printf("\n");

			if(cancelRegExp.exactMatch(formattedData)) {
				break;
			}
			else if(helpRegExp.exactMatch(formattedData)) {
				Utilities::clear();

				printf(" [a]bort - returns to previous menu.\n");
				printf("  [b]ack - returns to previous menu.\n");
				printf("[c]ancel - returns to previous menu.\n");
				printf("  [h]elp - displays this help message.\n");
				printf("       ? - displays this help message.\n");
				printf("\n");

				Utilities::pause();

				continue;
			}
		}

		gameType = GameTypes::Invalid;

		if(data.length() > 0) {
			gameType = GameTypes::parseFrom(data);
			if(!GameTypes::isValid(gameType)) {
				if(!trimmedArgs.isEmpty()) {
					trimmedArgs.clear();
				}
				else if(integerRegExp.exactMatch(data)) {
					value = data.toInt(&valid, 10);
					if(valid) {
						if(value == cancel) {
							break;
						}
						else if(GameTypes::isValid(value)) {
							gameType = static_cast<GameTypes::GameType>(value);
						}
					}
				}
			}
		}
		
		if(GameTypes::isValid(gameType)) {
			printf("Changing game type from \"%s\" to \"%s\".\n\n", GameTypes::toString(SettingsManager::getInstance()->gameType), GameTypes::toString(gameType));

			setGameType(gameType);

			Utilities::pause();

			break;
		}
		else {
			QByteArray dataBytes = data.toLocal8Bit();

			printf("Invalid game type: %s\n\n", dataBytes.data());

			Utilities::pause();
		}
	}
}

void Launcher::runModePrompt(const QString & args) {
	if(!m_initialized) { return; }

	bool valid = false;
	QTextStream in(stdin);
	QString input, data, formattedData;
	int value = -1;
	int cancel = -1;
	QString trimmedArgs = args.trimmed();
	bool skipInput = !trimmedArgs.isEmpty();
	LauncherModes::LauncherMode mode = LauncherModes::Invalid;

	static const QRegExp integerRegExp("^[0-9]+$");
	static const QRegExp  cancelRegExp("^(a(bort)?)|(b(ack)?)|(c(ancel)?)$");
	static const QRegExp    helpRegExp("^(\\?|h(elp)?)$");

	while(true) {
		Utilities::clear();

		if(skipInput) {
			data = trimmedArgs;
			skipInput = false;
		}
		else {
			printf("Current launch mode is set to: \"%s\" (default: \"%s\")\n\n", LauncherModes::toString(SettingsManager::getInstance()->launcherMode), LauncherModes::toString(SettingsManager::getInstance()->defaultLauncherMode));
			printf("Choose a game launch mode:\n");

			for(int i=static_cast<int>(LauncherModes::Invalid) + 1;i<static_cast<int>(LauncherModes::NumberOfModes);i++) {
				printf("%d: %s\n", i, LauncherModes::modeStrings[i]);

				cancel = i + 1;
			}

			printf("%d: Cancel\n", cancel);

			printf("> ");

			input = in.readLine();
			data = input.trimmed();
			formattedData = data.toLower();

			printf("\n");

			if(cancelRegExp.exactMatch(formattedData)) {
				break;
			}
			else if(helpRegExp.exactMatch(formattedData)) {
				Utilities::clear();

				printf(" [a]bort - returns to previous menu.\n");
				printf("  [b]ack - returns to previous menu.\n");
				printf("[c]ancel - returns to previous menu.\n");
				printf("  [h]elp - displays this help message.\n");
				printf("       ? - displays this help message.\n");
				printf("\n");

				Utilities::pause();

				continue;
			}
		}

		mode = LauncherModes::Invalid;

		if(data.length() > 0) {
			mode = LauncherModes::parseFrom(data);
			if(!LauncherModes::isValid(mode)) {
				if(!trimmedArgs.isEmpty()) {
					trimmedArgs.clear();
				}
				else if(integerRegExp.exactMatch(data)) {
					value = data.toInt(&valid, 10);
					if(valid) {
						if(value == cancel) {
							break;
						}
						else if(LauncherModes::isValid(value)) {
							mode = static_cast<LauncherModes::LauncherMode>(value);
						}
					}
				}
			}
		}
		
		if(LauncherModes::isValid(mode)) {
			printf("Changing game launch mode from \"%s\" to \"%s\".\n\n", LauncherModes::toString(SettingsManager::getInstance()->launcherMode), LauncherModes::toString(mode));

			setMode(mode);

			Utilities::pause();

			break;
		}
		else {
			QByteArray dataBytes = data.toLocal8Bit();

			printf("Invalid game launch mode: %s\n\n", dataBytes.data());

			Utilities::pause();
		}
	}
}

void Launcher::runIPAddressPrompt(const QString & args) {
	if(!m_initialized) { return; }

	bool valid = false;
	QTextStream in(stdin);
	QString input, data, formattedData;
	QString trimmedArgs = args.trimmed();
	bool skipInput = !trimmedArgs.isEmpty();

	static const QRegExp cancelRegExp("^(a(bort)?)|(b(ack)?)|(c(ancel)?)$");
	static const QRegExp   helpRegExp("^(\\?|h(elp)?)$");

	while(true) {
		Utilities::clear();

		if(skipInput) {
			data = trimmedArgs;
			skipInput = false;
		}
		else {
			printf("Enter host IP Address:\n");
			printf("> ");

			input = in.readLine();
			data = input.trimmed();
			formattedData = data.toLower();

			printf("\n");
		}

		if(cancelRegExp.exactMatch(data)) {
			return;
		}
		else if(helpRegExp.exactMatch(data)) {
			Utilities::clear();

			printf(" [a]bort - returns to previous menu.\n");
			printf("  [b]ack - returns to previous menu.\n");
			printf("[c]ancel - returns to previous menu.\n");
			printf("  [h]elp - displays this help message.\n");
			printf("       ? - displays this help message.\n");
			printf("\n");

			Utilities::pause();

			continue;
		}

		valid = true;

		if(data.length() == 0) { valid = false; }

		for(int i=0;i<data.length();i++) {
			if(data[i] == ' ' || data[i] == '\t') {
				valid = false;
			}
		}

		QByteArray dataBytes = data.toLocal8Bit();
		if(valid) {
			if(SettingsManager::getInstance()->serverIPAddress != NULL) { delete [] SettingsManager::getInstance()->serverIPAddress; }
			SettingsManager::getInstance()->serverIPAddress = Utilities::copyString(dataBytes.data());

			printf("Host IP Address changed to: %s\n\n", dataBytes.data());

			Utilities::pause();

			break;
		}
		else {
			printf("Invalid IP Address: %s\n\n", dataBytes.data());

			Utilities::pause();
		}
	}
}

bool Launcher::runGame(const ArgumentParser * args) {
	if(!m_initialized) { return false; }

	Script script;

	if(!updateScriptArgs()) {
		return false;
	}

	if(m_mode == LauncherModes::DOSBox) {
		bool scriptLoaded = false;
		const char * scriptFileName;

		if(m_gameType == GameTypes::Game) {
			scriptLoaded = script.readFrom(SettingsManager::getInstance()->DOSBoxGameScriptFileName);

			scriptFileName = SettingsManager::getInstance()->DOSBoxGameScriptFileName;
		}
		else if(m_gameType == GameTypes::SetupSound) {
			scriptLoaded = script.readFrom(SettingsManager::getInstance()->DOSBoxSetupSoundScriptFileName);

			scriptFileName = SettingsManager::getInstance()->DOSBoxSetupSoundScriptFileName;
		}
		else if(m_gameType == GameTypes::SetupVideo) {
			scriptLoaded = script.readFrom(SettingsManager::getInstance()->DOSBoxSetupVideoScriptFileName);

			scriptFileName = SettingsManager::getInstance()->DOSBoxSetupVideoScriptFileName;
		}
		else if(m_gameType == GameTypes::Client) {
			scriptLoaded = script.readFrom(SettingsManager::getInstance()->DOSBoxClientScriptFileName);

			scriptFileName = SettingsManager::getInstance()->DOSBoxClientScriptFileName;
		}
		else if(m_gameType == GameTypes::Server) {
			scriptLoaded = script.readFrom(SettingsManager::getInstance()->DOSBoxServerScriptFileName);

			scriptFileName = SettingsManager::getInstance()->DOSBoxServerScriptFileName;
		}
		else {	
			return false;
		}

		if(!scriptLoaded) {
			printf("Failed to load DOSBox script file: %s\n", scriptFileName);
			return false;
		}

		QString DOSBoxCommand = script.generateDOSBoxCommand(m_scriptArgs);
		QByteArray DOSBoxCommandBytes = DOSBoxCommand.toLocal8Bit();

#if _DEBUG
		printf("%s\n\n", DOSBoxCommandBytes.data());
#endif // _DEBUG

		system(DOSBoxCommandBytes.data());
		
#if _DEBUG
			Utilities::pause();
#endif // _DEBUG
	}
	else if(m_mode == LauncherModes::Windows) {
		bool scriptLoaded = false;
		const char * scriptFileName;

		if(m_gameType == GameTypes::Game || m_gameType == GameTypes::Client || m_gameType == GameTypes::Server) {
			scriptLoaded = script.readFrom(SettingsManager::getInstance()->windowsGameScriptFileName);

			scriptFileName = SettingsManager::getInstance()->windowsGameScriptFileName;
		}
		else if(m_gameType == GameTypes::SetupSound) {
			scriptLoaded = script.readFrom(SettingsManager::getInstance()->windowsSetupSoundScriptFileName);

			scriptFileName = SettingsManager::getInstance()->windowsSetupSoundScriptFileName;
		}
		else if(m_gameType == GameTypes::SetupVideo) {
			scriptLoaded = script.readFrom(SettingsManager::getInstance()->windowsSetupVideoScriptFileName);

			scriptFileName = SettingsManager::getInstance()->windowsSetupVideoScriptFileName;
		}
		else {
			return false;
		}

		if(!scriptLoaded) {
			printf("Failed to load Windows script file: %s\n", scriptFileName);
			return false;
		}

		for(int i=0;i<script.numberOfCommands();i++) {
			QString windowsCommand = script.generateWindowsCommand(m_scriptArgs, i);
			QByteArray windowsCommandBytes = windowsCommand.toLocal8Bit();

#if _DEBUG
			printf("%s\n\n", windowsCommandBytes.data());
#endif // _DEBUG

			system(windowsCommandBytes.data());

#if _DEBUG
			Utilities::pause();
#endif // _DEBUG
		}
	}

	return true;
}

bool Launcher::updateScriptArgs() {
	if(!m_initialized) { return false; }

	if(Utilities::stringLength(SettingsManager::getInstance()->gamePath) > 0 && Utilities::compareStrings(SettingsManager::getInstance()->gamePath, ".") != 0) {
		m_scriptArgs.setArgument("GAMEPATH", SettingsManager::getInstance()->gamePath);
	}
	m_scriptArgs.setArgument("Z", SettingsManager::getInstance()->gameFileName);
	m_scriptArgs.setArgument("ISOPATH", Utilities::generateFullPath(SettingsManager::getInstance()->CDISOPath, SettingsManager::getInstance()->CDISOFileName));
	m_scriptArgs.setArgument("SETSOUND", SettingsManager::getInstance()->setupSoundFileName);
	m_scriptArgs.setArgument("SETVIDEO", SettingsManager::getInstance()->setupVideoFileName);
	m_scriptArgs.setArgument("IP", SettingsManager::getInstance()->serverIPAddress);

	return true;
}

bool Launcher::handleArguments(const ArgumentParser * args, bool start) {
	if(args != NULL) {
		if(args->hasArgument("m")) {
			LauncherModes::LauncherMode newMode = LauncherModes::parseFrom(args->getValue("m"));
			
			if(isValid(newMode)) {
				m_mode = newMode;
			}
			else {
				printf("Invalid mode argument, please specify one of the following: %s / %s\n", LauncherModes::toString(LauncherModes::DOSBox), LauncherModes::toString(LauncherModes::Windows));
				return false;
			}
		}

		if(args->hasArgument("t")) {
			GameTypes::GameType newGameType = GameTypes::parseFrom(args->getValue("t"));

			if(isValid(newGameType)) {
				m_gameType = newGameType;

				printf("Setting game type to: %s\n", GameTypes::toString(m_gameType));

				if(m_gameType == GameTypes::Client) {
					QString ipAddress;

					if(args->hasArgument("ip")) {
						ipAddress = args->getValue("ip").trimmed();

						bool valid = true;
						for(int i=0;i<ipAddress.length();i++) {
							if(ipAddress[i] == ' ' || ipAddress[i] == '\t') {
								valid = false;
							}
						}

						if(ipAddress.length() == 0) { valid = false; }

						QByteArray ipAddressBytes = ipAddress.toLocal8Bit();

						if(valid) {
							if(SettingsManager::getInstance()->serverIPAddress != NULL) { delete [] SettingsManager::getInstance()->serverIPAddress; }
							SettingsManager::getInstance()->serverIPAddress = Utilities::copyString(ipAddressBytes.data());
						}
						else {
							printf("\nInvalid IP Address entered in arguments: %s\n\n", ipAddressBytes.data());

							runIPAddressPrompt();
						}
					}
				}
			}
			else {
				printf("Invalid game type, please specify one of the following: %s / %s / %s / %s\n", GameTypes::toString(GameTypes::Game), GameTypes::toString(GameTypes::SetupSound), GameTypes::toString(GameTypes::SetupVideo), GameTypes::toString(GameTypes::Client), GameTypes::toString(GameTypes::Server));
				return false;
			}
		}
	}
	
	if(start) {
		run();
	}

	return true;
}

int Launcher::checkForMissingExecutables() {
	int numberOfMissingExecutables = 0;

	QString fullDOSBoxExePath = Utilities::generateFullPath(SettingsManager::getInstance()->DOSBoxPath, SettingsManager::getInstance()->DOSBoxFileName);
	QString fullGameExePath = Utilities::generateFullPath(SettingsManager::getInstance()->gamePath, SettingsManager::getInstance()->gameFileName);
	QString fullSetupSoundExePath = Utilities::generateFullPath(SettingsManager::getInstance()->gamePath, SettingsManager::getInstance()->setupSoundFileName);
	QString fullSetupVideoExePath = Utilities::generateFullPath(SettingsManager::getInstance()->gamePath, SettingsManager::getInstance()->setupVideoFileName);
	QString fullCDISOPath = Utilities::generateFullPath(SettingsManager::getInstance()->CDISOPath, SettingsManager::getInstance()->CDISOFileName);

	QFileInfo DOSBoxExe(fullDOSBoxExePath);
	QFileInfo gameExe(fullGameExePath);
	QFileInfo setupSoundExe(fullSetupSoundExePath);
	QFileInfo setupVideoExe(fullSetupVideoExePath);
	QFileInfo gameCDISO(fullCDISOPath);

	if(!DOSBoxExe.isFile() || !DOSBoxExe.exists()) {
		numberOfMissingExecutables++;
		QByteArray fullDOSBoxExePathBytes = fullDOSBoxExePath.toLocal8Bit();
		printf("Missing DOSBox executable: %s\n", fullDOSBoxExePathBytes.data());
	}

	if(!gameExe.isFile() || !gameExe.exists()) {
		numberOfMissingExecutables++;
		QByteArray fullGameExePathBytes = fullGameExePath.toLocal8Bit();
		printf("Missing game executable: %s\n", fullGameExePathBytes.data());
	}

	if(!setupSoundExe.isFile() || !setupSoundExe.exists()) {
		numberOfMissingExecutables++;
		QByteArray fullSetupSoundExePathBytes = fullSetupSoundExePath.toLocal8Bit();
		printf("Missing sound setup executable: %s\n", fullSetupSoundExePathBytes.data());
	}

	if(!setupVideoExe.isFile() || !setupVideoExe.exists()) {
		numberOfMissingExecutables++;
		QByteArray fullSetupVideoExePathBytes = fullSetupVideoExePath.toLocal8Bit();
		printf("Missing video setup executable: %s\n", fullSetupVideoExePathBytes.data());
	}

	if(!gameCDISO.isFile() || !gameCDISO.exists()) {
		numberOfMissingExecutables++;
		QByteArray fullCDISOPathBytes = fullCDISOPath.toLocal8Bit();
		printf("Missing game CD ISO: %s\n", fullCDISOPathBytes.data());
	}

	return numberOfMissingExecutables++;
}

void Launcher::displayArgumentHelp() {
	printf("Z Launcher arguments:\n");
	printf(" -f \"Settings.ini\" - specifies an alternate settings file to use.\n");
	printf(" -m DOSBox/Windows - specifies mod manager mode, default: DOSBox.\n");
	printf(" -t Game/Setup Sound/Setup Video/Client/Server - specifies game type, default: Game.\n");
	printf(" -ip 127.0.0.1 - specifies host ip address if running in client mode.\n");
	printf(" -? - displays this help message.\n");
}

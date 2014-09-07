#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include "Utilities/Utilities.h"

namespace MenuOptions {
	enum MenuOption {
		Invalid,
		LaunchGame,
		LaunchClient,
		LaunchServer,
		SoundSetup,
		VideoSetup,
		ChangeGameType,
		ChangeLauncherMode,
		ChangeHostIPAddress,
		Quit,
		NumberOfOptions
	};
	
	extern const char * optionStrings[];
	extern const MenuOption defaultOption;
	
	bool isValid(int option);
	bool isValid(MenuOption option);
	const char * toString(MenuOption option);
	const char * toString(int option);
	MenuOption parseFrom(const char * data);
	MenuOption parseFrom(const QString & data);
}

#endif // MENU_OPTIONS_H

#include "Launcher/MenuOptions.h"

const char * MenuOptions::optionStrings[] = { "Launch Game", "Launch Client", "Launch Server", "Sound Setup", "Video Setup", "Change Game Type", "Change Launcher Mode", "Change Host IP Address", "Change Port", "Quit" };
const MenuOptions::MenuOption MenuOptions::defaultOption = MenuOptions::LaunchGame;

bool MenuOptions::isValid(MenuOption option) {
	return option > Invalid && option < NumberOfOptions;
}

bool MenuOptions::isValid(int option) {
	return option > static_cast<int>(Invalid) && option < static_cast<int>(NumberOfOptions);
}

const char * MenuOptions::toString(MenuOption option) {
	return toString(static_cast<int>(option));
}

const char * MenuOptions::toString(int option) {
	if(!isValid(option)) { return "Invalid"; }

	return optionStrings[option];
}

MenuOptions::MenuOption MenuOptions::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	MenuOption option = Invalid;

	char * optionString = Utilities::trimCopyString(data);

	for(int i=0;i<static_cast<int>(NumberOfOptions);i++) {
		if(Utilities::compareStringsIgnoreCase(optionString, optionStrings[i]) == 0) {
			option = static_cast<MenuOption>(i);
			break;
		}
	}

	delete [] optionString;

	return option;
}

MenuOptions::MenuOption MenuOptions::parseFrom(const QString & data) {
	QByteArray dataBytes = data.toLocal8Bit();
	return parseFrom(dataBytes.data());
}

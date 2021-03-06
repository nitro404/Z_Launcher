#include "Launcher/LauncherMode.h"

const char * LauncherModes::modeStrings[] = { "DOSBox", "Windows" };
const LauncherModes::LauncherMode LauncherModes::defaultMode = LauncherModes::DOSBox;

bool LauncherModes::isValid(LauncherMode mode) {
	return mode > Invalid && mode < NumberOfModes;
}

bool LauncherModes::isValid(int mode) {
	return mode > static_cast<int>(Invalid) && mode < static_cast<int>(NumberOfModes);
}

const char * LauncherModes::toString(LauncherMode mode) {
	return toString(static_cast<int>(mode));
}

const char * LauncherModes::toString(int mode) {
	if(!isValid(mode)) { return "Invalid"; }

	return modeStrings[mode];
}

LauncherModes::LauncherMode LauncherModes::parseFrom(const char * data) {
	if(data == NULL) { return Invalid; }

	LauncherMode mode = Invalid;

	char * modeString = Utilities::trimCopyString(data);

	for(int i=0;i<static_cast<int>(NumberOfModes);i++) {
		if(Utilities::compareStringsIgnoreCase(modeString, modeStrings[i]) == 0) {
			mode = static_cast<LauncherMode>(i);
			break;
		}
	}

	delete [] modeString;

	return mode;
}

LauncherModes::LauncherMode LauncherModes::parseFrom(const QString & data) {
	QByteArray dataBytes = data.toLocal8Bit();
	return parseFrom(dataBytes.data());
}

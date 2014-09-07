#ifndef LAUNCHER_MODE_H
#define LAUNCHER_MODE_H

#include "Utilities/Utilities.h"

namespace LauncherModes {
	enum LauncherMode {
		Invalid,
		DOSBox,
		Windows,
		NumberOfModes
	};
	
	extern const char * modeStrings[];
	extern const LauncherMode defaultMode;
	
	bool isValid(int mode);
	bool isValid(LauncherMode mode);
	const char * toString(LauncherMode mode);
	const char * toString(int mode);
	LauncherMode parseFrom(const char * data);
	LauncherMode parseFrom(const QString & data);
}

#endif // LAUNCHER_MODE_H

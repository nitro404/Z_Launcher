#include "Launcher/Launcher.h"

int main(int argc, char * argv[]) {
	Launcher launcher;

	launcher.init(argc, argv);

	launcher.uninit();
	
	return 0;
}

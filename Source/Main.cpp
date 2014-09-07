#include "Launcher/Launcher.h"

#if _DEBUG
#include <vld.h>
#endif // _DEBUG

int main(int argc, char * argv[]) {
	Launcher launcher;

	launcher.init(argc, argv);

	launcher.uninit();
	
	return 0;
}

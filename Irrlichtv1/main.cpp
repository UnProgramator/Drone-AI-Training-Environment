#include <irrlicht.h>
#include <iostream>
#include <string>

#include "GraphicsManager.h"

namespace alex_example {
	namespace fst_example{
		extern int main();
	}
	namespace snd_example {
		extern int main();
	}
}

int main() {
	return alex_example::fst_example::main();
}



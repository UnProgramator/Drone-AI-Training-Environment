#include <irrlicht.h>
#include <iostream>
#include <string>

#include "GraphicsManager.h"
#include "Main.h"




int main() {
	try {
		Main main_f;
		main_f.init_with_defaults();
		return main_f.main_loop(false);
	}
	catch (std::exception e) {
		e.what();
	}
}



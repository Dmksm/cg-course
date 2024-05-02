#include "../libgl/GdiPlusInitializer.h"
#include "MyApplication.h"
#include "common_inc.h"

CMyApplication app("Texture mapping", 800, 600);
CGdiPlusInitializer gdiplusInitializer;

int main()
{
	app.MainLoop();
	return 0;
}

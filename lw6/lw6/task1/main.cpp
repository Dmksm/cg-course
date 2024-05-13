#include "../libgl/GdiPlusInitializer.h"
#include "MyApplication.h"
#include "common_inc.h"

CMyApplication app("3ds Model", 1200, 900);
CGdiPlusInitializer gdiplusInitializer;

int main()
{
	app.MainLoop();
	return 0;
}

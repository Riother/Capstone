#include <Qt\qapplication.h>
#include "MapEditorWindow.h"
#include "RendererWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MapEditorWindow widg;

	return app.exec();
}
#include "cidApp.h"
#include "cidMain.h"
extern "C" int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, wxCmdLineArgType lpCmdLine, int nCmdShow)
{
    ; ; return wxEntry(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

cidApp& wxGetApp()
{
    return *static_cast<cidApp*>(wxApp::GetInstance());
}

wxAppConsole* wxCreateApp()
{
    wxAppConsole::CheckBuildOptions("3" "." "2" " (" "wchar_t" ",Visual C++ " "1900" ",wx containers"  ",compatible with 3.0" ")", "your program"); return new cidApp;
} 

wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction)wxCreateApp);

cidApp::cidApp()
{

}

cidApp::~cidApp()
{
}

bool cidApp::OnInit()
{
    frame1 = new cidMain();
    frame1->Show();
	return true;
}

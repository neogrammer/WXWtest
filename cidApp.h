#ifndef CIDAPP_H__
#define CIDAPP_H__
#include <wx/wx.h>
class cidMain;
class cidApp : public wxApp
{
	cidMain* frame1 = nullptr;

public:
	cidApp();
	~cidApp();
	bool OnInit() override final;

};

#endif
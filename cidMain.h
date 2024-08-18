#ifndef CIDMAIN_H__
#define CIDMAIN_H__
#include <wx/wx.h>
#include "Game.h"

class cidMain : public wxFrame
{
	Game game;

public:
	cidMain();
	~cidMain();

	wxButton* joinBtn = nullptr;
	wxButton* exitBtn = nullptr;
	wxTextCtrl* ipTextCtrl = nullptr;
	//wxListBox* list1 = nullptr;

	void OnJoinButtonClicked(wxCommandEvent& evt);
	void OnExitButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

#endif

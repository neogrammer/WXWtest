#include "cidMain.h"


wxBEGIN_EVENT_TABLE(cidMain, wxFrame)
	EVT_BUTTON(10001, OnJoinButtonClicked)
	EVT_BUTTON(10002, OnExitButtonClicked)

wxEND_EVENT_TABLE()

cidMain::cidMain() : wxFrame{ nullptr, wxID_ANY, "Cid GUI App", wxPoint{200, 50}, wxSize{1600,900} }
, game{}
{
	joinBtn = new wxButton(this, 10001, "Join");
	exitBtn = new wxButton(this, 10002, "Exit");
	ipTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint{ wxDefaultPosition }, wxSize{400, 40});
	
	wxBoxSizer* grid = new wxBoxSizer(wxVERTICAL);
	grid->Add(0, 300, wxEXPAND | wxALL, 0);
	grid->Add(ipTextCtrl, 0, wxALIGN_CENTER | wxALL, 0);
	grid->Add(0, 80, wxEXPAND | wxALL, 0);

	grid->Add(joinBtn, 0, wxALIGN_CENTER | wxALL, 0);
	grid->Add(0, 120, wxEXPAND | wxALL, 0);

	grid->Add(exitBtn, 0, wxALIGN_CENTER | wxALL, 0);
	grid->Add(0, 300, wxEXPAND | wxALL, 0);


	this->SetSizer(grid);
	grid->Layout();
}

cidMain::~cidMain()
{

}

void cidMain::OnJoinButtonClicked(wxCommandEvent& evt)
{
	std::string ipAddress = ipTextCtrl->GetValue().ToStdString();
	evt.Skip();
	if (game.init(ipAddress))
	{
		this->Hide();
		game.run();
		game.runCheckConns();
		this->Show();
	
	} // else let calling go back
}


void cidMain::OnExitButtonClicked(wxCommandEvent& evt)
{
	wxExit();
	evt.Skip();
}


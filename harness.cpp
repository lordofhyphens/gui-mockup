// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
//
// Included to provide a experimentation harness for UI elements.
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "OptionsGroup.hpp"
#include "log.hpp"
class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};
enum
{
    ID_Hello = 1
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello,   MyFrame::OnHello)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Hello World", wxPoint(50, 50), wxSize(450, 340) );
    frame->Show( true );
    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    Slic3r::OptionsGroup t = Slic3r::OptionsGroup(this, "Test!");
    t.create_single_option_line(Slic3r::Option(1, Slic3r::FieldTypes::TEXT, wxString(""), "Text field", "This is a generic text field", false));

    // create the Option item ahead of time for a combo field so we can populate it.
    Slic3r::Option cbox = Slic3r::Option(2, Slic3r::FieldTypes::SELECT, wxString(""), "Combo field", "This is a generic text field", false);
    cbox.labels.push_back("Item1");
    cbox.labels.push_back("Item2");
    cbox.labels.push_back("Item3");
    // make a line for it
    t.create_single_option_line(cbox);
    wxMenu *menuFile = new wxMenu;
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    // create text ctrl with minimal size 100x60
    sizer->Add(t.sizer());
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );

    SetMenuBar( menuBar );
    CreateStatusBar();
    SetSizerAndFit(sizer);
    SetStatusText( "Welcome to wxWidgets!" );
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}


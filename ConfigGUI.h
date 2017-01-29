
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <boost/any.hpp>

// Base class to encapsulate a sizer for a set of controls, a tooltip, and
// a label.
class GUIItem {
public:
    virtual boost::any value() = 0;
    virtual wxSizer* sizer() = 0;
};

class TextBoxItem : public GUIItem {
private:
    std::string _text;
    wxFrame* _parent;
    wxBoxSizer *_sizer;
public:
    TextBoxItem(wxFrame* parent, std::string label, std::string default_text = "", const wxSize & size = wxDefaultSize) : 
        _text(default_text), 
        _sizer(new wxBoxSizer(wxHORIZONTAL)),
        _parent(parent)
    { 
        _sizer->Add(new wxStaticText( _parent, -1, label));
        _sizer->Add(new wxTextCtrl( _parent, -1, default_text, wxDefaultPosition, size ));
    }
    wxSizer* sizer() { return _sizer;}
    boost::any value() {
        return boost::any(_text);
    }
};

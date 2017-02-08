// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/combobox.h>

#include <boost/any.hpp>
#include <memory>
#include <iostream>

// Base class to encapsulate a sizer for a set of controls, a tooltip, and
// a label.
// General implementation note: wxWidgets sizers clean up their child controls when they are destroyed, 
// so this just needs to instantiate new wx objects on the heap and make sure they get assigned to a parent.
class GUIItem 
{
protected:
    wxBoxSizer* _sizer;
    wxFrame* _parent;
    bool _readonly;
public:
    // Generic function to retrieve 
    virtual boost::any value() = 0;

    wxSizer* sizer() { return _sizer;}
    wxFrame* parent(wxFrame* parent) { _parent = parent; return _parent; }

    GUIItem() : 
        _parent(nullptr),
        _sizer(new  wxBoxSizer(wxHORIZONTAL)),
        _readonly(false) {}

    GUIItem(wxFrame* parent, bool readonly=false) : 
        _parent(parent),
        _sizer(new wxBoxSizer(wxHORIZONTAL)),
        _readonly(readonly) {}
    ~GUIItem()
    {
        // Deletion is only necessary if the child isn't assigned a parent
        if (_parent == nullptr) delete _sizer;
    }
};

class TextBoxItem : public GUIItem 
{
private:
    // local reference in case we need to use it relative to this object (instead of digging through Sizer)
    wxTextCtrl* _text;
public:
    TextBoxItem(wxFrame* parent, std::string label, std::string default_text = "", const wxSize & size = wxDefaultSize) : 
        GUIItem(parent)
    { 
        _text = new wxTextCtrl( _parent, -1, _(default_text), wxDefaultPosition, size );
        _sizer->Add(new wxStaticText(_parent, -1, label));
        _sizer->Add(_text);
    }
    boost::any value() 
    {
        return boost::any(_text);
    }
};

// Single-select combobox
class ComboItem : public GUIItem
{
private: 
    wxComboBox* combo;
public:
    ComboItem(wxFrame* parent, wxString label, std::vector<wxString> choices, wxSize minimum_size = wxDefaultSize, wxString initial = "" , bool readonly = false, bool sorted = false) : 
        GUIItem(parent)
    {
        wxArrayString tmpStrings; 
        for (auto choice : choices ) { tmpStrings.Add(choice);}
        combo = new wxComboBox(_parent, -1, initial, wxDefaultPosition, minimum_size, tmpStrings, 
            (readonly ? wxCB_READONLY : (sorted ? wxCB_SORT : wxCB_DROPDOWN)));
        _sizer->Add(new wxStaticText(_parent, -1, label));
        _sizer->Add(combo);
    }
    boost::any value()
    {
        return boost::any(combo->GetValue());
    }
};

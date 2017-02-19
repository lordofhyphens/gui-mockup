#ifndef FIELD_HPP
#define FIELD_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include<functional>
#include "Option.hpp"

namespace Slic3r {
enum class FieldTypes;
class Option;

class Field {
protected:
    wxSizer* _sizer;
    wxWindow* _window;
    wxFrame* _parent;
    // Factory function, to be implemented in children
    virtual void BUILD() = 0;
    // copy of the underlying function for reference
    const Option opt; 
public:
    std::function<void(wxCommandEvent&)> _on_change;
    std::function<void(wxCommandEvent&)> _on_kill_focus;
    // used if we need to know which OptionType this corresponds.
    const FieldTypes type;
    Field() : opt(Option()), type(FieldTypes::DEFAULT), _on_change(nullptr), _on_kill_focus(nullptr){}
    Field(const Option& opt) : opt(opt), type(opt.gui_type) { }
    Field(wxFrame* parent, const Option& opt) : opt(opt), type(opt.gui_type), _parent(parent) { }
    wxSizer* sizer() { return _sizer; }
    wxWindow* window() { return _window; }


    // 
    bool has_sizer() { return _sizer != nullptr; }
    bool has_window() { return _window != nullptr; }

    // subclasses should overload with a specific version
    virtual void set_value(boost::any value) = 0;
    virtual boost::any get_value() = 0;

    virtual void enable() = 0;
    virtual void disable() = 0;

};

class TextCtrl : public Field {
protected:
    void BUILD();
public:
    TextCtrl();
    TextCtrl(wxFrame* parent, const Option& opt) : Field(parent, opt) { BUILD(); };

    void set_value(std::string value) { 
            dynamic_cast<wxTextCtrl*>(_window)->SetValue(wxString(value));
    }
    void set_value(boost::any value) { 
        try {
            dynamic_cast<wxTextCtrl*>(_window)->SetValue(boost::any_cast<wxString>(value));
        } catch (boost::bad_any_cast) {
            // TODO Log error and do nothing
        }
    }
    boost::any get_value() { return boost::any(dynamic_cast<wxTextCtrl*>(_window)->GetValue()); }
    
    void enable() { dynamic_cast<wxTextCtrl*>(_window)->Enable(); dynamic_cast<wxTextCtrl*>(_window)->SetEditable(1); }
    void disable() { dynamic_cast<wxTextCtrl*>(_window)->Disable(); dynamic_cast<wxTextCtrl*>(_window)->SetEditable(0); }
    void __on_change(wxCommandEvent&);
    
};

}
#endif

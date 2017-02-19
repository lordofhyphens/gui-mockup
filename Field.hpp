#ifndef FIELD_HPP
#define FIELD_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "Option.hpp"

namespace Slic3r {
enum class FieldTypes;
class Option;

class Field {
protected:
    wxSizer* _sizer;
    wxWindow* _window;
    wxFrame* _parent;
    boost::any _value;
    virtual void BUILD() = 0;
    const Option opt; 
public:
    // used if we need to know which OptionType this corresponds.
    const FieldTypes type;
    Field() : opt(Option()), type(FieldTypes::DEFAULT) {}
    Field(const Option& opt) : opt(opt), type(opt.gui_type) { }
    Field(wxFrame* parent, const Option& opt) : opt(opt), type(opt.gui_type), _parent(parent) { }
    wxSizer* sizer() { return _sizer; }
    wxWindow* window() { return _window; }

    bool has_sizer() { return _sizer != nullptr; }
    bool has_window() { return _window != nullptr; }
    // subclasses should overload with a specific version
    void set_value(boost::any value) { _value = value;}
    boost::any get_value(boost::any value) { return _value; }

};

class TextCtrl : public Field {
protected:
    void BUILD();
public:
    TextCtrl();
    TextCtrl(wxFrame* parent, const Option& opt) : Field(parent, opt) { BUILD(); };
    void set_value(std::string value) { _value = value; }

};

}
#endif

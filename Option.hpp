#ifndef OPTION_HPP
#define OPTION_HPP
#include <boost/any.hpp>
#include "Widget.hpp"

namespace Slic3r {

// Abstraction cribbed from Slic3r::OptionGroup::Option
// May recombine Field into this, with boost::any and runtime type checking 
// through that we avoid needing to subclass to handle everything.
//
// Enumeration of configuration and UI types. 
enum class FieldTypes { 
    DEFAULT,
    BOOLEAN, 
    INTEGER,
    COLOR, 
    SELECT, 
    SELECT_OPEN, 
    F_ENUM_OPEN, 
    I_ENUM_OPEN, 
    I_ENUM_CLOSED,
    POINT,
    SLIDER,
    FLOAT,
    F_TEXT,
    I_TEXT,
    TEXT
};
class Option {
private: 
    wxSize _size;
public:
    // required values
    size_t opt_id;
    FieldTypes type;
    boost::any default_value;
    FieldTypes gui_type;
    std::string gui_flags;
    wxString label;
    wxString sidetext;
    wxString tooltip;
    bool multiline;
    bool full_width;
    // width, height are optional and will alter _size
    boost::any min;
    boost::any max;
    std::vector<wxString> labels;
    std::vector<boost::any> values;
    bool readonly; // can we just pull a const version of the object?
    // define the default GUI input types based on the provided FieldType.
    FieldTypes default_type(FieldTypes in); 
    Widget side_widget;
    wxSize size() const { return _size; }
    Option(size_t opt_id, FieldTypes type, boost::any default_value, size_t width, size_t height, FieldTypes gui_type, std::string gui_flags, std::string label, std::string sidetext, std::string tooltip, bool multiline, bool full_width, boost::any min, boost::any max) :
    opt_id(opt_id),
    type(type),
    default_value(default_value),
    gui_flags(gui_flags),
    label(_(label)),
    sidetext(_(sidetext)),
    tooltip(_(tooltip)),
    multiline(multiline),
    full_width(full_width),
    min(min),
    max(max),
    _size(wxSize(width,height))
    {}

    Option(size_t opt_id, FieldTypes type, boost::any default_value, FieldTypes gui_type, std::string gui_flags, std::string label, std::string sidetext, std::string tooltip, bool multiline, bool full_width, boost::any min, boost::any max) :
    opt_id(opt_id),
    type(type),
    default_value(default_value),
    gui_flags(gui_flags),
    label(_(label)),
    sidetext(_(sidetext)),
    tooltip(_(tooltip)),
    multiline(multiline),
    full_width(full_width),
    min(min),
    max(max),
    _size(wxDefaultSize)
    {}
        
    Option(size_t opt_id, FieldTypes type, boost::any default_value, std::string label, std::string tooltip, bool full_width, boost::any min = boost::any(), boost::any max = boost::any()) :
    opt_id(opt_id),
    type(type),
    default_value(default_value),
    gui_flags(""),
    label(_(label)),
    sidetext(_("")),
    tooltip(_(tooltip)),
    multiline(false),
    full_width(full_width),
    min(min),
    max(max),
    _size(wxDefaultSize)
    {
        gui_type = default_type(type);
    }
    Option() :
    opt_id(0),
    type(FieldTypes::DEFAULT),
    default_value(0),
    gui_flags(""),
    label(_("")),
    sidetext(_("")),
    tooltip(_("")),
    multiline(false),
    full_width(false),
    min(0),
    max(0),
    _size(wxDefaultSize)
    { gui_type = default_type(type); }

};
}
#endif

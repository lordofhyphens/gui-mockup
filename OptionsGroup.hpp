#include <wx/wxprec.h>
#ifndef WX_PRECOM
#include <wx/wx.h>
#endif

#include <boost/any.hpp>

#include "Widget.hpp"
#include "Field.hpp"
namespace Slic3r {

class Line;
class Option;

// OptionsGroup building class, cribbed from Slic3r::OptionGroup
// Usage: Instantitate, add individual items to it, and add its sizer to another wxWidgets sizer.
class OptionsGroup {
    private:
        bool _disabled;
        wxFlexGridSizer* _grid_sizer;
        wxSizer* _sizer;
        void BUILD(); 
        const bool staticbox;
        wxFrame* parent;
        std::vector<boost::any> fields;
        Field* _build_field(const Option& opt);
    public:
        const wxString title;

        size_t label_width;
        wxFont label_font;
        wxFont sidetext_font;
        bool extra_column;


        OptionsGroup() : parent(nullptr), title(wxT("")), staticbox(1), fields(std::vector<boost::any>()){};
        OptionsGroup(wxFrame* parent, std::string title) : 
            parent(parent), 
            title(title.c_str()), 
            staticbox(1),
            extra_column(false),
            label_width(0),
            fields(std::vector<boost::any>())
            { BUILD(); }

        OptionsGroup(wxFrame*, std::string, size_t label_width) :
            parent(parent), 
            title(title.c_str()), 
            staticbox(1),
            extra_column(false),
            fields(std::vector<boost::any>()),
            label_width(label_width) { BUILD(); }

        void append_line(const Line& line);
        Line create_single_option_line();
        void append_single_option_line(const Line& line);

        void disable() { _disabled = true; }
        void enable() { _disabled = false; }
        wxSizer* sizer() { return _sizer; }
};

// Abstraction cribbed from Slic3r::OptionGroup::Line
// Unsure if templated class or function overloading is the appropriate thing here.
class Line {
private:
    std::vector<Option> _options;
    std::vector<Widget> _extra_widgets;
    Widget _widget;
    wxSizer* _sizer;
    wxString _tooltip;
public:
    wxString label;
    bool full_width;
    wxSizer* sizer() const { return _sizer; }
    Line(const Option& z) : _tooltip(wxT("")), _sizer(nullptr), full_width(false), _widget(Widget()) { append_option(z); }
    inline void append_option(const Option& z) { _options.push_back(z); };
    void append_widget(const Widget& wid) { _extra_widgets.push_back(wid); }
    std::vector<Option> options() const { return _options; }
    const std::vector<Widget> extra_widgets() const { return _extra_widgets; }
    bool has_sizer() const { return _sizer != nullptr; }
    bool has_widget() const { return _widget.valid(); }
    Widget widget() const { return _widget; }
    const wxString tooltip() const { return _tooltip; }
};


// Enumeration of configuration and UI types. 
enum FieldTypes { 
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


// Abstraction cribbed from Slic3r::OptionGroup::Option
// May recombine Field into this, with boost::any and runtime type checking 
// through that we avoid needing to subclass to handle everything.
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

};
}

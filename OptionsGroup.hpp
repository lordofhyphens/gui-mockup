#include <wx/wxprec.h>
#ifndef WX_PRECOM
#include <wx/wx.h>
#endif

#include <boost/any.hpp>

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

        void append_line(Line*);
        Line create_single_option_line();
        void append_single_option_line(Line*);

        void disable() { _disabled = true; }
        void enable() { _disabled = false; }
        wxSizer* sizer() { return _sizer; }
};

// Abstraction cribbed from Slic3r::OptionGroup::Line
// Unsure if templated class or function overloading is the appropriate thing here.
class Line {
private:
    std::vector<boost::any> extra_widgets;
    std::vector<Option> options;
    boost::any widget;
public:
        void append_option();
        void append_widget();
        std::vector<Option> get_options() { return options; }
        std::vector<boost::any> get_extra_widgets() { return extra_widgets; }
};


// Enumeration of UI types. 
enum FieldTypes { 
    BOOLEAN, 
    INTEGER,
    COLOR, 
    SELECT, 
    SELECT_OPEN, 
    F_ENUM_OPEN, 
    I_ENUM_OPEN, 
    I_ENUM_CLOSED,
    POINT,
    SLIDER
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
    boost::any side_widget;
    Option(size_t opt_id, FieldTypes type, boost::any default_value, FieldTypes gui_type, std::string gui_flags, std::string label, std::string sidetext, std::string tooltip, bool multiline, bool full_width, boost::any min, boost::any min) {}

};
}

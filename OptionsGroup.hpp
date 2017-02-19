#ifndef OPTIONSGROUP_HPP
#define OPTIONSGROUP_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOM
#include <wx/wx.h>
#endif

#include <boost/any.hpp>
#include <map>
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
        wxFrame* _parent;
        std::map<size_t, Field*> fields;
        Field* _build_field(const Option& opt);
    public:
        const wxString title;

        size_t label_width;
        wxFont label_font;
        wxFont sidetext_font;
        bool extra_column;

        OptionsGroup() : _parent(nullptr), title(wxT("")), staticbox(1), fields(std::map<size_t, Field*>()){};
        OptionsGroup(wxFrame* parent, std::string title) : 
            _parent(parent), 
            title(title.c_str()), 
            staticbox(1),
            extra_column(false),
            label_width(0),
            fields(std::map<size_t, Field*>())
            { BUILD(); }

        OptionsGroup(wxFrame* parent, std::string, size_t label_width) :
            _parent(parent), 
            title(title.c_str()), 
            staticbox(1),
            extra_column(false),
            fields(std::map<size_t, Field*>()),
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



}

#endif

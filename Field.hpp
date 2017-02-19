#ifndef FIELD_HPP
#define FIELD_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "OptionsGroup.hpp"

namespace Slic3r {
enum class FieldTypes;
class Field {
protected:
    wxSizer* _sizer;
    wxWindow* _window;
public:
    // used if we need to know which OptionType this corresponds.
    const FieldTypes type;
    wxSizer* sizer() { return _sizer; }
    wxWindow* window() { return _window; }

    bool has_sizer() { return _sizer != nullptr; }
    bool has_window() { return _window != nullptr; }
    // To be overridden, subclasses can (and should) overload 
    // and provide an accessor
    virtual void set_value(boost::any value) = 0;
    virtual boost::any get_value(boost::any value) = 0;

};
}
#endif

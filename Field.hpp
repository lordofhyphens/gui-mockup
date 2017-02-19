#ifndef FIELD_HPP
#define FIELD_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

namespace Slic3r {
class Field {
protected:
    wxSizer* _sizer;
public:
    Field() : _sizer(nullptr) { }
    wxSizer* sizer() { return _sizer; }
};
}
#endif

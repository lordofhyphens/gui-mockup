#include "Field.hpp"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

namespace Slic3r {

void TextCtrl::BUILD() {
    wxString default_value = "";
    // Empty wxString object fails cast, default to "" if 
    // the recast fails from boost::any.
    try {
        default_value = boost::any_cast<wxString>(opt.default_value);
    } catch (const boost::bad_any_cast& e) {
        //TODO log error with wxLog
    }
    wxTextCtrl* temp = new wxTextCtrl(_parent, opt.opt_id, default_value, wxDefaultPosition, opt.size(), (opt.multiline ? wxTE_MULTILINE : 0));

    _on_change = [=](wxCommandEvent& a) { this->__on_change(a);};

    // This replaces the generic EVT_TEXT call to set the table up, it works with function objects.
    temp->Bind(wxEVT_TEXT, _on_change, opt.opt_id);

    // recast as a wxWindow to fit the calling convention
    _window = dynamic_cast<wxWindow*>(temp);
}

// Fixed (temporary) function. We can (and probably should) use lambdas instead.
void TextCtrl::__on_change(wxCommandEvent& a) {
    printf("Calling _on_change for %d.\n", opt.opt_id);
}

}

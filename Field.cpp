#include "Field.hpp"


namespace Slic3r { namespace GUI {

    void TextCtrl::BUILD() {
        auto size = wxSize(wxDefaultSize);
        if (opt.height >= 0) size.SetHeight(opt.height);
        if (opt.width >= 0) size.SetWidth(opt.width);

        auto temp = new wxTextCtrl(parent, wxID_ANY, wxString(opt.default_value->getString()), wxDefaultPosition, size, (opt.multiline ? wxTE_MULTILINE : 0));

        if (opt.tooltip.length() > 0) { window->SetToolTip(opt.tooltip); }

//        _on_change = [=](wxCommandEvent& a) { __on_change(a);};

//        window->Bind(wxEVT_TEXT, _on_change, window->GetId());
//        window->Bind(wxEVT_KILL_FOCUS, _on_kill_focus, window->GetId());

        // recast as a wxWindow to fit the calling convention
        window = dynamic_cast<wxWindow*>(temp);
    }
}}


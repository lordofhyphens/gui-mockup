#include "OptionsGroup.hpp"

// Translate the ifdef 
#ifdef __WXOSX__
const bool wxOSX = true;
#else
const bool wxOSX = false;
#endif

namespace Slic3r {
void OptionsGroup::BUILD() {
    if (staticbox) {
        wxStaticBox* box = new wxStaticBox(parent, -1, title);
        _sizer = new wxStaticBoxSizer(box, wxVERTICAL);
    } else {
        _sizer = new wxBoxSizer(wxVERTICAL);
    }
    size_t num_columns = 1;
    if (label_width != 0) ++num_columns;
    if (extra_column != 0) ++num_columns;

    _grid_sizer = new wxFlexGridSizer(0, num_columns, 0, 0);
    _grid_sizer->SetFlexibleDirection(wxHORIZONTAL);
    _grid_sizer->AddGrowableCol(label_width > 0);
    _sizer->Add(_grid_sizer, 0, wxEXPAND | wxALL, (wxOSX ? 0 : 5));
}
}

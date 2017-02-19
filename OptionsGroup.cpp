#include "OptionsGroup.hpp"
#include "Field.hpp"

// Translate the ifdef 
#ifdef __WXOSX__
    #define wxOSX true
#else
    #define wxOSX false
#endif

#define BORDER(a, b) ((wxOSX ? a : b))

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
    _sizer->Add(_grid_sizer, 0, wxEXPAND | wxALL, BORDER(0,5));
}

FieldTypes Option::default_type(FieldTypes in) {
    switch (in) {
        case FieldTypes::INTEGER:
            return FieldTypes::I_TEXT;
        case FieldTypes::FLOAT:
            return FieldTypes::F_TEXT;
        default:
            return FieldTypes::TEXT;
    }
}

void OptionsGroup::append_line(const Line& line) {
    if (line.has_sizer() || (line.has_widget() && line.full_width)) {
        wxASSERT(line.sizer() != nullptr);
        _sizer->Add( (line.has_sizer() ? line.sizer() : line.widget().sizer()), 0, wxEXPAND | wxALL, BORDER(0, 15));
        return;
    }
    wxSizer* grid_sizer = _grid_sizer;
    // If we have an extra column, build it.
    // If there's a label, build it.
    if (label_width != 0) {
        wxStaticText* label = new wxStaticText(parent, -1, _(line.label) + ":", wxDefaultPosition);
        label->Wrap(label_width);
        if (wxIsEmpty(line.tooltip())) { label->SetToolTip(line.tooltip()); }
        grid_sizer->Add(label, 0, wxALIGN_CENTER_VERTICAL, 0);
    }
    // If we have a widget, add it to the sizer
    if (line.has_widget()) {
        grid_sizer->Add(line.widget().sizer(), 0, wxEXPAND | wxALL, BORDER(0,15));
        return;
    }
    // If we have a single option with no sidetext just add it directly to the grid sizer
    if (line.options().size() == 1) {
        const Option& opt = line.options()[0];
        if (line.extra_widgets().size() && !wxIsEmpty(opt.sidetext) && line.extra_widgets().size() == 0) {
            Field* field = _build_field(opt);
            grid_sizer->Add(field->sizer(), 0, (opt.full_width ? wxEXPAND : 0) | wxALIGN_CENTER_VERTICAL, 0);
            if (field != nullptr) { delete field; }
        }
    }
    // Otherwise, there's more than one option or a single option with sidetext -- make
    // a horizontal sizer to arrange things.
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    grid_sizer->Add(sizer, 0, 0, 0);
    for (auto& option : line.options()) {
    }
    // Append extra sizers
    for (auto& widget : line.extra_widgets()) {
        _sizer->Add(widget.sizer(), 0, wxLEFT | wxALIGN_CENTER_VERTICAL, 4);
    }
}

Field* OptionsGroup::_build_field(const Option& opt) {
    Field* local_field = nullptr;
    switch (opt.type) {
        case FieldTypes::TEXT:
            break;
        default:
            break;
    }
    return local_field;
}
}

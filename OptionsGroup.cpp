#include "OptionsGroup.hpp"
#include "ConfigExceptions.hpp"

#include <utility>
#include <wx/tooltip.h>

namespace Slic3r { namespace GUI {

    const t_field& OptionsGroup::build_field(const Option& opt) {
        return build_field(opt.opt_id, opt.opt);
    }
    const t_field& OptionsGroup::build_field(const t_config_option_key& id) {
        const ConfigOptionDef& opt = options.at(id);
        return build_field(id, opt);
    }

    const t_field& OptionsGroup::build_field(const t_config_option_key& id, const ConfigOptionDef& opt) {
        // Check the gui_type field first, fall through
        // is the normal type.
        if (opt.gui_type.compare("select") == 0) {
        } else if (opt.gui_type.compare("select_open") == 0) {
        } else if (opt.gui_type.compare("color") == 0) {
        } else if (opt.gui_type.compare("f_enum_open") == 0 || 
                   opt.gui_type.compare("i_enum_open") == 0 ||
                   opt.gui_type.compare("i_enum_closed") == 0) {
        } else if (opt.gui_type.compare("slider") == 0) {
        } else if (opt.gui_type.compare("i_spin") == 0) { // Spinctrl
        } else { 
            switch (opt.type) {
                case coFloatOrPercent:
                case coPercent:
                case coFloat:
                case coString:
                    fields.emplace(id, STDMOVE(TextCtrl::Create<TextCtrl>(_parent, opt,id)));
                    break;
                case coNone:   break;
                default:
                    throw ConfigGUITypeError(""); break;
            }
        }
        // Grab a reference to fields for convenience
        const t_field& field = fields[id];
        field->parent = parent();
        // assign function objects for callbacks, etc.
        return field;
    }

    void OptionsGroup::append_line(const Line& line) {
        if (line.sizer != nullptr || (line.widget != nullptr && line.full_width > 0)){
            if (line.sizer != nullptr) {
                sizer->Add(line.sizer, 0, wxEXPAND | wxALL, wxOSX ? 0 : 15);
                return;
            }
            if (line.widget != nullptr) {
                sizer->Add(line.widget(_parent), 0, wxEXPAND | wxALL, wxOSX ? 0 : 15);
                return;
            }
        }

        auto grid_sizer = _grid_sizer;

        // Build a label if we have it
        if (label_width != 0) {
            auto label = new wxStaticText(parent(), wxID_ANY, line.label , wxDefaultPosition, wxSize(label_width, -1));
            label->SetFont(label_font);
            label->Wrap(label_width); // avoid a Linux/GTK bug
            grid_sizer->Add(label, 0, wxALIGN_CENTER_VERTICAL,0);
            if (line.label_tooltip.compare("") != 0)
                label->SetToolTip(line.label_tooltip);
        }

        // If there's a widget, build it and add the result to the sizer.
        if (line.widget != nullptr) {
            auto wgt = line.widget(parent());
            grid_sizer->Add(wgt, 0, wxEXPAND | wxALL, wxOSX ? 0 : 15);
            return;
        }

    
        // if we have a single option with no sidetext just add it directly to the grid sizer
        auto option_set = line.get_options();
        if (option_set.size() == 1 && option_set.front().opt.sidetext.size() == 0 &&
            option_set.front().side_widget == nullptr && line.get_extra_widgets().size() == 0) {
            const auto& option = option_set.front();
            const auto& field = build_field(option);
            std::cerr << "single option, no sidetext.\n";
            std::cerr << "field parent is not null?: " << (field->parent != nullptr) << "\n";

            if (is_window_field(field)) 
                grid_sizer->Add(field->getWindow(), 0, (option.opt.full_width ? wxEXPAND : 0) | wxALIGN_CENTER_VERTICAL, 0);
            if (is_sizer_field(field)) 
                grid_sizer->Add(field->getSizer(), 0, (option.opt.full_width ? wxEXPAND : 0) | wxALIGN_CENTER_VERTICAL, 0);
            return;
        }

        // if we're here, we have more than one option or a single option with sidetext
        // so we need a horizontal sizer to arrange these things
        auto sizer = new wxBoxSizer(wxHORIZONTAL);
        grid_sizer->Add(sizer, 0, 0, 0);
        for (auto opt : option_set) {
            
        }

        
    }
    Line OptionsGroup::create_single_option_line(const Option& option) const {
        Line retval {option.opt.label, option.opt.tooltip};
        Option tmp(option);
        tmp.opt.label = std::string("");
        retval.append_option(tmp);
        return retval;
    }


}}

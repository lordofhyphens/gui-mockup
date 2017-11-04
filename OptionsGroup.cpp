#include "OptionsGroup.hpp"
#include "ConfigExceptions.hpp"

#include <utility>

namespace Slic3r { namespace GUI {

    void OptionsGroup::build_field(const t_config_option_key& id) {
        const ConfigOptionDef& opt = options.at(id);

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
                    fields.emplace(id, STDMOVE(TextCtrl::Create<TextCtrl>(opt,id)));
                    break;
                case coNone:   break;
                default:
                    throw ConfigGUITypeError(""); break;
            }
        }
        // Grab a reference to fields for convenience
        t_field& field = fields[id];
        // assign function objects for callbacks, etc.
    }


}}

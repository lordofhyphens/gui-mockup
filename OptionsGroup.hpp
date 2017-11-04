#include <wx/wx.h>
#include <wx/stattext.h>
#include <wx/settings.h>

#include <map>
#include <functional>

#include "libslic3r/Config.hpp"
#include "libslic3r/PrintConfig.hpp"
#include "libslic3r/libslic3r.h"

#include "Field.hpp"

namespace Slic3r { namespace GUI {

/// Widget type describes a function object that returns a wxWindow (our widget) and accepts a wxWidget (parent window).
using widget_t = std::function<wxWindow*(wxWindow*)>;

class StaticText;

/// Wraps a ConfigOptionDef and adds function object for creating a side_widget.
struct Option {
    ConfigOptionDef opt {ConfigOptionDef()}; 
    t_config_option_key opt_id {""};
    widget_t side_widget {nullptr};
    bool readonly {false};

    Option(const ConfigOptionDef& _opt, t_config_option_key id) : opt(_opt), opt_id(id) {};
};

/// Represents option lines
class Line {
    public:
        wxString label {wxString("")};
        wxString label_tooltip {wxString("")};
        size_t full_width {0}; 
        wxSizer* sizer {nullptr};

        void append_option();

    private:
};

using t_optionfield_map = std::map<t_config_option_key, t_field>;

class OptionsGroup {
private: 
    const t_optiondef_map& options;

    /// Field list, contains unique_ptrs of the derived type.
    /// using types that need to know what it is beyond the public interface 
    /// need to cast based on the related ConfigOptionDef.
    t_optionfield_map fields;
    bool _disabled {false};
    wxGridSizer* _grid_sizer {nullptr};

protected:

    /// Generate a wxSizer or wxWindow from a configuration option
    /// Precondition: opt resolves to a known ConfigOption
    /// Postcondition: fields contains a wx gui object.
    void build_field(const t_config_option_key& id);

public:

    const wxWindow* parent {nullptr};
    const wxString title {wxString("")};
    size_t label_width {180};
    wxSizer* sizer {nullptr};
    const bool staticbox {true};

    wxFont sidetext_font {wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT) };
    wxFont label_font {wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT) };


    void append_line(const Line& line);
    Line create_single_option_line(const Option& option) const;
    inline void append_single_option_line(const Option& option) { append_line(create_single_option_line(option)); }

    // return a non-owning pointer reference 
    inline const Field* get_field(t_config_option_key id) const { try { return fields.at(id).get(); } catch (std::out_of_range e) { return nullptr; } }

    inline void enable() { for (auto& field : fields) field.second->enable(); }
    inline void disable() { for (auto& field : fields) field.second->disable(); }


    OptionsGroup(wxWindow* parent, std::string title, const ConfigDef& configs) : parent(parent), title(wxString(title)), options(configs.options) {};
};

class ConfigOptionsGroup: public OptionsGroup {
    public:
        /// reference to libslic3r config
        const std::shared_ptr<DynamicPrintConfig> config {nullptr};
        bool full_labels {0};
};

}}

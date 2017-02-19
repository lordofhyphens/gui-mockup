#include "Option.hpp"
namespace Slic3r {
FieldTypes Option::default_type(FieldTypes in) const {
    switch (in) {
        case FieldTypes::INTEGER:
            return FieldTypes::I_TEXT;
        case FieldTypes::FLOAT:
            return FieldTypes::F_TEXT;
        default:
            return FieldTypes::TEXT;
    }
}
}

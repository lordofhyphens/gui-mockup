#include "Option.hpp"
namespace Slic3r {
FieldTypes Option::default_type(FieldTypes in) const {
    switch (in) {
        default:
            return FieldTypes::TEXT;
    }
}
}

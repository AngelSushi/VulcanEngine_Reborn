#include <Reflection/VObject.h>

namespace VulcanCore {
    
    bool VObject::ImplementsInterface(const VInterface& Interface) const {
        return false;
        //return GetClass().ImplementsInterface(Interface);
    }
}

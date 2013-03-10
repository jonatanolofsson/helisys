#ifndef SYS_ACTUATOR_API_HPP_
#define SYS_ACTUATOR_API_HPP_

#include <sys/actuator/Actuator.hpp>
#include <sys/com/Maple.hpp>

namespace sys {
    namespace actuator {
        typedef Maple SerialLink;
    }
    typedef actuator::Actuator<actuator::SerialLink> Actuator;
}

#endif
#ifndef SYS_MODELS_C0_HPP_
#define SYS_MODELS_C0_HPP_

namespace sys {
    namespace math {
        namespace models {
            struct C0 {
                template<typename T>
                static void initialize(T& filter) {}

                static const int nofControls = 0;
            };
        }
    }
}

#endif
#ifndef SYS_MODELS_SCART3D_HPP_
#define SYS_MODELS_SCART3D_HPP_

namespace sys {
    namespace math {
        namespace models {
            struct SCart3D {
                enum state {
                    x = 0,
                    y = 1,
                    z = 2,

                    nofStates = 3
                };
                enum states {
                    position = x
                };

                template<typename T>
                static void initialize(T& filter) {
                    auto l = filter.retrieve_lock();
                    filter.state.setZero();

                    filter.covariance.setIdentity();
                }
            };
        }
    }
}

#endif
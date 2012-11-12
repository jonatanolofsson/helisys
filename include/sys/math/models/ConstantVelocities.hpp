#ifndef SYS_MATH_MODELS_CONSTANT_VELOCITY_HPP_
#define SYS_MATH_MODELS_CONSTANT_VELOCITY_HPP_

#include <Eigen/Core>
#include <sys/types.hpp>
#include <sys/math/constants.hpp>
#include <sys/math/statedifferentiation.hpp>
#include <cmath>

#include <iostream>

namespace sys {
    namespace models {
        namespace motion {
            using namespace Eigen;
            struct ConstantVelocities {
                template<typename T>
                static typename T::States predict(const T& filter) {
                    typedef typename T::Scalar Scalar;
                    typedef typename T::States States;
                    typedef typename T::StateDescription states;
                    auto& x = filter.state;
                    USING_XYZ
                    States xnext(x);

                    xnext.template segment<3>(states::position) += x.template segment<3>(states::velocity) * filter.dT;

                    // Note that this skew-symmetric matrix is diagonally shifted upwards-left compared
                    // to many representations, due to the storage model used by Eigen for quaternions: qx, qy, qz, qw
                    Matrix<Scalar, 4, 4> S;
                    S << QUATERNION_ROTATION_FROM_ROTVEL(x(states::omega[X]), x(states::omega[Y]), x(states::omega[Z]));

                    const Scalar wnorm     = x.template segment<3>(states::rotational_velocity).norm();
                    const Scalar wnormT2   = wnorm * filter.dT / 2;

                    if(wnorm > math::EPSILON) {
                        xnext.template segment<4>(states::quaternion) =
                            (std::cos(wnormT2) * x.template segment<4>(states::quaternion)
                                - (std::sin(wnormT2) / wnorm) * S * x.template segment<4>(states::quaternion)
                            ).normalized();
                    }

                    return xnext;
                }

                template<typename T>
                static Matrix<typename T::States::Scalar, T::States::RowsAtCompileTime, T::States::RowsAtCompileTime> systemJacobian(const T& filter) {
                    static const typename T::States dx = T::States::Constant(1e-3);
                    return math::template differentiateStates<T, predict<T>>(filter, dx);
                }

                template<typename T>
                static Matrix<typename T::States::Scalar, T::States::RowsAtCompileTime, T::States::RowsAtCompileTime> Q() {
                    typedef Matrix<typename T::States::Scalar, T::States::RowsAtCompileTime, T::States::RowsAtCompileTime> RetType;
                    return RetType::Identity();
                }
            };
        }
    }
}

#endif

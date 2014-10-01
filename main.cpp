#include <vector>
#include <memory>
#include <iostream>
#include <Eigen/Dense>
#include "typedefs.hpp"
#include "exp_quad.hpp"
#include <typeinfo>

using namespace Eigen;

void dunction() {
    auto cd = new ExponentiatedQuadratic<double> {};
    std::cout << cd << std::endl;
    auto cd2 = RBF<double>();
    std::cout << cd2 << std::endl;
}

int main() {
    dunction();
    MatrixX<double> X(3, 1);
    X << 1.0, 2.0, 3.0;

    auto c1 = RBF<double>();
    auto c2 = RBF<double>();

    std::cout << "NHyp 1 = " << c1->nhyp() << std::endl;
    std::cout << "NHyp 2 = " << c2->nhyp() << std::endl;

    auto Cd = c1 + c2;
    std::cout << "NHyp = " << Cd->nhyp() << std::endl;
    std::cout << "X times 2 = " << Cd->K(X) << std::endl;

    auto Cd2 = Cd + RBF<double>();
    std::cout << "NHyp = " << Cd2->nhyp() << std::endl;
    return 0;
}

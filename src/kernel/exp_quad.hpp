#import <Eigen/Dense>
#import "kernel.hpp"
#import "typedefs.hpp"

using namespace Eigen;
using namespace std;

template <typename N>
class ExponentiatedQuadratic : public Covariance<N>
{
    public:
    MatrixX<N> K (const Ref<const MatrixX<N>> X1, const Ref<const MatrixX<N>> X2) override {
        return X1;
    }
    MatrixX<N> K (const Ref<const MatrixX<N>> X) override {
        return X;
    }
    int nhyp() {
        return 5;
    }

};

template <typename N>
Covariance_ptr<N> RBF() {
    return Covariance_ptr<N>(new ExponentiatedQuadratic<N> {} );
}

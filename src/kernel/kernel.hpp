#ifndef kernel_h
#define kernel_h

#include <Eigen/Dense>
#include <vector>
#include "parameters.hpp"
#include "typedefs.hpp"

using namespace std;
using namespace Eigen;

template <typename N>
class Covariance {
protected:
    vector<Parameter<N> *> m_hyp;
    int m_dim;

public:
    vector<Parameter<N> *> get_hyp()
    {
        return m_hyp;
    }
    virtual int nhyp() = 0;
    void set_hyp(vector<Parameter<N> *> new_hyp)
    {
        m_hyp.clear();
        for (auto v : new_hyp) {
            m_hyp.push_back(v);
        }
    }
    virtual MatrixX<N> K (const Ref<const MatrixX<N>>, const Ref<const MatrixX<N>>) = 0;
    virtual MatrixX<N> K (const Ref<const MatrixX<N>>) = 0;
};

template <typename N>
using Covariance_ptr = std::shared_ptr<Covariance<N>>;

enum Operation {ADD=1, MULTIPLY};

template <typename N>
class CompositeCovariance : public Covariance<N> {
public:
    Covariance_ptr<N> m_c1;
    Covariance_ptr<N> m_c2;
    Operation m_op;
    CompositeCovariance(Operation op, Covariance_ptr<N> c1, Covariance_ptr<N> c2) : m_c1(c1), m_c2(c2), m_op(op) {}

    virtual MatrixX<N> K (const Ref<const MatrixX<N>> X1, const Ref<const MatrixX<N>> X2) override
    {
        switch (m_op) {
            case ADD:
                return m_c1->K(X1, X2) + m_c2->K(X1, X2);
            case MULTIPLY:
                return (m_c1->K(X1, X2).array() * m_c2->K(X1, X2).array()).matrix();
            }
    }
    virtual MatrixX<N> K (const Ref<const MatrixX<N>> X) override
    {
        switch (m_op) {
            case ADD:
                return m_c1->K(X) + m_c2->K(X);
            case MULTIPLY:
                return (m_c1->K(X).array() * m_c2->K(X).array()).matrix();
            }
    }
    int nhyp()
    {
        return (*m_c1).nhyp() + (*m_c2).nhyp();
    }
};

template <typename N>
Covariance_ptr<N> operator+ (Covariance_ptr<N> c1, Covariance_ptr<N> c2) {
    return Covariance_ptr<N>(new CompositeCovariance<N> {Operation::ADD, c1, c2} );
}
#endif

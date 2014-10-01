#include <iostream>
#include <cmath>

template <typename N>
class Parameter
{
    N m_raw_value;
public:
    virtual void operator=(N value) = 0;
    virtual N get_value() = 0;
    virtual void set_value(N value) = 0;
    virtual N val_d_raw() = 0;
    virtual std::string name() = 0;
    N get_raw_value() { return m_raw_value;}
    void set_raw_value(N raw_value) {m_raw_value = raw_value;};
};

template <typename N>
class PositiveParameter : public Parameter<N>{
public:
    PositiveParameter<N>(N value) {
        this->set_value(value);
    }
    void operator=(N value) {
        this->set_value(value);
    }
    std::string name()
    {
        return "PositiveParameter";
    }
    N get_value()
    {
        return std::exp(this->get_raw_value());
    }
    N val_d_raw() {
        return std::exp(this->get_raw_value());
    }
    void set_value(N value)
    {
        this->set_raw_value(std::log(value));
    }

};
template <typename N>
class NegativeParameter : public Parameter<N>{
public:
    NegativeParameter<N>(N value) {
        this->set_value(value);
    }
    void operator=(N value)
    {
        this->set_value(value);
    }
    N get_value()
    {
        return -std::exp(this->get_raw_value());
    }
    std::string name() {
        return "NegativeParameter";
    }
    N val_d_raw()
    {
        return -std::exp(this->get_raw_value());
    }
    void set_value(N value)
    {
        this->set_raw_value(std::log(-value));
    }
};
template <typename N>
class BoundedParameter : public Parameter<N>{
    N m_average;
    N m_scale;
public:
    void operator=(N value) {
        this->set_value(value);
    }
    BoundedParameter<N>(N value, N max_value, N min_value) {
        m_average = (max_value + min_value) / 2;
        m_scale = (max_value - min_value);
        this->set_value(value);
    }
    N get_value()
    {
        N sigmoid = 1 / ( 1 + std::exp(-this->get_raw_value()));
        return (sigmoid - 0.5) * m_scale + m_average;
    }
    std::string name()
    {
        return "BoundedParameter";
    }
    N val_d_raw() {
        double sigmoid = 1 / (1 + std::exp(-this->get_raw_value()));
        return sigmoid * sigmoid * std::exp(-this->get_raw_value()) * m_scale;
    }
    void set_value(N value)
    {
        N first = (value - m_average) / m_scale + 0.5;
        N second = 1 / first - 1;
        this->set_raw_value(-std::log(second));
    }
    void set_bounds(N max_value, N min_value)
    {
        m_average = (max_value + min_value) / 2;
        m_scale = (max_value - min_value);
    }
};
typedef PositiveParameter<double> positive_double;
typedef NegativeParameter<double> negative_double;
typedef BoundedParameter<double> bounded_double;

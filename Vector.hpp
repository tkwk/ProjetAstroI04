#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>
#include "Real.hpp"
#include <vector>
#include <cmath>

template<unsigned int N> class Vector;
template<unsigned int N> Vector<N> operator*(const real &, const Vector<N> &);
template<unsigned int N> std::ostream & operator<<(std::ostream &, const Vector<N> &);

template<unsigned int N>
class Vector {
private:
    std::vector<real> coordinates;
public:
    Vector<N> (); 
    Vector<N> (const Vector<N> &);
    Vector<N> (const std::vector<real> &);
    ~Vector<N> ();

    real operator[](const int &) const;
    real & operator[](const int &);
    Vector<N> & operator=(const Vector<N> &);
    Vector<N> operator+(const Vector<N> &) const;
    Vector<N> operator-(const Vector<N> &) const;
    Vector<N> operator/(const real &) const;

    friend std::ostream & operator<< <>(std::ostream &, const Vector<N> &);

    friend Vector<N> operator*<>(const real &, const Vector<N> &);
    
    friend Vector<3> operator*(const Vector<3> &, const Vector<3> &);
    friend Vector<3> operator*(const Vector<2> &, const Vector<2> &);

    real dotProduct(const Vector<N> &) const;
    real squaredNorm() const;
    real norm() const;

    Vector<N> normalized() const;
    Vector<N> & normalize();
};


template<unsigned int N>
Vector<N>::Vector() : coordinates(N) {}


template<unsigned int N>
Vector<N>::Vector(const Vector<N> & other) : coordinates(N) {
    *this=other;    
}


template<unsigned int N>
Vector<N>::Vector(const std::vector<real> & other) : coordinates(N) {
    for(int i=0;i<other.size();i++) {
        if(i<N) (*this)[i] = other[i];
    }
}


template<unsigned int N>
Vector<N>::~Vector() {}


template<unsigned int N>
real Vector<N>::operator[](const int & index) const {
    return this->coordinates[index];
}


template<unsigned int N>
real & Vector<N>::operator[](const int & index) {
    return this->coordinates[index];
}


template<unsigned int N>
Vector<N> & Vector<N>::operator=(const Vector<N> & other) {
    for(int i=0;i<N;i++)
        (*this)[i] = other[i];
    return *this;
}


template<unsigned int N>
Vector<N> Vector<N>::operator+(const Vector<N> & other) const {
    Vector<N> res;
    for(int i=0;i<N;i++)
        res[i] = (*this)[i] + other[i];
    return res;
}


template<unsigned int N>
Vector<N> Vector<N>::operator-(const Vector<N> & other) const {
    Vector<N> res;
    for(int i=0;i<N;i++)
        res[i] = (*this)[i] - other[i];
    return res;
}


template<unsigned int N>
Vector<N> Vector<N>::operator/(const real &s) const {
    return (1/s)*(*this);
}


template<unsigned int N>
Vector<N> operator*(const real &s, const Vector<N> &v) {
    Vector<N> res;
    for(int i=0;i<N;i++)
        res[i] = s*v[i];
    return res;
}


Vector<3> operator*(const Vector<3> one, const Vector<3> two) {
    Vector<3> res;
    res[0] = one[1]*two[2]-one[2]*two[1];
    res[1] = one[2]*two[0]-one[0]*two[2];
    res[2] = one[0]*two[1]-one[1]*two[0];
    return res;
}


Vector<3> operator*(const Vector<2> one, const Vector<2> two) {
    Vector<3> res;
    res[0] = 0.0;
    res[1] = 0.0;
    res[2] = one[0]*two[1]-one[1]*two[0];
    return res;
}


template<unsigned int N>
real Vector<N>::dotProduct(const Vector<N> &other) const {
    real res = 0.0;
    for(int i=0; i<N; i++)
        res += (*this)[i]*other[i];
    return res;
}


template<unsigned int N>
real Vector<N>::squaredNorm() const {
    return this->dotProduct(*this);
}


template<unsigned int N>
real Vector<N>::norm() const {
    return sqrt(this->squardNorm());
}


template<unsigned int N>
Vector<N> Vector<N>::normalized() const {
    return (*this)/(this->norm());
}


template<unsigned int N>
Vector<N> & Vector<N>::normalize() {
    return (*this)=(*this)/(this->norm());
}


template<unsigned int N>
std::ostream & std::operator<<(std::ostream & o, const Vector<N> &v) {
    o << "(";
    for(int i=0;i<N-1;i++)
        o << v[i] << ", ";
    o << v[N-1] << ")";
    return o;
}


#endif


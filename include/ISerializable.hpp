#ifndef CONWAY_ISERIALIZABLE_HPP
#define CONWAY_ISERIALIZABLE_HPP

#include <ostream>
#include <istream>

template<typename T>
class ISerializable {
  public:
    // virtual ~ISerializable() = 0;
    
    friend std::ostream& operator<<(std::ostream &out, const T &rhs);
    friend std::istream& operator>>(std::istream &in, const T &rhs);
};

// https://stackoverflow.com/a/8513537
// ISerializable<>::~ISerializable() { } // all destructors must exist

#endif
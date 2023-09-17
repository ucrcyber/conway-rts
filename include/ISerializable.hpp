#ifndef CONWAY_ISERIALIZABLE_HPP
#define CONWAY_ISERIALIZABLE_HPP

#include <ostream>
#include <istream>

template<typename T>
class ISerializable {
  public:
    // text based serialization methods (cin/cout) 
    friend std::ostream& operator<<(std::ostream &out, const T &rhs);
    friend std::istream& operator>>(std::istream &in, const T &rhs);

    /// @return whether it was successful or not
    virtual bool SerializeToOstream(std::ostream &out);

    /// @return whether it was successful or not
    virtual bool ParseFromIstream(std::istream &in);
};

// https://stackoverflow.com/a/8513537
// ISerializable<>::~ISerializable() { } // all destructors must exist

#endif
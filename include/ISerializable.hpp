#ifndef CONWAY_INCLUDE_ISERIALIZABLE_HPP
#define CONWAY_INCLUDE_ISERIALIZABLE_HPP

#include <iostream>

template<typename T>
class ISerializable {
  public:
    // https://stackoverflow.com/a/8513537
    virtual ~ISerializable() {} // all destructors must exist (necessary for bazel)

    // https://stackoverflow.com/a/437507/21507383
    // friendship is not transitive or inherited, so these have to
    // be redeclared if private access is needed
    
    // text based serialization methods (cin/cout) 
    // friend std::ostream& operator<<(std::ostream& out, const T& rhs);
    // friend std::istream& operator>>(std::istream& in, T& rhs);

    /// @return whether it was successful or not
    virtual bool SerializeToOstream(std::ostream& out) const = 0;

    /// @return whether it was successful or not
    virtual bool ParseFromIstream(std::istream& in) = 0;
};

#endif // CONWAY_INCLUDE_ISERIALIZABLE_HPP
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <boost/exception/exception.hpp>


namespace mazenet {

class Exception : public virtual std::exception, public virtual boost::exception {
 public:
  virtual const char* what() const noexcept override {
    return "mazenet::Exception";
  }
};

}  // namespace mazenet

#endif /* EXCEPTION_H */
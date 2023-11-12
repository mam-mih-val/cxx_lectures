#ifndef _DECORATORS_H_
#define _DECORATORS_H_

#include <cstddef>
#include <exception>
#include <iostream>

template <class D>
class Counter : public D{
public:
  Counter() : D() { n_devices_++; }
  ~Counter() { n_devices_--; }
  size_t GetNDevices() const { return n_devices_; }
protected:
  static size_t n_devices_;
};

template <class D>
size_t Counter<D>::n_devices_ = 0;

template <class D>
class StateLogger : public D{
public:
  StateLogger() : D() { }
  ~StateLogger() {}
  bool GetStatus() {
    auto status = D::GetStatus();
    if( status ){
      std::cout << "The device is online" << std::endl;
    } else {
      std::cout << "The device is offline" << std::endl;
    }
    return status;
  }
};

template <class D>
class Reconnectable : public D{
public:
  Reconnectable() : D() {}
  ~Reconnectable() {}
  bool GetStatus() {
    D::Update();
    while (!D::state_) {
      std::cout << "Device is offline. Reconnecting" << std::endl;
      D::Update();
    }
    return true;
  }
};

template <class D>
class SafeDevice{
  class DeviceIsNotAvaliable : public std::exception {
    const char * what() const noexcept override {}
  };
  SafeDevice() : dev_() {}
  D& GetDevice(){
    if( dev_.GetStatus() )
      return dev_;
    throw DeviceIsNotAvaliable();
  }
private:
  D dev_;
};

#endif
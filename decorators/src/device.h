#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <algorithm>
#include <bitset>
#include <cstddef>
#include <limits>
#include <random>

class Device{
public:
  Device() {
    std::random_device rd;
    random_engine = std::mt19937(rd());
  };
  Device( Device&& ) = default;
  virtual ~Device() = default;
  bool GetStatus(){
    Update();
    return state_;
  }
protected:
  void NewUpdate() { Update(); };
  virtual void Update() = 0;
  mutable bool state_{false};
  std::mt19937 random_engine{};
};


using stable_data_type = std::bitset< std::numeric_limits<size_t>::digits >;

class StableDevice : public Device{
public:
  StableDevice() : Device() {}
  ~StableDevice() override = default;
  StableDevice( StableDevice&& ) = default;
  
  void ReadData(){ 
    auto number = data_generator_( random_engine );
    data_ = stable_data_type( number );
  }
  
  const stable_data_type& GetData() const { 
    return data_; 
  }
  
  template<typename Func>
  auto Calculate( const Func& func ){ return func( data_ ); }

protected:
  void Update() override { state_ = state_generator_(random_engine) < 0.7; }
  stable_data_type data_{};
  std::uniform_int_distribution<size_t> data_generator_{std::numeric_limits<size_t>::min(),  std::numeric_limits<size_t>::max()};
  std::uniform_real_distribution<double> state_generator_{0, 1};
};

class UnstableDevice : public Device{
public:
  UnstableDevice() : Device() {}
  ~UnstableDevice() override = default;
  UnstableDevice( UnstableDevice&& ) = default;
  bool SendMessage( [[maybe_unused]] std::string msg_ ) const { return state_; }

protected:
  void Update() override { state_ = state_generator_( random_engine ) > 0.9; };
  std::uniform_real_distribution<double> state_generator_{0, 1};
};

#endif // _DEVICE_H_
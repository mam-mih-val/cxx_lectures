#include <algorithm>
#include <iostream>
#include <vector>

#include "device.h"
#include "decorators.h"

int main(){
  std::vector<Reconnectable<StateLogger<StableDevice>>> vec_s_dev(10);
  std::vector<Reconnectable<UnstableDevice>> vec_u_dev(20);

  std::for_each(vec_s_dev.begin(), vec_s_dev.end(), [ i=int{0} ]( Reconnectable<StateLogger<StableDevice>>& d ) mutable { 
    if(d.GetStatus()){
      d.ReadData();
      auto res = d.Calculate( [](auto& data){ return data.count(); } );
      std::cout << "Device i=" << i << " value=" << res << std::endl;
      ++i;
    }
  });

  std::for_each(vec_u_dev.begin(), vec_u_dev.end(), [i=int{0}]( Reconnectable<UnstableDevice>& d ) mutable{ 
    if(d.GetStatus()){
      auto msg_status = d.SendMessage( "You shall not pass" );
      std::cout << "Message on device i= " << i << " is delivered status:" << msg_status << std::endl;
      ++i;
    }
  });

  return 0;
}
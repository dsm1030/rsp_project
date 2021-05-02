#include <gui/gui_reconfigure.hpp>

gui_reconfigure::gui_reconfigure(){

  server_callback = boost::bind(&gui_reconfigure::callback, this, _1,_2);
  // _1 : bounding to the first param

  server.setCallback(server_callback);
}

void gui_reconfigure::callback(gui::guiConfig& config, uint32_t level){

  switch(level){
  case 1:
    std::cout<<config.status<<std::endl;
    break;
  case 2:
    std::cout<<config.distance<<std::endl;
    break;
  }
  
  
}

#include <gui/gui_reconfigure.hpp>

int main(int argc, char **argv){

  // create a node
  ros::init(argc,argv, "gui");

  // create a reconfigure object, which has a class, a dynamic reconfiguration server, and a call back has been done to this.
  gui_reconfigure gui;
  ros::spin();

  return 0;

}

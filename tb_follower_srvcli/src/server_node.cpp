#include <tb_follower_srvcli/server.hpp>

int main( int argc, char** argv ){

  ros::init(argc,argv,"action_srv");
  ros::NodeHandle nh;
  server server(nh);

  ros::MultiThreadedSpinner spinner(3);
  spinner.spin();
  // ros::spin();
  return 0;
}
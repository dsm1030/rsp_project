#include <tb_follower_srvcli/client.hpp>

int main( int argc, char** argv) {
  ros::init(argc,argv, "client");
  ros::NodeHandle nh;
  client client(nh);

  ros::spin();

  return 0;
}
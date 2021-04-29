#include <sensor_based_following/follower.hpp>

int main(int argc, char** argv ){
  ros::init(argc, argv, "follower");
  ros::NodeHandle nh;

  follower follower_node(nh);
  ros::spin();

  return 0;
}
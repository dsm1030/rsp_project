#include <ar_pose_filter/ar_filter.hpp>

int main( int argc, char** argv ){

  ros::init(argc,argv,"ar_filter_node");
  ros::NodeHandle nh;
  ar_filter filter(nh);

  ros::Rate rate(5);
  while(ros::ok()){
    filter.publisher();
    ros::spinOnce();
    rate.sleep();
  }
  
  return 0;
}
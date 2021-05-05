#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <tb_follower_msgs/ar_tag.h>

class ar_filter{

private: 
  ros::Publisher pub_ar;
  ros::Subscriber sub_pose;
  ros::NodeHandle nh;
  bool ifnew;
  double polar_th;
  double polar_r;
  double heading;

public:
  ar_filter( ros::NodeHandle& nh );
  void subCB( const geometry_msgs::PoseStampedConstPtr& msg );
  void publisher();



};
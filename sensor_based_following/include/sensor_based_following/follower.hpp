#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <algorithm>

class follower{

private:

  ros::NodeHandle nh;
  ros::Subscriber scan_sub;
  ros::Publisher cmd_pub;

  std::vector<int> scan_idx;
  double rref;
  int deg;



public:

  follower( ros::NodeHandle& nh );
  ~follower();
  void scan2cmd_cb(const sensor_msgs::LaserScanConstPtr& msg);
  void scanidx_init(const int deg);

};
#include <ros/ros.h>
#include <tb_follower_actions/followAction.h>
#include <tb_follower_msgs/ar_tag.h>
#include <math.h>
#include <actionlib/server/simple_action_server.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <algorithm>


class server{

  typedef actionlib::SimpleActionServer<tb_follower_actions::followAction> ActionServer;

private:

  ros::NodeHandle nh;
  ros::Subscriber sub_scan;
  ros::Subscriber sub_tag;
  ros::Publisher pub_cmd;
  std::unique_ptr<ActionServer> as;
  double rref;
  int deg;
  double tagth;
  double tagr;
  double dr;
  double min_range;
  int dth;
  double vx;
  double vth;
  bool new_ar;
  std::vector<int> scan_idx;


public:

  server( ros::NodeHandle& nh );
  void goalCB();
  void preemptCB();
  void subscanCB( const sensor_msgs::LaserScanConstPtr& msg );
  void subtagCB( const tb_follower_msgs::ar_tagConstPtr& msg );
  void pubvelcmd( const double x, const double th );
  void scanidx_init(const int deg);

};
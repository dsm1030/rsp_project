#include <ar_pose_filter/ar_filter.hpp>

ar_filter::ar_filter( ros::NodeHandle& nh ): nh( nh ), ifnew( 0 ), polar_th(0.0), polar_r(0.0), heading(0.0) {
  pub_ar = nh.advertise<tb_follower_msgs::ar_tag>("/tag_filtered", 10);
  sub_pose = nh.subscribe("/tag_pose", 10, &ar_filter::subCB, this);
}

void ar_filter::subCB( const geometry_msgs::PoseStampedConstPtr& msg ){
  double pi = 3.14159265359;
  polar_th = atan2(msg->pose.position.z,msg->pose.position.x)/pi*180.0 - 72.0;
  polar_r = pow( pow(msg->pose.position.x,2)+pow(msg->pose.position.y,2)+pow(msg->pose.position.z,2),0.5)+0.2;
  heading = 0.0; //need implementation
  ifnew = true;
}

void ar_filter::publisher(){
  tb_follower_msgs::ar_tag pubmsg;
  pubmsg.polar_th = polar_th;
  pubmsg.polar_r = polar_r;
  pubmsg.heading = heading;
  pubmsg.new_data = ifnew;
  pub_ar.publish(pubmsg);
  ifnew = false;
}
#include <sensor_based_following/follower.hpp>

follower::follower(ros::NodeHandle& nh): nh( nh ){

  deg = 70;
  scan_sub = nh.subscribe("scan_filtered", 10, &follower::scan2cmd_cb, this );
  cmd_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",10);
  nh.getParam("follow_range",rref);
  scanidx_init(deg);

}

follower::~follower(){}

void follower::scan2cmd_cb(const sensor_msgs::LaserScanConstPtr& msg){
  std::vector< double > laser_data;
  int idx;
  for(int i=0;i<scan_idx.size();i++){
    idx = scan_idx[i];
    // if(msg->ranges[idx] != 0.1){
    //   laser_data.push_back(msg->ranges[idx]);
    // } else
    if(i!=0 && i!=(scan_idx.size()-1) && msg->ranges[idx] == 0.1){
      laser_data.push_back((msg->ranges[idx-1]+msg->ranges[idx+1])/2);
    } else {
      laser_data.push_back(msg->ranges[idx]);
    }
  }

  // double laser_smooth[scan_idx.size()];
  std::vector<double> laser_smooth;
  for(int i=0;i<scan_idx.size();i++){
    idx = scan_idx[i];
    if((i>1) && (i<scan_idx.size()-2)){
      laser_smooth.push_back( (laser_data[i-2]+laser_data[i-1]+laser_data[i]+laser_data[i+1]+laser_data[i+2])/5 );
    } else {
      laser_smooth.push_back(laser_data[i]);
    }
  }

  int min_range_idx = std::min_element(laser_smooth.begin(),laser_smooth.end())-laser_smooth.begin();
  double min_range = *std::min_element(laser_smooth.begin(),laser_smooth.end());

  double dr = min_range-rref;
  int dth = min_range_idx-deg;

  geometry_msgs::Twist cmd_msg;
  if (dr<=-0.1){
    cmd_msg.linear.x = -0.05;
  } else if ((dr>-0.1) && (dr<=0.1)){
    cmd_msg.linear.x = 0.0;
  } else if ((dr>0.1) && (dr<=0.8)){
    cmd_msg.linear.x = 0.05+dr/8;
  } else if (dr>0.8){
    cmd_msg.linear.x = 0.15;
  } else {
    cmd_msg.linear.x = 0;
  }

  if (dth<-45){
    cmd_msg.angular.z = -0.5;
  } else if ((dth>=-45) && (dth<-25)){
    cmd_msg.angular.z = -0.3;
  } else if ((dth>=-25) && (dth<=25)){
    cmd_msg.angular.z = 0.0;
  } else if ((dth>25) && (dth<=45)){
    cmd_msg.angular.z = 0.3;
  } else if (dth>45){
    cmd_msg.angular.z = 0.5;
  } else {
    cmd_msg.angular.z = 0.0;
  }

  std::cout << min_range << std::endl;
  std::cout <<cmd_msg.linear.x << "  " << cmd_msg.angular.z << std::endl;

  cmd_pub.publish(cmd_msg);


}

void follower::scanidx_init(const int deg){
  for(int i=0;i<deg;i++){
    scan_idx.push_back(360-deg+i);
  }
  for(int i=0;i<(deg+1);i++){
    scan_idx.push_back(i);
  }
}
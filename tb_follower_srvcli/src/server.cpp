#include <tb_follower_srvcli/server.hpp>

server::server( ros::NodeHandle& nh ) : nh( nh ),tagth(0.0){

  deg = 70;
  scanidx_init(deg);
  pub_cmd = nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);
  sub_scan = nh.subscribe("/scan_filtered", 10, &server::subscanCB, this);
  sub_tag = nh.subscribe("/tag_filtered", 10, &server::subtagCB, this );

  as.reset(new ActionServer(nh, "action_server", false));
  as->registerGoalCallback( boost::bind(&server::goalCB, this));
  as->registerPreemptCallback( boost::bind(&server::preemptCB, this));
  as->start();
}

void server::goalCB(){
  tb_follower_actions::followGoal goal = *(as->acceptNewGoal());
  std::cout << "Goal accepted, following......" << std::endl;

  tb_follower_actions::followFeedback fb;
  fb.feedback.fb_code = "following......";

  ros::Rate rate(15);
  nh.getParam("/client_node/status",goal_status);

  while(goal_status){
    if (dr<=-0.1){
      vx = -0.05;
    } else if ((dr>-0.1) && (dr<=0.1)){
      vx = 0.0;
    } else if ((dr>0.1) && (dr<=0.8)){
      vx = 0.05+dr/8;
    } else if (dr>0.8){
      vx = 0.15;
    } else {
      vx = 0;
    }

    if (dth<-45){
      vth = -0.8;
    } else if ((dth>=-45) && (dth<-25)){
      vth = -0.5;
    } else if ((dth>=-25) && (dth<=25)){
      vth = 0.0;
    } else if ((dth>25) && (dth<=45)){
      vth = 0.5;
    } else if (dth>45){
      vth = 0.8;
    } else {
      vth = 0.0;
    }

    fb.feedback.linear_vel = vx;
    fb.feedback.angular_vel = vth;
    fb.feedback.cur_dist = dr;
    fb.feedback.cur_ang = dth;

    pubvelcmd(vx, vth);
    as->publishFeedback(fb);
    rate.sleep();
    nh.getParam("/client_node/status",goal_status);
  }

  std::cout << "end of following" << std::endl;
  pubvelcmd(0.0,0.0);
  as->setSucceeded();

}

void server::subscanCB(const sensor_msgs::LaserScanConstPtr& msg){
  nh.getParam("/follow_range",rref);
  std::vector< double > laser_data;
  int idx;
  for(int i=0;i<scan_idx.size();i++){
    idx = scan_idx[i];
    if(i!=0 && i!=(scan_idx.size()-1) && msg->ranges[idx] == 0.1){
      laser_data.push_back((msg->ranges[idx-1]+msg->ranges[idx+1])/2);
    } else {
      laser_data.push_back(msg->ranges[idx]);
    }
  }

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
  min_range = *std::min_element(laser_smooth.begin(),laser_smooth.end());

  if(new_ar){

    if( (abs(min_range_idx-tagth)<35) ){
      dr = min_range-rref;
      dth = min_range_idx-deg;
    } else {
      dth = std::round(tagth);
      dr = tagr-rref;
      // dr = laser_smooth[tagth+deg];
    }
  } else {
    dr = min_range-rref;
    dth = min_range_idx-deg;
  }
  // dr = min_range-rref;
  // dth = min_range_idx-deg;

}

void server::subtagCB(const tb_follower_msgs::ar_tagConstPtr& msg){
  // double pi = 3.14159265359;
  // tagth = atan2(msg->position.y,msg->position.x)/pi*180.0;
  new_ar = msg->new_data;
  tagth = msg->polar_th;
  tagr  = msg->polar_r;
}

void server::preemptCB(){
  // std::cout << "cancel goal" << std::endl;
  // as->setPreempted();
  // pubvelcmd(0.0,0.0);
}

void server::pubvelcmd( const double x, const double th ){
  geometry_msgs::Twist cmd_msg;
  cmd_msg.linear.x = x;
  cmd_msg.angular.z = th;
  pub_cmd.publish(cmd_msg);
}

void server::scanidx_init(const int deg){
  for(int i=0;i<deg;i++){
    scan_idx.push_back(360-deg+i);
  }
  for(int i=0;i<(deg+1);i++){
    scan_idx.push_back(i);
  }
}
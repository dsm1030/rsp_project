#include <tb_follower_srvcli/client.hpp>

client::client( ros::NodeHandle& nh ) : nh(nh){
  ac.reset(new ActionClient( "action_server", true));
  ac->waitForServer(ros::Duration(20));
  gui_callback = boost::bind(&client::guiCB, this ,_1,_2);
  gui_srv.setCallback(gui_callback);
}

void client::fbCB(const tb_follower_actions::followFeedbackConstPtr& msg){

}

void client::send_goal(){
  tb_follower_actions::followGoal goal;
  goal.goal.goal_dist = 0.0;
  ac->sendGoal(goal,ActionClient::SimpleDoneCallback(),ActionClient::SimpleActiveCallback(),boost::bind(&client::fbCB, this, _1));
}

void client::guiCB( tb_follower_srvcli::guiConfig &config, uint32_t level ){
  // switch(level){
  //   case 1:
  //     if (config.status){
  //       send_goal();
  //     } else {
  //       ac->cancelAllGoals();
  //     }
  //     break;
  //   case 1:
  //     nh.setParam("/follow_range",0.4);
  //     break;
  // }
  if (config.status){
    std::cout << "sending goal" << std::endl;
    nh.setParam("/follow_range", config.distance);
    send_goal();
  } else {
    ac->cancelAllGoals();
  }
}
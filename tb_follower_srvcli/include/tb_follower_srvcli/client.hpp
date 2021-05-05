#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <tb_follower_srvcli/guiConfig.h>
#include <actionlib/client/simple_action_client.h>
#include <tb_follower_actions/followAction.h>
#include <tb_follower_msgs/follow_distance_goal.h>

class client{

  typedef dynamic_reconfigure::Server<tb_follower_srvcli::guiConfig> gui_server;
  typedef actionlib::SimpleActionClient<tb_follower_actions::followAction> ActionClient;
private:
  gui_server gui_srv;
  gui_server::CallbackType gui_callback;
  ros::NodeHandle nh;
  std::unique_ptr<ActionClient> ac;

public:

  client( ros::NodeHandle& nh );
  void fbCB( const tb_follower_actions::followFeedbackConstPtr& msg );
  void send_goal();
  void guiCB( tb_follower_srvcli::guiConfig &config, uint32_t level );

};
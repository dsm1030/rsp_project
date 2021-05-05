#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "camera_link_broadcaster");
  ros::NodeHandle node;

  tf::TransformBroadcaster br;
  tf::Transform transform;

  ros::Rate rate(10.0);
  while (node.ok()){
    transform.setOrigin( tf::Vector3(0.035, 0, 0.12) );
    transform.setRotation( tf::Quaternion(0, 0.7071068, 0, 0.7071068) );
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_footprint", "camera_link"));
    rate.sleep();
  }
  return 0;
};

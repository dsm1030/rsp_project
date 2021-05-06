# RSP Project: Turtlebot AR Tag Following
A ROS implementation enables Turtlebot to detect and follow objects aided with ar tag detection.
## main dependencies
aruco_ros 
turtlebot3 
## Tutorial
1. Install
    - First you need to install ros and all listed dependent ros packages.
    - put `rsp_project` under your workspace's `src` folder
    - under your workspace directory, use `catkin build` command to build the packages
2. Setup
    - Make sure both the remote PC and turtlebot are connected to the same network. Use `ifconfig` on both machines to check their IP address. remotePC: {IP_OF_REMOTE_PC}, turtlebot: {IP_OF_RASPBERRYPI}.
    - turtlebot raspberrypi
      - update ROS IP settings: in `~/.bashrc`, add lines
      ```
      export ROS_MASTER_URI=http://{IP_OF_REMOTE_PC}:11311
      export ROS_HOSTNAME={IP_OF_RASPBERRYPI}
      ```
      - apply the changes.
      ```
      source ~/.bashrc
      ```
    - remote PC
      - set turtlebot model name: in `~/.bashrc`, add line
      ```
      export TURTLEBOT3_MODEL=burger
      ```
      - update ROS IP settings: in `~/.bashrc`, add lines
      ```
      export ROS_MASTER_URI=http://{IP_OF_REMOTE_PC}:11311
      export ROS_HOSTNAME={IP_OF_REMOTE_PC}
      ```
      - apply the changes.
      ```
      source ~/.bashrc
      ```
3. Start ROS on remote PC
    - source the built packages
    ```
    source {path_to_your_workspace}/devel/setup.bash
    ```
    - launch
    ```
    roslaunch tb_follower_launch tb_follower_launch.launch
    ```
    - a gui tool will show up, please select `client_node` from the left panel.
4. Launching Robot
    - on turtlebot, launch bringup
    ```
    roslaunch turtlebot3_bringup turtlebot3_robot.launch
    ```
    - open another terminal, launch raspicam
    ```
    roslaunch turtlebot3_bringup turtlebot3_rpicamera.launch
    ```
5. Using gui
    - status: this control starts/ends the following task, choose "1" to start follow, and "0" to stop
    - distance: it can adjust the following distance between the turtlebot follower and the target.




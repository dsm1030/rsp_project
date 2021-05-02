#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <gui/guiConfig.h>

class gui_reconfigure{

private:

  typedef dynamic_reconfigure::Server<gui::guiConfig> gui_server;

  gui_server server;
  gui_server::CallbackType server_callback;

public:

  gui_reconfigure();

  void callback(gui::guiConfig& config, uint32_t level);
// config contain a list of parameters
// unit32_t level is a binary mask to imply which parameter in the list has been changed


};

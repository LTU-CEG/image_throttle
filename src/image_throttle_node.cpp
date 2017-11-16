#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

double output_dt = 0;
image_transport::Publisher pub;
ros::Time last_time;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  const auto now = ros::Time::now();

  if ((now - last_time).toSec() >= output_dt)
  {
    last_time = now;

    pub.publish( msg );
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_throttle");
  ros::NodeHandle nh("~");
  double output_rate;

  if (!nh.getParam("output_rate", output_rate))
  {
    ROS_ERROR("No output_rate parameter specified, aborting!");
    return -1;
  }

  if (output_rate < 0)
  {
    ROS_ERROR("output_rate parameter cannot be negative, aborting!");
    return -1;
  }

  output_dt = 1.0 / output_rate;

  ROS_INFO_STREAM("Camera output rate set to " << output_rate << " Hz maximum.");

  last_time = ros::Time::now();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("input", 1, imageCallback);
  pub = it.advertise("output", 1);

  ros::spin();
}

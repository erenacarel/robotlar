#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>

void callback(const std_msgs::String::ConstPtr& msg){ //std_msgs::String::ConstPtr& 
    ROS_INFO("message : %s", msg->data.c_str());
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "solver");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    ros::Subscriber sub = n.subscribe("scan", 1000, callback);
	ros::Rate loop_rate(10);
    while(ros::ok())
	{
		geometry_msgs::Twist kumanda;
		kumanda.linear.x = 0.1;
		//kumanda.angular.z = 0.5;
		pub.publish(kumanda);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;


}


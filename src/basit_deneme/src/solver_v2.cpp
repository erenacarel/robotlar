#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>
#include <stdlib.h>

void move(double speed, double distance, bool isForward);

void callback(const sensor_msgs::LaserScan::ConstPtr& msg){ // std_msgs::String::ConstPtr& 
    ROS_INFO("message : %f", msg->ranges[360]);            // msg->data.c_str()
}


/*
float Fr_dist;
float Lt_dist;
float Rt_dist;

void callback(const sensor_msgs::LaserScan::ConstPtr &msg) {
ROS_INFO("Running");
float Fr_dist = msg->ranges[180];
float Lt_dist = msg->ranges[270];
float Rt_dist = msg->ranges[90];
ROS_INFO("Distance to Front: %f", Fr_dist);
ROS_INFO("Distance to Right: %f", Rt_dist);
}
*/

int main(int argc, char **argv)
{
    ros::init(argc, argv, "solver_v2");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    ros::Subscriber sub = n.subscribe("scan", 1000, callback);
    ros::Rate loop_rate(10);


    while(ros::ok()){
        geometry_msgs::Twist kumanda;
        sensor_msgs::LaserScan mesafe;
    /* 
        kumanda.linear.x = 0.25;
        kumanda.linear.y = 0;
        kumanda.angular.z = 0.75;
               
        kumanda.linear.x = 0.25;
        kumanda.linear.y = 0;
        kumanda.angular.z = -0.75;
    */
    /*
        if(mesafe.ranges[360] > 1){

            kumanda.linear.x = 0.1;
            kumanda.angular.z = 0.0;
            
        }

        if(mesafe.ranges[360] < 1){
            kumanda.linear.x = 0.0;
            kumanda.angular.z = 0.0;
        }
    
    	pub.publish(kumanda);
		ros::spinOnce();
		loop_rate.sleep();

    */

    move(0.25, -5, 1);
    }

    
    return 0;

}



void move(double speed, double distance, bool isForward){
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    geometry_msgs::Twist kumanda;
    //set a random linear velocity in the x-axis
    if (isForward)
        kumanda.linear.x =abs(speed);
    else
        kumanda.linear.x =-abs(speed);
    kumanda.linear.y =0;
    kumanda.linear.z =0;
    //set a random angular velocity in the y-axis
    kumanda.angular.x = 0;
    kumanda.angular.y = 0;
    kumanda.angular.z =0;

    double t0 = ros::Time::now().toSec();
    double current_distance = 0.0;
    ros::Rate loop_rate(100);
    do{
        pub.publish(kumanda);
        double t1 = ros::Time::now().toSec();
        current_distance = speed * (t1-t0);
        ros::spinOnce();
        loop_rate.sleep();
        //cout<<(t1-t0)<<", "<<current_distance <<", "<<distance<<endl;
    }while(current_distance<distance);
    kumanda.linear.x =0;
    pub.publish(kumanda);

}
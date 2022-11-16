#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>
#include <stdlib.h>

void move_forward(double speed, double distance, bool isForward);
void move_r(double speed, double distance);
void move_l(double speed, double distance);

void callback(const sensor_msgs::LaserScan::ConstPtr& msg){  
    ROS_INFO("message : %f", msg->ranges[360]);            
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "solver");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    ros::Subscriber sub = n.subscribe("scan", 1000, callback);
    ros::Rate loop_rate(10);


    while(ros::ok()){
        geometry_msgs::Twist kumanda;
        sensor_msgs::LaserScan mesafe;
        move_forward(0.25, 5, 1);
        //move_r(0.75, -1);
        //move_l(0.75, 1);
    }

    
    return 0;

}



void move_forward(double speed, double distance, bool isForward){
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    geometry_msgs::Twist kumanda;
    
    if (isForward)
        kumanda.linear.x =abs(speed);
    else
        kumanda.linear.x =-abs(speed);
    kumanda.linear.y =0;
    kumanda.linear.z =0;
    
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
        
    }while(current_distance<distance);
    kumanda.linear.x =0;
    pub.publish(kumanda);

}

void move_r(double speed, double distance){
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    geometry_msgs::Twist kumanda;
    
    
    kumanda.linear.x =  abs(speed);
    kumanda.linear.y = 0;
    kumanda.linear.z = 0;
    
    kumanda.angular.x = 0;
    kumanda.angular.y = 0;
    kumanda.angular.z = abs(speed);

    double t0 = ros::Time::now().toSec();
    double current_distance = 0.0;
    ros::Rate loop_rate(100);
    do{
        pub.publish(kumanda);
        double t1 = ros::Time::now().toSec();
        current_distance = speed * (t1-t0);
        ros::spinOnce();
        loop_rate.sleep();
        
    }while(current_distance<distance);
    kumanda.linear.x =0;
    pub.publish(kumanda);

}

void move_l(double speed, double distance){
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    geometry_msgs::Twist kumanda;

    kumanda.linear.x = abs(speed);
    kumanda.linear.y = 0;
    kumanda.linear.z = 0;
    
    kumanda.angular.x = 0;
    kumanda.angular.y = 0;
    kumanda.angular.z = -abs(speed);

    double t0 = ros::Time::now().toSec();
    double current_distance = 0.0;
    ros::Rate loop_rate(100);
    do{
        pub.publish(kumanda);
        double t1 = ros::Time::now().toSec();
        current_distance = speed * (t1-t0);
        ros::spinOnce();
        loop_rate.sleep();
        
    }while(current_distance<distance);
    kumanda.linear.x =0;
    pub.publish(kumanda);

}

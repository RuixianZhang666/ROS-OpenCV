#include<ros/ros.h> //ros标准库头文件
#include<iostream> //C++标准输入输出库
/*
  cv_bridge中包含CvBridge库
*/
#include<cv_bridge/cv_bridge.h> 
/*
  ROS图象类型的编码函数
*/
#include<sensor_msgs/image_encodings.h> 
/*
   image_transport 头文件用来在ROS系统中的话题上发布和订阅图象消息
*/
#include<image_transport/image_transport.h> 

//OpenCV2标准头文件
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
   
 int main(int argc, char** argv)  
    {  
      ros::init(argc, argv, "image_publisher");  
      ros::NodeHandle nh;  
      image_transport::ImageTransport it(nh);  
      image_transport::Publisher pub = it.advertise("camera/image", 1);  
      cv::Mat image = cv::imread("/home/zrxlovedjl/Pictures/3.jpg", CV_LOAD_IMAGE_COLOR);
      //cv::Mat element=getStructuringElement(MORPH_RECT, Size(15, 15));  
      cv::waitKey(30);
      cv::Mat imageout; 
      //cv::cvtColor(image, imageout, CV_RGB2GRAY);
      sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();  
      
      ros::Rate loop_rate(5);  
      while (nh.ok()) {  
        pub.publish(msg);  
        ros::spinOnce();  
        loop_rate.sleep();  
      }  
    }  

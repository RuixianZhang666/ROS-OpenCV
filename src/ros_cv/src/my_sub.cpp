    #include <ros/ros.h>  
    #include <image_transport/image_transport.h>  
    #include <opencv2/highgui/highgui.hpp>  
    #include <cv_bridge/cv_bridge.h>  
      
    void imageCallback(const sensor_msgs::ImageConstPtr& msg)  
    {  
	cv_bridge::CvImagePtr cv_ptr; // 声明一个CvImage指针的实例
      try  
      {  
        cv_ptr =  cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);  
      }  
      catch (cv_bridge::Exception& e)  
      {  
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());  
      }
	cv::imshow("view",cv_ptr->image);
	  //image_process(cv_ptr->image); //得到了cv::Mat类型的图象，在CvImage指针的image中，将结果传送给处理函数    
    }  
      
    int main(int argc, char **argv)  
    {  
      ros::init(argc, argv, "image_listener");  
      ros::NodeHandle nh;  
      cv::namedWindow("view");  
      cv::startWindowThread();  
      image_transport::ImageTransport it(nh);  
      image_transport::Subscriber sub = it.subscribe("camera/image", 1, imageCallback);  
      ros::spin();  
      cv::destroyWindow("view");  
    }  

 #include <opencv2\opencv.hpp>
 #include <iostream>
 #include <string>
using namespace cv;
 using namespace std;
 void main()
 {

		IplImage * src = cvLoadImage("G:\\seg17\\heben2.jpg");//cvCreateImage(cvSize(512,512), input->depth, input->nChannels );//原图像的定义
		//IplImage * result = cvCloneImage(src);
		IplImage* markers = cvCreateImage( cvGetSize(src), IPL_DEPTH_32S, 1 );

		cvZero( markers );

		unsigned int* plate_data = (unsigned int*)markers->imageData;
		//(1)逐列扫描图像像素点
		int temp_width = markers->width;
		int x = (markers->width)/2;
		int temp_height = markers->height;
		int y = (markers->height)/2;
		int r = ((x+y))/3;
		//cout<<x<<"   "<<y<<endl;
		int temp_step = markers->widthStep;
		//int n = markers->nChannels;
		for(int i = 0; i < temp_width; i++)

		{
			for(int j = 0; j < temp_height; j++)

			{
				int d = sqrt(pow(i-x,2.0) +pow(y-j,2.0));
				//cout<<d<<endl;
				if(d>r)//背景点在四周
				{	plate_data[j * temp_width + i*markers->nChannels] =2000000;//四周的点为背景点
				//cout<<d<<endl;
				}
					
				else if(d<=r )//目标点10*10
					plate_data[j * temp_width + i*markers->nChannels] =10000;//中间的点为目标点 
					
			}
		}

	

		IplImage *result= src;
		cvNamedWindow("result2",1);
		cvShowImage("result2",result);

		// paint the watershed image
			for(int i = 0; i < markers->height; i++ )
				for(int j = 0; j < markers->width; j++ )
				{
					int idx = CV_IMAGE_ELEM( markers, int, i, j );//markers的数据类型为IPL_DEPTH_32S  CV_IMAGE_ELEM读取某点的像素
					uchar* dst = &CV_IMAGE_ELEM(result, uchar, i, j*3 );//BGR三个通道的数是一起的,故要j*3
					if( idx == -1 ) //输出时若为-1，表示各个部分的边界
						dst[0] = dst[1] = dst[2] = (uchar)255;
					else if( idx < 0 )  //异常情况
						dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
					else if( idx == 10000 )//正常情况,目标区域
					{}
					else
						dst[0] = dst[1] = dst[2] = (uchar)255;//使背景变白,像素<255

				}

		cvNamedWindow("mask",1);
		cvShowImage("mask",markers);
		cvNamedWindow("result",1);
		cvShowImage("result",result);
		cvWaitKey(0);
		

 }
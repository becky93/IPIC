 #include <opencv2\opencv.hpp>
 #include <iostream>
 #include <string>
 #include<D:\我的资料库\Documents\Visual Studio 2010\Projects\test\test\corse.h>
  #include<D:\我的资料库\Documents\Visual Studio 2010\Projects\test\test\download.h>
using namespace cv;
 using namespace std;
 void main()
 {

		IplImage * src = cvLoadImage("E:\\seg17\\guilunmei.jpg");//cvCreateImage(cvSize(512,512), input->depth, input->nChannels );//原图像的定义
		IplImage * result = cvCloneImage(src);
		//IplImage* markers = cvCreateImage( cvGetSize(src), IPL_DEPTH_32S, 1 );

		//cvZero( markers );

		//unsigned int* plate_data = (unsigned int*)markers->imageData;
		////(1)逐列扫描图像像素点
		//int temp_width = markers->width;
		//int temp_height = markers->height;
		//int temp_step = markers->widthStep;
		////int n = markers->nChannels;
		//for(int i = 0; i < temp_width; i++)

		//{
		//	for(int j = 0; j < temp_height; j++)

		//	{
		//		if(( ( j < temp_height/10.0 ) || ( j >  temp_height * 9/10.0 ) ) &&( (i < ( temp_width ) / 10.0 )|| (i >( temp_width) *9/10.0 )) )//背景点在四周
		//			plate_data[j * temp_width + i*markers->nChannels] =2000000;//四周的点为背景点
		//			/*for(int k=0;k<n;k++)
		//				plate_data[j * temp_step + (i)*n+k] = 255;*/
		//		else if( ( j > ( temp_height/2.0-50 ) ) && ( j < ( temp_height/2.0+50 ) ) && ( i > ( temp_width/2.0-50 ) ) && ( i < ( temp_width/2.0+50 ) ) )//目标点10*10
		//			plate_data[j * temp_width + i*markers->nChannels] =10000;//中间的点为目标点 
		//			/*for(int k=0;k<n;k++)
		//				plate_data[j * temp_step + (i)*n+k] = 128;*/
		//		else 
		//			//plate_data[j * temp_step + i*markers->nChannels] =0;//其余点不重要	 
		//			plate_data[j * temp_width + i*markers->nChannels] =0;//其余点不重要	 
		//			/*for(int k=0;k<n;k++)
		//				plate_data[j * temp_step + (i)*n+k] = 1;*/
		//	}
		//}


		//cvWatershed(src,markers);
	

		//IplImage *result= src;
		//cvNamedWindow("result2",1);
		//cvShowImage("result2",result);

		//// paint the watershed image
		//	for(int i = 0; i < markers->height; i++ )
		//		for(int j = 0; j < markers->width; j++ )
		//		{
		//			int idx = CV_IMAGE_ELEM( markers, int, i, j );//markers的数据类型为IPL_DEPTH_32S  CV_IMAGE_ELEM读取某点的像素
		//			uchar* dst = &CV_IMAGE_ELEM(result, uchar, i, j*3 );//BGR三个通道的数是一起的,故要j*3
		//			if( idx == -1 ) //输出时若为-1，表示各个部分的边界
		//				dst[0] = dst[1] = dst[2] = (uchar)255;
		//			else if( idx < 0 )  //异常情况
		//				dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
		//			else if( idx == 10000 )//正常情况,目标区域
		//			{}
		//			else
		//				dst[0] = dst[1] = dst[2] = (uchar)255;//使背景变白,像素<255

		//		}

		//cvNamedWindow("mask",1);
		//cvShowImage("mask",markers);
		//cvNamedWindow("result",1);
		//cvShowImage("result",result);
		//cvWaitKey(0);
		IplImage * copy = cvCloneImage(src);
		IplImage * src2 = cvLoadImage("E:\\seg17\\rain.jpg");

		cvResize(src2,copy,CV_INTER_LINEAR);
		cvAddWeighted( copy,0.5,src,0.5,30,copy);
		cvNamedWindow("resultpaomo",1);
		cvShowImage("resultpaomo",copy);
		cvWaitKey(0);

		//corse(src,srcmask,result1,result1mask,k);
		

 }
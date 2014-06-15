#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include<D:\�ҵ����Ͽ�\Documents\Visual Studio 2010\Projects\test\test\download.h>
using namespace cv;
using namespace std;
void corse(IplImage * src,IplImage * srcmask,IplImage * result,IplImage * resultmask,int k)//����ԭͼ��ԭͼ�����룬�ֲڲ������Լ����ͼ���������
{
	IplImage * temp1 = src;
	IplImage * temp2 = srcmask;
	//cvZero(srcmask);
	for(int i=0;i<k;i++)
	{
		IplImage * tempa = cvCreateImage(           //ԭͼ��Ĵ���
			cvSize( temp1->width/2, temp1->height/2 ),  
			temp1->depth,  
			temp1->nChannels  
			);  
		cvPyrDown(temp1,tempa ,CV_GAUSSIAN_5x5); 
		temp1=tempa;

		IplImage * tempb = cvCreateImage(           //ԭͼ������Ĵ���
			cvSize( temp2->width/2, temp2->height/2 ),  
			temp2->depth,  
			temp2->nChannels  
			);  
		cvPyrDown(temp2,tempb,CV_GAUSSIAN_5x5);  
		temp2=tempb;
	}
	result = temp1;
	resultmask = temp2;

	IplImage* markers = cvCreateImage( cvGetSize( result), IPL_DEPTH_32S, 1 );

	cvZero( markers );

	unsigned int* plate_data = (unsigned int*)markers->imageData;
	//(1)����ɨ��ͼ�����ص�
	int temp_width = markers->width;
	int temp_height = markers->height;
	int temp_step = markers->widthStep;
	//int n = markers->nChannels;
	for(int i = 0; i < temp_width; i++)

	{
		for(int j = 0; j < temp_height; j++)

		{
			if(( ( j < temp_height/10.0 ) || ( j >  temp_height * 9/10.0 ) ) &&( (i < ( temp_width ) / 10.0 )|| (i >( temp_width) *9/10.0 )) )//������������
				plate_data[j * temp_width + i*markers->nChannels] =2000000;//���ܵĵ�Ϊ������
				/*for(int k=0;k<n;k++)
					plate_data[j * temp_step + (i)*n+k] = 255;*/
			else if( ( j > ( temp_height/2.0-10 ) ) && ( j < ( temp_height/2.0+10 ) ) && ( i > ( temp_width/2.0-10 ) ) && ( i < ( temp_width/2.0+10 ) ) )//Ŀ���10*10
				plate_data[j * temp_width + i*markers->nChannels] =10000;//�м�ĵ�ΪĿ��� 
				/*for(int k=0;k<n;k++)
					plate_data[j * temp_step + (i)*n+k] = 128;*/
			else 
				//plate_data[j * temp_step + i*markers->nChannels] =0;//����㲻��Ҫ	 
				plate_data[j * temp_width + i*markers->nChannels] =0;//����㲻��Ҫ	 
				/*for(int k=0;k<n;k++)
					plate_data[j * temp_step + (i)*n+k] = 1;*/
		}
	}

	//288
	//216
	//cout<<plate_data[288 * temp_step + 576];

	
	cvNamedWindow("maskf",1);
	cvShowImage("maskf",markers);
	ori(result);
	cvWatershed(result,markers);
	
	
	cvNamedWindow("result",1);
	cvShowImage("result",result);
	cvNamedWindow("mask",1);
	cvShowImage("mask",markers);
	
	cvWaitKey(0);

}
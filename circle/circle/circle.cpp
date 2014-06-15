 #include <opencv2\opencv.hpp>
 #include <iostream>
 #include <string>
using namespace cv;
 using namespace std;
 void main()
 {

		IplImage * src = cvLoadImage("G:\\seg17\\heben2.jpg");//cvCreateImage(cvSize(512,512), input->depth, input->nChannels );//ԭͼ��Ķ���
		//IplImage * result = cvCloneImage(src);
		IplImage* markers = cvCreateImage( cvGetSize(src), IPL_DEPTH_32S, 1 );

		cvZero( markers );

		unsigned int* plate_data = (unsigned int*)markers->imageData;
		//(1)����ɨ��ͼ�����ص�
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
				if(d>r)//������������
				{	plate_data[j * temp_width + i*markers->nChannels] =2000000;//���ܵĵ�Ϊ������
				//cout<<d<<endl;
				}
					
				else if(d<=r )//Ŀ���10*10
					plate_data[j * temp_width + i*markers->nChannels] =10000;//�м�ĵ�ΪĿ��� 
					
			}
		}

	

		IplImage *result= src;
		cvNamedWindow("result2",1);
		cvShowImage("result2",result);

		// paint the watershed image
			for(int i = 0; i < markers->height; i++ )
				for(int j = 0; j < markers->width; j++ )
				{
					int idx = CV_IMAGE_ELEM( markers, int, i, j );//markers����������ΪIPL_DEPTH_32S  CV_IMAGE_ELEM��ȡĳ�������
					uchar* dst = &CV_IMAGE_ELEM(result, uchar, i, j*3 );//BGR����ͨ��������һ���,��Ҫj*3
					if( idx == -1 ) //���ʱ��Ϊ-1����ʾ�������ֵı߽�
						dst[0] = dst[1] = dst[2] = (uchar)255;
					else if( idx < 0 )  //�쳣���
						dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
					else if( idx == 10000 )//�������,Ŀ������
					{}
					else
						dst[0] = dst[1] = dst[2] = (uchar)255;//ʹ�������,����<255

				}

		cvNamedWindow("mask",1);
		cvShowImage("mask",markers);
		cvNamedWindow("result",1);
		cvShowImage("result",result);
		cvWaitKey(0);
		

 }
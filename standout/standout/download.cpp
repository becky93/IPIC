// #include <opencv2\opencv.hpp>
// #include <iostream>
// #include <string>
// using namespace cv;
// using namespace std;
////using System;
//using System.Collectionsi.Generc;
//using System.ComponentModel;
//using System.Data;
//using System.Drawing;
//using System.Linq;
//using System.Text;
//using System.Windows.Forms;
//using System.Diagnostics;
//using System.Runtime.InteropServices;
//using Emgu.CV;
//using Emgu.CV.CvEnum;
//using Emgu.CV.Structure;
//using Emgu.CV.UI;
//
//namespace ImageProcessLearn
//{
//     partial class FormImageSegment : Form
//    {
//        //��Ա����
//        private string sourceImageFileName = "wky_tms_2272x1704.jpg";//Դͼ���ļ���
//        private Image<Bgr, Byte> imageSource = null;                //Դͼ��
//        private Image<Bgr, Byte> imageSourceClone = null;           //Դͼ��Ŀ�¡
//        private Image<Gray, Int32> imageMarkers = null;              //���ͼ��
//        private double xScale = 1d;                                 //ԭʼͼ����PictureBox��x�᷽���ϵ�����
//        private double yScale = 1d;                                 //ԭʼͼ����PictureBox��y�᷽���ϵ�����
//        private Point previousMouseLocation = new Point(-1, -1);    //�ϴλ�������ʱ�����������λ��
//        private const int LineWidth = 5;                            //���������Ŀ��
//        private int drawCount = 1;                                  //�û����Ƶ�������Ŀ������ָ����������ɫ
//        
//        public FormImageSegment()
//        {
//            InitializeComponent();
//        }
//
//        //�������ʱ
//        private void FormImageSegment_Load(object sender, EventArgs e)
//        {
//            //������ʾ
//            toolTip.SetToolTip(rbWatershed, "������Դͼ�����������ƴ��·ָ��������������������ڷ�ˮ���㷨");
//            toolTip.SetToolTip(txtPSLevel, "������������ͼ��ߴ��йأ���ֵֻ����ͼ��ߴ类2�����Ĵ��������򽫵ó�������");
//            toolTip.SetToolTip(txtPSThreshold1, "�������ӵĴ���ֵ");
//            toolTip.SetToolTip(txtPSThreshold2, "�ָ�صĴ���ֵ");
//            toolTip.SetToolTip(txtPMSFSpatialRadius, "�ռ䴰�İ뾶");
//            toolTip.SetToolTip(txtPMSFColorRadius, "ɫ�ʴ��İ뾶");
//            toolTip.SetToolTip(btnClearMarkers, "���������Դͼ���ϣ����ڷ�ˮ���㷨�Ĵ��·ָ���������");
//            //����ͼ��
//            LoadImage();
//        }
//
//        //������ر�ʱ���ͷ���Դ
//        private void FormImageSegment_FormClosing(object sender, FormClosingEventArgs e)
//        {
//            if (imageSource != null)
//                imageSource.Dispose();
//            if (imageSourceClone != null)
//                imageSourceClone.Dispose();
//            if (imageMarkers != null)
//                imageMarkers.Dispose();
//        }
//
//        //����Դͼ��
//        private void btnLoadImage_Click(object sender, EventArgs e)
//        {
//            OpenFileDialog ofd = new OpenFileDialog();
//            ofd.CheckFileExists = true;
//            ofd.DefaultExt = "jpg";
//            ofd.Filter = "ͼƬ�ļ�|*.jpg;*.png;*.bmp|�����ļ�|*.*";
//            if (ofd.ShowDialog(this) == DialogResult.OK)
//            {
//                if (ofd.FileName != "")
//                {
//                    sourceImageFileName = ofd.FileName;
//                    LoadImage();
//                }
//            }
//            ofd.Dispose();
//        }
//
//        //����ָ�����
//        private void btnClearMarkers_Click(object sender, EventArgs e)
//        {
//            if (imageSourceClone != null)
//                imageSourceClone.Dispose();
//            imageSourceClone = imageSource.Copy();
//            pbSource.Image = imageSourceClone.Bitmap;
//            imageMarkers.SetZero();
//            drawCount = 1;
//        }
//
//        //����갴�²���Դͼ�����ƶ�ʱ����Դͼ���ϻ��Ʒָ�����
//        private void pbSource_MouseMove(object sender, MouseEventArgs e)
//        {
//            //������������
//            if (e.Button == MouseButtons.Left)
//            {
//                if (previousMouseLocation.X >= 0 && previousMouseLocation.Y >= 0)
//                {
//                    Point p1 = new Point((int)(previousMouseLocation.X * xScale), (int)(previousMouseLocation.Y * yScale));
//                    Point p2 = new Point((int)(e.Location.X * xScale), (int)(e.Location.Y * yScale));
//                    LineSegment2D ls = new LineSegment2D(p1, p2);
//                    int thickness = (int)(LineWidth * xScale);
//                    imageSourceClone.Draw(ls, new Bgr(255d, 255d, 255d), thickness);
//                    pbSource.Image = imageSourceClone.Bitmap;
//                    imageMarkers.Draw(ls, new Gray(drawCount), thickness);
//                }
//                previousMouseLocation = e.Location;
//            }
//        }
//
//        //���ɿ�������ʱ������ͼ��ǰһλ������Ϊ��-1��-1��
//        private void pbSource_MouseUp(object sender, MouseEventArgs e)
//        {
//            previousMouseLocation = new Point(-1, -1);
//            drawCount++;
//        }
//
//        //����Դͼ��
//        private void LoadImage()
//        {
//            if (imageSource != null)
//                imageSource.Dispose();
//            imageSource = new Image<Bgr, byte>(sourceImageFileName);
//            if (imageSourceClone != null)
//                imageSourceClone.Dispose();
//            imageSourceClone = imageSource.Copy();
//            pbSource.Image = imageSourceClone.Bitmap;
//            if (imageMarkers != null)
//                imageMarkers.Dispose();
//            imageMarkers = new Image<Gray, Int32>(imageSource.Size);
//            imageMarkers.SetZero();
//            xScale = 1d * imageSource.Width / pbSource.Width;
//            yScale = 1d * imageSource.Height / pbSource.Height;
//            drawCount = 1;
//        }
//
//        //�ָ�ͼ��
//        private void btnImageSegment_Click(object sender, EventArgs e)
//        {
//            if (rbWatershed.Checked)
//                txtResult.Text += Watershed();
//            else if (rbPrySegmentation.Checked)
//                txtResult.Text += PrySegmentation();
//            else if (rbPryMeanShiftFiltering.Checked)
//                txtResult.Text += PryMeanShiftFiltering();
//        }
//
//        /// <summary>
//        /// ��ˮ���㷨ͼ��ָ�
//        /// </summary>
//        /// <returns>������ʱ</returns>
//        private string Watershed()
//        {
//            //��ˮ���㷨�ָ�
//            Image<Gray, Int32> imageMarkers2 = imageMarkers.Copy();
//            Stopwatch sw = new Stopwatch();
//            sw.Start();
//            CvInvoke.cvWatershed(imageSource.Ptr, imageMarkers2.Ptr);
//            sw.Stop();
//            //���ָ�Ľ��ת����256���Ҷ�ͼ��
//            pbResult.Image = imageMarkers2.Bitmap;
//            imageMarkers2.Dispose();
//            return string.Format("��ˮ��ͼ��ָ��ʱ��{0:F05}���롣\r\n", sw.Elapsed.TotalMilliseconds);
//        }
//
//        /// <summary>
//        /// �������ָ��㷨
//        /// </summary>
//        /// <returns></returns>
//        private string PrySegmentation()
//        {
//            //׼������
//            Image<Bgr, Byte> imageDest = new Image<Bgr, byte>(imageSource.Size);
//            MemStorage storage = new MemStorage();
//            IntPtr ptrComp = IntPtr.Zero;
//            int level = int.Parse(txtPSLevel.Text);
//            double threshold1 = double.Parse(txtPSThreshold1.Text);
//            double threshold2 = double.Parse(txtPSThreshold2.Text);
//            //�������ָ�
//            Stopwatch sw = new Stopwatch();
//            sw.Start();
//            CvInvoke.cvPyrSegmentation(imageSource.Ptr, imageDest.Ptr, storage.Ptr, out ptrComp, level, threshold1, threshold2);
//            sw.Stop();
//            //��ʾ���
//            pbResult.Image = imageDest.Bitmap;
//            //�ͷ���Դ
//            imageDest.Dispose();
//            storage.Dispose();
//            return string.Format("�������ָ��ʱ��{0:F05}���롣\r\n", sw.Elapsed.TotalMilliseconds);
//        }
//
//        /// <summary>
//        /// ��ֵƯ�Ʒָ��㷨
//        /// </summary>
//        /// <returns></returns>
//        private string PryMeanShiftFiltering()
//        {
//            //׼������
//            Image<Bgr, Byte> imageDest = new Image<Bgr, byte>(imageSource.Size);
//            double spatialRadius = double.Parse(txtPMSFSpatialRadius.Text);
//            double colorRadius = double.Parse(txtPMSFColorRadius.Text);
//            int maxLevel = int.Parse(txtPMSFNaxLevel.Text);
//            int maxIter = int.Parse(txtPMSFMaxIter.Text);
//            double epsilon = double.Parse(txtPMSFEpsilon.Text);
//            MCvTermCriteria termcrit = new MCvTermCriteria(maxIter, epsilon);
//            //��ֵƯ�Ʒָ�
//            Stopwatch sw = new Stopwatch();
//            sw.Start();
//            OpenCvInvoke.cvPyrMeanShiftFiltering(imageSource.Ptr, imageDest.Ptr, spatialRadius, colorRadius, maxLevel, termcrit);
//            sw.Stop();
//            //��ʾ���
//            pbResult.Image = imageDest.Bitmap;
//            //�ͷ���Դ
//            imageDest.Dispose();
//            return string.Format("��ֵƯ�Ʒָ��ʱ��{0:F05}���롣\r\n", sw.Elapsed.TotalMilliseconds);
//        }
//
//        /// <summary>
//        /// ���ı�������ָ�Ĳ�����������������ʱ���Բ�������У��
//        /// </summary>
//        /// <param name="sender"></param>
//        /// <param name="e"></param>
//        private void txtPSLevel_TextChanged(object sender, EventArgs e)
//        {
//            int level = int.Parse(txtPSLevel.Text);
//            if (level < 1 || imageSource.Width % (int)(Math.Pow(2, level - 1)) != 0 || imageSource.Height % (int)(Math.Pow(2, level - 1)) != 0)
//                MessageBox.Show(this, "ע�⣺������Ľ���������������Ҫ�󣬼��������ܻ���Ч��", "��������������");
//        }
//
//        /// <summary>
//        /// ���ı��ֵƯ�Ʒָ�Ĳ�����������������ʱ���Բ�������У��
//        /// </summary>
//        /// <param name="sender"></param>
//        /// <param name="e"></param>
//        private void txtPMSFNaxLevel_TextChanged(object sender, EventArgs e)
//        {
//            int maxLevel = int.Parse(txtPMSFNaxLevel.Text);
//            if (maxLevel < 0 || maxLevel > 8)
//                MessageBox.Show(this, "ע�⣺��ֵƯ�Ʒָ�Ľ���������ֻ����0��8֮�䡣", "��������������");
//        }
//    }
//}



#include<cv.h>
#include<highgui.h>
#include<iostream>

using namespace  std;

IplImage* marker_mask = 0;
IplImage* markers = 0;//Ŀ��ͼ��
IplImage* img0 = 0, *img = 0, *img_gray = 0, *wshed = 0;
CvPoint prev_pt = {-1,-1};
void on_mouse( int event, int x, int y, int flags, void* param )//opencv ���Զ�������������ʵ�ֵ
{
	if( !img )
		return;
	if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
		prev_pt = cvPoint(-1,-1);
	else if( event == CV_EVENT_LBUTTONDOWN )
		prev_pt = cvPoint(x,y);
	else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
	{
		CvPoint pt = cvPoint(x,y);
		if( prev_pt.x < 0 )
			prev_pt = pt;
		cvLine( marker_mask, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );//CvScalar ��Ա��double val[4] RGBAֵA=alpha
		cvLine( img, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
		prev_pt = pt;
		cvShowImage( "image", img);
	}
}
int ori(IplImage * src)
{
	//char* filename = argc >= 2 ? argv[1] : (char*)"fruits.jpg";
	CvMemStorage* storage = cvCreateMemStorage(0);//��̬�ڴ�洢���������� http://blog.sina.com.cn/s/blog_4f8d956b0100hqqn.html
	CvRNG rng = cvRNG(-1);//����������� http://blog.csdn.net/wobuaishangdiao/article/details/7693267
	if( (img0 = src) == 0 )
		return 0;
	printf( "Hot keys: \n"
		"\tESC - quit the program\n"
		"\tr - restore the original image\n"
		"\tw or SPACE - run watershed algorithm\n"
		"\t\t(before running it, roughly mark the areas on the image)\n"
		"\t  (before that, roughly outline several markers on the image)\n" );
	cvNamedWindow( "image", 1 );
	cvNamedWindow( "watershed transform", 1 );
	img = cvCloneImage( img0 );
	img_gray = cvCloneImage( img0 );
	wshed = cvCloneImage( img0 );
	marker_mask = cvCreateImage( cvGetSize(img), 8, 1 );
	markers = cvCreateImage( cvGetSize(img), IPL_DEPTH_32S, 1 );
	cvCvtColor( img, marker_mask, CV_BGR2GRAY );
	cvCvtColor( marker_mask, img_gray, CV_GRAY2BGR );//������ֻ�ý�RGBת��3ͨ���ĻҶ�ͼ��R=G=B,������ʾ��
	cvZero( marker_mask );
	cvZero( wshed );
	cvShowImage( "image", img );
	//cvShowImage( "watershed transform", wshed );
	cvSetMouseCallback( "image", on_mouse, 0 );
	for(;;)
	{
		int c = cvWaitKey(0);
		if( (char)c == 27 )
			break;
		if( (char)c == 'r' )
		{
			cvZero( marker_mask );
			cvCopy( img0, img );//cvCopy����Ҳ���������ã���Ӱ��ԭimg0ͼ��Ҳ��ʱ����
			cvShowImage( "image", img );
		}
		if( (char)c == 'w' || (char)c == ' ' )
		{
			CvSeq* contours = 0;
			CvMat* color_tab = 0;
			int i, j, comp_count = 0;

			//����ѡ����ǵ�ͼ��ȡ��������, ��ÿ�������ò�ͬ��������ʾ
			//��ͬ������ʹ�÷�ˮ���㷨ʱ���ͳ�Ϊ��ͬ�����ӵ�
			//�㷨���������Ը�����ͬ�����ӵ�Ϊ��������
			cvClearMemStorage(storage);
			cvFindContours( marker_mask, storage, &contours, sizeof(CvContour),
				CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
			cvZero( markers );
			for( ; contours != 0; contours = contours->h_next, comp_count++ )
			{
				cvDrawContours(markers, contours, cvScalarAll(comp_count+1),
					cvScalarAll(comp_count+1), -1, -1, 8, cvPoint(0,0) );
			}
			//cvShowImage("image",markers);
			if( comp_count == 0 )
				continue;
			color_tab = cvCreateMat( 1, comp_count, CV_8UC3 );//���������ɫ�б�
			for( i = 0; i < comp_count; i++ )

			{
				uchar* ptr = color_tab->data.ptr + i*3;
				ptr[0] = (uchar)(cvRandInt(&rng)%180 + 50);
				ptr[1] = (uchar)(cvRandInt(&rng)%180 + 50);
				ptr[2] = (uchar)(cvRandInt(&rng)%180 + 50);
			}
			{
				double t = (double)cvGetTickCount();
				cvWatershed( img0, markers );//cvShowImage( "image", markers);
				cvSave("img0.xml",markers);
				t = (double)cvGetTickCount() - t;
				printf( "exec time = %gms\n", t/(cvGetTickFrequency()*1000.) );
			}

			IplImage *wshed111= cvCloneImage(img0);


			for(int i = 0; i < markers->height; i++ )
			for(int j = 0; j < markers->width; j++ )
			{
				int idx = CV_IMAGE_ELEM( markers, int, i, j );//markers����������ΪIPL_DEPTH_32S
				uchar* dst = &CV_IMAGE_ELEM(wshed111, uchar, i, j*3 );//wshed, uchar, i, j*3 );//BGR����ͨ��������һ���,��Ҫj*3
				if( idx == -1 ) //���ʱ��Ϊ-1����ʾ�������ֵı߽�
					dst[0] = dst[1] = dst[2] = (uchar)255;
				else if(idx == 2 ) 
				{}//dst[0] = dst[1] = dst[2] = (uchar)0;
				/*{
						dst[0] = origin[0];
						dst[1] = origin[1];
						dst[2] = origin[2];
				}	*/			
				else
					dst[0] = dst[1] = dst[2] = (uchar)0;//128;
				/*{
						dst[0] = origin[0];
						dst[1] = origin[1];
						dst[2] = origin[2];
				}*/
			}cvShowImage( "watershed transform", wshed111 );

			// paint the watershed image
			for( i = 0; i < markers->height; i++ )
				for( j = 0; j < markers->width; j++ )
				{
					int idx = CV_IMAGE_ELEM( markers, int, i, j );//markers����������ΪIPL_DEPTH_32S
					uchar* dst = &CV_IMAGE_ELEM( wshed, uchar, i, j*3 );//BGR����ͨ��������һ���,��Ҫj*3
					if( idx == -1 ) //���ʱ��Ϊ-1����ʾ�������ֵı߽�
						dst[0] = dst[1] = dst[2] = (uchar)255;
					else if( idx <= 0 || idx > comp_count )  //�쳣���
						dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
					else //�������
					{
						uchar* ptr = color_tab->data.ptr + (idx-1)*3;
						dst[0] = ptr[0]; dst[1] = ptr[1]; dst[2] = ptr[2];
					}
				}
				cvAddWeighted( wshed, 0.5, img_gray, 0.5, 0, wshed );//wshed.x.y=0.5*wshed.x.y+0.5*img_gray+0��Ȩ�ں�ͼ��
				//cvShowImage( "watershed transform", wshed );
				cvReleaseMat( &color_tab );
		}
	}
	return 1;
}

int mark(IplImage * src)// int argc, char** argv )
{
	//char* filename = argc >= 2 ? argv[1] : (char*)"SAM_1008.BMP";
	CvMemStorage* storage = cvCreateMemStorage(0);//��̬�ڴ�洢���������� http://blog.sina.com.cn/s/blog_4f8d956b0100hqqn.html
	CvRNG rng = cvRNG(-1);//����������� http://blog.csdn.net/wobuaishangdiao/article/details/7693267
	if( (img0 = src) == 0 )
		return 0;
	printf( "Hot keys: \n"
		"\tESC - quit the program\n"
		"\tr - restore the original image\n"
		"\tw or SPACE - run watershed algorithm\n"
		"\t\t(before running it, roughly mark the areas on the image)\n"
		"\t  (before that, roughly outline several markers on the image)\n" );
	cvNamedWindow( "image", 1 );
	cvNamedWindow( "watershed transform", 1 );
	img = cvCloneImage( img0 ); 
	img_gray = cvCloneImage( img0 );
	wshed = cvCloneImage( img0 );
	marker_mask = cvCreateImage( cvGetSize(img), 8, 1 );
	markers = cvCreateImage( cvGetSize(img), IPL_DEPTH_32S, 1 );
	cvCvtColor( img, marker_mask, CV_BGR2GRAY );//http://blog.csdn.net/wanglp094/article/details/7646464
	cvCvtColor( marker_mask, img_gray, CV_GRAY2BGR );//������ֻ�ý�RGBת��3ͨ���ĻҶ�ͼ��R=G=B,������ʾ��
	cvZero( marker_mask );
	cvZero( wshed );
	cvShowImage( "image", img );//������޸ĺ��ͼ��
	cvShowImage( "watershed transform", wshed );//����ϴ�����ͼ��
	cvSetMouseCallback( "image", on_mouse, 0 );
	for(;;)
	{
		int c = cvWaitKey(0);
		if( (char)c == 27 )
			break;
		if( (char)c == 'r' )
		{
			cvZero( marker_mask );//����ͼ��
			cvCopy( img0, img );//cvCopy����Ҳ���������ã���Ӱ��ԭimg0ͼ��Ҳ��ʱ����
			cvShowImage( "image", img );
		}
		if( (char)c == 'w' || (char)c == ' ' )
		{
			CvSeq* contours = 0;
			CvMat* color_tab = 0;
			int i, j, comp_count = 0;

			//����ѡ����ǵ�ͼ��ȡ��������, ��ÿ�������ò�ͬ��������ʾ
			//��ͬ������ʹ�÷�ˮ���㷨ʱ���ͳ�Ϊ��ͬ�����ӵ�
			//�㷨���������Ը�����ͬ�����ӵ�Ϊ��������
			cvClearMemStorage(storage);//�ͷ��ڴ��
			cvFindContours( marker_mask, storage, &contours, sizeof(CvContour),//http://blog.sina.com.cn/s/blog_4bc179a80100hs50.html
				CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
			cvZero( markers );
			for( ; contours != 0; contours = contours->h_next, comp_count++ )
			{
				cvDrawContours(markers, contours, cvScalarAll(comp_count+1),//http://blog.csdn.net/fengbingchun/article/details/5971759
					cvScalarAll(comp_count+1), -1, -1, 8, cvPoint(0,0) );
			}
			cvShowImage("image",markers);
			if( comp_count == 0 )
				continue;
			color_tab = cvCreateMat( 1, comp_count, CV_8UC3 );//���������ɫ�б�
			for( i = 0; i < comp_count; i++ )

			{
				uchar* ptr = color_tab->data.ptr + i*3;
				ptr[0] = (uchar)(cvRandInt(&rng)%180 + 50);
				ptr[1] = (uchar)(cvRandInt(&rng)%180 + 50);
				ptr[2] = (uchar)(cvRandInt(&rng)%180 + 50);
			}
			{
				double t = (double)cvGetTickCount();
				cvWatershed( img0, markers );//�����Դ��������зָ�
				cvSave("img0.xml",markers);
				t = (double)cvGetTickCount() - t;
				printf( "exec time = %gms\n", t/(cvGetTickFrequency()*1000.) );
			}

			// paint the watershed image
			for( i = 0; i < markers->height; i++ )
				for( j = 0; j < markers->width; j++ )
				{
					int idx = CV_IMAGE_ELEM( markers, int, i, j );//markers����������ΪIPL_DEPTH_32S  CV_IMAGE_ELEM��ȡĳ�������
					uchar* dst = &CV_IMAGE_ELEM( wshed, uchar, i, j*3 );//BGR����ͨ��������һ���,��Ҫj*3
					if( idx == -1 ) //���ʱ��Ϊ-1����ʾ�������ֵı߽�
						dst[0] = dst[1] = dst[2] = (uchar)255;
					else if( idx <= 0 || idx > comp_count )  //�쳣���
						dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
					else if( idx == 1 )//�������,Ŀ������
					{}
						//uchar* ptr = color_tab->data.ptr + (idx-1)*3;
						//dst[0] = dst[1] = dst[2] = (uchar)0;//ʹĿ�꽨���Ӻڣ�����>255
						//dst[0] = ptr[0]; dst[1] = ptr[1]; dst[2] = ptr[2];
					//}
					else
						dst[0] = dst[1] = dst[2] = (uchar)255;//ʹ�������,����<255

				}
				//cvAddWeighted( wshed, 0.5, img_gray, 0.5, 0, wshed );//wshed.x.y=0.5*wshed.x.y+0.5*img_gray+0��Ȩ�ں�ͼ��
				cvShowImage( "watershed transform", wshed);
		
				cvReleaseMat( &color_tab );
		}
	}
	return 1;
}


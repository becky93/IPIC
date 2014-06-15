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
//        //成员变量
//        private string sourceImageFileName = "wky_tms_2272x1704.jpg";//源图像文件名
//        private Image<Bgr, Byte> imageSource = null;                //源图像
//        private Image<Bgr, Byte> imageSourceClone = null;           //源图像的克隆
//        private Image<Gray, Int32> imageMarkers = null;              //标记图像
//        private double xScale = 1d;                                 //原始图像与PictureBox在x轴方向上的缩放
//        private double yScale = 1d;                                 //原始图像与PictureBox在y轴方向上的缩放
//        private Point previousMouseLocation = new Point(-1, -1);    //上次绘制线条时，鼠标所处的位置
//        private const int LineWidth = 5;                            //绘制线条的宽度
//        private int drawCount = 1;                                  //用户绘制的线条数目，用于指定线条的颜色
//        
//        public FormImageSegment()
//        {
//            InitializeComponent();
//        }
//
//        //窗体加载时
//        private void FormImageSegment_Load(object sender, EventArgs e)
//        {
//            //设置提示
//            toolTip.SetToolTip(rbWatershed, "可以在源图像上用鼠标绘制大致分割区域线条，该线条用于分水岭算法");
//            toolTip.SetToolTip(txtPSLevel, "金字塔层数跟图像尺寸有关，该值只能是图像尺寸被2整除的次数，否则将得出错误结果");
//            toolTip.SetToolTip(txtPSThreshold1, "建立连接的错误阀值");
//            toolTip.SetToolTip(txtPSThreshold2, "分割簇的错误阀值");
//            toolTip.SetToolTip(txtPMSFSpatialRadius, "空间窗的半径");
//            toolTip.SetToolTip(txtPMSFColorRadius, "色彩窗的半径");
//            toolTip.SetToolTip(btnClearMarkers, "清除绘制在源图像上，用于分水岭算法的大致分割区域线条");
//            //加载图像
//            LoadImage();
//        }
//
//        //当窗体关闭时，释放资源
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
//        //加载源图像
//        private void btnLoadImage_Click(object sender, EventArgs e)
//        {
//            OpenFileDialog ofd = new OpenFileDialog();
//            ofd.CheckFileExists = true;
//            ofd.DefaultExt = "jpg";
//            ofd.Filter = "图片文件|*.jpg;*.png;*.bmp|所有文件|*.*";
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
//        //清除分割线条
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
//        //当鼠标按下并在源图像上移动时，在源图像上绘制分割线条
//        private void pbSource_MouseMove(object sender, MouseEventArgs e)
//        {
//            //如果按下了左键
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
//        //当松开鼠标左键时，将绘图的前一位置设置为（-1，-1）
//        private void pbSource_MouseUp(object sender, MouseEventArgs e)
//        {
//            previousMouseLocation = new Point(-1, -1);
//            drawCount++;
//        }
//
//        //加载源图像
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
//        //分割图像
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
//        /// 分水岭算法图像分割
//        /// </summary>
//        /// <returns>返回用时</returns>
//        private string Watershed()
//        {
//            //分水岭算法分割
//            Image<Gray, Int32> imageMarkers2 = imageMarkers.Copy();
//            Stopwatch sw = new Stopwatch();
//            sw.Start();
//            CvInvoke.cvWatershed(imageSource.Ptr, imageMarkers2.Ptr);
//            sw.Stop();
//            //将分割的结果转换到256级灰度图像
//            pbResult.Image = imageMarkers2.Bitmap;
//            imageMarkers2.Dispose();
//            return string.Format("分水岭图像分割，用时：{0:F05}毫秒。\r\n", sw.Elapsed.TotalMilliseconds);
//        }
//
//        /// <summary>
//        /// 金字塔分割算法
//        /// </summary>
//        /// <returns></returns>
//        private string PrySegmentation()
//        {
//            //准备参数
//            Image<Bgr, Byte> imageDest = new Image<Bgr, byte>(imageSource.Size);
//            MemStorage storage = new MemStorage();
//            IntPtr ptrComp = IntPtr.Zero;
//            int level = int.Parse(txtPSLevel.Text);
//            double threshold1 = double.Parse(txtPSThreshold1.Text);
//            double threshold2 = double.Parse(txtPSThreshold2.Text);
//            //金字塔分割
//            Stopwatch sw = new Stopwatch();
//            sw.Start();
//            CvInvoke.cvPyrSegmentation(imageSource.Ptr, imageDest.Ptr, storage.Ptr, out ptrComp, level, threshold1, threshold2);
//            sw.Stop();
//            //显示结果
//            pbResult.Image = imageDest.Bitmap;
//            //释放资源
//            imageDest.Dispose();
//            storage.Dispose();
//            return string.Format("金字塔分割，用时：{0:F05}毫秒。\r\n", sw.Elapsed.TotalMilliseconds);
//        }
//
//        /// <summary>
//        /// 均值漂移分割算法
//        /// </summary>
//        /// <returns></returns>
//        private string PryMeanShiftFiltering()
//        {
//            //准备参数
//            Image<Bgr, Byte> imageDest = new Image<Bgr, byte>(imageSource.Size);
//            double spatialRadius = double.Parse(txtPMSFSpatialRadius.Text);
//            double colorRadius = double.Parse(txtPMSFColorRadius.Text);
//            int maxLevel = int.Parse(txtPMSFNaxLevel.Text);
//            int maxIter = int.Parse(txtPMSFMaxIter.Text);
//            double epsilon = double.Parse(txtPMSFEpsilon.Text);
//            MCvTermCriteria termcrit = new MCvTermCriteria(maxIter, epsilon);
//            //均值漂移分割
//            Stopwatch sw = new Stopwatch();
//            sw.Start();
//            OpenCvInvoke.cvPyrMeanShiftFiltering(imageSource.Ptr, imageDest.Ptr, spatialRadius, colorRadius, maxLevel, termcrit);
//            sw.Stop();
//            //显示结果
//            pbResult.Image = imageDest.Bitmap;
//            //释放资源
//            imageDest.Dispose();
//            return string.Format("均值漂移分割，用时：{0:F05}毫秒。\r\n", sw.Elapsed.TotalMilliseconds);
//        }
//
//        /// <summary>
//        /// 当改变金字塔分割的参数“金字塔层数”时，对参数进行校验
//        /// </summary>
//        /// <param name="sender"></param>
//        /// <param name="e"></param>
//        private void txtPSLevel_TextChanged(object sender, EventArgs e)
//        {
//            int level = int.Parse(txtPSLevel.Text);
//            if (level < 1 || imageSource.Width % (int)(Math.Pow(2, level - 1)) != 0 || imageSource.Height % (int)(Math.Pow(2, level - 1)) != 0)
//                MessageBox.Show(this, "注意：您输入的金字塔层数不符合要求，计算结果可能会无效。", "金字塔层数错误");
//        }
//
//        /// <summary>
//        /// 当改变均值漂移分割的参数“金字塔层数”时，对参数进行校验
//        /// </summary>
//        /// <param name="sender"></param>
//        /// <param name="e"></param>
//        private void txtPMSFNaxLevel_TextChanged(object sender, EventArgs e)
//        {
//            int maxLevel = int.Parse(txtPMSFNaxLevel.Text);
//            if (maxLevel < 0 || maxLevel > 8)
//                MessageBox.Show(this, "注意：均值漂移分割的金字塔层数只能在0至8之间。", "金字塔层数错误");
//        }
//    }
//}



#include<cv.h>
#include<highgui.h>
#include<iostream>

using namespace  std;

IplImage* marker_mask = 0;
IplImage* markers = 0;//目标图像
IplImage* img0 = 0, *img = 0, *img_gray = 0, *wshed = 0;
CvPoint prev_pt = {-1,-1};
void on_mouse( int event, int x, int y, int flags, void* param )//opencv 会自动给函数传入合适的值
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
		cvLine( marker_mask, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );//CvScalar 成员：double val[4] RGBA值A=alpha
		cvLine( img, prev_pt, pt, cvScalarAll(255), 5, 8, 0 );
		prev_pt = pt;
		cvShowImage( "image", img);
	}
}
int ori(IplImage * src)
{
	//char* filename = argc >= 2 ? argv[1] : (char*)"fruits.jpg";
	CvMemStorage* storage = cvCreateMemStorage(0);//动态内存存储及操作函数 http://blog.sina.com.cn/s/blog_4f8d956b0100hqqn.html
	CvRNG rng = cvRNG(-1);//随机数生成器 http://blog.csdn.net/wobuaishangdiao/article/details/7693267
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
	cvCvtColor( marker_mask, img_gray, CV_GRAY2BGR );//这两句只用将RGB转成3通道的灰度图即R=G=B,用来显示用
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
			cvCopy( img0, img );//cvCopy（）也可以这样用，不影响原img0图像，也随时更新
			cvShowImage( "image", img );
		}
		if( (char)c == 'w' || (char)c == ' ' )
		{
			CvSeq* contours = 0;
			CvMat* color_tab = 0;
			int i, j, comp_count = 0;

			//下面选将标记的图像取得其轮廓, 将每种轮廓用不同的整数表示
			//不同的整数使用分水岭算法时，就成为不同的种子点
			//算法本来就是以各个不同的种子点为中心扩张
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
			color_tab = cvCreateMat( 1, comp_count, CV_8UC3 );//创建随机颜色列表
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
				int idx = CV_IMAGE_ELEM( markers, int, i, j );//markers的数据类型为IPL_DEPTH_32S
				uchar* dst = &CV_IMAGE_ELEM(wshed111, uchar, i, j*3 );//wshed, uchar, i, j*3 );//BGR三个通道的数是一起的,故要j*3
				if( idx == -1 ) //输出时若为-1，表示各个部分的边界
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
					int idx = CV_IMAGE_ELEM( markers, int, i, j );//markers的数据类型为IPL_DEPTH_32S
					uchar* dst = &CV_IMAGE_ELEM( wshed, uchar, i, j*3 );//BGR三个通道的数是一起的,故要j*3
					if( idx == -1 ) //输出时若为-1，表示各个部分的边界
						dst[0] = dst[1] = dst[2] = (uchar)255;
					else if( idx <= 0 || idx > comp_count )  //异常情况
						dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
					else //正常情况
					{
						uchar* ptr = color_tab->data.ptr + (idx-1)*3;
						dst[0] = ptr[0]; dst[1] = ptr[1]; dst[2] = ptr[2];
					}
				}
				cvAddWeighted( wshed, 0.5, img_gray, 0.5, 0, wshed );//wshed.x.y=0.5*wshed.x.y+0.5*img_gray+0加权融合图像
				//cvShowImage( "watershed transform", wshed );
				cvReleaseMat( &color_tab );
		}
	}
	return 1;
}

int mark(IplImage * src)// int argc, char** argv )
{
	//char* filename = argc >= 2 ? argv[1] : (char*)"SAM_1008.BMP";
	CvMemStorage* storage = cvCreateMemStorage(0);//动态内存存储及操作函数 http://blog.sina.com.cn/s/blog_4f8d956b0100hqqn.html
	CvRNG rng = cvRNG(-1);//随机数生成器 http://blog.csdn.net/wobuaishangdiao/article/details/7693267
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
	cvCvtColor( marker_mask, img_gray, CV_GRAY2BGR );//这两句只用将RGB转成3通道的灰度图即R=G=B,用来显示用
	cvZero( marker_mask );
	cvZero( wshed );
	cvShowImage( "image", img );//被鼠标修改后的图像
	cvShowImage( "watershed transform", wshed );//被“洗”后的图像
	cvSetMouseCallback( "image", on_mouse, 0 );
	for(;;)
	{
		int c = cvWaitKey(0);
		if( (char)c == 27 )
			break;
		if( (char)c == 'r' )
		{
			cvZero( marker_mask );//掩码图像
			cvCopy( img0, img );//cvCopy（）也可以这样用，不影响原img0图像，也随时更新
			cvShowImage( "image", img );
		}
		if( (char)c == 'w' || (char)c == ' ' )
		{
			CvSeq* contours = 0;
			CvMat* color_tab = 0;
			int i, j, comp_count = 0;

			//下面选将标记的图像取得其轮廓, 将每种轮廓用不同的整数表示
			//不同的整数使用分水岭算法时，就成为不同的种子点
			//算法本来就是以各个不同的种子点为中心扩张
			cvClearMemStorage(storage);//释放内存块
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
			color_tab = cvCreateMat( 1, comp_count, CV_8UC3 );//创建随机颜色列表
			for( i = 0; i < comp_count; i++ )

			{
				uchar* ptr = color_tab->data.ptr + i*3;
				ptr[0] = (uchar)(cvRandInt(&rng)%180 + 50);
				ptr[1] = (uchar)(cvRandInt(&rng)%180 + 50);
				ptr[2] = (uchar)(cvRandInt(&rng)%180 + 50);
			}
			{
				double t = (double)cvGetTickCount();
				cvWatershed( img0, markers );//利用自带函数进行分割
				cvSave("img0.xml",markers);
				t = (double)cvGetTickCount() - t;
				printf( "exec time = %gms\n", t/(cvGetTickFrequency()*1000.) );
			}

			// paint the watershed image
			for( i = 0; i < markers->height; i++ )
				for( j = 0; j < markers->width; j++ )
				{
					int idx = CV_IMAGE_ELEM( markers, int, i, j );//markers的数据类型为IPL_DEPTH_32S  CV_IMAGE_ELEM读取某点的像素
					uchar* dst = &CV_IMAGE_ELEM( wshed, uchar, i, j*3 );//BGR三个通道的数是一起的,故要j*3
					if( idx == -1 ) //输出时若为-1，表示各个部分的边界
						dst[0] = dst[1] = dst[2] = (uchar)255;
					else if( idx <= 0 || idx > comp_count )  //异常情况
						dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
					else if( idx == 1 )//正常情况,目标区域
					{}
						//uchar* ptr = color_tab->data.ptr + (idx-1)*3;
						//dst[0] = dst[1] = dst[2] = (uchar)0;//使目标建筑加黑，像素>255
						//dst[0] = ptr[0]; dst[1] = ptr[1]; dst[2] = ptr[2];
					//}
					else
						dst[0] = dst[1] = dst[2] = (uchar)255;//使背景变白,像素<255

				}
				//cvAddWeighted( wshed, 0.5, img_gray, 0.5, 0, wshed );//wshed.x.y=0.5*wshed.x.y+0.5*img_gray+0加权融合图像
				cvShowImage( "watershed transform", wshed);
		
				cvReleaseMat( &color_tab );
		}
	}
	return 1;
}


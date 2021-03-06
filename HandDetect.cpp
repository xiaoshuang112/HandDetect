﻿
#include "stdafx.h"
#include "HandDetect.h"
#include "opencv2/opencv.hpp"
#include "math.h"

#define  WIN_DEBUG
#define  PerThreshold 10

using namespace cv;

CvPoint P1,P2,P3,P4;

void swap(int *x,int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int choose_pivot(int i,int j )
{
	return((i+j) /2);
}

void quicksort(int list[],int m,int n)
{
	int key,i,j,k;
	if( m < n)
	{
		k = choose_pivot(m,n);
		swap(&list[m],&list[k]);
		key = list[m];
		i = m+1;
		j = n;
		while(i <= j)
		{
			while((i <= n) && (list[i] <= key))
				i++;
			while((j >= m) && (list[j] > key))
				j--;
			if( i < j)
				swap(&list[i],&list[j]);
		}
		// 交换两个元素的位置
		swap(&list[m],&list[j]);
		// 递归地对较小的数据序列进行排序
		quicksort(list,m,j-1);
		quicksort(list,j+1,n);
	}
}

int  Caldistance(CvPoint*Pt1,CvPoint*Pt2)
{
	int dis = (Pt1->x - Pt2->x)*(Pt1->x - Pt2->x) + (Pt1->y - Pt2->y)*(Pt1->y - Pt2->y);
	return dis;
}

int FindMax(int*M ,int Mask,int length)
{
	int Max = 0;

	int index =0;
	for(int i =0; i < length; i++)
	{
		if (Mask!=i)
		{
			if (Max < M[i])
			{
				Max = M[i];
				index = i;
			}
		}
	}

	return index;
}

int FindMin(int*M ,int length)
{
	int Min;
	if (M[0]!=0)
	{
		Min = M[0];
	}
	else
		Min = M[1];


	int index =0;
	for(int i =0; i < length; i++)
	{
		if ((Min > M[i])&&(M[i]!=0))
		{
			Min = M[i];
			index = i;
		}
	}

	return index;
}

int  FindFirstpoint(CvPoint*Pt)
{
	int distance[6]= {0};
	distance[0] = Caldistance(&Pt[0], &Pt[1]);//0
	distance[1] = Caldistance(&Pt[0], &Pt[2]);//1
	distance[2] = Caldistance(&Pt[0], &Pt[3]);//2
	distance[3] = Caldistance(&Pt[1], &Pt[2]);//3
	distance[4] = Caldistance(&Pt[1], &Pt[3]);//4
	distance[5] = Caldistance(&Pt[2], &Pt[3]);//5

	int index  = FindMax(distance, -1, 6);
	int indexs = FindMax(distance, index, 6);
//////////////////////////////////////////////////////////////////////////
	if ((0 == index)&&(1 == indexs))
	{
		P1 = Pt[0];//小指
		P2 = Pt[2];//中指
		P3 = Pt[1];//最远点

		P4 = Pt[3];//无名
		return 1;
	}

	if ((0 == index)&&(2 == indexs))
	{
		P1 = Pt[0];//小指
		P2 = Pt[3];//中指
		P3 = Pt[1];//最远点

		P4 = Pt[2];//无名
		return 1;
	}

	if ((0 == index)&&(3 == indexs))
	{
		P1 = Pt[1];//小指
		P2 = Pt[2];//中指
		P3 = Pt[0];//最远点

		P4 = Pt[3];//无名
		return 1;
	}

	if ((0 == index)&&(4 == indexs))
	{
		P1 = Pt[1];//小指
		P2 = Pt[3];//中指
		P3 = Pt[0];//最远点

		P4 = Pt[2];//无名
		return 1;
	}
//////////////////////////////////////////////////////////////////////////
	if ((1 == index)&&(0 == indexs))
	{
		P1 = Pt[0];//小指
		P2 = Pt[1];//中指
		P3 = Pt[2];//最远点

		P4 = Pt[3];//无名
		return 1;
	}

	if ((1 == index)&&(2 == indexs))
	{
		P1 = Pt[0];//小指
		P2 = Pt[3];//中指
		P3 = Pt[2];//最远点

		P4 = Pt[1];//无名
		return 1;
	}

	if ((1 == index)&&(3 == indexs))
	{
		P1 = Pt[2];//小指
		P2 = Pt[1];//中指
		P3 = Pt[0];//最远点

		P4 = Pt[3];//无名
		return 1;
	}

	if ((1 == index)&&(5 == indexs))
	{
		P1 = Pt[2];//小指
		P2 = Pt[3];//中指
		P3 = Pt[0];//最远点

		P4 = Pt[1];//无名
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	if ((2 == index)&&(0 == indexs))
	{
		P1 = Pt[0];//小指
		P2 = Pt[1];//中指
		P3 = Pt[3];//最远点

		P4 = Pt[2];//无名
		return 1;
	}

	if ((2 == index)&&(1 == indexs))
	{
		P1 = Pt[0];//小指
		P2 = Pt[2];//中指
		P3 = Pt[3];//最远点

		P4 = Pt[1];//无名
		return 1;
	}

	if ((2 == index)&&(4 == indexs))
	{
		P1 = Pt[3];//小指
		P2 = Pt[1];//中指
		P3 = Pt[0];//最远点

		P4 = Pt[2];//无名
		return 1;
	}

	if ((2 == index)&&(5 == indexs))
	{
		P1 = Pt[3];//小指
		P2 = Pt[2];//中指
		P3 = Pt[0];//最远点

		P4 = Pt[1];//无名
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	if ((3 == index)&&(0 == indexs))
	{
		P1 = Pt[1];//小指
		P2 = Pt[0];//中指
		P3 = Pt[2];//最远点

		P4 = Pt[3];//无名
		return 1;
	}

	if ((3 == index)&&(4 == indexs))
	{
		P1 = Pt[1];//小指
		P2 = Pt[3];//中指
		P3 = Pt[2];//最远点

		P4 = Pt[0];//无名
		return 1;
	}

	if ((3 == index)&&(1 == indexs))
	{
		P1 = Pt[2];//小指
		P2 = Pt[0];//中指
		P3 = Pt[1];//最远点

		P4 = Pt[3];//无名
		return 1;
	}

	if ((3 == index)&&(5 == indexs))
	{
		P1 = Pt[2];//小指
		P2 = Pt[3];//中指
		P3 = Pt[1];//最远点

		P4 = Pt[0];//无名
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	if ((4 == index)&&(0 == indexs))
	{
		P1 = Pt[1];//小指
		P2 = Pt[0];//中指
		P3 = Pt[3];//最远点

		P4 = Pt[2];//无名
		return 1;
	}

	if ((4 == index)&&(3 == indexs))
	{
		P1 = Pt[1];//小指
		P2 = Pt[2];//中指
		P3 = Pt[3];//最远点

		P4 = Pt[0];//无名
		return 1;
	}

	if ((4 == index)&&(2 == indexs))
	{
		P1 = Pt[3];//小指
		P2 = Pt[0];//中指
		P3 = Pt[1];//最远点

		P4 = Pt[2];//无名
		return 1;
	}

	if ((4 == index)&&(5 == indexs))
	{
		P1 = Pt[3];//小指
		P2 = Pt[2];//中指
		P3 = Pt[1];//最远点

		P4 = Pt[0];//无名
		return 1;
	}
	//////////////////////////////////////////////////////////////////////////
	if ((5 == index)&&(1 == indexs))
	{
		P1 = Pt[2];//小指
		P2 = Pt[0];//中指
		P3 = Pt[3];//最远点

		P4 = Pt[1];//无名
		return 1;
	}

	if ((5 == index)&&(3 == indexs))
	{
		P1 = Pt[2];//小指
		P2 = Pt[1];//中指
		P3 = Pt[3];//最远点

		P4 = Pt[0];//无名
		return 1;
	}

	if ((5 == index)&&(2 == indexs))
	{
		P1 = Pt[3];//小指
		P2 = Pt[0];//中指
		P3 = Pt[2];//最远点

		P4 = Pt[1];//无名
		return 1;
	}

	if ((5 == index)&&(4 == indexs))
	{
		P1 = Pt[3];//小指
		P2 = Pt[1];//中指
		P3 = Pt[2];//最远点

		P4 = Pt[0];//无名
		return 1;
	}

	else
	{
		return -1;
	}

	return 0;
}

//int  FindSecondpoint(CvPoint*Pt )
//{
//	int distance[4]= {0};
//	distance[0] = Caldistance(&P1,&Pt[0]);
//	distance[1] = Caldistance(&P1,&Pt[1]);
//	distance[2] = Caldistance(&P1,&Pt[2]);
//	distance[3] = Caldistance(&P1,&Pt[3]);
//
//	int index = FindMin(distance, 4);
//	P2 = Pt[index];
//
//
//	for (int i = 0; i < 4; i++)
//	{
//		P3 = Pt[i];
//		if ((P3.x!=P1.x)&&(P3.x!=P2.x)&&(P3.x!=P4.x))
//		{
//			break;
//		}
//	}
//
//	return 0;
//}

int  JudgePointNum(CvPoint*Pt)
{
	int ret  = FindFirstpoint(Pt);

	if (-1==ret)
	{
		return -1;
	}

	int Ax = P2.x - P1.x;
	int Ay = P2.y - P1.y;
	int Bx = P3.x - P1.x;
	int By = P3.y - P1.y;

	int directions = (Ax * By)-(Bx*Ay);

	if (directions > 0)
	{
		return 0;
	}
	else
		return 1;
	
}

double CalAngle(int ret)
{
	double angle = 0.0;

	int x = 1;
	int y = 0;

	int Ax = 0;//无名指向食指
	int Ay = 0;
	if (0==ret)
	{
	   Ax = P3.x - P4.x;//无名指向食指
	   Ay = (300 - P3.y) - (300 - P4.y);
	}

	if (1==ret)
	{
		Ax = P4.x - P3.x;//食指-无名指
		Ay = (300 - P4.y) - (300 - P3.y);
	}

	double cosB = abs(Ax)/sqrt(Ax*Ax + Ay*Ay); 
	angle = acos(cosB)*180/3.1415;

	//if (angle <30 )
	//{
	//	return 0;
	//}

	if ((Ax >=0)&&(Ay >= 0))
	{
		return angle;
	}

	if ((Ax >=0)&&(Ay <= 0))
	{
		angle = 0 - angle;
	}

	if ((Ax <=0)&&(Ay <= 0))
	{
		angle = angle - 180;
	}

	if ((Ax <=0)&&(Ay >= 0))
	{
		angle = 180 - angle;
	}

	return angle;
}

CvSeq* contour = NULL;  
CvSeq* contour_i = NULL;//存放contour初始位置
IplImage*Img = cvCreateImage(cvSize(300,300),8, 1);
HANDDETECT_API int _stdcall   HandDetect(BYTE*Src, int w, int h, double*Angle)
{
	if (NULL==Src)
	{
		return -1;
	}

	int ret = -99;

	IplImage*cvPhoto1 =	cvCreateImage(cvSize(w, h), 8, 3);
	IplImage*cvPhoto =	cvCreateImage(cvSize(w, h), 8, 1);
	for (int y = 0 ;y < cvPhoto1->height; y++)
	{
		memcpy(cvPhoto1->imageData+y*cvPhoto1->widthStep, Src + 3*y*cvPhoto1->width,3*cvPhoto1->width*sizeof(BYTE));//copy
	}

	cvCvtColor(cvPhoto1,cvPhoto, CV_RGB2GRAY);
	cvResize(cvPhoto, Img);//缩放
	cvReleaseImage(&cvPhoto);
	cvReleaseImage(&cvPhoto1);
#ifdef WIN_DEBUG
	IplImage*Img_d = cvCreateImage(cvSize(300,300),8, 1);
	cvCopy(Img, Img_d);
	cvNamedWindow("src", 0);
	cvShowImage(  "src", Img_d);
	cvSaveImage("Src.jpg",Img_d);
#endif 

	cvThreshold(Img,Img, 100, 255, 1);//二值化
	cvDilate(Img, Img);
	cvDilate(Img, Img);
	cvDilate(Img, Img);//膨胀

	cvThreshold (Img, Img, 100, 255, CV_THRESH_BINARY); 

#ifdef WIN_DEBUG
	cvNamedWindow("Dilate",0);
	cvShowImage("Dilate",  Img);
#endif

	CvMemStorage* storage = cvCreateMemStorage (0);

	CvScalar external_color;  
	CvScalar hole_color;  

	int contours = cvFindContours (Img, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_NONE);  
	contour_i = contour;//存放contour初始位置

	int count[100] = {0};
	int i = 0;
	for (;contour!=0; contour = (contour)->h_next)
	{
		double s=cvContourArea(contour,CV_WHOLE_SEQ);
        count[i] = int(s);
		i++;
	}

	contour = contour_i;
	contour_i = NULL;

	quicksort(count,0, i-1);//面积排序

	CvMoments *moment =  new CvMoments;//(CvMoments*)malloc( sizeof(CvMoments) );

	CvPoint mpoint[5] = {0};

	int v = 0;
	if (i < 4)
	{
		ret = -1;
	}

	if (i >= 4)
	{
		int per = 100 * count[i - 4] / count[i - 1];
		if (per < PerThreshold)
		{
			ret = -1;
		}
		if (ret != -1)
		{
			for (; contour != 0; contour = contour->h_next)
			{
				external_color = CV_RGB(0, 0, 0);
				hole_color     = CV_RGB(100, 100, 100);

				int s = (int)cvContourArea(contour, CV_WHOLE_SEQ);
				if ((s >= count[i - 4]) && (s <= count[i - 1]))
				{
					CvRect rect = cvBoundingRect(contour, 1);

                #ifdef WIN_DEBUG
					cvDrawContours (Img_d, contour, external_color, hole_color, 0, 2, 8);
					cvRectangleR(Img_d, rect, CV_RGB(0, 0, 0));
                #endif
					cvSetImageROI(Img, rect); //set ROI,
					cvMoments(Img, moment);
					cvResetImageROI(Img);
					double m00 = cvGetSpatialMoment( moment, 0, 0 );
					double m10 = cvGetSpatialMoment( moment, 1, 0 );
					double m01 = cvGetSpatialMoment( moment, 0, 1 );

					int x =  rect.x + (m10 / m00);
					int y =  rect.y + (m01 / m00);

                 #ifdef WIN_DEBUG
					cvCircle(Img, cvPoint(x, y), 2, cvScalar(0, 0, 0), 2);
                 #endif

					mpoint[v].x = x;
					mpoint[v].y = y;

					v++;
				}
			}
			ret = JudgePointNum(mpoint);
			*Angle = CalAngle( ret);
		}
	}

	#ifdef WIN_DEBUG
	cvLine(Img_d,cvPoint(P1.x,P1.y),cvPoint(P2.x,P2.y),cvScalar(0,0,0),2);
	cvLine(Img_d,cvPoint(P2.x,P2.y),cvPoint(P3.x,P3.y),cvScalar(0,0,0),2);
 	cvLine(Img_d,cvPoint(P3.x,P3.y),cvPoint(P1.x,P1.y),cvScalar(0,0,0),2);
	cvLine(Img_d,cvPoint(P3.x,P3.y),cvPoint(P4.x,P4.y),cvScalar(0,0,0),2);

	cvNamedWindow("Contour", 0); 
	cvShowImage ("Contour", Img_d);
	#endif

	
	//cvReleaseImage(&Img);

	delete moment;
	//free(moment);
	cvReleaseMemStorage(&storage);
	return ret;
}


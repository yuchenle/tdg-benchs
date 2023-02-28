/******************************************************************
 * Author:  Maria A. Serrano
 * Email:   maria.serranogracia@bsc.es
 ******************************************************************
 * Author:  Carlos A. Varela
 * Email:   carlos.varela@bsc.es
 ******************************************************************
 * 
 ******************************************************************/

#include <stdio.h>
#include <dirent.h> 
#include <sys/time.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

extern "C" {
#include "hog.h"
}

int NBLOCKS;
using namespace std;
using namespace cv;

// time measurement, will be set in vl_bsc_hog
timeval tim;

int num_iter;

int main(int argc, char** argv )
{
  // Check parameters
  if ( argc != 5 ) {
    fprintf(stderr, "usage: %s <Images_DirPath> <numImages> <num_iter> <block numbers per task> \n",argv[0]);
    return -1;
  }
  
  // Number of images to process
  int nImages = atoi(argv[2]);
  num_iter = atoi(argv[3]);
  if (num_iter < 0)
  {
    fprintf (stderr, "num_iter must be greater than 0\n"); 
    exit(-1);
  }

  NBLOCKS = atoi(argv[4]);
  if (NBLOCKS < 1 || NBLOCKS > 6)
  {
    fprintf (stderr, "NBLOCKS needs to be an integer between 1 and 6\n");
    exit (-1);
  }

  int iProcessed=0; 
  // Directory containing up to nImages images
  DIR *d;
  struct dirent *dir;
  d = opendir(argv[1]);
  if (d) {
    while (((dir = readdir(d)) != NULL) && iProcessed < nImages ) {
      if(dir-> d_type != DT_DIR) {
		
		char imName[256];
		strcpy(imName,argv[1]);
		strcat(imName,"/");
		strcat(imName,dir->d_name);	    

		Mat mat = imread( imName, 3);
		if ( !mat.data ) {
		  printf("No image data \n");
		  return -1;
		}
		
		Mat draw = mat.clone();
		
		// cv:mat data uchar (0-255) is converted to float/double (0.0-1.0), 
		// format used by VLFeat:
		//    CV_32F --> vl_float is float
		//    CV_64F --> vl_float is double  
		mat.convertTo(mat, CV_32F);
		vl_float const* image = (vl_float const*)mat.data;

		/******************************************************************************
		** BSC VLFeat HOG
		*****************************************************************************/
		gettimeofday(&tim, NULL);  
		long t3 = (tim.tv_sec)*1000000 + (tim.tv_usec);

		Locations *windows;

		// Extract HOG features
		vl_float* features = vl_bsc_hog(image, mat.cols, mat.rows, &windows);
		
		// Finishing timer counter
		gettimeofday(&tim, NULL);  
		long t4=(tim.tv_sec)*1000000 + (tim.tv_usec);   
		
		/******************************************************************************
		** Printing results and execution time
		*****************************************************************************/
		int nWindows = 0;
		for (int nW = 0; nW < NWINDOWS; nW++) {
		  if (windows[nW].weight > 0.0) {
			// Person located
			nWindows++;
			Rect r = Rect(Point(windows[nW].px,windows[nW].py), Size(64,128));
			rectangle(draw, r.tl(), r.br(), cv::Scalar(0,255,0), 2);
		  }
		}
	    iProcessed++;
	  }
    }
    if (iProcessed < nImages)
		printf("WARNING! Only %d images found in directory %s\n\n",iProcessed,argv[1]);
		
    closedir(d);
  } else {
    printf("Error! Could not open directory %s\n",argv[1]);
    return -1;
  }

  return 0;
}

/******************************************************************
 * Author:  Maria A. Serrano
 * Email:   maria.serranogracia@bsc.es
 ******************************************************************
 * 
 * Histogram of Oriented Gradients (HOG) - Definition
 *
 *****************************************************************
 * Adapted from the VLFeat library and is made available under
 * the terms of the BSD license.
 * @author Andrea Vedaldi
 * Copyright (C) 2007-12 Andrea Vedaldi and Brian Fulkerson.
 * All rights reserved.
 *****************************************************************
 */

/* NBLOCKSxNBLOCKS = number of blocks computed per OpenMP task
   NBLOCKS = 1 -->   1 block  per task --> 32026 OpenMP tasks
   NBLOCKS = 2 --> 2x2 blocks per task -->  8040 OpenMP tasks
   NBLOCKS = 3 --> 3x3 blocks per task -->  3600 OpenMP tasks
   NBLOCKS = 4 --> 4x4 blocks per task -->  2040 OpenMP tasks
   NBLOCKS = 5 --> 5x5 blocks per task -->  1296 OpenMP tasks
   NBLOCKS = 6 --> 6x6 blocks per task -->   920 OpenMP tasks
 */

// NBLOCKS is now defined in personDetector.cpp
// #if !defined (NBLOCKS)
// #define NBLOCKS 2
// #endif

#ifndef VL_HOG_H
#define VL_HOG_H

typedef long long unsigned  vl_size ;
typedef long long           vl_index ;
typedef long long unsigned  vl_uindex ; 
typedef int                 vl_bool ;
typedef float               vl_float ;


#define VL_TRUE 1   
#define VL_FALSE 0

#define VL_PI 3.141592653589793

#define VL_MIN(a,b) (((a)<(b))?(a):(b))
#define VL_MAX(a,b) (((a)>(b))?(a):(b))

// HOG and image configuration
#define NUM_ORIENTATIONS  9
#define CELL_SIZE         8
#define NUM_CHANNELS      3
#if !defined (WIDTH_FullHD)
#define WIDTH_FullHD      1920
#endif
#if !defined (HEIGHT_FullHD)
#define HEIGHT_FullHD     1080
#endif
#define WINWIDTH          7
#define WINHEIGHT         15 
#define WINSTRIDE         CELL_SIZE //8
#define NWINDOWS          (HOG_WIDHT-WINWIDTH+1)*(HOG_HEIGHT-WINHEIGHT+1)
#define HOG_DIMENSION     4*NUM_ORIENTATIONS
#define HOG_WIDHT         WIDTH_FullHD / CELL_SIZE
#define HOG_HEIGHT        HEIGHT_FullHD / CELL_SIZE 
#define HOG_STRIDE        HOG_WIDHT*HOG_HEIGHT
  
struct VlHog_
{
  /* helper vectors */
  vl_float * orientationX ;
  vl_float * orientationY ;
  
  /* buffers to check already computed cells */
  unsigned short * cell_GradComputed;
  unsigned short * cell_NormComputed;
} ;

typedef struct VlHog_ VlHog ;

 VlHog * vl_hog_new () ;
 
 void vl_hog_delete (VlHog * self) ;
 
/* 
 * BSC implementations
 * 
 */ 

struct Locations_
{
  /* Pixel */
  vl_index py;
  vl_index px;

  /* SVM result */
  vl_float weight;
} ;

typedef struct Locations_ Locations ;

 vl_float * vl_bsc_hog (vl_float const * image,
                      vl_size width, vl_size height, 
                      Locations **winDetected) ;
 

/* VL_HOG_H */
#endif

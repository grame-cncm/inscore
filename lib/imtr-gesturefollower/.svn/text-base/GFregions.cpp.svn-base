/*
 *  GFregions.cpp
 *  gf
 *
 *  Created by Bruno Zamborlin on 03/03/10.
 *  Copyright 2010 __IRCAM__. All rights reserved.
 *
 */

#include "GFregions.h"


inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }


GFregions::GFregions		()	{
  nRegions = 0; 
}
GFregions::~GFregions		()	{
  
}
void GFregions::reset		()					{
  nRegions = 0;
}


void GFregions::addRegion	(int start, int end){
  
  //checking boundaries between regions
  if (nRegions != 0 && ends[nRegions-1]>= start)
	start = ends[nRegions-1]+1;
  
  //checking limits
  if (start > maxFrameIdx)
	start = maxFrameIdx;
  if (end > maxFrameIdx)
	end = maxFrameIdx;
  
  if (end < start)
	end = start;  //regions with one frame are allowed
  
  starts[nRegions] = start;
  ends[nRegions] = end;
  nRegions++;
}


void GFregions::setSize		(int size)			{
  maxFrameIdx = max(size - 1,0);
}


int  GFregions::getRegion	(int frame)			{
  for (short i=0; i<nRegions; ++i){
	if (frame>=starts[i] && frame<=ends[i]) {
	  return i;
	}
  }
  return -1;  //index is not over an existing region
}


int  GFregions::nextStart	(int frame)			{
  
  //return 0 if there is no regions
  if (nRegions == 0) return 0;
  
  //next start
  for (short i=0; i<nRegions; ++i){
	if (starts[i] > frame)
	  return starts[i];
  }
  
  //if the frame is before last region, return the start of the first region
  return starts[0];
}


int  GFregions::nextEnd		(int frame)			{

  //return 0 if there is no regions
  if (nRegions == 0) return 0;
  
  //next end
  for (short i=0; i<nRegions; ++i){
	if (ends[i] > frame)
	  return ends[i];
  }
  
  //if the frame is before last region, return the end of the first region
  return ends[0];
}


int  GFregions::prevStart	(int frame)			{

  //return 0 if there is no regions
  if (nRegions == 0) return 0;
  
  //prev start
  for (short i=nRegions-1; i>=0; --i){
	if (starts[i] < frame)
	  return starts[i];
  }
  
  //if the frame is after last region, return the start of the first region
  return starts[0];

}


int  GFregions::prevEnd		(int frame)			{

  //return 0 if there is no regions
  if (nRegions == 0) return 0;
  
  //prev end
  for (short i=nRegions-1; i>=0; --i){
	if (ends[i] < frame)
	  return ends[i];
  }
  
  //if the frame is after last region, return the end of the first region
  return ends[0];

}


int	 GFregions::getN		(){
  return nRegions;
}


int GFregions::getStart	(int regionIdx){
  if (regionIdx<nRegions)
	return starts[regionIdx];
  else
	return 0;
}


int GFregions::getEnd	(int regionIdx){
  if (regionIdx<nRegions)
	return ends[regionIdx];
  else
	return 0;
}



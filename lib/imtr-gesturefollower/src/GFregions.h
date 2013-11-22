/*
 *  GFregions.h
 *  gf
 *
 *  Created by Bruno Zamborlin on 03/03/10.
 *  Copyright 2010 __IRCAM__. All rights reserved.
 *
 */

#ifndef GFREGIONS
#define GFREGIONS


class GFregions {

public:
  static const int GFREGIONS_CAPACITY = 100;
  
private:
  int maxFrameIdx;
  int starts[GFREGIONS_CAPACITY];
  int ends[GFREGIONS_CAPACITY];
  int nRegions;
  
public:
  GFregions();
  ~GFregions();
  void reset();
  void addRegion(int start, int end);
  void setSize(int size);
  int getRegion	(int frame);
  int nextStart	(int frame);
  int nextEnd	(int frame);
  int prevStart	(int frame);
  int prevEnd	(int frame);
  int getN		();
  int getStart	(int regionIdx);
  int getEnd	(int regionIdx);
};




#endif


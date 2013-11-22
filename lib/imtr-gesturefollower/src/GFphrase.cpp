/*
 *  GFphrase.cpp
 *  gf
 *
 *  Created by Bruno Zamborlin on 28/06/10.
 *
 */

#include "GFphrase.h"

/*#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif*/


#pragma mark -
#pragma mark Constructors

/***********************			PHRASE CLASS		********************/
/***	CLASS CONSTRUCTOR	***/
Phrase::Phrase(GF* parent_ , float* BMean_, int maxFrames_, int id_, float* _alfa) 
{	/*  create a new Phrase object, allocating internal memory for calculation. It takes also the pointer of the BMean matrix, which is preallocated externally. */
  parent				=	parent_;	/*	a pointer to the parent instance of class GF (in order to access to setting parameters)	*/
  maxFrames				=	maxFrames_;
  //channels				=	0;
  id					=	id_;
  oldIndex				=	0;
  freezeLikelihoodCount	=	0;
  likelihood_th			=	-10;
  restartCase			=	false;
  
  //name
  std::stringstream s;
  s<<"Phrase-"<<id+1;
  name = s.str();
  
  /*	Setting Learning Data	*/
  BMean =	BMean_;	/*	BMean is allocated with a fix amount of memory. 
									  *	the user of this library will take care about memory allocation/deallocation.
									  *	The BMean capacity amount (maximum allocable memory) is stored on the GF parent instance.
									  *  BMean is orientated by row: the element at row i and column j will be at [i*n+j]
									  */
  learned	=	false;
  size	  =	0;
  timetags = new float[maxFrames];		/*	a 'size' float vector containing timetags for each observation	*/
  for(int i = 0; i < maxFrames; i++)
    timetags[i] = 0.0;
  
  //Init results pointers
  index	= &(parent->index[id]);	//index = (parent->index)+1;
  n_index	= &(parent->n_index[id]);
  likelihood	= &(parent->likelihood[id]);
  n_likelihood	= &(parent->n_likelihood[id]);
  speed	= &(parent->speed[id]);
  
  
  /*	Setting Decoding Data	*/
  speedWindow	=	new float	[parent->smoothingSpeed];
  likelihoodWindow = new  float	[parent->likelihoodWindowSize];
  b =	new float	[maxFrames];			/*	vector for intermediate results. its size is "window". it doesn't require any initialization */
  
  regions.setSize(0);
  
  if (_alfa == NULL){
    alfa	=	new float	[maxFrames];			/*	the probability vector. its initialization is in the resetDecodingData() method   */
    if(alfa != NULL) alfaAllocatedInternally = true;
  }
  else {
    alfa = _alfa;
    alfaAllocatedInternally = false;
  }
  
  enabled	=	true;	
  reset();																/*	initialize/reset any field */
  resetSpeed();

  correct = (timetags != NULL && speedWindow != NULL && likelihoodWindow != NULL && b != NULL && alfa != NULL);
};
Phrase::~Phrase(){	
  if (alfaAllocatedInternally && alfa != NULL){
    delete [] alfa;
  }
  delete []	b;
  delete []	speedWindow;
  delete []	likelihoodWindow;
  delete []	timetags;
}

void 
Phrase::setMaxFrames(int mf)
{
  if(maxFrames != mf)
  {
    delete []	b;
    maxFrames = mf;
    b =	new float	[maxFrames];
    delete []	timetags;
    timetags = new float[maxFrames];
    for(int i = 0; i < maxFrames; i++)
      timetags[i] = 0.0;
  }
}
/***	RESET METHODS	***/

#pragma mark -
#pragma mark Reset methods

void	Phrase::reset(){					/*	reset any field */
  size = 0;
  resetDecodingData();
  learned = false;	
  regions.reset();
}
void	Phrase::resetDecodingData(){	/*	reset any decoding data	and initialize alfa */
  if (parent->isLearning && parent->learningPhrase == id) return;
  initAlfa();         /*	initialization of alfa		*/
  resetLikelihood();  /*  resetting likelihood		*/
  *index	=	 0;		/*	current index	*/
  //if (! parent->isCyclic) resetSpeed();       /*  resetting speed */
};
void	Phrase::resetSpeed(){	/* reset speed */
  *speed			=	1;     /*	present detected speed in [0 , MAXSPEED]	*/
  speedCounter	=	0;
  for(short i=0; i<parent->smoothingSpeed; ++i)
	speedWindow[i] = 1;
}
void	Phrase::resetLikelihood(){	/*  reset likelihood  */
  *likelihood       =	0;
  likelihoodCounter =	0;
  for(short i=0; i<parent->likelihoodWindowSize; ++i)
	likelihoodWindow[i] = 0;
}
void	Phrase::initAlfa(){	/*  initialize alfa (depending on "init_type")  */
  
  alfa[0] = 1;
  if (size <= 0) return;	//this method is invoked also during initialization, when m is still zero.
  
  if (parent->beginning == GF::FIRST){	//initialState : alfa = [1,0 ... 0]
	for (int i=1; i< size; ++i){
	  alfa[i] = 0;
	}
	return;
  }
  
  if (parent->beginning == GF::ANY){	//equalProb : alfa = [1/L ... 1/L]
	if (size==0) return;
	float t = 1 / ((float)size);
	for (int i=0; i < size; ++i)	
	  alfa[i] = t;
#ifdef TRACE_ON
	PRINT("initalfa before normalization: ");
	std::stringstream s;
	s <<"initalfa before normalization. t= "<<t;
	PRINTN(s.str());
	PRINTN(parent->postV(alfa, calculationWindowStart, calculationWindowEnd, size));
#endif
	normalizeAlfa(GFlibUtility::Sum(alfa, calculationWindowStart, calculationWindowEnd, size));
#ifdef TRACE_ON
	PRINT("initalfa after normalization: ");
	PRINTN(parent->postV(alfa, calculationWindowStart, calculationWindowEnd, size));
#endif
  }
}
void	Phrase::initAlfa(int pos){
  if (pos< 0) pos=0;
  if (pos >= size) pos = size-1;
  for (int i=0; i<size; ++i)
	alfa[i] = 0;
  alfa[pos] = 1;
}



void	Phrase::setRegions(int* argc, int argv){
  
  regions.reset();
  if (argv==0) return;
  
  for (int i=0; i<argv; ++i){
	if (argc[i] < 0) argc[i] = 0;
	if (argc[i] >= size) argc[i] = size-1;
  }
  
  for (int i=0; i<argv; i+=2){
	regions.addRegion(argc[i], argc[i+1]);  //start1 end1 , start2 end2 ...
  }
}

/***	ALGORITHM FUNCTIONS	***/

#pragma mark -
#pragma mark Algorithm


void	Phrase::calculateWindow(){	/***	1  - FILTERING 	***/
  
  int windowSize = parent->windowSize;
  
  //	No Window
  if (windowSize == 0 || windowSize >= size){
	calculationWindowStart = 0;
	calculationWindowEnd = size-1;
  }
  
  //calculating wStart and wEnd around the index
  else{
	calculationWindowStart	  = *index  - (windowSize / 3);
	calculationWindowEnd	  = *index  +	(windowSize * 2 / 3);
	
	if (calculationWindowStart < 0)
	  calculationWindowStart += (size-1);
	if (calculationWindowEnd >= size)			
	  calculationWindowEnd -= (size-1);
  }
	 
  if (calculationWindowStart == calculationWindowEnd){	//special unlucky case
	calculationWindowStart = 0;
	calculationWindowEnd = size-1;
  }
  
  // OLD METHOD: Filter vector
  /*
  //	No Filters
  if (windowSize == 0 || windowSize >= size){	//full calculation
	if (!filterVectorResetted && size>0){
	  for (int i=0; i<size; ++i)	//resetting the filter vector
		filterVector[i] = true;
	  filterVectorResetted = true;
	}
  }
  
  //	Sliding Window technique
  else{
	filterVectorResetted = false;
	
	//calculating wStart and wEnd around the index
	
	int wStart	= *index  - (windowSize / 3);
	int wEnd    = *index  +	(windowSize * 2 / 3);
	
	if (wStart < 0)				wStart += (size-1);
	if (wEnd > size-1)			wEnd -= (size-1);
	
	filterVector[wStart]=true;
	int i = (wStart+1) % size;
	bool b = true;
	while(i != wStart){
	  filterVector[i]=b;
	  if(i==wEnd) b = false;
	  i=(i+1) % size;
	}
  }
  */
  
  //optimized:
  //for (int count=0, int i=wStart;	  count++,  count<= windowSize; i=(i+1) % windowSize);
  
  
#ifdef TRACE_ON
  std::stringstream s;
  s <<"wStart="<<calculationWindowStart <<"  wEnd="<<calculationWindowEnd;
  PRINTN(s.str());
#endif
}
void	Phrase::calculateDistances(float* O){	/***	2  - CALCULATING DISTANCES :	calculate "b" from scratch, that is a vector with "window" length that contains distances between O (the incoming vector) and each row of the window of BMean */
  
  float* weights = parent->weights;
  
  //Mahalanobis distance
  if (parent->metric==GF::MAHAL){
	int i = calculationWindowStart;
	while (true){
	  b[i] = 	GFlibUtility::Mahalanobis	(O,	BMean+((i % size)*parent->channels),	parent->channels,	weights , parent->tolerance	);
	  if (i == calculationWindowEnd) break;
	  i = (i+1) % size;
	}
	return;
  }
  
  //K-L distance
  else {
	int i = calculationWindowStart;
	while (true){
	  b[i] = (	GFlibUtility::KullbackLeibler	(O,	BMean,	(i % size)*parent->channels,	parent->channels,	weights , parent->tolerance	));
	  if (i == calculationWindowEnd) break;
	  i = (i+1) % size;
	}
	return;
  }
}


void	Phrase::propagation(){	/***	3 - PROPAGATION	: alfa = alfa * b  (with zeros where alfa is not defined)	(was: b *= alfa) ***/
  
  int i = calculationWindowStart;
  while (true){
	//b[i] *= alfa[i];
    alfa[i] *= b[i];
	if (i == calculationWindowEnd) break;
	i = (i+1) % size;
  }
  
  /* old
   for (int b_idx=0; b_idx < w; ++b_idx){  //for each element of b
   int abs = (wStart + b_idx) % m;
   int alfa_idx;
   if ((alfaOffset > abs) && ((alfaOffset + w) >= m))  //calculating the corresponding position of alfa
   alfa_idx = m - alfaOffset + abs;
   else
   alfa_idx = wStart - alfaOffset + b_idx; 
   
   if (alfa_idx >= 0 && alfa_idx < w)  //if alfa is defined here
   b[b_idx]  *= alfa[alfa_idx];
   else
   b[b_idx] = 0; //else put zero
   }*/
}


void	Phrase::calculateIndexSpeed(){	/***	4 - CALCULATING INDEX	+ SPEED   ***/
  
  //	  UPDATE INDEX
  oldIndex = *index;
  *index = GFlibUtility::highestValueIndex(alfa, calculationWindowStart, calculationWindowEnd, size);
  //*index = floor(GFlibUtility::Mean(alfa, calculationWindowStart, calculationWindowEnd, size));

  //*index = Mean(b, m, filterVector);
  int newIndex = *index;
  
  restartCase = (newIndex <=  parent->autoRestartLimit) && (size - oldIndex <= parent->autoRestartLimit);	//restart case
  
  //forward option (index doesn't go back)
  if (!restartCase && parent->forward && *index < oldIndex){
    *index = oldIndex;
  }
  
  *n_index = ((float)((*index))) / size;	//calculate normalized index (in [0,1])
  
  
  //	  CALCULATE SPEED
  
  if (!restartCase){ //no speed calculation if restart case
	
	//calculating the instant speed
	float instantSpeed = newIndex - oldIndex;
	
	//setting new value into the window
	speedWindow[speedCounter] = instantSpeed;  //the modulo is to handle the cyclic case
	
	//incrementing counter
	speedCounter = (speedCounter+1) % parent->smoothingSpeed;
	
	//calculate the speed as the arithmetic mean of the window
	*speed = (GFlibUtility::Sum(speedWindow , parent->smoothingSpeed) / parent->smoothingSpeed);
	
#ifdef TRACE_ON
	std::stringstream s2;
	s2 <<"Speed calculation: oldIndex=  "<<oldIndex<<" , newIndex = "<<newIndex<<" , instantSpeed="<<instantSpeed<<", final speed = "<<*speed;
	PRINTN(s2.str());
#endif
	
  }
}
 
 
void	Phrase::translate(){	/***	5a - TRANSLATION		***/
  //alfa = optimized calculation of b*A, where A is the transition matrix based on the "speed"
  
  
  //temp buffer
  float *temp;
  temp = new float[size];
  memcpy(temp, alfa, size*sizeof(float));
  
  
  //clear alfa
  //TODO: optimize using memcpy
  for (int i=0; i < size; ++i){	//clear alpha entirely 
    alfa[i] = 0;
  }
  

  
  //translate (loop version with calculateWindow and regions)
  int i = calculationWindowStart;
  
  if (parent->viterbi){
    while (true){
      for (int j = 0; j <= GF::MAXSPEED; ++j){
        alfa[ (i+j) % size ] = max(b[i] * parent->expectedSpeed[j],alfa[ (i+j) % size ]);
      }
      if (i == calculationWindowEnd) break;
      i = (i+1) % size;
    }
  }
  else {
    while (true){
      for (int j = 0; j <= GF::MAXSPEED; ++j){
        alfa[ (i+j) % size ] += temp[i] * parent->expectedSpeed[j];
      }
      if (i == calculationWindowEnd) break;
      i = (i+1) % size;
    }
  }
  
  delete [] temp;
  //translate (loop version with calculateWindow)
  /*
  int i = calculationWindowStart;
  while (true){
	
	for (int j = 0; j <= MAXSPEED; ++j){
	  alfa[ (i+j) % size ] += b[i] * parent->expectedSpeed[j];
	}
   if (i == calculationWindowEnd) break;
	i = (i+1) % size;
  }
  */
  
  //translate (loop version)
  /*
  for (int i = 0; i < size; ++i){
	for (int j = 0; j <= MAXSPEED; ++j){
	  alfa[ (i+j) % size ] += b[i] * parent->expectedSpeed[j];
	}
  }
   */
  
  //translate (non-loop version)
  /*for (int i = 0; i < size; ++i){
   for (int j = 0; j <= MAXSPEED; ++j){
   if ((i+j) < size){
   alfa[i+j] += b[i] * expectedSpeed[j];
   }
   }
   }*/
  
}



void	Phrase::applyRegions(){
  
  int nRegions = regions.getN();
  
  if (nRegions == 0) return;	//no regions means all selected
  
  int currentRegion = regions.getRegion(*index);
  bool indexIsAtTheEnd = false;
  for (int i=0; i<nRegions; ++i){
	if (regions.getEnd(currentRegion) == *index)
	  indexIsAtTheEnd = true;
  }
  
  if (currentRegion == -1 || indexIsAtTheEnd) {	//if the index is not over an existing region or is at the end of a region
	parent->goTo(id, regions.nextStart(*index));  //go to the next region
  }
  
  //if window
  if (parent->windowSize > 0 && parent->windowSize < size){
	
	//erasing alfa where regions are not defined
	int i = calculationWindowStart;
	while (true){  //for all 'i' in the calculation window
	  if (regions.getRegion(i) == -1)  //if this frame is not inside the calculation window, erase alfa in this frame
		alfa[i] = 0;
	  if (i == calculationWindowEnd) break;
	  i = (i+1) % size;
	}
  }
}	


void	Phrase::calculateLikelihood(float alfaSum){	/***	6a - CALCULATE LIKELIHOOD		***/
  
  //check if this phrase has a freezed likelihood
  if (freezeLikelihoodCount > 0){	
	--freezeLikelihoodCount;
    return;
  }
  
  
  if (alfaSum == 0){  //setting new value into the window
	likelihoodWindow[likelihoodCounter] = GF::LH_MIN;	//in order to avoid -inf as likelihood (should never happen, already checked)
  }
  else{
	float L = log(alfaSum);
	if (L >= GF::LH_MIN)
	  likelihoodWindow[likelihoodCounter] = L;
	else 
	  likelihoodWindow[likelihoodCounter] = GF::LH_MIN;	//in order to avoid -inf numbers*/
  }
  
  //incrementing counter
  likelihoodCounter = (likelihoodCounter+1) % parent->likelihoodWindowSize;
  
  //calculate the likelihood as the arithmetic mean of the window
  *likelihood = GFlibUtility::Sum(likelihoodWindow , parent->likelihoodWindowSize) / parent->likelihoodWindowSize;
  
  
#ifdef TRACE_ON
  std::stringstream s2;
  float f1 = *likelihood * parent->likelihoodWindowSize;
  float f2 = log(alfaSum) * (1 - parent->likelihoodWindowSize);
  s2 <<"calculating LH: old LH was:  "<<likelihood<<" , alfaSum = "<<alfaSum<<" , log(alfaSum)="<<log(alfaSum)<<", (1 - parent->likelihoodWindow) = "<<(1 - parent->likelihoodWindowSize)<<" , new LH = "<<f1<<"  +  "<<f2;
  PRINTN(s2.str());
#endif

}


int		Phrase::normalizeAlfa(float alfaSum){	/***	6b - ALFA NORMALIZATION		***/
  
  //normalize alpha and update its likelihood
  if (alfaSum > 0){
	//int calculationWindowEnd_New = calculationWindowEnd + GF::MAXSPEED;
	//if (calculationWindowEnd_New > size) calculationWindowEnd_New = size;
	int i = calculationWindowStart;
	while (true){
	  alfa[i] /=  alfaSum;
	  if (i == calculationWindowEnd) break;
	  i = (i+1) % size;
	}
  }
  
#ifdef TRACE_ON
  else
	PRINTN("alfasum=zero: normalizing alfa");
#endif
  
  /*else	{	//if alfa = [0...0]
   resetDecodingData();
   *likelihood = - DBL_MAX;	//likelihood = -inf
   if (id == parent->likeliest){
   parent->errorDescr += "Alfa is zero! Resetting decoding data and setting LH=-inf";
   return 2;
   }
   }*/
  return 0;
}



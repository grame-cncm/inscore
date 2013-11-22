/*
 *  GFphrase.h
 *  gf
 *
 *  Created by Bruno Zamborlin on 28/06/10.
 *
 */
 
#ifndef   GFPHRASE
#define   GFPHRASE

#include  "GFlib.h"
#include  "GFregions.h"					/*  Handles GFregions			*/

/***********************			PHRASE CLASS		********************/

class GF;
class Phrase;




class Phrase {
  
public:

  GF*		parent;					/*	a pointer to the parent instance of class GF (in order to access to all the parameters)	*/
  int		id;						/* the unique id of this phrase																*/
  std::string	name;					/* the name of the phrase																	*/
  
  bool correct;
  
  /***	LEARNING FIELDS	***/
  float*	BMean;					/*	BMean
									  *	a [channels x m] matrix of floating points
									  *	where channels is a constant value and m increase dinamically up to a fix preallocated size (capacity)	*/
  int		size;					/*	number of effective stored rows	-> "size" of BMean (<= capacity)										*/
  float*	timetags;				/*	a 'size' float vector containing timetags for each observation											*/
  long		maxFrames;
  bool		learned;				/*	a flag to know if this phrase has already learned some data												*/
  bool		enabled;				/* if the decoding has to be performed for this phrase or not												*/
  
  
  /***	DECODING FIELDS	***/
  float*	alfa;					/*	the probability vector. its size is equal to "m"								*/
  bool      alfaAllocatedInternally;
  float*	b;						/*	vector for intermediate results. its size is equal to "m"						*/
  float*	likelihoodWindow;		/*	the history of likelihoods														*/
  int		likelihoodCounter;		/*	it stores the position of the last likelihood calculated                        */
  float*	speedWindow;			/*	the history of speeds															*/
  int		speedCounter;			/*	it stores the position of the last speed calculated								*/
  int		calculationWindowStart;	/*	the start of the calculation window												*/
  int		calculationWindowEnd;	/*	the start of the calculation window												*/
  int		oldIndex;				/*	the previous index																*/
  int		freezeLikelihoodCount;	/*	in how many steps the freeze of the likelihood will end							*/
  float		likelihood_th;
  bool		restartCase;			/*	tells if the current iteration is going to be restarted or not					*/
  GFregions regions;
  //int*		regions;			/*	list of active regions of the phrase (begin1, end1, begin2, end2 ecc...)		*/
  //int		nRegions;				/*  the number of regions															*/
  void		setRegions(int* obs, int size);
  
  //Results
  int*		index;
  float*	n_index;
  float*	likelihood;
  float*	n_likelihood;
  float*	speed;
  
  /***	CLASS CONSTRUCTOR/DECONSTRUCTOR	***/
  Phrase(GF* parent , float* BMean, int capacity, int id, float* alfa);  /*  create a new Phrase object, allocating internal memory for calculation. It takes also the pointer of the BMean matrix and results, which are preallocated externally. */
  ~Phrase();												/*  it destroys all its internal fields except BMean, which is allocated externally.                                                                        */
  
  
  /***	CLEAR METHODS	***/
  void	reset();				/*	reset any field                             */
  void	resetDecodingData();	/*	reset any decoding data                     */
  void	resetRegions();			/*  reset regions to default (1 region long as the whole phrase) */
  void	initAlfa();				/*	initialize alfa (depending on "init_type")	*/
  void	initAlfa(int pos);		/*	initialize alfa (depending on "init_type")	*/
  void	resetSpeed();			/*  resetting speed                             */
  void	resetLikelihood();		/*  resetting likelihood                        */
  
  void setMaxFrames(int maxFrames);
  
  /***	ALGORITHM FUNCTIONS		***/
  void	calculateWindow();					//	FILTERING: applying various filtering to processing data
  void	calculateDistances(float* O);       //	CALCULATING DISTANCES :	calculate "b" from scratch, that is a vector with "m" length calculated only where no filters are applied
  //																			that contains distances between O (the incoming vector) and each row of BMean
  void	translate();                        //	TRANSLATION OF ALFA
  void	propagation();                      //	PROPAGATION: b *= alfa  (b is still in [wStart,wEnd], with zeros where alfa is not defined)
  void	calculateIndexSpeed();              //	CALCULATING INDEX	/ DETECTING SPEED
  void	applyRegions();						//	APPLY REGIONS: erasing alpha where regions are not active
  //void	calculateTransitionMatrix();		//	CALCULATING THE EXPECTED PROBABILITY VECTOR
  void	calculateLikelihood(float alfaSum);	//	CALCULATING LIKELIHOOD
  int	normalizeAlfa(float alfaSum);		//	ALFA NORMALIZATION
};

#endif


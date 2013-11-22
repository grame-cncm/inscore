#include "GFlib.h"

/*#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif*/

/***********************			GESTURE CLASS		********************/

//  Static
const float	  GF::AUTORESTART_AMOUNT  = 0.95;	/*  used in the autoRestart() method   */
const int	  GF::MAXSPEED			  =	3;
const int	  GF::FIRST				  =0;
const int	  GF::ANY				  =1;
const int	  GF::MAHAL				  =	0;
const int	  GF::KL				  =	1;
const int	  GF::MAXSCENES			  =	10;
const float	  GF::SCORE_TH			  =	0.1;	/*	the threshold to convert a float into a boolen in the score  */
const int	  GF::LH_MIN			  =	-100;
const int	  GF::MAX_REGIONS		  =	32;		/* the maximum number of regions for each phrase	*/




/***	CLASS CONSTRUCTOR	***/

#pragma mark -
#pragma mark Class

GF::GF(GFClient* client_, int maxPhrases_,	int channels_, long capacity_,	float** BMeans_, float** alfa_, float*** score_)  {	/*  requirement in order to create a GF: BMeans_ must be a float pointer of a two dimensional preallocated array [maxPhrases_][channels_*capacity_] */
  
  /*	DEFAULT PARAMETERS	*/
  
  client = client_;
  
  //State
  isLearning = false;
  isDecoding = false;              
  isPlaying	= false;
  isPaused = false;
  autoTimeTag = false;
  forward = false;
  isLikelihoodWindowNorm = false;
  learningPhrase = 0;
  markerOffset	= 0;
  autoRestartLimit = 10;
  
  //Memory
  maxPhrases = maxPhrases_;
  defaultMaxFrames	= capacity_;
  maxChannels = MAX_DEFAULT_ALLOC_CHANNELS;
  channels = channels_;
  windowSize = 1000;
  channelName	= new std::string[maxChannels];
  for (int i=0; i<maxChannels; ++i)
  {
    std::stringstream s;
    s<<"CH-"<<i+1;
    channelName[i] = s.str();
  }
  maxLearnedPhrasesIndex = -1; //no leaned phrases
  
  //Performance
  tolerance = 0.2;
  likelihoodWindowSize	= 50;
  smoothingSpeed	= 50;
  tolerance	= 0.2;
  beginning	= FIRST;
  metric = MAHAL;
  likelihoodContrast = 1;
  frameperiod	= GFDEFAULTFRAMEPERIOD;
  weights  = new float[maxChannels];
  for (int i=0;i < maxChannels;++i)  
    weights[i] = 1;
  
  autorestart = 0;
  freezeLikelihoodAmount	=	5;
  
  viterbi = false;
  
  minObs = new float[maxChannels];
  maxObs = new float[maxChannels];
  rangeObs = new float[maxChannels];
  normalization = false;
  for (int i=0; i<maxChannels; ++i)
  {
    minObs[i] =  INF;
    maxObs[i] = - INF;
    rangeObs[i] = INF;
  }
  
  //Allocate BMeans
  float** BMeans;
  if (BMeans_ != NULL){//memory allocated externally
    BMeans = BMeans_;
    BMeanAllocatedInternally = false;
  }
  else{
    BMeans = new float*[maxPhrases];
    for (int i=0; i<maxPhrases; ++i)
      BMeans[i] = new float[channels * defaultMaxFrames];
    BMeanAllocatedInternally = true;
  }
  
  
  //Score
  sceneEnable = false;
  scene	= 0;
  
  if (score_ != NULL){//memory allocated externally
    score	= score_;
    scoreAllocatedInternally = false;
  }
  else{
    
    //  Allocating score : Score is a vector of "maxScene" matrixes, each with "maxPhrases+2" * "maxPhrases+2" allocated memory ("+2" is because of the "begin" and "end" rows)
    score = new float** [GF::MAXSCENES];
    if (!score) {
      client->memoryError("initializing the score");
    }
    for (int s=0; s<GF::MAXSCENES; s++ ){
      score[s] = new float* [maxPhrases+1];
      if (!score[s]) {
        client->memoryError("initializing the score");
      }
      for (int i=0; i<maxPhrases+1; ++i){
        score[s][i] = new float[maxPhrases+1];
        if (!score[s][i]) {
          client->memoryError("initializing the score");
        }
      }
    }
    scoreAllocatedInternally = true;
  }
  
  initScore();		//init score all to 1
  
  //Results
  index			= new int	[maxPhrases_];
  n_index		= new float	[maxPhrases_];
  likelihood	= new float	[maxPhrases_];
  n_likelihood	= new float	[maxPhrases_];
  speed			= new float	[maxPhrases_];
  
  //transition matrix
  expectedSpeed	=	new float	[MAXSPEED+1];					/*	vector for expected probability. its size is "MAXSPEED+1", with values in [0,MAXSPEED+1]. it doesn't require any initialization  */
  expectedSpeed[0] = 0.33;
  expectedSpeed[1] = 0.34;
  expectedSpeed[2] = 0.33;
  expectedSpeed[3] = 0.0;
  
  /***	FIELDS	***/
  
  /*
   //  Debugging fields
   errorDescr = "";
   
   //initializing errorDescr to GFlib info
   time_t myTime = time(NULL);
   tm *time = localtime(&myTime);
   std::stringstream s;
   s <<time->tm_mday<<"/"<<time->tm_mon+1<<"/"<<(time->tm_year+1900);
   errorDescr += s.str();
   */
  
  // Decoding fields
  likeliest     = 0;
  
  phrase = new Phrase* [maxPhrases];
  
  for (int i=0; i<maxPhrases; ++i)  {
    if (alfa_ == NULL)
      phrase[i]	=	new Phrase(this , BMeans[i], capacity_, i, NULL);
    else {
      phrase[i]	=	new Phrase(this , BMeans[i], capacity_, i, alfa_[i]);
    }
    
  }
}

GF::~GF()
{	/*  deconstructor  */  
  if (scoreAllocatedInternally)
  {
	// deallocating score 
	for (int s = 0; s < GF::MAXSCENES; ++s)
	{
	  for (int i = 0; i < maxPhrases+1; ++i)
		delete[] score[s][i];
	  delete[] score[s];
	}
	delete[] score;
  }
  
  if (BMeanAllocatedInternally)
  {
    for (int i=0; i<maxPhrases; ++i)
      delete[] phrase[i]->BMean;
  }
  
  for (int i=0; i<maxPhrases; ++i)
    delete phrase[i];
  delete  phrase;

  delete [] expectedSpeed;
  delete [] weights;
  delete [] index;
  delete [] n_index;
  delete [] likelihood;
  delete [] n_likelihood;
  delete [] speed;
  delete [] channelName;
  delete [] minObs;
  delete [] maxObs;
  delete [] rangeObs;
}


#pragma mark -
#pragma mark Memory

//set the number of max phrases with a given external memory pointer (NULL for allocating memory internally)
bool GF::setMaxPhrases(int newMaxPhrases, float** _BMeans, float** _alfa, int* sizes, int *capacity)
{ 
  if (newMaxPhrases < 1)
  {
    client->phraseOutOfBounds("maxPhrases", newMaxPhrases);
    return false;
  }
  
  int oldMaxPhrases = maxPhrases;
  maxPhrases = newMaxPhrases;
  
  //deallocating old memory
  if (BMeanAllocatedInternally)
    for (int i=0; i<oldMaxPhrases; ++i)
      delete[] phrase[i]->BMean;

  //Allocating memory internally
  if (_BMeans == NULL)
  { 
    _BMeans = new float*[newMaxPhrases];
    if(!_BMeans)
      client->memoryError("");
    
    for (int i=0; i<newMaxPhrases; ++i)
    {
      _BMeans[i] = new float[channels * capacity[i]];
      if(!_BMeans[i])
        client->memoryError("");
    }
    BMeanAllocatedInternally = true;
  }
  else
    BMeanAllocatedInternally = false;
  
  if(scoreAllocatedInternally)
  {
    //deallocate old scores
    for (int s = 0; s < GF::MAXSCENES; ++s){
      for (int i = 0; i < oldMaxPhrases+1; ++i)
        delete[] score[s][i];
      delete[] score[s];
    }
    
    for (int s=0; s<GF::MAXSCENES; ++s)
    {
      score[s] = new float* [newMaxPhrases+1];
      if (!score[s])
        client->memoryError("initializing the score");
      
      for (int i=0; i<newMaxPhrases+1; ++i)
      {
        score[s][i] = new float[newMaxPhrases+1];
        if (!score[s][i])
          client->memoryError("initializing the score");
      }
    }
    initScore();		//init score all to 1
  }
  
   //Results
  delete [] index;
  index	= new int[maxPhrases];
  delete [] n_index;
  n_index		= new float[maxPhrases];
  delete [] likelihood;
  likelihood	= new float[maxPhrases];
  delete [] n_likelihood;
  n_likelihood	= new float[maxPhrases];
  delete [] speed;
  speed	= new float[maxPhrases];
  
  //deleting old phrases
 Phrase *currentPhrase = NULL;
  for (int i=0; i<oldMaxPhrases; ++i)
  {
    currentPhrase = phrase[i];
    delete currentPhrase;
  }
  delete  phrase;
   
  //creating new phrases
  phrase = new Phrase* [newMaxPhrases];
  for (int i=0; i < newMaxPhrases; i++)  
  {
    phrase[i]	=	new Phrase(this , _BMeans[i],  capacity[i], i, _alfa[i]);
    if(phrase[i] != NULL && phrase[i]->correct)
    {
      phrase[i]->size = sizes[i];
      for(int j = 0; j < phrase[i]->size; j++)
        phrase[i]->timetags[j] = frameperiod * j;
    }
    else
    {
      delete phrase[i];
      maxPhrases = i-1;
      return false;
    }
    //phrase[i]->learned = (sizes[i] > 0);
  }
  return true;
}

void 
GF::updatePhraseMemory(float* _BMean, float* _alfa, int size, int maxFr, int phraseIndex)
{ 
  if(phraseIndex < maxPhrases)
  {
    phrase[phraseIndex]->BMean = _BMean;
    phrase[phraseIndex]->alfa = _alfa;
    phrase[phraseIndex]->size = size;
    phrase[phraseIndex]->setMaxFrames(maxFr);
    for(int i = 0; i < size; i++){
      phrase[phraseIndex]->timetags[i] = frameperiod * i;
    }
  }
}

void GF::setMaxFrames(int mf){ defaultMaxFrames = mf;} 
void GF::setChannels(int ch){ channels = ch;} 

void GF::setMaxChannels(int newMaxChannels)
{ 
  maxChannels = newMaxChannels;
  
  delete [] channelName;
  channelName		= new std::string[maxChannels];
  for (int i = 0; i<maxChannels; i++){
    std::stringstream s;
    s<<"CH-"<<i+1;
    channelName[i] = s.str();
  }
  
  delete [] weights;
  weights = new float[maxChannels];
  for (int i = 0;i < maxChannels; i++)  
    weights[i] = 1;
  
  delete [] minObs;
  minObs = new float[maxChannels];
  delete [] maxObs;
  maxObs = new float[maxChannels];
  delete [] rangeObs;
  rangeObs = new float[maxChannels];
  
  for (int i=0; i < maxChannels; i++)
  {
    minObs[i] =  -INF;
    maxObs[i] =   INF;
    rangeObs[i] = INF;
  }  
}


/***	CLEAR METHODS	***/

#pragma mark -
#pragma mark Clear/Restart

void		GF::clear(int i){	//clear learning and decoding data of the given phrase
  if (i>=0 && i<maxPhrases){
    if (phrase[i]->learned){
      phrase[i]->reset();	//clear one phrase
      updateMaxLearnedPhraseIndex();
    }
  }
}

void        GF::updateMaxLearnedPhraseIndex(){
  maxLearnedPhrasesIndex = -1;
  for (int i=0; i<maxPhrases; ++i){
    if (phrase[i]->learned)
      maxLearnedPhrasesIndex = i;
  }
}

void		GF::clearAll(){					// clear all
  for (int i=0; i<maxPhrases; ++i){
    GF::clear(i);
  }
}
void		GF::clear(std::string name){			//clear a phrase specified by its name
  for (int i=0; i<maxPhrases; ++i){
    if (phrase[i]->name == name)
      GF::clear(i);
  }
}

void		GF::clear(int phrase_idx,	int example_idx){
  GF::clear(phrase_idx);
}


void		GF::clear(std::string name,		int example_idx){
  GF::clear(name);
}


void		GF::play(float s){	//"-1" means "the last speed detected"
  isPlaying = true; //play mode
  setDecoding(true);
  for (int p=0; p<maxPhrases; p++){
    if (s != -1){
      speed[p] = s;	//set the given speed
    }
  }
}


void		GF::restart(int i){	//reset any decoding data of the given phrase
  if (i>= 0 && i<maxPhrases && phrase[i]->learned)
    phrase[i]->resetDecodingData();
}


void		GF::restartAll(){	//reset any decoding data of all phrases
  for (int i=0; i<maxPhrases; ++i){
    restart(i);
  }
  setScene(scene);	//reset all the "enabled" parameter to the initial state of the current scene
}
void	GF::initScore(){	//reset score to default (all transitions are possible)
  for (int s=0; s<MAXSCENES; ++s){
    for (int i=0; i<=maxPhrases; ++i)	{	//the first row is the "begin" row. it specifies wich phrases are active as soon as this scene is selected.
      score[s][i][0]=0;	//the "end" row is initialized to 0 (off)
      for (int j=1; j<=maxPhrases; ++j)	
        score[s][i][j]=1;
    }
  }
}

/***	SETTING PARAMETERS	***/

#pragma mark -
#pragma mark Parameters

void		GF::setBeginning(int x){
  if (x == FIRST){
    beginning = FIRST;
  }
  else if (x == ANY){
    beginning = ANY;
  }
  else{
    std::stringstream s;
    s <<"Beginning must be "<<FIRST<<" (for FIRST) or "<<ANY<<" (for ANY)";
    client->errorGeneric(s.str());
  }
}

void		GF::setAutoRestart(int i){
  if (i<0 || i>2){
    client->errorGeneric("autorestart must be 0, 1 or 2");
    return;
  }
  autorestart = i;
}
void		GF::setExpectedSpeed(float* f){
  for (int i=0; i <= MAXSPEED; ++i)
    expectedSpeed[i] = f[i];
}
void		GF::setMetric(int x){
  
  if (x == MAHAL){
    metric = MAHAL;
  }
  else if (x == KL){
    metric = KL;
  }
  else {
    std::stringstream s;
    s <<"Metric must be "<<MAHAL<<" (for Mahalanobis) or "<<KL<<" (for Kullback-Leibler)";
    client->errorGeneric(s.str());
  }
  
}
void		GF::setLikelihoodContrast(float x){
  if (x < 0 || x > 2){
    client->errorGeneric("Likelihood contrast must be in [0,2]");
    return;
  }
  likelihoodContrast = x;
}


void		GF::setLikelihoodWindow(int x){
  if (x<1){
    
    std::stringstream s;
    s <<"likelihoodwindow must be greater than zero but it is "<<x;
    client->errorGeneric(s.str());
    return;
  }
  
  likelihoodWindowSize = x;
  isLikelihoodWindowNorm = false;
  
  //rebuilting all LH windows
  for (int i=0;i<maxPhrases;++i){
    delete phrase[i]->likelihoodWindow;           //deallocating old window
    phrase[i]->likelihoodWindow = new float[likelihoodWindowSize];  //allocating window with the nez size
    phrase[i]->resetLikelihood();                 //resetting the window (setting all values to zero)
  }
}

//set likelihoodwindow as percentage of the longest phrase
void GF::setLikelihoodWindowNorm(float f)
{
  if (f < 0){
    std::stringstream s;
    s <<"likelihoodwindownorm must be greater than zero but it is "<<f;
    client->errorGeneric(s.str());
    return;
  }
  int longest = 0;
  for (int i=0; i<maxPhrases; ++i)
    if (longest < phrase[i]->size)
      longest = phrase[i]->size;
  
  likelihoodWindowSize = longest*f / 100;
  isLikelihoodWindowNorm = true;
  likelihoodWindowPercentage = f;
  
  //rebuilting all LH windows
  for (int i=0;i<maxPhrases;++i)
  {
    delete phrase[i]->likelihoodWindow;           //deallocating old window
    phrase[i]->likelihoodWindow = new float[likelihoodWindowSize];  //allocating window with the nez size
    phrase[i]->resetLikelihood();                 //resetting the window (setting all values to zero)
  }
}

void		GF::setLearning(int i){
  
  if (i<0 || i >= maxPhrases){
    std::stringstream s;
    s <<"learn message error:gesture_index must be in [1,"<<maxPhrases<<"]. Syntax: learn int:gesture_index [int:example_index] [symbol:name]";
    client->errorGeneric(s.str());
    return;
  }
  
  isLearning = true;
  learningPhrase = i;
  clear(learningPhrase);  //clear learning and decoding data of the learning phrase
}


void		GF::setLearning(int phrase_idx,int example_idx){
  if (phrase_idx >= 0 && phrase_idx < maxPhrases)
    GF::setLearning(phrase_idx);
  else{
    client->phraseOutOfBounds("setlearning", phrase_idx);
  }
};


void		GF::setLearning(int phrase_idx,int example_idx, std::string name_){
  setLearning(phrase_idx);
  if (phrase_idx >= 0 && phrase_idx < maxPhrases)
    phrase[phrase_idx]->name = name_;
  else{
    client->phraseOutOfBounds("setlearning", phrase_idx);
  }
};


void		GF::setLearningOff() {	//= learn off
  
  isLearning = false;
  if (phrase[learningPhrase]->size > 0){
    phrase[learningPhrase]->learned = true;
    phrase[learningPhrase]->regions.setSize(phrase[learningPhrase]->size);
    if (isLikelihoodWindowNorm){
      setLikelihoodWindowNorm(likelihoodWindowPercentage);
    }
  }
  updateMaxLearnedPhraseIndex();
}


void		GF::setDecoding(int x){
  if (x<0 || x > 1){
    client->errorGeneric("Decoding value must be 0 or 1");
    return;
  }
  if (x==0){
    isDecoding = false;
  }
  else{
    isDecoding = true;
    restartAll();	//when start decoding, reset any decoding data of all phrases
  }
}


void GF::setTolerance(float x)
{
#ifdef TRACE_ON
  std::stringstream s3;
  s3 <<"SET TOLERANCE "<<x;
  PRINTN(s3.str());
#endif
  if (x<=0)
  {
    client->errorGeneric("Tolerance must be greater than 0");
    return;
  }
  /*
   //scaling tolerance in [minTolerance, maxTolerance]
   tolerance = x * (maxTolerance - minTolerance) + minTolerance;
   //assign the new tolerance to each phrase, normalizing it by the number of channels
   for (int i=0; i<maxPhrases; ++i)
   phrase[i]->tolerance = tolerance / sqrt(phrase[i]->channels);
   */
  tolerance = x;
}

void GF::setChannelName(int id, std::string name)
{
  if (id>=0 && id<channels)
    channelName[id] = name;
}

void GF::setChannelNames(std::string* names, int size)
{  
  for (int i=0; i<channels; ++i)
  {
    if (i<size)
      channelName[i] = names[i];
  }
}

void GF::setFramePeriod(float frameperiod_)
{
  if (frameperiod_ > 0)
    frameperiod = frameperiod_;
}

void GF::setName(int index, std::string name)
{
  if (index>=0 && index < maxPhrases)
    phrase[index]->name = name;
}

void GF::setSmoothingSpeed(int x)
{
  if (x<1)
  {
    client->errorGeneric("Smoothing speed (the size of the speed window) must be greater than zero");
    return;
  }
  smoothingSpeed = x;
  
  //rebuilting all speed windows
  for (int i=0;i<maxPhrases;++i)
  {
    delete phrase[i]->speedWindow;            //deallocating old window
    phrase[i]->speedWindow = new float[x];    //allocating window with the nez size
    phrase[i]->resetSpeed();                  //resetting the window (setting all values to zero)
  }
}

void GF::setWeights(float *newWeights, int size)
{  
  int i;
  
  if(size > maxChannels)
    size = maxChannels;
  
  for (i = 0; i < size; i++)
  {
    if(newWeights[i] > 0.0)
      weights[i] = (float)newWeights[i];
    else
      weights[i] = 0.0f;
  }
  
  for (; i < maxChannels; i++)
    weights[i] = 0.0f;
}

void GF::setWeights(double *newWeights, int size)
{  
  int i;
  
  if(size > maxChannels)
    size = maxChannels;
  
  for (i = 0; i < size; i++)
  {
    if(newWeights[i] > 0.0)
      weights[i] = (float)newWeights[i];
    else
      weights[i] = 0.0f;
  }
  
  for (; i < maxChannels; i++)
    weights[i] = 0.0f;
}

void GF::setWindowSize(int windowSize_)
{
  //checking costraints
  if (windowSize_ < 0)
  {
    client->errorGeneric("Window size must be greater than zero");
    return;
  }
  
  //updating parameter
  windowSize = windowSize_;
}

void GF::setViterbi(bool b)
{
  viterbi = b;
}

void GF::setMarkerOffset(int offset)
{
  markerOffset = offset;
}

void GF::setForward(bool b)
{
  forward = b;
}

#pragma mark -
#pragma mark Normalization

void      GF::setNormalization(bool b){
  normalization = b;
}

void      GF::setMinMax(int channelIndex, float min, float max){
  if (channelIndex < channels && min <= max){
    minObs[channelIndex] = min;
    maxObs[channelIndex] = max;
    rangeObs[channelIndex] = max - min;
  }
}


void      GF::normalizeAllPhrases(){
  
  //is empty?
  bool empty = true;
  for (int i=0; i<maxPhrases; ++i){
    if (phrase[i]->learned){
      empty = false;
      break;
    }
  }
  if (empty) return;
  
  
  //reset
  for (int i=0; i<channels; ++i){
    minObs[i] =  INF;
    maxObs[i] = - INF;
    rangeObs[i] = INF;
  }
  
  
  //find new bounds
  for (int i=0; i<maxPhrases; ++i){
    if (phrase[i]->learned){
      int size = phrase[i]->size;
      for (int j=0; j<size; ++j){
        for(int ch=0; ch<channels; ++ch){
          int index = channels*j+ch;
          if (phrase[i]->BMean[index] < minObs[ch])
            minObs[ch] = phrase[i]->BMean[index];
          if (phrase[i]->BMean[index] > maxObs[ch])
            maxObs[ch] = phrase[i]->BMean[index];
        }
      }
    }
  }
  
  //range
  for (int i=0; i<channels; ++i){
    rangeObs[i] = maxObs[i] - minObs[i];
  }
  
  
  //normalize all phrases
  for (int i=0; i<maxPhrases; ++i){
    if (phrase[i]->learned){
      int size = phrase[i]->size;
      for (int j=0; j<size; ++j){
        normalizeObs(phrase[i]->BMean+(j*channels) , channels);
      }
    }
  }
  
}


void      GF::normalizeObs(float* obs, int size){
  for (int i=0; i<size; ++i)
  {
    obs[i] = (obs[i] - minObs[i]) / rangeObs[i];
  }
}




/***	SCORE / TRANSPORT	***/

#pragma mark -
#pragma mark Score/Transport

void		GF::enable(int* phraseList, int size){
  
  if (size == 1 && phraseList[0] == -2){ //disable all ("enable -1" in the patch)
    for (int i=0; i<maxPhrases; ++i){
      phrase[i]->enabled = false;
    }
    return;
  }
  
  if (size == 1 && phraseList[0] == -1){ //enable all ("enable 0" in the patch)
    for (int i=0; i<maxPhrases; ++i){
      phrase[i]->enabled = true;
    }
    return;
  } 
  
  for (int i=0; i<maxPhrases; ++i){
    phrase[i]->enabled = false;
  }
  
  for (int i=0; i<size; ++i){
    if (phraseList[i] >= 0 && phraseList[i] < maxPhrases){
      phrase[phraseList[i]]->enabled = true;
    }
  }
}

void GF::enableone(int i, bool b){ //enable this phrase without changing the others
  if (i >= 0 && i < maxPhrases){
    phrase[i]->enabled = b;
  }
  else{
    std::stringstream s;
    s<<"enable: phrase "<<i<<" does not exist";
    client->errorGeneric(s.str());
  }
}



void		GF::transition(int scene_, int col, int row, float value){
  if (scene_ < 0 || scene_ >= MAXSCENES){
    client->errorGeneric("Wrong number of scene. Syntax: transition scene row col value");
    return;
  }
  if (row < 0 || row > maxPhrases){
    std::stringstream s;
    s <<"The number of the row should be in [0,"<<maxPhrases+1<<"]";
    s << "Syntax: transition scene row col value";
    client->errorGeneric(s.str());
    return;
  }
  if (col < 0 || col > maxPhrases){
    std::stringstream s;
    s <<"The number of the col should be in [0,"<<maxPhrases+1<<"]";
    s << "Syntax: transition scene row col value";
    client->errorGeneric(s.str());
    return;
  }
  
  score[scene_][col][row] = value;
  
  if (value < 0){
    std::stringstream s;
    s <<"Warning: value "<<value<<" received. It will be considered as 0";
    s << "Syntax: transition scene row col value";
    client->errorGeneric(s.str());
    return;
  }
  
  if (value > 1){
    std::stringstream s;
    s <<"Warning: value "<<value<<" received. It will be considered as 1";
    s << "Syntax: transition scene row col value";
    client->errorGeneric(s.str());
    return;
  }
}



void		GF::setScene(int scene_){	//set the current scene of the score
  
  if (!sceneEnable) return;
  
  if (scene_ < 0 || scene_ >= MAXSCENES){
    std::stringstream s;
    s << "the number of the scene has to be in [0,"<< MAXSCENES <<"]";
    client->errorGeneric(s.str());
    return;
  }
  scene = scene_;
  
  for (int i=0; i<maxPhrases; ++i){
    if (score[scene][0][i+1] > SCORE_TH)	//the col zero is the "begin"
      phrase[i]->enabled = true;
    else
      phrase[i]->enabled = false;
  }
}


void		GF::nextScene(){	//applying the rules written in the score (enabling or disabling phrases)
  
  if (!sceneEnable) return;
  
#ifdef TRACE_ON
  std::stringstream s;
  s <<"APPLYING SCORE\n";
  PRINTN(s.str());
#endif
  
  //End
  if (score[scene][likeliest+1][0] > SCORE_TH){	//if the likeliest phrase has a transition to the "end"
    for (int i=0; i<maxPhrases; ++i){	//disabling all the phrases
      phrase[i]->enabled = false;
    }
    client->sceneEnded();//notify the client that the scene is ended
    
  }
  else{
    for (int i=0; i<maxPhrases; ++i){	//for each element of the scene matrix jumping the first column (the "end" column, see below)
      if (phrase[i]->learned){
        if (score[scene][likeliest+1][i+1] > SCORE_TH)	// "+1" because the first col is for the "begin" and the first row is for "end"
          phrase[i]->enabled = true;
        else
          phrase[i]->enabled = false;
      }
    }
  }
}


void		GF::goTo(int p, int pos){
  if (p < 0 || p > maxPhrases){
    std::stringstream s;
    s << "the phrase "<<p<<" does not exist";
    client->errorGeneric(s.str());
    return;
  }
  
  if (!phrase[p]->learned){
    return;
    /*std::stringstream s;
     s << "the phrase "<<p<<" has not been initialized";
     errorDescr += s.str();
     return 1;*/
  }
  if (pos<0) pos=0;
  if (pos>phrase[p]->size) pos = phrase[p]->size - 1;
  
  *phrase[p]->index = pos;	//set index	
  *phrase[p]->n_index = ((float)(*phrase[p]->index)) / phrase[p]->size;  //set normalized index
  phrase[p]->initAlfa(pos);	//set alfa
  
#ifdef TRACE_ON
  std::stringstream s;
  s << "GoTo "<<pos;
  PRINT(s.str()); 
#endif
  
}




#pragma mark -
#pragma mark Results


/***	GETTING RESULTS		***/
void	GF::normalizeLikelihoods(){	//normalize the list of likelihoods, applying normalization and contrast
  
  
#ifdef TRACE_ON
  std::stringstream s;
  s << "Likelihoods are: ";
  for (int i=0; i< maxPhrases; ++i){
    if (phrase[i]->learned && phrase[i]->enabled){	//for each initialized phrase  (so "usedPhrases" times)
      s<<" "<<i<<":    "<<likelihood[i]<<",";
    }
  }
  s << "   . ";
  PRINT(s.str()); 
#endif
  
  //apply contrast
  float nLikelihoodContrast = (likelihoodContrast-1) * 2;	//scaling likelihoodContrast from [0,1] to [-2,2]
  for (int i=0; i< maxPhrases; ++i){
    if (phrase[i]->learned && phrase[i]->enabled){	//for each initialized phrase
      n_likelihood[i] = pow(GFlibUtility::E , pow(GFlibUtility::E , nLikelihoodContrast) * likelihood[i]);	//
    }
    else	n_likelihood[i] = 0;
  }
  
  //normalization
  float sum = GFlibUtility::Sum(n_likelihood, maxPhrases);
  for (int i=0; i< maxPhrases; ++i)	//for each initialized phrase
    n_likelihood[i] /= sum;
  
  
  
#ifdef TRACE_ON
  std::stringstream s1;
  s1 << "After contrast and normalization, likelihoods are: ";
  for (int i=0; i< maxPhrases; ++i){
    if (phrase[i]->learned)
      if (phrase[i]->enabled)	//for each initialized phrase
        s1<<n_likelihood[i]<<"    ";
  }
  s1 << "   . ";
  PRINTN(s1.str());
#endif
  
}

void	GF::calculateLikeliest(){	/*	calculate the likeliest phrase	*/
  likeliest = 0;
  float max = - INF; //-infinite
  for (int i=0; i< maxPhrases; ++i){
    if (phrase[i]->learned && phrase[i]->enabled && likelihood[i] > max){
      likeliest = i;
      max = likelihood[i];
    }
  }
}


void GF::updatePhraseTimeTags(int phraseIndex, float* tg, int size)
{
  if(size <= phrase[phraseIndex]->maxFrames) 
  {
    for(int i = 0; i < size; i++){
      phrase[phraseIndex]->timetags[i] = frameperiod * i;
    }
    phrase[phraseIndex]->size = size;
    phrase[phraseIndex]->learned = true;
    phrase[phraseIndex]->regions.setSize(phrase[phraseIndex]->size);    
  }
  else{
    ostringstream s;
    s << "Phrase number " << phraseIndex << " is too small for stored observations. Its capacity is " << phrase[phraseIndex]->maxFrames << " (try creating a GestureFollower instance with a greater capacity in order to avoid this problem)";
    client->warning(s.str());
  }
}


/***	DECODING FUNCTIONS	***/
void		GF::observation(float* Obs, int size, bool normalize){	//receiving incoming observation; handling learning or call the "decoding" function for decoding
  
  if (size < 1 || (autoTimeTag && size < 2)){
    client->errorGeneric("observation has no data");
    return;
  }
  
  if (autoTimeTag)
    size--;
  
  if (size != channels){
    ostringstream s;
    s << "Incoming list has length=" << size << " but gf has " << channels << " channels. Do a 'clear' and restart the learning";
    client->errorGeneric(s.str());
    return;
  }
  
  /***	LEARNING	***/
  
  if (isLearning){
    
    phrase[learningPhrase]->learned = false;
    
    //push new observation into the active phrase
    if (phrase[learningPhrase]->size < phrase[learningPhrase]->maxFrames) {
      int m = phrase[learningPhrase]->size;
      int ch = channels;
      if (autoTimeTag){     //external sync mode: the first float of the observation is considered as timetag
        phrase[learningPhrase]->timetags[m] = Obs[0];
        for (int i=0; i<ch; ++i)
          phrase[learningPhrase]->BMean[ch*m+i] = Obs[i+1];       //add element in the "m" row
      }
      else
      {
        phrase[learningPhrase]->timetags[m] = frameperiod * m;				//Timetags (assuming costant frameperiod)
        for (int i=0; i<ch; ++i)
          phrase[learningPhrase]->BMean[ch*m+i] = Obs[i];	//add element in the "m" row
      }
      
      phrase[learningPhrase]->size++;
    }
    else{
      ostringstream s;
      s << "Phrase number " << learningPhrase << " is full and no more observations will be stored. Its capacity is " << phrase[learningPhrase]->maxFrames << " (try creating a GestureFollower instance with a greater capacity in order to avoid this problem)";
      client->warning(s.str());
    }
  }
  
  
  /***	DECODING	***/
  
  if (isDecoding){
    
    
    
    //if the GF is in pause mode, exit
    if (isPaused) return;	
    
    for (int p=0; p<maxPhrases; ++p){	//for any phrase
      if ((phrase[p]->learned) && (phrase[p]->size >= 1)){	//if the phrase has been initialized
#ifdef TRACE_ON
        std::stringstream s;
        s << "\n\nenabled list: [";
        for (int i=0; i<maxPhrases;++i)
          s<<phrase[i]->enabled<<",";
        s << "]\n";
        PRINT(s.str());
#endif
        if (phrase[p]->enabled && size == channels &&	//the decoding is done only if the number of channels of the phrase matches the size of the observation
            !(isLearning && learningPhrase==p))	//no decoding on the learning phrase
        {
#ifdef TRACE_ON
          std::stringstream s;
          s << "\n\n********      start decoding phrase "<<p<<"  with input  "<<postV(O , phrase[p]->calculationWindowStart, phrase[p]->calculationWindowEnd, size)<<"   , ";
          PRINT(s.str());
          ADDCOUNT
          std::stringstream s1;
          s1 << "      ********";
          PRINTN(s1.str());
#endif
          decoding(Obs, phrase[p], normalize); //do the decoding
        }
        else { // if the phrase is not enabled
          likelihood[p]	= - (std::numeric_limits<float>::infinity()); //-infinite
          index[p]		= 0;
          n_index[p]		= 0;
        }
      }
    }
    normalizeLikelihoods();
    calculateLikeliest();
    
    autoRestart();
  }
}


void		GF::decoding(float* Obs, Phrase* p, bool normalize){	//argument: the observation O
  
  if (isPlaying){	//play mode: go forward by "speed" steps
    int i = p->id;
    n_index[i] = fmod((n_index[i] + (speed[i] / p->size)) , 1);	//calculating n_index
    index[i] = n_index[i] * p->size;							//calculating index based on n_index to avoid rounding errors
    p->initAlfa(index[i]);										//init alfa to the current value
    return;
  }
  
  /***		normalize observation		***/
  if (normalize){
    normalizeObs(Obs, channels);
  }
  
  
  /***		 calculateWindow: calculating the calculation window		***/
  
  p->calculateWindow();		
  
#ifdef TRACE_ON
  std::stringstream s2;
  s2<<"1 - CALCULATED WINDOW: ["<< p->calculationWindowStart << " , " << p->calculationWindowEnd << "]";
  PRINTN(s2.str());
  /*
   for (int i=0; i<p->size; ++i){
   if (p->filterVector[i])	{PRINT(1);}
   else PRINT(0);
   PRINT(" , ");
   }
   PRINTN("");
   */
#endif
  
  
  
  /*			CALCULATING DISTANCES : 
   *			calculating b, that is a vector with "window" length, that contains distances between O (the incoming vector) and each row of the window of BMean		
   */
  
  p->calculateDistances(Obs);
  
  //checking if 'alfa' or 'b' are zero
  if (GFlibUtility::Sum(p->b, p->calculationWindowStart, p->calculationWindowEnd, p->size) <= GFlibUtility::FLOAT_EPSILON * p->size ||
      GFlibUtility::Sum(p->alfa,  p->calculationWindowStart, p->calculationWindowEnd, p->size) <= GFlibUtility::FLOAT_EPSILON * p->size){
    
    client->alphaIsZero(p->id); //alfa or b are zero, freezing the gesture
    p->initAlfa(*p->index);     //reinit alfa in the current point (otherwise alfa will be zero in the next iteration too)
    
#ifdef TRACE_ON
    PRINT("- FREEZING THE PHRASE BECAUSE B IS ZERO -");
    PRINTN(index[p->id]);
#endif
    
    return;
  }
  
  
  /***		TRANSLATION				***/
  
  //translating: alfa = translate(alfa)
  p->translate();
  
#ifdef TRACE_ON
  PRINT("5 - TRANSLATION: Alfa = translate(b) = ");
  PRINTN(postV(p->alfa ,  p->calculationWindowStart, p->calculationWindowEnd, p->size));
#endif
  
  
  
#ifdef TRACE_ON
  PRINT("2 - CALCULATING DISTANCES:  b =  ");
  PRINTN(postV(p->b , p->calculationWindowStart, p->calculationWindowEnd, p->size));
#endif
  
  
  
  /***		PROPAGATION: alfa *= b		***/
  
  p->propagation();	// 
  
  
  
#ifdef TRACE_ON
  PRINT("3 - PROPAGATION: b *= alfa => ");
  PRINTN(postV(p->b ,  p->calculationWindowStart, p->calculationWindowEnd, p->size));
#endif
  
  
  /***		CALCULATING INDEX	/ DETECTING SPEED	***/
  
  p->calculateIndexSpeed();
  
#ifdef TRACE_ON
  std::stringstream s1;
  s1 <<"4 - CALCULATING INDEX: highest b value = "<<hightestValueIndex(p->b, p->calculationWindowStart, p->calculationWindowEnd, p->size)<<"  , new index = "<<n_index[p->id]<<"  , speed = "<<speed[p->id];
  PRINTN(s1.str());
#endif
  
  
  
  
  p->applyRegions();
  
  
  
  /***		NORMALIZATION / LIKELIHOOD		***/
  
  float alfaSum = GFlibUtility::Sum (p->alfa ,  p->calculationWindowStart, p->calculationWindowEnd, p->size);
  
  p->calculateLikelihood(alfaSum);
  
  
  if (isnan(*(p->likelihood))){	//should never happen
    std::stringstream s;
    s<<"Likelihood of "<<p->name<<"is NaN";
    client->warning(s.str());
  }
  
  
  p->normalizeAlfa(alfaSum);
  
#ifdef TRACE_ON
  std::stringstream s3;
  s3 <<"6 - Likelihood = "<<likelihood[p->id]<<" , "<<"Normalized alfa = "<<postV(p->alfa, p->calculationWindowStart, p->calculationWindowEnd, p->size);
  PRINTN(s3.str());
#endif
  
}

void		GF::autoRestart(){	
  
  bool likeliestCompleted = false;
  
  if (phrase[likeliest]->size - phrase[likeliest]->oldIndex <= autoRestartLimit)
    likeliestCompleted = true;
  
  switch (autorestart){
      
    case 0:		//loop mode: never resetting LH
      break;
      
    case 1:		//likeliest ends -> restartAll
      if (likeliestCompleted)
        restartAll();
      break;
      
    case 2:	//lh(p) < th(p) -> resetalfa(p) + freezeLH(n)
      
      for (int p=0; p<maxPhrases; ++p){
        if (phrase[p]->learned && phrase[p]->enabled){
          if (likelihood[p] <= phrase[p]->likelihood_th && phrase[p]->freezeLikelihoodCount <= 0){
            phrase[p]->freezeLikelihoodCount = freezeLikelihoodAmount;
            restart(p);
            likelihood[p] = phrase[p]->likelihood_th; //setting the old likelihood and wait "freezeLikelihoodCount" frames before update the likelihood again
          }
        }
      }
      break;
  }
  
  if (likeliestCompleted)
    nextScene();
}




#pragma mark -
#pragma mark Debug


void	GF::getAlfa		(int idx, float* &alfa, int &size){	//for the current activePhrase, it returns alfa and its size
  idx--;//for the user, phrase starts from 1
  if (idx<0 || idx>= maxPhrases) return;
  alfa    = phrase[idx]->alfa;
  size    = phrase[idx]->size;
}


/***	DEBUGGING	***/

std::string	GF::postV(float* f, int start, int end, int size){	//return a std::string rappresentation of a float vector
  std::stringstream s;
  s << "[";
  
  int i=start;
  while(i!=end){
    s << f[i];
    s << " , ";
    i=(i+1)%size;
  }
  s << "]";
  return s.str();
}






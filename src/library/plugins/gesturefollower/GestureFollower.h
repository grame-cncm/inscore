/**
 * @file   GestureFollower.h
 * @author D. Fober
 * 
 * @brief  interface file for the gesture follower library.
 *
 * Copyright (C) 2013 by Grame, Lyon, France.
 * 
 */


#ifndef   __Gesture_Follower__
#define   __Gesture_Follower__

	
enum { kIdle=0, kLearning, kDecoding };

class GF;
class GFClient;
//--------------------------------------------------------------------------
/*!
 \brief The gesture follower interface class.
 */
class GestureFollower
{
	GF*	fGF;

	public:
		/*! \brief gesture follower constructor
			\param maxPhrases maximum input phrases that the follower can learn
			\param vecSize the size of each frame
			\param capacity the internal buffer size for each phrase (in frames)
		*/
				 GestureFollower(int maxPhrases, int vecSize, long capacity, GFClient* client=0);
		virtual ~GestureFollower();
		
		/*! \brief start to learn a phrase
			\param phraseIndex the phrase index 
		*/
		void	startLearn	(int phraseIndex);
		/*! \brief stop phrase learning */
		void	stopLearn	();		
		/*! \brief clear a phrase
			\param phraseIndex the phrase index 
		*/
		void	clear		(int phraseIndex);
		/*! \brief clear all phrases */
		void	clearAll	();

		/*! \brief start following gestures */
		void	startFollow	();
		/*! \brief stop following gestures */
		void	stopFollow	();

		/*! \brief sets the likelihood window size 
			\param size the window size
		*/
		void	setLikelihoodWindow (int size);

		/*! \brief gives the maximum phrases the gesture can handle 
			\return the maximum phrases value
		*/
		int		getMaxPhrases () const;

		/*! \brief gives the data frame size
			\return the data frame size
		*/
		int		getFrameSize () const;

		/*! \brief gives the follower capacity
			\return the follower capacity
		*/
		int		getCapacity () const;

		/*! \brief gives the likelihood window size 
			\return the likelihood window size
		*/
		int		getLikelihoodWindow () const;

		/*! \brief sets the follower tolerance 
			\param tolerance the tolerance (!! documenter)
		*/
		void	setTolerance (float tolerance);

		/*! \brief gives the follower tolerance 
			\return the tolerance value
		*/
		float	getTolerance () const;
		
		/*! \brief gesture data input
			\param data a pointer to float values
			\param size the values count
			\note observation should be called to input data both in learning and in decoding modes
		*/
		void	observation (float* data, int size);
		
		/*! \brief gives the likeliest recognized phrase index */
		int				likeliest() const;
		/*! \brief gives the current normalized location in the phrases (i.e. in [0,1]) */
		const float*	where() const;
		/*! \brief gives the normalized likelihood for all the phrases (i.e. sum of p is 1) */
		const float*	likelihood() const;
		/*! \brief gives the current phrases speed (i.e. a smoothed estimation of index_i - index_i-1)  */
		const float*	speed () const;

		/*! \brief gives a phrase current size 
			\param a phrase index
			\return the phrase current size
		*/
		int				getPhraseSize (int index) const;
		/*! \brief gives the follower current state (idle, learning or following) */
		int				getState() const;
};



#ifdef __cplusplus
extern "C" {
#endif

float		gfVersion();
const char* gfVersionStr();

GestureFollower *	newGestureFollower (int maxPhrases, int vecSize, long capacity, GFClient* client);
void				delGestureFollower (GestureFollower * gf);

void			startLearn	(GestureFollower * gf, int phraseIndex);
void			stopLearn	(GestureFollower * gf);		
void			clear		(GestureFollower * gf, int phraseIndex);
void			clearAll	(GestureFollower * gf);
void			startFollow	(GestureFollower * gf);
void			stopFollow	(GestureFollower * gf);
void			setLikelihoodWindow (GestureFollower * gf, int size);
int				getMaxPhrases (GestureFollower * gf);
int				getFrameSize (GestureFollower * gf);
int				getCapacity (GestureFollower * gf);
int				getLikelihoodWindow (GestureFollower * gf);
void			setTolerance (GestureFollower * gf, float tolerance);
float			getTolerance (GestureFollower * gf);
void			observation (GestureFollower * gf, float* data, int size);
int				likeliest(GestureFollower * gf);
const float*	where(GestureFollower * gf);
const float*	likelihood(GestureFollower * gf);
const float*	speed (GestureFollower * gf);
int				getPhraseSize(GestureFollower * gf, int i);
int				getState(GestureFollower * gf);

#ifdef __cplusplus
}
#endif


#endif

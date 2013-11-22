
#ifndef gfollower_h
#define gfollower_h

#include "GestureFollower.h"

class QProgressBar;

class gfollower : public GestureFollower
{
	QProgressBar*	fBar1;
	QProgressBar*	fBar2;
	QProgressBar*	fBar3;
	int				fBarScale;

	public:
		enum { kMaxPhrases=3, kSize = 512  };

				 gfollower();
				~gfollower() {}

	void setBars(QProgressBar* b1, QProgressBar* b2, QProgressBar* b3, int scale)
		{ fBar1=b1; fBar2=b2; fBar3=b3; fBarScale=scale; }
	void showlikelihood() const;

	void stop();
	void data(float x, float y);
};

#endif

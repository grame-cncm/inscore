

#include <iostream>
#include <QProgressBar>

#include "gfollower.h"


gfollower::gfollower() : GestureFollower(kMaxPhrases, 2, kSize)
	, fBar1(0) 
	, fBar2(0) 
	, fBar3(0) 
	, fBarScale(1)
	{}

void gfollower::stop()
{
	switch (getState()) {
		case kLearning:
			stopLearn();
			break;
		case kDecoding:
			stopFollow();
			break;
	}
}

void gfollower::showlikelihood() const
{
	if (fBar1 && fBar2 && fBar3) {
		const float* l = likelihood();
		fBar1->setValue (l[0] * fBarScale);
		fBar2->setValue (l[1] * fBarScale);
		fBar3->setValue (l[2] * fBarScale);
	}
}

void gfollower::data(float x, float y)
{
	state s = getState();
	if (s != GestureFollower::kIdle) {
		float data[2];
		data[0] = x;
		data[1] = y;
		observation(data, 2);
		if (s == GestureFollower::kDecoding) showlikelihood();
	}
}



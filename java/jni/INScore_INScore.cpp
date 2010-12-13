/*
	INScore Library - JNI Interface
	Copyright (C) 2010 Grame
	All rights reserved.
	Author D. Fober

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <iostream>
#include <QApplication>

#include "INScore_INScore.h"
#include "INScore.h"
#include "javaIDs.h"

using namespace std;

static QApplication * gApplication;

// --------------------------------------------------------------------------------------------
// fields IDs declarations
// --------------------------------------------------------------------------------------------
// the score handlers ID
static jfieldID gINSHandlerID, gINSListenerID;


using namespace inscore;

//--------------------------------------------------------------------------
class JavaListener : public GraphicUpdateListener
{
	JavaVM *	fVM;
	jobject		fObject;
	jmethodID	fMethodID;

	public :
				 JavaListener() { fObject = 0; }
		virtual ~JavaListener();
		bool init (JNIEnv* env, jobject	obj, jmethodID method);
		void update();
};

JavaListener::~JavaListener() {
	if (fObject) {
		JNIEnv*	env;
		if (fVM->AttachCurrentThread((void**)&env, 0)) {
			env->DeleteGlobalRef (fObject);
			fVM->DetachCurrentThread();
		}
	}
}

bool JavaListener::init (JNIEnv* env, jobject obj, jmethodID method)
{
	jint result = env->GetJavaVM (&fVM);
	if (result) {
		std::cerr << ">>> INScore JNI GetJavaVM failed" << std::endl;
		return false;
	}
	if (fObject) env->DeleteGlobalRef (fObject);
	fObject = env->NewGlobalRef(obj);
	fMethodID = method;
	return true;
}

void JavaListener::update ()	{ 
	JNIEnv*	env;
	if (fVM->AttachCurrentThread((void**)&env, 0))
		std::cerr << ">>> INScore JNI AttachCurrentThread failed" << std::endl;		
	else {
		env->MonitorEnter (fObject);
//cout << "[";
		env->CallVoidMethod (fObject, fMethodID);
//cout << "]\n";
		env->MonitorExit (fObject);
//		fVM->DetachCurrentThread();
	}
}

//--------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     INScore_INScore
 * Method:    GetVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_INScore_INScore_GetVersion
  (JNIEnv * env, jclass)
{
	return env->NewStringUTF(INScore::versionStr());
}

/*
 * Class:     INScore_INScore
 * Method:    GetJNIVersion
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_INScore_INScore_GetJNIVersion
  (JNIEnv * env, jclass)
{
	return env->NewStringUTF("1.00");
}

/*
 * Class:     INScore_INScore
 * Method:    Start
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_INScore_INScore_Start
  (JNIEnv * env, jobject obj, jint timeInterval, jint udpin, jint udpout, jint udperr)
{
	IGlue* glue = (IGlue*)env->GetLongField (obj, gINSHandlerID);
	if (glue) INScore::stop(glue);
	
	glue = INScore::start (timeInterval, udpin, udpout, udperr, true);
	env->SetLongField (obj, gINSHandlerID, (long)glue);
}

/*
 * Class:     INScore_INScore
 * Method:    Stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_INScore_INScore_Stop
  (JNIEnv * env, jobject obj)
{
	IGlue* glue = (IGlue*)env->GetLongField (obj, gINSHandlerID);
	if (!glue) return;

	INScore::stop (glue);
	env->SetLongField (obj, gINSHandlerID, 0);
}

/*
 * Class:     INScore_INScore
 * Method:    GetBitmap
 * Signature: ([III)I
 */
JNIEXPORT void JNICALL Java_INScore_INScore_GetBitmap
  (JNIEnv * env, jobject obj, jintArray bitmapArray, jint w, jint h)
{
	IGlue* glue = (IGlue*)env->GetLongField (obj, gINSHandlerID);
	if (!glue) return;

	jint *dstBitmap = env->GetIntArrayElements(bitmapArray, 0);
	if (!dstBitmap) return;

//cout << "<<";
	INScore::getGraphicScore (glue, (unsigned int *)dstBitmap, w, h);
//cout << ">>\n";

	env->ReleaseIntArrayElements(bitmapArray, dstBitmap, 0);
}

/*
 * Class:     INScore_INScore
 * Method:    timeTask
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_INScore_INScore_TimeTask
  (JNIEnv * env, jobject obj)
{
	IGlue* glue = (IGlue*)env->GetLongField (obj, gINSHandlerID);
	if (!glue) return;
//cout << "(";
	INScore::timeTask(glue);
//cout << ")\n";
}

/*
 * Class:     INScore_INScore
 * Method:    SetViewListener
 * Signature: (LINScore/ViewListener;)V
 */
JNIEXPORT void JNICALL Java_INScore_INScore_SetViewListener
  (JNIEnv * env, jobject obj, jobject listener)
{
	IGlue* glue = (IGlue*)env->GetLongField (obj, gINSHandlerID);
	if (!glue) return;

	JavaListener* currentlistener = (JavaListener*)env->GetLongField (obj, gINSListenerID);
	if (currentlistener) delete currentlistener;
	
	JavaListener* newListener = 0;
	if (listener) {
		jclass cl = env->GetObjectClass(listener);
		jmethodID javaCallback = env->GetMethodID (cl, "update", "()V"); 
		if (javaCallback == NULL) {
			fprintf(stderr, "ViewListener::update got NULL jmethodID\n");
		}
		else {
			newListener = new JavaListener;
			if (newListener->init (env, listener, javaCallback))
				INScore::setListener (glue, newListener);
		}
	}
	env->SetLongField (obj, gINSListenerID, (long)newListener);
}

/*
 * Class:     INScore_INScore
 * Method:    Init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_INScore_INScore_Init
  (JNIEnv * env, jclass cls)
{
	if (!getID (env, cls, gINSHandlerID, "fINSHandler", "J")) return;
	if (!getID (env, cls, gINSListenerID, "fINSListener", "J")) return;
	int argc = 0; char** argv = 0;
	gApplication = new QApplication(argc, argv);
}

#ifdef __cplusplus
}
#endif

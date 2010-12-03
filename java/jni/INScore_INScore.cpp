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

#include "INScore_INScore.h"
#include "INScore.h"

inscore::IGlue* gGlue = 0;

using namespace inscore;

//--------------------------------------------------------------------------
class JavaListener : public GraphicUpdateListener
{
	bool		fGlobalRef;
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
		if (fVM->AttachCurrentThread((void**)&env, 0))
			env->DeleteGlobalRef (fObject);
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
	fGlobalRef = true;
	fMethodID = method;
	return true;
}

void JavaListener::update ()	{ 
	JNIEnv*	env;
	if (fVM->AttachCurrentThread((void**)&env, 0))
		std::cerr << ">>> INScore JNI AttachCurrentThread failed" << std::endl;		
	else
		env->CallVoidMethod (fObject, fMethodID);
}

JavaListener gListener;

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
  (JNIEnv *env, jclass)
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
 * Method:    SetViewListener
 * Signature: (LINScore/ViewListener;)V
 */
JNIEXPORT void JNICALL Java_INScore_INScore_SetViewListener
  (JNIEnv * env, jclass, jobject listener)
{
	static bool errNotified = false;
	jclass cl = env->GetObjectClass(listener);
	jmethodID javaCallback = env->GetMethodID (cl, "update", "()V");
	if (javaCallback == NULL) {
		if (!errNotified) {
			fprintf(stderr, "ViewListener::update got NULL jmethodID\n");
			errNotified = true;
		}
		return;
	}
	if (gListener.init (env, listener, javaCallback))
		INScore::setListener (gGlue, &gListener);
}

/*
 * Class:     INScore_INScore
 * Method:    GetBitmap
 * Signature: ([III)I
 */
JNIEXPORT void JNICALL Java_INScore_INScore_GetBitmap
  (JNIEnv * env, jobject, jintArray bitmapArray, jint w, jint h)
{
	jint *dstBitmap = env->GetIntArrayElements(bitmapArray, 0);
	if (dstBitmap == 0) return;

	jint* data = dstBitmap;
	for (int i=0, n=w*h; i<n; i++) *data++ = 0;
	INScore::getScene (gGlue, (unsigned int *)dstBitmap, w, h);
	env->ReleaseIntArrayElements(bitmapArray, dstBitmap, 0);
}

/*
 * Class:     INScore_INScore
 * Method:    Init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_INScore_INScore_Init
  (JNIEnv *, jclass)
{
	gGlue = INScore::init(10, 7000);
}

#ifdef __cplusplus
}
#endif

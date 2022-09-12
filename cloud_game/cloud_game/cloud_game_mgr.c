#include "com_chen_cloud_cloud_game_mgr.h"
/*
* Class:     com_chen_cloud_game_cloud_game_mgr
* Method:    nativeMethod
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_com_chen_cloud_cloud_1game_1mgr_nativeMethod(JNIEnv *env, jobject obj)
{
	jclass cls = (*env)->GetObjectClass(env, obj);
	jmethodID mid = (*env)->GetStaticMethodID(env, cls, "callback", "()V");

	if (mid == NULL)
	{
		printf("not find callback !!!\n");
		return;
	}

	printf("find callback OK\n");
	(*env)->CallStaticVoidMethod(env, cls, mid);

}
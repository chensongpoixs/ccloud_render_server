#include "com_chen_cloud_cloud_game_mgr.h"



#define LOGI printf

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


/*
 * Class:     com_chen_cloud_cloud_game_mgr
 * Method:    Gpuinfo
 * Signature: (Ljava/util/List;)V
 */
JNIEXPORT void JNICALL Java_com_chen_cloud_cloud_1game_1mgr_Gpuinfo
(JNIEnv *env, jobject obj, jobject jobj)
{
	//获取ArrayList 对象
	jclass jcs_alist = (*env)->GetObjectClass(env, jobj);
	LOGI("====1=====\n");
	//获取Arraylist的methodid
	jmethodID alist_get = (*env)->GetMethodID(env, jcs_alist, "get", "(I)Ljava/lang/Object;");
	jmethodID alist_size = (*env)->GetMethodID(env, jcs_alist, "size", "()I");
	LOGI("====2=====\n");
	jint len = (*env)->CallIntMethod(env, jobj, alist_size);


	LOGI("======3====%d\n", len);
	for (int i = 0; i < len; i++) {
		//获取StuInfo对象
		jobject stu_obj = (*env)->CallObjectMethod(env, jobj, alist_get, i);
		//获取StuInfo类
		jclass stu_cls = (*env)->GetObjectClass(env, stu_obj);


		jmethodID gpuIndexId = (*env)->GetMethodID(env, stu_cls, "getGpuIndex", "()Ljava/lang/String;");
		jstring gpuIndexStr = (jstring)(*env)->CallObjectMethod(env, stu_obj, gpuIndexId);
		const char * gpu_index = (*env)->GetStringUTFChars(env, gpuIndexStr, 0);
		 
		jmethodID nameId = (*env)->GetMethodID(env, stu_cls, "getName", "()Ljava/lang/String;");
		jstring nameStr = (jstring)(*env)->CallObjectMethod(env, stu_obj, nameId);
		const char * stuName = (*env)->GetStringUTFChars(env, nameStr, 0);

		jmethodID usageRate = (*env)->GetMethodID(env, stu_cls, "getUsageRate", "()I");
		jint Rate = (*env)->CallIntMethod(env, stu_obj, usageRate);
		 

		jmethodID totalMemory = (*env)->GetMethodID(env, stu_cls, "getTotalMemory", "()Ljava/lang/String;");
		jstring totalMemoryStr = (jstring)(*env)->CallObjectMethod(env, stu_obj, totalMemory);
		const char * totalmemory = (*env)->GetStringUTFChars(env, totalMemoryStr, 0);


		jmethodID usedMemory = (*env)->GetMethodID(env, stu_cls, "getUsedMemory", "()Ljava/lang/String;");
		jstring usedMemoryStr = (jstring)(*env)->CallObjectMethod(env, stu_obj, usedMemory);
		const char * usedmemory = (*env)->GetStringUTFChars(env, usedMemoryStr, 0);

		LOGI("====freeMemory=====\n");
		jmethodID freeMemory = (*env)->GetMethodID(env, stu_cls, "getFreeMemory", "()Ljava/lang/String;");
		jstring freeMemoryStr = (jstring)(*env)->CallObjectMethod(env, stu_obj, freeMemory);
		const char * freememory = (*env)->GetStringUTFChars(env, freeMemoryStr, 0);

		LOGI("====VideoEncode=====\n");
		jmethodID VideoEncode = (*env)->GetMethodID(env, stu_cls, "getVideoEncode", "()Ljava/lang/String;");
		jstring VideoEncodeStr = (jstring)(*env)->CallObjectMethod(env, stu_obj, VideoEncode);
		const char * videoencode = (*env)->GetStringUTFChars(env, VideoEncodeStr, 0);
		LOGI("====VideoDecode=====\n");
		jmethodID VideoDecode = (*env)->GetMethodID(env, stu_cls, "getVideoDecode", "()Ljava/lang/String;");
		jstring VideoDecodeStr = (jstring)(*env)->CallObjectMethod(env, stu_obj, VideoDecode);
		const char * videodecode = (*env)->GetStringUTFChars(env, VideoDecodeStr, 0);

		LOGI("[i = %u][gpu_index = %s][name = %s][Rate = %u][totalmemory = %s][usedmemory = %s][freememory = %s][video_encode = %s][video_decode = %s]\n", i , gpu_index, stuName, Rate, totalmemory, usedmemory, freememory, videoencode, videodecode);
	}
	 
}
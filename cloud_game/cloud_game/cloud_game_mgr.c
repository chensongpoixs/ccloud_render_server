#include "com_chen_cloud_cloud_game_mgr.h"

//#include <thread>

#define LOGI printf


static JavaVM *g_jvm = NULL;
static JNIEnv *g_env = NULL;
/*
 * 加载动态库
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) 
{
	//设置日志
	g_jvm = vm; 
	LOGI("[%s][%d]\n", __FUNCTION__, __LINE__);

	int status = (*g_jvm)->GetEnv(g_jvm, (void **)&g_env, JNI_VERSION_1_6);
	if (status != JNI_OK) 
	{
		/*if (s_jvm->AttachCurrentThread(&env, NULL) != JNI_OK)
		{
			return;
		}*/
		LOGI("not find GetEnv （status = %u） !!!\n", status);
		return -1;
	}
	LOGI("  find GetEnv !!!\n");
	//jclass cls = (*g_env)->GetObjectClass(g_env, obj);
	//jmethodID mid = (*g_env)->GetStaticMethodID(env, cls, "callback", "()V");
	 
		/*jclass cls = (*g_env)->FindClass((g_env), "com/chen/cloud/cloud_game_mgr");
		LOGI("  find cloud_game_mgr !!!\n");
		jmethodID mid = (*g_env)->GetStaticMethodID((g_env), cls, "cppgpuinfo", "()V");
		if (mid == NULL)
		{
			LOGI("not find gpu_info !!!\n");
			return;
		}

		LOGI("find gpu_info OK\n");
		(*g_env)->CallStaticVoidMethod(g_env, cls, mid);*/
	 

	//jmethodID mid = env->GetStaticMethodID(cls, "test", "(I)V"); 
	//env->CallStaticVoidMethod(cls, mid, 100); 39 /*We are done.*/

	//	 jvm->DestroyJavaVM(); 
	//cout << "end of create vm \n"; 42 return 0; 43
	//}
 

	//printf("find callback OK\n");
	//(*env)->CallStaticVoidMethod(env, cls, mid);

	

	//fun(env);
	//if (status != JNI_OK) {
	//	//Detach线程
	//	s_jvm->DetachCurrentThread();
	//}

	return JNI_VERSION_1_6;
}
/*
 * 卸载动态库
 */
JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) 
{
	LOGI("[%s][%d]\n", __FUNCTION__, __LINE__);
//	g_jvm = NULL;
}






/*
* Class:     com_chen_cloud_game_cloud_game_mgr
* Method:    nativeMethod
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_com_chen_cloud_cloud_1game_1mgr_nativeMethod(JNIEnv *env, jclass cls)
{
	//jclass cls = (*env)->GetObjectClass(env, obj);
	jmethodID mid = (*env)->GetStaticMethodID(env, cls, "callback", "()V");

	if (mid == NULL)
	{
		printf("not find callback !!!\n");
		return;
	}

	printf("find callback OK\n");
	(*env)->CallStaticVoidMethod(env, cls, mid);



	jclass cloud_game_cls = (*g_env)->FindClass((g_env), "com/chen/cloud/cloud_game_mgr");
	LOGI("  find cloud_game_mgr !!!\n");
	jmethodID cloud_game_mid = (*g_env)->GetStaticMethodID((g_env), cloud_game_cls, "cppgpuinfo", "()V");
	if (cloud_game_mid == NULL)
	{
		LOGI("not find gpu_info !!!\n");
		return;
	}

	LOGI("find gpu_info OK\n");
	(*g_env)->CallStaticVoidMethod(g_env, cloud_game_cls, cloud_game_mid);

}


/*
 * Class:     com_chen_cloud_cloud_game_mgr
 * Method:    Gpuinfo
 * Signature: (Ljava/util/List;)V
 */
JNIEXPORT void JNICALL Java_com_chen_cloud_cloud_1game_1mgr_Gpuinfo
(JNIEnv *env, jclass cls, jobject jobj)
{
	LOGI("[%s][%d]\n", __FUNCTION__, __LINE__);
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
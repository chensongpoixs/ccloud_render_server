#include "com_chen_cloud_cloud_game_mgr.h"

//#include <thread>
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOGI printf
//#include <Windows.h>
#include <signal.h>
static FILE * fp = NULL;
static int stoped = 0;
void Stop(int i)
{
	if (fp)
	{
		fprintf(fp, "%s\n", __FUNCTION__);
		fflush(fp);
	}
	stoped = 1;
	LOGI("STOP !!!\n");
	//chen::g_cgateway.stop();
}

void RegisterSignal()
{
	signal(SIGINT, Stop);
	signal(SIGTERM, Stop);

}
//
//static JavaVM *g_jvm = NULL;
//static JNIEnv *g_env = NULL;
///*
// * 加载动态库
// */
//JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) 
//{
//	//设置日志
//	g_jvm = vm; 
//	LOGI("[%s][%d]\n", __FUNCTION__, __LINE__);
//
//	int status = (*g_jvm)->GetEnv(g_jvm, (void **)&g_env, JNI_VERSION_1_6);
//	if (status != JNI_OK) 
//	{
//		/*if (s_jvm->AttachCurrentThread(&env, NULL) != JNI_OK)
//		{
//			return;
//		}*/
//		LOGI("not find GetEnv （status = %u） !!!\n", status);
//		return -1;
//	}
//	LOGI("  find GetEnv !!!\n");
//	//jclass cls = (*g_env)->GetObjectClass(g_env, obj);
//	//jmethodID mid = (*g_env)->GetStaticMethodID(env, cls, "callback", "()V");
//	 
//		/*jclass cls = (*g_env)->FindClass((g_env), "com/chen/cloud/cloud_game_mgr");
//		LOGI("  find cloud_game_mgr !!!\n");
//		jmethodID mid = (*g_env)->GetStaticMethodID((g_env), cls, "cppgpuinfo", "()V");
//		if (mid == NULL)
//		{
//			LOGI("not find gpu_info !!!\n");
//			return;
//		}
//
//		LOGI("find gpu_info OK\n");
//		(*g_env)->CallStaticVoidMethod(g_env, cls, mid);*/
//	 
//
//	//jmethodID mid = env->GetStaticMethodID(cls, "test", "(I)V"); 
//	//env->CallStaticVoidMethod(cls, mid, 100); 39 /*We are done.*/
//
//	//	 jvm->DestroyJavaVM(); 
//	//cout << "end of create vm \n"; 42 return 0; 43
//	//}
// 
//
//	//printf("find callback OK\n");
//	//(*env)->CallStaticVoidMethod(env, cls, mid);
//
//	
//
//	//fun(env);
//	//if (status != JNI_OK) {
//	//	//Detach线程
//	//	s_jvm->DetachCurrentThread();
//	//}
//
//	return JNI_VERSION_1_6;
//}
/*
 * 卸载动态库
 */
//JNIEXPORT void JNICALL JNI_OnUnload(JavaVM* vm, void* reserved) 
//{
//	LOGI("[%s][%d]\n", __FUNCTION__, __LINE__);
////	g_jvm = NULL;
//}






/*
* Class:     com_chen_cloud_game_cloud_game_mgr
* Method:    nativeMethod
* Signature: ()V
*/
//JNIEXPORT void JNICALL Java_com_chen_cloud_cloud_1game_1mgr_nativeMethod(JNIEnv *env, jclass cls)
JNIEXPORT jboolean JNICALL Java_com_company_Main_CloudRenderLoop
(JNIEnv *evc, jclass cls)
{
	RegisterSignal();
	fp = fopen("./chensong.log", "wb+");
	if (fp)
	{
		fprintf(fp, "%s  loop run \n", __FUNCTION__);
		fflush(fp);
	}
	stoped = 0;
	LOGI("cpp exit !!!\n");
	while (stoped == 0)
	{
		Sleep(10);
		LOGI("sleep !!!\n");
	}
	LOGI("cpp exit !!!\n");
	if (fp)
	{
		fprintf(fp, "%s  loop exit \n", __FUNCTION__);
		fflush(fp);
	}
}

 
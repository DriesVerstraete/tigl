#ANDROID APPLICATION MAKEFILE
APP_BUILD_SCRIPT := $(call my-dir)/Android.mk
#APP_PROJECT_PATH := $(call my-dir)

APP_OPTIM := release

APP_PLATFORM    := android-11
APP_STL         := gnustl_shared
APP_CPPFLAGS    := -fexceptions -frtti
APP_ABI         := x86 armeabi armeabi-v7a
APP_MODULES     := TIGL_static tiglviewer-native

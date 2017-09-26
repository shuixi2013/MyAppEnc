LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := shell
LOCAL_SRC_FILES :=  main.c \
					linker.c



include $(BUILD_SHARED_LIBRARY)

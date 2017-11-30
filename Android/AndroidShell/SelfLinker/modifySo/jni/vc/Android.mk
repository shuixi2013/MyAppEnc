LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := shell
LOCAL_SRC_FILES :=  main.c \
					linker.c

#LOCAL_SHARED_LIBRARIES := -llog
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)

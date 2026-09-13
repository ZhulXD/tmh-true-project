LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libdobby
LOCAL_SRC_FILES := Tools/Dobby/libraries/$(TARGET_ARCH_ABI)/libdobby.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/dobby/
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := libcurl
LOCAL_SRC_FILES         := Tools/Login/library/curl-android-$(TARGET_ARCH_ABI)/lib/libcurl.a

include $(PREBUILT_STATIC_LIBRARY)
# ============================================================================#

include $(CLEAR_VARS)
LOCAL_MODULE            := libssl
LOCAL_SRC_FILES         := Tools/Login/library/openssl-android-$(TARGET_ARCH_ABI)/lib/libssl.a

include $(PREBUILT_STATIC_LIBRARY)
# ============================================================================#

include $(CLEAR_VARS)
LOCAL_MODULE            := libcrypto
LOCAL_SRC_FILES         := Tools/Login/library/openssl-android-$(TARGET_ARCH_ABI)/lib/libcrypto.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libAkSoundEngine2
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/imgui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Tools/Login
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Tools/Login/library/curl-android-$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Tools/Login/library/openssl-android-$(TARGET_ARCH_ABI)/include

LOCAL_ARM_MODE := arm
LOCAL_CFLAGS += -w -s -Wno-error=format-security -fvisibility=hidden -fpermissive -fexceptions
LOCAL_CPPFLAGS += -w -s -Wno-error=format-security -fvisibility=hidden -Werror -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fpermissive -Wall -fexceptions -Werror
LOCAL_LDFLAGS += -Wl,-s -Wl,--gc-sections,--strip-all,-llog
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lGLESv3 -ldl -lz

LOCAL_SRC_FILES := imgui/imgui.cpp    \
    imgui/imgui_draw.cpp\
    imgui/imgui_tables.cpp \
    imgui/imgui_widgets.cpp \
    imgui/backends/imgui_impl_android.cpp \
    imgui/backends/imgui_impl_opengl3.cpp \
    imgui/stb_image.cpp \
    imgui/android_native_app_glue.c \
    Tools/xDL/xdl.c \
    Tools/xDL/xdl_iterate.c \
    Tools/xDL/xdl_linker.c \
    Tools/xDL/xdl_lzma.c \
    Tools/xDL/xdl_util.c \
    Tools/fake_dlfcn.cpp \
    Tools/Il2Cpp.cpp \
    Tools/Tools.cpp \
    Tools/Login/Tools.cpp \
    XYZ/AutoUIConfig.cpp \
    KittyMemory/KittyMemory.cpp \
    KittyMemory/MemoryPatch.cpp \
    KittyMemory/MemoryBackup.cpp \
    KittyMemory/KittyUtils.cpp \
    Substrate/hde64.c \
    Substrate/SubstrateDebug.cpp \
    Substrate/SubstrateHook.cpp \
    Substrate/SubstratePosixMemory.cpp \
    Substrate/SymbolFinder.cpp \
	Substrate/And64InlineHook/And64InlineHook.cpp \
    xHook/xhook.c \
    xHook/xh_core.c \
    xHook/xh_elf.c \
    xHook/xh_jni.c \
    xHook/xh_log.c \
    xHook/xh_util.c \
    xHook/xh_version.c \
    Main.cpp
                     
LOCAL_STATIC_LIBRARIES  := libcurl libssl libcrypto libdobby

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
LOCAL_SRC_FILES += Tools/compat_atomic.s
endif

include $(BUILD_SHARED_LIBRARY)


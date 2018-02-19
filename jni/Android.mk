LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := sfml-example

LOCAL_SRC_FILES := main.cpp
LOCAL_SRC_FILES += Grid.hpp
LOCAL_SRC_FILES += Grid.cpp
LOCAL_SRC_FILES += Snake.hpp
LOCAL_SRC_FILES += Snake.cpp
LOCAL_SRC_FILES += WindowGroup.hpp
LOCAL_SRC_FILES += StartScreen.hpp
LOCAL_SRC_FILES += StartScreen.cpp
LOCAL_SRC_FILES += Util.hpp
LOCAL_SRC_FILES += Util.cpp
LOCAL_SRC_FILES += Button.hpp
LOCAL_SRC_FILES += Button.cpp


LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)

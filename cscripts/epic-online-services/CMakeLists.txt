include_directories(${PROJECT_SOURCE_DIR}/epic-online-services/SDK/Include SYSTEM GLAD)

set(EOS_SDK_BIN_DIR SDK/Bin)

if(LINUX)
set(EOS_SDK_LIBRARIES "${EOS_SDK_BIN_DIR}/libEOSSDK-Linux-Shipping.so") #linux
endif()

if (APPLE)
    set(EOS_SDK_LIBRARIES "${EOS_SDK_BIN_DIR}/libEOSSDK-Mac-Shipping.dylib") #mac
endif()

if (MSVC)
    set(EOS_SDK_LIBRARIES "${EOS_SDK_BIN_DIR}/libEOSSDK-Win64-Shipping.dll") #win
endif()
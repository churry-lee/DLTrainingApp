if(MSVC)
    set(CUDA_TOOLKIT_ROOT_DIR C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.6)
#    set(OPENCV_INSTALL_PATH D:/local_lib/opencv-454-win/lib)

    set(LIBTORCH_INSTALL_PATH D:/local_lib/libtorch-win-debug)
    set(QT_INSTALL_PATH D:/local_lib/qt-v6.4.2/6.4.2/msvc2019_64/lib/cmake)
    set(CMAKE_PREFIX_PATH ${OPENCV_INSTALL_PATH} ${LIBTORCH_INSTALL_PATH} ${QT_INSTALL_PATH})

    set(SPD_INCLUDE_DIRS D:/local_lib/spdlog/include)
    set(SPD_LIBRARY_DIRS D:/local_lib/spdlog/lib)
    set(SPD_LIBRARIES spdlogd)
elseif(${APPLE})
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SPDLOG REQUIRED IMPORTED_TARGET spdlog)
    pkg_check_modules(FMT REQUIRED IMPORTED_TARGET FMT)

    set(OPENCV_INSTALL_PATH /Users/iChurry/LocalLib/opencv-v4.7.0-debug/lib/cmake/opencv4)
    set(LIBTORCH_INSTALL_PATH /Users/ichurry/LocalLib/libtorch-v1.13.1-debug)
    set(CMAKE_PREFIX_PATH ${OPENCV_INSTALL_PATH} ${LIBTORCH_INSTALL_PATH})
endif(MSVC)

find_package(OpenCV REQUIRED)
set(OPENCV_LIBRARY opencv_core opencv_highgui opencv_imgproc opencv_video opencv_videoio opencv_dnn)

find_package(Torch REQUIRED)


set(LOCAL_INCLUDE_DIRS /usr/local/include)
set(LOCAL_LIBRARY_DIRS /usr/local/lib)

# Dependency 관련 변수 설정
set(DEP_INCLUDE_DIRS
        ${LOCAL_INCLUDE_DIRS}
        ${SPD_INCLUDE_DIRS} ${FMT_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        )
set(DEP_LIBRARY_DIRS
        ${LOCAL_LIBRARY_DIRS}
        ${SPD_LIBRARY_DIRS} ${FMT_LIBRARY_DIRS}
        ${OpenCV_LIBRARY_DIRS}
        )
set(DEP_LIBRARIES
        ${SPD_LIBRARIES} ${FMT_LIBRARIES}
        ${OpenCV_LDFLAGS} ${OpenCV_LIBRARIES}
        ${TORCH_LIBRARIES}
        )

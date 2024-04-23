cmake_minimum_required(VERSION 3.5.1)
project(openauto CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(base_directory ${CMAKE_CURRENT_SOURCE_DIR})
set(resources_directory ${base_directory}/assets)
set(sources_directory ${base_directory}/src)
set(include_directory ${base_directory}/include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${base_directory}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${base_directory}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${base_directory}/bin)
set(EXECUTABLE_OUTPUT_PATH ${base_directory}/bin)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
SET(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -Wall -pedantic -fPIC -fpermissive -g")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3")

SET(QT_USE_QTMULTIMEDIA TRUE)
SET(QT_USE_QTMULTIMEDIAWIDGETS TRUE)
SET(QT_DEBUG_PLUGINS TRUE)
SET(QML_IMPORT_TRACE TRUE)


set(AASDK_INCLUDE_DIRS "/home/rui/environments/rpi4/aasdk/include")
set(AASDK_PROTO_INCLUDE_DIRS "/home/rui/environments/rpi4/aasdk/build")
set(AASDK_LIBRARIES "/home/rui/environments/rpi4/aasdk/lib/libaasdk.a")
set(AASDK_PROTO_LIBRARIES "/home/rui/environments/rpi4/aasdk/lib/libaasdk_proto.a")

add_definitions(-DBOOST_ALL_DYN_LINK)

find_package(Boost REQUIRED COMPONENTS system log OPTIONAL_COMPONENTS unit_test_framework)
find_package(PkgConfig REQUIRED)
pkg_check_modules(libusb REQUIRED IMPORTED_TARGET libusb-1.0)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Multimedia MultimediaWidgets Quick X11Extras OpenGL OpenGLExtensions)
find_package(Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt5Bluetooth CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
find_package(RtAudio REQUIRED)

set(common_include_directory ${include_directory}/f1x/openauto/Common)
set(autoapp_sources_directory ${sources_directory}/autoapp)
set(autoapp_include_directory ${include_directory}/f1x/openauto/autoapp)
file(GLOB_RECURSE autoapp_source_files ${autoapp_sources_directory}/*.ui ${autoapp_sources_directory}/*.cpp ${autoapp_include_directory}/*.hpp ${common_include_directory}/*.hpp ${resources_directory}/*.qrc)

add_executable(autoapp ${autoapp_source_files})

add_library(aasdk_proto STATIC IMPORTED GLOBAL)
set_target_properties(aasdk_proto PROPERTIES IMPORTED_LOCATION ${AASDK_PROTO_LIBRARIES})

add_library(aasdk STATIC IMPORTED GLOBAL)
set_target_properties(aasdk PROPERTIES IMPORTED_LOCATION ${AASDK_LIBRARIES})

target_include_directories(autoapp PRIVATE 
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Multimedia_INCLUDE_DIRS}
                    ${Qt5MultimediaWidgets_INCLUDE_DIRS}
                    ${Qt5Quick_INCLUDE_DIRS}
                    ${Qt5OpenGL_INCLUDE_DIRS}
                    ${Qt5Bluetooth_INCLUDE_DIRS}
                    ${Boost_INCLUDE_DIRS}
                    ${LIBUSB_1_INCLUDE_DIRS}
                    ${GSTREAMER_INCLUDE_DIRS}
                    ${protobuf_INCLUDE_DIR}
                    ${OPENSSL_INCLUDE_DIR}
                    ${RTAUDIO_INCLUDE_DIRS}
                    ${AASDK_PROTO_INCLUDE_DIRS}
                    ${AASDK_INCLUDE_DIRS}
                    ${include_directory})
								
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

target_link_libraries(autoapp PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets Qt5::Gui Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Bluetooth Qt5::X11Extras Qt5::OpenGL Qt5::OpenGLExtensions)
target_link_libraries(autoapp PRIVATE Qt5::Multimedia)
target_link_libraries(autoapp PRIVATE RtAudio::rtaudio)
target_link_libraries(autoapp PRIVATE OpenSSL::SSL)
target_link_libraries(autoapp PRIVATE OpenSSL::Crypto)
target_link_libraries(autoapp PRIVATE PkgConfig::libusb)
target_link_libraries(autoapp PRIVATE ${GSTREAMER_LIBRARY_DIRS})
target_link_libraries(autoapp PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(autoapp PRIVATE Boost::boost Boost::system Boost::log)
target_link_libraries(autoapp PUBLIC aasdk aasdk_proto)


#target_link_libraries(autoapp PRIVATE
#                        ${AASDK_PROTO_LIBRARIES}
#                        ${AASDK_LIBRARIES})



# 8-bits-of-image-processing

cmake_minimum_required ( VERSION 3.23 )
project( 8-Bits-Image-Processing )

if (MSVC)
	
	set( SOURCES main.cpp )

	add_executable( 8-Bits-Image-Processing ${SOURCES} )
	
	set( OPENCV_DIR "C:/opencv" )
	set( OPENCV_INCLUDE_DIR ${OPENCV_DIR}/build/include )
	set( OPENCV_LIBS ${OPENCV_DIR}/build/x64/vc16/lib/opencv_world490.lib )	
	
	target_include_directories( 8-Bits-Image-Processing PUBLIC ${OPENCV_INCLUDE_DIR} )
								 
	target_link_libraries( 8-Bits-Image-Processing PUBLIC ${OPENCV_LIBS} )
								 
endif()						 

cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (SRCDIR  	${ROOT}/src)
set (GUIDOLIB 	${ROOT}/modules/guidolib)
set (GUIDOQT 	${GUIDOLIB}/environments/Qt)

set (CMAKE_AUTOMOC ON)

#######################################
# Qt settings
set (QTMODULES Core Gui Widgets Svg PrintSupport Multimedia MultimediaWidgets WebSockets Sensors Qml OpenGL)
find_package(Qt5 COMPONENTS ${QTMODULES} REQUIRED)
set (QT_INCLUDE_DIRS  ${Qt5Core_INCLUDE_DIRS}  
				${Qt5Gui_INCLUDE_DIRS} ${Qt5Widget_INCLUDE_DIRS} ${Qt5Svg_INCLUDE_DIRS} 
				${Qt5PrintSupport_INCLUDE_DIRS} ${Qt5Multimedia_INCLUDE_DIRS} ${Qt5MultimediaWidgets_INCLUDE_DIRS}
				${Qt5WebSockets_INCLUDE_DIRS} ${Qt5Sensors_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS})
foreach (QTLIB ${QTMODULES})
	set (QT_LIBRARIES ${QT_LIBRARIES} Qt5::${QTLIB})
endforeach(QTLIB)

set (QTVIEW_DEFINITIONS -DQTVIEW  -DQTJSENGINE)

file (GLOB QTVIEW_SRC  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${SRCDIR}/Qt/*.cpp" 
	"${SRCDIR}/Qt/*/*.cpp"
	"${SRCDIR}/view/QtView/*.cpp" 
	"${GUIDOQT}/libs/GuidoQt/*.cpp" 
)

file (GLOB QTVIEW_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${SRCDIR}/Qt/*.h" 
	"${SRCDIR}/Qt/*/*.h"
	"${SRCDIR}/view/QtView/*.h" 
	"${GUIDOQT}/libs/GuidoQt/include/*.h" 
)

#######################################
# set includes
set (QTVIEW_INCLUDE_DIRS ${QTVIEW_INCLUDE_DIRS} 
	"${SRCDIR}/Qt" 
	"${SRCDIR}/Qt/sensors" 	
	"${SRCDIR}/view/QtView" 
	"${GUIDOQT}/libs/GuidoQt/include"
) 

message (STATUS "Includes Qt View and Qt version ${Qt5Core_VERSION}")
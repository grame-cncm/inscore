
cmake_minimum_required(VERSION 3.6.0 FATAL_ERROR)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (SRCDIR  	${ROOT}/src)
set (INSCOREDIR ${SRCDIR}/inscore)
set (GUIDOLIB 	${ROOT}/modules/guidolib)
set (GUIDOQT 	${GUIDOLIB}/environments/Qt)
set (IBUNDLE 	${SRCDIR}/QArchive)

set (CMAKE_AUTOMOC ON)

#######################################
# Qt settings
if (QT6)
	set (QTVERS Qt6)
else()
	set (QTVERS Qt5)
endif()
# Core must be the first module, don't move it, it's used at packaging level to fix incorrect qr deployement
set (QTMODULES Core Gui Widgets Svg PrintSupport Multimedia MultimediaWidgets WebSockets Sensors Qml OpenGL)
if (IOS)
	set (QTMODULES ${QTMODULES} Quick QuickWidgets)
else()
	set (QTMODULES ${QTMODULES} OpenGL)
endif()
find_package(${QTVERS} COMPONENTS ${QTMODULES} REQUIRED)

if (QT6)
set (QT_INCLUDE_DIRS  ${Qt6Core_INCLUDE_DIRS}  
				${Qt6Gui_INCLUDE_DIRS} ${Qt6Widget_INCLUDE_DIRS} ${Qt6Svg_INCLUDE_DIRS} 
				${Qt6PrintSupport_INCLUDE_DIRS} ${Qt6Multimedia_INCLUDE_DIRS} 
				${Qt6MultimediaWidgets_INCLUDE_DIRS} ${Qt6WebSockets_INCLUDE_DIRS} 
				${Qt6Sensors_INCLUDE_DIRS} ${Qt6Qml_INCLUDE_DIRS})
if (IOS)
	set (QT_INCLUDE_DIRS ${QT_INCLUDE_DIRS} ${Qt6Quick_INCLUDE_DIRS} ${Qt6QuickWidgets_INCLUDE_DIRS})
else()
	set (QT_INCLUDE_DIRS ${QT_INCLUDE_DIRS} ${Qt6OpenGL_INCLUDE_DIRS})
endif()

else(QT6)
set (QT_INCLUDE_DIRS  ${Qt5Core_INCLUDE_DIRS}  
				${Qt5Gui_INCLUDE_DIRS} ${Qt5Widget_INCLUDE_DIRS} ${Qt5Svg_INCLUDE_DIRS} 
				${Qt5PrintSupport_INCLUDE_DIRS} ${Qt5Multimedia_INCLUDE_DIRS} 
				${Qt5MultimediaWidgets_INCLUDE_DIRS} ${Qt5WebSockets_INCLUDE_DIRS} 
				${Qt5Sensors_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS})
if (IOS)
	set (QT_INCLUDE_DIRS ${QT_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS} ${Qt5QuickWidgets_INCLUDE_DIRS})
else()
	set (QT_INCLUDE_DIRS ${QT_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS})
endif()
endif()

foreach (QTLIB ${QTMODULES})
	set (QT_LIBRARIES ${QT_LIBRARIES} ${QTVERS}::${QTLIB})
endforeach(QTLIB)
set (QTVIEW_DEFINITIONS -DQTVIEW  -DQTJSENGINE)


file (GLOB QTVIEW_SRC  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${SRCDIR}/Qt/*.cpp" 
	"${SRCDIR}/Qt/*/*.cpp"
	"${SRCDIR}/view/QtView/*.cpp" 
	"${GUIDOQT}/libs/GuidoQt/*.cpp" 

	"${INSCOREDIR}/httpserver/*.cpp" 
	"${INSCOREDIR}/osc/*.cpp" 
	"${INSCOREDIR}/signal/faust/*.cpp" 
	"${INSCOREDIR}/plugins/*/*.cpp" 
	"${INSCOREDIR}/servers/*.cpp" 
	"${INSCOREDIR}/web/*.cpp" 
	"${IBUNDLE}/*.cpp"
)

file (GLOB QTVIEW_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	"${SRCDIR}/Qt/*.h" 
	"${SRCDIR}/Qt/*/*.h"
	"${SRCDIR}/view/QtView/*.h" 
	"${GUIDOQT}/libs/GuidoQt/include/*.h" 

	"${INSCOREDIR}/httpserver/*.h" 
	"${INSCOREDIR}/osc/*.h" 
	"${INSCOREDIR}/plugins/*/*.h" 
	"${INSCOREDIR}/signal/faust/*.h" 
	"${INSCOREDIR}/servers/*.h" 
	"${INSCOREDIR}/web/*.h" 
	"${IBUNDLE}/*.h"
)

#######################################
# set includes
set (QTVIEW_INCLUDE_DIRS ${QTVIEW_INCLUDE_DIRS} 
	"${SRCDIR}/Qt" 
	"${SRCDIR}/Qt/sensors" 	
	"${SRCDIR}/view/QtView" 
	"${GUIDOQT}/libs/GuidoQt/include"

	"${INSCOREDIR}/httpserver" 
	"${INSCOREDIR}/osc" 
	"${INSCOREDIR}/plugins/faustDSP" 
	"${INSCOREDIR}/plugins/gesturefollower" 
	"${INSCOREDIR}/signal/faust" 
	"${INSCOREDIR}/servers" 
	"${INSCOREDIR}/web" 
	"${IBUNDLE}"
) 

message (STATUS "Includes Qt View and Qt version ${Qt5Core_VERSION}")


cmake_minimum_required(VERSION 3.6.0 FATAL_ERROR)

get_filename_component(ROOT ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (SRCDIR  	 ${ROOT}/src)
set (INSCOREDIR  ${SRCDIR}/inscore)
set (INSCORE2DIR ${SRCDIR}/inscore2)
set (MAPDIR      ${SRCDIR}/libmapping)
set (QARCHIVE 	 ${SRCDIR}/QArchive)
set (IBUNDLEDIR  ${ROOT}/tools/IBundle)

#######################################
# Qt settings
find_package(Qt5 COMPONENTS Core REQUIRED)
set (IBUNDLE_LIBRARIES Qt5::Core)

file (GLOB IBUNDLE_SRC 		RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	${IBUNDLEDIR}/src/*.cpp 
	${IBUNDLEDIR}/src/Parsing/*.cpp
	${QARCHIVE}/*.cpp

	${INSCOREDIR}/lib/TWallClock.cpp
	${INSCOREDIR}/controller/IMessage.cpp
	${INSCOREDIR}/scripting/TScripting.cpp 
	${INSCOREDIR}/scripting/TMaths.cpp 
	${INSCOREDIR}/lib/Tools.cpp
	${INSCOREDIR}/ITLParser/*.cpp 
	${INSCOREDIR}/expression/parser/*.cpp
	${INSCOREDIR}/expression/IExpression.cpp
	${INSCOREDIR}/expression/ExprFactory.cpp
	${INSCOREDIR}/expression/ExprInfo.cpp

	${INSCORE2DIR}/sorter/TSorter.cpp
	${INSCORE2DIR}/sorter/TScheduler.cpp

	${MAPDIR}/src/misc/rational.cpp 

)

file (GLOB IBUNDLE_HEADERS 	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
	${IBUNDLEDIR}/src/*.h 
	${IBUNDLEDIR}/src/Parsing/*.h
	${QARCHIVE}/*.h

	${INSCOREDIR}/controller/IMessage.h 
	${INSCOREDIR}/ITLParser/*.h
	${INSCOREDIR}/scripting/TScripting.h
	${INSCOREDIR}/scripting/TMaths.h
	${INSCOREDIR}/signal/TSignal.h
	${INSCOREDIR}/lib/Tools.h
	${INSCOREDIR}/expression/*.h 
	${INSCOREDIR}/expression/parser/*.h 
	${MAPDIR}/src/misc/rational.h
)

set (IBUNDLE_INCLUDE_DIRS
	${Qt5Core_INCLUDE_DIRS} 
	${IBUNDLEDIR}/src 
	${IBUNDLEDIR}/src/Parsing 
)

set ( IBUNDLE_DEFS -DIBUNDLE -DPARSERTEST -DNO_OSCSTREAM -DQTFUNCTOR)
if (WIN32)
	set ( IBUNDLE_DEFS ${IBUNDLE_DEFS} -DNOHOSTNAME -DWINDOWS)
elseif (APPLE)
	if (IOS)
		set ( IBUNDLE_DEFS ${IBUNDLE_DEFS} -DIOS)
	else()
		set ( IBUNDLE_DEFS ${IBUNDLE_DEFS} -DMACOS)
	endif()
elseif(UNIX)
		set ( IBUNDLE_DEFS ${IBUNDLE_DEFS} -D__LINUX__)
endif ()

message (STATUS "Includes IBundle")


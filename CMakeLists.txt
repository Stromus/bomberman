cmake_minimum_required(VERSION 3.9)
project(bomberman)

include_directories("./include" "./lib/irrlicht-1.8.4/include" "./lib/SFML/include")

if (WIN32)
	message("WIN32 FOUND")
	link_directories("./lib/irrlicht-1.8.4/lib/Win64-visualStudio")
	link_directories("./lib/SFML/lib/Windows")
endif (WIN32)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "include/*.hpp" "lib/irrlicht-1.8.4/include/*.h")

add_executable(bomberman ${SOURCE_FILES})

if (UNIX)
  message("UNIX FOUND")
  	message("Unzip files...")
	execute_process(
	  COMMAND ${CMAKE_COMMAND} -E tar xf irrlicht.zip
	  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/lib
	  )
	execute_process(
	  COMMAND ${CMAKE_COMMAND} -E tar xf SFML.zip
	  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/lib
	  )
	message("files Unziped")
	install(CODE "message(\"Unzip files...\")
	execute_process(
	  COMMAND ${CMAKE_COMMAND} -E tar xf ressources.zip
	  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	  )")
	find_package(OpenGL REQUIRED)
	find_package(X11 REQUIRED)
	set(LIBS X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL)
	find_library(IRRLICHT_LIB "Irrlicht" "./lib/irrlicht-1.8.4/lib/Linux")
	find_library(SFML_LIB "sfml-audio" "./lib/SFML/lib/Linux")
	target_link_libraries(bomberman ${IRRLICHT_LIB} ${SFML_LIB} ${OPENGL_LIBRARIES} ${X11_LIBRARIES} ${LIBS})
endif (UNIX)

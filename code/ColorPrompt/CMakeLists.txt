cmake_minimum_required(VERSION 3.13)
project(ColorPrompt)

set(TARGET_NAME ColorPrompt)
add_executable(${TARGET_NAME})
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
  add_definitions(-DNA_USE_WINDOWS_COMMON_CONTROLS_6=1)
  
  # multi processor compilation
  target_compile_options(${TARGET_NAME} PRIVATE /MP)
  # unicode. Theoretically, needs _MBCS to be undefined, but cmake does that.
  add_definitions(-D_UNICODE)

  # working directory
  set_property(TARGET ${TARGET_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $(OutDir))

  set(OUTPUT_DIRECTORY $(OutDir))

else()

  set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$CONFIGURATION/)

endif()



# copying resources
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_CURRENT_SOURCE_DIR}/res/ColorPromptChangelog.txt
      \"${OUTPUT_DIRECTORY}ColorPromptChangelog.txt\"
)



# ######### Sources ################

set(resourceFiles
  res/ColorPromptChangelog.txt
  res/ColorPromptStrings_deu.h
  res/ColorPromptStrings_eng.h
  res/ColorPromptStrings_jpn.h
)

set(sourceFiles
  src/ColorPromptApplication.h
  src/ColorPromptApplication.m
  src/CPAboutController.c
  src/CPAboutController.h
  src/CPColorPromptApplication.c
  src/CPColorPromptApplication.h
  src/CPColorsManager.c
  src/CPColorsManager.h
  src/CPDesign.c
  src/CPDesign.h
  src/CPOpenGLHelper.c
  src/CPOpenGLHelper.h
  src/CPPreferences.c
  src/CPPreferences.h
  src/CPTranslations.c
  src/CPTranslations.h
  src/main.c
  src/main.m
  src/mainC.h
)

set(colorControllersDisplaysSourceFiles
  src/ColorControllers/Displays/CPColorWell1D.c
  src/ColorControllers/Displays/CPColorWell1D.h
  src/ColorControllers/Displays/CPColorWell2D.c
  src/ColorControllers/Displays/CPColorWell2D.h
  src/ColorControllers/Displays/CPGammaDisplayController.c
  src/ColorControllers/Displays/CPGammaDisplayController.h
  src/ColorControllers/Displays/CPGrayColorWell.c
  src/ColorControllers/Displays/CPGrayColorWell.h
  src/ColorControllers/Displays/CPSpectralColorWell.c
  src/ColorControllers/Displays/CPSpectralColorWell.h
)

set(colorControllersSourceFiles
  src/ColorControllers/CPColorController.c
  src/ColorControllers/CPColorController.h
  src/ColorControllers/CPGrayColorController.c
  src/ColorControllers/CPGrayColorController.h
  src/ColorControllers/CPHSVHSLColorController.c
  src/ColorControllers/CPHSVHSLColorController.h
  src/ColorControllers/CPLabLchColorController.c
  src/ColorControllers/CPLabLchColorController.h
  src/ColorControllers/CPLuvUVWColorController.c
  src/ColorControllers/CPLuvUVWColorController.h
  src/ColorControllers/CPRGBColorController.c
  src/ColorControllers/CPRGBColorController.h
  src/ColorControllers/CPSpectralColorController.c
  src/ColorControllers/CPSpectralColorController.h
  src/ColorControllers/CPXYZColorController.c
  src/ColorControllers/CPXYZColorController.h
  src/ColorControllers/CPYCbCrColorController.c
  src/ColorControllers/CPYCbCrColorController.h
  src/ColorControllers/CPYuvYupvpColorController.c
  src/ColorControllers/CPYuvYupvpColorController.h
  src/ColorControllers/CPYxyColorController.c
  src/ColorControllers/CPYxyColorController.h
)

set(MachineSourceFiles
  src/Machine/CPMachineButtonsController.c
  src/Machine/CPMachineButtonsController.h
  src/Machine/CPMachineController.c
  src/Machine/CPMachineController.h
  src/Machine/CPMachineGrayController.c
  src/Machine/CPMachineGrayController.h
  src/Machine/CPMachineIlluminationController.c
  src/Machine/CPMachineIlluminationController.h
  src/Machine/CPMachineLabController.c
  src/Machine/CPMachineLabController.h
  src/Machine/CPMachineObserverController.c
  src/Machine/CPMachineObserverController.h
  src/Machine/CPMachineRGBController.c
  src/Machine/CPMachineRGBController.h
  src/Machine/CPMachineWindowController.c
  src/Machine/CPMachineWindowController.h
)

set(MetamericsSourceFiles
  src/Metamerics/CPChromaticityErrorController.c
  src/Metamerics/CPChromaticityErrorController.h
  src/Metamerics/CPColorConversionsYcdUVW.c
  src/Metamerics/CPColorConversionsYcdUVW.h
  src/Metamerics/CPColorRenderingIndexController.c
  src/Metamerics/CPColorRenderingIndexController.h
  src/Metamerics/CPMetamericsController.c
  src/Metamerics/CPMetamericsController.h
  src/Metamerics/CPTotalMetamericIndexController.c
  src/Metamerics/CPTotalMetamericIndexController.h
  src/Metamerics/CPTwoColorController.c
  src/Metamerics/CPTwoColorController.h
  src/Metamerics/CPUVMetamericIndexController.c
  src/Metamerics/CPUVMetamericIndexController.h
  src/Metamerics/CPVisMetamericIndexController.c
  src/Metamerics/CPVisMetamericIndexController.h
  src/Metamerics/CPWhitePoints.c
  src/Metamerics/CPWhitePoints.h
  src/Metamerics/CPWhitePointsController.c
  src/Metamerics/CPWhitePointsController.h
)

set(ThreeDeeSourceFiles
  src/ThreeDee/CPThreeDeeController.c
  src/ThreeDee/CPThreeDeeController.h
  src/ThreeDee/CPThreeDeeCoordinateController.c
  src/ThreeDee/CPThreeDeeCoordinateController.h
  src/ThreeDee/CPThreeDeeOpacityController.c
  src/ThreeDee/CPThreeDeeOpacityController.h
  src/ThreeDee/CPThreeDeeOptionsController.c
  src/ThreeDee/CPThreeDeeOptionsController.h
  src/ThreeDee/CPThreeDeeOptionsController.nal
  src/ThreeDee/CPThreeDeePerspectiveController.c
  src/ThreeDee/CPThreeDeePerspectiveController.h
  src/ThreeDee/CPThreeDeeView.c
  src/ThreeDee/CPThreeDeeView.h
)

source_group("res" FILES ${resourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${resourceFiles})

source_group("src/ColorControllers/Displays" FILES ${colorControllersDisplaysSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${colorControllersDisplaysSourceFiles})

source_group("src/ColorControllers" FILES ${colorControllersSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${colorControllersSourceFiles})

source_group("src/Machine" FILES ${MachineSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${MachineSourceFiles})

source_group("src/Metamerics" FILES ${MetamericsSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${MetamericsSourceFiles})

source_group("src/ThreeDee" FILES ${ThreeDeeSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${ThreeDeeSourceFiles})

source_group("src" FILES ${sourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${sourceFiles})



# ######### Linking to NALib ################

# Define GUI and OpenGL to be in use and hide the CMake GUI options.
add_definitions(-DNA_COMPILE_GUI=1)
add_definitions(-DNA_COMPILE_OPENGL=1)
set(COMPILE_NALIB_GUI 1 CACHE INTERNAL "GUI required")
set(COMPILE_NALIB_OPENGL 1 CACHE INTERNAL "OpenGL required")

set(NALIB_DIR "../../lib/NALib/code/NALib")
target_include_directories(${TARGET_NAME} PRIVATE ${NALIB_DIR}/src)
add_subdirectory(${NALIB_DIR} NALib)
target_link_libraries(${TARGET_NAME} PRIVATE NALib)



# ######### Linking to CML ################

set(CML_DIR "../../lib/CML/code/CML")
target_include_directories(${TARGET_NAME} PRIVATE ${CML_DIR}/src)
add_subdirectory(${CML_DIR} CML)
target_link_libraries(${TARGET_NAME} PRIVATE CML)



# ######### Linking to other libraries ################

find_package(OpenGL REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE ${OPENGL_gl_LIBRARY})

if (MSVC)
  target_link_libraries(${TARGET_NAME} PRIVATE ComCtl32.lib)
else()
  FIND_LIBRARY(CARBON_FRAMEWORK Carbon)
  FIND_LIBRARY(COCOA_FRAMEWORK Cocoa)
  FIND_LIBRARY(UTYPE_FRAMEWORK UniformTypeIdentifiers)
  target_link_libraries(${TARGET_NAME} PRIVATE ${CARBON_FRAMEWORK})
  target_link_libraries(${TARGET_NAME} PRIVATE ${COCOA_FRAMEWORK})
  target_link_libraries(${TARGET_NAME} PRIVATE ${UTYPE_FRAMEWORK})
  
endif()

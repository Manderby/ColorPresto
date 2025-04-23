cmake_minimum_required(VERSION 3.13)
project(ColorPresto)



# ######### define target ################

set(TARGET_NAME ColorPresto)

set(BUNDLE_IDENTIFIER_PREFIX "ch.manderim.")
set(VERSION_STRING 2.1)
set(BUILD_NUMBER_STRING 2.1.2)

if(MSVC)
  add_executable(${TARGET_NAME} WIN32 src/main.c)
elseif(APPLE)
  add_executable(${TARGET_NAME})
endif()



# ######### compiler settings ################

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# ######### Define package settings ################

if(MSVC)
  add_definitions(-DNA_USE_WINDOWS_COMMON_CONTROLS_6=1)
  
  # multi processor compilation
  target_compile_options(${TARGET_NAME} PRIVATE /MP)
  # unicode. Theoretically, needs _MBCS to be undefined, but cmake does that.
  add_definitions(-D_UNICODE)

  # working directory
  set_property(TARGET ${TARGET_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $(OutDir))

  set(OUTPUT_DIRECTORY $(OutDir))

elseif(APPLE)

  set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$CONFIGURATION/${TARGET_NAME}.app/Contents/Resources/)

endif()



# ######### Copying resources ################

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
      ${CMAKE_CURRENT_SOURCE_DIR}/res/ColorPrestoChangelog.txt
      \"${OUTPUT_DIRECTORY}ColorPrestoChangelog.txt\"
)

if(MSVC)
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/res/win/icon.png
        \"${OUTPUT_DIRECTORY}icon.png\"
  )

elseif(APPLE)
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/ColorPresto.icns
        \"${OUTPUT_DIRECTORY}ColorPresto.icns\"
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/de.lproj/InfoPlist.strings
        \"${OUTPUT_DIRECTORY}de.lproj/InfoPlist.strings\"
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/en.lproj/InfoPlist.strings
        \"${OUTPUT_DIRECTORY}en.lproj/InfoPlist.strings\"
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/es.lproj/InfoPlist.strings
        \"${OUTPUT_DIRECTORY}es.lproj/InfoPlist.strings\"
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/fr.lproj/InfoPlist.strings
        \"${OUTPUT_DIRECTORY}fr.lproj/InfoPlist.strings\"
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/jp.lproj/InfoPlist.strings
        \"${OUTPUT_DIRECTORY}jp.lproj/InfoPlist.strings\"
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/zh.lproj/InfoPlist.strings
        \"${OUTPUT_DIRECTORY}zh.lproj/InfoPlist.strings\"
    COMMAND ibtool --compile
        \"${OUTPUT_DIRECTORY}MainMenu.nib\"
        ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/ColorPresto.xib
  )

  set(BUNDLE_IDENTIFIER "${BUNDLE_IDENTIFIER_PREFIX}$(PRODUCT_NAME:rfc1034identifier)")

  set_target_properties(${TARGET_NAME} PROPERTIES
    MACOSX_BUNDLE YES
    MACOSX_BUNDLE_BUNDLE_NAME $(PRODUCT_NAME)
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER ${BUNDLE_IDENTIFIER}
    MACOSX_BUNDLE_GUI_IDENTIFIER ${BUNDLE_IDENTIFIER}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION_STRING}
    MACOSX_BUNDLE_BUNDLE_VERSION ${BUILD_NUMBER_STRING}
    MACOSX_BUNDLE_ICON_FILE "ColorPresto.icns"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
  )
endif()



# ######### Sources ################

set(resourceFiles
  res/ColorPrestoChangelog.txt
  res/ColorPrestoStrings_deu.h
  res/ColorPrestoStrings_eng.h
  res/ColorPrestoStrings_fra.h
  res/ColorPrestoStrings_jpn.h
  res/ColorPrestoStrings_spa.h
  res/ColorPrestoStrings_tlh.h
  res/ColorPrestoStrings_zho.h
)

set(macResourceFiles
  #res/mac/de.lproj/InfoPlist.strings
  #res/mac/en.lproj/InfoPlist.strings
  #res/mac/es.lproj/InfoPlist.strings
  #res/mac/fr.lproj/InfoPlist.strings
  #res/mac/jp.lproj/InfoPlist.strings
  #res/mac/zh.lproj/InfoPlist.strings
  res/mac/ColorPresto.icns
  res/mac/ColorPresto.xib
)

set(winResourceFiles
  res/win/icon.png
)

set(sourceFiles
  src/ColorPrestoApplication.h
  src/ColorPrestoApplication.m
  src/CPColorPrestoApplication.c
  src/CPColorPrestoApplication.h
  src/CPColorsManager.c
  src/CPColorsManager.h
  src/CPDesign.c
  src/CPDesign.h
  src/CPOpenGLHelper.c
  src/CPOpenGLHelper.h
  src/CPTranslations.c
  src/CPTranslations.h
  src/main.c
  src/main.m
  src/mainC.h
)

set(aboutFiles
  src/About/CPAboutController.c
  src/About/CPAboutController.h
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

set(machineSourceFiles
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

set(metamericsSourceFiles
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

set(preferencesSourceFiles
  src/Preferences/CPPreferences.c
  src/Preferences/CPPreferences.h
  src/Preferences/CPPreferencesController.c
  src/Preferences/CPPreferencesController.h
)

set(threeDeeSourceFiles
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



# ######### Group sources in project browser ################

source_group("res" FILES ${resourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${resourceFiles})

source_group("res/mac" FILES ${macResourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${macResourceFiles})

source_group("res/win" FILES ${winResourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${winResourceFiles})

source_group("src/About" FILES ${aboutFiles})
target_sources(${TARGET_NAME} PRIVATE ${aboutFiles})

source_group("src/ColorControllers/Displays" FILES ${colorControllersDisplaysSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${colorControllersDisplaysSourceFiles})

source_group("src/ColorControllers" FILES ${colorControllersSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${colorControllersSourceFiles})

source_group("src/Machine" FILES ${machineSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${machineSourceFiles})

source_group("src/Metamerics" FILES ${metamericsSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${metamericsSourceFiles})

source_group("src/Preferences" FILES ${preferencesSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${preferencesSourceFiles})

source_group("src/ThreeDee" FILES ${threeDeeSourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${threeDeeSourceFiles})

source_group("src" FILES ${sourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${sourceFiles})



# ######### Macro definitions ################

add_definitions(-DCP_VERSION_STRING=\"${VERSION_STRING}\")
add_definitions(-DCP_BUILD_NUMBER_STRING=\"${BUILD_NUMBER_STRING}\")



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

if(MSVC)
  target_link_libraries(${TARGET_NAME} PRIVATE ComCtl32.lib)
else()
  FIND_LIBRARY(CARBON_FRAMEWORK Carbon)
  FIND_LIBRARY(COCOA_FRAMEWORK Cocoa)
  FIND_LIBRARY(UTYPE_FRAMEWORK UniformTypeIdentifiers)
  target_link_libraries(${TARGET_NAME} PRIVATE ${CARBON_FRAMEWORK})
  target_link_libraries(${TARGET_NAME} PRIVATE ${COCOA_FRAMEWORK})
  target_link_libraries(${TARGET_NAME} PRIVATE ${UTYPE_FRAMEWORK})
  
endif()



# this hack removes the xxx-CMakeForceLinker.cxx dummy file
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE C)

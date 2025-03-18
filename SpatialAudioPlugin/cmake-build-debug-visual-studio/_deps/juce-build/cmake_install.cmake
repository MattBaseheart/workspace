# Install script for directory: C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/WolfSoundAudioPluginTemplate")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/cmake-build-debug-visual-studio/_deps/juce-build/modules/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/cmake-build-debug-visual-studio/_deps/juce-build/extras/Build/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-8.0.2" TYPE FILE FILES
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/cmake-build-debug-visual-studio/_deps/juce-build/JUCEConfigVersion.cmake"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/cmake-build-debug-visual-studio/_deps/juce-build/JUCEConfig.cmake"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/JUCECheckAtomic.cmake"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/JUCEHelperTargets.cmake"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/JUCEModuleSupport.cmake"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/JUCEUtils.cmake"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/JuceLV2Defines.h.in"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/LaunchScreen.storyboard"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/PIPAudioProcessor.cpp.in"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/PIPAudioProcessorWithARA.cpp.in"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/PIPComponent.cpp.in"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/PIPConsole.cpp.in"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/RecentFilesMenuTemplate.nib"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/UnityPluginGUIScript.cs.in"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/checkBundleSigning.cmake"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/copyDir.cmake"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/juce_runtime_arch_detection.cpp"
    "C:/Users/mbase/workspace/PluginDev/workspace/SpatialAudioPlugin/libs/juce/extras/Build/CMake/juce_LinuxSubprocessHelper.cpp"
    )
endif()


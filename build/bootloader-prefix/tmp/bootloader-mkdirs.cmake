# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Tanko/esp/v5.2.1/esp-idf/components/bootloader/subproject"
  "C:/Users/Tanko/ESP32/ble_ibeacon/build/bootloader"
  "C:/Users/Tanko/ESP32/ble_ibeacon/build/bootloader-prefix"
  "C:/Users/Tanko/ESP32/ble_ibeacon/build/bootloader-prefix/tmp"
  "C:/Users/Tanko/ESP32/ble_ibeacon/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/Tanko/ESP32/ble_ibeacon/build/bootloader-prefix/src"
  "C:/Users/Tanko/ESP32/ble_ibeacon/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Tanko/ESP32/ble_ibeacon/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Tanko/ESP32/ble_ibeacon/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()

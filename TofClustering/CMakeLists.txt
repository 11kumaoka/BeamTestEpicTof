cmake_minimum_required(VERSION 3.16)
project(TofCluPlugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(EICrecon REQUIRED)
find_package(JANA REQUIRED)

add_library(
  TofCluPlugin SHARED TofCluPlugin.cc
)

set_target_properties(TofCluPlugin PROPERTIES PREFIX "")

get_filename_component(EICRECON_BASE "${EICrecon_DIR}/../../" ABSOLUTE)

target_include_directories(TofCluPlugin PRIVATE 
    "${EICRECON_BASE}/include"
    "${EICRECON_BASE}/include/EICrecon" 
    ${EICrecon_INCLUDE_DIRS}
    ${JANA_INCLUDE_DIRS}
)

target_compile_definitions(TofCluPlugin PRIVATE USE_MODERN_PODIO_GLUE=1)

if(TARGET EICrecon::EICrecon)
    target_link_libraries(TofCluPlugin PRIVATE EICrecon::EICrecon)
else()
    target_link_libraries(TofCluPlugin PRIVATE ${EICrecon_LIBRARIES})
endif()

if(TARGET JANA::JANA)
    target_link_libraries(TofCluPlugin PRIVATE JANA::JANA)
else()
    target_link_libraries(TofCluPlugin PRIVATE ${JANA_LIBRARIES})
endif()

if(DEFINED ENV{EICrecon_MY})
  set(PLUGIN_INSTALL_DIR "$ENV{EICrecon_MY}/plugins")
else()
  set(PLUGIN_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/plugins")
endif()
install(TARGETS TofCluPlugin LIBRARY DESTINATION "${PLUGIN_INSTALL_DIR}")




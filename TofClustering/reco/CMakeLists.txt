find_package(EICrecon REQUIRED)
find_package(JANA REQUIRED)
find_package(DD4hep REQUIRED)

add_library(LGADBeamTestPlugin SHARED
  TofCluPlugin.cc
  LGADHitCalibration_beamTest.cc
  LGADHitClustering_beamTest.cc
  LGADTrack_beamTest.cc
)

set_target_properties(LGADBeamTestPlugin PROPERTIES PREFIX "")

get_filename_component(EICRECON_BASE "${EICrecon_DIR}/../../" ABSOLUTE)

target_include_directories(LGADBeamTestPlugin PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  "${EICRECON_BASE}/include"
  "${EICRECON_BASE}/include/EICrecon"
  ${EICrecon_INCLUDE_DIRS}
  ${JANA_INCLUDE_DIRS}
)

target_compile_definitions(LGADBeamTestPlugin PRIVATE USE_MODERN_PODIO_GLUE=1)

if(TARGET EICrecon::EICrecon)
  target_link_libraries(LGADBeamTestPlugin PRIVATE EICrecon::EICrecon)
else()
  target_link_libraries(LGADBeamTestPlugin PRIVATE ${EICrecon_LIBRARIES})
endif()

if(TARGET JANA::JANA)
  target_link_libraries(LGADBeamTestPlugin PRIVATE JANA::JANA)
else()
  target_link_libraries(LGADBeamTestPlugin PRIVATE ${JANA_LIBRARIES})
endif()

target_link_libraries(LGADBeamTestPlugin PRIVATE DD4hep::DDCore)

install(TARGETS LGADBeamTestPlugin
  LIBRARY DESTINATION lib
)



find_package(DD4hep REQUIRED)

set(PackageName testBeamACLGAD)

add_dd4hep_plugin(${PackageName} SHARED
  testBeamACLGAD_geo.cpp
)

target_link_libraries(${PackageName} PUBLIC DD4hep::DDCore)

if(TARGET DD4hep::DDDetectors)
  target_link_libraries(${PackageName} PUBLIC DD4hep::DDDetectors)
endif()

dd4hep_instantiate_package(${PackageName})

install(FILES
  btTOF.xml
  testBeamACLGAD.xml
  DESTINATION share/geometry
)

install(DIRECTORY
  calibrations
  DESTINATION share/geometry
)


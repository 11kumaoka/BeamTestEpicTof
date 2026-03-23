#include <DD4hep/DetFactoryHelper.h>
#include <XML/Utilities.h>
#include <XML/Layering.h>

using namespace dd4hep;

static Ref_t create_detector(Detector& desc, xml_h e, SensitiveDetector sens) {
  xml_det_t x_det = e;

  std::string det_name = x_det.nameStr();
  int det_id = x_det.id();

  DetElement det(det_name, det_id);

  xml_comp_t x_dim = x_det.child(_Unicode(dimensions));
  xml_comp_t x_pos = x_det.child(_Unicode(position));
  xml_comp_t x_mat = x_det.child(_Unicode(material));

  double sx = x_dim.attr<double>(_Unicode(x));
  double sy = x_dim.attr<double>(_Unicode(y));
  double sz = x_dim.attr<double>(_Unicode(z));

  Material mat = desc.material(x_mat.attr<std::string>(_Unicode(name)));

  Box solid(sx / 2.0, sy / 2.0, sz / 2.0);
  Volume vol(det_name + "_vol", solid, mat);

  sens.setType("tracker");
  vol.setSensitiveDetector(sens);

  Volume mother = desc.pickMotherVolume(det);

  Position pos(x_pos.x(), x_pos.y(), x_pos.z());
  PlacedVolume pv = mother.placeVolume(vol, Transform3D(RotationZYX(0, 0, 0), pos));

  pv.addPhysVolID("system", det_id);
  pv.addPhysVolID("layer", 0);
  pv.addPhysVolID("sensor", 0);

  det.setPlacement(pv);
  return det;
}

DECLARE_DETELEMENT(testBeamACLGAD, create_detector)


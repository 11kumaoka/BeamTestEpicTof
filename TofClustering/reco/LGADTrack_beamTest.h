#pragma once

#include <algorithms/algorithm.h>
#include <edm4eic/Measurement2DCollection.h>

namespace eicrecon {

class LGADTrack_beamTest
    : public algorithms::Algorithm<
          algorithms::Input<const edm4eic::Measurement2DCollection,
                            const edm4eic::Measurement2DCollection,
                            const edm4eic::Measurement2DCollection>,
          algorithms::Output<edm4eic::Measurement2DCollection>> {
public:
  LGADTrack_beamTest(std::string_view name)
      : Algorithm{name,
                  {"KumaTOFBarrelClusterHits1",
                   "KumaTOFBarrelClusterHits2",
                   "KumaTOFBarrelClusterHits3"},
                  {"KumaTOFTracks"},
                  ""} {}

  void init();
  void process(const Input& input, const Output& output) const final;
};

} // namespace eicrecon
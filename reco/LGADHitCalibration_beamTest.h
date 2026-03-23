// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2025 Chun Yuen Tsang

#pragma once

#include <DDRec/CellIDPositionConverter.h>
#include <algorithms/algorithm.h>
#include <edm4eic/RawTrackerHitCollection.h>
#include <edm4eic/TrackerHitCollection.h>
#include <spdlog/logger.h>
#include <memory>
#include <string>
#include <string_view>

#include "LGADHitCalibrationConfig_beamTest.h"
#include "algorithms/interfaces/WithPodConfig.h"

namespace eicrecon {

using LGADHitCalibrationAlgorithm_beamTest =
    algorithms::Algorithm<algorithms::Input<edm4eic::RawTrackerHitCollection>,
                          algorithms::Output<edm4eic::TrackerHitCollection>>;

class LGADHitCalibration_beamTest : public LGADHitCalibrationAlgorithm_beamTest,
                           public WithPodConfig<LGADHitCalibrationConfig_beamTest> {

public:
  LGADHitCalibration_beamTest(std::string_view name)
      : LGADHitCalibrationAlgorithm_beamTest{name, {"TOFBarrelADCTDC"}, {"TOFBarrelCalHit"}, ""} {};

  void init() final;
  void process(const Input&, const Output&) const final;

private:
  std::shared_ptr<spdlog::logger> m_log;

  const dd4hep::rec::CellIDPositionConverter* m_converter = nullptr;

  dd4hep::DDSegmentation::BitFieldCoder* m_decoder = nullptr;
  dd4hep::rec::CellID encodeBeamTestCellID(dd4hep::rec::CellID oldCellID) const;
};
} // namespace eicrecon

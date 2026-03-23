#pragma once

#include "LGADTrack_beamTest.h"
#include "extensions/jana/JOmniFactory.h"

namespace eicrecon {

class LGADTrack_beamTest_factory
    : public JOmniFactory<LGADTrack_beamTest_factory> {
private:
  std::unique_ptr<eicrecon::LGADTrack_beamTest> m_algo;

  PodioInput<edm4eic::Measurement2D> m_input1{this};
  PodioInput<edm4eic::Measurement2D> m_input2{this};
  PodioInput<edm4eic::Measurement2D> m_input3{this};

  PodioOutput<edm4eic::Measurement2D> m_output{this};

public:
  void Configure() {
    m_algo = std::make_unique<eicrecon::LGADTrack_beamTest>(GetPrefix());
    m_algo->level(static_cast<algorithms::LogLevel>(logger()->level()));
    m_algo->init();
  }

  void ChangeRun(int32_t /* run_number */) {}

  void Process(int32_t /* run_number */, uint64_t /* event_number */) {
    m_algo->process({m_input1(), m_input2(), m_input3()},
                    {m_output().get()});
  }
};

} // namespace eicrecon
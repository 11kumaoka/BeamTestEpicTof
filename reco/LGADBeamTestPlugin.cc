
#include <JANA/JApplication.h>
#include <edm4eic/EDM4eicVersion.h>
#include <TMath.h>
#include <edm4eic/unit_system.h>
#include <edm4hep/SimTrackerHit.h>
#include <Evaluator/DD4hepUnits.h>

#include "algorithms/digi/SiliconChargeSharingConfig.h"
#include "extensions/jana/JOmniFactoryGeneratorT.h"
#include "factories/digi/CFDROCDigitization_factory.h"
#include "factories/digi/PulseCombiner_factory.h"
#include "factories/digi/PulseGeneration_factory.h"
#include "factories/digi/SiliconChargeSharing_factory.h"
#include "factories/digi/SiliconPulseDiscretization_factory.h"
#include "factories/digi/SiliconTrackerDigi_factory.h"
// #include "factories/reco/LGADHitCalibration_factory.h"
// #include "factories/tracking/LGADHitClustering_factory.h"

#include "LGADHitCalibration_beamTest_factory.h"
#include "LGADHitClustering_beamTest_factory.h"
#include "LGADTrack_beamTest_factory.h"


extern "C" {
void InitPlugin(JApplication* app) {
  InitJANAPlugin(app);
  using namespace eicrecon;
    app->Add(new JOmniFactoryGeneratorT<LGADHitCalibration_beamTest_factory>(
      "KumaTOFBarrelCalibratedHits1", {"TOFBarrelADCTDC1"},
      {"KumaTOFBarrelCalibratedHits1"}, {}, app));
    app->Add(new JOmniFactoryGeneratorT<LGADHitCalibration_beamTest_factory>(
      "KumaTOFBarrelCalibratedHits2", {"TOFBarrelADCTDC2"},
      {"KumaTOFBarrelCalibratedHits2"}, {}, app));
    app->Add(new JOmniFactoryGeneratorT<LGADHitCalibration_beamTest_factory>(
        "KumaTOFBarrelCalibratedHits3", {"TOFBarrelADCTDC3"},
        {"KumaTOFBarrelCalibratedHits3"}, {}, app));


    app->Add(new JOmniFactoryGeneratorT<LGADHitClustering_beamTest_factory>(
        "KumaTOFBarrelClusterHits1", {"KumaTOFBarrelCalibratedHits1"}, // Input data collection tags
        {"KumaTOFBarrelClusterHits1"},                            // Output data tag
        {}, app));
    app->Add(new JOmniFactoryGeneratorT<LGADHitClustering_beamTest_factory>(
        "KumaTOFBarrelClusterHits2", {"KumaTOFBarrelCalibratedHits2"}, // Input data collection tags
        {"KumaTOFBarrelClusterHits2"},                            // Output data tag
        {}, app));
    app->Add(new JOmniFactoryGeneratorT<LGADHitClustering_beamTest_factory>(
        "KumaTOFBarrelClusterHits3", {"KumaTOFBarrelCalibratedHits3"}, // Input data collection tags
        {"KumaTOFBarrelClusterHits3"},                            // Output data tag
        {}, app));

          
    app->Add(new JOmniFactoryGeneratorT<eicrecon::LGADTrack_beamTest_factory>(
        "KumaTOFTracks", {"KumaTOFBarrelClusterHits1","KumaTOFBarrelClusterHits2","KumaTOFBarrelClusterHits3"},
        {"KumaTOFTracks"}, {}, app));

       
    // app->Add(new eicrecon::ForceTrackOutput_processor);



/* // Create TDCADC output from SimTrackerHit input
  // 1. Digitization
  app->Add(new JOmniFactoryGeneratorT<SiliconTrackerDigi_factory>(
      "KumaTOFBarrelRawHits", {"EventHeader", "TOFBarrelHits"},
      {"KumaTOFBarrelRawHits",
#if EDM4EIC_BUILD_VERSION >= EDM4EIC_VERSION(8, 7, 0)
       "KumaTOFBarrelRawHitLinks",
#endif
       "KumaTOFBarrelRawHitAssociations"},
       {.threshold = 0.1 * dd4hep::keV, .timeResolution = 0.025}, app));
    //   {.threshold = 6.0 * dd4hep::keV, .timeResolution = 0.025}, app));

  // 2. Calibration (CalibratedHits)
  app->Add(new JOmniFactoryGeneratorT<LGADHitCalibration_factory>(
      "KumaTOFBarrelCalibratedHits", {"KumaTOFBarrelADCTDC"},
      {"KumaTOFBarrelCalibratedHits"}, {}, app));

  app->Add(new JOmniFactoryGeneratorT<SiliconChargeSharing_factory>(
      "KumaTOFBarrelSharedHits", {"TOFBarrelHits"}, {"KumaTOFBarrelSharedHits"},
      {
          .sigma_mode     = SiliconChargeSharingConfig::ESigmaMode::rel,
          .sigma_sharingx = 1, .sigma_sharingy = 0.5,
          .min_edep       = 0.0 * edm4eic::unit::GeV,
          .readout        = "TOFBarrelHits",
      }, app));

  // app->Add(new JOmniFactoryGeneratorT<KumaSiliconChargeSharing_factory>(
  //     "KumaTOFBarrelSharedHits", {"TOFBarrelHits"}, {"KumaTOFBarrelSharedHits"},
  //     {
  //         .sigma_mode     = SiliconChargeSharingConfig::ESigmaMode::rel,
  //         .sigma_sharingx = 1, .sigma_sharingy = 0.5,
  //         .min_edep       = 0.0 * edm4eic::unit::GeV,
  //         .readout        = "TOFBarrelHits",
  //     }, app));


//   // 4. Pulse Generation
  const double x_when_landau_min = -0.22278;
  const double landau_min        = TMath::Landau(x_when_landau_min, 0, 1, true);
  const double sigma_analog      = 0.293951 * edm4eic::unit::ns;
  const double Vm                = 3e-4 * dd4hep::GeV;
  const double gain              = -256 / Vm / landau_min * sigma_analog;
  
  app->Add(new JOmniFactoryGeneratorT<PulseGeneration_factory<edm4hep::SimTrackerHit>>(
      "KumaLGADPulseGeneration", {"KumaTOFBarrelSharedHits"}, {"KumaTOFBarrelSmoothPulses"},
      {
        .pulse_shape_function = "LandauPulse",
    .pulse_shape_params   = {gain, sigma_analog, 3.0},
    .ignore_thres         = 0.01, // 0.05*256 
    .timestep             = 0.01 * edm4eic::unit::ns,
        //   .pulse_shape_function = "LandauPulse",
        //   .pulse_shape_params   = {gain, sigma_analog, 3.0},
        //   .ignore_thres         = 0.05 * 256,
        //   .timestep             = 0.01 * edm4eic::unit::ns,
      }, app));

//   // 5. Pulse Combiner & Discretization & CFD
  app->Add(new JOmniFactoryGeneratorT<PulseCombiner_factory>(
      "KumaTOFBarrelPulseCombiner", {"KumaTOFBarrelSmoothPulses"}, {"KumaTOFBarrelCombinedPulses"},
      {.minimum_separation = 25 * edm4eic::unit::ns}, app));

  app->Add(new JOmniFactoryGeneratorT<SiliconPulseDiscretization_factory>(
      "KumaTOFBarrelPulses", {"KumaTOFBarrelCombinedPulses"}, {"KumaTOFBarrelPulses"},
      {
          .EICROC_period = 25 * edm4eic::unit::ns,
          .local_period  = 25 * edm4eic::unit::ns / 1024,
          .global_offset = -3.0 * sigma_analog + 0.45 * edm4eic::unit::ns,
      }, app));

  app->Add(new JOmniFactoryGeneratorT<CFDROCDigitization_factory>(
      "KumaTOFBarrelADCTDC", {"KumaTOFBarrelPulses"}, {"KumaTOFBarrelADCTDC"}, {}, app));
    //   "KumaCFDROCDigitization", {"KumaTOFBarrelPulses"}, {"KumaTOFBarrelADCTDC"}, {}, app));
*/

    // app->Add(new JFactoryGeneratorT<BTOFFactory>());
    // app->Add(new DebugTOFProcessor());
}
}


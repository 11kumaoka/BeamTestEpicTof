#include "LGADTrack_beamTest.h"
#include <iostream>
#include <algorithm>

namespace eicrecon {

void LGADTrack_beamTest::init() {}

void LGADTrack_beamTest::process(const Input& input, const Output& output) const {
  const auto [clusters1, clusters2, clusters3] = input;
  auto [tracks] = output;



  for(size_t iClu2 = 0; iClu2 < clusters2->size(); ++iClu2) {
    float smallestChi2 = 99999.;
    int assCluIDs[3] = {-1, -1, -1};
    float selectedSlope = 99999.;
    float selectedIntercept = 99999.;
    for(size_t iClu1 = 0; iClu1 < clusters1->size(); ++iClu1) {
      for(size_t iClu3 = 0; iClu3 < clusters3->size(); ++iClu3) {
        const auto& clu1 = clusters1->at(iClu1);
        const auto& clu2 = clusters2->at(iClu2);
        const auto& clu3 = clusters3->at(iClu3);

        // if (std::abs(clu1.getTime() - clu2.getTime()) > 50 || std::abs(clu3.getTime() - clu2.getTime()) > 50) continue; // skip clusters with invalid time
        if (std::abs(clu1.getLoc()[0] - clu2.getLoc()[0]) > 1.5 || std::abs(clu3.getLoc()[0] - clu2.getLoc()[0]) > 1.5) continue; // skip clusters with invalid time

        float triggerWidthX = 8.; // ns, just an example value
        float triggerWidthY = 8.; // ns, just an example value
        float trig1X = 0.;
        float trig1Y = 0.;
        float trig1Z = 0.;
        float trig1WX = triggerWidthX/std::sqrt(12);
        float trig1WY = triggerWidthY/std::sqrt(12);
        float trig2X = 0.;
        float trig2Y = 0.;
        float trig2Z = 500.;
        float trig2WX = triggerWidthX/std::sqrt(12);
        float trig2WY = triggerWidthY/std::sqrt(12);

        auto loc1 = clu1.getLoc();
        auto loc2 = clu2.getLoc();
        auto loc3 = clu3.getLoc();
        float clu1Z = 50.;
        float clu2Z = 100.;
        float clu3Z = 150.;

        // float sumWX = c1.getCovariance()[0] + c2.getCovariance()[0] + c3.getCovariance()[0];
        float stripWeightX = 0.5/std::sqrt(12);
        // float sumW = trig1WX + stripWeightX + stripWeightX + stripWeightX + trig2WX;
        // float sumWZ = trig1Z/(trig1WX) + clu1Z/(stripWeightX) + clu2Z/(stripWeightX) + clu3Z/(stripWeightX) +  trig2Z/(trig2WX);
        // float sumWX = trig1X/(trig1WX) + loc1[0]/(stripWeightX) + loc2[0]/(stripWeightX) + loc3[0]/(stripWeightX) +  trig2X/(trig2WX);
        // float sumWZZ = trig1Z*trig1Z/(trig1WX) + clu1Z*clu1Z/(stripWeightX) + clu2Z*clu2Z/(stripWeightX) + clu3Z*clu3Z/(stripWeightX) +  trig2Z*trig2Z/(trig2WX);
        // float sumWZX = trig1X*trig1Z/(trig1WX) + loc1[0]*clu1Z/(stripWeightX) + loc2[0]*clu2Z/(stripWeightX) + loc3[0]*clu3Z/(stripWeightX) +  trig2X*trig2Z/(trig2WX);

        float sumW = stripWeightX + stripWeightX + stripWeightX;
        float sumWZ = clu1Z + clu2Z + clu3Z;
        float sumWX = loc1[0] + loc2[0] + loc3[0];
        float sumWZZ = clu1Z*clu1Z + clu2Z*clu2Z + clu3Z*clu3Z;
        float sumWZX = loc1[0]*clu1Z + loc2[0]*clu2Z + loc3[0]*clu3Z;


        // double denom = 3.*sumWZZ - sumWZ*sumWZX;
        double denom = 3.*sumWZZ - sumWZ*sumWZ;

        if (std::abs(denom) < 1e-12) {
          std::cerr << "Linear fit failed: denominator is too small." << std::endl;
        }
        else {
          double slope = (3.*sumWZX - sumWZ*sumWX) / denom;
          double intercept = (sumWX - slope*sumWZ) / 3.;

          // std::cout << "x:: hit1:" << loc1[0] << ", hit2:" << loc2[0] << ", hit3:" << loc3[0] << ", slope: " << slope << ", intercept: " << intercept << std::endl;

          // double chi2 = trig1WX * std::pow(trig1X - (slope*trig1Z + intercept), 2)\
          //   + stripWeightX * std::pow(loc1[0] - (slope*clu1Z + intercept), 2)\
          //   + stripWeightX * std::pow(loc2[0] - (slope*clu2Z + intercept), 2)\
          //   + stripWeightX * std::pow(loc3[0] - (slope*clu3Z + intercept), 2)\
          //   + trig2WX * std::pow(trig2X - (slope*trig2Z + intercept), 2);


          double chi2 = stripWeightX * std::pow(loc1[0] - (slope*clu1Z + intercept), 2)\
            + stripWeightX * std::pow(loc2[0] - (slope*clu2Z + intercept), 2)\
            + stripWeightX * std::pow(loc3[0] - (slope*clu3Z + intercept), 2);


          if (chi2 < smallestChi2) {
            smallestChi2 = chi2;
            assCluIDs[0] = iClu1;
            assCluIDs[1] = iClu2;
            assCluIDs[2] = iClu3;
            selectedSlope = slope;
            selectedIntercept = intercept;
          }
        }


      } // end of loop over clusters in layer 3
    } // end of loop over clusters in layer 1

    if(smallestChi2 > 100.) continue;
    auto out = tracks->create();
    out.setSurface(0);
    out.setLoc({selectedSlope, selectedIntercept});
    out.setTime(clusters1->at(assCluIDs[0]).getTime());
    out.setCovariance(clusters1->at(assCluIDs[0]).getCovariance());
  } // end of loop over clusters in layer 2


}

} // namespace eicrecon
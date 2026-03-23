// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
// 2024/11/28 Template a macro to compile written by Kumaoka
// Please replace the name Algorithm to your analysis name, (anyname ok).
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 

// #define trackEventDisplay_cxx
#include "trackEventDisplay.h"

#include <random>

#include <TStyle.h>
#include <TCanvas.h>



void trackEventDisplay::Loop()
{
   if (fChain == 0) return;

   HistInit();

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   Double_t numOfEvents[18] = {};
   Double_t numOfEvents_EachDet_TrigRegion[4][18] = {};
   Double_t numOfEvents_TrigRegion[4] = {}; // 0: Phys W/O Trig23, 1: Phys W Trig23, 2: Noise W/O Trig23, 3: Noise W Trig23
   
   size_t numOfPhys = 0;
   size_t numOfNoise = 0;

   bool bTargetEV = false;
   

    m_vTargetEvents = {};

   // Int_t numOfEventLoops = 1000;
   // Int_t numOfEventLoops = 5;
   Int_t numOfEventLoops = nentries;
   if(bTargetEV) numOfEventLoops = m_vTargetEvents.size();

   // float m_timewindow = 2000.0; // width of time split for a time frame [ns]
   // float m_timeslice_width = 20.0; // width of time split for a time frame [ns]   
   
   // for (Long64_t jentry=0; jentry<1000; jentry++) {
   for (Long64_t jentry = 0; jentry < numOfEventLoops; ++jentry) {
   // for (Long64_t jentry=0; jentry < nentries;++jentry) {
      Long64_t tempJEntry = jentry;
      if(bTargetEV) jentry =  m_vTargetEvents.at(jentry);
      m_pubEvNum = jentry;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // if(jentry%100 == 0)std::cout << " == event" << jentry << " =====" << std::endl;
      // std::cout << " == event" << jentry << " =====" << std::endl;
      
      // if(KumaTOFBarrelCalibratedHits1_ == 0 || KumaTOFBarrelCalibratedHits2_ ==0 || KumaTOFBarrelCalibratedHits3_ == 0) continue;
      // std::cout << "KumaTOFBarrelCalibratedHits1_ = " << KumaTOFBarrelCalibratedHits1_ << std::endl;
      

      if(KumaTOFBarrelCalibratedHits1_ == 0 || KumaTOFBarrelCalibratedHits2_ ==0 || KumaTOFBarrelCalibratedHits3_ == 0) continue;
      // std::cout << "KumaTOFTracks_ = " << KumaTOFTracks_ << std::endl;
      if(KumaTOFTracks_ == 0) continue;
      if(KumaTOFBarrelCalibratedHits2_  < 3) continue; // ModifKuma
      if(m_iDisplayCount < 9) recordEventsForED();

      numOfEvents[17]++;

    } // == end of loop over events



   Double_t scaleV = (m_vTargetEvents.size()/2.)/(1000.);
   if(!bTargetEV) scaleV = 1. - scaleV;
   std::cout << "numOfEventLoops : scaleV = " << numOfEventLoops << " : " << scaleV << std::endl;

   WriteHists();

   // for (size_t nHist = 0; nHist < numOfED; nHist++) {
   //    m_hEventDisplays[nHist] = nullptr;
   //    m_hEventDisplays[nHist] = new TH3D(
   //       Form("hEventDisplays%zu", nHist), ";z [mm];x [mm]; y [mm]", 1000, 0., 500, 60, -30, 30, 60, -30, 30
   //    );
   // }
   // drawEightEvents();

   for (int i = 0; i < numOfED; ++i) {
      m_hEventDisplays2D[i] = new TH2D(
         Form("hEventDisplay2D_%d", i),
         Form("Event %d;z [mm];x [mm]", i),
         100, -20, 320,
         60, -6, 6
      );
   }

   drawEightEvents2D_ZX();

   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;

}




// === s === For Event Display =========== #########################################################
void trackEventDisplay::recordEventsForED(){
   m_iDisplayCount++;
   Event ev;

   for (size_t i = 0; i < KumaTOFTracks_; ++i) {
      float slope = KumaTOFTracks_loc_a[i];
      float intercept = KumaTOFTracks_loc_b[i];

      std::cout << "slope:intercept = " << slope << " : " << intercept << std::endl;

      float x_vertex = slope * 0.0 + intercept; // Assuming z=0 for the vertex
      float x_endpoint = slope * 300.0 + intercept; // Assuming z=300 for the endpoint

      Particle p;
      p.vertex = {x_vertex, 4.0, 0.0};
      p.endpoint = {x_vertex, 4.0, 300.0};
      p.momentum = {1., 1., 50.};
      p.pdg = 211;
      p.charge = -1.;
      p.hasEndpoint = true;
      

      ev.particles.push_back(p);
   }
   m_eventsForED.push_back(ev);

   
   Int_t calibHitSize = 0;
   std::vector<std::vector<Vec3> > vCalibDetsHits;
   std::vector<Vec3> vCalibDetHits1;
   for (size_t iHits = 0; iHits < KumaTOFBarrelCalibratedHits1_; iHits++){
      Vec3 hitV3 = {KumaTOFBarrelCalibratedHits1_position_x[iHits], KumaTOFBarrelCalibratedHits1_position_y[iHits], KumaTOFBarrelCalibratedHits1_position_z[iHits]};
      vCalibDetHits1.push_back(hitV3);
   }
   // KumaTOFBarrelCalibratedHits1_ = calibHitSize;
   vCalibDetsHits.push_back(vCalibDetHits1);
   std::vector<Vec3> vCalibDetHits2;
   for (size_t iHits = 0; iHits < KumaTOFBarrelCalibratedHits2_; iHits++){
      Vec3 hitV3 = {KumaTOFBarrelCalibratedHits2_position_x[iHits], KumaTOFBarrelCalibratedHits2_position_y[iHits], KumaTOFBarrelCalibratedHits2_position_z[iHits]};
      vCalibDetHits2.push_back(hitV3);
   }
   vCalibDetsHits.push_back(vCalibDetHits2);
   std::vector<Vec3> vCalibDetHits3;
   for (size_t iHits = 0; iHits < KumaTOFBarrelCalibratedHits3_; iHits++){
      Vec3 hitV3 = {KumaTOFBarrelCalibratedHits3_position_x[iHits], KumaTOFBarrelCalibratedHits3_position_y[iHits], KumaTOFBarrelCalibratedHits3_position_z[iHits]};
      vCalibDetHits3.push_back(hitV3);
   }
   vCalibDetsHits.push_back(vCalibDetHits3);
   m_vRecordedCalibDetHits.push_back(vCalibDetsHits);


   std::vector<std::vector<Vec3> > vClustsDetsHits;
   std::vector<Vec3> vClustDetHits1;
   for (size_t iHits = 0; iHits < KumaTOFBarrelClusterHits1_; iHits++){
      Vec3 hitV3 = {KumaTOFBarrelClusterHits1_loc_a[iHits], KumaTOFBarrelClusterHits1_loc_b[iHits], 50.};
      vClustDetHits1.push_back(hitV3);
   }
   vClustsDetsHits.push_back(vClustDetHits1);
   std::vector<Vec3> vClustDetHits2;
   for (size_t iHits = 0; iHits < KumaTOFBarrelClusterHits2_; iHits++){
      Vec3 hitV3 = {KumaTOFBarrelClusterHits2_loc_a[iHits], KumaTOFBarrelClusterHits2_loc_b[iHits], 150.};
      vClustDetHits2.push_back(hitV3);
   }
   vClustsDetsHits.push_back(vClustDetHits2);
   std::vector<Vec3> vClustDetHits3;
   for (size_t iHits = 0; iHits < KumaTOFBarrelClusterHits3_; iHits++){
      Vec3 hitV3 = {KumaTOFBarrelClusterHits3_loc_a[iHits], KumaTOFBarrelClusterHits3_loc_b[iHits], 200.};
      vClustDetHits3.push_back(hitV3);
   }
   vClustsDetsHits.push_back(vClustDetHits3);
   m_vRecordedClustDetHits.push_back(vClustsDetsHits);


}

void trackEventDisplay::drawOneEvent(const Event& ev, int eventIndex, double fallbackLength) {
//   double xmin, xmax, ymin, ymax, zmin, zmax;
   // computeEventBounds(ev, xmin, xmax, ymin, ymax, zmin, zmax, fallbackLength);

   m_hEventDisplays[0]->SetStats(0);
   m_hEventDisplays[eventIndex]->Draw();
   gStyle->SetOptStat(0);
   for (size_t i = 0; i < ev.particles.size(); ++i) {
      const auto& p = ev.particles[i];
      const Vec3 a = p.vertex;
      const Vec3 b = p.endpoint;
      // const Vec3 b = getTrackEnd(p, fallbackLength);

      if (mag(sub(b, a)) < 1e-12) continue;

      auto* line = new TPolyLine3D(2);
      line->SetPoint(0, a.z, a.x, a.y);
      line->SetPoint(1, b.z, b.x, b.y);
      line->SetLineColor(colorFromPDG(p.pdg));
      line->SetLineWidth(2);
      line->Draw("same");
   
   }
   
   Int_t numOfCalibHits = KumaTOFBarrelCalibratedHits1_ + KumaTOFBarrelCalibratedHits2_ + KumaTOFBarrelCalibratedHits3_;
   auto* markers_Hits = new TPolyMarker3D(numOfCalibHits);
   for (size_t iHit = 0; iHit < KumaTOFBarrelCalibratedHits1_; ++iHit) {
      markers_Hits->SetPoint(iHit, 50.0, KumaTOFBarrelCalibratedHits1_position_x[iHit], 10.);

      markers_Hits->SetMarkerStyle(20);
      markers_Hits->SetMarkerSize(0.4);
      markers_Hits->SetMarkerColor(m_myHistColors[4]);
      markers_Hits->Draw("same");
   }

   Int_t numOfCluHits = KumaTOFBarrelClusterHits1_ + KumaTOFBarrelClusterHits2_ + KumaTOFBarrelClusterHits3_;
   auto* markers_Clu = new TPolyMarker3D(numOfCluHits);
   for (size_t iHit = 0; iHit < KumaTOFBarrelClusterHits1_; ++iHit) {
      markers_Clu->SetPoint(iHit, 50.0, KumaTOFBarrelClusterHits1_loc_a[iHit], 10.);

      markers_Clu->SetMarkerStyle(20);
      markers_Clu->SetMarkerSize(0.6);
      markers_Clu->SetMarkerColor(802);
      markers_Clu->Draw("same");
   }

   
}

void trackEventDisplay::drawEightEvents(double fallbackLength) {
  auto* c = new TCanvas("c_events", "MCParticle Event Display", 1800, 900);
  c->Divide(4, 2, 0.001, 0.001);
   gStyle->SetOptStat(0);
//   const int nDraw = std::min<int>(nPads, m_eventsForED.size());

  for (int i = 0; i < numOfED; ++i) {
      c->cd(i + 1);
      gStyle->SetOptStat(0);
      gPad->SetTheta(20);
      gPad->SetPhi(30);
      gPad->SetLeftMargin(0.02);
      gPad->SetRightMargin(0.02);
      gPad->SetTopMargin(0.08);
      gPad->SetBottomMargin(0.02);
      
      drawOneEvent(m_eventsForED[i], i, fallbackLength);
  }
  c->Update();

  TFile fout("EventDisplays.root", "RECREATE");
  c->Write();
  fout.Close();

  c->SaveAs("EventDisplays.pdf");
}




// === s === 2D event display
void trackEventDisplay::drawEightEvents2D_ZX(double fallbackLength) {
   auto* c = new TCanvas("c_events_2d", "Track Event Display 2D", 1800, 900);
   c->Divide(4, 2, 0.001, 0.001);
   gStyle->SetOptStat(0);

   for (int i = 0; i < numOfED; ++i) {
      c->cd(i + 1);
      gPad->SetLeftMargin(0.12);
      gPad->SetRightMargin(0.05);
      gPad->SetTopMargin(0.08);
      gPad->SetBottomMargin(0.12);

      drawOneEvent2D_ZX(m_eventsForED[i], i, fallbackLength);
   }

   c->Update();

   TFile fout("EventDisplays2D.root", "RECREATE");
   c->Write();
   fout.Close();

   c->SaveAs("EventDisplays2D.pdf");
}


void trackEventDisplay::drawOneEvent2D_ZX(const Event& ev, int eventIndex, double fallbackLength) {
   m_hEventDisplays2D[eventIndex]->SetStats(0);
   m_hEventDisplays2D[eventIndex]->Draw();
   gStyle->SetOptStat(0);


   auto* det1 = new TLine(50.0, -2.0, 50.0, 2.0);
   det1->SetLineStyle(2);
   det1->SetLineColor(kGray+2);
   det1->Draw("same");

   auto* det2 = new TLine(100.0, -2.0, 100.0, 2.0);
   det2->SetLineStyle(2);
   det2->SetLineColor(kGray+2);
   det2->Draw("same");

   auto* det3 = new TLine(150.0, -2.0, 150.0, 2.0);
   det3->SetLineStyle(2);
   det3->SetLineColor(kGray+2);
   det3->Draw("same");



   for (size_t i = 0; i < ev.particles.size(); ++i) {
      const auto& p = ev.particles[i];
      const Vec3 a = p.vertex;
      const Vec3 b = p.endpoint;

      if (mag(sub(b, a)) < 1e-12) continue;

      auto* line = new TLine(a.z, a.x, b.z, b.x);  // x-axis = z, y-axis = x
      line->SetLineColor(colorFromPDG(p.pdg));
      line->SetLineWidth(2);
      line->Draw("same");
   }
   
   // calibrated hits
   for(size_t iDet = 0; iDet < 3; iDet++){
      for(size_t iHit = 0; iHit < m_vRecordedCalibDetHits.at(eventIndex).at(iDet).size(); iHit++){
         auto* marker = new TMarker(50.0 * (iDet + 1), m_vRecordedCalibDetHits.at(eventIndex).at(iDet).at(iHit).x, 20);
         marker->SetMarkerSize(0.8);
         marker->SetMarkerStyle(20);
         marker->SetMarkerColor(4);
         marker->Draw("same");
      }

      for(size_t iHit = 0; iHit < m_vRecordedClustDetHits.at(eventIndex).at(iDet).size(); iHit++){
         auto* marker = new TMarker(50.0 * (iDet + 1), m_vRecordedClustDetHits.at(eventIndex).at(iDet).at(iHit).x, 20);
         marker->SetMarkerSize(1.5);
         marker->SetMarkerStyle(89);
         marker->SetMarkerColor(802);
         marker->Draw("same");
      }
   }


}


// === e === For Event Display =========== #########################################################





void trackEventDisplay::HistInit(){
   oFile = new TFile(oFileName.c_str(), "recreate");

   m_hEventDisplayZR = new TH2D(
      "m_hEventDisplayZR_Det",
      "Event Display; z [mm]; r [mm]",
      1000, -10000, 10000, 250, 0,2500
   );



}


void trackEventDisplay::WriteHists(){
   oFile->cd();

   m_hEventDisplayZR->Write();

   oFile->Close();
}



trackEventDisplay::trackEventDisplay(TTree *tree, std::string iTempFileName,std::string oTempFileName) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   iFileName = iTempFileName;
   oFileName = oTempFileName;

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(iFileName.c_str());
      if (!f || !f->IsOpen()) {
         f = new TFile(iFileName.c_str());
      }
      // "kuma example": you need to replace "tree" to your tree name in the input root file.
      f->GetObject("events",tree);

   }
   Init(tree);
}

trackEventDisplay::~trackEventDisplay()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}



// == s == MakeClass Default Functions == s ==
Int_t trackEventDisplay::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t trackEventDisplay::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}


void trackEventDisplay::Init(TTree *tree)
{
   // Set object pointer
   _KumaTOFBarrelClusterHits1_weights = 0;
   _KumaTOFBarrelClusterHits2_weights = 0;
   _KumaTOFBarrelClusterHits3_weights = 0;
   _KumaTOFTracks_weights = 0;


   GPIntKeys = 0;
   GPIntValues = 0;
   GPFloatKeys = 0;
   GPFloatValues = 0;
   GPDoubleKeys = 0;
   GPDoubleValues = 0;
   GPStringKeys = 0;
   GPStringValues = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchStatus("*", 0);
   fChain->SetBranchStatus("KumaTOFBarrelCalibratedHits1*", 1);
   fChain->SetBranchStatus("KumaTOFBarrelCalibratedHits2*", 1);
   fChain->SetBranchStatus("KumaTOFBarrelCalibratedHits3*", 1);
   fChain->SetBranchStatus("KumaTOFBarrelClusterHits1*", 1);
   fChain->SetBranchStatus("KumaTOFBarrelClusterHits2*", 1);
   fChain->SetBranchStatus("KumaTOFBarrelClusterHits3*", 1);
   fChain->SetBranchStatus("KumaTOFTracks*", 1);



    fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1", &KumaTOFBarrelCalibratedHits1_, &b_KumaTOFBarrelCalibratedHits1_);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.cellID", KumaTOFBarrelCalibratedHits1_cellID, &b_KumaTOFBarrelCalibratedHits1_cellID);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.position.x", KumaTOFBarrelCalibratedHits1_position_x, &b_KumaTOFBarrelCalibratedHits1_position_x);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.position.y", KumaTOFBarrelCalibratedHits1_position_y, &b_KumaTOFBarrelCalibratedHits1_position_y);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.position.z", KumaTOFBarrelCalibratedHits1_position_z, &b_KumaTOFBarrelCalibratedHits1_position_z);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.positionError.xx", KumaTOFBarrelCalibratedHits1_positionError_xx, &b_KumaTOFBarrelCalibratedHits1_positionError_xx);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.positionError.yy", KumaTOFBarrelCalibratedHits1_positionError_yy, &b_KumaTOFBarrelCalibratedHits1_positionError_yy);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.positionError.zz", KumaTOFBarrelCalibratedHits1_positionError_zz, &b_KumaTOFBarrelCalibratedHits1_positionError_zz);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.time", KumaTOFBarrelCalibratedHits1_time, &b_KumaTOFBarrelCalibratedHits1_time);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.timeError", KumaTOFBarrelCalibratedHits1_timeError, &b_KumaTOFBarrelCalibratedHits1_timeError);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.edep", KumaTOFBarrelCalibratedHits1_edep, &b_KumaTOFBarrelCalibratedHits1_edep);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits1.edepError", KumaTOFBarrelCalibratedHits1_edepError, &b_KumaTOFBarrelCalibratedHits1_edepError);
   fChain->SetBranchAddress("_KumaTOFBarrelCalibratedHits1_rawHit", &_KumaTOFBarrelCalibratedHits1_rawHit_, &b__KumaTOFBarrelCalibratedHits1_rawHit_);
   fChain->SetBranchAddress("_KumaTOFBarrelCalibratedHits1_rawHit.index", _KumaTOFBarrelCalibratedHits1_rawHit_index, &b__KumaTOFBarrelCalibratedHits1_rawHit_index);
   fChain->SetBranchAddress("_KumaTOFBarrelCalibratedHits1_rawHit.collectionID", _KumaTOFBarrelCalibratedHits1_rawHit_collectionID, &b__KumaTOFBarrelCalibratedHits1_rawHit_collectionID);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2", &KumaTOFBarrelCalibratedHits2_, &b_KumaTOFBarrelCalibratedHits2_);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.cellID", KumaTOFBarrelCalibratedHits2_cellID, &b_KumaTOFBarrelCalibratedHits2_cellID);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.position.x", KumaTOFBarrelCalibratedHits2_position_x, &b_KumaTOFBarrelCalibratedHits2_position_x);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.position.y", KumaTOFBarrelCalibratedHits2_position_y, &b_KumaTOFBarrelCalibratedHits2_position_y);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.position.z", KumaTOFBarrelCalibratedHits2_position_z, &b_KumaTOFBarrelCalibratedHits2_position_z);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.positionError.xx", KumaTOFBarrelCalibratedHits2_positionError_xx, &b_KumaTOFBarrelCalibratedHits2_positionError_xx);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.positionError.yy", KumaTOFBarrelCalibratedHits2_positionError_yy, &b_KumaTOFBarrelCalibratedHits2_positionError_yy);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.positionError.zz", KumaTOFBarrelCalibratedHits2_positionError_zz, &b_KumaTOFBarrelCalibratedHits2_positionError_zz);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.time", KumaTOFBarrelCalibratedHits2_time, &b_KumaTOFBarrelCalibratedHits2_time);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.timeError", KumaTOFBarrelCalibratedHits2_timeError, &b_KumaTOFBarrelCalibratedHits2_timeError);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.edep", KumaTOFBarrelCalibratedHits2_edep, &b_KumaTOFBarrelCalibratedHits2_edep);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits2.edepError", KumaTOFBarrelCalibratedHits2_edepError, &b_KumaTOFBarrelCalibratedHits2_edepError);
   fChain->SetBranchAddress("_KumaTOFBarrelCalibratedHits2_rawHit", &_KumaTOFBarrelCalibratedHits2_rawHit_, &b__KumaTOFBarrelCalibratedHits2_rawHit_);
   fChain->SetBranchAddress("_KumaTOFBarrelCalibratedHits2_rawHit.index", _KumaTOFBarrelCalibratedHits2_rawHit_index, &b__KumaTOFBarrelCalibratedHits2_rawHit_index);
   fChain->SetBranchAddress("_KumaTOFBarrelCalibratedHits2_rawHit.collectionID", _KumaTOFBarrelCalibratedHits2_rawHit_collectionID, &b__KumaTOFBarrelCalibratedHits2_rawHit_collectionID);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3", &KumaTOFBarrelCalibratedHits3_, &b_KumaTOFBarrelCalibratedHits3_);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.cellID", KumaTOFBarrelCalibratedHits3_cellID, &b_KumaTOFBarrelCalibratedHits3_cellID);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.position.x", KumaTOFBarrelCalibratedHits3_position_x, &b_KumaTOFBarrelCalibratedHits3_position_x);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.position.y", KumaTOFBarrelCalibratedHits3_position_y, &b_KumaTOFBarrelCalibratedHits3_position_y);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.position.z", KumaTOFBarrelCalibratedHits3_position_z, &b_KumaTOFBarrelCalibratedHits3_position_z);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.positionError.xx", KumaTOFBarrelCalibratedHits3_positionError_xx, &b_KumaTOFBarrelCalibratedHits3_positionError_xx);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.positionError.yy", KumaTOFBarrelCalibratedHits3_positionError_yy, &b_KumaTOFBarrelCalibratedHits3_positionError_yy);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.positionError.zz", KumaTOFBarrelCalibratedHits3_positionError_zz, &b_KumaTOFBarrelCalibratedHits3_positionError_zz);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.time", KumaTOFBarrelCalibratedHits3_time, &b_KumaTOFBarrelCalibratedHits3_time);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.timeError", KumaTOFBarrelCalibratedHits3_timeError, &b_KumaTOFBarrelCalibratedHits3_timeError);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.edep", KumaTOFBarrelCalibratedHits3_edep, &b_KumaTOFBarrelCalibratedHits3_edep);
   fChain->SetBranchAddress("KumaTOFBarrelCalibratedHits3.edepError", KumaTOFBarrelCalibratedHits3_edepError, &b_KumaTOFBarrelCalibratedHits3_edepError);
   fChain->SetBranchAddress("_KumaTOFBarrelCalibratedHits3_rawHit", &_KumaTOFBarrelCalibratedHits3_rawHit_, &b__KumaTOFBarrelCalibratedHits3_rawHit_);
   fChain->SetBranchAddress("_KumaTOFBarrelCalibratedHits3_rawHit.index", _KumaTOFBarrelCalibratedHits3_rawHit_index, &b__KumaTOFBarrelCalibratedHits3_rawHit_index);
   fChain->SetBranchAddress("_KumaTOFBarrelCalibratedHits3_rawHit.collectionID", _KumaTOFBarrelCalibratedHits3_rawHit_collectionID, &b__KumaTOFBarrelCalibratedHits3_rawHit_collectionID);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1", &KumaTOFBarrelClusterHits1_, &b_KumaTOFBarrelClusterHits1_);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.surface", KumaTOFBarrelClusterHits1_surface, &b_KumaTOFBarrelClusterHits1_surface);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.loc.a", KumaTOFBarrelClusterHits1_loc_a, &b_KumaTOFBarrelClusterHits1_loc_a);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.loc.b", KumaTOFBarrelClusterHits1_loc_b, &b_KumaTOFBarrelClusterHits1_loc_b);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.time", KumaTOFBarrelClusterHits1_time, &b_KumaTOFBarrelClusterHits1_time);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.covariance.xx", KumaTOFBarrelClusterHits1_covariance_xx, &b_KumaTOFBarrelClusterHits1_covariance_xx);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.covariance.yy", KumaTOFBarrelClusterHits1_covariance_yy, &b_KumaTOFBarrelClusterHits1_covariance_yy);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.covariance.zz", KumaTOFBarrelClusterHits1_covariance_zz, &b_KumaTOFBarrelClusterHits1_covariance_zz);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.covariance.xy", KumaTOFBarrelClusterHits1_covariance_xy, &b_KumaTOFBarrelClusterHits1_covariance_xy);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.covariance.xz", KumaTOFBarrelClusterHits1_covariance_xz, &b_KumaTOFBarrelClusterHits1_covariance_xz);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.covariance.yz", KumaTOFBarrelClusterHits1_covariance_yz, &b_KumaTOFBarrelClusterHits1_covariance_yz);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.weights_begin", KumaTOFBarrelClusterHits1_weights_begin, &b_KumaTOFBarrelClusterHits1_weights_begin);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.weights_end", KumaTOFBarrelClusterHits1_weights_end, &b_KumaTOFBarrelClusterHits1_weights_end);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.hits_begin", KumaTOFBarrelClusterHits1_hits_begin, &b_KumaTOFBarrelClusterHits1_hits_begin);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits1.hits_end", KumaTOFBarrelClusterHits1_hits_end, &b_KumaTOFBarrelClusterHits1_hits_end);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits1_hits", &_KumaTOFBarrelClusterHits1_hits_, &b__KumaTOFBarrelClusterHits1_hits_);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits1_hits.index", _KumaTOFBarrelClusterHits1_hits_index, &b__KumaTOFBarrelClusterHits1_hits_index);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits1_hits.collectionID", _KumaTOFBarrelClusterHits1_hits_collectionID, &b__KumaTOFBarrelClusterHits1_hits_collectionID);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits1_weights", &_KumaTOFBarrelClusterHits1_weights, &b__KumaTOFBarrelClusterHits1_weights);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2", &KumaTOFBarrelClusterHits2_, &b_KumaTOFBarrelClusterHits2_);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.surface", KumaTOFBarrelClusterHits2_surface, &b_KumaTOFBarrelClusterHits2_surface);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.loc.a", KumaTOFBarrelClusterHits2_loc_a, &b_KumaTOFBarrelClusterHits2_loc_a);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.loc.b", KumaTOFBarrelClusterHits2_loc_b, &b_KumaTOFBarrelClusterHits2_loc_b);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.time", KumaTOFBarrelClusterHits2_time, &b_KumaTOFBarrelClusterHits2_time);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.covariance.xx", KumaTOFBarrelClusterHits2_covariance_xx, &b_KumaTOFBarrelClusterHits2_covariance_xx);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.covariance.yy", KumaTOFBarrelClusterHits2_covariance_yy, &b_KumaTOFBarrelClusterHits2_covariance_yy);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.covariance.zz", KumaTOFBarrelClusterHits2_covariance_zz, &b_KumaTOFBarrelClusterHits2_covariance_zz);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.covariance.xy", KumaTOFBarrelClusterHits2_covariance_xy, &b_KumaTOFBarrelClusterHits2_covariance_xy);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.covariance.xz", KumaTOFBarrelClusterHits2_covariance_xz, &b_KumaTOFBarrelClusterHits2_covariance_xz);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.covariance.yz", KumaTOFBarrelClusterHits2_covariance_yz, &b_KumaTOFBarrelClusterHits2_covariance_yz);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.weights_begin", KumaTOFBarrelClusterHits2_weights_begin, &b_KumaTOFBarrelClusterHits2_weights_begin);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.weights_end", KumaTOFBarrelClusterHits2_weights_end, &b_KumaTOFBarrelClusterHits2_weights_end);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.hits_begin", KumaTOFBarrelClusterHits2_hits_begin, &b_KumaTOFBarrelClusterHits2_hits_begin);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits2.hits_end", KumaTOFBarrelClusterHits2_hits_end, &b_KumaTOFBarrelClusterHits2_hits_end);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits2_hits", &_KumaTOFBarrelClusterHits2_hits_, &b__KumaTOFBarrelClusterHits2_hits_);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits2_hits.index", _KumaTOFBarrelClusterHits2_hits_index, &b__KumaTOFBarrelClusterHits2_hits_index);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits2_hits.collectionID", _KumaTOFBarrelClusterHits2_hits_collectionID, &b__KumaTOFBarrelClusterHits2_hits_collectionID);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits2_weights", &_KumaTOFBarrelClusterHits2_weights, &b__KumaTOFBarrelClusterHits2_weights);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3", &KumaTOFBarrelClusterHits3_, &b_KumaTOFBarrelClusterHits3_);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.surface", KumaTOFBarrelClusterHits3_surface, &b_KumaTOFBarrelClusterHits3_surface);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.loc.a", KumaTOFBarrelClusterHits3_loc_a, &b_KumaTOFBarrelClusterHits3_loc_a);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.loc.b", KumaTOFBarrelClusterHits3_loc_b, &b_KumaTOFBarrelClusterHits3_loc_b);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.time", KumaTOFBarrelClusterHits3_time, &b_KumaTOFBarrelClusterHits3_time);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.covariance.xx", KumaTOFBarrelClusterHits3_covariance_xx, &b_KumaTOFBarrelClusterHits3_covariance_xx);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.covariance.yy", KumaTOFBarrelClusterHits3_covariance_yy, &b_KumaTOFBarrelClusterHits3_covariance_yy);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.covariance.zz", KumaTOFBarrelClusterHits3_covariance_zz, &b_KumaTOFBarrelClusterHits3_covariance_zz);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.covariance.xy", KumaTOFBarrelClusterHits3_covariance_xy, &b_KumaTOFBarrelClusterHits3_covariance_xy);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.covariance.xz", KumaTOFBarrelClusterHits3_covariance_xz, &b_KumaTOFBarrelClusterHits3_covariance_xz);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.covariance.yz", KumaTOFBarrelClusterHits3_covariance_yz, &b_KumaTOFBarrelClusterHits3_covariance_yz);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.weights_begin", KumaTOFBarrelClusterHits3_weights_begin, &b_KumaTOFBarrelClusterHits3_weights_begin);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.weights_end", KumaTOFBarrelClusterHits3_weights_end, &b_KumaTOFBarrelClusterHits3_weights_end);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.hits_begin", KumaTOFBarrelClusterHits3_hits_begin, &b_KumaTOFBarrelClusterHits3_hits_begin);
   fChain->SetBranchAddress("KumaTOFBarrelClusterHits3.hits_end", KumaTOFBarrelClusterHits3_hits_end, &b_KumaTOFBarrelClusterHits3_hits_end);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits3_hits", &_KumaTOFBarrelClusterHits3_hits_, &b__KumaTOFBarrelClusterHits3_hits_);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits3_hits.index", _KumaTOFBarrelClusterHits3_hits_index, &b__KumaTOFBarrelClusterHits3_hits_index);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits3_hits.collectionID", _KumaTOFBarrelClusterHits3_hits_collectionID, &b__KumaTOFBarrelClusterHits3_hits_collectionID);
   fChain->SetBranchAddress("_KumaTOFBarrelClusterHits3_weights", &_KumaTOFBarrelClusterHits3_weights, &b__KumaTOFBarrelClusterHits3_weights);
   fChain->SetBranchAddress("KumaTOFTracks", &KumaTOFTracks_, &b_KumaTOFTracks_);
   fChain->SetBranchAddress("KumaTOFTracks.surface", KumaTOFTracks_surface, &b_KumaTOFTracks_surface);
   fChain->SetBranchAddress("KumaTOFTracks.loc.a", KumaTOFTracks_loc_a, &b_KumaTOFTracks_loc_a);
   fChain->SetBranchAddress("KumaTOFTracks.loc.b", KumaTOFTracks_loc_b, &b_KumaTOFTracks_loc_b);
   fChain->SetBranchAddress("KumaTOFTracks.time", KumaTOFTracks_time, &b_KumaTOFTracks_time);
   fChain->SetBranchAddress("KumaTOFTracks.covariance.xx", KumaTOFTracks_covariance_xx, &b_KumaTOFTracks_covariance_xx);
   fChain->SetBranchAddress("KumaTOFTracks.covariance.yy", KumaTOFTracks_covariance_yy, &b_KumaTOFTracks_covariance_yy);
   fChain->SetBranchAddress("KumaTOFTracks.covariance.zz", KumaTOFTracks_covariance_zz, &b_KumaTOFTracks_covariance_zz);
   fChain->SetBranchAddress("KumaTOFTracks.covariance.xy", KumaTOFTracks_covariance_xy, &b_KumaTOFTracks_covariance_xy);
   fChain->SetBranchAddress("KumaTOFTracks.covariance.xz", KumaTOFTracks_covariance_xz, &b_KumaTOFTracks_covariance_xz);
   fChain->SetBranchAddress("KumaTOFTracks.covariance.yz", KumaTOFTracks_covariance_yz, &b_KumaTOFTracks_covariance_yz);
   fChain->SetBranchAddress("KumaTOFTracks.weights_begin", KumaTOFTracks_weights_begin, &b_KumaTOFTracks_weights_begin);
   fChain->SetBranchAddress("KumaTOFTracks.weights_end", KumaTOFTracks_weights_end, &b_KumaTOFTracks_weights_end);
   fChain->SetBranchAddress("KumaTOFTracks.hits_begin", KumaTOFTracks_hits_begin, &b_KumaTOFTracks_hits_begin);
   fChain->SetBranchAddress("KumaTOFTracks.hits_end", KumaTOFTracks_hits_end, &b_KumaTOFTracks_hits_end);
   fChain->SetBranchAddress("_KumaTOFTracks_hits", &_KumaTOFTracks_hits_, &b__KumaTOFTracks_hits_);
   fChain->SetBranchAddress("_KumaTOFTracks_hits.index", &_KumaTOFTracks_hits_index, &b__KumaTOFTracks_hits_index);
   fChain->SetBranchAddress("_KumaTOFTracks_hits.collectionID", &_KumaTOFTracks_hits_collectionID, &b__KumaTOFTracks_hits_collectionID);
   fChain->SetBranchAddress("_KumaTOFTracks_weights", &_KumaTOFTracks_weights, &b__KumaTOFTracks_weights);
   fChain->SetBranchAddress("GPIntKeys", &GPIntKeys, &b_GPIntKeys);
   fChain->SetBranchAddress("GPIntValues", &GPIntValues, &b_GPIntValues);
   fChain->SetBranchAddress("GPFloatKeys", &GPFloatKeys, &b_GPFloatKeys);
   fChain->SetBranchAddress("GPFloatValues", &GPFloatValues, &b_GPFloatValues);
   fChain->SetBranchAddress("GPDoubleKeys", &GPDoubleKeys, &b_GPDoubleKeys);
   fChain->SetBranchAddress("GPDoubleValues", &GPDoubleValues, &b_GPDoubleValues);
   fChain->SetBranchAddress("GPStringKeys", &GPStringKeys, &b_GPStringKeys);
   fChain->SetBranchAddress("GPStringValues", &GPStringValues, &b_GPStringValues);




   Notify();
}

Bool_t   trackEventDisplay::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void trackEventDisplay::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t trackEventDisplay::Cut(Long64_t entry)
{
   return 1;
}

// == e == MakeClass Default Functions == s ==




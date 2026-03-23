// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
// 2024/11/28 Template a macro to compile written by Kumaoka
// Please replace the name Algorithm to your analysis name, (anyname ok).
// And please search for the word "kuma example",
// You will find lines to need to modify
//
// Additionally, you need to modify Algorithm.cc and compile.C
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 

#ifndef trackEventDisplay_h
#define trackEventDisplay_h

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <string>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <TMath.h>
#include "Fit/Fitter.h"
#include <Math/Functor.h>

#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TProfile2D.h>
#include <TPolyLine3D.h>
#include <TPolyMarker3D.h>



#include <TApplication.h>
#include <TCanvas.h>
#include <TView.h>
#include <TAxis3D.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLatex.h>
#include <TMarker.h>
#include <TLine.h>

class trackEventDisplay {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any. 
   trackEventDisplay(TTree *tree=0, std::string iFileName="", std::string oFileName="");
   virtual ~trackEventDisplay();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   std::string fDir = "./";
   std::string iFileName = "";
   std::string oFileName = "";
   TFile *oFile; // output root file

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxKumaTOFBarrelCalibratedHits1 = 99999;
   static constexpr Int_t kMax_KumaTOFBarrelCalibratedHits1_rawHit = 99999;
   static constexpr Int_t kMaxKumaTOFBarrelCalibratedHits2 = 99999;
   static constexpr Int_t kMax_KumaTOFBarrelCalibratedHits2_rawHit = 99999;
   static constexpr Int_t kMaxKumaTOFBarrelCalibratedHits3 = 99999;
   static constexpr Int_t kMax_KumaTOFBarrelCalibratedHits3_rawHit = 99999;
   static constexpr Int_t kMaxKumaTOFBarrelClusterHits1 = 99999;
   static constexpr Int_t kMax_KumaTOFBarrelClusterHits1_hits = 99999;
   static constexpr Int_t kMaxKumaTOFBarrelClusterHits2 = 99999;
   static constexpr Int_t kMax_KumaTOFBarrelClusterHits2_hits = 99999;
   static constexpr Int_t kMaxKumaTOFBarrelClusterHits3 = 99999;
   static constexpr Int_t kMax_KumaTOFBarrelClusterHits3_hits = 99999;
   static constexpr Int_t kMaxKumaTOFTracks = 99999;
   static constexpr Int_t kMax_KumaTOFTracks_hits = 99999;

   // Declaration of leaf types
   Int_t           KumaTOFBarrelCalibratedHits1_;
   ULong_t         KumaTOFBarrelCalibratedHits1_cellID[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_position_x[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_position_y[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_position_z[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_positionError_xx[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_positionError_yy[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_positionError_zz[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_time[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_timeError[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_edep[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Float_t         KumaTOFBarrelCalibratedHits1_edepError[kMaxKumaTOFBarrelCalibratedHits1];   //[KumaTOFBarrelCalibratedHits1_]
   Int_t           _KumaTOFBarrelCalibratedHits1_rawHit_;
   Int_t           _KumaTOFBarrelCalibratedHits1_rawHit_index[kMax_KumaTOFBarrelCalibratedHits1_rawHit];   //[_KumaTOFBarrelCalibratedHits1_rawHit_]
   UInt_t          _KumaTOFBarrelCalibratedHits1_rawHit_collectionID[kMax_KumaTOFBarrelCalibratedHits1_rawHit];   //[_KumaTOFBarrelCalibratedHits1_rawHit_]
   Int_t           KumaTOFBarrelCalibratedHits2_;
   ULong_t         KumaTOFBarrelCalibratedHits2_cellID[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_position_x[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_position_y[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_position_z[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_positionError_xx[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_positionError_yy[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_positionError_zz[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_time[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_timeError[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_edep[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Float_t         KumaTOFBarrelCalibratedHits2_edepError[kMaxKumaTOFBarrelCalibratedHits2];   //[KumaTOFBarrelCalibratedHits2_]
   Int_t           _KumaTOFBarrelCalibratedHits2_rawHit_;
   Int_t           _KumaTOFBarrelCalibratedHits2_rawHit_index[kMax_KumaTOFBarrelCalibratedHits2_rawHit];   //[_KumaTOFBarrelCalibratedHits2_rawHit_]
   UInt_t          _KumaTOFBarrelCalibratedHits2_rawHit_collectionID[kMax_KumaTOFBarrelCalibratedHits2_rawHit];   //[_KumaTOFBarrelCalibratedHits2_rawHit_]
   Int_t           KumaTOFBarrelCalibratedHits3_;
   ULong_t         KumaTOFBarrelCalibratedHits3_cellID[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_position_x[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_position_y[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_position_z[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_positionError_xx[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_positionError_yy[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_positionError_zz[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_time[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_timeError[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_edep[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Float_t         KumaTOFBarrelCalibratedHits3_edepError[kMaxKumaTOFBarrelCalibratedHits3];   //[KumaTOFBarrelCalibratedHits3_]
   Int_t           _KumaTOFBarrelCalibratedHits3_rawHit_;
   Int_t           _KumaTOFBarrelCalibratedHits3_rawHit_index[kMax_KumaTOFBarrelCalibratedHits3_rawHit];   //[_KumaTOFBarrelCalibratedHits3_rawHit_]
   UInt_t          _KumaTOFBarrelCalibratedHits3_rawHit_collectionID[kMax_KumaTOFBarrelCalibratedHits3_rawHit];   //[_KumaTOFBarrelCalibratedHits3_rawHit_]
   Int_t           KumaTOFBarrelClusterHits1_;
   ULong_t         KumaTOFBarrelClusterHits1_surface[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Float_t         KumaTOFBarrelClusterHits1_loc_a[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Float_t         KumaTOFBarrelClusterHits1_loc_b[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Float_t         KumaTOFBarrelClusterHits1_time[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Float_t         KumaTOFBarrelClusterHits1_covariance_xx[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Float_t         KumaTOFBarrelClusterHits1_covariance_yy[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Float_t         KumaTOFBarrelClusterHits1_covariance_zz[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Float_t         KumaTOFBarrelClusterHits1_covariance_xy[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Float_t         KumaTOFBarrelClusterHits1_covariance_xz[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Float_t         KumaTOFBarrelClusterHits1_covariance_yz[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   UInt_t          KumaTOFBarrelClusterHits1_weights_begin[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   UInt_t          KumaTOFBarrelClusterHits1_weights_end[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   UInt_t          KumaTOFBarrelClusterHits1_hits_begin[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   UInt_t          KumaTOFBarrelClusterHits1_hits_end[kMaxKumaTOFBarrelClusterHits1];   //[KumaTOFBarrelClusterHits1_]
   Int_t           _KumaTOFBarrelClusterHits1_hits_;
   Int_t           _KumaTOFBarrelClusterHits1_hits_index[kMax_KumaTOFBarrelClusterHits1_hits];   //[_KumaTOFBarrelClusterHits1_hits_]
   UInt_t          _KumaTOFBarrelClusterHits1_hits_collectionID[kMax_KumaTOFBarrelClusterHits1_hits];   //[_KumaTOFBarrelClusterHits1_hits_]
   std::vector<float>   *_KumaTOFBarrelClusterHits1_weights;
   Int_t           KumaTOFBarrelClusterHits2_;
   ULong_t         KumaTOFBarrelClusterHits2_surface[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Float_t         KumaTOFBarrelClusterHits2_loc_a[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Float_t         KumaTOFBarrelClusterHits2_loc_b[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Float_t         KumaTOFBarrelClusterHits2_time[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Float_t         KumaTOFBarrelClusterHits2_covariance_xx[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Float_t         KumaTOFBarrelClusterHits2_covariance_yy[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Float_t         KumaTOFBarrelClusterHits2_covariance_zz[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Float_t         KumaTOFBarrelClusterHits2_covariance_xy[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Float_t         KumaTOFBarrelClusterHits2_covariance_xz[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Float_t         KumaTOFBarrelClusterHits2_covariance_yz[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   UInt_t          KumaTOFBarrelClusterHits2_weights_begin[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   UInt_t          KumaTOFBarrelClusterHits2_weights_end[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   UInt_t          KumaTOFBarrelClusterHits2_hits_begin[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   UInt_t          KumaTOFBarrelClusterHits2_hits_end[kMaxKumaTOFBarrelClusterHits2];   //[KumaTOFBarrelClusterHits2_]
   Int_t           _KumaTOFBarrelClusterHits2_hits_;
   Int_t           _KumaTOFBarrelClusterHits2_hits_index[kMax_KumaTOFBarrelClusterHits2_hits];   //[_KumaTOFBarrelClusterHits2_hits_]
   UInt_t          _KumaTOFBarrelClusterHits2_hits_collectionID[kMax_KumaTOFBarrelClusterHits2_hits];   //[_KumaTOFBarrelClusterHits2_hits_]
   std::vector<float>   *_KumaTOFBarrelClusterHits2_weights;
   Int_t           KumaTOFBarrelClusterHits3_;
   ULong_t         KumaTOFBarrelClusterHits3_surface[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Float_t         KumaTOFBarrelClusterHits3_loc_a[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Float_t         KumaTOFBarrelClusterHits3_loc_b[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Float_t         KumaTOFBarrelClusterHits3_time[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Float_t         KumaTOFBarrelClusterHits3_covariance_xx[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Float_t         KumaTOFBarrelClusterHits3_covariance_yy[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Float_t         KumaTOFBarrelClusterHits3_covariance_zz[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Float_t         KumaTOFBarrelClusterHits3_covariance_xy[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Float_t         KumaTOFBarrelClusterHits3_covariance_xz[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Float_t         KumaTOFBarrelClusterHits3_covariance_yz[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   UInt_t          KumaTOFBarrelClusterHits3_weights_begin[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   UInt_t          KumaTOFBarrelClusterHits3_weights_end[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   UInt_t          KumaTOFBarrelClusterHits3_hits_begin[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   UInt_t          KumaTOFBarrelClusterHits3_hits_end[kMaxKumaTOFBarrelClusterHits3];   //[KumaTOFBarrelClusterHits3_]
   Int_t           _KumaTOFBarrelClusterHits3_hits_;
   Int_t           _KumaTOFBarrelClusterHits3_hits_index[kMax_KumaTOFBarrelClusterHits3_hits];   //[_KumaTOFBarrelClusterHits3_hits_]
   UInt_t          _KumaTOFBarrelClusterHits3_hits_collectionID[kMax_KumaTOFBarrelClusterHits3_hits];   //[_KumaTOFBarrelClusterHits3_hits_]
   std::vector<float>   *_KumaTOFBarrelClusterHits3_weights;
   Int_t           KumaTOFTracks_;
   ULong_t         KumaTOFTracks_surface[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Float_t         KumaTOFTracks_loc_a[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Float_t         KumaTOFTracks_loc_b[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Float_t         KumaTOFTracks_time[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Float_t         KumaTOFTracks_covariance_xx[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Float_t         KumaTOFTracks_covariance_yy[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Float_t         KumaTOFTracks_covariance_zz[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Float_t         KumaTOFTracks_covariance_xy[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Float_t         KumaTOFTracks_covariance_xz[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Float_t         KumaTOFTracks_covariance_yz[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   UInt_t          KumaTOFTracks_weights_begin[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   UInt_t          KumaTOFTracks_weights_end[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   UInt_t          KumaTOFTracks_hits_begin[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   UInt_t          KumaTOFTracks_hits_end[kMaxKumaTOFTracks];   //[KumaTOFTracks_]
   Int_t           _KumaTOFTracks_hits_;
   Int_t           _KumaTOFTracks_hits_index[kMax_KumaTOFTracks_hits];   //[_KumaTOFTracks_hits_]
   UInt_t          _KumaTOFTracks_hits_collectionID[kMax_KumaTOFTracks_hits];   //[_KumaTOFTracks_hits_]


   std::vector<float>   *_KumaTOFTracks_weights;
   std::vector<std::string>  *GPIntKeys;
   std::vector<std::vector<int> > *GPIntValues;
   std::vector<std::string>  *GPFloatKeys;
   std::vector<std::vector<float> > *GPFloatValues;
   std::vector<std::string>  *GPDoubleKeys;
   std::vector<std::vector<double> > *GPDoubleValues;
   std::vector<std::string>  *GPStringKeys;
   std::vector<std::vector<std::string> > *GPStringValues;

   // List of branches
   TBranch        *b_KumaTOFBarrelCalibratedHits1_;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_cellID;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_position_x;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_position_y;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_position_z;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_positionError_xx;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_positionError_yy;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_positionError_zz;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_time;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_timeError;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_edep;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits1_edepError;   //!
   TBranch        *b__KumaTOFBarrelCalibratedHits1_rawHit_;   //!
   TBranch        *b__KumaTOFBarrelCalibratedHits1_rawHit_index;   //!
   TBranch        *b__KumaTOFBarrelCalibratedHits1_rawHit_collectionID;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_cellID;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_position_x;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_position_y;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_position_z;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_positionError_xx;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_positionError_yy;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_positionError_zz;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_time;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_timeError;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_edep;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits2_edepError;   //!
   TBranch        *b__KumaTOFBarrelCalibratedHits2_rawHit_;   //!
   TBranch        *b__KumaTOFBarrelCalibratedHits2_rawHit_index;   //!
   TBranch        *b__KumaTOFBarrelCalibratedHits2_rawHit_collectionID;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_cellID;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_position_x;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_position_y;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_position_z;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_positionError_xx;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_positionError_yy;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_positionError_zz;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_time;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_timeError;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_edep;   //!
   TBranch        *b_KumaTOFBarrelCalibratedHits3_edepError;   //!
   TBranch        *b__KumaTOFBarrelCalibratedHits3_rawHit_;   //!
   TBranch        *b__KumaTOFBarrelCalibratedHits3_rawHit_index;   //!
   TBranch        *b__KumaTOFBarrelCalibratedHits3_rawHit_collectionID;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_surface;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_loc_a;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_loc_b;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_time;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_covariance_xx;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_covariance_yy;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_covariance_zz;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_covariance_xy;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_covariance_xz;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_covariance_yz;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_weights_begin;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_weights_end;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_hits_begin;   //!
   TBranch        *b_KumaTOFBarrelClusterHits1_hits_end;   //!
   TBranch        *b__KumaTOFBarrelClusterHits1_hits_;   //!
   TBranch        *b__KumaTOFBarrelClusterHits1_hits_index;   //!
   TBranch        *b__KumaTOFBarrelClusterHits1_hits_collectionID;   //!
   TBranch        *b__KumaTOFBarrelClusterHits1_weights;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_surface;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_loc_a;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_loc_b;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_time;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_covariance_xx;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_covariance_yy;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_covariance_zz;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_covariance_xy;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_covariance_xz;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_covariance_yz;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_weights_begin;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_weights_end;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_hits_begin;   //!
   TBranch        *b_KumaTOFBarrelClusterHits2_hits_end;   //!
   TBranch        *b__KumaTOFBarrelClusterHits2_hits_;   //!
   TBranch        *b__KumaTOFBarrelClusterHits2_hits_index;   //!
   TBranch        *b__KumaTOFBarrelClusterHits2_hits_collectionID;   //!
   TBranch        *b__KumaTOFBarrelClusterHits2_weights;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_surface;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_loc_a;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_loc_b;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_time;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_covariance_xx;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_covariance_yy;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_covariance_zz;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_covariance_xy;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_covariance_xz;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_covariance_yz;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_weights_begin;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_weights_end;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_hits_begin;   //!
   TBranch        *b_KumaTOFBarrelClusterHits3_hits_end;   //!
   TBranch        *b__KumaTOFBarrelClusterHits3_hits_;   //!
   TBranch        *b__KumaTOFBarrelClusterHits3_hits_index;   //!
   TBranch        *b__KumaTOFBarrelClusterHits3_hits_collectionID;   //!
   TBranch        *b__KumaTOFBarrelClusterHits3_weights;   //!
   TBranch        *b_KumaTOFTracks_;   //!
   TBranch        *b_KumaTOFTracks_surface;   //!
   TBranch        *b_KumaTOFTracks_loc_a;   //!
   TBranch        *b_KumaTOFTracks_loc_b;   //!
   TBranch        *b_KumaTOFTracks_time;   //!
   TBranch        *b_KumaTOFTracks_covariance_xx;   //!
   TBranch        *b_KumaTOFTracks_covariance_yy;   //!
   TBranch        *b_KumaTOFTracks_covariance_zz;   //!
   TBranch        *b_KumaTOFTracks_covariance_xy;   //!
   TBranch        *b_KumaTOFTracks_covariance_xz;   //!
   TBranch        *b_KumaTOFTracks_covariance_yz;   //!
   TBranch        *b_KumaTOFTracks_weights_begin;   //!
   TBranch        *b_KumaTOFTracks_weights_end;   //!
   TBranch        *b_KumaTOFTracks_hits_begin;   //!
   TBranch        *b_KumaTOFTracks_hits_end;   //!
   TBranch        *b__KumaTOFTracks_hits_;   //!
   TBranch        *b__KumaTOFTracks_hits_index;   //!
   TBranch        *b__KumaTOFTracks_hits_collectionID;   //!
   TBranch        *b__KumaTOFTracks_weights;   //!
   TBranch        *b_GPIntKeys;   //!
   TBranch        *b_GPIntValues;   //!
   TBranch        *b_GPFloatKeys;   //!
   TBranch        *b_GPFloatValues;   //!
   TBranch        *b_GPDoubleKeys;   //!
   TBranch        *b_GPDoubleValues;   //!
   TBranch        *b_GPStringKeys;   //!
   TBranch        *b_GPStringValues;   //!

   // public member valuables
   std::vector<Int_t> m_vTargetEvents;
   Int_t m_pubEvNum = 0;

   // black, blue, red, green, violet, orange, light blue, light green, dark violet, brown, very light blue, 
   // yellow green, week red, dark blue, week green, dark cyan, dark orange, 
   Int_t m_myHistColors[18] = {4, 600, 632, 419, 880, 807, 867, 909, 814, 874, 635, 870, 824, 625, 602, 417, 434, 802}; // colors for histograms
   
   // TOFBarrelRecHits, TOFEndcapRecHits, BackwardMPGDEndcapRecHits, ForwardMPGDEndcapRecHits, MPGDBarrelRecHits, OuterMPGDBarrelRecHits, SiBarrelVertexRecHits, SiBarrelTrackerRecHits, SiEndcapTrackerRecHits
   Int_t m_TrackDetColors[9] = {880+10, 880+10, 880-2, 880-2, 880-2, 880-2, 880+4, 880+2, 880+2};
   // B0TrackerRecHits, ,  EcalBarrelScFiClusters, EcalEndcapNClusters, EcalEndcapPClusters, EcalFarForwardZDCClusters, EcalLumiSpecClusters, ForwardRomanPotRecHits, LFHCALClusters
   Int_t m_CalDetColors[8] = {860-3, 840-3, 600-9, 600-9, 880+1, 860+10, 880-6, 600-3};
   // B0ECalClusters:  860+7, ,EcalBarrelClusters: 880-4, EcalBarrelImagingClusters: 600-7
   // DIRCRawHits, DRICHRawHits, 
   Int_t m_PIDDetColors[2] = {860-6, 860};


   // histograms as output
   TH2D* m_hEventDisplayZR;

   
   // == member functions == // own function
   void HistInit();
   void WriteHists();
   

   int checkCount = 0;





   // === s === For Event Display ===========

   struct Vec3 {
      double x{};
      double y{};
      double z{};
   };

   struct Particle {
      Vec3 vertex;
      Vec3 momentum;
      Vec3 endpoint;
      int pdg{};
      double charge{};
      bool hasEndpoint{false};

      std::vector<int> parents;
      std::vector<int> daughters;
   };

   struct Event {
      std::vector<Particle> particles;
   };

   double mag(const Vec3& v) {
      return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
   }

   Vec3 normalize(const Vec3& v) {
      const double m = mag(v);
      if (m < 1e-12) return {0.0, 0.0, 0.0};
      return {v.x / m, v.y / m, v.z / m};
   }

   Vec3 add(const Vec3& a, const Vec3& b) {
      return {a.x + b.x, a.y + b.y, a.z + b.z};
   }

   Vec3 sub(const Vec3& a, const Vec3& b) {
      return {a.x - b.x, a.y - b.y, a.z - b.z};
   }

   Vec3 scale(const Vec3& v, double s) {
      return {v.x * s, v.y * s, v.z * s};
   }

   int colorFromPDG(int pdg) {
      const int apdg = std::abs(pdg);
      if (apdg == 11)   return kAzure + 1;    // e
      if (apdg == 13)   return kGreen + 2;    // mu
      if (apdg == 211)  return kRed + 1;      // pi
      if (apdg == 321)  return kOrange + 7;   // K
      if (apdg == 2212) return kMagenta + 1;  // proton
      if (apdg == 22)   return kYellow + 1;   // gamma
      if (apdg == 2112) return kGray + 2;     // neutron
      return kWhite;
   }

   Vec3 getTrackEnd(const Particle& p, double fallbackLength = 300.0) {
      if (p.hasEndpoint) {
         return p.endpoint;
      }

      const Vec3 dir = normalize(p.momentum);
      if (mag(dir) < 1e-12) {
         return p.vertex;
      }
      return add(p.vertex, scale(dir, fallbackLength));
   }

   void computeEventBounds(
      const Event& ev,
      double& xmin, double& xmax,
      double& ymin, double& ymax,
      double& zmin, double& zmax,
      double fallbackLength = 300.0
   ) {
      bool first = true;

      for (const auto& p : ev.particles) {
         const Vec3 a = p.vertex;
         const Vec3 b = getTrackEnd(p, fallbackLength);

         const Vec3 pts[2] = {a, b};
         for (const auto& q : pts) {
            if (first) {
               xmin = xmax = q.x;
               ymin = ymax = q.y;
               zmin = zmax = q.z;
               first = false;
            } else {
               xmin = std::min(xmin, q.x);
               xmax = std::max(xmax, q.x);
               ymin = std::min(ymin, q.y);
               ymax = std::max(ymax, q.y);
               zmin = std::min(zmin, q.z);
               zmax = std::max(zmax, q.z);
            }
         }
      }

      if (first) {
         xmin = ymin = zmin = -1.0;
         xmax = ymax = zmax =  1.0;
         return;
      }

      const double dx = xmax - xmin;
      const double dy = ymax - ymin;
      const double dz = zmax - zmin;
      const double margin = 0.15;

      xmin -= std::max(dx * margin, 1.0);
      xmax += std::max(dx * margin, 1.0);
      ymin -= std::max(dy * margin, 1.0);
      ymax += std::max(dy * margin, 1.0);
      zmin -= std::max(dz * margin, 1.0);
      zmax += std::max(dz * margin, 1.0);
   }

   std::vector<Event> m_eventsForED;

   Int_t numOfED = 8;
   TH3D* m_hEventDisplays[8];
   Int_t m_iDisplayCount = 0;

   std::vector<std::vector<std::vector<Vec3> > > m_vRecordedCalibDetHits;
   std::vector<std::vector<std::vector<Vec3> > > m_vRecordedClustDetHits;

   void recordEventsForED();
   void drawOneEvent(const Event& ev, int eventIndex, double fallbackLength = 300.0);
   void drawEightEvents(double fallbackLength = 300.0);

   TH2D* m_hEventDisplays2D[8];
   void drawOneEvent2D_ZX(const Event& ev, int eventIndex, double fallbackLength = 300.0);
   void drawEightEvents2D_ZX(double fallbackLength = 300.0);
   
   // === e === For Event Display ===========


};

#endif

// #ifndef triggerCombineChecker_cxx
// #define triggerCombineChecker_cxx


// #endif // #ifdef triggerCombineChecker_cxx







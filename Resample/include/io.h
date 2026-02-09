#pragma once

//ROOT
#include "ROOT/RVec.hxx"
#include "Math/Vector4D.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TInterpreter.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

//internal
#include "logging.h"

namespace io {


  template<typename H>
  inline H read(TFile * f, std::string const hist_name) {
  
    ASSERT(f != nullptr);
  
    H * hist = f->Get<H>(hist_name.c_str());
  
    if(! hist)
      ERROR(hist_name + " not found");

    H * hist_clone = static_cast<H *>(hist->Clone());

    hist_clone->SetDirectory(0);
  
    return std::move(* hist_clone);
  
  }
  
  template<typename H>
  inline void write(TFile * f, H * hist) {
  
    ASSERT(f != nullptr);
    ASSERT(hist != nullptr);
  
    f->cd();
  
    H * hist_clone = static_cast<H *>(hist->Clone());
    hist_clone->SetDirectory(f);
  
    hist_clone->Write(hist_clone->GetName(), TObject::kOverwrite);
  
    delete hist_clone;
  
  }

}



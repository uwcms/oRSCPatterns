// system include files
#include <memory>
#include <iostream>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegion.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloEmCand.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegionDetId.h"

#include "L1Trigger/UCT2015/interface/OrscLinks.h"


class OrscLinkPatterns : public edm::EDAnalyzer {
  public :
    explicit OrscLinkPatterns(const edm::ParameterSet&);
    ~OrscLinkPatterns();


  private:
    virtual void beginJob();
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    edm::Handle<L1CaloRegionCollection> newRegions;
    edm::Handle<L1CaloEmCollection> newEMCands;

    std::ofstream outfile;
};


OrscLinkPatterns::OrscLinkPatterns(const edm::ParameterSet& iConfig) {
}


OrscLinkPatterns::~OrscLinkPatterns() {
}


void
OrscLinkPatterns::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;

  iEvent.getByLabel("uctDigis", newRegions);
  iEvent.getByLabel("uctDigis", newEMCands);

  OrscLinks links;

  for (L1CaloRegionCollection::const_iterator newRegion = newRegions->begin();
      newRegion != newRegions->end(); newRegion++) {
    links.addRegion(*newRegion);
  }

  for (L1CaloEmCollection::const_iterator egtCand = newEMCands->begin();
      egtCand != newEMCands->end(); egtCand++) {
    links.addEM(*egtCand);
  }
}


void
OrscLinkPatterns::beginJob() {
  outfile.open("example.txt");
}


void
OrscLinkPatterns::endJob() {
  outfile.close();
}


DEFINE_FWK_MODULE(OrscLinkPatterns);

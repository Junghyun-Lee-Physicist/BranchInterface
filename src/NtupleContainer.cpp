#include "NtupleContainer.hpp"
#include <iostream>

namespace ttHH_TrigNbTag {
	
    void NtupleContainer::SetBranchAddresses(TTree* tree) {
    
        tree_ = tree;
    
        if (!tree) {
            std::cerr << "[TrigEffNSFs_BranchInterface] Null TTree pointer!" << std::endl;
            return;
        }
    
        // MakeClass mode for C-style arrays
        tree_->SetMakeClass(1);
    
        tree_->SetBranchAddress("passTrigger_HLT_IsoMu27",  &passTrigger_HLT_IsoMu27,  &b_passTrigger_HLT_IsoMu27);
        tree_->SetBranchAddress("passTrigger_HLT_PFHT1050", &passTrigger_HLT_PFHT1050, &b_passTrigger_HLT_PFHT1050);
        tree_->SetBranchAddress("passTrigger_6J1T_B",       &passTrigger_6J1T_B,       &b_passTrigger_6J1T_B);
        tree_->SetBranchAddress("passTrigger_6J1T_CDEF",    &passTrigger_6J1T_CDEF,    &b_passTrigger_6J1T_CDEF);
        tree_->SetBranchAddress("passTrigger_6J2T_B",       &passTrigger_6J2T_B,       &b_passTrigger_6J2T_B);
        tree_->SetBranchAddress("passTrigger_6J2T_CDEF",    &passTrigger_6J2T_CDEF,    &b_passTrigger_6J2T_CDEF);
        tree_->SetBranchAddress("passTrigger_4J3T_B",       &passTrigger_4J3T_B,       &b_passTrigger_4J3T_B);
        tree_->SetBranchAddress("passTrigger_4J3T_CDEF",    &passTrigger_4J3T_CDEF,    &b_passTrigger_4J3T_CDEF);
    
        tree_->SetBranchAddress("nMuons",  &nMuons,  &b_nMuons);
        tree_->SetBranchAddress("nElecs",  &nElecs,  &b_nElecs);
        tree_->SetBranchAddress("nJets",   &nJets,   &b_nJets);
        tree_->SetBranchAddress("HT",      &HT,      &b_HT);
    
        tree_->SetBranchAddress("jetPt",    jetPt,    &b_jetPt);
        tree_->SetBranchAddress("jetEta",   jetEta,   &b_jetEta);
        tree_->SetBranchAddress("bTagScore", bTagScore, &b_bTagScore);
    
        tree_->SetBranchAddress("hadFlavs", hadFlavs, &b_hadFlavs);
        tree_->SetBranchAddress("eventNumber",    &eventNumber,    &b_eventNumber);
        tree_->SetBranchAddress("runNumber",      &runNumber,      &b_runNumber);
        tree_->SetBranchAddress("PUWeight",       &PUWeight,       &b_PUWeight);
        tree_->SetBranchAddress("L1PrefiringWeight", &L1PrefiringWeight, &b_L1PrefiringWeight);
        tree_->SetBranchAddress("failGoldenJson", &failGoldenJson, &b_failGoldenJson);
        tree_->SetBranchAddress("passMETFilters", &passMETFilters, &b_passMETFilters);
    
    }

} // namespace ttHH_TrigNbTag

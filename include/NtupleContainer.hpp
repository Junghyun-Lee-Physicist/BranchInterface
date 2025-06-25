#ifndef NtupleContainer_hpp
#define NtupleContainer_hpp

#include <TTree.h>
#include <Rtypes.h> // Bool_t, Int_t, Float_t

namespace ttHH_TrigNbTag {

    class NtupleContainer {
    
      public:
      
        // Trigger bits
        Bool_t passTrigger_HLT_IsoMu27{false};
        Bool_t passTrigger_HLT_PFHT1050{false};
        Bool_t passTrigger_6J1T_B{false}, passTrigger_6J1T_CDEF{false};
        Bool_t passTrigger_6J2T_B{false}, passTrigger_6J2T_CDEF{false};
        Bool_t passTrigger_4J3T_B{false}, passTrigger_4J3T_CDEF{false};
    
        // Object counts
        Int_t  nMuons{-5}, nElecs{-5}, nJets{-5}, nbJets{-5};
        
        // Kinematics
        Float_t HT{-100.0};
        static const int MAX_JETS = 30;
        Float_t jetPt[MAX_JETS]{-100.0};
        Float_t jetEta[MAX_JETS]{-100.0};
        Float_t bTagScore[MAX_JETS]{-20.0};
        Int_t   hadFlavs[MAX_JETS]{-5};
    
        // Event meta-data
        UInt_t  eventNumber{1};
        UInt_t  runNumber{1};
    
        // Weights & filters
        Float_t PUWeight{-50000.0}, L1PrefiringWeight{-50000.0};
        Bool_t failGoldenJson{true}, passMETFilters{false};
    
        TBranch* b_passTrigger_HLT_IsoMu27{};
        TBranch* b_passTrigger_HLT_PFHT1050{};
        TBranch* b_passTrigger_6J1T_B{};
        TBranch* b_passTrigger_6J1T_CDEF{};
        TBranch* b_passTrigger_6J2T_B{};
        TBranch* b_passTrigger_6J2T_CDEF{};
        TBranch* b_passTrigger_4J3T_B{};
        TBranch* b_passTrigger_4J3T_CDEF{};
     
        TBranch* b_nMuons{};
        TBranch* b_nElecs{};
        TBranch* b_nJets{};
        TBranch* b_nbJets{};
     
        TBranch* b_HT{};
     
        TBranch* b_jetPt{};
        TBranch* b_jetEta{};
        TBranch* b_bTagScore{};
        TBranch* b_hadFlavs{};
        TBranch* b_partonFlavs{};
     
        TBranch* b_eventNumber{};
        TBranch* b_runNumber{};
     
        TBranch* b_PUWeight{};
        TBranch* b_L1PrefiringWeight{};
        TBranch* b_failGoldenJson{};
        TBranch* b_passMETFilters{};
     
        // Bind all branches of the tree to this ntuple container
        void SetBranchAddresses(TTree* tree);
    
        // Enable internal debug prints
        void SetDebug(bool dbg) { debug_ = dbg; }
    
      private:
    
        TTree* tree_{nullptr};
        bool   debug_{false};
    
    };

} // namespace ttHH_TrigNbTag

#endif

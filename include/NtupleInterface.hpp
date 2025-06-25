
#ifndef NtupleInterface_hpp
#define NtupleInterface_hpp

#include <string>
#include <TFile.h>
#include <TTree.h>
#include <memory>
#include <iostream>

template<typename NtupleContainerT>
class NtupleInterface {

public:
    explicit NtupleInterface(bool debug = false)
        : file_{nullptr},
          tree_{nullptr},
          ntuplePayload_{std::make_unique<NtupleContainerT>()},
	  debug_{debug}
    {}

    ~NtupleInterface(){
        CloseNtuple();
        if (debug_) std::cout << "[NtupleInterface] Destructor invoked - cleaning up TFile and TTree.\n";
    }

    bool OpenNtuple(const std::string& fileName, const std::string& treeName){
        if (file_) CloseNtuple();
        file_ = TFile::Open(fileName.c_str());
        if (!file_ || file_->IsZombie()) {
            std::cerr << "[NtupleInterface] Failed to open '" 
                      << fileName << "'\n";
            file_ = nullptr;
            return false;
        }
        tree_ = dynamic_cast<TTree*>(file_->Get(treeName.c_str()));
        if (!tree_) {
            std::cerr << "[NtupleInterface] Tree '" << treeName
                      << "' not found in '" << fileName << "'\n";
            file_->Close();
            file_ = nullptr;
            return false;
        }
        ntuplePayload_->SetDebug(debug_);
        ntuplePayload_->SetBranchAddresses(tree_);
        if (debug_) std::cout << "[NtupleInterface] Opened "
                              << fileName << "/" << treeName << "\n";
        return true;
    }

    Long64_t          GetNumberOfEntries() const{
        return tree_ ? tree_->GetEntries() : 0;
    }

    NtupleContainerT* GetNtupleContainer(Long64_t entry){
        if (!tree_) {
            if (debug_) std::cout << "[NtupleInterface] Tree not open\n";
            return nullptr;
        }
        Long64_t n = tree_->GetEntries();
        if (entry < 0 || entry >= n) {
            if (debug_) std::cout << "[NtupleInterface] Entry "
                                  << entry << " out of range\n";
            return nullptr;
        }
        tree_->GetEntry(entry);
        return ntuplePayload_.get();
    }

    void DisableBranch(const std::string& branchName) {
        if (tree_) tree_->SetBranchStatus(branchName.c_str(), 0);
        if (debug_) std::cout << "[NtupleInterface] Disabled branch: '"
                              << branchName << "'\n";
    }

    void EnableBranch(const std::string& branchName) {
        if (tree_) tree_->SetBranchStatus(branchName.c_str(), 1);
        if (debug_) std::cout << "[NtupleInterface] Enabled branch: '"
                              << branchName << "'\n";
    }

    void CloseNtuple() {
        if (file_) {
            if (debug_) std::cout << "[NtupleInterface] Closing file and cleaning up\n";
            file_->Close();
            delete file_;
            file_ = nullptr;
        }
        tree_ = nullptr;
    }

private:
    TFile*                            file_;
    TTree*                            tree_;
    std::unique_ptr<NtupleContainerT> ntuplePayload_;
    bool                              debug_;

};

#endif

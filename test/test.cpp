#include <iostream>
#include "NtupleInterface.hpp"
#include "NtupleContainer.hpp"

int main() {

    auto* ni = new NtupleInterface<ttHH_TrigNbTag::NtupleContainer>(true);
    if (!ni->OpenNtuple("sample/testSample_ttHH.root", "Tree/Tree")) {
	delete ni;
        return 1;
    }

    Long64_t nEntries = ni->GetNumberOfEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        auto* ev = ni->GetNtupleContainer(i);
	if (!ev) continue;
        std::cout << "Event " << i
                  << ": nJets=" << ev->nJets
                  << ", HT=" << ev->HT << "\n";
    }

    ni->CloseNtuple();
    delete ni;
    return 0;
}

# Branch Interface

## 1. Library Build

In the project root directory, run:

```bash
make                      # builds static library by default (lib/libBranchInterface.a)
# or
make LIBTYPE=shared       # builds shared library      (lib/libBranchInterface.so)
make clean                # removes all build artifacts
```

## 2. Environment Setup

Source the helper script to export include and library paths:

```bash
# for static linking
source env_setup.sh static

# or for shared linking
source env_setup.sh shared
```
This will:
	•  Add include/ to your C++ include search path
	•  Add lib/ to your linker search path (LIBRARY_PATH for static, LD_LIBRARY_PATH for shared)

You do not need to pass -I or -L manually when compiling after this.

## 3. Writing a Container

Create a header—for example include/MyContainer.hpp—that matches your ROOT TTree branches:
```cpp
#pragma once
#include <TTree.h>
#include <Rtypes.h>
#include <iostream>

class MyContainer {
public:
  // Declare a data member for each branch
  Int_t   nJets{};
  Float_t HT{};
  static const int MAX_JETS = 30;
  Float_t jetPt[MAX_JETS]{};

  // Bind branches to these members
  void SetBranchAddresses(TTree* tree) {
    tree->SetMakeClass(1);
    tree->SetBranchAddress("nJets", &nJets);
    tree->SetBranchAddress("HT",    &HT);
    tree->SetBranchAddress("jetPt", jetPt);
  }

  // Enable debug logging
  void SetDebug(bool debug) {
    if (debug) std::cout << "[MyContainer] Debug ON\n";
  }
};
```

## 4. Using the Interface
Write your application (e.g. test/test.cpp):
```cpp
#include "MyContainer.hpp"
#include "NtupleInterface.hpp"
#include <iostream>

int main() {
    // Pass `true` to enable debug logging
    NtupleInterface<MyContainer> ni(/*debug=*/true);

    // Open file and bind branches
    if (!ni.OpenNtuple("ttHH_0.root", "Tree/Tree"))
        return 1;

    // Loop over entries
    Long64_t nEntries = ni.GetNumberOfEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        MyContainer* ev = ni.GetNtupleContainer(i);
        if (!ev) continue;

        // Access branch values
        std::cout << "Event " << i
                  << ": nJets=" << ev->nJets
                  << ", HT="   << ev->HT   << "\n";
    }

    // Close file and free resources
    ni.CloseNtuple();
    return 0;
}
```

## 5. Compile and Link

From the test/ directory, run:
```bash
make
# or
Or compile manually:
g++ -std=c++17 -Wall -O2 \
    $(root-config --cflags) \
    -Iinclude \
    test.cpp \
    -Llib -lBranchInterface \
    $(root-config --libs) \
    -o test_app
```
	• $(root-config --cflags) adds ROOT include paths
	• $(root-config --libs) adds ROOT libraries
	• -lBranchInterface links your Branch Interface library

Then execute:
```bash
./test_app
```
Debug messages will print if you passed true to the constructor.


## 6. Developer Guide
Architecture
	•	Interface (include/NtupleInterface.hpp):
	•	A header‐only template class NtupleInterface<ContainerT>
	•	No recompilation needed when you add or modify containers
	•	Container (e.g. include/MyContainer.hpp):
	•	Defines data members for each TTree branch
	•	Implements SetBranchAddresses(TTree*) and SetDebug(bool)

Workflow
	1.	Define a new container to match your ntuple’s branches.
	2.	Include your container header and NtupleInterface.hpp in your application.
	3.	Instantiate:
```cpp
NtupleInterface<MyContainer> ni(debugFlag);
```

   	4.	Open the file and bind branches:
```cpp
ni.OpenNtuple("myFile.root", "MyTreeName");
```

	5.	Loop over entries using GetNumberOfEntries() and GetNtupleContainer(i).
	6.	Close with CloseNtuple() (optional—destructor also cleans up).

Why Header-Only?
	•	Templates must have their definitions visible at instantiation time.
	•	Placing all code in the header eliminates the need for explicit instantiation or separate builds.
	•	You can freely mix and match containers without touching the interface code.

⸻

With this setup, the interface code remains untouched as you develop new ntuple layouts—simply write a new container and plug it into NtupleInterface<YourContainer>. Happy analyzing!


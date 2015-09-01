//===---------------------- SymbolicRangeAnalysis.cpp ---------------------===//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "sra"

#include "SAGE/Python/PythonInterface.h"

#include "SymbolicRangeAnalysis.h"
#include "Redefinition.h"

#include "llvm/Support/Debug.h"

raw_ostream& operator<<(raw_ostream& OS, const SymbolicRangeAnalysis& SRR) {
  SRR.print(OS, nullptr);
  return OS;
}

using namespace llvm;

static RegisterPass<SymbolicRangeAnalysis>
  X("sra", "Symbolic range analysis with SAGE and QEPCAD");
char SymbolicRangeAnalysis::ID = 0;

void SymbolicRangeAnalysis::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<PythonInterface>();
  AU.addRequired<Redefinition>();
  AU.setPreservesAll();
}

bool SymbolicRangeAnalysis::runOnFunction(Function& F) {
  DEBUG(dbgs() << "SRA: runOnFunction: " << F.getName() << "\n");
  G_ = new SRAGraph(&F, getAnalysis<Redefinition>(), SNV_);
  return false;
}

SAGERange SymbolicRangeAnalysis::getRange(Value *V) {
  return G_->getRange(V);
}


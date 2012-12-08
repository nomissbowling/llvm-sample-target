//=== SampleInstPrinter.h - Convert Sample MCInst to assembly syntax -*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints a Sample MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#ifndef SAMPLEINSTPRINTER_H
#define SAMPLEINSTPRINTER_H
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/Support/Debug.h"

namespace llvm {
// These enumeration declarations were orignally in SampleInstrInfo.h but
// had to be moved here to avoid circular dependencies between
// LLVMSampleCodeGen and LLVMSampleAsmPrinter.
class TargetMachine;

class SampleInstPrinter : public MCInstPrinter {
public:
  SampleInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                  const MCRegisterInfo &MRI)
    : MCInstPrinter(MAI, MII, MRI) {}

  // Autogenerated by tblgen.
  void printInstruction(const MCInst *MI, raw_ostream &O);
  static const char *getRegisterName(unsigned RegNo);

  // must implement
  virtual void printRegName(raw_ostream &OS, unsigned RegNo) const /*override*/;
  virtual void printInst(const MCInst *MI, raw_ostream &O, StringRef Annot) /*override*/;

private:
  // used in printInstruction
  void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printMemOperand(const MCInst *MI, int opNum, raw_ostream &O);
};
} // end namespace llvm

#endif
//===-- SampleInstrInfo.cpp - Sample Instruction Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Sample implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "SampleInstrInfo.h"
#include "SampleTargetMachine.h"
#include "SampleMachineFunction.h"
#include "MCTargetDesc/SampleMCTargetDesc.h"
#include "InstPrinter/SampleInstPrinter.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/ADT/STLExtras.h"

#define GET_INSTRINFO_CTOR
#include "SampleGenInstrInfo.inc"

using namespace llvm;

SampleInstrInfo::SampleInstrInfo(SampleTargetMachine &tm)
  : SampleGenInstrInfo(),
    TM(tm),
    RI(*this){}

const SampleRegisterInfo &SampleInstrInfo::getRegisterInfo() const {
  return RI;
}

/// isLoadFromStackSlot - If the specified machine instruction is a direct
/// load from a stack slot, return the virtual or physical register number of
/// the destination along with the FrameIndex of the loaded stack slot.  If
/// not, return 0.  This predicate must return 0 if the instruction has
/// any side effects other than loading from the stack slot.
unsigned SampleInstrInfo::
isLoadFromStackSlot(const MachineInstr *MI, int &FrameIndex) const
{
  llvm_unreachable("not implemented");
  return 0;
}

/// isStoreToStackSlot - If the specified machine instruction is a direct
/// store to a stack slot, return the virtual or physical register number of
/// the source reg along with the FrameIndex of the loaded stack slot.  If
/// not, return 0.  This predicate must return 0 if the instruction has
/// any side effects other than storing to the stack slot.
unsigned SampleInstrInfo::
isStoreToStackSlot(const MachineInstr *MI, int &FrameIndex) const
{
  llvm_unreachable("not implemented");
  return 0;
}

void SampleInstrInfo::
copyPhysReg(MachineBasicBlock &MBB,
            MachineBasicBlock::iterator I, DebugLoc DL,
            unsigned DestReg, unsigned SrcReg,
            bool KillSrc) const {
  unsigned Opc = 0, ZeroReg = 0;
  Opc = Sample::ADD, ZeroReg = Sample::ZERO;

  MachineInstrBuilder MIB = BuildMI(MBB, I, DL, get(Opc));

  if (DestReg)
    MIB.addReg(DestReg, RegState::Define);

  if (ZeroReg)
    MIB.addReg(ZeroReg);

  if (SrcReg)
    MIB.addReg(SrcReg, getKillRegState(KillSrc));
}

void SampleInstrInfo::
storeRegToStackSlot(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                    unsigned SrcReg, bool isKill, int FI,
                    const TargetRegisterClass *RC,
                    const TargetRegisterInfo *TRI) const {
  DEBUG(dbgs() << ">> SampleInstrInfo::storeRegToStackSlot <<\n");
}

void SampleInstrInfo::
loadRegFromStackSlot(MachineBasicBlock &MBB,
                     MachineBasicBlock::iterator MI,
                     unsigned DestReg, int FI,
                     const TargetRegisterClass *RC,
                     const TargetRegisterInfo *TRI) const
{
  DEBUG(dbgs() << ">> SampleInstrInfo::loadRegFromStackSlot <<\n");

  DebugLoc DL;
  if (MI != MBB.end()) DL = MI->getDebugLoc();
  MachineFunction &MF = *MBB.getParent();
  MachineFrameInfo &MFI = *MF.getFrameInfo();

  MachineMemOperand *MMO =
    MF.getMachineMemOperand(MachinePointerInfo::getFixedStack(FI),
                            MachineMemOperand::MOLoad,
                            MFI.getObjectSize(FI),
                            MFI.getObjectAlignment(FI));

  BuildMI(MBB, MI, DL, get(Sample::LOAD))
      .addReg(DestReg).addFrameIndex(FI).addImm(0).addMemOperand(MMO);
}

//===----------------------------------------------------------------------===//
// Branch Analysis
//===----------------------------------------------------------------------===//

bool SampleInstrInfo::
AnalyzeBranch(MachineBasicBlock &MBB,
              MachineBasicBlock *&TBB,
              MachineBasicBlock *&FBB,
              SmallVectorImpl<MachineOperand> &Cond,
              bool AllowModify) const
{
  return false;
}

unsigned SampleInstrInfo::
InsertBranch(MachineBasicBlock &MBB, MachineBasicBlock *TBB,
             MachineBasicBlock *FBB,
             const SmallVectorImpl<MachineOperand> &Cond,
             DebugLoc DL) const {
  llvm_unreachable("Target didn't implement TargetInstrInfo::InsertBranch!");
}

unsigned SampleInstrInfo::
RemoveBranch(MachineBasicBlock &MBB) const
{
  llvm_unreachable("Target didn't implement TargetInstrInfo::InsertBranch!");
}
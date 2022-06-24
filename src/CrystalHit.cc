#include "G4Allocator.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "CrystalHit.hh"

namespace {
    G4ThreadLocal G4Allocator<CrystalHit>* scintHitAllocator = nullptr;
}

CrystalHit::CrystalHit(
        G4double depositedEnergy, const G4ThreeVector& position) :
    VirtualHit(position, 0),
    depositedEnergy(depositedEnergy)
{ }

CrystalHit::~CrystalHit()
{ }

void CrystalHit::Print()
{
    auto f = G4cout.flags();
    G4cout
        << "=== Begin CrystalHit ===" << G4endl
        << "Energy deposited: " << std::setw(7) << G4BestUnit(depositedEnergy, "Energy") << G4endl
        << "Position:         " << std::setw(7) << G4BestUnit(position, "Length") << G4endl
        << "=== End ScintCrystalHit ===" << G4endl;
    G4cout.flags(f);
    G4cout.flush();
}

bool CrystalHit::operator==(const CrystalHit& rhs)
{
    return
        depositedEnergy == rhs.peekDepositedEnergy() &&
        position == rhs.peekPosition();
}

const CrystalHit& CrystalHit::operator=(const CrystalHit& rhs)
{
    depositedEnergy = rhs.peekDepositedEnergy();
    position = rhs.peekPosition();
    return *this;
}

void* CrystalHit::operator new(size_t)
{
    if (!scintHitAllocator) scintHitAllocator = new G4Allocator<CrystalHit>;
    return static_cast<void*>(scintHitAllocator->MallocSingle());
}

void CrystalHit::operator delete(void* toDelete)
{
    scintHitAllocator->FreeSingle(static_cast<CrystalHit*>(toDelete));
}

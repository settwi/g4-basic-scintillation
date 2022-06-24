#include <G4Allocator.hh>
#include <G4UnitsTable.hh>
#include <G4SystemOfUnits.hh>

#include <SiHit.hh>

namespace
{
    G4ThreadLocal G4Allocator<SiHit>* alloc = nullptr;
}

SiHit::SiHit(
    const G4ThreeVector& position,
    G4double arrivalTime,
    G4double depositedEnergy
    ) :
        VirtualHit(position, arrivalTime),
        depositedEnergy(depositedEnergy)
{ }

SiHit::~SiHit()
{ }

void SiHit::Print()
{
    auto f = G4cout.flags();
    G4cout
        << "=== Begin SiHit ===" << G4endl
        << "Energy deposited: " << std::setw(7) << G4BestUnit(depositedEnergy, "Energy") << G4endl
        << "Position:         " << std::setw(7) << G4BestUnit(position, "Length") << G4endl
        << "Arrival time:     " << std::setw(7) << G4BestUnit(arrivalTime, "Time") << G4endl
        << "=== End SiCrystalHit ===" << G4endl;
    G4cout.flags(f);
    G4cout.flush();
}

bool SiHit::operator==(const SiHit& rhs)
{
    return
        position == rhs.peekPosition() &&
        arrivalTime == rhs.peekArrivalTime() &&
        depositedEnergy == rhs.peekDepositedEnergy();
}

const SiHit& SiHit::operator=(const SiHit& rhs)
{
    position = rhs.peekPosition();
    arrivalTime = rhs.peekArrivalTime();
    depositedEnergy = rhs.peekDepositedEnergy();
    return *this;
}

void* SiHit::operator new(size_t)
{
    if (!alloc) alloc = new G4Allocator<SiHit>;
    return static_cast<void*>(alloc->MallocSingle());
}

void SiHit::operator delete(void* toDelete)
{
    alloc->FreeSingle(static_cast<SiHit*>(toDelete));
}

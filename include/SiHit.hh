#pragma once

#include <G4String.hh>
#include <G4ThreeVector.hh>

#include <VirtualHit.hh>

class SiHit : public VirtualHit
{
    public:
        SiHit(
            const G4ThreeVector& position,
            G4double arrivalTime, G4double depositedEnergy);
        ~SiHit();
        const SiHit& operator=(const SiHit& rhs);
        bool operator==(const SiHit& rhs);

        G4double peekDepositedEnergy() const
        { return depositedEnergy; }

        void* operator new(size_t sz);
        void operator delete(void* toDelete);

        void Print() override;
        HitType hitType() const override
        { return HitType::Si; }

    private:
        G4double depositedEnergy;
};

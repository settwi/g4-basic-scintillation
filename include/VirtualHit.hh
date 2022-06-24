#pragma once

#include "G4VHit.hh"
#include "G4ThreeVector.hh"

class VirtualHit : public G4VHit
{
    public:
        VirtualHit(const G4ThreeVector& position, G4double arrivalTime);
        ~VirtualHit() =0;
        enum class HitType { ScintCryst, Si };

        virtual HitType hitType() const =0;
        virtual const G4ThreeVector& peekPosition() const
        { return position; }
        virtual G4double peekArrivalTime() const
        { return arrivalTime; }

        virtual void Draw() override;

    protected:
        G4double arrivalTime;
        G4ThreeVector position;
};

#pragma once

#include <fstream>
#include <unordered_map>
#include <vector>

#include <G4Accumulable.hh>
#include <G4Types.hh>
#include <G4String.hh>

class G4Event;
class G4Run;
class G4VHitsCollection;

class VirtualHit;

class AnalysisFileWrapper
{
    public:
        AnalysisFileWrapper(const std::string& fnPfx);
        ~AnalysisFileWrapper();

        std::ofstream& file()
        { return outf; }

        void reset(std::uint64_t newTimePfx);
    private:
        G4String buildFilename();
        std::uint64_t timePfx;
        G4String fileNamePrefix;
        std::ofstream outf;
};

class Analysis
{
    public:
        static Analysis& instance();
        static std::uint32_t currentRunNumber();

        void initFiles(G4bool isMaster);
        void saveFiles(G4bool isMaster);
        void saveEvent(const G4Event* evt);

        void addEvents(std::size_t nEvts)
        { totalEvents += nEvts; };

        void addIncidentEnergy(long double e);
        void saveScintillated(std::size_t num);

        Analysis(const Analysis&) =delete;
        void operator=(const Analysis&) =delete;
    private:
        static std::uint32_t runNumber;

        Analysis();
        ~Analysis();
        void processEvent(const G4Event* evt);
        void processHitCollection(const G4VHitsCollection* hc);
        void saveCrystalHits(const std::vector<VirtualHit*>* vec);
        void saveIncidentSpectrumChunk();

        void printSiHits(const std::vector<VirtualHit*>* vec);
        void saveSiHits(const std::vector<VirtualHit*>* vec);

        G4Accumulable<std::size_t> totalEvents;
        bool saveSiPositions;
        bool saveCrystPos;
        bool saveEachHitEnergy;

        std::vector<long double> incidentEnergiesChunk;

        AnalysisFileWrapper crystOut;
        AnalysisFileWrapper specIn;
        AnalysisFileWrapper siOut;
        AnalysisFileWrapper scintOut;
        std::vector<AnalysisFileWrapper*> wrappers;
};

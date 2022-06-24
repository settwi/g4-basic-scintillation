#include <ctime>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <memory>
#include <map>
#include <numeric>
#include <sstream>
#include <string>

#include <G4Accumulable.hh>
#include <G4AccumulableManager.hh>
#include <G4AutoLock.hh>
#include <G4Event.hh>
#include <G4Run.hh>
#include <G4String.hh>
#include <G4SystemOfUnits.hh>
#include <G4THitsCollection.hh>
#include <G4VHitsCollection.hh>


#include <Analysis.hh>
#include <CrystalHit.hh>
#include <SiHit.hh>
#include <VirtualHit.hh>

namespace {
    G4Mutex instMux = G4MUTEX_INITIALIZER;
    G4Mutex dataMux = G4MUTEX_INITIALIZER;

    static const G4String kSPEC_IN = "spec-in";
    static const G4String kCRYST_OUT = "cryst-out";
    static const G4String kSI_OUT = "si-out";
    static const G4String kSCINT_OUT = "scint-phots-out";
    static const std::string OUT_DIR = "data-out";
}

static std::string genBaseSubfolder(std::uint64_t milliz);
std::uint32_t Analysis::runNumber = 0;

Analysis::Analysis() :
    totalEvents(0),
    crystOut(kCRYST_OUT),
    specIn(kSPEC_IN),
    siOut(kSI_OUT),
    scintOut(kSCINT_OUT),

    // change these
    saveSiPositions(false),
    saveCrystPos(false),
    saveEachHitEnergy(false)
{
    G4AccumulableManager::Instance()->RegisterAccumulable(totalEvents);
    wrappers = {&crystOut, &specIn, &siOut, &scintOut};
}

Analysis::~Analysis()
{
}

Analysis& Analysis::instance()
{
    G4AutoLock l(&instMux);
    static Analysis a;
    return a;
}

std::uint32_t Analysis::currentRunNumber()
{ return runNumber; }

void Analysis::initFiles(G4bool isMaster)
{
    G4AutoLock l(&dataMux);
    if (!isMaster) return;

    G4AccumulableManager::Instance()->Reset();

    using clk = std::chrono::system_clock;
    auto nowOut = std::chrono::duration_cast<std::chrono::milliseconds>(
        clk::now().time_since_epoch());
    auto cnt = nowOut.count();

    (void) ++runNumber;
    for (auto* w : wrappers) {
        w->reset(cnt);
    }
}

void Analysis::saveFiles(G4bool isMaster)
{
    G4AutoLock l(&dataMux);
    if (!isMaster) return;

    G4AccumulableManager::Instance()->Merge();
    G4cout << "Total events " << totalEvents.GetValue() << G4endl;

    for (auto& w : wrappers) {
        w->file().flush();
        w->file().close();
    }
}

void Analysis::saveEvent(const G4Event* evt)
{
    G4AutoLock l(&dataMux);
    static const std::vector<VirtualHit*> empty;

    auto* hcote = evt->GetHCofThisEvent();
    if (hcote == nullptr) return; 
    
    G4int numHitColl = hcote->GetNumberOfCollections();
    for (G4int i = 0; i < numHitColl; ++i) {
        const auto* hc = hcote->GetHC(i);
        if (hc == nullptr) continue;
        processHitCollection(hc);
    }
}

void Analysis::processHitCollection(const G4VHitsCollection* hc)
{
    if (hc == nullptr) return;

    const auto* concreteHc = static_cast<const G4THitsCollection<VirtualHit>*>(hc);
    const auto* vec = concreteHc->GetVector();
    if (vec == nullptr || vec->size() == 0) return;

    const auto* testHit = (*vec)[0];
    if (testHit->hitType() == VirtualHit::HitType::ScintCryst) {
        saveCrystalHits(vec);
    } else if (testHit->hitType() == VirtualHit::HitType::Si) {
        saveSiHits(vec);
    } else {
        G4Exception(
            "src/Analysis.cc processHitCollection",
            "", FatalException, "unrecognized hit. what?");
    }

    saveIncidentSpectrumChunk();
}

void Analysis::saveCrystalHits(const std::vector<VirtualHit*>* vec)
{
    std::vector<G4double> deposits;
    std::vector<G4ThreeVector> crystHitPositions;

    for (const auto h : *vec) {
        auto* niceHit = static_cast<CrystalHit*>(h);
        auto curEng = niceHit->peekDepositedEnergy();
        deposits.push_back(curEng);

        if (saveCrystPos) {
            crystHitPositions.push_back(niceHit->peekPosition());
        }
    }

      if (not saveEachHitEnergy) {
          // channel second here just for legacy purposes
          double sum = std::accumulate(deposits.begin(), deposits.end(), 0.);
          crystOut.file() << (sum / keV);
          if (saveCrystPos) {
              for (const auto& hitPos : crystHitPositions)
                  crystOut.file() << ' ' << hitPos;
          }
      }
      else {
          for (std::size_t i = 0; i < deposits.size(); ++i) {
              const auto e = deposits[i];
              auto pos = crystHitPositions[i];
              crystOut.file()
                  << " ("
                      << pos.x()/mm << ','
                      << pos.y()/mm << ','
                      << pos.z()/mm << ','
                      << e/keV      << ')';
          }
      }
      crystOut.file() << std::endl;

    addEvents(1);
}

void Analysis::addIncidentEnergy(long double e)
{
    G4AutoLock l(&dataMux);
    incidentEnergiesChunk.push_back(e);
}

void Analysis::saveIncidentSpectrumChunk()
{
    for (const auto& e : incidentEnergiesChunk)
        specIn.file() << e / keV << std::endl;

    incidentEnergiesChunk.clear();
}

void Analysis::printSiHits(const std::vector<VirtualHit*>* vec)
{
    G4cout << "there were " << vec->size() << " silicon hits" << G4endl;
    G4cout.flush();
}

void Analysis::saveSiHits(const std::vector<VirtualHit*>* vec)
{
    siOut.file() << vec->size();
    if (saveSiPositions) {
        for (const auto* h : *vec) {
            const auto& p = h->peekPosition();
            const auto tofa = h->peekArrivalTime();
            siOut.file()
                << " (" << p.x()/mm << ',' << p.y()/mm << ',' << p.z()/mm
                << ',' << tofa/ns << ')';
        }
    }
    siOut.file() << std::endl;
}

void Analysis::saveScintillated(std::size_t num)
{
    G4AutoLock l(&dataMux);
    if (num == 0) return;
    // # scintillated per event can vary
    scintOut.file() << num << std::endl;
}

// filewrapper below

AnalysisFileWrapper::AnalysisFileWrapper(const std::string& fnPfx) :
    fileNamePrefix(fnPfx)
{ }

AnalysisFileWrapper::~AnalysisFileWrapper()
{ }

void AnalysisFileWrapper::reset(std::uint64_t newTimePfx)
{
    outf.flush();
    outf.close();
    if (newTimePfx) timePfx = newTimePfx;
    auto fn = buildFilename();
    outf.open(fn, std::ios::out);
}

G4String AnalysisFileWrapper::buildFilename()
{
    auto fold = genBaseSubfolder(timePfx);
    std::stringstream ss;
    ss << "run" << Analysis::currentRunNumber() << "-" << fold;
    auto prefixedFolder = ss.str();

    std::filesystem::path outPath(OUT_DIR);
    auto p = outPath / prefixedFolder;
    if (!std::filesystem::exists(p))
        std::filesystem::create_directory(p);

    ss.str("");
    ss << p.string() << "/" << fileNamePrefix << ".tab";

    return ss.str();
}

static std::string genBaseSubfolder(std::uint64_t milliz)
{
    static const std::size_t TIME_FMT_LEN = 256;
    static std::array<char, TIME_FMT_LEN> tmFmtAry;

    std::time_t secondz = milliz / 1e3;
    std::strftime(tmFmtAry.data(), TIME_FMT_LEN, "%F-%T", std::localtime(&secondz));
    const char* d = tmFmtAry.data();
    return std::string(d);
}

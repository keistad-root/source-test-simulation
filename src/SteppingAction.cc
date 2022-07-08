#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"

namespace B1 {
SteppingAction::SteppingAction(EventAction* eventAction)
    : fEventAction(eventAction) {}
SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    if (!fScoringVolume) {
        const DetectorConstruction* detConstruction =
            static_cast<const DetectorConstruction*>(
                G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        fScoringVolume = detConstruction->GetScoringVolume();
    }

    G4LogicalVolume* volume = step->GetPreStepPoint()
                                  ->GetTouchableHandle()
                                  ->GetVolume()
                                  ->GetLogicalVolume();

    if(volume != fScoringVolume) return;

    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep);
}
}    // namespace Fe55
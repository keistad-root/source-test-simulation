#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "Randomize.hh"

namespace B1 {

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4double probability = G4UniformRand();

    if (probability < 0.6) {
        G4ParticleDefinition* particle =
            particleTable->FindParticle(particleName = "e-");
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
        fParticleGun->SetParticleEnergy(5.19 * keV);
    } else if (probability < 0.762) {
        G4ParticleDefinition* particle =
            particleTable->FindParticle(particleName = "gamma");
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
        fParticleGun->SetParticleEnergy(5.89875 * keV);
    } else if (probability < 0.844) {
        G4ParticleDefinition* particle =
            particleTable->FindParticle(particleName = "gamma");
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
        fParticleGun->SetParticleEnergy(5.88765 * keV);
    } else if (probability < 0.8725) {
        G4ParticleDefinition* particle =
            particleTable->FindParticle(particleName = "gamma");
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
        fParticleGun->SetParticleEnergy(6.49045 * keV);
    } else {
    }
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    G4double R0 = 0.4 * cm;
    G4double h0 = 0.5 * cm;
    G4double radiusPos = R0 * G4UniformRand();
    G4double phiPos = 2 * 3.141592 * G4UniformRand();
    G4double x0 = radiusPos * std::cos(phiPos);
    G4double y0 = radiusPos * std::sin(phiPos);
    G4double z0 = -0.1 * cm + h0 * (G4UniformRand() - 0.5);
    fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
}    // namespace B1
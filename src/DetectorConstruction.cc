#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4Colour.hh"
#include "G4VisAttributes.hh"

namespace B1 {
DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();

    G4bool checkOverlaps = true;

    // World
    G4double world_sizeX = 10. * cm;
    G4double world_sizeY = 10. * cm;
    G4double world_sizeZ = 5. * cm;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box* solidWorld = new G4Box("World", 0.5 * world_sizeX, 0.5 * world_sizeY,
                                  0.5 * world_sizeZ);
    G4LogicalVolume* logicWorld =
        new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);
    // World

    // Shape 1:
    // part of Shape1
    G4double subshape1_sizeXY = 3.5 * cm;
    G4double subshape1_sizeZ = 0.5 * cm;
    G4Box* subshape1 =
        new G4Box("subshape1", subshape1_sizeXY, subshape1_sizeXY, subshape1_sizeZ);

    G4double subshape2_sizeX = 3.5 * cm;
    G4double subshape2_sizeY = 1.5 * cm;
    G4double subshape2_sizeZ = 0.55 * cm;
    G4Box* subshape2 =
        new G4Box("subshape2", subshape2_sizeX, subshape2_sizeY, subshape2_sizeZ);

    G4double empty1_sizeX = 3.25 * cm;
    G4double empty1_sizeY = 1. * cm;
    G4double empty1_sizeZ = 0.45 * cm;
    G4Box* empty1 =
        new G4Box("empty1", empty1_sizeX, empty1_sizeY, empty1_sizeZ);

    G4double empty2_sizeX = 3.25 * cm;
    G4double empty2_sizeY = 0.5 * cm;
    G4double empty2_sizeZ = 0.26 * cm;
    G4Box* empty2 =
        new G4Box("empty2", empty2_sizeX, empty2_sizeY, empty2_sizeZ);

    G4Tubs * source = new G4Tubs("source", 0., 0.45 * cm, 0.3 * cm,
                                 0. * deg, 360. * deg);
    // Part of shape 1
    // Fusing shape 1
    G4UnionSolid* shape1_step1 = new G4UnionSolid("shape1_step1", subshape1, subshape2, 0,
                                            G4ThreeVector(0, 0, 1.05 * cm));
    G4SubtractionSolid* shape1_step2 =
        new G4SubtractionSolid("shape1_step2", shape1_step1, empty1, 0,
                              G4ThreeVector(-0.5 * cm, 0, 0.65 * cm));
    G4SubtractionSolid* shape1_step3 =
        new G4SubtractionSolid("shape1_step3", shape1_step2, empty2, 0,
                               G4ThreeVector(-0.5 * cm, 0, 1.34 * cm));
    G4SubtractionSolid* solidShape1 = new G4SubtractionSolid(
        "shape1", shape1_step3, source, 0, G4ThreeVector(0, 0, -0.1 * cm));
    // Fusing shape 1
    G4Material* PLA = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
    G4ThreeVector pos1 = G4ThreeVector();
    G4LogicalVolume* logicShape1 =
        new G4LogicalVolume(solidShape1, PLA, "Shape1");

    new G4PVPlacement(0, pos1, logicShape1, "Shape1", logicWorld, false, 0,
                      checkOverlaps);
    // Shape1

    // ALPIDE def
    G4double alpide_sizeX = 1.5 * cm;
    G4double alpide_sizeY = 0.75 * cm;
    G4double alpide_sizeZ = 0.025 * mm;
    G4Material* Sil = nist->FindOrBuildMaterial("G4_Si");
    G4ThreeVector pos2 =
        G4ThreeVector(0, 0, -1.5 * cm);
    G4Box* alpide =
        new G4Box("alpide", alpide_sizeX, alpide_sizeY, alpide_sizeZ);
    G4LogicalVolume* logicAlpide = new G4LogicalVolume(alpide, Sil, "alpide");
    new G4PVPlacement(0, pos2, logicAlpide, "Shape1", logicWorld, false, 0,
                        checkOverlaps);
    G4VisAttributes* alpideVisAtt =
        new G4VisAttributes(G4Colour::Yellow());
    logicAlpide->SetVisAttributes(alpideVisAtt);
    // ALPIDE

    fScoringVolume = logicAlpide;
    return physWorld;
}
}    // namespace Fe55
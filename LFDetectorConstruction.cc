#include "LFDetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

LFDetectorConstruction::LFDetectorConstruction(): 
	G4VUserDetectorConstruction(),
	//fAir(0), 
	fWater(0), 
	fLead(0), 
	fWorldPhys(0), 
	fEnvPhys(0),
	fLeadPhys(0),
	fConstructed(false)
{;}

LFDetectorConstruction::~LFDetectorConstruction()
{;}

G4VPhysicalVolume* LFDetectorConstruction::Construct()
{
	
	if (!fConstructed)
	{
		fConstructed = true;
		DefineMaterials();
		SetupGeometry();
	}
	return fWorldPhys;
}

void LFDetectorConstruction::DefineMaterials()
{
	G4NistManager* nist = G4NistManager::Instance();
	fWater = nist->FindOrBuildMaterial("G4_WATER");
	fLead = nist->FindOrBuildMaterial("G4_Pb");
}

void LFDetectorConstruction::SetupGeometry()
{
	bool checkOverlaps = true;
	G4double atomicNumber = 1.; 
  	G4double massOfMole = 1.008*g/mole; 
  	G4double density = 1.e-25*g/cm3; 
  	G4double temperature = 2.73*kelvin; 
  	G4double pressure = 3.e-18*pascal; 
	
	//World
	
	G4VSolid* worldSolid = new G4Box ("World", 2.*m, 2.*m, 2.*m);
	G4Material* Vacuum = new G4Material
	("interGalactic", atomicNumber, massOfMole, density, kStateGas, 		temperature, pressure); 
	G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid, 	Vacuum, "World");
	fWorldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogical, 	"World", 0, false, 0);

	//Envelope
	
	G4VSolid* envSolid = new G4Box ("Envelope", 1.5*m, 1.5*m, 1.5*m);
	G4LogicalVolume* envLogical = new G4LogicalVolume(envSolid, Vacuum, "Envelope");
	fEnvPhys = new G4PVPlacement(0, G4ThreeVector(), envLogical, "Envelope", worldLogical, false, 0);

	//Solid
	
	G4ThreeVector posa = G4ThreeVector(0.*m, 0.*m, -1.25*m);
	G4double inR = 0.*cm;
	G4double outR = 1.5*m;
	G4double hz = 0.04*m;
	G4double startA = 0.*deg;
	G4double spanA = 360.*deg;
	
	G4Tubs* myleadtube = new G4Tubs("mylead", inR, outR, 0.05*hz, startA, spanA);

  	G4LogicalVolume* myleadlog = new G4LogicalVolume(myleadtube, fLead, "mylead");

	fLeadPhys = new G4PVPlacement(0, posa, myleadlog,"mylead", envLogical, false, 0, checkOverlaps);   

	// Visualization attributes
  	//
  	// worldLogical->SetVisAttributes(G4VisAttributes::Invisible);
  	G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
	G4VisAttributes* simpleBoxVisAtt4 = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  	simpleBoxVisAtt->SetVisibility(true);
	simpleBoxVisAtt4->SetVisibility(true);
	worldLogical->SetVisAttributes(simpleBoxVisAtt);
  	envLogical->SetVisAttributes(simpleBoxVisAtt4);
	
}


			

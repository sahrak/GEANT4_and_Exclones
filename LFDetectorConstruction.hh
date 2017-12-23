#ifndef LFdetectorConstruction_h 
#define LFDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4Material;
class G4LogicalVolume;

class LFDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
	  LFDetectorConstruction();
	  virtual ~LFDetectorConstruction();
	  virtual G4VPhysicalVolume* Construct();

	private:
	  void DefineMaterials();
	  void SetupGeometry();
	  //G4Material* fAir;
	  G4Material* fWater;
	  G4Material* fLead;
	  G4VPhysicalVolume* fWorldPhys;
	  G4VPhysicalVolume* fEnvPhys;
	  G4VPhysicalVolume* fLeadPhys;
	  bool fConstructed;
};

#endif


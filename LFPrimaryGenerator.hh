#ifndef LFPrimaryGeneratorAction_h
#define LFPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4Box.hh"


class G4ParticleGun;
class G4Event;

 class LFPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
 {
	public:
	  LFPrimaryGeneratorAction();
	  virtual ~LFPrimaryGeneratorAction();
	  virtual void GeneratePrimaries(G4Event* );
	  const G4ParticleGun* GetParticleGun() const {return fParticleGun; };

	private:
	  G4ParticleGun* fParticleGun;
	  G4Box* fEnvelopeBox;
 };

#endif

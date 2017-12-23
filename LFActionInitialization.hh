#ifndef LFActionInitialization_h
#define LFActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

  class LFActionInitialization : public G4VUserActionInitialization
  {
	public:
	  LFActionInitialization();
	  virtual ~LFActionInitialization();
	
	  virtual void Build() const;
  };

#endif

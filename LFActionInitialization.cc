#include "LFActionInitialization.hh"
#include "LFPrimaryGeneratorAction.hh"

LFActionInitialization::LFActionInitialization()
{;}

LFActionInitialization::~LFActionInitialization()
{;}

void LFActionInitialization::Build() const
{
     SetUserAction(new LFPrimaryGeneratorAction);
}
 

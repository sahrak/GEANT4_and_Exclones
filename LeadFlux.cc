#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "LFDetectorConstruction.hh"
#include "LFPrimaryGeneratorAction.hh"
#include "LFActionInitialization.hh"
//#include "LFSteppingAction.hh"
#include "G4ScoringManager.hh"

#include "QBBC.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "Randomize.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main (int argc, char** argv)
{
	G4UIExecutive* ui = 0;
	if (argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}
	
	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	
	G4RunManager* runManager = new G4RunManager;
	
	runManager->SetUserInitialization(new LFDetectorConstruction);
	
	/*G4VModularPhysicsList* physicslists = new QBBC;
	physicslists->SetVerboseLevel(1);
	runManager->SetUserInitialization(physicslists);*/

	G4VModularPhysicsList* physicsList = new FTFP_BERT;
  	physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  	runManager->SetUserInitialization(physicsList);

	runManager->SetUserInitialization(new LFActionInitialization);

	runManager->SetUserAction(new LFPrimaryGeneratorAction);
	//runManager->SetUserAction(new LFSteppingAction);
	G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();
	
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	if (!ui)
	{
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else
	{
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	
	delete visManager;
	delete runManager;
}


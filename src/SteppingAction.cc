#include "SteppingAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4SteppingManager.hh"

#include "RunAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4AnalysisManager.hh"

#include "G4PhysicalVolumeStore.hh"


SteppingAction::SteppingAction(RunAction* run, DetectorConstruction* det)
  :fRun(run),fDetector(det)
{ 

  // //Get name of volumes excluding repetitions 
  // std::string avname="";
  // G4PhysicalVolumeStore* pvols = G4PhysicalVolumeStore::GetInstance();
  // for(int i=0; i<(int)pvols->size(); i++){
  //   //G4cout << ((*pvols)[i])->GetName() << G4endl;
  //     avname = ((*pvols)[i])->GetName();
  //     if(!(std::find(vname.begin(),vname.end(),avname) != vname.end())){
	// vname.push_back(avname);
  //     }
  // }

}

SteppingAction::~SteppingAction()
{
}


void SteppingAction::UserSteppingAction(const G4Step* aStep)
{ 
   // Analysis manager
  
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  
  // man->FillNtupleIColumn(1,0,fRun->GetNumEvent()+fevt);
  // man->FillNtupleIColumn(1,1,aStep->GetTrack()->GetDynamicParticle()->GetPDGcode());
  // man->FillNtupleIColumn(1,2,aStep->GetTrack()->GetTrackID());
  // man->FillNtupleIColumn(1,3,aStep->GetTrack()->GetParentID());
  // man->FillNtupleDColumn(1,4,aStep->GetTrack()->GetPosition().x()/nm);
  // man->FillNtupleDColumn(1,5,aStep->GetTrack()->GetPosition().y()/nm);
  // man->FillNtupleDColumn(1,6,aStep->GetTrack()->GetPosition().z()/nm);
  // man->FillNtupleDColumn(1,7,aStep->GetTotalEnergyDeposit()/eV);
  // man->FillNtupleDColumn(1,8,aStep->GetTrack()->GetKineticEnergy()/eV);

  const G4VProcess* pds = aStep->GetPostStepPoint()->GetProcessDefinedStep();
  G4String processName = "unknown"; 
  if(pds) processName = pds->GetProcessName();

  // G4cout << "evt: "<< fRun->GetNumEvent(); 
  // G4cout << ", pdg: " << aStep->GetTrack()->GetDynamicParticle()->GetPDGcode();
  if (processName == "eIoni" || processName=="NoProcess" || processName=="unknown"
    || processName=="OpRayleigh" || processName=="Transportation" 
    || processName=="OpAbsorption" || processName=="Cerenkov") return;
  // G4cout << "id: " << aStep->GetTrack()->GetTrackID() 
  //   << ", mid: " << aStep->GetTrack()->GetParentID()
  //   << ", " << aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName()
  //   << ", DE: " << aStep->GetTotalEnergyDeposit()/MeV
  //   << ", process: " << processName 
  //   << "\n";
  // G4cout << ", x:   " << aStep->GetTrack()->GetPosition().x()/um;
  // G4cout << ", y:   " << aStep->GetTrack()->GetPosition().y()/um;
  // G4cout << ", z:   " << aStep->GetTrack()->GetPosition().z()/um;
  // G4cout << ", de:  " << aStep->GetTotalEnergyDeposit()/eV;
  // G4cout << ", e:   " << aStep->GetTrack()->GetKineticEnergy()/eV;

  //   if(aStep->GetTrack()->GetNextVolume()!=0){
  //     G4cout << ", vol: " << aStep->GetTrack()->GetNextVolume()->GetName();
      
  //     std::pair<int,int> aux = VolumeCode( aStep->GetTrack()->GetNextVolume()->GetName());

  //     G4int hv_id = man->GetH1Id("hv"); // get histogram int identifier, searched by histogram name
  //     man->FillH1(hv_id,aux.first); // fill histogram at thos volume code value,

  //     man->FillNtupleIColumn(1,9,aux.first);
  //     man->FillNtupleIColumn(1,10,aStep->GetPostStepPoint()->GetTouchableHandle()->GetReplicaNumber());
  //     G4cout << " " << aux.first;
  //     G4cout << " " << aStep->GetPostStepPoint()->GetTouchableHandle()->GetReplicaNumber();
  //     //if(aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName()!="World"){
  //     if(aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName()!=wname.c_str()){
	// man->FillNtupleIColumn(1,11,aux.second);
	// man->FillNtupleIColumn(1,12,aStep->GetPostStepPoint()->GetTouchableHandle()->GetReplicaNumber(1));
	// G4cout << " " << aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume(1)->GetName();
	// G4cout << " " << aStep->GetPostStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
	// G4cout << " " << aux.second;
  //     }else{
	// man->FillNtupleIColumn(1,11,aux.second);
	// man->FillNtupleIColumn(1,12,0);
	// G4cout << " " << "OutOfWorld";
	// G4cout << " " << aux.second;
  //       G4cout << " " << 0;
       
  //     }
  //   }else{
  //     std::pair<int,int> aux = VolumeCode("OutOfWorld");
  //     G4cout << ", vol: OutOfWorld";
  //     G4cout << " " << aux.first;
  //     G4cout << " " << 0;
  //     G4cout << " " << "OutOfWorld";
  //     G4cout << " " << aux.second;
  //     G4cout << " " << 0;
  //     G4int hv_id = man->GetH1Id("hv");
  //     man->FillH1(hv_id,aux.first);      
  //     man->FillNtupleIColumn(1,9,aux.first);
  //     man->FillNtupleIColumn(1,10,0);
  //     man->FillNtupleIColumn(1,11,aux.second);
  //     man->FillNtupleIColumn(1,12,0);
  //   }     
    
  //   if(aStep->GetPostStepPoint()->GetProcessDefinedStep()!=NULL){
  //     std::string name = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  //     G4cout << ", proccess: " << name << G4endl;
  //     p = imap.find(name);
  //     if(p!=imap.end()){
	// //###G4cout << "repeated" <<" "<< p->first <<" "<< p->second << G4endl;
	// man->FillNtupleIColumn(1,13,p->second);
  //     }
  //     if(p==imap.end()){
	// idx++;
	// std::pair<std::string, int> aux(name,idx);
	// imap.insert(aux);
	// man->FillNtupleIColumn(1,13,idx);
  //     }

  //     if(eveti!=fRun->GetNumEvent()){
	// eveti=fRun->GetNumEvent();
	// for(p=imap.begin(); p!=imap.end(); p++){
	//   G4cout << p->first << " " << p->second << G4endl;
	// }
	// G4cout << "n: " << idx << G4endl;
  //     }
      
  //   }else{
  //     G4cout << ", proccess: User Limit" << G4endl;
  //     man->FillNtupleIColumn(1,13,-1);
  //   }
  //   //man->AddNtupleRow(1);
  //   //G4cout << "Passed track" << G4endl;
}

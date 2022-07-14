#include "CsISD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "Constants.hh"

//
CsISD::CsISD(const G4String &sd_name, const G4String &hits_collection_name)
: G4VSensitiveDetector(sd_name),
  hits_collection(NULL)
{
  // hitcollection's name, have to be defined
  collectionName.insert(hits_collection_name);
}

//
CsISD::~CsISD()
{

}

//
//  build collection between hitsclooection and G4Event
//  call before G4Event start
void CsISD::Initialize(G4HCofThisEvent *hit_collection)
{
  // Create hits collection
  hits_collection = new CsIHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hc_id = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hit_collection->AddHitsCollection(hc_id, hits_collection);

  for(int i=0;i<N_OF_CSI_DETECTOR;i++) {
    hits_collection->insert(new CsIHit());
  }
}

//
G4bool CsISD::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  // energy deposit
  G4double e = step->GetTotalEnergyDeposit();

  if(e==0){
    return false;
  }

  auto touchable = step->GetPreStepPoint()->GetTouchable();
  auto physical = touchable->GetVolume();
  auto copy_no = physical->GetCopyNo();
	
  CsIHit *hit = (*hits_collection)[copy_no];
  hit->SetID(copy_no);
  hit->AddEdep(e); 

  return true;
}

//
void CsISD::EndOfEvent(G4HCofThisEvent*)
{
  //  print some information
  if(verboseLevel>1){
    G4int n_of_hits = hits_collection->entries();
    G4cout << G4endl << "-------->Hits Collection: in this event they are " << n_of_hits << " hits in the CsI array: " << G4endl;

    for(G4int i=0; i<n_of_hits; i++){
      (*hits_collection)[i]->Print();
    }
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
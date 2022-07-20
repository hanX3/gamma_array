#include "GeSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//
GeSD::GeSD(const G4String &sd_name, const G4String &hits_collection_name)
: G4VSensitiveDetector(sd_name),
  hits_collection(NULL)
{
  // hitcollection's name, have to be defined
  collectionName.insert(hits_collection_name);
}

//
GeSD::~GeSD()
{

}

//
//  build collection between hitsclooection and G4Event
//  call before G4Event start
void GeSD::Initialize(G4HCofThisEvent *hit_collection)
{
  // Create hits collection
  hits_collection = new GeHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hc_id = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hit_collection->AddHitsCollection(hc_id, hits_collection);

  hits_collection->insert(new GeHit());
}

//
G4bool GeSD::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  // energy deposit
  G4double e = step->GetTotalEnergyDeposit();

  if(e==0){
    return false;
  }
	
  GeHit *hit = (*hits_collection)[0];
  hit->AddEdep(e);

  return true;
}

//
void GeSD::EndOfEvent(G4HCofThisEvent*)
{
  //  print some information
  if(verboseLevel>1){ 
    G4int n_of_hits = hits_collection->entries();
    G4cout << G4endl << "-------->Hits Collection: in this event they are " << n_of_hits << " hits in the Ge array: " << G4endl;

    for(G4int i=0; i<n_of_hits; i++){
      (*hits_collection)[i]->Print();
    }
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
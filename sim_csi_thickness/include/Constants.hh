#ifndef Constants_h
#define Constants_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"

//
constexpr G4double WORLD_SIZE_X = 2. * m;
constexpr G4double WORLD_SIZE_Y = 2. * m;
constexpr G4double WORLD_SIZE_Z = 2. * m;

// Ge
constexpr G4double Ge_ARRAY_R        = 600. * mm; // Ge Array R
constexpr G4double TARGET_GE_DIS     = 140. * mm; // distance to the face of Ge detector

constexpr G4double GE_R              = 46.7 * mm;
constexpr G4double GE_HEIGHT         = 54.5 * mm;
constexpr G4double LN2_HOLE_R        = 5.55 * mm;
constexpr G4double LN2_HOLE_DEEP     = 47.95 * mm;

constexpr G4double GE_POS_DIS        = GE_HEIGHT + TARGET_GE_DIS;

//CsI
constexpr G4double CSI_ARRAY_R        = 100.* mm; // CsI Array R
constexpr G4double TARGET_CSI_DIS     = 50. * mm; // distance to the face of CsI detector

constexpr G4double CSI_SIZE_X         = 15. * mm;
constexpr G4double CSI_SIZE_Y         = 15. * mm;
constexpr G4double CSI_THICKNESS      = 2. * mm;
constexpr G4double MYLAR_SIZE_X       = 15. * mm;
constexpr G4double MYLAR_SIZE_Y       = 15. * mm;
constexpr G4double MYLAR_THICKNESS    = 2. * um;
constexpr G4double SI_SIZE_X          = 10. * mm;
constexpr G4double SI_SIZE_Y          = 10. * mm;
constexpr G4double SI_THICKNESS       = 0.3 * mm;

constexpr G4double MYLAR_POS_DIS      = TARGET_CSI_DIS + MYLAR_THICKNESS/2.;
constexpr G4double CSI_POS_DIS        = TARGET_CSI_DIS + MYLAR_THICKNESS + CSI_THICKNESS/2.;
constexpr G4double SI_POS_DIS         = TARGET_CSI_DIS + MYLAR_THICKNESS + CSI_THICKNESS + SI_THICKNESS/2.;

constexpr G4int    N_OF_CsI_DETECTOR  = 25;
constexpr G4double CSI_ARRAY_X[N_OF_CsI_DETECTOR] = {-40., -20., 0., 20., 40., -40., -20., 0., 20., 40., -40., -20., 0., 20., 40., -40., -20., 0., 20., 40., -40., -20., 0., 20., 40.};
constexpr G4double CSI_ARRAY_Y[N_OF_CsI_DETECTOR] = {-40., -40., -40., -40., -40., -20., -20., -20., -20., -20., 0., 0., 0., 0., 0., 20., 20., 20., 20., 20., 40., 40., 40., 40., 40.};

// PCB
constexpr G4double PCB_SIZE_X         = 100. * mm;
constexpr G4double PCB_SIZE_Y         = 100. * mm;
constexpr G4double PCB_THICKNESS      = 2. * mm;

constexpr G4double PCB_POS_DIS        = TARGET_CSI_DIS + MYLAR_THICKNESS + CSI_THICKNESS + SI_THICKNESS + PCB_THICKNESS/2.;

// Chamber
constexpr G4double CHAMBER_R_MIN      = 98. * mm;
constexpr G4double CHAMBER_R_MAX      = 100. * mm;

#endif

//---------------------------------------------------------------------------
// TestMicroEstablishment.cpp
//---------------------------------------------------------------------------
#include "TestMicroEstablishment.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "Grid.h"
#include "TreePopulation.h"
#include "MicroEstablishment.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestGetSubstrateProportions()
// Tests the function clMicroEstablishment::GetSubstrateProportions. There
// are three setup files:  WriteMicroEstablishmentXMLFile2(),
// WriteMicroEstablishmentXMLFile3(), and WriteMicroEstablishmentXMLFile5(). For
// all three, specific substrate proportions are assigned to cells and the
// results compared. Then we check seed distribution by checking the number of
// seedlings out of an original 100 that have z values greater than 0.
/////////////////////////////////////////////////////////////////////////////
TEST(MicroEstablishment, TestGetSubstrateProportions) {
  clTreePopulation *p_oPop;
  clMicroEstablishment *p_oEstablishment;
  clGrid *p_oSubstrate, *p_oSeeds;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  float *p_fProportions = new float[clMicroEstablishment::number_substrates], fExpected, fValue, fY, fMin, fMax;
  int iX, iY, iNumZ, iNumNoZ, i, iZ;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //************************************
    //First run:  mound proportion between 0 and 1
    //and substrate and seed grid cell resolutions are equal
    //************************************
    //Set up the run
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLFile1());
    p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");

    //In cell 0,0 of the "Substrate" set the substrate proportions
    iX = 0; iY = 0;
    fValue = 0.12;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.23;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.08;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.3;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.17;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,1 of the "Substrate" set the substrate proportions
    iX = 0; iY = 1;
    fValue = 0.22;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.45;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.002;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.178;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.15;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,2 of the "Substrate" set the substrate proportions
    iX = 0; iY = 2;
    fValue = 1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //Now run GetSubstrateProportions
    p_oEstablishment = dynamic_cast<clMicroEstablishment *>(p_oSimManager->GetBehaviorObject("MicroEstablishment"));

    iX = 0, iY = 0;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.09;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0.1725;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0.06;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0.225;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0.1275;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0.075;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0.03;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0.0575;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0.02;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0.075;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0.025;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0.0425;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    iX = 0, iY = 1;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.165;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0.3375;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0.0015;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0.1125;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0.1335;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0.055;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0.1125;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0.0005;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0.0375;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0.0445;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    iX = 0, iY = 2;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.75;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0.25;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    //******************************
    // Now check seed distribution
    //******************************
    //Add 100 seeds to each seed grid cell
    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
    p_oSeeds->SetValueOfCell(0, 1, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
    p_oSeeds->SetValueOfCell(0, 2, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);

    //Run just the establishment behavior
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      if (p_oSimManager->GetBehaviorObject(i)->GetName().compare("MicroEstablishment") == 0) {
        p_oSimManager->GetBehaviorObject(i)->Action();
      }
    }

    //Count the seedlings
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    iNumZ = 0; iNumNoZ = 0;
    fMin = 0; fMax = 6;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ + iNumNoZ);
    EXPECT_LT(78, iNumZ); EXPECT_GT(83, iNumZ);
    EXPECT_LT(18, iNumNoZ); EXPECT_GT(21, iNumNoZ);

    //Check our values for cell 0, 1
    iNumZ = 0; iNumNoZ = 0;
    fMin = 6; fMax = 12;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ + iNumNoZ);
    EXPECT_LT(73, iNumZ); EXPECT_GT(77, iNumZ);
    EXPECT_LT(23, iNumNoZ); EXPECT_GT(27, iNumNoZ);

    //Check our values for cell 0, 2
    iNumZ = 0; iNumNoZ = 0;
    fMin = 12; fMax = 18;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ + iNumNoZ);
    EXPECT_LT(73, iNumZ); EXPECT_GT(77, iNumZ);
    EXPECT_LT(23, iNumNoZ); EXPECT_GT(27, iNumNoZ);

    //************************************
    //Second run:  mound proportion is 1
    //and substrate and seed grid cell resolutions are not equal
    //************************************
    //Set up the run
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLFile2());
    p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");

    //In cell 0,0 of the "Substrate" set the substrate proportions
    iX = 0; iY = 0;
    fValue = 0.12;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.23;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.08;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.3;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.17;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,1 of the "Substrate" set the substrate proportions
    iX = 0; iY = 1;
    fValue = 0.22;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.45;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.002;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.178;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.15;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,2 of the "Substrate" set the substrate proportions
    iX = 0; iY = 2;
    fValue = 1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //Now run GetSubstrateProportions
    p_oEstablishment = dynamic_cast<clMicroEstablishment *>(p_oSimManager->GetBehaviorObject("MicroEstablishment"));

    iX = 0, iY = 0;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.12;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0.23;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0.08;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0.3;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0.17;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0.1;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    iX = 0, iY = 1;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.12;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0.23;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0.08;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0.3;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0.17;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0.1;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    iX = 0, iY = 2;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.22;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0.45;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0.002;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0.15;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0.178;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    iX = 0, iY = 3;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.22;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0.45;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0.002;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0.15;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0.178;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    iX = 0, iY = 4;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    iX = 0, iY = 5;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    //******************************
    // Now check seed distribution
    //******************************
    //Add 100 seeds to each seed grid cell
    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
    p_oSeeds->SetValueOfCell(0, 1, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
    p_oSeeds->SetValueOfCell(0, 2, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
    p_oSeeds->SetValueOfCell(0, 3, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
    p_oSeeds->SetValueOfCell(0, 4, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
    p_oSeeds->SetValueOfCell(0, 5, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);

    //Run just the establishment behavior
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      if (p_oSimManager->GetBehaviorObject(i)->GetName().compare("MicroEstablishment") == 0) {
        p_oSimManager->GetBehaviorObject(i)->Action();
      }
    }

    //Count the seedlings
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    iNumZ = 0; iNumNoZ = 0;
    fMin = 0; fMax = 5;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ);
    EXPECT_EQ(0, iNumNoZ);

    //Check our values for cell 0, 1
    iNumZ = 0; iNumNoZ = 0;
    fMin = 5; fMax = 10;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ);
    EXPECT_EQ(0, iNumNoZ);

    //Check our values for cell 0, 2
    iNumZ = 0; iNumNoZ = 0;
    fMin = 10; fMax = 15;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ);
    EXPECT_EQ(0, iNumNoZ);

    //Check our values for cell 0, 3
    iNumZ = 0; iNumNoZ = 0;
    fMin = 15; fMax = 20;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ);
    EXPECT_EQ(0, iNumNoZ);

    //Check our values for cell 0, 4
    iNumZ = 0; iNumNoZ = 0;
    fMin = 20; fMax = 25;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ);
    EXPECT_EQ(0, iNumNoZ);

    //Check our values for cell 0, 5
    iNumZ = 0; iNumNoZ = 0;
    fMin = 25; fMax = 30;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ);
    EXPECT_EQ(0, iNumNoZ);

    //************************************
    //Third run:  mound proportion 0
    //and substrate and seed grid cell resolutions are not equal
    //************************************
    //Set up the run
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLFile3());
    p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");

    //In cell 0,0 of the "Substrate" set the substrate proportions
    iX = 0; iY = 0;
    fValue = 0.12;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.23;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.08;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.3;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.17;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,1 of the "Substrate" set the substrate proportions
    iX = 0; iY = 1;
    fValue = 0.22;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.45;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.002;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.178;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.15;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,2 of the "Substrate" set the substrate proportions
    iX = 0; iY = 2;
    fValue = 1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,3 of the "Substrate" set the substrate proportions
    iX = 0; iY = 3;
    fValue = 0.12;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.23;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.08;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.3;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.17;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,4 of the "Substrate" set the substrate proportions
    iX = 0; iY = 4;
    fValue = 0.22;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.45;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.002;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.178;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.15;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,5 of the "Substrate" set the substrate proportions
    iX = 0; iY = 5;
    fValue = 1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,6 of the "Substrate" set the substrate proportions
    iX = 0; iY = 6;
    fValue = 0.12;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.23;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.08;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.3;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.17;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,7 of the "Substrate" set the substrate proportions
    iX = 0; iY = 7;
    fValue = 0.22;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.45;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.002;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.178;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.15;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,8 of the "Substrate" set the substrate proportions
    iX = 0; iY = 8;
    fValue = 1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,9 of the "Substrate" set the substrate proportions
    iX = 0; iY = 9;
    fValue = 0.12;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.23;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.08;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.3;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.17;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,10 of the "Substrate" set the substrate proportions
    iX = 0; iY = 10;
    fValue = 0.22;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.45;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 0.002;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.178;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.15;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //In cell 0,11 of the "Substrate" set the substrate proportions
    iX = 0; iY = 11;
    fValue = 1;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    p_oSubstrate->SetValueOfCell(iX, iY, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);

    //Now run GetSubstrateProportions
    p_oEstablishment = dynamic_cast<clMicroEstablishment *>(p_oSimManager->GetBehaviorObject("MicroEstablishment"));

    iX = 0, iY = 0;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0.365;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0.115;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0.1525;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0.1505;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0.0875;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0.1295;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    iX = 0, iY = 1;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0.39;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0.0575;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0.245;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0.076;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0.1;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0.1315;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    iX = 0, iY = 2;
    p_oEstablishment->GetSubstrateProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_decayedlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_freshlogs]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_ffmoss]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_fflitter]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_tipup]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::mound_scarsoil]), 0.001);
    fExpected = 0.585;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_decayedlogs]), 0.001);
    fExpected = 0.0575;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_freshlogs]), 0.001);
    fExpected = 0.1325;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_ffmoss]), 0.001);
    fExpected = 0.0755;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_fflitter]), 0.001);
    fExpected = 0.0625;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_scarsoil]), 0.001);
    fExpected = 0.087;
    EXPECT_LT(fabs(fExpected - p_fProportions[clMicroEstablishment::ground_tipup]), 0.001);

    //******************************
    // Now check seed distribution
    //******************************
    //Add 100 seeds to each seed grid cell
    fValue = 100;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
    p_oSeeds->SetValueOfCell(0, 1, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);
    p_oSeeds->SetValueOfCell(0, 2, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);

    //Run just the establishment behavior
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      if (p_oSimManager->GetBehaviorObject(i)->GetName().compare("MicroEstablishment") == 0) {
        p_oSimManager->GetBehaviorObject(i)->Action();
      }
    }

    //Count the seedlings
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    iNumZ = 0; iNumNoZ = 0;
    fMin = 0; fMax = 8;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ + iNumNoZ);
    EXPECT_TRUE(11 == iNumZ || 12 == iNumZ);
    EXPECT_TRUE(88 == iNumNoZ || 89 == iNumNoZ);

    //Check our values for cell 0, 1
    iNumZ = 0; iNumNoZ = 0;
    fMin = 8; fMax = 16;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ + iNumNoZ);
    EXPECT_TRUE(5 == iNumZ || 6 == iNumZ);
    EXPECT_TRUE(94 == iNumNoZ || 95 == iNumNoZ);

    //Check our values for cell 0, 2
    iNumZ = 0; iNumNoZ = 0;
    fMin = 16; fMax = 24;
    p_oAllSeedlings->StartOver();
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fY >= fMin && fY < fMax) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("z", p_oTree->GetSpecies(), p_oTree->GetType()), &iZ);
        if (iZ > 0) iNumZ++; else iNumNoZ++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(100, iNumZ + iNumNoZ);
    EXPECT_TRUE(5 == iNumZ || 6 == iNumZ);
    EXPECT_TRUE(94 == iNumNoZ || 95 == iNumNoZ);

    delete[] p_fProportions;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_fProportions;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestGetFreshLogProportions()
// Tests the function clMicroEstablishment::GetFreshLogProportions. There
// are three setup files:  WriteMicroEstablishmentXMLFile2(),
// WriteMicroEstablishmentXMLFile3(), and WriteMicroEstablishmentXMLFile5(). For
// all three, specific substrate proportions are assigned to cells and the
// results compared.
/////////////////////////////////////////////////////////////////////////////
TEST(MicroEstablishment, TestGetFreshLogProportions) {
  clMicroEstablishment *p_oEstablishment;
  clGrid *p_oSubstrate, *p_oSeeds;
  clPackage *p_oCohort;
  float *p_fProportions = new float[7], fExpected, fValue;
  int iX, iY, iValue;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //************************************
    //First run:  Substrate and seed grid cell resolutions are equal
    //************************************
    //Set up the run
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLFile1());
    p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");

    //In cell 0,0 of the "Substrate" set the cohorts
    iX = 0; iY = 0;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.777417188;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,1 of the "Substrate" set the cohorts
    iX = 0; iY = 1;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.258861021;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 4;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.293457344;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.13;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,2 of the "Substrate" set the cohorts
    iX = 0; iY = 2;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.786357413;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.106292692;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //Cell 0,3 will have no cohorts

    //Now run GetFreshLogProportions
    p_oEstablishment = dynamic_cast<clMicroEstablishment *>(p_oSimManager->GetBehaviorObject("MicroEstablishment"));

    iX = 0, iY = 0;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 1;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.281581332;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.428568508;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 0.85464512;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 2;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.101978523;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.24651043;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 3;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);


    //************************************
    //Second run:  Substrate has a bigger cell resolution than seed
    //************************************
    //Set up the run
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLFile2());
    p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");

    //In cell 0,0 of the "Substrate" set the cohorts
    iX = 0; iY = 0;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.577417188;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,1 of the "Substrate" set the cohorts
    iX = 0; iY = 1;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.258861021;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 4;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.293457344;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.13;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,2 of the "Substrate" set the cohorts
    iX = 0; iY = 2;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.786357413;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.106292692;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //Cell 0,3 will have no cohorts

    //Now run GetSubstrateProportions
    p_oEstablishment = dynamic_cast<clMicroEstablishment *>(p_oSimManager->GetBehaviorObject("MicroEstablishment"));

    iX = 0, iY = 0;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 1;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 2;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.281581332;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.428568508;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 0.85464512;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 3;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.281581332;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.428568508;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 0.85464512;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 4;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.101978523;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.24651043;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 5;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.101978523;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.24651043;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 6;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 7;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 0;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    //************************************
    //Third run:  Substrate has a smaller grid cell resolution than seeds
    //************************************
    //Set up the run
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLFile3());
    p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");

    //In cell 0,0 of the "Substrate" set the cohorts
    iX = 0; iY = 0;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.577417188;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,1 of the "Substrate" set the cohorts
    iX = 0; iY = 1;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.588610213;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 4;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.293457344;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.13;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,2 of the "Substrate" set the cohorts
    iX = 0; iY = 2;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.786357413;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.106292692;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //No cohorts for cell 0,3

    //In cell 0,4 of the "Substrate" set the cohorts
    iX = 0; iY = 4;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.386357413;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.106292692;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,5 of the "Substrate" set the cohorts
    iX = 0; iY = 5;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.577417188;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,6 of the "Substrate" set the cohorts
    iX = 0; iY = 6;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.588610213;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 4;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.293457344;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.13;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,7 of the "Substrate" set the cohorts
    iX = 0; iY = 7;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.786357413;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.106292692;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //No cohorts for cell 0,8

    //In cell 0,9 of the "Substrate" set the cohorts
    iX = 0; iY = 9;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.386357413;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.106292692;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,10 of the "Substrate" set the cohorts
    iX = 0; iY = 10;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.577417188;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,11 of the "Substrate" set the cohorts
    iX = 0; iY = 11;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.588610213;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 4;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.293457344;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.13;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,12 of the "Substrate" set the cohorts
    iX = 0; iY = 12;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.786357413;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.106292692;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.071340092;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //No cohorts for cell 0,13

    //In cell 0,14 of the "Substrate" set the cohorts
    iX = 0; iY = 14;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.386357413;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.106292692;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //In cell 0,15 of the "Substrate" set the cohorts
    iX = 0; iY = 15;
    p_oCohort = p_oSubstrate->CreatePackageOfCell(iX, iY);
    fValue = 0.577417188;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    //Now run GetFreshLogProportions
    p_oEstablishment = dynamic_cast<clMicroEstablishment *>(p_oSimManager->GetBehaviorObject("MicroEstablishment"));

    iX = 0, iY = 0;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.426917553;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.51954726;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 0.916348808;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 1;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.356536036;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.480185134;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 0.930139522;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 2;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.476480568;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.590289929;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 0.897222079;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    iX = 0, iY = 3;
    p_oEstablishment->GetFreshLogProportions(p_fProportions,
        p_oSeeds->GetOriginXOfCell(iX), p_oSeeds->GetOriginYOfCell(iY),
        p_oSeeds->GetEndXOfCell(iX), p_oSeeds->GetEndYOfCell(iY));
    fExpected = 0.396291957;
    EXPECT_LT(fabs(fExpected - p_fProportions[0]), 0.001);
    fExpected = 0.519816054;
    EXPECT_LT(fabs(fExpected - p_fProportions[1]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[2]), 0.001);
    fExpected = 1;
    EXPECT_LT(fabs(fExpected - p_fProportions[3]), 0.001);

    delete[] p_fProportions;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_fProportions;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestMoundZDistributions()
// Produces 1000 seeds in cell 0,0, and lets them all germinate (by setting
// substrate favorabilities to 1). WriteMicroEstablishmentXMLFile3() gives us
// the setup file, with mound proportion = 1. The substrate type is set to all
// moss (so fresh logs don't interfere). Then the z's of the seedlings will be
// collected and written to MoundZ.txt.
/////////////////////////////////////////////////////////////////////////////
/*TEST(MicroEstablishment, TestMoundZDistributions) {
  using namespace std;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    fstream oOut;
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllSeedlings;
    clTree *p_oSeedling;
    clGrid *p_oSeeds, *p_oSubstrate;
    float fValue;
    int iZValue;

    //Set up the run
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLFile2());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

    //In cell 0,0 of the "Disperse Seeds" grid, put 1000 seeds of species 1
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    fValue = 1000;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);

    //In cell 0,0 of the "Substrate" make the substrate all forest floor moss
    p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    fValue = 0;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 1;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    //Run establishment
    p_oSimManager->GetBehaviorObject("MicroEstablishment")->Action();

    //Open file to write to
    oOut.open("MoundZ.txt", ios::out | ios::trunc);
    oOut << "Height in mm\n";

    //Get all the seedlings
    p_oAllSeedlings = p_oPop->Find("type=1");
    //Count them into their different categories
    p_oSeedling = p_oAllSeedlings->NextTree();
    while (p_oSeedling) {
      //Get the Z value
      p_oSeedling->GetValue(p_oPop->GetIntDataCode("z", p_oSeedling->GetSpecies(), p_oSeedling->GetType()), &iZValue);

      oOut << iZValue << "\n";

      p_oSeedling = p_oAllSeedlings->NextTree();
    }

    oOut.close();
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}*/

/////////////////////////////////////////////////////////////////////////////
// TestFreshLogZDistributions()
// Tests the function clMicroEstablishment::SetFreshLogZAndRespite, to make
// sure that seedling z heights are properly distributed. This places 1000
// cells in cell 0,0, and lets them all germinate. The substrate type is set
// to all fresh log. WriteMicroEstablishmentXMLFile3() is used to set up. Then the z's of the
// seedlings are collected and written to FreshLogZ.txt.
/////////////////////////////////////////////////////////////////////////////
/*TEST(MicroEstablishment, TestFreshLogZDistributions) {
  using namespace std;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    fstream oOut;
    clPopulationBase * p_oTemp;
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllSeedlings;
    clTree *p_oSeedling;
    clGrid *p_oSeeds, *p_oSubstrate;
    float fValue;
    int iZValue;

    //Set up the run
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLFile2());
    p_oTemp = p_oSimManager->GetPopulationObject("treepopulation");
    p_oPop = (clTreePopulation *) p_oTemp;

    //In cell 0,0 of the "Disperse Seeds" grid, put 1000 seeds of species 1
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    fValue = 1000;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);

    //In cell 0,0 of the "Substrate" make the substrate all fresh log
    p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    fValue = 0;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 1;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);

    //Run establishment
    p_oSimManager->GetBehaviorObject("MicroEstablishment")->Action();

    //Open file to write to
    oOut.open("FreshLogZ.txt", ios::out | ios::trunc);
    oOut << "Height in mm\n";

    //Get all the seedlings
    p_oAllSeedlings = p_oPop->Find("type=1");
    //Count them into their different categories
    p_oSeedling = p_oAllSeedlings->NextTree();
    while (p_oSeedling) {
      //Get the Z value
      p_oSeedling->GetValue(p_oPop->GetIntDataCode("z", p_oSeedling->GetSpecies(), p_oSeedling->GetType()), &iZValue);

      oOut << iZValue << "\n";

      p_oSeedling = p_oAllSeedlings->NextTree();
    }

    oOut.close();
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}*/

/////////////////////////////////////////////////////////////////////////////
// TestSetZAndRespite()
// Tests the functions clMicroEstablishment::SetFreshLogZAndRespite,
// SetMoundZAndRespite, and SetGroundZAndRespite. It passes in a seedling to
// each to see if the expected results are correct for the last two (greater
// than 0 for z and 0 for respite in the first case, 0 for both z and respite
// in the second case). Then 1000 seeds of species 2 are added to cell (0,0)
// and the substrate set to all fresh logs. The fresh log proportions array
// will be split evenly between the four possible ages: 0, 2, 4, and 6. Then
// the seedlings are checked to make sure they're roughly equal to those ages.
/////////////////////////////////////////////////////////////////////////////
TEST(MicroEstablishment, TestSetZAndRespite) {
  clMicroEstablishment *p_oEstablishment;
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oSeedling;
  clGrid *p_oSeeds, *p_oSubstrate;
  clPackage *p_oCohort;
  float fValue;
  int *p_iAges, iValue, i;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    //Set up the run
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLFile1());

    p_oEstablishment = dynamic_cast<clMicroEstablishment *>(p_oSimManager->GetBehaviorObject("MicroEstablishment"));
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");;

    //Create a seedling
    p_oSeedling = p_oPop->CreateTree(2, 2, 0, clTreePopulation::seedling, 0);

    //See what it gets if it's on the ground - both respite counter and z should be 0
    p_oEstablishment->SetGroundZAndRespite(p_oSeedling);
    p_oSeedling->GetValue(p_oPop->GetIntDataCode("z", p_oSeedling->GetSpecies(), p_oSeedling->GetType()), &iValue);
    EXPECT_EQ(iValue, 0);
    p_oSeedling->GetValue(p_oPop->GetIntDataCode("lf_count", p_oSeedling->GetSpecies(), p_oSeedling->GetType()), &iValue);
    EXPECT_EQ(iValue, 0);

    //See what it gets if it's on a mound - respite counter should be 0, z greater
    p_oEstablishment->SetMoundZAndRespite(p_oSeedling);
    p_oSeedling->GetValue(p_oPop->GetIntDataCode("z", p_oSeedling->GetSpecies(), p_oSeedling->GetType()), &iValue);
    EXPECT_GT(iValue, 0);
    p_oSeedling->GetValue(p_oPop->GetIntDataCode("lf_count", p_oSeedling->GetSpecies(), p_oSeedling->GetType()), &iValue);
    EXPECT_EQ(iValue, 0);

    //***************************************
    // Fresh logs
    //***************************************
    p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    p_oSubstrate = p_oSimManager->GetGridObject("Substrate");

    //In cell 0,0 of the "Substrate" set the cohorts
    p_oCohort = p_oSubstrate->CreatePackageOfCell(0, 0);
    fValue = 0.96;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 4;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.37;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 3;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.27;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 2;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    p_oCohort = p_oSubstrate->CreatePackage(p_oCohort);
    fValue = 0.25;
    p_oCohort->SetValue(p_oSubstrate->GetPackageFloatDataCode("freshlog"), fValue);
    iValue = 1;
    p_oCohort->SetValue(p_oSubstrate->GetPackageIntDataCode("age"), iValue);

    fValue = 0;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);
    fValue = 1;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);

    //Add 1000 seeds
    fValue = 1000;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_0"), fValue);

    //Now run the behavior
    p_oEstablishment->Action();

    p_iAges = new int[4];

    for (i = 0; i < 4; i++) {
      p_iAges[i] = 0;
    }

    //Make sure the seedlings all have one of the allowed ages - 0, 2, 4, or 6
    p_oAllSeedlings = p_oPop->Find("type=1");
    //Count them into their different categories
    p_oSeedling = p_oAllSeedlings->NextTree();
    while (p_oSeedling) {
      //Get the count value
      p_oSeedling->GetValue(p_oPop->GetIntDataCode("lf_count", p_oSeedling->GetSpecies(), p_oSeedling->GetType()), &iValue);

      if (0 == iValue) {
        p_iAges[0]++;
      } else if (2 == iValue) {
        p_iAges[1]++;
      } else if (4 == iValue) {
        p_iAges[2]++;
      } else if (6 == iValue) {
        p_iAges[3]++;
      } else {
        FAIL() << "clMicroEstablishment::GetFreshLogZAndRespite failed - unallowed counter value.";
      }

      p_oSeedling = p_oAllSeedlings->NextTree();
    }

    //Make sure that the seedlings are in roughly equal groups
    fValue = (float)p_iAges[0]/((float)p_iAges[0]+(float)p_iAges[1]+(float)p_iAges[2]+(float)p_iAges[3]);
    EXPECT_GT(fValue, 0.22); EXPECT_LT(fValue, 0.29);
    fValue = (float)p_iAges[1]/((float)p_iAges[0]+(float)p_iAges[1]+(float)p_iAges[2]+(float)p_iAges[3]);
    EXPECT_GT(fValue, 0.22); EXPECT_LT(fValue, 0.29);
    fValue = (float)p_iAges[2]/((float)p_iAges[0]+(float)p_iAges[1]+(float)p_iAges[2]+(float)p_iAges[3]);
    EXPECT_GT(fValue, 0.22); EXPECT_LT(fValue, 0.29);
    fValue = (float)p_iAges[3]/((float)p_iAges[0]+(float)p_iAges[1]+(float)p_iAges[2]+(float)p_iAges[3]);
    EXPECT_GT(fValue, 0.22); EXPECT_LT(fValue, 0.29);

    delete[] p_iAges;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iAges;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
/////////////////////////////////////////////////////////////////////////////
TEST(MicroEstablishment, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteMicroEstablishmentXMLErrorFile1());
    FAIL() << "TestMicroEstablishment error processing didn't catch error for WriteMicroEstablishmentXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clMicroEstablishment::GetParameterFileData") != 0)
    {
      FAIL() << "TestMicroEstablishment error processing caught wrong error for WriteMicroEstablishmentXMLErrorFile1.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMicroEstablishmentXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMicroEstablishmentXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteMicroEstablishmentCommonStuff(oOut);

  oOut //Set both substrate and seeds grid to resolution of 6,6
       << "<grid gridName=\"Substrate\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"fflitter\">0</ma_floatCode>"
       << "<ma_floatCode label=\"ffmoss\">1</ma_floatCode>"
       << "<ma_floatCode label=\"tipup\">2</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog\">3</ma_floatCode>"
       << "<ma_floatCode label=\"declog\">4</ma_floatCode>"
       << "<ma_floatCode label=\"scarsoil\">5</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_plotLenX>200.0</ma_plotLenX>"
       << "<ma_plotLenY>200.0</ma_plotLenY>"
       << "<ma_lengthXCells>6.0</ma_lengthXCells>"
       << "<ma_lengthYCells>6.0</ma_lengthYCells>"
       << "</grid>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_plotLenX>200.0</ma_plotLenX>"
       << "<ma_plotLenY>200.0</ma_plotLenY>"
       << "<ma_lengthXCells>6.0</ma_lengthXCells>"
       << "<ma_lengthYCells>6.0</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightFilter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<listPosition>5</listPosition>"
       << "<version>1</version>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MicroEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<LightFilter2>"
       << "<lf_lightExtinctionCoefficient>1.535</lf_lightExtinctionCoefficient>"
       << "<lf_heightOfFilter>1.3</lf_heightOfFilter>"
       << "</LightFilter2>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>"
       << "<Substrate4>"
       << "<su_scarSoilDecayAlpha>0</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>0</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>3</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_freshLogFromfflitter>0</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_1\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_1\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.64</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate4>"
       << "<NonSpatialDisperse5>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse5>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MicroEstablishment6>"
       << "<es_moundProportion>0.75</es_moundProportion>"
       << "<es_maxRespite>6</es_maxRespite>"
       << "<es_meanMoundHeight>3</es_meanMoundHeight>"
       << "<es_moundStdDev>0.5</es_moundStdDev>"
       << "<es_meanFreshLogHeight>20</es_meanFreshLogHeight>"
       << "<es_freshLogStdDev>5</es_freshLogStdDev>"
       << "</MicroEstablishment6>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMicroEstablishmentXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMicroEstablishmentXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteMicroEstablishmentCommonStuff(oOut);

  oOut //Set substrate resolution to 10X10 and seeds grid resolution to 5X5
       << "<grid gridName=\"Substrate\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"fflitter\">0</ma_floatCode>"
       << "<ma_floatCode label=\"ffmoss\">1</ma_floatCode>"
       << "<ma_floatCode label=\"tipup\">2</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog\">3</ma_floatCode>"
       << "<ma_floatCode label=\"declog\">4</ma_floatCode>"
       << "<ma_floatCode label=\"scarsoil\">5</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_plotLenX>200.0</ma_plotLenX>"
       << "<ma_plotLenY>200.0</ma_plotLenY>"
       << "<ma_lengthXCells>10.0</ma_lengthXCells>"
       << "<ma_lengthYCells>10.0</ma_lengthYCells>"
       << "</grid>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_plotLenX>200.0</ma_plotLenX>"
       << "<ma_plotLenY>200.0</ma_plotLenY>"
       << "<ma_lengthXCells>5.0</ma_lengthXCells>"
       << "<ma_lengthYCells>5.0</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightFilter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MicroEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<LightFilter2>"
       << "<lf_lightExtinctionCoefficient>1.535</lf_lightExtinctionCoefficient>"
       << "<lf_heightOfFilter>1.3</lf_heightOfFilter>"
       << "</LightFilter2>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>"
       << "<Substrate4>"
       << "<su_scarSoilDecayAlpha>0</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>0</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>3</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_freshLogFromfflitter>0</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_1\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_1\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.64</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate4>"
       << "<NonSpatialDisperse5>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "</NonSpatialDisperse5>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MicroEstablishment6>"
       << "<es_moundProportion>1</es_moundProportion>"
       << "<es_maxRespite>6</es_maxRespite>"
       << "<es_meanMoundHeight>3</es_meanMoundHeight>"
       << "<es_moundStdDev>0.5</es_moundStdDev>"
       << "<es_meanFreshLogHeight>20</es_meanFreshLogHeight>"
       << "<es_freshLogStdDev>5</es_freshLogStdDev>"
       << "</MicroEstablishment6>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMicroEstablishmentXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMicroEstablishmentXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteMicroEstablishmentCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightFilter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MicroEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<LightFilter2>"
       << "<lf_lightExtinctionCoefficient>1.535</lf_lightExtinctionCoefficient>"
       << "<lf_heightOfFilter>1.3</lf_heightOfFilter>"
       << "</LightFilter2>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>"
       << "<Substrate4>"
       << "<su_scarSoilDecayAlpha>0</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>0</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>0</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>6.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_freshLogFromfflitter>0</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_1\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_1\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.64</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate4>"
       << "<NonSpatialDisperse5>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0.3</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "</NonSpatialDisperse5>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MicroEstablishment6>"
       << "<es_moundProportion>-0.87</es_moundProportion>"
       << "<es_maxRespite>3</es_maxRespite>"
       << "<es_meanMoundHeight>3</es_meanMoundHeight>"
       << "<es_moundStdDev>0.5</es_moundStdDev>"
       << "<es_meanFreshLogHeight>20</es_meanFreshLogHeight>"
       << "<es_freshLogStdDev>5</es_freshLogStdDev>"
       << "</MicroEstablishment6>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMicroEstablishmentXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteMicroEstablishmentXMLFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteMicroEstablishmentCommonStuff(oOut);

  oOut //Set substrate resolution to 2X8 and seeds grid resolution to 8X8
       << "<grid gridName=\"Substrate\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"fflitter\">0</ma_floatCode>"
       << "<ma_floatCode label=\"ffmoss\">1</ma_floatCode>"
       << "<ma_floatCode label=\"tipup\">2</ma_floatCode>"
       << "<ma_floatCode label=\"freshlog\">3</ma_floatCode>"
       << "<ma_floatCode label=\"declog\">4</ma_floatCode>"
       << "<ma_floatCode label=\"scarsoil\">5</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_plotLenX>200.0</ma_plotLenX>"
       << "<ma_plotLenY>200.0</ma_plotLenY>"
       << "<ma_lengthXCells>8.0</ma_lengthXCells>"
       << "<ma_lengthYCells>2.0</ma_lengthYCells>"
       << "</grid>"
       << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">0</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_plotLenX>200.0</ma_plotLenX>"
       << "<ma_plotLenY>200.0</ma_plotLenY>"
       << "<ma_lengthXCells>8.0</ma_lengthXCells>"
       << "<ma_lengthYCells>8.0</ma_lengthYCells>"
       << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>ConstantGLI</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>LightFilter</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MicroEstablishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>6</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<ConstantGLI1>"
       << "<li_constGLI>100</li_constGLI>"
       << "</ConstantGLI1>"
       << "<LightFilter2>"
       << "<lf_lightExtinctionCoefficient>1.535</lf_lightExtinctionCoefficient>"
       << "<lf_heightOfFilter>1.3</lf_heightOfFilter>"
       << "</LightFilter2>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>"
       << "<Substrate4>"
       << "<su_scarSoilDecayAlpha>0</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>0</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>3</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_freshLogFromfflitter>0</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_1\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_1\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.64</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate4>"
       << "<NonSpatialDisperse5>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "</NonSpatialDisperse5>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<MicroEstablishment6>"
       << "<es_moundProportion>0</es_moundProportion>"
       << "<es_maxRespite>6</es_maxRespite>"
       << "<es_meanMoundHeight>3</es_meanMoundHeight>"
       << "<es_moundStdDev>0.5</es_moundStdDev>"
       << "<es_meanFreshLogHeight>20</es_meanFreshLogHeight>"
       << "<es_freshLogStdDev>5</es_freshLogStdDev>"
       << "</MicroEstablishment6>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteMicroEstablishmentCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteMicroEstablishmentCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>2</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\"/>"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";
}

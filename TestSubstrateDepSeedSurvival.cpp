//---------------------------------------------------------------------------
// TestSubstrateDepSeedSurvival.cpp
//---------------------------------------------------------------------------
#include "TestSubstrateDepSeedSurvival.h"
#include <gtest/gtest.h>
#include "Grid.h"
#include "SimManager.h"
#include "BehaviorBase.h"
#include "TreePopulation.h"
#include <stdio.h>
#include <fstream>
#include <math.h>

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
// Performs error testing. This feeds in the set of error parameter files
// and verifies that the correct error is thrown for each.
////////////////////////////////////////////////////////////////////////////
TEST(SubstrateDepSeedSurvival, TestErrorProcessing) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteSubstrateDepSeedSurvivalXMLErrorFile1());
    FAIL() << "TestSubstrateDepSeedSurvival error processing didn't catch error for WriteSubstrateDepSeedSurvivalXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSubstrateDepSeedSurvival::GetParameterFileData") != 0)
    {
      FAIL() << "TestSubstrateDepSeedSurvival error processing caught wrong error for WriteSubstrateDepSeedSurvivalXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteSubstrateDepSeedSurvivalXMLErrorFile2());
    FAIL() << "TestSubstrateDepSeedSurvival error processing didn't catch error for WriteSubstrateDepSeedSurvivalXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSubstrateDepSeedSurvival::SetupGrids") != 0)
    {
      FAIL() << "TestSubstrateDepSeedSurvival error processing caught wrong error for WriteSubstrateDepSeedSurvivalXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteSubstrateDepSeedSurvivalXMLErrorFile3());
    FAIL() << "TestSubstrateDepSeedSurvival error processing didn't catch error for WriteSubstrateDepSeedSurvivalXMLErrorFile3.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clSubstrateDepSeedSurvival::SetupGrids") != 0)
    {
      FAIL() << "TestSubstrateDepSeedSurvival error processing caught wrong error for WriteSubstrateDepSeedSurvivalXMLErrorFile3.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Performs run 1 of normal processing. WriteSubstrateDepSeedSurvivalXMLFile1()
// does setup. This run has no gap status. Grid cell size is default for all
// grids. There are seven species but the first is not used. Non-spatial
// disperse is used but given parameter values such that it will add no seeds.
// Establishment will turn our surviving seeds into seedlings. We are interested
// in 4 grid cells; for each of these, the substrate proportions are set in the
// "Substrate" grid and 1000 seeds of each species are added to the "Dispersed
// Seeds" grid. Then the run progresses and the seedlings are counted.
/////////////////////////////////////////////////////////////////////////////
TEST(SubstrateDepSeedSurvival, TestNormalProcessingRun1) {
  float fValue, fExpectedFav;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  float fX, fY, fMin, fMax;
  int *p_iNumSeedlings = new int[7], i;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
   //Feed our file to the sim manager
   p_oSimManager->ReadFile(WriteSubstrateDepSeedSurvivalXMLFile1());

   clGrid *p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
   clGrid *p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
   clGrid *p_oSubsFav = p_oSimManager->GetGridObject("Substrate Favorability");
   clTreePopulation *p_oPop = (clTreePopulation*)p_oSimManager->GetPopulationObject("treepopulation");

   //For each of four cells, set 1000 seeds of each species
   fValue = 1000;
   p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
   p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
   p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
   p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
   p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
   p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
   p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
   p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
   p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
   p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
   p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
   p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
   p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
   p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
   p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
   p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
   p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
   p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
   p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
   p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
   p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
   p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
   p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
   p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);

   //Set the substrate proportions for these same cells
   fValue = 0;
   p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
   fValue = 0.42;
   p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
   fValue = 0.01;
   p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("declog"), fValue);
   fValue = 0.345;
   p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
   fValue = 0.081;
   p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
   fValue = 0.144;
   p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

   fValue = 0;
   p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
   fValue = 1;
   p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
   fValue = 0;
   p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("declog"), fValue);
   fValue = 0;
   p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
   fValue = 0;
   p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
   fValue = 0;
   p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

   fValue = 0.88;
   p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
   fValue = 0.02;
   p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
   fValue = 0.03;
   p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("declog"), fValue);
   fValue = 0.04;
   p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
   fValue = 0.0108;
   p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
   fValue = 0.0192;
   p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

   fValue = 0.21;
   p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
   fValue = 0.22;
   p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
   fValue = 0.23;
   p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("declog"), fValue);
   fValue = 0.24;
   p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
   fValue = 0.036;
   p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
   fValue = 0.064;
   p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

   //Do the run but don't let substrate run
   clBehaviorBase * p_oTempBehavior;
   std::string sBehaviorName;
   for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
     p_oTempBehavior = p_oSimManager->GetBehaviorObject( i );
     sBehaviorName = p_oTempBehavior->GetName();
     if (sBehaviorName.compare("Substrate") != 0 )
     {
       p_oTempBehavior->Action();
     }
   }

   //Check the substrate favorabilities
   fExpectedFav = 0.514865;
   p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.255923;
   p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.905418;
   p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.457311;
   p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.500969;
   p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.681351;
   p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

   fExpectedFav = 0.462;
   p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0;
   p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.98;
   p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.278;
   p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.462;
   p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 1;
   p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

   fExpectedFav = 0.06337;
   p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.0541724;
   p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.9529224;
   p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.8576868;
   p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.0615172;
   p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.0519668;
   p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

   fExpectedFav = 0.30859;
   p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.221618;
   p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.942308;
   p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.447316;
   p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.302414;
   p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
   fExpectedFav = 0.377756;
   p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
   EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

   //Count the seedlings
   p_oAllSeedlings = p_oPop->Find("type=1");

   //Check our values for cell 0, 0
   for (i = 0; i < 7; i++) {
     p_iNumSeedlings[i] = 0;
   }
   fMin = 0;
   fMax = 8;
   p_oTree = p_oAllSeedlings->NextTree();
   while (p_oTree) {
     p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
     p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
     if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
       p_iNumSeedlings[p_oTree->GetSpecies()]++;
     }
     p_oTree = p_oAllSeedlings->NextTree();
   }
   EXPECT_EQ(0, p_iNumSeedlings[0]);
   EXPECT_LT(fabs(514.865 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
   EXPECT_LT(fabs(255.923 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.15);
   EXPECT_LT(fabs(905.418 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
   EXPECT_LT(fabs(457.311 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
   EXPECT_LT(fabs(500.969 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
   EXPECT_LT(fabs(681.351 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

   //Check our values for cell 1, 1
   p_oAllSeedlings->StartOver();
   for (i = 0; i < 7; i++) {
     p_iNumSeedlings[i] = 0;
   }
   fMin = 8;
   fMax = 16;
   p_oTree = p_oAllSeedlings->NextTree();
   while (p_oTree) {
     p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
     p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
     if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
       p_iNumSeedlings[p_oTree->GetSpecies()]++;
     }
     p_oTree = p_oAllSeedlings->NextTree();
   }
   EXPECT_EQ(0, p_iNumSeedlings[0]);
   EXPECT_LT(fabs(462 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
   EXPECT_EQ(0, p_iNumSeedlings[2]);
   EXPECT_LT(fabs(980 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
   EXPECT_LT(fabs(278 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
   EXPECT_LT(fabs(462 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
   EXPECT_LT(fabs(1000 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

   //Check our values for cell 2, 2
   p_oAllSeedlings->StartOver();
   for (i = 0; i < 7; i++) {
     p_iNumSeedlings[i] = 0;
   }
   fMin = 16;
   fMax = 24;
   p_oTree = p_oAllSeedlings->NextTree();
   while (p_oTree) {
     p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
     p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
     if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
       p_iNumSeedlings[p_oTree->GetSpecies()]++;
     }
     p_oTree = p_oAllSeedlings->NextTree();
   }
   EXPECT_EQ(0, p_iNumSeedlings[0]);
   EXPECT_LT(fabs(63.37 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.15);
   EXPECT_LT(fabs(54.1724 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.15);
   EXPECT_LT(fabs(952.9224 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
   EXPECT_LT(fabs(857.6868 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
   EXPECT_LT(fabs(61.5172 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.15);
   EXPECT_LT(fabs(51.9668 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.15);


   //Check our values for cell 3, 3
   p_oAllSeedlings->StartOver();
   for (i = 0; i < 7; i++) {
     p_iNumSeedlings[i] = 0;
   }
   fMin = 24;
   fMax = 32;
   p_oTree = p_oAllSeedlings->NextTree();
   while (p_oTree) {
     p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
     p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
     if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
       p_iNumSeedlings[p_oTree->GetSpecies()]++;
     }
     p_oTree = p_oAllSeedlings->NextTree();
   }
   EXPECT_EQ(0, p_iNumSeedlings[0]);
   EXPECT_LT(fabs(308.59 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
   EXPECT_LT(fabs(221.618 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.1);
   EXPECT_LT(fabs(942.308 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
   EXPECT_LT(fabs(447.316 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
   EXPECT_LT(fabs(302.414 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
   EXPECT_LT(fabs(377.756 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

   delete[] p_iNumSeedlings;
   delete p_oSimManager;
   } catch (modelErr &e) {
     delete[] p_iNumSeedlings;
     delete p_oSimManager;
     FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
   }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun2()
// Performs run 2 of normal processing. WriteSubstrateDepSeedSurvivalXMLFile2() does setup. This
// run has gap status. Grid cell size is default for all grids. There are
// seven species but the first is not used. Spatial disperse is used but
// given parameter values such that it will add no seeds. Establishment will
// turn our surviving seeds into seedlings. We are interested in 4 grid
// cells; for each of these, the substrate proportions are set in the
// "Substrate" grid and 1000 seeds of each species are added to the "Dispersed
// Seeds" grid. Then the run progresses and the seedlings are counted.
/////////////////////////////////////////////////////////////////////////////
TEST(SubstrateDepSeedSurvival, TestNormalProcessingRun2) {

  float fValue, fExpectedFav;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  float fX, fY, fMin, fMax;
  int *p_iNumSeedlings = new int[7], i;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteSubstrateDepSeedSurvivalXMLFile2());

    clGrid *p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    clGrid *p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    clGrid *p_oSubsFav = p_oSimManager->GetGridObject("Substrate Favorability");
    clTreePopulation *p_oPop = (clTreePopulation*)p_oSimManager->GetPopulationObject("treepopulation");


    //For each of four cells, set 1000 seeds of each species
    fValue = 1000;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(4, 4, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(4, 4, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(4, 4, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(4, 4, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(4, 4, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(4, 4, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(5, 5, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(5, 5, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(5, 5, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(5, 5, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(5, 5, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(5, 5, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(6, 6, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(6, 6, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(6, 6, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(6, 6, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(6, 6, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(6, 6, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(7, 7, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(7, 7, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(7, 7, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(7, 7, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(7, 7, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(7, 7, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);

    //Set the substrate proportions for these same cells
    fValue = 0;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.42;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.01;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.345;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.081;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.144;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 1;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0.88;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.02;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.03;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.04;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.0108;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.0192;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0.21;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.22;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.23;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.24;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.036;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.064;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0;
    p_oSubstrate->SetValueOfCell(4, 4, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.42;
    p_oSubstrate->SetValueOfCell(4, 4, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.01;
    p_oSubstrate->SetValueOfCell(4, 4, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.345;
    p_oSubstrate->SetValueOfCell(4, 4, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.081;
    p_oSubstrate->SetValueOfCell(4, 4, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.144;
    p_oSubstrate->SetValueOfCell(4, 4, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0;
    p_oSubstrate->SetValueOfCell(5, 5, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 1;
    p_oSubstrate->SetValueOfCell(5, 5, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(5, 5, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(5, 5, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(5, 5, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(5, 5, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0.88;
    p_oSubstrate->SetValueOfCell(6, 6, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.02;
    p_oSubstrate->SetValueOfCell(6, 6, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.03;
    p_oSubstrate->SetValueOfCell(6, 6, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.04;
    p_oSubstrate->SetValueOfCell(6, 6, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.0108;
    p_oSubstrate->SetValueOfCell(6, 6, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.0192;
    p_oSubstrate->SetValueOfCell(6, 6, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0.21;
    p_oSubstrate->SetValueOfCell(7, 7, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.22;
    p_oSubstrate->SetValueOfCell(7, 7, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.23;
    p_oSubstrate->SetValueOfCell(7, 7, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.24;
    p_oSubstrate->SetValueOfCell(7, 7, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.036;
    p_oSubstrate->SetValueOfCell(7, 7, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.064;
    p_oSubstrate->SetValueOfCell(7, 7, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    //Create the trees that will create non-gap conditions
    p_oPop->CreateTree(36, 36, 0, clTreePopulation::adult, 20);
    p_oPop->CreateTree(44, 44, 0, clTreePopulation::adult, 20);
    p_oPop->CreateTree(52, 52, 0, clTreePopulation::adult, 20);
    p_oPop->CreateTree(60, 60, 0, clTreePopulation::adult, 20);

    //Do the run but don't let substrate run
    clBehaviorBase * p_oTempBehavior;
    std::string sBehaviorName;
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oTempBehavior = p_oSimManager->GetBehaviorObject( i );
      sBehaviorName = p_oTempBehavior->GetName();
      if (sBehaviorName.compare("Substrate") != 0 )
      {
        p_oTempBehavior->Action();
      }
    }

    //Check the substrate favorabilities
    fExpectedFav = 0.226105;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.353764;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.326917;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.32812;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.313801;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.34498;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.353;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.024;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.353;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.024;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.353;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.884088;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.4258332;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.9210936;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.442194;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.8957808;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.425526;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.33255;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.352784;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.562762;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.49702;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.371526;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.34808;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.514865;
    p_oSubsFav->GetValueOfCell(4, 4, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.255923;
    p_oSubsFav->GetValueOfCell(4, 4, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.905418;
    p_oSubsFav->GetValueOfCell(4, 4, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.457311;
    p_oSubsFav->GetValueOfCell(4, 4, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.500969;
    p_oSubsFav->GetValueOfCell(4, 4, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.681351;
    p_oSubsFav->GetValueOfCell(4, 4, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.462;
    p_oSubsFav->GetValueOfCell(5, 5, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0;
    p_oSubsFav->GetValueOfCell(5, 5, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.98;
    p_oSubsFav->GetValueOfCell(5, 5, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.278;
    p_oSubsFav->GetValueOfCell(5, 5, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.462;
    p_oSubsFav->GetValueOfCell(5, 5, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 1;
    p_oSubsFav->GetValueOfCell(5, 5, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.06337;
    p_oSubsFav->GetValueOfCell(6, 6, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.0541724;
    p_oSubsFav->GetValueOfCell(6, 6, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.9529224;
    p_oSubsFav->GetValueOfCell(6, 6, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.8576868;
    p_oSubsFav->GetValueOfCell(6, 6, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.0615172;
    p_oSubsFav->GetValueOfCell(6, 6, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.0519668;
    p_oSubsFav->GetValueOfCell(6, 6, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.30859;
    p_oSubsFav->GetValueOfCell(7, 7, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.221618;
    p_oSubsFav->GetValueOfCell(7, 7, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.942308;
    p_oSubsFav->GetValueOfCell(7, 7, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.447316;
    p_oSubsFav->GetValueOfCell(7, 7, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.302414;
    p_oSubsFav->GetValueOfCell(7, 7, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.377756;
    p_oSubsFav->GetValueOfCell(7, 7, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    //Count the seedlings
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 0;
    fMax = 8;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(226.105 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_LT(fabs(353.764 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.1);
    EXPECT_LT(fabs(326.917 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(328.12 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(313.801 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(344.98 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    //Check our values for cell 1, 1
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 8;
    fMax = 16;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(353 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_GT(p_iNumSeedlings[2], 14); EXPECT_LT(p_iNumSeedlings[2], 31);
    EXPECT_LT(fabs(353 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_GT(p_iNumSeedlings[4], 14); EXPECT_LT(p_iNumSeedlings[4], 31);
    EXPECT_LT(fabs(353 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_EQ(0, p_iNumSeedlings[6]);

    //Check our values for cell 2, 2
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 16;
    fMax = 24;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(884.088 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_LT(fabs(425.8332 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.1);
    EXPECT_LT(fabs(921.0936 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(442.194 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(895.7808 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(425.526 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    //Check our values for cell 3, 3
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 24;
    fMax = 32;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(332.55 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_LT(fabs(352.784 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.1);
    EXPECT_LT(fabs(562.762 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(497.02 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(371.526 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(348.08 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    //Check our values for cell 4, 4
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 32;
    fMax = 40;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(514.865 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_LT(fabs(255.923 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.1);
    EXPECT_LT(fabs(905.418 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(457.311 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(500.969 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(681.351 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    //Check our values for cell 5, 5
    p_oAllSeedlings->StartOver();
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 40;
    fMax = 48;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(462 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_EQ(0, p_iNumSeedlings[2]);
    EXPECT_LT(fabs(980 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(278 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.13);
    EXPECT_LT(fabs(462 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(1000 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    //Check our values for cell 6, 6
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 48;
    fMax = 56;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(63.37 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.2);
    EXPECT_LT(fabs(54.1724 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.25);
    EXPECT_LT(fabs(952.9224 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(857.6868 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(61.5172 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.2);
    EXPECT_LT(fabs(51.9668 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.2);


    //Check our values for cell 7, 7
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 56;
    fMax = 64;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(308.59 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_LT(fabs(221.618 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.11);
    EXPECT_LT(fabs(942.308 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(447.316 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(302.414 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(377.756 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
   } catch (modelErr &e) {
     delete[] p_iNumSeedlings;
     delete p_oSimManager;
     FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
   }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun3()
// Performs run 3 of normal processing. WriteSubstrateDepSeedSurvivalXMLFile3() does setup. This
// run has no gap status. Grid cell size is 16 X 16 m for "Dispersed Seeds"
// and 8 X 8 m for "Substrate". There are seven species but the first is not
// used. Non-spatial disperse is used but given parameter values such that it
// will add no seeds. Establishment will turn our surviving seeds into
// seedlings. We are interested in 4 grid cells in "Substrate" and the
// corresponding single grid cell encompassing them in "Dispersed Seeds"; for
// each of these, the substrate proportions are set in the "Substrate" grid
// and 1000 seeds of each species are added to the "Dispersed Seeds" grid.
// Then the run progresses and the seedlings are counted.
/////////////////////////////////////////////////////////////////////////////
TEST(SubstrateDepSeedSurvival, TestNormalProcessingRun3) {

  float fValue;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  float fX, fY, fMin, fMax;
  int *p_iNumSeedlings = new int[7], i;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteSubstrateDepSeedSurvivalXMLFile3());

    clGrid *p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    clGrid *p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    clTreePopulation *p_oPop = (clTreePopulation*)p_oSimManager->GetPopulationObject("treepopulation");

    //For cell 0, 0, set 1000 seeds of each species
    fValue = 1000;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);

    //Set the substrate proportions for four cells
    fValue = 0;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.01;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.11;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.3168;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.5632;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0.17;
    p_oSubstrate->SetValueOfCell(0, 1, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.06;
    p_oSubstrate->SetValueOfCell(0, 1, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.04;
    p_oSubstrate->SetValueOfCell(0, 1, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.15;
    p_oSubstrate->SetValueOfCell(0, 1, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.2088;
    p_oSubstrate->SetValueOfCell(0, 1, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.3712;
    p_oSubstrate->SetValueOfCell(0, 1, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0.45;
    p_oSubstrate->SetValueOfCell(1, 0, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.09;
    p_oSubstrate->SetValueOfCell(1, 0, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 0, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.34;
    p_oSubstrate->SetValueOfCell(1, 0, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.0432;
    p_oSubstrate->SetValueOfCell(1, 0, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.0768;
    p_oSubstrate->SetValueOfCell(1, 0, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0.36;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.17;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.01;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.34;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.0432;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.0768;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    //Do the run but don't let substrate run
    clBehaviorBase * p_oTempBehavior;
    std::string sBehaviorName;
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oTempBehavior = p_oSimManager->GetBehaviorObject( i );
      sBehaviorName = p_oTempBehavior->GetName();
      if (sBehaviorName.compare("Substrate") != 0 )
      {
        p_oTempBehavior->Action();
      }
    }

    //Count the seedlings
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 0;
    fMax = 16;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(509.9275 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_LT(fabs(280.244 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.15);
    EXPECT_LT(fabs(847.759 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(678.398 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(483.6795 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(362.963 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
   } catch (modelErr &e) {
     delete[] p_iNumSeedlings;
     delete p_oSimManager;
     FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
   }
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun4()
// Performs run 4 of normal processing. WriteSubstrateDepSeedSurvivalXMLFile4() does setup. This
// run has microtopography. Grid cell size is default for all grids. There
// are seven species but the first is not used. Non-spatial disperse is used
// but given parameter values such that it will add no seeds. Establishment
// will turn our surviving seeds into seedlings. We are interested in 4 grid
// cells; for each of these, the substrate proportions are set in the
// "Substrate" grid and 1000 seeds of each species are added to the "Dispersed
// Seeds" grid. Then the run progresses and the seedlings are counted.
/////////////////////////////////////////////////////////////////////////////
TEST(SubstrateDepSeedSurvival, TestNormalProcessingRun4) {
  float fValue, fExpectedFav;
  clTreeSearch *p_oAllSeedlings;
  clTree *p_oTree;
  float fX, fY, fMin, fMax;
  int *p_iNumSeedlings = new int[7], i;
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Feed our file to the sim manager
    p_oSimManager->ReadFile(WriteSubstrateDepSeedSurvivalXMLFile4());

    clGrid *p_oSeeds = p_oSimManager->GetGridObject("Dispersed Seeds");
    clGrid *p_oSubstrate = p_oSimManager->GetGridObject("Substrate");
    clGrid *p_oSubsFav = p_oSimManager->GetGridObject("Substrate Favorability");
    clTreePopulation *p_oPop = (clTreePopulation*)p_oSimManager->GetPopulationObject("treepopulation");

    //For each of four cells, set 1000 seeds of each species
    fValue = 1000;
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(0, 0, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(1, 1, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(2, 2, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_1"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_2"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_3"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_4"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_5"), fValue);
    p_oSeeds->SetValueOfCell(3, 3, p_oSeeds->GetFloatDataCode("seeds_6"), fValue);

    //Set the substrate proportions for these same cells
    fValue = 0;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.42;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.01;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.345;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.135;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.09;
    p_oSubstrate->SetValueOfCell(0, 0, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 1;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(1, 1, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0.88;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.02;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0.03;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.04;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.018;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.012;
    p_oSubstrate->SetValueOfCell(2, 2, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    fValue = 0.12;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("scarsoil"), fValue);
    fValue = 0.09;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("freshlog"), fValue);
    fValue = 0;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("declog"), fValue);
    fValue = 0.2;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("tipup"), fValue);
    fValue = 0.354;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("fflitter"), fValue);
    fValue = 0.236;
    p_oSubstrate->SetValueOfCell(3, 3, p_oSubstrate->GetFloatDataCode("ffmoss"), fValue);

    //Do the run but don't let substrate run
    clBehaviorBase * p_oTempBehavior;
    std::string sBehaviorName;
    for (i = 0; i < p_oSimManager->GetNumberOfBehaviors(); i++) {
      p_oTempBehavior = p_oSimManager->GetBehaviorObject( i );
      sBehaviorName = p_oTempBehavior->GetName();
      if (sBehaviorName.compare("Substrate") != 0 )
      {
        p_oTempBehavior->Action();
      }
    }

    //Check the substrate favorabilities
    fExpectedFav = 0.486175;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.24732625;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.78065125;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.39688375;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.36781375;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.59120125;
    p_oSubsFav->GetValueOfCell(0, 0, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.43475;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.006;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.82325;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.2145;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.43475;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.75;
    p_oSubsFav->GetValueOfCell(1, 1, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.289718;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.4113;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.881613;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.690883;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.271812;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.144549;
    p_oSubsFav->GetValueOfCell(2, 2, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    fExpectedFav = 0.6541015;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index1"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.35942;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index2"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.7924515;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index3"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.578244;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index4"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.371596;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index5"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);
    fExpectedFav = 0.476012;
    p_oSubsFav->GetValueOfCell(3, 3, p_oSubsFav->GetFloatDataCode("Favorability Index6"), &fValue);
    EXPECT_LT(fabs(fExpectedFav - fValue), 0.001);

    //Count the seedlings
    p_oAllSeedlings = p_oPop->Find("type=1");

    //Check our values for cell 0, 0
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 0;
    fMax = 8;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(486.175 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_LT(fabs(247.32625 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.2);
    EXPECT_LT(fabs(780.65125 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(396.88375 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(367.81375 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(591.20125 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    //Check our values for cell 1, 1
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 8;
    fMax = 16;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(434.75 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_LT(p_iNumSeedlings[2], 12);
    EXPECT_LT(fabs(823.25 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(214.5 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.2);
    EXPECT_LT(fabs(434.75 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(750 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    //Check our values for cell 2, 2
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 16;
    fMax = 24;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(289.718 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.15);
    EXPECT_LT(fabs(411.3 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.1);
    EXPECT_LT(fabs(881.613 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(690.883 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(271.812 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.15);
    EXPECT_LT(fabs(144.549 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.15);


    //Check our values for cell 3, 3
    p_oAllSeedlings->StartOver();
    for (i = 0; i < 7; i++) {
      p_iNumSeedlings[i] = 0;
    }
    fMin = 24;
    fMax = 32;
    p_oTree = p_oAllSeedlings->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
      p_oTree->GetValue(p_oPop->GetYCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fY);
      if (fX >= fMin && fX < fMax && fY >= fMin && fY < fMax) {
        p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllSeedlings->NextTree();
    }
    EXPECT_EQ(0, p_iNumSeedlings[0]);
    EXPECT_LT(fabs(654.1015 - p_iNumSeedlings[1])/p_iNumSeedlings[1], 0.1);
    EXPECT_LT(fabs(359.42 - p_iNumSeedlings[2])/p_iNumSeedlings[2], 0.1);
    EXPECT_LT(fabs(792.4515 - p_iNumSeedlings[3])/p_iNumSeedlings[3], 0.1);
    EXPECT_LT(fabs(578.244 - p_iNumSeedlings[4])/p_iNumSeedlings[4], 0.1);
    EXPECT_LT(fabs(371.596 - p_iNumSeedlings[5])/p_iNumSeedlings[5], 0.1);
    EXPECT_LT(fabs(476.012 - p_iNumSeedlings[6])/p_iNumSeedlings[6], 0.1);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
   } catch (modelErr &e) {
     delete[] p_iNumSeedlings;
     delete p_oSimManager;
     FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
   }
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateDepSeedSurvivalXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateDepSeedSurvivalXMLFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteSubstrateDepSeedSurvivalCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NoGapSubstrateSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_7\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_7\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_6\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_7\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_5\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<Substrate2>"
       << "<su_scarSoilDecayAlpha>0</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>0</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>0</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>6.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_DecayedLogToForestFloor>0</su_DecayedLogToForestFloor>"
       << "<su_freshLogFromfflitter>0</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_2\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_3\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_4\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_5\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_6\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_7\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_2\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_3\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_4\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_5\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_6\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_7\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_2\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_3\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_4\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_5\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_6\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_7\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.64</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate2>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse3>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_6\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_7\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_5\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_6\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_7\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_5\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_6\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_7\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse3>"
       << "<SubstrateDependentSeedSurvival4>"
       << "<es_scarifiedSoilCanopyFav>"
       << "<es_sscfVal species=\"Species_2\">0.01</es_sscfVal>"
       << "<es_sscfVal species=\"Species_3\">0.017</es_sscfVal>"
       << "<es_sscfVal species=\"Species_4\">0.96</es_sscfVal>"
       << "<es_sscfVal species=\"Species_5\">0.92</es_sscfVal>"
       << "<es_sscfVal species=\"Species_6\">0.01</es_sscfVal>"
       << "<es_sscfVal species=\"Species_7\">0</es_sscfVal>"
       << "</es_scarifiedSoilCanopyFav>"
       << "<es_tipUpCanopyFav>"
       << "<es_tucfVal species=\"Species_2\">0.315</es_tucfVal>"
       << "<es_tucfVal species=\"Species_3\">0.48</es_tucfVal>"
       << "<es_tucfVal species=\"Species_4\">0.95</es_tucfVal>"
       << "<es_tucfVal species=\"Species_5\">0.48</es_tucfVal>"
       << "<es_tucfVal species=\"Species_6\">0.315</es_tucfVal>"
       << "<es_tucfVal species=\"Species_7\">0.48</es_tucfVal>"
       << "</es_tipUpCanopyFav>"
       << "<es_freshLogCanopyFav>"
       << "<es_flcfVal species=\"Species_2\">0.462</es_flcfVal>"
       << "<es_flcfVal species=\"Species_3\">0</es_flcfVal>"
       << "<es_flcfVal species=\"Species_4\">0.98</es_flcfVal>"
       << "<es_flcfVal species=\"Species_5\">0.278</es_flcfVal>"
       << "<es_flcfVal species=\"Species_6\">0.462</es_flcfVal>"
       << "<es_flcfVal species=\"Species_7\">1</es_flcfVal>"
       << "</es_freshLogCanopyFav>"
       << "<es_decayedLogCanopyFav>"
       << "<es_dlcfVal species=\"Species_2\">0.155</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_3\">0.278</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_4\">0.99</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_5\">0</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_6\">0.155</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_7\">0</es_dlcfVal>"
       << "</es_decayedLogCanopyFav>"
       << "<es_forestFloorLitterCanopyFav>"
       << "<es_fflcfVal species=\"Species_2\">1</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_3\">0.391</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_4\">0.92</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_5\">0.391</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_6\">0.88</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_7\">0.391</es_fflcfVal>"
       << "</es_forestFloorLitterCanopyFav>"
       << "<es_forestFloorMossCanopyFav>"
       << "<es_ffmcfVal species=\"Species_2\">0.9</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_3\">0.388</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_4\">0.567</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_5\">0.995</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_6\">0.871</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_7\">0.445</es_ffmcfVal>"
       << "</es_forestFloorMossCanopyFav>"
       << "</SubstrateDependentSeedSurvival4>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateDepSeedSurvivalXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateDepSeedSurvivalXMLFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteSubstrateDepSeedSurvivalCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GapDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>GapSubstrateSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_7\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_7\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_6\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_7\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_5\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<Substrate2>"
       << "<su_scarSoilDecayAlpha>-5.1E-4</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>-7.0E-4</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>6.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_DecayedLogToForestFloor>0.55</su_DecayedLogToForestFloor>"
       << "<su_freshLogFromfflitter>0.0080</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_2\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_3\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_4\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_5\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_6\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_7\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_2\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_3\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_4\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_5\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_6\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_7\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_2\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_3\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_4\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_5\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_6\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_7\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.64</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate2>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<GapDisperse3>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_6\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_7\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_weibullCanopySTR>"
       << "<di_wcsVal species=\"Species_7\">0</di_wcsVal>"
       << "<di_wcsVal species=\"Species_6\">0</di_wcsVal>"
       << "<di_wcsVal species=\"Species_5\">0</di_wcsVal>"
       << "<di_wcsVal species=\"Species_4\">0</di_wcsVal>"
       << "<di_wcsVal species=\"Species_3\">0</di_wcsVal>"
       << "<di_wcsVal species=\"Species_2\">0</di_wcsVal>"
       << "</di_weibullCanopySTR>"
       << "<di_weibullCanopyBeta>"
       << "<di_wcbVal species=\"Species_7\">2.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_6\">2.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_5\">2.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_4\">2.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_3\">2.0</di_wcbVal>"
       << "<di_wcbVal species=\"Species_2\">2.0</di_wcbVal>"
       << "</di_weibullCanopyBeta>"
       << "<di_weibullCanopyDispersal>"
       << "<di_wcdVal species=\"Species_7\">1.76E-4</di_wcdVal>"
       << "<di_wcdVal species=\"Species_6\">1.76E-4</di_wcdVal>"
       << "<di_wcdVal species=\"Species_5\">1.76E-4</di_wcdVal>"
       << "<di_wcdVal species=\"Species_4\">1.76E-4</di_wcdVal>"
       << "<di_wcdVal species=\"Species_3\">1.76E-4</di_wcdVal>"
       << "<di_wcdVal species=\"Species_2\">1.76E-4</di_wcdVal>"
       << "</di_weibullCanopyDispersal>"
       << "<di_weibullCanopyTheta>"
       << "<di_wctVal species=\"Species_7\">3.0</di_wctVal>"
       << "<di_wctVal species=\"Species_6\">3.0</di_wctVal>"
       << "<di_wctVal species=\"Species_5\">3.0</di_wctVal>"
       << "<di_wctVal species=\"Species_4\">3.0</di_wctVal>"
       << "<di_wctVal species=\"Species_3\">3.0</di_wctVal>"
       << "<di_wctVal species=\"Species_2\">3.0</di_wctVal>"
       << "</di_weibullCanopyTheta>"
       << "<di_weibullGapSTR>"
       << "<di_wgsVal species=\"Species_7\">0</di_wgsVal>"
       << "<di_wgsVal species=\"Species_6\">0</di_wgsVal>"
       << "<di_wgsVal species=\"Species_5\">0</di_wgsVal>"
       << "<di_wgsVal species=\"Species_4\">0</di_wgsVal>"
       << "<di_wgsVal species=\"Species_3\">0</di_wgsVal>"
       << "<di_wgsVal species=\"Species_2\">0</di_wgsVal>"
       << "</di_weibullGapSTR>"
       << "<di_weibullGapBeta>"
       << "<di_wgbVal species=\"Species_2\">2.3</di_wgbVal>"
       << "<di_wgbVal species=\"Species_3\">2.3</di_wgbVal>"
       << "<di_wgbVal species=\"Species_4\">2.3</di_wgbVal>"
       << "<di_wgbVal species=\"Species_5\">2.3</di_wgbVal>"
       << "<di_wgbVal species=\"Species_6\">2.3</di_wgbVal>"
       << "<di_wgbVal species=\"Species_7\">2.3</di_wgbVal>"
       << "</di_weibullGapBeta>"
       << "<di_weibullGapDispersal>"
       << "<di_wgdVal species=\"Species_2\">1.32E-4</di_wgdVal>"
       << "<di_wgdVal species=\"Species_3\">1.32E-4</di_wgdVal>"
       << "<di_wgdVal species=\"Species_4\">1.32E-4</di_wgdVal>"
       << "<di_wgdVal species=\"Species_5\">1.32E-4</di_wgdVal>"
       << "<di_wgdVal species=\"Species_6\">1.32E-4</di_wgdVal>"
       << "<di_wgdVal species=\"Species_7\">1.32E-4</di_wgdVal>"
       << "</di_weibullGapDispersal>"
       << "<di_weibullGapTheta>"
       << "<di_wgtVal species=\"Species_2\">3.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_3\">3.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_4\">3.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_5\">3.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_6\">3.0</di_wgtVal>"
       << "<di_wgtVal species=\"Species_7\">3.0</di_wgtVal>"
       << "</di_weibullGapTheta>"
       << "<di_maxGapDensity>0</di_maxGapDensity>"
       << "<di_gapFunction>"
       << "<di_gfVal species=\"Species_7\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_6\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_5\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_4\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_3\">0</di_gfVal>"
       << "<di_gfVal species=\"Species_2\">0</di_gfVal>"
       << "</di_gapFunction>"
       << "<di_canopyFunction>"
       << "<di_cfVal species=\"Species_7\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_6\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_5\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_4\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_3\">0</di_cfVal>"
       << "<di_cfVal species=\"Species_2\">0</di_cfVal>"
       << "</di_canopyFunction>"
       << "</GapDisperse3>"
       << "<SubstrateDependentSeedSurvival4>"
       << "<es_scarifiedSoilCanopyFav>"
       << "<es_sscfVal species=\"Species_2\">0.01</es_sscfVal>"
       << "<es_sscfVal species=\"Species_3\">0.017</es_sscfVal>"
       << "<es_sscfVal species=\"Species_4\">0.96</es_sscfVal>"
       << "<es_sscfVal species=\"Species_5\">0.92</es_sscfVal>"
       << "<es_sscfVal species=\"Species_6\">0.01</es_sscfVal>"
       << "<es_sscfVal species=\"Species_7\">0</es_sscfVal>"
       << "</es_scarifiedSoilCanopyFav>"
       << "<es_tipUpCanopyFav>"
       << "<es_tucfVal species=\"Species_2\">0.315</es_tucfVal>"
       << "<es_tucfVal species=\"Species_3\">0.48</es_tucfVal>"
       << "<es_tucfVal species=\"Species_4\">0.95</es_tucfVal>"
       << "<es_tucfVal species=\"Species_5\">0.48</es_tucfVal>"
       << "<es_tucfVal species=\"Species_6\">0.315</es_tucfVal>"
       << "<es_tucfVal species=\"Species_7\">0.48</es_tucfVal>"
       << "</es_tipUpCanopyFav>"
       << "<es_freshLogCanopyFav>"
       << "<es_flcfVal species=\"Species_2\">0.462</es_flcfVal>"
       << "<es_flcfVal species=\"Species_3\">0</es_flcfVal>"
       << "<es_flcfVal species=\"Species_4\">0.98</es_flcfVal>"
       << "<es_flcfVal species=\"Species_5\">0.278</es_flcfVal>"
       << "<es_flcfVal species=\"Species_6\">0.462</es_flcfVal>"
       << "<es_flcfVal species=\"Species_7\">1</es_flcfVal>"
       << "</es_freshLogCanopyFav>"
       << "<es_decayedLogCanopyFav>"
       << "<es_dlcfVal species=\"Species_2\">0.155</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_3\">0.278</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_4\">0.99</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_5\">0</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_6\">0.155</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_7\">0</es_dlcfVal>"
       << "</es_decayedLogCanopyFav>"
       << "<es_forestFloorLitterCanopyFav>"
       << "<es_fflcfVal species=\"Species_2\">1</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_3\">0.391</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_4\">0.92</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_5\">0.391</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_6\">0.88</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_7\">0.391</es_fflcfVal>"
       << "</es_forestFloorLitterCanopyFav>"
       << "<es_forestFloorMossCanopyFav>"
       << "<es_ffmcfVal species=\"Species_2\">0.9</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_3\">0.388</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_4\">0.567</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_5\">0.995</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_6\">0.871</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_7\">0.445</es_ffmcfVal>"
       << "</es_forestFloorMossCanopyFav>"
       << "<es_scarifiedSoilGapFav>"
       << "<es_ssgfVal species=\"Species_2\">0.983</es_ssgfVal>"
       << "<es_ssgfVal species=\"Species_3\">0.424</es_ssgfVal>"
       << "<es_ssgfVal species=\"Species_4\">0.983</es_ssgfVal>"
       << "<es_ssgfVal species=\"Species_5\">0.424</es_ssgfVal>"
       << "<es_ssgfVal species=\"Species_6\">0.983</es_ssgfVal>"
       << "<es_ssgfVal species=\"Species_7\">0.424</es_ssgfVal>"
       << "</es_scarifiedSoilGapFav>"
       << "<es_tipUpGapFav>"
       << "<es_tugfVal species=\"Species_2\">0.009</es_tugfVal>"
       << "<es_tugfVal species=\"Species_3\">0.413</es_tugfVal>"
       << "<es_tugfVal species=\"Species_4\">0.009</es_tugfVal>"
       << "<es_tugfVal species=\"Species_5\">0.413</es_tugfVal>"
       << "<es_tugfVal species=\"Species_6\">0.009</es_tugfVal>"
       << "<es_tugfVal species=\"Species_7\">0.413</es_tugfVal>"
       << "</es_tipUpGapFav>"
       << "<es_freshLogGapFav>"
       << "<es_flgfVal species=\"Species_2\">0.353</es_flgfVal>"
       << "<es_flgfVal species=\"Species_3\">0.024</es_flgfVal>"
       << "<es_flgfVal species=\"Species_4\">0.353</es_flgfVal>"
       << "<es_flgfVal species=\"Species_5\">0.024</es_flgfVal>"
       << "<es_flgfVal species=\"Species_6\">0.353</es_flgfVal>"
       << "<es_flgfVal species=\"Species_7\">0</es_flgfVal>"
       << "</es_freshLogGapFav>"
       << "<es_decayedLogGapFav>"
       << "<es_dlgfVal species=\"Species_2\">0.058</es_dlgfVal>"
       << "<es_dlgfVal species=\"Species_3\">0.31</es_dlgfVal>"
       << "<es_dlgfVal species=\"Species_4\">0.88</es_dlgfVal>"
       << "<es_dlgfVal species=\"Species_5\">1</es_dlgfVal>"
       << "<es_dlgfVal species=\"Species_6\">0.058</es_dlgfVal>"
       << "<es_dlgfVal species=\"Species_7\">0.31</es_dlgfVal>"
       << "</es_decayedLogGapFav>"
       << "<es_forestFloorLitterGapFav>"
       << "<es_fflgfVal species=\"Species_2\">0.88</es_fflgfVal>"
       << "<es_fflgfVal species=\"Species_3\">0.771</es_fflgfVal>"
       << "<es_fflgfVal species=\"Species_4\">0.88</es_fflgfVal>"
       << "<es_fflgfVal species=\"Species_5\">0.771</es_fflgfVal>"
       << "<es_fflgfVal species=\"Species_6\">0.88</es_fflgfVal>"
       << "<es_fflgfVal species=\"Species_7\">0.771</es_fflgfVal>"
       << "</es_forestFloorLitterGapFav>"
       << "<es_forestFloorMossGapFav>"
       << "<es_ffmgfVal species=\"Species_2\">0.02</es_ffmgfVal>"
       << "<es_ffmgfVal species=\"Species_3\">0.942</es_ffmgfVal>"
       << "<es_ffmgfVal species=\"Species_4\">0.663</es_ffmgfVal>"
       << "<es_ffmgfVal species=\"Species_5\">0.716</es_ffmgfVal>"
       << "<es_ffmgfVal species=\"Species_6\">0.629</es_ffmgfVal>"
       << "<es_ffmgfVal species=\"Species_7\">0.951</es_ffmgfVal>"
       << "</es_forestFloorMossGapFav>"
       << "</SubstrateDependentSeedSurvival4>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateDepSeedSurvivalXMLFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateDepSeedSurvivalXMLFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteSubstrateDepSeedSurvivalCommonStuff(oOut);

  oOut << "<grid gridName=\"Dispersed Seeds\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"seeds_0\">0</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_1\">1</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_2\">2</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_3\">3</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_4\">4</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_5\">5</ma_floatCode>"
       << "<ma_floatCode label=\"seeds_6\">5</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_intCodes>"
       << "<ma_intCode label=\"count\">1</ma_intCode>"
       << "</ma_intCodes>"
       << "<ma_boolCodes>"
       << "<ma_boolCode label=\"Is Gap\">0</ma_boolCode>"
       << "</ma_boolCodes>"
       << "<ma_lengthXCells>16</ma_lengthXCells>"
       << "<ma_lengthYCells>16</ma_lengthYCells>";

  oOut << "</grid>"
       << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NoGapSubstrateSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_7\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_7\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_6\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_7\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_5\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<Substrate2>"
       << "<su_scarSoilDecayAlpha>-5.1E-4</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>-7.0E-4</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>6.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_DecayedLogToForestFloor>0.55</su_DecayedLogToForestFloor>"
       << "<su_freshLogFromfflitter>0.0080</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_2\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_3\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_4\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_5\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_6\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_7\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_2\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_3\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_4\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_5\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_6\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_7\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_2\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_3\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_4\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_5\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_6\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_7\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.64</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate2>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse3>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_6\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_7\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_5\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_6\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_7\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_5\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_6\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_7\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse3>"
       << "<SubstrateDependentSeedSurvival4>"
       << "<es_scarifiedSoilCanopyFav>"
       << "<es_sscfVal species=\"Species_2\">0.01</es_sscfVal>"
       << "<es_sscfVal species=\"Species_3\">0.017</es_sscfVal>"
       << "<es_sscfVal species=\"Species_4\">0.96</es_sscfVal>"
       << "<es_sscfVal species=\"Species_5\">0.92</es_sscfVal>"
       << "<es_sscfVal species=\"Species_6\">0.01</es_sscfVal>"
       << "<es_sscfVal species=\"Species_7\">0</es_sscfVal>"
       << "</es_scarifiedSoilCanopyFav>"
       << "<es_tipUpCanopyFav>"
       << "<es_tucfVal species=\"Species_2\">0.315</es_tucfVal>"
       << "<es_tucfVal species=\"Species_3\">0.48</es_tucfVal>"
       << "<es_tucfVal species=\"Species_4\">0.95</es_tucfVal>"
       << "<es_tucfVal species=\"Species_5\">0.48</es_tucfVal>"
       << "<es_tucfVal species=\"Species_6\">0.315</es_tucfVal>"
       << "<es_tucfVal species=\"Species_7\">0.48</es_tucfVal>"
       << "</es_tipUpCanopyFav>"
       << "<es_freshLogCanopyFav>"
       << "<es_flcfVal species=\"Species_2\">0.462</es_flcfVal>"
       << "<es_flcfVal species=\"Species_3\">0</es_flcfVal>"
       << "<es_flcfVal species=\"Species_4\">0.98</es_flcfVal>"
       << "<es_flcfVal species=\"Species_5\">0.278</es_flcfVal>"
       << "<es_flcfVal species=\"Species_6\">0.462</es_flcfVal>"
       << "<es_flcfVal species=\"Species_7\">1</es_flcfVal>"
       << "</es_freshLogCanopyFav>"
       << "<es_decayedLogCanopyFav>"
       << "<es_dlcfVal species=\"Species_2\">0.155</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_3\">0.278</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_4\">0.99</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_5\">0</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_6\">0.155</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_7\">0</es_dlcfVal>"
       << "</es_decayedLogCanopyFav>"
       << "<es_forestFloorLitterCanopyFav>"
       << "<es_fflcfVal species=\"Species_2\">1</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_3\">0.391</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_4\">0.92</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_5\">0.391</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_6\">0.88</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_7\">0.391</es_fflcfVal>"
       << "</es_forestFloorLitterCanopyFav>"
       << "<es_forestFloorMossCanopyFav>"
       << "<es_ffmcfVal species=\"Species_2\">0.9</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_3\">0.388</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_4\">0.567</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_5\">0.995</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_6\">0.871</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_7\">0.445</es_ffmcfVal>"
       << "</es_forestFloorMossCanopyFav>"
       << "</SubstrateDependentSeedSurvival4>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateDepSeedSurvivalXMLFile4()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateDepSeedSurvivalXMLFile4()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  WriteSubstrateDepSeedSurvivalCommonStuff(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_6\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_7\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>MicrotopographicSubstrateSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_7\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_3\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_5\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_6\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_7\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_6\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_7\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_5\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<Substrate2>"
       << "<su_scarSoilDecayAlpha>0</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>0</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>0</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>6.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_DecayedLogToForestFloor>0</su_DecayedLogToForestFloor>"
       << "<su_freshLogFromfflitter>0</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_2\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_3\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_4\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_5\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_6\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_7\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_2\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_3\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_4\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_5\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_6\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_7\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_2\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_3\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_4\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_5\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_6\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_7\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.4</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate2>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse3>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_3\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_4\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_5\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_6\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_7\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_4\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_3\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_5\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_6\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_7\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_4\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_3\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_5\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_6\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_7\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse3>"
       << "<SubstrateDependentSeedSurvival4>"
       << "<es_scarifiedSoilCanopyFav>"
       << "<es_sscfVal species=\"Species_2\">0.983</es_sscfVal>"
       << "<es_sscfVal species=\"Species_3\">0.424</es_sscfVal>"
       << "<es_sscfVal species=\"Species_4\">0.683</es_sscfVal>"
       << "<es_sscfVal species=\"Species_5\">0.155</es_sscfVal>"
       << "<es_sscfVal species=\"Species_6\">0.983</es_sscfVal>"
       << "<es_sscfVal species=\"Species_7\">0.424</es_sscfVal>"
       << "</es_scarifiedSoilCanopyFav>"
       << "<es_tipUpCanopyFav>"
       << "<es_tucfVal species=\"Species_2\">0.155</es_tucfVal>"
       << "<es_tucfVal species=\"Species_3\">0.413</es_tucfVal>"
       << "<es_tucfVal species=\"Species_4\">0.009</es_tucfVal>"
       << "<es_tucfVal species=\"Species_5\">0.413</es_tucfVal>"
       << "<es_tucfVal species=\"Species_6\">0.009</es_tucfVal>"
       << "<es_tucfVal species=\"Species_7\">0.413</es_tucfVal>"
       << "</es_tipUpCanopyFav>"
       << "<es_freshLogCanopyFav>"
       << "<es_flcfVal species=\"Species_2\">0.353</es_flcfVal>"
       << "<es_flcfVal species=\"Species_3\">0.024</es_flcfVal>"
       << "<es_flcfVal species=\"Species_4\">0.353</es_flcfVal>"
       << "<es_flcfVal species=\"Species_5\">0.024</es_flcfVal>"
       << "<es_flcfVal species=\"Species_6\">0.353</es_flcfVal>"
       << "<es_flcfVal species=\"Species_7\">0</es_flcfVal>"
       << "</es_freshLogCanopyFav>"
       << "<es_decayedLogCanopyFav>"
       << "<es_dlcfVal species=\"Species_2\">0.058</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_3\">0.31</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_4\">0.88</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_5\">1</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_6\">0.058</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_7\">0.31</es_dlcfVal>"
       << "</es_decayedLogCanopyFav>"
       << "<es_forestFloorLitterCanopyFav>"
       << "<es_fflcfVal species=\"Species_2\">0.88</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_3\">0.331</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_4\">0.88</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_5\">0.771</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_6\">0.88</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_7\">0.771</es_fflcfVal>"
       << "</es_forestFloorLitterCanopyFav>"
       << "<es_forestFloorMossCanopyFav>"
       << "<es_ffmcfVal species=\"Species_2\">0.456</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_3\">0.23</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_4\">0.78</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_5\">0.52</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_6\">0.338</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_7\">0.887</es_ffmcfVal>"
       << "</es_forestFloorMossCanopyFav>"
       << "<es_scarifiedSoilMoundFav>"
       << "<es_ssmfVal species=\"Species_2\">0.01</es_ssmfVal>"
       << "<es_ssmfVal species=\"Species_3\">0.424</es_ssmfVal>"
       << "<es_ssmfVal species=\"Species_4\">0.96</es_ssmfVal>"
       << "<es_ssmfVal species=\"Species_5\">0.92</es_ssmfVal>"
       << "<es_ssmfVal species=\"Species_6\">0.01</es_ssmfVal>"
       << "<es_ssmfVal species=\"Species_7\">0</es_ssmfVal>"
       << "</es_scarifiedSoilMoundFav>"
       << "<es_tipUpMoundFav>"
       << "<es_tumfVal species=\"Species_2\">0.315</es_tumfVal>"
       << "<es_tumfVal species=\"Species_3\">0.48</es_tumfVal>"
       << "<es_tumfVal species=\"Species_4\">0.95</es_tumfVal>"
       << "<es_tumfVal species=\"Species_5\">0.48</es_tumfVal>"
       << "<es_tumfVal species=\"Species_6\">0.315</es_tumfVal>"
       << "<es_tumfVal species=\"Species_7\">0.48</es_tumfVal>"
       << "</es_tipUpMoundFav>"
       << "<es_freshLogMoundFav>"
       << "<es_flmfVal species=\"Species_2\">0.462</es_flmfVal>"
       << "<es_flmfVal species=\"Species_3\">0</es_flmfVal>"
       << "<es_flmfVal species=\"Species_4\">0.98</es_flmfVal>"
       << "<es_flmfVal species=\"Species_5\">0.278</es_flmfVal>"
       << "<es_flmfVal species=\"Species_6\">0.462</es_flmfVal>"
       << "<es_flmfVal species=\"Species_7\">1</es_flmfVal>"
       << "</es_freshLogMoundFav>"
       << "<es_decayedLogMoundFav>"
       << "<es_dlmfVal species=\"Species_2\">0.88</es_dlmfVal>"
       << "<es_dlmfVal species=\"Species_3\">0.278</es_dlmfVal>"
       << "<es_dlmfVal species=\"Species_4\">0.99</es_dlmfVal>"
       << "<es_dlmfVal species=\"Species_5\">0</es_dlmfVal>"
       << "<es_dlmfVal species=\"Species_6\">0.771</es_dlmfVal>"
       << "<es_dlmfVal species=\"Species_7\">0</es_dlmfVal>"
       << "</es_decayedLogMoundFav>"
       << "<es_forestFloorLitterMoundFav>"
       << "<es_fflmfVal species=\"Species_2\">1</es_fflmfVal>"
       << "<es_fflmfVal species=\"Species_3\">0.391</es_fflmfVal>"
       << "<es_fflmfVal species=\"Species_4\">0.92</es_fflmfVal>"
       << "<es_fflmfVal species=\"Species_5\">0.391</es_fflmfVal>"
       << "<es_fflmfVal species=\"Species_6\">0.009</es_fflmfVal>"
       << "<es_fflmfVal species=\"Species_7\">0.391</es_fflmfVal>"
       << "</es_forestFloorLitterMoundFav>"
       << "<es_forestFloorMossMoundFav>"
       << "<es_ffmmfVal species=\"Species_2\">0.9</es_ffmmfVal>"
       << "<es_ffmmfVal species=\"Species_3\">0.388</es_ffmmfVal>"
       << "<es_ffmmfVal species=\"Species_4\">0.567</es_ffmmfVal>"
       << "<es_ffmmfVal species=\"Species_5\">0.995</es_ffmmfVal>"
       << "<es_ffmmfVal species=\"Species_6\">0.871</es_ffmmfVal>"
       << "<es_ffmmfVal species=\"Species_7\">0.445</es_ffmmfVal>"
       << "</es_forestFloorMossMoundFav>"
       << "<es_moundProportion>0.75</es_moundProportion>"
       << "</SubstrateDependentSeedSurvival4>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateDepSeedSurvivalXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateDepSeedSurvivalXMLErrorFile1()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NoGapSubstrateSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>5</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<Substrate2>"
       << "<su_scarSoilDecayAlpha>-5.1E-4</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>-7.0E-4</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>6.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_DecayedLogToForestFloor>0.55</su_DecayedLogToForestFloor>"
       << "<su_freshLogFromfflitter>0.0080</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_2\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_1\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_2\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_1\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_2\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.64</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate2>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse3>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse3>"
       << "<SubstrateDependentSeedSurvival4>"
       << "<es_scarifiedSoilCanopyFav>"
       << "<es_sscfVal species=\"Species_2\">0.01</es_sscfVal>"
       << "<es_sscfVal species=\"Species_1\">0.017</es_sscfVal>"
       << "</es_scarifiedSoilCanopyFav>"
       << "<es_tipUpCanopyFav>"
       << "<es_tucfVal species=\"Species_2\">0.315</es_tucfVal>"
       << "<es_tucfVal species=\"Species_1\">0.48</es_tucfVal>"
       << "</es_tipUpCanopyFav>"
       << "<es_freshLogCanopyFav>"
       << "<es_flcfVal species=\"Species_2\">0.462</es_flcfVal>"
       << "<es_flcfVal species=\"Species_1\">0</es_flcfVal>"
       << "</es_freshLogCanopyFav>"
       << "<es_decayedLogCanopyFav>"
       << "<es_dlcfVal species=\"Species_2\">1.155</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_1\">0.278</es_dlcfVal>"
       << "</es_decayedLogCanopyFav>"
       << "<es_forestFloorLitterCanopyFav>"
       << "<es_fflcfVal species=\"Species_2\">1</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_1\">0.391</es_fflcfVal>"
       << "</es_forestFloorLitterCanopyFav>"
       << "<es_forestFloorMossCanopyFav>"
       << "<es_ffmcfVal species=\"Species_2\">0.9</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_1\">0.388</es_ffmcfVal>"
       << "</es_forestFloorMossCanopyFav>"
       << "</SubstrateDependentSeedSurvival4>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateDepSeedSurvivalXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateDepSeedSurvivalXMLErrorFile2()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>NonSpatialDisperse</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NoGapSubstrateSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<GeneralDisperse>"
       << "<di_seedDistributionMethod>0</di_seedDistributionMethod>"
       << "</GeneralDisperse>"
       << "<NonSpatialDisperse1>"
       << "<di_minDbhForReproduction>"
       << "<di_mdfrVal species=\"Species_2\">15.0</di_mdfrVal>"
       << "<di_mdfrVal species=\"Species_1\">15.0</di_mdfrVal>"
       << "</di_minDbhForReproduction>"
       << "<di_nonSpatialSlopeOfLambda>"
       << "<di_nssolVal species=\"Species_1\">0</di_nssolVal>"
       << "<di_nssolVal species=\"Species_2\">0</di_nssolVal>"
       << "</di_nonSpatialSlopeOfLambda>"
       << "<di_nonSpatialInterceptOfLambda>"
       << "<di_nsiolVal species=\"Species_1\">0</di_nsiolVal>"
       << "<di_nsiolVal species=\"Species_2\">0</di_nsiolVal>"
       << "</di_nonSpatialInterceptOfLambda>"
       << "</NonSpatialDisperse1>"
       << "<SubstrateDependentSeedSurvival2>"
       << "<es_scarifiedSoilCanopyFav>"
       << "<es_sscfVal species=\"Species_2\">0.01</es_sscfVal>"
       << "<es_sscfVal species=\"Species_1\">0.017</es_sscfVal>"
       << "</es_scarifiedSoilCanopyFav>"
       << "<es_tipUpCanopyFav>"
       << "<es_tucfVal species=\"Species_2\">0.315</es_tucfVal>"
       << "<es_tucfVal species=\"Species_1\">0.48</es_tucfVal>"
       << "</es_tipUpCanopyFav>"
       << "<es_freshLogCanopyFav>"
       << "<es_flcfVal species=\"Species_2\">0.462</es_flcfVal>"
       << "<es_flcfVal species=\"Species_1\">0</es_flcfVal>"
       << "</es_freshLogCanopyFav>"
       << "<es_decayedLogCanopyFav>"
       << "<es_dlcfVal species=\"Species_2\">0.155</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_1\">0.278</es_dlcfVal>"
       << "</es_decayedLogCanopyFav>"
       << "<es_forestFloorLitterCanopyFav>"
       << "<es_fflcfVal species=\"Species_2\">1</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_1\">0.391</es_fflcfVal>"
       << "</es_forestFloorLitterCanopyFav>"
       << "<es_forestFloorMossCanopyFav>"
       << "<es_ffmcfVal species=\"Species_2\">0.9</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_1\">0.388</es_ffmcfVal>"
       << "</es_forestFloorMossCanopyFav>"
       << "</SubstrateDependentSeedSurvival2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateDepSeedSurvivalXMLErrorFile3()
/////////////////////////////////////////////////////////////////////////////
const char* WriteSubstrateDepSeedSurvivalXMLErrorFile3()
{
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Substrate</behaviorName>"
       << "<version>2.1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>NoGapSubstrateSeedSurvival</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>Establishment</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Seed\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seed\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality1>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality1>"
       << "<Substrate2>"
       << "<su_scarSoilDecayAlpha>-5.1E-4</su_scarSoilDecayAlpha>"
       << "<su_scarSoilDecayBeta>4.4</su_scarSoilDecayBeta>"
       << "<su_tipupDecayAlpha>-7.0E-4</su_tipupDecayAlpha>"
       << "<su_tipupDecayBeta>4.3</su_tipupDecayBeta>"
       << "<su_freshLogDecayAlpha>-0.05</su_freshLogDecayAlpha>"
       << "<su_freshLogDecayBeta>6.5</su_freshLogDecayBeta>"
       << "<su_decayedLogDecayAlpha>-0.7985</su_decayedLogDecayAlpha>"
       << "<su_decayedLogDecayBeta>1.1</su_decayedLogDecayBeta>"
       << "<su_DecayedLogToForestFloor>0.55</su_DecayedLogToForestFloor>"
       << "<su_freshLogFromfflitter>0.0080</su_freshLogFromfflitter>"
       << "<su_maxNumberDecayYears>10</su_maxNumberDecayYears>"
       << "<su_initialScarSoil>0.0</su_initialScarSoil>"
       << "<su_initialTipup>0.0</su_initialTipup>"
       << "<su_initialFreshLog>0.01</su_initialFreshLog>"
       << "<su_initialDecayedLog>0.11</su_initialDecayedLog>"
       << "<su_propOfDeadFall>"
       << "<su_podfVal species=\"Species_2\">0</su_podfVal>"
       << "<su_podfVal species=\"Species_1\">0</su_podfVal>"
       << "</su_propOfDeadFall>"
       << "<su_propOfFallUproot>"
       << "<su_pofuVal species=\"Species_2\">0</su_pofuVal>"
       << "<su_pofuVal species=\"Species_1\">0</su_pofuVal>"
       << "</su_propOfFallUproot>"
       << "<su_propOfSnagsUproot>"
       << "<su_posuVal species=\"Species_1\">0</su_posuVal>"
       << "<su_posuVal species=\"Species_2\">0</su_posuVal>"
       << "</su_propOfSnagsUproot>"
       << "<su_rootTipupFactor>3.0</su_rootTipupFactor>"
       << "<su_mossProportion>0.64</su_mossProportion>"
       << "<su_directionalTreeFall>1</su_directionalTreeFall>"
       << "</Substrate2>"
       << "<SubstrateDependentSeedSurvival3>"
       << "<es_scarifiedSoilCanopyFav>"
       << "<es_sscfVal species=\"Species_2\">0.01</es_sscfVal>"
       << "<es_sscfVal species=\"Species_1\">0.017</es_sscfVal>"
       << "</es_scarifiedSoilCanopyFav>"
       << "<es_tipUpCanopyFav>"
       << "<es_tucfVal species=\"Species_2\">0.315</es_tucfVal>"
       << "<es_tucfVal species=\"Species_1\">0.48</es_tucfVal>"
       << "</es_tipUpCanopyFav>"
       << "<es_freshLogCanopyFav>"
       << "<es_flcfVal species=\"Species_2\">0.462</es_flcfVal>"
       << "<es_flcfVal species=\"Species_1\">0</es_flcfVal>"
       << "</es_freshLogCanopyFav>"
       << "<es_decayedLogCanopyFav>"
       << "<es_dlcfVal species=\"Species_2\">0.155</es_dlcfVal>"
       << "<es_dlcfVal species=\"Species_1\">0.278</es_dlcfVal>"
       << "</es_decayedLogCanopyFav>"
       << "<es_forestFloorLitterCanopyFav>"
       << "<es_fflcfVal species=\"Species_2\">1</es_fflcfVal>"
       << "<es_fflcfVal species=\"Species_1\">0.391</es_fflcfVal>"
       << "</es_forestFloorLitterCanopyFav>"
       << "<es_forestFloorMossCanopyFav>"
       << "<es_ffmcfVal species=\"Species_2\">0.9</es_ffmcfVal>"
       << "<es_ffmcfVal species=\"Species_1\">0.388</es_ffmcfVal>"
       << "</es_forestFloorMossCanopyFav>"
       << "</SubstrateDependentSeedSurvival3>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}



/////////////////////////////////////////////////////////////////////////////
// WriteSubstrateDepSeedSurvivalCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteSubstrateDepSeedSurvivalCommonStuff( std::fstream &oOut )
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>2</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>100.0</plot_lenX>"
       << "<plot_lenY>100.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
       << "<plot_temp_C>12.88171785</plot_temp_C>"
       << "<plot_latitude>55.37</plot_latitude>"
       << "</plot>"
       << "<trees>"
       << "<tr_speciesList>"
       << "<tr_species speciesName=\"Species_1\" />"
       << "<tr_species speciesName=\"Species_2\" />"
       << "<tr_species speciesName=\"Species_3\" />"
       << "<tr_species speciesName=\"Species_4\" />"
       << "<tr_species speciesName=\"Species_5\" />"
       << "<tr_species speciesName=\"Species_6\" />"
       << "<tr_species speciesName=\"Species_7\" />"
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_6\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_7\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_6\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_7\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<allometry>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_6\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_7\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_6\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_7\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_6\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_7\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_4\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_5\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_6\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_7\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_5\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_6\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_7\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_6\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_7\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_5\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_6\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_7\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_6\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_7\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_6\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_7\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_5\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_6\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_7\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_6\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_7\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_6\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_7\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_6\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_7\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_6\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_7\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_6\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_7\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_6\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_7\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_6\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_7\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";
}

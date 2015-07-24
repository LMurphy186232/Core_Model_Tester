//---------------------------------------------------------------------------
// TestInsectInfestationMortality.cpp
//---------------------------------------------------------------------------
#include "TestInsectInfestationMortality.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "Grid.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// NormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
TEST(InsectInfestationMortality, NormalProcessingRun1) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  float fDiam, fX, fY, fExpected;
  int *p_iNumTrees = new int[5];
  int i, iSpecies, iYrsInfested, iYr;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {

    p_oSimManager->ReadFile(WriteInsectInfestationMortalityXMLFile1());
    p_oPop = (clTreePopulation *) p_oSimManager->GetPopulationObject("treepopulation");

    //Add 1000 trees to the plot of each kind
    fDiam = 20;
    for (i = 0; i < 1000; i++) {
      for (iYrsInfested = 0; iYrsInfested < 20; iYrsInfested++) {
        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        iSpecies = 0;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), iYrsInfested);

        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        iSpecies = 1;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), iYrsInfested);

        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        iSpecies = 3;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), iYrsInfested);

        fX = clModelMath::GetRand() * 100;
        fY = clModelMath::GetRand() * 100;
        iSpecies = 4;
        p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
        p_oTree->SetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), iYrsInfested);
      }

      //One more set of trees that will be beyond the probabilities array
      iYrsInfested = 40;
      fX = clModelMath::GetRand() * 100;
      fY = clModelMath::GetRand() * 100;
      iSpecies = 0;
      p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), iYrsInfested);

      fX = clModelMath::GetRand() * 100;
      fY = clModelMath::GetRand() * 100;
      iSpecies = 1;
      p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), iYrsInfested);

      fX = clModelMath::GetRand() * 100;
      fY = clModelMath::GetRand() * 100;
      iSpecies = 2;
      p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);

      fX = clModelMath::GetRand() * 100;
      fY = clModelMath::GetRand() * 100;
      iSpecies = 3;
      p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), iYrsInfested);

      fX = clModelMath::GetRand() * 100;
      fY = clModelMath::GetRand() * 100;
      iSpecies = 4;
      p_oTree = p_oPop->CreateTree(fX, fY, iSpecies, clTreePopulation::adult, fDiam);
      p_oTree->SetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), iYrsInfested);
    }


    //Run a timestep
    p_oSimManager->RunSim(1);

    //Count up the trees for each year
    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();

    //First check non-participating species
    iSpecies = 0;
    while (p_oTree) {
      if (2 == p_oTree->GetSpecies())
        iSpecies++;
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(1000, iSpecies);
    p_oAllTrees->StartOver();

    for (iYr = 0; iYr <= 20; iYr++) {

      for (i = 0; i < 5; i++) p_iNumTrees[i] = 0;
      p_oTree = p_oAllTrees->NextTree();
      while (p_oTree) {
        if (2 != p_oTree->GetSpecies()) {
          p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iYrsInfested);
          if (iYrsInfested == iYr)
            p_iNumTrees[p_oTree->GetSpecies()]++;
        }
        p_oTree = p_oAllTrees->NextTree();
      }

      switch (iYr) {
      case 0:
        EXPECT_EQ(1000, p_iNumTrees[0]);
        EXPECT_EQ(1000, p_iNumTrees[1]);
        EXPECT_EQ(1000, p_iNumTrees[3]);
        EXPECT_EQ(1000, p_iNumTrees[4]);
        break;

      case 1:
        fExpected = 1000;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 790.2439024;
        EXPECT_LT(fabs(p_iNumTrees[1] - fExpected)/fExpected, 0.05);
        fExpected = 999.9999884;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.05);
        fExpected = 999.9900001;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 2:
        fExpected = 999.9998976;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 668.0412371;
        EXPECT_LT(fabs(p_iNumTrees[1] - fExpected)/fExpected, 0.05);
        fExpected = 999.9881456;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.05);
        fExpected = 999.6801024;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 3:
        fExpected = 999.9940951;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 400;
        EXPECT_LT(fabs(p_iNumTrees[1] - fExpected)/fExpected, 0.05);
        fExpected = 999.3170732;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.05);
        fExpected = 997.5758906;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 4:
        fExpected = 999.8951534;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 192.2848665;
        EXPECT_LT(fabs(p_iNumTrees[1] - fExpected)/fExpected, 0.05);
        fExpected = 988.0678508;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.05);
        fExpected = 989.8637947;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 5:
        fExpected = 999.0243902;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 91.78470255;
        EXPECT_LT(fabs(p_iNumTrees[1] - fExpected)/fExpected, 0.2);
        fExpected = 902.6660658;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.05);
        fExpected = 969.6969697;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 6:
        fExpected = 993.9897242;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 47.05882353;
        EXPECT_LT(fabs(p_iNumTrees[1] - fExpected)/fExpected, 0.15);
        fExpected = 650;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.05);
        fExpected = 927.8503563;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 7:
        fExpected = 972.5284776;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 26.10797744;
        EXPECT_LT(p_iNumTrees[1] > 15 && p_iNumTrees[1], 40);
        fExpected = 423.4214362;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.10);
        fExpected = 856.1130754;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 8:
        fExpected = 903.0371268;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 15.51352645;
        EXPECT_LT(p_iNumTrees[1], 30);
        fExpected = 337.3179551;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.05);
        fExpected = 753.1935406;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 9:
        fExpected = 741.466587;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 9.756097561;
        EXPECT_LT(p_iNumTrees[1], 30);
        fExpected = 311.9321492;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.05);
        fExpected = 628.7370559;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 10:
        fExpected = 500;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.05);
        fExpected = 6.427933737;
        EXPECT_LT(p_iNumTrees[1], 20);
        fExpected = 304.207193;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.05);
        fExpected = 500;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.05);
        break;

      case 11:
        fExpected = 278.2614534;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.1);
        fExpected = 4.401575873;
        EXPECT_LT(p_iNumTrees[1], 10);
        fExpected = 301.6280676;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
        fExpected = 383.0669103;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.1);
        break;

      case 12:
        fExpected = 139.0484775;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.1);
        fExpected = 3.112840467;
        EXPECT_LT(p_iNumTrees[1], 10);
        fExpected = 300.6829268;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
        fExpected = 286.6709476;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.1);
        break;

      case 13:
        fExpected = 67.63223319;
        EXPECT_LT(fabs(p_iNumTrees[0] - fExpected)/fExpected, 0.2);
        fExpected = 2.262411843;
        EXPECT_LT(p_iNumTrees[1], 10);
        fExpected = 300.3068927;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
        fExpected = 212.1822306;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.1);
        break;

      case 14:
        fExpected = 33.41635571;
        EXPECT_LT(p_iNumTrees[0] > 20 && p_iNumTrees[0], 45);
        fExpected = 1.683248045;
        EXPECT_LT(p_iNumTrees[1], 10);
        fExpected = 300.1462983;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
        fExpected = 156.7830624;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.1);
        break;

      case 15:
        fExpected = 17.04592745;
        EXPECT_LT(p_iNumTrees[0], 30);
        fExpected = 1.277955272;
        EXPECT_LT(p_iNumTrees[1], 10);
        fExpected = 300.0733926;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
        fExpected = 116.3636364;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.15);
        break;

      case 16:
        fExpected = 9.012974492;
        EXPECT_LT(p_iNumTrees[0], 20);
        fExpected = 0.987548958;
        EXPECT_LT(p_iNumTrees[1], 10);
        fExpected = 300.0384934;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
        fExpected = 87.06433009;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.2);
        break;

      case 17:
        fExpected = 4.935849016;
        EXPECT_LT(p_iNumTrees[0], 10);
        fExpected = 0.775101074;
        EXPECT_LT(p_iNumTrees[1], 10);
        fExpected = 300.0209946;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
        fExpected = 65.79566367;
        EXPECT_LT(fabs(p_iNumTrees[4] - fExpected)/fExpected, 0.2);
        break;

      case 18:
        fExpected = 2.792931583;
        EXPECT_LT(p_iNumTrees[0], 10);
        fExpected = 0.616808019;
        EXPECT_LT(p_iNumTrees[1], 10);
        fExpected = 300.0118544;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
        fExpected = 50.26216747;
        EXPECT_LT(p_iNumTrees[4] > 35 && p_iNumTrees[4], 65);
        break;

      case 19:
        fExpected = 1.628381714;
        EXPECT_LT(p_iNumTrees[0], 10);
        fExpected = 0.496924894;
        EXPECT_LT(p_iNumTrees[1], 10);
        fExpected = 300.0069035;
        EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
        fExpected = 38.81838392;
        EXPECT_LT(p_iNumTrees[4] > 20 && p_iNumTrees[4], 50);
        break;

      }
      p_oAllTrees->StartOver();
    }

    // 40 yr trees
    iYr = 40;
    for (i = 0; i < 5; i++) p_iNumTrees[i] = 0;
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (2 != p_oTree->GetSpecies()) {
        p_oTree->GetValue(p_oPop->GetIntDataCode("YearsInfested", p_oTree->GetSpecies(), p_oTree->GetType()), &iYrsInfested);
        if (iYrsInfested == iYr)
          p_iNumTrees[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    fExpected = 0.000953673;
    EXPECT_LT(p_iNumTrees[0], 3);
    fExpected = 0.025311699;
    EXPECT_LT(p_iNumTrees[1], 3);
    fExpected = 300.000004;
    EXPECT_LT(fabs(p_iNumTrees[3] - fExpected)/fExpected, 0.1);
    fExpected = 0.975609756;
    EXPECT_LT(p_iNumTrees[4], 5);


    delete[] p_iNumTrees;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumTrees;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


////////////////////////////////////////////////////////////////////////////
// ErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(InsectInfestationMortality, ErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationMortalityXMLErrorFile1() );
    FAIL() << "TestInsectInfestationMortality error processing didn't catch error for WriteInsectInfestationMortalityXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestationMortality::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestInsectInfestationMortality error processing caught wrong error for WriteInsectInfestationMortalityXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationMortalityXMLErrorFile2() );
    FAIL() << "TestInsectInfestationMortality error processing didn't catch error for WriteInsectInfestationMortalityXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestationMortality::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestInsectInfestationMortality error processing caught wrong error for WriteInsectInfestationMortalityXMLErrorFile2.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationMortalityXMLErrorFile3() );
    FAIL() << "TestInsectInfestationMortality error processing didn't catch error for WriteInsectInfestationMortalityXMLErrorFile3.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestationMortality::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestInsectInfestationMortality error processing caught wrong error for WriteInsectInfestationMortalityXMLErrorFile3.";
    }
    ;
  }
  try
  {
    p_oSimManager->ReadFile( WriteInsectInfestationMortalityXMLErrorFile4() );
    FAIL() << "TestInsectInfestationMortality error processing didn't catch error for WriteInsectInfestationMortalityXMLErrorFile4.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clInsectInfestationMortality::DoShellSetup" ) != 0 )
    {
      FAIL() << "TestInsectInfestationMortality error processing caught wrong error for WriteInsectInfestationMortalityXMLErrorFile4.";
    }
    ;
  }
  delete p_oSimManager;
}

////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationMortalityXMLFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationMortalityXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>";

  oOut << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>100</plot_lenX>"
      << "<plot_lenY>100</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "<tr_species speciesName=\"Species_4\"/>"
      << "<tr_species speciesName=\"Species_5\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_5\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_5\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_5\">39.48</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_5\">0.0549</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_5\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_4\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_5\">1</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_5\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_5\">0.389</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_5\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_slopeOfHeight-Diam10>"
      << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
      << "<tr_sohdVal species=\"Species_5\">0.03418</tr_sohdVal>"
      << "</tr_slopeOfHeight-Diam10>"
      << "<tr_slopeOfAsymHeight>"
      << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
      << "<tr_soahVal species=\"Species_5\">0.0299</tr_soahVal>"
      << "</tr_slopeOfAsymHeight>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_5\">0</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_5\">0</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_5\">0</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_5\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_5\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_5\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_5\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>InsectInfestation</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>InsectInfestationMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_5\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_4\">1</di_iiVal>"
      << "<di_iiVal species=\"Species_5\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_4\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_5\">0.6</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "<di_ix0Val species=\"Species_4\">11</di_ix0Val>"
      << "<di_ix0Val species=\"Species_5\">8</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "<di_ixbVal species=\"Species_4\">-8</di_ixbVal>"
      << "<di_ixbVal species=\"Species_5\">-10</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_4\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_5\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>5</di_insectStartTimestep>"
      << "</InsectInfestation1>";

  oOut << "<InsectInfestationMortality2>"
      << "<mo_insectMortIntercept>"
      << "<mo_imiVal species=\"Species_1\">0</mo_imiVal>"
      << "<mo_imiVal species=\"Species_2\">0.2</mo_imiVal>"
      << "<mo_imiVal species=\"Species_4\">0</mo_imiVal>"
      << "<mo_imiVal species=\"Species_5\">0</mo_imiVal>"
      << "</mo_insectMortIntercept>"
      << "<mo_insectMortMaxRate>"
      << "<mo_immrVal species=\"Species_1\">1</mo_immrVal>"
      << "<mo_immrVal species=\"Species_2\">1</mo_immrVal>"
      << "<mo_immrVal species=\"Species_4\">0.7</mo_immrVal>"
      << "<mo_immrVal species=\"Species_5\">1</mo_immrVal>"
      << "</mo_insectMortMaxRate>"
      << "<mo_insectMortX0>"
      << "<mo_imx0Val species=\"Species_1\">10</mo_imx0Val>"
      << "<mo_imx0Val species=\"Species_2\">3</mo_imx0Val>"
      << "<mo_imx0Val species=\"Species_4\">6</mo_imx0Val>"
      << "<mo_imx0Val species=\"Species_5\">10</mo_imx0Val>"
      << "</mo_insectMortX0>"
      << "<mo_insectMortXb>"
      << "<mo_imxbVal species=\"Species_1\">-10</mo_imxbVal>"
      << "<mo_imxbVal species=\"Species_2\">-4</mo_imxbVal>"
      << "<mo_imxbVal species=\"Species_4\">-10</mo_imxbVal>"
      << "<mo_imxbVal species=\"Species_5\">-5</mo_imxbVal>"
      << "</mo_insectMortXb>"
      << "</InsectInfestationMortality2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationMortalityXMLErrorFile1()
////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationMortalityXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteInsectInfestationMortalityErrorCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>InsectInfestation</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>InsectInfestationMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>5</di_insectStartTimestep>"
      << "</InsectInfestation1>";

  oOut << "<InsectInfestationMortality2>"
      << "<mo_insectMortIntercept>"
      << "<mo_imiVal species=\"Species_1\">0</mo_imiVal>"
      << "<mo_imiVal species=\"Species_2\">-0.2</mo_imiVal>"
      << "</mo_insectMortIntercept>"
      << "<mo_insectMortMaxRate>"
      << "<mo_immrVal species=\"Species_1\">1</mo_immrVal>"
      << "<mo_immrVal species=\"Species_2\">1</mo_immrVal>"
      << "</mo_insectMortMaxRate>"
      << "<mo_insectMortX0>"
      << "<mo_imx0Val species=\"Species_1\">10</mo_imx0Val>"
      << "<mo_imx0Val species=\"Species_2\">3</mo_imx0Val>"
      << "</mo_insectMortX0>"
      << "<mo_insectMortXb>"
      << "<mo_imxbVal species=\"Species_1\">-10</mo_imxbVal>"
      << "<mo_imxbVal species=\"Species_2\">-4</mo_imxbVal>"
      << "</mo_insectMortXb>"
      << "</InsectInfestationMortality2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationMortalityXMLErrorFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationMortalityXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteInsectInfestationMortalityErrorCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>InsectInfestation</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>InsectInfestationMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>5</di_insectStartTimestep>"
      << "</InsectInfestation1>";

  oOut << "<InsectInfestationMortality2>"
      << "<mo_insectMortIntercept>"
      << "<mo_imiVal species=\"Species_1\">0</mo_imiVal>"
      << "<mo_imiVal species=\"Species_2\">0.2</mo_imiVal>"
      << "</mo_insectMortIntercept>"
      << "<mo_insectMortMaxRate>"
      << "<mo_immrVal species=\"Species_1\">4</mo_immrVal>"
      << "<mo_immrVal species=\"Species_2\">1</mo_immrVal>"
      << "</mo_insectMortMaxRate>"
      << "<mo_insectMortX0>"
      << "<mo_imx0Val species=\"Species_1\">10</mo_imx0Val>"
      << "<mo_imx0Val species=\"Species_2\">3</mo_imx0Val>"
      << "</mo_insectMortX0>"
      << "<mo_insectMortXb>"
      << "<mo_imxbVal species=\"Species_1\">-10</mo_imxbVal>"
      << "<mo_imxbVal species=\"Species_2\">-4</mo_imxbVal>"
      << "</mo_insectMortXb>"
      << "</InsectInfestationMortality2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationMortalityXMLErrorFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationMortalityXMLErrorFile3() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteInsectInfestationMortalityErrorCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>InsectInfestation</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>InsectInfestationMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">9</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>5</di_insectStartTimestep>"
      << "</InsectInfestation1>";

  oOut << "<InsectInfestationMortality2>"
      << "<mo_insectMortIntercept>"
      << "<mo_imiVal species=\"Species_1\">0</mo_imiVal>"
      << "<mo_imiVal species=\"Species_2\">0.2</mo_imiVal>"
      << "</mo_insectMortIntercept>"
      << "<mo_insectMortMaxRate>"
      << "<mo_immrVal species=\"Species_1\">1</mo_immrVal>"
      << "<mo_immrVal species=\"Species_2\">1</mo_immrVal>"
      << "</mo_insectMortMaxRate>"
      << "<mo_insectMortX0>"
      << "<mo_imx0Val species=\"Species_1\">10</mo_imx0Val>"
      << "<mo_imx0Val species=\"Species_2\">3</mo_imx0Val>"
      << "</mo_insectMortX0>"
      << "<mo_insectMortXb>"
      << "<mo_imxbVal species=\"Species_1\">-10</mo_imxbVal>"
      << "<mo_imxbVal species=\"Species_2\">-4</mo_imxbVal>"
      << "</mo_insectMortXb>"
      << "</InsectInfestationMortality2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationMortalityXMLErrorFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteInsectInfestationMortalityXMLErrorFile4() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  WriteInsectInfestationMortalityErrorCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>InsectInfestation</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>InsectInfestationMortality</behaviorName>"
      << "<version>1</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2</version>"
      << "<listPosition>3</listPosition>"
      << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
      << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
      << "</behavior>"
      << "</behaviorList>";

  oOut << "<InsectInfestation1>"
      << "<di_insectIntercept>"
      << "<di_iiVal species=\"Species_1\">0.01</di_iiVal>"
      << "<di_iiVal species=\"Species_2\">0.01</di_iiVal>"
      << "</di_insectIntercept>"
      << "<di_insectMaxInfestation>"
      << "<di_imiVal species=\"Species_1\">1</di_imiVal>"
      << "<di_imiVal species=\"Species_2\">1</di_imiVal>"
      << "</di_insectMaxInfestation>"
      << "<di_insectX0>"
      << "<di_ix0Val species=\"Species_1\">5</di_ix0Val>"
      << "<di_ix0Val species=\"Species_2\">1</di_ix0Val>"
      << "</di_insectX0>"
      << "<di_insectXb>"
      << "<di_ixbVal species=\"Species_1\">-4</di_ixbVal>"
      << "<di_ixbVal species=\"Species_2\">-6</di_ixbVal>"
      << "</di_insectXb>"
      << "<di_insectMinDBH>"
      << "<di_imdVal species=\"Species_1\">2.2</di_imdVal>"
      << "<di_imdVal species=\"Species_2\">2.2</di_imdVal>"
      << "</di_insectMinDBH>"
      << "<di_insectStartTimestep>5</di_insectStartTimestep>"
      << "</InsectInfestation1>";

  oOut << "<InsectInfestationMortality2>"
      << "<mo_insectMortIntercept>"
      << "<mo_imiVal species=\"Species_1\">0</mo_imiVal>"
      << "<mo_imiVal species=\"Species_2\">0.2</mo_imiVal>"
      << "</mo_insectMortIntercept>"
      << "<mo_insectMortMaxRate>"
      << "<mo_immrVal species=\"Species_1\">1</mo_immrVal>"
      << "<mo_immrVal species=\"Species_2\">1</mo_immrVal>"
      << "</mo_insectMortMaxRate>"
      << "<mo_insectMortX0>"
      << "<mo_imx0Val species=\"Species_1\">0</mo_imx0Val>"
      << "<mo_imx0Val species=\"Species_2\">3</mo_imx0Val>"
      << "</mo_insectMortX0>"
      << "<mo_insectMortXb>"
      << "<mo_imxbVal species=\"Species_1\">-10</mo_imxbVal>"
      << "<mo_imxbVal species=\"Species_2\">-4</mo_imxbVal>"
      << "</mo_insectMortXb>"
      << "</InsectInfestationMortality2>";

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}


/////////////////////////////////////////////////////////////////////////////
// WriteInsectInfestationMortalityErrorCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteInsectInfestationMortalityErrorCommonStuff(std::fstream &oOut)
{
  using namespace std;
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
      << "<paramFile fileCode=\"06010101\">"
      << "<plot>"
      << "<timesteps>1</timesteps>"
      << "<yearsPerTimestep>1</yearsPerTimestep>"
      << "<randomSeed>1</randomSeed>"
      << "<plot_lenX>100</plot_lenX>"
      << "<plot_lenY>100</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>55.37</plot_latitude>"
      << "</plot>"
      << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
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
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">1</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">1</tr_cdtdVal>"
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
}

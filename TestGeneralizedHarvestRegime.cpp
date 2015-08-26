//---------------------------------------------------------------------------
// TestGeneralizedHarvestRegime.cpp
//---------------------------------------------------------------------------
#include "TestGeneralizedHarvestRegime.h"
#include <gtest/gtest.h>
#include <fstream>
#include <math.h>
#include "TreePopulation.h"
#include "SimManager.h"
#include "BehaviorBase.h"


////////////////////////////////////////////////////////////////////////////
// TestRun1()
// Tests the decision to log the plot. Many replicates are run with the same
// probability of logging for each. If logging occurs, all trees are to be
// cut, which allows us to easily determine which runs were logged and
// which were not. Saplings have no mortality and a gamma probability
// distribution is used.
////////////////////////////////////////////////////////////////////////////
TEST(GeneralizedHarvestRegime, TestRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int iNumRuns = 10000,
      iCutRuns = 0, iNoCutRuns = 0, iNumTrees, i;

  for (i = 0; i < iNumRuns; i++) {
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteGeneralizedHarvestRegimeXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    p_oSimManager->RunSim(1);

    //See if we got any adults this run. Note that since we have to draw on
    //the gamma distribution, even if we specify 100% removal, the actual
    //rate might be less, allowing a handful of individuals to remain. So
    //allow for that.
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();

    iNumTrees = 0;
    if (p_oTree) {
      while (p_oTree) {
        iNumTrees++;
        p_oTree = p_oAllTrees->NextTree();
      }
      if (iNumTrees < 5) iNumTrees = 0;
      if (iNumTrees > 0) EXPECT_EQ(100, iNumTrees);
    }
    if (iNumTrees == 0) iCutRuns++;
    else iNoCutRuns++;

    //Make sure saplings were untouched
    p_oAllTrees = p_oPop->Find("type=2");
    p_oTree = p_oAllTrees->NextTree();
    iNumTrees = 0;
    while (p_oTree) {
      iNumTrees++;
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(50, iNumTrees);
  }

  EXPECT_LT(abs(iCutRuns - 7880), 1000);
  EXPECT_LT(abs(iNoCutRuns - (iNumRuns - 7880)), 1000);
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun2()
// Tests the decision to log the plot. This is the same as Test 1 but with
// a different initial biomass and therefore a different logging probability.
// It also uses the user-defined distribution.
////////////////////////////////////////////////////////////////////////////
TEST(GeneralizedHarvestRegime, TestRun2) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int iNumRuns = 1000,
      iCutRuns = 0, iNoCutRuns = 0, iNumTrees, i;

  for (i = 0; i < iNumRuns; i++) {
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteGeneralizedHarvestRegimeXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    p_oSimManager->RunSim(1);

    //See if we got any adults this run. Note that since we have to draw on
    //the gamma distribution, even if we specify 100% removal, the actual
    //rate might be less, allowing a handful of individuals to remain. So
    //allow for that.
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();

    iNumTrees = 0;
    if (p_oTree) {
      while (p_oTree) {
        iNumTrees++;
        p_oTree = p_oAllTrees->NextTree();
      }
      if (iNumTrees < 5) iNumTrees = 0;
      if (iNumTrees > 0) EXPECT_EQ(200, iNumTrees);
    }
    if (iNumTrees == 0) iCutRuns++;
    else iNoCutRuns++;

    //Make sure saplings were untouched
    p_oAllTrees = p_oPop->Find("type=2");
    ASSERT_TRUE(p_oAllTrees->NextTree());
  }

  EXPECT_LT(abs(iCutRuns - 938), 100);
  EXPECT_LT(abs(iNoCutRuns - (iNumRuns - 938)), 100);
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun3()
// Tests the decision to log the plot.
////////////////////////////////////////////////////////////////////////////
TEST(GeneralizedHarvestRegime, TestRun3) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fBA = 0, fPostCutBA = 0, fDBH;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteGeneralizedHarvestRegimeXMLFile3() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      fBA += clModelMath::CalculateBasalArea(fDBH);
      p_oTree = p_oAllTrees->NextTree();
    }

    p_oSimManager->RunSim(1);

    //See if we got any adults this run
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      fPostCutBA += clModelMath::CalculateBasalArea(fDBH);
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_LT(fabs((fPostCutBA / fBA) - (1-0.71627)), 0.5);
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun4()
// Tests the decision to log the plot.
////////////////////////////////////////////////////////////////////////////
TEST(GeneralizedHarvestRegime, TestRun4) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fBA = 0, fPostCutBA = 0, fDBH;

    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteGeneralizedHarvestRegimeXMLFile4() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      fBA += clModelMath::CalculateBasalArea(fDBH);
      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure there are 1000 saplings
    int iSaps = 0;
    p_oAllTrees = p_oPop->Find("type=2");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iSaps++;
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_EQ(iSaps, 1000);

    p_oSimManager->RunSim(1);

    //See if we got any adults this run
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
      fPostCutBA += clModelMath::CalculateBasalArea(fDBH);
      p_oTree = p_oAllTrees->NextTree();
    }

    EXPECT_LT(fabs((fPostCutBA / fBA) - (1-0.12567)), 0.5);

    //How many saplings should have been removed?
    iSaps = 0;
    float fProb, fP = 0.2, fM = 50, fN = -1, fPCR = 100.0 * (1-(fPostCutBA/fBA));
    fProb = fP + ((1-fP)/(1 + pow(fPCR/fM, fN)));

    p_oAllTrees = p_oPop->Find("type=2");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iSaps++;
      p_oTree = p_oAllTrees->NextTree();
    }

    int iExpectedSaps = (1000*(1-fProb));
    EXPECT_LT(abs(iSaps - iExpectedSaps), 250);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun4a()
// Tests the cut amount. This is a user-defined distribution with two
// intensity classes, with equal possibility. This will run replicates and
// make sure that the cut classes work out.
////////////////////////////////////////////////////////////////////////////
TEST(GeneralizedHarvestRegime, TestRun4a) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    clTreePopulation * p_oPop;
    clTreeSearch *p_oAllTrees;
    clTree *p_oTree;
    float fBA = 0, fPostCutBA = 0, fDBH;
    int iNumRuns = 1000,
      iCut1Runs = 0, iCut2Runs = 0, i;

    for (i = 0; i < iNumRuns; i++) {
      //Load our test file and get our tree population pointers
      p_oSimManager->ReadFile( WriteGeneralizedHarvestRegimeXMLFile4a() );
      p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
      fBA = 0;
      fPostCutBA = 0;

      p_oAllTrees = p_oPop->Find("type=3");
      p_oTree = p_oAllTrees->NextTree();
      while (p_oTree) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
        fBA += clModelMath::CalculateBasalArea(fDBH);
        p_oTree = p_oAllTrees->NextTree();
      }

      p_oSimManager->RunSim(1);

      //See if we got any adults this run
      p_oAllTrees = p_oPop->Find("type=3");
      p_oTree = p_oAllTrees->NextTree();
      while (p_oTree) {
        p_oTree->GetValue(p_oPop->GetDbhCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fDBH);
        fPostCutBA += clModelMath::CalculateBasalArea(fDBH);
        p_oTree = p_oAllTrees->NextTree();
      }

      if (fPostCutBA / fBA < 0.5) {
        //Intensity class 2
        EXPECT_LT(fabs((fPostCutBA / fBA) - (1-0.73)), 0.25);
        iCut1Runs++;
      } else {

        //Intensity class 1
        EXPECT_LT(fabs((fPostCutBA / fBA) - (1-0.22)), 0.25);
        iCut2Runs++;
      }
    }

    EXPECT_LT(abs(iCut1Runs - 500), 50);
    EXPECT_LT(abs(iCut2Runs - 500), 50);

    delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// TestRun5()
// Tests the decision to log the plot when BA is used rather than biomass.
////////////////////////////////////////////////////////////////////////////
TEST(GeneralizedHarvestRegime, TestRun5) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int iNumRuns = 10000,
      iCutRuns = 0, iNoCutRuns = 0, iNumTrees, iNumSaps, i;

  for (i = 0; i < iNumRuns; i++) {
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteGeneralizedHarvestRegimeXMLFile5());
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    p_oSimManager->RunSim(1);

    //See if we got any adults this run. Note that since we have to draw on
    //the gamma distribution, even if we specify 100% removal, the actual
    //rate might be less, allowing a handful of individuals to remain. So
    //allow for that.
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();

    iNumTrees = 0;
    if (p_oTree) {
      while (p_oTree) {
        iNumTrees++;
        p_oTree = p_oAllTrees->NextTree();
      }
      if (iNumTrees < 5) iNumTrees = 0;
      if (iNumTrees > 0) EXPECT_EQ(200, iNumTrees);
    }

    //Check the number of removed saplings
    iNumSaps = 0;
    p_oAllTrees = p_oPop->Find("type=2");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      iNumSaps++;
      p_oTree = p_oAllTrees->NextTree();
    }

    if (iNumTrees == 0) {
      iCutRuns++;
      EXPECT_LT(abs(iNumSaps - 266), 55);
    } else {
      iNoCutRuns++;
      EXPECT_EQ(1000, iNumSaps);
    }


  }

  EXPECT_LT(abs(iCutRuns - 5654), 1000);
  EXPECT_LT(abs(iNoCutRuns - (iNumRuns - 5654)), 1000);


  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}


////////////////////////////////////////////////////////////////////////////
// TestRun6()
// Tests the decision to log the plot when BA is used rather than biomass.
////////////////////////////////////////////////////////////////////////////
TEST(GeneralizedHarvestRegime, TestRun6) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;
  int iNumRuns = 10000,
      iCutRuns = 0, iNoCutRuns = 0, iNumTrees, i;

  for (i = 0; i < iNumRuns; i++) {
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile(WriteGeneralizedHarvestRegimeXMLFile6());
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );

    p_oSimManager->RunSim(1);

    //See if we got any adults this run. Note that since we have to draw on
    //the gamma distribution, even if we specify 100% removal, the actual
    //rate might be less, allowing a handful of individuals to remain. So
    //allow for that.
    p_oAllTrees = p_oPop->Find("type=3");
    p_oTree = p_oAllTrees->NextTree();

    iNumTrees = 0;
    if (p_oTree) {
      while (p_oTree) {
        iNumTrees++;
        p_oTree = p_oAllTrees->NextTree();
      }
      if (iNumTrees < 5) iNumTrees = 0;
      if (iNumTrees > 0) EXPECT_EQ(200, iNumTrees);
    }
    if (iNumTrees == 0) iCutRuns++;
    else iNoCutRuns++;

    //Make sure saplings were untouched
    p_oAllTrees = p_oPop->Find("type=2");
    p_oTree = p_oAllTrees->NextTree();
    iNumTrees = 0;
    while (p_oTree) {
      iNumTrees++;
      p_oTree = p_oAllTrees->NextTree();
    }
    EXPECT_EQ(50, iNumTrees);
  }

  EXPECT_LT(abs(iCutRuns - 5654), 1000);
  EXPECT_LT(abs(iNoCutRuns - (iNumRuns - 5654)), 1000);
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

////////////////////////////////////////////////////////////////////////////
// WriteGeneralizedHarvestRegimeXMLFileSet1()
////////////////////////////////////////////////////////////////////////////
const char* WriteGeneralizedHarvestRegimeXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  int iNumTreesPerSpecies = 50;

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>80.0</plot_lenX>"
       << "<plot_lenY>80.0</plot_lenY>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::sapling << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";

  for (int i = 0; i < iNumTreesPerSpecies; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }
  for (int i = 0; i < iNumTreesPerSpecies; i++) {
    oOut << "<tree sp=\"1\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }
  for (int i = 0; i < iNumTreesPerSpecies; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::sapling << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << clModelMath::GetRand() * 8 + 1 << "</fl>"
         << "</tree>";
  }
  oOut << "</tr_treemap>"
       << "</trees>";

  WriteGeneralizedHarvestRegimeAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GeneralizedHarvestRegime</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DimensionAnalysis</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";
  oOut << "<GeneralizedHarvestRegime1>"
       << "<di_genHarvLogProbA>65.51</di_genHarvLogProbA>"
       << "<di_genHarvLogProbM>1.38</di_genHarvLogProbM>"
       << "<di_genHarvLogProbB>0.282</di_genHarvLogProbB>"
       << "<di_genHarvLogRemoveAlpha>200</di_genHarvLogRemoveAlpha>"
       << "<di_genHarvLogRemoveBeta>1</di_genHarvLogRemoveBeta>"
       << "<di_genHarvLogRemoveMu>0</di_genHarvLogRemoveMu>"
       << "<di_genHarvGammaScale>0.000001</di_genHarvGammaScale>"
       << "<di_genHarvAllowedDeviation>0</di_genHarvAllowedDeviation>"
       << "<di_genHarvLogCutProbAlpha>"
       << "<di_ghlcpaVal species=\"Species_1\">1.748758</di_ghlcpaVal>"
       << "<di_ghlcpaVal species=\"Species_2\">1.853409</di_ghlcpaVal>"
       << "</di_genHarvLogCutProbAlpha>"
       << "<di_genHarvLogCutProbBeta>"
       << "<di_ghlcpbVal species=\"Species_1\">0.001083513</di_ghlcpbVal>"
       << "<di_ghlcpbVal species=\"Species_2\">0.001018502</di_ghlcpbVal>"
       << "</di_genHarvLogCutProbBeta>"
       << "<di_genHarvLogCutProbGamma>"
       << "<di_ghlcpgVal species=\"Species_1\">1</di_ghlcpgVal>"
       << "<di_ghlcpgVal species=\"Species_2\">0.9468814</di_ghlcpgVal>"
       << "</di_genHarvLogCutProbGamma>"
       << "<di_genHarvLogCutProbMu>"
       << "<di_ghlcpmVal species=\"Species_1\">42.53707</di_ghlcpmVal>"
       << "<di_ghlcpmVal species=\"Species_2\">39.45325</di_ghlcpmVal>"
       << "</di_genHarvLogCutProbMu>"
       << "<di_genHarvLogCutProbA>21.2954</di_genHarvLogCutProbA>"
       << "<di_genHarvLogCutProbB>0.01202805</di_genHarvLogCutProbB>"
       << "<di_genHarvLogCutProbC>15.20595</di_genHarvLogCutProbC>"
       << "<di_genHarvUseBiomassOrBA>1</di_genHarvUseBiomassOrBA>"
       << "<di_genHarvDoSaplingMort>0</di_genHarvDoSaplingMort>"
       << "<di_genHarvSapMortP>0.2</di_genHarvSapMortP>"
       << "<di_genHarvSapMortM>50</di_genHarvSapMortM>"
       << "<di_genHarvSapMortN>-1</di_genHarvSapMortN>"
       << "</GeneralizedHarvestRegime1>";

    WriteGeneralizedHarvestRegimeDimensionAnalysis(oOut);

    oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGeneralizedHarvestRegimeXMLFile2()
////////////////////////////////////////////////////////////////////////////
const char* WriteGeneralizedHarvestRegimeXMLFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  int iNumTreesPerSpecies = 100;

  //Open file to write to
  fstream oOut;
  oOut.open(cFileString, ios::out | ios::trunc);

  //Write file
  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>1</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>80.0</plot_lenX>"
       << "<plot_lenY>80.0</plot_lenY>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::sapling << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";

  for (int i = 0; i < iNumTreesPerSpecies; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }
  for (int i = 0; i < iNumTreesPerSpecies; i++) {
    oOut << "<tree sp=\"1\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }
  for (int i = 0; i < iNumTreesPerSpecies; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::sapling << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << clModelMath::GetRand() * 8 + 1 << "</fl>"
         << "</tree>";
  }
  oOut << "</tr_treemap>"
       << "</trees>";

  WriteGeneralizedHarvestRegimeAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GeneralizedHarvestRegime</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DimensionAnalysis</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";
  oOut << "<GeneralizedHarvestRegime1>"
       << "<di_genHarvLogProbA>65.51</di_genHarvLogProbA>"
       << "<di_genHarvLogProbM>1.38</di_genHarvLogProbM>"
       << "<di_genHarvLogProbB>0.282</di_genHarvLogProbB>"
       << "<di_genHarvRemoveDist>0</di_genHarvRemoveDist>"
       << "<di_genHarvIntensClass1>0.1</di_genHarvIntensClass1>"
       << "<di_genHarvIntensClass2>0.2</di_genHarvIntensClass2>"
       << "<di_genHarvIntensClass3>0.3</di_genHarvIntensClass3>"
       << "<di_genHarvIntensClass4>0.4</di_genHarvIntensClass4>"
       << "<di_genHarvIntensClass5>0.5</di_genHarvIntensClass5>"
       << "<di_genHarvIntensClass6>0.6</di_genHarvIntensClass6>"
       << "<di_genHarvIntensClass7>0.7</di_genHarvIntensClass7>"
       << "<di_genHarvIntensClass8>0.8</di_genHarvIntensClass8>"
       << "<di_genHarvIntensClass9>0.999</di_genHarvIntensClass9>"
       << "<di_genHarvIntensClass10>1</di_genHarvIntensClass10>"
       << "<di_genHarvIntensClassProb1>0</di_genHarvIntensClassProb1>"
       << "<di_genHarvIntensClassProb2>0</di_genHarvIntensClassProb2>"
       << "<di_genHarvIntensClassProb3>0</di_genHarvIntensClassProb3>"
       << "<di_genHarvIntensClassProb4>0</di_genHarvIntensClassProb4>"
       << "<di_genHarvIntensClassProb5>0</di_genHarvIntensClassProb5>"
       << "<di_genHarvIntensClassProb6>0</di_genHarvIntensClassProb6>"
       << "<di_genHarvIntensClassProb7>0</di_genHarvIntensClassProb7>"
       << "<di_genHarvIntensClassProb8>0</di_genHarvIntensClassProb8>"
       << "<di_genHarvIntensClassProb9>0</di_genHarvIntensClassProb9>"
       << "<di_genHarvIntensClassProb10>1.0</di_genHarvIntensClassProb10>"
       << "<di_genHarvAllowedDeviation>0</di_genHarvAllowedDeviation>"
       << "<di_genHarvLogCutProbAlpha>"
       << "<di_ghlcpaVal species=\"Species_1\">1.748758</di_ghlcpaVal>"
       << "<di_ghlcpaVal species=\"Species_2\">1.853409</di_ghlcpaVal>"
       << "</di_genHarvLogCutProbAlpha>"
       << "<di_genHarvLogCutProbBeta>"
       << "<di_ghlcpbVal species=\"Species_1\">0.001083513</di_ghlcpbVal>"
       << "<di_ghlcpbVal species=\"Species_2\">0.001018502</di_ghlcpbVal>"
       << "</di_genHarvLogCutProbBeta>"
       << "<di_genHarvLogCutProbGamma>"
       << "<di_ghlcpgVal species=\"Species_1\">1</di_ghlcpgVal>"
       << "<di_ghlcpgVal species=\"Species_2\">0.9468814</di_ghlcpgVal>"
       << "</di_genHarvLogCutProbGamma>"
       << "<di_genHarvLogCutProbMu>"
       << "<di_ghlcpmVal species=\"Species_1\">42.53707</di_ghlcpmVal>"
       << "<di_ghlcpmVal species=\"Species_2\">39.45325</di_ghlcpmVal>"
       << "</di_genHarvLogCutProbMu>"
       << "<di_genHarvLogCutProbA>21.2954</di_genHarvLogCutProbA>"
       << "<di_genHarvLogCutProbB>0.01202805</di_genHarvLogCutProbB>"
       << "<di_genHarvLogCutProbC>15.20595</di_genHarvLogCutProbC>"
       << "<di_genHarvUseBiomassOrBA>1</di_genHarvUseBiomassOrBA>"
       << "<di_genHarvDoSaplingMort>0</di_genHarvDoSaplingMort>"
       << "<di_genHarvSapMortP>0.2</di_genHarvSapMortP>"
       << "<di_genHarvSapMortM>50</di_genHarvSapMortM>"
       << "<di_genHarvSapMortN>-1</di_genHarvSapMortN>"
       << "</GeneralizedHarvestRegime1>";

  WriteGeneralizedHarvestRegimeDimensionAnalysis(oOut);

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGeneralizedHarvestRegimeXMLFile3()
////////////////////////////////////////////////////////////////////////////
const char* WriteGeneralizedHarvestRegimeXMLFile3() {
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
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>80.0</plot_lenX>"
       << "<plot_lenY>80.0</plot_lenY>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::sapling << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";

  for (int i = 0; i < 50; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }
  for (int i = 0; i < 50; i++) {
    oOut << "<tree sp=\"1\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }
  for (int i = 0; i < 50; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::sapling << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 8) + 0.1 << "</fl>"
         << "</tree>";
  }
  oOut << "</tr_treemap>"
       << "</trees>";

  WriteGeneralizedHarvestRegimeAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GeneralizedHarvestRegime</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DimensionAnalysis</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";
  oOut << "<GeneralizedHarvestRegime1>"
       << "<di_genHarvLogProbA>0</di_genHarvLogProbA>"
       << "<di_genHarvLogProbM>0</di_genHarvLogProbM>"
       << "<di_genHarvLogProbB>0.282</di_genHarvLogProbB>"
       << "<di_genHarvRemoveDist>1</di_genHarvRemoveDist>"
       << "<di_genHarvLogRemoveAlpha>99.6</di_genHarvLogRemoveAlpha>"
       << "<di_genHarvLogRemoveBeta>1</di_genHarvLogRemoveBeta>"
       << "<di_genHarvLogRemoveMu>0.00211</di_genHarvLogRemoveMu>"
       << "<di_genHarvGammaScale>0.000001</di_genHarvGammaScale>"
       << "<di_genHarvAllowedDeviation>0.1</di_genHarvAllowedDeviation>"
       << "<di_genHarvLogCutProbAlpha>"
       << "<di_ghlcpaVal species=\"Species_1\">1.748758</di_ghlcpaVal>"
       << "<di_ghlcpaVal species=\"Species_2\">1.853409</di_ghlcpaVal>"
       << "</di_genHarvLogCutProbAlpha>"
       << "<di_genHarvLogCutProbBeta>"
       << "<di_ghlcpbVal species=\"Species_1\">0.001083513</di_ghlcpbVal>"
       << "<di_ghlcpbVal species=\"Species_2\">0.001018502</di_ghlcpbVal>"
       << "</di_genHarvLogCutProbBeta>"
       << "<di_genHarvLogCutProbGamma>"
       << "<di_ghlcpgVal species=\"Species_1\">1</di_ghlcpgVal>"
       << "<di_ghlcpgVal species=\"Species_2\">0.9468814</di_ghlcpgVal>"
       << "</di_genHarvLogCutProbGamma>"
       << "<di_genHarvLogCutProbMu>"
       << "<di_ghlcpmVal species=\"Species_1\">42.53707</di_ghlcpmVal>"
       << "<di_ghlcpmVal species=\"Species_2\">39.45325</di_ghlcpmVal>"
       << "</di_genHarvLogCutProbMu>"
       << "<di_genHarvLogCutProbA>21.2954</di_genHarvLogCutProbA>"
       << "<di_genHarvLogCutProbB>0.01202805</di_genHarvLogCutProbB>"
       << "<di_genHarvLogCutProbC>15.20595</di_genHarvLogCutProbC>"
       << "<di_genHarvUseBiomassOrBA>1</di_genHarvUseBiomassOrBA>"
       << "</GeneralizedHarvestRegime1>";

  WriteGeneralizedHarvestRegimeDimensionAnalysis(oOut);

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGeneralizedHarvestRegimeXMLFile4()
////////////////////////////////////////////////////////////////////////////
const char* WriteGeneralizedHarvestRegimeXMLFile4() {
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
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::sapling << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";

  for (int i = 0; i < 100; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }
  for (int i = 0; i < 100; i++) {
    oOut << "<tree sp=\"1\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::sapling << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 8) + 0.1 << "</fl>"
         << "</tree>";
  }
  oOut << "</tr_treemap>"
       << "</trees>";

  WriteGeneralizedHarvestRegimeAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GeneralizedHarvestRegime</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DimensionAnalysis</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";
  oOut << "<GeneralizedHarvestRegime1>"
       << "<di_genHarvLogProbA>0</di_genHarvLogProbA>"
       << "<di_genHarvLogProbM>0</di_genHarvLogProbM>"
       << "<di_genHarvLogProbB>0.282</di_genHarvLogProbB>"
       << "<di_genHarvRemoveDist>1</di_genHarvRemoveDist>"
       << "<di_genHarvLogRemoveAlpha>24.3</di_genHarvLogRemoveAlpha>"
       << "<di_genHarvLogRemoveBeta>1</di_genHarvLogRemoveBeta>"
       << "<di_genHarvLogRemoveMu>0.00211</di_genHarvLogRemoveMu>"
       << "<di_genHarvGammaScale>0.000001</di_genHarvGammaScale>"
       << "<di_genHarvAllowedDeviation>0.1</di_genHarvAllowedDeviation>"
       << "<di_genHarvLogCutProbAlpha>"
       << "<di_ghlcpaVal species=\"Species_1\">1.748758</di_ghlcpaVal>"
       << "<di_ghlcpaVal species=\"Species_2\">1.853409</di_ghlcpaVal>"
       << "</di_genHarvLogCutProbAlpha>"
       << "<di_genHarvLogCutProbBeta>"
       << "<di_ghlcpbVal species=\"Species_1\">0.001083513</di_ghlcpbVal>"
       << "<di_ghlcpbVal species=\"Species_2\">0.001018502</di_ghlcpbVal>"
       << "</di_genHarvLogCutProbBeta>"
       << "<di_genHarvLogCutProbGamma>"
       << "<di_ghlcpgVal species=\"Species_1\">1</di_ghlcpgVal>"
       << "<di_ghlcpgVal species=\"Species_2\">0.9468814</di_ghlcpgVal>"
       << "</di_genHarvLogCutProbGamma>"
       << "<di_genHarvLogCutProbMu>"
       << "<di_ghlcpmVal species=\"Species_1\">3.063641</di_ghlcpmVal>"
       << "<di_ghlcpmVal species=\"Species_2\">51.29938</di_ghlcpmVal>"
       << "</di_genHarvLogCutProbMu>"
       << "<di_genHarvLogCutProbA>65.51862</di_genHarvLogCutProbA>"
       << "<di_genHarvLogCutProbB>0.2821873</di_genHarvLogCutProbB>"
       << "<di_genHarvLogCutProbC>1.386188</di_genHarvLogCutProbC>"
       << "<di_genHarvUseBiomassOrBA>1</di_genHarvUseBiomassOrBA>"
       << "<di_genHarvDoSaplingMort>1</di_genHarvDoSaplingMort>"
       << "<di_genHarvSapMortP>0.2</di_genHarvSapMortP>"
       << "<di_genHarvSapMortM>50</di_genHarvSapMortM>"
       << "<di_genHarvSapMortN>-1</di_genHarvSapMortN>"
       << "</GeneralizedHarvestRegime1>";
  WriteGeneralizedHarvestRegimeDimensionAnalysis(oOut);

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGeneralizedHarvestRegimeXMLFile4a()
////////////////////////////////////////////////////////////////////////////
const char* WriteGeneralizedHarvestRegimeXMLFile4a() {
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
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>200.0</plot_lenX>"
       << "<plot_lenY>200.0</plot_lenY>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::sapling << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";

  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"1\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 199 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 50) + 10 << "</fl>"
         << "</tree>";
  }

  oOut << "</tr_treemap>"
       << "</trees>";

  WriteGeneralizedHarvestRegimeAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GeneralizedHarvestRegime</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";
  oOut << "<GeneralizedHarvestRegime1>"
       << "<di_genHarvLogProbA>0</di_genHarvLogProbA>"
       << "<di_genHarvLogProbM>0</di_genHarvLogProbM>"
       << "<di_genHarvLogProbB>0.282</di_genHarvLogProbB>"
       << "<di_genHarvRemoveDist>0</di_genHarvRemoveDist>"
       << "<di_genHarvIntensClass1>0.1</di_genHarvIntensClass1>"
       << "<di_genHarvIntensClass2>0.22</di_genHarvIntensClass2>"
       << "<di_genHarvIntensClass3>0.23</di_genHarvIntensClass3>"
       << "<di_genHarvIntensClass4>0.3</di_genHarvIntensClass4>"
       << "<di_genHarvIntensClass5>0.4</di_genHarvIntensClass5>"
       << "<di_genHarvIntensClass6>0.5</di_genHarvIntensClass6>"
       << "<di_genHarvIntensClass7>0.6</di_genHarvIntensClass7>"
       << "<di_genHarvIntensClass8>0.74</di_genHarvIntensClass8>"
       << "<di_genHarvIntensClass9>0.75</di_genHarvIntensClass9>"
       << "<di_genHarvIntensClass10>1</di_genHarvIntensClass10>"
       << "<di_genHarvIntensClassProb1>0</di_genHarvIntensClassProb1>"
       << "<di_genHarvIntensClassProb2>0</di_genHarvIntensClassProb2>"
       << "<di_genHarvIntensClassProb3>0.5</di_genHarvIntensClassProb3>"
       << "<di_genHarvIntensClassProb4>0</di_genHarvIntensClassProb4>"
       << "<di_genHarvIntensClassProb5>0</di_genHarvIntensClassProb5>"
       << "<di_genHarvIntensClassProb6>0</di_genHarvIntensClassProb6>"
       << "<di_genHarvIntensClassProb7>0</di_genHarvIntensClassProb7>"
       << "<di_genHarvIntensClassProb8>0</di_genHarvIntensClassProb8>"
       << "<di_genHarvIntensClassProb9>0.5</di_genHarvIntensClassProb9>"
       << "<di_genHarvIntensClassProb10>0.0</di_genHarvIntensClassProb10>"
       << "<di_genHarvAllowedDeviation>0.001</di_genHarvAllowedDeviation>"
       << "<di_genHarvLogCutProbAlpha>"
       << "<di_ghlcpaVal species=\"Species_1\">1.748758</di_ghlcpaVal>"
       << "<di_ghlcpaVal species=\"Species_2\">1.853409</di_ghlcpaVal>"
       << "</di_genHarvLogCutProbAlpha>"
       << "<di_genHarvLogCutProbBeta>"
       << "<di_ghlcpbVal species=\"Species_1\">0.001083513</di_ghlcpbVal>"
       << "<di_ghlcpbVal species=\"Species_2\">0.001018502</di_ghlcpbVal>"
       << "</di_genHarvLogCutProbBeta>"
       << "<di_genHarvLogCutProbGamma>"
       << "<di_ghlcpgVal species=\"Species_1\">0</di_ghlcpgVal>"
       << "<di_ghlcpgVal species=\"Species_2\">0</di_ghlcpgVal>"
       << "</di_genHarvLogCutProbGamma>"
       << "<di_genHarvLogCutProbMu>"
       << "<di_ghlcpmVal species=\"Species_1\">42.53707</di_ghlcpmVal>"
       << "<di_ghlcpmVal species=\"Species_2\">39.45325</di_ghlcpmVal>"
       << "</di_genHarvLogCutProbMu>"
       << "<di_genHarvLogCutProbA>21.2954</di_genHarvLogCutProbA>"
       << "<di_genHarvLogCutProbB>0.01202805</di_genHarvLogCutProbB>"
       << "<di_genHarvLogCutProbC>15.20595</di_genHarvLogCutProbC>"
       << "<di_genHarvUseBiomassOrBA>0</di_genHarvUseBiomassOrBA>"
       << "<di_genHarvDoSaplingMort>0</di_genHarvDoSaplingMort>"
       << "</GeneralizedHarvestRegime1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGeneralizedHarvestRegimeXMLFile5()
////////////////////////////////////////////////////////////////////////////
const char* WriteGeneralizedHarvestRegimeXMLFile5() {
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
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>80.0</plot_lenX>"
       << "<plot_lenY>80.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.8</plot_temp_C>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::sapling << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";

  for (int i = 0; i < 100; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">25</fl>"
         << "</tree>";
  }
  for (int i = 0; i < 100; i++) {
    oOut << "<tree sp=\"1\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">25</fl>"
         << "</tree>";
  }
  for (int i = 0; i < 1000; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::sapling << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 8) + 0.1 << "</fl>"
         << "</tree>";
  }
  oOut << "</tr_treemap>"
       << "</trees>";

  WriteGeneralizedHarvestRegimeAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GeneralizedHarvestRegime</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>DimensionAnalysis</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "</behavior>"
       << "</behaviorList>";
  oOut << "<GeneralizedHarvestRegime1>"
       << "<di_genHarvLogProbA>1</di_genHarvLogProbA>"
       << "<di_genHarvLogProbM>0.8</di_genHarvLogProbM>"
       << "<di_genHarvLogProbB>0.02</di_genHarvLogProbB>"
       << "<di_genHarvRemoveDist>1</di_genHarvRemoveDist>"
       << "<di_genHarvLogRemoveAlpha>200</di_genHarvLogRemoveAlpha>"
       << "<di_genHarvLogRemoveBeta>1</di_genHarvLogRemoveBeta>"
       << "<di_genHarvLogRemoveMu>0</di_genHarvLogRemoveMu>"
       << "<di_genHarvGammaScale>0.000001</di_genHarvGammaScale>"
       << "<di_genHarvAllowedDeviation>0.1</di_genHarvAllowedDeviation>"
       << "<di_genHarvLogCutProbAlpha>"
       << "<di_ghlcpaVal species=\"Species_1\">1</di_ghlcpaVal>"
       << "<di_ghlcpaVal species=\"Species_2\">1</di_ghlcpaVal>"
       << "</di_genHarvLogCutProbAlpha>"
       << "<di_genHarvLogCutProbBeta>"
       << "<di_ghlcpbVal species=\"Species_1\">0</di_ghlcpbVal>"
       << "<di_ghlcpbVal species=\"Species_2\">0</di_ghlcpbVal>"
       << "</di_genHarvLogCutProbBeta>"
       << "<di_genHarvLogCutProbGamma>"
       << "<di_ghlcpgVal species=\"Species_1\">0</di_ghlcpgVal>"
       << "<di_ghlcpgVal species=\"Species_2\">0</di_ghlcpgVal>"
       << "</di_genHarvLogCutProbGamma>"
       << "<di_genHarvLogCutProbMu>"
       << "<di_ghlcpmVal species=\"Species_1\">0</di_ghlcpmVal>"
       << "<di_ghlcpmVal species=\"Species_2\">0</di_ghlcpmVal>"
       << "</di_genHarvLogCutProbMu>"
       << "<di_genHarvLogCutProbA>100000</di_genHarvLogCutProbA>"
       << "<di_genHarvLogCutProbB>1</di_genHarvLogCutProbB>"
       << "<di_genHarvLogCutProbC>1</di_genHarvLogCutProbC>"
       << "<di_genHarvUseBiomassOrBA>0</di_genHarvUseBiomassOrBA>"
       << "<di_genHarvDoSaplingMort>1</di_genHarvDoSaplingMort>"
       << "<di_genHarvSapMortP>0.2</di_genHarvSapMortP>"
       << "<di_genHarvSapMortM>50</di_genHarvSapMortM>"
       << "<di_genHarvSapMortN>-1</di_genHarvSapMortN>"
       << "</GeneralizedHarvestRegime1>";
  WriteGeneralizedHarvestRegimeDimensionAnalysis(oOut);

  oOut << "</paramFile>";

  oOut.close();

  return cFileString;
}

////////////////////////////////////////////////////////////////////////////
// WriteGeneralizedHarvestRegimeXMLFile6()
////////////////////////////////////////////////////////////////////////////
const char* WriteGeneralizedHarvestRegimeXMLFile6() {
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
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>0</randomSeed>"
       << "<plot_lenX>80.0</plot_lenX>"
       << "<plot_lenY>80.0</plot_lenY>"
       << "<plot_precip_mm_yr>1150.64</plot_precip_mm_yr>"
       << "<plot_temp_C>12.8</plot_temp_C>"
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
       << "<tr_treemap>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_1\" tp=\"" << clTreePopulation::sapling << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>"
       << "<tm_treeSettings sp=\"Species_2\" tp=\"" << clTreePopulation::adult << "\">"
       << "<tm_floatCodes>"
       << "<tm_floatCode label=\"X\">0</tm_floatCode>"
       << "<tm_floatCode label=\"Y\">1</tm_floatCode>"
       << "<tm_floatCode label=\"DBH\">2</tm_floatCode>"
       << "</tm_floatCodes>"
       << "</tm_treeSettings>";

  for (int i = 0; i < 100; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">25</fl>"
         << "</tree>";
  }
  for (int i = 0; i < 100; i++) {
    oOut << "<tree sp=\"1\" tp=\"" << clTreePopulation::adult << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">25</fl>"
         << "</tree>";
  }
  for (int i = 0; i < 50; i++) {
    oOut << "<tree sp=\"0\" tp=\"" << clTreePopulation::sapling << "\">"
         << "<fl c=\"0\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"1\">" << clModelMath::GetRand() * 79 << "</fl>"
         << "<fl c=\"2\">" << (clModelMath::GetRand() * 8) + 0.1 << "</fl>"
         << "</tree>";
  }
  oOut << "</tr_treemap>"
       << "</trees>";

  WriteGeneralizedHarvestRegimeAllometry(oOut);

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>GeneralizedHarvestRegime</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "</behaviorList>";
  oOut << "<GeneralizedHarvestRegime1>"
       << "<di_genHarvLogProbA>1</di_genHarvLogProbA>"
       << "<di_genHarvLogProbM>0.8</di_genHarvLogProbM>"
       << "<di_genHarvLogProbB>0.02</di_genHarvLogProbB>"
       << "<di_genHarvRemoveDist>1</di_genHarvRemoveDist>"
       << "<di_genHarvLogRemoveAlpha>200</di_genHarvLogRemoveAlpha>"
       << "<di_genHarvLogRemoveBeta>1</di_genHarvLogRemoveBeta>"
       << "<di_genHarvLogRemoveMu>0</di_genHarvLogRemoveMu>"
       << "<di_genHarvGammaScale>0.000001</di_genHarvGammaScale>"
       << "<di_genHarvAllowedDeviation>0.1</di_genHarvAllowedDeviation>"
       << "<di_genHarvLogCutProbAlpha>"
       << "<di_ghlcpaVal species=\"Species_1\">1</di_ghlcpaVal>"
       << "<di_ghlcpaVal species=\"Species_2\">1</di_ghlcpaVal>"
       << "</di_genHarvLogCutProbAlpha>"
       << "<di_genHarvLogCutProbBeta>"
       << "<di_ghlcpbVal species=\"Species_1\">0</di_ghlcpbVal>"
       << "<di_ghlcpbVal species=\"Species_2\">0</di_ghlcpbVal>"
       << "</di_genHarvLogCutProbBeta>"
       << "<di_genHarvLogCutProbGamma>"
       << "<di_ghlcpgVal species=\"Species_1\">0</di_ghlcpgVal>"
       << "<di_ghlcpgVal species=\"Species_2\">0</di_ghlcpgVal>"
       << "</di_genHarvLogCutProbGamma>"
       << "<di_genHarvLogCutProbMu>"
       << "<di_ghlcpmVal species=\"Species_1\">0</di_ghlcpmVal>"
       << "<di_ghlcpmVal species=\"Species_2\">0</di_ghlcpmVal>"
       << "</di_genHarvLogCutProbMu>"
       << "<di_genHarvLogCutProbA>100000</di_genHarvLogCutProbA>"
       << "<di_genHarvLogCutProbB>1</di_genHarvLogCutProbB>"
       << "<di_genHarvLogCutProbC>1</di_genHarvLogCutProbC>"
       << "<di_genHarvUseBiomassOrBA>0</di_genHarvUseBiomassOrBA>"
       << "</GeneralizedHarvestRegime1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}


////////////////////////////////////////////////////////////////////////////
// WriteGeneralizedHarvestRegimeDimensionAnalysis()
////////////////////////////////////////////////////////////////////////////
void WriteGeneralizedHarvestRegimeDimensionAnalysis(std::fstream &oOut) {
  oOut << "<DimensionAnalysis2>"
       << "<bi_a>"
       << "<bi_aVal species=\"Species_1\">1000</bi_aVal>"
       << "<bi_aVal species=\"Species_2\">1000</bi_aVal>"
       << "</bi_a>"
       << "<bi_b>"
       << "<bi_bVal species=\"Species_1\">0</bi_bVal>"
       << "<bi_bVal species=\"Species_2\">0</bi_bVal>"
       << "</bi_b>"
       << "<bi_c>"
       << "<bi_cVal species=\"Species_1\">0</bi_cVal>"
       << "<bi_cVal species=\"Species_2\">0</bi_cVal>"
       << "</bi_c>"
       << "<bi_d>"
       << "<bi_dVal species=\"Species_1\">1</bi_dVal>"
       << "<bi_dVal species=\"Species_2\">1</bi_dVal>"
       << "</bi_d>"
       << "<bi_e>"
       << "<bi_eVal species=\"Species_1\">0</bi_eVal>"
       << "<bi_eVal species=\"Species_2\">0</bi_eVal>"
       << "</bi_e>"
       << "<bi_eqID>"
       << "<bi_eiVal species=\"Species_1\">4</bi_eiVal>"
       << "<bi_eiVal species=\"Species_2\">4</bi_eiVal>"
       << "</bi_eqID>"
       << "<bi_dbhUnits>"
       << "<bi_duVal species=\"Species_1\">0</bi_duVal>"
       << "<bi_duVal species=\"Species_2\">1</bi_duVal>"
       << "</bi_dbhUnits>"
       << "<bi_biomassUnits>"
       << "<bi_buVal species=\"Species_1\">1</bi_buVal>"
       << "<bi_buVal species=\"Species_2\">1</bi_buVal>"
       << "</bi_biomassUnits>"
       << "<bi_useCorrectionFactor>"
       << "<bi_ucfVal species=\"Species_1\">0</bi_ucfVal>"
       << "<bi_ucfVal species=\"Species_2\">0</bi_ucfVal>"
       << "</bi_useCorrectionFactor>"
       << "<bi_correctionFactorValue>"
       << "<bi_cfvVal species=\"Species_1\">1</bi_cfvVal>"
       << "<bi_cfvVal species=\"Species_2\">1</bi_cfvVal>"
       << "</bi_correctionFactorValue>"
       << "<bi_whatDia>"
       << "<bi_wdVal species=\"Species_1\">0</bi_wdVal>"
       << "<bi_wdVal species=\"Species_2\">0</bi_wdVal>"
       << "</bi_whatDia>"
       << "</DimensionAnalysis2>";
}

////////////////////////////////////////////////////////////////////////////
// WriteGeneralizedHarvestRegimeAllometry()
////////////////////////////////////////////////////////////////////////////
void WriteGeneralizedHarvestRegimeAllometry(std::fstream &oOut) {
  oOut << "<allometry>"
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
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_stdMaxCrownRad>"
       << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
       << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
       << "</tr_stdMaxCrownRad>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.0269</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0241</tr_soahVal>"
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

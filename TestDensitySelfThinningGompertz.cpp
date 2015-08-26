//---------------------------------------------------------------------------
// TestDensitySelfThinningGompertz.cpp
//---------------------------------------------------------------------------
#include "TestDensitySelfThinningGompertz.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "TreePopulation.h"
#include "BehaviorBase.h"
#include <fstream>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
/////////////////////////////////////////////////////////////////////////////
TEST(DensitySelfThinningGompertz, TestNormalProcessingRun1 ) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;

  float fDiam, fX, fY;
  int *p_iNumSeedlings, i, iNumSpecies;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteDensitySelfThinningGompertzXMLFile1() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    iNumSpecies = p_oPop->GetNumberOfSpecies();

    //Set up our tree count array
    p_iNumSeedlings = new int[iNumSpecies];

    //Create 1000 of each kind of tree affected by mortality
    //Seedlings of Species 1, 2, 3
    fDiam = 0.01;
    for (i = 0; i < 1000; i++) {
      //Cell 0, 0
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::seedling, fDiam);
      p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::seedling, fDiam);

      //Far away where there will be no neighbors
      p_oTree = p_oPop->CreateTree(50, 50, 0, clTreePopulation::seedling, fDiam);
      p_oTree = p_oPop->CreateTree(50, 50, 1, clTreePopulation::seedling, fDiam);
      p_oTree = p_oPop->CreateTree(50, 50, 2, clTreePopulation::seedling, fDiam);
    }

    //Neighbors
    for (i = 0; i < 100; i++) {
      fDiam = 0.279166667;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 0, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 100; i++) {
      fDiam = 2.842696629;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 1, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 200; i++) {  //neighbor too short
      fDiam = 1.250582751;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 2, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 300; i++) {
      fDiam = 3.465034965;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 2, clTreePopulation::sapling, fDiam);
    }


    //Run for one timestep
    p_oSimManager->RunSim(1);


    //Count the seedlings in cell 0,0
    for (i = 0; i < iNumSpecies; i++)
      p_iNumSeedlings[i] = 0;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (clTreePopulation::seedling == p_oTree->GetType()) {
        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
        if (fX == 1) p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure they are as expected
    //Seedlings of Species 1
    EXPECT_EQ(p_iNumSeedlings[0], 1000);
    //Seedlings of Species 2
    EXPECT_LT(fabs(p_iNumSeedlings[1] - 920.3) / p_iNumSeedlings[1], 0.10 );
    //Seedlings of Species 3
    EXPECT_LT(fabs(p_iNumSeedlings[2] - 951.36) / p_iNumSeedlings[2], 0.10 );

    //Count the seedlings with no neighbors
    for (i = 0; i < iNumSpecies; i++)
      p_iNumSeedlings[i] = 0;

    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (clTreePopulation::seedling == p_oTree->GetType()) {
        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
        if (fX == 50) p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure they are as expected
    EXPECT_EQ(p_iNumSeedlings[0], 1000);
    EXPECT_LT(fabs(p_iNumSeedlings[1] - 920.3) / p_iNumSeedlings[1], 0.10 );
    EXPECT_EQ(p_iNumSeedlings[2], 1000);

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
/////////////////////////////////////////////////////////////////////////////
TEST(DensitySelfThinningGompertz, TestNormalProcessingRun2 ) {
  clTreePopulation * p_oPop;
  clTreeSearch *p_oAllTrees;
  clTree *p_oTree;

  float fDiam, fX, fY;
  int *p_iNumSeedlings, i, iNumSpecies;

  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try {
    //Load our test file and get our tree population pointers
    p_oSimManager->ReadFile( WriteDensitySelfThinningGompertzXMLFile2() );
    p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
    iNumSpecies = p_oPop->GetNumberOfSpecies();

    //Set up our tree count array
    p_iNumSeedlings = new int[iNumSpecies];

    //Create 1000 of each kind of tree affected by mortality
    //Seedlings of Species 1, 2, 3
    fDiam = 0.01;
    for (i = 0; i < 1000; i++) {
      //Cell 0, 0
      p_oTree = p_oPop->CreateTree(1, 1, 0, clTreePopulation::seedling, fDiam);
      p_oTree = p_oPop->CreateTree(1, 1, 1, clTreePopulation::seedling, fDiam);
      p_oTree = p_oPop->CreateTree(1, 1, 2, clTreePopulation::seedling, fDiam);

      //Far away where there will be no neighbors
      p_oTree = p_oPop->CreateTree(50, 50, 0, clTreePopulation::seedling, fDiam);
      p_oTree = p_oPop->CreateTree(50, 50, 1, clTreePopulation::seedling, fDiam);
      p_oTree = p_oPop->CreateTree(50, 50, 2, clTreePopulation::seedling, fDiam);
    }

    //Neighbors
    for (i = 0; i < 100; i++) {
      fDiam = 0.279166667;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 0, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 100; i++) {
      fDiam = 2.842696629;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 1, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 200; i++) {  //neighbor too short
      fDiam = 1.250582751;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 2, clTreePopulation::sapling, fDiam);
    }
    for (i = 0; i < 300; i++) {
      fDiam = 3.465034965;
      fX = 2 + (clModelMath::GetRand() * 4);
      fY = 2 + (clModelMath::GetRand() * 4);
      p_oPop->CreateTree(fX, fY, 2, clTreePopulation::sapling, fDiam);
    }


    //Run for one timestep
    p_oSimManager->RunSim(1);


    //Count the seedlings in cell 0,0
    for (i = 0; i < iNumSpecies; i++)
      p_iNumSeedlings[i] = 0;

    p_oAllTrees = p_oPop->Find("all");
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (clTreePopulation::seedling == p_oTree->GetType()) {
        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
        if (fX == 1) p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure they are as expected
    //Seedlings of Species 1
    EXPECT_EQ(p_iNumSeedlings[0], 1000);
    //Seedlings of Species 2
    EXPECT_LT(fabs(p_iNumSeedlings[1] - 779.556) / p_iNumSeedlings[1], 0.10 );
    //Seedlings of Species 3
    EXPECT_LT(fabs(p_iNumSeedlings[2] - 861.069) / p_iNumSeedlings[2], 0.10 );

    //Count the seedlings with no neighbors
    for (i = 0; i < iNumSpecies; i++)
      p_iNumSeedlings[i] = 0;

    p_oAllTrees->StartOver();
    p_oTree = p_oAllTrees->NextTree();
    while (p_oTree) {
      if (clTreePopulation::seedling == p_oTree->GetType()) {
        p_oTree->GetValue(p_oPop->GetXCode(p_oTree->GetSpecies(), p_oTree->GetType()), &fX);
        if (fX == 50) p_iNumSeedlings[p_oTree->GetSpecies()]++;
      }
      p_oTree = p_oAllTrees->NextTree();
    }

    //Make sure they are as expected
    EXPECT_EQ(p_iNumSeedlings[0], 1000);
    EXPECT_LT(fabs(p_iNumSeedlings[1] - 779.556) / p_iNumSeedlings[1], 0.10 );
    EXPECT_EQ(p_iNumSeedlings[2], 1000);

    delete[] p_iNumSeedlings;
    delete p_oSimManager;
  } catch (modelErr &e) {
    delete[] p_iNumSeedlings;
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
/////////////////////////////////////////////////////////////////////////////

TEST(DensitySelfThinningGompertz ,  TestErrorProcessing ) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile(WriteDensitySelfThinningGompertzXMLErrorFile1());
    FAIL() << "TestDensitySelfThinningGompertz error processing didn't catch error for WriteDensitySelfThinningGompertzXMLErrorFile1.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDensitySelfThinningGompertz::DoShellSetup" ) != 0)
    {
      FAIL() << "TestDensitySelfThinningGompertz error processing caught the wrong error for WriteDensitySelfThinningGompertzXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile(WriteDensitySelfThinningGompertzXMLErrorFile2());
    FAIL() << "TestDensitySelfThinningGompertz error processing didn't catch error for WriteDensitySelfThinningGompertzXMLErrorFile2.";
  }
  catch (modelErr& err)
  {
    if (err.sFunction.compare("clDensitySelfThinningGompertz::DoShellSetup" ) != 0)
    {
      FAIL() << "TestDensitySelfThinningGompertz error processing caught the wrong error for WriteDensitySelfThinningGompertzXMLErrorFile2.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningGompertzXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySelfThinningGompertzXMLFile1()
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
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>1.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>";

  WriteDensitySelfThinningGompertzCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>GompertzDensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<GompertzDensitySelfThinning1>"
      << "<mo_gompertzSelfThinningG>"
      << "<mo_gstgVal species=\"Species_2\">0.08</mo_gstgVal>"
      << "<mo_gstgVal species=\"Species_3\">1.8</mo_gstgVal>"
      << "</mo_gompertzSelfThinningG>"
      << "<mo_gompertzSelfThinningH>"
      << "<mo_gsthVal species=\"Species_2\">5</mo_gsthVal>"
      << "<mo_gsthVal species=\"Species_3\">5</mo_gsthVal>"
      << "</mo_gompertzSelfThinningH>"
      << "<mo_gompertzSelfThinningI>"
      << "<mo_gstiVal species=\"Species_2\">26.6</mo_gstiVal>"
      << "<mo_gstiVal species=\"Species_3\">3.152</mo_gstiVal>"
      << "</mo_gompertzSelfThinningI>"
      << "<mo_gompertzSelfThinningMinHeight>"
      << "<mo_gstmhVal species=\"Species_2\">0</mo_gstmhVal>"
      << "<mo_gstmhVal species=\"Species_3\">1.35</mo_gstmhVal>"
      << "</mo_gompertzSelfThinningMinHeight>"
      << "<mo_gompertzSelfThinningRadius>9</mo_gompertzSelfThinningRadius>"
      << "</GompertzDensitySelfThinning1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningGompertzXMLFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySelfThinningGompertzXMLFile2()
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
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>3.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>";

  WriteDensitySelfThinningGompertzCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>GompertzDensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<GompertzDensitySelfThinning1>"
      << "<mo_gompertzSelfThinningG>"
      << "<mo_gstgVal species=\"Species_2\">0.08</mo_gstgVal>"
      << "<mo_gstgVal species=\"Species_3\">1.8</mo_gstgVal>"
      << "</mo_gompertzSelfThinningG>"
      << "<mo_gompertzSelfThinningH>"
      << "<mo_gsthVal species=\"Species_2\">5</mo_gsthVal>"
      << "<mo_gsthVal species=\"Species_3\">5</mo_gsthVal>"
      << "</mo_gompertzSelfThinningH>"
      << "<mo_gompertzSelfThinningI>"
      << "<mo_gstiVal species=\"Species_2\">26.6</mo_gstiVal>"
      << "<mo_gstiVal species=\"Species_3\">3.152</mo_gstiVal>"
      << "</mo_gompertzSelfThinningI>"
      << "<mo_gompertzSelfThinningMinHeight>"
      << "<mo_gstmhVal species=\"Species_2\">0</mo_gstmhVal>"
      << "<mo_gstmhVal species=\"Species_3\">1.35</mo_gstmhVal>"
      << "</mo_gompertzSelfThinningMinHeight>"
      << "<mo_gompertzSelfThinningRadius>9</mo_gompertzSelfThinningRadius>"
      << "</GompertzDensitySelfThinning1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningGompertzXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySelfThinningGompertzXMLErrorFile1()
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
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>3.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>";

  WriteDensitySelfThinningGompertzCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>GompertzDensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<GompertzDensitySelfThinning1>"
      << "<mo_gompertzSelfThinningG>"
      << "<mo_gstgVal species=\"Species_2\">0.08</mo_gstgVal>"
      << "<mo_gstgVal species=\"Species_3\">1.8</mo_gstgVal>"
      << "</mo_gompertzSelfThinningG>"
      << "<mo_gompertzSelfThinningH>"
      << "<mo_gsthVal species=\"Species_2\">5</mo_gsthVal>"
      << "<mo_gsthVal species=\"Species_3\">5</mo_gsthVal>"
      << "</mo_gompertzSelfThinningH>"
      << "<mo_gompertzSelfThinningI>"
      << "<mo_gstiVal species=\"Species_2\">26.6</mo_gstiVal>"
      << "<mo_gstiVal species=\"Species_3\">3.152</mo_gstiVal>"
      << "</mo_gompertzSelfThinningI>"
      << "<mo_gompertzSelfThinningMinHeight>"
      << "<mo_gstmhVal species=\"Species_2\">0</mo_gstmhVal>"
      << "<mo_gstmhVal species=\"Species_3\">1.35</mo_gstmhVal>"
      << "</mo_gompertzSelfThinningMinHeight>"
      << "<mo_gompertzSelfThinningRadius>-9</mo_gompertzSelfThinningRadius>"
      << "</GompertzDensitySelfThinning1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningGompertzXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteDensitySelfThinningGompertzXMLErrorFile2()
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
      << "<rt_timestep>0</rt_timestep>"
      << "<randomSeed>0</randomSeed>"
      << "<yearsPerTimestep>3.0</yearsPerTimestep>"
      << "<plot_lenX>100.0</plot_lenX>"
      << "<plot_lenY>100.0</plot_lenY>"
      << "<plot_precip_mm_yr>1150.645781</plot_precip_mm_yr>"
      << "<plot_temp_C>12.88171785</plot_temp_C>"
      << "<plot_latitude>0.0</plot_latitude>"
      << "</plot>";

  WriteDensitySelfThinningGompertzCommonStuff(oOut);

  oOut << "<behaviorList>"
      << "<behavior>"
      << "<behaviorName>GompertzDensitySelfThinning</behaviorName>"
      << "<version>1.0</version>"
      << "<listPosition>1</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "</behavior>"
      << "<behavior>"
      << "<behaviorName>RemoveDead</behaviorName>"
      << "<version>2.0</version>"
      << "<listPosition>2</listPosition>"
      << "<applyTo species=\"Species_2\" type=\"Seedling\" />"
      << "<applyTo species=\"Species_3\" type=\"Seedling\" />"
      << "</behavior>"
      << "</behaviorList>"
      << "<GompertzDensitySelfThinning1>"
      << "<mo_gompertzSelfThinningG>"
      << "<mo_gstgVal species=\"Species_2\">0.08</mo_gstgVal>"
      << "<mo_gstgVal species=\"Species_3\">1.8</mo_gstgVal>"
      << "</mo_gompertzSelfThinningG>"
      << "<mo_gompertzSelfThinningH>"
      << "<mo_gsthVal species=\"Species_2\">5</mo_gsthVal>"
      << "<mo_gsthVal species=\"Species_3\">5</mo_gsthVal>"
      << "</mo_gompertzSelfThinningH>"
      << "<mo_gompertzSelfThinningI>"
      << "<mo_gstiVal species=\"Species_2\">26.6</mo_gstiVal>"
      << "<mo_gstiVal species=\"Species_3\">3.152</mo_gstiVal>"
      << "</mo_gompertzSelfThinningI>"
      << "<mo_gompertzSelfThinningMinHeight>"
      << "<mo_gstmhVal species=\"Species_2\">0</mo_gstmhVal>"
      << "<mo_gstmhVal species=\"Species_3\">-1.35</mo_gstmhVal>"
      << "</mo_gompertzSelfThinningMinHeight>"
      << "<mo_gompertzSelfThinningRadius>9</mo_gompertzSelfThinningRadius>"
      << "</GompertzDensitySelfThinning1>"
      << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteDensitySelfThinningGompertzCommonStuff()
/////////////////////////////////////////////////////////////////////////////
void WriteDensitySelfThinningGompertzCommonStuff(std::fstream &oOut) {
  oOut << "<trees>"
      << "<tr_speciesList>"
      << "<tr_species speciesName=\"Species_1\"/>"
      << "<tr_species speciesName=\"Species_2\"/>"
      << "<tr_species speciesName=\"Species_3\"/>"
      << "</tr_speciesList>"
      << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
      << "<tr_minAdultDBH>"
      << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
      << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
      << "</tr_minAdultDBH>"
      << "<tr_maxSeedlingHeight>"
      << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
      << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
      << "</tr_maxSeedlingHeight>"
      << "</trees>"
      << "<allometry>"
      << "<tr_canopyHeight>"
      << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
      << "<tr_chVal species=\"Species_2\">39.54</tr_chVal>"
      << "<tr_chVal species=\"Species_3\">40.0</tr_chVal>"
      << "</tr_canopyHeight>"
      << "<tr_stdAsympCrownRad>"
      << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_2\">0.0614</tr_sacrVal>"
      << "<tr_sacrVal species=\"Species_3\">0.0242</tr_sacrVal>"
      << "</tr_stdAsympCrownRad>"
      << "<tr_stdCrownRadExp>"
      << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
      << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
      << "</tr_stdCrownRadExp>"
      << "<tr_stdMaxCrownRad>"
      << "<tr_smcrVal species=\"Species_1\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_2\">10</tr_smcrVal>"
      << "<tr_smcrVal species=\"Species_3\">10</tr_smcrVal>"
      << "</tr_stdMaxCrownRad>"
      << "<tr_conversionDiam10ToDBH>"
      << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_2\">0.5944</tr_cdtdVal>"
      << "<tr_cdtdVal species=\"Species_3\">0.7059</tr_cdtdVal>"
      << "</tr_conversionDiam10ToDBH>"
      << "<tr_interceptDiam10ToDBH>"
      << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
      << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
      << "</tr_interceptDiam10ToDBH>"
      << "<tr_stdAsympCrownHt>"
      << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
      << "<tr_sachVal species=\"Species_2\">0.368</tr_sachVal>"
      << "<tr_sachVal species=\"Species_3\">0.464</tr_sachVal>"
      << "</tr_stdAsympCrownHt>"
      << "<tr_stdCrownHtExp>"
      << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
      << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
      << "</tr_stdCrownHtExp>"
      << "<tr_adultLinearSlope>"
      << "<tr_alsVal species=\"Species_1\">0.96</tr_alsVal>"
      << "<tr_alsVal species=\"Species_2\">0.89</tr_alsVal>"
      << "<tr_alsVal species=\"Species_3\">0.858</tr_alsVal>"
      << "</tr_adultLinearSlope>"
      << "<tr_adultLinearIntercept>"
      << "<tr_aliVal species=\"Species_1\">-0.258</tr_aliVal>"
      << "<tr_aliVal species=\"Species_2\">-0.33</tr_aliVal>"
      << "<tr_aliVal species=\"Species_3\">0.027</tr_aliVal>"
      << "</tr_adultLinearIntercept>"
      << "<tr_saplingLinearSlope>"
      << "<tr_salsVal species=\"Species_1\">0.96</tr_salsVal>"
      << "<tr_salsVal species=\"Species_2\">0.89</tr_salsVal>"
      << "<tr_salsVal species=\"Species_3\">0.858</tr_salsVal>"
      << "</tr_saplingLinearSlope>"
      << "<tr_saplingLinearIntercept>"
      << "<tr_saliVal species=\"Species_1\">-0.258</tr_saliVal>"
      << "<tr_saliVal species=\"Species_2\">-0.33</tr_saliVal>"
      << "<tr_saliVal species=\"Species_3\">0.027</tr_saliVal>"
      << "</tr_saplingLinearIntercept>"
      << "<tr_seedlingLinearSlope>"
      << "<tr_selsVal species=\"Species_1\">0.96</tr_selsVal>"
      << "<tr_selsVal species=\"Species_2\">0.89</tr_selsVal>"
      << "<tr_selsVal species=\"Species_3\">0.858</tr_selsVal>"
      << "</tr_seedlingLinearSlope>"
      << "<tr_seedlingLinearIntercept>"
      << "<tr_seliVal species=\"Species_1\">-0.258</tr_seliVal>"
      << "<tr_seliVal species=\"Species_2\">-0.33</tr_seliVal>"
      << "<tr_seliVal species=\"Species_3\">0.027</tr_seliVal>"
      << "</tr_seedlingLinearIntercept>"
      << "<tr_whatSeedlingHeightDiam>"
      << "<tr_wsehdVal species=\"Species_1\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_2\">1</tr_wsehdVal>"
      << "<tr_wsehdVal species=\"Species_3\">1</tr_wsehdVal>"
      << "</tr_whatSeedlingHeightDiam>"
      << "<tr_whatSaplingHeightDiam>"
      << "<tr_wsahdVal species=\"Species_1\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_2\">1</tr_wsahdVal>"
      << "<tr_wsahdVal species=\"Species_3\">1</tr_wsahdVal>"
      << "</tr_whatSaplingHeightDiam>"
      << "<tr_whatAdultHeightDiam>"
      << "<tr_wahdVal species=\"Species_1\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_2\">1</tr_wahdVal>"
      << "<tr_wahdVal species=\"Species_3\">1</tr_wahdVal>"
      << "</tr_whatAdultHeightDiam>"
      << "<tr_whatAdultCrownRadDiam>"
      << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
      << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
      << "</tr_whatAdultCrownRadDiam>"
      << "<tr_whatAdultCrownHeightHeight>"
      << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
      << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
      << "</tr_whatAdultCrownHeightHeight>"
      << "<tr_whatSaplingCrownRadDiam>"
      << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
      << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
      << "</tr_whatSaplingCrownRadDiam>"
      << "<tr_whatSaplingCrownHeightHeight>"
      << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
      << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
      << "</tr_whatSaplingCrownHeightHeight>"
      << "</allometry>";
}

//---------------------------------------------------------------------------
// TestStormDirectKiller.cpp
//---------------------------------------------------------------------------
#include "TestStormDirectKiller.h"
#include <gtest/gtest.h>
#include "SimManager.h"
#include "Grid.h"
#include "TreePopulation.h"
#include "Storm.h"
#include <fstream>
#include <sstream>
#include <math.h>

////////////////////////////////////////////////////////////////////////////
// TestErrorProcessing()
////////////////////////////////////////////////////////////////////////////
TEST(StormDirectKiller, TestErrorProcessing)
{
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  try
  {
    p_oSimManager->ReadFile( WriteStormDirectKillerXMLErrorFile1() );
    FAIL() << "TestStormDirectKiller error processing didn't catch error for WriteStormDirectKillerXMLErrorFile1.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormDirectKiller::GetGridInfo" ) != 0 )
    {
      FAIL() << "TestStormDirectKiller error processing caught wrong error for WriteStormDirectKillerXMLErrorFile1.";
    }
    ;
  }

  try
  {
    p_oSimManager->ReadFile( WriteStormDirectKillerXMLErrorFile2() );
    FAIL() << "TestStormDirectKiller error processing didn't catch error for WriteStormDirectKillerXMLErrorFile2.";
  }
  catch ( modelErr& err )
  {
    if ( err.sFunction.compare("clStormDirectKiller::GetDeadCodes" ) != 0 )
    {
      FAIL() << "TestStormDirectKiller error processing caught wrong error for WriteStormDirectKillerXMLErrorFile2.";
    }
    ;
  }
  delete p_oSimManager;
}

/////////////////////////////////////////////////////////////////////////////
// TestNormalProcessingRun1()
// Tests normal processing. WriteStormDirectKillerXMLFile1() writes the parameter file.
// Aspects of the run:
// -- 4 species.
// -- Plot size 50X50.
// -- Behavior applied to seedlings, saplings, and adults of species 1 and 4,
//    adults only of species 2, none of species 3.
// -- Susceptibility map - 25X25 m cells; 0 in southern half of the plot, 1 in
//    northern half.
// -- 1000 each of seedlings, saplings, and adults of each species, on each
//    half of the plot.
// -- Timestep 1: No storms.
// -- Timestep 2: Storm of 0.2.
// -- Timestep 3: No storms.
// -- Timestep 4: Storm of 0.5 and 0.6.
//
// The run proceeds for 5 timesteps and the number of trees with each damage
// counter is checked through time.
/////////////////////////////////////////////////////////////////////////////
TEST(StormDirectKiller, TestNormalProcessingRun1) {
  clSimManager * p_oSimManager = new clSimManager( 7, 1, "" );
  int **p_iNorthCount, **p_iSouthCount; //Tree counts - species by type
  try {
  //Feed our file to the sim manager
  p_oSimManager->ReadFile( WriteStormDirectKillerXMLFile1() );

  //Get the tree population
  clTreePopulation * p_oPop = ( clTreePopulation * ) p_oSimManager->GetPopulationObject( "treepopulation" );
  clTreeSearch * p_oAllTrees;
  clTree * p_oTree;
  float fY;
  int i, j, iNumSpecies = p_oPop->GetNumberOfSpecies(),
      iNumTypes = p_oPop->GetNumberOfTypes();

  p_iNorthCount = new int*[iNumSpecies];
  p_iSouthCount = new int*[iNumSpecies];
  for (i = 0; i < iNumSpecies; i++) {
    p_iNorthCount[i] = new int[iNumTypes];
    p_iSouthCount[i] = new int[iNumTypes];
    for (j = 0; j < iNumTypes; j++) {
      p_iNorthCount[i][j] = 0;
      p_iSouthCount[i][j] = 0;
    }
  }

  //Add 1000 trees of each species and type to both the northern and southern
  //halves of the plot.
  for ( i = 0; i < 1000; i++ )
  {
    p_oPop->CreateTree( 1.0, 1.0, 0, clTreePopulation::adult, 30.0 );
    p_oPop->CreateTree( 9.0, 1.0, 1, clTreePopulation::adult, 30.0 );
    p_oPop->CreateTree( 1.0, 9.0, 2, clTreePopulation::adult, 30.0 );
    p_oPop->CreateTree( 9.0, 9.0, 3, clTreePopulation::adult, 30.0 );
    p_oPop->CreateTree( 25.0, 1.0, 0, clTreePopulation::sapling, 4.0 );
    p_oPop->CreateTree( 33.0, 1.0, 1, clTreePopulation::sapling, 4.0 );
    p_oPop->CreateTree( 25.0, 9.0, 2, clTreePopulation::sapling, 4.0 );
    p_oPop->CreateTree( 33.0, 9.0, 3, clTreePopulation::sapling, 4.0 );
    p_oPop->CreateTree( 41.0, 1.0, 0, clTreePopulation::seedling, 1.0 );
    p_oPop->CreateTree( 49.0, 1.0, 1, clTreePopulation::seedling, 1.0 );
    p_oPop->CreateTree( 41.0, 9.0, 2, clTreePopulation::seedling, 1.0 );
    p_oPop->CreateTree( 49.0, 9.0, 3, clTreePopulation::seedling, 1.0 );

    p_oPop->CreateTree( 1.0, 30.0, 0, clTreePopulation::adult, 30.0 );
    p_oPop->CreateTree( 9.0, 30.0, 1, clTreePopulation::adult, 30.0 );
    p_oPop->CreateTree( 1.0, 39.0, 2, clTreePopulation::adult, 30.0 );
    p_oPop->CreateTree( 9.0, 39.0, 3, clTreePopulation::adult, 30.0 );
    p_oPop->CreateTree( 25.0, 30.0, 0, clTreePopulation::sapling, 4.0 );
    p_oPop->CreateTree( 33.0, 30.0, 1, clTreePopulation::sapling, 4.0 );
    p_oPop->CreateTree( 25.0, 39.0, 2, clTreePopulation::sapling, 4.0 );
    p_oPop->CreateTree( 33.0, 39.0, 3, clTreePopulation::sapling, 4.0 );
    p_oPop->CreateTree( 41.0, 30.0, 0, clTreePopulation::seedling, 1.0 );
    p_oPop->CreateTree( 49.0, 30.0, 1, clTreePopulation::seedling, 1.0 );
    p_oPop->CreateTree( 41.0, 39.0, 2, clTreePopulation::seedling, 1.0 );
    p_oPop->CreateTree( 49.0, 39.0, 3, clTreePopulation::seedling, 1.0 );
  }

  //Timestep 1: no storms. All trees should still be present.
  p_oSimManager->RunSim(1);
  p_oAllTrees = p_oPop->Find( "all" );
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    p_oTree->GetValue( p_oPop->GetYCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fY );
    if (fY < 25)
      p_iSouthCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    else
      p_iNorthCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;

    p_oTree = p_oAllTrees->NextTree();
  }

  for (i = 0; i < iNumSpecies; i++) {
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::seedling]);
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::sapling]);
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::adult]);

    EXPECT_EQ(1000, p_iNorthCount[i][clTreePopulation::seedling]);
    EXPECT_EQ(1000, p_iNorthCount[i][clTreePopulation::sapling]);
    EXPECT_EQ(1000, p_iNorthCount[i][clTreePopulation::adult]);
  }

  for (i = 0; i < iNumSpecies; i++) {
    for (j = 0; j < iNumTypes; j++) {
      p_iNorthCount[i][j] = 0;
      p_iSouthCount[i][j] = 0;
    }
  }

  //Timestep 2: storm of 0.2.
  p_oSimManager->RunSim(1);
  p_oAllTrees = p_oPop->Find( "all" );
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    p_oTree->GetValue( p_oPop->GetYCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fY );
    if (fY < 25)
      p_iSouthCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    else
      p_iNorthCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;

    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  for (i = 0; i < iNumSpecies; i++) {
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::seedling]);
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::sapling]);
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::adult]);
  }

  //Species 1
  EXPECT_LT(fabs(919 - p_iNorthCount[0][clTreePopulation::seedling])/919, 0.1);
  EXPECT_LT(fabs(919 - p_iNorthCount[0][clTreePopulation::sapling])/919, 0.1);
  EXPECT_LT(fabs(919 - p_iNorthCount[0][clTreePopulation::adult])/919, 0.1);

  //Species 2
  EXPECT_EQ(1000, p_iNorthCount[1][clTreePopulation::seedling]);
  EXPECT_EQ(1000, p_iNorthCount[1][clTreePopulation::sapling]);
  EXPECT_LT(fabs(230 - p_iNorthCount[1][clTreePopulation::adult])/230, 0.1);

  //Species 3
  EXPECT_EQ(1000, p_iNorthCount[2][clTreePopulation::seedling]);
  EXPECT_EQ(1000, p_iNorthCount[2][clTreePopulation::sapling]);
  EXPECT_EQ(1000, p_iNorthCount[2][clTreePopulation::adult]);

  //Species 4
  EXPECT_LT(p_iNorthCount[3][clTreePopulation::seedling], 10);
  EXPECT_LT(p_iNorthCount[3][clTreePopulation::sapling], 10);
  EXPECT_LT(p_iNorthCount[3][clTreePopulation::adult], 10);

  for (i = 0; i < iNumSpecies; i++) {
    for (j = 0; j < iNumTypes; j++) {
      p_iNorthCount[i][j] = 0;
      p_iSouthCount[i][j] = 0;
    }
  }

  //Timestep 3: No storms.
  p_oSimManager->RunSim(1);
  p_oAllTrees = p_oPop->Find( "all" );
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    p_oTree->GetValue( p_oPop->GetYCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fY );
    if (fY < 25)
      p_iSouthCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    else
      p_iNorthCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;

    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  for (i = 0; i < iNumSpecies; i++) {
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::seedling]);
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::sapling]);
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::adult]);
  }

  //Species 1
  EXPECT_LT(fabs(919 - p_iNorthCount[0][clTreePopulation::seedling])/919, 0.1);
  EXPECT_LT(fabs(919 - p_iNorthCount[0][clTreePopulation::sapling])/919, 0.1);
  EXPECT_LT(fabs(919 - p_iNorthCount[0][clTreePopulation::adult])/919, 0.1);

  //Species 2
  EXPECT_EQ(1000, p_iNorthCount[1][clTreePopulation::seedling]);
  EXPECT_EQ(1000, p_iNorthCount[1][clTreePopulation::sapling]);
  EXPECT_LT(fabs(230 - p_iNorthCount[1][clTreePopulation::adult])/230, 0.1);

  //Species 3
  EXPECT_EQ(1000, p_iNorthCount[2][clTreePopulation::seedling]);
  EXPECT_EQ(1000, p_iNorthCount[2][clTreePopulation::sapling]);
  EXPECT_EQ(1000, p_iNorthCount[2][clTreePopulation::adult]);

  //Species 4
  EXPECT_LT(p_iNorthCount[3][clTreePopulation::seedling], 10);
  EXPECT_LT(p_iNorthCount[3][clTreePopulation::sapling], 10);
  EXPECT_LT(p_iNorthCount[3][clTreePopulation::adult], 10);

  for (i = 0; i < iNumSpecies; i++) {
    for (j = 0; j < iNumTypes; j++) {
      p_iNorthCount[i][j] = 0;
      p_iSouthCount[i][j] = 0;
    }
  }

  //Timestep 4: Two storms.
  p_oSimManager->RunSim(1);
  p_oAllTrees = p_oPop->Find( "all" );
  p_oTree = p_oAllTrees->NextTree();
  while ( p_oTree )
  {
    p_oTree->GetValue( p_oPop->GetYCode( p_oTree->GetSpecies(), p_oTree->GetType() ), & fY );
    if (fY < 25)
      p_iSouthCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;
    else
      p_iNorthCount[p_oTree->GetSpecies()][p_oTree->GetType()]++;

    p_oTree = p_oAllTrees->NextTree();
  }

  //Validate the counts
  for (i = 0; i < iNumSpecies; i++) {
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::seedling]);
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::sapling]);
    EXPECT_EQ(1000, p_iSouthCount[i][clTreePopulation::adult]);
  }

  //Species 1
  EXPECT_LT(fabs(421 - p_iNorthCount[0][clTreePopulation::seedling])/421, 0.1);
  EXPECT_LT(fabs(421 - p_iNorthCount[0][clTreePopulation::sapling])/421, 0.1);
  EXPECT_LT(fabs(421 - p_iNorthCount[0][clTreePopulation::adult])/421, 0.1);

  //Species 2
  EXPECT_EQ(1000, p_iNorthCount[1][clTreePopulation::seedling]);
  EXPECT_EQ(1000, p_iNorthCount[1][clTreePopulation::sapling]);
  //EXPECT_LT(fabs(68 - p_iNorthCount[1][clTreePopulation::adult])/68, 0.1);
  EXPECT_GT(p_iNorthCount[1][clTreePopulation::adult], 50);
  EXPECT_LT(p_iNorthCount[1][clTreePopulation::adult], 90);

  //Species 3
  EXPECT_EQ(1000, p_iNorthCount[2][clTreePopulation::seedling]);
  EXPECT_EQ(1000, p_iNorthCount[2][clTreePopulation::sapling]);
  EXPECT_EQ(1000, p_iNorthCount[2][clTreePopulation::adult]);

  //Species 4
  EXPECT_LT(p_iNorthCount[3][clTreePopulation::seedling], 10);
  EXPECT_LT(p_iNorthCount[3][clTreePopulation::sapling], 10);
  EXPECT_LT(p_iNorthCount[3][clTreePopulation::adult], 10);

  for (i = 0; i < iNumSpecies; i++) {
    delete[] p_iNorthCount[i];
    delete[] p_iSouthCount[i];
  }
  delete[] p_iNorthCount;
  delete[] p_iSouthCount;
  delete p_oSimManager;
  } catch (modelErr &e) {
    delete p_oSimManager;
    FAIL() << "Testing failed in function: " << e.sFunction << " with message: " << e.sMoreInfo;
  }
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormDirectKillerXMLFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormDirectKillerXMLFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>50</plot_lenX>"
       << "<plot_lenY>50</plot_lenY>"
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
       << "</tr_speciesList>"
       << "<tr_seedDiam10Cm>0.1</tr_seedDiam10Cm>"
       << "<tr_minAdultDBH>"
       << "<tr_madVal species=\"Species_1\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_2\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_3\">10.0</tr_madVal>"
       << "<tr_madVal species=\"Species_4\">10.0</tr_madVal>"
       << "</tr_minAdultDBH>"
       << "<tr_maxSeedlingHeight>"
       << "<tr_mshVal species=\"Species_1\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_2\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_3\">1.35</tr_mshVal>"
       << "<tr_mshVal species=\"Species_4\">1.35</tr_mshVal>"
       << "</tr_maxSeedlingHeight>"
       << "</trees>"
       << "<grid gridName=\"Storm Susceptibility\">"
       << "<ma_floatCodes>"
       << "<ma_floatCode label=\"index\">0</ma_floatCode>"
       << "</ma_floatCodes>"
       << "<ma_plotLenX>50.0</ma_plotLenX>"
       << "<ma_plotLenY>50.0</ma_plotLenY>"
       << "<ma_lengthXCells>25.0</ma_lengthXCells>"
       << "<ma_lengthYCells>25.0</ma_lengthYCells>"
       << "<ma_v x=\"0\" y=\"0\">"
       << "<fl c=\"0\">0</fl>"
       << "</ma_v>"
       << "<ma_v x=\"0\" y=\"1\">"
       << "<fl c=\"0\">1</fl>"
       << "</ma_v>"
       << "<ma_v x=\"1\" y=\"0\">"
       << "<fl c=\"0\">0</fl>"
       << "</ma_v>"
       << "<ma_v x=\"1\" y=\"1\">"
       << "<fl c=\"0\">1</fl>"
       << "</ma_v>"
       << "</grid>"
       << "<allometry>"
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_3\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_4\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
       << "<tr_canopyHeight>"
       << "<tr_chVal species=\"Species_1\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_2\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_3\">39.48</tr_chVal>"
       << "<tr_chVal species=\"Species_4\">39.48</tr_chVal>"
       << "</tr_canopyHeight>"
       << "<tr_stdAsympCrownRad>"
       << "<tr_sacrVal species=\"Species_1\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_2\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_3\">0.0549</tr_sacrVal>"
       << "<tr_sacrVal species=\"Species_4\">0.0549</tr_sacrVal>"
       << "</tr_stdAsympCrownRad>"
       << "<tr_stdCrownRadExp>"
       << "<tr_screVal species=\"Species_1\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_2\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_3\">1.0</tr_screVal>"
       << "<tr_screVal species=\"Species_4\">1.0</tr_screVal>"
       << "</tr_stdCrownRadExp>"
       << "<tr_conversionDiam10ToDBH>"
       << "<tr_cdtdVal species=\"Species_1\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_2\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_3\">0.8008</tr_cdtdVal>"
       << "<tr_cdtdVal species=\"Species_4\">0.8008</tr_cdtdVal>"
       << "</tr_conversionDiam10ToDBH>"
       << "<tr_interceptDiam10ToDBH>"
       << "<tr_idtdVal species=\"Species_1\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_2\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_3\">0</tr_idtdVal>"
       << "<tr_idtdVal species=\"Species_4\">0</tr_idtdVal>"
       << "</tr_interceptDiam10ToDBH>"
       << "<tr_stdAsympCrownHt>"
       << "<tr_sachVal species=\"Species_1\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_2\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_3\">0.389</tr_sachVal>"
       << "<tr_sachVal species=\"Species_4\">0.389</tr_sachVal>"
       << "</tr_stdAsympCrownHt>"
       << "<tr_stdCrownHtExp>"
       << "<tr_scheVal species=\"Species_1\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_2\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_3\">1.0</tr_scheVal>"
       << "<tr_scheVal species=\"Species_4\">1.0</tr_scheVal>"
       << "</tr_stdCrownHtExp>"
       << "<tr_slopeOfHeight-Diam10>"
       << "<tr_sohdVal species=\"Species_1\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_2\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_3\">0.03418</tr_sohdVal>"
       << "<tr_sohdVal species=\"Species_4\">0.03418</tr_sohdVal>"
       << "</tr_slopeOfHeight-Diam10>"
       << "<tr_whatSeedlingHeightDiam>"
       << "<tr_wsehdVal species=\"Species_1\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_2\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_3\">0</tr_wsehdVal>"
       << "<tr_wsehdVal species=\"Species_4\">0</tr_wsehdVal>"
       << "</tr_whatSeedlingHeightDiam>"
       << "<tr_whatSaplingHeightDiam>"
       << "<tr_wsahdVal species=\"Species_1\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_2\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_3\">0</tr_wsahdVal>"
       << "<tr_wsahdVal species=\"Species_4\">0</tr_wsahdVal>"
       << "</tr_whatSaplingHeightDiam>"
       << "<tr_whatAdultHeightDiam>"
       << "<tr_wahdVal species=\"Species_1\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_2\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_3\">0</tr_wahdVal>"
       << "<tr_wahdVal species=\"Species_4\">0</tr_wahdVal>"
       << "</tr_whatAdultHeightDiam>"
       << "<tr_whatAdultCrownRadDiam>"
       << "<tr_wacrdVal species=\"Species_1\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_2\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_3\">0</tr_wacrdVal>"
       << "<tr_wacrdVal species=\"Species_4\">0</tr_wacrdVal>"
       << "</tr_whatAdultCrownRadDiam>"
       << "<tr_whatAdultCrownHeightHeight>"
       << "<tr_wachhVal species=\"Species_1\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_2\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_3\">0</tr_wachhVal>"
       << "<tr_wachhVal species=\"Species_4\">0</tr_wachhVal>"
       << "</tr_whatAdultCrownHeightHeight>"
       << "<tr_whatSaplingCrownRadDiam>"
       << "<tr_wscrdVal species=\"Species_1\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_2\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_3\">0</tr_wscrdVal>"
       << "<tr_wscrdVal species=\"Species_4\">0</tr_wscrdVal>"
       << "</tr_whatSaplingCrownRadDiam>"
       << "<tr_whatSaplingCrownHeightHeight>"
       << "<tr_wschhVal species=\"Species_1\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_2\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_3\">0</tr_wschhVal>"
       << "<tr_wschhVal species=\"Species_4\">0</tr_wschhVal>"
       << "</tr_whatSaplingCrownHeightHeight>"
       << "</allometry>";

  oOut << "<behaviorList>"
       << "<behavior>"
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDirectKiller</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_4\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_4\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_3\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_3\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_3\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_4\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>";

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
       << "<st_susceptibility>0</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDirectKiller2>"
       << "<st_stormDirectKillerA>"
       << "<st_sdkaVal species=\"Species_1\">-3.4</st_sdkaVal>"
       << "<st_sdkaVal species=\"Species_2\">2</st_sdkaVal>"
       << "<st_sdkaVal species=\"Species_4\">10</st_sdkaVal>"
       << "</st_stormDirectKillerA>"
       << "<st_stormDirectKillerB>"
       << "<st_sdkbVal species=\"Species_1\">4.8</st_sdkbVal>"
       << "<st_sdkbVal species=\"Species_2\">-3.97628</st_sdkbVal>"
       << "<st_sdkbVal species=\"Species_4\">1</st_sdkbVal>"
       << "</st_stormDirectKillerB>"
       << "<st_stmScheduledStorms>"
       << "<st_stmEvent min=\"0.2\" max=\"0.2\" yr=\"2\"/>"
       << "<st_stmEvent min=\"0.5\" max=\"0.5\" yr=\"4\"/>"
       << "<st_stmEvent min=\"0.6\" max=\"0.6\" yr=\"4\"/>"
       << "</st_stmScheduledStorms>"
       << "</StormDirectKiller2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;

}

/////////////////////////////////////////////////////////////////////////////
// WriteStormDirectKillerXMLErrorFile1()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormDirectKillerXMLErrorFile1() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>50</plot_lenX>"
       << "<plot_lenY>50</plot_lenY>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "<behaviorName>StormDirectKiller</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality2>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality2>";

  oOut << "<StormDirectKiller1>"
       << "<st_stormDirectKillerA>"
       << "<st_sdkaVal species=\"Species_1\">-3.4</st_sdkaVal>"
       << "<st_sdkaVal species=\"Species_2\">2</st_sdkaVal>"
       << "<st_sdkaVal species=\"Species_2\">10</st_sdkaVal>"
       << "</st_stormDirectKillerA>"
       << "<st_stormDirectKillerB>"
       << "<st_sdkbVal species=\"Species_1\">4.8</st_sdkbVal>"
       << "<st_sdkbVal species=\"Species_2\">-3.97628</st_sdkbVal>"
       << "<st_sdkbVal species=\"Species_4\">1</st_sdkbVal>"
       << "</st_stormDirectKillerB>"
       << "</StormDirectKiller1>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

/////////////////////////////////////////////////////////////////////////////
// WriteStormDirectKillerXMLErrorFile2()
/////////////////////////////////////////////////////////////////////////////
const char* WriteStormDirectKillerXMLErrorFile2() {
  using namespace std;
  const char *cFileString = "TestFile1.xml";

  //Open file to write to
  std::fstream oOut;
  oOut.open( cFileString, ios::out | ios::trunc );

  oOut << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>"
       << "<paramFile fileCode=\"06010101\">"
       << "<plot>"
       << "<timesteps>5</timesteps>"
       << "<yearsPerTimestep>1</yearsPerTimestep>"
       << "<randomSeed>1</randomSeed>"
       << "<plot_lenX>50</plot_lenX>"
       << "<plot_lenY>50</plot_lenY>"
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
       << "<tr_slopeOfAsymHeight>"
       << "<tr_soahVal species=\"Species_1\">0.0299</tr_soahVal>"
       << "<tr_soahVal species=\"Species_2\">0.0299</tr_soahVal>"
       << "</tr_slopeOfAsymHeight>"
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
       << "<behaviorName>Storm</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>1</listPosition>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StormDirectKiller</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>2</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>StochasticMortality</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>3</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "</behavior>"
       << "<behavior>"
       << "<behaviorName>RemoveDead</behaviorName>"
       << "<version>1</version>"
       << "<listPosition>4</listPosition>"
       << "<applyTo species=\"Species_1\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_1\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_1\" type=\"Seedling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Adult\"/>"
       << "<applyTo species=\"Species_2\" type=\"Sapling\"/>"
       << "<applyTo species=\"Species_2\" type=\"Seedling\"/>"
       << "</behavior>"
       << "</behaviorList>"
       << "<StochasticMortality3>"
       << "<mo_stochasticMortRate>"
       << "<mo_smrVal species=\"Species_1\">0.0</mo_smrVal>"
       << "<mo_smrVal species=\"Species_2\">0.0</mo_smrVal>"
       << "</mo_stochasticMortRate>"
       << "</StochasticMortality3>";

  oOut << "<Storm1>"
       << "<st_s1ReturnInterval>0</st_s1ReturnInterval>"
       << "<st_s2ReturnInterval>0</st_s2ReturnInterval>"
       << "<st_s3ReturnInterval>0</st_s3ReturnInterval>"
       << "<st_s4ReturnInterval>0</st_s4ReturnInterval>"
       << "<st_s5ReturnInterval>0</st_s5ReturnInterval>"
       << "<st_s6ReturnInterval>0</st_s6ReturnInterval>"
       << "<st_s7ReturnInterval>0</st_s7ReturnInterval>"
       << "<st_s8ReturnInterval>0</st_s8ReturnInterval>"
       << "<st_s9ReturnInterval>0</st_s9ReturnInterval>"
       << "<st_s10ReturnInterval>0</st_s10ReturnInterval>"
       << "<st_susceptibility>1</st_susceptibility>"
       << "<st_stochasticity>0</st_stochasticity>"
       << "<st_stmSSTPeriod>1</st_stmSSTPeriod>"
       << "<st_stmSineD>0</st_stmSineD>"
       << "<st_stmSineF>1</st_stmSineF>"
       << "<st_stmSineG>1</st_stmSineG>"
       << "<st_stmTrendSlopeM>0</st_stmTrendSlopeM>"
       << "<st_stmTrendInterceptI>1</st_stmTrendInterceptI>"
       << "</Storm1>"
       << "<StormDirectKiller2>"
       << "<st_stormDirectKillerA>"
       << "<st_sdkaVal species=\"Species_1\">-3.4</st_sdkaVal>"
       << "<st_sdkaVal species=\"Species_2\">2</st_sdkaVal>"
       << "<st_sdkaVal species=\"Species_2\">10</st_sdkaVal>"
       << "</st_stormDirectKillerA>"
       << "<st_stormDirectKillerB>"
       << "<st_sdkbVal species=\"Species_1\">4.8</st_sdkbVal>"
       << "<st_sdkbVal species=\"Species_2\">-3.97628</st_sdkbVal>"
       << "<st_sdkbVal species=\"Species_4\">1</st_sdkbVal>"
       << "</st_stormDirectKillerB>"
       << "</StormDirectKiller2>"
       << "</paramFile>";

  oOut.close();

  return cFileString;
}

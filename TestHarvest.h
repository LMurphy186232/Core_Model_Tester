//---------------------------------------------------------------------------
// TestHarvest
//---------------------------------------------------------------------------
#if !defined(TestHarvest_H)
#define TestHarvest_H

class clTreePopulation;
class clSimManager;

#include <fstream>

/**
 * For testing trees.
 */
struct treestruct{
  float fX, /**<X coordinate*/
  fY; /**<Y coordinate*/
int iSpecies; /**<Tree species*/
bool bDead, /**<whether the tree should be dead*/
bFound;  /**<whether it was found in the tree population*/
};


//Harvest run seven deliberately skipped...

/**
 * Writes a parameter file to test disturbance for run 1.  This has a tree
 * map so an expected tree set is created.
 * @param bTallestFirst What to set the "tallest first" cut flag to.
 * @return Filename written.
 */
const char* WriteHarvestXMLFile1(bool bTallestFirst);

/**
 * Writes a parameter file to test disturbance for run 2.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteHarvestXMLFile2();

/**
 * Writes a parameter file to test disturbance for run 3.  This has a tree
 * map so an expected tree set is created.
 * @param bTallestFirst What to set the "tallest first" cut flag to.
 * @return Filename written.
 */
const char* WriteHarvestXMLFile3(bool bTallestFirst);

/**
 * Writes a parameter file to test disturbance for run 4.  This has a tree
 * map so an expected tree set is created.
 * @param bTallestFirst What to set the "tallest first" cut flag to.
 * @return Filename written.
 */
const char* WriteHarvestXMLFile4(bool bTallestFirst);

/**
 * Writes a parameter file to test disturbance for run 5.  This has a tree
 * map so an expected tree set is created.
 * @param bTallestFirst What to set the "tallest first" cut flag to.
 * @return Filename written.
 */
const char* WriteHarvestXMLFile5(bool bTallestFirst);

/**
 * Writes a parameter file to test disturbance for run 6.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteHarvestXMLFile6(bool bTallestFirst);

/**
 * Writes a parameter file to test disturbance for run 8. This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteHarvestXMLFile8();

/**
 * Writes a parameter file to test disturbance for run 9. This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteHarvestXMLFile9(bool bTallestFirst);

/**
 * Writes the tree map for harvest parameter files.
 * @param oOut File stream to write to.
 */
void WriteHarvestTreeMap(std::fstream &oOut);

/**
 * Writes the tree map for run 9 harvest parameter file .
 * @return Filename written.
 */
const char* WriteHarvestRun9TreeMap();

/**
 * Writes the tree map for harvest parameter files.
 * @param oOut File stream to write to.
 * @param iRandomSeed Random seed.
 */
void WriteHarvestFileBeginning(std::fstream &oOut, int iRandomSeed);

/**
 * Checks the results of the tree population against the expected results.
 */
void CheckHarvestResults(clTreePopulation *p_oPop, int iNumTrees, treestruct *p_FakeTrees);
//---------------------------------------------------------------------------
#endif // TestHarvest_H

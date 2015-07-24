//---------------------------------------------------------------------------
// TestSelectionHarvest
//---------------------------------------------------------------------------
#if !defined(TestSelectionHarvest_H)
#define TestSelectionHarvest_H

class clTreePopulation;

/**Tree structure for testing*/
struct tree{float fX, /**<X coordinate*/
  fY; /**<Y coordinate*/
int iSpecies; /**<Tree species*/
bool bDead, /**<Whether the tree should be dead*/
bFound;  /**<Whether it was found in the tree population*/
};

/**
 * Writes a parameter file to test disturbance for run 1.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile1();

/**
 * Writes a parameter file to test disturbance for run 2.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile2();

/**
 * Writes a parameter file to test disturbance for run 3.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile3();

/**
 * Writes a parameter file to test disturbance for run 4.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile4();

/**
 * Writes a parameter file to test disturbance for run 5.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile5();

/**
 * Writes a parameter file to test disturbance for run 6.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile6();

/**
 * Writes a parameter file to test disturbance for run 7.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile7();

/**
 * Writes a parameter file to test disturbance for run 8.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile8();

/**
 * Writes a parameter file to test disturbance for run 9.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile9();

/**
 * Writes a parameter file to test disturbance for run 10.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile10();

/**
 * Writes a parameter file to test disturbance for run 11.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile11();

/**
 * Writes a parameter file to test disturbance for run 12.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile12();

/**
 * Writes a parameter file to test disturbance for run 12.  This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteSelectionHarvestXMLFile13();

/**
 * Writes the tree map for harvest parameter files.
 * @param cFileName File to write to.
 */
void WriteSelectionHarvestTreeMap(const char *cFileName);

/**
 * Checks the results of the tree population against the expected results.
 * @param p_oPop Tree population object
 * @param iNumTrees Number of trees in p_FakeTrees
 * @param p_FakeTrees List of trees.
 */
void CheckResults(clTreePopulation *p_oPop, int iNumTrees, tree *p_FakeTrees);
//---------------------------------------------------------------------------
#endif // TestSelectionHarvest_H

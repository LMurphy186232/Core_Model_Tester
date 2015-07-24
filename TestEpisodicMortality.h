//---------------------------------------------------------------------------
// TestEpisodicMortality
//---------------------------------------------------------------------------
#if !defined(TestEpisodicMortality_H)
#define TestEpisodicMortality_H

class clTreePopulation;

/**
 * For testing trees.
 */
//struct tree;
struct treestruct{float fX, /**<X coordinate*/
  fY; /**<Y coordinate*/
int iSpecies; /**<Tree species*/
bool bDead, /**<whether the tree should be dead*/
bFound;  /**<whether it was found in the tree population*/
};

/**
 * Writes a parameter file to test episodic mortality for run 1. This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteEpisodicMortalityXMLFile1();

/**
 * Writes a parameter file to test episodic mortality for run 2. This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteEpisodicMortalityXMLFile2();

/**
 * Writes a parameter file to test episodic mortality for run 3. This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteEpisodicMortalityXMLFile3();

/**
 * Writes a parameter file to test episodic mortality for run 4. This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteEpisodicMortalityXMLFile4();

/**
 * Writes a parameter file to test episodic mortality for run 5. This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteEpisodicMortalityXMLFile5();

/**
 * Writes a parameter file to test episodic mortality for run 6. This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteEpisodicMortalityXMLFile6();

/**
 * Writes a parameter file to test episodic mortality for run 8. This has a tree
 * map so an expected tree set is created.
 * @return Filename written.
 */
const char* WriteEpisodicMortalityXMLFile8();

/**
 * Writes the tree map for mortality episode parameter files.
 * @return Filename written.
 */
void WriteEpisodicMortalityTreeMap(const char *cFileName);

/**
 * Checks the results of the tree population against the expected results.
 * The dead trees should be snags.
 * @param p_oPop Tree population
 * @param iNumTrees Number of trees in p_FakeTrees
 * @param p_FakeTrees Tree list.
 */
void CheckEpisodicMortalityResults(clTreePopulation *p_oPop, int iNumTrees, treestruct *p_FakeTrees);
//---------------------------------------------------------------------------
#endif // TestEpisodicMortality_H

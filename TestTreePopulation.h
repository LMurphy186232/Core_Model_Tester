//---------------------------------------------------------------------------
// TestTreePopulation
//---------------------------------------------------------------------------
#if !defined(TestTreePopulation_H)
#define TestTreePopulation_H

#include <stddef.h>

class clTreePopulation;
class clTree;
class clTreeSearch;

/**
 * Tests the clTreePopulation class. The test script guiding the test is
 * Population Test.xls.
 */

/**
 * This is for making a fake linked list. One of these takes the place of a
 * real tree and overlays the previous and next links.
 */
class clFakeLinkedList {
public:
  clTree *prev, /**<Link to the previous tree in the fake hash table*/
  *thisTree, /**<Current tree record*/
  *next; /**<Link to the nextree in the fake hash table*/
  clFakeLinkedList *prevLink, /**<Link to the previous record in the fake hash table*/
  *nextLink; /**<Link to the next record in the fake hash table*/
  /**
   * Constructor
   * @param p_tree Tree to make this record out of
   */
  clFakeLinkedList(clTree *p_tree) {prev = NULL; thisTree = p_tree;
  next = NULL; prevLink = NULL; nextLink = NULL;};
};

/**This structure is for testing tree results - arrays of this struct can
  tell, for a given list of trees, which should be found, and which actually
  were*/
struct treeResults {
  clTree* p_oTree;      /**<Pointer to the tree being tested*/
  short int iFoundFlag; /**<This can be incremented each time the tree is found,
                          which can guard against duplicate finds*/
  bool bShouldBe;       /**<Whether or not this tree should be found*/
};

/**
 * Checks the real hash table against the predicted results.
 * @param p_oPop Pointer to tree population.
 * @param p_oShortestHD Shortest links
 * @param p_oTallestHD Tallest links
 * @param p_oShort Fake shortest hash table.
 * @param p_oTall Fake tallest hash table.
 * @param iNumXCells Number population X cells.
 * @param iNumYCells Number population Y cells.
 */
void CheckHashTable(clTreePopulation *p_oPop, clTree ****p_oShortestHD,
    clTree ****p_oTallestHD, clFakeLinkedList ***p_oShort,
    clFakeLinkedList ***p_oTall, int iNumXCells, int iNumYCells);

/**
 * Loads the first set of trees for hash table checking.
 * @param p_oPop Pointer to tree population.
 * @param p_oShortestHD Shortest links
 * @param p_oTallestHD Tallest links
 * @param p_oShort Fake shortest hash table.
 * @param p_oTall Fake tallest hash table.
 * @param iNumXCells Number population X cells.
 * @param iNumYCells Number population Y cells.
 * @param p_oTreeSet The set of trees to create
 * @param bFullCheck If true, the function checks the hash table after each
 * tree is created to make sure it is correct.
 * @param bUpdateHashTable If true, this creates the fake hash table and
 * keeps it updated.
 */
void LoadTrees1(clTreePopulation *p_oPop, clTree ****p_oShortestHD,
    clTree ****p_oTallestHD, clFakeLinkedList ***p_oShort,
    clFakeLinkedList ***p_oTall, clTree **p_oTreeSet, int iNumXCells, int iNumYCells, bool bFullCheck,
    bool bUpdateHashTable);

/**
 * Loads the first set of trees for hash table checking.
 * @param p_oPop Pointer to tree population.
 * @param p_oTreeSet The set of trees to create
 * @param bFullCheck If true, the function checks the hash table after each
 * tree is created to make sure it is correct.
 */

void LoadTrees2(clTreePopulation *p_oPop, clTree **p_oTreeSet, bool bFullCheck);


/**
 * Cleans up memory for CheckHashTable.
 * @param p_oShortestHD Shortest links
 * @param p_oTallestHD Tallest links
 * @param p_oShort Fake shortest hash table.
 * @param p_oTall Fake tallest hash table.
 * @param iNumXCells Number population X cells.
 * @param iNumYCells Number population Y cells.
 */
void EmptyFakeHashTable(clTree ****p_oShortestHD, clTree ****p_oTallestHD,
    clFakeLinkedList ***p_oShort, clFakeLinkedList ***p_oTall, int iNumXCells,
    int iNumYCells);

/**
 * Performs the first set of tree search tests.
 */
void DoSet1Searches(clTreePopulation *p_oPop, clTree **p_oTreeSet);
/**
 * Performs the second set of tree search tests.
 */
void DoSet2Searches(clTreePopulation *p_oPop, clTree **p_oTreeSet);
/**
 * Performs the third set of tree search tests.
 */
void DoSet3Searches(clTreePopulation *p_oPop);

/**
 * Checks the tree results against a list of expected results. This will check
 * for trees not found that should be found, trees that are found which should
 * not be found, and trees found multiple times. This will also make sure that
 * tree searches can handle continued calls to NextTree() after NULL-ing without
 * choking. Results are directed to the log file.
 * @param p_expected Array of treeResults which shows expected values. There can
 * be trees in this list that are not expected to be found.
 * @param iNumResults Number of elements in p_expected array.
 * @param p_oActual Tree search object to test.
 * @param p_oFirstTree The expected first tree found.
 */
void CheckTreeSearch(struct treeResults *p_expected,
    short int iNumResults, clTreeSearch *p_oActual, clTree *p_oFirstTree);

/**
 * Performs updates of the tree set to make sure the hash table is updated
 * correctly.
 * @param p_oPop Pointer to tree population object
 * @param p_oShortestHD Shortest links
 * @param p_oTallestHD Tallest links
 * @param p_oShort Fake shortest hash table.
 * @param p_oTall Fake tallest hash table.
 * @param iNumXCells Number population X cells.
 * @param iNumYCells Number population Y cells.
 * @param p_oTreeSet The set of trees to create
 * @param bFullCheck Whether to check the hash table after each update
 * @param bUpdateNow Matches the trees' bUpdateNow argument
 * @param bUpdateAllometry Matches the trees' bUpdateAllometry argument
 */
void UpdateHashTableTrees(clTreePopulation * p_oPop, clTree * * * * p_oShortestHD, clTree * * * * p_oTallestHD,
    clFakeLinkedList * * * p_oShort, clFakeLinkedList * * * p_oTall, clTree * * p_oTreeSet, int iNumXCells, int iNumYCells, bool bFullCheck,
    bool bUpdateNow, bool bUpdateAllometry);

/**
 * Deletes the set of trees in a certain order to make sure the hash table is
 * updated correctly.
 * @param p_oPop Pointer to tree population object
 * @param p_oShortestHD Shortest links
 * @param p_oTallestHD Tallest links
 * @param p_oShort Fake shortest hash table.
 * @param p_oTall Fake tallest hash table.
 * @param iNumXCells Number population X cells.
 * @param iNumYCells Number population Y cells.
 * @param p_oTreeSet The set of trees
 */
void DeleteHashTableTrees(clTreePopulation * p_oPop, clTree * * * * p_oShortestHD,
    clTree * * * * p_oTallestHD, clFakeLinkedList * * * p_oShort, clFakeLinkedList * * * p_oTall, clTree * * p_oTreeSet,
    int iNumXCells, int iNumYCells);

/**
 * Writes a parameter file for testing. This is primarily for hash table
 * sorting. Characteristics:
 * <ul>
 * <li>Three species, with various values for getting/setting.
 * <li>Known plot lengths for pop. cell testing.
 * <li>The only behavior does not use snags or stumps.
 * </ul>
 * @return Filename written.
 */
const char* WriteTreePopulationXMLFile1();

/**
 * Writes a parameter file for testing. This is primarily for hash table
 * sorting. Characteristics:
 * <ul>
 * <li>Known plot lengths for pop. cell testing.
 * <li>The only behavior does not use snags or stumps.
 * </ul>
 * @return Filename written.
 */
const char* WriteTreePopulationXMLFile2();

/**
 * Writes a parameter file for testing. Characteristics:
 * <ul>
 * <li>Two species.
 * <li>There is no behavior which uses snags.
 * <li>There is a behavior which uses stumps, but only for Species 1.
 * <li>There is a tree map with seedlings, saplings, adults, and snags.
 * </ul>
 * @return Filename written.
 */
const char* WriteTreePopulationXMLFile3();

/**
 * Writes a parameter file for testing. Characteristics:
 * <ul>
 * <li>Two species.
 * <li>There is a behavior which uses snags.
 * <li>There is a behavior which uses stumps, but only for Species 1.
 * <li>There is a tree map with seedlings, saplings, adults, and snags.
 * </ul>
 * @return Filename written.
 */
const char* WriteTreePopulationXMLFile4();

/**
 * Writes a parameter file for testing. Characteristics:
 * <ul>
 * <li>3 years per timestep.
 * <li>Two species.
 * <li>There is a behavior which uses snags.
 * <li>There is a behavior which uses stumps, but only for Species 1.
 * <li>There is a tree map with seedlings, saplings, adults, and snags.
 * </ul>
 * @return Filename written.
 */
const char* WriteTreePopulationXMLFile5();

/**
 * Writes a parameter file for testing distance-height tree searches on
 * a plot which has odd-sized end grids (100X100 m plot).
 * @return Filename written.
 */
const char* WriteTreePopulationXMLFile6();
//---------------------------------------------------------------------------
#endif // TestTreePopulation_H

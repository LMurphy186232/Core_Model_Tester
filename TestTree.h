//---------------------------------------------------------------------------
// TestTree
//---------------------------------------------------------------------------
#if !defined(TestTree_H)
  #define TestTree_H

/**
 * Tests the clTree class.
 */

/**
 * Writes a parameter file to test trees.  Two species are used; the only
 * difference between the two is the maximum seedling height.
 * @return Filename written.
 */
const char* WriteTreeXMLFile1();

/**
 * Writes a parameter file to test trees. This provides lots of tree data
 * members.
 * @return Filename written.
 */
const char* WriteTreeXMLFile2();
//---------------------------------------------------------------------------
#endif // TestTree_H

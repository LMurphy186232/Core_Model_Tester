//---------------------------------------------------------------------------
// TestGermination
//---------------------------------------------------------------------------
#if !defined(TestGermination_H)
#define TestGermination_H

class clGrid;


/** Verifies the seedling counts for TestGermination.
 * @param p_oSeedGrid Dispersed seeds grid.
 */
void VerifyXMLFile1(clGrid * p_oSeedGrid);

/**
 * Writes a parameter file to direct testing using the first set of testing
 * conditions.  This contains all tree information and disperse information.
 * It also has a tree map so we'll be dealing with a known list of trees.
 * @return Filename written.
 */
const char* WriteGerminationXMLFile1();

/**
 * Writes a parameter file with a germination parameter less than 0.
 * @return Filename written.
 */
const char* WriteGerminationXMLErrorFile1();

/**
 * Writes a parameter file with a germination parameter greater than 1.
 * @return Filename written.
 */
const char* WriteGerminationXMLErrorFile2();
//---------------------------------------------------------------------------

#endif // TestGermination_H

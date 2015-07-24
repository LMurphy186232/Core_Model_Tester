//---------------------------------------------------------------------------
// TestMortality
//---------------------------------------------------------------------------
#if !defined(TestCompetitionMortality_H)
#define TestCompetitionMortality_H


/**
 * Writes a parameter file to direct testing using the first set of testing
 * conditions.  This contains all tree information and disperse information.
 * It also has a tree map so we'll be dealing with a known list of trees.
 * @return Filename written.
 */
const char* WriteCompetitionMortalityXMLFile1();

/**
 * Writes a bad parameter file: Passes a timestep >1 to this behavior.
 * @return Filename written.
 */
const char* WriteCompetitionMortalityXMLFile2();
//---------------------------------------------------------------------------

#endif // TestMortality_H

//---------------------------------------------------------------------------
// TestNCICompetitionTempDep
//---------------------------------------------------------------------------
#if !defined(TestNCICompetitionTempDep_H)
#define TestNCICompetitionTempDep_H
#include <fstream>

const char* WriteNCICompTempDepXMLFile1();

const char* WriteNCICompTempDepXMLFile2();

const char* WriteNCICompTempDepXMLFile3();

const char* WriteNCICompTempDepXMLFile4();


/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCICompTempDepCommonStuff(std::fstream &oOut);

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * @param oOut File stream to write to.
 */
void WriteNCICompTempDepTreeStuff(std::fstream &oOut);

//---------------------------------------------------------------------------
#endif

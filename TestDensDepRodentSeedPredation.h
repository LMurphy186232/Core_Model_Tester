//---------------------------------------------------------------------------
// TestDensDepRodentSeedPredation
//---------------------------------------------------------------------------
#if !defined(TestDensDepRodentSeedPredation_H)
#define TestDensDepRodentSeedPredation_H

class clSimManager;
#include <fstream>

/**
 * Writes the parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteDensDepRodentSeedPredationXMLFile1();

/**
 * Writes the parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteDensDepRodentSeedPredationXMLFile2();

/**
 * Writes the parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteDensDepRodentSeedPredationXMLFile3();

/**
 * Writes the parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteDensDepRodentSeedPredationErrorFile1();

/** Writes common portions of the parameter file - trees and allometry.
 * @param oOut Filestream to write to.
 */
void WriteDensDepRodentSeedPredationTreesAllometry(std::fstream &oOut);


//---------------------------------------------------------------------------
#endif // TestDensDepRodentSeedPredation_H

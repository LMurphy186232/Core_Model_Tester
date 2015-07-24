//---------------------------------------------------------------------------
// TestNeighborhoodSeedPredation
//---------------------------------------------------------------------------
#if !defined(TestNeighborhoodSeedPredation_H)
#define TestNeighborhoodSeedPredation_H

class clSimManager;
#include <fstream>

/**
 * Does the testing for runs one and five
 * @param p_oSimManager Sim manager object.
 */
void TestRun1And5(clSimManager *p_oSimManager);

/**
 * Does the testing for runs two and six
 * @param p_oSimManager Sim manager object.
 */
void TestRun2And6(clSimManager *p_oSimManager);

/**
 * Writes the parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLFile1();

/**
 * Writes the parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLFile2();

/**
 * Writes the parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLFile3();

/**
 * Writes the parameter file for normal processing run 4.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLFile4();

/**
 * Writes the parameter file for normal processing run 5.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLFile5();

/**
 * Writes the parameter file for normal processing run 6.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLFile6();

/**
 * Writes the parameter file for normal processing run 7.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLFile7();

/**
 * Writes a file where minimum neighbor DBH is negative.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLErrorFile1();

/**
 * Writes a file where masting threshod is negative.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLErrorFile2();

/**
 * Writes a file where neighborhood radius is negative.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLErrorFile3();

/**
 * Writes a file where there are no disperse behaviors.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLErrorFile4();

/**
 * Writes a file where the neighborhood seed predation behavior is the linked
 * version but there is no functional response seed predation.
 * @return Filename written.
 */
const char* WriteNeighborhoodSeedPredationXMLErrorFile5();

/** Writes common portions of the parameter file - trees and allometry.
 * @param oOut Filestream to write to.
 */
void WriteNeighborhoodSeedPredationTreesAllometry(std::fstream &oOut);

/**
 * Writes common seed predation parameters
 * @param oOut File stream to write to.
 */
void WriteNeighborhoodSeedPredationCommonPredationParameters (std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestNeighborhoodSeedPredation_H

//---------------------------------------------------------------------------
// TestEpiphyticEstablishment
//---------------------------------------------------------------------------
#if !defined(TestEpiphyticEstablishment_H)
#define TestEpiphyticEstablishment_H

#include <fstream>

/**
 * Writes a parameter file to direct testing for normal processing run one.
 * @return Filename written.
 */
const char* WriteEpiphyticEstablishmentXMLFile1();

/**
 * Writes a parameter file to direct testing for normal processing run two.
 * @return Filename written.
 */
const char* WriteEpiphyticEstablishmentXMLFile2();

/**
 * Writes a file where the number of altitude angles is less than 1.
 * @return Filename written.
 */
const char* WriteEpiphyticEstablishmentXMLErrorFile1();

/**
 * Writes a file where the number of azimuth angles is less than 1.
 * @return Filename written.
 */
const char* WriteEpiphyticEstablishmentXMLErrorFile2();

/**
 * Writes a file where the behavior is applied to seedlings.
 * @return Filename written.
 */
const char* WriteEpiphyticEstablishmentXMLErrorFile3();

/**
 * Writes a file where some of the trees don't have mortality applied.
 * @return Filename written.
 */
const char* WriteEpiphyticEstablishmentXMLErrorFile4();

/**
 * Writes common portions of the test parameter files.
 * @param oOut File stream to write to.
 */
void WriteEpiphyticEstablishmentErrorCommonStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestEpiphyticEstablishment_H

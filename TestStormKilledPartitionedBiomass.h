//---------------------------------------------------------------------------
// TestStormKilledPartitionedBiomass
//---------------------------------------------------------------------------
#if !defined(TestStormKilledPartitionedBiomass_H)
#define TestStormKilledPartitionedBiomass_H
#include <fstream>

class clTreePopulation;

/**
 * Tests the class clStormKilledPartitionedBiomass.
 */
/**
 * Writes the parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteStormKilledPartitionedBiomassXMLFile1();

/**
 * Writes the parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteStormKilledPartitionedBiomassXMLFile2();

/**
 * Writes the parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteStormKilledPartitionedBiomassXMLFile3();

/**
 * Writes the parameter file for normal processing run 4.
 * @return Filename written.
 */
const char* WriteStormKilledPartitionedBiomassXMLFile4();

/**
 * Writes an error file where the Partitioned Biomass behavior, DBH version,
 * is applied to seedlings.
 * @return Filename written.
 */
const char* WriteStormKilledPartitionedBiomassXMLErrorFile1();

/**
 * Writes an error file where the Partitioned Biomass behavior, height version,
 * is applied to seedlings.
 * @return Filename written.
 */
const char* WriteStormKilledPartitionedBiomassXMLErrorFile2();

/**
 * Creates the test tree set.
 * @param p_oPop Tree population object.
 */
void CreateStormKilledPartitionedBiomassTrees(clTreePopulation *p_oPop);

/**
 * Writes common beginning of the test parameter files, which is everything
 * after the grid settings.
 * @param oOut File stream to write to.
 */
void WriteStormKilledPartitionedBiomassCommonFileBegin(std::fstream &oOut);

/**
 * Writes common ending of the test parameter files, which is everything
 * after the grid settings.
 * @param oOut File stream to write to.
 */
void WriteStormKilledPartitionedBiomassCommonFileEnd(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestStormKilledPartitionedBiomass_H

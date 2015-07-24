//---------------------------------------------------------------------------
// TestPartitionedBiomass
//---------------------------------------------------------------------------
#if !defined(TestPartitionedBiomass_H)
#define TestPartitionedBiomass_H
#include <fstream>
class clTreePopulation;

/**
 * Writes the parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WritePartitionedBiomassXMLFile1();

/**
 * Writes the parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WritePartitionedBiomassXMLFile2();

/**
 * Writes the parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WritePartitionedBiomassXMLFile3();

/**
 * Writes the parameter file for normal processing run 4.
 * @return Filename written.
 */
const char* WritePartitionedBiomassXMLFile4();

/**
 * Writes an error file where the Partitioned Biomass behavior, DBH version,
 * is applied to seedlings.
 * @return Filename written.
 */
const char* WritePartitionedBiomassXMLErrorFile1();

/**
 * Writes an error file where the Partitioned Biomass behavior, height version,
 * is applied to seedlings.
 * @return Filename written.
 */
const char* WritePartitionedBiomassXMLErrorFile2();

/**
 * Creates the test tree set.
 * @param p_oPop Tree population object.
 */
void CreatePartitionedBiomassTrees(clTreePopulation *p_oPop);

/**
 * Writes common beginning of the test parameter files, which is everything
 * after the grid settings.
 * @param oOut File stream to write to.
 */
void WritePartitionedBiomassCommonFileBegin(std::fstream &oOut);

/**
 * Writes common ending of the test parameter files, which is everything
 * after the grid settings.
 * @param oOut File stream to write to.
 */
void WritePartitionedBiomassCommonFileEnd(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestPartitionedBiomass_H

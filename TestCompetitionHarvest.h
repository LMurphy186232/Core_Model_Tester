//---------------------------------------------------------------------------
// TestCompetitionHarvest
//---------------------------------------------------------------------------
#if !defined(TestCompetitionHarvest_H)
#define TestCompetitionHarvest_H

#include <fstream>

/**
 * Writes a parameter file for run 1.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLFile1();

/**
 * Writes a parameter file for run 1, without the file written.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLFile1a();

/**
 * Writes a parameter file for run 2.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLFile2(int mostcomp);

/**
 * Writes a parameter file for run 3.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLFile3();

/**
 * Writes a parameter file for run 4.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLFile4(int mostcomp);

/**
 * Writes a parameter file where the competition harvest behavior is applied
 * to seedlings.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLErrorFile1();

/**
 * Writes a parameter file where the harvest type is fixed interval and the
 * harvest interval is less than 1.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLErrorFile2();

/**
 * Writes a parameter file where the harvest type is fixed BA with proportion
 * to cut but cut amount is not a proportion between 0 and 1.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLErrorFile3();

/**
 * Writes a parameter file where the species proportions to cut do not add up
 * to 1.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLErrorFile4();

/**
 * Writes a parameter file where the harvest type is fixed BA but the minimum
 * interval is less than 1.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLErrorFile5();

/**
 * Writes a parameter file where a value in max crowding radius is not
 * greater than 0.
 * @return Filename written.
 */
const char* WriteCompetitionHarvestXMLErrorFile6();

/**
 * Writes common portions of the test parameter files (tree pop, plot, etc).
 * Ends with &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteCompetitionHarvestCommonErrorStuff(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestCompetitionHarvest_H

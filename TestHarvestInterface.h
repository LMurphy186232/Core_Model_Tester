//---------------------------------------------------------------------------
// TestHarvestInterface
//---------------------------------------------------------------------------
#if !defined(TestHarvestInterface_H)
#define TestHarvestInterface_H

#include <fstream>

/**
 * Writes a parameter file for normal processing run 1.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLFile1();

/**
 * Writes a parameter file for normal processing run 2.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLFile2();

/**
 * Writes a parameter file for normal processing run 3.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLFile3();

/**
 * Writes a parameter file for normal processing run 4.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLFile4();

/**
 * Writes a parameter file for normal processing run 5.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLFile5();

/**
 * Writes a parameter file for normal processing run 6.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLFile6();

/**
 * Writes batch file 1, for normal processing run 5.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLBatch1();

/**
 * Writes a batch file to provoke an error in the length of the batch
 * parameters file.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorBatch1();

/**
 * Writes a parameters file, for normal processing run 5.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceAllParamsFile();

/**
 * Writes an error file where the harvest executable isn't where it's supposed
 * to be.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorFile1();

/**
 * Writes an error file where the harvest period is negative.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorFile2();

/**
 * Writes an error file where requested tree attributes don't exist at all.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorFile3();

/**
 * Writes an error file where requested tree attributes don't exist for all
 * species.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorFile4();

/**
 * Writes an error file where the harvest return file will not exist.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorFile5();

/**
 * Writes an error file where the update return file will not exist.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorFile6();

/**
 * Writes an error file where a tree to harvest will not exist.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorFile7();

/**
 * Writes an error file where a tree to update will not exist.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorFile8();

/**
 * Writes an error file where the parameter batch file is missing.
 * @return Filename written.
 */
const char* WriteHarvestInterfaceXMLErrorFile9();

/**
 * Writes the tree portions of the test parameter files, from &lt;trees&gt; to
 * &lt;/trees&gt;.
 * @param oOut File stream to write to.
 */
void WriteHarvestInterfaceTrees(std::fstream &oOut);

/**
 * Writes the allometry portions of the test parameter files, from
 * &lt;allometry&gt; to &lt;/allometry&gt;.
 * @param oOut File stream to write to.
 */
void WriteHarvestInterfaceAllometry(std::fstream &oOut);
//---------------------------------------------------------------------------
#endif // TestAdvancedHarvestShell_H

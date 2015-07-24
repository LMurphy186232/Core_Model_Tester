//---------------------------------------------------------------------------
// TestPostHarvestSkiddingMort
//---------------------------------------------------------------------------
#if !defined(TestPostHarvestSkiddingMort_H)
  #define TestPostHarvestSkiddingMort_H

/**
* Tests the PostHarvestSkiddingMort class descended from clMortalityBase.
* @author Mark Vanderwel
*/

/**
 * Writes a parameter file with the specifications given for
 * TestPostHarvestSkiddingMort(), runs 1 and 2. If parameter value of 1 is
 * passed, then the Harvest Interface behavior is included in the parameter
 * file.
 * @return Filename written.
 */
const char* WritePostHarvestSkiddingMortXMLFile1(int iRun);
//---------------------------------------------------------------------------
#endif // TestPostHarvestSkiddingMort_H

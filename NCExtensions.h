/*
-------------------------------------------------------------------------
OBJECT NAME:    NCExtensions.h 

FULL NAME:     NetCDF-4 extensions 

DESCRIPTION:   NetCDF-4 common functions between ncpp and aeros. Methods
               to retrieve netCDF attributes of various data types. These 
	       will trap any exceptions that the netCDF API throws. 
	       
               @param var the variable to get the attribute from
               @param target the attribute name to get
               @param output the variable to place the attribute, this is the return data
               @param defaultValue is the value to use if the attribute does not exist
               @returns true/false as to success of reading attribute (i.e. did it exist)

COPYRIGHT:      University Corporation for Atmospheric Research, 1995-2025
-------------------------------------------------------------------------
*/
#ifndef NCExtensions_H
#define NCExtensions_H

#include <netcdf>

#ifdef __cplusplus
extern "C" {
#endif
bool getStringAttribute(netCDF::NcVar& var, const char target[], std::string& output);
bool getIntAttribute(netCDF::NcVar& var, const char target[], int& output, int defaultValue = 0);
bool getFloatAttribute(netCDF::NcVar& var, const char target[], float& output, float defaultValue = 0.0);
bool getVectorOfFloatAttributes(netCDF::NcVar& var, const char target[], std::vector<float>& output);
bool getVectorOfDoubleAttributes(netCDF::NcVar& var, const char target[], std::vector<double>& output);
#ifdef __cplusplus
}
#endif

#endif

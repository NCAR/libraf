/*
-------------------------------------------------------------------------
OBJECT NAME:    NCExtensions.cc

FULL NAME:	NetCDF-4 C++ extensions

DESCRIPTION:	NetCDF-4 common functions between ncpp and aeros. Methods
		to retrieve netCDF attributes of various data types. These
		will trap any exceptions that the netCDF API throws.

		@param var the variable to get the attribute from
		@param target the attribute name to get
		@param output the variable to place the attribute, this is the return data
		@param defaultValue is the value to use if the attribute does not exist
		@returns true/false as to success of reading attribute (i.e. did it exist)

COPYRIGHT:      University Corporation for Atmospheric Research, 2025
-------------------------------------------------------------------------
*/

#include "NCExtensions.h"


/* -------------------------------------------------------------------- */
bool getStringAttribute(netCDF::NcVar& var, const char target[], std::string& output)
{
  netCDF::NcVarAtt attr;

  try
  {
    attr = var.getAtt(target);
    if (!attr.isNull())
    {
       int len = attr.getAttLength();
       char buff[1024];
       attr.getValues(buff);
       buff[len] = '\0';
       output = buff;
    }
  }
  catch(const netCDF::exceptions::NcException& e)
  {
    output.clear();
    //std::cerr << "getStringAttribute returning false. Attribute "
    //<< target << " not found error"<< std::endl;
    return false;
  }
  return true;
}

/* -------------------------------------------------------------------- */
bool getIntAttribute(netCDF::NcVar& var, const char target[], int& output, int defaultValue)
{
  netCDF::NcVarAtt attr;
  try
  {
    attr = var.getAtt(target);
    if(!attr.isNull())
    {
      int vals[32];
      attr.getValues(vals);
      output = vals[0];
    }
  }
  catch(const netCDF::exceptions::NcException& e)
  {
    output = defaultValue;
    //std::cerr << getIntAttribute returning false. Attribute " << target << " not found" << std::endl;
    return false;
  }
  return true;
}

/* -------------------------------------------------------------------- */
bool getFloatAttribute(netCDF::NcVar& var, const char target[], float& output, float defaultValue)
{
  netCDF::NcVarAtt attr;
  try
  {
    attr = var.getAtt(target);
    if (!attr.isNull())
    {
      float vals[32];
      attr.getValues(vals);
      output = vals[0];
    }
  }
  catch(const netCDF::exceptions::NcException& e)
  {
    output = defaultValue;
    //std::cerr << "getFloatAttribute returning false. Attribute " << target << " not found" << std::endl;
    return false;
  }
  return true;
}

/* -------------------------------------------------------------------- */
bool getVectorOfFloatAttributes(netCDF::NcVar& var, const char target[], std::vector<float>& output)
{
  netCDF::NcVarAtt attr;
  try
  {
    output.clear();
    attr = var.getAtt(target);

    if (!attr.isNull())
    {
      output.resize(attr.getAttLength());
      attr.getValues(output.data());
    }
  }
  catch(const netCDF::exceptions::NcException& e)
  {
    // is target null terminated?
    //std::cerr << "Probe::getVecorOfFloatAttribute returning false. Attribute " << target << " not found" << std::endl;
    return false;
  }
  return true;
}

/* -------------------------------------------------------------------- */
bool getVectorOfDoubleAttributes(netCDF::NcVar& var, const char target[], std::vector<double>& output)
{
  netCDF::NcVarAtt attr;
  try
  {
    output.clear();
    attr = var.getAtt(target);

    if (!attr.isNull())
    {
      output.resize(attr.getAttLength());
      attr.getValues(output.data());
    }
  }
  catch(const netCDF::exceptions::NcException& e)
  {
    // is target null terminated?
    //std::cerr << "Probe::getVecorOfDoubleAttributes returning false. Attribute " << target << " not found" << std::endl;
    return false;
  }
  return true;
}
/* -------------------------------------------------------------------- */
bool getVectorOfIntAttributes(netCDF::NcVar& var, const char target[], std::vector<int>& output)
{
  netCDF::NcVarAtt attr;
  try
  {
    output.clear();
    attr = var.getAtt(target);

    if (!attr.isNull())
    {
      output.resize(attr.getAttLength());
      attr.getValues(output.data());
    }
  }
  catch(const netCDF::exceptions::NcException& e)
  {
    // is target null terminated?
    //std::cerr << "Probe::getVecorOfDoubleAttributes returning false. Attribute " << target << " not found" << std::endl;
    return false;
  }
  return true;
}

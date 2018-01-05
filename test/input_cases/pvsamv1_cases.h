#ifndef _PVSAMV1_DATA_H_
#define _PVSAMV1_DATA_H_

#include <map>
#include "code_generator_utilities.h"
#include "pvsamv1_common_data.h"

/**
*   Data for high-level integration test that verifies whether results for a no-financials PV system in Phoenix
*   matches expected results.  Data generated from code-generator (Shift+F5) within SAM UI.
*   Test uses SSCAPI interfaces (similiar to SDK usage) to pass and receive data to PVSAMV1
*/
int pvsam_nofinancial_pheonix(ssc_data_t &data)
{
	pvsamv_nofinancial_default(data);
	return run_module(data, "pvsamv1");
}

/**
*   Data for high-level integration test that verifies whether results for a residential PV system in Phoenix
*   matches expected results.  Data generated from code-generator (Shift+F5) within SAM UI.
*   Test uses SSCAPI interfaces (similiar to SDK usage) to pass and receive data to PVSAMV1
*/
int pvsam_residential_pheonix(ssc_data_t &data)
{
	belpe_default(data);
	int status = run_module(data, "belpe");

	pvsamv1_with_residential_default(data);
	status += run_module(data, "pvsamv1");

	utility_rate5_default(data);
	status += run_module(data, "utilityrate5");

	cashloan_default(data);
	status += run_module(data, "cashloan");

	return status;
}

/**
*   Data for high-level integration test that verifies whether results for a no-financials PV system in Phoenix
*   with a custom input weather datafile matches expected results. 
*/
int pvsam_nofinancial_custom_input_weather(ssc_data_t &data)
{
	pvsamv_nofinancial_default(data);
	ssc_data_set_string(data, "solar_resource_file", solar_resource_path_15_min);
	return run_module(data, "pvsamv1");
}

/**
*   Data for high-level integration test that verifies sky model behavior
*   for a default case 
*/
int pvsam_test_albedo_and_radiation(ssc_data_t &data, int sky_diffuse_model, int irrad_mode)
{
	pvsamv_nofinancial_default(data);

	ssc_data_set_number(data, "irrad_mode", static_cast<ssc_number_t>(irrad_mode));
	ssc_data_set_number(data, "sky_model", static_cast<ssc_number_t>(sky_diffuse_model));
	return run_module(data, "pvsamv1");
}

/**
*   Data for high-level integration test that verifies module and inverter model behavior
*   for a default case
*/
int pvsam_test_module_and_inverter_model(ssc_data_t &data, int module_model, int inverter_model)
{
	pvsamv_nofinancial_default(data);

	ssc_data_set_number(data, "module_model", static_cast<ssc_number_t>(module_model));
	ssc_data_set_number(data, "inverter_model", static_cast<ssc_number_t>(inverter_model));
	return run_module(data, "pvsamv1");
}

/**
*   Data for high-level integration test that modifies one parameter of pvsamv1 default case
*/
int pvsam_no_financial_default_with_mods(ssc_data_t &data, std::map<std::string, double> pairs)
{
	pvsamv_nofinancial_default(data);
	for (std::map<std::string, double>::iterator it = pairs.begin(); it != pairs.end(); it++)
	{
		std::string name = std::string(it->first);
		ssc_number_t value = static_cast<ssc_number_t>(it->second);
		//std::cout << name << " : " << value << std::endl;
		ssc_data_set_number(data, const_cast<char *>(name.c_str()), value);
	}
	return run_module(data, "pvsamv1");
}
#endif

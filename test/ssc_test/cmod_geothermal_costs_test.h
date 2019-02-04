#ifndef _CMOD_GEOTHERMAL_COSTS_TEST_H_
#define _CMOD_GEOTHERMAL_COSTS_TEST_H_

#include <gtest/gtest.h>
#include <memory>

#include "core.h"
#include "sscapi.h"
#include "../ssc/vartab.h"
#include "../ssc/common.h"
#include "../input_cases/code_generator_utilities.h"
#include "../input_cases/geothermal_common_data.h"


class CMGeothermalCosts : public ::testing::Test {

public:

	ssc_data_t data;
	ssc_number_t calculated_value;
	ssc_number_t * calculated_array;

	void SetUp()
	{
		data = ssc_data_create(); //Data structure for cmod_geothermal_costs
		geothermal_costs_default(data);
	}
	void TearDown() {
		if (data) {
			ssc_data_clear(data);
		}
	}
	void SetCalculated(std::string name)
	{
		ssc_data_get_number(data, const_cast<char *>(name.c_str()), &calculated_value);
	}
	// apparently memory of the array is managed internally to the sscapi.
	void SetCalculatedArray(std::string name)
	{
		int n;
		calculated_array = ssc_data_get_array(data, const_cast<char *>(name.c_str()), &n);
	}
};

#endif 

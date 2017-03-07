//! robotkernel interface process data inspection
/*!
 * author: Robert Burger
 *
 * $Id$
 */

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab:

/*
 * This file is part of robotkernel.
 *
 * robotkernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * robotkernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with robotkernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "interface_process_data_inspection.h"
#include "robotkernel/kernel.h"
#include "robotkernel/helpers.h"
#include "robotkernel/exceptions.h"

SERVICE_PROVIDER_DEF(process_data_inspection, 
		interface_process_data_inspection::process_data_inspection);

using namespace std;
using namespace std::placeholders;
using namespace robotkernel;
using namespace interface_process_data_inspection;

const char* interface_process_data_inspection::process_data_inspection_sp_magic = "process_data_inspection"; 

//! default construction
/*!
 * \param mod_name module name to register for
 * \param dev_name interface device name
 * \param slvae_id module slave id
 */
process_data_inspection_handler::process_data_inspection_handler(
		std::string mod_name, std::string dev_name, int slave_id) : 
	log_base(mod_name, (mod_name + "." + dev_name + ".process_data_inspection")), 
	mod_name(mod_name), dev_name(dev_name), slave_id(slave_id) {
	kernel& k = *kernel::get_instance();

	stringstream base;
	base << mod_name << "." << dev_name << ".process_data_inspection.";

	k.add_service(mod_name, base.str() + "in", service_definition_in,
			std::bind(&process_data_inspection_handler::service_in, this, _1, _2));
	k.add_service(mod_name, base.str() + "out", service_definition_out,
			std::bind(&process_data_inspection_handler::service_out, this, _1, _2));
}

//! handler destruction
process_data_inspection_handler::~process_data_inspection_handler() {
	kernel& k = *kernel::get_instance();

	stringstream base;
	base << mod_name << "." << dev_name << ".process_data_inspection.";
	k.remove_service(base.str() + "in");
	k.remove_service(base.str() + "out");
};

//! service callback request input process data
/*!
 * \param request service request data
 * \parma response service response data
 * \return success
 */
int process_data_inspection_handler::service_in(const robotkernel::service_arglist_t& request, 
		robotkernel::service_arglist_t& response) {
	process_data_t pdg;
	pdg.slave_id = slave_id;

	// default response values
	std::vector<rk_type> data;
	string error_message;

	log(verbose, "pdin for slave_id %d requested\n", slave_id);

	int ret = kernel::request_cb(mod_name.c_str(), 
			MOD_REQUEST_GET_PDIN, (void *)&pdg);

	if (ret == -1) {
		error_message = "gettings process data in failed";
	} else {
		uint8_t *tmp = (uint8_t *)pdg.pd;
		data.resize(pdg.len);

		for (unsigned i = 0; i < pdg.len; ++i)
			data[i] = tmp[i];
	}

#define IN_RESP_DATA			0
#define IN_RESP_ERROR_MESSAGE 	1
	response.resize(2);
	response[IN_RESP_DATA]          = data;
	response[IN_RESP_ERROR_MESSAGE] = error_message;

	return 0;
}

const std::string process_data_inspection_handler::service_definition_in =
"response:\n"
"   vector/uint8_t: data\n"
"   string: error_message\n";

//! service callback request output process data
/*!
 * \param request service request data
 * \parma response service response data
 * \return success
 */
int process_data_inspection_handler::service_out(const robotkernel::service_arglist_t& request, 
		robotkernel::service_arglist_t& response) {
	process_data_t pdg;
	pdg.slave_id = slave_id;

	// default response values
	std::vector<rk_type> data;
	string error_message;

	log(verbose, "pdout for slave_id %d requested\n", slave_id);

	int ret = kernel::request_cb(mod_name.c_str(), 
			MOD_REQUEST_GET_PDOUT, (void *)&pdg);

	if(ret == -1) {
		error_message = "gettings process data out failed";
	} else {
		uint8_t *tmp = (uint8_t *)pdg.pd;
		data.resize(pdg.len);

		for (unsigned i = 0; i < pdg.len; ++i)
			data[i] = tmp[i];
	}

#define OUT_RESP_DATA			0
#define OUT_RESP_ERROR_MESSAGE 	1
	response.resize(2);
	response[OUT_RESP_DATA]          = data;
	response[OUT_RESP_ERROR_MESSAGE] = error_message;

	return 0;
}

const std::string process_data_inspection_handler::service_definition_out =
"response:\n"
"   vector/uint8_t: data\n"
"   string: error_message\n";


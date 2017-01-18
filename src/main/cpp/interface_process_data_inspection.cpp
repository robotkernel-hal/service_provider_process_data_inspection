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

INTERFACE_DEF(process_data_inspection, 
        interface_process_data_inspection::process_data_inspection)

using namespace std;
using namespace robotkernel;
using namespace interface_process_data_inspection;
        
//! default construction
/*!
 * \param mod_name module name to register for
 * \param dev_name interface device name
 * \param slvae_id module slave id
 */
process_data_inspection::process_data_inspection(const YAML::Node& node)
: interface_base("process_data_inspection", node) {
    kernel& k = *kernel::get_instance();
    
    stringstream base;
    base << mod_name << "." << dev_name << ".process_data_inspection.";

    k.add_service(mod_name, base.str() + "in", service_definition_in,
            boost::bind(&process_data_inspection::service_in, this, _1));
    k.add_service(mod_name, base.str() + "out", service_definition_out,
            boost::bind(&process_data_inspection::service_out, this, _1));
}

//! service callback request input process data
/*!
 * \param message service message
 * \return success
 */
int process_data_inspection::service_in(YAML::Node& message) {
    process_data_t pdg;
    pdg.slave_id = slave_id;

    // default response values
    std::vector<uint16_t> data;
    message["response"]["data"] = data;
    message["response"]["error_message"] = "";

    log(verbose, "pdin for slave_id %d requested\n", slave_id);

    int ret = kernel::request_cb(mod_name.c_str(), 
            MOD_REQUEST_GET_PDIN, (void *)&pdg);

    if(ret == -1) {
        message["response"]["error_message"] = 
            "gettings process data in failed\n";
    } else {
        uint8_t *tmp = (uint8_t *)pdg.pd;
        data.resize(pdg.len);

        for (unsigned i = 0; i < pdg.len; ++i)
            data[i] = tmp[i];
    
        message["response"]["data"] = data;
    }

    return 0;
}
        
const std::string process_data_inspection::service_definition_in =
    "response:\n"
    "   uint8_t*: data\n"
    "   string: error_message\n";

//! service callback request output process data
/*!
 * \param message service message
 * \return success
 */
int process_data_inspection::service_out(YAML::Node& message) {
    process_data_t pdg;
    pdg.slave_id = slave_id;

    // default response values
    std::vector<uint16_t> data;
    message["response"]["data"] = data;
    message["response"]["error_message"] = "";

    log(verbose, "pdout for slave_id %d requested\n", slave_id);

    int ret = kernel::request_cb(mod_name.c_str(), 
            MOD_REQUEST_GET_PDOUT, (void *)&pdg);

    if(ret == -1) {
        message["response"]["error_message"] = 
            "gettings process data out failed\n";
    } else {
        uint8_t *tmp = (uint8_t *)pdg.pd;
        data.resize(pdg.len);

        for (unsigned i = 0; i < pdg.len; ++i)
            data[i] = tmp[i];
    
        message["response"]["data"] = data;
    }

    return 0;
}
        
const std::string process_data_inspection::service_definition_out =
    "response:\n"
    "   uint8_t*: data\n"
    "   string: error_message\n";


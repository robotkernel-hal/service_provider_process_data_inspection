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

INTERFACE_DEF(process_data_inspection, interface_process_data_inspection::process_data_inspection)

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
    if (!k.clnt)
        throw str_exception("[interface_sercos_protocol|%s] no ln_connection!\n", 
                mod_name.c_str());
    
    stringstream base;
    base << k.clnt->name << "." << mod_name << "." << dev_name;

    register_in (k.clnt, base.str() + ".process_data_inspection.in");
    register_out(k.clnt, base.str() + ".process_data_inspection.out");
}

//! request input process data
int process_data_inspection::on_in(ln::service_request& req,
        ln_service_robotkernel_process_data_inspection_in& svc) {
    process_data_t pdg;
    pdg.slave_id = slave_id;

    log(verbose, "pdin for slave_id %d requested\n", slave_id);

    int ret = kernel::request_cb(mod_name.c_str(), MOD_REQUEST_GET_PDIN, (void *)&pdg);

    if(ret == -1) {
	    svc.resp.data = NULL;
	    svc.resp.data_len = 0;
    } else {
	    svc.resp.data = (uint8_t *)pdg.pd;
	    svc.resp.data_len = pdg.len;
    }

    req.respond();
    return 0;
}

//! request output process data
int process_data_inspection::on_out(ln::service_request& req,
        ln_service_robotkernel_process_data_inspection_out& svc) {
    process_data_t pdg;
    pdg.slave_id = slave_id;
    
    log(verbose, "pdout for slave_id %d requested\n", slave_id);

    int ret = kernel::request_cb(mod_name.c_str(), MOD_REQUEST_GET_PDOUT, (void *)&pdg);

    if(ret == -1) {
	    svc.resp.data = NULL;
	    svc.resp.data_len = 0;
    } else {
	    svc.resp.data = (uint8_t *)pdg.pd;
	    svc.resp.data_len = pdg.len;
    }

    req.respond();
    return 0;
}


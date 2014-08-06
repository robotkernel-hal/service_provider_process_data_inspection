//! robotkernel module class
/*!
 * author: Robert Burger
 *
 * $Id$
 */

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
#include "robotkernel/exceptions.h"
#undef BUILD_DATE
#undef PACKAGE
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACAKGE_VERSION
#undef VERSION
#include "config.h"

using namespace std;
using namespace robotkernel;
using namespace interface;
        
//! default construction
/*!
 * \param mod_name module name to register for
 */
process_data_inspection::process_data_inspection(const std::string& mod_name, 
        const std::string& dev_name, const int& slave_id) 
    : _mod_name(mod_name), _dev_name(dev_name), _slave_id(slave_id) {
    kernel& k = *kernel::get_instance();
    if (!k.clnt)
        throw str_exception("[interface_sercos_protocol|%s] no ln_connection!\n", 
                mod_name.c_str());
    
    stringstream base;
    base << k.clnt->name << "." << _mod_name << "." << _dev_name << ".";

    register_in(k.clnt, base.str() + "process_data_inspection.in");
    register_out(k.clnt, base.str() + "process_data_inspection.out");
}


int process_data_inspection::on_in(ln::service_request& req, ln_service_robotkernel_process_data_inspection_in& svc) {
    process_data_t pdg;
    pdg.slave_id = _slave_id;
    kernel::request_cb(_mod_name.c_str(), MOD_REQUEST_GET_PDIN, (void *)&pdg);

    svc.resp.data = (uint8_t *)pdg.pd;
    svc.resp.data_len = pdg.len;
    req.respond();
    return 0;
}

int process_data_inspection::on_out(ln::service_request& req, ln_service_robotkernel_process_data_inspection_out& svc) {
    process_data_t pdg;
    pdg.slave_id = _slave_id;
    kernel::request_cb(_mod_name.c_str(), MOD_REQUEST_GET_PDOUT, (void *)&pdg);

    svc.resp.data = (uint8_t *)pdg.pd;
    svc.resp.data_len = pdg.len;
    req.respond();
    return 0;
}


#ifdef __cplusplus
extern "C" {
#endif
#if 0
}
#endif

//! interface register
/*!
 * \param mod_name module name to register
 * \return interface handle
 */
INTERFACE_HANDLE intf_register(const char *mod_name, const char *dev_name, int slave_id) {
    process_data_inspection *s = NULL;

    klog(info, INTFNAME "%s: build by: " BUILD_USER "@" BUILD_HOST "\n", mod_name);
    klog(info, INTFNAME "%s: build date: " BUILD_DATE "\n", mod_name);

    // parsing sercos ring configuration
    try {
        s = new process_data_inspection(string(mod_name), string(dev_name), slave_id);
    } catch(exception& e) {
        klog(error, INTFNAME "%s: error constructing intercae:\n%s", mod_name, e.what());
        goto ErrorExit;
    }

    return (INTERFACE_HANDLE)s;

ErrorExit:
    if (s)
        delete s;

    return (INTERFACE_HANDLE)NULL;
}

//! interface unregister
/*!
 * \param hdl interface handle
 */
void intf_unregister(INTERFACE_HANDLE hdl) {
    // cast struct
    process_data_inspection *s = (process_data_inspection *)hdl;

    if (s)
        delete s;
}

#if 0
{
#endif
#ifdef __cplusplus
}
#endif


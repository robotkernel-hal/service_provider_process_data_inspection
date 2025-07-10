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

#include "provider.h"
#include "service_definitions.h"

#include "robotkernel/helpers.h"
#include "robotkernel/exceptions.h"

SERVICE_PROVIDER_DEF(process_data_inspection, 
        service_provider::process_data_inspection::provider);

using namespace std;
using namespace std::placeholders;

using namespace robotkernel;
using namespace service_provider;

//! handler construction
process_data_inspection::handler::handler(const robotkernel::sp_service_interface_t& req) 
    : log_base(req->owner, "process_data_inspection", req->device_name) 
{
    _instance = std::dynamic_pointer_cast<process_data_inspection::base>(req);
    if (!_instance)
        throw runtime_error(string("wrong base class"));

    add_svc_pd_inspect(_instance->owner, _instance->device_name + ".pd_inspect");
}

//! svc_in
/*!
 * \param[in]   req     Service request data.
 * \param[out]  resp    Service response data.
 */
void process_data_inspection::handler::svc_pd_inspect(const struct svc_req_pd_inspect& req, struct svc_resp_pd_inspect& resp) {
    log(verbose, "pdin %s:%s requested\n", _instance->owner.c_str(), 
            _instance->device_name.c_str());

    try {
        _instance->pd_inspect(resp.data);
    } catch (std::exception& e) {
        resp.error_message = e.what();
    }
}


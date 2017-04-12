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

#include "service_provider/process_data_inspection/provider.h"

#include "robotkernel/kernel.h"
#include "robotkernel/helpers.h"
#include "robotkernel/exceptions.h"

SERVICE_PROVIDER_DEF(process_data_inspection, 
        service_provider::process_data_inspection::provider);

using namespace std;
using namespace std::placeholders;

using namespace robotkernel;
using namespace service_provider;
using namespace string_util;

//! handler construction
process_data_inspection::handler::handler(const robotkernel::sp_service_requester_t& req) 
    : log_base("process_data_inspection", 
            req->owner + "." + req->service_prefix + ".process_data_inspection") {

    _instance = std::dynamic_pointer_cast<process_data_inspection::base>(req);
    if (!_instance)
        throw str_exception("wrong base class");

    kernel& k = *kernel::get_instance();

    stringstream base;
    base << _instance->owner << "." << _instance->service_prefix << ".process_data_inspection.";

    k.add_service(_instance->owner, base.str() + "in", service_definition_in,
            std::bind(&process_data_inspection::handler::service_in, this, _1, _2));
    k.add_service(_instance->owner, base.str() + "out", service_definition_out,
            std::bind(&process_data_inspection::handler::service_out, this, _1, _2));
}

//! handler destruction
process_data_inspection::handler::~handler() {
    kernel& k = *kernel::get_instance();

    stringstream base;
    base << _instance->owner << "." << _instance->service_prefix << ".process_data_inspection.";
    k.remove_service(base.str() + "in");
    k.remove_service(base.str() + "out");
};

//! service callback request input process data
/*!
 * \param request service request data
 * \parma response service response data
 * \return success
 */
int process_data_inspection::handler::service_in(
        const robotkernel::service_arglist_t& request, 
        robotkernel::service_arglist_t& response) {
    pd_t data_in;

    // default response values
    std::vector<rk_type> data;
    string error_message;

    log(verbose, "pdin %s:%s requested\n", _instance->owner.c_str(), 
            _instance->service_prefix.c_str());

    try {
        _instance->get_pdin(data_in);
        data.assign(data_in.begin(), data_in.end());
    } catch (std::exception& e) {
        error_message = e.what();
    }

#define IN_RESP_DATA            0
#define IN_RESP_ERROR_MESSAGE   1
    response.resize(2);
    response[IN_RESP_DATA]          = data;
    response[IN_RESP_ERROR_MESSAGE] = error_message;

    return 0;
}

const std::string process_data_inspection::handler::service_definition_in =
"response:\n"
"   vector/uint8_t: data\n"
"   string: error_message\n";

//! service callback request output process data
/*!
 * \param request service request data
 * \parma response service response data
 * \return success
 */
int process_data_inspection::handler::service_out(const robotkernel::service_arglist_t& request, 
        robotkernel::service_arglist_t& response) {
    pd_t data_out;

    // default response values
    std::vector<rk_type> data;
    string error_message;

    log(verbose, "pdout %s:%s requested\n", _instance->owner.c_str(), 
            _instance->service_prefix.c_str());

    try {
        _instance->get_pdout(data_out);
        data.assign(data_out.begin(), data_out.end());
    } catch (std::exception& e) {
        error_message = e.what();
    }

#define OUT_RESP_DATA           0
#define OUT_RESP_ERROR_MESSAGE  1
    response.resize(2);
    response[OUT_RESP_DATA]          = data;
    response[OUT_RESP_ERROR_MESSAGE] = error_message;

    return 0;
}

const std::string process_data_inspection::handler::service_definition_out =
"response:\n"
"   vector/uint8_t: data\n"
"   string: error_message\n";


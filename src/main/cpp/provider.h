//! robotkernel module class
/*!
 * author: Robert Burger
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

#ifndef SERVICE_PROVIDER__PROCESS_DATA_INSPECTION__PROVIDER_H
#define SERVICE_PROVIDER__PROCESS_DATA_INSPECTION__PROVIDER_H

// Robotkernel includes
#include "robotkernel/service_provider_base.h"
#include "robotkernel/service_provider_intf.h"
#include "robotkernel/service.h"
#include "robotkernel/kernel.h"
#include "robotkernel/log_base.h"

// Service provider includes
#include "service_provider/process_data_inspection/base.h"
#include "service_definitions.h"

namespace service_provider {
namespace process_data_inspection {

// forward declaration
class handler;

class provider : 
    public robotkernel::service_provider_base<handler, base> 
{
    public:
        //! default construction
        /*!
        */
        provider(const std::string& name)
            : service_provider_base(name, "process_data_inspection") {};

        ~provider() {};
};

class handler : 
    public robotkernel::log_base,
    public svc_base_in,
    public svc_base_out
{
    public:
        typedef std::shared_ptr<process_data_inspection::base> base_t;
        base_t _instance;

        //! handler construction
        handler(const robotkernel::sp_service_interface_t& req);

        //! handler destruction
        ~handler() {}

        //! svc_in
        /*!
         * \param[in]   req     Service request data.
         * \param[out]  resp    Service response data.
         */
        virtual void svc_in(const struct svc_req_in& req, struct svc_resp_in& resp);

        //! svc_out
        /*!
         * \param[in]   req     Service request data.
         * \param[out]  resp    Service response data.
         */
        virtual void svc_out(const struct svc_req_out& req, struct svc_resp_out& resp);
};

}; // namespace process data inspection
}; // namespace interface

#endif // SERVICE_PROVIDER__PROCESS_DATA_INSPECTION__PROVIDER_H


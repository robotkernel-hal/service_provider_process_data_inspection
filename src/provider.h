//! robotkernel module class
/*!
 * author: Robert Burger
 */

// vim: tabstop=4 softtabstop=4 shiftwidth=4 expandtab:

/*
 * This file is part of robotkernel.
 *
 * robotkernel is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * robotkernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with robotkernel; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SERVICE_PROVIDER_PROCESS_DATA_INSPECTION__PROVIDER_H
#define SERVICE_PROVIDER_PROCESS_DATA_INSPECTION__PROVIDER_H

// Robotkernel includes
#include "robotkernel/service_provider_base.h"
#include "robotkernel/service.h"
#include "robotkernel/robotkernel.h"
#include "robotkernel/log_base.h"

// Service provider public includes
#include "service_provider_process_data_inspection/base.h"

// Service provider private includes
#include "service_definitions.h"

namespace service_provider_process_data_inspection {

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
    public svc_base_pd_inspect
{
    public:
        typedef std::shared_ptr<service_provider_process_data_inspection::base> base_t;
        base_t _instance;

        //! handler construction
        handler(const robotkernel::sp_service_interface_t& req);

        //! handler destruction
        ~handler() {}

        //! svc_inspect
        /*!
         * \param[in]   req     Service request data.
         * \param[out]  resp    Service response data.
         */
        virtual void svc_pd_inspect(const struct svc_req_pd_inspect& req, struct svc_resp_pd_inspect& resp);
};

}; // namespace service_provider_process_data_inspection

#endif // SERVICE_PROVIDER_PROCESS_DATA_INSPECTION__PROVIDER_H


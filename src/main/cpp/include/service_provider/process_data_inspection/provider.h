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

#ifndef __SERVICE_PROVIDER__PROCESS_DATA_INSPECTION__PROVIDER_H__
#define __SERVICE_PROVIDER__PROCESS_DATA_INSPECTION__PROVIDER_H__

#include "robotkernel/service_provider_base.h"
#include "robotkernel/service_provider_intf.h"
#include "robotkernel/service.h"
#include "robotkernel/kernel.h"
#include "robotkernel/log_base.h"

#include "service_provider/process_data_inspection/base.h"

namespace service_provider {

    namespace process_data_inspection {

        // forward declaration
        class handler;

        class provider : public robotkernel::service_provider_base<handler, base> {
            public:
                //! default construction
                /*!
                */
                provider()
                    : service_provider_base("process_data_inspection") {};

                ~provider() {};

        };

        class handler : public robotkernel::log_base {
            public:
                typedef std::shared_ptr<process_data_inspection::base> base_t;
                base_t _instance;

                //! handler construction
                handler(const robotkernel::sp_service_requester_t& req);

                //! handler destruction
                ~handler();

                //! service callback request input process data
                /*!
                 * \param request service request data
                 * \parma response service response data
                 * \return success
                 */
                int service_in(const robotkernel::service_arglist_t& request, 
                        robotkernel::service_arglist_t& response);
                static const std::string service_definition_in;

                //! service callback request output process data
                /*!
                 * \param request service request data
                 * \parma response service response data
                 * \return success
                 */
                int service_out(const robotkernel::service_arglist_t& request, 
                        robotkernel::service_arglist_t& response);
                static const std::string service_definition_out;
        };

    }; // namespace process data inspection

}; // namespace interface

#endif // __INTERFACE_PROCESS_DATA_INSPECTION_H__


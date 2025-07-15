//! robotkernel interface canopen protocol
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

#ifndef SERVICE_PROVIDER_PROCESS_DATA_INSPECTION__BASE_H
#define SERVICE_PROVIDER_PROCESS_DATA_INSPECTION__BASE_H

#include <list>
#include "robotkernel/service_interface.h"
#include "robotkernel/process_data.h"

namespace service_provider_process_data_inspection {

//! process data definition
typedef std::vector<uint8_t> pd_t;

class base : 
    public robotkernel::service_interface 
{
    public:
        //! construction
        base(const std::string& owner, const std::string& service_prefix)
            : robotkernel::service_interface(owner, service_prefix + ".process_data_inspection") {};

        //! destruction
        virtual ~base() = 0;

        //! return process data
        /*!
         * \param pd return process data
         */
        virtual void pd_inspect(pd_t& pd) = 0;
};

class pd_inspection : 
    public base 
{
    private:
        robotkernel::sp_process_data_t pd_dev;

    public:
        //! construction
        pd_inspection(const std::string& owner, const std::string& service_prefix,
                robotkernel::sp_process_data_t pd_dev)
            : base(owner, service_prefix), pd_dev(pd_dev) {}
        
        //! return process data
        /*!
         * \param pd return process data
         */
        virtual void pd_inspect(pd_t& pd) { 
            if (pd_dev) {
                pd.resize(pd_dev->length);
                memcpy(&pd[0], pd_dev->peek(), pd_dev->length);
            } else {
                pd.resize(0);
            }
        }
};

typedef std::shared_ptr<service_provider_process_data_inspection::pd_inspection> sp_pd_inspection_t;

inline base::~base() { }

}; // namespace service_provider_process_data_inspection

#endif // SERVICE_PROVIDER_PROCESS_DATA_INSPECTION__BASE_H


//! robotkernel interface canopen protocol
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

#ifndef __SERVICE_PROVIDER__PROCESS_DATA_INSPECTION__BASE__H__
#define __SERVICE_PROVIDER__PROCESS_DATA_INSPECTION__BASE__H__

#include <list>
#include "robotkernel/service_interface.h"

namespace service_provider {
#ifdef EMACS
}
#endif

namespace process_data_inspection {
#ifdef EMACS
}
#endif

//! process data definition
typedef std::vector<uint8_t> pd_t;

class base : 
    public robotkernel::service_interface 
{
    public:
        //! construction
        base(std::string owner, std::string service_prefix)
            : robotkernel::service_interface(owner, service_prefix + ".process_data_inspection") {};

        //! destruction
        virtual ~base() = 0;

        //! return input process data (measurements)
        /*!
         * \param pd return input process data
         */
        virtual void get_pdin(pd_t& pd) = 0;

        //! return output process data (commands)
        /*!
         * \param pd return output process data
         */
        virtual void get_pdout(pd_t& pd) = 0;
};

inline base::~base() { }

#ifdef EMACS 
{
#endif
}; // namespace process_data_inspection

#ifdef EMACS 
{
#endif
}; // namespace service_provider

#endif // __SERVICE_PROVIDER__PROCESS_DATA_INSPECTION__BASE__H__


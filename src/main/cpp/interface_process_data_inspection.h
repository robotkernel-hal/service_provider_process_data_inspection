//! robotkernel module class
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

#ifndef __INTERFACE_PROCESS_DATA_INSPECTION_H__
#define __INTERFACE_PROCESS_DATA_INSPECTION_H__

#include "robotkernel/kernel.h"
#include "robotkernel/interface_base.h"

namespace interface_process_data_inspection {
    
class process_data_inspection : public robotkernel::interface_base {
    public:
        //! default construction
        /*!
         * \param node configuration node 
         */
        process_data_inspection(const YAML::Node& node);
        
        //! service callback request input process data
        /*!
         * \param message service message
         * \return success
         */
        int service_in(YAML::Node& message);
        static const std::string service_definition_in;

        //! service callback request output process data
        /*!
         * \param message service message
         * \return success
         */
        int service_out(YAML::Node& message);
        static const std::string service_definition_out;
};

} // namespace interface

#endif // __INTERFACE_PROCESS_DATA_INSPECTION_H__


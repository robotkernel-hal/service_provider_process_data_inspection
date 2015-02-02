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

#define LN_UNREGISTER_SERVICE_IN_BASE_DETOR  
#include "ln_messages.h"
#undef LN_UNREGISTER_SERVICE_IN_BASE_DETOR

#define INTFNAME "[interface_process_data_inspection] "

namespace interface {
    
class process_data_inspection : 
    public ln_service_in_base,
    public ln_service_out_base
{
    std::string _mod_name;
    std::string _dev_name;
    int _slave_id;

    public:
        //! default construction
        /*!
         * \param mod_name module name to register for
         * \param dev_name interface device name
         * \param slvae_id module slave id
         */
        process_data_inspection(const std::string& mod_name, 
                const std::string& dev_name, const int& slave_id);

        //! request input process data
        int on_in(ln::service_request& req, 
                ln_service_robotkernel_process_data_inspection_in& svc);

        //! request output process data
        int on_out(ln::service_request& req, 
                ln_service_robotkernel_process_data_inspection_out& svc);
};

} // namespace interface

#endif // __INTERFACE_PROCESS_DATA_INSPECTION_H__


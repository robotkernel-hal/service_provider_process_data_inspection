'''
(C) Robert Burger <robert.burger@dlr.de>

This file is part of Robotkernel-GUI.

Robotkernel-GUI is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Robotkernel-GUI is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Robotkernel-GUI.  If not, see <http://www.gnu.org/licenses/>.
'''

import time, traceback
import helpers

class process_data_inspection_device(helpers.svc_wrapper):
    def __init__(self, clnt, prefix):
        helpers.svc_wrapper.__init__(self, clnt, prefix)
        self.inspection_data = []

    def update(self):
        self.svc_pd_inspection.call()
        self.inspection_data = self.svc_pd_inspection.resp.data


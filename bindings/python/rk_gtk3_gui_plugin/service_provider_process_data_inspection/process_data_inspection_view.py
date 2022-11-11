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
from __future__ import absolute_import
from __future__ import division

from builtins import zip
import os, traceback
import math

import gi
gi.require_version('Gtk', '3.0')
gi.require_version('GLib', '2.0')
from gi.repository import Gtk
from gi.repository import GObject


import helpers
from .process_data_inspection_wrapper import process_data_inspection_device

class process_data_inspection_view(helpers.service_provider_view, helpers.builder_base):
    def __init__(self, parent, container):
        fn = os.path.join(os.path.dirname(__file__), 'process_data_inspection_view.ui')
        helpers.builder_base.__init__(self, fn, 'process_data_inspection_box', 'pdi_adjustment')
        helpers.service_provider_view.__init__(self, parent.app, parent, self.process_data_inspection_box, 'in')

        container.pack_start(self.process_data_inspection_box, True, True, 0)

        fd = helpers.gui_utils.get_monospace_font_description()
        self.in_tv.modify_font(fd)
        self.out_tv.modify_font(fd)

        self.timer = 0
        self.timer_id = None
        self.is_running = False

        self.last_hex = {}

    def show(self, module, device):
        helpers.service_provider_view.show(self)
        self.last_hex = {}

        device_key = (module, device)
        if device_key not in self.devices:
            self.devices[device_key] = process_data_inspection_device(self.app.clnt,
                    "%s.%s.%s.process_data_inspection" % (self.parent.name, module, device))

        if self.current_device != device_key:
            self.current_device = device_key
            self.do_refresh()

    def do_refresh(self):
        if self.current_device is None:
            return False
        dev = self.devices[self.current_device]
        dev.update()
        self.show_data("in_tv", dev.in_data)
        self.show_data("out_tv", dev.out_data)

    def generate_hex_listing(self, data, line_len=16):
        text = ["%d bytes:" % len(data)]
        if len(data) > 0:
            ml = 2 * int(math.ceil(math.log(len(data)) / math.log(2) / 8.))
            ml = max(ml, 2)
            o = 0
            while o < len(data):
                text.append("0x%0*x  %s" % (ml, o, " ".join(["%02x" % f for f in data[o:o+line_len]])))
                o += line_len
        return "\n".join(text)

    def show_data(self, tv_name, data):
        hex = self.generate_hex_listing(data)
        tv = getattr(self, tv_name)
        b = tv.get_buffer()
        last = self.last_hex.get(tv_name)
        if last == hex:
            return
        self.last_hex[tv_name] = hex
        if last is None:
            b.set_text(hex)
            return
        # compare/change
        # compare line by line and replace/instet
        offset = 0
        for line_old, line_new in zip(last.split("\n"), hex.split("\n")):
            ll = len(line_new) + 1
            if line_old != line_new:
                # replace
                s_iter = b.get_iter_at_offset(offset)
                e_iter = b.get_iter_at_offset(offset + ll)
                b.delete(s_iter, e_iter)
                b.insert(s_iter, line_new + "\n")
            offset += ll

    def on_refresh_btn_clicked(self, btn):
        self.do_refresh()

    def on_pdi_adjustment_value_changed(self, adj):
        v = adj.get_value()
        self.timer = int(v / 0.1) * 0.1
        if self.timer_id is not None:
            GObject.source_remove(self.timer_id)
            self.timer_id = None
        if self.timer > 0:
            self.timer_id = GObject.timeout_add(int(v * 1000), self.on_timeout)

    def on_timeout(self):
        if self.timer <= 0:
            return False
        self.do_refresh()
        return True

from conan import ConanFile
import os


class MainProject(ConanFile):
    python_requires = "conan_template/[~6]@robotkernel/stable"
    python_requires_extend = "conan_template.RobotkernelConanFile"

    name = "service_provider_process_data_inspection"
    url = "https://rmc-github.robotic.dlr.de/robotkernel/service_provider_process_data_inspection"
    description = "robotkernel service provider for process data inspeciton."
    exports_sources = ["*", "!.gitignore", "!bindings"]

    tool_requires = ["robotkernel_generator/[~6]@robotkernel/stable"]

    def requirements(self):
        self.requires(f"{self.name}_ln_msgdef/{self.version}@{self.user}/{self.channel}")
        self.requires("robotkernel/[~6]@robotkernel/stable")


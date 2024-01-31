from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import patch, copy
from os.path import join
import re


class DnsLibsConan(ConanFile):
    name = "algorithms"
    license = "Apache-2.0"
    author = "Jollu Emiluulu"
    url = "https://github.com/Jollu8/Algorithms"
    vcs_url = "https://github.com/Jollu8/Algorithms.git"
    description = "Different algorithms implemented in C++"
    topics = ("tools", "containers")
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
    }
    # A list of paths to patches. The paths must be relative to the conanfile directory.
    # They are applied in case of the version equals 777 and mostly intended to be used
    # for testing.
    patch_files = []
    exports_sources = patch_files

    def requirements(self):
        self.requires("fmt/10.1.1", transitive_headers=True)
        self.requires("magic_enum/0.9.5", transitive_headers=True)
        # self.requires("ada/2.7.4", transitive_headers=True)

    def build_requirements(self):
        self.test_requires("gtest/1.14.0")

    def configure(self):
        self.options["spdlog"].no_exceptions = True
        self.options["gtest"].build_gmock = False
        self.options["pcre2"].build_pcre2grep = False

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def source(self):
        self.run(f"git init . && git remote add origin {self.vcs_url} && git fetch")
        if re.match(r'\d+\.\d+\.\d+', self.version) is not None:
            version_hash = self.conan_data["commit_hash"][self.version]["hash"]
            self.run("git checkout -f %s" % version_hash)
        else:
            self.run("git checkout -f %s" % self.version)
            for p in self.patch_files:
                patch(self, patch_file=p)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build(target="algorithms")

    def package(self):
        MODULES = [
            "tools"
            "containers"
        ]

        for m in MODULES:
            copy(self, "*.h", src=join(self.source_folder, "%s/include" % m), dst=join(self.package_folder, "include"), keep_path = True)

        copy(self, "*.dll", src=self.build_folder, dst=join(self.package_folder, "bin"), keep_path=False)
        copy(self, "*.lib", src=self.build_folder, dst=join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.so", src=self.build_folder, dst=join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.dylib", src=self.build_folder, dst=join(self.package_folder, "lib"), keep_path=False)
        copy(self, "*.a", src=self.build_folder, dst=join(self.package_folder, "lib"), keep_path=False)


    def package_info(self):
        self.cpp_info.name = "enjo"
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.libs = [
            "tools",
            "containers",
        ]
        self.cpp_info.libdirs = ['lib']
        self.cpp_info.requires = [
            "fmt::fmt",
            "magic_enum::magic_enum",
            "ada::ada",
        ]
        if self.settings.os == "Windows":
            self.cpp_info.system_libs = ["ws2_32", "iphlpapi", "ntdll"]
        self.cpp_info.defines.append("FMT_EXCEPTIONS=0")

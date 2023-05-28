/*
 * Copyright (C) 2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sys/sysinfo.h>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"

void property_override(char const prop[], char const value[])
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

std::string read_cmdline(const std::string& key) {
    std::ifstream cmdline("/proc/cmdline");
    std::string line;
    std::string value;

    if (cmdline.is_open()) {
        while (std::getline(cmdline, line)) {
            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, ' ')) {
                std::string::size_type pos = token.find(key);
                if (pos != std::string::npos) {
                    value = token.substr(pos + key.length() + 1);
                    return value;
                }
            }
        }
    }

    return value;
}

void load_bootmode_properties() {
    std::string boot_reason = read_cmdline("androidboot.bootreason");

    if (boot_reason == "usb")
        property_override("ro.bootmode", "charger");
}

void load_dalvik_properties() {
    char const *heapstartsize;
    char const *heapgrowthlimit;
    char const *heapsize;
    char const *heapminfree;
    char const *heapmaxfree;
    char const *heaptargetutilization;
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram >= 5ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        heapstartsize = "16m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.5";
        heapminfree = "8m";
        heapmaxfree = "32m";
    } else if (sys.totalram >= 3ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-4096-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.6";
        heapminfree = "8m";
        heapmaxfree = "16m";
    } else {
        return;
    }

    property_override("dalvik.vm.heapstartsize", heapstartsize);
    property_override("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_override("dalvik.vm.heapsize", heapsize);
    property_override("dalvik.vm.heaptargetutilization", heaptargetutilization);
    property_override("dalvik.vm.heapminfree", heapminfree);
    property_override("dalvik.vm.heapmaxfree", heapmaxfree);
}

void vendor_load_properties() {
    load_bootmode_properties();
    load_dalvik_properties();
}

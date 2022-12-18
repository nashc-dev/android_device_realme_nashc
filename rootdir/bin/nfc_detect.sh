#!/vendor/bin/sh
#
# Copyright (C) 2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

if [ -f /proc/oplus_nfc/chipset ]; then
    if [ $(cat /proc/oplus_nfc/chipset) != "NULL" ]; then
        # Due to only vendor_init being able to set exported_default_prop, we need to set the sku
        # as a different property and then use a setprop in the init rc to set the correct property.
        setprop ro.vendor.device.variant nfc
    fi
fi

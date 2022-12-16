#!/vendor/bin/sh
#
# Copyright (C) 2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

if [ -f /proc/oplus_nfc/chipset ]; then
    if [ $(cat /proc/oplus_nfc/chipset) != "NULL" ]; then
        setprop ro.boot.product.vendor.sku nfc
    fi
fi

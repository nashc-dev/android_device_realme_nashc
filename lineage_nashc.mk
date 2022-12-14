#
# Copyright (C) 2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/non_ab_device.mk)

# Inherit from device makefile.
$(call inherit-product, device/realme/nashc/device.mk)

# Inherit some common LineageOS stuff.
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

PRODUCT_NAME := lineage_nashc
PRODUCT_DEVICE := nashc
PRODUCT_MANUFACTURER := Realme
PRODUCT_BRAND := Realme
PRODUCT_MODEL := Realme 8

PRODUCT_GMS_CLIENTID_BASE := android-realme

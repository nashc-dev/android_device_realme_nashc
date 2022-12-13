#
# Copyright (C) 2022 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := $(call my-dir)

ifneq ($(filter nashc, $(TARGET_DEVICE)),)
include $(call all-makefiles-under,$(LOCAL_PATH))

VENDOR_SYMLINKS := \
    $(TARGET_OUT_VENDOR)/lib/hw \
    $(TARGET_OUT_VENDOR)/lib64/hw

$(VENDOR_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	$(hide) echo "Making vendor symlinks"
	@mkdir -p $(TARGET_OUT_VENDOR)/lib/hw
	@mkdir -p $(TARGET_OUT_VENDOR)/lib64/hw
	@ln -sf libSoftGatekeeper.so $(TARGET_OUT_VENDOR)/lib/hw/gatekeeper.default.so
	@ln -sf libSoftGatekeeper.so $(TARGET_OUT_VENDOR)/lib64/hw/gatekeeper.default.so
	@ln -sf libMcGatekeeper.so $(TARGET_OUT_VENDOR)/lib64/hw/gatekeeper.trustonic.so
	@ln -sf libMcGatekeeper.so $(TARGET_OUT_VENDOR)/lib/hw/gatekeeper.trustonic.so
	$(hide) touch $@

ALL_DEFAULT_INSTALLED_MODULES += $(VENDOR_SYMLINKS)
endif

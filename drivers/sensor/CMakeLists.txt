#
# Copyright (c) 2022 Circuit Dojo LLC
#
# SPDX-License-Identifier: Apache-2.0
#

zephyr_library_amend()
zephyr_library_sources_ifdef(CONFIG_DRV2605L drv2605l.c)
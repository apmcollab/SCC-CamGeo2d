#
# This makefile builds the CamGeo2d support library. 
#

SHELL=/bin/sh

# Location of SCC source files and Makescripts files

SCC_Dir=../SCC
MAKESCRIPTS_Dir=$(SCC_Dir)/MakeScripts

# Use BaseCommonConfig.mk if it exists, otherwise use BaseCommonConfig_Default.mk 

ifneq ("$(wildcard $(MAKESCRIPTS_Dir)/BaseCommonConfig.mk)","")
	include $(MAKESCRIPTS_Dir)/BaseCommonConfig.mk
else
	include $(MAKESCRIPTS_Dir)/BaseCommonConfig_Default.mk
endif

# Parameters for library construction script 

CXX     := g++
LIB_DIR = ./lib
SRC_DIR = .

INCLUDES    += -I$(SCC_Dir)

# Create library directory if it doesn't exist 

create_lib_dir := \
$(shell if [ ! -e $(LIB_DIR) ]; then mkdir $(LIB_DIR); fi) 

# specify make parameters

ifndef VERBOSE
QUIET     :=@
MAKEFLAGS += --no-print-directory
MAKEFLAGS := $(sort $(MAKEFLAGS))
endif

ifeq ($(MAKECMDGOALS),release)

CFLAGS      :=-O2  -fno-gcse -fno-optimize-sibling-calls -Wno-write-strings
CXXFLAGS    :=-O2  -fno-gcse -fno-optimize-sibling-calls -Wno-write-strings
CDEFINES    += 
CXXDEFINES  += 
endif

ifeq ($(MAKECMDGOALS),debug)
CFLAGS      =-g -Wall -fno-inline
CDEFINES    =-D_DEBUG
CXXFLAGS    =-g -Wall -fno-inline
CXXDEFINES  +=-D_DEBUG 
endif

RELEASE_DIR  = ./_releaseCamGeo2d
DEBUG_DIR    = ./_debugCamGeo2d

DEBUG_LIBRARY    = $(LIB_DIR)/libCamGeo2d_debug.a
RELEASE_LIBRARY  = $(LIB_DIR)/libCamGeo2d.a 

include $(MAKESCRIPTS_Dir)/CommonLibMake.mk


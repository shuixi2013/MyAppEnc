CC=clang
ROOT := $(shell pwd)
INCLUDE:= ../include
COMMON := ../common
USR_SUB_DIR := ./SoEraser ./SoFix


usr:
	@for n in $(USR_SUB_DIR); do $(MAKE) -C $$n ; done 

clean:
	@for n in $(USR_SUB_DIR); do $(MAKE) -C $$n  clean; done 

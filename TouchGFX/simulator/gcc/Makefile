# Helper macros to convert spaces into question marks and back again
e := 
sp := $(e) $(e)
qs = $(subst ?,$(sp),$1)
sq = $(subst $(sp),?,$1)

# Get name of this Makefile (avoid getting word 0 and a starting space)
makefile_name := $(wordlist 1,1000,$(MAKEFILE_LIST))

# Get path of this Makefile
makefile_path := $(call qs,$(dir $(call sq,$(abspath $(call sq,$(makefile_name))))))

# Get path where the Application is
application_path := $(call qs,$(abspath $(call sq,$(makefile_path)../..)))
proj_path := G:\SPELS\meteo_tgfx
.PHONY: clean assets all

ifneq ($(words $(makefile_path))$(words $(MAKEFILE_LIST)),11)
all clean assets:
$(error Spaces not allowed in path)
else

ADDITIONAL_SOURCES :=
ADDITIONAL_INCLUDE_PATHS :=
ADDITIONAL_LIBRARY_PATHS :=
ADDITIONAL_LIBRARIES :=
#ADDITIONAL_LIBRARIES += ../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
#ADDITIONAL_LIBRARIES += ../Middlewares/Third_Party/FreeRTOS/Source/include
#ADDITIONAL_LIBRARIES += ../Core/Inc
#ADDITIONAL_LIBRARIES += ../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
export ADDITIONAL_SOURCES ADDITIONAL_INCLUDE_PATHS ADDITIONAL_LIBRARY_PATHS ADDITIONAL_LIBRARIES

all: $(filter assets,$(MAKECMDGOALS))
all assets: $(filter clean,$(MAKECMDGOALS))
all clean assets:
	@$(MAKE) -r -f generated/simulator/gcc/Makefile -s $(MFLAGS) $@ -C "$(application_path)"
endif


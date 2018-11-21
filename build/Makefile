PJDIR=/Users/dwianto/Desktop/bssn_sip/src/pjproject
include $(PJDIR)/build.mak
include $(PJDIR)/build/common.mak

export LIBDIR := $(PJDIR)/lib
export BINDIR := $(PJDIR)/bin

RULES_MAK := $(PJDIR)/build/rules.mak


###############################################################################
# Gather all flags.
#
export _CFLAGS 	:= $(CC_CFLAGS) $(OS_CFLAGS) $(HOST_CFLAGS) $(M_CFLAGS) \
		   $(PJ_CFLAGS) $(CFLAGS) $(CC_INC)../../pjsip/include \
		   $(CC_INC)$(PJDIR)/pjlib/include \
		   $(CC_INC)$(PJDIR)/pjlib-util/include \
		   $(CC_INC)$(PJDIR)/pjnath/include \
		   $(CC_INC)$(PJDIR)/pjmedia/include
export _CXXFLAGS:= $(_CFLAGS) $(CC_CXXFLAGS) $(OS_CXXFLAGS) $(M_CXXFLAGS) \
		   $(HOST_CXXFLAGS) $(CXXFLAGS)
export _LDFLAGS := $(CC_LDFLAGS) $(OS_LDFLAGS) $(M_LDFLAGS) $(HOST_LDFLAGS) \
		   $(APP_LDFLAGS) $(APP_LDLIBS) $(LDFLAGS)

export DYLD_LIBRARY_PATH := $(APP_LDLIBS)



export CC_OUT CC AR RANLIB HOST_MV HOST_RM HOST_RMDIR HOST_MKDIR OBJEXT LD LDOUT

TARGETS := latihan

all: $(TARGETS)

swig:
	$(MAKE) -C ../src/swig

doc:

dep: depend
distclean: realclean

.PHONY: all dep depend clean realclean distclean
.PHONY: $(TARGETS)
.PHONY: $(PJSUA_EXE) $(PJSYSTEST_EXE)


latihan:
		$(MAKE) -f Latihan.mak


clean depend realclean:

	$(MAKE) -f Latihan.mak $@
	@if test "$@" = "depend"; then \
	  echo '$(BINDIR)/$(PJSUA_EXE): $(APP_LIB_FILES)' >> .pjsua-$(TARGET_NAME).depend; \
	  echo '$(BINDIR)/$(PJSYSTEST_EXE): $(APP_LIB_FILES)' >> .pjsystest-$(TARGET_NAME).depend; \
	fi
	@if echo "$(TARGET_NAME)" | grep -q "apple-darwin_ios$$"; then \
	  for F in $(filter %$(TARGET_NAME).a,$(PJ_LIBXX_FILES)); do \
	    tmp=`echo $${F##*/} | sed -e "s/\-$(TARGET_NAME)\.a/.a/"`; \
	    rm -f ../src/pjsua/ios/$$tmp; \
	  done; \
	fi;

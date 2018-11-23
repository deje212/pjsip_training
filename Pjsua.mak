PJDIR=/Users/dwianto/Desktop/bssn_sip/src/pjproject
include $(PJDIR)/build.mak
include $(PJDIR)/build/common.mak

export LIBDIR := $(PJDIR)/lib
export BINDIR := $(PJDIR)/bin

RULES_MAK := $(PJDIR)/build/rules.mak

###############################################################################
# Gather all flags.
#
export _CFLAGS 	:= $(PJ_CFLAGS) $(CFLAGS) -DCMAKE_INSTALL_RPATH_USE_LINK_PATH="ON"
export _CXXFLAGS:= $(PJ_CXXFLAGS) $(CFLAGS)
export _LDFLAGS := $(PJ_LDFLAGS) $(PJ_LDLIBS) $(LDFLAGS)
export _LDXXFLAGS := $(PJ_LDXXFLAGS) $(PJ_LDXXLIBS) $(LDFLAGS)
export _DYLD_LIBRARY_PATH :=/Users/dwianto/Desktop/bssn_sip/src/pjproject/pjlib/lib:/Users/dwianto/Desktop/bssn_sip/src/pjproject/pjlib-util/lib:/Users/dwianto/Desktop/bssn_sip/src/pjproject/pjnath/lib:/Users/dwianto/Desktop/bssn_sip/src/pjproject/pjmedia/lib:/Users/dwianto/Desktop/bssn_sip/src/pjproject/pjsip/lib:/Users/dwianto/Desktop/bssn_sip/src/pjproject/third_party/lib:/usr/local/opt/openssl/lib


SRCDIR := $(PJDIR)latihan-apps/apps
OBJDIR := $(PJDIR)latihan-apps/output/pjsua_apps
BINDIR := $(PJDIR)latihan-apps/bin/pjsua_apps


FILES :=	pjsua_init


EXES := $(foreach file, $(FILES), $(file)$(HOST_EXE))


.PHONY: $(EXES)

all: $(EXES) $(PJSUA2_EXES)

$(EXES):
	$(MAKE) --no-print-directory -f $(RULES_MAK) LATIHAN_SRCDIR=$(SRCDIR) LATIHAN_OBJS=$@.o LATIHAN_CFLAGS="$(_CFLAGS)" LATIHAN_CXXFLAGS="$(_CXXFLAGS)" LATIHAN_LDFLAGS="$(_LDFLAGS)" LATIHAN_EXE=$@ APP=LATIHAN app=LATIHAN $(subst /,$(HOST_PSEP),$(BINDIR)/$@)


depend:

clean:
	$(MAKE) -f $(RULES_MAK) APP=LATIHAN app=apps $@
	$(subst @@,$(EXES),$(HOST_RM))
	$(subst @@,$(BINDIR),$(HOST_RMDIR))

distclean realclean: clean
	$(MAKE) -f $(RULES_MAK) APP=LATIHAN app=apps $@

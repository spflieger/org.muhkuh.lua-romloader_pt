m4 -E <application/templates/muhkuh_version.h.m4 >application/muhkuh_version.h.tmp
cmp -s application/muhkuh_version.h.tmp application/muhkuh_version.h || cp application/muhkuh_version.h.tmp application/muhkuh_version.h

m4 -E <application/templates/muhkuh.rc.m4 >application/muhkuh.rc.tmp
cmp -s application/muhkuh.rc.tmp application/muhkuh.rc || cp application/muhkuh.rc.tmp application/muhkuh.rc


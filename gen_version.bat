m4 -E <application\templates\muhkuh_version.h.m4 >application\muhkuh_version.h.tmp
cmp -s application\muhkuh_version.h.tmp application\muhkuh_version.h || copy application\muhkuh_version.h.tmp application\muhkuh_version.h

m4 -E <application\templates\muhkuh.rc.m4 >application\muhkuh.rc.tmp
cmp -s application\muhkuh.rc.tmp application\muhkuh.rc || copy application\muhkuh.rc.tmp application\muhkuh.rc


m4 -E <regkuh\templates\regkuh_version.h.m4 >regkuh\regkuh_version.h.tmp
cmp -s regkuh\regkuh_version.h.tmp regkuh\regkuh_version.h || copy regkuh\regkuh_version.h.tmp regkuh\regkuh_version.h

m4 -E <regkuh\templates\regkuh.rc.m4 >regkuh\regkuh.rc.tmp
cmp -s regkuh\regkuh.rc.tmp regkuh\regkuh.rc || copy regkuh\regkuh.rc.tmp regkuh\regkuh.rc


m4 -E <serverkuh\templates\serverkuh_version.h.m4 >serverkuh\serverkuh_version.h.tmp
cmp -s serverkuh\serverkuh_version.h.tmp serverkuh\serverkuh_version.h || copy serverkuh\serverkuh_version.h.tmp serverkuh\serverkuh_version.h

m4 -E <serverkuh\templates\serverkuh.rc.m4 >serverkuh\serverkuh.rc.tmp
cmp -s serverkuh\serverkuh.rc.tmp serverkuh\serverkuh.rc || copy serverkuh\serverkuh.rc.tmp serverkuh\serverkuh.rc

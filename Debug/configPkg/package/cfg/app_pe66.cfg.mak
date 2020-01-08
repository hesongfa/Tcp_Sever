# invoke SourceDir generated makefile for app.pe66
app.pe66: .libraries,app.pe66
.libraries,app.pe66: package/cfg/app_pe66.xdl
	$(MAKE) -f F:\SYSBIOS\Application\NDK_TCPCopy/src/makefile.libs

clean::
	$(MAKE) -f F:\SYSBIOS\Application\NDK_TCPCopy/src/makefile.libs clean


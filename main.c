#include <sys/utsname.h>

#include <stdio.h>



int main(){
	
	struct utsname info;
	
	uname(&info);
	
	printf("Sistema %s %s %s versao %s em %s", info.sysname, info.nodename, info.release, info.version, info.machine);

}

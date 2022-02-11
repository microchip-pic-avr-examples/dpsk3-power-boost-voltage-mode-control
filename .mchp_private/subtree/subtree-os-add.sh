#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
echo Adding subtree repository 'subrepo-os' ro project repository...
git remote add subrepo-os https://bitbucket.microchip.com/scm/mcu16asmpsl/subrepo-rtos-6g2.git
echo Adding subtree repository complete
echo 
echo Downloading subtree contents into project repository...
git subtree add --prefix="dpsk_boost_vmc.X/sources/os" subrepo-os main --squash 
echo Download source files complete
echo
echo Press Enter to exit
read

#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git remote add subrepo-boost https://bitbucket.microchip.com/scm/mcu16asmpsl/subrepo-boost-converter.git
git subtree add --prefix="dpsk_vmc.X/sources/pwr_control/devices/boost" subrepo-boost main --squash
echo Press Enter to exit
read

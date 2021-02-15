#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git remote add subrepo-boost https://bitbucket.microchip.com/scm/mcu16asmpsl/subrepo-boost-converter.git
git subtree add --prefix="dpsk_boost_vmc.X/sources/power_control/devices" subrepo-boost main --squash
echo Press Enter to exit
read

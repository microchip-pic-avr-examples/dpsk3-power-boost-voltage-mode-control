#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
git subtree pull --prefix="dpsk_boost_vmc.X/sources/power_control/devices" subrepo-boost main --squash 
echo Press Enter to exit
read

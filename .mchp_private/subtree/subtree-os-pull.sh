#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
echo Pulling changes from subtree 'subrepo-os' branch 'main' into recently checked out working branch...
git subtree pull --prefix="dpsk_boost_vmc.X/sources/os" subrepo-os main --squash 
echo Pull complete
echo
echo Press Enter to exit
read

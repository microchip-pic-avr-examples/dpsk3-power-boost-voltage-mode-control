#!/bin/sh
echo $SSH_AUTH_SOCK
cd ../../
echo Pushing changes to subtree 'subrepo-os' branch 'version-update' from recently checked out working branch...
git subtree push --prefix="dpsk_boost_vmc.X/sources/os" subrepo-os feature/version-update --squash 
echo Pushing changes to subtree directory complete
echo
echo Press Enter to exit
read

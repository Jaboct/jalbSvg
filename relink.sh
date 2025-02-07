#! /bin/bash
# -x

# jalbSvg has 2 testEnv (runnable) Layouts, jalbSvg and jalbJvg.

# set working dir the dir of this file.

projName=jalbSvg

workspaceDir=~/workspace/jHigh
testEnvDir=~/workspace/jHigh/testEnv
modCoreDir=~/programs/modCore/
rm $testEnvDir/lay/jh/$projName

# make sure these exist as to not make dead links.
ln -s $workspaceDir/$projName/lay/$projName $testEnvDir/lay/jh/$projName
ln -s $workspaceDir/$projName/lay/jalbJvg $testEnvDir/lay/jh/jalbJvg

ln -s $workspaceDir/$projName/$projName $modCoreDir/lay/jh/$projName




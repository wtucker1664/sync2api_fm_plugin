#!/bin/bash
############

cd "`dirname \"$0\"`"

DAFolder="DA"
TempFolder="Temp"
ProductName="24U FM Template"
ProductVersion="2.2"
ArchiveName="24uFMTemplate22.zip"

FMTFolder="${ProductName} ${ProductVersion}"

#clean up
cd "../${TempFolder}"
if [ -d "${FMTFolder}" ]; then
    echo "${FMTFolder} found. Deleting..."
    rm -rf "${FMTFolder}"
fi

#create temporary direcory structure
echo "Creating \"${FMTFolder}\" in Temp folder"
mkdir "${FMTFolder}"
cd "${FMTFolder}"

#Copy needed files
echo "Coping files needed for DA"
ditto "../../Documentation/" "Documentation/"
mkdir Output
ditto "../../Projects/" "Projects/"
ditto "../../Sources/" "Sources/"
ditto "../../Support/" "Support/"
mkdir Temp

#delete files not to be in DA
echo "Deleting unnecessary files"
rm -rf "Support/FMPluginSDK"
mv -f "Support/FMPlugInSDKp" "Support/FMPlugInSDK"
rm -rf Output/*Debug.*
rm -f Projects/DAC*.*
rm -f Projects/XCode/FMTemplate.XC23.xcodeproj/*.mode1
rm -f Projects/XCode/FMTemplate.XC23.xcodeproj/*.pbxuser
rm -f Documentation/*Spec*.txt
rm -f Documentation/*.tif

#delete .DS_Store files
rm -f Documentation/.DS_Store
rm -f Output/.DS_Store
rm -f Projects/.DS_Store
rm -f Projects/XCode/.DS_Store
rm -f Projects/VisualStudio/.DS_Store
rm -f Sources/.DS_Store
rm -f Support/.DS_Store
rm -f Support/FMPluginSDK/.DS_Store
rm -f Support/FMPluginSDK/Libraries/.DS_Store
rm -f Support/FMPluginSDK/Headers/.DS_Store
rm -f Support/FMPluginSDK/Headers/FMWrapper/.DS_Store
rm -f Support/FMTemplate/.DS_Store
rm -f Support/VisualStudio/.DS_Store
rm -f Support/XCode/.DS_Store

#create archive to DA
echo "Creating *.zip archive in DA folder"
cd ..
rm -f "../${DAFolder}/${ArchiveName}"
ditto -c -k --keepParent --sequesterRsrc "${FMTFolder}" "../${DAFolder}/${ArchiveName}"

#delete temporary directory
echo "Deleting \"${FMTFolder}\" in Temp folder"
rm -rf "${FMTFolder}"
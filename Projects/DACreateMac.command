#!/bin/bash
############

cd "`dirname \"$0\"`"

DAFolder="DA"
TempFolder="Temp"
ProductName="24U FM Template"
ProductVersion="2.2"

FMTFolder="${ProductName} ${ProductVersion}"

#clean up
cd "../${TempFolder}"
if [ -d "${ProductName}" ]; then
    echo "${ProductName} found. Deleting..."
    rm -rf "${ProductName}"
fi

#create temporary direcory structure
echo "Creating \"${ProductName}\" in Temp folder"
mkdir "${ProductName}"
cd "${ProductName}"
echo "Creating \"${FMTFolder}\" in \"${ProductName}\" folder"
mkdir "${FMTFolder}"
cd "${FMTFolder}"

#Copy needed files
echo "Coping files needed for DA"
ditto "../../../Documentation/" "../Documentation/"
mkdir Output
ditto "../../../Projects/" "Projects/"
ditto "../../../Sources/" "Sources/"
ditto "../../../Support/" "Support/"
mkdir Temp

#delete .DS_Store files
rm -f ../../.DS_Store
rm -f ../.DS_Store
rm -f .DS_Store
rm -f ../Documentation/.DS_Store
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

#copy back-uped .DS_Store
DSBackUp="../../../Research/DAMac_DS_Backup"
ditto "${DSBackUp}/pre.store" ../../.DS_Store
ditto "${DSBackUp}/base.store" ../.DS_Store
ditto "${DSBackUp}/doc.store" ../Documentation/.DS_Store
ditto "${DSBackUp}/base2.store" .DS_Store
ditto "${DSBackUp}/proj.store" Projects/.DS_Store
ditto "${DSBackUp}/proj_vs.store" Projects/VisualStudio/.DS_Store
ditto "${DSBackUp}/proj_xcode.store" Projects/XCode/.DS_Store
ditto "${DSBackUp}/sources.store" Sources/.DS_Store
ditto "${DSBackUp}/supp.store" Support/.DS_Store
ditto "${DSBackUp}/supp_sdk.store" Support/FMPlugInSDK/.DS_Store
ditto "${DSBackUp}/supp_sdk_h1.store" Support/FMPlugInSDK/Headers/.DS_Store
ditto "${DSBackUp}/supp_sdk_h2.store" Support/FMPlugInSDK/Headers/FMWrapper/.DS_Store
ditto "${DSBackUp}/supp_fmt.store" Support/FMTemplate/.DS_Store
ditto "${DSBackUp}/supp_vs.store" Support/VisualStudio/.DS_Store
ditto "${DSBackUp}/supp_xcode.store" Support/XCode/.DS_Store


#delete files not to be in DA
echo "Deleting unnecessary files"
rm -rf "Support/FMPluginSDK"
mv -f "Support/FMPlugInSDKp" "Support/FMPlugInSDK"
rm -rf Output/*Debug.*
rm -f Projects/DAC*.*
rm -f Projects/XCode/FMTemplate.XC23.xcodeproj/*.mode1
rm -f Projects/XCode/FMTemplate.XC23.xcodeproj/*.pbxuser
rm -f ../Documentation/*Spec*.txt
mkdir ../.bg
mv ../Documentation/bgpicture.tif ../.bg/

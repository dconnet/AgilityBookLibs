#!/usr/bin/env python
# Generate Mac App packaging files: Info.plist, version.plist, PkgInfo
#
# Revision History
# 2022-07-27 Created
"""GenContents.py [-i icns] [-l lang] [-e ext] [-d desc] -n name -v version -c copyright contents
-i icns:      File name
-l lang:      Localization id
-e ext:       File extension
-d desc:      File extension description
-n name:      App name
-v version:   Version string
-c copyright: Full copyright string
contents:     Path to Bundle.app/Contents (where to create files)
"""

# icns
#  Info.plist: CFBundleIconFile, CFBundleTypeIconFile
# lang
#  Info.plist: CFBundleLocalizations
# ext
#  Info.plist: CFBundleTypeExtensions
# desc
#  Info.plist: CFBundleTypeName
# name
#  Info.plist: CFBundleExecutable, CFBundleGetInfoString, CFBundleIdentifier, CFBundleName
#  version.plist: ProjectName
# version
#  Info.plist: CFBundleGetInfoString, CFBundleLongVersionString, CFBundleShortVersionString, CFBundleVersion
#  version.plist: BuildVersion, CFBundleShortVersionString, CFBundleVersion
# copyright
#  Info.plist: CFBundleGetInfoString, CFBundleLongVersionString, NSHumanReadableCopyrigh

import getopt
import os
import sys


def GenInfo(contents, name, shortVer, ver, copyright, icnsFile, loc, ext, extDesc):
	filename = contents + '/Info.plist'
	output = open(filename, 'w', newline='\n')
	if not output:
		print('ERROR: Failed to open "' + filename + '"')
		return False
	print('<?xml version="1.0" encoding="UTF-8"?>', file=output)
	print('<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">', file=output)
	print('<plist version="1.0">', file=output)
	print('<dict>', file=output)
	print('\t<key>CFBundleDevelopmentRegion</key>', file=output)
	print('\t<string>English</string>', file=output)
	print('\t<key>CFBundleExecutable</key>', file=output)
	print('\t<string>' + name + '</string>', file=output)
	print('\t<key>CFBundleGetInfoString</key>', file=output)
	print('\t<string>' + name + ' Version ' + ver + ', ' + copyright + '</string>', file=output)
	if len(icnsFile) > 0:
		print('\t<key>CFBundleIconFile</key>', file=output)
		print('\t<string>' + icnsFile + '</string>', file=output)
	print('\t<key>CFBundleIdentifier</key>', file=output)
	print('\t<string>com.agilityrecordbook.' + name + '</string>', file=output)
	print('\t<key>CFBundleInfoDictionaryVersion</key>', file=output)
	print('\t<string>6.0</string>', file=output)
	if len(loc) > 0:
		print('\t<key>CFBundleLocalizations</key>', file=output)
		print('\t<array>', file=output)
		for l in loc:
			print('\t\t<string>' + l + '</string>', file=output)
		print('\t</array>', file=output)
	if len(ext) > 0:
		print('\t<key>CFBundleDocumentTypes</key>', file=output)
		print('\t<array>', file=output)
		print('\t\t<dict>', file=output)
		print('\t\t\t<key>CFBundleTypeExtensions</key>', file=output)
		print('\t\t\t<array>', file=output)
		print('\t\t\t\t<string>' + ext + '</string>', file=output)
		print('\t\t\t</array>', file=output)
		if len(icnsFile) > 0:
			print('\t\t\t<key>CFBundleTypeIconFile</key>', file=output)
			print('\t\t\t<string>' + icnsFile + '</string>', file=output)
		if len(extDesc) > 0:
			print('\t\t\t<key>CFBundleTypeName</key>', file=output)
			print('\t\t\t<string>' + extDesc + '</string>', file=output)
		print('\t\t\t<key>CFBundleTypeRole</key>', file=output)
		print('\t\t\t<string>Editor</string>', file=output)
		print('\t\t\t<key>LSIsAppleDefaultForType</key>', file=output)
		print('\t\t\t<true/>', file=output)
		print('\t\t\t<key>LSTypeIsPackage</key>', file=output)
		print('\t\t\t<false/>', file=output)
		print('\t\t</dict>', file=output)
		print('\t</array>', file=output)
	print('\t<key>CFBundleLongVersionString</key>', file=output)
	print('\t<string>' + ver + ', ' + copyright + '</string>', file=output)
	print('\t<key>CFBundleName</key>', file=output)
	print('\t<string>' + name + '</string>', file=output)
	print('\t<key>CFBundlePackageType</key>', file=output)
	print('\t<string>APPL</string>', file=output)
	print('\t<key>CFBundleShortVersionString</key>', file=output)
	print('\t<string>' + shortVer + '</string>', file=output)
	print('\t<key>CFBundleVersion</key>', file=output)
	print('\t<string>' + ver + '</string>', file=output)
	print('\t<key>NSHumanReadableCopyright</key>', file=output)
	print('\t<string>' + copyright + '</string>', file=output)
	print('\t<key>ATSApplicationFontsPath</key>', file=output)
	print('\t<string>Fonts</string>', file=output)
	print('\t<key>NSPrincipalClass</key>', file=output)
	print('\t<string>wxNSApplication</string>', file=output)
	print('</dict>', file=output)
	print('</plist>', file=output)
	return True


def GenVersion(contents, name, ver):
	filename = contents + '/version.plist'
	output = open(filename, 'w', newline='\n')
	if not output:
		print('ERROR: Failed to open "' + filename + '"')
		return False
	print('<?xml version="1.0" encoding="UTF-8"?>', file=output)
	print('<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">', file=output)
	print('<plist version="1.0">', file=output)
	print('<dict>', file=output)
	print('\t<key>BuildVersion</key>', file=output)
	print('\t<string>' + ver + '</string>', file=output)
	print('\t<key>CFBundleShortVersionString</key>', file=output)
	print('\t<string>' + ver + '</string>', file=output)
	print('\t<key>CFBundleVersion</key>', file=output)
	print('\t<string>' + ver + '</string>', file=output)
	print('\t<key>ProjectName</key>', file=output)
	print('\t<string>' + name + '</string>', file=output)
	print('</dict>', file=output)
	print('</plist>', file=output)
	return True


def GenPkgInfo(contents):
	filename = contents + '/PkgInfo'
	output = open(filename, 'w')
	if not output:
		print('ERROR: Failed to open "' + filename + '"')
		return False
	# No newline
	output.write('APPL????')
	output.close()
	return True


def main():
	icnsFile = ''
	loc = set()
	ext = ''
	extDesc = ''
	name = ''
	ver = ''
	copyright = ''

	try:
		opts, args = getopt.getopt(sys.argv[1:], 'i:l:e:d:n:v:c:')
	except getopt.error as msg:
		print(msg)
		print('Usage:', __doc__)
		return 1
	for o, a in opts:
		if '-i' == o:
			icnsFile = a
		elif '-l' == o:
			loc.add(a)
		elif '-e' == o:
			ext = a
		elif '-d' == o:
			extDesc = a
		elif '-n' == o:
			name = a
		elif '-v' == o:
			ver = a
		elif '-c' == o:
			copyright = a
	if not len(args) == 1:
		print('Usage:', __doc__)
		return 1

	if not os.access(args[0], os.F_OK):
		print('ERROR: "' + args[0] + '" does not exist!')
		print('Usage:', __doc__)
		return 1;

	if len(name) == 0:
		print('ERROR: Must specify app name (-n)')
		print('Usage:', __doc__)
		return 1;

	if len(ver) == 0:
		print('ERROR: Must specify version (-v)')
		print('Usage:', __doc__)
		return 1;
	shortVer = ver

	if len(copyright) == 0:
		print('ERROR: Must specify copyright (-c)')
		print('Usage:', __doc__)
		return 1;

	if len(loc) > 0:
		loc.add('en')

	# Reduce version to 3 parts (per CFBundleShortVersionString)
	parts = ver.split('.')
	if len(parts) > 3:
		shortVer = parts[0] + '.' + parts[1] + '.' + parts[2]

	if not GenInfo(args[0], name, shortVer, ver, copyright, icnsFile, loc, ext, extDesc):
		return 1
	if not GenVersion(args[0], name, shortVer):
		return 1
	if not GenPkgInfo(args[0]):
		return 1
	return 0


if __name__ == '__main__':
	sys.exit(main())

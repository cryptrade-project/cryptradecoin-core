
Debian
====================
This directory contains files used to package cryptradecoind/cryptradecoin-qt
for Debian-based Linux systems. If you compile cryptradecoind/cryptradecoin-qt yourself, there are some useful files here.

## cryptradecoin: URI support ##


cryptradecoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install cryptradecoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your cryptradecoinqt binary to `/usr/bin`
and the `../../share/pixmaps/cryptradecoin128.png` to `/usr/share/pixmaps`

cryptradecoin-qt.protocol (KDE)


Atril
==================================================
Atril is a simple multi-page document viewer. It can display and print PostScript (PS), Encapsulated PostScript (EPS), DJVU, DVI, XPS and Portable Document Format (PDF) files. When supported by the document, it also allows searching for text, copying text to the clipboard, hypertext navigation, and table-of-contents bookmarks. Atril is a fork of Evince.

This software is licensed under the GNU GPL. For more on the license, see COPYING.

Atril Requirements
==================================================
* [MATE Platform libraries](https://github.com/Libre-MATE/mate-desktop/)
* [Poppler](https://poppler.freedesktop.org/) for PDF viewing
* [GhostScript](https://www.ghostscript.com/) for PostScript viewing

Atril Optional Backend Libraries
==================================================
* [DjVuLibre](http://djvu.sourceforge.net/) for DjVu viewing
* [RAR](https://www.rarlab.com/) for viewing CBR comics
* [libgxps](https://wiki.gnome.org/Projects/libgxps) for XPS documents
* [minizip-compat](https://www.zlib.net/) for EPUB documents

Atril Requirements to Run Tests
==================================================
* [python-dogtail](https://gitlab.com/dogtail/dogtail)
* [python-pyatspi2](https://download.gnome.org/sources/pyatspi/)
* git installed on your system

Atril Compilation
==================================================
* git submodule init
* git submodule update --remote --recursive
* ./autogen.sh
* make

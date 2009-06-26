## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(datadir)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(OPENSTREETMAP_GPS_MAP_CFLAGS) \
        -DLIBSOUP2_2 -DGLIB2_12

AM_CFLAGS =\
	 -Wall\
	 -g

INCLUDES  = -I/usr/include -I/usr/include/glib-2.0/ -I/usr/include/glib-2.0/glib/ -I/usr/include/gtk-2.0/  -I/usr/include/gtk-2.0/gdk -I/usr/include/cairo -I/usr/lib/glib-2.0/include/ -I/usr/include/pango-1.0/ -I/usr/lib/gtk-2.0/include/ -I /usr/include/atk-1.0/ -I/usr/include/libsoup-2.2/

bin_PROGRAMS = openstreetmap-gps-map

openstreetmap_gps_map_SOURCES = \
	main.c

openstreetmap_gps_map_DEPENDENCIES = \
	libosmgpsmap.la

openstreetmap_gps_map_LDFLAGS = \
	-losmgpsmap -lgthread-2.0 
LIBS = `pkg-config --libs gtk+-2.0` `pkg-config --libs libsoup-2.2`
openstreetmap_gps_map_LDADD = $(OPENSTREETMAP_GPS_MAP_LIBS)

lib_LTLIBRARIES = \
	libosmgpsmap.la

libosmgpsmap_la_SOURCES = \
	converter.c \
	osm-gps-map.c

libosmgpsmap_la_CFLAGS = \
	-DG_LOG_DOMAIN=\"OsmGpsMap\"

libosmgpsmapincdir = $(includedir)/osmgpsmap
libosmgpsmapinc_HEADERS = \
	osm-gps-map.h

noinst_HEADERS = \
	converter.h \
	osm-gps-map-types.h

EXTRA_DIST = \
	poi.png

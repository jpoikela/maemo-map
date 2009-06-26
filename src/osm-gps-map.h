/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et sw=4 ts=4 cino=t0,(0: */
/*
 * osm-gps-map.h
 * Copyright (C) Marcus Bauer 2008 <marcus.bauer@gmail.com>
 * Copyright (C) John Stowers 2009 <john.stowers@gmail.com>
 *
 * Contributions by
 * Everaldo Canuto 2009 <everaldo.canuto@gmail.com>
 *
 * osm-gps-map.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * osm-gps-map.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _OSM_GPS_MAP_H_
#define _OSM_GPS_MAP_H_

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

G_BEGIN_DECLS

#define OSM_TYPE_GPS_MAP             (osm_gps_map_get_type ())
#define OSM_GPS_MAP(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), OSM_TYPE_GPS_MAP, OsmGpsMap))
#define OSM_GPS_MAP_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), OSM_TYPE_GPS_MAP, OsmGpsMapClass))
#define OSM_IS_GPS_MAP(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OSM_TYPE_GPS_MAP))
#define OSM_IS_GPS_MAP_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), OSM_TYPE_GPS_MAP))
#define OSM_GPS_MAP_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), OSM_TYPE_GPS_MAP, OsmGpsMapClass))

#ifdef LIBSOUP2_2
#define SOUP_TYPE_URI  (soup_uri_get_type())
#define SOUP_URI(obj)  (G_TYPE_CHECK_INSTANCE_CAST ((obj), SOUP_TYPE_URI, SoupUri))
#define SOUP_URI_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST ((klass), SOUP_TYPE_URI, SoupUriClass))
#endif

typedef struct _OsmGpsMapClass OsmGpsMapClass;
typedef struct _OsmGpsMap OsmGpsMap;
typedef struct _OsmGpsMapPrivate OsmGpsMapPrivate;

struct _OsmGpsMapClass
{
    GtkDrawingAreaClass parent_class;
};

struct _OsmGpsMap
{
    GtkDrawingArea parent_instance;
    OsmGpsMapPrivate *priv;
};

typedef struct {
    float rlat;
    float rlon;
} coord_t;

//http://www.internettablettalk.com/forums/showthread.php?t=5209
//https://garage.maemo.org/plugins/scmsvn/viewcvs.php/trunk/src/maps.c
//http://www.ponies.me.uk/maps/GoogleTileUtils.java
//http://www.mgmaps.com/cache/MapTileCacher.perl
#define MAP_SOURCE_NOKIAOVIMAP              "http://maptile.svc.nokia.com.edgesuite.net/maptiler/maptile/newest/normal.day/#Z/#X/#Y/256/png"
#define MAP_SOURCE_OPENSTREETMAP            "http://tile.openstreetmap.org/#Z/#X/#Y.png"
#define MAP_SOURCE_OPENSTREETMAP_RENDERER   "http://tah.openstreetmap.org/Tiles/tile/#Z/#X/#Y.png"
#define MAP_SOURCE_OPENAERIALMAP            "http://tile.openaerialmap.org/tiles/1.0.0/openaerialmap-900913/#Z/#X/#Y.jpg"
#define MAP_SOURCE_GOOGLE_MAPS              "http://mt#R.google.com/mt?x=#X&y=#Y&zoom=#S"
//No longer working
//#define MAP_SOURCE_GOOGLE_HYBRID          "http://mt#R.google.com/mt?n=404&v=w2t.99&x=#X&y=#Y&zoom=#S"
#define MAP_SOURCE_GOOGLE_HYBRID            "http://mt#R.google.com/mt?x=#X&y=#Y&zoom=#S"
#define MAP_SOURCE_GOOGLE_SATTELITE         "http://khm#R.google.com/kh?n=404&v=32&x=#X&y=#Y&z=#Z"
#define MAP_SOURCE_GOOGLE_SATTELITE_QUAD    "http://khm#R.google.com/kh?n=404&v=3&t=#Q"
#define MAP_SOURCE_MAPS_FOR_FREE            "http://maps-for-free.com/layer/relief/z#Z/row#Y/#Z_#X-#Y.jpg"
#define MAP_SOURCE_VIRTUAL_EARTH_SATTELITE  "http://a#R.ortho.tiles.virtualearth.net/tiles/a#W.jpeg?g=50"

GType osm_gps_map_get_type (void) G_GNUC_CONST;

void osm_gps_map_download_maps (OsmGpsMap *map, coord_t *pt1, coord_t *pt2, int zoom_start, int zoom_end);
void osm_gps_map_get_bbox (OsmGpsMap *map, coord_t *pt1, coord_t *pt2);
void osm_gps_map_set_mapcenter (OsmGpsMap *map, float latitude, float longitude, int zoom);
void osm_gps_map_set_center (OsmGpsMap *map, float latitude, float longitude);
int osm_gps_map_set_zoom (OsmGpsMap *map, int zoom);
void osm_gps_map_add_track (OsmGpsMap *map, GSList *track);
void osm_gps_map_clear_tracks (OsmGpsMap *map);
void osm_gps_map_add_image (OsmGpsMap *map, float latitude, float longitude, GdkPixbuf *image);
void osm_gps_map_clear_images (OsmGpsMap *map);
void osm_gps_map_osd_speed (OsmGpsMap *map, float speed);
void osm_gps_map_draw_gps (OsmGpsMap *map, float latitude, float longitude, float heading);
void osm_gps_map_clear_gps (OsmGpsMap *map);
coord_t osm_gps_map_get_co_ordinates (OsmGpsMap *map, int pixel_x, int pixel_y);
GtkWidget * osm_gps_map_new(void);
void osm_gps_map_screen_to_geographic (OsmGpsMap *map,
                                       gint pixel_x, gint pixel_y,
                                       gfloat *latitude, gfloat *longitude);
void osm_gps_map_geographic_to_screen (OsmGpsMap *map,
                                       gfloat latitude, gfloat longitude,
                                       gint *pixel_x, gint *pixel_y);
void osm_gps_map_scroll (OsmGpsMap *map, gint dx, gint dy);

G_END_DECLS

#endif /* _OSM_GPS_MAP_H_ */

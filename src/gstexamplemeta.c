#include "gstexamplemeta.h"

/*
 * Example usage:
 * #include <gstexamplemeta.h>
 *
 * For creating meta:
 * GstExampleMeta *meta = gst_buffer_add_example_meta  (outbuf, self->count, 2);
 *
 * For reading/changing:
 * GstExampleMeta *meta = gst_buffer_get_example_meta  (outbuf); 
 * if (!meta)
 * {
 *         GST_WARNING("meta was null");
 * }
 * else
 * {
 *         GST_WARNING("Reading mdi: x=%d, y=%d", meta->x, meta->y);
 *         meta->y = meta->x * 5
 * }
 */

static gboolean
gst_example_meta_init (GstMeta * meta, gpointer params, GstBuffer * buffer)
{
	GstExampleMeta *emeta = (GstExampleMeta *) meta;

    emeta->x = 0;
    emeta->y = 0;

	return TRUE;
}

static gboolean
gst_example_meta_transform (GstBuffer * dest, GstMeta * meta,
		GstBuffer * buffer, GQuark type, gpointer data)
{
	GstExampleMeta *dmeta, *smeta;;

	smeta = (GstExampleMeta *) meta;

    dmeta =
            (GstExampleMeta *) gst_buffer_add_meta (dest, GST_EXAMPLE_META_INFO,
            NULL);

    if (!dmeta)
        return FALSE;

    GST_DEBUG ("copy example metadata");
    dmeta->x = smeta->x;
    dmeta->y = smeta->y;
	return TRUE;
}

GType
gst_example_meta_api_get_type (void)
{
	static volatile GType type = 0;
	static const gchar *tags[] = { };

	if (g_once_init_enter (&type)) {
		GType _type = gst_meta_api_type_register ("GstExampleMetaAPI", tags);
		g_once_init_leave (&type, _type);
	}
	return type;
}

/* example metadata */
const GstMetaInfo *
gst_example_meta_get_info (void)
{
	static const GstMetaInfo *example_meta_info = NULL;

	if (g_once_init_enter ((GstMetaInfo **) & example_meta_info)) {
		const GstMetaInfo *meta =
				gst_meta_register (GST_EXAMPLE_META_API_TYPE, "GstExampleMeta",
				sizeof (GstExampleMeta), (GstMetaInitFunction) gst_example_meta_init,
				(GstMetaFreeFunction) NULL, gst_example_meta_transform);
		g_once_init_leave ((GstMetaInfo **) & example_meta_info,
				(GstMetaInfo *) meta);
	}
	return example_meta_info;
}

GstExampleMeta *
gst_buffer_add_example_meta (GstBuffer * buffer, gint x, gint y)
{
	GstExampleMeta *meta;
	guint i;

	meta =
			(GstExampleMeta *) gst_buffer_add_meta (buffer, GST_EXAMPLE_META_INFO, NULL);

	if (!meta)
		return NULL;

	meta->x = x;
	meta->y = y;
	
	return meta;
}

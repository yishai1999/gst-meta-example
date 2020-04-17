#ifndef __GST_EXAMPLE_META_H__
#define __GST_EXAMPLE_META_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_EXAMPLE_META_API_TYPE (gst_example_meta_api_get_type())
#define GST_EXAMPLE_META_INFO  (gst_example_meta_get_info())
typedef struct _GstExampleMeta GstExampleMeta;

struct _GstExampleMeta {
  GstMeta            meta;

  gint x;
  gint y;
};

GType gst_example_meta_api_get_type (void);

const GstMetaInfo * gst_example_meta_get_info (void);

#define gst_buffer_get_example_meta(buffer) \
  ((GstExampleMeta*)gst_buffer_get_meta((buffer),GST_EXAMPLE_META_API_TYPE))

GstExampleMeta * gst_buffer_add_example_meta  (GstBuffer *buffer, gint x, gint y);

G_END_DECLS

#endif /* __GST_EXAMPLE_META_H__ */

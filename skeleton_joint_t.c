/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#include <string.h>
#include "skeleton_joint_t.h"

static int __skeleton_joint_t_hash_computed;
static int64_t __skeleton_joint_t_hash;

int64_t __skeleton_joint_t_hash_recursive(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == __skeleton_joint_t_get_hash)
            return 0;

    __lcm_hash_ptr cp;
    cp.parent =  p;
    cp.v = (void*)__skeleton_joint_t_get_hash;
    (void) cp;

    int64_t hash = 0x9ed48f65609215a0LL
         + __int32_t_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
         + __int32_t_hash_recursive(&cp)
        ;

    return (hash<<1) + ((hash>>63)&1);
}

int64_t __skeleton_joint_t_get_hash(void)
{
    if (!__skeleton_joint_t_hash_computed) {
        __skeleton_joint_t_hash = __skeleton_joint_t_hash_recursive(NULL);
        __skeleton_joint_t_hash_computed = 1;
    }

    return __skeleton_joint_t_hash;
}

int __skeleton_joint_t_encode_array(void *buf, int offset, int maxlen, const skeleton_joint_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].x), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].y), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].z), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].screen_x), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &(p[element].screen_y), 1);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int skeleton_joint_t_encode(void *buf, int offset, int maxlen, const skeleton_joint_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __skeleton_joint_t_get_hash();

    thislen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    thislen = __skeleton_joint_t_encode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int __skeleton_joint_t_encoded_array_size(const skeleton_joint_t *p, int elements)
{
    int size = 0, element;
    for (element = 0; element < elements; element++) {

        size += __int32_t_encoded_array_size(&(p[element].x), 1);

        size += __int32_t_encoded_array_size(&(p[element].y), 1);

        size += __int32_t_encoded_array_size(&(p[element].z), 1);

        size += __int32_t_encoded_array_size(&(p[element].screen_x), 1);

        size += __int32_t_encoded_array_size(&(p[element].screen_y), 1);

    }
    return size;
}

int skeleton_joint_t_encoded_size(const skeleton_joint_t *p)
{
    return 8 + __skeleton_joint_t_encoded_array_size(p, 1);
}

int __skeleton_joint_t_decode_array(const void *buf, int offset, int maxlen, skeleton_joint_t *p, int elements)
{
    int pos = 0, thislen, element;

    for (element = 0; element < elements; element++) {

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].x), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].y), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].z), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].screen_x), 1);
        if (thislen < 0) return thislen; else pos += thislen;

        thislen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &(p[element].screen_y), 1);
        if (thislen < 0) return thislen; else pos += thislen;

    }
    return pos;
}

int __skeleton_joint_t_decode_array_cleanup(skeleton_joint_t *p, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int32_t_decode_array_cleanup(&(p[element].x), 1);

        __int32_t_decode_array_cleanup(&(p[element].y), 1);

        __int32_t_decode_array_cleanup(&(p[element].z), 1);

        __int32_t_decode_array_cleanup(&(p[element].screen_x), 1);

        __int32_t_decode_array_cleanup(&(p[element].screen_y), 1);

    }
    return 0;
}

int skeleton_joint_t_decode(const void *buf, int offset, int maxlen, skeleton_joint_t *p)
{
    int pos = 0, thislen;
    int64_t hash = __skeleton_joint_t_get_hash();

    int64_t this_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (this_hash != hash) return -1;

    thislen = __skeleton_joint_t_decode_array(buf, offset + pos, maxlen - pos, p, 1);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int skeleton_joint_t_decode_cleanup(skeleton_joint_t *p)
{
    return __skeleton_joint_t_decode_array_cleanup(p, 1);
}

int __skeleton_joint_t_clone_array(const skeleton_joint_t *p, skeleton_joint_t *q, int elements)
{
    int element;
    for (element = 0; element < elements; element++) {

        __int32_t_clone_array(&(p[element].x), &(q[element].x), 1);

        __int32_t_clone_array(&(p[element].y), &(q[element].y), 1);

        __int32_t_clone_array(&(p[element].z), &(q[element].z), 1);

        __int32_t_clone_array(&(p[element].screen_x), &(q[element].screen_x), 1);

        __int32_t_clone_array(&(p[element].screen_y), &(q[element].screen_y), 1);

    }
    return 0;
}

skeleton_joint_t *skeleton_joint_t_copy(const skeleton_joint_t *p)
{
    skeleton_joint_t *q = (skeleton_joint_t*) malloc(sizeof(skeleton_joint_t));
    __skeleton_joint_t_clone_array(p, q, 1);
    return q;
}

void skeleton_joint_t_destroy(skeleton_joint_t *p)
{
    __skeleton_joint_t_decode_array_cleanup(p, 1);
    free(p);
}

int skeleton_joint_t_publish(lcm_t *lc, const char *channel, const skeleton_joint_t *p)
{
      int max_data_size = skeleton_joint_t_encoded_size (p);
      uint8_t *buf = (uint8_t*) malloc (max_data_size);
      if (!buf) return -1;
      int data_size = skeleton_joint_t_encode (buf, 0, max_data_size, p);
      if (data_size < 0) {
          free (buf);
          return data_size;
      }
      int status = lcm_publish (lc, channel, buf, data_size);
      free (buf);
      return status;
}

struct _skeleton_joint_t_subscription_t {
    skeleton_joint_t_handler_t user_handler;
    void *userdata;
    lcm_subscription_t *lc_h;
};
static
void skeleton_joint_t_handler_stub (const lcm_recv_buf_t *rbuf,
                            const char *channel, void *userdata)
{
    int status;
    skeleton_joint_t p;
    memset(&p, 0, sizeof(skeleton_joint_t));
    status = skeleton_joint_t_decode (rbuf->data, 0, rbuf->data_size, &p);
    if (status < 0) {
        fprintf (stderr, "error %d decoding skeleton_joint_t!!!\n", status);
        return;
    }

    skeleton_joint_t_subscription_t *h = (skeleton_joint_t_subscription_t*) userdata;
    h->user_handler (rbuf, channel, &p, h->userdata);

    skeleton_joint_t_decode_cleanup (&p);
}

skeleton_joint_t_subscription_t* skeleton_joint_t_subscribe (lcm_t *lcm,
                    const char *channel,
                    skeleton_joint_t_handler_t f, void *userdata)
{
    skeleton_joint_t_subscription_t *n = (skeleton_joint_t_subscription_t*)
                       malloc(sizeof(skeleton_joint_t_subscription_t));
    n->user_handler = f;
    n->userdata = userdata;
    n->lc_h = lcm_subscribe (lcm, channel,
                                 skeleton_joint_t_handler_stub, n);
    if (n->lc_h == NULL) {
        fprintf (stderr,"couldn't reg skeleton_joint_t LCM handler!\n");
        free (n);
        return NULL;
    }
    return n;
}

int skeleton_joint_t_subscription_set_queue_capacity (skeleton_joint_t_subscription_t* subs,
                              int num_messages)
{
    return lcm_subscription_set_queue_capacity (subs->lc_h, num_messages);
}

int skeleton_joint_t_unsubscribe(lcm_t *lcm, skeleton_joint_t_subscription_t* hid)
{
    int status = lcm_unsubscribe (lcm, hid->lc_h);
    if (0 != status) {
        fprintf(stderr,
           "couldn't unsubscribe skeleton_joint_t_handler %p!\n", hid);
        return -1;
    }
    free (hid);
    return 0;
}


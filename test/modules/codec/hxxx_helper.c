/*****************************************************************************
 * hxxx_helper.c: hxxx_helper packetizer unit testing
 *****************************************************************************
 * Copyright (C) 2021 VideoLabs, VideoLAN and VLC Authors
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "../../libvlc/test.h"

const char vlc_module_name[] = "hxxx_helper";

#include "../../../modules/packetizer/hxxx_nal.h"
#include "../../../modules/codec/hxxx_helper.h"

const uint8_t test_samples_raw_h264_annexb[] = {
  0x00, 0x00, 0x00, 0x01, 0x67, 0xf4, 0x00, 0x0a, 0x91, 0x9b, 0x2b, 0xd0,
  0x80, 0x00, 0x00, 0x03, 0x00, 0x80, 0x00, 0x00, 0x19, 0x07, 0x89, 0x12,
  0xcb, 0x00, 0x00, 0x01, 0x68, 0xeb, 0xec, 0x44, 0x84, 0x40, 0x00, 0x00,
  0x01, 0x65, 0x88, 0x84, 0x00, 0x37, 0xff, 0xfe, 0xf5, 0xdb, 0xf3, 0x2c,
  0xac, 0x66, 0x67, 0xff, 0x00, 0x00, 0x01, 0x41, 0x9a, 0x24, 0x6c, 0x46,
  0xff, 0xfe, 0xc0 };

const uint8_t test_extradata_raw_h264_annexb[] = {
  0x00, 0x00, 0x00, 0x01, 0x67, 0xf4, 0x00, 0x0a, 0x91, 0x9b, 0x2b, 0xd0,
  0x80, 0x00, 0x00, 0x03, 0x00, 0x80, 0x00, 0x00, 0x19, 0x07, 0x89, 0x12,
  0xcb, 0x00, 0x00, 0x00, 0x01, 0x68, 0xeb, 0xec, 0x44, 0x84, 0x40 };

const uint8_t test_extradata_raw_h264_avc1[] = {
  0x01, 0xf4, 0x00, 0x0a, 0xff, 0xe1, 0x00, 0x15, 0x67, 0xf4, 0x00, 0x0a,
  0x91, 0x9b, 0x2b, 0xd0, 0x80, 0x00, 0x00, 0x03, 0x00, 0x80, 0x00, 0x00,
  0x19, 0x07, 0x89, 0x12, 0xcb, 0x01, 0x00, 0x06, 0x68, 0xeb, 0xec, 0x44,
  0x84, 0x40 };

const uint8_t test_samples_raw_h264_avc1[] = {
  0x00, 0x00, 0x00, 0x15, 0x67, 0xf4, 0x00, 0x0a, 0x91, 0x9b, 0x2b, 0xd0,
  0x80, 0x00, 0x00, 0x03, 0x00, 0x80, 0x00, 0x00, 0x19, 0x07, 0x89, 0x12,
  0xcb, 0x00, 0x00, 0x00, 0x06, 0x68, 0xeb, 0xec, 0x44, 0x84, 0x40, 0x00,
  0x00, 0x00, 0x0f, 0x65, 0x88, 0x84, 0x00, 0x37, 0xff, 0xfe, 0xf5, 0xdb,
  0xf3, 0x2c, 0xac, 0x66, 0x67, 0xff, 0x00, 0x00, 0x00, 0x08, 0x41, 0x9a,
  0x24, 0x6c, 0x46, 0xff, 0xfe, 0xc0 };

const uint8_t test_samples_raw_h265_annexb[] = {
  0x00, 0x00, 0x00, 0x01, 0x40, 0x01, 0x0c, 0x01, 0xff, 0xff, 0x04, 0x08,
  0x00, 0x00, 0x03, 0x00, 0x9e, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00, 0x1e,
  0x95, 0x98, 0x09, 0x00, 0x00, 0x01, 0x42, 0x01, 0x01, 0x04, 0x08, 0x00,
  0x00, 0x03, 0x00, 0x9e, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00, 0x1e, 0x90,
  0x11, 0x08, 0xb2, 0xca, 0xcd, 0x57, 0x95, 0xcd, 0x40, 0x80, 0x80, 0x01,
  0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x19, 0x08, 0x00,
  0x00, 0x01, 0x44, 0x01, 0xc1, 0x73, 0x18, 0x31, 0x08, 0x90, 0x00, 0x00,
  0x01, 0x28, 0x01, 0xaf, 0x19, 0x80, 0xef, 0xef, 0xcb, 0x5f, 0xfe, 0x52,
  0x0b, 0xfe, 0xbb, 0x6d, 0xfd, 0x0f, 0xf8 };

const uint8_t test_samples_raw_h265_hvc1[] = {
  0x00, 0x00, 0x00, 0x17, 0x40, 0x01, 0x0c, 0x01, 0xff, 0xff, 0x04, 0x08,
  0x00, 0x00, 0x03, 0x00, 0x9e, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00, 0x1e,
  0x95, 0x98, 0x09, 0x00, 0x00, 0x00, 0x29, 0x42, 0x01, 0x01, 0x04, 0x08,
  0x00, 0x00, 0x03, 0x00, 0x9e, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00, 0x1e,
  0x90, 0x11, 0x08, 0xb2, 0xca, 0xcd, 0x57, 0x95, 0xcd, 0x40, 0x80, 0x80,
  0x01, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x19, 0x08,
  0x00, 0x00, 0x00, 0x08, 0x44, 0x01, 0xc1, 0x73, 0x18, 0x31, 0x08, 0x90,
  0x00, 0x00, 0x00, 0x12, 0x28, 0x01, 0xaf, 0x19, 0x80, 0xef, 0xef, 0xcb,
  0x5f, 0xfe, 0x52, 0x0b, 0xfe, 0xbb, 0x6d, 0xfd, 0x0f, 0xf8 };

const uint8_t test_extradata_raw_h265_annexb[] = {
  0x00, 0x00, 0x00, 0x01, 0x40, 0x01, 0x0c, 0x01, 0xff, 0xff, 0x04, 0x08,
  0x00, 0x00, 0x03, 0x00, 0x9e, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00, 0x1e,
  0x95, 0x98, 0x09, 0x00, 0x00, 0x01, 0x42, 0x01, 0x01, 0x04, 0x08, 0x00,
  0x00, 0x03, 0x00, 0x9e, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00, 0x1e, 0x90,
  0x11, 0x08, 0xb2, 0xca, 0xcd, 0x57, 0x95, 0xcd, 0x40, 0x80, 0x80, 0x01,
  0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x19, 0x08, 0x00,
  0x00, 0x01, 0x44, 0x01, 0xc1, 0x73, 0x18, 0x31, 0x08, 0x90 };

const uint8_t test_extradata_raw_h265_hvc1[] = {
  0x01, 0x04, 0x08, 0x00, 0x00, 0x00, 0x9e, 0x08, 0x00, 0x00, 0x00, 0x00,
  0x1e, 0xf0, 0x00, 0xfc, 0xff, 0xf8, 0xf8, 0x00, 0x00, 0x0f, 0x03, 0xa0,
  0x00, 0x01, 0x00, 0x17, 0x40, 0x01, 0x0c, 0x01, 0xff, 0xff, 0x04, 0x08,
  0x00, 0x00, 0x03, 0x00, 0x9e, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00, 0x1e,
  0x95, 0x98, 0x09, 0xa1, 0x00, 0x01, 0x00, 0x29, 0x42, 0x01, 0x01, 0x04,
  0x08, 0x00, 0x00, 0x03, 0x00, 0x9e, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00,
  0x1e, 0x90, 0x11, 0x08, 0xb2, 0xca, 0xcd, 0x57, 0x95, 0xcd, 0x40, 0x80,
  0x80, 0x01, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x19,
  0x08, 0xa2, 0x00, 0x01, 0x00, 0x08, 0x44, 0x01, 0xc1, 0x73, 0x18, 0x31,
  0x08, 0x90 };

static int compare_any(const uint8_t *p0, size_t s0, uint8_t prefix0,
                       const uint8_t *p1, size_t s1, uint8_t prefix1)
{
    hxxx_iterator_ctx_t it0, it1;
    hxxx_iterator_init(&it0, p0, s0, prefix0);
    hxxx_iterator_init(&it1, p1, s1, prefix1);
    const uint8_t *nal0 = NULL, *nal1 = NULL;
    size_t nalsz0 = 0, nalsz1 = 0;
    int b0, b1;
    for(;;)
    {
        b0 = it0.i_nal_length_size ? hxxx_iterate_next(&it0, &nal0, &nalsz0)
                                   : hxxx_annexb_iterate_next(&it0, &nal0, &nalsz0);
        b1 = it1.i_nal_length_size ? hxxx_iterate_next(&it1, &nal1, &nalsz1)
                                   : hxxx_annexb_iterate_next(&it1, &nal1, &nalsz1);
        assert(b0 == b1);
        if(b0 != b1)
            return 1;
        if(!b0)
            break;
        assert(nalsz0 == nalsz1);
        assert(memcmp(nal0, nal1, nalsz0) == 0);
    }
    return 0;
}

static void dump_hex(const char *s, const uint8_t *p, size_t sz)
{
    fprintf(stderr, "%s:\t", s);
    for(size_t i=0; i<sz; i++)
        fprintf(stderr, "0x%2.2x, ", p[i]);
    fprintf(stderr, "\n");
}

static int test_extrainit(vlc_fourcc_t codec,
                          const uint8_t *p_annexb, size_t i_annexb,
                          const uint8_t *p_xvc, size_t i_xvc)
{
    struct hxxx_helper hlpr;

    fprintf(stderr,"AnnexB extra init\n");
    hxxx_helper_init(&hlpr, NULL, codec, 0, 0);
    hxxx_helper_set_extra(&hlpr, p_annexb, i_annexb);
    assert(hlpr.i_input_nal_length_size == 0);
    assert(hlpr.i_output_nal_length_size == 0);

    block_t *b = hxxx_helper_get_extradata_block(&hlpr);
    if(!b)
        return 1;
    assert(compare_any(b->p_buffer, b->i_buffer, 0, p_annexb, i_annexb, 0) == 0);
    block_Release(b);
    hxxx_helper_clean(&hlpr);

    fprintf(stderr,"xVC1 extra init\n");
    hxxx_helper_init(&hlpr, NULL, codec, 0, 0);
    hxxx_helper_set_extra(&hlpr, p_xvc, i_xvc);
    assert(hlpr.i_input_nal_length_size);
    assert(hlpr.i_output_nal_length_size == 0);
    b = hxxx_helper_get_extradata_block(&hlpr);
    if(!b)
        return 1;
    assert(compare_any(b->p_buffer, b->i_buffer, 0, p_annexb, i_annexb, 0) == 0);
    block_Release(b);

    hxxx_helper_clean(&hlpr);

    return 0;
}

static int test_configuration_change(vlc_fourcc_t codec,
                                     const uint8_t *p_annexb, size_t i_annexb,
                                     size_t i_borkoffset)
{
    fprintf(stderr,"test_configuration_change\n");

    struct hxxx_helper hlpr;
    hxxx_helper_init(&hlpr, NULL, codec, 0, 0);

    block_t *b = block_Alloc(i_annexb);
    if(!b)
        return 1;
    memcpy(b->p_buffer, p_annexb, i_annexb);

    dump_hex("in", b->p_buffer, b->i_buffer);

    assert(!hxxx_helper_has_new_config(&hlpr));
    b = hxxx_helper_process_block(&hlpr, b);
    if(!b)
        return 1;

    /* now have a config */
    assert(hxxx_helper_has_new_config(&hlpr));

    b = hxxx_helper_process_block(&hlpr, b);
    if(!b)
        return 1;

    /* should not have a new config */
    assert(!hxxx_helper_has_new_config(&hlpr));

    /* patch our SPS */
    b->p_buffer[i_borkoffset] = ~ b->p_buffer[i_borkoffset];
    dump_hex("in new", b->p_buffer, b->i_buffer);
    b = hxxx_helper_process_block(&hlpr, b);
    if(!b)
        return 1;

    /* now have a new SPS/PPS config */
    assert(hxxx_helper_has_new_config(&hlpr));

    block_Release(b);

    hxxx_helper_clean(&hlpr);

    return 0;
}

static int test_any(struct hxxx_helper *hlpr,
                    const uint8_t *p_in, size_t i_in,
                    const uint8_t *p_out, size_t i_out,
                    const uint8_t *p_extraout, size_t i_extraout)
{
    block_t *b = block_Alloc(i_in);
    if(!b)
        return 1;
    memcpy(b->p_buffer, p_in, i_in);

    dump_hex("in", b->p_buffer, b->i_buffer);

    assert(!hxxx_helper_has_new_config(hlpr));
    b = hxxx_helper_process_block(hlpr, b);
    if(!b)
        return 1;
    assert(hxxx_helper_has_new_config(hlpr));

    dump_hex("out", b->p_buffer, b->i_buffer);

    if(compare_any(b->p_buffer, b->i_buffer, hlpr->i_output_nal_length_size,
                   p_out, i_out, hlpr->i_output_nal_length_size))
    {
        block_Release(b);
        return 1;
    }

    block_Release(b);

    b = hxxx_helper_get_extradata_block(hlpr);
    if(!b)
        return 1;

    dump_hex("extra", b->p_buffer, b->i_buffer);
    if(hlpr->i_output_nal_length_size)
    {
        if(b->i_buffer != i_extraout || memcmp(b->p_buffer, p_extraout, i_extraout))
        {
            assert(b->i_buffer == i_extraout);
            assert(!memcmp(b->p_buffer, p_extraout, i_extraout));
            block_Release(b);
            return 1;
        }
    }
    else if(compare_any(b->p_buffer, b->i_buffer, 0, p_extraout, i_extraout, 0))
    {
        block_Release(b);
        return 1;
    }

    block_Release(b);

    return 0;
}

#define RUN_TEST(codec, source0, prefix0, source1, prefix1) \
    do\
    {\
        struct hxxx_helper hlpr;\
        hxxx_helper_init(&hlpr, NULL, codec, prefix0, prefix1);\
        ret = test_any(&hlpr, \
                       test_samples_raw_##source0, sizeof(test_samples_raw_##source0),\
                       test_samples_raw_##source1, sizeof(test_samples_raw_##source1),\
                       test_extradata_raw_##source1, sizeof(test_extradata_raw_##source1));\
        hxxx_helper_clean(&hlpr);\
        if(ret) return ret;\
    } while(0)

static int test_annexb(void)
{
    int ret;
    fprintf(stderr,"H264\n");
    fprintf(stderr,"AnnexB -> AnnexB\n");
    RUN_TEST(VLC_CODEC_H264, h264_annexb, 0, h264_annexb, 0);
    fprintf(stderr,"AVC1 -> AVC1\n");
    RUN_TEST(VLC_CODEC_H264, h264_avc1, 4, h264_avc1, 4);
    fprintf(stderr,"AVC1 -> AnnexB\n");
    RUN_TEST(VLC_CODEC_H264, h264_avc1, 4, h264_annexb, 0);
    fprintf(stderr,"AnnexB -> AVC1\n");
    RUN_TEST(VLC_CODEC_H264, h264_annexb, 0, h264_avc1, 4);

    ret = test_extrainit(VLC_CODEC_H264,
                test_extradata_raw_h264_annexb, sizeof(test_extradata_raw_h264_annexb),
                test_extradata_raw_h264_avc1, sizeof(test_extradata_raw_h264_avc1));
    if(ret) return ret;

    fprintf(stderr,"HEVC\n");
    fprintf(stderr,"AnnexB -> AnnexB\n");
    RUN_TEST(VLC_CODEC_HEVC, h265_annexb, 0, h265_annexb, 0);
    fprintf(stderr,"HVC1 -> HVC1\n");
    RUN_TEST(VLC_CODEC_HEVC, h265_hvc1, 4, h265_hvc1, 4);
    fprintf(stderr,"HVC1 -> AnnexB\n");
    RUN_TEST(VLC_CODEC_HEVC, h265_hvc1, 4, h265_annexb, 0);
    fprintf(stderr,"AnnexB -> HVC1\n");
    RUN_TEST(VLC_CODEC_HEVC, h265_annexb, 0, h265_hvc1, 4);

    ret = test_extrainit(VLC_CODEC_HEVC,
                test_extradata_raw_h265_annexb, sizeof(test_extradata_raw_h265_annexb),
                test_extradata_raw_h265_hvc1, sizeof(test_extradata_raw_h265_hvc1));
    if(ret) return ret;

    ret = test_configuration_change(VLC_CODEC_H264,
                test_samples_raw_h264_annexb, sizeof(test_samples_raw_h264_annexb), 4+2); // poke constraints
    if(ret) return ret;

    ret = test_configuration_change(VLC_CODEC_HEVC,
                test_samples_raw_h265_annexb, sizeof(test_samples_raw_h265_annexb), 4+2); // poke profiletieridc
    if(ret) return ret;

    return 0;
}


int main(void)
{
    test_init();

    return test_annexb();
}

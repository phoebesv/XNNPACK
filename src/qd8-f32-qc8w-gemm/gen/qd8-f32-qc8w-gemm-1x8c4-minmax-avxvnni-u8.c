// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/MRx8c4-avxvnni.c.in
//   Generator: tools/xngen
//
// Copyright 2023 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <stdint.h>

#include <immintrin.h>

#include <xnnpack/gemm.h>
#include <xnnpack/intrinsics-polyfill.h>
#include <xnnpack/math.h>
#include <xnnpack/unaligned.h>
#include <xnnpack/prefetch.h>


void xnn_qd8_f32_qc8w_gemm_minmax_ukernel_1x8c4__avxvnni_u8(
    size_t mr,
    size_t nc,
    size_t kc,
    const int8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    float* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_f32_minmax_params params[restrict XNN_MIN_ELEMENTS(1)],
    const struct xnn_qd8_quantization_params quantization_params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(mr != 0);
  assert(mr <= 1);
  assert(nc != 0);
  assert(kc != 0);
  assert(kc % sizeof(int8_t) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  kc = round_up_po2(kc, 4 * sizeof(int8_t));
  const int8_t* a0 = a;
  float* c0 = c;

  const __m256i vinput_zero_point0 = _mm256_set1_epi32((int) quantization_params[0].zero_point + 128);
  const __m256 voutput_min = _mm256_set1_ps(params->avxvnni.min);
  const __m256 voutput_max = _mm256_set1_ps(params->avxvnni.max);
  const __m256i vsign_mask = _mm256_set1_epi8(params->avxvnni.sign_mask);
  do {
    const __m256i vksum01234567 = _mm256_load_si256(w);
    __m256i vacc0x0x01234567 = _mm256_mullo_epi32(vksum01234567, vinput_zero_point0);
    w = (const int32_t*) w + 8;

    size_t k = kc;
    while (k >= 32 * sizeof(int8_t)) {
      __m256i va0x0x0123 = _mm256_set1_epi32((int) unaligned_load_u32(a0 + 0));
      __m256i va0x1x0123 = _mm256_set1_epi32((int) unaligned_load_u32(a0 + 4));
      __m256i va0x2x0123 = _mm256_set1_epi32((int) unaligned_load_u32(a0 + 8));
      __m256i va0x3x0123 = _mm256_set1_epi32((int) unaligned_load_u32(a0 + 12));
      __m256i va0x4x0123 = _mm256_set1_epi32((int) unaligned_load_u32(a0 + 16));
      __m256i va0x5x0123 = _mm256_set1_epi32((int) unaligned_load_u32(a0 + 20));
      __m256i va0x6x0123 = _mm256_set1_epi32((int) unaligned_load_u32(a0 + 24));
      __m256i va0x7x0123 = _mm256_set1_epi32((int) unaligned_load_u32(a0 + 28));
      a0 += 32;

      va0x0x0123 = _mm256_xor_si256(va0x0x0123, vsign_mask);
      va0x1x0123 = _mm256_xor_si256(va0x1x0123, vsign_mask);
      va0x2x0123 = _mm256_xor_si256(va0x2x0123, vsign_mask);
      va0x3x0123 = _mm256_xor_si256(va0x3x0123, vsign_mask);
      va0x4x0123 = _mm256_xor_si256(va0x4x0123, vsign_mask);
      va0x5x0123 = _mm256_xor_si256(va0x5x0123, vsign_mask);
      va0x6x0123 = _mm256_xor_si256(va0x6x0123, vsign_mask);
      va0x7x0123 = _mm256_xor_si256(va0x7x0123, vsign_mask);

      const __m256i vb0x01234567 = _mm256_load_si256((const __m256i*) ((const int8_t*) w + 0));
      const __m256i vb1x01234567 = _mm256_load_si256((const __m256i*) ((const int8_t*) w + 32));
      const __m256i vb2x01234567 = _mm256_load_si256((const __m256i*) ((const int8_t*) w + 64));
      const __m256i vb3x01234567 = _mm256_load_si256((const __m256i*) ((const int8_t*) w + 96));
      const __m256i vb4x01234567 = _mm256_load_si256((const __m256i*) ((const int8_t*) w + 128));
      const __m256i vb5x01234567 = _mm256_load_si256((const __m256i*) ((const int8_t*) w + 160));
      const __m256i vb6x01234567 = _mm256_load_si256((const __m256i*) ((const int8_t*) w + 192));
      const __m256i vb7x01234567 = _mm256_load_si256((const __m256i*) ((const int8_t*) w + 224));
      w = (const int8_t*) w + 256;

      vacc0x0x01234567 = _mm256_dpbusd_avx_epi32(vacc0x0x01234567, va0x0x0123, vb0x01234567);
      vacc0x0x01234567 = _mm256_dpbusd_avx_epi32(vacc0x0x01234567, va0x1x0123, vb1x01234567);
      vacc0x0x01234567 = _mm256_dpbusd_avx_epi32(vacc0x0x01234567, va0x2x0123, vb2x01234567);
      vacc0x0x01234567 = _mm256_dpbusd_avx_epi32(vacc0x0x01234567, va0x3x0123, vb3x01234567);
      vacc0x0x01234567 = _mm256_dpbusd_avx_epi32(vacc0x0x01234567, va0x4x0123, vb4x01234567);
      vacc0x0x01234567 = _mm256_dpbusd_avx_epi32(vacc0x0x01234567, va0x5x0123, vb5x01234567);
      vacc0x0x01234567 = _mm256_dpbusd_avx_epi32(vacc0x0x01234567, va0x6x0123, vb6x01234567);
      vacc0x0x01234567 = _mm256_dpbusd_avx_epi32(vacc0x0x01234567, va0x7x0123, vb7x01234567);

      k -= 32 * sizeof(int8_t);
    }
    while (k != 0) {
      __m256i va0x0123 = _mm256_set1_epi32((int) unaligned_load_u32(a0));
      a0 += 4;

      va0x0123 = _mm256_xor_si256(va0x0123, vsign_mask);

      const __m256i vb01234567 = _mm256_load_si256(w);

      vacc0x0x01234567 = _mm256_dpbusd_avx_epi32(vacc0x0x01234567, va0x0123, vb01234567);

      w = (const int8_t*) w + 32;
      k -= 4 * sizeof(int8_t);
    }

    __m256 vout0x01234567 = _mm256_cvtepi32_ps(vacc0x0x01234567);

    vout0x01234567 = _mm256_mul_ps(vout0x01234567, _mm256_set1_ps(quantization_params[0].inv_scale));

    const __m256 vfilter_output_scale01234567 = _mm256_load_ps((const float*) w);
    const __m256 vbias01234567 = _mm256_load_ps((const float*) w + 8);
    w = (const float*) w + 16;

    vout0x01234567 = _mm256_fmadd_ps(vout0x01234567, vfilter_output_scale01234567, vbias01234567);

    vout0x01234567 = _mm256_max_ps(vout0x01234567, voutput_min);

    vout0x01234567 = _mm256_min_ps(vout0x01234567, voutput_max);

    if(nc >= 8) {
      _mm256_storeu_ps(c0, vout0x01234567);
      a0 = (const int8_t*) ((uintptr_t) a0 - kc);
      c0 = (float*) ((uintptr_t) c0 + cn_stride);
      nc -= 8;
    } else {
      __m128 vout0x0123 = _mm256_castps256_ps128(vout0x01234567);
      if (nc & 4) {
        _mm_storeu_ps(c0, vout0x0123);
        c0 += 4;
        vout0x0123 = _mm256_extractf128_ps(vout0x01234567, 1);
      }
      if (nc & 2) {
        _mm_storel_pi((__m64*) c0, vout0x0123);
        c0 += 2;
        vout0x0123 = _mm_movehl_ps(vout0x0123, vout0x0123);
      }
      if (nc & 1) {
        _mm_store_ss(c0, vout0x0123);
      }
      nc = 0;
    }
  } while (nc != 0);
}

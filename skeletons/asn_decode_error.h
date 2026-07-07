/*
 * Structured decode-error reporting.
 *
 * Complements asn_dec_rval_t.failed_type (which only ever carries the single,
 * deepest ASN.1 type name) with the containing field name, its index within
 * the enclosing SEQUENCE/SEQUENCE OF/CHOICE, and the bit offset at which the
 * failure was detected. Intended for surfacing actionable decode-failure
 * detail to callers (e.g. JNI wrappers) without changing existing decoder
 * function signatures.
 */
#ifndef	_ASN_DECODE_ERROR_H_
#define	_ASN_DECODE_ERROR_H_

#include <asn_system.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct asn_decode_error_info_s {
    int has_error;
    const char *type_name;   /* Type name of the SEQUENCE/CHOICE that observed the failure */
    const char *field_name;  /* Name of the failing member, or NULL for SEQUENCE OF/SET OF elements */
    long element_index;      /* 1-based member/element index, or -1 if not applicable */
    size_t bit_offset;       /* Bits consumed so far in this decode operation */
    int code;                /* asn_dec_rval_code_e: RC_OK / RC_WMORE / RC_FAIL */
    const char *src_file;    /* usdot-asn1c runtime file recording the failure (server-side diagnostics only) */
    int src_line;
} asn_decode_error_info_t;

/*
 * Clears any decode error recorded for the current thread.
 * Must be called at the start of every top-level decode operation
 * (uper_decode()) so a threadpool-reused thread never leaks a previous
 * request's error into a new one.
 */
void asn_clear_decode_error(void);

/*
 * Records decode-failure context for the current thread, but only if no
 * error has already been recorded since the last asn_clear_decode_error().
 * Decode failures are detected bottom-up (the deepest, most specific field
 * fails first and that failure is then returned up through its parents), so
 * first-write-wins naturally keeps the most specific context instead of
 * letting an outer SEQUENCE/CHOICE overwrite it while the failure unwinds.
 */
void asn_set_decode_error(const char *type_name, const char *field_name,
                          long element_index, size_t bit_offset, int code,
                          const char *src_file, int src_line);

/*
 * Returns the calling thread's last recorded decode error, or NULL if
 * asn_clear_decode_error() was called more recently than any
 * asn_set_decode_error().
 */
const asn_decode_error_info_t *asn_get_last_decode_error(void);

#ifdef __cplusplus
}
#endif

#endif	/* _ASN_DECODE_ERROR_H_ */
